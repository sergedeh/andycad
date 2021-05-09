// TextCad.h: interface for the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
#define AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_
#include "Vector.h"	// Added by ClassView
#include "Rectangle.h"	// Added by ClassView
#include "figure.h"	// Added by ClassView
#include <map>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
class CTextCad : public CFigure  
{
public:
	void copy(CTextCad *text);
	void updatecopy();
	LOGFONT getFont();
	bool inRegion(CVector point);
	void assign(CDC *hdc,CVector p,CString s);
	void openfile(CFile &file);
	void savefile(CFile &file);
	CPoint textend(CDC *hdc);
	CPoint deletetext(CDC *hdc);
	CPoint texthome(CDC *hdc);
	CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl);
	bool PtinRegion(CVector point);
	void drawTrans(CDC *hdc);
	void translate(CWnd *wnd,CDC *hdc, CVector prevpos, CVector postpos);
	void draw(CDC *hdc);
	CPoint kbmovecurs(CDC *hdc,CString& d);
	CPoint entertext(CDC *hdc);
	CPoint deleteback(CDC *hdc);
	CPoint drawtext(CDC *hdc, UINT nchar);
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

private:
	CVector vecsepos;
	vector<CVector>::iterator iter,biter,ssiter,seiter;
	vector<bool> vecbe;
	vector<CString*> stk;
	vector<CString*>::iterator is;
	map<int,CString> mstr;
	CRectangle rec;
	bool fPrevB;
	bool selmode;
	LOGFONT pfont;
	TEXTMETRIC textmet;
	struct text
	{
	bool start;
	CVector ltext;
	UINT ptext;
	public:
		void copy(CTextCad* text);
	};
	CString *str;

	CVector curspos;
	vector<CVector> vecpos;
	vector<vector<CVector*> > vlpos;
	vector<vector<CVector*> >::iterator liter;

	vector<text> vectext;
	vector<text>::iterator titer;

	int width; 
};

#endif // !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
