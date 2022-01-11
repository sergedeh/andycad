//
//  CSnapcentp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapcentp__
#define __testcommand__CSnapcentp__

#include <iostream>
// SnapCentP.h: interface for the CSnapCentP class.
//
//////////////////////////////////////////////////////////////////////

#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"
class CSnapCentP : public CSnapPoint
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapCentP();
	virtual ~CSnapCentP();
    
};

#endif /* defined(__testcommand__CSnapcentp__) */
