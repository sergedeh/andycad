// Text1.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "Text1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CText

IMPLEMENT_DYNCREATE(CText, CEditView)

CText::CText()
{
}

CText::~CText()
{
}


BEGIN_MESSAGE_MAP(CText, CEditView)
	//{{AFX_MSG_MAP(CText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CText drawing

void CText::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CText diagnostics

#ifdef _DEBUG
void CText::AssertValid() const
{
	CEditView::AssertValid();
}

void CText::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CText message handlers




