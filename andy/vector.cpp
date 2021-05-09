// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Vector.h"
#include "tVector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//n=-5500,f=5500
	double CVector::n=500,CVector::f=100000,CVector::r=550,CVector::l=-550,CVector::t=425,CVector::b=-425;
	double CVector::Sx=1100,CVector::Sy=-850;
	double CVector::zstore=0,CVector::wstore=0;
	bool CVector::perspec=false;
	CVector::PLANESNAP CVector::planesnap=front;


CVector::V CVector::vec0, CVector::vecx, CVector::vecy,CVector::vecz,\
		   CVector::veci0, CVector::vecix, CVector::veciy,CVector::veciz,\
		   CVector::pvec0, CVector::pvecx, CVector::pvecy,CVector::pvecz,\
		   CVector::pveci0, CVector::pvecix, CVector::pveciy,CVector::pveciz;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector(const CVector begin, const CVector end)
{
/*	w=end.w-begin.w;
	x=(w!=0)?(end.x-begin.x)*w:end.x-begin.x;
	y=(w!=0)?(end.y-begin.y)*w:end.y-begin.y;
*/
	vb.x=begin.x;
	vb.y=begin.y;
	vb.z=begin.z;
	vb.w=begin.w;

	ve.x=end.x;
	ve.y=end.y;
	ve.z=end.z;
	ve.w=end.w;

	w=end.w-begin.w;
	x=end.x-begin.x;
	y=end.y-begin.y;
	z=end.z-begin.z;


/*	double xdum=x,ydum=y,zdum=z;
	x=x*vecx.x+y*vecy.x+z*vecz.x+vec0.x*w;
	y=xdum*vecx.y+y*vecy.y+z*vecz.y+vec0.y*w;
	z=xdum*vecx.z+ydum*vecy.z+z*vecz.z+vec0.z*w;
	w=xdum*vecx.w+ydum*vecy.w+zdum*vecz.w+vec0.w*w;

/*	if(w!=0)
	{
		x=x/w;
		y=y/w;
	}*/
}

CVector::~CVector()
{

}

/*double CVector::pointtoVector(CVector line,CVector point)
{
	//effectue l'operation
	//   point dot this
	//d=---------------- dot point
	//   point dot point
	
	//

/*	CPoint orpoint=point;
	CVector vpoint,vline;
	vpoint.x=point.x;
	vpoint.y=point.y;
	vpoint.z=0;
	CVector vorpoint=vpoint;
	
	vline.x=line.x;
	vline.y=line.y;
	vline.z=0;
	double proj1=vpoint.dot(vline)/vline.dot(vline);
	vpoint=vline.scalarMult(proj1);
	xhit=vpoint.x;
	yhit=vpoint.y;
	zhit=vpoint.z;

	vpoint.operator -=(vorpoint);
	double result=absc(vpoint);
	return	result;*/

/*	CVector orpoint=point;
	double proj1=point.dot(line)/line.dot(line);
	point=line*proj1;
	
	hitpoint=point;

	point.operator -=(orpoint);

	double result=absc(point);
	return	result;

}
*/


double CVector::pointtoVector(CVector line,CVector point,CVector* hitpoint)
{
	//effectue l'operation
	//   point dot this
	//d=---------------- dot point
	//   point dot point
	
	//

    CVector orpoint=point;
	double proj1=point.dot(line)/line.dot(line);
	point=line*proj1;
	
//	hitpoint=point;
	xhit=point.x;
	yhit=point.y;
	zhit=point.z;
	if(hitpoint!=NULL)
		*hitpoint=point;

	point.operator -=(orpoint);

	double result=absc(point);
	return	result;
	
/*	CVector orpoint=point;
	double proj1=point.dot(line)/line.dot(line);
	point=line.scalarMult(proj1);
	xhit=point.x;
	yhit=point.y;
	zhit=point.z;

	point.operator -=(orpoint);
	double result=absc(point);
	return	result;*/
}


CVector CVector::operator *(double v)
{
	CVector r;

	r.x=x*v;
	r.y=y*v;
	r.z=z*v;
 return r;
}



CVector CVector::operator *(CVector v)
{


	CVector r;
	r.x=y*v.z-z*v.y;//-(z*v.y-y*v.z);
	r.y=-(x*v.z-z*v.x);
	r.z=x*v.y-y*v.x;

	return r;
}

CVector CVector::intersect(CVector v,bool b)
{
CVector v1,v2;
	CVector vrx,vry,vrz;
	if(!b)
		{
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	v1=vrx*x+vry*y+vrz*z;
	v2=vrx*v.x+vry*v.y+vrz*v.z;
		}
	else
		{
	v1=*this;
	v2=v;
		}

	v1.x=(w!=0)?v1.x*w:v1.x;
	v1.y=(w!=0)?v1.y*w:v1.y;

	v2.x=(v2.w!=0)?v2.x*v2.w:v2.x;
	v2.y=(v2.w!=0)?v2.y*v2.w:v2.y;


	CVector r;
	r.w=v1.x*v2.y-v1.y*v2.x;r.ws=r.w;
	r.x=-(w*v2.y-v1.y*v2.w);
	r.y=w*v2.x-v1.x*v2.w;

	ws=r.w;

	if (sqrt(pow(r.w,2))>0)
	{
	r.x=r.x/r.w;
	r.y=r.y/r.w;
	r.w=1;
	}
	else
	{
		r.w=0;
	}

	
	v1.x=(w!=0)?v1.x/w:v1.x;
	v1.y=(w!=0)?v1.y/w:v1.y;
	w=(w!=0)?1:0;

	v.x=(v2.w!=0)?v2.x/v2.w:v2.x;
	v.y=(v2.w!=0)?v2.y/v2.w:v2.y;
	v.w=(v2.w!=0)?1:0;

	if(!b) r=vrx*r.x+vry*r.y+vrz*r.z;

	return r;
}
CVector::CVector (const V vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
	w=vec.w;

}

