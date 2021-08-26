// SnapNearP.cpp: implementation of the CSnapNearP class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapNearP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapNearP::CSnapNearP()
{
	bkcolor=RGB(255,0,0);
}

CSnapNearP::~CSnapNearP()
{

}
bool CSnapNearP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"near");
}
