// CAABB.cpp: implemntation of the CAABB class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "AABB.h"
#include "Vector.h"
//#include "Vectorm.h"
#include "assert.h"
//#include "eulerangle.h"
//#include "rotationmatrix.h"
//#include "eqmatrix.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAABB::CAABB()
{
empty();
}

CAABB::~CAABB()
{

}
//Give the point on th box starting at p0 to p7
//An edge has (po p1 and p2)  => 3 points
CVector CAABB::corner(int i) const
{
	assert(i>=0);
	assert(i<=7);

	return CVector(
		(i&1)? max.x:min.x,
		(i&2)? max.y:min.y,
		(i&4)? max.z:min.z);
}

CVector CAABB::getclosestOpCorner(CVector p)
{
	if(pointinRegion(corner(0),p))
		return corner(3);
	else
	if(pointinRegion(corner(1),p))
		return corner(2);
	else
	if(pointinRegion(corner(2),p))
		return corner(1);
	else
	if(pointinRegion(corner(3),p))
		return corner(0);
	else
	if(pointinRegion((corner(0)+corner(1))/2,p))
		return (corner(3)+corner(2))/2;
	else
	if(pointinRegion((corner(3)+corner(2))/2,p))
		return (corner(1)+corner(0))/2;
	else
	if(pointinRegion((corner(1)+corner(3))/2,p))
		return (corner(2)+corner(0))/2;
	else
	if(pointinRegion((corner(2)+corner(0))/2,p))
		return (corner(1)+corner(3))/2;


}

void CAABB::empty()
{
	const float grossnum = 1E37f;
	min.x=min.y=min.z=grossnum;
	max.x=max.y=max.z=-grossnum;
};

void CAABB::add(CVector &p)
{

// Expand the box as necessary to contain the point.
if (p.x < min.x) min.x = p.x;
if (p.x > max.x) max.x = p.x;
if (p.y < min.y) min.y = p.y;
if (p.y > max.y) max.y = p.y;
if (p.z < min.z) min.z = p.z;
if (p.z > max.z) max.z = p.z;
}

void CAABB::add(const CAABB &box)
{
	if(box.min.x < min.x) min.x= box.min.x;
    if(box.max.x > max.x) max.x = box.max.x;
	if(box.min.y < min.y) min.y= box.min.y;
    if(box.max.y > max.y) max.y = box.max.y;
	if(box.min.z < min.z) min.z= box.min.z;
    if(box.max.z > max.z) max.z = box.max.z;

}


// Transform the box and compute the new CAABB. Remember, this always
// results in an CAABB that is at least as big as the origin, and it may be
// considerably bigger.

