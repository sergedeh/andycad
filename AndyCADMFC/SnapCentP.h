// SnapCentP.h: interface for the CSnapCentP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPCENTP_H__ED60497D_188E_4BE0_9D97_413404635544__INCLUDED_)
#define AFX_SNAPCENTP_H__ED60497D_188E_4BE0_9D97_413404635544__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "CVector.h"

class CSnapCentP : public CSnapPoint  
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapCentP();
	virtual ~CSnapCentP();

};

#endif // !defined(AFX_SNAPCENTP_H__ED60497D_188E_4BE0_9D97_413404635544__INCLUDED_)
