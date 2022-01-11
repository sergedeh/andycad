//
//  CSnapparagrid.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapparagrid__
#define __testcommand__CSnapparagrid__

#include <iostream>
// SnapParaGrid.h: interface for the CSnapParaGrid class.
//
//////////////////////////////////////////////////////////////////////
#include "cSnapPara.h"

class CSnapParaGrid : public CSnapPara
{
public:
	void setBasePoint(CVector  vl);
	void execute(CVector &v, CDC *hdc);
	bool snappara2(CVector  vl,CVector vs, CVector &v);
	CSnapParaGrid();
	virtual ~CSnapParaGrid();
protected:
    
};

#endif /* defined(__testcommand__CSnapparagrid__) */
