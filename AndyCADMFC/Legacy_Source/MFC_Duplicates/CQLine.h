//
//  CQLine.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CQLine__
#define __testcommand__CQLine__

#include <iostream>
// QLine.h: interface for the CQLine class.
//
//////////////////////////////////////////////////////////////////////


#include "cLine.h"
using namespace std;
class CQLine : public CLine
{
public:
	void setstyle(string s);
	long Readfile(fstream &file);
	void openfile(fstream &file);
	void savefile(fstream &file);
	CQLine();
	CQLine(fstream &file);
	~CQLine();
	void polystate(CVector pos);
	bool getCharge();
	void setMove(bool mv,CVector pos);
	bool draw(bool fPrevLine, CDC *hdc,CVector point);
	void draw(CDC *hdc);
	friend class CInter;
protected:
	CVector prevpos;
	string style;
    
};

#endif /* defined(__testcommand__CQLine__) */
