// Linestyle.cpp : implementation file
//

#include "Stdafx.h"
#include "cad.h"
#include "Linestyle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinestyle dialog


CLinestyle::CLinestyle()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CLinestyle)
	//}}AFX_DATA_INIT
}


void CLinestyle::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinestyle)
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinestyle, CDialogBar)
	//{{AFX_MSG_MAP(CLinestyle)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinestyle message handlers

void CLinestyle::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
/*	HBITMAP hbmIcon; 
    HBITMAP hbmMask; 

	CDC *hdc=GetDC();

            if (nIDCtl == -1)            // empty item 
                break; 
 
            // Determine the bitmaps used to draw the icon. 
 
            switch (lpDrawItemStruct->itemData) 
            { 
                case ID_BREAD: 
                    hbmIcon = hbmBread; 
                    hbmMask = hbmBreadMask; 
                    break; 
 
                case ID_DAIRY: 
                    hbmIcon = hbmDairy; 
                    hbmMask = hbmDairyMask; 
                    break; 
 
                case ID_FRUIT: 
                    hbmIcon = hbmFruit; 
                    hbmMask = hbmFruitMask; 
                    break; 
 
                default:                /* meat */ 
  /*                  hbmIcon = hbmMeat; 
                    hbmMask = hbmMeatMask; 
                    break; 
            } 
 
            // The colors depend on whether the item is selected. 
 
            clrForeground = SetTextColor(lpDrawItemStruct->hDC, 
                GetSysColor(lpDrawItemStruct->itemState & ODS_SELECTED ? 
                COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT)); 
 
            clrBackground = SetBkColor(lpDrawItemStruct->hDC, 
                GetSysColor(lpDrawItemStruct->itemState & ODS_SELECTED ? 
                COLOR_HIGHLIGHT : COLOR_WINDOW)); 
 
            // Calculate the vertical and horizontal position. 
 
            GetTextMetrics(lpDrawItemStruct->hDC, &tm); 
            y = (lpDrawItemStruct->rcItem.bottom + lpDrawItemStruct->rcItem.top - 
                tm.tmHeight) / 2; 
            x = LOWORD(GetDialogBaseUnits()) / 4; 
 
            // Get and display the text for the list item. 
 
            SendMessage(lpDrawItemStruct->hwndItem, CB_GETLBTEXT, 
                lpDrawItemStruct->itemID, (LPARAM) (LPCSTR) achTemp); 
 
            ExtTextOut(lpDrawItemStruct->hDC, CX_BITMAP + 2 * x, y, 
                ETO_CLIPPED | ETO_OPAQUE, &lpDrawItemStruct->rcItem, 
                achTemp, lstrlen(achTemp), NULL); 
 
            // Restore the previous colors. 
 
            SetTextColor(lpDrawItemStruct->hDC, clrForeground); 
            SetBkColor(lpDrawItemStruct->hDC, clrBackground); 
 
            // Show the icon. 
 
            hdc = CreateCompatibleDC(lpDrawItemStruct->hDC); 
            if (hdc == NULL) 
                break; 
 
            SelectObject(hdc, hbmMask); 
            BitBlt(lpDrawItemStruct->hDC, x, lpDrawItemStruct->rcItem.top + 1, 
                CX_BITMAP, CY_BITMAP, hdc, 0, 0, SRCAND); 
 
            SelectObject(hdc, hbmIcon); 
            BitBlt(lpDrawItemStruct->hDC, x, lpDrawItemStruct->rcItem.top + 1, 
                CX_BITMAP, CY_BITMAP, hdc, 0, 0, SRCPAINT); 
 
            DeleteDC(hdc); 
 
            // If the item has the focus, draw focus rectangle. 
 
            if (lpDrawItemStruct->itemState & ODS_FOCUS) 
                DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem); 
 

	*/
	
	CDialogBar::OnDrawItem(nIDCtl, lpDrawItemStruct);
}








BOOL CLinestyle::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID ) 
{
	// TODO: Add your specialized code here and/or call the base class
		CRect wnd_rec;

	bool r=CDialogBar::Create(pParentWnd,nIDTemplate,nStyle,nID );

	GetWindowRect(wnd_rec);
//	wnd_rec.DeflateRect(10,10,10,10);
	m_combo.Create(CBS_SIMPLE,wnd_rec,this,520);
	IsWindowVisible();
	m_combo.IsWindowVisible();
	m_combo.ShowWindow(SW_SHOW);
	m_combo.IsWindowVisible();
	return r;
}
