// Property.h: interface for the CProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTY_H__8807CD1A_1594_4261_9940_8F21AFC679CE__INCLUDED_)
#define AFX_PROPERTY_H__8807CD1A_1594_4261_9940_8F21AFC679CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
using namespace std;

class CProperty  
{
public:
	virtual void getValue(CProperty* p) {};
	virtual void getValue(vector<CProperty*>& p) {};
	virtual void setValue(CProperty* v){};
	CString getName();
	CString getType();
	CProperty(CString n) {name=n;};
	CProperty();
	virtual ~CProperty();
private:
	CString name;
};

#endif // !defined(AFX_PROPERTY_H__8807CD1A_1594_4261_9940_8F21AFC679CE__INCLUDED_)
