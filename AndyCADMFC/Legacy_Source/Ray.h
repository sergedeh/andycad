// Ray.h: interface for the CRay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAY_H__F445B457_CD9E_45D4_9E30_1CB6068BFA8E__INCLUDED_)
#define AFX_RAY_H__F445B457_CD9E_45D4_9E30_1CB6068BFA8E__INCLUDED_

#include "CVector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
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

#endif // !defined(AFX_RAY_H__F445B457_CD9E_45D4_9E30_1CB6068BFA8E__INCLUDED_)
