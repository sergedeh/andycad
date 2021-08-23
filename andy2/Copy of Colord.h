#if !defined(AFX_COLORD_H__24B68F3E_2944_4791_AF5A_2EE0901FDBEA__INCLUDED_)
#define AFX_COLORD_H__24B68F3E_2944_4791_AF5A_2EE0901FDBEA__INCLUDED_
#include "BArrowC.h"	// Added by ClassView
#include "reccolor.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorD window

class CColorD : public CDialogBar
{
// Construction
public:
	CColorD();

// Attributes
public:
	CBitmap *bmp;
	CDC dcmemory;
	int nsize;
	CBitmap *GetBitmap(){return bmp;}
	CPalette palette;
	LOGPALETTE* pLP;
	LPBITMAPINFO lpbm;

// Operations
public:
 virtual CSize CalcDynamicLayout( int nLength, DWORD dwMode );
 virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
 void OnLButtonarr1();
 void OnLButtonarr2();
 void OnLButtonpal();
 static void* getCColorD(){ return pColorD;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorD)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorD();

	// Generated message map functions
protected:
	CBArrowC arrow1,arrow2;
	CRecColor *but;
	CButton st1,st2,cl1,cl2;
	CColorDialog coldial;
	int nbcolbut;
	int itpos;
	
	struct {
    LOGPALETTE lp;
    PALETTEENTRY ape[256];
	} pal;

	static void *pColorD;
	static int iter;

	CDC *hdc;

	//{{AFX_MSG(CColorD)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/*
LRESULT __stdcall MainWndProc(HWND hwnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
);*/
//////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORD_H__24B68F3E_2944_4791_AF5A_2EE0901FDBEA__INCLUDED_)