//DEL void CAABB::setTransformedBx(const CAABB &box, const CEQMatrix &m) {
//DEL // If we're empty, then bail
//DEL 	if (box.isEmpty()) 
//DEL 	{
//DEL 	empty();
//DEL 	return;
//DEL 	}
//DEL 	min = max = getTranslation(m);
//DEL 	// Examine each of the nine matrix elements
//DEL 	// and compute the new CAABB
//DEL 	if (m.m11 > 0.0f) {
//DEL 	min.x += m.m11 * box.min.x; max.x += m.m11 * box.max.x;
//DEL 	} else {
//DEL 	min.x += m.m11 * box.max.x; max.x += m.m11 * box.min.x;
//DEL 	}
//DEL 	if (m.m12 > 0.0f) {
//DEL 	min.y += m.m12 * box.min.x; max.y += m.m12 * box.max.x;
//DEL 	} else {
//DEL 	min.y += m.m12 * box.max.x; max.y += m.m12 * box.min.x;
//DEL 	}
//DEL 	if (m.m13 > 0.0f) {
//DEL 	min.z += m.m13 * box.min.x; max.z += m.m13 * box.max.x;
//DEL 	} else {
//DEL 	min.z += m.m13 * box.max.x; max.z += m.m13 * box.min.x;
//DEL 	}
//DEL 	if (m.m21 > 0.0f) {
//DEL 	min.x += m.m21 * box.min.y; max.x += m.m21 * box.max.y;
//DEL 	} else {
//DEL 	min.x += m.m21 * box.max.y; max.x += m.m21 * box.min.y;
//DEL 	}
//DEL 	if (m.m22 > 0.0f) {
//DEL 	min.y += m.m22 * box.min.y; max.y += m.m22 * box.max.y;
//DEL 	} else {
//DEL 	min.y += m.m22 * box.max.y; max.y += m.m22 * box.min.y;
//DEL 	}
//DEL 	if (m.m23 > 0.0f) {
//DEL 	min.z += m.m23 * box.min.y; max.z += m.m23 * box.max.y;
//DEL 	} else {
//DEL 	min.z += m.m23 * box.max.y; max.z += m.m23 * box.min.y;
//DEL 	}
//DEL 	if (m.m31 > 0.0f) {
//DEL 	min.x += m.m31 * box.min.z; max.x += m.m31 * box.max.z;
//DEL 	} else {
//DEL 	min.x += m.m31 * box.max.z; max.x += m.m31 * box.min.z;
//DEL 	}
//DEL 	if (m.m32 > 0.0f) {
//DEL 	min.y += m.m32 * box.min.z; max.y += m.m32 * box.max.z;
//DEL 	} else {
//DEL 	min.y += m.m32 * box.max.z; max.y += m.m32 * box.min.z;
//DEL 	}
//DEL 	if (m.m33 > 0.0f) {
//DEL 	min.z += m.m33 * box.min.z; max.z += m.m33 * box.max.z;
//DEL 	} else {
//DEL 	min.z += m.m33 * box.max.z; max.z += m.m33 * box.min.z;
//DEL 	}
//DEL }

// CAABB::isEmpty
// Return true if the box is empty
bool CAABB::isEmpty() const
{
	// Check if we're inverted on any axis
	return (min.x > max.x) || (min.y > max.y) || (min.z > max.z);
}


// Return true if the box contains a point
bool CAABB::containpts(const CVector &p) const
{
	// Check for overlap on each axis
	return
	(p.x >= min.x) && (p.x <= max.x) &&
	(p.y >= min.y) && (p.y <= max.y) &&
	(p.z >= min.z) && (p.z <= max.z);
}


// Return the closest point on this box to another point
CVector CAABB::closestPt(const CVector &p) const
{
	// "Push" p into the box on each dimension
	CVector r;
	if (p.x < min.x) {
	r.x = min.x;
	} else if (p.x > max.x) {
	r.x = max.x;
	} else {
	r.x = p.x;
	}
	if (p.y < min.y) {
	r.y = min.y;
	} else if (p.y > max.y) {
	r.y = max.y;
	} else {
	r.y = p.y;
	}
	if (p.z < min.z) {
	r.z = min.z;
	} else if (p.z > max.z) {
	r.z = max.z;
	} else {
	r.z = p.z;
	}
// Return it
return r;
}

/*
// Return true if we intersect a sphere. Uses Arvo's algorithm.
bool CAABB::intersectsphere(const CVectorm &center, float radius) const
{
	// Find the closest point on box to the point
	CVector closestPoint = closestPt(center);
	// Check if it's within range
	return distanceSquared(center, closestPoint) < radius*radius;
}*/

// Parametric intersection with a ray. Returns parametric point
// of intsersection in range 0...1 or a really big number (>1) if no
// intersection.

