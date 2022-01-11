//
//  CPlane.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CPlane__
#define __testcommand__CPlane__

#include <iostream>
// Plane.h: interface for the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "CVector.h"	// Added by ClassView
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

#endif /* defined(__testcommand__CPlane__) */
