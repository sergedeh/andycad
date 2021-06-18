// PropPage.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPage

IMPLEMENT_DYNAMIC(CPropPage, CPropertySheet)

CPropPage::CPropPage(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CPropPage::CPropPage(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
//	AddPage(&arc);
	AddPage(&Line);
	AddPage(&Circle);
	AddPage(&spline);
//	AddPage(&Object);
}

CPropPage::~CPropPage()
{
}


BEGIN_MESSAGE_MAP(CPropPage, CPropertySheet)
	//{{AFX_MSG_MAP(CPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPage message handlers





BOOL CPropPage::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
int ids [] = {IDOK, IDCANCEL};//, ID_APPLY_NOW, IDHELP };
    
    // Hide Apply and Help buttons
    CWnd *pWnd = GetDlgItem (ID_APPLY_NOW);
    pWnd->ShowWindow (FALSE);
    pWnd = GetDlgItem (IDHELP);
    pWnd->ShowWindow (FALSE);
    
  
    CRect rectWnd;
    CRect rectBtn;
    
    GetWindowRect (rectWnd);
    GetDlgItem (IDCANCEL)->GetWindowRect (rectBtn);
    
    int btnWidth = rectBtn.Width();
    int btnHeight = rectBtn.Height();
    int btnOffset = rectWnd.bottom - rectBtn.bottom;
    int btnLeft = rectWnd.right - rectWnd.left;

    rectWnd.right = rectBtn.right+btnOffset;
    MoveWindow(rectWnd);

	
	return bResult;
}
