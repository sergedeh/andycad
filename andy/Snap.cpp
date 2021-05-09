// Snap.cpp: implementation of the CSnap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Snap.h"
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include <iterator>
#include "ray.h"
#include "aabb.h"
#include "tvector.h"
#include "intp.h"
#include "snapobjectdlg.h"
#include "snapgriddlg.h"
#include "draw.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

class istop;

typedef multimap<CVector,S,istop> vtoS;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnap::CSnap()
{
	snapPrev=false;
	hitpoint=CVector(0,0);
	pvl=CVector(0,0);
	xvl=pvl;
	xvp=xvl;
	j=0;
	b_prev=false;
	visible=false;
	m_appint = FALSE;
	m_center = FALSE;
	m_endpoint = FALSE;
	m_exten = FALSE;
	m_inter = FALSE;
	m_midpoint = FALSE;
	m_nearest = FALSE;
	m_para = FALSE;
	m_perp = FALSE;
	m_snaponobj = FALSE;
	m_tangent = FALSE;
	m_trackingon = FALSE;

	m_gridon = FALSE;
	m_snapongrid = FALSE;
	m_angle = 0.0f;
	m_gridxspacing = 5.0f;
	m_gridyspacing = 5.0f;
	m_polardistance = 0.0f;
	m_xbase = 0.0f;
	m_ybase = 0.0f;
	m_snapxspacing = 5.0f;
	m_snapyspacing = 5.0f;


}

CSnap::~CSnap()
{

}

class isleft
{
public:
	const bool operator () (point s1,point s2)
	{

		return (s1.v.x>s2.v.x);
	};
};
class istop:public binary_function<CVector,CVector,bool>
{
public:
	bool operator () (first_argument_type s1,second_argument_type s2) const
	{

		return s1.y<s2.y;
	};
	bool operator () (first_argument_type s1)
	{

		return s1.y<s2.y;
	};
	istop(first_argument_type s):s2(s){};
	istop(){};
protected:
	first_argument_type s2;
};

class isbot:public binary_function<S,S,bool>
{
public:
	bool operator () (first_argument_type s1,second_argument_type s2) const
	{

		return s1.top()>s2.top();
	};
};


/*bool isSleft(S e1,S e2)
{
	return true;
}*/
const bool ispleft(CVector p, S s)
{
	return (p.x==s.left());
}
CVector intersect(S s1,S s2)
{
	CRay v1(s1.b,s1.e,1);
	CRay v2(s2.b,s2.e,1);
	
	CVector inter=v2.Intersect(v1);
	return inter;
}



queue<CVector> poter;

void CSnap::SendNotify(CString s, void *param[])
{
	if(s=="vertices")
	{
		vector<CVector>* vecb=(vector<CVector>*)param[0];
		vector<CVector>* vece=(vector<CVector>*)param[1];
		vsegment.clear();
		for(vector<CVector>::iterator ib=vecb->begin(),ie=vece->begin();ib!=vecb->end();ib++,ie++)
		{
			vsegment.push_back(S(*ib,*ie));
		}
	}
	else
	if(s=="mouse")
	{
	//	CPoint *v=(CPoint*)param[0];
	//	poter.push(*v);
	//	CDC* hdc=(CDC*)param[1];
//		checksnap(*v,hdc);
	}

}

void CSnap::checksnap(CVector v, CDC *hdc)
{
	for(int i=0;i<*nbf;i++)
	{
	}
}

void CSnap::display(CVector v, CDC *hdc)
{
  CAABB r,r2;
  CBrush brush(RGB(0,255,0));
  CBrush* oldbrush=hdc->SelectObject(&brush);
  CVector v1;
  if(v.w!=-2)
  {
  int oldr2=hdc->SetROP2(R2_NOTXORPEN);
  if(b_prev)
  {
	  CPoint p1=prev;
	  CRect rt2(p1.x,p1.y,p1.x,p1.y);
	  rt2.InflateRect(5,5);
	  hdc->Ellipse(rt2);
	  tool.draw(hdc);
//	  rt2.OffsetRect(0,7);
//	  hdc->DrawText();

  }
  else
  {
 		tool.assign(hdc,v,"Hello");

  }
	
  CPoint p1=v;
  CRect rt2(p1.x,p1.y,p1.x,p1.y);
  rt2.InflateRect(5,5);
  hdc->Ellipse(rt2);
  b_prev=true;
  v_current=v;
  hdc->SetROP2(oldr2);
  }
  
  if((v.w==-2)&&(b_prev))
  {
	  int oldr2=hdc->SetROP2(R2_NOTXORPEN);
	  b_prev=false;
	  CPoint p1=prev;
	  CRect rt2(p1.x,p1.y,p1.x,p1.y);
	  rt2.InflateRect(5,5);
	  hdc->Ellipse(rt2);
	  hdc->SetROP2(oldr2);
	  b_prev=false;
  }
  
  hdc->SelectObject(oldbrush);
  prev=v;
}


