// Verb.cpp: implementation of the CVerb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Verb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVerb::CVerb(CString s): CParserVerb (s)
{

}

CVerb::~CVerb()
{

}


void CVerb::Execute()
{

}

void CVerb::setData(CFigure* df)
{
     figure=df;
}
