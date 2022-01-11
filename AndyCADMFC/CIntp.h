//
//  CIntp.h
//  testcommand
//
//  Created by Serge Deh on 10/20/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CIntp__
#define __testcommand__CIntp__

#include <iostream>
// IntP.h: interface for the CIntP class.
//
//////////////////////////////////////////////////////////////////////

#include "cproperty.h"

class CIntP : public CProperty
{
public:
	int getValue();
	CIntP(string n, int p);
	void setValue(CIntP* v);
	void getValue(CIntP* p);
    
	CIntP();
	virtual ~CIntP();
private:
	int s;
    
};

#endif /* defined(__testcommand__CIntp__) */
