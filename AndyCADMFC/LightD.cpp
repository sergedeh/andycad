// LightD.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "LightD.h"
#include "cadview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightD dialog


CLightD::CLightD(CWnd* pParent /*=NULL*/)
	: CDialog(CLightD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightD)
	m_y = 0.0f;
	m_x = 0.0f;
	m_z = 0.0f;
	m_ab = 0;
	m_ag = 0;
	m_ar = 0;
	m_sg = 0;
	m_sr = 0;
	m_sab = _T("");
	m_sag = _T("");
	m_sar = _T("");
	m_ssb = _T("");
	m_ssg = _T("");
	m_ssr = _T("");
	m_db = 0;
	m_dg = 0;
	m_dr = 0;
	m_sdr = _T("");
	m_sdg = _T("");
	m_sdb = _T("");
	//}}AFX_DATA_INIT
}


void CLightD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightD)
	DDX_Control(pDX, IDC_STATIC_AMBIENTLIGHT2, m_dl);
	DDX_Control(pDX, IDC_SLIDER_AR2, m_drslider);
	DDX_Control(pDX, IDC_SLIDER_AG2, m_dgslider);
	DDX_Control(pDX, IDC_SLIDER_AB2, m_dbslider);
	DDX_Control(pDX, IDC_SLIDER_SR, m_srslider);
	DDX_Control(pDX, IDC_SLIDER_SG, m_sgslider);
	DDX_Control(pDX, IDC_SLIDER_AR, m_arslider);
	DDX_Control(pDX, IDC_SLIDER_AG, m_agslider);
	DDX_Control(pDX, IDC_SLIDER_AB, m_abslider);
	DDX_Control(pDX, IDC_STATIC_SPECLIGHT, m_sl);
	DDX_Control(pDX, IDC_STATIC_AMBIENTLIGHT, m_al);
	DDX_Text(pDX, IDC_EDIT_LY, m_y);
	DDX_Text(pDX, IDC_EDIT_LX, m_x);
	DDX_Text(pDX, IDC_EDIT_LZ, m_z);
	DDX_Slider(pDX, IDC_SLIDER_AB, m_ab);
	DDX_Slider(pDX, IDC_SLIDER_AG, m_ag);
	DDX_Slider(pDX, IDC_SLIDER_AR, m_ar);
	DDX_Slider(pDX, IDC_SLIDER_SG, m_sg);
	DDX_Slider(pDX, IDC_SLIDER_SR, m_sr);
	DDX_Text(pDX, IDC_STATIC_AB, m_sab);
	DDX_Text(pDX, IDC_STATIC_AG, m_sag);
	DDX_Text(pDX, IDC_STATIC_AR, m_sar);
	DDX_Text(pDX, IDC_STATIC_SG, m_ssg);
	DDX_Text(pDX, IDC_STATIC_SR, m_ssr);
	DDX_Slider(pDX, IDC_SLIDER_AB2, m_db);
	DDX_Slider(pDX, IDC_SLIDER_AG2, m_dg);
	DDX_Slider(pDX, IDC_SLIDER_AR2, m_dr);
	DDX_Text(pDX, IDC_STATIC_AR2, m_sdr);
	DDX_Text(pDX, IDC_STATIC_AG2, m_sdg);
	DDX_Text(pDX, IDC_STATIC_AB2, m_sdb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightD, CDialog)
	//{{AFX_MSG_MAP(CLightD)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_LX, OnChangeEditLx)
	ON_EN_CHANGE(IDC_EDIT_LY, OnChangeEditLy)
	ON_EN_CHANGE(IDC_EDIT_LZ, OnChangeEditLz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightD message handlers

void CLightD::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
//	GetDlgItem(
	UpdateData(TRUE);
	m_ssr.Format("%f",(float)m_sr/255);
	m_ssg.Format("%f",(float)m_sg/255);

	CDC* hdc=m_sl.GetWindowDC();
	CRect rect;
	m_sl.GetClientRect(&rect);
	CBrush b(RGB(m_sr,m_sr,m_sr));
	CBrush* ob=hdc->SelectObject(&b);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);

	m_sar.Format("%d",m_ar);
	m_sag.Format("%d",m_ag);
	m_sab.Format("%d",m_ab);

	m_sdr.Format("%d",m_dr);
	m_sdg.Format("%d",m_dg);
	m_sdb.Format("%d",m_db);

	hdc=m_al.GetWindowDC();
	m_al.GetClientRect(&rect);
	CBrush b1(RGB(m_ar,m_ag,m_ab));
	ob=hdc->SelectObject(&b1);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);

	hdc=m_dl.GetWindowDC();
	m_dl.GetClientRect(&rect);
	CBrush b2(RGB(m_dr,m_dg,m_db));
	ob=hdc->SelectObject(&b2);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);
	
	
	UpdateData(FALSE);

	void* param[3];
	float spec[3];
	spec[0]=(m_sr>0)?(float)m_sr/255:m_sr;
	spec[1]=(m_sg>0)?(float)m_sg/255:m_sg;

	float amb[3];
	amb[0]=(m_ar>0)?(float)m_ar/255:m_ar;
	amb[1]=(m_ag>0)?(float)m_ag/255:m_ag;
	amb[2]=(m_ab>0)?(float)m_ab/255:m_ab;

	float diff[3];
	diff[0]=(m_dr>0)?(float)m_dr/255:m_dr;
	diff[1]=(m_dg>0)?(float)m_dg/255:m_dg;
	diff[2]=(m_db>0)?(float)m_db/255:m_db;

	float pos[3];
	pos[0]=m_x;
	pos[1]=m_y;
	pos[2]=m_z;

	param[0]=spec;
	param[1]=amb;
	param[2]=diff;
	param[3]=pos;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Light",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CLightD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int min,max;
	m_arslider.SetRange(0,255,TRUE);
	m_agslider.SetRange(0,255,TRUE);
	m_abslider.SetRange(0,255,TRUE);
	m_drslider.SetRange(0,255,TRUE);
	m_dgslider.SetRange(0,255,TRUE);
	m_dbslider.SetRange(0,255,TRUE);
	m_srslider.SetRange(0,255,TRUE);
	m_sgslider.SetRange(0,255,TRUE);
