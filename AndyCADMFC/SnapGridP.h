// SnapGridP.h: interface for the CSnapGridP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPGRIDP_H__1CD9D43E_F588_4E8E_858F_D9A036EFB349__INCLUDED_)
#define AFX_SNAPGRIDP_H__1CD9D43E_F588_4E8E_858F_D9A036EFB349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "vector.h"

class CSnapGridP : public CSnapPoint  
{
public:
	void execute(CVector &v, CDC *hdc);
	void Init(CSnap *d,CVector base,CVector space);
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapGridP();
	virtual ~CSnapGridP();
private:
	float	m_xbase;
	float	m_ybase;
	float	m_snapxspacing;
	float	m_snapyspacing;

};

#endif // !defined(AFX_SNAPGRIDP_H__1CD9D43E_F588_4E8E_858F_D9A036EFB349__INCLUDED_)
