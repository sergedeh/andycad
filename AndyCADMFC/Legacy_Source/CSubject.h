//
//  CSubject.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSubject__
#define __testcommand__CSubject__

#include <iostream>
// Subject.h: interface for the CSubject class.
//
//////////////////////////////////////////////////////////////////////

#include <vector>
//#include "CObserver.h"
//#include "CCadView.h"

using namespace std;
class CObserver;
class CCadView;
class CSubject
{
public:
	virtual void Unregister(CObserver *o);
	void setview(CCadView *v);
	virtual void RegisterInterest(CObserver *obs){observers.push_back(obs);};
	CSubject();
	~CSubject();
protected:
	vector<CObserver* > observers;
	CCadView* view;
};

#endif /* defined(__testcommand__CSubject__) */
