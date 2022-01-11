//
//  CDimText.cpp
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CDimText.h"
// DimText.cpp: implementation of the CDimText class.
//
//////////////////////////////////////////////////////////////////////

int CDimText::precision_type=1;
int CDimText::aprecision_type=1;
string CDimText::style="linear-meter";
string CDimText::astyle="angle-degree";
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimText::CDimText()
{
	precision="%.2f";
}
void CDimText::initText(string _style,CDC* hdc,CVector v,float u)
{
	string _number;
/*	if((_style!="linear-meter")&&(_style!="radius-meter")&&(_style!="diameter-meter"))
	{
        if(astyle=="angle-degree")
        {
            u=(360*u)/(2*pi);
            if(aprecision_type==1)
            {
                _number.Format(_T("%.0f"),u);
            }else
                if(aprecision_type==2)
                {
                    _number.Format(_T("%.1f"),u);
                }else
                    if(aprecision_type==3)
                    {
                        _number.Format(_T("%.2f"),u);
                    }
            _number=_number+_T(" deg");
            assign(hdc,v,_number);
        }else
            if(astyle=="angle-radian")
            {
                if(aprecision_type==1)
                {
                    _number.Format(_T("%.0f"),u);
                }else
                    if(aprecision_type==2)
                    {
                        _number.Format(_T("%.1f"),u);
                    }else
                        if(aprecision_type==3)
                        {
                            _number.Format(_T("%.2f"),u);
                        }else
                            if(aprecision_type==4)
                            {
                                _number.Format(_T("%.3f"),u);
                            }else
                                if(aprecision_type==5)
                                {
                                    _number.Format(_T("%.4f"),u);
                                }
                _number=_number+_T(" r");
                assign(hdc,v,_number);
            }
	}else
	{
        if(style=="linear-meter")
        {
            u=u/1000;
            if(precision_type==1)
            {
                _number.Format(_T("%.0f"),u);
            }else
                if(precision_type==2)
                {
                    _number.Format(_T("%.1f"),u);
                }else
                    if(precision_type==3)
                    {
                        _number.Format(_T("%.2f"),u);
                    }else
                        if(precision_type==4)
                        {
                            _number.Format(_T("%.3f"),u);
                        }else
                            if(precision_type==5)
                            {
                                _number.Format(_T("%.4f"),u);
                            }
            _number=_number+_T(" m");
            assign(hdc,v,_number);
        }else
            if(style=="linear-centimeter")
            {
                u=u/10;
                if(precision_type==1)
                {
                    _number.Format(_T("%.0f"),u);
                }else
                    if(precision_type==2)
                    {
                        _number.Format(_T("%.1f"),u);
                    }else
                        if(precision_type==3)
                        {
                            _number.Format(_T("%.2f"),u);
                        }
                _number=_number+_T(" cm");
                assign(hdc,v,_number);
            }else
                if(style=="linear-millimeter")
                {
                    if(precision_type==1)
                    {
                        _number.Format(_T("%.0f"),u);
                    }else
                        if(precision_type==2)
                        {
                            _number.Format(_T("%.1f"),u);
                        }
                    _number=_number+_T(" mm");
                    assign(hdc,v,_number);
                }else
                    if((style=="linear-feet")||(_style=="engineering"))
                    {
                        if(precision_type==1)
                        {
                            _number.Format(_T("%.0f"),u);
                        }else
                            if(precision_type==2)
                            {
                                _number.Format(_T("%.1f"),u);
                            }else
                                if(precision_type==3)
                                {
                                    _number.Format(_T("%.2f"),u);
                                }else
                                    if(precision_type==4)
                                    {
                                        _number.Format(_T("%.3f"),u);
                                    }
                        _number=_number+_T(" \'");
                        assign(hdc,v,_number);
                    }else
                        if(style=="linear-inch")
                        {
                            if(precision_type==1)
                            {
                                _number.Format(_T("%.0f"),u);
                            }else
                                if(precision_type==2)
                                {
                                    _number.Format(_T("%.1f"),u);
                                }else
                                    if(precision_type==3)
                                    {
                                        _number.Format(_T("%.2f"),u);
                                    }
                            _number=_number+_T(" \"");
                            assign(hdc,v,_number);
                        }
        if(_style=="radius-meter")
        {
            //		_number.Format(precision,u);
            _number=_T("R ") + _number;//+ _T(" m");;
            assign(hdc,v,_number);
        }else
            if(_style=="diameter-meter")
            {
                //		_number.Format(precision,u);
                _number=_T("D ") + _number;//+ _T(" m");;
                assign(hdc,v,_number);
            }
	}*///*****************
}

CDimText::~CDimText()
{
    
}