CVector CVector::scalarMult(double value)
{
	x=x;
	y=y;

//	w=value*w;
	x=value*x;
	y=value*y;
	z=value*z;

	return (*this);
}

CVector::CVector()
{
	x=0;y=0;w=1;z=0;
	if(perspec)
	{
		z=n-pvec0.z;
	}

}	

CVector::CVector(const CPoint point)
{


//	x=point.x-Sx/2;
//	y=-point.y+Sy/2;
	x=point.x-Sx/2;
	y=-point.y+Sy/2;
//	z=-2*pvec0.z;
	if(perspec) 
	{
//		y=-y;
//		x=-x;
	}
	w=1;
	z=n;
/*	if(perspec) 
	{
		z=f;
//		w=f;
	}

/*
	x=-point.x*2*w/Sx+w;
	y=-point.y*2*w/Sy+w;


//testing of removing view or transform
	if(perspec)
	{
	x=((r-l)*x)/(2*n);
	y=((t-b)*y)/(2*n);
	}
	else
	{
	 x=x*(r-l)/2;
	 y=y*(t-b)/2;
	}
*/	w=1;


	double xdum=x,ydum=y,zdum=z,wdum=w;

//	add on november

	xc=xdum*pvecx.x+ydum*pvecy.x+zdum*pvecz.x+pvec0.x*wdum;
	yc=xdum*pvecx.y+ydum*pvecy.y+zdum*pvecz.y+pvec0.y*wdum;
	zc=xdum*pvecx.z+ydum*pvecy.z+zdum*pvecz.z+pvec0.z*wdum;
	w=xdum*pvecx.w+ydum*pvecy.w+zdum*pvecz.w+pvec0.w*wdum;

	x=xc,y=yc,z=zc;
	xc=x;yc=y;zc=z;

	xdum=xc,ydum=yc,wdum=w,zdum=zc;
	w=xc*vecx.w+yc*vecy.w+zc*vecz.w+vec0.w*wdum;
	x=xc*vecx.x+yc*vecy.x+zc*vecz.x+vec0.x*wdum;
	y=xdum*vecx.y+yc*vecy.y+zc*vecz.y+vec0.y*wdum;
	z=xdum*vecx.z+ydum*vecy.z+zc*vecz.z+vec0.z*wdum;
//	snaptoplane(*this);


}

CVector::operator CPoint ()
{
	double x1,y1,w1,z1;
	double xdum=x,ydum=y,zdum=z,wc;
//testing of removing view or transform
	x1=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*w;
	y1=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*w;
	z1=xdum*vecix.z+y*veciy.z+z*veciz.z+veci0.z*w;
	w1=xdum*vecix.w+ydum*veciy.w+zdum*veciz.w+veci0.w*w;

	xdum=x1,ydum=y1,zdum=z1;
		

	xc=x1*pvecix.x+y1*pveciy.x+z1*pveciz.x+pveci0.x*w1;
	yc=xdum*pvecix.y+y1*pveciy.y+z1*pveciz.y+pveci0.y*w1;
	zc=xdum*pvecix.z+ydum*pveciy.z+z1*pveciz.z+pveci0.z*w1;
	wc=xdum*pvecix.w+ydum*pveciy.w+zdum*pveciz.w+pveci0.w*w1;


	xdum=xc,ydum=yc,zdum=zc;

	zstore=zc;
	bool nb=true;
	if(perspec)
	{
		x1=(2*n/(r-l))*xc;
		y1=(2*n/(t-b))*yc;

		z1=(f/(f-n))*(1-(n/zc));
		w1=zc*((-2*f*n)/(f-n));//-zc;
		x1=x1/zc;
		y1=y1/zc;
		if(z1<0)
		{
		int opiy=0;
		nb=false;
		}
		zstore=w1;

		wstore=w1;
	}
	else
	{
		x1=xc*(2/(r-l));
		y1=yc*(2/(t-b));
		z1=zc*(-2)/(f-n)+wc*(-(f+n)/(f-n));
		w1=wc;
		zstore=z1;
	}
	

	x1=((x1+1)*(Sx)/2);
	y1=((y1+1)*(Sy)/2);
//	x1=x1+(Sx/2);
//	y1=y1-(Sy/2);
	float i=x1,j=y1;
	CPoint p;
	p.x=i;
	p.y=j;
	return p;
//		return CPoint((int)x1,(int)y1);
}

