// MultVar.h: interface for the CMultVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTVAR_H__5E9F3AD1_C52C_481F_8896_8EA774694778__INCLUDED_)
#define AFX_MULTVAR_H__5E9F3AD1_C52C_481F_8896_8EA774694778__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserVar.h"
#include <vector>
using namespace std;

class CMultVar : public CParserVar  
{
public:
	vector<CParserObject*> getVector();
	void add(CParserObject* v1);
	CMultVar(CParserObject *v1, CParserObject *v2);
	CMultVar();
	virtual ~CMultVar();
private:
	vector<CParserObject*> multVec;

};

#endif // !defined(AFX_MULTVAR_H__5E9F3AD1_C52C_481F_8896_8EA774694778__INCLUDED_)
