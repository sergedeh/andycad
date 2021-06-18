// LayerD.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "LayerD.h"
#include "Mainfrm.h"
#include "caddoc.h"
#include "cadview.h"
#include "layerad.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerD dialog


CLayerD::CLayerD()
{
	//{{AFX_DATA_INIT(CLayerD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLayerD::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayerD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerD, CDialogBar)
	//{{AFX_MSG_MAP(CLayerD)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerD message handlers

int CLayerD::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	libimlist.Create(IDR_LAYDI,16,2,RGB(192,192,192));
	libimtool.Create(IDR_LAYTOO,16,2,RGB(192,192,192));
	
	GetClientRect(&wnd);
	CRect hrec=wnd;
	hrec.DeflateRect(CSize(10,100));
	hrec.OffsetRect(CSize(50,50));
	hrec.bottom=hrec.top+10;

	hto.Create(WS_CHILD|WS_VISIBLE|TBSTYLE_FLAT,hrec,this,ID_LAYHD);
	hto.SetImageList(&libimtool);
	TBBUTTON bt1,bt2,bt3,bt4,bt5,bt6;
	bt1.iBitmap=0;
	bt1.idCommand=WM_LAYADD;
	bt1.fsState=TBSTATE_ENABLED;
	bt1.fsStyle=TBSTYLE_BUTTON;
	bt1.iString=NULL;
	hto.InsertButton(0,&bt1);

	bt2.iBitmap=1;
	bt2.idCommand=WM_LAYCURRENT;
	bt2.fsState=TBSTATE_ENABLED;
	bt2.fsStyle=TBSTYLE_BUTTON;
	bt2.iString=NULL;
	hto.InsertButton(1,&bt2);

	bt3.iBitmap=2;
	bt3.idCommand=WM_LAYERLOCK;
	bt3.fsState=TBSTATE_ENABLED;
	bt3.fsStyle=TBSTYLE_BUTTON;
	bt3.iString=NULL;
	hto.InsertButton(2,&bt3);

	bt4.iBitmap=3;
	bt4.idCommand=WM_LAYREMOVE;
	bt4.fsState=TBSTATE_ENABLED;
	bt4.fsStyle=TBSTYLE_BUTTON;
	bt4.iString=NULL;
	hto.InsertButton(3,&bt4);

	bt5.iBitmap=4;
	bt5.idCommand=WM_LAYUP;
	bt5.fsState=TBSTATE_ENABLED;
	bt5.fsStyle=TBSTYLE_BUTTON;
	bt5.iString=NULL;
	hto.InsertButton(4,&bt5);

	bt6.iBitmap=5;
	bt6.idCommand=WM_LAYDOWN;
	bt6.fsState=TBSTATE_ENABLED;
	bt6.fsStyle=TBSTYLE_BUTTON;
	bt6.iString=NULL;
	hto.InsertButton(5,&bt6);


	wnd.DeflateRect(CSize(10,30));
	wnd.right-=1;

	m_liblist.Create(LVS_REPORT|LVS_ALIGNLEFT|LVS_EDITLABELS|\
		LVS_SHOWSELALWAYS|LVS_SINGLESEL\
		|WS_VISIBLE|WS_BORDER,wnd,this,ID_LAYT);
	m_liblist.SetImageList(&libimlist,LVSIL_SMALL);

	LV_COLUMN col;
	col.mask=LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;  
	col.fmt=LVCFMT_LEFT;
	col.pszText="Layer";
	col.iSubItem=0;
	col.iImage=0;
	col.iOrder=0;
	col.cx=wnd.Size().cx;
	m_liblist.InsertColumn(0,&col);

	return 0;
}
void CLayerD::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
}
void CLayerD::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CLayerD::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(wParam==WM_LAYADD)
	{
		CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
		
		CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
		CLayerad ld;
		if((ld.DoModal()==IDOK)&&(ld.m_layadd !=""))
		{
			cd->m_objects->addlayer(m_liblist,ld.m_layadd);
		}
			else
		{
				AfxMessageBox("Enter Layer Label",MB_OK,MB_ICONINFORMATION );
		
			
		}
	}
	if(wParam==WM_LAYREMOVE)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();

	  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
		if (pos == NULL)
			::AfxMessageBox("No Layer selected",MB_ICONINFORMATION );
		else
		{
			  int nItem = m_liblist.GetNextSelectedItem(pos);
			  LVITEM rl;m_liblist.GetItem(&rl);

              cd->m_objects->removelayer(m_liblist.GetItemText(nItem,0));
			  m_liblist.DeleteItem(nItem);	
			  cv->update();
		}

	}
	if(wParam==WM_LAYUP)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();

	  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
		if (pos == NULL)
			::AfxMessageBox("No Layer selected",MB_ICONINFORMATION );
		else
		{
			  int nItem = m_liblist.GetNextSelectedItem(pos);
			  if(nItem>0){
			  LVITEM rl,rl2;
			  rl.iItem=nItem;
			  rl.mask=LVIF_IMAGE;
			  rl.iSubItem=0;
			  BOOL a1=m_liblist.GetItem(&rl);
			  CString xrl=m_liblist.GetItemText(nItem,0);
			  rl2.iItem=nItem-1;
			  rl2.mask=LVIF_IMAGE;
			  rl2.iSubItem=0;
			  a1=m_liblist.GetItem(&rl2);
			  CString xrl2=m_liblist.GetItemText(nItem-1,0);
			  CPoint p;
			  m_liblist.GetItemPosition(nItem-1,&p);
			  rl.iItem=nItem-1;
			  a1=m_liblist.SetItem(&rl);
			  m_liblist.SetItemText(nItem-1,0,xrl);
			  rl2.iItem=nItem;
			  a1=m_liblist.SetItem(&rl2);
			  m_liblist.SetItemText(nItem,0,xrl2);

              cd->m_objects->uplayer(m_liblist.GetItemText(nItem,0));
			  m_liblist.SendMessage(WM_KEYDOWN,0x00000026,0x01480001);
			  m_liblist.SendMessage(WM_KEYUP,0x00000026,0xC1480001);
		//	  m_liblist.RedrawItems(0,nItem);
			  cv->update();
			  }
		}

	}
	if(wParam==WM_LAYDOWN)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();

	  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
		if (pos == NULL)
			::AfxMessageBox("No Layer selected",MB_ICONINFORMATION );
		else
		{
			  int nItem = m_liblist.GetNextSelectedItem(pos);
			  if(nItem<m_liblist.GetItemCount()-1){
			  LVITEM rl,rl2;
			  rl.iItem=nItem;
			  rl.mask=LVIF_IMAGE;
			  rl.iSubItem=0;
			  BOOL a1=m_liblist.GetItem(&rl);
			  CString xrl=m_liblist.GetItemText(nItem,0);
			  rl2.iItem=nItem+1;
			  rl2.mask=LVIF_IMAGE;
			  rl2.iSubItem=0;
			  a1=m_liblist.GetItem(&rl2);
			  CString xrl2=m_liblist.GetItemText(nItem+1,0);
			  CPoint p;
			  m_liblist.GetItemPosition(nItem+1,&p);
			  rl.iItem=nItem-1;
			  a1=m_liblist.SetItem(&rl);
			  m_liblist.SetItemText(nItem+1,0,xrl);
			  rl2.iItem=nItem;
			  a1=m_liblist.SetItem(&rl2);
			  m_liblist.SetItemText(nItem,0,xrl2);

              cd->m_objects->downlayer(m_liblist.GetItemText(nItem,0));
			  m_liblist.SendMessage(WM_KEYDOWN,0x00000028,0x01500001);
			  m_liblist.SendMessage(WM_KEYUP,0x00000028,0xC1500001);
		//	  m_liblist.RedrawItems(0,nItem);
			  cv->update();
			  }
		}

	}
	if(wParam==WM_LAYCURRENT)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();

	  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
		if (pos == NULL)
			::AfxMessageBox("No Layer selected",MB_ICONINFORMATION);
		else
		{
			  int nItem = m_liblist.GetNextSelectedItem(pos);
              cd->m_objects->setcurlayer(m_liblist,m_liblist.GetItemText(nItem,0));
			  cv->update();
		}

	}
		if(wParam==WM_LAYERLOCK)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();

	  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
		if (pos == NULL)
			::AfxMessageBox("No Layer selected",MB_ICONINFORMATION);
		else
		{

		 int nItem = m_liblist.GetNextSelectedItem(pos);
			  CString s=m_liblist.GetItemText(nItem,0);

              cd->m_objects->lockcurlayer(m_liblist,s);
			  cv->change=true;
			  cv->Invalidate(TRUE);
			  cv->update();}

	}



	return CDialogBar::OnCommand(wParam, lParam);
}



BOOL CLayerD::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	if(wParam==ID_LAYT)
	{
		LPNMHDR lpnmh = (LPNMHDR) lParam; 
		if(lpnmh->code==NM_DBLCLK)
		{
		  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
		  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
		  CCadView *cv=(CCadView*) mg->GetActiveView();
		  POSITION pos = m_liblist.GetFirstSelectedItemPosition();
			if (pos == NULL)
				::AfxMessageBox("No Layer selected");
			else
			{
				while(pos)
				{
				  int nItem = m_liblist.GetNextSelectedItem(pos);
				  LVITEM rl;
				  rl.mask=LVIF_IMAGE;
				  rl.iItem=nItem;
				  rl.iSubItem=0;
				  m_liblist.GetItem(&rl);
				  if(rl.iImage!=2)
				  {
				  rl.iImage=(rl.iImage==1)?0:1;
				  cd->m_objects->setclayer(m_liblist.GetItemText(nItem,0),rl.iImage);
				  m_liblist.SetItem(&rl);
				  cv->update();
				  }
				}
			}
			}
	}
	return CDialogBar::OnNotify(wParam, lParam, pResult);
}