CVector CVector::ppprojection(CVector point,CVector* v1)
{
	CVector orpoint=point;
	double proj1=point.dot(*this)/dot(*this);
	point=scalarMult(proj1);

	if(v1!=NULL) 
		*v1=point;
	point.operator -=(orpoint);
	return point;

}

bool CVector::pointinRegion(CVector point, CVector region)
{
	CPoint pregion=region;
	CPoint ppoint=point;
/*	if ((abs(region.x-point.x)<=5)&&(abs(region.y-point.y)<=5)&&(abs(region.z-point.z)<=5))
	{
		return true;
	}*/
	if ((abs(pregion.x-ppoint.x)<=5)&&(abs(pregion.y-ppoint.y)<=5))
	{
		return true;
	}
	else return false;

}


CPoint CVector::divideVect(CVector ptDebut, CVector ptEnd)
{
	CVector resultat;
	resultat.x=(ptDebut.x+ptEnd.x)/2;
	resultat.y=(ptDebut.y+ptEnd.y)/2;
	resultat.z=(ptDebut.z+ptEnd.z)/2;
	return resultat;

}


CVector::CVector(double fx,double fy,double fz,double fw)
{
	
	x=fx;
	y=fy;
	z=fz;
	w=fw;
	
}

void CVector::assignLP(CVector v)
{
	CVector bvec0,bvecx,bvecy,bvecz,vecv,vvec0,vvecy,vvecx,vvecz;
	bvec0.x=0;;
	bvec0.y=0;
	bvec0.z=0;
	bvec0.w=1;

	bvecx.x=1;;
	bvecx.y=0;
	bvecx.z=0;
	bvecx.w=0;

	bvecy.x=0;;
	bvecy.y=1;
	bvecy.z=0;
	bvecy.w=0;

	bvecz.x=0;;
	bvecz.y=0;
	bvecz.z=1;
	bvecz.w=0;

	vecv.x=vec0.x-bvec0.x;
	vecv.y=vec0.y-bvec0.y;
	vecv.z=vec0.z-bvec0.z;
	vecv.w=vec0.w-bvec0.w;

	vvec0.x=bvecx.x*vecv.x+ bvecx.y*vecv.y+ bvecx.z*vecv.z+bvecx.w*vecv.w;
	vvec0.y=bvecy.x*vecv.x+ bvecy.y*vecv.y+ bvecy.z*vecv.z+bvecy.w*vecv.w;
	vvec0.z=bvecz.x*vecv.x+ bvecz.y*vecv.y+ bvecz.z*vecv.z+bvecz.w*vecv.w;
	vvec0.w=bvec0.x*vecv.x+ bvec0.y*vecv.y+ bvec0.z*vecv.z+bvec0.w*vecv.w;

	vvecy.x=bvecx.x*vecy.x+ bvecx.y*vecy.y+ bvecx.z*vecy.z+bvecx.w*vecy.w;
	vvecy.y=bvecy.x*vecy.x+ bvecy.y*vecy.y+ bvecy.z*vecy.z+bvecy.w*vecy.w;
	vvecy.z=bvecz.x*vecy.x+ bvecz.y*vecy.y+ bvecz.z*vecy.z+bvecz.w*vecy.w;
	vvecy.w=bvec0.x*vecy.x+ bvec0.y*vecy.y+ bvec0.z*vecy.z+bvec0.w*vecy.w;

	vvecx.x=bvecx.x*vecx.x+ bvecx.y*vecx.y+ bvecx.z*vecx.z+ bvecx.w*vecx.w;
	vvecx.y=bvecy.x*vecx.x+ bvecy.y*vecx.y+ bvecy.z*vecx.z+ bvecy.w*vecx.w;
	vvecx.z=bvecz.x*vecx.x+ bvecz.y*vecx.y+ bvecz.z*vecx.z+ bvecz.w*vecx.w;
	vvecx.w=bvec0.x*vecx.x+ bvec0.y*vecx.y+ bvec0.z*vecx.z+ bvec0.w*vecx.w;

	vvecz.x=bvecx.x*vecz.x+ bvecx.y*vecz.y+ bvecx.z*vecz.z+ bvecx.w*vecz.w;
	vvecz.y=bvecy.x*vecz.x+ bvecy.y*vecz.y+ bvecy.z*vecz.z+ bvecy.w*vecz.w;
	vvecz.z=bvecz.x*vecz.x+ bvecz.y*vecz.y+ bvecz.z*vecz.z+ bvecz.w*vecz.w;
	vvecz.w=bvec0.x*vecz.x+ bvec0.y*vecz.y+ bvec0.z*vecz.z+ bvec0.w*vecz.w;

	x=v.x;
	y=v.y;
	z=v.z;
	w=v.w;


	
	double xdum=x,ydum=y,zdum=z,wdum=w;
	w=xdum*vvecx.w+y*vvecy.w+z*vvecz.w+vvec0.w*w;
	x=x*vvecx.x+y*vvecy.x+z*vvecz.x+vvec0.x*wdum;
	y=xdum*vvecx.y+y*vvecy.y+z*vvecz.y+vvec0.y*wdum;
	z=xdum*vvecx.z+ydum*vvecy.z+z*vvecz.z+vvec0.z*wdum;

}

