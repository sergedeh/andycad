// Ruler1.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "Ruler1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuler

CRuler::CRuler()
{
	
}

CRuler::~CRuler()
{
}


BEGIN_MESSAGE_MAP(CRuler, CControlBar)
	//{{AFX_MSG_MAP(CRuler)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRuler message handlers

void CRuler::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	

//	if (rec.bottom<0) rec.bottom=-rec.bottom;
//	rec.bottom*=10;

	CFont theFont;
	theFont.CreateFont(14,10,0,0,1500,FALSE,FALSE,FALSE,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS | CLIP_LH_ANGLES,
		DEFAULT_QUALITY,DEFAULT_PITCH | FF_MODERN,"Courier New");

	// Select the objects to draw with
	
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_CENTER | TA_BASELINE | TA_NOUPDATECP);
	dc.SetTextColor(RGB(0,18,164));
	dc.SetROP2(R2_COPYPEN);
	
	CFont *oldFont =   (CFont *) (dc.SelectObject(&theFont));
	CPen *oldPen =     (CPen *)  (dc.SelectStockObject(BLACK_PEN));
	CBrush *oldBrush = (CBrush *)(dc.SelectStockObject(LTGRAY_BRUSH));
	
	int olddc=dc.SetMapMode(MM_LOENGLISH);

	CRect rec=rlrec;

//	GetClientRect(rec);
	dc.DPtoLP(rec);

	dc.Rectangle(rec);
	int step=50;
	
	if (horiz)
	{
	int Origin=rec.left;
	//bigstep=step;
	dc.SetROP2(R2_NOTXORPEN);
	int i=0;
	CString pl;
	
	//CPoint oldPosition(Origin,rec.Width());
	for ( int x=Origin;x<rec.right;x+=2*step)
	{
		pl.Format("%d",i);
		dc.MoveTo(x ,rec.bottom);
		dc.LineTo(x,rec.top);
		
		dc.MoveTo(x+step,rec.bottom);
		dc.LineTo(x+step,rec.bottom+10);
	//	pl=i;
		dc.TextOut(x,rec.bottom+10,pl);
	
		i=i+1;
	}
	}
	else
	{
	int Origin=rec.top;
	dc.SetROP2(R2_NOTXORPEN);
	int i=0;
	CString pl;
	for (int x=Origin;x>rec.bottom;x-=2*step)
	{
		pl.Format("%d",i);
		dc.MoveTo(rec.right,x);
		dc.LineTo(rec.left,x);
		
		dc.MoveTo(rec.right,x+step);
		dc.LineTo(rec.right-15,x+step);
	//	pl=i;
		dc.TextOut(rec.right-20,x,pl);
		i=i+1;
	}
	}
	// Unselect the objects in use before deleting them
	dc.SelectObject(oldFont);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

	dc.SetMapMode(olddc);
	// Do not call CWnd::OnPaint() for painting messages
}


CRect CRuler::Create(bool orient, CWnd *Parent)
{

	
	
	pParent=Parent;
	//CSize rlrec;//=((CScrollView*)pParent)->GetTotalSize();
	CRect rec;
	pParent->GetClientRect(rec)	;
	//rec.SetRectEmpty();
	//rec.bottom=rlrec.cy;
	//rec.right=rlrec.cx;
	
	
	
	horiz=orient;
//	initrec=rlrec;
	if (horiz)
	{
	rec.bottom=rec.top+25;
	}
	else
	{
		rec.right=rec.left+25;
	}
	
	if (CWnd::Create(AfxRegisterWndClass(0,NULL,(HBRUSH)WHITE_BRUSH,NULL),"drawwnd",
		WS_CHILD|WM_PARENTNOTIFY, rec,pParent,NULL))
	{
		return rec;
	}

}

void CRuler::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
//	CSize rlrec=((CScrollView*)pParent)->GetTotalSize();
	GetParent()->GetClientRect(rlrec);
	CRect rec;rec.SetRectEmpty();
//	rec.bottom=rlrec.cy;
//	rec.right=rlrec.cx;
	

	if (horiz)
	{
	rec.bottom=rec.top+25;
	}
	else
	{
		rec.right=rec.left+25;
	}
	MoveWindow(rec,true);

}

void CRuler::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{
}

