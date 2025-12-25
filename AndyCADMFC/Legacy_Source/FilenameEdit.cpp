// FilenameEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "ScriptApp.h"
#include "FilenameEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit

CFilenameEdit::CFilenameEdit()
{
}

CFilenameEdit::~CFilenameEdit()
{
}


BEGIN_MESSAGE_MAP(CFilenameEdit, CEdit)
	//{{AFX_MSG_MAP(CFilenameEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit helpers

BOOL CFilenameEdit::IsValidFileChar( UINT nChar )
{
	// Step through all of the possibilities, starting with
	// regular letters, digits, and the underscore.
	if ( __iscsym(nChar) ) {
		// Legal character (letter, number, or underscore
		return TRUE;
	} // if

	// Check for (allowed) special characters 
	switch ( nChar ) {
		case ' ': // space
		case '$':
		case '%':
		case '\'':
		case '-':
		case '@':
		case '{':
		case '}':
		case '~':
		case '`':
		case '!':
		case '#':
		case '(':
		case ')':
			// These are valid, so exit
			return TRUE;

		case VK_TAB:
		case VK_RETURN:
		case VK_ESCAPE:
		case VK_DELETE:
		case VK_BACK:
			// Characters we want the edit control to see
			return TRUE;

		default:
			// Continue checking
			break;
	} // switch

	// Nope...
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit message handlers

void CFilenameEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if ( !IsValidFileChar(nChar) ) {
		// Just make noise
		::MessageBeep(0xFFFFFFFF);
		return;
	} // else
	
	// Call base class
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CFilenameEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ( nChar == VK_ESCAPE ) {
		// Must handle VK_ESCAPE specially.
		// In a normal dialog, VK_ESCAPE gets handled by the dialog box
		// window process, and the edit control never sees the character.
		// When the edit control lives on a property page, this doesn't
		// happen.  If VK_ESCAPE is not handled here then when the escape
		// key is pressed the entire control disappears from the dialog!
		// If the parent of the control is a dialog, and the dialog's parent
		// is also a dialog, that's a sign that the control is on a
		// property page.
		TCHAR cClass1[12];
		TCHAR cClass2[12];

		// Clear window class name arrays
		memset(cClass1, 0, sizeof(cClass1));
		memset(cClass2, 0, sizeof(cClass2));

		// Get parent and parent's parent window pointers
		CWnd* pDialog = GetParent();
		CWnd* pDialogParent = pDialog->GetParent();

		// Get class names of the windows that own the
		// phone number edit control and its parent.
		if ( pDialog != NULL ) {
			::GetClassName(pDialog->m_hWnd, cClass1, sizeof(cClass1)/sizeof(TCHAR));
		} // if

		if ( pDialogParent != NULL ) {
			::GetClassName(pDialogParent->m_hWnd, cClass2, sizeof(cClass2)/sizeof(TCHAR));
		} // if

		// If parent is a dialog, and parent's parent is a dialog,
		// simulate Cancel button press.
		static const TCHAR szDialogClass[] = _T("#32770"); // Special window class for dialogs
		if (0 == _tcscmp(cClass1, szDialogClass) && 0 == _tcscmp(cClass2, szDialogClass)) {
			CWnd* pCancel = pDialogParent->GetDlgItem(IDCANCEL);	// Get the Cancel button
			pDialogParent->SendMessage(WM_COMMAND,
				MAKEWPARAM(IDCANCEL, BN_CLICKED),
				(LPARAM) (NULL != pCancel->m_hWnd ? pCancel->m_hWnd : NULL));
			return;
		} // if
	} // if

	// Call base class
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
