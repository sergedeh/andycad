//
//  CSnapmidp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapmidp.h"
// SnapMidP.cpp: implementation of the CSnapMidP class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapMidP.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapMidP::CSnapMidP()
{
	//bkcolor=RGB(42,112,219);*************
}

CSnapMidP::~CSnapMidP()
{
    
}
bool CSnapMidP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"mid");
}
