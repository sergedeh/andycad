// DimArrow.h: interface for the CDimArrow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMARROW_H__30481C59_0D5B_4EA4_AC6C_3B70AD221B73__INCLUDED_)
#define AFX_DIMARROW_H__30481C59_0D5B_4EA4_AC6C_3B70AD221B73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"

class CDimArrow : public CLine  
{
public:
	CDimArrow();
	void Arrow();
	void initArrow(int _style, CFigure& line,float u1, float u2,int u,bool dir=false);
	virtual ~CDimArrow();
	int style;

};

#endif // !defined(AFX_DIMARROW_H__30481C59_0D5B_4EA4_AC6C_3B70AD221B73__INCLUDED_)
