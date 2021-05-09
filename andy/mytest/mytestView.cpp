// mytestView.cpp : implementation of the CMytestView class
//

#include "stdafx.h"
#include "mytest.h"

#include "mytestDoc.h"
#include "mytestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMytestView

IMPLEMENT_DYNCREATE(CMytestView, CView)

BEGIN_MESSAGE_MAP(CMytestView, CView)
	//{{AFX_MSG_MAP(CMytestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMytestView construction/destruction

CMytestView::CMytestView()
{
	// TODO: add construction code here

}

CMytestView::~CMytestView()
{
}

BOOL CMytestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMytestView drawing

void CMytestView::OnDraw(CDC* pDC)
{
	CMytestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMytestView printing

BOOL CMytestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMytestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMytestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMytestView diagnostics

#ifdef _DEBUG
void CMytestView::AssertValid() const
{
	CView::AssertValid();
}

void CMytestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMytestDoc* CMytestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMytestDoc)));
	return (CMytestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMytestView message handlers
