// CntrItem.h : interface of the CAndycadCntrItem class
//

#if !defined(AFX_CNTRITEM_H__58034FFA_A98C_4E1C_82A3_2526CE8E566E__INCLUDED_)
#define AFX_CNTRITEM_H__58034FFA_A98C_4E1C_82A3_2526CE8E566E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAndycadDoc;
class CAndycadView;

class CAndycadCntrItem : public COleDocObjectItem
{
	DECLARE_SERIAL(CAndycadCntrItem)

// Constructors
public:
	CAndycadCntrItem(CAndycadDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CAndycadDoc* GetDocument()
		{ return (CAndycadDoc*)COleDocObjectItem::GetDocument(); }
	CAndycadView* GetActiveView()
		{ return (CAndycadView*)COleDocObjectItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAndycadCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CAndycadCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__58034FFA_A98C_4E1C_82A3_2526CE8E566E__INCLUDED_)
