// Layerad.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "Layerad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerad dialog


CLayerad::CLayerad(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLayerad)
	m_layadd = _T("");
	//}}AFX_DATA_INIT
}


void CLayerad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayerad)
	DDX_Text(pDX, IDC_EDITLAYADD, m_layadd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerad, CDialog)
	//{{AFX_MSG_MAP(CLayerad)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerad message handlers
