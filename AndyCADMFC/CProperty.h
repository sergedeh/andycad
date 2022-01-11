//
//  CProperty.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CProperty__
#define __testcommand__CProperty__

#include <iostream>
// Property.h: interface for the CProperty class.
//
//////////////////////////////////////////////////////////////////////
#include <vector>
using namespace std;

class CProperty
{
public:
	virtual void getValue(CProperty* p) {};
	virtual void getValue(vector<CProperty*>& p) {};
	virtual void setValue(CProperty* v){};
	string getName();
	string getType();
	CProperty(string n) {name=n;};
	CProperty();
	virtual ~CProperty();
private:
	string name;
};

#endif /* defined(__testcommand__CProperty__) */
