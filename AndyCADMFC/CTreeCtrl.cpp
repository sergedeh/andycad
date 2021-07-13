// CTreeCtrl.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "CTreeCtrl.h"
#include "cadview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTreeCtrl

CCTreeCtrl::CCTreeCtrl()
{
	drag=false;
}

CCTreeCtrl::~CCTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CCTreeCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CCTreeCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTreeCtrl message handlers

int CCTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect wnd;
	GetClientRect(&wnd);
	wnd.top+=17;
//	wnd.DeflateRect(CSize(0,0));

/*	CRect hrec=wnd;
	hrec.bottom=hrec.top+17;

	hlist.Create(HDS_HORZ|CCS_TOP|WS_VISIBLE|\
		HDS_BUTTONS,hrec,this,ID_LAYHD);
	HDITEM hd;
	hd.mask=HDI_FORMAT|HDI_TEXT;
	hd.fmt=HDF_STRING;
	hd.pszText="Library";
	hd.cchTextMax = lstrlen(hd.pszText); 
	hlist.InsertItem(1,&hd);
*/
	libimlist.Create(IDR_LIBIM,16,2,RGB(192,192,192));

/*	m_libtree.Create(TVS_HASLINES|LVS_ICON|\
		TVS_HASBUTTONS|TVS_EDITLABELS|TVS_SHOWSELALWAYS\
		|TVS_LINESATROOT|WS_CHILD|WS_VISIBLE\
		,wnd,this,IDC_LIBT1);
//	m_libtree.ModifyStyle(TVS_DISABLEDRAGDROP,0);
*/
	m_libtree.SetImageList(&libimlist,TVSIL_NORMAL);
	
	
	return 0;
}

BOOL CCTreeCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if(wParam==IDC_LIBT1)
	{
	//	GetParent()->SendMessage(WM_NOTIFY,wParam,lParam);
		LPNMHDR lpnmh = (LPNMHDR) lParam;
		if(lpnmh->code==TVN_BEGINDRAG)
		{
			
 		HTREEITEM it=m_libtree.GetSelectedItem();
			if(!m_libtree.ItemHasChildren(it))
 			{
				HTREEITEM pit=m_libtree.GetParentItem(it);
 				
 				CFrameWnd *pFrame = 
 						 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
 
 				// Get the active view attached to the active MDI child
 				// window.
 				CCadView *pView = (CCadView *) pFrame->GetActiveView();
 			
				CRect rc;
				m_libtree.GetItemRect(it,rc,0);
				CPoint pl=rc.CenterPoint();
				m_libtree.MapWindowPoints(pView,&pl,1);
 				pView->draglib(m_libtree.GetItemText(pit),m_libtree.GetItemText(it),pl);

//				pView->SetCapture();
				drag=true;
 			}
		}
	}
	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void CCTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
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
	
	CListCtrl::OnMouseMove(nFlags, point);
}
