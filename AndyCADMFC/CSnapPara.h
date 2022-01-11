//
//  CSnapPara.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapPara__
#define __testcommand__CSnapPara__

#include <iostream>
// SnapPara.h: interface for the CSnapPara class.
//
//////////////////////////////////////////////////////////////////////
#include "cCommand.h"
#include "cvector.h"
#include "CDC.h"

class CSnap;
class CSnapPara : public CCommand
{
public:
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);
	void setBasePoint(CVector  vl);
	bool snappara2(CVector  vl,CVector vs, CVector &v);
    
	CSnapPara();
	virtual ~CSnapPara();
protected:
	bool snappara(CVector  vl,CVector& vs, CVector &v);
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	CSnap* snap;
	float	m_snapxspacing;
	float	m_snapyspacing;
    
    
};

#endif /* defined(__testcommand__CSnapPara__) */
