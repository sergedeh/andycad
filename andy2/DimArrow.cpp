// DimArrow.cpp: implementation of the CDimArrow class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "DimArrow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimArrow::CDimArrow()
{

}
void CDimArrow::initArrow(int _style, CFigure& line,float u1, float u2,int u,bool dir)
{
	switch(_style)
	{
	case 0:
		Arrow();
		if(!dir)
			setRefLine(2.5,1);
		else
			setRefLine(1,2.5);
		connectTo(&line,u1,u2,u);
		break;
	default:
		break;
	}
}
void CDimArrow::Arrow()
{
	CPoint p0(0,0);
	CPoint p2(0,10);
	CPoint p1(30,5);
	vector<CVector> g;
	g.push_back(p0);
	g.push_back(p1);
	g.push_back(p2);
	g.push_back(p0);
	CLine l(g);
	copy(&l);
	cancharge=true;
}
CDimArrow::~CDimArrow()
{

}
