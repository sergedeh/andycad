#if !defined(AFX_PARSEDLG_H__DDF622D1_E068_434D_9170_A6458D91F86B__INCLUDED_)
#define AFX_PARSEDLG_H__DDF622D1_E068_434D_9170_A6458D91F86B__INCLUDED_

#include "Parser.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParseDlg.h : header file
//
#include <vector>
#include <string>
#include "editparse.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CParseDlg dialog

class CParseDlg : public CDialogBar,public CObserver
{
// Construction
public:
	void update(LPCTSTR input, LPCTSTR output);
	CParseDlg();   // standard constructor
	void SendNotify(CString s,void* param[7]);
	void setInterest(CSubject *sub);
	bool OnFromEditChar(UINT nChar);
	bool OnFromEditLButton(CPoint point);

// Dialog Data
	//{{AFX_DATA(CParseDlg)
	CEditParse	m_com;
	CString	m_log;
	enum { IDD = IDD_DIALOGBAR_PARSE };
	//}}AFX_DATA
    CString com;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	vector<CString> cmds;
	int cur_i,cur_x;
	bool back;
	friend CParser;
	CParser* parser;
	LRESULT OnInitDialog(WPARAM u,LPARAM v);

	// Generated message map functions
	//{{AFX_MSG(CParseDlg)
	afx_msg void OnUpdateEditCommand();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSEDLG_H__DDF622D1_E068_434D_9170_A6458D91F86B__INCLUDED_)
