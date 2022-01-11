//
//  CSnapgridp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapgridp__
#define __testcommand__CSnapgridp__

#include <iostream>
// SnapGridP.h: interface for the CSnapGridP class.
//
//////////////////////////////////////////////////////////////////////

#include "csnappoint.h"
#include "cvector.h"
#include "CDC.h"

class CSnapGridP : public CSnapPoint
{
public:
	void execute(CVector &v, CDC *hdc);
	void Init(CSnap *d,CVector base,CVector space);
	bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc);
	CSnapGridP();
	virtual ~CSnapGridP();
private:
	float	m_xbase;
	float	m_ybase;
	float	m_snapxspacing;
	float	m_snapyspacing;
    
};

#endif /* defined(__testcommand__CSnapgridp__) */
