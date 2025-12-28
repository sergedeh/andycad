// ParserFloat.h: interface for the CParserFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERFLOAT_H__268FD18C_876E_463A_AD39_FC87D17AE656__INCLUDED_)
#define AFX_PARSERFLOAT_H__268FD18C_876E_463A_AD39_FC87D17AE656__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserObject.h"

class CParserFloat : public CParserObject  
{
public:
	CParserFloat(CString s="");
	virtual ~CParserFloat();
	bool isLegal();
	double getValue() {return value;}
    protected:
	float value;

};

#endif // !defined(AFX_PARSERFLOAT_H__268FD18C_876E_463A_AD39_FC87D17AE656__INCLUDED_)
