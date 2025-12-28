// DrawWnd.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "DrawWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawWnd

CDrawWnd::CDrawWnd()
{
}

CDrawWnd::~CDrawWnd()
{
}


BEGIN_MESSAGE_MAP(CDrawWnd, CWnd)
	//{{AFX_MSG_MAP(CDrawWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDrawWnd message handlers



void CDrawWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	CRect rlrec;
	pParent->GetClientRect(rlrec);
	ratio[0]=(float)rlrec.bottom/(float)initrec.bottom;
	ratio[1]=(float)rlrec.right/(float)initrec.right;

//	CPoint pas;
//	pas=(pParent)->GetRatio();
	
	initrec.right*=ratio[0];
	initrec.bottom*=ratio[1];
	MoveWindow(wnd_rec);
	

	// TODO: Add your message handler code here
	
}



BOOL CDrawWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	pParent=pParentWnd;
	initrec=rect;	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

//DEL BOOL CDrawWnd::OnEraseBkgnd(CDC* pDC) 
//DEL {
//DEL 	
//DEL 	CBrush br,*bold;
//DEL 	//pDC->Detach();
//DEL 	
//DEL 	br.CreateSolidBrush(RGB(255,255,255));
//DEL 	bold=pDC->SelectObject(&br);
//DEL 	
//DEL 	CRect wndrec;
//DEL 	GetClientRect(wndrec);
//DEL 	pDC->FillRect(wndrec,&br);
//DEL 	CPen pat;
//DEL 	pat.CreatePen(PS_DOT,0.5,RGB(0,0,0));
//DEL 	pDC->SelectObject(&pat);
//DEL 	int i=0;
//DEL 	for(i=0;i<wndrec.bottom;i=i+20)
//DEL 	{
//DEL 		pDC->MoveTo(0,i);
//DEL 		pDC->LineTo(wnd_rec.right,i);
//DEL 	}
//DEL 	for(i=0;i<wndrec.right;i=i+20)
//DEL 	{
//DEL 		pDC->MoveTo(i,0);
//DEL 		pDC->LineTo(i,wndrec.bottom);
//DEL 	}
//DEL 
//DEL 	pDC->SelectObject(bold);
//DEL 	//pDC->SetBkColor(RGB(1,0,0));		
//DEL 	return true;//CWnd::OnEraseBkgnd(pDC);
//DEL }
