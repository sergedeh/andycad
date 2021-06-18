// SnapPerp.h: interface for the CSnapPerp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPPERP_H__4CEC8B9B_A938_4958_A524_0D5DA67717EA__INCLUDED_)
#define AFX_SNAPPERP_H__4CEC8B9B_A938_4958_A524_0D5DA67717EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "vector.h"

class CSnap;
class CSnapPerp : public CCommand  
{
public:
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);
	void setBasePoint(CVector  vl);
	bool snapperp2(CVector  vl,CVector vs, CVector &v);

	CSnapPerp();
	virtual ~CSnapPerp();
private:
	bool snapperp(CVector  vl,CVector& vs, CVector &v);
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	CSnap* snap;
	float	m_snapxspacing;
	float	m_snapyspacing;

};

#endif // !defined(AFX_SNAPPERP_H__4CEC8B9B_A938_4958_A524_0D5DA67717EA__INCLUDED_)
