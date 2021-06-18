// Observer.h: interface for the CObserver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBSERVER_H__576935D0_377C_42A4_8097_57B1959DC11F__INCLUDED_)
#define AFX_OBSERVER_H__576935D0_377C_42A4_8097_57B1959DC11F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObserver  
{
public:
	virtual void SendNotify(CString s,void* param[7]){};
	CObserver();
	virtual ~CObserver();

};

#endif // !defined(AFX_OBSERVER_H__576935D0_377C_42A4_8097_57B1959DC11F__INCLUDED_)
