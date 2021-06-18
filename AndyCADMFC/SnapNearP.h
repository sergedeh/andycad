// SnapNearP.h: interface for the CSnapNearP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPNEARP_H__F789E55C_4B13_42E8_A7FF_903D38945877__INCLUDED_)
#define AFX_SNAPNEARP_H__F789E55C_4B13_42E8_A7FF_903D38945877__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "vector.h"

class CSnapNearP : public CSnapPoint  
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapNearP();
	virtual ~CSnapNearP();

};

#endif // !defined(AFX_SNAPNEARP_H__F789E55C_4B13_42E8_A7FF_903D38945877__INCLUDED_)
