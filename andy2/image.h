// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__D0F6C1D4_6B84_46D5_BEAB_10BD3E00C905__INCLUDED_)
#define AFX_IMAGE_H__D0F6C1D4_6B84_46D5_BEAB_10BD3E00C905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Figure.h"
#include "rectangle.h"
#include <cstdint>
#include <vector>

class CImage :/*public CxImage,*/ public CLine
{
public:
	bool Hatch(CDC* hdc);
	void copy(const CFigure *fig);
	long Draw(HDC hdc, long x, long y, long cx, long cy, RECT* pClipRect, bool bSmooth);
	PBITMAPINFO CreateBMPInfo(HBITMAP hBMP, bool set);
	void CreateBMPFile(LPTSTR pszFile,HBITMAP hBMP, HDC hDC);
	void drawTrans(CDC *hdc);
	void openfile(CDC *hdc,CFile &file);
	void savefile(CDC *hdc,CFile &file);
	CImage(CDC *hdc,CFile &file);
	CImage();
	virtual ~CImage();
	bool draw(bool fPrevLine, CDC *hdc,CVector point);
	void draw(CDC *hdc);
	// Direct2D path: the image as a bitmap brush (smooth sampling), with the
	// Transparency level (alpha) times each pixel's own alpha, and repeat
	// mode as brush wrapping. Only for image_texture shapes with no clipping;
	// everything else stays on draw(CDC*).
	void draw(acr::IRenderer* r) override;
	bool canRender() const override;
	void setMove(bool mv,CVector pos);
	void create(CVector pos);
    bool getCharge();
	BOOL LoadBitmap(CDC *hdc);
	// Build the image quad (corners + texture coordinates) from two opposite
	// corners, as the interactive Image tool does. Used by the test-drawing
	// generator.
	bool buildFromRect(CVector b, CVector e);
	// Use an in-memory bitmap as the texture (stretched or tiled), with an
	// optional transparency key colour. `name` is stored as texture_file.
	void setGeneratedTexture(CDC* hdc, CBitmap* bmp, const CString& name,
	                         bool tiled, COLORREF transparentColour,
	                         double opacity = 1.0);
	// Blend mode for the generator: 0 image_texture, 1 replace, 2 decal,
	// 3 multiply, 4 backcolor (matches CFigure::tex_vert_mode names).
	void setBlendMode(int mode, COLORREF fill);
 
	void initL();
	void setPtsBegin(CVector point);
	DWORD GetColorTableSize(WORD wBitCount);
	HGLOBAL ConvertDDBtoDIB(CBitmap *pBmp,CDC *hdc);

private:
	CRectangle rec;
	CBitmap* hB,*phB;
	BITMAP bm;
	HBITMAP hBitmap;
	float prevu;

};

#endif // !defined(AFX_IMAGE_H__D0F6C1D4_6B84_46D5_BEAB_10BD3E00C905__INCLUDED_)
