//
//  CDimArrow.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CDimArrow__
#define __testcommand__CDimArrow__

#include <iostream>
// DimArrow.h: interface for the CDimArrow class.
//
//////////////////////////////////////////////////////////////////////
#include "cLine.h"

class CDimArrow : public CLine
{
public:
	CDimArrow();
	void Arrow();
	void initArrow(int _style, CFigure& line,float u1, float u2,int u,bool dir=false);
	virtual ~CDimArrow();
	int style;
    
};

#endif /* defined(__testcommand__CDimArrow__) */
