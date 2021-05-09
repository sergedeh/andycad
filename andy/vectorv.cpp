// Vectorv.cpp: implementation of the CVectorv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Vectorv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVectorv::CVectorv()
{

}

CVectorv::~CVectorv()
{

}
CVectorv::CVectorv(const CVector begin, const CVector end)
{
	CVector::CVector(begin,end);
}

CVectorv::CVectorv(double fx,double fy)
{
	//CVector::CVector(fx,fy,false);
}

    


void CVectorv::assign(CVector vec)
{
//	CVector::assign(vec,false);
}

void CVectorv::assign(CVector begin, CVector end)
{
	CVector::assign(begin,end);

}
