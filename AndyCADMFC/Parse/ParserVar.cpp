// ParserVar.cpp: implementation of the CParserVar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ParserVar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserVar::CParserVar(CString s)
{
   s.MakeLower();
   value = -1;
   type = VAR;/*
   if (s=="frname") value = FRNAME;
   if (s=="lname") value = LNAME;
   if (s=="age") value = AGE;
   if (s=="club") value = CLUB;
   if (s=="time") value = TIME;
   if (s=="image") value = IMAGE;
*/}


CParserVar::~CParserVar()
{

}

bool CParserVar::isLegal()
{
   return (value >= 0);
}
void CParserVar::addArgs(CParserObject* p)
{
	args.push_back(p);
}
