// TVector.cpp: implementation of the CTVector class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "TVector.h"
#include "Matrix1.h"
#include "cam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

	CVector CTVector::vx,CTVector::vy,CTVector::vz;
	CVector CTVector::v0r;
	vector<CVector> CTVector::base;
	vector<CVector> CTVector::b1,CTVector::bo,CTVector::bi1,CTVector::bio,\
		CTVector::vbo,CTVector::vbio;
	vector<CVector>::iterator CTVector::itbase=CTVector::base.begin();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CTVector::~CTVector()
{

if(!bo.size())
{
 b1.clear();bo.clear();bi1.clear();bio.clear();	
}

}
CTVector::CTVector()
{
	if(!bo.size())
	{
	bo.resize(5);
	bio.resize(5);

	bo[0].x=1;
	bo[0].y=0;
	bo[0].z=0;
	bo[0].w=0;

	bo[1].x=0;
	bo[1].y=1;
	bo[1].z=0;
	bo[1].w=0;

	bo[2].x=0;
	bo[2].y=0;
	bo[2].z=1;
	bo[2].w=0;

	bo[3].x=0;
	bo[3].y=0;
	bo[3].z=0;
	bo[3].w=1;

	bio.resize(5);
	bio[0].x=1;
	bio[0].y=0;
	bio[0].z=0;
	bio[0].w=0;

	bio[1].x=0;
	bio[1].y=1;
	bio[1].z=0;
	bio[1].w=0;

	bio[2].x=0;
	bio[2].y=0;
	bio[2].z=1;
	bio[2].w=0;

	bio[3].x=0;
	bio[3].y=0;
	bio[3].z=0;
	bio[3].w=1;
	}

	bi1.resize(5);
	b1.resize(5);
	b1[0].x=1;
	b1[0].y=0;
	b1[0].z=0;
	b1[0].w=0;

	b1[1].x=0;
	b1[1].y=1;
	b1[1].z=0;
	b1[1].w=0;

	b1[2].x=0;
	b1[2].y=0;
	b1[2].z=1;
	b1[2].w=0;

	b1[3].x=0;
	b1[3].y=0;
	b1[3].z=0;
	b1[3].w=1;

	CMatrix mat;

	bi1.resize(5);
	double Dx[5], Dy[5],Dz[5],Dw[5];
	double N[16];
	Dx[0]=1;
	Dx[1]=0;
	Dx[2]=0;
	Dx[3]=0;

	Dy[0]=0;
	Dy[1]=1;
	Dy[2]=0;
	Dy[3]=0;

	Dz[0]=0;
	Dz[1]=0;
	Dz[2]=1;
	Dz[3]=0;

	Dw[0]=0;
	Dw[1]=0;
	Dw[2]=0;
	Dw[3]=1;

	
	N[0]=1;
	N[1]=0;
	N[2]=0;
	N[3]=0;

	N[4]=0;
	N[5]=1;
	N[6]=0;
	N[7]=0;
	
	N[8]=0;
	N[9]=0;
	N[10]=1;
	N[11]=0;

	N[12]=0;
	N[13]=0;
	N[14]=0;
	N[15]=1;
	
	
	mat.LUG(Dx,N,3,3,3);
	mat.LUG(Dy,N,3,3,1);
	mat.LUG(Dz,N,3,3,1);
	mat.LUG(Dw,N,3,3,1);

	for(int i=0;i<4;i++)
	{
		bi1[i].x=Dx[i];
		bi1[i].y=Dy[i];
		bi1[i].z=Dz[i];
		bi1[i].w=Dw[i];
	}

}


void CTVector::SetWindowOrig(CVector vvx, CVector vvy, CVector vv0)
{

}

void CTVector::Translate(CVector vt)
{

	vx.x=1;
	vx.y=0;
	vx.z=0;
	vx.w=0;
	base.push_back(vx);
	vy.x=0;
	vy.y=1;
	vy.z=0;
	vy.w=0;
	base.push_back(vy);
	vz.x=0;
	vz.y=0;
	vz.z=1;
	vz.w=0;
	base.push_back(vz);
	v0r.x=vt.x;
	v0r.y=vt.y;
	v0r.z=vt.z;
	v0r.w=1;
	base.push_back(v0r);
}

void CTVector::Scale(double scx, double scy,double scz)
{
	vx.x=scx;
	vx.y=0;
	vx.z=0;
	vx.w=0;
	base.push_back(vx);
	vy.y=scy;
	vy.x=0;
	vy.z=0;
	vy.w=0;
	base.push_back(vy);
	vz.z=scz;
	vz.y=0;
	vz.x=0;
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);

}

void CTVector::TRotate(double angle)
{
	vx.x=cos(angle);
	vx.y=sin(angle);
	vx.z=0;
	vx.w=0;
	base.push_back(vx);
	vy.x=-sin(angle);
	vy.y=cos(angle);
	vy.z=0;
	vy.w=0;
	base.push_back(vy);
	vz.x=0;
	vz.y=0;
	vz.z=1;
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);
}

void CTVector::TRotatex(double angle)
{
	vx.x=1;
	vx.y=0;
	vx.z=0;
	vx.w=0;
	base.push_back(vx);
	vy.x=0;
	vy.y=cos(angle);
	vy.z=sin(angle);
	vy.w=0;
	base.push_back(vy);
	vz.x=0;
	vz.y=-sin(angle);
	vz.z=cos(angle);
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);
}
void CTVector::TRotatey(double angle)
{
	vx.x=cos(angle);
	vx.y=0;
	vx.z=-sin(angle);
	vx.w=0;
	base.push_back(vx);
	vy.x=0;
	vy.y=1;
	vy.z=0;
	vy.w=0;
	base.push_back(vy);
	vz.x=sin(angle);
	vz.y=0;
	vz.z=cos(angle);
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);
}

