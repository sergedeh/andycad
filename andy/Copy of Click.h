// Click.h: interface for the CClick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLICK_H__718AA5B7_68EE_4851_97D2_D3F119CA5613__INCLUDED_)
#define AFX_CLICK_H__718AA5B7_68EE_4851_97D2_D3F119CA5613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "State.h"

class CClick : public CState  
{
public:
	void processpoint(CVector point);
	CClick(CFigure *fig);
	virtual ~CClick();

};

#endif // !defined(AFX_CLICK_H__718AA5B7_68EE_4851_97D2_D3F119CA5613__INCLUDED_)