void CVector::assignPL(CVector v)
{
	CVector bvec0,bvecx,bvecy,bvecz,vecv,vvec0,vvecy,vvecx,vvecz;
	bvec0.x=0;
	bvec0.y=0;
	bvec0.z=0;
	bvec0.w=1;

	bvecx.x=1;
	bvecx.y=0;
	bvecx.z=0;
	bvecx.w=0;

	bvecy.x=0;
	bvecy.y=1;
	bvecy.z=0;
	bvecy.w=0;

	bvecz.x=0;;
	bvecz.y=0;
	bvecz.z=1;;
	bvecz.w=0;

	vecv.x=bvec0.x-vec0.x;
	vecv.y=bvec0.y-vec0.y;
	vecv.z=bvec0.z-vec0.z;
	vecv.w=bvec0.w-vec0.w;


	vvec0.x=vecx.x*vecv.x+ vecy.x*vecv.y+ vecz.x*vecv.z+ vec0.x*vecv.w;
	vvec0.y=vecx.y*vecv.x+ vecy.y*vecv.y+ vecz.y*vecv.z+ vec0.y*vecv.w;
	vvec0.z=vecx.z*vecv.x+ vecy.z*vecv.y+ vecz.z*vecv.z+ vec0.z*vecv.w;
	vvec0.w=vecx.w*vecv.x+ vecy.w*vecv.y+ vecz.w*vecv.z+ vec0.w*vecv.w;

	vvecy.x=vecx.x*bvecy.x+ vecy.x*bvecy.y+ vecz.x*bvecy.z+ vec0.x*bvecy.w;
	vvecy.y=vecx.y*bvecy.x+ vecy.y*bvecy.y+ vecz.y*bvecy.z+ vec0.y*bvecy.w;
	vvecy.z=vecx.z*bvecy.x+ vecy.z*bvecy.y+ vecz.z*bvecy.z+ vec0.z*bvecy.w;
	vvecy.w=vecx.w*bvecy.x+ vecy.w*bvecy.y+ vecz.w*bvecy.z+ vec0.w*bvecy.w;

	vvecx.x=vecx.x*bvecx.x+ vecy.x*bvecx.y+ vecz.x*bvecx.z+ vec0.x*bvecx.w;
	vvecx.y=vecx.y*bvecx.x+ vecy.y*bvecx.y+ vecz.y*bvecx.z+ vec0.y*bvecx.w;
	vvecx.z=vecx.z*bvecx.x+ vecy.z*bvecx.y+ vecz.z*bvecx.z+ vec0.z*bvecx.w;
	vvecx.w=vecx.w*bvecx.x+ vecy.w*bvecx.y+ vecz.w*bvecx.z+ vec0.w*bvecx.w;

	vvecz.x=vecx.x*bvecz.x+ vecy.x*bvecz.y+ vecz.x*bvecz.z+ vec0.x*bvecz.w;
	vvecz.y=vecx.y*bvecz.x+ vecy.y*bvecz.y+ vecz.y*bvecz.z+ vec0.y*bvecz.w;
	vvecz.z=vecx.z*bvecz.x+ vecy.z*bvecz.y+ vecz.z*bvecz.z+ vec0.z*bvecz.w;
	vvecz.w=vecx.w*bvecz.x+ vecy.w*bvecz.y+ vecz.w*bvecz.z+ vec0.w*bvecz.w;
	x=v.x;
	y=v.y;
	z=v.z;
	w=v.w;


	
	double xdum=x,ydum=y,wdum=w;
	x=x*vvecx.x+y*vvecy.x+z*vvecz.x+vvec0.x*wdum;
	y=xdum*vvecx.y+y*vvecy.y+z*vvecz.y+vvec0.y*wdum;
	z=xdum*vvecx.z+ydum*vvecy.z+z*vvecz.z+vvec0.z*wdum;

}



void CVector::assign(CVector v)
{
	x=v.x;
	y=v.y;
	z=v.z;
	w=v.w;

	double xdum=x,ydum=y,wdum=w;
//	w=xdum*vecx.w+y*vecy.w+z*vecz.z+vec0.w*w;
	x=x*vecx.x+y*vecy.x+z*vecz.x+vec0.x*wdum;
	y=xdum*vecx.y+y*vecy.y+z*vecz.y+vec0.y*wdum;
	z=xdum*vecx.z+ydum*vecy.z+z*vecz.z+vec0.z*wdum;

}
        

void CVector::assign(CVector vec,bool point)
{
	x=(vec.w!=0)?(vec.x*vec.w):vec.x;
	y=(vec.w!=0)?(vec.y*vec.w):vec.y;
	z=(vec.w!=0)?(vec.z*vec.w):vec.z;
	w=vec.w;

	
	double xdum=x,ydum=y,wdum=w;
	w=xdum*vecx.w+y*vecy.w+z*vecz.w+vec0.w*w;
	x=x*vecx.x+y*vecy.x+z*vecz.x+vec0.x*wdum;
	y=xdum*vecx.y+y*vecy.y+z*vecz.y+vec0.y*wdum;
	z=xdum*vecx.z+ydum*vecy.z+z*vecz.z+vec0.z*wdum;
	if(w!=0)
	{
	x=x/w;
	y=y/w;
	z=z/w;
	}

}