void CTVector::TRotate(CVector n,double angle)
{
	vx.x=pow(n.x,2)*(1-cos(angle))+cos(angle);
	vx.y=n.x*n.y*(1-cos(angle))+n.z*sin(angle);
	vx.z=n.x*n.z*(1-cos(angle))-n.y*sin(angle);
	vx.w=0;
	base.push_back(vx);
	vy.x=n.x*n.y*(1-cos(angle))-n.z*sin(angle);
	vy.y=pow(n.y,2)*(1-cos(angle))+cos(angle);
	vy.z=n.y*n.z*(1-cos(angle))+n.x*sin(angle);
	vy.w=0;
	base.push_back(vy);
	vz.x=n.x*n.z*(1-cos(angle))+n.y*sin(angle);
	vz.y=n.y*n.z*(1-cos(angle))-n.x*sin(angle);
	vz.z=pow(n.z,2)*(1-cos(angle))+cos(angle);
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);
}



void CTVector::Shear(double shx, double shy,double shz)
{

	vx.y=shy;
	vx.x=1;
	vx.w=0;
	base.push_back(vx);
	vy.x=shx;
	vy.y=1;
	vy.w=0;
	base.push_back(vy);
	v0r.x=0;
	v0r.y=0;
	v0r.w=1;
	base.push_back(v0r);
}

void CTVector::popTransform()
{

	CVector servant;

	vector<CVector>::iterator itp=bo.end()-1;

	servant.vec0.x=itp->x;
	servant.vec0.y=itp->y;
	servant.vec0.z=itp->z;
	servant.vec0.w=itp->w;itp--;

	servant.vecz.x=itp->x;
	servant.vecz.y=itp->y;
	servant.vecz.z=itp->z;
	servant.vecz.w=itp->w;itp--;

	servant.vecy.x=itp->x;
	servant.vecy.y=itp->y;
	servant.vecy.z=itp->z;
	servant.vecy.w=itp->w;itp--;

	servant.vecx.x=itp->x;
	servant.vecx.y=itp->y;
	servant.vecx.z=itp->z;
	servant.vecx.w=itp->w;

	bo.pop_back();
	bo.pop_back();
	bo.pop_back();
	bo.pop_back();


	itp=bio.end()-1;

	servant.veci0.x=itp->x;
	servant.veci0.y=itp->y;
	servant.veci0.z=itp->z;
	servant.veci0.w=itp->w;itp--;

	servant.veciz.x=itp->x;
	servant.veciz.y=itp->y;
	servant.veciz.z=itp->z;
	servant.veciz.w=itp->w;itp--;

	servant.veciy.x=itp->x;
	servant.veciy.y=itp->y;
	servant.veciy.z=itp->z;
	servant.veciy.w=itp->w;itp--;

	servant.vecix.x=itp->x;
	servant.vecix.y=itp->y;
	servant.vecix.z=itp->z;
	servant.vecix.w=itp->w;

	bio.pop_back();
	bio.pop_back();
	bio.pop_back();
	bio.pop_back();


}

void CTVector::VpopTransform()
{

	CVector servant;

	vector<CVector>::iterator itp=vbo.end()-1;

	servant.pvec0.x=itp->x;
	servant.pvec0.y=itp->y;
	servant.pvec0.z=itp->z;
	servant.pvec0.w=itp->w;itp--;

	servant.pvecz.x=itp->x;
	servant.pvecz.y=itp->y;
	servant.pvecz.z=itp->z;
	servant.pvecz.w=itp->w;itp--;

	servant.pvecy.x=itp->x;
	servant.pvecy.y=itp->y;
	servant.pvecy.z=itp->z;
	servant.pvecy.w=itp->w;itp--;

	servant.pvecx.x=itp->x;
	servant.pvecx.y=itp->y;
	servant.pvecx.z=itp->z;
	servant.pvecx.w=itp->w;

	vbo.pop_back();
	vbo.pop_back();
	vbo.pop_back();
	vbo.pop_back();


	itp=vbio.end()-1;

	servant.pveci0.x=itp->x;
	servant.pveci0.y=itp->y;
	servant.pveci0.z=itp->z;
	servant.pveci0.w=itp->w;itp--;

	servant.pveciz.x=itp->x;
	servant.pveciz.y=itp->y;
	servant.pveciz.z=itp->z;
	servant.pveciz.w=itp->w;itp--;

	servant.pveciy.x=itp->x;
	servant.pveciy.y=itp->y;
	servant.pveciy.z=itp->z;
	servant.pveciy.w=itp->w;itp--;

	servant.pvecix.x=itp->x;
	servant.pvecix.y=itp->y;
	servant.pvecix.z=itp->z;
	servant.pvecix.w=itp->w;

	vbio.pop_back();
	vbio.pop_back();
	vbio.pop_back();
	vbio.pop_back();


}


CVector CTVector::unitvector(CVector v)
{
	CVector result;
   	double tr=v.dot(v)/(v.absc(v)*v.absc(v));
	result=result*tr;
	return result;
}


