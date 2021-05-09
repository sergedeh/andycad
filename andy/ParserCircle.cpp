// ParserCircle.cpp: implementation of the CParserCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ParserCircle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserCircle::CParserCircle(CString s):CVerb(s)
{
  value = CIRCLE;
}

CParserCircle::~CParserCircle()
{

}

void CParserCircle::Execute()
{

}
