// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__04018D3B_2A49_4F83_AD58_02731A62FFA7__INCLUDED_)
#define AFX_RECTANGLE_H__04018D3B_2A49_4F83_AD58_02731A62FFA7__INCLUDED_

#include "bezier.h"	// Added by ClassView
#include "Line.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRectangle :public CLine 
{
public:
	virtual CFigure* generateCopy();
	void drawMesh(CDC *hdc,float r);
	CRectangle(CVector b,CVector e);
	void getchargeL();
	void setstyle(int i);
//	void translate(CWnd *wnd,CDC *hdc,CVector prevpos,CVector postpos);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void savefile(CFile &file);
	void setType(CString  option);
	void createvec();
	CRectangle mirror(CDC *hdc, CRectangle  *rectangle);
	void drawpointdyna(CDC *hdc, CVector pbe, CVector pbb);
	void drawinit(CDC *hdc, CVector begin, CVector end);
	void draw(CDC* hdc);
	bool  draw(bool fPrevLine, CDC *hdc,CVector point);
	void polystate(CVector pos);
	bool getCharge();
	void setMove(bool mv,CVector pos);
	friend class CInter;

	CRectangle();
	CRectangle(CFile &file);
	virtual ~CRectangle();

private:
	enum TP{select, rect} tprect;
	CVector prev_v2,prev_v3x,prev_e,prev_v3y;
	CBezier* bez;

};

#endif // !defined(AFX_RECTANGLE_H__04018D3B_2A49_4F83_AD58_02731A62FFA7__INCLUDED_)
