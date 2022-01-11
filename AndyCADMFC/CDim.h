//
//  CDim.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CDim__
#define __testcommand__CDim__

#include <iostream>
// Dim.h: interface for the CDim class.
//
//////////////////////////////////////////////////////////////////////
#include "cLibS.h"
#include "cline.h"
#include "cdimarrow.h"
#include "ctextcad.h"
#include "cdimtext.h"
#include"cCercle.h"
#include"cconstraint.h"

class CDim : public CLibS
{
public:
	void UpdateDim(CFigure* f,CDC* hdc);
	void buildDim(CDC* hdc,float u, float v);
	void SendNotify(string s, void *param[]);
	void drivingParam(CFigure* f,vector<CVector> vv);
	const CAABB getbox(CDC* hdc);
	CDim(fstream &file,CDC* hdc);
	long ReadFike(fstream& file);
	void openfile(fstream& file,CDC* hdc);
	void savefile(fstream& file);
	void getArc(CVector &c, CVector& c1, CVector& c2,CVector point);
	bool isReady();
	void draw(CDC *hdc);
	void addSL(vector<CVector> vec);
	void setstyle(string st);
	void initL();
	bool draw(bool fPrevLine, CDC *hdc, CVector point);
	void setPtsBegin(CVector pos);
	void create(CVector pos);
	bool getCharge(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	bool PtinRegion(CVector point);
	CLine pline,v1line,v2line,arrow1,arrow2,a1line,a2line;
	CDimArrow arrow11,arrow22;
	CCercle cline;
	CTextCad text;
	CDimText text2;
    
	CDim();
	virtual ~CDim();
private:
	bool v1sel,v2sel,vl,vl2,vpc,pfull,ptext;
	enum STYLE{vert,horiz,free,diam,radius,ang,leader,multline} style;
	CVector bl,bf;
	CGPoint ppoint;
	vector<CVector> linesel;
	map<CFigure* ,vector< vector<CVector> > > d_params;
	bool state;
	CConstraint* constraint;
    
};


#endif /* defined(__testcommand__CDim__) */
