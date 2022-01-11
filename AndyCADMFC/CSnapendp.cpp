//
//  CSnapendp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapendp.h"
// SnapEndP.cpp: implementation of the CSnapEndP class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapEndP.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapEndP::CSnapEndP()
{
//	bkcolor=RGB(255,128,0);******************
}

CSnapEndP::~CSnapEndP()
{
    
}
bool CSnapEndP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"end");
}
