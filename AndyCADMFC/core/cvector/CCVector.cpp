//
//  CCVector.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//
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

void CCVector::saveTo(ofstream &file)
{
	file.write(reinterpret_cast<const char*>(&b), sizeof(b));
	file.write(reinterpret_cast<const char*>(&g), sizeof(b));
	file.write(reinterpret_cast<const char*>(&r), sizeof(b));
}

void CCVector::loadFrom(ifstream &file)
{
	file.read(reinterpret_cast<char*>(&b), sizeof(b));
	file.read(reinterpret_cast<char*>(&g), sizeof(b));
	file.read(reinterpret_cast<char*>(&r), sizeof(b));
}
long CCVector::skipRead(ifstream &file)
{
	file.seekg(sizeof(double) * 3, std::ios::cur);
	return static_cast<long>(file.tellg());
}
