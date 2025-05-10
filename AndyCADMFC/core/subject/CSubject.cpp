//
//  CSubject.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "pch.h" 
#include "CSubject.h"
// Subject.cpp: implementation of the CSubject class.
//
//////////////////////////////////////////////////////////////////////
#include <algorithm>
//typedef vector<CObject*>::iterator it;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubject::CSubject()
{
    
}

CSubject::~CSubject()
{
    
}

void CSubject::setview(CCadView *v)
{
    view=v;
}

void CSubject::Unregister(CObserver *o)
{
    remove(observers.begin(),observers.end(),o);
}