void CVector::assign(CVector begin, CVector end)
{

	vb.x=begin.x;
	vb.y=begin.y;
	vb.z=begin.z;
	vb.w=begin.w;

	ve.x=end.x;
	ve.y=end.y;
	ve.z=end.z;
	ve.w=end.w;

	w=end.w-begin.w;
	x=end.x-begin.x;
	y=end.y-begin.y;
	z=end.z-begin.z;

}

void CVector::polarcvec(double absci, double argo)
{
	x=absci*cos(argo);
	y=absci*sin(argo);
}

CVector CVector::operator +(CVector v)
{

	CVector r;
	r.x=x+v.x;
	r.y=y+v.y;
	r.z=z+v.z;
	
	return r;
}

CVector CVector::operator -(CVector v)
{

	CVector r;

	r.x=x-v.x;
	r.y=y-v.y;
	r.z=z-v.z;

	return r;
}

void CVector::operator +=(CVector v)
{
	x=x+v.x;
	y=y+v.y;
	z=z+v.z;
	
}

void CVector::operator -=(CVector v)
{
	x=x-v.x;
	y=y-v.y;
	z=z-v.z;

}
CVector CVector::operator /(double i)
{

	CVector r;

	r.x=x/i;
	r.y=y/i;
	r.z=z/i;
	return r;

}


CVector CVector::getcamor()
{
	return CVector(pvec0.x,pvec0.y,pvec0.z,1);

}

CVector CVector::getcamx()
{
	return CVector(pvecx.x,pvecy.x,pvecz.x,0);
}

CVector CVector::getcamy()
{
	return CVector(pvecx.y,pvecy.y,pvecz.y,0);
}

CVector CVector::getcamz()
{
	return CVector(pvecx.z,pvecy.z,pvecz.z,0);
}

CVector CVector::getscrtop()
{
	return CVector(l,t,0,1);

}

CVector CVector::getscrb()
{
	return CVector(r,b,0,1);
}

void CVector::setcamor(CVector v)
{
  pvec0.x=v.x,
  pvec0.y=v.y;
  pvec0.z=v.z;
  pveci0.x=v.x,
  pveci0.y=v.y;
  pveci0.z=v.z;
  zstore=v.z;
}

CPoint CVector::cP()
{
	double x1,y1,w1,z1;
	double xdum=x,ydum=y,zdum=z;



	x1=x*((2*n)/(r-l));
	y1=y*((2*n)/(t-b));
	z1=x*((r+l)/(r-l))+y*((t+b)/(t-b))+z*(-(f+n)/(f-n))+w*(-1);
	w1=z*(-(2*f*n)/(f-n));
	if (x1>1) x1=1;if(y1>1) y1=1;
	if (x1<-1) x1=-1;if(y1<-1) y1=-1;

	if(w1!=0)
	{
	x1/=w1;
	y1/=w1;
	}
	

	x1=((Sx-1)*(x1+1))/2;
	y1=((Sy-1)*(y1+1))/2;

	return CPoint (x1,y1);
}

void CVector::initz()
{
 zstore=0;
}

void CVector::viewi()
{
	double xdum,ydum,wdum,zdum;

/*	xdum=x,ydum=y,wdum=w,zdum=z;
	w=xdum*vecix.w+y*veciy.w+veci0.w*w;
	x=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*wdum;
	y=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*wdum;
	z=xdum*vecix.z+ydum*veciy.z+z*veciz.z+veci0.z*wdum;
*/
	xdum=x,ydum=y,wdum=w,zdum=z;
	w=xdum*pvecix.w+y*pveciy.w+pveci0.w*w;
	x=x*pvecix.x+y*pveciy.x+z*pveciz.x+pveci0.x*wdum;
	y=xdum*pvecix.y+y*pveciy.y+z*pveciz.y+pveci0.y*wdum;
	z=xdum*pvecix.z+ydum*pveciy.z+z*pveciz.z+pveci0.z*wdum;

}

CVector CVector::camxyz()
{
	return CVector(xc,yc,zc);
}

