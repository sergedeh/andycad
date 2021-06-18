// Memento.cpp: implementation of the CMemento class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Memento.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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
