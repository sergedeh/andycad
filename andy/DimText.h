// DimText.h: interface for the CDimText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMTEXT_H__0EBF0B10_6CB4_40DD_9EDE_52E93158204A__INCLUDED_)
#define AFX_DIMTEXT_H__0EBF0B10_6CB4_40DD_9EDE_52E93158204A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextCad.h"

class CDimText : public CTextCad  
{
public:
	void initText(CString _style,CDC* hdc,CVector v,float u);
	CDimText();
	virtual ~CDimText();
	static CString style,astyle;
	static int precision_type,aprecision_type;
private:
	CString precision;

};

#endif // !defined(AFX_DIMTEXT_H__0EBF0B10_6CB4_40DD_9EDE_52E93158204A__INCLUDED_)
