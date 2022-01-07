// CustomWidth.cpp : implementation file
//

#include "pch.h"
#include "AndyCADMFC.h"
#include "CustomWidth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomWidth dialog


CCustomWidth::CCustomWidth(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomWidth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomWidth)
	m_cwidth = 0.0;
	//}}AFX_DATA_INIT
}


void CCustomWidth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomWidth)
	DDX_Text(pDX, IDC_EDIT1, m_cwidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomWidth, CDialog)
	//{{AFX_MSG_MAP(CCustomWidth)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomWidth message handlers
