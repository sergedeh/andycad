// mytestDoc.cpp : implementation of the CMytestDoc class
//

#include "stdafx.h"
#include "mytest.h"

#include "mytestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMytestDoc

IMPLEMENT_DYNCREATE(CMytestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMytestDoc, CDocument)
	//{{AFX_MSG_MAP(CMytestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMytestDoc construction/destruction

CMytestDoc::CMytestDoc()
{
	// TODO: add one-time construction code here

}

CMytestDoc::~CMytestDoc()
{
}

BOOL CMytestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMytestDoc serialization

void CMytestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMytestDoc diagnostics

#ifdef _DEBUG
void CMytestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMytestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMytestDoc commands