void CTVector::pushUnit()
{

	CVector servant;
	servant.vecx.x=1;
	servant.vecx.y=0;
	servant.vecx.z=0;
	servant.vecx.w=0;

	servant.vecy.x=0;
	servant.vecy.y=1;
	servant.vecy.z=0;
	servant.vecy.w=0;

	servant.vecz.x=0;
	servant.vecz.y=0;
	servant.vecz.z=1;
	servant.vecz.w=0;

	servant.vec0.x=0;
	servant.vec0.y=0;
	servant.vec0.z=0;
	servant.vec0.w=1;

	servant.vecix.x=1;
	servant.vecix.y=0;
	servant.vecix.z=0;
	servant.vecix.w=0;

	servant.veciy.x=0;
	servant.veciy.y=1;
	servant.veciy.z=0;
	servant.veciy.w=0;

	servant.veciz.x=0;
	servant.veciz.y=0;
	servant.veciz.z=1;
	servant.veciz.w=0;

	servant.veci0.x=0;
	servant.veci0.y=0;
	servant.veci0.z=0;
	servant.veci0.w=1;
}

void CTVector::pushTransform()
{
 CVector servant;
   CVector vx(servant.vecx.x,servant.vecx.y,servant.vecx.z,servant.vecx.w);
   CVector vy(servant.vecy.x,servant.vecy.y,servant.vecy.z,servant.vecy.w);
   CVector vz(servant.vecz.x,servant.vecz.y,servant.vecz.z,servant.vecz.w);
   CVector v0(servant.vec0.x,servant.vec0.y,servant.vec0.z,servant.vec0.w);
   
   bo.push_back(vx);
   bo.push_back(vy);
   bo.push_back(vz);
   bo.push_back(v0);

   CVector vix(servant.vecix.x,servant.vecix.y,servant.vecix.z,servant.vecix.w);
   CVector viy(servant.veciy.x,servant.veciy.y,servant.veciy.z,servant.veciy.w);
   CVector viz(servant.veciz.x,servant.veciz.y,servant.veciz.z,servant.veciz.w);
   CVector vi0(servant.veci0.x,servant.veci0.y,servant.veci0.z,servant.veci0.w);
   
   bio.push_back(vix);
   bio.push_back(viy);
   bio.push_back(viz);
   bio.push_back(vi0);
}

void CTVector::VpushTransform()
{
 CVector servant;
   CVector vx(servant.pvecx.x,servant.pvecx.y,servant.pvecx.z,servant.pvecx.w);
   CVector vy(servant.pvecy.x,servant.pvecy.y,servant.pvecy.z,servant.pvecy.w);
   CVector vz(servant.pvecz.x,servant.pvecz.y,servant.pvecz.z,servant.pvecz.w);
   CVector v0(servant.pvec0.x,servant.pvec0.y,servant.pvec0.z,servant.pvec0.w);
   
   vbo.push_back(vx);
   vbo.push_back(vy);
   vbo.push_back(vz);
   vbo.push_back(v0);

   CVector vix(servant.pvecix.x,servant.pvecix.y,servant.pvecix.z,servant.pvecix.w);
   CVector viy(servant.pveciy.x,servant.pveciy.y,servant.pveciy.z,servant.pveciy.w);
   CVector viz(servant.pveciz.x,servant.pveciz.y,servant.pveciz.z,servant.pveciz.w);
   CVector vi0(servant.pveci0.x,servant.pveci0.y,servant.pveci0.z,servant.pveci0.w);
   
   vbio.push_back(vix);
   vbio.push_back(viy);
   vbio.push_back(viz);
   vbio.push_back(vi0);
}


