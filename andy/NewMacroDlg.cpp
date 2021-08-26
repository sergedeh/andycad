// NewMacroDlg.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "NewMacroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewMacroDlg dialog


CNewMacroDlg::CNewMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewMacroDlg)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CNewMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewMacroDlg)
	DDX_Control(pDX, IDC_NAMEEDIT, m_CName);
	DDX_Text(pDX, IDC_TEXTEDIT, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewMacroDlg, CDialog)
	//{{AFX_MSG_MAP(CNewMacroDlg)
	ON_BN_CLICKED(IDOK, OnSave)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewMacroDlg message handlers



void CNewMacroDlg::OnCancel() 
{
	// Check to see if any text has been added, and
	// prompt for cancel if so...
	UpdateData(TRUE);
	if ( m_strText.GetLength() > 0 ) {
		// Prompt...
		if ( AfxMessageBox("Are you sure?",MB_YESNO|MB_ICONQUESTION) == IDNO ) {
			// They declined...
			return;
		} // if
	} // if
	
	CDialog::OnCancel();
}

BOOL CNewMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Clear the file name edit control
	m_CName.SetWindowText(_T(""));
	m_CName.SetFocus(); // note FALSE return below...
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewMacroDlg::OnSave() 
{
	// Save the text using the filename given.  We've already
	// made sure only valid characters are given in the
	// macro name edit control, so we'll determine the current
	// directory and save the text in the macro text control
	// using the name as a filename.
	try {
		// Pull file name text
		UpdateData(TRUE);
		CString strFilename;
		m_CName.GetWindowText(strFilename);

		// If they didn't give us a filename but did type
		// in the text control, we tell them to give us a 
		// macro name...
		if ( !strFilename.GetLength() && m_strText.GetLength() ) {
			// They didn't provide a name...
			AfxMessageBox("You must provide a macro name",MB_OK|MB_ICONINFORMATION);
			return;
		} // if

		// If they gave us a filename but didn't type
		// in the text control, we tell them to give us a 
		// macro...
		if ( strFilename.GetLength() && !m_strText.GetLength() ) {
			// They didn't provide a macro...
			AfxMessageBox("You must provide a macro",MB_OK|MB_ICONINFORMATION);
			return;
		} // if

		// If they didn't give us a filename and didn't type
		// in the edit control, we simply exit...
		if ( !strFilename.GetLength() && !m_strText.GetLength() ) {
			// They didn't provide a name...
			EndDialog(IDCANCEL);
			return;
		} // if

		// We've now ascertained we have a filename (with
		// valid characters) and some macro text to save,
		// so we'll now save what we have.  Note we don't
		// parse and/or check for validity.
		TCHAR szCurrentDir[_MAX_PATH+1];
		GetCurrentDirectory(_MAX_PATH,szCurrentDir);
		CString strPath(szCurrentDir);
		if ( strPath[strPath.GetLength()-1] != '\\' ) {
			// The directory doesn't end with a backslash,
			// so we add one now.
			strPath += '\\';
		} // if
		strFilename = strPath + strFilename + _T(".mac");
		CFile fileMacro(strFilename,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite);

		// Write the file
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
	
	// Return
	EndDialog(IDOK);
	
}

void CNewMacroDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
