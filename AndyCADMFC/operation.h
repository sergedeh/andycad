// Operation.h: interface for the COperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATION_H__0BB1AF49_4518_417E_9DEC_177AF371C6B1__INCLUDED_)
#define AFX_OPERATION_H__0BB1AF49_4518_417E_9DEC_177AF371C6B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vectorv.h"
#include "Vectorp.h"

class COperation  
{
public:
	COperation();
	virtual ~COperation();

	static  CVectorp operator+(CVectorp p,CVectorv v){ return CVectorp(p.x+v.x,p.y+v.y);}
	static  CVectorv operator+(CVectorv v,CVectorp p){ return CVectorv(p.x+v.x,p.y+v.y);}
	
	static CVectorp operator -(CVectorp p,CVectorv v){ return CVectorp(p.x-v.x,p.y-v.y);}
	static CVectorv operator -(CVectorv v,CVectorp p){ return CVectorv(p.x-v.x,p.y-v.y);}

	static CVectorp operator +(CVectorp p,CVectorp v){ return CVectorp(p.x+v.x,p.y+v.y);}
	static CVectorv operator +(CVectorv v,CVectorv p){ return CVectorv(p.x+v.x,p.y+v.y);}

	static CVectorp operator -(CVectorp p,CVectorp v){ return CVectorp(p.x-v.x,p.y-v.y);}
	static CVectorv operator -(CVectorv v,CVectorv p){ return CVectorv(p.x-v.x,p.y-v.y);}

};

#endif // !defined(AFX_OPERATION_H__0BB1AF49_4518_417E_9DEC_177AF371C6B1__INCLUDED_)
