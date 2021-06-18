// Subject.cpp: implementation of the CSubject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Subject.h"
#include <algorithm>

typedef vector<CObject*>::iterator it;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubject::CSubject()
{

}

CSubject::~CSubject()
{

}

void CSubject::setview(CView *v)
{
 view=v;
}

void CSubject::Unregister(CObserver *o)
{
 remove(observers.begin(),observers.end(),o);
}
