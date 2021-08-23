// mytestDoc.h : interface of the CMytestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTESTDOC_H__24CE6A39_10DA_40A4_9D11_F4E32E1FE773__INCLUDED_)
#define AFX_MYTESTDOC_H__24CE6A39_10DA_40A4_9D11_F4E32E1FE773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMytestDoc : public CDocument
{
protected: // create from serialization only
	CMytestDoc();
	DECLARE_DYNCREATE(CMytestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMytestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMytestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMytestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTESTDOC_H__24CE6A39_10DA_40A4_9D11_F4E32E1FE773__INCLUDED_)
