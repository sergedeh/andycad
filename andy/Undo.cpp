// Undo.cpp: implementation of the CUndo class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Undo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUndo::CUndo()
{

}

CUndo::~CUndo()
{

}
/*void CUndo::undo(bool rdo)
{
	vs.clear();
	int i=draw->getFigures();
	if(undoList.size()>0)
	{
		//get last element in undo list
		string obj = undoList.top();
		undoList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		if (obj=="create")
		{
		if(fit>0)
		{
		//remove last created rectangle
		CMemento* m = vmemento.back();vmemento.pop_back();
		delete m;
		if(rdo)
		{
        CMemento* m1 = new CMemento(draw->getFigure(i-1));
	    rmemento.push_back(m1);
	    redoList.push("delete");
		}
		draw->
		delete fig[fit-1];
		fig.pop_back();
		fit--;count--;
		}
		}
		if (obj=="delete")
		{
		//get the Memento
		CMemento* m = vmemento.back();vmemento.pop_back();
		fig.resize(fit+1);
		fig[fit]=m->getM(); //and restore the old position
		CFigure* f=m->getF();
		vector<CMemento*>::iterator pi;
		for(pi=vmemento.begin();pi!=vmemento.end();pi++)
		{
			if((*pi)->getF()==f)
				(*pi)->setF(fig[fit]);
		}
		for(pi=rmemento.begin();pi!=rmemento.end();pi++)
		{
			if((*pi)->getF()==f)
				(*pi)->setF(fig[fit]);
		}
		delete m;
		if(rdo)
		{
        CMemento* m1 = new CMemento(fig[fit]);
	    rmemento.push_back(m1);
	    redoList.push("create");
		}
		fit++;count++;
		}
		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = vmemento.back();vmemento.pop_back();
		if(rdo)
		{
        CMemento* m1 = new CMemento(m->getM());
	    rmemento.push_back(m1);
	    redoList.push("Memento");
		}
		m->Restore(); //and restore the old position
		delete m;
		}
	}

}

void CUndo::redo(CDC *hdc)
{
	vs.clear();
	if(redoList.size()>0)
	{
		//get last element in undo list
		string obj = redoList.top();
		redoList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		if (obj=="delete")
		{
		//remove last created rectangle
		CMemento* m = rmemento.back();rmemento.pop_back();
		fig.resize(fit+1);
		fig[fit]=m->getM(); //and restore the old position
		delete m;
        CMemento* m1 = new CMemento(fig[fit]);
	    vmemento.push_back(m1);
	    undoList.push("create");
		fit++;count++;
		}
		if (obj=="create")
		{
			if(fit>0)
			{
			CMemento* m = rmemento.back();rmemento.pop_back();
			delete m;
			//remove last created rectangle
			CMemento* m1 = new CMemento(fig[fit-1]);
			vmemento.push_back(m1);
			undoList.push("delete");
			delete fig[fit-1];
			fig.pop_back();
			fit--;count--;
			}
		}

		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = rmemento.back();rmemento.pop_back();
		CFigure *f=m->getM();
        CMemento* m1 = new CMemento(f);
		m->Restore(); //and restore the old position
		delete m;
	    vmemento.push_back(m1);
	    undoList.push("Memento");
		}
	}

}
*/
