//
//  CAABB.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CAABB__
#define __testcommand__CAABB__

#include <iostream>
#include "CVectorm.h"
class CVector;
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
	void add(CPoint p);
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

#endif /* defined(__testcommand__CAABB__) */
