// Text.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "Text.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Text

IMPLEMENT_DYNCREATE(Text, CEditView)

Text::Text()
{
}

Text::~Text()
{
}


BEGIN_MESSAGE_MAP(Text, CEditView)
	//{{AFX_MSG_MAP(Text)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Text drawing

void Text::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// Text diagnostics

#ifdef _DEBUG
void Text::AssertValid() const
{
	CEditView::AssertValid();
}

void Text::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Text message handlers
/////////////////////////////////////////////////////////////////////////////
