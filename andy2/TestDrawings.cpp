// TestDrawings.cpp — generates image test drawings in the current .deh format.
//
// Older sample drawings no longer open reliably, so the image work (see the
// Direct2D image plan) needs fresh baselines. Set the environment variable
// ANDYCAD_MAKE_TEST_DRAWINGS to an output folder and start the app: once the
// view is initialised it writes the drawings below, then closes itself.
//
// Each drawing holds one textured image shape plus a plain outline line so
// both code paths appear on screen. The texture is generated in memory (a
// 64x64 four-colour checker with a magenta key block) and stored inside the
// .deh file, so the drawings do not depend on any external image file.

#include "Stdafx.h"
#include "cad.h"
#include "cadDoc.h"
#include "cadView.h"
#include "Draw.h"
#include "Image.h"
#include "line.h"
#include "Libs.h"
#include "TextCad.h"
#include "TestDrawings.h"

namespace {

// Write a 24-bit BMP of `bmp` (selected out of any DC) to `path`.
bool SaveBitmapFile(HDC ref, HBITMAP bmp, const CString& path)
{
	BITMAP bm = {};
	if (!GetObject(bmp, sizeof(bm), &bm))
		return false;
	BITMAPINFOHEADER bih = {};
	bih.biSize = sizeof(bih);
	bih.biWidth = bm.bmWidth;
	bih.biHeight = bm.bmHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = BI_RGB;
	DWORD stride = ((bm.bmWidth * 3 + 3) & ~3);
	bih.biSizeImage = stride * bm.bmHeight;
	std::vector<BYTE> bits(bih.biSizeImage);
	if (!GetDIBits(ref, bmp, 0, bm.bmHeight, bits.data(), (BITMAPINFO*)&bih, DIB_RGB_COLORS))
		return false;
	BITMAPFILEHEADER bfh = {};
	bfh.bfType = 0x4D42;
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	bfh.bfSize = bfh.bfOffBits + bih.biSizeImage;
	CFile f;
	if (!f.Open(path, CFile::modeCreate | CFile::modeWrite))
		return false;
	f.Write(&bfh, sizeof(bfh));
	f.Write(&bih, sizeof(bih));
	f.Write(bits.data(), bih.biSizeImage);
	f.Close();
	return true;
}

bool RenderFiguresToBmp(CCadView* view, CDC* ref, const std::vector<CFigure*>& figs, const CString& path)
{
	CDC mem;
	mem.CreateCompatibleDC(ref);
	CBitmap bmp;
	CRect rc;
	view->GetClientRect(&rc);
	bmp.CreateCompatibleBitmap(ref, rc.Width(), rc.Height());
	CBitmap* old = mem.SelectObject(&bmp);
	mem.FillSolidRect(0, 0, rc.Width(), rc.Height(), RGB(255, 255, 255));
	view->OnPrepareDC(&mem);
	for (CFigure* f : figs)
		f->draw(&mem);
	mem.SelectObject(old);
	return SaveBitmapFile(ref->GetSafeHdc(), (HBITMAP)bmp.GetSafeHandle(), path);
}

// Draw one figure into an off-screen bitmap with the view's mapping and save it.
bool RenderFigureToBmp(CCadView* view, CDC* ref, CFigure* f, const CString& path)
{
	CDC mem;
	mem.CreateCompatibleDC(ref);
	CBitmap bmp;
	CRect rc;
	view->GetClientRect(&rc);
	bmp.CreateCompatibleBitmap(ref, rc.Width(), rc.Height());
	CBitmap* old = mem.SelectObject(&bmp);
	mem.FillSolidRect(0, 0, rc.Width(), rc.Height(), RGB(255, 255, 255));
	view->OnPrepareDC(&mem);
	f->draw(&mem);
	mem.SelectObject(old);
	return SaveBitmapFile(ref->GetSafeHdc(), (HBITMAP)bmp.GetSafeHandle(), path);
}

const COLORREF kKeyColour = RGB(255, 0, 255);   // transparency key (magenta)

// 64x64 32bpp DIB: 8x8 checker of red/blue over green/yellow halves, plus a
// 16x16 magenta block in the middle that the transparent variants drop.
HBITMAP MakeCheckerBitmap(HDC ref, bool withHole)
{
	const int W = 64, H = 64;
	BITMAPINFO bi = {};
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = W;
	bi.bmiHeader.biHeight = -H;          // top-down
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	void* bits = nullptr;
	HBITMAP bmp = CreateDIBSection(ref, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
	if (!bmp || !bits)
		return nullptr;
	DWORD* px = static_cast<DWORD*>(bits);
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			bool odd = ((x / 8) + (y / 8)) & 1;
			COLORREF c;
			if (y < H / 2)
				c = odd ? RGB(220, 30, 30) : RGB(30, 60, 220);
			else
				c = odd ? RGB(30, 170, 60) : RGB(240, 210, 40);
			DWORD a = 0xFF;
			if (x >= 24 && x < 40 && y >= 24 && y < 40)
			{
				c = kKeyColour;
				if (withHole)
					a = 0;   // per-pixel transparency: a see-through hole
			}
			// DIB pixels are 0xAARRGGBB (BGRA in memory).
			px[y * W + x] = (a << 24) | (GetRValue(c) << 16) | (GetGValue(c) << 8) | GetBValue(c);
		}
	}
	return bmp;
}

