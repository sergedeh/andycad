//
//  CCommand.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CCommand__
#define __testcommand__CCommand__

#include <iostream>
// Command.h: interface for the CCommand class.
//
//////////////////////////////////////////////////////////////////////
class CCommand
{
public:
	virtual void Execute() {};
	CCommand();
	virtual ~CCommand();
    
};

#endif /* defined(__testcommand__CCommand__) */
