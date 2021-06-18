// SnapIntP.cpp: implementation of the CSnapIntP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapIntP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapIntP::CSnapIntP()
{
	bkcolor=RGB(42,112,219);
}

CSnapIntP::~CSnapIntP()
{

}
bool CSnapIntP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"inter");
}
