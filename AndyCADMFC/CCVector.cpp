//
//  CCVector.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//
#include "pch.h"
#include "CCVector.h"
// CVector.cpp: implementation of the CCVector class.
//
//////////////////////////////////////////////////////////////////////


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
long CCVector::Readfile(CFile &file)
{
	file.Seek(sizeof(b),CFile::current);
	file.Seek(sizeof(b),CFile::current);
	return file.Seek(sizeof(b),CFile::current);
}
