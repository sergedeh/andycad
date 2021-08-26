// SubWnd.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "SubWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubWnd

CSubWnd::CSubWnd()
{
}

CSubWnd::~CSubWnd()
 {
 }


BEGIN_MESSAGE_MAP(CSubWnd, CWnd)
	//{{AFX_MSG_MAP(CSubWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSubWnd message handlers

int CSubWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


//	m_drawwnd.Create(AfxRegisterWndClass(0,NULL,(HBRUSH)WHITE_BRUSH,NULL),"drawwnd",
//		WS_CHILD|WS_VISIBLE, wndrec,this,NULL);
	

	return 0;
}

void CSubWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rlrec;
	GetClientRect(rlrec);
	ratio[0]=(float)rlrec.bottom/(float)initrec.bottom;
	ratio[1]=(float)rlrec.right/(float)initrec.right;


	LPARAM pam=cy,pam1=m_wndRect.bottom;
	pam<<=16;pam1<<=16;
	pam+=cx;pam1+=m_wndRect.right;
//	m_drawwnd.PostMessage(WM_SIZE,nType,pam);
//	m_hruler.PostMessage(WM_SIZE,nType,pam);
//	m_vruler.PostMessage(WM_SIZE,nType,pam);
	  //
		// Set the horizontal scrolling parameters.
    //
	
	int m_nHScrollMax=initrec.right*1.5;
	m_nHPageSize=initrec.right;
    m_nHScrollPos=min (m_nHScrollPos, m_nViewWidth -
            m_nHPageSize - 1);

    SCROLLINFO si;
    si.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    si.nMin = 0;
    si.nMax = m_nHScrollMax;
    si.nPos = m_nHScrollPos;
    si.nPage = m_nHPageSize;

    SetScrollInfo (SB_HORZ, &si, TRUE);

    //
    // Set the vertical scrolling parameters.
    //
    
    int m_nVScrollMax=initrec.bottom*1.5;
	m_nVPageSize=initrec.bottom;
    m_nVScrollPos=min (m_nVScrollPos, m_nViewHeight -
            m_nVPageSize - 1);


	si.fMask = SIF_PAGE|SIF_POS|SIF_RANGE;
    si.nMin = 0;
    si.nMax = m_nVScrollMax;
    si.nPos = m_nVScrollPos;
    si.nPage =m_nVPageSize;

    SetScrollInfo (SB_VERT, &si, TRUE);

    	
}


BOOL CSubWnd::OnEraseBkgnd(CDC* pDC) 
{
	/*
	CBrush br,*bold;
	//pDC->Detach();
	//pDC->SetWindowOrg (m_nHScrollPos, m_nVScrollPos);


	br.CreateSolidBrush(RGB(255,255,255));
	bold=pDC->SelectObject(&br);
	
	CRect wndrec;
	GetClientRect(wndrec);
	pDC->FillRect(wndrec,&br);
	CPen pat;
	pat.CreatePen(PS_DOT,0.5,RGB(0,0,0));
	pDC->SelectObject(&pat);
	int i=0;
	
	int step=20*ratio[1];
	for(i=0;i<wndrec.bottom;i+=(i+20)*1.5)
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(wndrec.right,i);
	}
	for(i=0;i<wndrec.right;i=(i+20)*1.5)
	{
		pDC->MoveTo(i,0);
		pDC->LineTo(i,wndrec.bottom);
	}

	pDC->SelectObject(bold);
	//pDC->SetBkColor(RGB(1,0,0));	
	// Do not call CWnd::OnPaint() for painting messages*/


	return true;//CWnd::OnEraseBkgnd(pDC);
}

void CSubWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  int nDelta;

    switch (nSBCode) {

    case SB_LINELEFT:
        nDelta = -10;
        break;

    case SB_PAGELEFT:
        nDelta = -m_nHPageSize;
        break;

    case SB_THUMBTRACK:
        nDelta = (int) nPos - m_nHScrollPos;
        break;

    case SB_PAGERIGHT:
        nDelta = m_nHPageSize;
        break;

    case SB_LINERIGHT:
        nDelta = 10;
        break;
    default: // Ignore other scroll bar messages
        return;
    }

    int nScrollPos = m_nHScrollPos + nDelta;
    int nMaxPos = initrec.Width() - m_nHPageSize;

    if (nScrollPos < 0)
        nDelta = -m_nHScrollPos;
    else if (nScrollPos > nMaxPos)
        nDelta = nMaxPos - m_nHScrollPos;

    if (nDelta != 0) {
        m_nHScrollPos += nDelta;
        SetScrollPos (SB_HORZ, m_nHScrollPos, TRUE);
        ScrollWindow (-nDelta, 0);
    }
	
//	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSubWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  int nDelta;

    switch (nSBCode) {

    case SB_LINEUP:
        nDelta = -10;
        break;

    case SB_PAGEUP:
        nDelta = -m_nVPageSize;
        break;

    case SB_THUMBTRACK:
        nDelta = (int) nPos - m_nVScrollPos;
        break;

    case SB_PAGEDOWN:
        nDelta = m_nVPageSize;
        break;

    case SB_LINEDOWN:
        nDelta = 10;
        break;

    default: // Ignore other scroll bar messages
        return;
    }

    int nScrollPos = m_nVScrollPos + nDelta;
    int nMaxPos = initrec.Height() - m_nVPageSize;

    if (nScrollPos < 0)
        nDelta = -m_nVScrollPos;
    else if (nScrollPos > nMaxPos)
        nDelta = nMaxPos - m_nVScrollPos;

    if (nDelta != 0) {
        m_nVScrollPos += nDelta;
        SetScrollPos (SB_VERT, m_nVScrollPos, TRUE);
        ScrollWindow (0, -nDelta);
    }
	
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CSubWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC *pDC=GetDC();
	
	CBrush br,*bold;
	//pDC->Detach();
	dc.SetWindowOrg(m_nHScrollPos, m_nVScrollPos);
  

	 //// draw a grid lines
	CPen pen (PS_SOLID, 0, RGB (192, 192, 192));
    CPen* pOldPen = dc.SelectObject (&pen);

	br.CreateSolidBrush(RGB(255,255,255));
	bold=pDC->SelectObject(&br);
	
	CRect wndrec;
	GetClientRect(wndrec);
	pDC->FillRect(wndrec,&br);
	CPen pat;
	pat.CreatePen(PS_DOT,0.5,RGB(0,0,0));
	pDC->SelectObject(&pat);
	int i=0;
	
	int step=20*ratio[1];
	for(i=0;i<wndrec.bottom;i+=(i+20)*1.5)
	{
		pDC->MoveTo(0,i);
		pDC->LineTo(wndrec.right,i);
	}
	for(i=0;i<wndrec.right;i=(i+20)*1.5)
	{
		pDC->MoveTo(i,0);
		pDC->LineTo(i,wndrec.bottom);

	}
	// Do not call CWnd::OnPaint() for painting messages

}
