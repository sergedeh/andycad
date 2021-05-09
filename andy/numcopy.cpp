// NumCopy.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "NumCopy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumCopy dialog


CNumCopy::CNumCopy(CWnd* pParent /*=NULL*/)
	: CDialog(CNumCopy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNumCopy)
	m_offset = 0.0f;
	//}}AFX_DATA_INIT
}


void CNumCopy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumCopy)
	DDX_Text(pDX, IDC_EDIT1, m_offset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNumCopy, CDialog)
	//{{AFX_MSG_MAP(CNumCopy)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumCopy message handlers
