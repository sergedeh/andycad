//
//  CSnappoint.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnappoint.h"
// SnapPoint.cpp: implementation of the CSnapPoint class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapPoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapPoint::CSnapPoint()
{
	snapPrev=false;
	lock=false;
	hitpoint=CVector(0,0);
	pvl=CVector(0,0);
	xvl=pvl;
	xvp=xvl;
}

CSnapPoint::~CSnapPoint()
{
    
}
void CSnapPoint::Init(CSnap *_snap,CVector space)
{
	snap=_snap;
	lock=false;
	m_snapxspacing=space.x;
	m_snapyspacing=space.y;
	min_spacing=space.x<space.y?space.x:space.y;
	min_spacing=min_spacing/3;
}
bool CSnapPoint::isSnapped()
{
	return lock;
}
void CSnapPoint::execute(CVector &v, CDC *hdc)
{
	CVector _vh=hitpoint;_vh.v2D();
	CVector _vv=v;_vv.v2D();
	if((snapPrev)&&(absc(_vh-_vv)<20)) return;//min_spacing)) return;
	CVector vl9;
	bool cv=false;
	cv=getSnapPoint(v,vl9,hdc);//draw->getSnapEndPoint(v,vl9,hdc);
	lock=cv;
	CGPoint ph=hitpoint;
	CGPoint nbb=v;
/*	int jj=hdc->SetROP2(R2_NOTXORPEN);
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(52,120,221));
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bkcolor);//RGB(255,128,0));
	CBrush *oldb=hdc->SelectObject(&brush);
	if(snapPrev){
		CRect nbbR=CRect(CGPoint(ph.x-10,ph.y+10),CGPoint(ph.x+10,ph.y-10));
		nbbR.NormalizeRect();
		BOOL nv=hdc->Rectangle(nbbR);
	}
	if(cv)
	{
		CRect nbbR=CRect(CGPoint(nbb.x-10,nbb.y+10),CGPoint(nbb.x+10,nbb.y-10));
		nbbR.NormalizeRect();
		BOOL nu=hdc->Rectangle(nbbR);
		snapPrev=true;
	}else
	{
		snapPrev=false;
	}
	hdc->SetROP2(jj);
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
	hitpoint=v;*///***************
    
}
