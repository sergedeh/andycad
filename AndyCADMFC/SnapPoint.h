// SnapPoint.h: interface for the CSnapPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPPOINT_H__16578957_BC2F_4A27_9220_C3EA4DF7E184__INCLUDED_)
#define AFX_SNAPPOINT_H__16578957_BC2F_4A27_9220_C3EA4DF7E184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "vector.h"

class CSnap;
class CSnapPoint : public CCommand  
{
public:
	virtual bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc)=0;
	bool isSnapped();
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);

	CSnapPoint();
	virtual ~CSnapPoint();
protected:
	COLORREF bkcolor;
	CSnap* snap;
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	float	m_snapxspacing;
	float	m_snapyspacing;
	float min_spacing;
private:

};

#endif // !defined(AFX_SNAPPOINT_H__16578957_BC2F_4A27_9220_C3EA4DF7E184__INCLUDED_)
