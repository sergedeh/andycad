//
//  CSnapintp.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CSnapintp.h"
// SnapIntP.cpp: implementation of the CSnapIntP class.
//
//////////////////////////////////////////////////////////////////////
#include "cdraw.h"
#include "cSnapIntP.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnapIntP::CSnapIntP()
{
	//bkcolor=RGB(42,112,219);**************
}

CSnapIntP::~CSnapIntP()
{
    
}
bool CSnapIntP::getSnapPoint(CVector& v,CVector& vl,CDC* hdc)
{
	return snap->getSnapPoint(v,vl,hdc,"inter");
}
