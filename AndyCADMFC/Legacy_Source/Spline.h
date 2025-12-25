// Spline.h: interface for the CSpline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLINE_H__0247249E_C08A_4326_ADC2_98045A5F37EA__INCLUDED_)
#define AFX_SPLINE_H__0247249E_C08A_4326_ADC2_98045A5F37EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LibS.h"
#include "bezier.h"
#include <set>

class CSpline : public CLibS  
{
public:
	void draw(CDC* hdc);
	void closecurve(CVector point,CDC *hdc);
	void drawselect(CDC* hdc);
	bool PtinRegion(CVector point);
	void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	CFigure * closecurve();
	CSpline();
	virtual ~CSpline();
protected:
	vector<CVector*> v;
	CBezier b;

};

#endif // !defined(AFX_SPLINE_H__0247249E_C08A_4326_ADC2_98045A5F37EA__INCLUDED_)
