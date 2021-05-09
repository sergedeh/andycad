// SnapMidP.h: interface for the CSnapMidP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPMIDP_H__3241B4BD_8C68_40B4_A55A_76C184B996BC__INCLUDED_)
#define AFX_SNAPMIDP_H__3241B4BD_8C68_40B4_A55A_76C184B996BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "snappoint.h"
#include "vector.h"

class CSnapMidP : public CSnapPoint  
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapMidP();
	virtual ~CSnapMidP();

};

#endif // !defined(AFX_SNAPMIDP_H__3241B4BD_8C68_40B4_A55A_76C184B996BC__INCLUDED_)