float CAABB::rayIntersect(
const CVectorm &rayOrg, // orgin of the ray
const CVectorm &rayDelta, // length and direction of the ray
CVectorm *returnNormal // optionally, the normal is returned
) const 
{
	// We'll return this huge number if no intersection
	const float kNoIntersection = 1e30f;
	// Check for point inside box, trivial reject, and determine parametric
	// distance to each front face
	bool inside = true;
	float xt, xn;
	if (rayOrg.x < min.x) {
	xt = min.x - rayOrg.x;
	if (xt > rayDelta.x) return kNoIntersection;
	xt /= rayDelta.x;
	inside = false;
	xn = -1.0f;
	} else if (rayOrg.x > max.x) {
	xt = max.x - rayOrg.x;
	if (xt < rayDelta.x) return kNoIntersection;
	xt /= rayDelta.x;
	inside = false;
	xn = 1.0f;
	} else {
	xt = -1.0f;
	}
	float yt, yn;
	if (rayOrg.y < min.y) {
	yt = min.y - rayOrg.y;
	if (yt > rayDelta.y) return kNoIntersection;
	yt /= rayDelta.y;
	inside = false;
	yn = -1.0f;
	} else if (rayOrg.y > max.y) {
	yt = max.y - rayOrg.y;
	if (yt < rayDelta.y) return kNoIntersection;
	yt /= rayDelta.y;
	inside = false;
	yn = 1.0f;
	} else {
	yt = -1.0f;
	}
	float zt, zn;
	if (rayOrg.z < min.z) {
	zt = min.z - rayOrg.z;
	if (zt > rayDelta.z) return kNoIntersection;
	zt /= rayDelta.z;
	inside = false;
	zn = -1.0f;
	} else if (rayOrg.z > max.z) {
	zt = max.z - rayOrg.z;
	if (zt < rayDelta.z) return kNoIntersection;
	zt /= rayDelta.z;
	inside = false;
	zn = 1.0f;
	} else {
	zt = -1.0f;
	}
	// Inside box?
	if (inside) 
	{
	  if (returnNormal != NULL) 
	  {
	   *returnNormal = -rayDelta;
    	returnNormal->normalize();
	  }
	return 0.0f;
	}
	// Select farthest plane - this is
	// the plane of intersection.
	int which = 0;
	float t = xt;
	if (yt > t) {
	which = 1;
	t = yt;
	}

	if (zt > t) {
	which = 2;
	t = zt;
	}
		switch (which) 
		{
		case 0: // intersect with yz plane
		{
		float y = rayOrg.y + rayDelta.y*t;
		if (y < min.y || y > max.y) return kNoIntersection;
		float z = rayOrg.z + rayDelta.z*t;
		if (z < min.z || z > max.z) return kNoIntersection;
		if (returnNormal != NULL) {
		returnNormal->x = xn;
		returnNormal->y = 0.0f;
		returnNormal->z = 0.0f;
		}
		} break;
		case 1: // intersect with xz plane
		{
		float x = rayOrg.x + rayDelta.x*t;
		if (x < min.x || x > max.x) return kNoIntersection;
		float z = rayOrg.z + rayDelta.z*t;
		if (z < min.z || z > max.z) return kNoIntersection;
		if (returnNormal != NULL) {
		returnNormal->x = 0.0f;
		returnNormal->y = yn;
		returnNormal->z = 0.0f;
		}
		} break;
		case 2: // intersect with xy plane
		{
		float x = rayOrg.x + rayDelta.x*t;
		if (x < min.x || x > max.x) return kNoIntersection;
		float y = rayOrg.y + rayDelta.y*t;
		if (y < min.y || y > max.y) return kNoIntersection;
		if (returnNormal != NULL) {
		returnNormal->x = 0.0f;
		returnNormal->y = 0.0f;
		returnNormal->z = zn;
		}
		} break;
		}
// Return parametric point of intersection
return t;
}

int CAABB::classifyPlane(CVector &n, float d) const {
// Inspect the normal and compute the minimum and maximum
// D values.
	  float minD, maxD;
			if (n.x > 0.0f) 
			{
			minD = n.x*min.x; maxD = n.x*max.x;
			} 
			else 
			{
			minD = n.x*max.x; maxD = n.x*min.x;
			}
			if (n.y > 0.0f)
			{
			minD += n.y*min.y; maxD += n.y*max.y;
			} else
			{
			minD += n.y*max.y; maxD += n.y*min.y;
			}
			if (n.z > 0.0f)
			{
			minD += n.z*min.z; maxD += n.z*max.z;
			} else 
			{
			minD += n.z*max.z; maxD += n.z*min.z;
			}
			// Check if completely on the front side of the plane
			if (minD >= d) 
			{
			return +1;
			}
			// Check if completely on the back side of the plane
			if (maxD <= d)
			{
			return -1;
			}
// We straddle the plane
return 0;
}





