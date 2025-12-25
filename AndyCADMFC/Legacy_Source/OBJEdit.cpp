// OBJEdit.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "OBJEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COBJEdit dialog


COBJEdit::COBJEdit(CWnd* pParent /*=NULL*/)
	: CDialog(COBJEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(COBJEdit)
	m_auth = _T("");
	m_descr = _T("");
	m_name = _T("");
	m_cost = 0.0;
	//}}AFX_DATA_INIT
}


void COBJEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COBJEdit)
	DDX_Text(pDX, IDC_OBJEDITAUTH, m_auth);
	DDX_Text(pDX, IDC_OBJEDITDESC, m_descr);
	DDX_Text(pDX, IDC_OBJEDITNAME, m_name);
	DDX_Text(pDX, IDC_OBJEDITCOST, m_cost);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COBJEdit, CDialog)
	//{{AFX_MSG_MAP(COBJEdit)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBJEdit message handlers

void COBJEdit::setobj(FINFO oh)
{
	m_auth=oh.author;
	m_cost=oh.cost;
	m_descr=oh.description;
	m_name=oh.name;
}
