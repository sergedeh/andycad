// Constraint.h: interface for the CConstraint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSTRAINT_H__07EA32AB_F348_4E16_84DF_96093D463F0A__INCLUDED_)
#define AFX_CONSTRAINT_H__07EA32AB_F348_4E16_84DF_96093D463F0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CVector.h"
class CFigure;
class CConstraint  
{
public:
	bool UpdateEdgeToPerpendicular(CFigure* _f1);
	void EdgeToPerpendicular(CFigure* _f1, float _i1, CFigure* _f2, float _i2);
	void EdgeToVertical(CFigure* _f1, float _i1);
	bool UpdateEdgeToVertical(CFigure* _f1);
	bool UpdateEdgeToHorizontal(CFigure* _f1);
	bool UpdateEdgetoEdge(CFigure* _f1);
	bool UpdatePointtoPoint(CFigure* _f1);
	CConstraint(CFigure * _f1,CFigure * _f2);
	virtual ~CConstraint();
	void EdgeToHorizontal(CFigure* _f1, float _i1);
	void EdgeToEdge(CFigure* _f1, float _i1, CFigure* _f2, float _i2);
	void PointToPoint(CFigure* _f1,float _i1,CFigure* _f2,float _i2);
    bool Update(CFigure* _f1);
	bool done;
private:
	CFigure* f1,*f2;
	float i1,i2,du,da;
	CVector v,v1,v2,vedge10,vedge11,vedge20,vedge21;
	int type;
};

#endif // !defined(AFX_CONSTRAINT_H__07EA32AB_F348_4E16_84DF_96093D463F0A__INCLUDED_)
