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
#include "txted.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

	struct mytext2
		{
		CFont* f;
		CFont*pf;
		char c;
		CPoint v;
		bool s;
		};
	struct myfont
		{
			TEXTMETRIC tm;
			map<char,ABCFLOAT> abc;
			LOGFONT* pf;
			COLORREF col;
		};

typedef map<CVector*,mytext2> tmap;
typedef tmap::value_type tpair;
typedef tmap::iterator ti;
typedef map<int,mytext2>::iterator itmap;
typedef	map<CFont*,myfont>::iterator ifmap;

class CTextCad : public CLine  
{
public:
//	DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	void Stream(CArchive& ar, BOOL bSelection);
	void Serialize(CArchive& ar);
	void setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor);
	void getfont(CHARFORMAT& cf);
	void setpara(CString l);
	bool WndVisible();
	void setWnd(CWnd* cad);
	void assign(CDC* hdc, CVector p);
	CFigure* generateCopy();
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void editobj(CDC* hdc);
	void editobj(CVector point);
	void edittext();
	void setText(CString vtext,CDC* hdc);
	void draw3D(CDC *hdc);
	void InitZoom();
	void updatecopy();
	CFont* getFont();
	bool inRegion(CVector point);
	void assign(CDC *hdc,CVector p,CString s,CHARFORMAT* _cf=NULL);
	void openfile(CFile &file,CDC* hdc);
	void savefile(CFile &file);
	void savefiledxf(CStdioFile& file);
	void setFStyle(FSTYLE* _fstyle);
	CPoint textend(CDC *hdc);
	CPoint deletetext(CDC *hdc);
	CPoint texthome(CDC *hdc);
	CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf);
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
	CTextCad(CFile &file,CDC* hdc);
	virtual ~CTextCad();

private:
	CPoint updatecurs(int i);
	void updatepos();
	itmap uptext(int i);
	itmap downtext(int i);

	CVector vecsepos;
	int iter,biter,sbiter,seiter,liter;
	vector<bool> vecbe;
	vector<CString*> stk;
	vector<CString*>::iterator is;
	map<int,CString> mstr;
	CRectangle rec;
	bool fPrevB;
	bool selmode;
	CFont* pfont,*tfont;
	TEXTMETRIC textmet;
	struct text
	{
	bool start;
	CVector ltext;
	UINT ptext;
	};
	CString *str;
	static CWnd * wd;

	CVector curspos;
	vector<CVector> vecpos;
	vector<vector<CVector*> > vlpos;
	//vector<vector<CVector*> >::iterator liter;

	vector<text> vectext;
	vector<text>::iterator titer;
	map<int,mytext2> ltext; //Contain the list of characters with font detils and positions
	map<char,ABC> cmap; //Contain detail about the font dimmensions
	map<CFont*,myfont> fmap,pfmap; // map between a font name and its details
    CTxtED* rich;
	CVector ppvlo;
	int width; 
	float z_prev,u_prev;
		CBezier bz;
		CString mtext;
	FSTYLE* fstyle;

};

#endif // !defined(AFX_TEXTCAD_H__47586488_0253_41BC_B265_5966EF9478BA__INCLUDED_)