void CTVector::updateMatrix(bool v)
{

	vector<CVector> resi(4*4);
	double *N;
	N=new double[4*4];
//	double *D;
//	D=new double[4*4];

	double *Dx, *Dy,*Dz,*Dw;
	Dx=new double[5];
	Dy=new double[5];
	Dz=new double[5];
	Dw=new double[5];

	Dx[0]=1;
	Dx[1]=0;
	Dx[2]=0;
	Dx[3]=0;

	Dy[0]=0;
	Dy[1]=1;
	Dy[2]=0;
	Dy[3]=0;

	Dz[0]=0;
	Dz[1]=0;
	Dz[2]=1;
	Dz[3]=0;

	Dw[0]=0;
	Dw[1]=0;
	Dw[2]=0;
	Dw[3]=1;

	CVector servant;
	CMatrix mat;
	vector<CVector> res(40),op(40);

	vector<CVector>::iterator itp=base.begin(),it=base.begin();
	vector<CVector>::iterator iterb;
	
	vector<CVector>::iterator bvecx=itp;itp++;
	vector<CVector>::iterator bvecy=itp;itp++;
	vector<CVector>::iterator bvecz=itp;itp++;
	vector<CVector>::iterator bvec0=itp;itp++;

	op.assign(it,it+4);
	res=op;
	if(base.size()>4)
	{
	int j=4;
    while(it+j<base.end())
	{
	op.assign(it+j,it+j+4);
	res=mat.mult(res,op);
	j=j+4;
	} 
	}


	if(vi==world)
	{

	op[0].x=servant.vecx.x;
	op[0].y=servant.vecx.y;
	op[0].z=servant.vecx.z;
	op[0].w=servant.vecx.w;

	op[1].x=servant.vecy.x;
	op[1].y=servant.vecy.y;
	op[1].z=servant.vecy.z;
	op[1].w=servant.vecy.w;

	op[2].x=servant.vecz.x;
	op[2].y=servant.vecz.y;
	op[2].z=servant.vecz.z;
	op[2].w=servant.vecz.w;

	op[3].x=servant.vec0.x;
	op[3].y=servant.vec0.y;
	op[3].z=servant.vec0.z;
	op[3].w=servant.vec0.w;

	
//	std::copy(op.begin(),op.end(),bo.begin());

	res=mat.mult(op,res);


	N[0]=res[0].x;
	N[1]=res[0].y;
	N[2]=res[0].z;
	N[3]=res[0].w;

	N[4]=res[1].x;
	N[5]=res[1].y;
	N[6]=res[1].z;
	N[7]=res[1].w;
	
	N[8]=res[2].x;
	N[9]=res[2].y;
	N[10]=res[2].z;
	N[11]=res[2].w;

	N[12]=res[3].x;
	N[13]=res[3].y;
	N[14]=res[3].z;
	N[15]=res[3].w;
//	mat.Transpose(N,4,4);
	
	
	mat.LUG(Dx,N,3,3,1);
	mat.LUG(Dy,N,3,3,1);
	mat.LUG(Dz,N,3,3,1);
	mat.LUG(Dw,N,3,3,1);

//	mat.LUG(D,N,3,3,3);

	for(int i=0;i<4;i++)
	{
		resi[i].x=Dx[i];
		resi[i].y=Dy[i];
		resi[i].z=Dz[i];
		resi[i].w=Dw[i];
	}

//	mat.mult(D,res);


	servant.vecx.x=res[0].x;
	servant.vecx.y=res[0].y;
	servant.vecx.z=res[0].z;
	servant.vecx.w=res[0].w;

	servant.vecy.x=res[1].x;
	servant.vecy.y=res[1].y;
	servant.vecy.z=res[1].z;
	servant.vecy.w=res[1].w;

	servant.vecz.x=res[2].x;
	servant.vecz.y=res[2].y;
	servant.vecz.z=res[2].z;
	servant.vecz.w=res[2].w;

	servant.vec0.x=res[3].x;
	servant.vec0.y=res[3].y;
	servant.vec0.z=res[3].z;
	servant.vec0.w=res[3].w;

/* Inverse vector processing */

	op[0].x=servant.vecix.x;
	op[0].y=servant.vecix.y;
	op[0].z=servant.vecix.z;
	op[0].w=servant.vecix.w;

	op[1].x=servant.veciy.x;
	op[1].y=servant.veciy.y;
	op[1].z=servant.veciy.z;
	op[1].w=servant.veciy.w;

	op[2].x=servant.veciz.x;
	op[2].y=servant.veciz.y;
	op[2].z=servant.veciz.z;
	op[2].w=servant.veciz.w;

	op[3].x=servant.veci0.x;
	op[3].y=servant.veci0.y;
	op[3].z=servant.veci0.z;
	op[3].w=servant.veci0.w;
	
//	std::copy(op.begin(),op.end(),bio.begin());

	servant.vecix.x=resi[0].x;
	servant.vecix.y=resi[0].y;
	servant.vecix.z=resi[0].z;
	servant.vecix.w=resi[0].w;

	servant.veciy.x=resi[1].x;
	servant.veciy.y=resi[1].y;
	servant.veciy.z=resi[1].z;
	servant.veciy.w=resi[1].w;

	servant.veciz.x=resi[2].x;
	servant.veciz.y=resi[2].y;
	servant.veciz.z=resi[2].z;
	servant.veciz.w=resi[2].w;

	servant.veci0.x=resi[3].x;
	servant.veci0.y=resi[3].y;
	servant.veci0.z=resi[3].z;
	servant.veci0.w=resi[3].w;

	
	}
	else
	if(vi==view)
	{

	op[0].x=servant.pvecx.x;
	op[0].y=servant.pvecx.y;
	op[0].z=servant.pvecx.z;
	op[0].w=servant.pvecx.w;

	op[1].x=servant.pvecy.x;
	op[1].y=servant.pvecy.y;
	op[1].z=servant.pvecy.z;
	op[1].w=servant.pvecy.w;

	op[2].x=servant.pvecz.x;
	op[2].y=servant.pvecz.y;
	op[2].z=servant.pvecz.z;
	op[2].w=servant.pvecz.w;

	op[3].x=servant.pvec0.x;
	op[3].y=servant.pvec0.y;
	op[3].z=servant.pvec0.z;
	op[3].w=servant.pvec0.w;
	
	std::copy(op.begin(),op.end(),b1.begin());

	res=mat.mult(op,res);

	N[0]=res[0].x;
	N[1]=res[0].y;
	N[2]=res[0].z;
	N[3]=res[0].w;

	N[4]=res[1].x;
	N[5]=res[1].y;
	N[6]=res[1].z;
	N[7]=res[1].w;
	
	N[8]=res[2].x;
	N[9]=res[2].y;
	N[10]=res[2].z;
	N[11]=res[2].w;

	N[12]=res[3].x;
	N[13]=res[3].y;
	N[14]=res[3].z;
	N[15]=res[3].w;
//	mat.Transpose(N,4,4);
	
	
	mat.LUG(Dx,N,3,3,1);
	mat.LUG(Dy,N,3,3,1);
	mat.LUG(Dz,N,3,3,1);
	mat.LUG(Dw,N,3,3,1);

	for(int i=0;i<4;i++)
	{
		resi[i].x=Dx[i];
		resi[i].y=Dy[i];
		resi[i].z=Dz[i];
		resi[i].w=Dw[i];
	}

	
	
	servant.pvecx.x=res[0].x;
	servant.pvecx.y=res[0].y;
	servant.pvecx.z=res[0].z;
	servant.pvecx.w=res[0].w;

	servant.pvecy.x=res[1].x;
	servant.pvecy.y=res[1].y;
	servant.pvecy.z=res[1].z;
	servant.pvecy.w=res[1].w;

	servant.pvecz.x=res[2].x;
	servant.pvecz.y=res[2].y;
	servant.pvecz.z=res[2].z;
	servant.pvecz.w=res[2].w;

	servant.pvec0.x=res[3].x;
	servant.pvec0.y=res[3].y;
	servant.pvec0.z=res[3].z;
	servant.pvec0.w=res[3].w;


/* Inverse vector processing */

	op[0].x=servant.pvecix.x;
	op[0].y=servant.pvecix.y;
	op[0].z=servant.pvecix.z;
	op[0].w=servant.pvecix.w;

	op[1].x=servant.pveciy.x;
	op[1].y=servant.pveciy.y;
	op[1].z=servant.pveciy.z;
	op[1].w=servant.pveciy.w;

	op[2].x=servant.pveciz.x;
	op[2].y=servant.pveciz.y;
	op[2].z=servant.pveciz.z;
	op[2].w=servant.pveciz.w;

	op[3].x=servant.pveci0.x;
	op[3].y=servant.pveci0.y;
	op[3].z=servant.pveci0.z;
	op[3].w=servant.pveci0.w;
	
	std::copy(op.begin(),op.end(),bi1.begin());
	
	
	servant.pvecix.x=resi[0].x;
	servant.pvecix.y=resi[0].y;
	servant.pvecix.z=resi[0].z;
	servant.pvecix.w=resi[0].w;

	servant.pveciy.x=resi[1].x;
	servant.pveciy.y=resi[1].y;
	servant.pveciy.z=resi[1].z;
	servant.pveciy.w=resi[1].w;

	servant.pveciz.x=resi[2].x;
	servant.pveciz.y=resi[2].y;
	servant.pveciz.z=resi[2].z;
	servant.pveciz.w=resi[2].w;

	servant.pveci0.x=resi[3].x;
	servant.pveci0.y=resi[3].y;
	servant.pveci0.z=resi[3].z;
	servant.pveci0.w=resi[3].w;

	}
	else if(vi==local)
	{

	}

	
	delete []N;

	delete []Dx;
	delete []Dy;
	delete []Dz;
	delete []Dw;
	
}

