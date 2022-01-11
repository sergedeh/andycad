//
//  CRay.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//
#include "pch.h"
#include "CRay.h"
// Ray.cpp: implementation of the CRay class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRay::CRay()
{
    
}

CRay::~CRay()
{
    
}
void CRay::setPara()
{
	p0=porg;
	d=phead-porg;
}

CVector CRay::Intersect(CRay l)
{
	setPara();
	l.setPara();
	CVector op=l.d*d;
	double f=op.absc(op);
	f=f*f;
    
	if(f<1E-10)
	{
		op.x=1E-10;
		op.y=1E-10;
		return op;
	}
	else
	{
		double j=((l.p0-p0)*l.d).dot(d*l.d);
		if(((j<1E-10)&&(j>0))||((j<0)&&(j>-1E-10)) )
		{
			j=0;
		}
		j=j/f;
		op=p0+d*j;
		
        
		if(segment)
		{
            CVector p=phead+porg;
            p=p/2;
            CVector v1=phead-p;
            CVector v3=op-p;
            float i1=absc(v1);
            float i2=absc(v3);
			if(i1+5>=i2)
			{
				if(l.segment)
				{
					p=l.phead+l.porg;
					p=p/2;
					v1=l.phead-p;
					v3=op-p;
					i1=absc(v1);
					i2=absc(v3);
					if(i1+5>=i2)
						return op;
					else
					{
						op.x=1E-10;
						op.y=1E-10;
						return op;
					}
				}
				else
					return op;
                
			}
			else
			{
				op.x=1E-10;
				op.y=1E-10;
				return op;
			}
            
		}
		return op;
	}
    
}

CPoint CRay::Intersectp(CRay l)
{
	setPara();
	l.setPara();
	CPoint po;
	CVector op=l.d*d;
	double f=op.absc(op);
	f=f*f;
    
	if(f<1E-10)
	{
		po.x=1E5;
		po.y=1E5;
        
		return po;
	}
	else
	{
		double j=((l.p0-p0)*l.d).dot(d*l.d);
		if(((j<1E-10)&&(j>0))||((j<0)&&(j>-1E-10)) )
		{
			j=0;
		}
		j=j/f;
		op=p0+d*j;
		
        
		if(segment)
		{
            CVector p=phead+porg;
            p=p/2;
            CVector v1=phead-p;
            CVector v3=op-p;
            float i1=absc(v1);
            float i2=absc(v3);
			if(i1>=i2)
			{
                /*		if((((porg.x-op.x<=1E-15)&&(op.x-phead.x<=1E-15))||\
                 ((phead.x-op.x<=1E-15)&&(op.x-porg.x<=1E-15)))&&\
                 (((porg.y-op.y<=1E-15)&&(op.y-phead.y<=1E-15))||\
                 ((phead.y-op.y<=1E-15)&&(op.y-porg.y<=1E-15)))&&\
                 (((porg.z-op.z<=1E-15)&&(op.z-phead.z<=1E-15))||\
                 ((phead.z-op.z<=1E-15)&&(op.z-porg.z<=1E-15))))
                 {*/
				return CPoint(op.x,op.y);
			}
			else
			{
				op.x=1E5;
				op.y=1E5;
				return CPoint(op.x,op.y);
			}
            
		}
		return CPoint(op.x,op.y);
	}
    
}


float CRay::getPara(CVector v)
{
	setPara();
	float t;
    
	t=d.dot(v-p0)/v.absc(d);
    
	return t;
}

void CRay::assign(CVector begin, CVector end)
{
	segment=true;
	porg=begin;
	phead=end;
}

CVector CRay::getclosestPoint(CVector v)
{
	setPara();
	float t;
    
    //	t=d.dot(v-p0)/v.absc(d);
	CVector v1=d/v.absc(d);
	t=v1.dot(v-p0);
    
	CVector m=porg+v1*t;
    
	return m;
    
}


