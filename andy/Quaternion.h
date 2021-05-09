// Quaternion.h: interface for the CQuaternion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUATERNION_H__D11EAD5F_574D_4E2F_A934_593597816253__INCLUDED_)
#define AFX_QUATERNION_H__D11EAD5F_574D_4E2F_A934_593597816253__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vector.h"
using namespace std;
class CQuaternion  
{
public:
	CQuaternion();
	CQuaternion(CVector v):n(v),w(0){};
	CQuaternion(CVector v,float angle):n(v),w(angle){};
	CQuaternion operator*(float w1);
	CQuaternion operator/(float w1);
	void setquat(CVector v,float angle){n=v*sin(angle/2);w=cos(angle/2); }
	virtual ~CQuaternion();
	CVector n;
	float w;

};
	void operator -(CQuaternion q);
	float absc(CQuaternion q);
	CQuaternion conjug(CQuaternion q);
	CQuaternion Inv(CQuaternion q);
	CQuaternion operator *(CQuaternion q1,CQuaternion q2);
	CQuaternion argu(CQuaternion q1,CQuaternion q2);
//	CQuaternion operator +(CQuaternion q1,CQuaternion q2);
	float dot(CQuaternion q1,CQuaternion q2);
	CQuaternion log(CQuaternion q);
	CQuaternion exp(CQuaternion q);
	CQuaternion pow(CQuaternion q,float w);

#endif // !defined(AFX_QUATERNION_H__D11EAD5F_574D_4E2F_A934_593597816253__INCLUDED_)
