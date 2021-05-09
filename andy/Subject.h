// Subject.h: interface for the CSubject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBJECT_H__E8813E84_E4FA_4F45_BB71_9E52D1207748__INCLUDED_)
#define AFX_SUBJECT_H__E8813E84_E4FA_4F45_BB71_9E52D1207748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "observer.h"


using namespace std;
class CSubject  
{
public:
	virtual void Unregister(CObserver *o);
	void setview(CView *v);
	virtual void RegisterInterest(CObserver *obs){observers.push_back(obs);};
	CSubject();
	virtual ~CSubject();
protected:
	vector<CObserver* > observers;
	CView* view;
};

#endif // !defined(AFX_SUBJECT_H__E8813E84_E4FA_4F45_BB71_9E52D1207748__INCLUDED_)