/*	m_sar="0";
	m_sag="0";
	m_sab="0";

	m_ssr="0";
	m_ssg="0";
	m_ssb="0";
*/
	
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		 //m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		 m_tooltip.AddTool(GetDlgItem(IDC_SLIDER_SR), "Slider through the Bar to increase and decrease the Specular Light intensity");
		 m_tooltip.AddTool(GetDlgItem(IDC_SLIDER_SG), "Slider through the Bar to increase and decrease the Specular Light Glossiness/Shiningness");
		 /*m_tooltip.AddTool(GetDlgItem(IDC_SLIDER_SR), "<text>");
		 m_tooltip.AddTool(GetDlgItem(IDC_SLIDER_SR), "<text>");
		 m_tooltip.AddTool(GetDlgItem(IDC_SLIDER_SR), "<text>");*/
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLightD::updatepara()
{
	m_ssr.Format("%f",(float)m_sr/255);
	m_ssg.Format("%f",(float)m_sg/255);


	m_sar.Format("%d",m_ar);
	m_sag.Format("%d",m_ag);
	m_sab.Format("%d",m_ab);

	m_sdr.Format("%d",m_dr);
	m_sdg.Format("%d",m_dg);
	m_sdb.Format("%d",m_db);
	UpdateData(FALSE);

}

