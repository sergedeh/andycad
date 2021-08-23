// PopBar.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "PopBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopBar

CPopBar::CPopBar()
{
}

CPopBar::~CPopBar()
{
}


BEGIN_MESSAGE_MAP(CPopBar, CToolBar)
	//{{AFX_MSG_MAP(CPopBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopBar message handlers

void CPopBar::create()
{
/*	CreateEx(this, TBSTYLE_FLAT|TBSTYLE_LIST|TBN_DROPDOWN, WS_CHILD | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),IDR_CER) ||
		!m_cercToolBar.LoadToolBar(IDR_CER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	CToolBarCtrl& tbctrl=GetToolBarCtrl();
	int ncount=tbctrl.GetButtonCount();
	TBBUTTON tbut;
	for(int i=0;i<=ncount-1;i++)
	{
		tbctrl.GetButton(i,&tbut);
		tbut.iBitmap=I_IMAGENONE;
		tbut.fsStyle|=BTNS_DROPDOWN;


	}*/

}
