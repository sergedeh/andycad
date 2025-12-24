//
//  CDimL.h
//  testcommand
//
//  Created by Serge Deh on 10/19/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CDimL__
#define __testcommand__CDimL__

#include <iostream>
// DimL.h: interface for the CDimL class.
//
//////////////////////////////////////////////////////////////////////
#include "cLibS.h"
#include "cline.h"
#include "cdimarrow.h"
#include "cdimtext.h"
#include "ctextcad.h"

class CDimL : public CLibS
{
public:
	const CAABB getbox(CDC* hdc);
	CDimL(fstream &file,CDC* hdc);
	void savefile(fstream &file);
	void openfile(fstream &file,CDC* hdc);
	long ReadFike(fstream &file);
	bool isReady();
	void draw(CDC *hdc);
	void setstyle(string st);
	bool PtinRegion(CVector point);
	void initL();
	bool draw(bool fPrevLine, CDC *hdc, CVector point);
	void setPtsBegin(CVector pos);
	void create(CVector pos);
	bool getCharge(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	CLine pline,pl1,pl2,v1line,v2line,arrow1,arrow2;
	CDimArrow arrow11,arrow22;
	CTextCad text;
	CDimText text2;
    
	CDimL();
	virtual ~CDimL();
    
private:
	bool v1sel,v2sel,vl,vl2,vpc,pfull,ptext;
	enum STYLE {vert,horiz,free} style;
	CVector bl,bf;
	bool state;
    
    
};

#endif /* defined(__testcommand__CDimL__) */
