// StringP.h: interface for the CStringP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGP_H__BBE403C4_93F6_4297_A81A_54E388E43F75__INCLUDED_)
#define AFX_STRINGP_H__BBE403C4_93F6_4297_A81A_54E388E43F75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "property.h"

class CStringP : public CProperty  
{
public:
	void setValue(CStringP* v);
	void getValue(CStringP* p);
	CStringP();
	virtual ~CStringP();
private :
	CString s;

};

#endif // !defined(AFX_STRINGP_H__BBE403C4_93F6_4297_A81A_54E388E43F75__INCLUDED_)
