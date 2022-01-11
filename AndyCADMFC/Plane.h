// Plane.h: interface for the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANE_H__8CE805D1_E97C_45C7_98A0_8B92CB0DA265__INCLUDED_)
#define AFX_PLANE_H__8CE805D1_E97C_45C7_98A0_8B92CB0DA265__INCLUDED_

#include "CVector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CRay;
class CPlane  
{
public:
	CPlane(float p,CVector nn);
	double getCircumR();
	CVector getCircumC();
	CVector closest_point(CVector v);
	double dist_to_point(CVector p);
	CPlane();
	CPlane(CPoint i,CPoint j,CPoint k);
	virtual ~CPlane();
	CPlane(CVector i,CVector j,CVector k);
	CPlane(CVector p,CVector nn);
	CVector getBarycent(CVector p);
	friend CVector intersect(CRay l,CPlane v);

	void computeCircum();
	
	CVector n;
	double d;
	CVector p1,p2,p3;
	CVector circumC;
	double circumR;
};

#endif // !defined(AFX_PLANE_H__8CE805D1_E97C_45C7_98A0_8B92CB0DA265__INCLUDED_)