CVector CVector::getDepth()
{
	double x1,y1,w1,z1;
	double xdum=x,ydum=y,zdum=z,wc;
//testing of removing view or transform
	x1=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*w;
	y1=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*w;
	z1=xdum*vecix.z+y*veciy.z+z*veciz.z+veci0.z*w;
	w1=xdum*vecix.w+ydum*veciy.w+zdum*veciz.w+veci0.w*w;

	xdum=x1,ydum=y1,zdum=z1;
		

	xc=x1*pvecix.x+y1*pveciy.x+z1*pveciz.x+pveci0.x*w1;
	yc=xdum*pvecix.y+y1*pveciy.y+z1*pveciz.y+pveci0.y*w1;
	zc=xdum*pvecix.z+ydum*pveciy.z+z1*pveciz.z+pveci0.z*w1;
	wc=xdum*pvecix.w+ydum*pveciy.w+zdum*pveciz.w+pveci0.w*w1;


	xdum=xc,ydum=yc,zdum=zc;

	zstore=zc;

/*	double x1=x,y1=y,w1=w,z1=z,wc;
	double xdum=x,ydum=y,zdum=z;

	x1=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*w;
	y1=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*w;
	z1=xdum*vecix.z+y*veciy.z+z*veciz.z+veci0.z*w;
	w1=xdum*vecix.w+ydum*veciy.w+zdum*veciz.w+veci0.w*w;

	xdum=x1,ydum=y1,zdum=z1;
	
	xc=x1*pvecix.x+y1*pveciy.x+z1*pveciz.x+pveci0.x*w1;
	yc=xdum*pvecix.y+y1*pveciy.y+z1*pveciz.y+pveci0.y*w1;
	zc=xdum*pvecix.z+ydum*pveciy.z+z1*pveciz.z+pveci0.z*w1;
	wc=xdum*pvecix.w+ydum*pveciy.w+z1*pveciz.w+pveci0.w*w1;
	

	xdum=x1,ydum=y1;//,zc=z1;

	zstore=zc;
//	zc=-zc;
*/	//bool bol=false;
	w1=1;
	if(perspec)
	{
	x1=(2*n/(r-l))*xc;
	y1=(2*n/(t-b))*yc;
//	w1=zc*((-2*f*n)/(f-n));//-zc;
	if(zc<0) w1=0;
	if(zc<0)
		{
		zc=0.1;//-1/(10*zc);
		}

	if(zc==0)	zc=0.1;
		
	x1=x1/zc;
	y1=y1/zc;
/*	if((y1<1)||(y1>-1)) 
		w1=1;
	if((x1<1)||(x1>-1))
		w1=1;*/
/*	y1=y1>-3?y1:-3;
	y1=y1<3?y1:3;
	x1=x1>-3?x1:-3;
	x1=x1<3?x1:3;
*/
	z1=t/8;
	
	z1=(f/(f-n))*(1-(n/zc));
//	z1=z1-f;
//	z1=-z1;
//		y1=(f/(f-0))*(1-(0/z1));
//	z1=y1;

	}
	else
	{
	x1=xc*(2/(r-l));
	y1=yc*(2/(t-b));
//	z1=w1*(-(f+n)/(f-n))+zc*(-2/(f-n));

	y1=y1>-1?y1:-1;
	y1=y1<1?y1:1;
	x1=x1>-1?x1:-1;
	x1=x1<1?x1:1;
	if(zc<0)
		{
		zc=-1/(10*zc);
		}

	z1=zc*(-2)/(f-n)+wc*(-(f+n)/(f-n));
	w1=wc;
	z1=z1-f;
	}
	x1=((x1+1)*(Sx-1)/(2));
	y1=((y1+1)*(Sy-1)/(2));

	return CVector(x1,y1,z1,w1);

}

void CVector::setperspective()
{
	perspec=(!perspec);
}

void CVector::translatecamxy(CVector v)
{
	pvec0.x+=v.x;
	pvec0.y+=v.y;
}

void CVector::translatecamz(CVector v)
{
	pvec0.z+=v.z;
}

void CVector::assignInv(CVector v)
{
	double xdum=v.x,ydum=v.y,zdum=v.z;
	x=v.x;y=v.y;z=v.z;

	x=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*w;
	y=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*w;
	z=xdum*vecix.z+y*veciy.z+z*veciz.z+veci0.z*w;
	w=xdum*vecix.w+ydum*veciy.w+zdum*veciz.w+veci0.w*w;

}

void CVector::setScreen(int w, int h)
{
	Sx=w-1;
	Sy=-h+1;
	r=w/2;
	l=-w/2;
	t=h/2;
	b=-h/2;
}
CSize CVector::getScreen()
{
	return CSize(Sx,Sy);
}

bool CVector::getPerspective()
{
 return perspec;
}

bool CVector::isOn()
{
 CVector zv=getDepth();
 //zv.z=-zv.z;
//	bool b=(n+f<zv.z)&&(zv.z<f+f)&&(l<zv.x)&&(r>zv.x);
	if(zv.y>t)
	{
		int h=0;
	}
	if(zv.z>2*f)
	{
		int h=0;
	}

 
 return (zv.z>-1);//((n+f+f/4<zv.z)&&(zv.z<f+2*f)&&(l<zv.x)&&(r>zv.x)&&(b<zv.y)&&(t>zv.y));
}

void CVector::v2D()
{
	 CPoint ppt(*this);
	 x=ppt.x;
	 y=ppt.y;
	 z=0;
 /*CVector vrx,vry,vrz,v;
 vrx.getcoorx();vry.getcoory();vrz.getcoorz();
 v=vrx*x+vry*y+vrz*z;;
 x=v.x;
 y=v.y;
 z=v.z;*/
	 
}

void CVector::v3D()
{
 CPoint p(x,y);
 CVector v=p;
// CVector vrx,vry,vrz;
// vrx.getcoorx();vry.getcoory();vrz.getcoorz();
// v=vrx*x+vry*y+vrz*z;;
 x=v.x;
 y=v.y;
 z=v.z;
}

