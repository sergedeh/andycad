// SnapEndP.h: interface for the CSnapEndP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPENDP_H__22E36D38_3B98_4063_8724_8DE8ED6A5AF8__INCLUDED_)
#define AFX_SNAPENDP_H__22E36D38_3B98_4063_8724_8DE8ED6A5AF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "vector.h"

class CSnapEndP : public CSnapPoint  
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapEndP();
	virtual ~CSnapEndP();
};

#endif // !defined(AFX_SNAPENDP_H__22E36D38_3B98_4063_8724_8DE8ED6A5AF8__INCLUDED_)
