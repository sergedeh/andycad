// SnapParaGrid.h: interface for the CSnapParaGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAPPARAGRID_H__21C8A8B2_9C23_41FD_98F3_30FC71BE246B__INCLUDED_)
#define AFX_SNAPPARAGRID_H__21C8A8B2_9C23_41FD_98F3_30FC71BE246B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SnapPara.h"

class CSnapParaGrid : public CSnapPara  
{
public:
	void setBasePoint(CVector  vl);
	void execute(CVector &v, CDC *hdc);
	bool snappara2(CVector  vl,CVector vs, CVector &v);
	CSnapParaGrid();
	virtual ~CSnapParaGrid();
protected:

};

#endif // !defined(AFX_SNAPPARAGRID_H__21C8A8B2_9C23_41FD_98F3_30FC71BE246B__INCLUDED_)
