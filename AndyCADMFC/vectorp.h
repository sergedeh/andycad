// Vectorp.h: interface for the CVectorp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORP_H__2DC3C92B_748A_42A8_9DDF_D8562575CDDE__INCLUDED_)
#define AFX_VECTORP_H__2DC3C92B_748A_42A8_9DDF_D8562575CDDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CVector.h"


class CVectorp : public CVector  
{
public:
	CVectorp();
	virtual ~CVectorp();

	void assign(CVectorp vec);
	CVectorp(double fx,double fy); 
	CVectorp(const CPoint point);
	inline CVectorp& polarc(double absc,double argu){ return CVectorp(absc*cos(argu),absc*sin(argu));}



	inline CVectorp operator -(int i){return CVectorp(x-i,y-i);}
	inline CVectorp operator +(int i){return CVectorp(x+i,y+i);}
	inline CVectorp operator /(int i){return CVectorp(x/i,y/i);}
	friend class COperation;

};

#endif // !defined(AFX_VECTORP_H__2DC3C92B_748A_42A8_9DDF_D8562575CDDE__INCLUDED_)
