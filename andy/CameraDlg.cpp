// CameraDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "CameraDlg.h"
#include "cadview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraDlg dialog


CCameraDlg::CCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraDlg::IDD, pParent)
{
	pv=false;
	//{{AFX_DATA_INIT(CCameraDlg)
	m_xp = 0.0f;
	m_xt = 0.0f;
	m_yp = 0.0f;
	m_yt = 0.0f;
	m_zp = 0.0f;
	m_zt = 0.0f;
	m_fp = 0.0f;
	m_np = 0.0f;
	m_sfov = _T("");
	m_fov = 0;
	//}}AFX_DATA_INIT
}


void CCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraDlg)
	DDX_Control(pDX, IDC_SLIDERFOV, m_cfov);
	DDX_Text(pDX, IDC_EDITXP, m_xp);
	DDX_Text(pDX, IDC_EDITXT, m_xt);
	DDX_Text(pDX, IDC_EDITYP, m_yp);
	DDX_Text(pDX, IDC_EDITYT, m_yt);
	DDX_Text(pDX, IDC_EDITZP, m_zp);
	DDX_Text(pDX, IDC_EDITZT, m_zt);
	DDX_Text(pDX, IDC_EDITFPLANE, m_fp);
	DDX_Text(pDX, IDC_EDITNPLANE, m_np);
	DDX_Text(pDX, IDC_STATICFOV, m_sfov);
	DDX_Slider(pDX, IDC_SLIDERFOV, m_fov);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CCameraDlg)
	ON_EN_CHANGE(IDC_EDITXP, OnChangeEditxp)
	ON_EN_CHANGE(IDC_EDITYP, OnChangeEdityp)
	ON_EN_CHANGE(IDC_EDITZP, OnChangeEditzp)
	ON_EN_CHANGE(IDC_EDITXT, OnChangeEditxt)
	ON_EN_CHANGE(IDC_EDITYT, OnChangeEdityt)
	ON_EN_CHANGE(IDC_EDITZT, OnChangeEditzt)
	ON_EN_CHANGE(IDC_EDITFPLANE, OnChangeEditfplane)
	ON_EN_CHANGE(IDC_EDITNPLANE, OnChangeEditnplane)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraDlg message handlers

void CCameraDlg::updatepara()
{
	m_cfov.SetRange(1,180,TRUE);
	UpdateData(FALSE);
}

void CCameraDlg::OnChangeEditxp() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::OnChangeEdityp() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::OnChangeEditzp() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::OnChangeEditxt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::OnChangeEdityt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::OnChangeEditzt() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	sendNotify();		
}

void CCameraDlg::updateviewpara()
{
	pv=!pv;
	UpdateData(FALSE);
	if(!pv)
	{
		sendNotify();	
	}

}

void CCameraDlg::OnChangeEditfplane() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	sendNotify();		
}

void CCameraDlg::OnChangeEditnplane() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	sendNotify();	
}

void CCameraDlg::sendNotify()
{
	UpdateData(TRUE);

	void* param[4];

	float pos[3];
	pos[0]=m_xp;
	pos[1]=m_yp;
	pos[2]=m_zp;

	float target[3];
	target[0]=m_xt;
	target[1]=m_yt;
	target[2]=m_zt;

	float plane[2];
	plane[0]=m_fp;
	plane[1]=m_np;

	float fov[1];
	fov[0]=m_fov;

	param[0]=pos;
	param[1]=target;
	param[2]=plane;
	param[3]=fov;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Camera",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();

}

void CCameraDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	m_sfov.Format("%d",m_fov);
	UpdateData(FALSE);
	sendNotify();	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

int CCameraDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}



void CCameraDlg::SendNotify(CString s, void *param[])
{
	if(s=="Camera")
	{
		float *spec=(float*)param[0];
		float xp,yp,zp;
		m_xp=*spec;spec++;
		m_yp=*spec;spec++;
		m_zp=*spec;spec++;
		
		float xt,yt,zt;
		spec=(float*)param[1];
		m_xt=*spec;spec++;
		m_yt=*spec;spec++;
		m_zt=*spec;spec++;

		spec=(float*)param[2];
		m_fp=*spec;spec++;
		m_np=*spec;

		float *ispec=(float*)param[3];
		m_fov=*ispec;
		m_sfov.Format("%d",m_fov);
	
		UpdateData(FALSE);

	}

}

BOOL CCameraDlg::PreTranslateMessage(MSG* pMsg)
{
	
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

BOOL CCameraDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		 m_tooltip.AddTool(GetDlgItem(IDC_SLIDERFOV), "Use the slider to increase or decrease your Field Of View");
		 m_tooltip.AddTool(GetDlgItem(IDC_STATICAM), "Using the mouse click your specified Camera position \nand Click again to specify you Target Position\n(What you which to Look At)");
		 m_tooltip.AddTool(GetDlgItem(IDC_STATICCS), "Specify your Camera Setting,\n by Specifying you Far and Near Plane");
	}
	return TRUE;	// CG: This was added by the ToolTips component.
}
