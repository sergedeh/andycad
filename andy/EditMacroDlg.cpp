// EditMacroDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "EditMacroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMacroDlg dialog


CEditMacroDlg::CEditMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditMacroDlg)
	m_strMacroName = _T("");
	m_strText = _T("");
	//}}AFX_DATA_INIT

	// Initialize our filename
	m_strFile = _T("");
}


void CEditMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMacroDlg)
	DDX_Text(pDX, IDC_MACRONAMETXT, m_strMacroName);
	DDX_Text(pDX, IDC_TEXTEDIT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CEditMacroDlg)
	ON_EN_UPDATE(IDC_TEXTEDIT, OnUpdateTextedit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditMacroDlg message handlers

BOOL CEditMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
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
	} // catch

	// Set the focus to the edit control
	UpdateData(FALSE);
	CWnd* pEdit = GetDlgItem(IDC_TEXTEDIT);
	pEdit->SetFocus(); // note we set the return value to FALSE below...
	
	return FALSE; // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditMacroDlg::OnUpdateTextedit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	// If the user typed a character, we can enable the 
	// save button
	CWnd* pButton = GetDlgItem(IDOK);
	pButton->EnableWindow(TRUE);
	
}

void CEditMacroDlg::OnOK() 
{
	// Save the text using the filename we created earlier.
	try {
		// Save the macro text
		ASSERT(m_strFile.GetLength());
		CFile fileMacro(m_strFile,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite);

		// Write the file
		UpdateData(TRUE);
		fileMacro.Write(m_strText.GetBuffer(m_strText.GetLength()),m_strText.GetLength());

		// Flush it
		fileMacro.Flush();

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
		strMsg = _T("File error writing macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
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
		strMsg = _T("Error writing macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
	} // catch
	
	CDialog::OnOK();
}
