// RecPattern.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "RecPattern.h"
#include "ColorD.h"
#include "cadDoc.h"
#include "cadview.h"
#include "imagex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//CBitmap CRecPattern::pat1, CRecPattern::pat2;

BEGIN_MESSAGE_MAP(CRecPattern, CButton)
	//{{AFX_MSG_MAP(CRecPattern)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecPattern

CRecPattern::CRecPattern()
{
 change=true;
}


CRecPattern::~CRecPattern()
{
}



/////////////////////////////////////////////////////////////////////////////
// CRecPattern message handlers

int CRecPattern::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	GetClientRect(&v);

/*	CPaintDC dc(this); // device context for painting

	CDC *hdc=GetDC();	
	CDC* phdc=new CDC;
	phdc->CreateCompatibleDC(hdc);
	pattern.CreateCompatibleBitmap(hdc,25,25);
	CBitmap* o=phdc->SelectObject(&pattern);

	CImagex texture(hdc->GetSafeHdc(),patsource.GetBuffer(10));

	int s1=StretchDIBits(phdc->GetSafeHdc(),0,0,25,25,0,0,texture.GetWidth(),texture.GetHeight(),\
		texture.GetDIBits(),texture.GetBitmapInfo(),DIB_RGB_COLORS,SRCCOPY);
	phdc->SelectObject(o);
	delete phdc;
	ReleaseDC(hdc);
*/	
	return 0;
}

void CRecPattern::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(change)
	//ccolor=color;
	change=true;
	CFrameWnd *pFrame = 
             (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->OnChangeTexture(patsource); 	

//	(GetParent()->GetParent()->GetActiveView();

	CPaintDC dc(this); // device context for painting


	CRect v;
	GetClientRect(&v);
	v.InflateRect(-1,-1,-1,-1);
	CBrush br(pattern);
	dc.FillRect(v,&br);	


//	CButton::OnLButtonDown(nFlags, point);
}

 void CRecPattern::OnPaint() 
 {
	CPaintDC dc(this); // device context for painting
 	CBrush br(pattern);
	CBrush br1(RGB(255,255,255));
 
 	CRect v;
 	GetClientRect(&v);
//	dc.FillRect(v,&br1);
 	dc.FillRect(v,&br);	
 
 	// Do not call CButton::OnPaint() for painting messages
 }



void CRecPattern::setBitmap(CBitmap* s,CString sg)
{
 pattern=s;
 patsource=sg;
}

