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
};

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
			if (!ok) log += _T("  (") + why + _T(")");
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
