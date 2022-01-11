//
//  CSnappoint.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnappoint__
#define __testcommand__CSnappoint__

#include <iostream>
// SnapPoint.h: interface for the CSnapPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "cCommand.h"
#include "cvector.h"
#include "CDC.h"
class CSnap;
class CSnapPoint : public CCommand
{
public:
	virtual bool getSnapPoint(CVector& v,CVector& vl,CDC* hdc)=0;
	bool isSnapped();
	void Init(CSnap *_snap,CVector space);
	void execute(CVector& v, CDC* hdc);
    
	CSnapPoint();
	~CSnapPoint();
protected:
	//COLORREF bkcolor;*************
	CSnap* snap;
	bool snapPrev,lock;
	CVector hitpoint,pvl,xvl,xvp;
	float	m_snapxspacing;
	float	m_snapyspacing;
	float min_spacing;
private:
    
};

#endif /* defined(__testcommand__CSnappoint__) */
