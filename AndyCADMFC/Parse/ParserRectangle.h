// ParserRectangle.h: interface for the CParserRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERRECTANGLE_H__C0B1A1C1_E195_4230_86BF_80BB4155A35B__INCLUDED_)
#define AFX_PARSERRECTANGLE_H__C0B1A1C1_E195_4230_86BF_80BB4155A35B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Verb.h"

class CParserRectangle : public CVerb  
{
public:
	void Execute();
	CParserRectangle(CString s="");
	virtual ~CParserRectangle();

};

#endif // !defined(AFX_PARSERRECTANGLE_H__C0B1A1C1_E195_4230_86BF_80BB4155A35B__INCLUDED_)
