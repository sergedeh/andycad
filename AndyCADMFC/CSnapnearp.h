//
//  CSnapnearp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapnearp__
#define __testcommand__CSnapnearp__

#include <iostream>
// SnapNearP.h: interface for the CSnapNearP class.
//
//////////////////////////////////////////////////////////////////////
#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"
class CSnapNearP : public CSnapPoint
{
public:
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapNearP();
	virtual ~CSnapNearP();
    
};

#endif /* defined(__testcommand__CSnapnearp__) */
