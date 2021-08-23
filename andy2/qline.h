// QLine.h: interface for the CQLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QLINE_H__54BF99E8_F32C_448D_B4F0_E06E2EF62D1A__INCLUDED_)
#define AFX_QLINE_H__54BF99E8_F32C_448D_B4F0_E06E2EF62D1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
using namespace std;
class CQLine : public CLine  
{
public:
	void setstyle(CString s);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void savefile(CFile &file);
	CQLine();
	CQLine(CFile &file);
	virtual ~CQLine();
	void polystate(CVector pos);
	bool getCharge();
	void setMove(bool mv,CVector pos);
	bool draw(bool fPrevLine, CDC *hdc,CVector point);
	void draw(CDC *hdc);
	friend class CInter;
protected:
	CVector prevpos;
	CString style;

};

#endif // !defined(AFX_QLINE_H__54BF99E8_F32C_448D_B4F0_E06E2EF62D1A__INCLUDED_)
