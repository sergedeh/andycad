// MLinestyle.cpp: implementation of the CMLinestyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "MLinestyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMLinestyle::CMLinestyle()
{
	m_bmp1.LoadBitmap(IDB_BITMAPAT2);
	m_bmp2.LoadBitmap(IDB_BITMAPAT20);
	m_bmp3.LoadBitmap(IDB_BITMAPAT22);
	m_bmp4.LoadBitmap(IDB_BITMAPAT11);
}

CMLinestyle::~CMLinestyle()
{

}

void CMLinestyle::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
BITMAP bm;

	switch(lpMeasureItemStruct->itemData)
	{
	case MENU1:		{
			m_bmp1.GetBitmap(&bm);
			break;
		}
		case MENU2:
		{
			m_bmp2.GetBitmap(&bm);
			break;
		}
	}
	lpMeasureItemStruct->itemWidth=bm.bmWidth;
	lpMeasureItemStruct->itemHeight=bm.bmHeight;
}

void CMLinestyle::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CDC *ptrDC;
	CDC dcMem;
	CBitmap *ptrBmpOld;
	CBitmap *ptrBmp;
	CRect rect;

	if(!(lpDrawItemStruct->CtlType & ODT_MENU))
	{
		CMenu::DrawItem(lpDrawItemStruct);
		return;
	}

	ptrDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	dcMem.CreateCompatibleDC(ptrDC);

	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		switch(lpDrawItemStruct->itemData)
		{
			case MENU1:
			{
				ptrBmp=&m_bmp2;
				break;
			}
			case MENU2:
			{
				ptrBmp=&m_bmp1;
				break;
			}
		}
	}
	else
	{
		switch(lpDrawItemStruct->itemData)
		{
			case MENU1:
			{
				ptrBmp=&m_bmp2;
				break;
			}
			case MENU2:
			{
				ptrBmp=&m_bmp1;
				break;
			}
		}
	}	
	
	ptrBmpOld=dcMem.SelectObject(ptrBmp);
	rect=lpDrawItemStruct->rcItem;
	ptrDC->BitBlt
	(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(),
		&dcMem,
		0,
		0,
		SRCCOPY
	);
	dcMem.SelectObject(ptrBmpOld);

}
