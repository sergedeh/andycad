// IntP.cpp: implementation of the CIntP class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "IntP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntP::CIntP()
{

}

CIntP::~CIntP()
{

}
void CIntP::getValue(CIntP *p)
{
	p->s=s;
}

void CIntP::setValue(CIntP *v)
{
	s=v->s;
}

CIntP::CIntP(CString n, int p)
		:CProperty(n)
{
	s=p;
}

int CIntP::getValue()
{
	return s;
}
