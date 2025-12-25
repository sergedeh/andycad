// Dim.h: interface for the CDim class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIM_H__2DDC54CA_CA7E_4A7F_9F72_BF0AADF11C84__INCLUDED_)
#define AFX_DIM_H__2DDC54CA_CA7E_4A7F_9F72_BF0AADF11C84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LibS.h"
#include "line.h"
#include "dimarrow.h"
#include "textcad.h"
#include "dimtext.h"
#include"Cercle.h"
#include"constraint.h"

class CDim : public CLibS  
{
public:
	void UpdateDim(CFigure* f,CDC* hdc);
	void buildDim(CDC* hdc,float u, float v);
	void SendNotify(CString s, void *param[]);
	void drivingParam(CFigure* f,vector<CVector> vv);
	const CAABB getbox(CDC* hdc);
	CDim(CFile &file,CDC* hdc);
	LONG ReadFike(CFile& file);
	void openfile(CFile& file,CDC* hdc);
	void savefile(CFile& file);
	void getArc(CVector &c, CVector& c1, CVector& c2,CVector point);
	bool isReady();
	void draw(CDC *hdc);
	void addSL(vector<CVector> vec);
	void setstyle(CString st);
	void initL();
	bool draw(bool fPrevLine, CDC *hdc, CVector point);
	void setPtsBegin(CVector pos);
	void create(CVector pos);
	bool getCharge(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	bool PtinRegion(CVector point);
	CLine pline,v1line,v2line,arrow1,arrow2,a1line,a2line;
	CDimArrow arrow11,arrow22;
	CCercle cline;
	CTextCad text;
	CDimText text2;

	CDim();
	virtual ~CDim();
private:
	bool v1sel,v2sel,vl,vl2,vpc,pfull,ptext;
	enum STYLE{vert,horiz,free,diam,radius,ang,leader,multline} style;
	CVector bl,bf;
	CPoint ppoint;
	vector<CVector> linesel;
	map<CFigure* ,vector< vector<CVector> > > d_params;
	bool state;
	CConstraint* constraint;

};

#endif // !defined(AFX_DIM_H__2DDC54CA_CA7E_4A7F_9F72_BF0AADF11C84__INCLUDED_)
