// SnapIntP.h: interface for the CSnapIntP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPINTP_H__C8F3CD4D_207F_4142_97DC_0F0038617FE0__INCLUDED_)
#define AFX_SNAPINTP_H__C8F3CD4D_207F_4142_97DC_0F0038617FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "vector.h"

class CSnapIntP : public CSnapPoint  
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapIntP();
	virtual ~CSnapIntP();

};

#endif // !defined(AFX_SNAPINTP_H__C8F3CD4D_207F_4142_97DC_0F0038617FE0__INCLUDED_)
