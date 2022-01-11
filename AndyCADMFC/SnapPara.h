// SnapPara.h: interface for the CSnapPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPPARA_H__1C066187_8A39_4548_8F56_42C0D9743110__INCLUDED_)
#define AFX_SNAPPARA_H__1C066187_8A39_4548_8F56_42C0D9743110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "CVector.h"

class CSnap;
class CSnapPara : public CCommand  
{
public:
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);
	void setBasePoint(CVector  vl);
	bool snappara2(CVector  vl,CVector vs, CVector &v);

	CSnapPara();
	virtual ~CSnapPara();
protected:
	bool snappara(CVector  vl,CVector& vs, CVector &v);
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	CSnap* snap;
	float	m_snapxspacing;
	float	m_snapyspacing;


};

#endif // !defined(AFX_SNAPPARA_H__1C066187_8A39_4548_8F56_42C0D9743110__INCLUDED_)
