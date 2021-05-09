

#include "stdafx.h"
#include "RegDialog.h"
#include "cad.h"

#include <afx.h>
#include <afxwin.h>
#include <afxinet.h>
#include <afx.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////      App Specific Data !!!    ///////////////////

int DaysLimit =7;
long KeyCode  =100000;
CString Version = "1.1";
//////////////////////////////////////////////////////////////////////	


CRegDialog::CRegDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDialog)
	//}}AFX_DATA_INIT
}


void CRegDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDialog)
	DDX_Control(pDX, IDCANCEL, m_on);
	DDX_Control(pDX, IDC_EDIT, m_entercode);
	DDX_Control(pDX, IDC_STATIC1, m_stat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDialog, CDialog)
	//{{AFX_MSG_MAP(CRegDialog)
	ON_BN_CLICKED(IDC_ASKCODE, OnAskcode)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDialog message handlers

BOOL CRegDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

//	CWinApp* pApp = AfxGetApp();
	CCadApp* pApp =(CCadApp*)AfxGetApp();

	int Run = pApp->GetProfileInt(Version,"Times run",0);
	Run++;
	pApp->WriteProfileInt(Version,"Times run",Run);

	CTime curTime = CTime::GetCurrentTime();
	int curYear = curTime.GetYear();
	int curMonth = curTime.GetMonth();
	int curDay = curTime.GetDay();
	int firYear =pApp->GetProfileInt(Version,"Run year",0);
	int firMonth =pApp->GetProfileInt(Version,"Run month",0);
	int firDay =pApp->GetProfileInt(Version,"Run day",0);

	int firAbs = (firYear-2000)*365+(firMonth-1)*30+(firDay);
	int curAbs = (curYear-2000)*365+(curMonth-1)*30+(curDay);
	int DaysToUse = DaysLimit-(curAbs-firAbs);
	if (DaysToUse > 0)
		{
		CString Str;
		Str.Format("You can use this product for %d  Days before the licence expires!\nTo register press Register Button and you will receive Registration Code. Type it below and press OK",DaysToUse);
		m_stat.SetWindowText(Str);

		}
	else
		{
		m_on.EnableWindow(FALSE);
		m_stat.SetWindowText("Sorry, trial period is finished!\n\nTo register press Register button and you will receive Registration Code. Type it below and press OK.");
		int DeadFlag = 17;
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
		}


		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		//m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegDialog::OnAskcode() 
{
	//AfxMessageBox("Registration! Go to internet link, send mail or WinExec(something.exe)");	

	CInternetSession ss;
	CStdioFile* web;
	CString site;
	site="https://andycad.onfastspring.com/andycad-2d/";
//	site="https://paystack.com/pay/-mdtkjibgi_test";
//	web= ss.OpenURL(site);
	ShellExecute(0,NULL,site,NULL,NULL,SW_SHOWDEFAULT);
}


