// InfoBar.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "InfoBar.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoBar dialog


CInfoBar::CInfoBar()
{
	//{{AFX_DATA_INIT(CInfoBar)
	m_xv = 0;
	m_yv = 0;
	m_length = 0;
	m_angle = 0;
	m_area = 0;
	m_zv = 0;
	//}}AFX_DATA_INIT
}

CInfoBar::~CInfoBar()
{
}

void CInfoBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoBar)
	DDX_Text(pDX, IDC_MOUSX, m_xv);
	DDX_Text(pDX, IDC_MOUSEY, m_yv);
	DDX_Text(pDX, IDC_OBLENGTH, m_length);
	DDX_Text(pDX, IDC_OBANGLE, m_angle);
	DDX_Text(pDX, IDC_OBAREA, m_area);
	DDX_Text(pDX, IDC_MOUSEZ, m_zv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoBar, CDialogBar)
	//{{AFX_MSG_MAP(CInfoBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoBar message handlers
int CInfoBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
void CInfoBar::setInterest(CSubject *sub)
{
	sub->RegisterInterest(this);
}

void CInfoBar::SendNotify(CString s, void *param[])
{
	if(s=="mouse")
	{
		CVector point=*(CVector*)param[0];
		m_xv=point.x;
		m_yv=point.y;
		m_zv=point.z;
		UpdateData(FALSE);
	}

	if(s=="selectinfo")
	{
	    m_length=*(float*)param[0];
		m_angle=*(float*)param[1];
        m_area =*(float*)param[2];
		m_xv=*(float*)param[4];
		m_yv=*(float*)param[5];
		m_zv=*(float*)param[6];
		UpdateData(FALSE);
	}

}
