// ParserArc.h: interface for the CParserArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERARC_H__614429E3_EF7B_4123_BA39_2D529CC9057A__INCLUDED_)
#define AFX_PARSERARC_H__614429E3_EF7B_4123_BA39_2D529CC9057A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Verb.h"

class CParserArc : public CVerb  
{
public:
	void Execute();
	CParserArc(CString s="");
	virtual ~CParserArc();

};

#endif // !defined(AFX_PARSERARC_H__614429E3_EF7B_4123_BA39_2D529CC9057A__INCLUDED_)
