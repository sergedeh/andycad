// Plane.cpp: implementation of the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Plane.h"
#include "ray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlane::CPlane()
{

}

CPlane::~CPlane()
{

}

CPlane::CPlane(CVector i,CVector j,CVector k):p1(i),p2(j),p3(k)
{
	CVector e3=p2-p1;
	CVector e2=p3-p2;
	double jj=e2.absc(e3*e2);
	if(jj!=0)
	{
		n=(e3*e2)/jj;
		d=n.dot(p1);
	}
	computeCircum();
}
CPlane::CPlane(CVector p,CVector nn)
{
	n=nn/n.absc(nn);
	d=p.dot(n); 
}
CPlane::CPlane(float p,CVector nn)
{
	n=nn/n.absc(nn);
	d=p; 
}

double CPlane::dist_to_point(CVector p)
{
 return n.dot(p)-d;
}

CVector CPlane::closest_point(CVector v)
{
  return v+n*(d-v.dot(n));
}
CVector CPlane::getBarycent(CVector p)
{
	CVector e1=p3-p2;
	CVector e2=p1-p3;
	CVector e3=p2-p1;

	CVector d1=p-p1;
	CVector d2=p-p2;
	CVector d3=p-p3;
	
	double g=(e1*e2).dot(n);
	double b1=((e1*d3).dot(n))/g;
	double b2=((e2*d1).dot(n))/g;
	double b3=((e3*d2).dot(n))/g;
	return CVector(b1,b2,b3);
}

CVector intersect(CRay l,CPlane v)
{
	double t=v.d-l.p0.dot(v.n);
	t=t/(v.n.dot(l.d));
	return CVector(l.p0+l.d*t);
}

void CPlane::computeCircum()
{
/* CVector e1=p3-p2;
 CVector ue1=e1.dot(e1)/e1.absc(e1);
 CVector e2=p1-p3;
 CVector ue2=e2.dot(e2)/e2.absc(e2);
 CVector e3=p2-p1;
 CVector ue3=e3.dot(e3)/e3.absc(e3);

 float d1=-e2.dot(e3);
 float d2=-e3.dot(e1);
 float d3=-e1.dot(e2);

 float c1=d2*d3;
 float c2=d3*d1;
 float c3=d1*d2;
 float c=c1+c2+c3;

 circumC=(p1*(c2+c3)+p2*(c1+c3)+p3*(c2+c1))/(2*c);
 circumR=sqrt( abs(( (d1+d2)*(d2+d3)*(d3*d1) )/c))/2;
*/
	 CVector b1=(p1+p2)/2;


	 CVector ra=b1-p1;
	 
	 CPoint pb1(b1);
	 CVector vpb1(pb1.x,pb1.y);

	 CPoint pc1(p1);
	 CVector vpc1(pc1.x,pc1.y);

	 ra=vpb1-vpc1;

	 CVector ba=vpb1+ra.polarc(ra.absc(ra),ra.argu(ra)+pi/2);
	 CVector l1=vpb1.intersect(ba);

	 CVector b2=(p3+p1)/2;
	 
	 CVector r1=b2-p1;

	 CPoint pb2(b2);
	 CVector vpb2(pb2.x,pb2.y);

		
	 r1=vpb2-vpc1;


	 CVector bi=vpb2+ra.polarc(ra.absc(r1),ra.argu(r1)+pi/2);
	 CVector l2=bi.intersect(vpb2);
	 
	 CVector Ct=l1.intersect(l2);
	 
	 CPoint pCt1(Ct.x,Ct.y);
	 circumC=pCt1;

}

CVector CPlane::getCircumC()
{
	return circumC;
}

double CPlane::getCircumR()
{
	return circumR;
}

CPlane::CPlane(CPoint i, CPoint j, CPoint k)
{
	p1.x=i.x;
	p1.y=i.y;
	p1.z=0;

	p2.x=j.x;
	p2.y=j.y;
	p2.z=0;

	p3.x=k.x;
	p3.y=k.y;
	p3.z=0;

	CVector e3=p2-p1;
	CVector e2=p3-p2;
	double jj=e2.absc(e3*e2);
	if(jj>1E-10)
	{
		n=(e3*e2)/jj;
		d=n.dot(p1);
	}
	computeCircum();

}
