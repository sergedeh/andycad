// CntrItem.cpp : implementation of the CAndycadCntrItem class
//

#include "stdafx.h"
#include "andycad.h"

#include "andycadDoc.h"
#include "andycadView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAndycadCntrItem implementation

IMPLEMENT_SERIAL(CAndycadCntrItem, COleDocObjectItem, 0)

CAndycadCntrItem::CAndycadCntrItem(CAndycadDoc* pContainer)
	: COleDocObjectItem(pContainer)
{
	// TODO: add one-time construction code here
	
}

CAndycadCntrItem::~CAndycadCntrItem()
{
	// TODO: add cleanup code here
	
}

void CAndycadCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleDocObjectItem::OnChange(nCode, dwParam);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

BOOL CAndycadCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// During in-place activation CAndycadCntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleDocObjectItem::SetItemRects to move the item
	//  to the new position.

	if (!COleDocObjectItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: update any cache you may have of the item's rectangle/extent

	return TRUE;
}


void CAndycadCntrItem::OnActivate()
{
}

void CAndycadCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleDocObjectItem::OnDeactivateUI(bUndoable);

    // Hide the object if it is not an outside-in object
    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CAndycadCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleDocObjectItem data.
	// Since this sets up the m_pDocument pointer returned from
	//  CAndycadCntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleDocObjectItem::Serialize(ar);

	// now store/retrieve data specific to CAndycadCntrItem
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

BOOL CAndycadCntrItem::CanActivate()
{
	// Editing in-place while the server itself is being edited in-place
	//  does not work and is not supported.  So, disable in-place
	//  activation in this case.
	CAndycadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)));
	if (pDoc->IsInPlaceActive())
		return FALSE;

	// otherwise, rely on default behavior
	return COleClientItem::CanActivate();
}

/////////////////////////////////////////////////////////////////////////////
// CAndycadCntrItem diagnostics

#ifdef _DEBUG
void CAndycadCntrItem::AssertValid() const
{
	COleDocObjectItem::AssertValid();
}

void CAndycadCntrItem::Dump(CDumpContext& dc) const
{
	COleDocObjectItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
