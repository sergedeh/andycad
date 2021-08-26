// SnapEndP.cpp: implementation of the CSnapEndP class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapEndP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapEndP::CSnapEndP()
{
	bkcolor=RGB(255,128,0);
}

CSnapEndP::~CSnapEndP()
{

}
bool CSnapEndP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"end");
}
