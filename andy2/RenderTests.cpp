// RenderTests.cpp — see RenderTests.h.
//
// Each case builds one figure and applies colour, texture and transparency
// through the same calls the UI makes (setLcolor from the colour toolbar,
// setTexture from the pattern buttons, the "Transparency" notification from
// the Transparency dialog). The figure is drawn into an off-screen bitmap
// with the view's mapping, once with GDI and once with Direct2D, and pixels
// are checked at known places.

#include "Stdafx.h"
#include "cad.h"
#include "cadDoc.h"
#include "cadView.h"
#include "Draw.h"
#include "Image.h"
#include "line.h"
#include "Libs.h"
#include "Cercle.h"
#include "ImageFile.h"
#include "RenderTests.h"
#include "render/D2DRenderer.h"
#include "render/ViewRenderer.h"
#include "MainFrm.h"
#include "RecPattern.h"
#include "resource.h"

#include <cmath>
#include <functional>
#include <string>
#include <vector>

namespace {

const COLORREF kFill = RGB(200, 40, 40);
const COLORREF kLine = RGB(0, 0, 0);
const COLORREF kWhite = RGB(255, 255, 255);
// Texels of tests/drawings/texture_checker.png (64x64, 8x8 cells: red/blue
// on top, green/yellow below, transparent 16x16 block in the middle).
const COLORREF kBlue = RGB(30, 60, 220), kRed = RGB(220, 30, 30), kGreen = RGB(30, 170, 60);

struct Sample { double tx, ty; COLORREF want; const char* what; };

COLORREF Blend(COLORREF c, COLORREF bg, double a) {
	return RGB((int)lround((1 - a) * GetRValue(bg) + a * GetRValue(c)),
	           (int)lround((1 - a) * GetGValue(bg) + a * GetGValue(c)),
	           (int)lround((1 - a) * GetBValue(bg) + a * GetBValue(c)));
}

bool Near(COLORREF a, COLORREF b, int tol) {
	return abs(GetRValue(a) - GetRValue(b)) <= tol && abs(GetGValue(a) - GetGValue(b)) <= tol &&
	       abs(GetBValue(a) - GetBValue(b)) <= tol;
}

CString Hex(COLORREF c) {
	CString s;
	s.Format(_T("#%02X%02X%02X"), GetRValue(c), GetGValue(c), GetBValue(c));
	return s;
}

struct Shape {
	const char* name;
	std::function<CFigure*()> make;
	double x0, y0, x1, y1;          // world bounding box (texture coordinates span it)
	bool textured = true;           // texture cases apply
};

enum Case { Solid, Solid50, Tex, Tex50, Tile, Multiply, Decal50, FillOnly, CaseCount };
const char* kCaseName[] = { "solid colour", "colour, 50% transparency", "texture", "texture, 50% transparency", "tiled texture",
                            "texture, multiply with fill colour", "texture, decal at 50%", "texture, fill colour only" };
// Texture blend mode per case (Format > Texture), -1 = leave as set by setTexture.
int CaseBlend(Case c) { return c == Multiply ? 3 : c == Decal50 ? 2 : c == FillOnly ? 4 : -1; }
bool CaseHas50(Case c) { return c == Solid50 || c == Tex50 || c == Decal50; }
bool CaseTextured(Case c) { return c != Solid && c != Solid50; }

COLORREF Mul(COLORREF a, COLORREF b) {
	return RGB(GetRValue(a) * GetRValue(b) / 255, GetGValue(a) * GetGValue(b) / 255, GetBValue(a) * GetBValue(b) / 255);
}

struct Result { CString status; CString detail; };

// Off-screen render of one figure with the view's mapping.
struct Canvas {
	CDC mem;
	CBitmap bmp;
	CBitmap* old = nullptr;
	CRect rc;
	Canvas(CCadView* view, CDC* ref) {
		view->GetClientRect(&rc);
		mem.CreateCompatibleDC(ref);
		bmp.CreateCompatibleBitmap(ref, rc.Width(), rc.Height());
		old = mem.SelectObject(&bmp);
		mem.FillSolidRect(0, 0, rc.Width(), rc.Height(), kWhite);
		view->OnPrepareDC(&mem);
	}
	~Canvas() { mem.SelectObject(old); }
	COLORREF At(double wx, double wy) {
		CVector w(wx, wy, 0, 1);
		CPoint l = w;
		mem.LPtoDP(&l, 1);
		int sm = mem.SetMapMode(MM_TEXT);
		CPoint vo = mem.SetViewportOrg(0, 0);
		CPoint wo = mem.SetWindowOrg(0, 0);
		COLORREF c = mem.GetPixel(l.x, l.y);
		mem.SetWindowOrg(wo);
		mem.SetViewportOrg(vo);
		mem.SetMapMode(sm);
		return c;
	}
	CPoint Device(double wx, double wy) {
		CVector w(wx, wy, 0, 1);
		CPoint l = w;
		mem.LPtoDP(&l, 1);
		return l;
	}
	// Crop around the shape and save it as PNG (CImageFile).
	void SavePng(const CString& path, const Shape& s) {
		CPoint a = Device(s.x0, s.y0), b = Device(s.x1, s.y1);
		int l = min(a.x, b.x) - 10, t = min(a.y, b.y) - 10, r = max(a.x, b.x) + 10, btm = max(a.y, b.y) + 10;
		l = max(l, 0); t = max(t, 0); r = min(r, rc.Width()); btm = min(btm, rc.Height());
		int w = r - l, h = btm - t;
		if (w <= 0 || h <= 0) return;
		BITMAPINFO bi = {};
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = rc.Width();
		bi.bmiHeader.biHeight = -rc.Height();
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;
		bi.bmiHeader.biCompression = BI_RGB;
		std::vector<uint32_t> all((size_t)rc.Width() * rc.Height());
		mem.SelectObject(old);
		GetDIBits(mem.GetSafeHdc(), (HBITMAP)bmp.GetSafeHandle(), 0, rc.Height(), all.data(), &bi, DIB_RGB_COLORS);
		mem.SelectObject(&bmp);
		std::vector<uint32_t> crop((size_t)w * h);
		for (int y = 0; y < h; ++y)
			for (int x = 0; x < w; ++x)
				crop[(size_t)y * w + x] = all[(size_t)(t + y) * rc.Width() + (l + x)] | 0xFF000000u;
		CImageFile f;
		f.Assign(w, h, crop.data());
		f.Save(std::wstring(CStringW(path)));
	}
};

void ApplyCase(CFigure* f, Case c, CDC* hdc, const CString& texture) {
	f->setLcolor(hdc, kLine, kFill);                     // colour toolbar
	if (CaseTextured(c))
		f->setTexture(texture, hdc);                     // pattern buttons
	if (c == Tile)
		f->setTiled(true);                               // Format > Texture > Tile
	if (CaseBlend(c) >= 0)
		f->setTextureBlend(CaseBlend(c));                // Format > Texture > blend mode
	if (CaseHas50(c)) {                                  // Transparency dialog, 50%
		float level = 0.5f;
		void* param[7] = { &level };
		f->SendNotify(_T("Transparency"), param);
	}
}

// Texel (tx, ty) of the 64x64 texture stretched over the shape's box.
void TexelToWorld(const Shape& s, double tx, double ty, double& wx, double& wy) {
	wx = s.x0 + (s.x1 - s.x0) * (tx + 0.5) / 64.0;
	wy = s.y1 - (s.y1 - s.y0) * (ty + 0.5) / 64.0;
}

Result Check(Canvas& cv, const Shape& s, Case c, COLORREF fill = kFill) {
	Result r;
	std::vector<Sample> samples;
	double cx = (s.x0 + s.x1) / 2, cy = (s.y0 + s.y1) / 2;
	if (c == Multiply) {
		samples.push_back({ 20, 20, Mul(kBlue, fill), "blue texel x fill" });
		samples.push_back({ 44, 20, Mul(kRed, fill), "red texel x fill" });
		samples.push_back({ 20, 44, Mul(kGreen, fill), "green texel x fill" });
	} else if (c == Decal50) {
		samples.push_back({ 20, 20, Blend(fill, kBlue, 0.5), "blue texel half fill" });
		samples.push_back({ 44, 20, Blend(fill, kRed, 0.5), "red texel half fill" });
		samples.push_back({ 20, 44, Blend(fill, kGreen, 0.5), "green texel half fill" });
	} else if (c == Solid || c == Solid50 || c == FillOnly) {
		COLORREF want = c == Solid50 ? Blend(fill, kWhite, 0.5) : fill;
		samples.push_back({ -1, -1, want, "centre" });
		samples.push_back({ -2, -2, want, "off-centre" });
	} else if (c == Tex || c == Tex50) {
		double a = c == Tex ? 1.0 : 0.5;
		samples.push_back({ 20, 20, Blend(kBlue, kWhite, a), "blue texel" });
		samples.push_back({ 44, 20, Blend(kRed, kWhite, a), "red texel" });
		samples.push_back({ 20, 44, Blend(kGreen, kWhite, a), "green texel" });
		samples.push_back({ 32, 32, kWhite, "transparent texel" });
	}
	if (c == Tile) {
		// Repeating: the same colour one image width apart, and not uniform.
		CPoint d0 = cv.Device(cx, cy);
		int sm = cv.mem.SetMapMode(MM_TEXT);
		CPoint vo = cv.mem.SetViewportOrg(0, 0), wo = cv.mem.SetWindowOrg(0, 0);
		COLORREF a0 = cv.mem.GetPixel(d0.x, d0.y), a1 = 0;
		int distinct = 0;
		COLORREF seen[8] = {};
		int nseen = 0;
		for (int k = 0; k < 64; k += 4) {
			COLORREF p = cv.mem.GetPixel(d0.x + k, d0.y);
			bool known = false;
			for (int q = 0; q < nseen; ++q) known |= Near(seen[q], p, 10);
			if (!known && nseen < 8) seen[nseen++] = p;
		}
		distinct = nseen;
		cv.mem.SetWindowOrg(wo); cv.mem.SetViewportOrg(vo); cv.mem.SetMapMode(sm);
		bool pattern = distinct >= 3;
		bool notWhite = !Near(a0, kWhite, 3) || distinct >= 3;
		r.status = (pattern && notWhite) ? _T("PASS") : _T("FAIL");
		r.detail.Format(_T("%d distinct colours along 64 px"), distinct);
		(void)a1;
		return r;
	}
	int bad = 0;
	for (const Sample& sm : samples) {
		double wx, wy;
		if (sm.tx == -1) { wx = cx; wy = cy; }
		else if (sm.tx == -2) { wx = cx + (s.x1 - s.x0) * 0.2; wy = cy - (s.y1 - s.y0) * 0.15; }
		else TexelToWorld(s, sm.tx, sm.ty, wx, wy);
		COLORREF got = cv.At(wx, wy);
		if (!Near(got, sm.want, 24)) {
			++bad;
			CString d;
			d.Format(_T("%s: got %s want %s; "), CString(sm.what), (LPCTSTR)Hex(got), (LPCTSTR)Hex(sm.want));
			r.detail += d;
		}
	}
	r.status = bad == 0 ? _T("PASS") : _T("FAIL");
	if (bad == 0) r.detail.Format(_T("%d points ok"), (int)samples.size());
	return r;
}

} // namespace

