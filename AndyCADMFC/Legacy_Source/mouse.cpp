// Mouse.cpp: implementation of the CMouse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Mouse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoint CMouse::Prevposition=0;
CPoint CMouse::Postposition=0;
bool CMouse::LBdown=false;
bool CMouse::move=false;

CMouse::CMouse()
{
	

}

CMouse::~CMouse()
{

}

void CMouse::setPostPos(CPoint point)
{
	Postposition=point;

}

CPoint CMouse::getPostPos()
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

void CMouse::setPrevPos(CPoint point)
{
	Prevposition=point;

}

CPoint CMouse::getPrevPos()
{
	return Prevposition;

}
