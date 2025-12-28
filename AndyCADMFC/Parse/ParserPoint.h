// ParserPoint.h: interface for the CParserPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERPOINT_H__E7161704_1F3F_461C_952F_AA915CBECEA6__INCLUDED_)
#define AFX_PARSERPOINT_H__E7161704_1F3F_461C_952F_AA915CBECEA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserObject.h"

class CParserPoint : public CParserObject  
{
public:
	CParserPoint(CString s="");
	virtual ~CParserPoint();
    bool isLegal();
	double getValue() {return value;}
    protected:
	float value;
};

#endif // !defined(AFX_PARSERPOINT_H__E7161704_1F3F_461C_952F_AA915CBECEA6__INCLUDED_)