void CTVector::initVect()
{
	CVector servant;
	
	servant.vec0.x=0;
	servant.vec0.y=0;
	servant.vec0.z=0;
	servant.vec0.w=1;
	
	servant.vecy.x=0;
	servant.vecy.y=1;
	servant.vecy.z=0;
	servant.vecy.w=0;
	
	servant.vecz.x=0;
	servant.vecz.y=0;
	servant.vecz.z=1;
	servant.vecz.w=0;

	servant.vecx.x=1;
	servant.vecx.y=0;
	servant.vecx.z=0;
	servant.vecx.w=0;

	servant.veci0.x=0;
	servant.veci0.y=0;
	servant.veci0.z=0;
	servant.veci0.w=1;
	
	servant.veciy.x=0;
	servant.veciy.y=1;
	servant.veciy.z=0;
	servant.veciy.w=0;
	
	servant.veciz.x=0;
	servant.veciz.y=0;
	servant.veciz.z=1;
	servant.veciz.w=0;

	servant.vecix.x=1;
	servant.vecix.y=0;
	servant.vecix.z=0;
	servant.vecix.w=0;

	Translate(CVector(0,0,CVector::n));
//	TRotatex(-pi/4);
	endT();

}

void CTVector::endT()
{
	vi=world;
	if (base.empty()) return;
	updateMatrix(false);
	base.clear();

}
void CTVector::VendT()
{
	vi=view;
	if (base.empty()) return;
	updateMatrix(true);
	base.clear();

}
double CTVector::getzoomrat()
{
	CVector s;
	return s.pvecx.x;

}

void CTVector::VinitVect()
{
	CVector servant;

	servant.pvec0.x=0;
	servant.pvec0.y=0;
	servant.pvec0.z=0;
	servant.pvec0.w=1;
	

	servant.pvecy.x=0;
	servant.pvecy.y=1;
	servant.pvecy.z=0;
	servant.pvecy.w=0;
	
	servant.pvecz.x=0;
	servant.pvecz.y=0;
	servant.pvecz.z=1;
	servant.pvecz.w=0;

	servant.pvecx.x=1;
	servant.pvecx.y=0;
	servant.pvecx.z=0;
	servant.pvecx.w=0;


	servant.pveci0.x=0;
	servant.pveci0.y=0;
	servant.pveci0.z=0;
	servant.pveci0.w=1;
	
	servant.pveciy.x=0;
	servant.pveciy.y=1;
	servant.pveciy.z=0;
	servant.pveciy.w=0;
	
	servant.pveciz.x=0;
	servant.pveciz.y=0;
	servant.pveciz.z=1;
	servant.pveciz.w=0;

	servant.pvecix.x=1;
	servant.pvecix.y=0;
	servant.pvecix.z=0;
	servant.pvecix.w=0;
	CVector vx(1,0,0),vy(0,1,0),vz(0,0,-1),vo(0,0,0);//CVector::f);
	TCam(vx,vy,vz,vo);
	VendT();
//	CCAM cam;
//	cam.setcamvector(vo,vz,vx,vy);


}

