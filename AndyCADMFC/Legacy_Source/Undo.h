// Undo.h: interface for the CUndo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDO_H__D69BDEA2_7676_441B_A14A_2F79418FB2C4__INCLUDED_)
#define AFX_UNDO_H__D69BDEA2_7676_441B_A14A_2F79418FB2C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "memento.h"
#include <stack>
#include <vector>
using namespace std;
class CUndo  
{
public:
	CUndo();
	virtual ~CUndo();
private:
	//Shape Undo redo
	vector<CMemento*> vmemento;
	vector<CMemento*> rmemento;
	stack<string> undoList;
	stack<string> redoList;

};

#endif // !defined(AFX_UNDO_H__D69BDEA2_7676_441B_A14A_2F79418FB2C4__INCLUDED_)