bool RunRenderTestsIfRequested(CCadView* view)
{
	char* dir = nullptr;
	size_t n = 0;
	if (_dupenv_s(&dir, &n, "ANDYCAD_RUN_RENDER_TESTS") != 0 || !dir || !*dir) { free(dir); return false; }
	CString outDir(dir);
	free(dir);
	CreateDirectory(outDir, nullptr);
	CString texture = outDir + _T("\\texture_checker.png");
	if (GetFileAttributes(texture) == INVALID_FILE_ATTRIBUTES) {
		// The checker texture: same pixels as tests/drawings/texture_checker.png.
		std::vector<uint32_t> px(64 * 64);
		for (int y = 0; y < 64; ++y)
			for (int x = 0; x < 64; ++x) {
				bool odd = ((x / 8) + (y / 8)) & 1;
				COLORREF c = y < 32 ? (odd ? kRed : kBlue) : (odd ? kGreen : RGB(240, 210, 40));
				uint32_t a = (x >= 24 && x < 40 && y >= 24 && y < 40) ? 0 : 0xFF;
				px[y * 64 + x] = (a << 24) | (GetRValue(c) << 16) | (GetGValue(c) << 8) | GetBValue(c);
			}
		CImageFile f;
		f.Assign(64, 64, px.data());
		f.Save(std::wstring(CStringW(texture)));
	}

	// Direct2D on for this run (the renderer reads the setting once).
	_putenv_s("ANDYCAD_RENDERER", "d2d");
	acr::D2DRenderer* d2d = acr::ViewRenderer();

	std::vector<Shape> shapes = {
		{ "rectangle", []() { CRectangle* r = new CRectangle; r->setCorners(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1)); return (CFigure*)r; }, -150, -100, 150, 100 },
		{ "circle", []() { return (CFigure*)new CCercle(CVector(0, 0, 0, 1), 100); }, -100, -100, 100, 100 },
		{ "polygon", []() {
			CLine* l = new CLine;
			std::vector<std::vector<CVector>> loops(1);
			for (int k = 0; k < 6; ++k) loops[0].push_back(CVector(110 * cos(k * 3.14159265 / 3), 110 * sin(k * 3.14159265 / 3), 0, 1));
			l->setFromLoops(loops, kFill);
			return (CFigure*)l; }, -110, -95.26, 110, 95.26 },
		{ "image", []() { CImage* i = new CImage; i->buildFromRect(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1)); return (CFigure*)i; }, -150, -100, 150, 100 },
		{ "block (rectangle inside)", []() {
			CLibS* lib = new CLibS;
			CRectangle r; r.setCorners(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1));
			lib->add(&r); lib->updatecore(); return (CFigure*)lib; }, -150, -100, 150, 100 },
	};

	CDC* hdc = view->GetDC();
	view->OnPrepareDC(hdc);
	CString md, csv = _T("object,case,renderer,status,detail\r\n");
	md = _T("# Render tests: colour, texture, transparency\r\n\r\n");
	md += _T("Each object gets its fill through the UI's own calls (colour toolbar: setLcolor; pattern buttons: setTexture; Transparency dialog: the \"Transparency\" notification at 50%), ")
	      _T("is drawn with GDI and with Direct2D, and pixels are checked against the intended result on a white background.\r\n\r\n");
	md += _T("| Object | Case | GDI | Direct2D |\r\n| --- | --- | --- | --- |\r\n");
	int pass[2] = { 0, 0 }, total[2] = { 0, 0 };
	for (const Shape& s : shapes) {
		for (int c = 0; c < CaseCount; ++c) {
			CString cells[2];
			for (int rdr = 0; rdr < 2; ++rdr) {
				CFigure* f = nullptr;
				Result res;
				try {
					f = s.make();
					ApplyCase(f, (Case)c, hdc, texture);
					Canvas cv(view, hdc);
					bool usedD2D = false;
					if (rdr == 0) {
						f->draw(&cv.mem);
					} else if (d2d && f->canRender() && acr::BeginViewBatch(d2d, cv.mem.GetSafeHdc())) {
						f->draw(d2d);
						acr::EndViewBatch(d2d);
						usedD2D = true;
					} else if (d2d && f->isRenderGroup()) {
						// As CDraw::display does: children through Direct2D where they can.
						usedD2D = true;
						for (int k = 0; k < f->renderChildCount(); ++k) {
							CFigure* ch = f->renderChild(k);
							if (ch->canRender() && acr::BeginViewBatch(d2d, cv.mem.GetSafeHdc())) {
								ch->draw(d2d);
								acr::EndViewBatch(d2d);
							} else {
								ch->draw(&cv.mem);
								usedD2D = false;
							}
						}
					} else {
						f->draw(&cv.mem);   // the figure falls back to GDI in Direct2D mode
					}
					res = Check(cv, s, (Case)c);
					if (rdr == 1 && !usedD2D) res.detail = _T("(drawn by GDI fallback) ") + res.detail;
					CString png;
					png.Format(_T("%s\\%s_%d_%s.png"), (LPCTSTR)outDir, (LPCTSTR)CString(s.name).Left(5), c, rdr ? _T("d2d") : _T("gdi"));
					png.Replace(_T(" "), _T("_"));
					cv.SavePng(png, s);
				} catch (...) {
					res.status = _T("ERROR");
					res.detail = _T("exception while drawing");
				}
				delete f;
				total[rdr]++;
				if (res.status == _T("PASS")) pass[rdr]++;
				cells[rdr] = res.status == _T("PASS") ? CString(_T("PASS")) : res.status + _T(": ") + res.detail;
				CString line;
				line.Format(_T("%s,%s,%s,%s,\"%s\"\r\n"), (LPCTSTR)CString(s.name), (LPCTSTR)CString(kCaseName[c]),
				            rdr ? _T("Direct2D") : _T("GDI"), (LPCTSTR)res.status, (LPCTSTR)res.detail);
				csv += line;
			}
			CString row;
			row.Format(_T("| %s | %s | %s | %s |\r\n"), (LPCTSTR)CString(s.name), (LPCTSTR)CString(kCaseName[c]),
			           (LPCTSTR)cells[0], (LPCTSTR)cells[1]);
			md += row;
		}
	}
	CString sum;
	sum.Format(_T("\r\nGDI: %d of %d pass. Direct2D: %d of %d pass.\r\n"), pass[0], total[0], pass[1], total[1]);
	md += sum;
	view->ReleaseDC(hdc);

	auto write = [](const CString& path, const CString& text) {
		CFile f;
		if (f.Open(path, CFile::modeCreate | CFile::modeWrite)) {
			CStringA a(text);
			f.Write(a.GetString(), a.GetLength());
			f.Close();
		}
	};
	write(outDir + _T("\\report.md"), md);
	write(outDir + _T("\\results.csv"), csv);
	view->GetDocument()->SetModifiedFlag(FALSE);
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
	return true;
}


