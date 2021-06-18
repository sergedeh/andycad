// BArrowC.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "BArrowC.h"
#include "ColorD.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBArrowC

CBArrowC::CBArrowC()
{
	st=false;
	TM1=1;
}

CBArrowC::~CBArrowC()
{
}


BEGIN_MESSAGE_MAP(CBArrowC, CButton)
	//{{AFX_MSG_MAP(CBArrowC)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBArrowC message handlers



void CBArrowC::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MSG msg;

	CButton::OnLButtonDown(nFlags, point);
	st=true;

	SetTimer(TM1,100,(TIMERPROC)NULL);

   
 	CColorD* pC=(CColorD*) CColorD::getCColorD();
	// TODO: Add your message handler code here and/or call default
	if(left)
	{
	pC->OnLButtonarr1();//PostMessage(WM_LBUTTONDOWN,0,0);
	}
	else
	{
	pC->OnLButtonarr2();//PostMessage(WM_LBUTTONDOWN,0,0);
	}
	
}

void CBArrowC::setorient(bool b)
{
	left=b;
}

void CBArrowC::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(st)
	{ 
 		CColorD* pC=(CColorD*) CColorD::getCColorD();
		// TODO: Add your message handler code here and/or call default
		if(left)
		{
	//	SetState(1);
		pC->OnLButtonarr1();//PostMessage(WM_LBUTTONDOWN,0,0);
		}
		else
		{
		pC->OnLButtonarr2();//PostMessage(WM_LBUTTONDOWN,0,0);
	//	GetParent()->PostMessage(WM_LBUTTONDOWN,0,0);
		}
	}

	CButton::OnTimer(nIDEvent);
}

void CBArrowC::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	st=false;
	KillTimer(TM1);
	CButton::OnLButtonUp(nFlags, point);
}