// CAABB::intersectPlane
//
// Perform dynamic CAABB-plane intersection test.
// Only intersections with the front side of the plane are detected
float CAABB::intersectplane(
						CVector &n,
						float planeD,
						 CVector &dyn
						) const 
{
		// Make sure they are passing in normalized vectors
		assert(fabs(n.dot(n) - 1.0) < .01);
		assert(fabs(dyn.dot(dyn) - 1.0) < .01);
		// We'll return this huge number if no intersection
		const float kNoIntersection = 1e30f;
		// Compute glancing angle. Make sure we are moving toward
		// the front of the plane.
		float dot = n.dot(dyn);
		if (dot >= 0.0f)
		{
		return kNoIntersection;
		}
		// Inspect the normal and compute the minimum and maximum
		// D values. minD is the D value of the "frontmost" corner point
		float minD, maxD;
		if (n.x > 0.0f) 
		{
		minD = n.x*min.x; maxD = n.x*max.x;
		}
		else 
		{
		minD = n.x*max.x; maxD = n.x*min.x;
		}
		if (n.y > 0.0f) 
		{
		minD += n.y*min.y; maxD += n.y*max.y;
		} 
		else 
		{
		minD += n.y*max.y; maxD += n.y*min.y;
		}
		if (n.z > 0.0f) {
		minD += n.z*min.z; maxD += n.z*max.z;
		} 
		else
		{
		minD += n.z*max.z; maxD += n.z*min.z;
		}
		// Check if we're already completely on the other
		// side of the plane
		if (maxD <= planeD) 
		{
		return kNoIntersection;
		}

		// Perform standard ray trace equation using the
		// frontmost corner point
		float t = (planeD - minD) / dot;
		// Were we already penetrating?
		if (t < 0.0f)
		{
		return 0.0f;
		}
		// Return it. If > l, then we didn't hit in time. That's
		// the condition that the caller should be checking for.
		return t;
}



/////////////////////////////////////////////////////////////////////////////
//
// Global nonmember code
//
/////////////////////////////////////////////////////////////////////////////

bool CAABB::intersectAABB(const CAABB &box2, CAABB *boxIntersect) const //check for intersection of 2 AABB
{
// Check for no overlap
if (min.x > box2.max.x) return false;
if (max.x < box2.min.x) return false;
if (min.y > box2.max.y) return false;
if (max.y < box2.min.y) return false;
if (min.z > box2.max.z) return false;
if (max.z < box2.min.z) return false;
// We have overlap. Compute CAABB of intersection, if they want it
if (boxIntersect != NULL) {
boxIntersect->min.x = max(min.x, box2.min.x);
boxIntersect->max.x = min(max.x, box2.max.x);
boxIntersect->min.y = max(min.y, box2.min.y);
boxIntersect->max.y = min(max.y, box2.max.y);
boxIntersect->min.z = max(min.z, box2.min.z);
boxIntersect->max.z = min(max.z, box2.max.z);
}
// They intersected
return true;

}
bool CAABB::intersectAABB2(const CAABB &box2, CAABB *boxIntersect) const //check for intersection of 2 AABB
{
// Check for no overlap
if (min.x > box2.max.x) return false;
if (max.x < box2.min.x) return false;
if (min.y > box2.max.y) return false;
if (max.y < box2.min.y) return false;
// We have overlap. Compute CAABB of intersection, if they want it
if (boxIntersect != NULL) {
boxIntersect->min.x = max(min.x, box2.min.x);
boxIntersect->max.x = min(max.x, box2.max.x);
boxIntersect->min.y = max(min.y, box2.min.y);
boxIntersect->max.y = min(max.y, box2.max.y);
boxIntersect->min.z = max(min.z, box2.min.z);
boxIntersect->max.z = min(max.z, box2.max.z);
}
// They intersected
return true;

}

