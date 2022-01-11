//
//  CSnapintp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapintp__
#define __testcommand__CSnapintp__

#include <iostream>
// SnapIntP.h: interface for the CSnapIntP class.
//
//////////////////////////////////////////////////////////////////////
#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"
class CSnapIntP : public CSnapPoint
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapIntP();
	virtual ~CSnapIntP();
    
};

#endif /* defined(__testcommand__CSnapintp__) */
