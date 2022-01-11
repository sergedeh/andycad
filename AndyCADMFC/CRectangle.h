//
//  CRectangle.h
//  testcommand
//
//  Created by Serge Deh on 10/16/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CRectangle__
#define __testcommand__CRectangle__

#include <iostream>
#include "CLine.h"

// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "CBezier.h"	// Added by ClassView

class CRectangle :public CLine
{
public:
	virtual CFigure* generateCopy();
	void drawMesh(CDC *hdc,float r);
	CRectangle(CVector b,CVector e);
	void getchargeL();
	void setstyle(int i);
    //	void translate(CWnd *wnd,CDC *hdc,CVector prevpos,CVector postpos);
	long Readfile(fstream &file);
	void openfile(fstream &file);
	void savefile(fstream &file);
	void setType(string  option);
	void createvec();
	CRectangle mirror(CDC *hdc, CRectangle  *rectangle);
	void drawpointdyna(CDC *hdc, CVector pbe, CVector pbb);
	void drawinit(CDC *hdc, CVector begin, CVector end);
	void draw(CDC* hdc);
	bool  draw(bool fPrevLine, CDC *hdc,CVector point);
	void polystate(CVector pos);
	bool getCharge();
	void setMove(bool mv,CVector pos);
	friend class CInter;
    
	CRectangle();
	CRectangle(fstream &file);
	virtual ~CRectangle();
    
private:
	enum TP{select, rect} tprect;
	CVector prev_v2,prev_v3x,prev_e,prev_v3y;
	CBezier* bez;
    
};
#endif /* defined(__testcommand__CRectangle__) */