// ---------------------------------------------------------------------------
// UI-driven tests: the same objects and checks, but every step goes through
// the window messages a user produces.

namespace {

CCadView* g_uiView = nullptr;
CString g_uiDir;

void Pump(int ms = 60) {
	DWORD end = GetTickCount() + ms;
	MSG m;
	do {
		while (PeekMessage(&m, NULL, 0, 0, PM_REMOVE)) {
			if (m.message == WM_QUIT) { PostQuitMessage((int)m.wParam); return; }
			if (!AfxGetApp()->PreTranslateMessage(&m)) { TranslateMessage(&m); DispatchMessage(&m); }
		}
		Sleep(5);
	} while ((int)(end - GetTickCount()) > 0);
}

// Client pixel of a world point, as the view's mouse handlers map it.
CPoint ClientPoint(CCadView* view, double wx, double wy) {
	CDC* dc = view->GetDC();
	view->OnPrepareDC(dc);
	CPoint p = CVector(wx, wy, 0, 1);
	dc->LPtoDP(&p, 1);
	view->ReleaseDC(dc);
	return p;
}

void Click(HWND w, CPoint p, UINT down = WM_LBUTTONDOWN, UINT up = WM_LBUTTONUP, WPARAM keys = MK_LBUTTON) {
	LPARAM lp = MAKELPARAM(p.x, p.y);
	SendMessage(w, WM_MOUSEMOVE, 0, lp);
	SendMessage(w, down, keys, lp);
	SendMessage(w, WM_MOUSEMOVE, keys, lp);
	SendMessage(w, up, 0, lp);
}

template <class T> T* FindChildButton(CWnd* bar, std::function<bool(T*)> want) {
	for (CWnd* c = bar->GetWindow(GW_CHILD); c; c = c->GetWindow(GW_HWNDNEXT)) {
		T* b = dynamic_cast<T*>(CWnd::FromHandlePermanent(c->GetSafeHwnd()));
		if (b && want(b)) return b;
	}
	return nullptr;
}

// Drives the modal Transparency dialog: drag the slider to 50%, press OK.
int g_transTicks = 0;
bool g_transDone = false;
VOID CALLBACK TransparencyDialogDriver(HWND, UINT, UINT_PTR id, DWORD) {
	HWND dlg = NULL;
	EnumThreadWindows(GetCurrentThreadId(), [](HWND h, LPARAM lp) -> BOOL {
		if (IsWindowVisible(h) && GetDlgItem(h, IDC_TSLIDER)) { *(HWND*)lp = h; return FALSE; }
		return TRUE;
	}, (LPARAM)&dlg);
	if (!dlg) {
		if (++g_transTicks > 100) KillTimer(NULL, id);   // give up after ~5 s
		return;
	}
	KillTimer(NULL, id);
	HWND slider = GetDlgItem(dlg, IDC_TSLIDER);
	SendMessage(slider, TBM_SETPOS, TRUE, 50);
	SendMessage(dlg, WM_HSCROLL, MAKEWPARAM(TB_THUMBTRACK, 50), (LPARAM)slider);
	SendMessage(dlg, WM_HSCROLL, MAKEWPARAM(TB_ENDTRACK, 0), (LPARAM)slider);
	g_transDone = true;
	PostMessage(dlg, WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), (LPARAM)GetDlgItem(dlg, IDOK));
}

