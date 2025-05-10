//
//  CMemento.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CMemento__
#define __testcommand__CMemento__

#include <iostream>
// Memento.h: interface for the CMemento class.
//
//////////////////////////////////////////////////////////////////////

#include "cfigure.h"
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

#endif /* defined(__testcommand__CMemento__) */