void CVector::getcoorx()
{
	x=vecx.x;
	y=vecx.y;
	z=vecx.z;
	snapcoortoplane(*this,0);
}

void CVector::getcoory()
{
	x=vecy.x;
	y=vecy.y;
	z=vecy.z;
	snapcoortoplane(*this,1);
}

void CVector::getcoorz()
{
	x=vecz.x;
	y=vecz.y;
	z=vecz.z;
	snapcoortoplane(*this,2);
}

void CVector::getcooro()
{
	x=vec0.x;
	y=vec0.y;
	z=vec0.z;

}

CString CVector::setplanesnap(CString s)
{
	CString sd;
	switch(planesnap)
	{
	case front:
		{
			sd="front";
			break;
		}
	case left:
		{
			sd="left";
			break;
		}
	case top:
		{
			sd="top";
			break;
		}
	}
	if(s=="front")
	{
		planesnap=front;
	}
	else if(s=="left")
	{
		planesnap=left;
	}
	else if(s=="top")
	{
		planesnap=top;
	}else
	{
		planesnap=snapnull;
	}
	return sd;
}

CVector::PLANESNAP CVector::getplanesnap()
{
	return planesnap;
}

bool CVector::snaptoplane(CVector &v)
{
 CTVector t;
 if(planesnap==front)
 {
	 t.pushTransform();
	 CVector n(0,0,1);
	 t.Project(n);
	 t.endT();
	 v.assign(v);
//	 v.z=f;
	 t.popTransform();//pushUnit();
	 return true;
 }else
 if(planesnap==left)
 {
	 CVector n(0,0,1);//;n.getcoorz();//(0,0,1);
	 t.pushTransform();
	 t.Project(n);
	 t.endT();
	 v.assign(v);
	 t.popTransform();//pushUnit();
	 return true;
 }
else
 if(planesnap==top)
 {
	 CVector n(0,0,1);//n.getcoorz();//(0,0,1);
	 t.pushTransform();
	 t.Project(n);
	 t.endT();
	 v.assign(v);
	 t.popTransform();//pushUnit();
	 return true;
 }
}

void CVector::snapcoortoplane(CVector &v,int i)
{
 CTVector t;
 if(planesnap==front)
 {
	 if(i==0)
	 {
	 v.x=1;v.y=0;v.z=0;
	 }
	 else
	 if(i==1)
	 {
	 v.x=0;v.y=1;v.z=0;
	 }
	 else
	 if(i==2)
	 {
	 v.x=0;v.y=0;v.z=1;
	 }
 }else
 if(planesnap==left)
 {
	 if(i==0)
	 {
	 v.x=0;v.y=0;v.z=1;
	 }
	 else
	 if(i==1)
	 {
	 v.x=0;v.y=1;v.z=0;
	 }
	 else
	 if(i==2)
	 {
	 v.x=1;v.y=0;v.z=0;
	 }
 }
else
 if(planesnap==top)
 {
	 if(i==0)
	 {
	 v.x=1;v.y=0;v.z=0;
	 }
	 else
	 if(i==1)
	 {
	 v.x=0;v.y=0;v.z=-1;
	 }
	 else
	 if(i==2)
	 {
	 v.x=0;v.y=1;v.z=0;
	 }
 }

}

void CVector::assignF()
{
	double xdum=x,ydum=y,zdum=z,w1=w;
	
/*	x=x*pvecix.x+y*pveciy.x+z*pveciz.x+pveci0.x*w;
	y=xdum*pvecix.y+y*pveciy.y+z*pveciz.y+pveci0.y*w;
	z=xdum*pvecix.z+ydum*pveciy.z+z*pveciz.z+pveci0.z*w;
	w=xdum*pvecix.w+ydum*pveciy.w+zdum*pveciz.w+pveci0.w*w;
*/
	x=x*pvecx.x+y*pvecy.x+z*pvecz.x+pvec0.x*w;
	y=xdum*pvecx.y+y*pvecy.y+z*pvecz.y+pvec0.y*w;
	z=xdum*pvecx.z+ydum*pvecy.z+z*pvecz.z+pvec0.z*w;
	w=xdum*pvecx.w+ydum*pvecy.w+zdum*pvecz.w+pvec0.w*w;
}

void CVector::zoom(double zr)
{
	Sx/=zr;
	Sy/=zr;
	r/=zr;
	l/=zr;
	t/=zr;
	b/=zr;

}

double absc(const CVector v,bool b){
	if(!b)
		{
	CVector vrx,vry,vrz;
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	CVector v1=vrx*v.x+vry*v.y+vrz*v.z;
	
	return sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z);
		}
	else
		return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);

}

double angleBetween(CVector v1,CVector v2)
{
	float len1=absc(v1);
	float len2=absc(v2);
	float dot=v1.dot(v2);
	float a=dot/(len1*len2);
	
	if(a>=1.0)
		return 0.0;
	else if (a<=-1.0)
		return pi;
	else
		return (v1*v2).z>0?acos(a):-acos(a);
}
double argu(const CVector v,bool b){
	CVector vrx,vry,vrz;
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
//	if(v.x==0) return 0;
	if(!b)
		{
	CVector v1=vrx*v.x+vry*v.y+vrz*v.z;
			return atan2(v1.y,v1.x);
		}
	else
	{
			return atan2(v.y,v.x);
	}
}

