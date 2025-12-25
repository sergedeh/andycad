// OwnList.h : header file
//

#ifndef __OWNLIST_H__
#define __OWNLIST_H__

// This class handles an owner-draw list box.  The list box in question
// handles color bars instead of text.  It shows all of the required
// features for an owner-draw list box. See the on-line help for CListBox 
// for other ways you can manipulate the contents of an owner-draw list
// box.
//
// You can actually handle just about anything you want in an owner-draw 
// list box as long as you override functions CompareItem, DrawItem, and 
// MeasureItem.  Strings are easiest and don't require all the overrides.  
// Other examples: bitmaps, text in varying fonts, text in a non-standard 
// font, etc.
//
// TODO:
//	1.	Create an owner-draw list box in your resources to use with
//		this class.  You will need to have the following features set
//		on the Styles page for the list box:
//		- Owner-Draw: Variable
//		- Has Strings: Unchecked
//		- Sort: Checked (to show off owner-draw sorting)
//
//	2.	Subclass your owner-draw list box to associate it with this
//		class.  The following statement placed in OnInitDialog() for 
//		the dialog you used this list box in should work fine:
//			m_myDraw.SubclassDlgItem(IDC_MYDRAW, this);
//		where:
//			m_myDraw is an instance of the owner-draw list box class
//			IDC_MYDRAW is the ID associated with your list box resource
//
//	3.	Call m_myDraw.LoadList() to initialize the contents of the owner-draw
//		list box.  Do this immediately after you subclass the list box
//		control.
//
//	4.	The list box implemented here is single selection for simplicity.  
//		If you want	something different (like multiple or extended selection),
//		you will need to do the following:
//		- change the Selections type on the Styles page for the list box 
//			appropriately
//		- use the multiple-selection operations functions provided for 
//			CListBox to manipulate the selections (see the on-line help 
//			for CListBox for more details on these functions)

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox window

class COwnerDrawListBox : public CListBox
{
// Construction
public:
	COwnerDrawListBox();

// Attributes
public:

// Operations
public:
	void AddListItem(COLORREF color);
	void LoadList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnerDrawListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COwnerDrawListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(COwnerDrawListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif __OWNLIST_H__	// end define of COwnerDrawListBox