void CLightD::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC* hdc=m_sl.GetWindowDC();
	CRect rect;
	m_sl.GetClientRect(&rect);
	CBrush b(RGB(m_sr,m_sr,m_sr));
	CBrush* ob=hdc->SelectObject(&b);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);
	
	hdc=m_al.GetWindowDC();
	m_al.GetClientRect(&rect);
	CBrush b1(RGB(m_ar,m_ag,m_ab));
	ob=hdc->SelectObject(&b1);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);

	hdc=m_dl.GetWindowDC();
	m_dl.GetClientRect(&rect);
	CBrush b2(RGB(m_dr,m_dg,m_db));
	ob=hdc->SelectObject(&b2);
	hdc->Rectangle(&rect);
	hdc->SelectObject(ob);
	ReleaseDC(hdc);

	UpdateData(FALSE);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CLightD::OnChangeEditLx() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData(TRUE);

	void* param[3];
	float spec[3];
	spec[0]=(m_sr>0)?(float)m_sr/255:m_sr;
	spec[1]=(m_sg>0)?(float)m_sg/255:m_sg;

	float amb[3];
	amb[0]=(m_ar>0)?(float)m_ar/255:m_ar;
	amb[1]=(m_ag>0)?(float)m_ag/255:m_ag;
	amb[2]=(m_ab>0)?(float)m_ab/255:m_ab;

	float diff[3];
	diff[0]=(m_dr>0)?(float)m_dr/255:m_dr;
	diff[1]=(m_dg>0)?(float)m_dg/255:m_dg;
	diff[2]=(m_db>0)?(float)m_db/255:m_db;

	float pos[3];
	pos[0]=m_x;
	pos[1]=m_y;
	pos[2]=m_z;

	param[0]=spec;
	param[1]=amb;
	param[2]=diff;
	param[3]=pos;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Light",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();
	// TODO: Add your control notification handler code here
	
}

void CLightD::OnChangeEditLy() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);

	void* param[3];
	float spec[3];
	spec[0]=(m_sr>0)?(float)m_sr/255:m_sr;
	spec[1]=(m_sg>0)?(float)m_sg/255:m_sg;

	float amb[3];
	amb[0]=(m_ar>0)?(float)m_ar/255:m_ar;
	amb[1]=(m_ag>0)?(float)m_ag/255:m_ag;
	amb[2]=(m_ab>0)?(float)m_ab/255:m_ab;

	float diff[3];
	diff[0]=(m_dr>0)?(float)m_dr/255:m_dr;
	diff[1]=(m_dg>0)?(float)m_dg/255:m_dg;
	diff[2]=(m_db>0)?(float)m_db/255:m_db;

	float pos[3];
	pos[0]=m_x;
	pos[1]=m_y;
	pos[2]=m_z;

	param[0]=spec;
	param[1]=amb;
	param[2]=diff;
	param[3]=pos;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Light",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();
	
	// TODO: Add your control notification handler code here
	
}

void CLightD::OnChangeEditLz() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);

	void* param[3];
	float spec[3];
	spec[0]=(m_sr>0)?(float)m_sr/255:m_sr;
	spec[1]=(m_sg>0)?(float)m_sg/255:m_sg;

	float amb[3];
	amb[0]=(m_ar>0)?(float)m_ar/255:m_ar;
	amb[1]=(m_ag>0)?(float)m_ag/255:m_ag;
	amb[2]=(m_ab>0)?(float)m_ab/255:m_ab;

	float diff[3];
	diff[0]=(m_dr>0)?(float)m_dr/255:m_dr;
	diff[1]=(m_dg>0)?(float)m_dg/255:m_dg;
	diff[2]=(m_db>0)?(float)m_db/255:m_db;

	float pos[3];
	pos[0]=m_x;
	pos[1]=m_y;
	pos[2]=m_z;

	param[0]=spec;
	param[1]=amb;
	param[2]=diff;
	param[3]=pos;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
		(*it)->SendNotify("Light",param);
	}
	CCadView* v=(CCadView*)view;
	v->change=true;
	v->Invalidate();
	
	// TODO: Add your control notification handler code here
	
}

BOOL CLightD::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}
