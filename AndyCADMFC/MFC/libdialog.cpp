// Libdialog.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "Libdialog.h"
#include "cadview.h"
#include "caddoc.h"
#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibdialog dialog


CLibdialog::CLibdialog()
{
	drag=false;
	m_libtree=NULL;
	//{{AFX_DATA_INIT(CLibdialog)
	//}}AFX_DATA_INIT
}
CLibdialog::~CLibdialog()
{
}

BEGIN_MESSAGE_MAP(CLibdialog, CDialogBar)
	//{{AFX_MSG_MAP(CLibdialog)
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibdialog message handlers

void CLibdialog::OnMouseMove(UINT nFlags, CPoint point) 
{

	if(drag)
	{
 		CFrameWnd *pFrame = 
 				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

 		// Get the active view attached to the active MDI child
 		// window.
 		CCadView *pView = (CCadView *) pFrame->GetActiveView();
		CPoint lk=point;
		MapWindowPoints(pView,&lk,1);
		LPARAM kl;
		kl=lk.y;
		kl=kl<<16;
		kl|=lk.x;
 		
 	}
	CDialogBar::OnMouseMove(nFlags, point);
}

BOOL CLibdialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(wParam==WM_LAYADD)
	{
		CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
		CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
		CCadView *cv=(CCadView*) mg->GetActiveView();

		cd->m_objects->addobject(*(CTreeCtrl*)GetDlgItem(IDC_LIBT1),cv->getHdc());//*m_libtree);
	}
	if(wParam==WM_LAYREMOVE)
	{
	  CMainFrame* mg=(CMainFrame*)::AfxGetMainWnd();
	  CCadDoc *cd=(CCadDoc*)mg->GetActiveDocument();
	  CCadView *cv=(CCadView*) mg->GetActiveView();
	  
      cd->m_objects->removeobject(*(CTreeCtrl*)GetDlgItem(IDC_LIBT1),cv->getHdc());//*m_libtree);
	}
	return CDialogBar::OnCommand(wParam, lParam);
}




//DEL void CLibdialog::OnBegindragTree1(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
//DEL 	// TODO: Add your control notification handler code here
//DEL  		HTREEITEM it=m_libtree.GetSelectedItem();
//DEL 			if(!m_libtree.ItemHasChildren(it))
//DEL  			{
//DEL 				HTREEITEM pit=m_libtree.GetParentItem(it);
//DEL  				
//DEL  				CFrameWnd *pFrame = 
//DEL  						 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
//DEL  
//DEL  				// Get the active view attached to the active MDI child
//DEL  				// window.
//DEL  				CCadView *pView = (CCadView *) pFrame->GetActiveView();
//DEL  			
//DEL 				CRect rc;
//DEL 				m_libtree.GetItemRect(it,rc,0);
//DEL 				CPoint pl=rc.CenterPoint();
//DEL 				m_libtree.MapWindowPoints(pView,&pl,1);
//DEL  				pView->draglib(m_libtree.GetItemText(pit),m_libtree.GetItemText(it),pl);
//DEL 
//DEL //				pView->SetCapture();
//DEL 				drag=true;
//DEL  			}
//DEL 	
//DEL 	*pResult = 0;
//DEL }



int CLibdialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	libimtool.Create(IDR_LAYTOO,16,2,RGB(192,192,192));

	GetClientRect(&wnd);
//	wnd.DeflateRect(CSize(10,10));

	CRect hrec=wnd;
	hrec.DeflateRect(CSize(10,100));
	hrec.bottom=hrec.top+30;

	hto.Create(WS_CHILD|WS_VISIBLE|TBSTYLE_FLAT,hrec,this,ID_LAYHD);
	hto.SetImageList(&libimtool);
	TBBUTTON bt1,bt2,bt3;
	bt1.iBitmap=0;
	bt1.idCommand=WM_LAYADD;
	bt1.fsState=TBSTATE_ENABLED;
	bt1.fsStyle=TBSTYLE_BUTTON;
	bt1.iString=NULL;
//	hto.InsertButton(0,&bt1);


	wnd.DeflateRect(CSize(10,30));
	wnd.right-=1;
	hrec=wnd;
	hrec.bottom=hrec.top+18;

/*	hlist.Create(HDS_HORZ|WS_VISIBLE|HDS_HIDDEN|
		HDS_BUTTONS|WS_BORDER|WS_CHILD,hrec,this,ID_LAYHD);
*/	HDITEM hd;
	hd.mask=HDI_FORMAT|HDI_TEXT|HDI_WIDTH;
	hd.fmt=HDF_LEFT|HDF_STRING;
	hd.pszText="Library";
	hd.cxy=hrec.Size().cx;
	hd.cchTextMax=lstrlen(hd.pszText);
//	hlist.InsertItem(0,&hd);

	wnd.top=hrec.bottom+1;

	INITCOMMONCONTROLSEX g;
	g.dwICC=ICC_TREEVIEW_CLASSES;
	g.dwSize=sizeof(g);

	libimlist.Create(IDR_LIBIM,16,2,RGB(192,192,192));
/*	m_libtree->Create(TVS_HASLINES|LVS_ICON|\
		TVS_HASBUTTONS|TVS_EDITLABELS|TVS_SHOWSELALWAYS\
		|TVS_LINESATROOT|WS_VISIBLE|WS_BORDER|WS_CHILD\
		,wnd,this,IDC_LIBT1);
/*	HWND hwndTV = CreateWindowEx(0, WC_TREEVIEW, "Tree View", 
        WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 
        wnd.left, wnd.top, wnd.Width(), wnd.Height(), 
        GetSafeHwnd( ), (HMENU)IDC_LIBT1, AfxGetInstanceHandle(), NULL);
	m_libtree.Attach(hwndTV);
*/
	m_libtree = (CTreeCtrl*)GetDlgItem(IDC_LIBT1);

//	m_libtree->SetImageList(&libimlist,TVSIL_NORMAL);

/*	m_libtreel.Create(LVS_REPORT|LVS_ALIGNLEFT|LVS_EDITLABELS|
		LVS_SHOWSELALWAYS|LVS_SINGLESEL
		|WS_VISIBLE|WS_BORDER,wnd,this,ID_LAYT);
	m_libtreel.SetImageList(&libimlist,LVSIL_SMALL);
*/
	// TODO: Add your specialized creation code here
	
	return 0;
}