void CTVector::VpushUnit()
{
	CVector servant;
	servant.pvecx.x=1;
	servant.pvecx.y=0;
	servant.pvecx.z=0;
	servant.pvecx.w=0;

	servant.pvecy.x=0;
	servant.pvecy.y=1;
	servant.pvecy.z=0;
	servant.pvecy.w=0;

	servant.pvecz.x=0;
	servant.pvecz.y=0;
	servant.pvecz.z=1;
	servant.pvecz.w=0;

	servant.pvec0.x=0;
	servant.pvec0.y=0;
	servant.pvec0.z=0;
	servant.pvec0.w=1;

	servant.pvecix.x=1;
	servant.pvecix.y=0;
	servant.pvecix.z=0;
	servant.pvecix.w=0;

	servant.pveciy.x=0;
	servant.pveciy.y=1;
	servant.pveciy.z=0;
	servant.pveciy.w=0;

	servant.pveciz.x=0;
	servant.pveciz.y=0;
	servant.pveciz.z=1;
	servant.pveciz.w=0;

	servant.pveci0.x=0;
	servant.pveci0.y=0;
	servant.pveci0.z=0;
	servant.pveci0.w=1;

}

void CTVector::LendT()
{
	vi=local;
	updateMatrix(true);
	base.clear();
}

