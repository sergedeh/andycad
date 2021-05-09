// cadDoc.h : interface of the CCadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CADDOC_H__2417D808_88FC_4CE8_921C_580480478F55__INCLUDED_)
#define AFX_CADDOC_H__2417D808_88FC_4CE8_921C_580480478F55__INCLUDED_

#include "Draw.h"	// Added by ClassView
#include "Parser.h"	// Added by ClassView
#include "Parserdxf.h"	// Added by ClassView
#include "CadAutoWnd.h"	// Added by ClassView
#include "CadAutoCanvas.h"	// Added by ClassView
#include "CadAutoUtils.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define HINT_DELCHAR_AFTER 100
#define HINT_DELCHAR_BEFORE 101
#define HINT_DELETE_SELECTION 102
#define HINT_PASTE 103
#define HINT_SELECTION 104
#define HINT_UNSELECTION 105
#define HINT_INPUT 106

//class CDraw;
class CCadView;
//class CCADSrvrItem;

class CCadDoc : public COleDocument//,public OleServerDoc
{
protected: // create from serialization only
	CCadDoc();
	DECLARE_DYNCREATE(CCadDoc)

// Attributes
public:

	CParser *m_parser;
	CParserDxf *m_parserdxf;
	CDraw *m_objects;
//	CCADSrvrItem* GetEmbeddedItem()
//		{ return (CCADSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:
	COLORREF GetPaperColor() const { return m_paperColor; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL
	protected:

// Implementation
public:
	virtual ~CCadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//virtual BOOL OnNewDocument();
protected:
//	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);	
	
// Generated message map functions
protected:
	CSize m_size;
	int m_nMapMode;
	COLORREF m_paperColor;
	CString fstr;
	int exti;

public:
	BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);
	void setcolor(COLORREF l,COLORREF b);
	void OnFileOpen(); 
	

	//{{AFX_MSG(CCadDoc)
	afx_msg void OnFileImport();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CCadDoc)
	afx_msg LPDISPATCH GetWindow();
	afx_msg void SetWindow(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetCanvas();
	afx_msg void SetCanvas(LPDISPATCH newValue);
	afx_msg LPDISPATCH GetUtils();
	afx_msg void SetUtils(LPDISPATCH newValue);
	afx_msg void Quit();
	//}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()
    DECLARE_INTERFACE_MAP()

private:
	CCadAutoCanvas auto_canvas;
	CCadAutoWnd auto_wnd;
	CCadAutoUtils auto_utils;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADDOC_H__2417D808_88FC_4CE8_921C_580480478F55__INCLUDED_)
