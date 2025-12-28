/////////////////////////////////////////////////////////////////////////////
// CMemDoc.h : interface of the CCMemDCDoc class
//
// Written by Kelly Ward
// of Microsoft Product Support Services, Languages Developer Support
// Copyright (c) 1996 Microsoft Corporation. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


class CCMemDCDoc : public CDocument
{
protected: // create from serialization only
	CCMemDCDoc();
	DECLARE_DYNCREATE(CCMemDCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCMemDCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCMemDCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCMemDCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
