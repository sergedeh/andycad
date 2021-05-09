// RecColor.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "RecColor.h"
#include "ColorD.h"
#include "cadDoc.h"
#include "cadview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COLORREF CRecColor::ccolor=0,CRecColor::bcolor=0;

/////////////////////////////////////////////////////////////////////////////
// CRecColor

CRecColor::CRecColor()
{
	change=true;
}

CRecColor::~CRecColor()
{
}


BEGIN_MESSAGE_MAP(CRecColor, CButton)
	//{{AFX_MSG_MAP(CRecColor)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecColor message handlers

void CRecColor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	    
	CBrush br;
/*	CPalette* pOldPalette = dc.SelectPalette (&((CColorD*)GetParent())->palette, FALSE);
	dc.SelectObject(&br);
	dc.RealizePalette();
*/	
	br.CreateSolidBrush(color);

	CRect v;
	GetClientRect(&v);
	dc.FillRect(v,&br);	
//	dc.SelectPalette (pOldPalette, FALSE);

	// Do not call CButton::OnPaint() for painting messages
}



int CRecColor::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

//	palette=pal;
/*	struct {
    LOGPALETTE lp;
    PALETTEENTRY ape[256];
	} pal;

	LOGPALETTE* pLP = (LOGPALETTE*) &pal;
	pLP->palVersion = 0x300;
	pLP->palNumEntries = 255;

	for (int i=0; i<255; i++) {
    pLP->palPalEntry[i].peRed =i*i;
    pLP->palPalEntry[i].peGreen =155-3*i;
    pLP->palPalEntry[i].peBlue =55-i;
    pLP->palPalEntry[i].peFlags = 0;
	}

	palette.CreatePalette (pLP);*/

	
	// TODO: Add your specialized creation code here
	
	return 0;
}






void CRecColor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(change)
	ccolor=color;
	change=true;
	CFrameWnd *pFrame = 
             (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->OnChangeColor(ccolor,bcolor); 	

//	(GetParent()->GetParent()->GetActiveView();

	CPaintDC dc(this); // device context for painting
	CBrush br;
/*	CPalette* pOldPalette = dc.SelectPalette (&((CColorD*)GetParent())->palette, FALSE);
	dc.SelectObject(&br);
	dc.RealizePalette();
*/	


	CRect v;
	GetClientRect(&v);
//	v.InflateRect(-20,-20,-20,-20);
//	Invalidate();
	br.CreateSolidBrush(PALETTERGB(155,155,155));
	dc.FillRect(v,&br);	
	v.InflateRect(-2,-2,-2,-2);
	br.Detach();
	br.CreateSolidBrush(color);
	
	dc.FillRect(v,&br);	

//	(GetParent()->GetParent())
//	::getsetcolor(bcolor,ccolor);

//	CButton::OnLButtonDown(nFlags, point);
}

void CRecColor::OnRButtonDown(UINT nFlags, CPoint point) 
{
	bcolor=color;
	change=false;
	CButton::OnRButtonDown(nFlags, point);

	SendMessage(BM_CLICK);
}
