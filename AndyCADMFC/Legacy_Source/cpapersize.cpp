// CPaperSize.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "CPaperSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCPaperSize dialog


CCPaperSize::CCPaperSize(CWnd* pParent /*=NULL*/)
	: CDialog(CCPaperSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCPaperSize)
	m_wunit = _T("");
	m_ewu = 1.0f;
	m_epu = 1.0f;
	//}}AFX_DATA_INIT
}


void CCPaperSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCPaperSize)
	DDX_Control(pDX, IDC_RADIOMETRIC, m_cmet);
	DDX_Control(pDX, IDC_RADIOIMPERIAL, m_cimp);
	DDX_Text(pDX, IDC_STATICUNITY, m_wunit);
	DDX_Text(pDX, IDC_EDITWU, m_ewu);
	DDX_Text(pDX, IDC_EDITPU, m_epu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCPaperSize, CDialog)
	//{{AFX_MSG_MAP(CCPaperSize)
	ON_BN_CLICKED(IDC_RADIOMETRIC, OnRadiometric)
	ON_BN_CLICKED(IDC_RADIOIMPERIAL, OnRadioimperial)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_LENGTH_TYPE2,OnLTDrop)
	ON_CBN_SELCHANGE(IDC_LENGTH_TYPE3,OnLTDrop2)
	ON_CBN_SELCHANGE(IDC_LENGTH_TYPE_ANGLE,OnLTDropAngle)
	ON_CBN_SELCHANGE(IDC_LENGTH_TYPE6,OnLTDropAngle6)
	ON_CBN_SELCHANGE(IDC_LENGTH_TYPE4,OnLTDrop3)
	ON_BN_CLICKED(IDC_CHECK1, OnFitToPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCPaperSize message handlers


int CCPaperSize::getUnit() 
{
	return unit==metric;
}

void CCPaperSize::setdata(int f, float fw,float fp,int lprec,int aprec)
{
	m_ewu = fw;
	m_epu = fp;
	if(f)
		unit=metric;	
	else
		unit=inch;

}

void CCPaperSize::setdata2(int l_type, int l_stype,int prec)
{
	length_type=l_type;
	length_subtype=l_stype;
	length_prec=prec;
}
void CCPaperSize::setdata3(int a_type, int aprec)
{
	angle_type=a_type;
	angle_prec=aprec;
}

void CCPaperSize::setdata4(bool a_fit)
{
	fit=a_fit;
}


BOOL CCPaperSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmet.SetCheck(unit==metric);
	m_cimp.SetCheck(unit==inch);
	CButton* comb0=(CButton*)GetDlgItem(IDC_CHECK1);
	comb0->SetCheck(fit);
	CEdit* comb00=(CEdit*)GetDlgItem(IDC_EDITWU);
	CEdit* comb20=(CEdit*)GetDlgItem(IDC_EDITPU);
	if(fit)
	{
		comb00->EnableWindow(FALSE);
		comb20->EnableWindow(FALSE);
	}else
	{
		comb00->EnableWindow(TRUE);
		comb20->EnableWindow(TRUE);
	}

/*	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE2);
	comb->SetCurSel(0);
	CComboBox* comb2=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE3);
	comb2->SetCurSel(0);
	comb2->EnableWindow(TRUE);
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE4);
	comb3->ResetContent();
	comb3->AddString(_T("1\""));
	comb3->AddString(_T("0.1\""));
	comb3->AddString(_T("0.01\""));
	comb3->SetCurSel(0);
	length_type=comb->GetCurSel()+1;
	length_subtype=comb2->GetCurSel()+1;
	length_prec=comb3->GetCurSel()+1;
*/
	int stype=length_subtype;
	int prec=length_prec;
	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE2);
	comb->SetCurSel(length_type-1);
	OnLTDrop();
	CComboBox* comb2=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE3);
	comb2->SetCurSel(stype-1);
	OnLTDrop2();
	comb2->EnableWindow(TRUE);
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE4);
	comb3->SetCurSel(prec-1);
	OnLTDrop3();

/*	comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE_ANGLE);
	comb->SetCurSel(0);
	comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE6);
	comb3->ResetContent();
	comb3->AddString(_T("1 r"));
	comb3->AddString(_T("0.1 r"));
	comb3->AddString(_T("0.01 r"));
	comb3->AddString(_T("0.001 r"));
	comb3->AddString(_T("0.0001 r"));
	comb3->SetCurSel(0);
	comb3->EnableWindow(TRUE);
	angle_type=comb->GetCurSel()+1;
	angle_prec=comb3->GetCurSel()+1;
*/
	int atype=angle_type;
	int aprec=angle_prec;
	comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE_ANGLE);
	comb->SetCurSel(atype-1);
	OnLTDropAngle();
	comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE6);
	comb3->SetCurSel(aprec-1);
	OnLTDropAngle6();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CCPaperSize::OnFitToPage() 
{
	// TODO: Add your control notification handler code here

	CButton* comb0=(CButton*)GetDlgItem(IDC_CHECK1);
	fit=comb0->GetCheck();
	CEdit* comb=(CEdit*)GetDlgItem(IDC_EDITWU);
	CEdit* comb2=(CEdit*)GetDlgItem(IDC_EDITPU);
	if(fit)
	{
		comb->EnableWindow(FALSE);
		comb2->EnableWindow(FALSE);
	}else
	{
		comb->EnableWindow(TRUE);
		comb2->EnableWindow(TRUE);
	}

}

