// AABB.h: interface for the CAABB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AABB_H__E96947B3_4CEA_412B_A280_F482AF5C899D__INCLUDED_)
#define AFX_AABB_H__E96947B3_4CEA_412B_A280_F482AF5C899D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <stdlib.h>
#include <assert.h>


#include "Vector.h"
#include "Vectorm.h"
#include "matrix1.h"
//#include "eqmatrix.h"

//class CEQMatrix;

class CAABB 
{
public:
	CVector getclosestOpCorner(CVector p);
	bool is_stabbed(CVector v);
	double diagonal();
	double volume();
	operator CRect();
	void inflate(float radius);
	bool operator ==(CAABB* b) {return (min==b->min)&&(max==b->max);}
	void add(CPoint& p);
	bool ccontainpts(CPoint p);
	CVector getParam(CVector p);
	void draw(CDC* hdc);
   
	CVector min, max;
	CVector size() {
		return max-min;
	};
/*	float xsize(){x.max -x.min;}
	float ysize(){y.max -y.min;}
	float zsize(){z.max -z.min;}
*/
	CVector center(){return (min+max)*.5f;}

	CVector corner(int i) const ;

	void empty(); //empty the box

	void add(CVector &p); // add a point to the box
    void add(const CAABB &box); // add a AABB to the box



    bool isEmpty() const; //return true if box is empty;

	bool containpts(const CVector &p) const; //return true if box contain points;

	CVector closestPt(const CVector &p) const ; //closestpoit to this box;

//	bool intersectsphere(const CVector &center, float radius) const; //box intersect sphere

    float rayIntersect(const CVectorm &rayOrg, const CVectorm &rayDelta, CVectorm *returnNormal) const;
	
	int classifyPlane(CVector &n, float d) const;

	float intersectplane(CVector &n, float planeD, CVector &dyn) const;//dynamic intersection with plane

 

 bool intersectAABB(const CAABB &box2, CAABB *boxIntersect=0) const; //check for intersection of 2 AABB
 bool intersectAABB2(const CAABB &box2, CAABB *boxIntersect=0) const; //check for intersection of 2 AABB
 float intersectMovingAABB
		(
		const CAABB &stayingbox, 
		const CAABB &movingbox,
		CVector &d
		)const;


	CAABB();
	virtual ~CAABB();

};

#endif // !defined(AFX_AABB_H__E96947B3_4CEA_412B_A280_F482AF5C899D__INCLUDED_)

