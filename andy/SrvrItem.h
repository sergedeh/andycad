// SrvrItem.h : interface of the CAndycadSrvrItem class
//

#if !defined(AFX_SRVRITEM_H__D6ADA19B_FF4C_43C2_847E_9D0D3A136290__INCLUDED_)
#define AFX_SRVRITEM_H__D6ADA19B_FF4C_43C2_847E_9D0D3A136290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAndycadSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CAndycadSrvrItem)

// Constructors
public:
	CAndycadSrvrItem(CAndycadDoc* pContainerDoc);

// Attributes
	CAndycadDoc* GetDocument() const
		{ return (CAndycadDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAndycadSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CAndycadSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__D6ADA19B_FF4C_43C2_847E_9D0D3A136290__INCLUDED_)
