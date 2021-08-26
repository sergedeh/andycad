// ParserObject.cpp: implementation of the CParserObject class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "ParserObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int CParserObject::VERB=1, CParserObject::VAR=2, CParserObject::MULTVAR=3,CParserObject::FLOAT=4,CParserObject::POINT=5;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserObject::CParserObject()
{

}

CParserObject::~CParserObject()
{

}
