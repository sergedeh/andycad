// ParserArc.cpp: implementation of the CParserArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ParserArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserArc::CParserArc(CString s):CVerb(s)
{
	value = ARC;
}

CParserArc::~CParserArc()
{

}

void CParserArc::Execute()
{

}