// Copy what the view shows into a Canvas (white bitmap with the view's mapping).
void CaptureView(CCadView* view, Canvas& cv) {
	view->change = true;
	view->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
	Pump(150);
	CDC* src = view->GetDC();
	int sm = cv.mem.SetMapMode(MM_TEXT);
	CPoint vo = cv.mem.SetViewportOrg(0, 0), wo = cv.mem.SetWindowOrg(0, 0);
	cv.mem.BitBlt(0, 0, cv.rc.Width(), cv.rc.Height(), src, 0, 0, SRCCOPY);
	cv.mem.SetWindowOrg(wo); cv.mem.SetViewportOrg(vo); cv.mem.SetMapMode(sm);
	view->ReleaseDC(src);
}

void RunUITests() {
	CCadView* view = g_uiView;
	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	CCadDoc* doc = view->GetDocument();
	CString outDir = g_uiDir;
	CreateDirectory(outDir, nullptr);
	frame->ShowWindow(SW_SHOWMAXIMIZED);
	frame->SetForegroundWindow();
	Pump(300);

	// The checker texture (same pixels as the automated tests).
	CString texture = outDir + _T("\\texture_checker.png");
	if (GetFileAttributes(texture) == INVALID_FILE_ATTRIBUTES) {
		std::vector<uint32_t> px(64 * 64);
		for (int y = 0; y < 64; ++y)
			for (int x = 0; x < 64; ++x) {
				bool odd = ((x / 8) + (y / 8)) & 1;
				COLORREF c = y < 32 ? (odd ? kRed : kBlue) : (odd ? kGreen : RGB(240, 210, 40));
				uint32_t a = (x >= 24 && x < 40 && y >= 24 && y < 40) ? 0 : 0xFF;
				px[y * 64 + x] = (a << 24) | (GetRValue(c) << 16) | (GetGValue(c) << 8) | GetBValue(c);
			}
		CImageFile f;
		f.Assign(64, 64, px.data());
		f.Save(std::wstring(CStringW(texture)));
	}

	const bool d2d = acr::ViewRenderer() != nullptr;
	const CString rname = d2d ? _T("d2d") : _T("gdi");

	// A saturated swatch on the colour bar to use as the fill colour.
	CRecColor* swatch = FindChildButton<CRecColor>(&frame->colorToolBar, [](CRecColor* b) {
		int r = GetRValue(b->color), g = GetGValue(b->color), bl = GetBValue(b->color);
		return b->IsWindowVisible() && max(r, max(g, bl)) - min(r, min(g, bl)) > 120;
	});
	CRecPattern* patBtn = FindChildButton<CRecPattern>(&frame->patternBar, [](CRecPattern* b) { return b->IsWindowVisible() != 0; });

	std::vector<Shape> shapes = {
		{ "rectangle", []() { CRectangle* r = new CRectangle; r->setCorners(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1)); return (CFigure*)r; }, -150, -100, 150, 100 },
		{ "circle", []() { return (CFigure*)new CCercle(CVector(0, 0, 0, 1), 100); }, -100, -100, 100, 100 },
		{ "polygon", []() {
			CLine* l = new CLine;
			std::vector<std::vector<CVector>> loops(1);
			for (int k = 0; k < 6; ++k) loops[0].push_back(CVector(110 * cos(k * 3.14159265 / 3), 110 * sin(k * 3.14159265 / 3), 0, 1));
			l->setFromLoops(loops, kFill);
			return (CFigure*)l; }, -110, -95.26, 110, 95.26 },
		{ "image", []() { CImage* i = new CImage; i->buildFromRect(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1)); return (CFigure*)i; }, -150, -100, 150, 100 },
		{ "block (rectangle inside)", []() {
			CLibS* lib = new CLibS;
			CRectangle r; r.setCorners(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1));
			lib->add(&r); lib->updatecore(); return (CFigure*)lib; }, -150, -100, 150, 100 },
	};
	// A point on each outline the user clicks to select it.
	auto pickPoint = [](const Shape& s, double& x, double& y) {
		if (CString(s.name) == _T("circle")) { x = 100; y = 0; }
		else if (CString(s.name) == _T("polygon")) { x = 110; y = 0; }
		else { x = s.x1; y = s.y1; }
	};

	CString md, csv = _T("object,case,renderer,status,detail\r\n");
	md.Format(_T("# UI tests: colour, texture, transparency (%s)\r\n\r\n"), d2d ? _T("Direct2D") : _T("GDI"));
	md += _T("Each object is added to an empty drawing, selected with a mouse click on its outline (Select tool), ")
	      _T("then: fill colour = right click on a colour-bar swatch; texture = click on a pattern-bar button (its source set to the test checker); ")
	      _T("tiling and blend modes = Format > Texture menu items (checked enabled first); transparency = Format > Transparency, slider dragged to 50, OK. Pixels are read back from the window.\r\n\r\n");
	CString sw;
	sw.Format(_T("Colour-bar swatch used: %s. Pattern button: %s.\r\n\r\n"),
	          swatch ? (LPCTSTR)Hex(swatch->color) : _T("none found"), patBtn ? _T("found") : _T("none found"));
	md += sw;
	md += _T("| Object | Case | Result |\r\n| --- | --- | --- |\r\n");
	int pass = 0, total = 0;
	const Case cases[] = { Solid, Solid50, Tex, Tex50, Tile, Multiply, Decal50, FillOnly };
	for (const Shape& s : shapes) {
		for (Case c : cases) {
			Result res;
			CFigure* f = s.make();
			doc->m_objects->addFigure(f);
			frame->SendMessage(WM_COMMAND, ID_TBSELECT);
			view->change = true;
			view->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			Pump();
			double px, py;
			pickPoint(s, px, py);
			Click(view->GetSafeHwnd(), ClientPoint(view, px, py));
			Pump();
			CString steps;
			bool ok = doc->m_objects->selectedCount() == 1;
			if (!ok) steps += _T("click did not select it; ");
			COLORREF fill = swatch ? swatch->color : 0;
			if (ok) {
				if (!swatch) { ok = false; steps += _T("no colour swatch; "); }
				else Click(swatch->GetSafeHwnd(), CPoint(5, 5), WM_RBUTTONDOWN, WM_RBUTTONUP, MK_RBUTTON);
			}
			if (ok && CaseTextured(c)) {
				if (!patBtn) { ok = false; steps += _T("no pattern button; "); }
				else { patBtn->patsource = texture; Click(patBtn->GetSafeHwnd(), CPoint(5, 5)); }
			}
			Pump();
			// Format > Texture: the menu item must be enabled for the selection.
			auto menuCommand = [&](UINT id, const TCHAR* what) {
				struct Probe : CCmdUI { bool en = false; void Enable(BOOL b) override { en = b != 0; m_bEnableChanged = TRUE; }
					void SetCheck(int) override {} void SetRadio(BOOL) override {} void SetText(LPCTSTR) override {} } pr;
				pr.m_nID = id;
				pr.DoUpdate(frame, FALSE);
				if (!pr.en) { ok = false; CString e; e.Format(_T("menu %s disabled; "), what); steps += e; return; }
				frame->SendMessage(WM_COMMAND, id);
			};
			if (ok && c == Tile) menuCommand(ID_TEXTURE_TILE, _T("Tile"));
			if (ok && c == Multiply) menuCommand(ID_TEXTURE_MULTIPLY, _T("Multiply"));
			if (ok && c == Decal50) menuCommand(ID_TEXTURE_DECAL, _T("Decal"));
			if (ok && c == FillOnly) menuCommand(ID_TEXTURE_FILLONLY, _T("Fill Colour Only"));
			Pump();
			if (ok && CaseHas50(c)) {
				g_transTicks = 0; g_transDone = false;
				SetTimer(NULL, 0, 50, TransparencyDialogDriver);
				frame->SendMessage(WM_COMMAND, ID_TRANSPARENCY);   // modal; the driver answers it
				if (!g_transDone) { ok = false; steps += _T("Transparency dialog not driven; "); }
			}
			// Click on empty canvas to drop the selection (handles off the shape).
			CRect cr; view->GetClientRect(&cr);
			Click(view->GetSafeHwnd(), CPoint(cr.left + 15, cr.bottom - 15));
			Pump();
			{
				CDC* ref = view->GetDC();
				Canvas cv(view, ref);
				view->ReleaseDC(ref);
				CaptureView(view, cv);
				if (ok) {
					res = Check(cv, s, c, fill);
				} else {
					res.status = _T("FAIL");
				}
				res.detail = steps + res.detail;
				CString png;
				png.Format(_T("%s\\ui_%s_%d_%s.png"), (LPCTSTR)outDir, (LPCTSTR)CString(s.name).Left(5), (int)c, (LPCTSTR)rname);
				png.Replace(_T(" "), _T("_"));
				cv.SavePng(png, s);
			}
			if (doc->m_objects->selectedCount() == 0)
				doc->m_objects->removeFigure(f);
			else
				res.detail += _T(" (still selected; left in the drawing)");
			total++;
			if (res.status == _T("PASS")) pass++;
			CString row;
			row.Format(_T("| %s | %s | %s |\r\n"), (LPCTSTR)CString(s.name), (LPCTSTR)CString(kCaseName[c]),
			           res.status == _T("PASS") ? _T("PASS") : (LPCTSTR)(res.status + _T(": ") + res.detail));
			md += row;
			CString line;
			line.Format(_T("%s,%s,%s,%s,\"%s\"\r\n"), (LPCTSTR)CString(s.name), (LPCTSTR)CString(kCaseName[c]),
			            (LPCTSTR)rname, (LPCTSTR)res.status, (LPCTSTR)res.detail);
			csv += line;
		}
	}
	CString sum;
	sum.Format(_T("\r\n%d of %d pass.\r\n"), pass, total);
	md += sum;
	auto write = [](const CString& path, const CString& text) {
		CFile f;
		if (f.Open(path, CFile::modeCreate | CFile::modeWrite)) {
			CStringA a(text);
			f.Write(a.GetString(), a.GetLength());
			f.Close();
		}
	};
	write(outDir + _T("\\ui_") + rname + _T(".md"), md);
	write(outDir + _T("\\ui_") + rname + _T(".csv"), csv);
	doc->SetModifiedFlag(FALSE);
	frame->PostMessage(WM_CLOSE);
}

VOID CALLBACK StartUITests(HWND, UINT, UINT_PTR id, DWORD) {
	KillTimer(NULL, id);
	RunUITests();
}

} // namespace

bool RunUITestsIfRequested(CCadView* view)
{
	char* dir = nullptr;
	size_t n = 0;
	if (_dupenv_s(&dir, &n, "ANDYCAD_RUN_UI_TESTS") != 0 || !dir || !*dir) { free(dir); return false; }
	g_uiDir = dir;
	free(dir);
	g_uiView = view;
	SetTimer(NULL, 0, 1500, StartUITests);
	return true;
}
