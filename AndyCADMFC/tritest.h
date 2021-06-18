#include "renderer/fixed_func.h"

using namespace swr;
using namespace swr::detail;

		struct { int x0, y0, x1, y1; } clip_rect_;
		struct { int offset; int mask; } interlace_;
		unsigned varying_count_;

		inline bool ilace_drawit(interlace_ v,int y)
		{
			return ((y + v.offset) & interlace_.mask) == 0;
		}

		// Type definitions
		struct Vertex {
			int x, y; // in 28.4 fixed point
			int z; // range from 0 to 0x7fffffff
			int w; // in 16.16 fixed point
			int varyings[8];
		};


	int invert(int value)
		{
			// tells how many bits of precision are lost. the minimum value is 2.
			// larger values make the function faster but less accurate.
			static const unsigned bit_loss = 2;
			
			if ((value >> bit_loss) == 0) return 0xffffffff;

		#ifndef ARM940
			return (1 << (32 - bit_loss)) / (value >> bit_loss);
		#else
			int q, r;
			divmodsi(1 << (32 - bit_loss), value >> bit_loss, &q, &r);
			return q;
		#endif
		}
				struct FragmentData {
			int z;
			int varyings[8];
		};

		// Use for perspective spans. Defined here for convenience
		struct FragmentDataPerspective {
			int oow;
			FragmentData fd;
		};

		void compute_gradients(
			int DX12, int DY12, // deltas in x and y to the other vertices
			int DX31, int DY31,
			int inv_area, // inverse of area in 8.24
			int z0, int z1, int z2, // values at the vertices for which to 
			                        // compute gradients
			int &dx, int &dy) // result will be stored here
		{
			const int DZ12 = z0 - z1;
			const int DZ31 = z2 - z0;

			const int a = (__int64)DY12 * DZ31 - (__int64)DZ12 * DY31;
			const int b = (__int64)DZ12 * DX31 - (__int64)DX12 * DZ31;

			dx = (a * -inv_area) >> 28;
			dy = (b * -inv_area) >> 28;
		};

			struct {
		int w;
		int h;
	} perspective_threshold_;
bool perspective_correction_;

			// computes the gradients of the varyings to be used for stepping
			struct Gradients {
				FragmentDataPerspective dx;
				FragmentDataPerspective dy;

				Gradients(const Vertex &v1, const Vertex &v2, const Vertex &v3,
					int DX12, int DY12, int DX31, int DY31, int inv_area)
				{
					if (FragSpan::interpolate_z)
						compute_gradients(DX12, DY12, DX31, DY31, 
							inv_area, v1.z, v2.z, v3.z, dx.fd.z, dy.fd.z);

					if (FragSpan::varying_count) {
						int invw1 = invert(v1.w);
						int invw2 = invert(v2.w);
						int invw3 = invert(v3.w);

						compute_gradients(DX12, DY12, DX31, DY31, 
							inv_area, invw1, invw2, invw3, dx.oow, dy.oow);

						for (unsigned i = 0; i < FragSpan::varying_count; ++i) {
							int var1 = fixmul<16>(v1.varyings[i], invw1);
							int var2 = fixmul<16>(v2.varyings[i], invw2);
							int var3 = fixmul<16>(v3.varyings[i], invw3);

							compute_gradients(DX12, DY12, DX31, DY31, 
								inv_area, var1, var2, var3, 
								dx.fd.varyings[i], dy.fd.varyings[i]);
						}
					}
				}
			};

			// Edge structure used to walk the edge of the triangle and fill the
			// scanlines
			struct Edge {
				int x, x_step, numerator, denominator, error_term; // DDA info for x
				int y, height;

				FragmentDataPerspective fragment_data;
				FragmentDataPerspective fragment_step;

				const Gradients& grad;		

				Edge(const Gradients &grad_, const Vertex* top, const Vertex *bottom)
					: grad(grad_)
				{
					y = ceil28_4(top->y);
					int yend = ceil28_4(bottom->y);
					height = yend - y;

					if (height) {
						int dn = bottom->y - top->y;
						int dm = bottom->x - top->x;

						int initial_numerator = dm*16*y - dm*top->y + 
							dn*top->x - 1 + dn*16;
						floor_divmod(initial_numerator, dn*16, &x, &error_term);
						floor_divmod(dm*16, dn*16, &x_step, &numerator);
						denominator = dn*16;

						int y_prestep = y*16 - top->y;
						int x_prestep = x*16 - top->x;
						
						#define PRESTEP(VAR) \
							(((y_prestep * grad.dy.VAR) >> 4) + \
							((x_prestep * grad.dx.VAR) >> 4))
							
						#define STEP(VAR) \
							(x_step * grad.dx.VAR + grad.dy.VAR)

						if (FragSpan::interpolate_z) {
							fragment_data.fd.z = top->z + PRESTEP(fd.z);
							fragment_step.fd.z = STEP(fd.z);
						}

						if (FragSpan::varying_count) {
							int invw = invert(top->w);

							fragment_data.oow = invw + PRESTEP(oow);
							fragment_step.oow = STEP(oow);

							for (unsigned i = 0; i < FragSpan::varying_count; ++i) {
								fragment_data.fd.varyings[i] = 
									fixmul<16>(top->varyings[i], invw) + PRESTEP(fd.varyings[i]);
								fragment_step.fd.varyings[i] = STEP(fd.varyings[i]);
							}
						}

						#undef STEP
						#undef PRESTEP
					}
				}

				void step(bool step_varyings)
				{
					x += x_step; y++; height--;

					if (step_varyings) 
						FRAGMENTDATA_PERSPECTIVE_APPLY(FragSpan, fragment_data, +=, fragment_step);

					error_term += numerator;
					if (error_term >= denominator) {
						x++;
						if (step_varyings) 
							FRAGMENTDATA_PERSPECTIVE_APPLY(FragSpan, fragment_data, +=, grad.dx);
						error_term -= denominator;
					}
				}
			};


			struct scanline {
				static void draw(const Edge *left, const Edge *right, int cl, int cr)
				{
					int y = left->y;
					int l = left->x;
					int r = std::min(right->x, cr);
					const Gradients &grad = left->grad;

					if (r - l <= 0) return;

					FragmentDataPerspective fdp;
					FRAGMENTDATA_PERSPECTIVE_APPLY(FragSpan, fdp, =, left->fragment_data);

					// skip pixels left of the clipping rectangle
					if (l < cl) {
						int d = cl - l;
						FRAGMENTDATA_PERSPECTIVE_APPLY(FragSpan, fdp, += d *, grad.dx);
						l = cl;
					}

					FragSpan::perspective_span(l, y, fdp, grad.dx, r - l);
				}
			};
