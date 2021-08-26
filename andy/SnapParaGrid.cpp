// SnapParaGrid.cpp: implementation of the CSnapParaGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "SnapParaGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapParaGrid::CSnapParaGrid()
{
}

CSnapParaGrid::~CSnapParaGrid()
{

}
void CSnapParaGrid::setBasePoint(CVector  vl)
{
	bool cv=false;
	CVector vxunit;
	vxunit.getcoorx();
	xvl=vxunit;
	cv=snappara2(xvl,xvp,vl);
	if(!cv) 
	{
		CVector vyunit;
		vyunit.getcoory();
		xvl=vyunit;
		cv=snappara2(xvl,xvp,vl);
	}
	xvp=vl;
}

bool CSnapParaGrid::snappara2(CVector  vl,CVector vs, CVector &v)
{
		CVector vo,ve;
//		CVector _vs=vs;_vs.v2D();
//		CVector _vv=v;_vv.v2D();
//		CVector _vl=vl;_vl.v2D();
//		ve=_vl.ppprojection(_vv-_vs,&vo);
		ve=vl.ppprojection(v-vs,&vo);
		CVector v1=v-vs,v01=vo;
		v1.v2D();v01.v2D();
		ve=v01-v1;
		double d=absc(ve);
		if((d<20)&&(d>=0))
		{
			v=vs+vo;
			return true;
		}

		return false;

}

void CSnapParaGrid::execute(CVector &v, CDC *hdc)
{
	CVector _vh=hitpoint;_vh.v2D();
	CVector _vv=v;_vv.v2D();
	if((snapPrev)&&(absc(_vh-_vv)<20)) return;//min_spacing)) return;
//	if((snapPrev)&&(absc(hitpoint-v)<20)) return;
	CVector vl9;

	bool cv=false;
	CVector vxunit;
	vxunit.getcoorx();
	xvl=vxunit;
	cv=snappara2(xvl,xvp,v);
	if(!cv) 
	{
		CVector vyunit;
		vyunit.getcoory();
		xvl=vyunit;
		cv=snappara2(xvl,xvp,v);
	}


	vl9=xvl;
	CPoint ph=hitpoint;
	CPoint nbb=xvp;//v;
	int jj=hdc->SetROP2(R2_NOTXORPEN); 
	CPen pen;
	pen.CreatePen(PS_DASH,1,RGB(52,120,221));
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
