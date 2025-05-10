//
//  CRay.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CRay__
#define __testcommand__CRay__

#include <iostream>
// Ray.h: interface for the CRay class.
//
//////////////////////////////////////////////////////////////////////
#include "../utils/CRect.hpp"
#include "../vector/CVector.h"	// Added by ClassView
class CPlane;
class CRay
{
public:
	CVector getclosestPoint(CVector v);
	void assign(CVector begin,CVector end);
	float getPara(CVector v);
	CRay();
	CRay(CVector& be,CVector& en,bool b=false):porg(be),phead(en),segment(b){};
	CRay(CPoint& be,CPoint& en,bool b=false):porg(CVector(be.x,be.y,0)),phead(CVector(en.x,en.y,0)),segment(b){};
    //	CRay(CVector& be,CVector& en,bool b=false):porg(be),phead(en),segment(b){};
	void setPara();
	CPoint Intersectp(CRay l);
	CVector Intersect(CRay l);
	virtual ~CRay();
	friend CVector intersect(CRay l,CPlane v);
	operator CVector(){ return CVector(porg,phead);}
	CVector getPorg(){return porg;}
	CVector getPhead(){return phead;}
	operator CRect(){ return CRect(porg,phead);}
    
private:
	CVector porg,phead;
	CVector p0,d;
	bool segment;
    
};

#endif /* defined(__testcommand__CRay__) */
