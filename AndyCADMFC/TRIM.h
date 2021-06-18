// TRIM.h: interface for the CTRIM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIM_H__E094EBCC_CA25_4443_AEBD_33F694AB1266__INCLUDED_)
#define AFX_TRIM_H__E094EBCC_CA25_4443_AEBD_33F694AB1266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Verb.h"

class CTRIM : public CVerb  
{
public:
	void Execute();
	CTRIM(CString s);
	virtual ~CTRIM();

};

#endif // !defined(AFX_TRIM_H__E094EBCC_CA25_4443_AEBD_33F694AB1266__INCLUDED_)
