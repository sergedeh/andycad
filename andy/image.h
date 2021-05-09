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

class CImage :public CxImage, public CLine 
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
	void setMove(bool mv,CVector pos);
	void create(CVector pos);
    bool getCharge();
	BOOL LoadBitmap(CDC *hdc); 
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
