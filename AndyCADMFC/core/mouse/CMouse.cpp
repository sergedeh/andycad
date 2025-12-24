//
//  CMouse.cpp
//  testcommand
//
//  Created by Serge Deh on 10/19/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CMouse.h"
// Mouse.cpp: implementation of the CMouse class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPoint CMouse::Prevposition=CGPoint(0,0);
CGPoint CMouse::Postposition=CGPoint(0,0);
bool CMouse::LBdown=false;
bool CMouse::move=false;

CMouse::CMouse()
{
	
    
}

CMouse::~CMouse()
{
    
}

void CMouse::setPostPos(CGPoint point)
{
	Postposition=point;
    
}

CGPoint CMouse::getPostPos()
{
	return Postposition;
    
}

void CMouse::setMove(bool moveStatus)
{
	move=moveStatus;
	
}

bool CMouse::getMove()
{
	return move;
    
}

void CMouse::setLBdown(bool LBdownstate)
{
	LBdown=LBdownstate;
    
}

bool CMouse::getLBdownStatus()
{
	return LBdown;
    
}

void CMouse::setPrevPos(CGPoint point)
{
	Prevposition=point;
    
}

CGPoint CMouse::getPrevPos()
{
	return Prevposition;
    
}