/*
// intersectMovingAABB
float CAABB::intersectMovingAABB(const CAABB &stayingbox, const CAABB &movingbox,  CVector &d)
{
	// We'll return this huge number if no intersection
	const float kNoIntersection = 1e30f;
	// Initialize interval to contain all the time under consideration
	float tEnter = 0.0f;
	float tLeave = 1.0f;

	// Check x-axis
	if (d.x == 0.0f) {
	// Empty or infinite inverval on x
			if (
			(stayingbox.min.x >= movingbox.max.x) ||
			(stayingbox.max.x <= movingbox.min.x)
			) {
			// Empty time interval so no intersection
			return kNoIntersection;
			}
	// Inifinite time interval - no update necessary
	} 
	else
	{
	// Divide once
	float oneOverD = 1.0f / d.x;
	// Compute time value when they begin and end overlapping
	float xEnter = (stayingbox.min.x - movingbox.max.x) * oneOverD;
	float xLeave = (stayingbox.max.x - movingbox.min.x) * oneOverD;
	// Check for interval out of order
		if (xEnter > xLeave) 
		{
		swap(xEnter, xLeave);
		}
	// Update interval
	if (xEnter > tEnter) tEnter = xEnter;
	if (xLeave < tLeave) tLeave = xLeave;
	// Check if this resulted in empty interval
			if (tEnter > tLeave)
			{
				return kNoIntersection;
			}
	}
	// Check y-axis
	if (d.y == 0.0f) 
	{
	// Empty or infinite inverval on y
	if (
	(stayingbox.min.y >= movingbox.max.y) ||
	(stayingbox.max.y <= movingbox.min.y))
			{
			// Empty time interval, so no intersection
			return kNoIntersection;
			}
	// Infinite time interval - no update necessary
	} 
	else 
	{
	// Divide once
	float oneOverD = 1.0f / d.y;
	// Compute time value when they begin and end overlapping
	float yEnter = (stayingbox.min.y - movingbox.max.y) * oneOverD;
	float yLeave = (stayingbox.max.y - movingbox.min.y) * oneOverD;
	// Check for interval out of order
	if (yEnter > yLeave)
		 {
		swap(yEnter, yLeave);
		}
		// Update interval
		if (yEnter > tEnter) tEnter = yEnter;
		if (yLeave < tLeave) tLeave = yLeave;
		// Check if this resulted in empty interval
		if (tEnter > tLeave) 
		{
		return kNoIntersection;
		}
	}
	// Check z-axis
	if (d.z == 0.0f) 
	{
		// Empty or infinite inverval on z
		if (
		(stayingbox.min.z >= movingbox.max.z) ||
		(stayingbox.max.z <= movingbox.min.z)
		)
			 {
			// Empty time interval, so no intersection
				return kNoIntersection;
				}
	// Infinite time interval - no update necessary
	}
	 else 
	{
	// Divide once
		float oneOverD = 1.0f / d.z;
		// Compute time value when they begin and end overlapping
		float zEnter = (stayingbox.min.z - movingbox.max.z) * oneOverD;
		float zLeave = (stayingbox.max.z - movingbox.min.z) * oneOverD;
		// Check for interval out of order
		if (zEnter > zLeave) 
		{
		swap(zEnter, zLeave);
		}
		// Update interval
		if (zEnter > tEnter) tEnter = zEnter;
		if (zLeave < tLeave) tLeave = zLeave;
		// Check if this resulted in empty interval
			if (tEnter > tLeave) 
			{
			return kNoIntersection;
			}
		}
	// OK, we have an intersection. Return the parametric point in time
	// where the intersection occurs
	return tEnter;
}			
*/

