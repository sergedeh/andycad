// Spline.cpp: implementation of the CSpline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Spline.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpline::CSpline()
{

}

CSpline::~CSpline()
{

}

CFigure * CSpline::closecurve()
{
	vector<CVector> v0;
	v0.push_back(elem[0]->ptbegin[0]);
	v0.push_back(*(elem[iter-1]->ptend.end()-1));
	CVector vc=v0[0];
	v0[0]=v0[1];
	v0[1]=vc;

  CBezier *b=new CBezier(3,v0);
  add(b);
  v.clear();
  for(int j=0;j<iter;j++)
  {
	  for(vector<CVector>::iterator i=elem[j]->ptbegin.begin();i!=elem[j]->ptbegin.end();i++)
	  {
		v.push_back(i);
	  }

  }
  return b;
}

void CSpline::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
	if((click)||(multiselect))
	{

	prevptend=ptend;
	prevptbegin=ptbegin;
	vector<CVector*>::iterator k;
	
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);
	bool b=false;
	for (k=v.begin();k!=v.end();k++)
	{
		ptsBegin=**k;
	
		if (pointinRegion(ptsBegin,prevpos))
		{
			**k=postpos;
			drawpoint(hdc,*k);
			b=true;
		}
	}
	if(!b) 
		CLibS::translate(wnd,hdc,prevpos,postpos);
	else
	{
		ptbegin.clear();
		ptend.clear();
		for(int i=0;i<iter;i++)
		{
			ptbegin.insert(ptbegin.end(),elem[i]->ptbegin.begin(),elem[i]->ptbegin.end());
			ptend.insert(ptend.end(),elem[i]->ptend.begin(),elem[i]->ptend.end());
			((CBezier*)elem[i])->redraw=true;
		}

			if((!multiselect)||(!getLibstatus()))
			{
				updatecore();
				for(int i=0;i<iter;i++)
				{
					elem[i]->setcore(core);
				}
			}
	}
	}

}

bool CSpline::PtinRegion(CVector point)
{
	click=false;
	for(int i=0;i<iter;i++)
	{
		bool vt;
		vt=elem[i]->PtinRegion(point);
		if (vt)
		{
			sel[i]=true;
		}
		else 
		{
			sel[i]=false;
		}
		click|=vt;
		if(click)
		{
			select=elem[i]->getselectmode();
			for(int i=0;i<iter;i++)
			{
				elem[i]->setselectmode(select);//selecttoint());
			}
		}
	}
	if((Rectangleselect(point))&&(!multiselect))
	{
		select=st;
		if(!multiselect)
		{
			for(int i=0;i<iter;i++)
			{
		//		elem[j]->setrecselect(i);
				elem[i]->setcore(core);
				elem[i]->setmultcore(true);
				elem[i]->setselectmode(selecttoint());
				elem[i]->setrecselect(recselectpoint);
			}
		}
	click=true;
	}
	else
	{
		if(!multiselect)
		{
			for(int i=0;i<iter;i++)
			{
				elem[i]->setmultcore(false);
			}	
		}
	}
	if(!multiselect)
	{
		for(i=0;i<iter;i++)
		{
			elem[i]->setMultselect(click);
		}
	}
	return click;

}

void CSpline::drawselect(CDC *hdc)
{
  if((!multiselect)||(!getLibstatus()))
  {
	for(int i=0;i<iter;i++)
	{
		elem[i]->drawselect(hdc);
	}
		CPoint pt0(core[8]);
		hdc->MoveTo(pt0);
		hdc->TextOut(pt0.x,pt0.y,"Ol");
		CPoint pt1(core[9]);
		hdc->LineTo(pt1);
		hdc->TextOut(pt1.x,pt1.y,"Xl");
		hdc->MoveTo(pt0);
		CPoint pt2(core[10]);
		hdc->LineTo(pt2);
		hdc->TextOut(pt2.x,pt2.y,"Yl");
		hdc->MoveTo(pt0);
		CPoint pt3(core[11]);
		hdc->LineTo(pt3);
		hdc->TextOut(pt3.x,pt3.y,"Z");
  }
}

void CSpline::closecurve(CVector point, CDC *hdc)
{
/*	for(int i=0;i<iter;i++)
	{
		elem[i]->closecurve(point,hdc);
	}*/
/*	b.getdisplayparam(this);
	vector<CVector> pM;
	int m=0;
	int j=0;
	CVector c;
	for(int i=0;i<iter;i++)
	{
		CVector* M1=elem[i]->getVector();
		m=_msize(M1)/sizeof(c);
		for(int jj=0;jj<m;jj++)
		{
			pM.push_back(M1[jj]);
		}
		free(M1);
	}
	j=pM.size();
	CVector *M=new CVector[j];
	for(i=0;i<j;i++)
	{
		M[i]=pM[i];
	}

	if(texture_file!="")
	{
		CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
        b.ScanPolygon(hdc,bcolor,M,j,&texture);
    }
	else
	{
        b.ScanPolygon(hdc,bcolor,M,j,NULL);
	}

	delete []M;*/
	cl=true;
	draw(hdc);

}

void CSpline::draw(CDC *hdc)
{
	if(cl)
	{
	b.getdisplayparam(this);
	vector<CVector> pM;
	int m=0;
	int j=0;
	CVector c;
	for(int i=0;i<iter;i++)
	{
		CVector* M1=elem[i]->getVector();
		m=_msize(M1)/sizeof(c);
		for(int jj=0;jj<m;jj++)
		{
			pM.push_back(M1[jj]);
		}
		free(M1);
	}
	j=pM.size();
	CVector *M=new CVector[j];
	for(i=0;i<j;i++)
	{
		M[i]=pM[i];
	}

	if(texture_file!="")
	{
		CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
        b.ScanPolygon(hdc,bcolor,M,j,&texture);
    }
	else
	{
        b.ScanPolygon(hdc,bcolor,M,j,NULL);
	}
	delete []M;
	}
	CLibS::draw(hdc);

}
