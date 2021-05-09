// TextCad.h: interface for the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
#define AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_
#include "Vector.h"	// Added by ClassView
#include "Rectangle.h"	// Added by ClassView
#include "figure.h"	// Added by ClassView
#include <map>
#include <functional>
#include "Bezier.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;


class CTextCad : public CBezier  
{
public:
	void drawselect(CDC* hdc);
	void setText(CString vtext,CDC* pDC);
	void PolyDraw(CDC* pDC);

	void draw(CDC *hdc);
	void setMove(bool b, CVector point);
	void editobj(CDC* hdc);
	void edittext();
	void setText1(CString vtext,CDC* hdc);
	void updatecopy();
	CFont* getFont();
	void assign(CDC *hdc,CVector p,CString s);
	void openfile(CFile &file);
	void savefile(CFile &file);
	CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl);
	void create(CVector pos);
	void initL();
	bool getCharge();
	void setPtsBegin(CVector point);
	bool draw(bool fPrevLine,CDC *hdc, CVector point);
	CRectangle* getRectangle();
	CTextCad();
	CTextCad(CFile &file);
	virtual ~CTextCad();

private:

	CVector vecsepos;
	int iter,biter,sbiter,seiter,liter;
	CRectangle rec;
	bool fPrevB;
	bool selmode;
	CFont* pfont;
	TEXTMETRIC textmet;
	CString *str;
	CWnd * wd;

	LPPOINT lpPoints;
    LPBYTE lpTypes;
	int nNumPts;

	int width; 
	CString mtext;
    vector<int> off;
};

#endif // !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
