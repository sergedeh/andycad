// Quaternion.cpp: implementation of the CQuaternion class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Quaternion.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuaternion::CQuaternion()
{

}

CQuaternion::~CQuaternion()
{

}

	void operator -(CQuaternion q) {q.n=-q.n;q.w=-q.w;}
	CQuaternion CQuaternion::operator*(float w1){return CQuaternion(n*w1,w*w1);}
	CQuaternion CQuaternion::operator/(float w1){return CQuaternion(n/w1,w/w1);}
	float absc(CQuaternion q) {return sqrt(pow(q.w,2)+pow(absc(q.n),2));}
	CQuaternion conjug(CQuaternion q){ return CQuaternion(-q.n,q.w);};
	CQuaternion Inv(CQuaternion q){return CQuaternion(conjug(q)/absc(q));};
	CQuaternion operator *(CQuaternion q1,CQuaternion q2) {return CQuaternion(q2.n*q1.w+q1.n*q2.w+q2.n*q1.n,q1.w*q2.w-q1.n.dot(q2.n));}
	CQuaternion argu(CQuaternion q1,CQuaternion q2) {return CQuaternion(Inv(q1)*q2);}
//	CQuaternion operator +(CQuaternion q1,CQuaternion q2) {return CQuaternion(q1.Inv(q1)*q2);}
	float dot(CQuaternion q1,CQuaternion q2){ return (q1.w*q2.w+q1.n.dot(q2.n));}
	CQuaternion log(CQuaternion q) {return CQuaternion(q.n*q.w,0);}
	CQuaternion exp(CQuaternion q) {return CQuaternion(q.n*sin(q.w),cos(q.w));} 
	CQuaternion pow(CQuaternion q,float w){return exp(log(q)*w);}
