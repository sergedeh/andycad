// PolarTrackDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "PolarTrackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolarTrackDlg dialog


CPolarTrackDlg::CPolarTrackDlg()
	: CPropertyPage(CPolarTrackDlg::IDD)
{
	//{{AFX_DATA_INIT(CPolarTrackDlg)
	m_addangle = FALSE;
	m_polartrackon = FALSE;
	//}}AFX_DATA_INIT
}


void CPolarTrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPolarTrackDlg)
	DDX_Check(pDX, IDC_CHECKADDANGLE, m_addangle);
	DDX_Check(pDX, IDC_CHECKPOLARTRACKON, m_polartrackon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPolarTrackDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPolarTrackDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolarTrackDlg message handlers