void CRegDialog::OnOK() 
{
	CDialog::OnOK();
	try{
	CCadApp* pApp =(CCadApp*)AfxGetApp();
//	CWinApp* pApp = AfxGetApp();	
	CString TempStr;
	m_entercode.GetWindowText(TempStr);
//	long enteredCode = atol(TempStr);

	pApp->WriteProfileString(Version,"Code",TempStr);
	
	CInternetSession ss;
	CStdioFile* web;
	CString site;
//	site="http://www.andycad.com.ng/wp/";
//	site="http://localhost:55930/";
//	web= ss.OpenURL(site);

	CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
	// URL-encoded form variables -
	// name = "John Doe", userid = "hithere", other = "P&Q"
	CString strFormData = _T("secret_key=5cf6668e197e74.82794873&slm_action=slm_check&license_key="+TempStr);

	CInternetSession session;
	CHttpConnection *pConnection = session.GetHttpConnection(_T("andycad.com.ng"));
	CHttpFile *pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,
		_T("wp/"));
	BOOL result = pFile->SendRequest(strHeaders, (LPVOID) (LPCTSTR) strFormData,
		strFormData.GetLength());
	CString lines,status;
	pFile->ReadString(lines);
	pConnection->Close();

//	sscanf(lines,"%s:%s,",status);
//	lines.Find("\"status\":\"active\"");
//	CString status;
//	if(status==_T("active"))
//	if (KeyCode == m_entercode)
	if(lines.Find("\"status\":\"pending\"")!=-1)
	{

		if(IDOK)
		{
					//this is not working	
				strFormData = _T("secret_key=5cf6668e197e74.82794873&slm_action=slm_activate&license_key="+TempStr);
				CInternetSession session;
				CHttpConnection* pConnection = session.GetHttpConnection(_T("andycad.com.ng"));
				CHttpFile *pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,
					_T("wp/"));
				result = pFile->SendRequest(strHeaders, (LPVOID) (LPCTSTR) strFormData,
					strFormData.GetLength());
				pFile->ReadString(lines);
				pConnection->Close();
				if(lines.Find("\"result\":\"success\"")!=-1)
				{
					CCadApp* pApp =(CCadApp*)AfxGetApp();
					pApp->WriteProfileString(Version,"License",TempStr);
					m_crypto.DeriveKey(_T("jeongpal2008"));
					CByteArray arData;
					m_crypto.Encrypt(TempStr, arData);
					pApp->WriteProfileString(Version,"LicenseCheck",CString(arData.GetData()));
					AfxMessageBox("Thank you for registering!",MB_OK);
				}
				else
				{
					AfxMessageBox("Possible System Error. Please check your connection and Try Again. If problem persist contact support@andycad.com.ng",MB_ICONINFORMATION ,MB_OK);
					if(IDOK)
					{
					CRegDialog dlg;
					dlg.DoModal();	
					}
				}
		}
	}
	else
	{
	
		AfxMessageBox("Invalid Registration Code! Please check your code and Try Again",MB_ICONINFORMATION ,MB_OK);
		
		if(IDOK)
		{
		CRegDialog dlg;
	    dlg.DoModal();	
		}
		
	}
	}
	catch(...)
	{
		AfxMessageBox("System Error. Please check your connection and Try Again",MB_ICONINFORMATION ,MB_OK);
		if(IDOK)
		{
		CRegDialog dlg;
	    dlg.DoModal();	
		}

	}

}


void CRegDialog::Check()
{

	//CWinApp* pApp = AfxGetApp();
	CCadApp* pApp =(CCadApp*)AfxGetApp();
	CString strStarted = pApp->GetProfileString(Version,"Started");
//	pApp->WriteProfileString(Version,"License","");

	if (strStarted == "")   //First Start
	{
		pApp->WriteProfileString(Version,"Started","Yes");
		
		CTime theTime = CTime::GetCurrentTime();
		int Year = theTime.GetYear();
		int Month = theTime.GetMonth();
		int Day = theTime.GetDay();
		int Code = 0;
		int DeadFlag = 0;
		int Run = 1;
		pApp->WriteProfileString(Version,"License","");
		pApp->WriteProfileInt(Version,"Run year",Year);
		pApp->WriteProfileInt(Version,"Run month",Month);
		pApp->WriteProfileInt(Version,"Run day",Day);
		pApp->WriteProfileInt(Version,"Times run",Run);
		pApp->WriteProfileInt(Version,"Code",Code);
		pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
	}
	else //Not First Start
	{
		CString askCode,askCode2;
		int DeadFlag;
//		askCode = pApp->GetProfileInt(Version,"Code",0);
		askCode = pApp->GetProfileString(Version,"LicenseCheck","");
		askCode2 = pApp->GetProfileString(Version,"License","");
		CString spk,spa;
		spk.Format(_T("%d"),KeyCode);
		spa.Format(_T("%d"),askCode);
//		AfxMessageBox("Welcome to AndyCAD keyCode:"+spk+" askCode:"+spa);
//		if (KeyCode!=askCode)
		m_crypto.DeriveKey(_T("jeongpal2008"));
		CByteArray arData;
		m_crypto.Encrypt(askCode2, arData);
		
		if ((askCode2.IsEmpty())||(CString(arData.GetData())!=askCode))
			{	
				CRegDialog dlgReg;
				int pk=dlgReg.DoModal();
				if(pk==IDOK)
				{
				askCode2 = pApp->GetProfileString(Version,"License",0);
				CByteArray arData;
				m_crypto.Encrypt(askCode2, arData);
				if (CString(arData.GetData())!=askCode)
					{
					//	DeadFlag = pApp->GetProfileInt(Version,"Dead Flag",0);
					//	if (DeadFlag==1)
							exit(0);
					}
				}else
					if (pk==IDCANCEL)
				{
					return;
				}
			}
		else
			{
				DeadFlag=0;
				pApp->WriteProfileInt(Version,"Dead Flag",DeadFlag);
			}

	
	}

}

void CRegDialog::OnClose() 
{
	exit(1);
}


BOOL CRegDialog::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}
