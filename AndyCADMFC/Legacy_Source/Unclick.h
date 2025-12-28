// Unclick.h: interface for the CUnclick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNCLICK_H__86F00F10_49BA_437E_8F2A_EED873392E62__INCLUDED_)
#define AFX_UNCLICK_H__86F00F10_49BA_437E_8F2A_EED873392E62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "State.h"

class CUnclick : public CState  
{
public:
	void processpoint(CVector point);
	CUnclick(CFigure *fig);
	virtual ~CUnclick();

};

#endif // !defined(AFX_UNCLICK_H__86F00F10_49BA_437E_8F2A_EED873392E62__INCLUDED_)
