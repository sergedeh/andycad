// EditParse.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "EditParse.h"
#include "parsedlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditParse

CEditParse::CEditParse()
{
}

CEditParse::~CEditParse()
{
}


BEGIN_MESSAGE_MAP(CEditParse, CEdit)
	//{{AFX_MSG_MAP(CEditParse)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditParse message handlers

void CEditParse::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if((nChar==(UINT)(VK_BACK))||(nChar==(UINT)(VK_RETURN)))
	{
		CParseDlg* wnd=(CParseDlg*)CWnd::GetOwner();
		if(wnd->OnFromEditChar(nChar))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}else
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


void CEditParse::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CEdit::CalcWindowRect(lpClientRect, nAdjustType);
}

/*int CEditParse::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetWindowText(_T("Command: "));
	return 0;
}*/



void CEditParse::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if((nChar!=(UINT)(VK_BACK))&&(nChar!=(UINT)(VK_RETURN)))
	{
	CParseDlg* wnd=(CParseDlg*)CWnd::GetOwner();
	if(wnd->OnFromEditChar(nChar))
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

}







void CEditParse::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CParseDlg* wnd=(CParseDlg*)CWnd::GetOwner();
	if(wnd->OnFromEditLButton(point))
		CEdit::OnLButtonDown(nFlags, point);
}
