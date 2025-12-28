// MultVar.cpp: implementation of the CMultVar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "MultVar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMultVar::CMultVar(CParserObject *v1, CParserObject *v2)
{
   multVec.push_back(v1);
   multVec.push_back(v2);
   type = MULTVAR;

}

CMultVar::~CMultVar()
{

}

CMultVar::CMultVar()
{
   type = MULTVAR;

}


void CMultVar::add(CParserObject* v1)
{
	multVec.push_back(v1);
}

vector<CParserObject*> CMultVar::getVector()
{
	return multVec;
}
