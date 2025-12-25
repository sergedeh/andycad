// Pattern.h: interface for the CPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATTERN_H__279E50B4_6EC1_4477_9C74_EE84CCBEC6ED__INCLUDED_)
#define AFX_PATTERN_H__279E50B4_6EC1_4477_9C74_EE84CCBEC6ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BArrowp.h"
#include "RecPattern.h"
#include <vector>

using namespace std;

class CPattern : public CDialogBar  
{
public:
	CPattern();

public:
	CBitmap *bmp;
	CDC dcmemory;
	int nsize;
	CBitmap *GetBitmap(){return bmp;}
	CFile patfile;
	LOGPALETTE* pLP;
	LPBITMAPINFO lpbm;

// Operations
public:
 virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
 virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
 void OnLButtonarr1();
 void OnLButtonarr2();
 void OnLButtonpal();
 static void* getCPatternD(){ return pPatternD;}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPattern)
	public:
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CPattern();

	// Generated message map functions
protected:
	CBArrowP arrow1,arrow2;
	CRecPattern *but;
	CButton st1,st2,cl1,cl2;
	CColorDialog coldial;
	int nbcolbut;
	int itpos;
	
	struct {
    LOGPALETTE lp;
    PALETTEENTRY ape[256];
	} pal;

	static void *pPatternD;
	static int iter;
	vector<CString> fvec;
	vector<CBitmap*> paty;

	CDC *hdc;

protected:
	//{{AFX_MSG(CPattern)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERN_H__279E50B4_6EC1_4477_9C74_EE84CCBEC6ED__INCLUDED_)
