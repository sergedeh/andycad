// CVector.cpp: implementation of the CCVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "CVector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CCVector::CCVector()
{

}*/

CCVector::~CCVector()
{

}

void CCVector::savefile(CFile &file)
{
	file.Write(&b,sizeof(b));
	file.Write(&g,sizeof(b));
	file.Write(&r,sizeof(b));

}

void CCVector::openfile(CFile &file)
{
	file.Read(&b,sizeof(b));
	file.Read(&g,sizeof(b));
	file.Read(&r,sizeof(b));
}
LONG CCVector::Readfile(CFile &file)
{
	file.Seek(sizeof(b),CFile::current);
	file.Seek(sizeof(b),CFile::current);
	return file.Seek(sizeof(b),CFile::current);
}
