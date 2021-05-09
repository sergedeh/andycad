#if !defined(AFX_ADDINSETTINGSDIALOG_H__710B1E08_BCD7_4EF4_ABC0_993DEA2E6FEA__INCLUDED_)
#define AFX_ADDINSETTINGSDIALOG_H__710B1E08_BCD7_4EF4_ABC0_993DEA2E6FEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddinSettingsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddinSettingsDialog dialog

class CAddinSettingsDialog : public CDialog
{
// Construction
public:
	CAddinSettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddinSettingsDialog)
	enum { IDD = IDD_DIALOG_ADDIN_SETTINGS };
	CCheckListBox	m_ListAddin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddinSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddinSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINSETTINGSDIALOG_H__710B1E08_BCD7_4EF4_ABC0_993DEA2E6FEA__INCLUDED_)
