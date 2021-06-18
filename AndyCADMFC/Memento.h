// Memento.h: interface for the CMemento class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMENTO_H__CF34F925_B7E4_4826_824E_1951846924D1__INCLUDED_)
#define AFX_MEMENTO_H__CF34F925_B7E4_4826_824E_1951846924D1__INCLUDED_

#include "figure.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemento  
{
public:
	void setF(CFigure* l);
	CFigure* getF();
	CFigure* getM();
	void Restore();
	CMemento(CFigure* i); 
	virtual ~CMemento();
private:
//	CMemento* redo;
	CFigure* fig;
	CFigure* cfig;
//	vector<CVector> ptbegin,ptend;
//	vector<CVector> prevptbegin,prevptend;
//	int x,y;
};

#endif // !defined(AFX_MEMENTO_H__CF34F925_B7E4_4826_824E_1951846924D1__INCLUDED_)
