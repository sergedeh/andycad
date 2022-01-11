// Vectorv.h: interface for the CVectorv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORV_H__45364FB0_A4D9_49CC_AB05_9771216F9987__INCLUDED_)
#define AFX_VECTORV_H__45364FB0_A4D9_49CC_AB05_9771216F9987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CVector.h"

class CVectorv : public CVector  
{
public:
	CVectorv();
	virtual ~CVectorv();
	
	//friend class COperation;
	void assign(CVector begin, CVector end);
	void assign(CVector vec);
	CVectorv(double fx,double fy); 
	CVectorv(const CVector begin,const CVector end);

	inline CVectorv& polarc(double absc,double argu){ return CVectorv(absc*cos(argu),absc*sin(argu));}
	inline CVectorv mult(CVector v) { return CVectorv(x*v.x,-y*v.y);};
	inline CVectorv mult(double v) { return CVectorv(x*v,y*v);};
	inline  CVectorv (CVector v) {x=v.x;y=v.y;}; 

	inline CVectorv operator -(int i){return CVectorv(x-i,y-i);}
	inline CVectorv operator +(int i){return CVectorv(x+i,y+i);}
	inline CVectorv operator /(int i){return CVectorv(x/i,y/i);}



};

#endif // !defined(AFX_VECTORV_H__45364FB0_A4D9_49CC_AB05_9771216F9987__INCLUDED_)

