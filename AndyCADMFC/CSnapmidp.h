//
//  CSnapmidp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapmidp__
#define __testcommand__CSnapmidp__

#include <iostream>
// SnapMidP.h: interface for the CSnapMidP class.
//
//////////////////////////////////////////////////////////////////////
#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"
class CSnapMidP : public CSnapPoint
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapMidP();
	virtual ~CSnapMidP();
    
};

#endif /* defined(__testcommand__CSnapmidp__) */
