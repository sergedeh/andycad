// andycadView.cpp : implementation of the CAndycadView class
//

#include "stdafx.h"
#include "andycad.h"

#include "andycadDoc.h"
#include "CntrItem.h"
#include "andycadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAndycadView

IMPLEMENT_DYNCREATE(CAndycadView, CView)

BEGIN_MESSAGE_MAP(CAndycadView, CView)
	//{{AFX_MSG_MAP(CAndycadView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAndycadView construction/destruction

CAndycadView::CAndycadView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CAndycadView::~CAndycadView()
{
}

BOOL CAndycadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAndycadView drawing

void CAndycadView::OnDraw(CDC* pDC)
{
	CAndycadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CAndycadView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	//Active documents should always be activated
	COleDocument* pDoc = (COleDocument*) GetDocument();
	if (pDoc != NULL)
	{
		// activate the first one
		POSITION posItem = pDoc->GetStartPosition();
		if (posItem != NULL)
		{
			CDocItem* pItem = pDoc->GetNextItem(posItem);

			// only if it's an Active document
			COleDocObjectItem *pDocObjectItem =
				DYNAMIC_DOWNCAST(COleDocObjectItem, pItem);

			if (pDocObjectItem != NULL)
			{
				pDocObjectItem->DoVerb(OLEIVERB_SHOW, this);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAndycadView printing

BOOL CAndycadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!CView::DoPreparePrinting(pInfo))
		return FALSE;
	
	if (!COleDocObjectItem::OnPreparePrinting(this, pInfo))
		return FALSE;

	return TRUE;
}

void CAndycadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAndycadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAndycadView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add customized printing code here
	if(pInfo->m_bDocObject)
		COleDocObjectItem::OnPrint(this, pInfo, TRUE);
	else
		CView::OnPrint(pDC, pInfo);
}

void CAndycadView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CAndycadView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CAndycadCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CAndycadView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CAndycadCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal(COleInsertDialog::DocObjectsOnly) != IDOK)
		return;

	BeginWaitCursor();

	CAndycadCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CAndycadDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CAndycadCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
		pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CAndycadView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CAndycadView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CAndycadView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAndycadView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAndycadView diagnostics

#ifdef _DEBUG
void CAndycadView::AssertValid() const
{
	CView::AssertValid();
}

void CAndycadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAndycadDoc* CAndycadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAndycadDoc)));
	return (CAndycadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAndycadView message handlers
