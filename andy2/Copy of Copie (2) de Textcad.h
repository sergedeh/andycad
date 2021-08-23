// TextCad.h: interface for the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
#define AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_
#include "Vector.h"	// Added by ClassView
#include "Rectangle.h"	// Added by ClassView
#include "bezier.h"	// Added by ClassView
#include <map>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

	struct mytext1
		{
		LOGFONT* f;
		char c;
		CPoint v;
		bool s;
		};
	struct myfont
		{
			TEXTMETRIC tm;
			map<char,ABCFLOAT> abc;
			COLORREF col;
		};

typedef map<int,mytext1>::iterator itmap;
typedef	map<LOGFONT*,myfont>::iterator ifmap;


class CTextCad : public CBezier  
{
public:
	void edittext0();
	void edittext();
	bool inRegion(CVector point);
	void assign(CDC *hdc,CVector p,CString s);
	void openfile(CFile &file);
	void savefile(CFile &file);
	CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl);
	bool PtinRegion(CVector point);
	void drawTrans(CDC *hdc);
	void translate(CWnd *wnd,CDC *hdc, CVector prevpos, CVector postpos);
	void draw(CDC *hdc);
	void create(CVector pos);
//	CRect getTextrec(CDC *hdc);
	void getTextrec(CWnd* wnd,CDC *hdc);
	void initL();
	void setMove(bool b,CVector point);
	void FillText();
	bool getCharge();
	void setPtsBegin(CVector point);
	bool draw(bool fPrevLine,CDC *hdc, CVector point);
	CRectangle* getRectangle();
	CTextCad();
	CTextCad(CFile &file);
	virtual ~CTextCad();
	CPoint drawtext(CDC *hdc, UINT nchar);
private:
	CRichEditCtrl* rich;
	static CWnd* view;
	CBitmap* bm;
	bool fPrevB,in;
	CRectangle rec;
	int pw1;
	map<int,mytext1> ltext;
	map<char,ABC> cmap;
	map<LOGFONT*,myfont> fmap;
	int iter;
};

#endif // !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
