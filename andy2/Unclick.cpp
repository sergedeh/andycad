// Unclick.cpp: implementation of the CUnclick class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Unclick.h"
#include "click.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnclick::CUnclick(CFigure *fig)
{
	figure=fig;
}

CUnclick::~CUnclick()
{

}

void CUnclick::processpoint(CVector point)
{

	if(figure->PtinRegion(point))
	{
//		figure->setclickstate(new CClick(figure));
	}
}
