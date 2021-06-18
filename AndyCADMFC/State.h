// State.h: interface for the CState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATE_H__4A887451_7AE8_4932_AF1B_0622408C52DA__INCLUDED_)
#define AFX_STATE_H__4A887451_7AE8_4932_AF1B_0622408C52DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "figure.h"

class CState  
{
public:
	virtual void processpoint(CVector point);
	CState();
	virtual ~CState();

protected:
	CFigure* figure;
};

#endif // !defined(AFX_STATE_H__4A887451_7AE8_4932_AF1B_0622408C52DA__INCLUDED_)
