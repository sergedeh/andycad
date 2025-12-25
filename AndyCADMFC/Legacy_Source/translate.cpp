// Translate.cpp: implementation of the CTranslate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Translate.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

void CTransform::Translate(CVector mouseVect)
{

/*	(*piterb).x+=mouseVect.x;
	(*piterb).y+=mouseVect.y;
	(*pitere).x+=mouseVect.x;
	(*pitere).y+=mouseVect.y;*/
	
}

//DEL CPoint CTransform::rotate(CPoint point, double angle)
//DEL {
//DEL 	complex<double> v(point.x,point.y),v1;
//DEL 
//DEL 	v1=polar(abs(v),arg(v)+angle);
//DEL 	point.x=v1.real();
//DEL 	point.y=v1.imag();
//DEL 	return point;
//DEL 	
//DEL }

void CTransform::scale(CVector vector)
{
//	point.x=point.x* vector.x;
//	point.y=point.y* vector.y;
	
}

void CTransform::rotateend(CPoint &point, CPoint valeur)
{
	double angleA=atan2(valeur.y,valeur.x);
	double angleA1=atan2(point.y,point.x);
	double angleA2=angleA-angleA1;

	point.x=point.x* cos(angleA2)+point.y*sin(angleA2);
	point.y=-point.x* sin(angleA2)+point.y*cos(angleA2);

}

CPoint CTransform::mirror(CPoint point)
{
/*		CVector VMain(PtsBegin,PtsEnd);
		CVector VpointB(PtsBegin,point);
			
		float angleA2=atan2(VMain.y,VMain.x)-atan2(VpointB.y,VpointB.x);
				
		point=rotate(VpointB,angleA2);*/
		return point;
}

//DEL void CTransform::setRotateCenter(CPoint point)
//DEL {
//DEL 	rotateCenter=point;
//DEL }

CPoint CTransform::getRotateCenter()
{
 return rotateCenter;
}



void CTransform::setAngle(double angle)
{
	anglerot=angle;

}

double CTransform::getAngle()
{
	return anglerot;
}

void CTransform::setUnitvec(CVector vx, CVector vy)
{
	

}