void CCPaperSize::OnLTDrop3() 
{
	// TODO: Add your control notification handler code here

	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE2);
	CComboBox* comb2=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE3);
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE4);
	length_type=comb->GetCurSel()+1;
	length_subtype=comb2->GetCurSel()+1;
	length_prec=comb3->GetCurSel()+1;

}

void CCPaperSize::OnLTDropAngle6() 
{
	// TODO: Add your control notification handler code here
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE6);
	angle_prec=comb3->GetCurSel()+1;
}

void CCPaperSize::OnLTDropAngle() 
{
	// TODO: Add your control notification handler code here
	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE_ANGLE);

	int i=comb->GetCurSel();
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE6);
	if(i==0)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 r"));
	comb3->AddString(_T("0.1 r"));
	comb3->AddString(_T("0.01 r"));
	comb3->AddString(_T("0.001 r"));
	comb3->AddString(_T("0.0001 r"));
	comb3->SetCurSel(0);
	}else
	if(i==1)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 d"));
	comb3->AddString(_T("0.1 d"));
	comb3->AddString(_T("0.01 d"));
	comb3->SetCurSel(0);
	}
	angle_type=i+1;
	angle_prec=comb3->GetCurSel()+1;

}

void CCPaperSize::OnLTDrop() 
{
	// TODO: Add your control notification handler code here
	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE2);

	int i=comb->GetCurSel();
	CComboBox* comb2=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE3);
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE4);
	if((i==1)||(i==3))
	{
	comb2->SetCurSel(0);
	comb2->EnableWindow(FALSE);
	comb3->ResetContent();
	comb3->AddString(_T("1\""));
	comb3->AddString(_T("1/2\""));
	comb3->AddString(_T("1/4\""));
	comb3->AddString(_T("1/8\""));
	comb3->AddString(_T("1/16\""));
	comb3->AddString(_T("1/32\""));
	comb3->AddString(_T("1/64\""));
	comb3->SetCurSel(0);
	}else
	if(i==2)
	{
	comb2->SetCurSel(1);
	comb2->EnableWindow(FALSE);
	comb3->ResetContent();
	comb3->AddString(_T("1'"));
	comb3->AddString(_T("0.1'"));
	comb3->AddString(_T("0.01'"));
	comb3->AddString(_T("0.001'"));
	comb3->SetCurSel(0);
	}else
	if(i==0)
	{
	comb2->SetCurSel(0);
	comb2->EnableWindow(TRUE);
	comb3->ResetContent();
	comb3->AddString(_T("1\""));
	comb3->AddString(_T("0.1\""));
	comb3->AddString(_T("0.01\""));
	comb3->SetCurSel(0);
	}
	length_type=comb->GetCurSel()+1;
	length_subtype=comb2->GetCurSel()+1;
	length_prec=comb3->GetCurSel()+1;
}

void CCPaperSize::OnLTDrop2() 
{
	// TODO: Add your control notification handler code here
	CComboBox* comb=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE3);
	CComboBox* comb3=(CComboBox*)GetDlgItem(IDC_LENGTH_TYPE4);

	int i=comb->GetCurSel();
	if(i==0)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1\""));
	comb3->AddString(_T("0.1\""));
	comb3->AddString(_T("0.01\""));
	comb3->SetCurSel(0);
	}else
	if(i==1)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1'"));
	comb3->AddString(_T("0.1'"));
	comb3->AddString(_T("0.01'"));
	comb3->AddString(_T("0.001'"));
	comb3->SetCurSel(0);
	}else
	if(i==2)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 mm"));
	comb3->AddString(_T("0.1 mm"));
	comb3->SetCurSel(0);
	}else
	if(i==3)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 cm"));
	comb3->AddString(_T("0.1 cm"));
	comb3->AddString(_T("0.01 cm"));
	comb3->SetCurSel(0);
	}else
	if(i==4)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 m"));
	comb3->AddString(_T("0.1 m"));
	comb3->AddString(_T("0.01 m"));
	comb3->AddString(_T("0.001 m"));
	comb3->AddString(_T("0.0001 m"));
	comb3->SetCurSel(0);
	}else
	if(i==5)
	{
	comb3->ResetContent();
	comb3->AddString(_T("1 pt"));
	comb3->AddString(_T("0.1 pt"));
	comb3->SetCurSel(0);
	}
	length_type=1;
	length_subtype=comb->GetCurSel()+1;
	length_prec=comb3->GetCurSel()+1;
}

void CCPaperSize::OnRadiometric() 
{
	// TODO: Add your control notification handler code here
	m_cmet.SetCheck(1);
	m_cimp.SetCheck(0);
	unit=metric;	
	m_wunit="mm";
	UpdateData(FALSE);
}
void CCPaperSize::OnRadioimperial() 
{
	// TODO: Add your control notification handler code here
	m_cmet.SetCheck(0);
	m_cimp.SetCheck(1);
	unit=inch;	
	m_wunit="inch";
	UpdateData(FALSE);
}
