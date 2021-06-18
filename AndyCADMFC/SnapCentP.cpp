// SnapCentP.cpp: implementation of the CSnapCentP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapCentP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapCentP::CSnapCentP()
{
	bkcolor=RGB(42,112,219);
}

CSnapCentP::~CSnapCentP()
{

}
bool CSnapCentP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"center");
}