bool pointinRegion(CVector point, CVector region)
{
		CPoint pregion=region;
		CPoint ppoint=point;
		if ((abs(pregion.x-ppoint.x)<=10)&&(abs(pregion.y-ppoint.y)<=10))
		{
			return true;
		}
		else return false;

}

double pointtoVector(CVector line,CVector point,CVector* hitpoint)
{
	//effectue l'operation
	//   point dot this
	//d=---------------- dot point
	//   point dot point
	
	//

    CVector orpoint=point;
	double proj1=point.dot(line)/line.dot(line);
	point=line*proj1;
	
	if(hitpoint!=NULL) 
		*hitpoint=point;
/*	xhit=point.x;
	yhit=point.y;
	zhit=point.z;
*/
	point.operator -=(orpoint);

	double result=absc(point);
	return	result;
	
}
CVector polarc(double absc,double argu,bool b)
{ 
	CVector vrx,vry,vrz;
	CVector v;
	if(!b)
	{
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	v=vrx*absc*cos(argu)+vry*absc*sin(argu);
	}
	else
	{
	v=CVector(1,0,0,0)*absc*cos(argu)+CVector(0,1,0,0)*absc*sin(argu);
	}
	return v;
}

CVector getcamor()
{
	CVector v;
	return v.getcamor();//(CVector::pvec0.x,CVector::pvec0.y,CVector::pvec0.z,1);

}

void CVector::savefile(CFile &file)
{
	file.Write(&x, sizeof(x));
	file.Write(&y, sizeof(y));
	file.Write(&z, sizeof(z));
	file.Write(&w, sizeof(w));
}

void CVector::openfile(CFile &file)
{
	file.Read(&x, sizeof(x));
	file.Read(&y, sizeof(y));
	file.Read(&z, sizeof(z));
	file.Read(&w, sizeof(w));
}
LONG CVector::Readfile(CFile &file)
{
	file.Seek(sizeof(x),CFile::current);
	file.Seek(sizeof(y),CFile::current);
	file.Seek(sizeof(z),CFile::current);
	return file.Seek(sizeof(w),CFile::current);
}


void CVector::world()
{
	double xdum,ydum,wdum,zdum;

	xdum=x,ydum=y,wdum=w,zdum=z;
	w=xdum*vecx.w+y*vecy.w+vec0.w*w;
	x=x*vecx.x+y*vecy.x+z*vecz.x+vec0.x*wdum;
	y=xdum*vecx.y+y*vecy.y+z*vecz.y+vec0.y*wdum;
	z=xdum*vecx.z+ydum*vecy.z+z*vecz.z+vec0.z*wdum;

}

void CVector::setfarplane(float v)
{
	f=v;
}

void CVector::setnearplane(float v)
{
	n=v;
}

float CVector::getfarplane()
{
	return f;
}

float CVector::getnearplane()
{
	return n;
}

void CVector::worldi()
{
	double xdum,ydum,wdum,zdum;

	xdum=x,ydum=y,wdum=w,zdum=z;
	w=xdum*vecix.w+y*veciy.w+veci0.w*w;
	x=x*vecix.x+y*veciy.x+z*veciz.x+veci0.x*wdum;
	y=xdum*vecix.y+y*veciy.y+z*veciz.y+veci0.y*wdum;
	z=xdum*vecix.z+ydum*veciy.z+z*veciz.z+veci0.z*wdum;

/*	xdum=x,ydum=y,zdum=z;
		

	x=x*pvecix.x+y*pveciy.x+z*pveciz.x+pveci0.x*w;
	y=xdum*pvecix.y+y*pveciy.y+z*pveciz.y+pveci0.y*w;
	z=xdum*pvecix.z+ydum*pveciy.z+z*pveciz.z+pveci0.z*w;
	w=xdum*pvecix.w+ydum*pveciy.w+zdum*pveciz.w+pveci0.w*w;
*/
}

void CVector::Normalise()
{

	float f=absc(*this);
	if(f==0) return;
	x=x/f;
	x=((x<1E-5)&&(x>-1E-5))?0:x;
	y=y/f;
	y=((y<1E-5)&&(y>-1E-5))?0:y;
	z=z/f;
	z=((z<1E-5)&&(z>-1E-5))?0:z;

}

void CVector::Scale(double f)
{
	x*=f;
	y*=f;
	z*=f;
}

CVector CVector::sgetscrb()
{
	return CVector(0,0);
}

CVector CVector::sgetscrtop()
{
	int x1=Sx;
	int y1=Sy;
	return CVector(x1,y1);
}

int orientation(CVector v1, CVector v2, CVector v3)
{
      double orin = (v2.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (v2.y - v1.y);

      if (orin > 0.0)      return -1;         /* Orientaion is to the left-hand side  */
      else if (orin < 0.0) return 1;        /* Orientaion is to the right-hand side */
      else                 return 0; /* Orientaion is neutral aka collinear  */

}

CVector CVector::getscrbot()
{
  return CVector (r,b,0,1);
}
