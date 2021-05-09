// DimL.h: interface for the CDimL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIML_H__05A8A9F5_4DD5_4D76_9429_2E85AD58754E__INCLUDED_)
#define AFX_DIML_H__05A8A9F5_4DD5_4D76_9429_2E85AD58754E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LibS.h"
#include "line.h"
#include "dimarrow.h"
#include "dimtext.h"
#include "textcad.h"

class CDimL : public CLibS  
{
public:
	const CAABB getbox(CDC* hdc);
	CDimL(CFile &file,CDC* hdc);
	void savefile(CFile &file);
	void openfile(CFile &file,CDC* hdc);
	LONG ReadFike(CFile &file);
	bool isReady();
	void draw(CDC *hdc);
	void setstyle(CString st);
	bool PtinRegion(CVector point);
	void initL();
	bool draw(bool fPrevLine, CDC *hdc, CVector point);
	void setPtsBegin(CVector pos);
	void create(CVector pos);
	bool getCharge(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	CLine pline,pl1,pl2,v1line,v2line,arrow1,arrow2;
	CDimArrow arrow11,arrow22;
	CTextCad text;
	CDimText text2;

	CDimL();
	virtual ~CDimL();

private:
	bool v1sel,v2sel,vl,vl2,vpc,pfull,ptext;
	enum STYLE {vert,horiz,free} style;
	CVector bl,bf;
	bool state;


};

#endif // !defined(AFX_DIML_H__05A8A9F5_4DD5_4D76_9429_2E85AD58754E__INCLUDED_)
