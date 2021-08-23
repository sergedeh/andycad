// andycadDoc.h : interface of the CAndycadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANDYCADDOC_H__B885BC11_CC61_4F75_88C2_F05232D81126__INCLUDED_)
#define AFX_ANDYCADDOC_H__B885BC11_CC61_4F75_88C2_F05232D81126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAndycadSrvrItem;

class CAndycadDoc : public COleServerDoc
{
protected: // create from serialization only
	CAndycadDoc();
	DECLARE_DYNCREATE(CAndycadDoc)

// Attributes
public:
	CAndycadSrvrItem* GetEmbeddedItem()
		{ return (CAndycadSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAndycadDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAndycadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	//{{AFX_MSG(CAndycadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAndycadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANDYCADDOC_H__B885BC11_CC61_4F75_88C2_F05232D81126__INCLUDED_)