void CTVector::InitCamView(CString s,CAABB& box)
{
	
	if(s=="top")
	{
	CVector vz(0,1,0,0);
	CVector vx(1,0,0,0);
	CVector vy(0,0,-1,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(0,CVector::n,0,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("top");

	}
	else
	if(s=="bottom")
	{
	CVector vz(0,-1,0,0);
	CVector vx(1,0,0,0);
	CVector vy(0,0,-1,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(0,-CVector::n,0,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("top");
	}
	else
	if(s=="left")
	{
	CVector vz(1,0,0,0);
	CVector vx(0,0,1,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(CVector::n,0,0,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("left");

	}
	else
	if(s=="right")
	{
	CVector vz(-1,0,0,0);
	CVector vx(0,0,1,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(-CVector::n,0,0,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("left");

	}
	else
	if(s=="front")
	{
	CVector vz(0,0,1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(0,0,CVector::n,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("front");
	}
	else
	if(s=="back")
	{
	CVector vz(0,0,-1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	c=CVector(0,0,0,1);
	CVector vo(0,0,-CVector::n,1);
	setWorld(vx,vy,vz,vo);
	vz.setplanesnap("front");
	}
	else
	if(s=="NE")
	{
	CVector vz(0,0,1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	initVect();
	TRotatex(pi/3);
	TRotate(-pi/4);
	endT();


	}
	else
	if(s=="NW")
	{
	CVector vz(0,0,1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	initVect();
	TRotatex(pi/3);
	TRotate(pi/4);
	endT();


	}
	else
	if(s=="SE")
	{
	CVector vz(0,0,1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	initVect();
	TRotatex(pi/3);
	TRotate(-(3*pi)/4);
	endT();

	}
	else
	if(s=="SW")
	{
	CVector vz(0,0,1,0);
	CVector vx(1,0,0,0);
	CVector vy(0,-1,0,0);
	CVector c;
	CVector vzc,vxc,vyc;
	initVect();
	TRotatex(pi/3);
	TRotate((3*pi)/4);
	endT();

	}
}

void CTVector::setCam(CVector vx, CVector vy, CVector vz,CVector vo)
{

	CVector servant;
	servant.pvecx.x=vx.x;
	servant.pvecx.y=vx.y;
	servant.pvecx.z=vx.z;
	servant.pvecx.w=0;

	servant.pvecy.x=vy.x;
	servant.pvecy.y=vy.y;
	servant.pvecy.z=vy.z;
	servant.pvecy.w=0;

	servant.pvecz.x=vz.x;
	servant.pvecz.y=vz.y;
	servant.pvecz.z=vz.z;
	servant.pvecz.w=0;

	servant.pvec0.x=vo.x;
	servant.pvec0.y=vo.y;
	servant.pvec0.z=vo.z;
	servant.pvec0.w=vo.w;
	
	vector<CVector> resi(4*4);
	double *N;
	N=new double[4*4];

	double Dx[5], Dy[5],Dz[5],Dw[5];

	Dx[0]=1;
	Dx[1]=0;
	Dx[2]=0;
	Dx[3]=0;

	Dy[0]=0;
	Dy[1]=1;
	Dy[2]=0;
	Dy[3]=0;

	Dz[0]=0;
	Dz[1]=0;
	Dz[2]=1;
	Dz[3]=0;

	Dw[0]=0;
	Dw[1]=0;
	Dw[2]=0;
	Dw[3]=1;

	CMatrix mat;


	N[0]=servant.pvecx.x;
	N[1]=servant.pvecx.y;
	N[2]=servant.pvecx.z;
	N[3]=servant.pvecx.w;

	N[4]=servant.pvecy.x;
	N[5]=servant.pvecy.y;
	N[6]=servant.pvecy.z;
	N[7]=servant.pvecy.w;
	
	N[8]=servant.pvecz.x;
	N[9]=servant.pvecz.y;
	N[10]=servant.pvecz.z;
	N[11]=servant.pvecz.w;

	N[12]=servant.pvec0.x;
	N[13]=servant.pvec0.y;
	N[14]=servant.pvec0.z;
	N[15]=servant.pvec0.w;
//	mat.Transpose(N,4,4);
	
	
	mat.LUG(Dx,N,3,3,1);
	mat.LUG(Dy,N,3,3,1);
	mat.LUG(Dz,N,3,3,1);
	mat.LUG(Dw,N,3,3,1);

	for(int i=0;i<4;i++)
	{
		CVector v;
		v.x=Dx[i];
		v.y=Dy[i];
		v.z=Dz[i];
		if(fabs(v.x)<1E-5) v.x=0;
		if(fabs(v.y)<1E-5) v.y=0;
		if(fabs(v.z)<1E-5) v.z=0;
//		if(i!=3) v=v/absc(v);
		v.w=Dw[i];

		resi[i].x=v.x;
		resi[i].y=v.y;
		resi[i].z=v.z;
		resi[i].w=v.w;
	}

	servant.pvecix.x=resi[0].x;
	servant.pvecix.y=resi[0].y;
	servant.pvecix.z=resi[0].z;
	servant.pvecix.w=resi[0].w;

	servant.pveciy.x=resi[1].x;
	servant.pveciy.y=resi[1].y;
	servant.pveciy.z=resi[1].z;
	servant.pveciy.w=resi[1].w;

	servant.pveciz.x=resi[2].x;
	servant.pveciz.y=resi[2].y;
	servant.pveciz.z=resi[2].z;
	servant.pveciz.w=resi[2].w;

	servant.pveci0.x=resi[3].x;
	servant.pveci0.y=resi[3].y;
	servant.pveci0.z=resi[3].z;
	servant.pveci0.w=resi[3].w;

	delete []N;

}

void CTVector::setWorld(CVector vx, CVector vy, CVector vz,CVector vo)
{

	CVector servant;
	servant.vecx.x=vx.x;
	servant.vecx.y=vx.y;
	servant.vecx.z=vx.z;
	servant.vecx.w=vx.w;

	servant.vecy.x=vy.x;
	servant.vecy.y=vy.y;
	servant.vecy.z=vy.z;
	servant.vecy.w=vy.w;

	servant.vecz.x=vz.x;
	servant.vecz.y=vz.y;
	servant.vecz.z=vz.z;
	servant.vecz.w=vz.w;

	servant.vec0.x=vo.x;
	servant.vec0.y=vo.y;
	servant.vec0.z=vo.z;
	servant.vec0.w=vo.w;
	
	vector<CVector> resi(4*4);
	double *N;
	N=new double[4*4];

	double Dx[5], Dy[5],Dz[5],Dw[5];

	Dx[0]=1;
	Dx[1]=0;
	Dx[2]=0;
	Dx[3]=0;

	Dy[0]=0;
	Dy[1]=1;
	Dy[2]=0;
	Dy[3]=0;

	Dz[0]=0;
	Dz[1]=0;
	Dz[2]=1;
	Dz[3]=0;

	Dw[0]=0;
	Dw[1]=0;
	Dw[2]=0;
	Dw[3]=1;

	CMatrix mat;


	N[0]=servant.vecx.x;
	N[1]=servant.vecx.y;
	N[2]=servant.vecx.z;
	N[3]=servant.vecx.w;

	N[4]=servant.vecy.x;
	N[5]=servant.vecy.y;
	N[6]=servant.vecy.z;
	N[7]=servant.vecy.w;
	
	N[8]=servant.vecz.x;
	N[9]=servant.vecz.y;
	N[10]=servant.vecz.z;
	N[11]=servant.vecz.w;

	N[12]=servant.vec0.x;
	N[13]=servant.vec0.y;
	N[14]=servant.vec0.z;
	N[15]=servant.vec0.w;
//	mat.Transpose(N,4,4);
	
	
	mat.LUG(Dx,N,3,3,1);
	mat.LUG(Dy,N,3,3,1);
	mat.LUG(Dz,N,3,3,1);
	mat.LUG(Dw,N,3,3,1);

	for(int i=0;i<4;i++)
	{
		CVector v;
		v.x=Dx[i];
		v.y=Dy[i];
		v.z=Dz[i];
		
//		if(i!=3) v=v/absc(v);
		v.w=Dw[i];

		resi[i].x=v.x;
		resi[i].y=v.y;
		resi[i].z=v.z;
		resi[i].w=v.w;
	}

	servant.vecix.x=resi[0].x;
	servant.vecix.y=resi[0].y;
	servant.vecix.z=resi[0].z;
	servant.vecix.w=resi[0].w;

	servant.veciy.x=resi[1].x;
	servant.veciy.y=resi[1].y;
	servant.veciy.z=resi[1].z;
	servant.veciy.w=resi[1].w;

	servant.veciz.x=resi[2].x;
	servant.veciz.y=resi[2].y;
	servant.veciz.z=resi[2].z;
	servant.veciz.w=resi[2].w;

	servant.veci0.x=resi[3].x;
	servant.veci0.y=resi[3].y;
	servant.veci0.z=resi[3].z;
	servant.veci0.w=resi[3].w;
	delete []N;

}



void CTVector::setsnapplane(CString s)
{
	CVector v,servant;

	if(s=="front")
	{
		v.setplanesnap("front");
	}
	else if(s=="left")
	{
		v.setplanesnap("left");
	}
	else if(s=="top")
	{
		v.setplanesnap("top");
	}else
	{
		v.setplanesnap("null");
	}

}

void CTVector::Project(CVector n)
{
	vx.x=1-pow(n.x,2);
	vx.y=-n.x*n.y;
	vx.z=-n.x*n.z;
	vx.w=0;
	base.push_back(vx);
	vy.x=-n.x*n.y;
	vy.y=1-pow(n.y,2);
	vy.z=-n.z*n.y;
	vy.w=0;
	base.push_back(vy);
	vz.z=1-pow(n.z,2);
	vz.y=-n.y*n.z;
	vz.x=-n.x*n.z;
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);

}

void CTVector::Reflect(CVector n)
{
	vx.x=1-2*pow(n.x,2);
	vx.y=-2*n.x*n.y;
	vx.z=-2*n.x*n.z;
	vx.w=0;
	base.push_back(vx);
	vy.x=-2*n.x*n.y;
	vy.y=1-2*pow(n.y,2);
	vy.z=-2*n.z*n.y;
	vy.w=0;
	base.push_back(vy);
	vz.z=1-2*pow(n.z,2);
	vz.y=-2*n.y*n.z;
	vz.x=-2*n.x*n.z;
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);

}

void CTVector::Scale(CVector n, float f)
{
	vx.x=1+(f-1)*n.x*n.x;
	vx.y=(f-1)*n.x*n.y;
	vx.z=(f-1)*n.x*n.z;
	vx.w=0;
	base.push_back(vx);
	vy.x=(f-1)*n.x*n.y;
	vy.y=1+(f-1)*n.y*n.y;
	vy.z=(f-1)*n.z*n.y;
	vy.w=0;
	base.push_back(vy);
	vz.x=(f-1)*n.x*n.z;
	vz.y=(f-1)*n.y*n.z;
	vz.z=1+(f-1)*n.z*n.z;
	vz.w=0;
	base.push_back(vz);
	v0r.x=0;
	v0r.y=0;
	v0r.z=0;
	v0r.w=1;
	base.push_back(v0r);

}

void CTVector::savefile(CFile &file)
{
	CVector servant;
	file.Write(&servant.b,sizeof(servant.b));
	file.Write(&servant.t,sizeof(servant.t));
	file.Write(&servant.l,sizeof(servant.l));
	file.Write(&servant.r,sizeof(servant.r));
	file.Write(&servant.f,sizeof(servant.f));
	file.Write(&servant.n,sizeof(servant.n));
	file.Write(&servant.Sx,sizeof(servant.Sx));
	file.Write(&servant.Sy,sizeof(servant.Sy));
	file.Write(&servant.perspec,sizeof(bool));
	servant.pvec0.savefile(file);
	servant.pveci0.savefile(file);
	servant.pvecx.savefile(file);
	servant.pvecix.savefile(file);
	servant.pvecy.savefile(file);
	servant.pveciy.savefile(file);
	servant.pvecz.savefile(file);
	servant.pveciz.savefile(file);
}

void CTVector::openfile(CFile &file)
{
	CVector servant;
	file.Read(&servant.b,sizeof(servant.b));
	file.Read(&servant.t,sizeof(servant.b));
	file.Read(&servant.l,sizeof(servant.b));
	file.Read(&servant.r,sizeof(servant.b));
	file.Read(&servant.f,sizeof(servant.b));
	file.Read(&servant.n,sizeof(servant.b));
	file.Read(&servant.Sx,sizeof(servant.Sx));
	file.Read(&servant.Sy,sizeof(servant.Sx));
	file.Read(&servant.perspec,sizeof(bool));
	servant.pvec0.openfile(file);
	servant.pveci0.openfile(file);
	servant.pvecx.openfile(file);
	servant.pvecix.openfile(file);
	servant.pvecy.openfile(file);
	servant.pveciy.openfile(file);
	servant.pvecz.openfile(file);
	servant.pveciz.openfile(file);
}
LONG CTVector::Readfile(CFile &file)
{
	CVector servant;
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.b),CFile::current);
	file.Seek(sizeof(servant.Sx),CFile::current);
	file.Seek(sizeof(servant.Sx),CFile::current);
	file.Seek(sizeof(bool),CFile::current);
	servant.pvec0.Readfile(file);
	servant.pveci0.Readfile(file);
	servant.pvecx.Readfile(file);
	servant.pvecix.Readfile(file);
	servant.pvecy.Readfile(file);
	servant.pveciy.Readfile(file);
	servant.pvecz.Readfile(file);
	return servant.pveciz.Readfile(file);
}

void CTVector::TCam(CVector v1x, CVector v1y, CVector v1z, CVector v1o)
{
	vx.x=v1x.x;
	vx.y=v1y.x;
	vx.z=v1z.x;
	vx.w=0;
	base.push_back(vx);
	vy.x=v1x.y;
	vy.y=v1y.y;
	vy.z=v1z.y;
	vy.w=0;
	base.push_back(vy);
	vz.x=v1x.z;
	vz.y=v1y.z;
	vz.z=v1z.z;
	vz.w=0;
	base.push_back(vz);
	CVector vtx(v1x.x,v1y.x,v1z.x),vty(v1x.y,v1y.y,v1z.y),vtz(v1x.z,v1y.z,v1z.z);
	v0r.x=-v1o.dot(vtx);;
	v0r.y=-v1o.dot(vty);
	v0r.z=-v1o.dot(vtz);
	v0r.w=1;
	base.push_back(v0r);

}

void CTVector::create()
{

}
