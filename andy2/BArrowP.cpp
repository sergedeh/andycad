// BArrowP.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "BArrowP.h"
#include "pattern.h"
//#include "RecPattern.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBArrowP

CBArrowP::CBArrowP()
{
	st=false;
	TM1=1;
}

CBArrowP::~CBArrowP()
{
}


BEGIN_MESSAGE_MAP(CBArrowP, CButton)
	//{{AFX_MSG_MAP(CBArrowP)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBArrowP message handlers

void CBArrowP::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MSG msg;

	CButton::OnLButtonDown(nFlags, point);
	st=true;

	SetTimer(TM1,100,(TIMERPROC)NULL);

   
 	CPattern* pC=(CPattern*) CPattern::getCPatternD();
	// TODO: Add your message handler code here and/or call default
	if(left)
	{
	pC->OnLButtonarr1();//PostMessage(WM_LBUTTONDOWN,0,0);
	}
	else
	{
	pC->OnLButtonarr2();//PostMessage(WM_LBUTTONDOWN,0,0);
	}

	CButton::OnLButtonDown(nFlags, point);
}

void CBArrowP::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
		if(st)
	{ 
 		CPattern* pC=(CPattern*) CPattern::getCPatternD();
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

void CBArrowP::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		st=false;
	KillTimer(TM1);
	CButton::OnLButtonUp(nFlags, point);
}

void CBArrowP::setorient(bool b)
{
 left=b;
}
