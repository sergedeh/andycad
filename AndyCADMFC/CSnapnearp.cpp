//
//  CSnapnearp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapnearp.h"
// SnapNearP.cpp: implementation of the CSnapNearP class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapNearP.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapNearP::CSnapNearP()
{
	//bkcolor=RGB(255,0,0);************************
}

CSnapNearP::~CSnapNearP()
{
    
}
bool CSnapNearP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"near");
}
