// ChFi.h: interface for the CChFi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHFI_H__25E79295_69A7_48FE_9248_6D07F3365043__INCLUDED_)
#define AFX_CHFI_H__25E79295_69A7_48FE_9248_6D07F3365043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LibS.h"
#include"Cercle.h"
#include"line.h"


class CChFi : public CLibS  
{
public:
	CChFi();
	virtual ~CChFi();
	CLine pl1,pl2,v1line,v2line,arrow1,arrow2;
	CCercle pline;
private:
	bool straight;
	bool v1sel,v2sel;
	vector<CVector> linesel;

};

#endif // !defined(AFX_CHFI_H__25E79295_69A7_48FE_9248_6D07F3365043__INCLUDED_)
