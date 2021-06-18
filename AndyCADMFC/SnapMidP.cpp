// SnapMidP.cpp: implementation of the CSnapMidP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "draw.h"
#include "SnapMidP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapMidP::CSnapMidP()
{
	bkcolor=RGB(42,112,219);
}

CSnapMidP::~CSnapMidP()
{

}
bool CSnapMidP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"mid");
}