void CSnap::clear(CDC *hdc)
{
}

void CSnap::executePoint(CVector &v, CDC *hdc)
{
	if(m_snaponobj)
	{
		if(m_para)
		{
			para_snap.setBasePoint(v);
			para_snap.execute(v,hdc);
		}
		if(m_perp)
		{
			perp_snap.setBasePoint(v);
			perp_snap.execute(v,hdc);
		}else
		if(m_midpoint)
		{
			CVector vl;
			midp_snap.getSnapPoint(v,vl,hdc);
		}
		if(m_nearest)
		{
			CVector vl;
			nearp_snap.getSnapPoint(v,vl,hdc);
		}
		if(m_endpoint)
		{
			CVector vl;
			endp_snap.getSnapPoint(v,vl,hdc);
		}
		if(m_inter)
		{
			CVector vl;
			intp_snap.getSnapPoint(v,vl,hdc);
		}
		if(m_center)
		{
			CVector vl;
			centp_snap.getSnapPoint(v,vl,hdc);
		}
	}
		if(m_snapongrid)
		{
			CVector vl;
			gridp_snap.getSnapPoint(v,vl,hdc);
			grid_snap.setBasePoint(v);
			grid_snap.execute(v,hdc);
		}else
		{
			execute(v,hdc);
		}

	
}
void CSnap::execute(CVector &v, CDC *hdc)
{
	if(m_snaponobj)
	{
		bool cv=false;
		CVector vl;
		if(m_appint)
			draw->getAppInt(v);
		if(m_center)
		{
			centp_snap.execute(v,hdc);
			cv=centp_snap.isSnapped();
		}
		if((m_endpoint)&&(!cv))
		{
			endp_snap.execute(v,hdc);
			cv=endp_snap.isSnapped();
		}
		if((m_exten)&&(!cv))
		{
			cv=draw->getSnapExten(v,hdc);
		}
		if((m_inter)&&(!cv))
		{
			intp_snap.execute(v,hdc);
			cv=intp_snap.isSnapped();
		}
		if((m_midpoint)&&(!cv))
		{
			midp_snap.execute(v,hdc);
			cv=midp_snap.isSnapped();
		}
		if((m_nearest)&&(!cv))
		{
			if((snapPrev)&&(absc(hitpoint-v)<10)) return;
			nearp_snap.execute(v,hdc);
			cv=nearp_snap.isSnapped();
		}
		if(m_exten)
		{
		CPoint ph=hitpoint;
		CPoint nbb=v;
		int jj=hdc->SetROP2(R2_NOTXORPEN); 
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(52,120,221));
		CPen *oldp=hdc->SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(42,112,219));
		CBrush *oldb=hdc->SelectObject(&brush);
		if(snapPrev){
			CRect nbbR=CRect(CPoint(ph.x-10,ph.y+10),CPoint(ph.x+10,ph.y-10));
			nbbR.NormalizeRect();
			BOOL nv=hdc->Rectangle(nbbR);
		}
		if(cv)
		{
			CRect nbbR=CRect(CPoint(nbb.x-10,nbb.y+10),CPoint(nbb.x+10,nbb.y-10));
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
		hitpoint=v;
		}
		if(m_para)
		{
			para_snap.execute(v,hdc);
		}
		if(m_perp)
		{
			perp_snap.execute(v,hdc);
		}
		if(m_tangent)
			draw->getSnapTangent(v,hdc);
//		display(v,hdc);
	}
	if(m_snapongrid)
	{
			gridp_snap.execute(v,hdc);
			grid_snap.execute(v,hdc);

/*		if(!b_prev)
		{
			v.x-=fmod(v.x,m_snapxspacing);
			v.y-=fmod(v.y,m_snapyspacing);
			vprev=v;
			b_prev=true;
		//	v=vprev;
			return;
		}
		CVector v1;
		float f=m_snapxspacing/10;
		f=2;
		float fmx=v.x-vprev.x;//fmod(v.x,m_snapxspacing);
		float fmy=v.y-vprev.y;//fmod(v.y,m_snapyspacing);
		if(v==vprev) return;
		float afmx=fmx>0?fmx:-fmx;
		float afmy=fmy>0?fmy:-fmy;

//		if(v!=vprev)
		{
		if(afmx>afmy)
		{
			if(afmx>=f)
			{
				v.x=fmx>0?vprev.x + m_snapxspacing:vprev.x - m_snapxspacing;
				v.y=vprev.y;
			}
			else
				v=vprev;
		}
		else
		{
			if(afmy>=f)
			{
				v.y=fmy>0?vprev.y + m_snapyspacing:vprev.y - m_snapyspacing;
				v.x=vprev.x;
			}
			else
				v=vprev;

		}
		if(afmx==afmy)
		{
			v=vprev;
//			v.x=fxmin;
//			v.y=fymin;
		}
		}*/
	}
	else
		b_prev=false;
	vprev=v;
