// RunMacroDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "RunMacroDlg.h"
#include "EditMacroDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRunMacroDlg dialog


CRunMacroDlg::CRunMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRunMacroDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRunMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRunMacroDlg)
	DDX_Control(pDX, IDC_MACROLIST, m_CMacroList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRunMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CRunMacroDlg)
	ON_LBN_SELCHANGE(IDC_MACROLIST, OnSelchangeMacrolist)
	ON_BN_CLICKED(IDC_EDIT_RUN, OnEditRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunMacroDlg message handlers

BOOL CRunMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Clear any existing data
	m_CMacroList.ResetContent();

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
		int iItem = m_CMacroList.AddString(strFileTitle);

		while ( FindNextFile(hSearchHandle,&wfd) ) {
			// While we have more files...
			strFileTitle = wfd.cFileName;
			strFileTitle = strFileTitle.Left(strFileTitle.Find("."));
			m_CMacroList.AddString(strFileTitle);
		} // while

		// Close our search handle
		FindClose(hSearchHandle);
	} // if
	
	// Make sure no macro files are selected...
	m_CMacroList.SetCurSel(-1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRunMacroDlg::OnOK() 
{
	// Pull the filename
	m_CMacroList.GetText(m_CMacroList.GetCurSel(),m_strMacroName);

	// Rebuild the macro filename
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	ASSERT(m_strMacroName.GetLength());
	m_strFile = strPath + m_strMacroName + ".mac";

	// Load the file
	try {
		CFile fileMacro(m_strFile,CFile::modeRead|CFile::shareDenyWrite);

		// Determine the file's length
		DWORD dwSize = fileMacro.GetLength();

		// Read the file
		fileMacro.Read(m_strText.GetBuffer(dwSize),dwSize);
		m_strText.ReleaseBuffer();

		// Close it
		fileMacro.Close();
	} // try
	catch (CFileException* e) {
		// File I/O error
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						e->m_cause,
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("File error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
		EndDialog(IDCANCEL);
		return;
	} // catch
	catch (...) {
		// Some other error...
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("Error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
		EndDialog(IDCANCEL);
		return;
	} // catch
	
	CDialog::OnOK();
}

void CRunMacroDlg::OnSelchangeMacrolist() 
{
	// The user selected a macro, so enable the buttons
	CWnd* pButton = GetDlgItem(IDOK);
	pButton->EnableWindow(TRUE);
	pButton = GetDlgItem(IDC_EDIT);
	pButton->EnableWindow(TRUE);
	
}

void CRunMacroDlg::OnEditRun() 
{
	// Pull the macro filename
	CString strFilename;
	m_CMacroList.GetText(m_CMacroList.GetCurSel(),strFilename);

	// Bring up the edit macro dialog
	CEditMacroDlg dlgEditMacro;
	dlgEditMacro.m_strMacroName = strFilename;
	dlgEditMacro.DoModal();
	
}
