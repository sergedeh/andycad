// MClick.h: interface for the CMClick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCLICK_H__BC823814_2019_439F_8941_6C07D28FE8D5__INCLUDED_)
#define AFX_MCLICK_H__BC823814_2019_439F_8941_6C07D28FE8D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Observer.h"
#include "state.h"

class CMClick : 
	public CState , 
	public CObserver  
{
public:
	void processpoint(CVector point);
	void SendNotify(CString s, void* param[7]);
	CMClick(CFigure* fig);
	virtual ~CMClick();

private:
	bool m;
};

#endif // !defined(AFX_MCLICK_H__BC823814_2019_439F_8941_6C07D28FE8D5__INCLUDED_)
