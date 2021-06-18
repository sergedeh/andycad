// Vectorp.cpp: implementation of the CVectorp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Vectorp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVectorp::CVectorp()
{

}

CVectorp::~CVectorp()
{

}

CVectorp::CVectorp(const CPoint point)
{
	CVector::CVector(point);
}

CVectorp::CVectorp(double fx,double fy)
{
//	CVector::CVector(fx,fy,true);
}

void CVectorp::assign(CVectorp vec)
{
//	CVector::assign(vec,true);
}

