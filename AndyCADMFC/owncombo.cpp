// OwnCombo.cpp : implementation file
// See OwnCombo.h for details on how to use this class
//

#include "stdafx.h"
#include "OwnCombo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ClOwnerDrawComboBox

ClOwnerDrawComboBox::ClOwnerDrawComboBox()
{
	// You can't actually add anything to the combo box here since the
	// associated CWnd hasn't been created yet.  Save any initialization
	// you need to do for after the CWnd has been constructed.  The TODO: 
	// comments in OwnCombo.h explain how to do this for 
	// ClOwnerDrawComboBox as implemented here.
}

ClOwnerDrawComboBox::~ClOwnerDrawComboBox()
{
}


BEGIN_MESSAGE_MAP(ClOwnerDrawComboBox, CComboBox)
	//{{AFX_MSG_MAP(ClOwnerDrawComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ClOwnerDrawComboBox message handlers

// This function compares two colors to each other. If you're doing 
// something different, like comparing two bitmaps to each other, use 
// a different algorithm.  If you are working with strings, the default 
// implementation provided by MFC will probably do the job just fine.  
// (Example of a string where you need to do your own comparisons: if 
// your sorting scheme is different than a standard collating sequence, 
// such as one where the comparisons need to be case-insensitive.)
int ClOwnerDrawComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	COLORREF color1 = (COLORREF)lpCompareItemStruct->itemData1;
	COLORREF color2 = (COLORREF)lpCompareItemStruct->itemData2;
	if (color1 == color2)
		return 0;       // exact match

	// first do an intensity sort, lower intensities go first
	int intensity1 = GetRValue(color1) + GetGValue(color1) + GetBValue(color1);
	int intensity2 = GetRValue(color2) + GetGValue(color2) + GetBValue(color2);
	if (intensity1 < intensity2)
		return -1;      // lower intensity goes first
	else if (intensity1 > intensity2)
		return 1;       // higher intensity goes second

	// if same intensity, sort by color (blues first, reds last)
	if (GetBValue(color1) > GetBValue(color2))
		return -1;
	else if (GetGValue(color1) > GetGValue(color2))
		return -1;
	else if (GetRValue(color1) > GetRValue(color2))
		return -1;
	else
		return 1;
}

// This function draws a color bar in the client space of this combo box 
// item.  If your combo box item contains something other than color bars, 
// you need to replace the contents of this function with your own code 
// for drawing it.  If you are working with strings, the default MFC
// implementation of this function will probably work just fine for you.  
// (Example of a string where you need to do the drawing yourself: one 
// displayed in a different font than the rest of the dialog.)
void ClOwnerDrawComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	COLORREF color = (COLORREF)lpDrawItemStruct->itemData; // RGB in item data

	// White space
	CRect rcItem(lpDrawItemStruct->rcItem);
	rcItem.InflateRect(-2, -2);

	// Paint the color item in the color requested
	CBrush brush(color);
	pDC->FillRect(rcItem, &brush);

	// Focus rect
	if (lpDrawItemStruct->itemAction & ODA_FOCUS)
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
}

#define COLOR_ITEM_HEIGHT   20

// We made our color bars all be the same height for simplicity.  You 
// can actually specify variable heights as long as you set the 
// CBS_OWNERDRAWVARIABLE style.
void ClOwnerDrawComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// all items are of fixed size
	// must use CBS_OWNERDRAWVARIABLE for this to work
	lpMeasureItemStruct->itemHeight = COLOR_ITEM_HEIGHT;
}

void ClOwnerDrawComboBox::AddListItem(COLORREF color)
{
	// add a combo box item
	AddString((LPCTSTR) color);
		// Combo box does not have the CBS_HASSTRINGS style, so the
		//  normal combo box string is used to store an RGB color
}

// add 8 colors to the combo box (primary + secondary color only)
void ClOwnerDrawComboBox::LoadList()
{
	for (int red = 0; red <= 255; red += 255)
		for (int green = 0; green <= 255; green += 255)
			for (int blue = 0; blue <= 255; blue += 255)
				AddListItem(RGB(red, green, blue));
}

