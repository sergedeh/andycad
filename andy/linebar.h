// LineBar.h: interface for the CLineBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEBAR_H__5A4AFC00_2568_4CD3_A1BA_602D3370537C__INCLUDED_)
#define AFX_LINEBAR_H__5A4AFC00_2568_4CD3_A1BA_602D3370537C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLineBar : public CToolBar  
{
public:

	CLineBar();
	BOOL AddComboBoxline();
	BOOL ShowComboBoxline();
	BOOL HideComboBoxline();
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	virtual ~CLineBar();

protected:
	CComboBox m_combox;
};

#endif // !defined(AFX_LINEBAR_H__5A4AFC00_2568_4CD3_A1BA_602D3370537C__INCLUDED_)
