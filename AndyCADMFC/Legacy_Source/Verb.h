// Verb.h: interface for the CVerb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERB_H__3D899454_3C33_45E4_998A_FC032646E1F0__INCLUDED_)
#define AFX_VERB_H__3D899454_3C33_45E4_998A_FC032646E1F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "ParserVerb.h"
#include "figure.h"

class CVerb : public CCommand, public CParserVerb
{
public:
	void setData(CFigure *df);
	void Execute();
	CVerb(CString s);

	virtual ~CVerb();
	CFigure* figure;

};

#endif // !defined(AFX_VERB_H__3D899454_3C33_45E4_998A_FC032646E1F0__INCLUDED_)
