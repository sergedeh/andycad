// FileMacroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "FileMacroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileMacroDlg dialog


CFileMacroDlg::CFileMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileMacroDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Initialize our macro name
	m_strMacroName = _T("");
}


void CFileMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileMacroDlg)
	DDX_Control(pDX, IDC_MACROCOMBO, m_CMacroCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CFileMacroDlg)
	ON_CBN_SELCHANGE(IDC_MACROCOMBO, OnSelchangeMacrocombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileMacroDlg message handlers

BOOL CFileMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Clear any existing data
	m_CMacroCombo.ResetContent();

	// Find all files in the current directory with the
	// macro file extension, ".mac".
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	CString strFile = strPath + "*.mac";
	WIN32_FIND_DATA wfd;
	HANDLE hSearchHandle = FindFirstFile(strFile,&wfd);
	if ( hSearchHandle != INVALID_HANDLE_VALUE ) {
		// Pull first filename
		CString strFileTitle(wfd.cFileName);
		strFileTitle = strFileTitle.Left(strFileTitle.Find("."));
		int iItem = m_CMacroCombo.AddString(strFileTitle);

		while ( FindNextFile(hSearchHandle,&wfd) ) {
			// While we have more files...
			strFileTitle = wfd.cFileName;
			strFileTitle = strFileTitle.Left(strFileTitle.Find("."));
			m_CMacroCombo.AddString(strFileTitle);
		} // while

		// Close our search handle
		FindClose(hSearchHandle);
	} // if

	// Make sure no macro files are selected...
	m_CMacroCombo.SetCurSel(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileMacroDlg::OnSelchangeMacrocombo() 
{
	CWnd* pButton = GetDlgItem(IDOK);
	pButton->EnableWindow(TRUE);
}

void CFileMacroDlg::OnOK() 
{
	m_CMacroCombo.GetLBText(m_CMacroCombo.GetCurSel(),m_strMacroName);
	
	CDialog::OnOK();
}
