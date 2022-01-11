//
//  CSnapgridp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapgridp.h"
// SnapGridP.cpp: implementation of the CSnapGridP class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapGridP::CSnapGridP()
{
//	bkcolor=RGB(42,112,219);********************
}

CSnapGridP::~CSnapGridP()
{
    
}
bool CSnapGridP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	double x=fmod(v.x-m_xbase,m_snapxspacing);
	x=x>0?x:-x;
	if(x>m_snapxspacing/2){
		if(v.x>0)
		{
            v.x-=fmod(v.x-m_xbase,m_snapxspacing);
            v.x+=m_snapxspacing;
		}else
		{
            v.x-=fmod(v.x-m_xbase,m_snapxspacing);
            v.x-=m_snapxspacing;
		}
	}else
	{
        v.x-=fmod(v.x-m_xbase,m_snapxspacing);
	}
    
	double y=fmod(v.y-m_ybase,m_snapyspacing);
	y=y>0?y:-y;
	if(y>m_snapyspacing/2){
		if(v.y>0)
		{
            v.y-=fmod(v.y-m_ybase,m_snapyspacing);
            v.y+=m_snapyspacing;
		}else
		{
            v.y-=fmod(v.y-m_ybase,m_snapyspacing);
            v.y-=m_snapyspacing;
		}
	}else
	{
        v.y-=fmod(v.y-m_ybase,m_snapyspacing);
	}
	return true;
}
void CSnapGridP::Init(CSnap *d,CVector base,CVector space)
{
	snap=d;
	m_xbase=base.x;
	m_ybase=base.y;
	m_snapxspacing=space.x;
	m_snapyspacing=space.y;
}
void CSnapGridP::execute(CVector &v, CDC *hdc)
{
	if((snapPrev)&&(absc(hitpoint-v)<m_snapxspacing/3)) return;
	CVector vl9;
	bool cv=false;
	cv=getSnapPoint(v,vl9,hdc);//draw->getSnapEndPoint(v,vl9,hdc);
	lock=cv;
	CGPoint ph=hitpoint;
	CGPoint nbb=v;
/*	int jj=hdc->SetROP2(R2_NOTXORPEN);
	CPen pen;
	pen.CreatePen(PS_SOLID,5,RGB(52,120,221));
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bkcolor);//RGB(255,128,0));
	CBrush *oldb=hdc->SelectObject(&brush);
	if(snapPrev){
		CRect nbbR=CRect(CGPoint(ph.x-10,ph.y+10),CGPoint(ph.x+10,ph.y-10));
		nbbR.NormalizeRect();
		hdc->MoveTo(ph);
		hdc->LineTo(CGPoint(ph.x-20,ph.y));
		hdc->MoveTo(ph);
		hdc->LineTo(CGPoint(ph.x+20,ph.y));
		hdc->MoveTo(ph);
		hdc->LineTo(CGPoint(ph.x,ph.y+20));
		hdc->MoveTo(ph);
		hdc->LineTo(CGPoint(ph.x,ph.y-20));
	}
	if(cv)
	{
		CRect nbbR=CRect(CGPoint(nbb.x-10,nbb.y+10),CGPoint(nbb.x+10,nbb.y-10));
		nbbR.NormalizeRect();
        //		BOOL nu=hdc->Rectangle(nbbR);
		hdc->MoveTo(nbb);
		hdc->LineTo(CGPoint(nbb.x-20,nbb.y));
		hdc->MoveTo(nbb);
		hdc->LineTo(CGPoint(nbb.x+20,nbb.y));
		hdc->MoveTo(nbb);
		hdc->LineTo(CGPoint(nbb.x,nbb.y+20));
		hdc->MoveTo(nbb);
		hdc->LineTo(CGPoint(nbb.x,nbb.y-20));
		snapPrev=true;
	}else
	{
		snapPrev=false;
	}
	hdc->SetROP2(jj);
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
	hitpoint=v;*///***************************
    
}
