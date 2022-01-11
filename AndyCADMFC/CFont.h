//
//  CFont.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CFont__
#define __testcommand__CFont__

#include <iostream>
#include <map>
//#include "CGPoint.h"
#include "CFigure.h"
using namespace std;
class CArchive
{
    
};
class CTxtED
{
    
};
class CFont
{
    
};
struct LOGFONT {
    
};
struct TEXTMETRIC {
    
};
struct ABCFLOAT {
    
};
struct CHARFORMAT {
    
};
struct ABC {
    
};
struct FSTYLE {
    
};
struct mytext2
{
    CFont* f;
    CFont*pf;
    char c;
    CGPoint v;
    bool s;
};
struct myfont
{
    TEXTMETRIC tm;
    map<char,ABCFLOAT> abc;
    LOGFONT* pf;
    COLORREF col;
};

#endif /* defined(__testcommand__CFont__) */
