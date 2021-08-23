// Translate.h: interface for the CTranslate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATE_H__B539E288_6EF2_443B_931F_3A13A27D5AC9__INCLUDED_)
#define AFX_TRANSLATE_H__B539E288_6EF2_443B_931F_3A13A27D5AC9__INCLUDED_

#include "vector.h"
#include<vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;

class CTransform  
{
public:



	void setUnitvec(CVector vx, CVector vy);
	double getAngle();
	void setAngle(double angle);
	CPoint getRotateCenter();
	CPoint mirror(CPoint point);
	void rotateend(CPoint &point, CPoint valeur);
	void scale(CVector vector);
	void Translate(CVector mouseVect);
	
	CTransform();
	virtual ~CTransform();
	CVector rotateCenter;
	CVector prevrotateCenter;
private:

	int scaleFactor;
	double anglerot;
	CVector Vtranslate;
	

};


#endif // !defined(AFX_TRANSLATE_H__B539E288_6EF2_443B_931F_3A13A27D5AC9__INCLUDED_)
