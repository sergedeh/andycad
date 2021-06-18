// IntP.h: interface for the CIntP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTP_H__6201234B_5617_4248_A151_7F63866440F1__INCLUDED_)
#define AFX_INTP_H__6201234B_5617_4248_A151_7F63866440F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "property.h"

class CIntP : public CProperty  
{
public:
	int getValue();
	CIntP(CString n, int p);
	void setValue(CIntP* v);
	void getValue(CIntP* p);

	CIntP();
	virtual ~CIntP();
private:
	int s;

};

#endif // !defined(AFX_INTP_H__6201234B_5617_4248_A151_7F63866440F1__INCLUDED_)