//	if(m_gridon)
//		displaygrid(hdc,draw);

}
void CSnap::init()
{
	para_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	perp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	endp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	midp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	nearp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	intp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	centp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	gridp_snap.Init(this,CVector(m_xbase,m_ybase,0),CVector(m_snapxspacing,m_snapyspacing));
	grid_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
}
bool CSnap::getSnapPoint(CVector& v,CVector &vl,CDC* hdc,CString type)
{
	if(type=="center")
	{
		return draw->getSnapCenter(v,hdc);
	}
	if(type=="end")
	{
		return draw->getSnapEndPoint(v,vl,hdc);
	}
	if(type=="inter")
	{
	    return draw->getSnapInter(v,hdc);
	}
	if(type=="mid")
	{
		return draw->getSnapMidPoint(v,vl,hdc);
	}
	if(type=="near")
	{
		return draw->getSnapNearest(v,vl,hdc);
	}
	if(type=="")
	{
	return draw->getSnapMidPoint(v,vl,hdc)||draw->getSnapNearest(v,vl,hdc)||draw->getSnapEndPoint(v,vl,hdc);
	}
}
void CSnap::init(vector<CProperty *> dlg,CDraw* d,CDC* hdc)
{

	CSnapObjectDlg* odlg=(CSnapObjectDlg*)dlg[1];
	m_appint = odlg->m_appint;
	m_center = odlg->m_center;
	m_endpoint = odlg->m_endpoint;
	m_exten = odlg->m_exten;
	m_inter = odlg->m_inter;
	m_midpoint = odlg->m_midpoint;
	m_nearest = odlg->m_nearest;
	m_para = odlg->m_para;
	m_perp = odlg->m_perp;
	m_snaponobj = odlg->m_snapon;
	m_tangent = odlg->m_tangent;
	m_trackingon = odlg->m_trackingon;

	CSnapGridDlg* gdlg=(CSnapGridDlg*)dlg[0];
	m_gridon = gdlg->m_gridon;
	m_snapongrid = gdlg->m_snapon;
	m_angle = gdlg->m_angle;
	m_gridxspacing = gdlg->m_gridxspacing;
	m_gridyspacing = gdlg->m_gridyspacing;
	m_polardistance = gdlg->m_polardistance;
	m_xbase = gdlg->m_xbase;
	m_ybase = gdlg->m_ybase;
	m_snapxspacing = gdlg->m_snapxspacing;
	m_snapyspacing = gdlg->m_snapyspacing;
	b_prev=false;
/*	if(visible)
	snapPrev=true;
	else
		snapPrev=false;*/
	snapPrev=false;
	draw=d;
	para_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	perp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	endp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	midp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	nearp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	intp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	centp_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	gridp_snap.Init(this,CVector(m_xbase,m_ybase,0),CVector(m_snapxspacing,m_snapyspacing));
	grid_snap.Init(this,CVector(m_snapxspacing,m_snapyspacing));
	execute(hitpoint,hdc);

}

void CSnap::displaygrid(CDC *hdc,CDraw *draw)
{

//	snapPrev=false;
//	execute(hitpoint,hdc);
 if(m_gridon)
	draw->displaygrid(hdc,m_gridxspacing);//,m_gridyspacing);
}

void CSnap::setval(vector<CProperty *>dlg)
{
	CSnapObjectDlg* odlg=(CSnapObjectDlg*)dlg[1];
	odlg->m_appint=m_appint;
	 odlg->m_center=m_center;
	 odlg->m_endpoint=m_endpoint;
	 odlg->m_exten=m_exten;
	 odlg->m_inter=m_inter;
	 odlg->m_midpoint=m_midpoint;
	 odlg->m_nearest=m_nearest;
	 odlg->m_para=m_para ;
	 odlg->m_perp=m_perp;
	 odlg->m_snapon=m_snaponobj;
	 odlg->m_tangent=m_tangent;
	 odlg->m_trackingon=m_trackingon;

	CSnapGridDlg* gdlg=(CSnapGridDlg*)dlg[0];
	 gdlg->m_gridon=m_gridon;
	 gdlg->m_snapon=m_snapongrid;
	 gdlg->m_angle=m_angle;
	 gdlg->m_gridxspacing=m_gridxspacing;
	 gdlg->m_gridyspacing=m_gridyspacing;
	 gdlg->m_polardistance=m_polardistance;
	 gdlg->m_xbase=m_xbase;
	 gdlg->m_ybase=m_ybase;
	 gdlg->m_snapxspacing=m_snapxspacing;
	 gdlg->m_snapyspacing=m_snapyspacing;

}
