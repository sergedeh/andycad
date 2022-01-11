//
//  CSnapcentp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapcentp.h"
// SnapCentP.cpp: implementation of the CSnapCentP class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapCentP.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapCentP::CSnapCentP()
{
	//bkcolor=RGB(42,112,219);*****
}

CSnapCentP::~CSnapCentP()
{
    
}
bool CSnapCentP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"center");
}
