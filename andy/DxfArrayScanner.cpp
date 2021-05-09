// DxfArrayScanner.cpp: implementation of the CDxfArrayScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "DxfArrayScanner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDxfArrayScanner::CDxfArrayScanner()
{

}
CDxfArrayScanner::CDxfArrayScanner(vector<string> lines)
{

}

CDxfArrayScanner::~CDxfArrayScanner()
{

}

bool CDxfArrayScanner::hasNext()
{
	return false;
}
