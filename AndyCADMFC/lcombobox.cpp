// LComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "LComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLComboBox

CLComboBox::CLComboBox()
{
}

CLComboBox::~CLComboBox()
{
}


BEGIN_MESSAGE_MAP(CLComboBox, CComboBoxEx)
	//{{AFX_MSG_MAP(CLComboBox)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLComboBox message handlers




int CLComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBoxEx::OnCreate(lpCreateStruct) == -1)
		return -1;
                                                                                                                  	
	char *text="Bonjour";
	ps.iItem=0;
	ps.pszText=text;
	ps.mask=CBEIF_TEXT;
	ps.iImage=0;
	ps.iSelectedImage=0;
	
	return 0;
}



BOOL CLComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID ) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	bool r=CComboBoxEx::Create(dwStyle,rect,pParentWnd,nID);
	InsertItem(&ps);
	return r;
}

void CLComboBox::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CComboBoxEx::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
