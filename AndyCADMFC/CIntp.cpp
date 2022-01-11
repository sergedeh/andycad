//
//  CIntp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/20/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CIntp.h"
// IntP.cpp: implementation of the CIntP class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntP::CIntP()
{
    
}

CIntP::~CIntP()
{
    
}
void CIntP::getValue(CIntP *p)
{
	p->s=s;
}

void CIntP::setValue(CIntP *v)
{
	s=v->s;
}

CIntP::CIntP(string n, int p)
:CProperty(n)
{
	s=p;
}

int CIntP::getValue()
{
	return s;
}
