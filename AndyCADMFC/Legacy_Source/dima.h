// DimA.h: interface for the CDimA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMA_H__34BC5258_4219_4D72_A5D6_C4B4BCBABB1A__INCLUDED_)
#define AFX_DIMA_H__34BC5258_4219_4D72_A5D6_C4B4BCBABB1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LibS.h"
#include"Cercle.h"
#include "textcad.h"

class CDimA : public CLibS  
{
public:
	CDimA(CFile &file,CDC* hdc);
	bool getCharge2CLine(CLine *pl);
	vector<CVector> getlselch();
	bool getChargeFilt(CCercle *pl);
	void setFiltParam(double lk);
	void setChamfParam(double l);
	void setchamfparam(double t);
	void addSLChamf(vector<CVector> vec,CFigure* fih);
	CFigure * getChargeChamf();
	void orient(double angle);
	bool PtinRegion(CVector point);
	void addSL(vector<CVector> vec);
	void initL();
	bool draw(bool fPrevLine, CDC *hdc, CVector point);
	void setPtsBegin(CVector pos);
	void create(CVector pos);
	bool getCharge(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	CLine pl1,pl2,v1line,v2line,arrow1,arrow2;
	CTextCad text;
	CCercle pline;

	CDimA();
	virtual ~CDimA();
private:
	bool straight;
	bool v1sel,v2sel,tsel;
	vector<CVector> linesel;
	vector<CVector> lineselch;
	static double la,ra;
	CFigure* vecfig[2];
	int it;


};

#endif // !defined(AFX_DIMA_H__34BC5258_4219_4D72_A5D6_C4B4BCBABB1A__INCLUDED_)
