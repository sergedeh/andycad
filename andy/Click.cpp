// Click.cpp: implementation of the CClick class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Click.h"
#include "mClick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClick::CClick(CFigure *fig)
{
	figure=fig;
	figure->sendclickNotify();
	  //figure->drawselect();
}

CClick::~CClick()
{

}

void CClick::processpoint(CVector point)
{
  if(!figure->PtinRegion(point))
  {
//	  figure->setclickstate(new CMClick(figure));
  }
  else
  {
	  //figure->drawselect();
  }
}
