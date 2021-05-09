// StringP.cpp: implementation of the CStringP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "StringP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringP::CStringP()
{

}

CStringP::~CStringP()
{

}

void CStringP::getValue(CStringP *p)
{
	p->s=s;
}

void CStringP::setValue(CStringP *v)
{
	s=v->s;
}