void CAABB::draw(CDC *hdc)
{
//	int old=hdc->SetROP2(R2_NOTXORPEN);
	CPen pen;
	pen.CreatePen(PS_COSMETIC,3,RGB(52,120,221));
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(NULL);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->MoveTo(corner(0));
	CPoint p0(corner(0));
	hdc->TextOut(p0.x,p0.y,"0");
	
	hdc->LineTo(corner(1));
	CPoint p1(corner(1));
	hdc->TextOut(p1.x,p1.y,"1");
	
	hdc->LineTo(corner(3));
	CPoint p3(corner(3));
	hdc->TextOut(p3.x,p3.y,"3");
	
	hdc->LineTo(corner(2));
	CPoint p2(corner(2));
	hdc->TextOut(p2.x,p2.y,"2");
	
	hdc->LineTo(corner(0));
	if(corner(0)!=corner(4))
	{
	hdc->LineTo(corner(4));
	CPoint p4(corner(4));
	hdc->TextOut(p4.x,p4.y,"4");

	hdc->LineTo(corner(5));
	CPoint p5(corner(5));
	hdc->TextOut(p5.x,p5.y,"5");

	hdc->MoveTo(corner(2));
	hdc->LineTo(corner(6));
	CPoint p6(corner(6));
	hdc->TextOut(p6.x,p6.y,"6");

	hdc->LineTo(corner(7));
	CPoint p7(corner(7));
	hdc->TextOut(p7.x,p7.y,"7");

	hdc->LineTo(corner(3));
	hdc->MoveTo(corner(4));
	hdc->LineTo(corner(6));
	hdc->LineTo(corner(7));
	hdc->LineTo(corner(5));
	hdc->LineTo(corner(4));
	}
//	hdc->SetROP2(old);    			
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
}
// Give parametric value of a point relative to the box
CVector CAABB::getParam(CVector p)
{
	CVector v;
	if(max.x!=min.x)
		v.x=(p.x-min.x)/(max.x-min.x);
	else v.x=1E15;
	if(max.y!=min.y)
		v.y=1-((p.y-min.y)/(max.y-min.y));
	else v.y=1E15;
	if(max.z!=min.z)
		v.z=(p.z-min.z)/(max.z-min.z);
	else v.z=1E15;
	return v;
}

bool CAABB::ccontainpts(CPoint p)
{
	// Check for overlap on each axis
	CAABB po;
	po.empty();
	po.add(CPoint(corner(0)));
	po.add(CPoint(corner(1)));
	po.add(CPoint(corner(2)));
	po.add(CPoint(corner(3)));
	po.add(CPoint(corner(4)));
	po.add(CPoint(corner(5)));
	po.add(CPoint(corner(6)));
	po.add(CPoint(corner(7)));
	CVector vp;
	vp.x=p.x;
	vp.y=p.y;
	vp.z=0;
	return po.containpts(vp);
}

void CAABB::add(CPoint &p)
{
// Expand the box as necessary to contain the point.
	min.z=0;max.z=0;
if (p.x < min.x) min.x = p.x;
if (p.x > max.x) max.x = p.x;
if (p.y < min.y) min.y = p.y;
if (p.y > max.y) max.y = p.y;
}

void CAABB::inflate(float radius)
{
	max.x+=radius;
	max.y+=radius;
	max.z+=radius;
	min.x-=radius;
	min.y-=radius;
	min.z-=radius;
}

CAABB::operator CRect()
{
	return CRect(min,max);
}

double CAABB::volume()
{
	return (max.x -min.x)*(max.y-min.y)*(max.z-min.z);
}

double CAABB::diagonal()
{
  double x, y, z;

  x = max.x - min.x;
  y = max.y - min.y;
  z = max.z - min.z;

  return x*x + y*y + z*z;

}

bool CAABB::is_stabbed(CVector v)
{
  if (v.x > min.x ||
      v.y < max.y || v.y > min.y ||
      v.z < max.z || v.z > min.z)
    return false;
  return true;

}
