// ParserFloat.cpp: implementation of the CParserFloat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ParserFloat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserFloat::CParserFloat(CString s)
{
    value=-1E-15;
	type=FLOAT;
	if(atof(s)!=0)
	{
	value=atof(s);
	}

}

CParserFloat::~CParserFloat()
{

}

bool CParserFloat::isLegal()
{
   return (value !=-1E-15);
}

