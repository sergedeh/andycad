// MClick.cpp: implementation of the CMClick class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "MClick.h"
#include "Click.h"
#include "unClick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMClick::CMClick(CFigure* fig)
{
	figure=fig;

}

CMClick::~CMClick()
{

}

void CMClick::SendNotify(CString s, void *param[])
{
	if(s=="click")
	{
		m=true;
	}
}

void CMClick::processpoint(CVector point)
{
 if(m)
 {
//	 figure->setclickstate(new CClick(figure));
 }
 else
 {
//	 figure->setclickstate(new CUnclick(figure));
 }
 }
