#if !defined(AFX_TEXT1_H__76D89ADC_FA77_45CA_99AF_589F9E133E8D__INCLUDED_)
#define AFX_TEXT1_H__76D89ADC_FA77_45CA_99AF_589F9E133E8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Text1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CText view

class CText : public CEditView
{
protected:
	CText();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CText)

// Attributes
public:

// Operations


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CText)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CText();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CText)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXT1_H__76D89ADC_FA77_45CA_99AF_589F9E133E8D__INCLUDED_)
