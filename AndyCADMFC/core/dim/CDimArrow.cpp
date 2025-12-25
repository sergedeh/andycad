//
//  CDimArrow.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CDimArrow.h"
// DimArrow.cpp: implementation of the CDimArrow class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimArrow::CDimArrow()
{
    
}
void CDimArrow::initArrow(int _style, CFigure& line,float u1, float u2,int u,bool dir)
{
	switch(_style)
	{
        case 0:
            Arrow();
            if(!dir)
                setRefLine(2.5,1);
            else
                setRefLine(1,2.5);
            connectTo(&line,u1,u2,u);
            break;
        default:
            break;
	}
}
void CDimArrow::Arrow()
{
	CGPoint p0=CGPointv(0,0);
	CGPoint p2= CGPointv(0,10);
	CGPoint p1= CGPointv(30,5);
	vector<CVector> g;
	g.push_back(p0);
	g.push_back(p1);
	g.push_back(p2);
	g.push_back(p0);
	CLine l(g);
	copy(&l);
	cancharge=true;
}
CDimArrow::~CDimArrow()
{
    
}
