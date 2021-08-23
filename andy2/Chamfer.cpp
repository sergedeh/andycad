// Chamfer.cpp: implementation of the CChamfer class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Chamfer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChamfer::CChamfer(CString s):CVerb(s)
{
 value= CHAMFER;
}

CChamfer::~CChamfer()
{

}

void CChamfer::Execute()
{


}