struct Variant
{
	const char* file;
	bool        tiled;
	bool        transparent;
	bool        image = true;
	bool        frame = true;
	int         mode = 0;                       // see CImage::setBlendMode
	COLORREF    fill = RGB(255, 255, 255);
	double      level = 1.0;                    // Transparency level (alpha)
	bool        block = false;                  // two rectangles grouped in a block
	bool        text = false;                   // a two-line text object
	int         textCount = 1;                  // >1: a grid of small text objects (timing)
	double      rotateDeg = 0;                  // rotate the text after layout (transform check)
	// Other transform checks after layout (0 = none):
	double      scaleBy = 0;                    // uniform scale
	bool        artistic = false;               // characters scale with the box
	bool        mirrorX = false;                // mirror left-right
	double      moveX = 0;                      // translate along x
	bool        toCurves = false;               // convert the text to curves
	// Shapes textured from texture_checker.png (an image file next to the
	// drawings), loaded through CFigure::setTexture like the Texture command.
	int         texturedShape = 0;              // 1 rectangle, 2 image, 3 tiled rectangle
};

CString g_textureFile;   // full path of texture_checker.png

const Variant kVariants[] = {
	{ "image_stretch.deh",             false, false },
	{ "image_stretch_transparent.deh", false, true  },
	{ "image_tile.deh",                true,  false },
	{ "image_tile_transparent.deh",    true,  true  },
	{ "image_only.deh",                false, false, true,  false },
	{ "frame_only.deh",                false, false, false, true  },
	{ "image_replace.deh",             false, false, true,  true, 1 },
	{ "image_decal.deh",               false, false, true,  true, 2, RGB(255, 255, 255), 0.5 },
	{ "image_multiply.deh",            false, false, true,  true, 3, RGB(255, 160, 0) },
	{ "image_backcolor.deh",           false, false, true,  true, 4, RGB(40, 90, 200), 0.5 },
	{ "block.deh",                     false, false, false, false, 0, RGB(255, 255, 255), 1.0, true },
	{ "text.deh",                      false, false, false, true,  0, RGB(255, 255, 255), 1.0, false, true },
	{ "text_rotated.deh",              false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 30 },
	{ "text_scale_rewrap.deh",         false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 0, 1.5, false },
	{ "text_scale_chars.deh",          false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 0, 1.5, true },
	{ "text_mirror.deh",               false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 0, 0, false, true },
	{ "text_move.deh",                 false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 0, 0, false, false, 120 },
	{ "text_curves.deh",               false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 1, 0, 0, false, false, 0, true },
	{ "rect_textured.deh",             false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, false, 1, 0, 0, false, false, 0, false, 1 },
	{ "rect_textured_tiled.deh",       false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, false, 1, 0, 0, false, false, 0, false, 3 },
	{ "image_from_png.deh",            false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, false, 1, 0, 0, false, false, 0, false, 2 },
	{ "text_many.deh",                 false, false, false, false, 0, RGB(255, 255, 255), 1.0, false, true, 40 },
};

