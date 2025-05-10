//
//  CInter.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CInter__
#define __testcommand__CInter__

#include <iostream>
// Inter.h: interface for the CInter class.
//
//////////////////////////////////////////////////////////////////////

#include "CVector.h"
#include "CFigure.h"
#include "Clibs.h"
#include "Ccercle.h"
#include "Crectangle.h"
#include "Cqline.h"
#include "Ctextcad.h"
using namespace std;
class CInter : public CFigure
{
public:
	CLibS* copy2(CVector cent,float d, CFigure *pbulk, CLibS *line);
	CFigure* paste(CVector cent,CVector point,CFigure *line);
	CLibS* copybyL(CFigure *base, CLibS* line);
	void copybyL(CFigure *base, CFigure *line,CFigure *result);
	CLibS* pasteArray(CVector cent,CLibS *line,bool of,int nbrow,int nbcol, double distx,double disty,int nblevel,double lspacing);
	CLibS* RotateCopyP(CDC *hdc,double ang,int nnb, bool align,int nblevel,int dlevel, CLibS *line);
	CLibS* copybyC(CDC *hdc,CVector cent,CVector point,CFigure *pbulk, CLibS *line);
	CLibS* RotateCopyP(CDC *hdc,CVector cent,CVector point,bool align, CLibS* line);
	CLibS* paste(CVector cent,CVector point,CLibS *line);
	void Updateselect();
	bool inReg(CFigure *c1,CFigure *r1);
	void mirror(CFigure *base, CFigure *line,CFigure *result);
    /*	CCercle mirror(CFigure *base, CCercle *line);
     CLine mirror(CFigure *base, CLine *line);
     CRectangle mirror(CFigure *base, CRectangle *line);*/
	CLibS* mirror(CFigure *base, CLibS* line);
	CBezier* subdivide(double t, int p,double *U,CVector *P,int n);
	vector<CVector*> linesel;
	CInter();
	virtual ~CInter();
    
};
#endif /* defined(__testcommand__CInter__) */
