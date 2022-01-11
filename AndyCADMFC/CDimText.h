//
//  CDimText.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CDimText__
#define __testcommand__CDimText__

#include <iostream>
// DimText.h: interface for the CDimText class.
//
//////////////////////////////////////////////////////////////////////

#include "cTextCad.h"

class CDimText : public CTextCad
{
public:
	void initText(string _style,CDC* hdc,CVector v,float u);
	CDimText();
	~CDimText();
	static string style,astyle;
	static int precision_type,aprecision_type;
private:
	string precision;
    
};


#endif /* defined(__testcommand__CDimText__) */
