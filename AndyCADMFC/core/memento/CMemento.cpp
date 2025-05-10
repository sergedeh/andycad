//
//  CMemento.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CMemento.h"
// Memento.cpp: implementation of the CMemento class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemento::CMemento(CFigure* i)
{
	try{
        fig=i;
        cfig=fig->generateCopy();
	}catch(...)
	{
	}
    //	ptbegin=fig->ptbegin;
    //	ptend=fig->ptend;
    //	prevptbegin=fig->prevptbegin;
    //	prevptend=fig->prevptend;
    
}

CMemento::~CMemento()
{
    //	free(fig);
	delete cfig;
}
void CMemento::Restore()
{
	fig->copy(cfig);
}

CFigure* CMemento::getM()
{
	return cfig->generateCopy();
}

CFigure* CMemento::getF()
{
	return fig;
}

void CMemento::setF(CFigure *l)
{
	fig=l;
}
