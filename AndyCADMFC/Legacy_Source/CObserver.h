//
//  CObserver.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CObserver__
#define __testcommand__CObserver__

#include <iostream>
#include <string>
using namespace std;
// Observer.h: interface for the CObserver class.
//
//////////////////////////////////////////////////////////////////////

class CObserver
{
public:
	virtual void SendNotify(string s,void* param[7]){};
	CObserver();
	~CObserver();
    
};

#endif /* defined(__testcommand__CObserver__) */
