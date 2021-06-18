// LineBar.cpp: implementation of the CLineBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "LineBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineBar::CLineBar()
{

}

CLineBar::~CLineBar()
{

}
BOOL CLineBar::AddComboBoxline()
{
	CRect rect;
	GetItemRect(0, rect);
	rect.bottom=rect.top+150;
	if	(!m_combox.Create(	WS_CHILD | CBS_DROPDOWN | CBS_AUTOHSCROLL |
		WS_VSCROLL | CBS_HASSTRINGS, rect,	this, ID_BL))
	return FALSE;  	
	else 
	
	{	m_combox.AddString("Solid");
		m_combox.AddString("Dot");
		m_combox.AddString("Double dot");
		
		return TRUE;
	}
	
}

BOOL CLineBar::ShowComboBoxline()
{
	CRect rect;
	SetButtonInfo(0, ID_BL, TBBS_SEPARATOR,150);
	if(m_combox.m_hWnd != NULL)
	{
		m_combox.ShowWindow(SW_SHOW);
	}
		return FALSE;
}
BOOL CLineBar::HideComboBoxline()
{
	SetButtonInfo(0, ID_BL, TBBS_BUTTON, 0);
	if(m_combox.m_hWnd != NULL)m_combox.ShowWindow(SW_HIDE);
	return TRUE;
}


CSize CLineBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	if(dwMode & LM_HORZDOCK)ShowComboBoxline();
	else HideComboBoxline();
	return CToolBar::CalcDynamicLayout(nLength, dwMode);
}
