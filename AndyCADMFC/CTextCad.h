//
//  CTextCad.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CTextCad__
#define __testcommand__CTextCad__

#include <iostream>
// TextCad.h: interface for the CTextCad class.
//
//////////////////////////////////////////////////////////////////////
#include "cVector.h"	// Added by ClassView
#include "cRectangle.h"	// Added by ClassView
#include "cfigure.h"	// Added by ClassView
#include <map>
#include <functional>
#include "cBezier.h"
#include "CFont.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;


typedef map<CVector*,mytext2> tmap;
typedef tmap::value_type tpair;
typedef tmap::iterator ti;
typedef map<int,mytext2>::iterator itmap;
typedef	map<CFont*,myfont>::iterator ifmap;

class CTextCad : public CLine
{
public:
    //	DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	void Stream(CArchive& ar, bool bSelection);
	void Serialize(CArchive& ar);
	void setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor);
	void getfont(CHARFORMAT& cf);
	void setpara(string l);
	bool WndVisible();
	void setWnd(CWnd* cad);
	void assign(CDC* hdc, CVector p);
	CFigure* generateCopy();
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void editobj(CDC* hdc);
	void editobj(CVector point);
	void edittext();
	void setText(string vtext,CDC* hdc);
	void draw3D(CDC *hdc);
	void InitZoom();
	void updatecopy();
	CFont* getFont();
	bool inRegion(CVector point);
	void assign(CDC *hdc,CVector p,string s,CHARFORMAT* _cf=NULL);
	void openfile(fstream &file,CDC* hdc);
	void savefile(fstream &file);
//	void savefiledxf(CStdioFile& file);**************
	void setFStyle(FSTYLE* _fstyle);
	CGPoint textend(CDC *hdc);
	CGPoint deletetext(CDC *hdc);
	CGPoint texthome(CDC *hdc);
	CGPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf);
	bool PtinRegion(CVector point);
	void drawTrans(CDC *hdc);
	void translate(CWnd *wnd,CDC *hdc, CVector prevpos, CVector postpos);
	void draw(CDC *hdc);
	CGPoint kbmovecurs(CDC *hdc,string& d);
	CGPoint entertext(CDC *hdc);
	CGPoint deleteback(CDC *hdc);
	CGPoint drawtext(CDC *hdc, int nchar);
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
	CTextCad(fstream &file,CDC* hdc);
	~CTextCad();
    
private:
	CGPoint updatecurs(int i);
	void updatepos();
	itmap uptext(int i);
	itmap downtext(int i);
    
	CVector vecsepos;
	int iter,biter,sbiter,seiter,liter;
	vector<bool> vecbe;
	vector<string*> stk;
	vector<string*>::iterator is;
	map<int,string> mstr;
	CRectangle rec;
	bool fPrevB;
	bool selmode;
	CFont* pfont,*tfont;
	TEXTMETRIC textmet;
	struct text
	{
        bool start;
        CVector ltext;
        int ptext;
	};
	string *str;
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
    string mtext;
	FSTYLE* fstyle;
    
};

#endif /* defined(__testcommand__CTextCad__) */
