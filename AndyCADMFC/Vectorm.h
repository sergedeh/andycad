// Vectorm.h: interface for the CVectorm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORM_H__7935573B_1482_412F_94C8_5CB64AD461D0__INCLUDED_)
#define AFX_VECTORM_H__7935573B_1482_412F_94C8_5CB64AD461D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CVector.h"


class CVectorm : public CVector  
{
public:
	float x,y,z;
	CVectorm();
	virtual ~CVectorm();


CVectorm(const CVectorm &a) : x(a.x), y(a.y), z(a.z) {}
// Construct given three values

CVectorm(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
// Standard object maintenance
// Assignment. We adhere to C convention and
// return reference to the lvalue

CVectorm &operator =(const CVectorm &a) {
x = a.x; y = a.y; z = a.z;
return *this;
}

// Check for equality
bool operator ==(const CVectorm &a) const {
return x==a.x && y==a.y && z==a.z;
}

bool operator !=(const CVectorm &a) const {
return x!=a.x || y!=a.y || z!=a.z;
}
// Vector operations
// Set the vector to zero

void zero() { x = y = z = 0.0f; }
// Unary minus returns the negative of the vector

CVectorm operator -() const { return CVectorm(-x,-y,-z); }
// Binary + and - add and subtract vectors

CVectorm operator +(const CVectorm &a) const {
return CVectorm(x + a.x, y + a.y, z + a.z);
}

CVectorm operator -(const CVectorm &a) const {
return CVectorm(x - a.x, y - a.y, z - a.z);
}

// Multiplication and division by scalar
CVectorm operator *(float a) const 
{
return CVectorm(x*a, y*a, z*a);
}

CVectorm operator /(float a) const {
float oneOverA = 1.0f / a; // NOTE: no check for divide by zero here
return CVectorm(x*oneOverA, y*oneOverA, z*oneOverA);
}

// Combined assignment operators to conform to
// C notation convention
CVectorm &operator +=(const CVectorm &a) {
x += a.x; y += a.y; z += a.z;
return *this;
}

CVectorm &operator -=(const CVectorm &a) {
			x -= a.x; y -= a.y; z -= a.z;
			return *this;
			}
			CVectorm &operator *=(float a) {
			x *= a; y *= a; z *= a;
			return *this;
			}
			CVectorm &operator /=(float a) {
			float oneOverA = 1.0f / a;
			x *= oneOverA; y *= oneOverA; z *= oneOverA;
			return *this;
}


// Normalize the vector
void normalize() 
{
	float magSq = x*x + y*y + z*z;
	if (magSq > 0.0f) { // check for divide-by-zero
	float oneOverMag = 1.0f / sqrt(magSq);
	x *= oneOverMag;
	y *= oneOverMag;
	z *= oneOverMag;
}
}
// Vector dot product. We overload the standard
// multiplication symbol to do this
float operator *(const CVectorm &a) const {
return x*a.x + y*a.y + z*a.z;
}
};
/////////////////////////////////////////////////////////////////////////////
//
// Nonmember functions
//
/////////////////////////////////////////////////////////////////////////////
// Compute the magnitude of a vector
inline float vectorMag(const CVectorm &a) {
return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
// Compute the cross product of two vectors
inline CVectorm crossProduct(const CVectorm &a, const CVectorm &b) {
return CVectorm(
a.y*b.z - a.z*b.y,
a.z*b.x - a.x*b.z,
a.x*b.y - a.y*b.x
);
}
// Scalar on the left multiplication, for symmetry
inline CVectorm operator *(float k, const CVectorm &v) {
return CVectorm(k*v.x, k*v.y, k*v.z);
}
// Compute the distance between two points
inline float distance(const CVectorm &a, const CVectorm &b) {
float dx = a.x - b.x;
float dy = a.y - b.y;
float dz = a.z - b.z;
return sqrt(dx*dx + dy*dy + dz*dz);
}


/////////////////////////////////////////////////////////////////////////////
//
// Global variables
//
/////////////////////////////////////////////////////////////////////////////
// We provide a global zero vector constant
extern const CVectorm kZeroVector;

#endif // !defined(AFX_VECTORM_H__7935573B_1482_412F_94C8_5CB64AD461D0__INCLUDED_)
