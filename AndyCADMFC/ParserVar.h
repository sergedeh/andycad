// ParserVar.h: interface for the CParserVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERVAR_H__20BAE668_49B8_439E_A3A7_CC21A28ED6B4__INCLUDED_)
#define AFX_PARSERVAR_H__20BAE668_49B8_439E_A3A7_CC21A28ED6B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserObject.h"
#include <vector>
using namespace std;

class CParserVar : public CParserObject  
{
public:
	CParserVar(CString s="");
	virtual ~CParserVar();

	bool isLegal();
	void addArgs(CParserObject* p);
	static int RADIUS,LENGTH;
protected:
	vector<CParserObject*> args;
};

#endif // !defined(AFX_PARSERVAR_H__20BAE668_49B8_439E_A3A7_CC21A28ED6B4__INCLUDED_)
