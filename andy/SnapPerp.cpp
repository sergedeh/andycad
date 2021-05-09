// SnapPerp.cpp: implementation of the CSnapPerp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapPerp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapPerp::CSnapPerp()
{
	snapPrev=false;
	lock=false;
	hitpoint=CVector(0,0);
	pvl=CVector(0,0);
	xvl=pvl;
	xvp=xvl;

}

CSnapPerp::~CSnapPerp()
{

}
void CSnapPerp::Init(CSnap *_snap,CVector space)
{
	snap=_snap;
	lock=false;
	m_snapxspacing=space.x;
	m_snapyspacing=space.y;
}
void CSnapPerp::execute(CVector &v, CDC *hdc)
{
//	if((snapPrev)&&(absc(hitpoint-v)<20)) return;
	CVector _vh=hitpoint;_vh.v2D();
	CVector _vv=v;_vv.v2D();
	if((snapPrev)&&(absc(_vh-_vv)<20)) return;//min_spacing)) return;
	CVector vl9;
	bool cv=false;
	if(snap->getSnapPoint(v,vl9,hdc))//draw->getSnapMidPoint(v,vl9,hdc)||draw->getSnapNearest(v,vl9,hdc)||draw->getSnapEndPoint(v,vl9,hdc))
	{
		if(vl9==CVector(0,0,0)) return;
		xvl=vl9;
		xvp=v;
	}
	cv=snapperp(xvl,xvp,v);
	vl9=xvl;
	CPoint ph=hitpoint;
	CPoint nbb=xvp;//v;
	int jj=hdc->SetROP2(R2_NOTXORPEN); 
	CPen pen;
	pen.CreatePen(PS_DASH,1,RGB(103,244,102));
	CPen *oldp=hdc->SelectObject(&pen);
	if(snapPrev){
		hdc->MoveTo(ph);
		hdc->LineTo(pvl);
		snapPrev=false;
	}
	if(cv)
	{
			hdc->MoveTo(nbb);
			hdc->LineTo(v);
			snapPrev=true;
	}else
	{
		snapPrev=false;
		cv=false;
	}
	hdc->SetROP2(jj);
	hdc->SelectObject(oldp);
	hitpoint=xvp;
	pvl=v;

}
void CSnapPerp::setBasePoint(CVector  vl)
{
		snapperp(xvl,xvp,vl);
		xvp=vl;
}
bool CSnapPerp::snapperp2(CVector  vl,CVector vs, CVector &v)
{
		CVector vo,ve;
		ve=vl.ppprojection(v-vs,&vo);
		double d=absc(ve);
		if((d<20)&&(d>=0))
		{
			v=vs+vo;
			return true;
		}

		return false;

}
bool CSnapPerp::snapperp(CVector  vl,CVector& vs, CVector &v)
{
		vl=polarc(absc(vl),argu(vl)+pi/2);
		CVector vo,ve;
		ve=vl.ppprojection(v-vs,&vo);
		double d=absc(ve);
		if((d<20)&&(d>=0))
		{
			v=vs+vo;
			return true;
		}

		return false;
}