bool WriteDrawing(CCadView* view, CCadDoc* doc, CDC* hdc, CBitmap& texture,
                  CBitmap& holed, const Variant& v, const CString& path, CString& why)
{
	CDraw* draw = doc->m_objects;
	draw->Init();

	// Image shape, 300 x 200 logical units.
	if (v.image)
	{
	CImage* img = new CImage;
	if (!img->buildFromRect(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1)))
	{
		delete img;
		why = _T("image quad not built");
		return false;
	}
	// Transparent variants: the magenta block has alpha 0 in the image, and
	// the shape's Transparency level is 60%.
	img->setGeneratedTexture(hdc, v.transparent ? &holed : &texture, "generated:checker64",
	                         v.tiled, RGB(255, 255, 255), v.transparent ? 0.6 : v.level);
	if (v.mode != 0)
		img->setBlendMode(v.mode, v.fill);
	draw->addFigure(img);
	}

	// A plain outline next to it, so the drawing also exercises lines.
	if (v.frame)
	{
		// Default-construct first: only that constructor sets the type name
		// ("CRectangle") that the file writer keys on.
		CRectangle* frame = new CRectangle;
		frame->setCorners(CVector(-170, -120, 0, 1), CVector(170, 120, 0, 1));
		draw->addFigure(frame);
	}

	if (v.texturedShape == 1 || v.texturedShape == 3)
	{
		CRectangle* r = new CRectangle;
		r->setCorners(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1));
		r->setTexture(g_textureFile, hdc);
		if (v.texturedShape == 3)
			r->setTiled(true);
		draw->addFigure(r);
	}
	if (v.texturedShape == 2)
	{
		CImage* img = new CImage;
		img->buildFromRect(CVector(-150, -100, 0, 1), CVector(150, 100, 0, 1));
		img->setTexture(g_textureFile, hdc);
		draw->addFigure(img);
	}
	if (v.block)
	{
		CLibS* lib = new CLibS;
		CRectangle a, b;
		a.setCorners(CVector(-150, -100, 0, 1), CVector(-10, 100, 0, 1));
		b.setCorners(CVector(10, -100, 0, 1), CVector(150, 100, 0, 1));
		lib->add(&a);
		lib->add(&b);
		lib->updatecore();
		draw->addFigure(lib);
	}

	if (v.text)
	{
		for (int k = 0; k < v.textCount; ++k)
		{
			bool grid = v.textCount > 1;
			double ox = grid ? -400 + (k % 8) * 110 : 0;
			double oy = grid ? 200 - (k / 8) * 90 : 0;
			double hw = grid ? 50 : 150, hh = grid ? 40 : 80;
			CTextCad* t = new CTextCad;
			t->setPtsBegin(CVector(ox - hw, oy + hh, 0, 1));
			t->create(CVector(ox + hw, oy - hh, 0, 1));
			t->getCharge();
			draw->addFigure(t);
			t->setTextForTest(hdc, _T("AndyCAD text\r\nDirect2D test 0123"), 7);
			if (v.toCurves)
			{
				// Lay the text out, convert it, and render text and curves
				// separately so they can be compared pixel by pixel.
				CString base = path.Left(path.GetLength() - 4);
				RenderFigureToBmp(view, hdc, t, base + _T("_text.bmp"));
				std::vector<CFigure*> curves = t->toCurves(hdc);
				for (CFigure* c : curves)
					draw->addFigure(c);
				RenderFiguresToBmp(view, hdc, curves, base + _T("_curves.bmp"));
				draw->removeFigure(t);
				CString note;
				note.Format(_T("curve figures=%d"), (int)curves.size());
				why = note;
				continue;
			}
			bool transformCheck = v.rotateDeg != 0 || v.scaleBy != 0 || v.mirrorX || v.moveX != 0;
			if (v.artistic)
				t->setScaleCharacters(true);
			if (transformCheck)
			{
				// Lay out once, rotate through the general figure transform, and
				// check the characters followed without a new layout.
				CString base = path.Left(path.GetLength() - 4);
				RenderFigureToBmp(view, hdc, t, base + _T("_before.bmp"));
				int n0 = t->layoutCount();
				t->setRotateCenter(t->getCenter());
				if (v.rotateDeg != 0)
					t->rotate((float)(v.rotateDeg * 3.14159265358979 / 180.0), 0);
				if (v.scaleBy != 0)
					t->scale((float)v.scaleBy, 0);
				if (v.mirrorX)
					t->scale(-1.0f, 1);
				if (v.moveX != 0)
					t->Translate(CVector(v.moveX, 0, 0, 0));
				RenderFigureToBmp(view, hdc, t, base + _T("_after.bmp"));
				int n1 = t->layoutCount();
				CString note;
				note.Format(_T("layouts before=%d after=%d"), n0, n1);
				why = note;   // reported in the log line
			}
		}
	}

	CFile file;
	if (!file.Open(path, CFile::modeCreate | CFile::modeReadWrite))
	{
		why = _T("cannot open file");
		return false;
	}
	view->Save(1, file);
	file.Close();
	return true;
}

} // namespace

