// TextDi.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "TextDi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDi dialog


CTextDi::CTextDi(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextDi)
	m_text = _T("");
	//}}AFX_DATA_INIT
	pnew=false;
}


void CTextDi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDi)
	DDX_Text(pDX, IDC_EDIT1, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextDi, CDialog)
	//{{AFX_MSG_MAP(CTextDi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDi message handlers

void CTextDi::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CDialog::OnOK();
}

void CTextDi::settext(CString s)
{
	pnew=true;
	m_text=s;
}

BOOL CTextDi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization her
	if(pnew)
		UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
