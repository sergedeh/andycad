//
//  CSnapendp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapendp__
#define __testcommand__CSnapendp__

#include <iostream>
// SnapEndP.h: interface for the CSnapEndP class.
//
//////////////////////////////////////////////////////////////////////
#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"
class CSnapEndP : public CSnapPoint
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapEndP();
	virtual ~CSnapEndP();
};

#endif /* defined(__testcommand__CSnapendp__) */