bool MakeImageTestDrawingsIfRequested(CCadView* view)
{
	char* dir = nullptr;
	size_t n = 0;
	if (_dupenv_s(&dir, &n, "ANDYCAD_MAKE_TEST_DRAWINGS") != 0 || !dir || !*dir)
	{
		free(dir);
		return false;
	}
	CString outDir(dir);
	g_textureFile = outDir + _T("\\texture_checker.png");
	free(dir);
	CreateDirectory(outDir, nullptr);

	CCadDoc* doc = view->GetDocument();
	CDC* hdc = view->GetDC();
	view->OnPrepareDC(hdc);

	CString log;
	HBITMAP raw = MakeCheckerBitmap(hdc->GetSafeHdc(), false);
	HBITMAP rawHoled = MakeCheckerBitmap(hdc->GetSafeHdc(), true);
	if (raw && rawHoled)
	{
		CBitmap texture, holed;
		texture.Attach(raw);
		holed.Attach(rawHoled);
		for (const Variant& v : kVariants)
		{
			CString path = outDir + _T("\\") + v.file;
			bool ok = false;
			CString why;
			try { ok = WriteDrawing(view, doc, hdc, texture, holed, v, path, why); }
			catch (CException* e) { TCHAR m[256] = {}; e->GetErrorMessage(m, 255); why = CString(_T("exception: ")) + m; e->Delete(); }
			catch (...) { why = _T("unknown exception"); }
			log += (ok ? _T("OK   ") : _T("FAIL ")) + path;
			if (!why.IsEmpty()) log += _T("  (") + why + _T(")");
			log += _T("\r\n");
		}
	}
	else
	{
		log = _T("FAIL could not create the texture bitmap\r\n");
	}
	view->ReleaseDC(hdc);

	// Leave a log next to the drawings, then reset and close the app.
	CFile lf;
	if (lf.Open(outDir + _T("\\make_test_drawings.log"), CFile::modeCreate | CFile::modeWrite))
	{
		CStringA a(log);
		lf.Write(a.GetString(), a.GetLength());
		lf.Close();
	}
	doc->m_objects->Init();
	doc->SetModifiedFlag(FALSE);
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
	return true;
}
