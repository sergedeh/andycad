// ParserCircle.h: interface for the CParserCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERCIRCLE_H__BCEB5F6E_93EC_4513_9E9D_B2F8E57967EE__INCLUDED_)
#define AFX_PARSERCIRCLE_H__BCEB5F6E_93EC_4513_9E9D_B2F8E57967EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Verb.h"

class CParserCircle : public CVerb  
{
public:
	void Execute();
	CParserCircle(CString s="");
	virtual ~CParserCircle();

};

#endif // !defined(AFX_PARSERCIRCLE_H__BCEB5F6E_93EC_4513_9E9D_B2F8E57967EE__INCLUDED_)
