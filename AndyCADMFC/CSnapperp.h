//
//  CSnapperp.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnapperp__
#define __testcommand__CSnapperp__

#include <iostream>
// SnapPerp.h: interface for the CSnapPerp class.
//
//////////////////////////////////////////////////////////////////////

#include "cCommand.h"
#include "cvector.h"
#include "CDC.h"

class CSnap;
class CSnapPerp : public CCommand
{
public:
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);
	void setBasePoint(CVector  vl);
	bool snapperp2(CVector  vl,CVector vs, CVector &v);
    
	CSnapPerp();
	virtual ~CSnapPerp();
private:
	bool snapperp(CVector  vl,CVector& vs, CVector &v);
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	CSnap* snap;
	float	m_snapxspacing;
	float	m_snapyspacing;
    
};

#endif /* defined(__testcommand__CSnapperp__) */
