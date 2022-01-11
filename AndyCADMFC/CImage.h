//
//  CImage.h
//  testcommand
//
//  Created by Serge Deh on 10/16/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CImage__
#define __testcommand__CImage__

#include <iostream>
// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "cFigure.h"
#include "crectangle.h"

class CImage :public CxImage, public CLine
{
public:
	bool Hatch(CDC* hdc);
	void copy(const CFigure *fig);
/*	long Draw(HDC hdc, long x, long y, long cx, long cy, RECT* pClipRect, bool bSmooth);
	PBITMAPINFO CreateBMPInfo(HBITMAP hBMP, bool set);
	void CreateBMPFile(LPTSTR pszFile,HBITMAP hBMP, HDC hDC);*///************
	void drawTrans(CDC *hdc);
	void openfile(CDC *hdc,fstream &file);
	void savefile(CDC *hdc,fstream &file);
	CImage(CDC *hdc,fstream &file);
	CImage();
	~CImage();
	bool draw(bool fPrevLine, CDC *hdc,CVector point);
	void draw(CDC *hdc);
	void setMove(bool mv,CVector pos);
	void create(CVector pos);
    bool getCharge();
	bool LoadBitmap(CDC *hdc);
	void initL();
	void setPtsBegin(CVector point);
/*	DWORD GetColorTableSize(WORD wBitCount);
	HGLOBAL ConvertDDBtoDIB(CBitmap *pBmp,CDC *hdc);*///************
    
private:
	CRectangle rec;
	CBitmap* hB,*phB;
/*	BITMAP bm;
	HBITMAP hBitmap;*///***************
	float prevu;
    
};

#endif /* defined(__testcommand__CImage__) */
