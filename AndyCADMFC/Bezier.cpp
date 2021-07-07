// Bezier.cpp: implementation of the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#include "PCH.h"
#include "AndyCADMFC.h"
#include "CVector.h"
#include "Bezier.h"
#include "Matrix1.h"
#include "Inter.h"
#include <algorithm>
#include <functional>
#include "ray.h"
#include "line.h"
#include <process.h>
#include "ffd.h"
#include "render.h"
#include "plane.h"
#include "cam.h"
#include "geometry.h"
#include <stdlib.h>
#include "image.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//CMemoryState oldMemState, newMemState, diffMemState;
float CBezier::EXTRUSC=100;
CRender render;
CMesh* smesh=NULL;
CVector pCt;
CCAM cam;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	CCVector CBezier::S_spec(0.5,0.5,0.5);
	CCVector CBezier::M_spec(0.5,0.5,0.5);
	CCVector CBezier::S_diff(S_spec);
	CCVector CBezier::G_amb(1,1,1);//255,255,255);
	CVector CBezier::lsou(0,0,10);
	CVector CBezier::view(getcamor());
	float CBezier::m_gls=0;
	bool CBezier::dtri=true;

struct t_param
{
   CVector* M;
	int i;
	int j;
	CBezier* object;
	HANDLE mutex;
	t_param(CBezier* b):object(b){
	};
};
HANDLE thread[1000];
DWORD WINAPI NURBSp(LPVOID l)
{
  t_param* t=(t_param*) l;
  CBezier* object=t->object;
  int i=t->i;
  int j=t->j;
 
  CVector nsu;
  CVector nsv;
  CVector ns;
 // WaitForSingleObject(t.mutex,INFINITE);   
  nsu=object->Sur_deriv(object->deg,object->deg1,object->C,object->ncp,object->ncp1,object->Para[i],object->Para1[j],object->Kn,object->Kn1,object->Para,true,false);
  nsv=object->Sur_deriv(object->deg,object->deg1,object->C,object->ncp,object->ncp1,object->Para[i],object->Para1[j],object->Kn,object->Kn1,object->Para,false,true);
  ns=nsu*nsv;
  ns=ns/absc(ns);
  nsu=object->NURBS(object->deg,object->deg1,object->C,\
	  object->ncp,object->ncp1,object->Para[i],\
	  object->Para1[j],object->Kn,object->Kn1);

  CVertex vertex(nsu,object->Para[i],object->Para1[j]);
  vertex.setnormal(ns);
	 *object->mesh.Vertex((object->N+1)*j+i)=vertex;
	delete l;  
//	CloseHandle(thread[j*object->N+i]);
  return NULL;
}

CBezier::CBezier()
{
/*	#ifdef _DEBUG
    oldMemState.Checkpoint();
    #endif
*/
	init();
//	Para=new double[N+1];
/*	if(smesh==NULL)
	{
	smesh=new CMesh;
	sphere(smesh);
	}*/
}
CBezier::CBezier(int degree,vector<CVector>& mpoint,bool fit,CDC* hdc)
{
	init();

	handle=0;
	tas=0;
	j=0;
	move=false;fPrevB=false;

    ncpe=0;
   	cancharge=false;
	name="CBezier";
	lkp=0;
	Pprev=NULL;
	minpara=0;
	maxpara=1;
  

	N=150; //point on the line
   Para.resize(N+1);
   Para1.resize(N+1);
   Para2.resize(N+1);
   Kn.resize(10);
//   Kn1.resize(50);
//   Kn2.resize(50);
	deg=degree;           // degree of polynomial = t-1
    vector<CVector> pts;//[100];
	vector<CVector>::iterator rsult;

	if(fit){
		ncp=mpoint.size()-1;	
		int i=0;
		Para_universp(0,1,N,Para);
		Knot_Univer(ncp+degree-1,degree,Kn,0,1);
		vector<CVector> vi;

		int ncpi=ncp;
		ContP.resize(ncp+(degree-1)+1);
 		INT_curve(mpoint,ncp,degree,Kn,Kn,ContP);
 		ncp+=(degree-1);
//		for(int ji=1;ji<ncpi;ji++)
//		{
//			addnode(mpoint[ji],NULL);
//		}
	if(!hdc)
	{
		vMr.resize(N);

//   Para_universp(0,1,N,Para);
		for(int iter=0;iter<N;iter++)
		{
			vMr[iter]=NURBS(deg,ContP,ncp+1,Para[iter],Kn);
		}
	}
	}else
	{
		ncp=mpoint.size()-1;
		Para_universp(0,1,N,Para);
		Knot_Univer(ncp,degree,Kn,0,1);
//		Knot_UniverSp(0,1,ncp+1,deg,Kn);
		ContP.resize(ncp+1);
		for(int ji=0;ji<=ncp;ji++)
		{
			
			ContP[ji]=mpoint[ji];
		}
	if(!hdc)
	{
		vMr.resize(N);

//   Para_universp(0,1,N,Para);
		for(int iter=0;iter<N;iter++)
		{
			vMr[iter]=NURBS(deg,ContP,ncp-1,Para[iter],Kn);
		}
	}
	}
    getCharge(hdc);
}
CBezier::CBezier(int degree,vector<CVector>& mpoint,vector<float>& mknts,bool fit,CDC* hdc)
{
	init();

	handle=0;
	tas=0;
	j=0;
	move=false;fPrevB=false;

    ncpe=0;
   	cancharge=false;
	name="CBezier";
	lkp=0;
	Pprev=NULL;
	minpara=0;
	maxpara=1;
  

	N=150; //point on the line
	int nknts=mknts.size();
   Para.resize(N+1);
   Para1.resize(N+1);
   Para2.resize(N+1);
   Kn.resize(nknts);
//   Kn1.resize(50);
//   Kn2.resize(50);
	deg=degree;           // degree of polynomial = t-1
    vector<CVector> pts;//[100];
	vector<CVector>::iterator rsult;

	if(fit){
		ncp=mpoint.size()-1;	
		int i=0;
		Para_universp(0,1,ncp+degree,Para);
		Knot_Univer(ncp+degree-1,degree,Kn,0,1);
		vector<CVector> vi;

		int ncpi=ncp;
		ContP.resize(ncp+(degree-1)+1);
 		INT_curve(mpoint,ncp,degree,Kn,Kn,ContP);
 		ncp+=(degree-1)+1;
		for(int ji=1;ji<ncpi;ji++)
		{
			addnode(mpoint[ji],NULL);
		}
	}else
	{
		ncp=mpoint.size();
//		Para_universp(0,1,ncp+degree,Para);
//		Knot_Univer(ncp+1,degree,Kn,0,1);
		ContP.resize(ncp);
		for(int ji=0;ji<ncp;ji++)
		{
			
			ContP[ji]=mpoint[ji];
		}
		for(ji=0;ji<nknts;ji++)
		{
			
			Kn[ji]=mknts[ji];
		}
	if(!hdc)
	{
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
//	   vMr[iter]=NURBS(deg,ContP,ncp-1,Para[iter],Kn);
	   vMr[iter]=Bspline(deg,ContP,ncp-1,Para[iter],Kn);
   }
	}
	}
//   vMr.resize(N);

//   Para_universp(0,1,N,Para);

/*   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,ContP,ncp+1,Para[iter],Kn);
   }*/
    getCharge(hdc);
}
CBezier::~CBezier()
{
  // delete [] CP;
  // delete[] Kn;

    Para.clear();
    Para1.clear();
	Para2.clear();
	Kn.clear();
	Kn0.clear();
	Kn2.clear();
	Kn1.clear();
	CP.clear();
	C.clear();


/*	if(surf)
	{
	   delete [] Ptr;
	   delete [] Pt1r;
	}*/
	redraw=false;
//	if(Mr!=NULL) delete []Mr;
	if(FFDbox!=NULL)
		delete FFDbox;
/*	#ifdef _DEBUG
    newMemState.Checkpoint();
    #endif

	if( diffMemState.Difference( oldMemState, newMemState ) )
	{
    TRACE( "Memory leaked!\n" );
    diffMemState.DumpAllObjectsSince();
	}

*/
}

vector<CVector> CBezier::getSvec()
{
   CVector *M=new CVector[N+1];
//   Para=new double[N+1];
   Para_universp(minpara,maxpara,N,Para);

   vector<CVector> svec;
   indexvec.clear();
   indexpos.clear();
   int lk=Kn[deg]*N;

   CVector nb;
   CVector nbplus;
 //  CVector vn;

 	CVector v2,v3;
	double v11,v12,v22,v32;
   CVector ln;	
   CVector intp;
  
   for(int iter=0;iter<=N-1;iter=iter+1)
   {
	   nb=NURBS(deg,CP,ncp,Para[iter],Kn);
	   nbplus=NURBS(deg,CP,ncp,Para[iter+1],Kn);
	   CRay vn(nb,nbplus,1);
	  // CVector ln=intvec[0]*intvec[2];	
	  // CVector intp=ln*vn;

	   CVector v(nb,nbplus);
		v2=nb+nbplus;
		v2=v2/2;

		v11=absc(v2-nb);
	for(vector<CVector>::iterator it=intvec.begin();it<intvec.end();it=it+3)
	{
	   CRay ln(*it,*(it+2),1);	
/*	   ln=(*it).intersect((*(it+2)));	
	   v3=(*it)+(*(it+2));
	   v3=v3/2;

	   v22=absc(v3-(*it));
*/	   intp=vn.Intersect(ln);
	

	  if (intp.x!=1E-10)
	  {
/*		v12=absc(v2-intp);
		v32=absc(v3-intp);
		  if((v12<=v11)&&(v32<=v22+5))
		  {*/
		  indexvec.push_back(iter);
		  indexpos.push_back(intp);
		  svec.push_back(nb);
		  svec.push_back(nb);
		  svec.push_back(nbplus);
		 // }
	  }
	}
	 }

   delete []M;
//   delete []Para;
	return svec;
}
void CBezier::OffsetMesh(float u, CFigure *f)
{
//	getMesh()->offset(u,f->getMesh());
	mesh2.empty();
	   for(int iter=0;iter<ncp;iter++)
		{
		   float u=(float)iter/ncp;
		   mesh2.addVertex (new CVertex(ContP[iter],u,0));
		}
	   for(iter=0;iter<ncp-1;iter++)
		{
	       new CEdge(mesh2.Vertex(iter),mesh2.Vertex(iter + 1),mesh2.Ecount());
		}
	CMesh mesh3;
	mesh3.copy(&mesh2);
	mesh2.offset(u,&mesh3);
	CBezier* f2=(CBezier*)f;
	vector<CVector> vb=mesh3.getVectors();
	f2->ContP.clear();
	f2->vMr.clear();
	for(int i=0;i<vb.size();i++)//vector<CVector>::iterator i=vb.begin();i<vb.end();i++)
	{
	CVector v1=vb[i];
	v1.w=CP[i].w;
	f2->ContP.push_back(v1);//
	}//copy(=mesh3.getVectors();
	f2->addtovecBezier();
}

vector<CFigure*> CBezier::Trim(vector<CVector>& v1,CFigure *f,bool side,bool st)
{
	CFigure::Trim(v1,f,side,st);
	vector<CFigure*> b0,b;
	int _i=0;
	int j=v1.size(),j1;
	if(j==1)
	{
		b0=breakcurve2(v1[0],v1[0]);
		b.insert(b.begin(),b0[0]);
		return b;
	}
	CBezier *vb=new CBezier();
	vb->copy(this);
	vector<CFigure*>::iterator ib;
	for(vector<CVector>::iterator i=v1.begin();i<v1.end();i=i+2,_i++)
	{
		b0=vb->breakcurve2(*i,*(i+1));
		ib=find(b.begin(),b.end(),(CFigure*)vb);
		if(ib!=b.end())
			b.erase(ib);
		b.insert(b.begin(),b0.begin(),b0.end());
		vb=(CBezier*)b0.back();
	}
	if(j%2==1)
	{
		b0=vb->breakcurve2(v1[_i-1],v1[_i-1]);
		b.push_back(b0[0]);
		return b;
	}
	return b;
	_i=0;
	vector<CFigure*>::iterator i1;
	for(vector<CFigure*>::iterator i0=b.begin();i0<b.end();i0++,_i++)
	{
		if(_i==1)
		{
			i0=b.erase(i0);
			i1=i0+1;
			if(i1<b.end())
			{
				i0=i1;
				i0=b.erase(i0);
			}
			_i=-1;
		}
	}
	return b;
}
void* CBezier::Trim(vector<CVector> vec)
{
	vector<CVector> *arr= new vector<CVector>[2];
	vector<CVector> resultb, resulte;

	indexvec.push_back(petit);indexpos.push_back(v0);
	indexvec.push_back(0);indexpos.push_back(NURBS(deg,CP,ncp,Para[0],Kn));
	indexvec.push_back(N);indexpos.push_back(NURBS(deg,CP,ncp,Para[N],Kn));
	int minv;
	int mxmin;
	CVector minp,maxp;
	redraw=true;

	for(int j=0;j<indexvec.size();j++)
	{
		for(int i=0;i<indexvec.size()-1;i++)
		{
			minv=indexvec[i];minp=indexpos[i];
			mxmin=indexvec[i+1];maxp=indexpos[i+1];
			if(minv>mxmin)
			{
				int mmv=minv; CVector mmp=minp;
				minv=mxmin;minp=maxp;
				mxmin=mmv;maxp=mmp;

			}
			indexvec[i]=minv;indexpos[i]=minp;
			indexvec[i+1]=mxmin;indexpos[i+1]=maxp;
		}
		
	}

	int indexpetit;
	for(j=0;j<indexvec.size();j++)
	{
		if(indexvec[j]==petit)
		{
			indexpetit=j;
	
		}
	}
//	if((indexpetit!=0)&&(indexpetit<indexvec.size()-1)&&(indexvec.size()>2))
//	{
	double _T[50];
	CBezier *bs=new CBezier;
	bs->copy(this);
	CVector p,pp;
//	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
	p=NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	pp=NURBS(deg,CP,ncp,Para[indexvec[indexpetit+1]],Kn);
	cl=false;

	//prevref=indexvec[indexpetit+1];

	int s=0;
	int g;
		for(int iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	s=0;
		for(iter=0;iter<=ncp+deg+1;iter++)
		{
			if(Kn[iter]==Para[indexvec[indexpetit+1]])
			{
				s++;
			}
		}
		for(g=0;g<deg-s;g++)
		{
			Bohms(Para[indexvec[indexpetit+1]], deg,Kn,CP,ncp);	
		}

	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				bs->Kn[i]=Kn[i];
				h++;
			}
		}
		bs->Kn[h]=bs->Kn[h-1];
		bs->minpara=bs->Kn[0];
		bs->maxpara=bs->Kn[h];

		for(i=0;i<=h;i++)
		{
			bs->Kn[i]=(bs->Kn[i]-bs->minpara)/(bs->maxpara-bs->minpara);
		}
		bs->minpara=0;
		bs->maxpara=1;


	int b;
		for(i=0;i<=deg;i++)
		{
			_T[i]=Para[indexvec[indexpetit+1]];
		}
		
		b=i;
		
		for(i=deg;i<=ncp+deg+1;i++)
		{
			if(Kn[i]>Para[indexvec[indexpetit+1]])
			{
				_T[b]=Kn[i];
				b++;
			}
		}

	for(i=0;i<b;i++)
	{
		Kn[i]=_T[i];
	}
	minpara=Kn[0];
	maxpara=Kn[b-1];

	for(i=0;i<b;i++)
	{
		Kn[i]=(Kn[i]-minpara)/(maxpara-minpara);
	}
	minpara=0;
	maxpara=1;


//	if (!cl)
//	{	
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	bs->CP[nn]=indexpos[indexpetit-1];//CP[mi];
	if(nn==0)
	{
	//	bs->x=-1;
	}
//	if(nn==ncp)
	bs->ncp=nn;
	bs->addtovec();
	bs->deg=deg;

	int kj=1E10;;
	for(i=0;i<=ncp;i++)
	{
		if(pp==CP[i])
		{
		kj=i;
		break;
		}
	}
	nn=0;
	for(i=kj;i<=ncp;i++)
	{
		CP[i-kj]=CP[i];
		nn++;
	}
	CP[0]=indexpos[indexpetit+1];

	Para_universp(bs->minpara,bs->maxpara,N,bs->Para);
	ncp=nn-1;
	addtovec();
	return bs;
//	}
/*	else if(indexpetit==0)
	{
	double T[50];
	CBezier *bs=new CBezier;
	*bs=*this;
	CVector p,pp;
	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
	pp=NURBS(deg,CP,ncp,Para[indexvec[indexpetit+1]],Kn);
	cl=false;
	
	int s=0;
	int g;
	s=0;
		for(int iter=0;iter<=ncp+deg+1;iter++)
		{
			if(Kn[iter]==Para[indexvec[indexpetit+1]])
			{
				s++;
			}
		}
		for(g=0;g<deg-s;g++)
		{
			Bohms(Para[indexvec[indexpetit+1]], deg,Kn,CP,ncp);	
		}

	int h=0;
	int b;
		for(i=0;i<=deg;i++)
		{
			T[i]=Para[indexvec[indexpetit+1]];
		}
		
		b=i;
		
		for(i=deg;i<=ncp+deg+1;i++)
		{
			if(Kn[i]>Para[indexvec[indexpetit+1]])
			{
				T[b]=Kn[i];
				b++;
			}
		}

	for(i=0;i<b;i++)
	{
		Kn[i]=T[i];
	}
	minpara=Kn[0];
	maxpara=Kn[b-1];

	int nn=0;
	bs->x=-1;
	int kj;
	for(i=0;i<=ncp;i++)
	{
		if(pp==CP[i])
		{
		kj=i;
		break;
		}
	}
	nn=0;
	for(i=kj;i<=ncp;i++)
	{
		CP[i-kj]=CP[i];
		nn++;
	}
	CP[0]=indexpos[indexpetit+1];

	bs->Para=new double[N+1];
	Para_universp(bs->minpara,bs->maxpara,N,bs->Para);
	ncp=nn-1;
	addtovec();
	delete []Para;
	return bs;

	}
	else if(indexvec[indexpetit]==indexvec[indexvec.size()-1])
	{
	double T[50];
	CBezier *bs=new CBezier;
	*bs=*this;
	CVector p,pp;
	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
	p=NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	cl=false;

	int s=0;
	int iter;
	int g;
		for(iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				Kn[i]=Kn[i];
				h++;
			}
		}
		Kn[h]=Kn[h-1];
		minpara=Kn[0];
		maxpara=Kn[h];


	int b;
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	CP[nn]=indexpos[indexpetit-1];//CP[mi];

	bs->x=-1;
	
	ncp=nn;
	addtovec();
	delete []Para;
	return bs;

	}
	else if((indexpetit==deg)||(indexpetit==1))
	{
	double T[50];
	CBezier *bs=new CBezier;
	*bs=*this;
	CVector p,pp;
	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
//	bs-cl
	p=NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	cl=false;

	int s=0;
	int iter;
	int g;
		for(iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				Kn[i]=Kn[i];
				h++;
			}
		}
		Kn[h]=Kn[h-1];
		minpara=Kn[0];
		maxpara=Kn[h];


	int b;
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	bs->CP[nn]=	indexpos[indexpetit+1];//CP[mi];

	bs->x=-1;
	
	ncp=nn;
	addtovec();
	delete []Para;
	return bs;

	}*/

}
vector<CFigure*> CBezier::delbezier(CVector v1,CVector v2)
{
	CBezier* z1=new CBezier(),*z2=new CBezier();
	z1->copy(this);z2->copy(this);
		bool c=false;
	//	drawdel(hdc);
		int i,k,i0=0,ip=0;
		for(i=0;i<ncp;i=i+3,i0++)
		{
			if(pointinRegion(v1,ContP[i]))
			{
				ip=i0;
				k=i+1;
				c=true;
				break;
			}
		}
		if(c)
		{
			z1->ContP.erase(z1->ContP.begin()+k,z1->ContP.end());
			z1->ncp=i0+1;
			double irep=0;
			int i0=0;
			int _i1=0;
			vector<int> vecpos;
			for(vector<double>::iterator _i=Kn.begin();_i!=Kn.end();_i++,_i1++)
			{
				if(*_i==irep)
				{
					i0++;
					if((i0==deg-1)&&(*_i!=0))
					{
						vecpos.push_back(_i1-deg);
						i0=0;
					}
				}else
				{
						i0=0;
				}
					irep=*_i;
					if(*_i==1) break;
			}

			z1->Kn.erase(z1->Kn.begin()+vecpos[ip-1]+deg+1,z1->Kn.end());
			z1->Kn.push_back(z1->Kn[vecpos[ip-1]+1]);

			z1->addtovecBezier();
		}

			i0=0;
			k=0;
		//	c=false;
			ip=0;
			for(i=0;i<ncp;i=i+3,i0++)
			{
				if(pointinRegion(v2,ContP[i]))
				{
					ip=i0;
					k=i;
					c&=true;
					break;
				}
			}
		if(c)
		{
			z2->ContP.erase(z2->ContP.begin(),z2->ContP.begin()+k);
			z2->ncp=ncp-i;
			double irep=0;
			int _i1=0;
			vector<int> vecpos;
			for(vector<double>::iterator _i=Kn.begin();_i!=Kn.end();_i++,_i1++)
			{
				if(*_i==irep)
				{
					i0++;
					if((i0==deg-1)&&(*_i!=0))
					{
						vecpos.push_back(_i1-deg);
						i0=0;
					}
				}else
				{
						i0=0;
				}
					irep=*_i;
					if(*_i==1) break;
			}

			z2->Kn.erase(z2->Kn.begin(),z2->Kn.begin()+vecpos[ip-1]+1);
			z2->Kn.insert(z2->Kn.begin(),z2->Kn[0]);

			z2->addtovecBezier();

		}
		vector<CFigure*> vp;
		if(c)
		{
		vp.push_back(z1);
		vp.push_back(z2);
		}
		return vp;
}

vector<CFigure*> CBezier::breakcurve2(CVector v1,CVector v2)
{
	CBezier *b=new CBezier();
	b->copy(this);
	if(v1!=v2)
	{
	v1=addnode(v1,NULL);
	v2=addnode(v2,NULL);
	}else
	{
	v1=addnode(v1,NULL);
	v2=v1;
	}
	vector<CFigure*> bo=delbezier(v1,v2);
	delete b;
	return bo;
}
void* CBezier::breakcurve(CVector point) 
{
	double T[50];
	CBezier *bs=new CBezier;
	CVector p;
	petit=PtonSpline(point);
//	Para=new double [N+1];
	Para_universp(0,1,N,Para);
	int i,k;
	bs->linestate=linestate;
	p=NURBS(deg,CP,ncp,Para[petit],Kn);

	int s=0;
	for(int iter=0;iter<=ncp+deg+1;iter++)
	{
		if(Kn[iter]==Para[petit])
		{
			s++;
		}
	}
	for(int g=0;g<deg-s;g++)
	{
	Bohms(Para[petit], deg,Kn,CP,ncp);	
	}
		
	int h=0;
	for(i=0;i<=ncp+deg+1;i++)
	{
		if(Kn[i]<=Para[petit])
		{
			bs->Kn[i]=Kn[i];
			h++;
		}
	}
	bs->Kn[h]=bs->Kn[h-1];
	for(i=0;i<=deg;i++)
	{
		T[i]=Para[petit];
	}
	int b=i;
	for(i=deg;i<=ncp+deg+1;i++)
	{
		if(Kn[i]>Para[petit])
		{
			T[b]=Kn[i];
			b++;
		}
	}
	for(i=0;i<b;i++)
	{
		Kn[i]=T[i];
	}
//	if (!cl)
//	{	
	int nn=0;;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else break;
	}
	bs->CP[nn]=p;
	CP[0]=p;

	for(i=1;i<=ncp-nn;i++)
	{
		CP[i]=CP[nn+i];
	}
	bs->ncp=nn;
	bs->addtovec();
	bs->deg=deg;
	
//	bs->Para=new double[N+1];
	Para_universp(0,1,N,bs->Para);
	ncp=ncp-nn;
	addtovec();
//	delete []Para;
	return bs;

	/*	}
	else
	{
		CP[0]=point;
		CP[1]=
		for(int i=1;i<=ncp;i++)
		{
			CP[i]=
		}
		CPoint;
	}*/


}




void CBezier::closecurve(CVector point,CDC *hdc)
{
	cl=true;
	return;
/*	if(!surf)
	{
	drawdel(hdc);
	int i,k;

	vector<CVector> v;
	v.push_back(ptbegin.front());
	v.push_back(ptend.back());


	UpdateSM();
	linestate=D4;
	selectSM(hdc);
	}
	draw(hdc);*/
/*	vector<CBezier*> fg;
	vector<CBezier*>::iterator it;
	vector<CVector> m;
	vector<CVector>::iterator iter,itere;
	CBezier *b=new CBezier(ptbegin.front(),ptbegin.back());
	buildcubicspline(b);
	getCharge();
	delete b; 

*/
	for(int i=0;i<ncp+deg+1;i++)
	{
		Kn[i]/=2;
	}
	Kn[i++]=1;
	Kn[i++]=1;
	Kn[i++]=1;
	Kn[i++]=1;
	redraw=true;
	CP.resize(CP.size()+3);
	CP[ncp+3]=CP[0];
	CP[ncp+1]=CP[0]*((float)1/3)+CP[ncp+2]*((float)2/3);
	CP[ncp+2]=CP[0]*((float)2/3)+CP[ncp+2]*((float)1/3);
	ContP.resize(ContP.size()+3);
	ContP[ncp+3]=CP[0];
	ContP[ncp+1]=CP[0]*((float)1/3)+CP[ncp+2]*((float)2/3);
	CP[ncp+2]=CP[0]*((float)2/3)+CP[ncp+2]*((float)1/3);
	ncp+=3;
	addtovec();

}

/*
void CBezier::buildcubicspline(CBezier* fg)
{
	
	int s=fg->size();
	deg=1;
	ncp=s;
//	N=10;
//	 Para_universp(0,1,s,Para);

	 multiset<double> Ks;
	 vector<double> d1(ncp+deg+2);
	 vector<double>::iterator diter;
//     Knot_Univer(ncp,deg,Kn,0,1);
	 int l=0;
	 double m=1,k=0;
	 Kn[0]=0;
	 for(int i=0;i<=deg+ncp+1;i+++)
	 {
		 Kn[i]/=2;
	 }
	 for(i=deg;i<=deg+fg->ncp+1;i+++)
	 {
		 Kn[i]/=fg->Kn[i;
	 }

	 for(int j=1;j<=s+1;j=j+1)//deg+ncp+2;j++)
	 {
		 m=(double)k/s;
		 Kn[j]=m;
//		 Kn[j+1]=m;
//		 Kn[j+2]=m;
		 k++;
	 }
	 Kn[j]=1;

	 vector<CVector>::iterator iter;
	 for(j=0;j<s;j++)
	 {
		for(int k=0;k<=1;k++)
		{
			CP[j*1+k]=(*fg)[j]->CP[k];
		}
	 }
//	 N=100;
//	 ncp-=1;//CP.size()-1;

}
*/
void CBezier::drawselect(CDC *hdc)
{
	if((ffd)&&(select==pnt)) 
	{
		FFDbox->drawselect(hdc);
		return;
	}
	if((click)&&(!spline))
	{
		pitere=ptend.begin();

		if(select==full)
		{
			box.draw(hdc);
		}
		int jj=hdc->SetROP2(R2_COPYPEN);    			
		CPoint pb,pe;

		if((!multiselect)&&(!getLibstatus()))
			updatecore();	
	
		CPen pen;
		pen.CreatePen(PS_COSMETIC,5,RGB(255,0,0));
		CPen *oldp=hdc->SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(42,112,219));
		CBrush *oldb=hdc->SelectObject(&brush);

		vector<CVector>::iterator bonbon;
		if(!surf)
		{
			if(select==pnt)
			{
				int io=0;
				for (piterb=ContP.begin();piterb<ContP.end();piterb++)
				{

					ptsBegin=*piterb;
					ptsEnd=*pitere;
					pb=ptsBegin;
					pe=ptsEnd;
	
					hdc->MoveTo(ptsBegin); 
					hdc->Ellipse(CRect(CPoint(pb.x-15, pb.y+15),CPoint(pb.x+15, pb.y-15)));
					CString sp;
					sp.Format(_T("%d"),io);
			//		hdc->TextOut(ph.x,ph.y,sp);
					CPoint ap(pb.x+35, pb.y+15);
						hdc->TextOut(ap.x,ap.y,sp);
					io++;
					pitere=pitere+1;
				}
					pb=hitpoint;
					CPoint ph=hitpoint;
					hdc->MoveTo(hitpoint); 
					hdc->Ellipse(CRect(CPoint(pb.x-15, pb.y+15),CPoint(pb.x+15, pb.y-15)));
					CString sp;
					sp.Format(_T("%.3f"),jpetit);
			//		hdc->TextOut(ph.x,ph.y,sp);
					CString spx;
					spx.Format(_T("%.3f"),hitpoint.x);
					CString spy;
					spy.Format(_T("%.3f"),hitpoint.y);
					spy="X:"+spx+" Y:"+spy;
			//		hdc->TextOut(ph.x,ph.y+50,spy);

				CPen pen20;
				pen20.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen20);
				for (piterb=ContP.begin();piterb<ContP.end();piterb=piterb+2)
				{
					ptsBegin=*piterb;
					ptsEnd=*(piterb+1);
					CVector ptsEnd1=*(piterb+2);
					if(piterb==ContP.begin())
					{
					hdc->MoveTo(ptsBegin); 
					hdc->LineTo(ptsEnd);
					}else if(ptsEnd1!=ContP.back())
					{
					hdc->MoveTo(ptsBegin); 
					hdc->LineTo(ptsEnd);
					if(ptsEnd!=ContP.back())
						hdc->LineTo(ptsEnd1);
					piterb++;
					}
					if(ptsEnd==ContP.back())
					{
						ptsBegin=*(piterb-1);
						hdc->MoveTo(ptsBegin); 
						ptsEnd=*(piterb);
						hdc->LineTo(ptsEnd);
					}
				}
		
			}
		}
		hdc->SelectObject(oldp);
		CPen pen1;
		pen1.CreatePen(PS_COSMETIC,5,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen1);

		if(!core.empty())
		{
			if(select==full)
			{
				for (bonbon=core.begin();bonbon<core.end()-3;bonbon++)
				{
					hdc->MoveTo(*bonbon); 
					CPoint pbonbon=*bonbon;
					CVector vbonbon;
					vbonbon.x=pbonbon.x;
					vbonbon.y=pbonbon.y;
					vbonbon.z=0;
					if(*bonbon!=core[8])
					{
						hdc->Ellipse(CRect(CPoint(pbonbon.x-13, pbonbon.y+13),CPoint(pbonbon.x+13, pbonbon.y-13)));
					}
				}
				CPoint pt0(rotateCenter);
				hdc->MoveTo(pt0);
		//		hdc->TextOut(pt0.x,pt0.y,"Ol");
				CPoint pt1(core[13]);
				hdc->SelectObject(oldp);
				CPen pen3;
				pen3.CreatePen(PS_GEOMETRIC,5,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen3);
				hdc->Ellipse(CRect(CPoint(pt0.x-13, pt0.y+13),CPoint(pt0.x+13, pt0.y-13)));

				hdc->SelectObject(oldp);
				CPen pen0;
				CBrush brush0;
				LOGBRUSH lb;
				lb.lbStyle=BS_HOLLOW;
				brush0.CreateBrushIndirect(&lb);
				oldb=hdc->SelectObject(&brush0);
				pen0.CreatePen(PS_COSMETIC,4,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen0);
				hdc->Ellipse(CRect(CPoint(pt1.x-17, pt1.y+17),CPoint(pt1.x+17, pt1.y-17)));

				hdc->SelectObject(oldp);
				CPen pen2;
				pen2.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen2);
				
				hdc->LineTo(pt1);
			}

		}

	hdc->SelectObject(oldb);
	hdc->SetROP2(jj);    
	hdc->SelectObject(oldp);

	}
}




CVector CBezier::addnode(CVector point, CDC *hdc)
{
	CVector v=v0,v1=v0,v2=v0;
/*	vector<CVector> onC;
	for(int i=0;i<ncp;i++)
	{
		if(i%3==0)
			onC.push_back(ContP[i]);
	}
	int oc=onC.size();
	vector<int> ioC;
	ioC.resize(oc);
	   for(int iter=0;iter<N;iter++)
	   {
			for(int i=0;i<oc;i++)
			{
			   if(absc(vMr[iter]-onC[i])<5)
			   {
				   ioC[i]=iter;
			   }
			}
	   }
	   int vi=N+1;
	   for(iter=0;iter<N-1;iter++)
	   {
		    CVector nb=vMr[iter];
		    CVector nbplus=vMr[iter+1];
			CVector vpoint(nb,point);
			CVector v9(nb,nbplus);
			CVector v2=nb+nbplus;
			v2=v2/2;

			double v11=absc(v2-nb);
			double v12=absc(v2-point);

			  if ((pointtoVector(v9,vpoint)<5)&&(v12<=v11))
			  {
				v=vMr[iter];
				vi=iter;
				v1=vMr[iter+1];
				v2=vMr[iter-1];
				break;
			  }
	   }
	   if(vi==N+1) return;

		for(i=0;i<oc;i++)
		{
		   if(ioC[i]>vi)
		   {
			   vi=i-1;
			   break;
		   }
		}
		int vi0=vi;
	    for(iter=0;iter<ncp;iter++)
		{
			if(ContP[iter]==onC[vi])
			{
				ContP.insert(ContP.begin()+iter+2,3,onC[vi]);
				vi=iter;
				break;
			}
		}
		double t0=-1,t1=-1;
		CVector p1,p2,p3,p4,q2,q3;
	   for(int iter0=0;iter0<N;iter0++)
	   {
		    CVector nb=vMr[iter0];
		    CVector nbplus=vMr[iter0+1];
			CVector vpoint(nb,onC[vi0-1]);
			CVector v9(nb,nbplus);
			CVector v2=nb+nbplus;
			v2=v2/2;

			double v11=absc(v2-nb);
			double v12=absc(v2-onC[vi0-1]);

			  if ((pointtoVector(v9,vpoint)<5)&&(v12<=v11))
			  {
					t0=iter0/N;
				break;
				}
	   }
		p4=v;//onC[vi0];
		p1=onC[vi0];
		p2=ContP[vi+1];
		p3=ContP[vi+2];
	   t1=vi/N;
	   CVector vt10=(p2-p1)*3*pow((1-t1),2);
	   CVector vt11=(p3-p2)*6*(1-t1)+(p4-p3)*3*pow(t1,2);
	   CVector dbdt1=vt10+vt11;

	   CVector vt00=(p2-p1)*3*pow((1-t0),2);
	   CVector vt01=(p3-p2)*6*(1-t0)+(p4-p3)*3*pow(t0,2);
	   CVector dbdt0=vt00+vt01;
	   q2=p1+dbdt0*1/3*(t1-t0);
	   q3=p4+dbdt1*1/3*(t1-t0);
	   ContP[iter]=q2;
	   ContP[iter+1]=p1;
	   ContP[iter+2]=q3;*/
/*
	   for(iter0=0;iter0<N;iter0++)
	   {
		    CVector nb=vMr[iter0];
		    CVector nbplus=vMr[iter0+1];
			CVector vpoint(nb,onC[vi0+1]);
			CVector v9(nb,nbplus);
			CVector v2=nb+nbplus;
			v2=v2/2;

			double v11=absc(v2-nb);
			double v12=absc(v2-onC[vi0+1]);

			  if ((pointtoVector(v9,vpoint)<5)&&(v12<=v11))
			  {
					t1=iter0/N;
					break;
				}
	   }
		p1=onC[vi0];
		p4=onC[vi0+1];
		p2=ContP[iter+1];
		p3=ContP[iter+2];
	    t0=vi/N;

		vt10=(p2-p1)*3*pow((1-t1),2);
	   vt11=(p3-p2)*6*(1-t1)+(p4-p3)*3*pow(t1,2);
	   dbdt1=vt10+vt11;
	   
	   vt00=(p2-p1)*3*pow((1-t0),2);
	   vt01=(p3-p2)*6*(1-t0)+(p4-p3)*3*pow(t0,2);
	   dbdt0=vt00+vt01;
	   q2=p1+dbdt0*1/3*(t1-t0);
	   q3=p4+dbdt1*1/3*(t1-t0);
	   ContP[iter+1]=q2;
	   ContP[iter+2]=q3;

*/
/*	ContP[vi-1]=ContP[vi-2]+polarc(10,argu(ContP[vi-1]-ContP[vi-2]));
	ContP[vi]=v-polarc(50,argu(v1-v));
	ContP[vi+1]=v;
	ContP[vi+2]=v+polarc(50,argu(v2-v));
	ContP[vi+3]=ContP[vi+4]+polarc(10,argu(ContP[vi+3]-ContP[vi+4]));
	*/
//		addtovecBezier(hdc);
		double t1=-1,t2;
		deg=3;
		vector<CVector> cls;
		vector<double> dcls;
		vector<pair<double,double> > dst;
	   	Para_universp(0,1,N,Para);
//		Knot_Univer(ncp,deg,Kn,0,1);
	   for(int iter0=0;iter0<N;iter0++)
	   {
		    CVector nb=Bspline(deg,ContP,ncp,Para[iter0],Kn);
		    CVector nbplus=Bspline(deg,ContP,ncp,Para[iter0+1],Kn);//vMr[iter0+1];
			CVector vpoint(nb,point);
			CVector v9(nb,nbplus);
			CVector v2=nb+v9/2;
//			v2=v2/2;

			double v11=absc(v2-nb);
			double v12=absc(v2-point);
			double vp0=pointtoVector(v9,vpoint);

			double r=absc(vpoint);///absc(nbplus-nb);

//			  if ((r<5))
			  {
					t1=(double)iter0/N;
					t2=(double)(iter0+1)/N;
					dst.push_back(make_pair(r,t1));//+r*(t2-t1)));
					petit=iter0;
//					break;
				}

	   }
	   if(dst.size()>0){
		   int dstz=dst.size();
		   double mint=dst[0].second;
		   double mm=dst[0].first;
		   for(int i=1;i<dstz;i++)
		   {
			   if(mm>dst[i].first){
				   mint=dst[i].second;
				   mm=dst[i].first;
			   }

		   }
		   t1=mint;
	//	   r=mm;
	   }
   		float f1;
		CVector uv;
		if(mesh.PtonEdge(point,hitpoint,f1,uv))
		{
			jpetit=f1;
		}


		int s = count(Kn.begin(),Kn.begin()+deg+ncp+2, t1);
//		CVector mn= NURBS(deg,ContP,ncp,f1,Kn);
		CVector mn1= Bspline(deg,ContP,ncp,t1,Kn);
		for(int g=0;g<deg-s;g++)
		{
//			insertknot(t1,deg,deg-s,Kn,ContP,ncp);
			Bohms(t1, deg,Kn,ContP,ncp);	
		}
		addtovecBezier(hdc);
//		draw(hdc);
		return mn1;

	   for(iter0=0;iter0<N;iter0++)
	   {
				for(int jo=0;jo<ncp;jo++)
				{
					if((jo%3==0)&&(absc(ContP[jo]-vMr[iter0])<5))
					{
						t2=(double)iter0/N;
						cls.push_back(ContP[jo]);
						dcls.push_back(t2);
					}
				}

	   }
//	   if(t1==-1) return;
//	   t1=f1;
//	   t1=0.5;

/*	   CVector P0_1=P0*(1-t1)+P1*t1;
	   CVector P1_2=P1*(1-t1)+P2*t1;
	   CVector P2_3=P2*(1-t1)+P3*t1;

	   CVector P01_12=P0_1*(1-t1)+P1_2*t1;
	   CVector P12_23=P1_2*(1-t1)+P2_3*t1;
	   
	   CVector P0112_1223=P01_12*(1-t1)+P12_23*t1;*/
	   //P0,P0_1,P01_12,P0112_1223 =>first curve
	   //P0112_1223,P12_23,P2_3,P3 =>Second Curve
	    int o=0;
	   for(int jo=0;jo<ncp;jo++)
		{
			if(jo%3==0)
			{
				if(dcls[o]>t1)
				{
					int jo1=jo-3;
					CVector P0=ContP[jo1];
					CVector P1=ContP[jo1+1];
					CVector P2=ContP[jo1+2];
					CVector P3=ContP[jo1+3];
					ContP.insert(ContP.begin()+jo-3,ContP[jo]);
					ContP.insert(ContP.begin()+jo-3,ContP[jo]);
					ContP.insert(ContP.begin()+jo-3,ContP[jo]);
					ContP[jo1+1]=P0*(1-t1)+P1*t1;//P0_1
					CVector P0_1=ContP[jo1+1];
					CVector P1_2=P1*(1-t1)+P2*t1;;
					ContP[jo1+2]=P0_1*(1-t1)+P1_2*t1;//P01_12
					CVector P2_3=P2*(1-t1)+P3*t1;
					CVector P12_23=P1_2*(1-t1)+P2_3*t1;
					CVector P01_12=P0_1*(1-t1)+P1_2*t1;
					ContP[jo1+3]=P01_12*(1-t1)+P12_23*t1;//0112_1223
					ContP[jo1+4]=P12_23;
					ContP[jo1+5]=P2_3;
					break;
				}
				o++;
			}
		}

/*		for(int i=0;i<deg;i++)
		{
		Bohms(0.5,deg,Kn,ContP,ncp);
		}
*/

	addtovecBezier(hdc);
//	redraw=true;
	
	

	//Original addnode based on spline theory
/*
	bool isOK=false;
	vector<CVector>::iterator testb, teste;
	deg=3;	

	pitere=ptend.begin();
	petit=PtonSpline(point);
	if(petit!=-1)
	{
//	Para=new double [N+1];
	Para_universp(0,1,N,Para);
	
	Bohms(Para[petit],deg,Kn,CP,ncp);

//	drawselect(hdc);
	addtovecBezier();
//	drawselect(hdc);
//	delete []Para;
	}
*/	
}



bool CBezier::draw(bool fPrevLine, CDC *hdc,CVector point)
 {

//		computePieceSpline(hdc);
//		computePieceBezier(hdc);
//		computeLagrange(hdc);
//	    IDrawD1BSpline(hdc,bezier[0],bezier[1],bezier[2]);
	int i0=ContP.size();
	if(i0==0)
	{
		Pprev=new CPoint [i0];
		return FALSE;
	}
		drawBezier(fPrevLine,hdc,point);
      return true;
 }
bool CBezier::drawBezier(bool fPrevLine, CDC *hdc,CVector point)
 {

	CPen pen;

	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	int i0=ContP.size();
//	Knot_Univer(ncp,deg,Kn,0,1);
	CPoint *Pt=new CPoint [i0];
   for(int iter=0;iter<i0;iter++)
	 {
	   Pt[iter]=ContP[iter];
	}

	int im=hdc->SetROP2(R2_NOTXORPEN); 
   
	if ((fPrevB)||(i0==prevstart))
	{
	   iter=0;
/*	   CPoint *_p=Pprev;
	   while(iter<prevstart-1)
	   {
	   hdc->MoveTo(*_p);
	   hdc->PolyBezierTo(_p,3);
	   iter=iter+2;
	   _p=_p+2;
	   }*/
	   hdc->PolyBezier(Pprev,prevstart);

	}
	else
	{

		Pprev=new CPoint [i0];
//		Pprev=new CPoint [N+1];
	}

	iter=0;
/*	CPoint *_p=Pt;
	   while(iter<i0-1)
	   {
	   hdc->MoveTo(*_p);
	   hdc->PolyBezierTo(_p,3);
	   iter=iter+2;
	   _p=_p+2;
	   }*/
	hdc->BeginPath();
	   hdc->PolyBezier(Pt,i0);
	hdc->EndPath();
/*	hdc->FlattenPath();
	vector<CPoint>_p;
	vector<BYTE> _b;
	int n_p=0;//hdc->GetPath(NULL,NULL,NULL);
	if(n_p>0){
	_p.resize(n_p);
	_b.resize(n_p);
	if(hdc->GetPath(_p.begin(),_b.begin(),n_p)){
//		if(Mr!=NULL) {
//		delete [] Mr;
//		Mr=NULL;
//		}
 //   Mr=new CVector[n_p];
		vMr.resize(n_p);
	N=n_p;
	   for(iter=0;iter<n_p;iter++)
	   {
			vMr[iter]=_p[iter];
	   }
	hdc->StrokePath();
	   }
	}*/
	hdc->StrokePath();

	prevstart=i0;
	delete []Pprev;
	Pprev=new CPoint[i0];
	hdc->SelectObject(oldp);
 	for (int i=0; i<i0;i++)
	{
	Pprev[i]=Pt[i];
	}
	delete []Pt;
	hdc->SetROP2(im); 

	fPrevB=true;

      return TRUE;
 }

void CBezier::draw(CDC *hdc)
{
	DWORD tick=GetTickCount();
	vector<CVector>::iterator rsult;
	CRect v(p0,p2);

	if((ffd)&&(select==pnt))
		FFDbox->draw(hdc);
	if((!surf)&&(!vol))
	{
//		redraw=true;
//		DrawBSpline(hdc);
//		if(redraw)
//			DrawBSpline(hdc);
//		else
	DWORD tick=GetTickCount();
	CBezier* f=new CBezier;
	f->copy(this);
	DWORD ptickc=GetTickCount()-tick;
	DWORD tickc=GetTickCount();
	CString sc;
	sc.Format("time spend to Copy a line:%d \n",ptickc);
	TRACE(sc);
	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	v1=v0.sgetscrtop();
	CPoint p(v0.x,v0.y);
    v0 = p;
	p.x=v1.x;
	p.y=v1.y;
	v1 =p;
//	v1.z=0;
//	v0.z=0;
	CRectangle r(v0,v1);
//	clipshape.push_back(&r);
	   for(int i=0;i<clipshape.size();i++)
	   {
		   f->Clip(clipshape[i]);
	   }
//	clipshape.erase(std::find(clipshape.begin(),clipshape.end(),&r));
	DWORD ptickcc=GetTickCount()-tickc;
	CString scc;
	scc.Format("time spend to Clip a line:%d \n",ptickcc);
	TRACE(scc);
	   if (cl)
	   {
		if(texture_file!="")
		{
			CImagex texture;//(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
			if(mode_texture==wrap)
			{
			f->Hatch(hdc);
			}
			CFigure::ScanPolygon(hdc,bcolor,&texture);
		}
		else
		{
			CFigure::ScanPolygon(hdc,bcolor,NULL);
		}
	   }
			f->drawBezier(hdc);
			try{
			delete f;
			}catch(...)
			{
			}
//		DrawNURBS(hdc);
	}else
	if((surf)&&(!vol))
	{
		surface(hdc);
	}else if(vol)
	{
		volume(hdc);
	}


	if(/*(!multiselect)&&*/(!getLibstatus()))
	{
	selectSM(hdc);
//	if(transselectedstate()) drawselect(hdc);
	}
	if (getRotstate())
	{
	CPoint r(rotateCenter);
	hdc->MoveTo(r.x,r.y-15);
	hdc->LineTo(r.x,r.y+15);
	hdc->MoveTo(r.x-15,r.y);
	hdc->LineTo(r.x+15,r.y);
	}
	
	DWORD ptick=GetTickCount()-tick;
	CString s;
	s.Format("time spend to Draw a spline:%d \n",ptick);
	TRACE(s);


}

void CBezier::drawBezier(CDC *hdc)
{
	getCharge(hdc);
	vector<CVector>::iterator rsult;
	CRect v(p0,p2);

	if((ffd)&&(select==pnt))
		FFDbox->draw(hdc);
	if((!surf)&&(!vol))
	{
	CPen pen;

	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	CBrush *ob;
	brush.CreateSolidBrush(bcolor);
	ob=hdc->SelectObject(&brush);
	int s=ContP.size();
	int s1=hdc->GetROP2();
/*	if((prevstart>0)&&(prevstart!=s))
	{
	int im=hdc->SetROP2(R2_NOTXORPEN);
	hdc->MoveTo(Pprev[0]);
 	hdc->PolyBezierTo(Pprev,prevstart);
	hdc->SetROP2(im); 
	}*/
	CPoint *Pt=new CPoint [s];
	   for(int iter=0;iter<s;iter++)
		{
			Pt[iter]=ContP[iter];
		}
	   iter=0;
/*		CPoint *_p=Pt;///Good snippet for bezier display
	   while(iter<s-1)
	   {
//	   hdc->MoveTo(*_p);
	   s1=hdc->PolyBezier(_p,4);
	   iter=iter+3;
	   _p=_p+3;
	   }*/
//	   
		mesh.displayEdge(hdc);
//		mesh2.displayEdge(hdc);
	   //hdc->PolyBezier(Pt,s);
/*	hdc->BeginPath();
	   hdc->PolyBezier(Pt,s);
	hdc->EndPath();
	hdc->FlattenPath();
	vector<CPoint>_p;
	vector<BYTE> _b;
	int n_p=hdc->GetPath(NULL,NULL,NULL);
	if(n_p>0){
	_p.resize(n_p);
	_b.resize(n_p);
	if(hdc->GetPath(_p.begin(),_b.begin(),n_p)){
//		if(Mr!=NULL) {
//		delete [] Mr;
//		Mr=NULL;
//		}
 //   Mr=new CVector[n_p];
		vMr.resize(n_p);
	N=n_p;
	   for(iter=0;iter<n_p;iter++)
	   {
			vMr[iter]=_p[iter];
	   }
	hdc->StrokePath();
	   }
	}*/

	   s1=GetLastError();
   hdc->SelectObject(ob);
	hdc->SelectObject(oldp);
	if(s>0)
		delete Pt;

	}else
	if((surf)&&(!vol))
	{
		surface(hdc);
	}else if(vol)
	{
		volume(hdc);
	}


	if(/*(!multiselect)&&*/(!getLibstatus()))
	{
//	selectSM(hdc);
	if(transselectedstate()) drawselect(hdc);
	}
	if (getRotstate())
	{
	CPoint r(rotateCenter);
	hdc->MoveTo(r.x,r.y-15);
	hdc->LineTo(r.x,r.y+15);
	hdc->MoveTo(r.x-15,r.y);
	hdc->LineTo(r.x+15,r.y);
	}
	


}


void CBezier::drawinit(CDC *hdc,CVector begin,CVector end)
{
	ContP.push_back(begin);
	ContP.push_back(end);

	if (ContP.size()>=3)
	{
		draw(hdc);
	}


}

bool CBezier::PtinRegion(CVector point)
{
	if(ffd)
	{

//	 if(FFDbox->PtinRegion(point)) return true;
	}
/*  if (Rectangleselect(point))
   {
		if((recselectpoint!=rotsca)&&(recselectpoint!=rotmsca))
		{
	   rotateCenter=box.getclosestOpCorner(point);
		}else
		{
			if(recselectpoint==rotsca)
			{
				angle=0;
				if(prevrotateCenter==v0)
				{
				rotateCenter=box.center();
				}
			}
		}
	   click=true;
	   select=st;
	   return true;
   }
	CAABB box2=box;
	box2.inflate(20);
	if(!box2.ccontainpts(point)) 
	{
		click=false;
		prevrotateCenter=v0;
		return false;
	}
*/
	if(surf) 
	{
/*	   vector<CTriangle> l;
	   CRect r(point,point);
	   r.InflateRect(5,5);
	   CVector vl=r.TopLeft();
	   CVector vb=r.BottomRight();
	   CAABB br;
	   br.add(vl);
	   br.add(vb);
	   quadtree.query(&l,point);*/
	   for(vector<CTriangle*>::iterator k=mesh.tbegin();k!=mesh.tend();k++)
	   {
		   CPoint pv1((*k)->Vertex(0)->v);
		   CPoint pv2((*k)->Vertex(1)->v);
		   CPoint pv3((*k)->Vertex(2)->v);
		   CPlane pl1(pv1,pv2,pv3);
		   pv2=point;
		   CVector pv(pv2.x,pv2.y,0);
		   //pv.v2D();
		   CVector t=pl1.getBarycent(pv);
		   if((t.x<1)&&(0<t.x)&&(t.y<1)&&(0<t.y)&&(t.z<1)&&(0<t.z))
		   {
			   click=true;
			   select=full;
			   mesh.select=mesh.all;
			   return true;
		  }
		   else
		   {
			   click=false;
			   mesh.select=mesh.none;
		   }

	   }
	}
 
 bool okj=false;
 bool sol=false;
// fPrevB=false;
// click=false;


 if(!surf)
 {
//	 addvec(ptbegin,ptend);
/*	 for(int i=0;i<=ncp;i++)
	   {
		   if ((pointinRegion(point,CP[i]))&&(!multiselect))
		   {
			   click=true;
			   select=pnt;
			  /* if(CP[i]==ptbegin[1])
			   {
				   select=st;
				   petit=i;
			   }*/
/*			   okj=true;
			   return true;
		   }
	   }*/
 }
 else
 if(surf)
 {
/*	 saddvec(ptbegin,ptend);
	 for(int i=0;i<=ncp;i++)
	   {
		 for(int j=0;j<=ncp;j++)
		 {
		   if ((pointinRegion(point,C[(ncp+1)*i+j]))&&(!multiselect))
		   {
			   click=true;
			   select=pnt;
			  /* if(CP[i]==ptbegin[1])
			   {
				   select=st;
				   petit=i;
			   }*/
/*			   okj=true;
			   return true;
		   }
		 }
	   }
*/
 }

   if(!surf)
   {
	   bool b= CFigure::PtinRegion(point);
		prevrotateCenter=v0;
		return b;

   }
   else
   if(surf)
   {
		 int s=0;
		  CMatrix mathelp;
		  vector<int> se;se.resize(N+1);
		  CPoint *Pt=new CPoint[(N+1)*(N1+1)];
		  CPoint *Pt1=new CPoint[(N+1)*(N1+1)];
		  lk=Kn[deg]*N;
		  lh=Kn[ncp+deg]*N;///maxpara);

 /*
		  for(int jiter=0;jiter<=N1;jiter++)
		  {
			  s=0;
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Pt[(N+1)*jiter+(iter-lk)]=(CVector)mesh.Vertex((N+1)*jiter+iter);//Mr[(N+1)*jiter+iter];
			   Pt1[(N+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];	
			   s++;
			}
			se[jiter]=s;
		  }	

		  int s1=0;
		  vector<int> se1;se1.resize(N+1);
		  mathelp.Transpose(Pt1,(lh-lk)+1,N1+1);
*/
		  for(int jiter=0;jiter<=N1;jiter++)
		  {
		   for(int iter=lk;iter<lh;iter++)
			 {
			   CPoint nb=(CVector)*mesh.Vertex((N+1)*jiter+(iter-lk));
			   CPoint nbplus=(CVector)*mesh.Vertex((N+1)*jiter+(iter+1-lk));


			CPoint vpo=CPoint(point)-nb;
			CVector vpoint(vpo.x,vpo.y);//nb,point);
			CPoint vppo=nbplus-CPoint(nb);
		   CVector v(vppo.x,vppo.y);//nb,nbplus);
			CPoint v2=nb+nbplus,v22;
			v2.x=v2.x/2;
			v2.y=v2.y/2;
			v22=v2;
			v2=v2-nb;
			double v11=absc(CVector(v2.x,v2.y));
			v2=v22-point;
			double v12=absc(CVector(v2.x,v2.y));

	  if ((pointtoVector(CVector(vppo.x,vppo.y),CVector(vpo.x,vpo.y))<5)&&(v12<=v11+20))
	  {

		  
/*		  CVector vpoint(nb,point);
			   CVector v(nb,nbplus);
				CVector v2=nb+nbplus;
				v2=v2/2;

				double v11=absc(v2-nb);
				double v12=absc(v2-point);

				  if ((pointtoVector(CPoint(v),CPoint(vpoint))<5)&&(v12<=v11+1))
				  {*/
					   click=true;
					   petit=iter;
					   petitj=jiter;
					   select=full;
				//	   Rectangleselect(point);
					   delete []Pt;
					   delete []Pt1;
			//		   delete []Para;

					   return true; 
				  } else
					{
						click=false;
					}
				   nb=Pt1[(N+1)*jiter+(iter-lk)];
				   nbplus=Pt1[(N+1)*jiter+(iter+1-lk)];;

			vpo=CPoint(point)-nb;
			CVector vpoint1(vpo.x,vpo.y);//nb,point);
			vppo=nbplus-CPoint(nb);
		    CVector v1(vppo.x,vppo.y);//nb,nbplus);
			v2=nb+nbplus;
			v2.x=v2.x/2;
			v2.y=v2.y/2;
			v22=v2;
			v2=v2-nb;
			v11=absc(CVector(v2.x,v2.y));
			v2=v22-point;
			v12=absc(CVector(v2.x,v2.y));

	  if ((pointtoVector(CVector(vppo.x,vppo.y),CVector(vpo.x,vpo.y))<5)&&(v12<=v11+20))
	  {
/*				   vpoint=CVector(nb,point);
				   v=CVector(nb,nbplus);
					v2=nb+nbplus;
					v2=v2/2;

					v11=absc(v2-nb);
					v12=absc(v2-point);

				  if ((pointtoVector(CPoint(v),CPoint(vpoint))<5)&&(v12<=v11+1))
				  {*/
					   click=true;
					   petit=iter;
					   select=full;
					//   Rectangleselect(point);
					   delete []Pt;
					   delete []Pt1;

					   return true; 
				  } else
					{
						click=false;
					}
		   }
		  }	

					   delete []Pt;
					   delete []Pt1;
   }
	return false;

 /*  if (Rectangleselect(point)&&(!getmultcore()))
   {
	   click=true;
	   select=st;
	   return true;
   }
   else
   {

	return false;
   }*/
}

void CBezier::setselectmode(SELECT j)
{
	select=j;
	if(select==full)
		mesh.select=mesh.all;
}

bool CBezier::inRegion(CVector point)
{
	return CFigure::inRegion(point);

 bool okj=false;
 bool sol=false;
	if(!box.ccontainpts(point)) 
	{
		return false;
	}
 if(!surf)
 {/*
 addvec(ptbegin,ptend);

 for(int i=0;i<=ncp;i++)
   {
	   if ((pointinRegion(point,CP[i]))&&(!multiselect))
	   {
		   select=pnt;
		   if(CP[i]==ptbegin[1])
		   {
			   select=st;
			   petit=i;
		   }
		   okj=true;
		   return true;
	   }
   }*/
	   bool b= CFigure::PtinRegion(point);
		prevrotateCenter=v0;
		return b;

 }
  else
 if(surf)
 {
/*	 saddvec(ptbegin,ptend);
	 for(int i=0;i<=ncp;i++)
	   {
		 for(int j=0;j<=ncp;j++)
		 {
		   if ((pointinRegion(point,C[(ncp+1)*i+j]))&&(!multiselect))
		   {
			   click=true;
			   select=pnt;
			   okj=true;
			   return true;
		   }
		 }
	   }
*/
/*	   vector<CTriangle> l;
	   CRect r(point,point);
	   r.InflateRect(5,5);
	   CVector vl=r.TopLeft();
	   CVector vb=r.BottomRight();
	   CAABB br;
	   br.add(vl);
	   br.add(vb);
	   quadtree.query(&l,point);*/
	   for(vector<CTriangle*>::iterator k=mesh.tbegin();k!=mesh.tend();k++)
	   {
		   CPoint pv1((*k)->Vertex(0)->v);
		   CPoint pv2((*k)->Vertex(1)->v);
		   CPoint pv3((*k)->Vertex(2)->v);
		   CPlane pl1(pv1,pv2,pv3);
		   CVector pv=point;
		   pv.v2D();
		   CVector t=pl1.getBarycent(pv);
		   if((t.x<1)&&(0<t.x)&&(t.y<1)&&(0<t.y)&&(t.z<1)&&(0<t.z))
		   {
			   click=true;
			   select=full;
			   mesh.select=mesh.all;
			   return true;
		  }
		   else
		   {
			   click=false;
			   mesh.select=mesh.none;
		   }

	   }

 }
  
 if(!surf)
 {
   CVector *M=new CVector[N+1];
//   Para=new double[N+1];
   Para_universp(minpara,maxpara,N,Para);

   int lk=Kn[deg]*N;
  
   for(int iter=0;iter<N;iter++)
   {
	   CPoint nb=NURBS(deg,CP,ncp,Para[iter],Kn);
	   CPoint nbplus=NURBS(deg,CP,ncp,Para[iter+1],Kn);

/*		CVector vpoint(nb,point);
	   CVector v(nb,nbplus);
		CVector v2=nb+nbplus;
		v2=v2/2;

		double v11=absc(v2-nb);
		double v12=absc(v2-point);
*/
			CPoint vpo=CPoint(point)-nb;
			CVector vpoint(vpo.x,vpo.y);//nb,point);
			CPoint vppo=nbplus-CPoint(nb);
		   CVector v(vppo.x,vppo.y);//nb,nbplus);
			CPoint v2=nb+nbplus,v22;
			v2.x=v2.x/2;
			v2.y=v2.y/2;
			v22=v2;
			v2=v2-nb;
			double v11=absc(CVector(v2.x,v2.y));
			v2=v22-point;
			double v12=absc(CVector(v2.x,v2.y));

	  if ((pointtoVector(CVector(vppo.x,vppo.y),CVector(vpo.x,vpo.y))<5)&&(v12<=v11+20))
	  {
		   petit=iter;
		   select=full;
		   Rectangleselect(point);
		   delete []M;
//		   delete []Para;

		   return true; 
	  } else
		{
		}
	}
      delete []M;
 }
 else
 {
/*	 		 int s=0;
		  CMatrix mathelp;
		  vector<int> se;se.resize(N1+1);
		  CPoint *Pt=new CPoint[(N+1)*(N1+1)];
		  CPoint *Pt1=new CPoint[(N+1)*(N1+1)];
 		  lk=Kn[deg]*N;
		  lh=Kn[ncp+deg]*N;///maxpara);

		  for(int jiter=0;jiter<=N1;jiter++)
		  {
			  s=0;
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Pt[(N+1)*jiter+(iter-lk)]=(CVector)mesh.Vertex((N+1)*jiter+iter);//Mr[(N+1)*jiter+iter];
			   Pt1[(N+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];	
			   s++;
			}
			se[jiter]=s;
		  }	

		  int s1=0;
		  vector<int> se1;se1.resize(N+1);
		  mathelp.Transpose(Pt1,(lh-lk)+1,N1+1);

		  for(jiter=0;jiter<=N1;jiter++)
		  {
		   for(int iter=lk;iter<lh;iter++)
			 {
			   CVector nb=Pt[(N+1)*jiter+(iter-lk)];
			   CVector nbplus=Pt[(N+1)*jiter+(iter+1-lk)];;

				CVector vpoint(nb,point);
			   CVector v(nb,nbplus);
				CVector v2=nb+nbplus;
				v2=v2/2;

				double v11=absc(v2-nb);
				double v12=absc(v2-point);

				  if ((pointtoVector(CPoint(v),CPoint(vpoint))<5)&&(v12<=v11+1))
				  {
					   click=true;
					   petit=iter;
					   petitj=jiter;
					   select=full;
					   Rectangleselect(point);
					   delete []Pt;
					   delete []Pt1;
			//		   delete []Para;

					   return true; 
				  } else
					{
						click=false;
					}

				   nb=Pt1[(N+1)*jiter+(iter-lk)];
				   nbplus=Pt1[(N+1)*jiter+(iter+1-lk)];;

				   vpoint=CVector(nb,point);
				   v=CVector(nb,nbplus);
					v2=nb+nbplus;
					v2=v2/2;

					v11=absc(v2-nb);
					v12=absc(v2-point);

				  if ((pointtoVector(CPoint(v),CPoint(vpoint))<5)&&(v12<=v11+1))
				  {
					   click=true;
					   petit=iter;
					   select=full;
					   Rectangleselect(point);
					   delete []Pt;
					   delete []Pt1;

					   return true; 
				  } else
					{
						click=false;
					}
		   }
		  }	

					   delete []Pt;
					   delete []Pt1;
 */
 }


//   delete []Para;
  if (Rectangleselect(point)&&(!getmultcore()))
   {
//	   click=true;
//	   select=point;
	   return true;
   }
   else
   {
	return false;
   }

}


void CBezier::drawTrans(CDC *hdc)
{
	if(surf) return;

	if((ffd)&&(select==pnt))
	{
		FFDbox->drawTrans(hdc);
	}
	CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	int jj=hdc->SetROP2(R2_NOTXORPEN);    

	int i=0;
	if(!fPrevB)
	{
		int n=hdc->SetROP2(R2_NOTXORPEN);
		if(!surf) DrawBSpline(hdc);
	}

	DrawDynaBspline(hdc); 

	if((!multiselect)&&(!getLibstatus()))
	{
/*	piterpb=prevptbegin.begin();
	piterpe=prevptend.begin();
	pitere=ptend.begin();

	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
	ptsBegin=*piterb;
	ptsEnd=*pitere;
	ptsPrevBegin=*piterpb;
	ptsPrevEnd=*piterpe;
	
	pitere=pitere+1;
	piterpb=piterpb+1;
	piterpe=piterpe+1;

	

	hdc->MoveTo(ptsPrevBegin); 
	hdc->Ellipse(CRect(CVector(ptsPrevBegin.x-3, ptsPrevBegin.y+3),CVector(ptsPrevBegin.x+3, ptsPrevBegin.y-3)));
//	hdc->MoveTo(ptsPrevEnd.x, ptsPrevEnd.y); 
//	hdc->EllipseRectangle(ptsPrevEnd.x-5, ptsPrevEnd.y+5,ptsPrevEnd.x+5, ptsPrevEnd.y-5);

	hdc->MoveTo(ptsBegin); 
	hdc->Ellipse(CRect(CVector(ptsBegin.x-3, ptsBegin.y+3),CVector(ptsBegin.x+3, ptsBegin.y-3)));
//	hdc->MoveTo(ptsEnd.x, ptsEnd.y); 
//	hdc->Rectangle(ptsEnd.x-5, ptsEnd.y+5,ptsEnd.x+5, ptsEnd.y-5);
    }
	
//	hdc->Ellipse(CRect(CVector(ptsPrevEnd.x-5, ptsPrevEnd.y+5),CVector(ptsPrevEnd.x+5, ptsPrevEnd.y-5)));

//	hdc->Ellipse(CRect(CVector(ptsEnd.x-5, ptsEnd.y+5),CVector(ptsEnd.x+5, ptsEnd.y-5)));
*/

	if (Isrotate)
	{
	hdc->MoveTo(CVector(rotateCenter.x,rotateCenter.y-25));
	hdc->LineTo(CVector(rotateCenter.x,rotateCenter.y+25));
	hdc->MoveTo(CVector(rotateCenter.x-25,rotateCenter.y));
	hdc->LineTo(CVector(rotateCenter.x+25,rotateCenter.y));
	}
	hdc->SetROP2(jj);    

	
		updatecore();	
	}
	hdc->SelectObject(oldp);


//		updatecore();	

//		vector<CVector>::iterator bonbon=coreprec.begin();

/*		if(!coreprec.empty())
		{

		for (bonbon=coreprec.begin();bonbon<coreprec.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		hdc->Rectangle(bonbon->x-5, bonbon->y+5,bonbon->x+5, bonbon->y-5);
		}

		for (bonbon=core.begin();bonbon<core.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		hdc->Rectangle(bonbon->x-5, bonbon->y+5,bonbon->x+5, bonbon->y-5);
		}
		}*/
}
CFigure* CBezier::translatep(CVector prevpos, CVector postpos)
{
	if(ffd)
	{
		FFDbox->translatep(prevpos,postpos);
	}
	return CFigure::translatep(prevpos,postpos);

}
void CBezier::Rotate(int sens,CVector prevpoint,CVector postpoint)
{
	if((ffd)&&(select==pnt))
	{
		FFDbox->Rotate(sens,prevpoint,postpoint);
		return;
	}

	CTVector vh;

	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	CVector ptb,pte;	
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector piv=(core[0]+core[4])/2;
	piv=rotateCenter-piv;
	prevpoint=rotateCenter-prevpoint;
	postpoint=rotateCenter-postpoint;

/*	postpoint.v2D();
	prevpoint.v2D();
	double alphab=argu(rotateCenter)-argu(prevpoint);//-argu(piv);
	angle=alphab;*/
	double alphab=argu(postpoint)-argu(prevpoint);//-argu(piv);
	angle=alphab;
//	angle=alphab+argu(prevpoint);

	CVector v00,v01;
	CTVector vt;
	v00.assign(rotateCenter,v0);
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(-rotateCenter);

	if(sens==1)
	{
	vt.TRotatex(angle);
	}else
	if(sens==2)
	{
	vt.TRotatey(angle);
	}
	else
	{
	vt.TRotate(angle);
	}
	v01.assign(v0,rotateCenter);
	vt.Translate(rotateCenter);
	vt.endT();
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		piterb->assign(*piterb,true);
		pitere->assign(*pitere,true);


	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}

	}
   if(surf)
   {
   CMesh::ivertex iv=mesh.vbegin();
   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
   {
	   (iv)->second->assign(*iv->second);
   }
 //  mesh.updateTri();

/*   for(int jiter=0;jiter<=N1;jiter++)
   {
	 for(int iter=lk;iter<=lh;iter++)
	 {
	   Mr[(lh-lk+1)*jiter+iter].assign(Mr[(lh-lk+1)*jiter+iter],true);
	 }
   }*/
   }
   else
   {
	
	 for(int iter=lk;iter<lh;iter++)
	 {
	   vMr[iter].assign(vMr[iter],true);
	 }
   }

	vt.popTransform();
	
}
	


void CBezier::DrawDynaBspline(CDC *hdc)
{
	return;
	if(!surf)
	{
	addvec(ptbegin,ptend);
   CVector *M;
   M=new CVector[N+1];


    CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
    Para_universp(minpara,maxpara,N,Para);

	if(redraw)
	{
      CMesh::ivertex iv=mesh.vbegin();
   for(int iter=0;iter<N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
	  (iv)->second->v=Mr[iter];
	  iv++;

   }
   redraw=false;
	}

   if(ffd)
   {
	   setFFD(Mr);
   }
   

   CPoint *Pt=new CPoint [N+1];
   int s=0;
   for(int iter=0;iter<N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   s++;
	}
   

	int jj=hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
 
	hdc->Polyline(&Pprev[0],N);
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
	
 	hdc->Polyline(&Pt[0],N);


	for (int i=0; i<=N;i++)
	{
	Pprev[i]=Pt[i];
	}

	hdc->SelectObject(oldp);

   hdc->SetROP2(jj); 

	fPrevB=true;
	delete [] M;
//	delete []Para;
	delete []Pt;

//		mesh.displayEdge (hdc);
		}
		else if((surf)&&((select==full)||(rotstate==R3)))
		{
		//	trans=true;
		/* int s=0;
		  CMatrix mathelp;
		  vector<int> se;se.resize(N+1);
		  CPoint *Pt=new CPoint[(N+1)*(N1+1)];
		  CPoint *Pt1=new CPoint[(N+1)*(N1+1)];
 
		  for(int jiter=0;jiter<=N1;jiter++)
		  {
			  s=0;
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Pt[(N+1)*jiter+(iter-lk)]=(CVector)mesh.Vertex((N+1)*jiter+iter);//Mr[(N+1)*jiter+iter];
			   Pt1[(N+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];	
			   s++;
			}
			se[jiter]=s;
		  }	

		  int s1=0;
		  vector<int> se1;se1.resize(N+1);
		  mathelp.Transpose(Pt1,(lh-lk)+1,N1+1);*/
        int jj=hdc->SetROP2(R2_NOTXORPEN);
  		if (fPrevB)
		{
	//		mesh.displayEdge(hdc);
		/*   if (cl) hdc->BeginPath();
   
		  for(jiter=0;jiter<=N1;jiter++)
		  {
 			hdc->Polyline(&Ptr[(N+1)*jiter],se[jiter]);
		  }
		  for(jiter=0;jiter<=(lh-lk);jiter++)
		  {
 			hdc->Polyline(&Pt1r[(N1+1)*jiter],N1+1);
		  }
			if (cl)
		   {
		   hdc->EndPath();
		   hdc->StrokeAndFillPath();
		   }*/
		}
		else
		{
		/*	if(Ptr!=NULL)
			{
				delete []Ptr;
				Ptr=NULL;
				delete []Pt1r;
				Pt1r=NULL;
			}
			Ptr=new CPoint [(N1+1)*(lh-lk+1)];
			Pt1r=new CPoint [(N1+1)*(lh-lk+1)];*/
			 
		}
		
		/*

		  for(jiter=0;jiter<=N1;jiter++)
		  {
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Ptr[(N+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];
			   Pt1r[(N+1)*jiter+(iter-lk)]=Pt1[(N+1)*jiter+(iter-lk)];	
			}
		  }	

*/
  
		   CPen pen;
			pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
			CPen *oldp=hdc->SelectObject(&pen);

			CBrush brush;
			CBrush *ob;
			brush.CreateSolidBrush(bcolor);
			ob=hdc->SelectObject(&brush);


/*		   if (cl) hdc->BeginPath();
   
		  for(jiter=0;jiter<=N1;jiter++)
		  {
 			hdc->Polyline(&Pt[(N+1)*jiter],se[jiter]);
		  }
		  for(jiter=0;jiter<=(lh-lk);jiter++)
		  {
 			hdc->Polyline(&Pt1[(N1+1)*jiter],N1+1);
		  }
			if (cl)
		   {
		   hdc->EndPath();
		   hdc->StrokeAndFillPath();
		   }
  */
    if(dtri)
	{
	light l;
	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=GetRValue(bcolor);
	int gh1=GetGValue(bcolor);
	int gh2=GetBValue(bcolor);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);
	M_spec=M_spec/255;
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	

	
  //  mesh.updateTri();
	col* mytext=NULL;;
	int pheight;
	int pwidth;
	if(texture_file!="")
	{
	CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
	BYTE* text=(BYTE*)texture.GetDIBits();
    pheight=texture.GetHeight();
	pwidth=texture.GetWidth();
	mytext=new col[pheight*pwidth];
	int i = 0;
		int x, y,q;
	int r,g,b;
		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
			}
			i+=pwidth%4;
		}
	}
	l.S_spec=S_spec;
	l.S_diff=S_diff;
	l.M_spec=M_spec;
	l.M_diff=M_diff;
	l.M_amb=M_amb;
	l.lsou=lsou;
	l.view=view;
	l.alpha=alpha;
	surface(hdc);

/*	if(ffd)
    {
	   setFFD(Mr);
    }
	else
	{
		   CMesh::ivertex iv=mesh.vbegin();int i=0;
		   for(iv=mesh.vbegin();iv!=mesh.vend();iv++,i++)
		   {
			  *iv=Mr[i];
		   }
	}*/

//	mesh.displayTri(hdc,loc,lit,mytext,pwidth,pheight,&l);
	if(mytext!=NULL) 
		delete []mytext;
	}
	else
	{
		mesh.displayEdge(hdc);
	}
		   hdc->SetROP2(jj); 
		   hdc->SelectObject(ob);
		   hdc->SelectObject(oldp);

		//   delete [] Pt;
		 //  delete [] Pt1;
		}
		else if(surf)
		{
			trans=true;
		}
	fPrevB=true;


}
void CBezier::UpdateMesh()
{
	for (piterb=ContP.begin();piterb<ContP.end();piterb++)
	{
		piterb->assign(*piterb,true);
	}
	CFigure::UpdateMesh();
	addtovecBezier();
	
}


void CBezier::translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos)
{

	if((ffd)&&(select==pnt))
	{
		FFDbox->translate(wnd,hdc,prevpos,postpos);
		return;
	}
//		CFigure::translate(wnd,hdc,prevpos,postpos);
	
/*	if(surf)
	{
		if((linestate==D4)||(select==st))
		{
			TransformRect(prevpos,postpos);
			return;
		}else
		if ((select==full)||(multiselect||getLibstatus()))
		{
		mesh.translate(prevpos,postpos);
		return;
		}
	}
	else
	{
		CFigure::translate(wnd,hdc,prevpos,postpos);
	}*/
	if((linestate==D4)||(select==st))
	{
		prevptend=ptend;
		prevptbegin=ptbegin;
		if(recselectpoint==rotsca)
		{
			CFigure::Rotate(-1,prevpos,postpos);
			
		}else
		if(recselectpoint==rotmsca)
		{
			CFigure::moveRotCenter(hdc,prevpoint,postpos);
			return;
			
		}else
		{
		int d=(recselectpoint==vsca)?2:(recselectpoint==hsca)?1:-1;
		Scale(d,prevpos,postpos);
		}
		redraw=true;
		if(surf) 
			C=ptbegin;
		else
		{
//			if(!getmultcore()) 
			{
				draw(fPrevB,hdc,CVector(0,0));
		addtovecBezier(hdc);
				return;
//				drawTrans(hdc);
			}
		}

//		CFigure::translate(wnd,hdc,prevpos,postpos);
	}
//	else 
//	{
	bool alr=false,ale=false;
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector MouseVect(prevpos,postpos);
	int _j=0;
	if(select==pnt)
	{
	for (piterb=ContP.begin();piterb<ContP.end();piterb++)
	{
		ptsBegin=*piterb;
	//	ptsEnd=*pitere;

		CVector vpoint(ptsBegin,prevpos);
		CVector v(ptsBegin,ptsEnd);
	
		if ((pointinRegion(ptsBegin,prevpos))&&((!multiselect)||(!getLibstatus())))
		{
		multiselect=false;
			if(!alr)
			{
			*piterb+=MouseVect;
			int n=_j%3;
			if(n==1)
			{
				if((piterb-1)!=ContP.begin())
				{
					*(piterb-2)-=MouseVect;
				}
			}else
			if(n==2)
			{
				if((piterb+1)!=ContP.end())
				{
					*(piterb+2)-=MouseVect;
				}
			}else
			if(n==0)
			{
				if((piterb!=ContP.begin())&&(piterb!=ContP.end()-1))
				{
					*(piterb-1)+=MouseVect;
					*(piterb+1)+=MouseVect;
				}else
				if(piterb==ContP.begin())
				{
					*(piterb+1)+=MouseVect;
				}else
				if(piterb==ContP.end()-1)
				{
					*(piterb-1)+=MouseVect;
				}
			}
			
			alr=true;
			redraw=true;
			}
		}
		_j++;
	}
	}
//	}
//		if(surf) C=ptbegin;
//	else
//		CP=ptbegin;
//		CFigure::translate(wnd,hdc,prevpos,postpos);

		if ((select==full)&&(((!ale)&&(!alr))||(multiselect||getLibstatus())))
		{
			vector<CVector>::iterator  pite,pitb;
			pite=ptend.begin();
			CVector mouseVect(prevpos,postpos);
/*			for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb++,pite++)
			{
				if(transref)
				{
			
					(*pitb)=mouseVect.x>0?\
					(*pitb)+polarc(absc(mouseVect),argu(refline)):(*pitb)-polarc(absc(mouseVect),argu(refline));		
	
		//		(*pite)=mouseVect.x>0?\
		//			(*pite)+polarc(absc(mouseVect),argu(refline)):(*pite)-polarc(absc(mouseVect),argu(refline));		
				}
				else
				{
				(*pitb).x+=mouseVect.x;
				(*pitb).y+=mouseVect.y;
				(*pitb).z+=mouseVect.z;
				}

			}*/
/*			   if(!surf)
			   {
				   if(N!=mesh.Vcount())
				   {
					//   fPrevB=false;
				//		draw(fPrevB,hdc,CVector(0,0));
				//	   addtovecBezier();
				   }

				   CMesh::ivertex iv=mesh.vbegin();
				   for(int jiter=0;jiter<N;jiter++)
				   {
					   vMr[jiter]+=mouseVect;
			//		  (*iv)->v=Mr[jiter];
			//		  iv++;
				   }

					for (piterb=ContP.begin();piterb<ContP.end();piterb++)
					{
					*piterb+=MouseVect;
					}
					
					rotateCenter+=MouseVect;
				}*/
		CFigure::translate(wnd,hdc,prevpos,postpos);
		}
	//		   	if(surf) C=ptbegin;
	//			else
	//			CP=ptbegin;
/*			   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
			   {
				   (*iv)+=mouseVect;
			   }*/
		
//		}
//	}
			   if(surf)
			   {
				   CMesh::ivertex iv=mesh.vbegin();
				   for(iv=mesh.vbegin(),piterb=ptbegin.begin();iv!=mesh.vend();iv++,piterb++)
				   {
					   (iv)->second->v=*piterb;
				   }
			   }

/*				if(!getLibstatus())
				{
					if(!surf)
					{
						draw(fPrevB,hdc,CVector(0,0));
	//				drawTrans(hdc);
				//	wnd->Invalidate();
					}
				}*/

}
const CAABB CBezier::getbox(CDC* hdc) 
{
	bool b=multiselect;
	multiselect=false;
	SELECT s=select;
	if(hdc!=NULL)
		getCharge(hdc);
	CBezier* f =new CBezier;
	f->copy(this);
	if((!multiselect))
		f->updatecore();
	select=s;
	multiselect=b;
	CAABB bo=f->box;
	delete f;
	return bo;
}

void CBezier::savefiledxf(CStdioFile& file)
{
	file.WriteString("  0");file.WriteString("\n");
	file.WriteString("SPLINE");file.WriteString("\n");
	file.WriteString("  5");file.WriteString("\n");
	file.WriteString(gethandle().c_str());file.WriteString("\n");
	file.WriteString("330");file.WriteString("\n");
	file.WriteString("1F");file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbEntity");file.WriteString("\n");
	file.WriteString("  8");file.WriteString("\n");
	file.WriteString(getLayer().name);file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbSpline");file.WriteString("\n");
	file.WriteString("210");file.WriteString("\n");
	file.WriteString("0.0");file.WriteString("\n");
	file.WriteString("220");file.WriteString("\n");
	file.WriteString("0.0");file.WriteString("\n");
	file.WriteString("230");file.WriteString("\n");
	file.WriteString("1.0");file.WriteString("\n");
	file.WriteString(" 70");file.WriteString("\n");
	file.WriteString("     8");file.WriteString("\n");
	file.WriteString(" 71");file.WriteString("\n");
	CString ps;
	ps.Format(_T("%i"),deg);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 72");file.WriteString("\n");
	ps.Format(_T("%i"),Kn.size());
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 73");file.WriteString("\n");
	ps.Format(_T("%i"),ContP.size());
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 74");file.WriteString("\n");
	file.WriteString("     0");file.WriteString("\n");
	file.WriteString(" 42");file.WriteString("\n");
	file.WriteString("0.0000000001");file.WriteString("\n");
	file.WriteString(" 43");file.WriteString("\n");
	file.WriteString("0.0000000001");file.WriteString("\n");
	for(int i=0;i<Kn.size();i++)
	{
		file.WriteString(" 40");file.WriteString("\n");
		ps.Format(_T("%f"),Kn[i]);
		file.WriteString(ps);file.WriteString("\n");
	}
	for(i=0;i<ContP.size();i++)
	{
		file.WriteString(" 10");file.WriteString("\n");
		ps.Format(_T("%f"),ContP[i].x);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 20");file.WriteString("\n");
		ps.Format(_T("%f"),ContP[i].y);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 30");file.WriteString("\n");
		ps.Format(_T("%f"),ContP[i].z);
		file.WriteString(ps);file.WriteString("\n");
	}
}

void CBezier::savefile(CFile &file)
{

	file.Write(&N, sizeof(N));
	file.Write(&N1, sizeof(N1));
	file.Write(&N2, sizeof(N2));
	file.Write(&ncp, sizeof(ncp));
	file.Write(&ncp1, sizeof(ncp1));
	file.Write(&ncp2, sizeof(ncp2));
	file.Write(&ncpe, sizeof(ncpe));
	file.Write(&deg,sizeof(deg));
	file.Write(&deg1,sizeof(deg1));
	file.Write(&deg2,sizeof(deg2));
	int ukn=Kn.size(),ukn1=Kn1.size(),ukn2=Kn2.size();
	file.Write(&ukn,sizeof(int));
	file.Write(&ukn1,sizeof(int));
	file.Write(&ukn2,sizeof(int));
	
	file.Write(&prevref,sizeof(prevref));
 	file.Write(&minpara, sizeof(minpara));
	file.Write(&maxpara, sizeof(maxpara));
	file.Write(&minpara1, sizeof(minpara1));
	file.Write(&maxpara1, sizeof(maxpara1));
	file.Write(&surf, sizeof(surf));
	file.Write(&vol, sizeof(vol));

	for(int it=0;it<ncp;it++)
	{
		CP[it].savefile(file);
	}
	for(it=0;it<ncp1*ncp;it++)
	{
		C[it].savefile(file);
	}

	for(it=0;it<ukn;it++)
	{
		file.Write(&Kn[it], sizeof(double));
	}
	
	for(it=0;it<ukn1;it++)
	{
		file.Write(&Kn1[it], sizeof(double));
	}
	
	for(it=0;it<ukn2;it++)
	{
		file.Write(&Kn2[it], sizeof(double));
	}
	CFigure::savefile(file);	 
//	mesh.savefile(file);

	file.Write(&ffd, sizeof(ffd));
	file.Write(&bffd, sizeof(bffd));
	if(ffd)
	FFDbox->savefile(file);	

	if(!surf)
	{
/*		for(int i=0;i<=N;i++)
		{
			Mr[i].savefile(file);
		}
		*/
	}


}

void CBezier::openfile(CFile &file)
{
//	init();
	file.Read(&N, sizeof(N));
	file.Read(&N1, sizeof(N1));
	file.Read(&N2, sizeof(N2));
	file.Read(&ncp, sizeof(ncp));
	file.Read(&ncp1, sizeof(ncp1));
	file.Read(&ncp2, sizeof(ncp2));
	file.Read(&ncpe, sizeof(ncpe));
	file.Read(&deg,sizeof(deg));
	file.Read(&deg1,sizeof(deg1));
	file.Read(&deg2,sizeof(deg2));
	int ukn=0,ukn1=0,ukn2=0;
	file.Read(&ukn,sizeof(int));
	file.Read(&ukn1,sizeof(int));
	file.Read(&ukn2,sizeof(int));
	
	file.Read(&prevref,sizeof(prevref));
 	file.Read(&minpara, sizeof(minpara));
	file.Read(&maxpara, sizeof(maxpara));
	file.Read(&minpara1, sizeof(minpara1));
	file.Read(&maxpara1, sizeof(maxpara1));
	file.Read(&surf, sizeof(surf));
	file.Read(&vol, sizeof(vol));

	CP.clear();
	C.clear();
	ContP.clear();
	for(int it=0;it<ncp;it++)
	{
		CVector v;
		v.openfile(file);
		CP.push_back(v);
	}
	for(it=0;it<ncp;it++)
	{
		ContP.push_back(CP[it]);
	}
	for(it=0;it<ncp1*ncp;it++)
	{
		CVector v;
		v.openfile(file);
		C.push_back(v);
	}
	Kn.resize(ukn);
	for(it=0;it<ukn;it++)
	{
		file.Read(&Kn[it], sizeof(double));
	}
	Kn1.resize(ukn1);
	for(it=0;it<ukn1;it++)
	{
		file.Read(&Kn1[it], sizeof(double));
	}
	Kn2.resize(ukn2);
	for(it=0;it<ukn2;it++)
	{
		file.Read(&Kn2[it], sizeof(double));
	}
	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);

	CFigure::openfile(file);
//	if(surf)
//		mesh.openfile(file);
	if(surf)
	   mesh.RWRender();

	file.Read(&ffd, sizeof(ffd));
	file.Read(&bffd, sizeof(bffd));
	if(ffd)
	{
	FFDbox=new CFFD(this,"2x2x2");
	FFDbox->openfile(file);
	}
	redraw=false;
/*	if(!surf)
	{
	Mr=new CVector[N+1];//(CVector*)calloc(N+1,sizeof(CVector));
	int pl=_CrtCheckMemory();
	for(int i=0;i<=N;i++)
	{
		CVector v;
		v.openfile(file);
		Mr[i]=v;
		if(i==N)
		{
			int k=0;
		}
	}
	}*/
	updatecore();
	name="CBezier";

//	}//endif

}
LONG CBezier::Readfile(CFile &file)
{
	init();
	LONG g;
	file.Read(&N, sizeof(N));
	file.Read(&N1, sizeof(N1));
	file.Read(&N2, sizeof(N2));
	file.Read(&ncp, sizeof(ncp));
	file.Read(&ncp1, sizeof(ncp1));
	file.Read(&ncp2, sizeof(ncp2));
	file.Read(&ncpe, sizeof(ncpe));
	file.Read(&deg,sizeof(deg));
	file.Read(&deg1,sizeof(deg1));
	file.Read(&deg2,sizeof(deg2));
	int ukn=0,ukn1=0,ukn2=0;
	file.Read(&ukn,sizeof(int));
	file.Read(&ukn1,sizeof(int));
	file.Read(&ukn2,sizeof(int));
	
	file.Seek(sizeof(prevref),CFile::current);
 	file.Seek(sizeof(minpara),CFile::current);
	file.Seek(sizeof(maxpara),CFile::current);
	file.Seek(sizeof(minpara1),CFile::current);
	file.Seek(sizeof(maxpara1),CFile::current);
	file.Seek(sizeof(surf),CFile::current);
	file.Seek(sizeof(vol),CFile::current);

	for(int it=0;it<ncp;it++)
	{
		CVector v;
		v.Readfile(file);
	}
	for(it=0;it<ncp1*ncp;it++)
	{
		CVector v;
		v.Readfile(file);
	}

	for(it=0;it<ukn;it++)
	{
		file.Seek(sizeof(double),CFile::current);
	}
	
	for(it=0;it<ukn1;it++)
	{
		file.Seek(sizeof(double),CFile::current);
	}
	
	for(it=0;it<ukn2;it++)
	{
		file.Seek(sizeof(double),CFile::current);
	}

	CFigure::Readfile(file);
//	if(surf)
//	mesh.Readfile(file);

	g=file.Read(&ffd, sizeof(ffd));
	g=file.Read(&bffd, sizeof(bffd));
	if(ffd)
	{
	FFDbox=new CFFD(this,"2x2x2");
	g=FFDbox->Readfile(file);
	}
	if(!surf)
	{
/*	for(int i=0;i<=N;i++)
	{
		CVector v;
		g=v.Readfile(file);
	}
*/	}
	return g;
//	name="CBezier";

//	}//endif

}

void CBezier::setPtsBegin(CPoint pos)
{
//	ptsBegin=pos;
//	bezier[i]=pos;
//	i=i+3;
	down=true;
	polystate(pos);

}

void CBezier::addtovec(CDC* hdc)//()
{
	int i,j;
	ptbegin.clear();
	ptend.clear();
	if(!surf)
	{
		CP.clear();
		for(i=0;i<ncp;i++)
		{
		CP.push_back(ContP[i]);
		}
		for(i=0;i<=ncp;i++)
		{
		ptbegin.push_back(CP[i]);
		}
		for(i=0;i<=ncp;i++)
		{
		ptend.push_back(CP[i]);
		}
		mesh.empty();
		int lk=Kn[deg]*N;
		int lh=Kn[ncp+deg]*N;
		if (!Mr)
		{
		   int lk=Kn[deg]*N;
		   int lh=Kn[ncp+deg]*N;

		   Mr=new CVector[N+1];
		   Para_universp(0,1,N,Para);

		   for(int iter=lk;iter<=lh;iter++)
		   {
				Mr[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
		   }

		}
	   for(int iter=lk;iter<=lh;iter++)
		{
		   mesh.addVertex (new CVertex(Mr[iter],Para[iter],0));
		}
	   for(iter=lk;iter<lh;iter++)
		{
	       new CEdge(mesh.Vertex(iter),mesh.Vertex(iter + 1),mesh.Ecount());
		}

		for(i=0;i<=ncp;i++)
		{
//		   mesh.addVertex (new CVertex(CP[i],0,0));
		}

	}else
	if(surf)
	{
		ptbegin.resize((ncp1+1)*(ncp+1));
		ptend.resize((ncp1+1)*(ncp+1));
		for(i=0;i<=ncp1;i++)
		{
		  for(j=0;j<=ncp;j++)
		  {
			ptbegin[i*(ncp+1)+j]=C[i*(ncp+1)+j];
		  }
		}
		for(i=0;i<=ncp1;i++)
		{
		  for(j=0;j<=ncp;j++)
		  {
			ptend[i*(ncp+1)+j]=C[i*(ncp+1)+j];
		  }
		}
	}
	updatecore();
	setInit();
}
CMesh* CBezier::Clip(CFigure* f)
{
//	if(std::find(clipshape.begin(),clipshape.end(),f)==clipshape.end())
//		clipshape.push_back(f);
	return CFigure::Clip(f);
}
vector<double> CBezier::getKn()
{
	Kn.resize(ncp+deg+2);
	return Kn;
}
vector<CVector> CBezier::getCP()
{
	CP.resize(ncp+1);
	return CP;
}
void CBezier::addtovecBezier(CDC* hdc)
{
	try{
	int i,j;
	ptbegin.clear();
	ptend.clear();
	CP.clear();
	int ncp0=ContP.size();
	ncp=ncp0;
	if(!surf)
	{
		
		if(hdc!=NULL)
		{
			CPoint *Pt=new CPoint [ncp0];
		   for(int iter=0;iter<ncp0;iter++)
			{
				Pt[iter]=ContP[iter];
			}
		   iter=0;
			hdc->BeginPath();
			hdc->PolyBezier(Pt,ncp0);
			hdc->EndPath();
			hdc->FlattenPath();
			vector<CPoint>_p;
			vector<BYTE> _b;
			int n_p=hdc->GetPath(NULL,NULL,NULL);
			if(n_p>0){
			_p.resize(n_p);
			_b.resize(n_p);
			if(hdc->GetPath(_p.begin(),_b.begin(),n_p)){
				N=n_p;
				vMr.resize(n_p);
				Para.resize(n_p);
				if(name=="CBezier")
				{
				   for(iter=0;iter<n_p;iter++)
				   {
						vMr[iter]=_p[iter];
				   }
				}else
				{
							int lk=Kn[deg]*N;
							int lh=Kn[ncp+deg]*N;
							   Para_universp(0,1,N,Para);
					//			Knot_Univer(ncp,deg,Kn,0,1);

							   for(int iter=0;iter<n_p;iter++)
							   {
									vMr[iter]=NURBS(deg,ContP,ncp,Para[iter],Kn);
							   }
				}
		   }
		}

		}
//		if(prevstart<0) return;
		for(i=0;i<ncp0;i++)
		{
		ptbegin.push_back(ContP[i]);
		CP.push_back(ContP[i]);
		}
		ptend.assign(ptbegin.begin(),ptbegin.end());
		
		mesh.empty();
		lk=0;
		lh=N;
//		Para_universp(0,1,N-1,Para);
		if(vMr.size()==0) return;
	   for(int iter=lk;iter<lh;iter++)
		{
		   CVertex *_v=new CVertex(vMr[iter],Para[iter],0);
		   mesh.addVertex(_v);
		   _v=NULL;
		}
	   for(iter=lk;iter<lh-1;iter++)
		{
	       new CEdge(mesh.Vertex(iter),mesh.Vertex(iter + 1),mesh.Ecount());
		}
	   for(i=0;i<clipshape.size();i++)
	   {
		   CFigure::Clip(clipshape[i]);
	   }
/*		mesh2.empty();
	   for(iter=0;iter<ncp;iter++)
		{
		   float u=(float)iter/ncp;
		   CVertex * _v=new CVertex(ContP[iter],u,0);
		   mesh2.addVertex (_v);
		   _v=NULL;
		}
	   for(iter=0;iter<ncp-1;iter++)
		{
	       new CEdge(mesh2.Vertex(iter),mesh2.Vertex(iter + 1),mesh2.Ecount());
		}*/
		for(i=0;i<=ncp;i++)
		{
//		   mesh.addVertex (new CVertex(CP[i],0,0));
		}

	}else
	if(surf)
	{
		ptbegin.resize((ncp1+1)*(ncp+1));
		ptend.resize((ncp1+1)*(ncp+1));
		for(i=0;i<=ncp1;i++)
		{
		  for(j=0;j<=ncp;j++)
		  {
			ptbegin[i*(ncp+1)+j]=C[i*(ncp+1)+j];
		  }
		}
		for(i=0;i<=ncp1;i++)
		{
		  for(j=0;j<=ncp;j++)
		  {
			ptend[i*(ncp+1)+j]=C[i*(ncp+1)+j];
		  }
		}
	}
	if(!multiselect) 
		updatecore();
	setInit();
	}catch(...)
		{
		CString s=GetLastError();
		AfxMessageBox(s);
	}
}

void CBezier::addvec(vector<CVector> vectb, vector<CVector> vecte)
{
	if(!surf)
	{
/*	int i=0;
	ptbegin=vectb;
	ptend=vecte;
	for(pitere=ptbegin.begin();pitere<ptbegin.end();pitere++)
	{
		CP[i]=*pitere;
		i++;
	}
*/	
	   int lh=Kn[ncp+deg]*N;

		for(int i=0;i<=ncp;i++)
		{
//		   CP[i]= *mesh.Vertex(lh+1+i);
		}

	}
	else
	{
	  saddvec(vectb,vecte);
//	  surf0=false;
	}
//	CP[i]=ptend.back();

//	updatecore();


}

void CBezier::saddvec(vector<CVector> vectb, vector<CVector> vecte)
{
/*	if(!bffd)
	{
	int i=0;
	ptbegin=vectb;
	ptend=vecte;
	for(pitere=ptbegin.begin();pitere<ptbegin.end();pitere++)
	{
		C[i]=*pitere;
		i++;
	}
	}
	else
	{*/
	if(surf)
	{
	int i=0;
	ptbegin=vectb;
	ptend=vecte;
	CMesh::ivertex iv;
	for(pitere=ptbegin.begin(),piterb=ptend.begin(),iv=mesh.vbegin();iv!=mesh.vend();pitere++,piterb++,iv++)
	{
		(iv)->second->v=*pitere;
//		iv->n=*piterb;
	}
   ptend.push_back((mesh.vbegin())->second->v);
	updatecore();
	}
}
void CBezier::selectSM(CDC *hdc)
{
	CFigure::selectSM(hdc);
	return;
	CVector p;
	switch (linestate)
	{
	case(D0):
		{
			if(((Up)&&(click))||((multiselect)&&(click)))
			{
			Up=false;
			linestate=D1;
			}
			if((down)&&(!click))
			{
			down=false;
			}
			if((down)&&(move)&&(click))
			{
			move=false;
			click=false;
			}
		}
		break;
	case(D1):
		{
			if((down)&&(!click))
			{
			linestate=D0;
			down=false;
			}
			break;
		}
	
	}
}

/*void CBezier::polystate(CVector pos)
{
	CVector p;
	pos.snaptoplane(pos);
	switch (lstate)
	{
	case(L1):
		{
			if(ContP.size()==0)
			{
			ContP.push_back(pos);
			ContP.push_back(pos);
			}
			ContP.back()=pos;
			if(Up)
			{
			control1=pos;
			cancharge=true;
			lstate=L2;
			Up=false;
			move=false;
			down=false;
			}
		}
		break;
	case(L2):
		{
		    if (down)
			{
				control2=pos;
				lstate=L3;
				Up=false;
				move=false;
				down=false;

			}
			break;
		}
	case(L3):
		{
			if(move)
			{
				if(!pointinRegion(pos,control1))
				{
					ContP.clear();
					ptbegin.clear();
					ptend.clear();
					ContP.push_back(control2);
					ContP.push_back(pos);
					control1=pos;
					fPrevB=false;
					lstate=L4;
				}
				else 
				{
					ContP.push_back(control2);
					lstate=L5;
				}
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	case(L4):
		{
			if(Up)
			{
				ContP.back()=pos;
				lstate=L2;
				control1=pos;
				cancharge=true;
				Up=false;
				move=false;
				down=false;
				 tas++;

			}
			else
			{
				ContP.back()=pos;
			}
			break;
		}
	case(L5):
		{
			if(Up)
			{
				ContP.back()=pos;
				control1=pos;
				lstate=L6;
				cancharge=false;
				Up=false;
				move=false;
				down=false;
				 tas++;

			}
			else
			{
				ContP.back()=pos;
			}

			break;
		}
	case(L6):
		{
			if(down)
			{
//				ContP.push_back(pos);
//				ContP.push_back(pos);
				control2=pos;
				cancharge=false;
				lstate=L3;
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	
	}


}
*/
  
void CBezier::polystate(CVector pos)
{
	CVector p;
//	pos.snaptoplane(pos);
	switch (lstate)
	{
	case(L1):
		{
			if((down)&&(ContP.size()==0))
			{
			ContP.push_back(pos);
			ContP.push_back(pos);
			ContP.push_back(pos);
			ContP.push_back(pos);
			N=0;
			move=false;
			freemove=false;
			}
			if(down){
			int n=ContP.size();
			CVector be=ContP[n-3]; 
			control1=pos;
			be=pos-be;
			CVector md=be+pos;
			ContP[n-3]=pos;
			ContP[n-2]=pos;
			ContP.back()=pos;
			}
			if(Up)
			{
			cancharge=true;
			lstate=L2;
			Up=false;
			move=false;
			down=false;
//			fPrevB=true;;
			}
			else if(ContP.size()>0)
			{
			ContP.back()=pos;			
			}
		}
		break;
	case(L2):
		{
		    if (down)
			{
//				ContP.back()=pos;
				ContP.push_back(pos);
				ContP.push_back(pos);
				ContP.push_back(pos);
//				control2=pos;
//				lstate=L3;
//				Up=false;
				move=false;
				freemove=false;
//				fPrevB=false;
//				cancharge=false;
				down=false;

			}
			else
			if(move)
			{

			int n=ContP.size();
			CVector be=ContP[n-4],be1;
			be1=be;
			control1=pos;
			be=pos-be;
			CVector md=pos;
            ContP[n-5]=be1-be;
			ContP[n-3]=pos;
			ContP[n-2]=pos;
			ContP.back()=pos;
			move=false;
			}
			else
			if(Up)
			{
			cancharge=false;
			Up=false;
			move=false;
//			down=false;
//				fPrevB=true;
			Knot_UniverSp(0,1,ncp,deg,Kn);
//			Knot_Univer(ncp-3,deg,Kn,0,1);
			//ncp=ncp-3;//ContP.size();
			}else if(freemove)
			{
			int n=ContP.size();
			ContP[n-2]=pos;
				ContP.back()=pos;
				freemove=false;

			}
			
			break;
		}
	case(L3):
		{
			if(move)
			{
				if(!pointinRegion(pos,control1))
				{
//					ContP.clear();
//					ptbegin.clear();
//					ptend.clear();
//					ContP.push_back(control2);
//					ContP.push_back(pos);
					control1=pos;
					fPrevB=false;
					lstate=L4;
				}
				else 
				{
//					ContP.push_back(control2);
					int n=ContP.size();
					CVector be=control1; 
					CVector md=(be+pos)/2;
					ContP[n-3]=md;
					ContP[n-2]=md;
					lstate=L5;
				}
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	case(L4):
		{
			if(Up)
			{
				ContP.back()=pos;
				lstate=L2;
				control1=pos;
				cancharge=true;
				Up=false;
				move=false;
				down=false;
				 tas++;

			}
			else
			{
				ContP.back()=pos;
			}
			break;
		}
	case(L5):
		{
			if(Up)
			{
				ContP.back()=pos;
				control1=pos;
				lstate=L6;
				cancharge=false;
				Up=false;
				move=false;
				down=false;
				 tas++;

			}
			else
			{
				ContP.back()=pos;
			}

			break;
		}
	case(L6):
		{
			if(down)
			{
//				ContP.push_back(pos);
//				ContP.push_back(pos);
				control2=pos;
				cancharge=false;
				lstate=L3;
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	
	}


}

void CBezier::create(CVector pos)
{
	Up=true;
//	if(!cancharge)
	polystate(pos);


}

bool CBezier::getCharge(CDC *hdc)
{
	addtovecBezier(hdc);
//	addtovec(hdc);
//	updatecore();
	return cancharge;
}

void CBezier::initL()
{
	if(ContP.size()>2)
	{ 
//	ContP.clear();

	fPrevB=false;
	}
//	delete []Pprev;

}
void CBezier::initLBezier()
{
	ContP.clear();
	fPrevB=false;
	lstate=L1;
}

void CBezier::setMenuSelect(bool menu)
{
	menusel=menu;
	lstate=L3;
	CVector vtest(0,0,1);
//	polystate(NULL,vtest);
}


void CBezier::setMove(bool mv,CVector pos)
{
	move=mv;
//	if(!cancharge)
	polystate(pos);

}
void CBezier::setFreeMove(bool mv,CVector pos)
{
	freemove=mv;
//	if(!cancharge)
	polystate(pos);

}

void CBezier::computeHermite(CDC *hdc,CVector p1, CVector p2, CVector p1p, CVector p2p)
{

	double C[4][2]={0};
	double M[4][4]={
					{2,-3,0,1},
					{-2,3,0,0},
					{1,-2,1,0},
					{1,-1,0,0}
					};
	double G[2][4];
	G[0][0]=p1.x;
	G[0][1]=p2.x;
	G[0][2]=p1p.x;
	G[0][3]=p2p.x;
	G[1][0]=p1.y;
	G[1][1]=p2.y;
	G[1][2]=p1p.y;
	G[1][3]=p2p.y;


	C[0][0]=2*p1.x-2*p2.x+p1p.x+p2p.x;
	C[0][1]=-3*p1.x+3*p2.x+-2*p1p.x-p2p.x;
	C[0][2]=p1p.x;
	C[0][3]=p1.x;
	C[1][0]=2*p1.y-2*p2.y+p1p.y+p2p.y;
	C[1][1]=-3*p1.y+3*p2.y+-2*p1p.y-p2p.y;
	C[1][2]=p1p.y;
	C[1][3]=p1.y;

	

	hdc->MoveTo(p1);

	for (double t=0;t<1;t+=0.1)
	{
	double V[1][2]={0};
	double T[2][4]={
		{t*t*t,t*t,t,1},
		{t*t*t,t*t,t,1}};

	for(int i=0;i<4;i++)
	{
		V[0][0]+=C[i][0]*T[0][i];
		V[0][1]+=C[i][1]*T[1][i];
	}
	V[0][0]+=p1.x;
	V[0][1]+=p1.y;
	hdc->LineTo(V[0][0],V[0][1]);

	}


}


void CBezier::computeLagrange(CDC *hdc)
{
//  int *u;
//  int n,p,i;
	N=500; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=3;           // degree of polynomial = t-1

 

	vector<CVector>::iterator rsult;


	ncp=ContP.size()-1;
//	ncp=3;
	deg=ncp;
	if(ncp!=lkp)
	{
		int r=0;
	}

	int i=0;
	for (rsult=ContP.begin();rsult<ContP.end();rsult++)
	{
	CP[i]=*rsult;
	i++;
	}

	CVector *M=new CVector [501];
	CVector U[100];

	int d=deg;
	Para_universp(0,1,ncp,Kn);
	int j=0;

	vector<double> T;//[501];
	Para_universp(0,1,N,T);

	if(ncp>9)
	{
		i=0;
	}
	for (i=0;i<=d;i++)
		{
			U[i]=CP[i];
		}
	for(int t=0;t<N;t++)
	{
	
		for(int r=1;r<=d;r++)
		{
			for(i=0;i<=d-r;i++)
			{
				double er=Kn[i+r]-Kn[i];
				if(sqrt(er*er)<1E-3)
				{
				U[r*(d+1)+i].x=0;
				U[r*(d+1)+i].y=0;
				}
				else 
				{
				U[r*(d+1)+i].x=((Kn[i+r]-T[t])/(Kn[i+r]-Kn[i]))*U[(r-1)*(d+1)+i].x +((T[t]-Kn[i])/(Kn[i+r]-Kn[i]))*U[(r-1)*(d+1)+i+1].x;
				U[r*(d+1)+i].y=((Kn[i+r]-T[t])/(Kn[i+r]-Kn[i]))*U[(r-1)*(d+1)+i].y+((T[t]-Kn[i])/(Kn[i+r]-Kn[i]))*U[(r-1)*(d+1)+i+1].y;
				}
			}
		}

		if((t==(int)(Kn[3]*N))||(t==(int)(Kn[4]*N))||(t==(int)(Kn[5]*N)))
		{
			int s=0;
		}
		M[t]=U[d*(d+1)];
	}

	
//	CPprev=new CVector[N+1];

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	   
		hdc->MoveTo(CPprev[0]);
		for(int iter=0;iter<N;iter++)
		{
			hdc->LineTo(CPprev[iter]);
		}
	}
	
 	
    hdc->MoveTo(M[0]);
	for(int iter=0;iter<N;iter++)
	{
	hdc->LineTo(M[iter]);
	}

  	for (i=0; i<N;i++)
	{
	CPprev[i]=M[i];
	}

	lkp=ncp;

	fPrevB=true;

	delete []M;

}

void CBezier::computeBezier(CDC *hdc,CVector *Uv)
{
//  int *u;
//  int n,p,i;
	N=500; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
//	deg=2;           // degree of polynomial = t-1

 

//	vector<CVector>::iterator rsult;


//	ncp=ContP.size()-1;
//	ncp=3;
//	deg=ncp-1;
	CVector U[500];
	int i=0;
	for (int gl=0;gl<=deg;gl++)
	{
	U[gl]=Uv[gl];
	}
	if(ncp!=lkp)
	{
		int s=0;
	}

	CVector M[501];


//	int d=deg;

	vector<double> T;//[501];
	Para_universp(0,1,N,T);


	for(int t=0;t<=N;t++)
	{
	
		for(int r=1;r<=deg;r++)
		{
			for(i=r;i<=deg;i++)
			{
				U[r*(deg+1)+i].x=(1-T[t])*U[(r-1)*(deg+1)+i-1].x +T[t]*U[(r-1)*(deg+1)+i].x;
				U[r*(deg+1)+i].y=(1-T[t])*U[(r-1)*(deg+1)+i-1].y+T[t]*U[(r-1)*(deg+1)+i].y;
			}
		}

		M[t]=U[deg*(deg+1)+deg];
	}

	
//	CPprev=new CVector[N+1];

   
	if ((fPrevB)&&(lkp==ncp))
	{
	hdc->SetROP2(R2_NOTXORPEN); 
	   
		hdc->MoveTo(CPprev[0]);
		for(int iter=0;iter<N;iter++)
		{
			hdc->LineTo(CPprev[iter]);
		}
	}
	
 	
    hdc->MoveTo(M[0]);
	for(int iter=0;iter<N;iter++)
	{
	hdc->LineTo(M[iter]);
	}

  	for (i=0; i<N;i++)
	{
	CPprev[i]=M[i];
	}

	lkp=ncp;

	fPrevB=true;


}

void CBezier::computePieceBezier(CDC *hdc)
{
//  int *u;
//  int n,p,i;
	N=500; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=3;           // degree of polynomial = t-1

 

	vector<CVector>::iterator rsult;


	ncp=ContP.size()-1;
	int nc=3;
	deg=nc-1;
	CVector pts[100];

	CVector U[1000];
	int i=0;
	for (rsult=ContP.begin();rsult<ContP.end();rsult++)
	{
	pts[i]=*rsult;
	i++;
	}
	int jj=i;
	int s=0;
	

	if((fPrevB)&&(ncp!=lkp))
	{
//		CP[j]=CP[j-1];j++;
		CP[j]=CP[j-1]*2-CP[j-2];j++;
		CP[j]=pts[jj-2];j++;
		CP[j]=pts[jj-3];j++;
	}

	if(!fPrevB)
	{
		CP[j]=pts[jj-2];j++;
		CP[j]=pts[jj-1];j++;
		deg=1;
		computeBezier(hdc,&CP[j-2]);
	}
	if(nc>2)
	{
		deg=3;
		CP[j-1]=pts[jj-1];
		computeBezier(hdc,&CP[j-4]);
	}

	lkp=ncp;
		

}



void CBezier::computeSpline(CDC *hdc,double *U, vector<CVector> C,int i)
{
//  int *u;
//  int n,p,i;
	N=500; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
//	deg=3;           // degree of polynomial = t-1

 



	if(ncp!=lkp)
	{
		int r=0;
	}


	CVector *M=new CVector [501];
	CVector Mv[501];


	vector<double> T;//[501];

	Para_universp(0,1,N,T);

	if(ncp>9)
	{
//		int i=0;
	}
	for(int t=0;t<N;t++)
	{
		int r=0;
		for(int j=i-deg+r;j<=i;j++)
		{
		Mv[r*(N+1)+j].x=C[j].x;
		Mv[r*(N+1)+j].y=C[j].y;
		}
		r=1;
		for(j=i-deg+r;j<=i;j++)
		{
			Mv[r*(N+1)+j].x=((U[j+deg-r+1]-T[t])/(U[j+deg-r+1]-U[j]))*Mv[(r-1)*(N+1)+j-1].x +((T[t]-U[j])/(U[j+deg-r+1]-U[j]))*Mv[(r-1)*(N+1)+j].x;
			Mv[r*(N+1)+j].y=((U[j+deg-r+1]-T[t])/(U[j+deg-r+1]-U[j]))*Mv[(r-1)*(N+1)+j-1].y+((T[t]-U[j])/(U[j+deg-r+1]-U[j]))*Mv[(r-1)*(N+1)+j].y;
			r++;
		}
		M[t]=Mv[(r-1)*(N+1)+j-1];
	}

	
//	CPprev=new CVector[N+1];

//	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	   
		hdc->MoveTo(CPprev[0]);
		for(int iter=0;iter<N;iter++)
		{
			hdc->LineTo(CPprev[iter]);
		}
	}
	
 	
    hdc->MoveTo(M[0]);
	for(int iter=0;iter<N;iter++)
	{
	hdc->LineTo(M[iter]);
	}

  	for (i=0; i<N;i++)
	{
	CPprev[i]=M[i];
	}

	lkp=ncp;

	fPrevB=true;

	delete []M;

}

void CBezier::computePieceSpline(CDC *hdc)
{
//  int *u;
//  int n,p,i;
	N=500; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=3;           // degree of polynomial = t-1

 

	vector<CVector>::iterator rsult;


	ncp=ContP.size()-1;
	int nc=3;
	deg=nc-1;
	CVector pts[100];

	CVector U[1000];
	int i=0;
	for (rsult=ContP.begin();rsult<ContP.end();rsult++)
	{
	CP[i]=*rsult;
	i++;
	}
	int jj=i;
	int s=0;
	deg=ncp-1;

	Knot_Univer(ncp,deg,Kn,0,1);

	for(i=deg+1;i<=ncp;i++)
	{
	computeSpline(hdc,&Kn[i],CP,i);
	}

	lkp=ncp;
		

}





void CBezier::IDrawD1BSpline(CDC *hdc, CVector p1, CVector p2, CVector p3)
{

//  int *u;
//  int n,p,i;
//	N=50; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=3;           // degree of polynomial = t-1

 
    vector<CVector> pts;//[100];

	vector<CVector>::iterator rsult;


	ncp=ContP.size()-1;	
	if(ncp>3)
		{
		int jhk=0;
		}

	int i=0;

	 Para_universp(0,1,ncp+3,Para);
     Knot_Univer(ncp+2,deg,Kn,0,1);
	INT_curve(ContP,ncp,deg,Kn,Kn,CP);
	ncp+=2;

   int lk=Kn[deg]*N;
   int lh=Kn[ncp+deg]*N;



	CVector *M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

	CPoint *Pt=new CPoint [N+1];
	Para_universp(0,1,N,Para);

   for(int iter=lk;iter<=lh;iter++)
	 {
	   Mr[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
	}

  
   int s;
   for(iter=lk;iter<=lh;iter++)
	 {
	   Pt[iter-lk]=Mr[iter];
	   s=iter-lk;
	}
	
	CPen pen;

	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);

	int im=hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	   
 	hdc->Polyline(Pprev,s);

	}
	else
	{
		Pprev=new CPoint [N+1];
	}
	
 	hdc->Polyline(Pt,s);
	hdc->SelectObject(oldp);
 	for (i=0; i<=s;i++)
	{
	Pprev[i]=Pt[i];
	}
	
	delete []M;
	delete []Pt;
	hdc->SetROP2(im); 

	fPrevB=true;



}


void CBezier::DrawNURBS(CDC *hdc)
{
			CPoint *Pt1=new CPoint [ncp];
			int ncp0=ContP.size();
			ncp=ncp0;
		   for(int iter=0;iter<ncp0;iter++)
			{
				Pt1[iter]=ContP[iter];
			}
		   iter=0;
			hdc->BeginPath();
			hdc->PolyBezier(Pt1,ncp0);
			hdc->EndPath();
			delete [] Pt1;
			hdc->FlattenPath();
			vector<CPoint>_p;
			vector<BYTE> _b;
			int n_p=hdc->GetPath(NULL,NULL,NULL);
			if(n_p>0){
			_p.resize(n_p);
			_b.resize(n_p);
			if(hdc->GetPath(_p.begin(),_b.begin(),n_p)){
				N=n_p;
				Para.resize(N+1);
				   Para_universp(0,1,N,Para);
				   CPoint *Pt=new CPoint [N+1];
				  for(int iter=0;iter<N;iter++)
				   {
					   Pt[iter]=NURBS(deg,ContP,ncp,Para[iter],Kn);
				   }
				   CPen pen;
					pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
					CPen *oldp=hdc->SelectObject(&pen);

					CBrush brush;
					CBrush *ob;
					brush.CreateSolidBrush(bcolor);
					ob=hdc->SelectObject(&brush);
					hdc->Polyline(Pt,N+1);
					delete [] Pt;
				   if (cl)
				   {
					if(texture_file!="")
					{
						CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
				//        ScanPolygon(hdc,bcolor,Mr,lh-lk,&texture);
					}
					else
					{
				  //      ScanPolygon(hdc,bcolor,Mr,lh-lk,NULL);
					}
				   }

				   hdc->SelectObject(ob);
				   hdc->SelectObject(oldp);
			}
			}
}

void CBezier::DrawBSpline(CDC *hdc)
{

   addvec(ptbegin,ptend);
   CVector M[501];
	CPoint Pt[501];
	
	Para_universp(minpara,maxpara,N,Para);


   lk=Kn[deg]*N;
   lh=Kn[ncp+deg+1]*N;
   if(redraw)
   {
	   
	   if(Mr==NULL) Mr=new CVector[N+1];
      CMesh::ivertex iv=mesh.vbegin();
	  if(iv!=NULL){
   for(int iter=0;iter<N;iter++)
   {
	  Mr[iter]=/*Bspline(deg,CP,ncp,Para[iter],Kn);//*/NURBS(deg,CP,ncp+1,Para[iter],Kn);
	  (iv)->second->v=Mr[iter];
	  iv++;
   }
	  }
/*   updatecore();
   quadtree.empty();
   quadtree.assign(box);
   for(iter=0;iter<N;iter++)
   {
	  quadtree.insert(CRay(Mr[iter],Mr[iter+1]));
   }
*/
   updateffd();
   redraw=false;
   }
   if(ffd)
   setFFD(Mr);

   if (cl)
   {
	if(texture_file!="")
	{
		CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
        ScanPolygon(hdc,bcolor,Mr,lh-lk,&texture);
    }
	else
	{
        ScanPolygon(hdc,bcolor,Mr,lh-lk,NULL);
	}
   }
 

   CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);

	CBrush brush;
	CBrush *ob;
	brush.CreateSolidBrush(bcolor);
	ob=hdc->SelectObject(&brush);
	mesh.displayEdge(hdc);

   hdc->SelectObject(ob);
   hdc->SelectObject(oldp);

}





void CBezier::computeBspline(CDC *hdc, CVector p1, CVector p2, CVector p3, CVector p4)
{

	double Vx,Vy;
	hdc->MoveTo(p1);
	
	for (double t=0;t<1.05;t+=0.05)
	{
		Vx=(1-t)*(1-t)*(1-t)*p1.x+3*(1-t)*(1-t)*t*p2.x+3*(1-t)*t*t*p3.x+t*t*t*p4.x;
		Vy=(1-t)*(1-t)*(1-t)*p1.y+3*(1-t)*(1 -t)*t*p2.y+3*(1-t)*t*t*p3.y+t*t*t*p4.y;
		hdc->LineTo(Vx,Vy);
	}


}


CVector CBezier::NURBS( int p, vector<CVector>& P,int n,double u,vector<double>& U)
{
	double base[100],resultN=0;
	CVector result;
	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	double test=0;
		
	for (int i=0; i<n; i++)
	{
		base[i]=compute_base(p,u,U,i,n-1);
		resultN+=base[i]*P[i].w;
	}
	if(resultN==0)
	{
		int hgb=0;
	}
	for(i=0;i<n;i++)
	{
//		base=compute_base(p,u,U,i,n);
		result.x+=(base[i]*P[i].x*P[i].w)/resultN;
		result.y+=(base[i]*P[i].y*P[i].w)/resultN;
		result.z+=(base[i]*P[i].z*P[i].w)/resultN;
		result.w+=(base[i]*P[i].w)/resultN;
//		test+=base;
	}
		result.x=result.x/result.w;
		result.y=result.y/result.w;
		result.z=result.z/result.w;
//		result.w=1;

	return result;
}
CVector CBezier::NURBS( int p, vector<CVector> P,int n,double u,double v,vector<double> U)
{
	double base[100],base1[100],resultN=0;

	vector<CVector> Pr;Pr.resize(n+1);

	CVector result;
	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	double test=0;
	CVector vc;
		
	for (int j=0; j<=n; j++)
	{
		base[j]=compute_base(p,u,U,j,n);
	}
	for (int i=0; i<=n; i++)
	{
		base1[i]=compute_base(p,v,U,i,n);
	}

	for (i=0; i<=n; i++)
	{

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;


		for (j=0; j<=n; j++)
		{
			resultN+=base[j]*P[i*(n+1)+j].w;
		}
		for(j=0;j<=n;j++)
		{
	//		base=compute_base(p,u,U,i,n);
			result.x+=(base[j]*P[i*(n+1)+j].x*P[i*(n+1)+j].w)/resultN;
			result.y+=(base[j]*P[i*(n+1)+j].y*P[i*(n+1)+j].w)/resultN;
			result.z+=(base[j]*P[i*(n+1)+j].z*P[i*(n+1)+j].w)/resultN;
			result.w+=(base[j]*P[i*(n+1)+j].w)/resultN;
	//		test+=base;
		}
		Pr[i].x=result.x/result.w;
		Pr[i].y=result.y/result.w;
		Pr[i].z=result.z/result.w;
//		Pr[i].w=1;
	}

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;

	for (i=0; i<=n; i++)
	{
		resultN+=base1[i]*Pr[i].w;
	}
	for (i=0; i<=n; i++)
	{
		result.x+=(base1[i]*Pr[i].x*Pr[i].w)/resultN;
		result.y+=(base1[i]*Pr[i].y*Pr[i].w)/resultN;
		result.z+=(base1[i]*Pr[i].z*Pr[i].w)/resultN;
		result.w+=(base1[i]*Pr[i].w)/resultN;
	}

	result.x=result.x/result.w;
	result.y=result.y/result.w;
	result.z=result.z/result.w;
//	result.w=1;


	return result;
}


CVector CBezier::NURBS( int p,int p1, vector<CVector> P,int n,int n1,double u,double v,vector<double> U,vector<double> V)
{
	double base[100],base1[100],resultN=0;

	vector<CVector> Pr;Pr.resize(n1+1);

	CVector result;
	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	double test=0;
	CVector vc;
		
	for (int j=0; j<=n; j++)
	{
		base[j]=compute_base(p,u,U,j,n);
	}
	for (int i=0; i<=n1; i++)
	{
		base1[i]=compute_base(p1,v,V,i,n1);
	}

	double Nres=0;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n1;j++)
		{
			Nres+=base[i]*base1[j]*P[i*(n1+1)+j].w;
		}
	}

/*	for (i=0; i<=n1; i++)
	{

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;


		for (j=0; j<=n; j++)
		{
			resultN+=base[j]*P[i*(n+1)+j].w;
		}
		for(j=0;j<=n;j++)
		{
	//		base=compute_base(p,u,U,i,n);
			result.x+=(base[j]*P[i*(n+1)+j].x*P[i*(n+1)+j].w)/resultN;
			result.y+=(base[j]*P[i*(n+1)+j].y*P[i*(n+1)+j].w)/resultN;
			result.z+=(base[j]*P[i*(n+1)+j].z*P[i*(n+1)+j].w)/resultN;
			result.w+=(base[j]*P[i*(n+1)+j].w)/resultN;
	//		test+=base;
		}
		Pr[i].x=result.x/result.w;
		Pr[i].y=result.y/result.w;
		Pr[i].z=result.z/result.w;
//		Pr[i].w=1;
	}
*/
	for (i=0; i<=n1; i++)
	{

		for(j=0;j<=n;j++)
		{
			result.x+=(base[j]*base1[i]*P[i*(n+1)+j].x*P[i*(n+1)+j].w)/Nres;
			result.y+=(base[j]*base1[i]*P[i*(n+1)+j].y*P[i*(n+1)+j].w)/Nres;
			result.z+=(base[j]*base1[i]*P[i*(n+1)+j].z*P[i*(n+1)+j].w)/Nres;
			result.w+=(base[j]*base1[i]*P[i*(n+1)+j].w)/Nres;
		}
	}

/*	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;


		for(j=0;j<=n;j++)
		{
	//		base=compute_base(p,u,U,i,n);
			result.x+=(base[j]*P[i*(n+1)+j].x*P[i*(n+1)+j].w);
			result.y+=(base[j]*P[i*(n+1)+j].y*P[i*(n+1)+j].w);
			result.z+=(base[j]*P[i*(n+1)+j].z*P[i*(n+1)+j].w);
			result.w+=(base[j]*P[i*(n+1)+j].w);
	//		test+=base;
		}
		Pr[i].x=result.x/result.w;
		Pr[i].y=result.y/result.w;
		Pr[i].z=result.z/result.w;
//		Pr[i].w=1;
	}


	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;

	for (i=0; i<=n1; i++)
	{
		resultN+=base1[i]*Pr[i].w;
	}
	for (i=0; i<=n1; i++)
	{
		result.x+=(base1[i]*Pr[i].x*Pr[i].w)/resultN;
		result.y+=(base1[i]*Pr[i].y*Pr[i].w)/resultN;
		result.z+=(base1[i]*Pr[i].z*Pr[i].w)/resultN;
		result.w+=(base1[i]*Pr[i].w)/resultN;
	}*/

	result.x=result.x/result.w;
	result.y=result.y/result.w;
	result.z=result.z/result.w;
	result.w=1;


	return result;
}
CVector CBezier::Sur_deriv( int p,int p1, vector<CVector> P,int n,int n1,double u,double v,vector<double> U,vector<double> V,vector<double> T,bool du,bool dv)
{
	double base[100],base1[100],based[100],base1d[100],resultN=0;

	vector<CVector> Pr;Pr.resize(n1+1);

	CVector result,resultu,resultv;
	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	
	resultu.x=0;
	resultu.y=0;
	resultu.z=0;
	resultu.w=0;

	resultv.x=0;
	resultv.y=0;
	resultv.z=0;
	resultv.w=0;

	double test=0;
	CVector vc;

	if(du)
	{
	for (int j=0; j<=n; j++)
	{
		based[j]=compute_D1base(p,p,u,U,U,j,n);
	}
	}
	for (int j=0; j<=n; j++)
	{
		base[j]=compute_base(p,u,U,j,n);
	}

	if(dv)
	{
	for (int i=0; i<=n1; i++)
	{
		base1d[i]=compute_D1base(p1,p1,v,V,V,i,n1);
	}
	}
	for (int i=0; i<=n1; i++)
	{
		base1[i]=compute_base(p1,v,V,i,n1);
	}

	double Nres=0,Nresu=0,Nresv=0;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n1;j++)
		{
			Nres+=base[i]*base1[j]*P[i*(n1+1)+j].w;
		}
	}

	if(du)
	{
	for(int i=0;i<=n;i++)
	{
		for(j=0;j<=n1;j++)
		{
			Nresu+=based[i]*base1[j]*P[i*(n1+1)+j].w;
		}
	}
	}
	if(dv)
	{
	for(int i=0;i<=n;i++)
	{
		for(j=0;j<=n1;j++)
		{
			Nresv+=base[i]*base1d[j]*P[i*(n1+1)+j].w;
		}
	}
	}
	
	for (i=0; i<=n1; i++)
	{

		for(j=0;j<=n;j++)
		{
			result.x+=(base[j]*base1[i]*P[i*(n+1)+j].x*P[i*(n+1)+j].w);
			result.y+=(base[j]*base1[i]*P[i*(n+1)+j].y*P[i*(n+1)+j].w);
			result.z+=(base[j]*base1[i]*P[i*(n+1)+j].z*P[i*(n+1)+j].w);
			result.w+=(base[j]*base1[i]*P[i*(n+1)+j].w);
		}
	}

	if(du)
	{
	for (i=0; i<=n1; i++)
	{

		for(j=0;j<=n;j++)
		{
			resultu.x+=(based[j]*base1[i]*P[i*(n+1)+j].x*P[i*(n+1)+j].w);
			resultu.y+=(based[j]*base1[i]*P[i*(n+1)+j].y*P[i*(n+1)+j].w);
			resultu.z+=(based[j]*base1[i]*P[i*(n+1)+j].z*P[i*(n+1)+j].w);
			resultu.w+=(based[j]*base1[i]*P[i*(n+1)+j].w);
		}
	}
	}

	if(dv)
	{
	for (i=0; i<=n1; i++)
	{

		for(j=0;j<=n;j++)
		{
			resultv.x+=(base[j]*base1d[i]*P[i*(n+1)+j].x*P[i*(n+1)+j].w);
			resultv.y+=(base[j]*base1d[i]*P[i*(n+1)+j].y*P[i*(n+1)+j].w);
			resultv.z+=(base[j]*base1d[i]*P[i*(n+1)+j].z*P[i*(n+1)+j].w);
			resultv.w+=(base[j]*base1d[i]*P[i*(n+1)+j].w);
		}
	}
	}

	if(du)
	{
	result.x=(Nres*resultu.x-Nresu*result.x)/pow(Nres,2);
	result.y=(Nres*resultu.y-Nresu*result.y)/pow(Nres,2);
	result.z=(Nres*resultu.z-Nresu*result.z)/pow(Nres,2);
	result.w=(Nres*resultu.w-Nresu*result.w)/pow(Nres,2);
	}
	if(dv)
	{
	result.x=(Nres*resultv.x-Nresu*result.x)/pow(Nres,2);
	result.y=(Nres*resultv.y-Nresu*result.y)/pow(Nres,2);
	result.z=(Nres*resultv.z-Nresu*result.z)/pow(Nres,2);
	result.w=(Nres*resultv.w-Nresu*result.w)/pow(Nres,2);
	}

	if(result.w==0) result.w=1;

	result.x=result.x/result.w;
	result.y=result.y/result.w;
	result.z=result.z/result.w;
//	result.w=1;


	return result;
}


CVector CBezier::NURBS( int p,int p1,int p2, vector<CVector> P,int n,int n1,int n2,double u,double v,double w,vector<double> U,vector<double> V,vector<double> W)
{
	double base[100],base1[100],base2[100],resultN=0;

	vector<CVector> Pr;Pr.resize(n1+n2+1);

	int k=0;
	CVector result;
	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	double test=0;
	CVector vc;
		
	for (int j=0; j<=n; j++)
	{
		base[j]=compute_base(p,u,U,j,n);
	}
	for (int i=0; i<=n1; i++)
	{
		base1[i]=compute_base(p1,v,V,i,n1);
	}
	for (i=0; i<=n2; i++)
	{
		base2[i]=compute_base(p2,w,W,i,n2);
	}

	double Nres=0;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n1;j++)
		{
			for(k=0;k<=n2;k++)
			{
				Nres+=base[i]*base1[j]*base2[k]*P[i*(n1+1)*(n2+1)+j*(n2+1)+k].w;//i*(n1+1)*+j].w;
			}
		}
	}

	for (i=0; i<=n2; i++)
	{
		for(j=0;j<=n1;j++)
		{
			for(k=0;k<=n;k++)
			{
				result.x+=(base[k]*base1[j]*base2[i]*P[i*(n1+1)*(n+1)+j*(n+1)+k].x*P[i*(n1+1)*(n+1)+j*(n+1)+k].w)/Nres;//*(n+1)+j].x*P[i*(n+1)+j].w)/Nres;
				result.y+=(base[k]*base1[j]*base2[i]*P[i*(n1+1)*(n+1)+j*(n+1)+k].y*P[i*(n1+1)*(n+1)+j*(n+1)+k].w)/Nres;//[i*(n+1)+j].y*P[i*(n+1)+j].w)/Nres;
				result.z+=(base[k]*base1[j]*base2[i]*P[i*(n1+1)*(n+1)+j*(n+1)+k].z*P[i*(n1+1)*(n+1)+j*(n+1)+k].w)/Nres;//[i*(n+1)+j].z*P[i*(n+1)+j].w)/Nres;
				result.w+=(base[k]*base1[j]*base2[i]*P[i*(n1+1)*(n+1)+j*(n+1)+k].w)/Nres;//[i*(n+1)+j].w)/Nres;
			}
		}
	}
/*
	for (int i1=0; i1<=n2; i1++)
	{
	for (i=0; i<=n1; i++)
	{

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;


		for (j=0; j<=n; j++)
		{
			resultN+=base[j]*P[i*(n+1)+j].w;
		}
		for(j=0;j<=n;j++)
		{
	//		base=compute_base(p,u,U,i,n);
			result.x+=(base[j]*P[i1*(n1+1)*(n+1)+i*(n+1)+j].x*P[i1*(n1+1)*(n+1)+i*(n+1)+j].w)/resultN;
			result.y+=(base[j]*P[i1*(n1+1)*(n+1)+i*(n+1)+j].y*P[i1*(n1+1)*(n+1)+i*(n+1)+j].w)/resultN;
			result.z+=(base[j]*P[i1*(n1+1)*(n+1)+i*(n+1)+j].z*P[i1*(n1+1)*(n+1)+i*(n+1)+j].w)/resultN;
			result.w+=(base[j]*P[i1*(n1+1)*(n+1)+i*(n+1)+j].w)/resultN;
	//		test+=base;
		}
		Pr[i].x=result.x/result.w;
		Pr[i].y=result.y/result.w;
		Pr[i].z=result.z/result.w;
//		Pr[i].w=1;
	}

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;

	for (i=0; i<=n1; i++)
	{
		resultN+=base1[i]*Pr[i].w;
	}
	for (i=0; i<=n1; i++)
	{
		result.x+=(base1[i]*Pr[i].x*Pr[i].w)/resultN;
		result.y+=(base1[i]*Pr[i].y*Pr[i].w)/resultN;
		result.z+=(base1[i]*Pr[i].z*Pr[i].w)/resultN;
		result.w+=(base1[i]*Pr[i].w)/resultN;
	}

		Pr[i1].x=result.x/result.w;
		Pr[i1].y=result.y/result.w;
		Pr[i1].z=result.z/result.w;
	}

	result.x=0;
	result.y=0;
	result.z=0;
	result.w=0;
	resultN=0;

	for (i=0; i<=n2; i++)
	{
		resultN+=base2[i]*Pr[i].w;
	}
	for (i=0; i<=n2; i++)
	{
		result.x+=(base2[i]*Pr[i].x*Pr[i].w)/resultN;
		result.y+=(base2[i]*Pr[i].y*Pr[i].w)/resultN;
		result.z+=(base2[i]*Pr[i].z*Pr[i].w)/resultN;
		result.w+=(base2[i]*Pr[i].w)/resultN;
	}
*/
	result.x=result.x/result.w;
	result.y=result.y/result.w;
	result.z=result.z/result.w;
	result.w=1;


	return result;
}



//B-Spline calculation
CVector CBezier::Bspline( int p, vector<CVector> P,int n,double u,vector<double> U)
{
	double base;
	CVector result;
	result.x=0;
	result.y=0;
	result.z=0;
	double test=0;
		
	for (int i=0; i<n; i++)
	{
		base=compute_base(p,u,U,i,n);
		result.x+=base*P[i].x;
		result.y+=base*P[i].y;
		result.z+=base*P[i].z;
		test+=base;
	}
	return result;
}

//Base calculation for B-spline blending function

double CBezier::compute_base(int p, double u,vector<double> B,int i,int n)
{
	int interdeg=0;
	int ab=p+1;
	vector<double> result(ab*(p+n+3));
//	result=new double[ab*(p+n+3)];
	double test=0;
	int emult=0,bmult=0;


	for(int iter=0;iter<=p+n+1;iter++)
	{
		if (B[0]==B[iter])
		{
			bmult++;
		}
		else
		if (B[iter]==B[p+n+1])
		{
			emult++;
		}
	}

	
	for( iter=0;iter<p+n+1;iter++)
	{
		if ((B[0]==u)&&(iter==p))
		{
			if (bmult=n+1)
			{
			result[ab*iter]=1;
		//	return 1;
			}
		}
		else
		if ((u==B[p+n+1])&&(iter==n))
		{
			if (emult=p+1)
			{
			result[ab*iter]=1;
		//	return 1;
			}
		}
		else
	
		if((B[iter]<=u)&&(u<B[iter+1]))
		{
			result[ab*iter]=1;
		}
		else
		{
 			result[ab*iter]=0;
		}
	}

	
	for (int j=1;j<=p;j++)
	{
		test=0;
		for(int iter=0;iter<n+p+1-j;iter++)
		{
	
			if(!(B[iter+j]==B[iter]))
			{
				result[ab*iter+j]=(u-B[iter])/(B[iter+j]-B[iter])*result[ab*iter+(j-1)];
			}
			else
			{
				result[ab*iter+j]=0;
			}

			if(!(B[iter+j+1]==B[iter+1]))
			{
				result[ab*iter+j]+=((B[iter+j+1]-u)/(B[iter+j+1]-B[iter+1]))*result[ab*(iter+1)+(j-1)];
			}
			test+=result[ab*iter+j];
		
		}
	}

	double rs=result[ab*i+p];
		
		return rs;
}


// base calculation for differential B-Spline

double CBezier::computebase(int pp,int p, double u,vector<double> U,int i,int n)
{
	double result[500];
	int interdeg=0;
	int ab=p+1;
	double test=0;
	int emult=0,bmult=0;


	for(int iter=0;iter<=p+n+1;iter++)
	{
		if (U[0]==U[iter])
		{
			bmult++;
		}
		else
		if (U[iter]==U[p+n+1])
		{
			emult++;
		}
	}

	
	for( iter=0;iter<=p+n+1;iter++)
	{
		if ((U[0]==u)&&(iter==p))
		{
			if (bmult=n+1)
			{
			result[ab*iter]=1;
			}
		}
		else
		if ((u==U[p+n+1])&&(iter==n))
		{
			if (emult=n+1)
			{
			result[ab*iter]=1;
			}
		}
		else
	
		if((U[iter]<=u)&&(u<U[iter+1]))
		{
			result[ab*iter]=1;
		}
		else
		{
 			result[ab*iter]=0;
		}
	}

	
	for (int j=1;j<=p;j++)
	{
		test=0;
		for(int iter=0;iter<=n+p+1-j;iter++)
		{
	
			if(!(U[iter+j]==U[iter]))
			{
				result[ab*iter+j]=(u-U[iter])/(U[iter+j]-U[iter])*result[ab*iter+(j-1)];
			}
			else
			{
				result[ab*iter+j]=0;
			}

			if(!(U[iter+j+1]==U[iter+1]))
			{
				result[ab*iter+j]+=((U[iter+j+1]-u)/(U[iter+j+1]-U[iter+1]))*result[ab*(iter+1)+(j-1)];
			}
			test+=result[ab*iter+j];
		
		}
	}
	double rs=result[ab*i+pp];
//	delete [] result;
		
		return rs;
}





double CBezier::compute_D1base(int pp,int p, double u,vector<double> T,vector<double> U,int i,int n)
{
	double f,d;
	if ((T[i+p]-T[i])!=0)
	{
		d=(p/(T[i+p]-T[i]))*computebase(pp-1,p,u,U,i,n);
	}
	else
	{
		d=0;
	}
	if ((T[i+p+1]-T[i+1])!=0)
	{
		f=-(p/(T[i+p+1]-T[i+1]))*computebase(pp-1,p,u,U,i+1,n);
	}
	else
	{
		f=0;
	}
	return f+d;

}

double CBezier::compute_D2base(int pp,int p, double u,vector<double> T,vector<double> U,int i,int n)
{
	double f,d;
	if ((T[i+p]-T[i])!=0)
	{
		d=(p/(T[i+p]-T[i]))*compute_D1base(pp-1,p-1,u,T,U,i,n);
	}
	else
	{
		d=0;
	}
	if ((T[i+p+1]-T[i+1])!=0)
	{
		f=-(p/(T[i+p+1]-T[i+1]))*compute_D1base(pp-1,p-1,u,T,U,i+1,n);
	}
	else
	{
		f=0;
	}
	return f+d;
}





void CBezier::insertknot(double t, int h, int p,vector<double> U,vector<CVector> P,int n)
{

	/*Input: knot t in [uk, uk+1) with initial multiplicity s to be inserted h times, 
			where h+s is less than or equal to p, the degree of the given B-spline curve 
	  Output: a new set of control points after t is inserted h times 

	  Let control points Pk, Pk-1, ..., Pk-p be renamed as Pk,0, Pk-1,0, ..., Pk-p,0 by adding a second subscript 0. 

		for r := 1 to h do 

		for i := k-p+r to k-s do 

		begin 

		Let ai,r = (t - ui) / ( ui+p-r+1 - ui ) 
		Let Pi,r = (1 - ai,r) Pi-1,r-1 + ai,r Pi,r-1 

		end 

		The new set of control points are constructed from the original ones from P0 to Pk-p,
		followed by the top edge of the diagram above (i.e., Pk-p+1,1, Pk-p+2,2, ..., Pk-p+h,h),
		followed by the right edge of the diagram (i.e., Pk-p+h+1,h, Pk-p+h+2,h, ...., Pk-s,h),
		followed by the bottom edge of the diagram (i.e., Pk-s,h-1, Pk-s,h-2, ...., Pk-s,1), 
		followed by the original control points Pk-s, ..., Pk, ..., Pn. 

	*/

	int s=0;
	int m=n+p+1;
	double Uc[50];
//	n=n+h;

	int k;
	int l=0;

	for(int iter=0;iter<m;iter++)
	{
		if((U[iter]<=t)&&(t<U[iter+1]))
		{
			k=iter;
	
			l++;
		}
			if(U[iter]==t)
		{
			s++;
		}

	}
	if((h+s)<=p+1)
	{
	CVector PV[100];;
	

	int vm=k-p;
	if (vm<0) vm=0;
	int vk=k-s;
	if (vk<0) vk=0;
	int r=0;
	for(iter=n;iter>=0;iter--)
	{
	PV[(n+1)*r+iter].x=P[iter].x*P[iter].w;
	PV[(n+1)*r+iter].y=P[iter].y*P[iter].w;
	PV[(n+1)*r+iter].w=P[iter].w;
	}

	double a[100];
	
		
		for(r=1; r<=h;r++)
		{

			for(int i=vm+r; i<=vk; i++)
			{
				a[(n+1)*r+i]=(t-U[i])/(U[i+p-r+1]-U[i]);
				PV[(n+1)*r+i].x=(1-a[(n+1)*r+i])*PV[(n+1)*(r-1)+(i-1)].x+a[(n+1)*r+i]*PV[(n+1)*(r-1)+i].x;
				PV[(n+1)*r+i].y=(1-a[(n+1)*r+i])*PV[(n+1)*(r-1)+(i-1)].y+a[(n+1)*r+i]*PV[(n+1)*(r-1)+i].y;
				PV[(n+1)*r+i].w=(1-a[(n+1)*r+i])*PV[(n+1)*(r-1)+(i-1)].w+a[(n+1)*r+i]*PV[(n+1)*(r-1)+i].w;
			}

		}

	int hi;
	int hh=0;
	for(hi=0;hi<=k;hi++)
	{
		Uc[hi]=U[hh];hh++;

	}
	for(hi=k+1;hi<k+1+h;hi++)
	{
	Uc[hi]=t;
	}
	for(hi=k+1+h;hi<=m+h;hi++)
	{
		Uc[hi]=U[hh];
		hh++;
	}
	m=m+h;
	for(hi=0;hi<=m;hi++)
	{
		U[hi]=Uc[hi];
	}


	r=0;
	int j=0;
	for(iter=0;iter<=k-p;iter++)
	{
	P[j].x=PV[(n+1)*r+iter].x/PV[(n+1)*r+iter].w;
	P[j].y=PV[(n+1)*r+iter].y/PV[(n+1)*r+iter].w;
	P[j].w=PV[(n+1)*r+iter].w;
	j++;
	}


	for(iter=1;iter<=h;iter++)
	{
	P[j].x=PV[(n+1)*iter+(k-p+iter)].x/PV[(n+1)*iter+(k-p+iter)].w;
	P[j].y=PV[(n+1)*iter+(k-p+iter)].y/PV[(n+1)*iter+(k-p+iter)].w;
	P[j].w=PV[(n+1)*iter+(k-p+iter)].w;
	j++;
	}

	for(iter=k-p+h+1;iter<=k-s;iter++)
	{
	P[j].x=PV[(n+1)*h+iter].x/PV[(n+1)*h+iter].w;
	P[j].y=PV[(n+1)*h+iter].y/PV[(n+1)*h+iter].w;
	P[j].w=PV[(n+1)*h+iter].w;
	j++;
	}

	for(iter=h-1;iter>=1;iter--)
	{
	P[j].x=PV[(n+1)*iter+(k-s)].x/PV[(n+1)*iter+(k-s)].w;
	P[j].y=PV[(n+1)*iter+(k-s)].y/PV[(n+1)*iter+(k-s)].w;
	P[j].w=PV[(n+1)*iter+(k-s)].w;
	j++;
	}

	r=0;
	for(iter=k-s;iter<=n;iter++)
	{
	P[j].x=PV[(n+1)*r+iter].x/PV[(n+1)*r+iter].w;
	P[j].y=PV[(n+1)*r+iter].y/PV[(n+1)*r+iter].w;
	P[j].w=PV[(n+1)*r+iter].w;
	j++;
	}
	
//	delete [] a;
	}

	ncp+=h;

}



void CBezier::Oslo(int p,vector<double> B,vector<double> T,vector<CVector> P,int n,int m)
{
	double result[150];
	int interdeg=0;
	int ab=p+1;
	int k;
	double test=0;
	int emult=0,bmult=0;
	CVector b[50];
	CVector bb[50];
	CVector bv[50];
	int l;



	for (int i=0;i<=m;i++)
	{

	
	for(int iter=0;iter<=p+n+1;iter++)
	{
	
		if((B[iter]<=T[i+deg])&&(T[i+deg]<B[iter+1]))
		{
			k=iter;
		}
	}

	for(int jj=k-deg;jj<=k;jj++)
	{
		b[jj]=P[jj];
	}

	for(int j=deg;j>=1;j--)
	{
		int h=1;
		for(l=k-j+1;l<=k;l++)
		{
			bv[l]=b[l-1]*((B[j+l]-T[i+j])/(B[j+l]-B[l]))+b[l]*((T[i+j]-B[l])/(B[j+l]-B[l]));
			h++;
		}
		for(l=k-j+1;l<=k;l++)
		{
			b[l]=bv[l];
		}

	}
	bb[i]=b[l-1];
	}

	for(int jj=0;jj<=m;jj++)
	{
		P[jj]=bb[jj];
	}


}


void CBezier::insertknotU(double t, int h, int p,vector<double> U,int n)
{

	int s=0;
	int m=n+p+1;
	double Uc[50];
//	n=n+h;

	int k;
	int l=0;

	for(int iter=0;iter<=m;iter++)
	{
		if(((U[iter]<=t)&&(t<U[iter+1])||(U[iter]==t)))
		{
			if (s==0)
			{
			k=iter;
			}
			s++;
	
			l++;
		}

	}

	if (s!=0)
	{
	for(iter=0;iter<=k;iter++)
	{
		Uc[iter]=U[iter];

	}
	for(iter=k+1;iter<=k+h;iter++)
	{
		Uc[iter]=t;

	}
	for(iter=k+h+1;iter<=m+h;iter++)
	{
		Uc[iter]=U[iter-h];

	}
	for(iter=0;iter<=m+h;iter++)
	{
		U[iter]=Uc[iter];

	}
	}


}



// The Uniformly Spaced Method for parameter

void CBezier::Para_universp(double min,double maxu, int n,vector<double>& T)
{

//	T.clear();
	double interv;
	interv=(maxu-min)/(n-1);
/*	for(int i=0; i<=n; i++)
	{
		T.push_back(min);
	}*/
	T[0]=min;
	for(int i=1; i<=n;i++)
	{
		T[i]=i*interv+min;
	}

}


//knot vector Uniformelly spaced 

double * CBezier::Knot_UniverSp(double min,double maxu, int n,int p)
{
	double *V;
	V=new double [n+p+2];
	int m=n+p+1;

	for(int i=0; i<=p; i++)
	{
		V[i]=min;
	}
	for(int j=p+1; j<=n; j++)
	{
		V[j]=(double)j/(n+p+1);
	}

	for(j=n+1; j<=m; j++)
	{
		V[j]=1;
	}

	return V;

}
void CBezier::Knot_UniverSp(double min,double maxu, int n,int p,vector<double>& V)
{
	int m=n+p+1;

	for(int i=0; i<=p; i++)
	{
		V[i]=min;
	}
	for(int j=p+1; j<n; j=j+p)
	{
		for(int h=j;h<p+j;h++)
		{
			V[h]=(double)(j)/(n+p+1);
		}
	}

	for(j=n; j<m; j++)
	{
		V[j]=1;
	}

//	return V;

}

// The chord Length Method for parameter computation

double* CBezier::Para_chord(double min,double max,CVector *point,int n)
{
	//	 min t0 minimum
	//	 max tm
	//	 n number of point in the T vector
	//	 point the vector with the point 

	
	double *p;

	int basex=0;
	double dx=0;
	double dy=0;
	double d=0;
	double rx,ry;

	for(int i=1;i<=n;i++)
	{
		rx=point[i].x-point[i-1].x;
		ry=point[i].y-point[i-1].y;
		dx+=sqrt(rx*rx);
		dy+=sqrt(ry*ry);
	}
	d=sqrt(dx*dx+dy*dy);

	double *T;
	T=new double [n+1];

	for(i=0; i<=n; i++)
	{
		T[i]=0;
	}


	T[0]=min;
	T[n]=max;

	double dxk=0;
	double dyk=0;
	double dk=0;


	for(i=0;i<=n;i++)
	{
		dyk=0;
		dxk=0;
		for(int j=1; j<=i;j++)
		{
			rx=point[j].x-point[j-1].x;
			ry=point[j].y-point[j-1].y;
			dxk+=sqrt(rx*rx);
			dyk+=sqrt(ry*ry);
		}
		dk=sqrt(dxk*dxk+dyk*dyk);
		T[i]=min+(dk/d)*(max-min);
	}
	return T;

}
void CBezier::Para_chord(double min,double max,CVector *point,int n,double* T)
{
	//	 min t0 minimum
	//	 max tm
	//	 n number of point in the T vector
	//	 point the vector with the point 

	double d=0,dx=0;
	CVector rx;

	for(int i=1;i<=n;i++)
	{
		rx=point[i]-point[i-1];
		d+=absc(rx);
	}


	for(i=0; i<=n; i++)
	{
		T[i]=0;
	}


	T[0]=min;
	T[n]=max;


	for(i=1;i<=n-1;i++)
	{
		rx=point[i]-point[i-1];
		dx=absc(rx);
		T[i]=T[i-1]+(dx/d);
	}

}


//knot vector: Gresville algorithme

double* CBezier::Grev_knot1(int n, int p, vector<double> T)
{
	double *u;
//	int m=n+p+1;
	u=new double [n+1];
	double dt=0,k;

	for(int i=0;i<=p;i++)
	{
		Kn[i]=0;
	}
	k=i;
	for(j=1; j<=n-p; j++,k++)
	{
		dt=0;
		for(int i=j; i<=j+p-1;i++)
		{
		dt+=T[i];
		}
		Kn[k]=dt/p;
	}
//	k=i;
	for(;k<=n+p+1;k++)
	{
		Kn[k]=1;
	}

	return u;
}


//knot vector generation:De Boor algorithm 

void CBezier::Knot_deBoor(int n, int p, vector<double> T,vector<double> U)
{
//	double *u;
	int m=n+p+1;
//	u=new double [m+1];
	double dt=0;

	for(int i=0; i<=m; i++)
	{
		if (i<=p)
		{
		U[i]=0;
		}
		else 
		if((i>p)&&(i<=n))
		{
			for(int j=1;j<=n-p;j++)
			{
				dt=0;
				for(int k=j; k<=j+p-1;k++)
				{
				dt+=T[k]/p;
				}
				U[j+p]=dt;
				i++;
			}
			i--;
		}
		 else
		{
			U[i]=1;
		}

	}
//	return u;
}

// The Universal Method: knot vector generation

void CBezier::Knot_Univer(int n, int p,vector<double>& U,double min, double max)
{
	int m=n+p+1;

	for(int k=0;k<=m;k++)
	{
		U[k]=min;
	}
	double dt=0;

	int j;
	for(int i=0; i<=m; i++)
	{
		if (i<p)
		{
		U[i]=min;
		}
		else 
		if(i>=p)
		{
			if(i<=n)
			{
				for(j=0;j<=n-p+1;j++)
				{
					U[j+p]=(((max-min)*(double)j)/(n-p+1))+min;
					i=j+p;
				}
				
			}
			 else
			{
				U[i]=max;
			}
		}
	}
}


void CBezier::INT_curve(vector<CVector> point,int n, int p,vector<double> U, vector<double> T,vector<CVector>& P)
{
	CMatrix mathelp;


	int nv=n+2;
	double *N;
	N=new double[(n+3)*(n+3)];

	double *Dx, *Dy,*Dz;
	Dx=new double[n+5];
	Dy=new double[n+5];
	Dz=new double[n+5];


	for(int j=0; j<=nv;j++)
	{
	N[j]=compute_D2base(p,p,T[p],T,U,j,nv);
	}

	for(int i=1; i<=nv-1;i++)
	{
	 for(int j=0;j<=nv;j++)
		{

			N[i*(nv+1)+j]=compute_base(p, T[p+(i-1)],U,j,nv);
		}

	}

	for(j=0; j<=nv;j++)
	{
	N[i*(nv+1)+j]=compute_D2base(p,p,T[p+(i-1)-1],T,U,j,nv);
	}

	
	Dx[0]=0;//-(CPprev[n+2].x-CPprev[n+1].x)*2;
	Dy[0]=0;//(CPprev[n+2].y-CPprev[n+1].y)*2;
	Dz[0]=0;//(CPprev[n+2].y-CPprev[n+1].y)*2;

	for(i=1;i<=n+1;i++)
	{
		Dx[i]=point[i-1].x;
		Dy[i]=point[i-1].y;
		Dz[i]=point[i-1].z;
	}
	Dx[i]=(point[n].x-point[n-1].x);
	Dy[i]=(point[n].y-point[n-1].y);
	Dz[i]=(point[n].z-point[n-1].z);

	
	mathelp.LUG(Dx,N,nv,nv,1);
	mathelp.LUG(Dy,N,nv,nv,1);
	mathelp.LUG(Dz,N,nv,nv,1);

	for(i=0;i<=n+2;i++)
	{
		P[i].x=Dx[i];
		P[i].y=Dy[i];
		P[i].z=Dz[i];
	}

	delete [] Dx;
	delete [] Dy;
	delete [] Dz;
	delete [] N;

}

/*
void CBezier::INT_curve2(vector<CVector> point,int n, int p,vector<double> U, vector<double> T,vector<CVector>& P)
{
	CMatrix mathelp;


	int nv=n+2;
	double *N;
	N=new double[(n+3)*(n+3)];

	double *Dx, *Dy,*Dz;
	Dx=new double[n+5];
	Dy=new double[n+5];
	Dz=new double[n+5];


	for(int j=0; j<=nv;j++)
	{
	N[j]=compute_D2base(p,p,T[p],T,U,j,nv);
	}

	for(int i=1; i<=nv-1;i++)
	{
	 for(int j=0;j<=nv;j++)
		{

			N[i*(nv+1)+j]=compute_base(p, T[p+(i-1)],U,j,nv);
		}

	}

	for(j=0; j<=nv;j++)
	{
	N[i*(nv+1)+j]=compute_D2base(p,p,T[p+(i-1)-1],T,U,j,nv);
	}

	
	Dx[0]=0;//-(CPprev[n+2].x-CPprev[n+1].x)*2;
	Dy[0]=0;//(CPprev[n+2].y-CPprev[n+1].y)*2;
	Dz[0]=0;//(CPprev[n+2].y-CPprev[n+1].y)*2;

	for(i=1;i<=n+1;i++)
	{
		Dx[i]=point[i-1].x;
		Dy[i]=point[i-1].y;
		Dz[i]=point[i-1].z;
	}
	Dx[i]=(point[n].x-point[n-1].x);
	Dy[i]=(point[n].y-point[n-1].y);
	Dz[i]=(point[n].z-point[n-1].z);

	
	mathelp.LUG(Dx,N,nv,nv,1);
	mathelp.LUG(Dy,N,nv,nv,1);
	mathelp.LUG(Dz,N,nv,nv,1);

	for(i=0;i<=n+2;i++)
	{
		P[i].x=Dx[i];
		P[i].y=Dy[i];
		P[i].z=Dz[i];
	}

	delete [] Dx;
	delete [] Dy;
	delete [] Dz;
	delete [] N;

}
*/

void CBezier::INT_curveI(CVector* point,int n, int p,vector<double> U, vector<double> T,CVector* P)
{
	CMatrix mathelp;


	int nv=n;
	double *N;
	N=new double[(n+3)*(n+3)];

	double *Dx, *Dy,*Dz;
	Dx=new double[n+5];
	Dy=new double[n+5];
	Dz=new double[n+5];



	for(int i=0; i<=nv;i++)
	{
	 for(int j=0;j<=nv;j++)
		{
			N[i*(nv+1)+j]=compute_base(p, T[p+i],U,j,nv);
		}


	}


	

	for(i=0;i<=n;i++)
	{
		Dx[i]=point[i].x;
		Dy[i]=point[i].y;
		Dz[i]=point[i].z;
	}

	
	mathelp.LUG(Dx,N,nv,nv,1);
	mathelp.LUG(Dy,N,nv,nv,1);
	mathelp.LUG(Dz,N,nv,nv,1);

	for(i=0;i<=n;i++)
	{
		P[i].x=Dx[i];
		P[i].y=Dy[i];
		P[i].z=Dz[i];
	}

	delete [] Dx;
	delete [] Dy;
	delete [] Dz;
	delete [] N;

}




CVector  CBezier::surface_Boor(vector<CVector> P,int m,int n,int p,int q, double u, double v,vector<double> U, vector<double> V)
{
	int s=0, ss=0,t=0,dd,cc;
	int pu=m+p+1;
	CVector *q_i,p_uv;
	q_i=new CVector [n+1];

	double base1,base2;
	p_uv.x=0;
	p_uv.y=0;
	
	
	double test=0,test1=0,test2=0;

	for (int c=0;c<=pu;c++)
	{
		if(U[c]==u)
		{
			s++;
		}
		if((U[c]<=u)&&(u<U[c+1]))
		{
			dd=c;

		}
	}
	for (c=0;c<=pu;c++)
	{
		if(V[c]==v)
		{
			t++;
		}
		if((V[c]<=v)&&(v<V[c+1]))
		{
			cc=c;

		}

	}


	int li=cc-s;
	int lj=dd-t;

	if (cc-p>=0)
	{
	for (int i=cc-p;i<=li;i++)
		{
		//	q_i[i]=insert_Boor(v, q,V,&P[i*(m+1)],m);
			/*base1=compute_base(q,v,V,j,m);
			test1+=base1;
			q_i[i].x+=base1*P[i*m+j].x;
			q_i[i].y+=base1*P[i*m+j].y;*/
		}
//		p_uv=insert_Boor(u, p,U,q_i,m);
	}
			
		/*for(i=max(cc-p,0);i<=li;i++)
		{
			base2=compute_base(p,u,U,i,n);
			test2+=base2;
			p_uv.x+=base2*q_i[i].x;
			p_uv.y+=base2*q_i[i].y;
		}*/
		test=test1*test2;;
//	delete q_i;
	return p_uv;
}


double * CBezier::surface_KnotCLR(vector<CVector> point,int m,int n)
{
	/*
	Input: (m+1)×(n+1) data points di,j;
	Output: Parameters in the u-direction s0, ..., sm
          and parameters in the v-direction t0, ..., tn;
	Algorithm:

      ** calculate s0, ..., sm **
      for j := 0 to n do ** column j **
            Compute a set of m+1 parameters u0,j, u1,j, ..., um,j; 
			for i := 0 to m do
            si = (ui,0 + ui,1 + ... + ui,n)/(n+1); ** parameters for the u-direction are available **

      ** calculate t0, ..., tn **
      for i := 0 to m do ** row i **
            Compute a set of n+1 parameters vi,0, vi,1, ..., vi,n; for j := 0 to n do
            tj = (v0,j + v1,j + ... + vn,j)/(m+1); ** parameters for the v-direction are available **
	*/


	CVector *pt;

	pt=new CVector[(n+1)*(m+1)];


	double *vs;
	double *v;

	vs=new double [N+1];

	v=new double [N+1];

	for(int i=0;i<=m;i++)
	{
		v[i]=0;
	}

	for(i=0; i<=m;i++)
	{
		vs=Para_chord(0,1,&point[(1+n)*i],N);
	
		for(int j=0;j<=n;j++)
		{
			v[i]+=vs[j]/(n+1);
		}
	}
	return v;
}


double * CBezier::surface_KnotCLC(vector<CVector> point,int m,int n)
{
	/*
	Input: (m+1)×(n+1) data points di,j;
	Output: Parameters in the u-direction s0, ..., sm
          and parameters in the v-direction t0, ..., tn;
	Algorithm:

      ** calculate s0, ..., sm **
      for j := 0 to n do ** column j **
            Compute a set of m+1 parameters u0,j, u1,j, ..., um,j; 
			for i := 0 to m do
            si = (ui,0 + ui,1 + ... + ui,n)/(n+1); ** parameters for the u-direction are available **

      ** calculate t0, ..., tn **
      for i := 0 to m do ** row i **
            Compute a set of n+1 parameters vi,0, vi,1, ..., vi,n; for j := 0 to n do
            tj = (v0,j + v1,j + ... + vn,j)/(m+1); ** parameters for the v-direction are available **
	*/


	CVector *pt;

	pt=new CVector[(n+1)*(m+1)];


	double *us;
	double *s;

	us=new double [N+1];

	s=new double [N+1];

	for(int i=0;i<=m;i++)
	{
		s[i]=0;
	}

	for (int j=0;j<=m;j++)
	{
		for(int i=0; i<=n;i++)
		{
		pt[(1+n)*j+i]=point[(1+n)*i+j];
		}
	}


	for(j=0; j<=n;j++)
	{
		us=Para_chord(0,1,&pt[(1+m)*j],N);
	
		for(int i=0;i<=m;i++)
		{
			s[j]+=us[i]/(m+1);
		}
	}

	return s;
}






double * CBezier::surface_KnotUSC(int m,int n,vector<CVector> point)
{
	/*
	Input: (m+1)×(n+1) data points di,j;
	Output: Parameters in the u-direction s0, ..., sm
          and parameters in the v-direction t0, ..., tn;
	Algorithm:

      ** calculate s0, ..., sm **
      for j := 0 to n do ** column j **
            Compute a set of m+1 parameters u0,j, u1,j, ..., um,j; 
			for i := 0 to m do
            si = (ui,0 + ui,1 + ... + ui,n)/(n+1); ** parameters for the u-direction are available **

      ** calculate t0, ..., tn **
      for i := 0 to m do ** row i **
            Compute a set of n+1 parameters vi,0, vi,1, ..., vi,n; for j := 0 to n do
            tj = (v0,j + v1,j + ... + vn,j)/(m+1); ** parameters for the v-direction are available **
	*/


	double *vs;
	double *v;

	CVector *pt;
	pt=new CVector[(n+1)*(m+1)];

	vs=new double [n+1];
	v=new double [n+1];

	for(int i=0;i<=n;i++)
	{
		v[i]=0;
	}
	
	for (int j=0;j<=n;j++)
	{
		for(int i=0; i<=m;i++)
		{
		pt[(1+m)*j+i]=point[(1+m)*i+j];
		}
	}


	for(i=0; i<=n;i++)
	{
//		Para_universp(0,1,N,vs);
		for(int j=0;j<=m;j++)
		{
			v[i]+=vs[j]/(m+1);
		}
	}
	
	return v;
}


double * CBezier::surface_KnotUSR(int m,int n,vector<CVector> point)
{
	/*
	Input: (m+1)×(n+1) data points di,j;
	Output: Parameters in the u-direction s0, ..., sm
          and parameters in the v-direction t0, ..., tn;
	Algorithm:

      ** calculate s0, ..., sm **
      for j := 0 to n do ** column j **
            Compute a set of m+1 parameters u0,j, u1,j, ..., um,j; 
			for i := 0 to m do
            si = (ui,0 + ui,1 + ... + ui,n)/(n+1); ** parameters for the u-direction are available **

      ** calculate t0, ..., tn **
      for i := 0 to m do ** row i **
            Compute a set of n+1 parameters vi,0, vi,1, ..., vi,n; for j := 0 to n do
            tj = (v0,j + v1,j + ... + vn,j)/(m+1); ** parameters for the v-direction are available **
	*/


	double *vs;
	double *v;

	vs=new double [N+1];
	v=new double [N+1];



	for(int i=0;i<=n;i++)
	{
		v[i]=0;
	}

	for(i=0; i<=m;i++)
	{
//		Para_universp(0,1,N,vs);
 		for(int j=0;j<=n;j++)
		{
			v[i]+=vs[j]/(n+1);
		}

	}
	
	
	return v;
}






CVector CBezier::insert_Boor(double t, int p,vector<double> U,vector<CVector> P,int n)
{
	int h=0;
	int s=0;
	int m=n+p+1;
	int c=n;
//	n=n+h;

	int k;
	int l=0;

	for(int iter=0;iter<=m;iter++)
	{
		if((U[iter]<t)&&(t<U[iter+1]))
		{
			s=0;
			h=p;
			k=iter;
		}
		if(U[iter]==t)
		{
			s++;
			h=p-s;
			k=iter;
		}
	}

	if ((h>0)&&(k-p>=0))
	{
	CVector *PV;
	PV=new CVector [(n+3)*(n+3)];

	double *arv;
	arv=new double[(n+3)*(n+3)];
	
	for(iter=0;iter<=n;iter++)
	{
	PV[iter*(n+1)]=P[iter];
	}

		
	for(int r=1; r<=h;r++)
	{
		for(int i=k-p+r; i<=k-s; i++)
		{
			arv[(n+1)*i+r]=(t-U[i])/(U[i+p-r+1]-U[i]);
			PV[(n+1)*i+r].x=(1-arv[(n+1)*i+r])*PV[(n+1)*(i-1)+(r-1)].x+arv[(n+1)*i+r]*PV[(n+1)*i+(r-1)].x;
			PV[(n+1)*i+r].y=(1-arv[(n+1)*i+r])*PV[(n+1)*(i-1)+(r-1)].y+arv[(n+1)*i+r]*PV[(n+1)*i+(r-1)].y;
		}
	}
	delete [] arv;
	CVector result=PV[(n+1)*(k-s)+(p-s)];
	delete [] PV;
	
	return result; 
	}
	else
		return -1;
}

void CBezier::Bohms(double t, int p,vector<double>& U,vector<CVector>& P,int &n)
{
	vector<CVector> Pv;
	int k=0;
	int m=n+p+1;
	vector<double> Uc;



	for(int iter=0;iter<=m;iter++)
	{
		if((U[iter]<=t)&&(t<U[iter+1]))
		{
			k=iter;
		}
	}

	for(iter=0;iter<ncp;iter++)
	{
	P[iter].x=P[iter].x*P[iter].w;
	P[iter].y=P[iter].y*P[iter].w;
	P[iter].z=P[iter].z*P[iter].w;
	}

	for(int i=0;i<=n+1;i++)
	{
		Pv.push_back(v0);
		if((0<=i)&&(i<=k-p))
		{
			Pv[i]=P[i];
		}

		if(((k-p+1<=i)&&(i<=k))&&(U[i+p]!=U[i]))
		{
			double a1=(t-U[i])/(U[i+p]-U[i]);
			double a2=(U[i+p]-t)/(U[i+p]-U[i]);
			Pv[i].x=P[i].x*(a1)+P[i-1].x*(a2);
			Pv[i].y=P[i].y*(a1)+P[i-1].y*(a2);
			Pv[i].z=P[i].z*(a1)+P[i-1].z*(a2);
			Pv[i].w=P[i].w*(a1)+P[i-1].w*(a2);
		}

		if((k+1<=i)&&(i<=n+1))
		{
			Pv[i]=P[i-1];
		}

	}	
/*
	for(i ftr4tgb nkuy5b lkint i=0;i<n+1;i++)
	{
		if((0<=i)&&(i<=k-p+1))
		{
			Pv[i]=P[i];
		}

		if((k-p+2<=i)&&(i<=k))
		{
			if(U[i+p-1]==U[i]) continue;
			Pv[i].x=P[i].x*((t-U[i])/(U[i+p-1]-U[i]))+P[i-1].x*((U[i+p-1]-t)/(U[i+p-1]-U[i]));
			Pv[i].y=P[i].y*((t-U[i])/(U[i+p-1]-U[i]))+P[i-1].y*((U[i+p-1]-t)/(U[i+p-1]-U[i]));
			Pv[i].z=P[i].z*((t-U[i])/(U[i+p-1]-U[i]))+P[i-1].z*((U[i+p-1]-t)/(U[i+p-1]-U[i]));
			Pv[i].w=P[i].w*((t-U[i])/(U[i+p-1]-U[i]))+P[i-1].w*((U[i+p-1]-t)/(U[i+p-1]-U[i]));
		}

		if((k+1<=i)&&(i<=n+1))
		{
			Pv[i]=P[i-1];
		}

	}
*/
	for(iter=0;iter<=k;iter++)
	{
		Uc.push_back(U[iter]);

	}
	
	Uc.push_back(t);

	for(iter=k+2;iter<=m+1;iter++)
	{
		Uc.push_back(U[iter-1]);

	}
	n=n+1;
	P.resize(P.size()+1);
	U.resize(U.size()+1);

	for(iter=0;iter<=n+p+1;iter++)
	{
		U[iter]=Uc[iter];

	}

	for(i=0;i<n;i++)
	{
		P[i].x=Pv[i].x/Pv[i].w;
		P[i].y=Pv[i].y/Pv[i].w;
		P[i].z=Pv[i].z/Pv[i].w;
		P[i].w=Pv[i].w;
	}
//	Pv.clear();
//	Uc.clear();
//	delete []Pv;
//	delete []Uc;

}

void CBezier::Bohms(double u,double v,double w, int pu,int pv,int pw,vector<double>& U,vector<double>& V,vector<double>& W,vector<CVector>& P,int &nu,int &nv,int &nw)
{
	vector<CVector> Pv((nu+2)*(nv+2)*(nw+2));
	vector<double> Uc(U.size());
	int k=0;
	int m=nu+pu+1;


	//u direction
	if((u!=0)&&(u!=1))
	{

	for(int iter=0;iter<=m;iter++)
	{
		if((U[iter]<=u)&&(u<U[iter+1]))
		{
			k=iter;
		}
	}

	for(int a=0;a<=nw;a++)
	{
		for(int j=0;j<=nv;j++)
		{
			for(iter=0;iter<=nu;iter++)
			{
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			}
		}
	}


	for(a=0;a<=nw;a++)
	{
		for(j=0;j<=nv;j++)
		{
			for(int i=0;i<=nu+1;i++)
			{
				if((0<=i)&&(i<=k-pu))
				{
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i]=P[a*(nv+1)*(nu+1)+j*(nu+1)+i];
				}

				if((k-pu+1<=i)&&(i<=k))
				{
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].x*((u-U[i])/(U[i+pu]-U[i]))+P[a*(nv+1)*(nu+1)+j*(nu+1)+i-1].x*((U[i+pu]-u)/(U[i+pu]-U[i]));
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].y*((u-U[i])/(U[i+pu]-U[i]))+P[a*(nv+1)*(nu+1)+j*(nu+1)+i-1].y*((U[i+pu]-u)/(U[i+pu]-U[i]));
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].z*((u-U[i])/(U[i+pu]-U[i]))+P[a*(nv+1)*(nu+1)+j*(nu+1)+i-1].z*((U[i+pu]-u)/(U[i+pu]-U[i]));
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i].w=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].w*((u-U[i])/(U[i+pu]-U[i]))+P[a*(nv+1)*(nu+1)+j*(nu+1)+i-1].w*((U[i+pu]-u)/(U[i+pu]-U[i]));
				}

				if((k+1<=i)&&(i<=nu+1))
				{
					Pv[a*(nv+1)*(nu+2)+j*(nu+2)+i]=P[a*(nv+1)*(nu+1)+j*(nu+1)+i-1];
				}

			}
		}
	}

	for(iter=0;iter<=k;iter++)
	{
		Uc[iter]=U[iter];

	}
	
	Uc[iter]=u;

	for(iter=k+2;iter<=m+1;iter++)
	{
		Uc[iter]=U[iter-1];

	}
	if((u!=0)&&(u!=1)) nu=nu+1;

	for(iter=0;iter<=nu+pu+1;iter++)
	{
		U[iter]=Uc[iter];

	}

//	P.resize(P.size()+nu);
	P.clear();
	CVector bv;
	for(a=0;a<=nw;a++)
	{
		for(j=0;j<=nv;j++)
		{
			for(int i=0;i<=nu;i++)
			{
				bv.x=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.y=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.z=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.w=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P.push_back(bv);
/*				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].x=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].y=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].z=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].w=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
*/			}
		}
	}
	}
 //v direction
	if((v!=0)&&(v!=1))
	{
	Uc.resize(V.size());
	k=0;
	m=nv+pv+1;
	for(int iter=0;iter<=m;iter++)
	{
		if((V[iter]<=v)&&(v<V[iter+1]))
		{
			k=iter;
		}
	}

	for(int a=0;a<=nw;a++)
	{
		for(iter=0;iter<=nu;iter++)
		{
			for(int j=0;j<=nv;j++)
			{
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			}
		}
	}

	for(a=0;a<=nw;a++)
	{
		for(int i=0;i<=nu;i++)
		{
			for(int j=0;j<=nv+1;j++)
			{
				if((0<=j)&&(j<=k-pv))
				{
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i]=P[a*(nv+1)*(nu+1)+j*(nu+1)+i];
				}

				if((k-pv+1<=j)&&(j<=k))
				{
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].x*((v-V[j])/(V[j+pv]-V[j]))+P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i].x*((V[j+pv]-v)/(V[j+pv]-V[j]));
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].y*((v-V[j])/(V[j+pv]-V[j]))+P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i].y*((V[j+pv]-v)/(V[j+pv]-V[j]));
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].z*((v-V[j])/(V[j+pv]-V[j]))+P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i].z*((V[j+pv]-v)/(V[j+pv]-V[j]));
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i].w=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].w*((v-V[j])/(V[j+pv]-V[j]))+P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i].w*((V[j+pv]-v)/(V[j+pv]-V[j]));
				}

				if((k+1<=j)&&(j<=nv+1))
				{
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i]=P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i];
				}

			}
		}
	}

	for(iter=0;iter<=k;iter++)
	{
		Uc[iter]=V[iter];

	}
	
	Uc[iter]=v;

	for(iter=k+2;iter<=m+1;iter++)
	{
		Uc[iter]=V[iter-1];

	}
	if((v!=0)&&(v!=1)) nv=nv+1;

	for(iter=0;iter<=nv+pv+1;iter++)
	{
		V[iter]=Uc[iter];

	}

//	P.resize(P.size()+nv*nu);
	CVector bv;
	P.clear();
	for(a=0;a<=nw;a++)
	{
		for(j=0;j<=nv;j++)
		{
			for(int i=0;i<=nu;i++)
			{
				bv.x=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.y=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.z=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.w=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P.push_back(bv);
			}
		}
	}


	}



 //w direction
	if((w!=0)&&(w!=1))
	{
	Uc.resize(W.size());
	k=0;
	m=nw+pw+1;
	for(int iter=0;iter<=m;iter++)
	{
		if((W[iter]<=w)&&(w<W[iter+1]))
		{
			k=iter;
		}
	}

	for(int a=0;a<=nw;a++)
	{
		for(iter=0;iter<=nu;iter++)
		{
			for(int j=0;j<=nv;j++)
			{
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].x*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].y*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].z*P[a*(nv+1)*(nu+1)+j*(nu+1)+iter].w;
			}
		}
	}

	for(a=0;a<=nw+1;a++)
	{
		for(int i=0;i<=nu;i++)
		{
			for(int j=0;j<=nv;j++)
			{
				if((0<=j)&&(j<=k-pw))
				{
					Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i]=P[a*(nv+1)*(nu+1)+j*(nu+1)+i];
				}

				if((k-pv+1<=j)&&(j<=k))
				{
					Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].x*((w-W[j])/(W[j+pw]-W[j]))+P[(a-1)*(nv+1)*(nu+1)+j*(nu+1)+i].x*((W[j+pw]-w)/(W[j+pw]-W[j]));
					Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].y*((w-W[j])/(W[j+pw]-W[j]))+P[(a-1)*(nv+1)*(nu+1)+j*(nu+1)+i].y*((W[j+pw]-w)/(W[j+pw]-W[j]));
					Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].z*((w-W[j])/(W[j+pw]-W[j]))+P[(a-1)*(nv+1)*(nu+1)+j*(nu+1)+i].z*((W[j+pw]-w)/(W[j+pw]-W[j]));
					Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w=P[a*(nv+1)*(nu+1)+j*(nu+1)+i].w*((w-W[j])/(W[j+pw]-W[j]))+P[(a-1)*(nv+1)*(nu+1)+j*(nu+1)+i].w*((W[j+pw]-w)/(W[j+pw]-W[j]));
				}

				if((k+1<=j)&&(j<=nv+1))
				{
					Pv[a*(nv+2)*(nu+1)+j*(nu+1)+i]=P[a*(nv+1)*(nu+1)+(j-1)*(nu+1)+i];
				}

			}
		}
	}

	for(iter=0;iter<=k;iter++)
	{
		Uc[iter]=W[iter];

	}
	
	Uc[iter]=w;

	for(iter=k+2;iter<=m+1;iter++)
	{
		Uc[iter]=W[iter-1];

	}
	if((v!=0)&&(v!=1)) nw=nw+1;

	for(iter=0;iter<=nw+pw+1;iter++)
	{
		W[iter]=Uc[iter];

	}

//	P.resize(P.size()+nw);
	P.clear();
	CVector bv;
	for(a=0;a<=nw;a++)
	{
		for(j=0;j<=nv;j++)
		{
			for(int i=0;i<=nu;i++)
			{
				bv.x=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.y=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.z=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				bv.w=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P.push_back(bv);
/*				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].x=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].x/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].y=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].y/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].z=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].z/Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
				P[a*(nv+1)*(nu+1)+j*(nu+1)+i].w=Pv[a*(nv+1)*(nu+1)+j*(nu+1)+i].w;
*/			}
		}
	}


	}


//	delete []Pv;
//	delete []Uc;

}


vector<CVector>  CBezier::INT_surface(vector<CVector> point,int n, int m,int q,int p,vector<double> V,vector<double> U,vector<double> Tv,vector<double> Tu)
{
	
	/*Input: (m+1)×(n+1) data points dij and degree (p,q);
	Output: A B-spline surface of degree (p,q) that contains all data points;
	Algorithm:

			Compute parameters in the u-direction s0, s1, ..., sm and the knot vector U;
			Compute parameters in the v-direction t0, t1, ..., tn and the knot vector V;
		     for d := 0 to n do ** for column d **
				begin ** computing "intermediate data points" q's **
                  Apply curve interpolation to column d of data points (i.e., d0d, d1d, ... dmd) using
                      # degree p
                      # parameters s0, s1, ..., sm
                      # knot vector U 
                  The result is column d of the "intermediate data points" q0d, q1d, ..., qmd 
				  end 
			for c := 0 to m do ** for row c **
				begin ** computing the desired control points p's **
                  Apply curve interpolation to row c of the q's (i.e., qc0, qc1, ... qcn) using
                      # degree q
                      # parameters t0, t1, ..., tn
                      # knot vector V 
                  The result is row c of the desired control points pc0, pc1, ..., pcn 
				 end 
	*/
	
	
	CVector **q_d;
	q_d=new CVector*[n+1];

	vector< vector<CVector> > qd(m+n+3);
	vector< vector<CVector> > rd(m+n+3);

//	CVector **r_d;
//	r_d=new CVector*[m+1];

	CVector *pt;
	pt=new CVector[point.size()];

	vector<CVector>pt1(m+1);
//	Para_universp(0,1,m+3,Para);
	std::copy(point.begin(),point.end(),pt);


	for(int d=0;d<=n;d++)
	{
//		q_d[d]=new CVector[n+1];
		qd[d].resize(m+5);

		std::copy(&pt[(m+1)*d],&pt[(m+1)*d]+m+1,pt1.begin());

		INT_curve(pt1,m,q,V,V,qd[d]);
	}
	CMatrix mathelp;
	mathelp.Transpose(qd,n+1,m+3);

	pt1.resize(n+3);

//	Knot_Univer(n+3,f1.deg,Kn,0,1);
	for(int c=0; c<=m+2;c++)
	{
//		r_d[c]=new CVector[m+1];
		rd[c].resize(n+5);

		std::copy(qd[c].begin(),qd[c].begin()+n+1,pt1.begin());
		
		INT_curve(pt1,n,q,V,V,rd[c]);
//		INT_curveI(pt1.begin(),n,p,U,U,rd[c].begin());
	}

	mathelp.Transpose(rd,m+3,n+3);

	for (int i=0;i<=n+2;i++)
	{
/*		for (int j=0;j<=n+2;j++)
		{
			point[(n+3)*i+j]=*(rd[i].begin()+j);
		}
*/		for (int j=0;j<=m+2;j++)
		{
			point[(m+3)*i+j]=*(rd[i].begin()+j);
		}
	}




/*	for(d=0;d<=n;d++)
	{
		delete [] q_d[d];
	}

	for(c=0; c<=m;c++)
	{
		delete [] r_d[c];
	}

	delete [] r_d;
	delete [] q_d;*/
	delete [] pt;

	return point;

}


//DEL void CBezier::sethandle(int hn)
//DEL {
//DEL 	handle=hn;
//DEL 
//DEL }

//DEL int CBezier::gethandle()
//DEL {
//DEL 	return handle;
//DEL 
//DEL }

int CBezier::PtonSpline(CVector point)
{
   
   CVector *M=new CVector[N+1];
//   Para=new double[N+1];
   Para_universp(0,1,N,Para);
//     Knot_Univer(ncp+2,deg,Kn,0,1);

   int lk=Kn[deg]*N;
  
   for(int iter=0;iter<=N-1;iter=iter+1)
   {
	   CVector nb=NURBS(deg,CP,ncp-1,Para[iter],Kn);
	   CVector nbplus=NURBS(deg,CP,ncp-1,Para[iter+1],Kn);

		CVector vpoint(nb,point);
	   CVector v(nb,nbplus);
		CVector v2=nb+nbplus;
		v2=v2/2;

		double v11=absc(v2-nb);
		double v12=absc(v2-point);

	  if ((pointtoVector(v,vpoint)<5)&&(v12<=v11))
	  {
		 // hitpoint=nb;
		   delete []M;
//		   delete []Para;

		   return iter; 
	  }
	 }

   delete []M;
//   delete []Para;
   return -1;
 
}

void CBezier::deletenode(CVector point, CDC *hdc)
{
	if(ncp>3)
	{
		bool c=false;
	//	drawdel(hdc);
		int i,k,i0=0,ip=0;
		for(i=0;i<ncp;i=i+3,i0++)
		{
			if(pointinRegion(point,ContP[i]))
			{
				ip=i0;
				k=i-1;
				c=true;
				break;
			}
		}
		if(c)
		{
//			for(i=k;i<ncp;i++)
//			{
				ContP.erase(ContP.begin()+k,ContP.begin()+k+deg);
//			}
			ncp=ncp-deg;
			int irep=0;
			int i0=0;
			vector<int> vecpos;
			for(vector<double>::iterator _i=Kn.begin();_i!=Kn.end();_i++)
			{
				if(*_i==irep)
				{
					i0++;
					if(i0==deg)
					{
						vecpos.push_back(*_i-deg);
						i0=0;
					}
				}
			}

//			Knot_Univer(ncp,deg,Kn,0,1);
			Kn.erase(Kn.begin()+vecpos[ip],Kn.begin()+vecpos[ip]+deg);

			addtovecBezier();
//			UpdateSM();
//			linestate=D4;
//			selectSM(hdc);
//			draw(hdc);
//			drawselect(hdc);
		}
	}
	else
	{
		AfxMessageBox("Not enough Control Point");
	}

}

//DEL bool CBezier::snapok(CVector point)
//DEL {
//DEL 	snap=false;
//DEL 	snapb=false;
//DEL 	pitere=ptend.begin();
//DEL 
//DEL 	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
//DEL 	{
//DEL 	
//DEL 				if ((abs((piterb->x-point.x)<=10)&&(abs(piterb->y-point.y)<=10)))
//DEL 				{
//DEL 					snapvec=*piterb;
//DEL 					snapb=true;
//DEL 				}
//DEL 				if ((abs((pitere->x-point.x)<=10)&&(abs(pitere->y-point.y)<=10)))
//DEL 				{
//DEL 					snapvec=*pitere;
//DEL 					snapb=true;
//DEL 				}
//DEL 				if ((abs((pc.x-point.x)<=20)&&(abs(pc.y-point.y)<=20)))
//DEL 				{
//DEL 					snapvec=pc;
//DEL 					snapb=true;
//DEL 				}
//DEL 				if(snapb)
//DEL 				{
//DEL 				snapv.clear();
//DEL 				snapv.push_back(*piterb);
//DEL 				snapv.push_back(hitpoint);
//DEL 				snapv.push_back(*pitere);
//DEL 				snap=true;
//DEL 				break;
//DEL 				}
//DEL 
//DEL 			if ((pitere+1)<ptend.end())
//DEL 			{
//DEL 			pitere=pitere+1;
//DEL 			} 
//DEL 		}
//DEL 	return snap;
//DEL }

bool CBezier::takeinfo(CVector point)
{

/*	if(PtonSpline(point)!=-1)
	{
		updateinfo();
		computeangle(point,point);
		return true;
	}
	else
	{*/
	return false;
//	}
}

CBezier::CBezier(CFile &file)
{
	handle=0;
	tas=0;
	j=0;
	move=false;fPrevB=false;cancharge=true;

   N=250; //point on the line
   ncp=4;          // number of control points = n+1; for interpolation purpose add +3 to this number
                   // when calculating the knot vector
   deg=3;          // degree of polynomial = t-1

    ncpe=0;
   	cancharge=false;
	name="CBezier";
	lkp=0;
	Pprev=NULL;
	minpara=0;
	maxpara=1;
  
	init();

	openfile(file);
}

void CBezier::deleteobj()
{
	for(int i=0;i<ptbegin.size();i++)
	{
		CP[i]=v0;
	}
	CFigure::deleteobj();
}

//DEL bool CBezier::Undo()
//DEL {
//DEL 	for(int i=0;i<ptbegin.size();i++)
//DEL 	{
//DEL 		CP[i]=v0;
//DEL 	}
//DEL 	return CFigure::Undo();
//DEL }

//DEL bool CBezier::Redo()
//DEL {
//DEL 	for(int i=0;i<ptbegin.size();i++)
//DEL 	{
//DEL 		CP[i]=v0;
//DEL 	}
//DEL 	return CFigure::Redo();
//DEL }
bool CBezier::fsnap(CVector& v,CVector &vl,LPCTSTR snapmode,CDC* hdc)
{
	return CFigure::fsnap(v,vl,snapmode,hdc);
}

bool CBezier::fsnap(CVector &v,CDC* hdc)
{

  CVector vb(ptbegin.front(),v);
	bool hb=false;
	set<CVector,isfarV> zvec;

  if(absc(vb)<=20)
  {
	  v=ptbegin.front();
	  zvec.insert(v);
	  hb=true;
  }
  CVector ve(ptbegin.back(),v);
  if(absc(ve)<=20)
  {
	  v=ptbegin.back();
	  zvec.insert(v);
	  hb=true;
  }
  if(hb) 
  {
	  v=*zvec.begin();
	  return true;
  }
  if(inRegion(v))
  {
	  v=NURBS(deg,CP,ncp,Para[petit],Kn);//selectvec[1];
	  return true;
  }

  return false;
}

void CBezier::surface(CDC *hdc)
{
   vector<CEdge> edge;
   vector<CVertex> vtx;
	mesh.redraw=true;
	if(trans)
		{
			mesh.empty();
			surf=false;
			trans=false;
		}
//   N=20; //point on the line
//   N1=20;
   if(!revol)
   {
//   deg1=1;
 //  ncp1=1;
   }

   if(!surf)
   {
   mesh.RWRender();
   saddvec(ptbegin,ptend);
 //  Mr=new CVector[(N+1)*(N1+1)];

	
	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);

   lk=0;//Kn[deg]*N;
   lh=Kn[ncp+deg]*N;///maxpara);
 
   CVector vc;

   if(surf0)
   {
	   surf0=false;
   }
	   surf=true;
	   addtovec();


   int iter;
	CVector nsu,nsv,ns;

	mesh.empty();
    mesh.resizevertex((N+1)*(N1+1)*(N2+1));
	computesurfacep();
	redraw=false;
   updatecore();

 	//u direction
/*   int i=0;
   for(int jiter=0;jiter<N1;jiter++)
   {
	   for(iter=0;iter<N;iter++)
	   {
		  mesh.addEdge(CEdge(&mesh.Vertex((N+1)*jiter+iter),&mesh.Vertex((N+1)*jiter+iter+1),(N+1)*jiter+iter));
		  mesh.addEdge(CEdge(&mesh.Vertex((N+1)*jiter+iter+1),&mesh.Vertex((N+1)*(jiter+1)+iter+1),(N+1)*jiter+iter+1));
		  mesh.addEdge(CEdge(&mesh.Vertex((N+1)*(jiter+1)+iter+1),&mesh.Vertex((N+1)*(jiter+1)+iter),(N+1)*jiter+iter+2));
		  mesh.addEdge(CEdge(&mesh.Vertex((N+1)*(jiter+1)+iter),&mesh.Vertex((N+1)*jiter+iter),(N+1)*jiter+iter+3));
		  mesh.addEdge(CEdge(&mesh.Vertex((N+1)*jiter+iter),&mesh.Vertex((N+1)*(jiter+1)+iter+1),(N+1)*jiter+iter+4));
		  i+=5;
	   }
   }
   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  mesh.addTri(CTriangle(mesh.Edge(i),mesh.Edge(i+1),-mesh.Edge(i+4)));
		  mesh.addTri(CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4)));
	   }
  */
   int i=0;
   for(int kiter=0;kiter<=N2;kiter=kiter+N2)
   {
   for(int jiter=0;jiter<N1;jiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
		  i+=5;
	 }
   }
   if(N2==0) kiter++;
   }


   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4));
		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();
		  new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4));
	   }
	
	
	//v direction
   i=ed;
   for(int jiter=0;jiter<=N1;jiter=jiter+N1)
   {
   for(int kiter=0;kiter<N2;kiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
		  i+=5;
	   }
   }
   if(N1==0) jiter++;
   }
   int ed1=ed;
   ed=i;
  	   for(i=ed1;i<ed;i+=5)
	   {
		  new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4));
  		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();
		  new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4));
	   }
	//w direction
	i=ed;
   for(iter=0;iter<=N;iter=iter+N)
   {
   for(int kiter=0;kiter<N2;kiter++)
   {
	   for(jiter=0;jiter<N1;jiter++)
	   {
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
		  i+=5;
	   }
   }
   if(N==0) iter++;
   }
   ed1=ed;
   ed=i;
  	   for(i=ed1;i<ed;i+=5)
	   {
		  new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4));
		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();
		  new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4));
	   }
/*
    quadtree.empty();
    quadtree.assign(box);
	int tc=mesh.Tcount();
  	   for(i=0;i<tc;i++)
	   {
		   quadtree.insert(mesh.Triangle(i));
	   }
*/
// mesh.RUpdate();
   }

   if((redraw)&&(!bffd))
   {
/*	CVector nsu,nsv,ns;
   for(int jiter=0;jiter<N1;jiter++)
   {
	   for(int iter=0;iter<N;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
		  ns=nsu*nsv;
		  CVertex vertex(NURBS(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1),Para[iter],Para1[jiter]);
		  vertex.setnormal(ns);
		  mesh.Vertex((N+1)*jiter+iter)=vertex;
	   }

   }*/
	computesurfacep();
//   updateffd();
   redraw=false;

 //  mesh.RUpdate();
   }
/*   CPen pen;
 //  lplb.lbStyle=BS_NULL;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);

	CBrush brush;
	CBrush *ob;
	brush.CreateSolidBrush(bcolor);

	ob=hdc->SelectObject(&brush);
*/

    if(dtri)
	{
	CVector p[5];
	CPoint ppo[5];
	int gh=GetRValue(bcolor);
	int gh1=GetGValue(bcolor);
	int gh2=GetBValue(bcolor);
//	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);
//	M_spec=M_spec/255;
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
//	CCVector M_amb(M_diff);
//	M_amb=M_amb/255;
	
   if((ffd)&&(select==pnt))
	   setFFD(Mr);

	l.S_spec=S_diff;
	l.S_diff=S_diff;
	l.M_spec=M_spec;
	l.M_diff=M_diff;
	l.M_amb=M_diff;
	l.G_amb=G_amb;
	l.lsou=lsou;
	l.view=cam.getcamor();
	l.alpha=alpha;
	l.m_gls=m_gls;

	mesh.updateShadingpara(lit,mytext,pwidth,pheight,&l);
	}
	else
	{
		mesh.displayEdge(hdc);
	}

//	    hdc->SelectObject(ob);
//		brush.DeleteObject();

}

/*void CBezier::surface(CDC *hdc)
{

	if(trans)
		{
			surf=false;
			trans=false;
		}
   N=15; //point on the line
   N1=15;
   if(!revol)
   {
//   deg1=1;
 //  ncp1=1;
   }

   if(!surf)
   {
   saddvec(ptbegin,ptend);
   Mr=new CVector[(N+1)*(N1+1)];

	
	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);

   lk=0;//Kn[deg]*N;
   lh=Kn[ncp+deg]*N;///maxpara);
 
   CVector vc;

   if(surf0)
   {
	   if(!revol) Knot_Univer(ncp1,deg1,Kn1,0,1);

	   if(!tsurf)
	   {
	   for(int ce=0;ce<=ncp;ce++)
	   {
		  C[ce]=CP[ce];
		  vc=C[ce];
	   }
	   
	   for(int c=1;c<=ncp1;c++)
	   {
		   for(int ce=0;ce<=ncp;ce++)
		   {
			  C[c*(ncp+1)+ce]=CP[ce]; 
			  C[c*(ncp+1)+ce].z+=c*20; 
			  vc=C[c*(ncp+1)+ce];
		   }
	   }
	   }
	   surf0=false;
   }
	   surf=true;
	   addtovec();


   int iter;

   for(int jiter=0;jiter<=N1;jiter++)
   {
	   for(iter=0;iter<=N;iter++)
	   {
		  Mr[(N+1)*jiter+iter]=NURBS(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1);
	   }
   }
   



   for(int jiter=0;jiter<=N1;jiter++)
   {
	   for(iter=0;iter<=N;iter++)
	   {
		  Mr1[(N+1)*jiter+iter]=Mr[(N+1)*jiter+iter];
	   }
   }
	CMatrix mathelp;
	mathelp.Transpose(Mr1,N+1,N1+1);
   }

  int s=0;
  CMatrix mathelp;
  vector<int> se;se.resize(N+1);
  CVector *Pt=new CVector[(N+1)*(N1+1)];
  CVector *Pt1=new CVector[(N+1)*(N1+1)];
 
  for(int jiter=0;jiter<=N1;jiter++)
  {
	  s=0;
   for(int iter=lk;iter<=lh;iter++)
	 {
	   Pt[(N+1)*jiter+(iter-lk)]=Mr[(N+1)*jiter+iter];
	   Pt1[(N+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];	
	   s++;
	}
    se[jiter]=s;
  }	
  			if(Ptr!=NULL)
			{
				delete []Ptr;
				Ptr=NULL;
				delete []Pt1r;
				Pt1r=NULL;
			}
			Ptr=new CPoint [(N1+1)*(lh-lk+1)];
			Pt1r=new CPoint [(N1+1)*(lh-lk+1)];



  int s1=0;
  vector<int> se1;se1.resize(N+1);
  mathelp.Transpose(Pt1,(lh-lk)+1,N1+1);

		  for(jiter=0;jiter<=N1;jiter++)
		  {
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Ptr[(lh-lk+1)*jiter+(iter-lk)]=Pt[(N+1)*jiter+(iter-lk)];
			   Pt1r[(lh-lk+1)*jiter+(iter-lk)]=Pt1[(N+1)*jiter+(iter-lk)];	
			}
		  }	
   vector<vector<CVector> > jgrid;
   jgrid.resize((N1+1)*(lh-lk+1));
   vector<CVector> c1;c1.resize(4);
   
   for(jiter=0;jiter<=N1-1;jiter++)
	 {
	   for(int iter=lk;iter<=lh-1;iter++)
		 {
	     c1[0]=Pt[jiter*(lh-lk+1)+iter-lk];
	     c1[1]=Pt[jiter*(lh-lk+1)+iter-lk+1];
	     c1[2]=Pt[(jiter+1)*(lh-lk+1)+iter-lk];
	     c1[3]=Pt[(jiter+1)*(lh-lk+1)+1+iter-lk];
         jgrid[jiter*(lh-lk)+iter-lk]=c1;
		}
	  }	
   


  
   CPen pen;
 //  lplb.lbStyle=BS_NULL;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);

	CBrush brush;
	CBrush *ob;


	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=GetRValue(bcolor);
	int gh1=GetGValue(bcolor);
	int gh2=GetBValue(bcolor);
	CCVector S_spec(0.5,0.5,0.5);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);M_spec=M_spec/255;
	CCVector S_diff(S_spec);
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector G_amb(M_diff);//255,255,255);
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	
	CVector view(0,0,500);
	CVector lsou(0,0,-500);

   for(jiter=0;jiter<=N1-1;jiter++)
	 {
//	   bcolor=ccol;
	   for(int iter=lk;iter<=lh-1;iter++)
		 {

		 

		 p[0]=jgrid[jiter*(lh-lk)+iter-lk][0];
		 p[1]=jgrid[jiter*(lh-lk)+iter-lk][1];
		 p[2]=jgrid[jiter*(lh-lk)+iter-lk][2];
		 p[3]=p[0];
		 p[4]=(p[0]+p[1]+p[2])/3;

		 ppo[0]=p[0];
		 ppo[1]=p[1];
		 ppo[2]=p[2];
		 ppo[3]=p[3];
		 ppo[4]=p[4];

		 CVector po=(view-p[4])/(absc(view-p[4]));
		 CVector l=(lsou-p[4])/(absc(lsou-p[4]));
		 CVector n=(p[1]-p[0])*(p[2]-p[0]);
		 n=n/absc(n);
		 CVector r=n*(2*(n.dot(l)))-l;
		 
		 double b=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),m_gls);	 	
		 CCVector clit1=(S_spec*b)*M_spec;
		 CCVector clit2=(S_diff*max(n.dot(l),0))*M_diff;
		 CCVector clit=clit1+clit2+G_amb*M_amb;
		 

		brush.CreateSolidBrush(clit.toRGB());//bcolor);
	
		ob=hdc->SelectObject(&brush);


		CVector *pp=(CVector*)tri[jiter*(lh-lk)+iter].Vertex();
		ppo[0]=pp[0];
		ppo[1]=pp[1];
		ppo[2]=pp[2];
		ppo[3]=pp[3];

		
		if(!cl)
		 {
         hdc->Polyline(ppo,4);
		 }
		 else
		 {
         hdc->Polygon(ppo,4);
		 }

	    hdc->SelectObject(ob);
		brush.DeleteObject();


		 p[0]=jgrid[jiter*(lh-lk)+iter-lk][1];
		 p[1]=jgrid[jiter*(lh-lk)+iter-lk][3];
		 p[2]=jgrid[jiter*(lh-lk)+iter-lk][2];
		 p[3]=p[0];

		 p[4]=(p[0]+p[1]+p[2])/3;

		 ppo[0]=p[0];
		 ppo[1]=p[1];
		 ppo[2]=p[2];
		 ppo[3]=p[3];
		 ppo[4]=p[4];

		 po=(view-p[4])/(absc(view-p[4]));
		 l=(lsou-p[4])/(absc(lsou-p[4]));
		 n=(p[1]-p[0])*(p[2]-p[0]);
		 n=n/absc(n);
		 r=n*(2*(n.dot(l)))-l;
		 

		 b=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),m_gls);	 	
		 clit1=(S_spec*b)*M_spec;
		 clit2=(S_diff*max(n.dot(l),0))*M_diff;
		 clit=clit1+clit2+G_amb*M_amb;

		 
		brush.CreateSolidBrush(clit.toRGB());//bcolor);
		ob=hdc->SelectObject(&brush);
		
		pp=(CVector*)tri[jiter*(lh-lk)+iter+1].Vertex();
		ppo[0]=pp[0];
		ppo[1]=pp[1];
		ppo[2]=pp[2];
		ppo[3]=pp[3];

		if(!cl)
		 {
         hdc->Polyline(ppo,4);
		 }
		 else
		 {
         hdc->Polygon(ppo,4);
		 }

	    hdc->SelectObject(ob);
		brush.DeleteObject();

	   }
   }
   
   hdc->SelectObject(ob);
   hdc->SelectObject(oldp);
   delete [] Pt;
   delete [] Pt1;
}*/

void CBezier::volume(CDC *hdc)
{
   N=15; //point on the line
   N1=15;
   N2=2;

   if(!vol)
   {
   saddvec(ptbegin,ptend);
   Mr=new CVector[(N+1)*(N1+1)*(N2+1)];

	
	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);
	Para_universp(minpara1,maxpara1,N2,Para2);

   lk=0;//Kn[deg]*N;
   lh=Kn[ncp+deg]*N;///maxpara);
 
   CVector vc;
   C.resize((ncp+1)*(ncp+1)*(ncp2+1));

   if(vol0)
   {
	   Knot_Univer(ncp2,deg2,Kn2,0,1);

	   int nh=(ncp1+1)*(ncp+1);
	   for(int c=1;c<=ncp2;c++)
	   {
		   for(int ce=0;ce<=ncp;ce++)
		   {
			for(int ce1=0;ce1<=ncp1;ce1++)
			{
			  C[c*(ncp+1)*(ncp1+1)+ce*(ncp1+1)+ce1]=C[ce*(ncp1+1)+ce1]; 
			  C[c*(ncp+1)*(ncp1+1)+ce*(ncp1+1)+ce1].z+=c*50; 
			  vc=C[c*(ncp+1)*(ncp1+1)+ce*(ncp1+1)+ce1];
		   }
		   }
	   }
	   vol0=false;
   }
	   vol=true;surf=false;
	   addtovec();


   int iter;

   for(int viter=0;viter<=N2;viter++)
   {
   for(int jiter=0;jiter<=N1;jiter++)
   {
	   for(iter=0;iter<=N;iter++)
	   {
		  Mr[viter*(N+1)*(N1+1)+(N+1)*jiter+iter]=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[viter],Kn,Kn1,Kn2);
	   }
   }
   }
   }

  int s=0;
  CMatrix mathelp;
  vector<int> se;se.resize(N+1);
  CVector *Pt=new CVector[(N+1)*(N1+1)*(N2+1)];
  CVector *Pt1=new CVector[(N+1)*(N1+1)*(N2+1)];
 
  for(int viter=0;viter<=N2;viter++)
  {
  for(int jiter=0;jiter<=N1;jiter++)
  {
	  s=0;
   for(int iter=lk;iter<=lh;iter++)
	 {
	   Pt[viter*(lh-lk+1)*(N1+1)+(lh-lk+1)*jiter+(iter-lk)]=Mr[viter*(N+1)*(N1+1)+(N+1)*jiter+iter];
	   Pt1[viter*(lh-lk+1)*(N1+1)+(lh-lk+1)*jiter+(iter-lk)]=Pt[viter*(lh-lk+1)*(N1+1)+(lh-lk+1)*jiter+(iter-lk)];	
	   s++;
	}
    se[jiter]=s;
  }	
  }
  			if(Ptr!=NULL)
			{
				delete []Ptr;
				Ptr=NULL;
				delete []Pt1r;
				Pt1r=NULL;
			}
			Ptr=new CPoint [(N2+1)*(N1+1)*(lh-lk+1)];
			Pt1r=new CPoint [(N2+1)*(N1+1)*(lh-lk+1)];





/*  int s1=0;
  vector<int> se1;se1.resize(N+1);
  mathelp.Transpose(Pt1,((lh-lk)+1)*(N1+1),N2+1);

		  for(viter=0;viter<=N2;viter++)
		  {
		  for(int jiter=0;jiter<=N1;jiter++)
		  {
		   for(int iter=lk;iter<=lh;iter++)
			 {
			   Ptr[viter*(N1+1)*(lh-lk+1)+(lh-lk+1)*jiter+(iter-lk)]=Pt[viter*(N1+1)*(lh-lk+1)+(lh-lk+1)*jiter+(iter-lk)];
			   Pt1r[viter*(N1+1)*(lh-lk+1)+(lh-lk+1)*jiter+(iter-lk)]=Pt1[viter*(N1+1)*(lh-lk+1)+(lh-lk+1)*jiter+(iter-lk)];	
			}
		  }	
		  }
   vector<vector<CVector> > jgrid;
   jgrid.resize((N2+1)*(N1+1)*(lh-lk+1));
   vector<CVector> c1;c1.resize(4);
   
   for(viter=0;viter<=N2-1;viter++)
	 {

   for(int jiter=0;jiter<=N1-1;jiter++)
	 {
	   for(int iter=lk;iter<=lh-1;iter++)
		 {
	     c1[0]=Pt[viter*(N1+1)*(lh-lk+1)+jiter*(lh-lk+1)+iter-lk];
	     c1[1]=Pt[viter*(N1+1)*(lh-lk+1)+jiter*(lh-lk+1)+iter-lk+1];
	     c1[2]=Pt[viter*(N1+1)*(lh-lk+1)+(jiter+1)*(lh-lk+1)+iter-lk];
	     c1[3]=Pt[viter*(N1+1)*(lh-lk+1)+(jiter+1)*(lh-lk+1)+1+iter-lk];
         jgrid[viter*(N1+1)*(lh-lk+1)+jiter*(lh-lk)+iter-lk]=c1;
		}
	  }	
   

   CPen pen;
//  lplb.lbStyle=BS_NULL;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);

	CBrush brush;
	CBrush *ob;
	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=GetRValue(bcolor);
	int gh1=GetGValue(bcolor);
	int gh2=GetBValue(bcolor);
	CCVector S_spec(0.5,0.5,0.5);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);M_spec=M_spec/255;
	CCVector S_diff(S_spec);
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector G_amb(M_diff);//255,255,255);
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	
	CVector view(0,0,500);
	CVector lsou(0,0,-500);

   for(jiter=0;jiter<=N1-1;jiter++)
	 {
//	   bcolor=ccol;
	   for(int iter=lk;iter<=lh-1;iter++)
		 {

		 

		 p[0]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][0];
		 p[1]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][1];
		 p[2]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][2];
		 p[3]=p[0];
		 p[4]=(p[0]+p[1]+p[2])/3;

		 ppo[0]=p[0];
		 ppo[1]=p[1];
		 ppo[2]=p[2];
		 ppo[3]=p[3];
		 ppo[4]=p[4];

		 CVector po=(view-p[4])/(absc(view-p[4]));
		 CVector l=(lsou-p[4])/(absc(lsou-p[4]));
		 CVector n=(p[1]-p[0])*(p[2]-p[0]);
		 n=n/absc(n);
		 CVector r=n*(2*(n.dot(l)))-l;
		 
		 double b=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),m_gls);	 	
		 CCVector clit1=(S_spec*b)*M_spec;
		 CCVector clit2=(S_diff*max(n.dot(l),0))*M_diff;
		 CCVector clit=clit1+clit2+G_amb*M_amb;
		 

		brush.CreateSolidBrush(clit.toRGB());//bcolor);
		ob=hdc->SelectObject(&brush);
		
		if(!cl)
		 {
         hdc->Polyline(ppo,4);
		 }
		 else
		 {
         hdc->Polygon(ppo,4);
		 }

	    hdc->SelectObject(ob);
		brush.DeleteObject();


		 p[0]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][1];
		 p[1]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][3];
		 p[2]=jgrid[viter*(N1)*(lh-lk)+jiter*(lh-lk)+iter-lk][2];
		 p[3]=p[0];

		 p[4]=(p[0]+p[1]+p[2])/3;

		 ppo[0]=p[0];
		 ppo[1]=p[1];
		 ppo[2]=p[2];
		 ppo[3]=p[3];
		 ppo[4]=p[4];

		 po=(view-p[4])/(absc(view-p[4]));
		 l=(lsou-p[4])/(absc(lsou-p[4]));
		 n=(p[1]-p[0])*(p[2]-p[0]);
		 n=n/absc(n);
		 r=n*(2*(n.dot(l)))-l;
		 

		 b=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),m_gls);	 	
		 clit1=(S_spec*b)*M_spec;
		 clit2=(S_diff*max(n.dot(l),0))*M_diff;
		 clit=clit1+clit2+G_amb*M_amb;

		 
		 
		brush.CreateSolidBrush(clit.toRGB());//bcolor);
		ob=hdc->SelectObject(&brush);
		
		if(!cl)
		 {
         hdc->Polyline(ppo,4);
		 }
		 else
		 {
         hdc->Polygon(ppo,4);
		 }

	    hdc->SelectObject(ob);
		brush.DeleteObject();


	   }
   }


   
   hdc->SelectObject(ob);
   hdc->SelectObject(oldp);
   }
  */ delete [] Pt;
   delete [] Pt1;


}



void CBezier::surface(CBezier *fig1, CBezier *fig2)
{
	ncp1=1;
	int m=max(fig1->Kn.size(),fig2->Kn.size());
	fig1->Kn.resize(m);fig2->Kn.resize(m);
	tsurf=true;
	deg=max(fig1->deg,fig2->deg);
	ncp=max(fig1->ncp,fig2->ncp);

	if(fig1->deg<deg)
	{
		fig1->degel();
	}
	if(fig2->deg<deg)
	{
		fig2->degel();
	}



	/*double* g=new double[fig1->ncp+fig1->deg+2];
	for(int j=0;j<=fig1->ncp+fig1->deg+1;j++)
	{
		g[j]=fig1->Kn[j];
	}
	double* g1=new double[fig2->ncp+fig2->deg+2];
	for(j=0;j<=fig1->ncp+fig2->deg+1;j++)
	{
		g1[j]=fig1->Kn[j];
	}*/

	set_union(fig1->Kn.begin(),fig1->Kn.end(),fig2->Kn.begin(),fig2->Kn.end(),Kn.begin());

	vector<double> Kn2;Kn2.resize(100);
	set_symmetric_difference(fig1->Kn.begin(),fig1->Kn.end(),fig2->Kn.begin(),fig2->Kn.end(),Kn2.begin());
    Kn2.resize(Kn2.size()-count(Kn2.begin(),Kn2.end(),0));

	/*double* g3=new double[50];
	for(j=0;j<=50;j++)
	{
		g3[j]=Kn2[j];
	}*/

	int i=0;
	while(Kn2[i]!=0)
	{
		if(count(fig1->Kn.begin(),fig1->Kn.end(),Kn2[i])<count(fig2->Kn.begin(),fig2->Kn.end(),Kn2[i]))
		{
			Bohms(Kn2[i],fig1->deg,fig1->Kn,fig1->CP,fig1->ncp);
			i--;
		}
		if(count(fig2->Kn.begin(),fig2->Kn.end(),Kn2[i])<count(fig1->Kn.begin(),fig1->Kn.end(),Kn2[i]))
		{
			Bohms(Kn2[i],fig2->deg,fig2->Kn,fig2->CP,fig2->ncp);
			i--;
		}
		i++;
	}

	Kn2.clear();

	
	deg=max(fig1->deg,fig2->deg);
	ncp=max(fig1->ncp,fig2->ncp);
//	Kn.resize(m);
//	CP.resize(ncp);

	
/*	for(j=0;j<=ncp+deg;j++)
	{
		g3[j]=Kn[j];
	}*/


/*	int gb=-1;
	for(int i=0;i<=fig1->ncp;i++)
	{
		double d=fig1->Kn[i+deg];

		int g=find(Kn.begin()+fig1->deg,Kn.begin()+fig1->deg+fig1->ncp,fig1->Kn[i+deg])-(Kn.begin()+deg);
		if(gb==g) g=g+1;
		gb=g;
		CP[g]=fig1->CP[i];
	}
	gb=-1;
	for(i=0;i<=fig2->ncp;i++)
	{
		int g=find(Kn.begin()+fig2->deg,Kn.begin()+fig2->deg+fig2->ncp,fig2->Kn[i+deg])-(Kn.begin()+deg);
		if(gb==g) g=g+1;
		gb=g;
		CP[g+ncp+1]=fig2->CP[i];
	}*/
	for(i=0;i<=fig1->ncp;i++)
	{
		C[i]=fig1->CP[i];
	}
	for(i=0;i<=fig2->ncp;i++)
	{
		C[i+ncp+1]=fig2->CP[i];
	}

	surf=true;
	addtovec();
	surf=false;

/*	delete []g;
	delete []g1;
	delete []g3;*/

}
void CBezier::surface(CBezier *fig1, CFigure *fig2)
{
	CVector vg[2];
	vg[0]=fig2->ptbegin.front();
	vg[1]=fig2->ptend.front();
	
	ncp=fig1->ncp;
	deg=fig1->deg;
	minpara=fig1->minpara;
	maxpara=fig1->maxpara;
	//N=fig1->N;
	for(int i=0;i<=fig1->Kn.size();i++)
	{
		Kn[i]=fig1->Kn[i];
	}
	for(i=0;i<=fig1->Para.size();i++)
	{
		Para[i]=fig1->Para[i];
	}

	deg1=2;
	ncp1=8;
	
		Kn1[0]=0;
		Kn1[1]=0;
		Kn1[2]=0;
		Kn1[3]=(double)1/4;
		Kn1[4]=(double)1/4;
		Kn1[5]=(double)1/2;
		Kn1[6]=(double)1/2;
		Kn1[7]=(double)3/4;
		Kn1[8]=(double)3/4;
		Kn1[9]=1;
		Kn1[10]=1;
		Kn1[11]=1;
	
	C.resize((ncp+1)*(ncp1+1));
	tsurf=true;
	revol=true;



/*	for(i=0;i<=fig1->ncp;i++)
	{
		C[i]=fig1->CP[i];
	}
*/
	CVector d1=vg[1]-vg[0];
	CVector f;
	for(i=0;i<=fig1->ncp;i++)
	{
	CVector pt=fig1->CP[i]-vg[0];
	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;
	//CVector pt1=pd-d;

/*	CVector pd=Ct*(pt.dot(Ct)/(absc(Ct)*absc(Ct)));
    CVector d=pt-pd;
	double dd=absc(Ct);
	CVector ud=Ct/dd;
	CVector d2=ud*d;d2.w=0;
	CVector pt1=pd-d;*/

	pt=fig1->CP[i];
	pd=vg[0]+pd;
	CVector pt1=pd-d;

	C[i*(8+1)]=pt;
	f=pt;
	C[i*(8+1)+1]=pt+d2;
	f=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	f=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	f=pt1+d2;
	C[i*(8+1)+4]=pt1;
	f=pt1;
	C[i*(8+1)+5]=pt1-d2;
	f=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	f=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	f=pt-d2;
	C[i*(8+1)+8]=pt;
	f=pt;

	C[i*(8+1)].w=1;
	C[i*(8+1)+1].w=1/sqrt(2);
	C[i*(8+1)+2].w=1;
	C[i*(8+1)+3].w=1/sqrt(2);
	C[i*(8+1)+4].w=1;
	C[i*(8+1)+5].w=1/sqrt(2);
	C[i*(8+1)+6].w=1;
	C[i*(8+1)+7].w=1/sqrt(2);
	C[i*(8+1)+8].w=1;
	}
	CMatrix mathelp;

	mathelp.Transpose(C,9,fig1->ncp+1);
	for(i=0;i<9;i++)
	{
	  for(int j=0;j<=fig1->ncp;j++)
	  {
		  f=C[i*(fig1->ncp+1)+j];
	  }
	}

	surf=true;
	addtovec();
	surf=false;

}



void CBezier::copy(const CFigure *fig)
{
	CBezier *bg=(CBezier*) fig;

	ncp=bg->ncp;
	ncp1=bg->ncp1;
	ncp2=bg->ncp2;

	deg=bg->deg;
	deg1=bg->deg1;
	deg2=bg->deg2;

	maxpara=bg->maxpara;
	minpara=bg->minpara;
	maxpara1=bg->maxpara1;
	minpara1=bg->minpara1;

	N=bg->N;
	N1=bg->N1;
	N2=bg->N2;
	lk=bg->lk;
	lh=bg->lh;

	surf=bg->surf;
	surf0=bg->surf0;
	tsurf=bg->tsurf;
	revol=bg->revol;
	
	prevstart=bg->prevstart;

	ffd=bg->ffd;
	bffd=bg->bffd;

	int s=bg->ContP.size();
	ContP.resize(s);
	for(int i=0; i<s;i++)
	{
		ContP[i]=bg->ContP[i];
	}
	s=bg->vMr.size();
	vMr.resize(s);
	for(i=0; i<s;i++)
	{
		vMr[i]=bg->vMr[i];
	}

	CP.resize(bg->ncp+1);
	for(i=0; i<=bg->ncp;i++)
	{
		CP[i]=bg->CP[i];
	}
	C.resize((ncp+1)*(ncp1+1)*(ncp2+1));
	for(i=0; i<=bg->ncp;i++)
	{
		for(int j=0;j<=bg->ncp1;j++)
		{
			for(int k=0;k<=bg->ncp2;k++)
			{
			 C[i*(bg->ncp1+1)*(bg->ncp2+1)+j*(bg->ncp2+1)+k]=bg->C[i*(bg->ncp1+1)*(bg->ncp2+1)+j*(bg->ncp2+1)+k];
			}
		}
	}
	Kn.resize(bg->Kn.size());
	for(i=0; i<bg->Kn.size();i++)
	{
		Kn[i]=bg->Kn[i];
	}
	Kn1.resize(bg->Kn1.size());
	for(i=0; i<bg->Kn1.size();i++)
	{
		Kn1[i]=bg->Kn1[i];
	}
	Kn2.resize(bg->Kn2.size());
	for(i=0; i<bg->Kn2.size();i++)
	{
		Kn2[i]=bg->Kn2[i];
	}
	Para.resize(bg->Para.size());
	for(i=0; i<bg->Para.size();i++)
	{
		Para[i]=bg->Para[i];
	}
	Para1.resize(bg->Para1.size());
	for(i=0; i<bg->Para1.size();i++)
	{
		Para1[i]=bg->Para1[i];
	}
	Para2.resize(bg->Para2.size());
	for(i=0; i<bg->Para2.size();i++)
	{
		Para2[i]=bg->Para2[i];
	}

	if(bg->surf)
	{
		mesh.copy(&bg->mesh);
	}
	else if(bg->Mr != 0)
	{
	Mr=new CVector[(N+1)];
	for(i=0; i<=N;i++)
	{
		Mr[i]=bg->Mr[i];
	}

	}
	if(surf)
	{
		mesh.RWRender();
	}

	CFigure::copy(fig);
    
//		box=fig->box;
	
	if(surf)
	{
		redraw=false;
		trans=false;
	}



	if(bg->ffd)
	{
		ffd=false;
		setFFDon(bg->FFDbox->type);
	}

}

void CBezier::BSdegelv(CBezier *fig, int d)
{

	int n;
	int d2=fig->deg;
	int n2=fig->ncp;


	vector<double> K;K.resize(50);
	vector<double> Kc;Kc.resize(50);

	for(int i=0;i<=fig->ncp+fig->deg;i++)
	{
		K[i]=fig->Kn[i];
	}

	for(i=fig->deg;i<=n2;i++)
	{
		n=count(K.begin(),K.begin()+d2+n2+1,K[i]);

		for(int j=0;j<fig->deg-n;j++)
		{
			Bohms(K[i],fig->deg,fig->Kn,fig->CP,fig->ncp);
		}

	}
	ncpe=0;
	for(i=0;i<ncp;i++)
	{
		int h1=find(fig->Kn.begin()+deg,fig->Kn.end(),K[deg+i])-fig->Kn.begin();
		int h2=find(fig->Kn.begin()+deg,fig->Kn.end(),K[deg+i+1])-fig->Kn.begin();
		Bdegel(deg,h1,h2,fig->CP);
	}

	for(i=0;i<=fig->ncp+fig->deg;i++)
	{
		Kc[i]=fig->Kn[i];
	}

	fig->deg++;
	for(i=0;i<=ncp;i++)
	{
	vector<double>::iterator g=Kc.begin()+(find(Kc.begin(),Kc.end(),K[deg+i])-Kc.begin());
	Kc.erase(g,g+deg-count(Kc.begin(),Kc.end(),K[deg+i]));
	}
		          
	Oslo(fig->deg,fig->Kn,Kc,P,ncpe,find(Kc.begin(),Kc.end(),1)+deg-1-Kc.begin()-fig->deg-1);
	
	for(i=0;i<=ncpe;i++)
	{
		CP[i]=P[i];
	}
	fig->ncp=ncpe;

/*	for(int iter=0;iter<=ncp+deg+1;iter++)
	{
		if(Kn[iter]==Para[petit])
		{
			s++;
		}
	}
	for(int g=0;g<deg-s;g++)
	{
	Bohms(Para[petit], deg,Kn,CP,ncp);	
	}*/
}


void CBezier::Bdegel(int d, int start, int end, vector<CVector>& Po)
{
	CVector re,v0(0,0,0);int u;
	for(int i=0;i<d+1;i++)
	{
		u=ncpe+i;
		if(start+i<1) continue;
		P[ncpe+i]=Po[start+i-1]*((double)i/(double)(d+1))+Po[start+i]*(1-(double)i/(double)(d+1));
		re=P[ncpe+i];
	}
	P[ncpe]=Po[start];
	re=P[ncpe];
	P[ncpe+d+1]=Po[start+d];
	re=P[ncpe+d+1];
	ncpe+=d+1;

}

void CBezier::degel()
{
	int nl[10];
	int d2=deg;
	int n2=ncp;

 P.resize(50);
	vector<double> K;K.resize(50);
	vector<double> Kc;Kc.resize(50);
	vector<double> Kc1;Kc1.resize(50);



	for(int i=0;i<=ncp+deg+1;i++)
	{
		K[i]=Kn[i];
	}
	double k;
	for(i=0;i<=ncp+deg+1;i++)
	{
		k=Kn[i];
	}
	
	for(i=deg;i<=deg+n2;i++)
	{
		nl[i-deg]=count(K.begin(),K.begin()+d2+n2+1,K[i]);

		for(int j=0;j<deg-nl[i-deg];j++)
		{
			Bohms(K[i],deg,Kn,CP,ncp);
		}

	}

	ncpe=0;
	for(i=0;i<ncp-1;i=i+deg)
	{
		Bdegel(deg,i,i+deg,CP);
	}

	Kc[0]=Kn[0];
	for(i=1;i<=ncp+deg+1;i++)
	{
		Kc[i]=Kn[i-1];
	}
	Kc[i]=Kc[i-1];
	Kc[i+1]=Kc[i-1];

	deg++;
	for(i=0;i<=ncpe+deg+1;i++)
	{
		Kc1[i]=Kc[i];
	}
	
	for(i=0;i<=n2;i++)
	{
     int q=nl[i];
	 if(q>0)
	 {
	 for(int j=d2;j>q;j--)
	 {
	Kc.erase(find(Kc.begin(),Kc.end(),K[d2+i]));
	 }
	 }
	}
	int jk=0;
	for(i=0;i<=n2;i++)
	{
	if(count(Kc1.begin(),Kc1.end(),K[d2+i])==d2)
	{
		jk++;
		Kc1.insert(Kc1.begin+find(Kc1.begin(),Kc1.end(),K[d2+i]),K[d2+i]);
	}
	}
		          
	for(i=0;i<=ncp+deg+1;i++)
	{
		k=Kc[i];
	}

	for(i=0;i<=ncpe+deg+1;i++)
	{
		k=Kc1[i];
	}
	int ncpe1=ncpe-(jk*(deg-1));
//	Oslo(deg,Kc1,Kc,P,ncpe,ncpe1);

	ncp=ncpe;
	Kn.resize(ncp+deg+2);

	for(i=0;i<=ncp+deg+1;i++)
	{
		Kn[i]=Kc1[i];
	}

	CP.resize(ncpe+1);
	ncp=ncpe+1;
	CVector ts;
	for(i=0;i<=ncpe+1;i++)
	{
		CP[i]=P[i];
		ts=P[i];
	}
//	addtovec();
}

/*
void CBezier::degel()
{
	int nl[10];
	int d2=deg;
	int n2=ncp;

	P.resize(50);
	vector<double> K;K.resize(50);
	vector<double> Kc;Kc.resize(50);
	vector<double> Kc1;Kc1.resize(50);



	for(int i=0;i<=ncp+deg+1;i++)
	{
		K[i]=Kn[i];
	}
	double k;
	for(i=0;i<=ncp+deg+1;i++)
	{
		k=Kn[i];
	}
	
	for(i=deg;i<=deg+n2;i++)
	{
		nl[i-deg]=count(K.begin(),K.begin()+d2+n2+1,K[i]);

		for(int j=0;j<deg-nl[i-deg];j++)
		{
			Bohms(K[i],deg,Kn,CP,ncp);
		}

	}

	ncpe=0;
	for(i=0;i<ncp;i=i+deg)
	{
		Bdegel(deg,i,i+deg,CP);
	}

	Kc[0]=Kn[0];
	for(i=1;i<=ncp+deg+1;i++)
	{
		Kc[i]=Kn[i-1];
	}
	Kc[i]=Kc[i-1];
	Kc[i+1]=Kc[i-1];

	deg++;
	for(i=0;i<=ncpe+deg+1;i++)
	{
		Kc1[i]=Kc[i];
	}
	
	for(i=0;i<=n2;i++)
	{
     int q=nl[i];
	 if(q>0)
	 {
	 for(int j=d2;j>q;j--)
	 {
	Kc.erase(find(Kc.begin(),Kc.end(),K[d2+i]));
	 }
	 }
	}
	int jk=0;
	for(i=0;i<=n2;i++)
	{
	if(count(Kc1.begin(),Kc1.end(),K[d2+i])==d2)
	{
		jk++;
		Kc1.insert(Kc1.begin+find(Kc1.begin(),Kc1.end(),K[d2+i]),K[d2+i]);
	}
	}
		          
	for(i=0;i<=ncp+deg+1;i++)
	{
		k=Kc[i];
	}

	for(i=0;i<=ncpe+deg+1;i++)
	{
		k=Kc1[i];
	}
	int ncpe1=ncpe-(jk*(deg-1));
//	Oslo(deg,Kc1,Kc,P,ncpe,ncpe1);

	ncp=ncpe;
	Kn.resize(ncp+deg+2);

	for(i=0;i<=ncp+deg+1;i++)
	{
		Kn[i]=Kc1[i];
	}

	CP.resize(ncpe+1);
	CVector ts;
	for(i=0;i<=ncpe+1;i++)
	{
		CP[i]=P[i];
		ts=P[i];
	}
	addtovec();
}

*/

void CBezier::degel(int &ncp0,int &deg0,vector<double> V,vector<CVector>CP0,vector<CVector>&P0)
{
	int nl[10];
	int d2=deg0;
	int n2=ncp0;


	vector<double> K;K.resize(50);
	vector<double> Kc;Kc.resize(50);
	vector<double> Kc1;Kc1.resize(50);



	for(int i=0;i<=ncp0+deg0+1;i++)
	{
		K[i]=V[i];
	}
	double k;
	for(i=0;i<=ncp0+deg0+1;i++)
	{
		k=V[i];
	}
	
	for(i=deg0;i<=deg0+n2;i++)
	{
		nl[i-deg0]=count(K.begin(),K.begin()+d2+n2+1,K[i]);

		for(int j=0;j<deg0-nl[i-deg0];j++)
		{
			Bohms(K[i],deg0,V,CP0,ncp0);
		}

	}

	ncpe=0;
	for(i=1;i<ncp0;i=i+deg0)
	{
		Bdegel(deg0,i,i+deg0,CP0);
	}

	Kc[0]=V[0];
	for(i=1;i<=ncp0+deg0+1;i++)
	{
		Kc[i]=V[i-1];
	}
	Kc[i]=Kc[i-1];
	Kc[i+1]=Kc[i-1];

	deg0++;
	for(i=0;i<=ncpe+deg0+1;i++)
	{
		Kc1[i]=Kc[i];
	}
	
	for(i=0;i<=n2;i++)
	{
     int q=nl[i];
	 if(q>0)
	 {
	 for(int j=d2;j>q;j--)
	 {
	Kc.erase(find(Kc.begin(),Kc.end(),K[d2+i]));
	 }
	 }
	}
	int jk=0;
	for(i=0;i<=n2;i++)
	{
	if(count(Kc1.begin(),Kc1.end(),K[d2+i])==d2)
	{
		jk++;
		Kc1.insert(Kc1.begin+find(Kc1.begin(),Kc1.end(),K[d2+i]),K[d2+i]);
	}
	}
		          
	for(i=0;i<=ncp0+deg0+1;i++)
	{
		k=Kc[i];
	}

	for(i=0;i<=ncpe+deg0+1;i++)
	{
		k=Kc1[i];
	}
	int ncpe1=ncpe-(jk*(deg0-1));
//	Oslo(deg,Kc1,Kc,P,ncpe,ncpe1);

	ncp0=ncpe;
	V.resize(ncp0+deg0+2);

	for(i=0;i<=ncp0+deg0+1;i++)
	{
		V[i]=Kc1[i];
	}

	CP0.resize(ncpe+1);
	CVector ts;
	for(i=0;i<=ncpe+1;i++)
	{
		P0[i]=CP0[i];
		ts=P0[i];
	}
	//addtovec();
}


void CBezier::SUdegel(int du, int dv)
{



	vector< vector<CVector> > qd(ncp+ncp1+3);
	vector< vector<CVector> > rd(ncp+ncp1+3);


	CVector *pt;
	pt=new CVector[C.size()];

	vector<CVector>pt1(ncp+1);
//	Para_universp(0,1,m+3,Para);
	std::copy(C.begin(),C.end(),pt);

    int m1=0;
	for(int dg=deg;dg<du;dg++)
	{
	for(int d=0;d<=ncp1;d++)
	{
		m1=ncp;
//		q_d[d]=new CVector[n+1];
		qd[d].resize(ncp+5);

		std::copy(&pt[(ncp+1)*d],&pt[(ncp+1)*d]+ncp+1,pt1.begin());

		degel(m1,dg,Kn,pt1,qd[d]);
	}
	ncp=m1;
	}

	CMatrix mathelp;
	if(m1==0) 
	{
	for(int d=0;d<=ncp1;d++)
	{
		m1=ncp;
//		q_d[d]=new CVector[n+1];
		qd[d].resize(ncp+5);

		std::copy(&pt[(ncp+1)*d],&pt[(ncp+1)*d]+ncp+1,qd[d].begin());

	}
	}
	mathelp.Transpose(qd,ncp1+1,ncp+1);

	pt1.resize(ncp1+3);
	int n1;
	for(dg=deg1;dg<dv;dg++)
	{
	for(int d=0;d<=ncp;d++)
	{
		n1=ncp1;
//		q_d[d]=new CVector[n+1];
		rd[d].resize(ncp1+5);

		std::copy(qd[d].begin(),qd[d].begin()+ncp1+1,pt1.begin());

		degel(n1,dg,Kn1,pt1,rd[d]);
	}
	ncp1=n1;
	}
	deg1=dv;
	deg=du;

	mathelp.Transpose(rd,ncp+1,ncp1+1);

	for (int i=0;i<=ncp1+1;i++)
	{
		for (int j=0;j<=ncp+1;j++)
		{
			C[(ncp+3)*i+j]=*(rd[i].begin()+j);
		}
	}


	delete [] pt;


}




void CBezier::loftsurface(vector<CBezier*>& fg, int l,int h)
{
	if(h==-1)
		ncp1=l-1;
	else
		ncp1=h;
	tsurf=true;
	deg=fg[0]->deg;
	ncp=fg[0]->ncp;
	deg1=3;
	for(int i=0;i<=ncp1;i++)
	{
		deg=deg>=fg[i]->deg?deg:fg[i]->deg;
	}
	
	for(i=0;i<=ncp1;i++)
	{
		while(deg>fg[i]->deg)
		{
			fg[i]->degel();
		}
	}
	vector<double> Kn2(50);
	vector<double> Kn3(50);
	vector<double> Kn4(50);
    

	for(i=0;i<=ncp1;i++)
	{
		fg[i]->Kn.resize(fg[i]->ncp+fg[i]->deg+2);
	}

	std::copy(fg[0]->Kn.begin(),fg[0]->Kn.end(),Kn3.begin());

	for(i=0;i<=ncp1-1;i++)
	{
	
//	std::sort(fg[i+1]->Kn.begin(),fg[i+1]->Kn.end());
	insert_iterator<vector<double> > bi(Kn,Kn.begin());
	insert_iterator<vector<double> > bi3(Kn3,Kn3.begin());
	set_union(fg[i+1]->Kn.begin(),fg[i+1]->Kn.end(),Kn3.begin(),Kn3.end(),bi);
	std::copy(Kn.begin(),Kn.end(),bi3);
	Kn.resize(50);
	Kn3.resize(50);
//	bi2=Kn2.begin();
	}
	
	Kn3.assign(50,0);
	Kn2.assign(50,0);
	bool kspeed=false;
	vector<double>::iterator iter;
	for(i=0;i<=ncp1;i++)
	{
	Kn4.assign(50,1);
	for(int j=0;j<=ncp1;j++)
	{
	iter=set_symmetric_difference(fg[i]->Kn.begin(),fg[i]->Kn.end(),fg[j]->Kn.begin(),fg[j]->Kn.end(),Kn3.begin());
	if(Kn3.begin()!=iter)
	{
//	std::sort(Kn3.begin(),Kn3.end());
	insert_iterator<vector<double> > bi2(Kn2,Kn2.begin());
	insert_iterator<vector<double> > bi4(Kn4,Kn4.begin());
	set_union(Kn3.begin(),iter,Kn4.begin(),Kn4.end(),bi2);
	std::copy(Kn2.begin(),Kn2.end(),bi4);
//	std::sort(Kn4.begin(),Kn4.end());
	Kn2.resize(50);
	Kn4.resize(50);
	kspeed=true;
	}
	}
	}
//	Kn3.assign(50,);
//	std::set_difference(Kn4.begin(),Kn4.end(),Kn3.begin(),Kn3.end(),Kn2.begin());

	for(i=0;i<=ncp1;i++)
	{
		fg[i]->Kn.resize(50);
	}
	i=0;
	while((Kn2[i]!=1)&&(kspeed))//&&(Kn2[i]!=0))
	{
		if(Kn2[i]!=0)
		{
		if(std::count(Kn2.begin(),Kn2.end(),Kn2[i])>deg)
		{
			Kn2.erase(Kn2.begin()+i);
			i--;
		}
		}
		i++;
	}
	i=0;
	bool b=false;
	for(i=0;(!((Kn3[i]==0)&&(b))&&(kspeed));i++)
	{
		if(Kn3[i]!=0)
		{
		if(std::count(Kn3.begin(),Kn3.end(),Kn3[i])>deg)
		{
			Kn3.erase(Kn3.begin()+i);
			i--;
		}
		b=true;
		}
//		i++;
	}
	i=0;
	for(int j=0;j<=ncp1;j++)
	{
	while((Kn2[i]!=1)&&(kspeed))//&&(Kn2[i]!=0))
	{
		if(std::count(fg[j]->Kn.begin(),fg[j]->Kn.end(),Kn2[i])<std::count(Kn.begin(),Kn.end(),Kn2[i]))
		{
			Bohms(Kn2[i],deg,fg[j]->Kn,fg[j]->CP,fg[j]->ncp);
			i--;
		}
		i++;
	}
	i=0;
	}

	Kn2.clear();

	for(i=0;i<=ncp1;i++)
	{
		ncp=ncp>=fg[i]->ncp?ncp:fg[i]->ncp;
	}

	Knot_Univer(ncp1+2,deg1,Kn1,0,1);
	N=fg[0]->ncp+1;//N;
	CP.resize(l*(ncp+1));
	for(j=0;j<l;j++)
	{
	for(i=0;i<=ncp;i++)
	{
		CP[j*(ncp+1)+i]=fg[j]->CP[i];
	}
	}
	C.resize((l+2)*(ncp+1));
	vector<CVector> bbp(l);
	ContP.resize(l+2);
	CBezier be;
	for(i=0;i<=ncp;i++)
	{
		for(j=0;j<=ncp1;j++)
		{
			bbp[j]=CP[j*(ncp+1)+i];
		}
		INT_curve(bbp,ncp1,deg1,Kn1,Kn1,ContP);
/*		be.ncp=ncp1;
		be.deg=deg1;
		be.Kn=Kn1;
		be.CP=bbp;
		be.degel();
		be.degel();
		for(j=0;j<=be.ncp;j++)
		{
			if(j*(ncp+1)+i>=C.size())
				C.resize(j*(ncp+1)+i+1);

			C[j*(ncp+1)+i]=be.CP[j];
		}*/
		for(j=0;j<=ncp;j++)
		{
			C[j*(ncp+1)+i]=ContP[j];
		}
	}
//	Kn1=be.Kn;

	ncp1+=2;//be.ncp;
	N1=ncp1+1;
//	deg1=be.deg;


	Kn2.resize(50);
	Kn3.resize(50);
	Kn4.resize(50);
	Kn4.clear();

}

void CBezier::revolsurface(vector<CBezier*> fg, int l,bool simple)
{
	CVector vg[2];
	vg[0]=*fg[0]->ptbegin.begin();
	vg[1]=*(fg[0]->ptbegin.begin()+1);


	ncp=fg[1]->ncp;
	deg=fg[1]->deg;
	minpara=fg[1]->minpara;
	maxpara=fg[1]->maxpara;
	N=ncp;
	N1=10;
	Para_universp(0,1,ncp1,Para1);
    Knot_Univer(ncp2,deg1,Kn2,0,1);
	Kn.resize(fg[1]->Kn.size());
	for(int i=0;i<fg[1]->Kn.size();i++)
	{
		Kn[i]=fg[1]->Kn[i];
	}
	Para.resize(fg[1]->Para.size());
	for(i=0;i<fg[1]->Para.size();i++)
	{
		Para[i]=fg[1]->Para[i];
	}
	deg1=2;
	ncp1=8;
	
		Kn1[0]=0;
		Kn1[1]=0;
		Kn1[2]=0;
		Kn1[3]=(double)1/4;
		Kn1[4]=(double)1/4;
		Kn1[5]=(double)1/2;
		Kn1[6]=(double)1/2;
		Kn1[7]=(double)3/4;
		Kn1[8]=(double)3/4;
		Kn1[9]=1;
		Kn1[10]=1;
		Kn1[11]=1;
	
	C.resize((ncp+1)*(ncp1+1));
	tsurf=true;
	revol=true;



//	CVector d1=fg[0]->CP[j]+vrz;
	CVector f;
	CVector vry,vrz1;vry.getcoory();
	CVector d1=vry;
	if(!simple)
	{
	for(i=0;i<=fg[1]->ncp;i++)
	{
	d1=fg[0]->CP[i+1]-fg[0]->CP[i];
	d1.w=0;

	CVector pt=fg[1]->CP[i]-fg[0]->CP[i];

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;
/*	CVector pt=fg[1]->CP[i]-vg[0];

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;
	
	


/*	CVector pd=Ct*(pt.dot(Ct)/(absc(Ct)*absc(Ct)));
    CVector d=pt-pd;
	double dd=absc(Ct);
	CVector ud=Ct/dd;
	CVector d2=ud*d;d2.w=0;
	CVector pt1=pd-d;*/

	pt=fg[1]->CP[i];
	pd=fg[0]->CP[i]+pd;
	CVector pt1=pd-d;

	C[i*(8+1)]=pt;
	C[i*(8+1)+1]=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	C[i*(8+1)+4]=pt1;
	C[i*(8+1)+5]=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	C[i*(8+1)+8]=pt;

	C[i*(8+1)].w=1;
	C[i*(8+1)+1].w=1/sqrt(2);
	C[i*(8+1)+2].w=1;
	C[i*(8+1)+3].w=1/sqrt(2);
	C[i*(8+1)+4].w=1;
	C[i*(8+1)+5].w=1/sqrt(2);
	C[i*(8+1)+6].w=1;
	C[i*(8+1)+7].w=1/sqrt(2);
	C[i*(8+1)+8].w=1;
	}
	}
	else
	{
/*	CVector vry,vrz;vry.getcoory();
	CVector d1=vry;

	CVector pt=fg[1]->CP[0]-vg[0];

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;

	vg0=vg[0].x*vrx+vg[0].y*vry+vg[0].z*vrz;*/
	d1=vg[1]-vg[0];
	d1.w=0;
	for(i=0;i<=fg[1]->ncp;i++)
	{

	CVector pt=fg[1]->CP[i]-fg[0]->CP[0];

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;
/*	CVector pt=fg[1]->CP[0]-vg[0];
	pt=fg[1]->CP[0].x*vrx+fg[1]->CP[0].y*vry+fg[1]->CP[0].z*vrz;
*/

/*	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;

/*	CVector pd=Ct*(pt.dot(Ct)/(absc(Ct)*absc(Ct)));
    CVector d=pt-pd;
	double dd=absc(Ct);
	CVector ud=Ct/dd;
	CVector d2=ud*d;d2.w=0;
	CVector pt1=pd-d;*/

	pt=fg[1]->CP[i];
	pd=fg[0]->CP[0]+pd;
	CVector pt1=pd-d;

	C[i*(8+1)]=pt;
	C[i*(8+1)+1]=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	C[i*(8+1)+4]=pt1;
	C[i*(8+1)+5]=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	C[i*(8+1)+8]=pt;

	C[i*(8+1)].w=1;
	C[i*(8+1)+1].w=1/sqrt(2);
	C[i*(8+1)+2].w=1;
	C[i*(8+1)+3].w=1/sqrt(2);
	C[i*(8+1)+4].w=1;
	C[i*(8+1)+5].w=1/sqrt(2);
	C[i*(8+1)+6].w=1;
	C[i*(8+1)+7].w=1/sqrt(2);
	C[i*(8+1)+8].w=1;
	}



	}
	CMatrix mathelp;

	mathelp.Transpose(C,9,fg[1]->ncp+1);

/*	int lo;
	CVector v1,v2,v3,pv3,pk,pv2;
	for(j=1;j<=ncp2;j++)
	{
		for(i=0;i<=ncp1;i++)
		{
			for(int k=0;k<=ncp;k++)
			{
			
				if((k!=0)&&(k!=ncp))
				{

				v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1];
				v2=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
				v1=v1*pv2;
				v2=v2*pv2;
				v2=(v2/absc(v2))*50;
				v1=(v1/absc(v1))*50;
				v3=v2-v1;
			if(pv3.dot(v3)<0) 
			{
		//		v3=-v3;
			}
//			pv3=v3;
				}
			if((k==0)||(k==ncp))
			{
			if(i==0)
			{
				pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			}
			v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(i!=ncp1) pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(k==ncp) v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
			v3=v1*pv2;
			v3=(v3/absc(v3))*50;
			pv3=v3;
			}
			
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]+v3;
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w;
			}
		}
	}*/

}

void CBezier::extrussurface(vector<CBezier*> fg, int l)
{
	ncp1=l-1;
	tsurf=true;
	if(l==3)
	{
		loftsurface(fg,2);
		
		CVector vrz,vrx,vry;vrz.getcoorz();vrx.getcoorx();vry.getcoory();

		N1=fg[2]->ncp;
//		N=fg[0]->ncp;
		deg1=fg[2]->deg;
		ncp1=fg[2]->ncp;
//		std::copy(fg[0]->Kn.begin(),fg[0]->Kn.end(),Kn.begin());
		std::copy(fg[2]->Kn.begin(),fg[2]->Kn.end(),Kn1.begin());

//		EXTRUSC=absc(CVector(fg[2]->CP[0],fg[2]->CP[fg[2]->ncp]));
/*		for(int i=0;i<=ncp;i++)
		{
		C[i]=fg[0]->CP[i];
		}
*/		vector<CVector> C2=C;
		for(j=0;j<=ncp1;j++)
		{
//			CVector v1(fg[2]->CP[j-1],fg[2]->CP[j]);
//			v1=vry*v1.y;
			for(int i=0;i<=ncp;i++)
			{
			C2[j*(ncp+1)+i]=C[0*(ncp+1)+i]*(1-j/ncp1)+C[1*(ncp+1)+i]*(j/ncp1);
			C2[j*(ncp+1)+i].w=C[0*(ncp+1)+i].w;
			}
		}
		C=C2;
		for(j=1;j<ncp1;j++)
		{
			CVector v1(C[j*(ncp+1)],fg[2]->CP[j]);
			v1=vrx*v1.x+vry*v1.y+vrz*v1.z;
			for(int i=0;i<=ncp;i++)
			{
			C[j*(ncp+1)+i]=C[j*(ncp+1)+i]+v1;
			C[j*(ncp+1)+i].w=C[j*(ncp+1)+i].w;
			}
		}



	}else
	if(l==2)
	{
	CVector vrz,vrx,vry;vrz.getcoorz();vrx.getcoorx();vry.getcoory();
	deg=fg[0]->deg;
	ncp=fg[0]->ncp;

	N1=fg[1]->ncp*2;
	N=fg[0]->ncp;
//	deg1=(fg[1]->deg>1)?fg[1]->deg:2;
	ncp1=fg[1]->ncp;
	std::copy(fg[0]->Kn.begin(),fg[0]->Kn.end(),Kn.begin());
//	std::copy(fg[1]->Kn.begin(),fg[1]->Kn.end(),Kn1.begin());
	Knot_Univer(ncp1,deg1,Kn1,0,1);

	CAABB bol;
	for(int i=0;i<=ncp;i++)
	{
	C[i]=fg[0]->CP[i];
	bol.add(C[i]);
	}


	CTVector vt;
	vector<CVector> Cv(C.size());
	CVector ov=bol.center();
	vt.pushTransform();

	for(i=0;i<=ncp;i++)
	{
//	Cv[i].assignInv(fg[0]->CP[i]);
	Cv[i]=fg[0]->CP[i];
	}
	CVector v2;
	for(j=1;j<=ncp1;j++)
	{
		CVector v1(fg[1]->CP[0],fg[1]->CP[j]),vm;
		v2=fg[1]->CP[j]-fg[1]->CP[j-1];
		if(j!=ncp1) 
		{
			vm=fg[1]->CP[j]-fg[1]->CP[j+1];
			v2=v2-vm;
		}
		
		vt.pushUnit();
		vt.Translate(-ov);
		float gv=1/cos(argu(v2));
		if(j==ncp1) gv=1;
		vt.TRotate(argu(v2));
		vt.Scale(gv,gv,gv);
		vt.Translate(v1);
		vt.Translate(ov);
		vt.endT();
		v2=ov;
		v2.assign(ov);
//		v1.assignInv(v1);
		for(int i=0;i<=ncp;i++)
		{
		C[j*(ncp+1)+i].assign(Cv[i],true);
//		C[j*(ncp+1)+i]=C[j*(ncp+1)+i]+v1;
//		C[j*(ncp+1)+i].w=Cv[i].w;

		}
	}

	vt.popTransform();
	vector<CBezier*> b(ncp1+1);
	for(i=0;i<=ncp1;i++)
	{

		b[i]=new CBezier;
		b[i]->ncp=ncp;
		b[i]->Kn=Kn;
		b[i]->deg=deg;
		for(int j=0;j<=ncp;j++)
		{
		b[i]->CP[j]=C[i*(ncp+1)+j];
		}
	}
	int pncp1=ncp1;
	loftsurface(b,ncp1+1);
	for(i=0;i<=pncp1;i++)
	{

		delete b[i];
	}

/*	int l,lo;
	CVector v1,v2,v3,pv3,pk,pv2;
	for(j=1;j<=ncp2;j++)
	{
		for(i=0;i<=ncp1;i++)
		{
			for(int k=0;k<=ncp;k++)
			{
			
				if((k!=0)&&(k!=ncp))
				{

				v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1];
				v2=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
				v1=v1*pv2;
				v2=v2*pv2;
				v2=(v2/absc(v2))*50;
				v1=(v1/absc(v1))*50;
				v3=v2-v1;
			if(pv3.dot(v3)<0) 
			{
		//		v3=-v3;
			}
//			pv3=v3;
				}
			if((k==0)||(k==ncp))
			{
			if(i==0)
			{
				pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			}
			v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(i!=ncp1) pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(k==ncp) v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
			v3=v1*pv2;
			v3=(v3/absc(v3))*50;
			pv3=v3;
			}
			
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]+v3;
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w;
			}
		}
	}*/

	}
	else if(l==1)
	{

	CVector vrz;vrz.getcoorz();
	deg=fg[0]->deg;
	ncp=fg[0]->ncp;
	deg1=1;
	ncp1=1;
	N1=ncp1;
	N=fg[0]->ncp;
	Kn1[0]=0;
	Kn1[1]=0;
	Kn1[2]=1;
	Kn1[3]=1;
//	EXTRUSC=absc(CVector(fg[1]->CP[0],fg[1]->CP[fg[1]->ncp]));
	std::copy(fg[0]->Kn.begin(),fg[0]->Kn.end(),Kn.begin());
	for(j=0;j<=ncp1;j++)
	{
		for(int i=0;i<=ncp;i++)
		{
		C[j*(ncp+1)+i]=fg[0]->CP[i]+vrz*EXTRUSC*j;
		}
	}

	}
}

void CBezier::surface(CString type,vector<CBezier*> fg, int l,float vthick)
{
	if(type=="loft")
	{
		loftsurface(fg,l);
//		Knot_Univer(ncp1,deg1,Kn1,0,1);
	//	SUdegel(3,3);
	}
	else
	if(type=="simplerevol")
	{
		loftsurface(fg,l);
		revolsurface(fg,l,true);
	}
	else
	if((type=="extrus")||(type=="extrus2")||(type=="gextrusion"))
	{
	  extrussurface(fg,l);
	}
	else
	if(type=="coon")
	{
	CBezier f1,f2,tr;
	vector<CBezier*> fg1(2),fg2(2);
	for(int h=0;h<2;h++)
	{
		fg1[h]=new CBezier;
		fg2[h]=new CBezier;
	}
	fg1[0]->copy(fg[0]);fg1[1]->copy(fg[1]);
	fg2[0]->copy(fg[2]);fg2[1]->copy(fg[3]);

	vector<CVector> fg3(50),fs;
	fg3[0]=fg[0]->CP[0];fg3[1]=fg[0]->CP[fg[0]->ncp];
	fg3[2]=fg[1]->CP[0];fg3[3]=fg[1]->CP[fg[1]->ncp];

	f1.loftsurface(fg1,2);
	f2.loftsurface(fg2,2);

	vector< vector<CVector> > qd(2);
	vector< vector<CVector> > rd(2);

/*	for(int d=0;d<=1;d++)
	{
		std::copy(f1.C[2*f1.ncp].begin(),f1.C[f1.ncp],qd[d].begin());
		std::copy(f2.C[0],f2.C[f2.ncp],rd[d].begin());
	}
	CMatrix mathelp;
	mathelp.Transpose(qd,2,f1.ncp);
	mathelp.Transpose(rd,2,f2.ncp);*/


//	Para_universp(minpara,maxpara,N,Para);
	Knot_Univer(3,f1.deg,Kn,0,1);
	Knot_Univer(1,f1.deg1,Kn1,0,1);


	fs=tr.INT_surface(fg3,1,1,f1.deg,f2.deg1,Kn,Kn1,Para,Para);
	int n1=(f1.C).size();
	int n2=(f2.C).size();
	fs.resize(n1);

	ncp1=l-1;
//	tsurf=true;
	deg=f1.deg;
	ncp=f1.ncp;
	deg1=f1.deg;
	ncp1=f1.ncp;

	for(int i=0;i<=ncp1;i++)
	{
		for(int j=0;j<=ncp;j++)
		{
		C[((ncp+1)*i)+j]=/*f2.C[((ncp+1)*i)+j]+f1.C[((ncp+1)*i)+j]-*/fs[((ncp+1)*i)+j];
		}
	}


	tsurf=true;
//	surf0=false;
	std::copy(f1.Kn.begin(),f1.Kn.end(),Kn.begin());
	std::copy(f2.Kn.begin(),f2.Kn.end(),Kn1.begin());
	
	for(h=0;h<2;h++)
	{
		delete fg1[h];
		delete fg2[h];
	}

	}
	if(vthick!=0)
	{
	ncp2=1;
	deg2=1;
	Para_universp(0,1,ncp2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);
	N2=1;
	C.resize((ncp+1)*(ncp1+1)*(ncp2+1));

	int lo;
	CVector v1,v2,v3,pv3,pk,pv2;
	for(j=1;j<=ncp2;j++)
	{
		for(int i=0;i<=ncp1;i++)
		{
			for(int k=0;k<=ncp;k++)
			{
			
				if((k!=0)&&(k!=ncp))
				{

				v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1];
				v2=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
				v1=v1*pv2;
				v2=v2*pv2;
				v2=(v2/absc(v2))*vthick;
				v1=(v1/absc(v1))*vthick;
				v3=v2-v1;
			if(pv3.dot(v3)<0) 
			{
		//		v3=-v3;
			}
//			pv3=v3;
				}
			if((k==0)||(k==ncp))
			{
			if(i==0)
			{
				pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			}
			v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k+1]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(i!=ncp1) pv2=C[(j-1)*(ncp1+1)*(ncp+1)+(i+1)*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k];
			if(k==ncp) v1=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]-C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k-1];
			v3=v1*pv2;
			v3=(v3/absc(v3))*vthick;
			pv3=v3;
			}
			
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k]+v3;
			C[j*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w=C[(j-1)*(ncp1+1)*(ncp+1)+i*(ncp+1)+k].w;
			}
		}
	}
	}
	else
	{
		ncp2=0;
		deg2=0;
		N2=0;
	}

	surf=true;
	addtovec();
	surf=false;

}


bool CBezier::PtinNode(CVector point,int multi)
{
	if(ffd)
	{
	 if(FFDbox->PtinNode(point,multi))
	 {
		 select=pnt;
		 return true;
	 }
	}

 bool okj=false;
 bool sol=false;

if(!surf)
 {
	 addvec(ptbegin,ptend);
	 for(int i=0;i<=ncp;i++)
	   {
		   if ((pointinRegion(point,CP[i]))&&(!multiselect))
		   {
			   click=true;
			   select=pnt;
			  /* if(CP[i]==ptbegin[1])
			   {
				   select=st;
				   petit=i;
			   }*/
			   okj=true;
			   return true;
		   }
	   }
 }
 else
 if(surf)
 {
	 saddvec(ptbegin,ptend);
	 for(int i=0;i<=ncp;i++)
	   {
		 for(int j=0;j<=ncp;j++)
		 {
		   if ((pointinRegion(point,C[(ncp+1)*i+j]))&&(!multiselect))
		   {
			   click=true;
			   select=pnt;
			  /* if(CP[i]==ptbegin[1])
			   {
				   select=st;
				   petit=i;
			   }*/
			   okj=true;
			   return true;
		   }
		 }
	   }

 }

}
/*

void CBezier::ScanPolygon(CDC *hdc, COLORREF rgba,CVector *K,int s,CImagex *texture)
{
	BYTE* text=(BYTE*)texture->GetDIBits();
    int pheight=texture->GetHeight();
	int pwidth=texture->GetWidth();
	col* mytext=new col[pheight*pwidth];
	auto_ptr <col> m(mytext);
	int i = 0;
		int x, y,q;
	int r,g,b;
		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
			}
			i+=pwidth%4;
		}

	int width;
	int height;

	double u,vv;
	CVector ev=ptend.back();
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	double ytop=(vi->y>ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=(vi->x<ev.x)?vi->x:ev.x;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=(vi->y<ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=(vi->x>ev.x)?vi->x:ev.x;

	CPoint tl(CVector(xleft,ytop,0));
	CPoint lb(CVector(xright,ybot,0));
	hdc->LPtoDP(&tl);
	hdc->LPtoDP(&lb);
	xleft=tl.x;
	ytop=tl.y;
	width=lb.x-tl.x;
	height=tl.y-lb.y;


	vector <Edges> v;
	vector<Edges> vl;
//	list<int> ;
	for(int it=0,ite=1;ite!=s;it++,ite++)
	{
		CPoint p1(K[it]);
		hdc->LPtoDP(&p1);
		u=(double)(p1.x-xleft)/width;
		vv=(double)(ytop-p1.y)/height;
		vertex v1(p1,u,vv);

		CPoint p2(K[ite]);
		hdc->LPtoDP(&p2);
		u=(double)(p2.x-xleft)/width;
		vv=(double)(ytop-p2.y)/height;
		vertex v2(p2,u,vv);

		CRect r(p1,p2);
		r.NormalizeRect();
		if(r.top!=r.bottom)
			v.push_back(Edges(p1,p2,r));
	}
	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	ytop=v.begin()->r.top;
	double vt=0;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.top;

	ybottom=gi->r.bottom;
	int vb=1;
	int prevyt=0;

	double dv=(double)1/(ybottom-ytop);
	
	int o=hdc->SetMapMode(MM_TEXT);


	for (y=ytop;y<=ybottom;y++) {

	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y>=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),*i);
				if(il!=vl.end()) vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	vl.push_back(e);//	insert/remove edges from “active edge list”
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatex(ip,y,width,xleft);//update x coordinate of every active edge
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate

	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double du=(uright-uleft)/(xright-xleft);
	for (int x=xleft+1;x<=xright-1;x++)
	{
		int yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		uleft+=du;
	}
	}
	vt+=dv;
	}
	hdc->SetMapMode(o);
}
*/
void CBezier::ScanPolygon(CDC *hdc, COLORREF rgba,CVector *K,int s,CImagex *texture)
{
/*	int pheight;
	int pwidth;
	int i = 0;
	int x, y,q;
	int r,g,b;
	col* mytext=NULL;

	if(texture!=NULL)
	{

	BYTE* text=(BYTE*)texture->GetDIBits();
    pheight=texture->GetHeight();
	pwidth=texture->GetWidth();
	mytext=new col[pheight*pwidth];

		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
			}
			i+=pwidth%4;
		}
	}

	int width;
	int height;

	vector <Edges> v;
	vector<Edges> vl;
	double u,vv;
	CVector ev=ptend.back();
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	double ytop=(vi->y>ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=(vi->x<ev.x)?vi->x:ev.x;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=(vi->y<ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=(vi->x>ev.x)?vi->x:ev.x;

	CPoint tl(CVector(xleft,ytop,0));
	CPoint lb(CVector(xright,ybot,0));
	hdc->LPtoDP(&tl);
	hdc->LPtoDP(&lb);
	xleft=tl.x;
	ytop=tl.y;
	width=lb.x-tl.x;
	height=tl.y-lb.y;

	CPoint blend(blend_p);
	hdc->LPtoDP(&blend);
	blend.x=xleft;
	blend.y=ytop;
	CPoint nblend(blend_plane);
	hdc->LPtoDP(&nblend);
	nblend.x=width;
	nblend.y=0;
	blend_radius=width;
//	CPlane pl(CVector(blend.x,blend.y,0),CVector(nblend.x,nblend.y,0));
	float initalpha=0;
	float endalpha=1;

	for(int it=0,ite=1;ite!=s;it++,ite++)
	{
		CPoint p1(K[it]);
		hdc->LPtoDP(&p1);
		if(mode_texture==wrap)
		{
		u=(double)(p1.x-xleft)/pwidth;
		vv=(double)(ytop-p1.y)/pheight;
		}
		else
		{
		u=(double)(p1.x-xleft)/width;
		vv=(double)(ytop-p1.y)/height;
		}
	
		vertex v1(p1,u,vv);

		CPoint p2(K[ite]);
		hdc->LPtoDP(&p2);
		u=(double)(p2.x-xleft)/pwidth;
		vv=(double)(ytop-p2.y)/pheight;


		vertex v2(p2,u,vv);

		CRect r(p1,p2);
		r.NormalizeRect();
		if(r.top!=r.bottom)
		{
			v.push_back(Edges(v1,v2,r));
		}
	}
   if(v.size()!=0)
   {


	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	ytop=v.begin()->r.top;
	double vt=0;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.bottom;
	double vtop=v.begin()->gettop().y;
	int vb=1;
	int prevyt=0;

	double dv=(double)1/(ybottom-ytop);
	if(mode_texture==wrap)
	{
		dv=ybottom-ytop;
	}
	
	int o=hdc->SetMapMode(MM_TEXT);
	int br=	GetRValue(rgba);
	int bg=	GetGValue(rgba);
	int bb=	GetBValue(rgba);

	for (y=ytop;y<=ybottom;y++) {

	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y>=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),*i);
				if(il!=vl.end()) vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	insert/remove edges from “active edge list”
	if(mode_texture!=wrap)
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatex(ip,y,width,xleft);//update x coordinate of every active edge
	}
	else
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatexw(ip,y,pwidth,xleft);//update x coordinate of every active edge
	}
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate
	int yt;
	
	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double du=(uright-uleft)/(xright-xleft);
//	double alpha=1;
	for (int x=xleft;x<=xright;x++)
	{
//		int yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		if(tex_vert_mode==replace)
		{
		 r=mytext[yt].r;
		 g=mytext[yt].g;
		 b=mytext[yt].b;
		//hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		}else
		if(tex_vert_mode==decal)
		{
		//alpha=computealpha(x,y,&pl,initalpha,endalpha);
		 r=(1-alpha)*mytext[yt].r+alpha*br;
		 g=(1-alpha)*mytext[yt].g+alpha*bg;
		 b=(1-alpha)*mytext[yt].b+alpha*bb;
		}else
		if(tex_vert_mode==multiply)
		{
		 r=(mytext[yt].r/255*br/255)*255;
		 g=(mytext[yt].g/255*bg/255)*255;
		 b=(mytext[yt].b/255*bb/255)*255;
		}
		else
		if(tex_vert_mode==image_texture)
		{
		if(mode_texture==wrap)
		{
		u=uleft;
		vv=vt;
		vv=(double)(vt)/pheight;

		u=__min(u-floor(u),1);
		u=__max(u,0);
		vv=__min(vv-floor(vv),1);
		vv=__max(vv,0);
		}

		yt=floor(pheight*vv)*(pwidth)+floor(pwidth*u);
		COLORREF back=hdc->GetPixel(x,y);
		
		br=	GetRValue(back);
		bg=	GetGValue(back);
		bb=	GetBValue(back);
		
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;

		}
		else 
		if(tex_vert_mode==backcolor)
		{
		COLORREF back=hdc->GetPixel(x,y);
		
		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*br;
		g=(1-alpha)*bg1+alpha*bg;
		b=(1-alpha)*bb1+alpha*bb;
		}
		hdc->SetPixel(x,y,RGB(r,g,b));

//		hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		uleft+=du;
	}
	}
	if(mode_texture!=wrap)
	{
	vt+=dv;
	}else
	{
		vt++;
	}
	}
	hdc->SetMapMode(o);
	}
	if(mytext!=NULL)
		delete []mytext;
*/
	int pheight;
	int pwidth;
	int i = 0;
	int x, y,q;
	int r,g,b;
	col* mytext=NULL;

	if(texture!=NULL)
	{

	BYTE* text=(BYTE*)texture->GetDIBits();
    pheight=texture->GetHeight();
	pwidth=texture->GetWidth();
	mytext=new col[pheight*pwidth];

		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
			}
			i+=pwidth%4;
		}
	}

	int width=0;
	int height=0;

	vector <Edges> v;
	vector<Edges> vl;
	double u,vv;
	ptbegin=mesh.getVectors();
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	double ytop=vi->y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=vi->x;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=vi->y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=vi->x;

	CVector tl(xleft,ytop,0);
	CVector lb(xright,ybot,0);
//	hdc->LPtoDP(&tl);
//	hdc->LPtoDP(&lb);
	xleft=tl.x;
	ytop=tl.y;
	float xd;
	float yd;
	width=lb.x-tl.x;
	height=tl.y-lb.y;
	width=(width>0)?width:-width;
	height=(height>0)?height:-height;

	if(texture!=NULL)
	{
	xd=(float)width/pwidth;
	yd=(float)height/pheight;
	}
	unsigned ph,pw;
	CPoint blend(blend_p);
	hdc->LPtoDP(&blend);
	blend.x=xleft;
	blend.y=ytop;
	CPoint nblend(blend_plane);
	hdc->LPtoDP(&nblend);
	nblend.x=width;
	nblend.y=0;
	blend_radius=width;
	CPlane pl(CVector(blend.x,blend.y,0),CVector(nblend.x,nblend.y,0));
	float initalpha=0;
	float endalpha=1;
//	blend_mode=linearb;
//	tex_vert_mode=decal;

//This part is commented to allow experimenetation with the CMesh class

/*	for(vector<CVector>::iterator it=ptbegin.begin(),ite=ptend.begin();it!=ptbegin.end();it++,ite++)
	{
		CPoint p1(*it);
		hdc->LPtoDP(&p1);
		if(mode_texture==wrap)
		{
		u=(double)(p1.x-xleft)/pwidth;
		vv=(double)(ytop-p1.y)/pheight;
		}
		else
		{
		u=(double)(p1.x-xleft)/width;
		vv=(double)(ytop-p1.y)/height;
		}
	
/*		if(mode_texture==wrap)
		{
		u=__min(u-floor(u),1);
		u=__max(u,0);
		vv=__min(vv-floor(vv),1);
		vv=__max(vv,0);
		}
*//*		vertex v1(p1,u,vv);

		CPoint p2(*ite);
		hdc->LPtoDP(&p2);
//		u=(double)(p2.x-xleft)/pwidth;
//		vv=(double)(ytop-p2.y)/pheight;
		if(mode_texture==wrap)
		{
		u=(double)(p2.x-xleft)/pwidth;
		vv=(double)(ytop-p2.y)/pheight;
		}
		else
		{
		u=(double)(p2.x-xleft)/width;
		vv=(double)(ytop-p2.y)/height;
		}


/*		if(mode_texture==wrap)
		{
		u=__min(u-floor(u),1);
		u=__max(u,0);
		vv=__min(vv-floor(vv),1);
		vv=__max(vv,0);
		}
*//*		vertex v2(p2,u,vv);

		CRect r(p1,p2);
		r.NormalizeRect();
		if(r.top!=r.bottom)
		{
			v.push_back(Edges(v1,v2,r));
		}
	}
*/
	vector<CEdge*> vel=mesh.getEdgeList();
	for(vector<CEdge*>::iterator it=vel.begin();it!=vel.end();it++)
	{
		CVertex* vx=(*it)->Start();
		CVector t=*vx;
		CPoint p1(t);
		hdc->LPtoDP(&p1);
		vertex v1(p1,vx->un,vx->vn);

		vx=(*it)->End();
		t=*vx;
		CPoint p2(t);
		hdc->LPtoDP(&p2);
		vertex v2(p2,vx->un,vx->vn);

		CRect r(p1,p2);
		if(r.top<r.bottom)
		{
			int xc=r.top;
			r.top=r.bottom;
			r.bottom=xc;
		}
		if(r.top!=r.bottom)
		{
			v.push_back(Edges(v1,v2,r));

		}

	}

if(v.size()!=0)
   {


	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	ytop=v.begin()->r.top;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.bottom;
	double u_bottom=gi->getbottom().x;
	double v_bottom=gi->getbottom().y;

	double v_top=v.begin()->gettop().y;
	double u_top=v.begin()->gettop().x;


	
	int o=hdc->SetMapMode(MM_TEXT);
	int br=	GetRValue(rgba);
	int bg=	GetGValue(rgba);
	int bb=	GetBValue(rgba);

	for (y=ytop;y>=ybottom;y--) {

	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y<=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),i);
				if(il!=vl.end()) 
					vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	insert/remove edges from “active edge list”
	if(mode_texture!=wrap)
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatex(ip,y,width,xleft);//update x coordinate of every active edge
	}
	else
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatexw(ip,y,pwidth,xleft);//update x coordinate of every active edge
	}
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate
	int yt;
	
	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	double vleft=ik->v_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double vright=(ik+1)->v_current;
	double du=(uright-uleft)/(xright-xleft);
	double dv=(vright-vleft)/(xright-xleft);
	double dx=(double)1/(xright-xleft);

//	double alpha=1;
	for (double x=xleft;x<=xright;x++)
	{
//		int yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		if(tex_vert_mode==replace)
		{
		 r=mytext[yt].r;
		 g=mytext[yt].g;
		 b=mytext[yt].b;
		//hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		}else
		if(tex_vert_mode==decal)
		{
		//alpha=computealpha(x,y,&pl,initalpha,endalpha);
		 r=(1-alpha)*mytext[yt].r+alpha*br;
		 g=(1-alpha)*mytext[yt].g+alpha*bg;
		 b=(1-alpha)*mytext[yt].b+alpha*bb;
		}else
		if(tex_vert_mode==multiply)
		{
		 r=(mytext[yt].r/255*br/255)*255;
		 g=(mytext[yt].g/255*bg/255)*255;
		 b=(mytext[yt].b/255*bb/255)*255;
		}
		else
		if(tex_vert_mode==image_texture)
		{
		float u_wrap;
		float v_wrap;
		if(mode_texture==wrap)
		{
		float g=xd*uleft;
		unsigned t=g;
		u_wrap=g-t;

		g=yd*vleft;
		t=g;
		v_wrap=g-t;

		ph=(pheight-1)*v_wrap;
		pw=(pwidth-1)*u_wrap;
		yt=ph*pwidth+pw;
//		yt=floor((pheight-1)*v_wrap)*pwidth+floor((pwidth-1)*u_wrap);
		}

		if(tex_vert_mode!=wrap)
		{
		ph=(pheight-1)*vleft;
		pw=(pwidth-1)*uleft;
		yt=ph*pwidth+pw;
//		yt=floor((pheight-1)*vleft)*pwidth+floor((pwidth-1)*uleft);
		}
		COLORREF back=hdc->GetPixel(x,y);
		
		br=	GetRValue(back);
		bg=	GetGValue(back);
		bb=	GetBValue(back);
		
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;

		}
		else 
		if(tex_vert_mode==backcolor)
		{
		COLORREF back=hdc->GetPixel(x,y);
		
		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*br;
		g=(1-alpha)*bg1+alpha*bg;
		b=(1-alpha)*bb1+alpha*bb;
		}
		hdc->SetPixelV(x,y,RGB(r,g,b));

//		hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		uleft+=du;
		vleft+=dv;
	}
	}
	if(mode_texture!=wrap)
	{
//	vleft+=dyv;
//	uleft+=dyu;
	}else
	{
//		vleft++;
	}
	}
	hdc->SetMapMode(o);
	}
	if(mytext!=NULL)
		delete []mytext;

}	

CVector * CBezier::getVector()
{
   addvec(ptbegin,ptend);
   CVector* M= (CVector*)calloc(N+1,sizeof(CVector));
	
	Para_universp(minpara,maxpara,N,Para);

   int lk=Kn[deg]*N;
   int lh=Kn[ncp+deg]*N;///maxpara);
   for(int iter=0;iter<=N;iter++)
   {
	  M[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }

 return M;
}

void CBezier::postTranslate(CVector v)
{
//	if(surf)
	{
		if((ffd)&&(select==pnt))
			FFDbox->postTranslate(v);
	   CMesh::ivertex iv=mesh.vbegin();
	   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
	   {
//		   (iv)->second->v.assign((iv)->second->v,true);
	   }
	for (piterb=ContP.begin();piterb<ContP.end();piterb++)
	{
//		piterb->assign(*piterb,true);;
	}
	}
/*	else
		{
		   for(int jiter=0;jiter<N;jiter++)
		   {
			   vMr[jiter].assign(vMr[jiter],true);
		   }
		}
*/
}

void CBezier::buildspline(vector<CBezier*>* fg)
{
	ncp1=0;
	deg1=0;
	ncp2=0;
	deg2=0;
	int s=fg->size();
	deg=1;
	ncp=s;
	N=s;
//	 Para_universp(0,1,s,Para);

	 multiset<double> Ks;
	 vector<double> d1(ncp+deg+2);
	 vector<double>::iterator diter;
//   Knot_Univer(ncp,deg,Kn,0,1);
	 int l=0;
	 double m=1,k=0;
	 Kn[0]=0;
//	 Kn[1]=0;
	 int n=s+1;
	 for(int j=1;j<=n;j=j+1)//deg+ncp+2;j++)
	 {
	 	 m=(double)k/s;
		 Kn[j]=m;
/*		 if((m!=1)&&(m!=0))
		 {
			 Kn[j+1]=m;j++;n++;
		 }*/
//		 Kn[j+1]=m;
//		 Kn[j+2]=m;
		 k++;
	 }
	 Kn[j]=1;
//	 Kn[j+1]=1;

	 vector<CVector>::iterator iter;
	 for(j=0;j<s;j++)
	 {
		for(int k=0;k<=1;k++)
		{
			CP[j*1+k]=(*fg)[j]->CP[k];
		}
	 }
//	 N=100;
//	 ncp-=1;//CP.size()-1;

}

CBezier::CBezier(CFigure *fig)
{
init(); 
	
vector<CBezier*> fg;
vector<CBezier*>::iterator it;

 vector<CVector>::iterator iter,itere;
  for(iter=fig->ptbegin.begin(),itere=fig->ptend.begin();iter!=fig->ptbegin.end();iter++,itere++)
  {
		CBezier *b=new CBezier(*iter,*itere);
		fg.push_back(b);
  }
	buildspline(&fg);
   getCharge();
  for(it=fg.begin();it!=fg.end();it++)
  {
		delete *it;//fg.push_back(b);
//		delete b;
  }
}

CBezier::CBezier(CVector begin, CVector end,int d)
{
	init();
	deg=d;           // degree of polynomial = t-1
    vector<CVector> pts;//[100];
	pts.push_back(begin);
	pts.push_back(end);

	
	vector<CVector>::iterator rsult;

	ncp=pts.size()-1;	
	int i=0;
//	 Para_universp(0,1,ncp+deg,Para);
     Knot_Univer(ncp,deg,Kn,0,1);
//	 Grev_knot1(ncp+deg-1,deg,Para);

	 CP[0]=begin;
//	 CP[1]=(begin+end)/2;
	 CP[1]=end;
	if(deg==3)
	{
 	INT_curve(pts,ncp,deg,Kn,Kn,CP);
 	ncp+=(deg-1);
	}
	N=2;
   getCharge();

}

void CBezier::init()
{
	revol=false;
	surf=false;surf0=true;trans=false;vol0=true;vol=false;
	handle=0;
	tas=0;
	j=0;
	tsurf=false;
	move=false;fPrevB=false;cancharge=true;
	redraw=true;

   N=150; //point on the line
   ncp=4;          // number of control points = n+1; for interpolation purpose add +3 to this number
                   // when calculating the knot vector
   deg=3;          // degree of polynomial = t-1
   Kn.resize(50);
   Kn1.resize(50);
   Kn2.resize(50);
 
   ncpe=0;
   CP.resize(50);C.resize(50*50);
   Para.resize(N+1);
   Para1.resize(N+1);
   Para2.resize(N+1);
   	cancharge=false;
	name="CBezier";
	lkp=0;
	Pprev=NULL;
	Ptr=NULL;
	Pt1r=NULL;
	minpara=0;
	maxpara=1;
	minpara1=0;
	maxpara1=1;
	strans=false;

	fPrevB=false;
	Mr=NULL;
	N1=0;
	N2=0;
    deg1=0;
    ncp1=0;
    deg2=0;
    ncp2=0;
	FFDbox=NULL;
	ffd=false;
	bffd=false;
	if(mytext!=NULL)
		delete []mytext;
	mytext = NULL;
//	mytext=NULL;;
}

void CBezier::setFFDon(CString option)
{
	if((Mr==NULL)&&(!surf)) return;
	if(FFDbox!=NULL) 
		delete FFDbox;

		FFDbox=new CFFD(this,option);
		bffd=true;
		ptbegin.clear();
		ptend.clear();
			if(mesh.Vcount()>0)
			{
		   for(CMesh::ivertex iv=mesh.vbegin();iv!=mesh.vend();iv++)
		   {
				  ptbegin.push_back((iv)->second->v);
				  ptend.push_back((iv)->second->n);
		   }
		   ptend.push_back((mesh.vbegin())->second->v);
			}


	ffd=true;
	updateffd();
	redraw=true;
/*	if(!ffd)
	{
		FFDbox->setselectmode(null);
	}
*/
}

void CBezier::setFFD(CVector *M)
{
	if(FFDbox==NULL) return;
   	if(box.intersectAABB(FFDbox->box))
	{
		vector<CVector> Cb=FFDbox->getPoint();
		vector<double> Knu=FFDbox->getKnu();
		vector<double> Knv=FFDbox->getKnv();
		vector<double> Knw=FFDbox->getKnw();
		if(!surf)
		{
		   for(int iter=0;iter<=N;iter++)
		   {
			  CVector k=FFDbox->Para[iter];
			  if((k.x>=0)&&(k.x<=1)&&(k.y>=0)&&(k.y<=1))
			  {
				  M[iter]=NURBS(1,1,Cb,1,1,k.x,k.y,Knu,Knv);
			  }
		  }
		}
		else
		{
		   CMesh::ivertex iv=mesh.vbegin();int i=0;
           CVector nsu;
		   CVector nsv;
		   CVector ns;
			i=0;
		   for(iv=mesh.vbegin(),pitere=ptbegin.begin();iv!=mesh.vend();iv++,pitere++)
		   {
			  CVector k=FFDbox->Para[i];//FFDbox->box.getParam(*iv);//Mr[i]);
			  if((k.x>=0)&&(k.x<=1)&&(k.y>=0)&&(k.y<=1)&&(k.z>=0)&&(k.z<=1))
			  {
				  (iv)->second->updatev(NURBS(FFDbox->degu,FFDbox->degv,FFDbox->degw,Cb,FFDbox->ncpu,FFDbox->ncpv,FFDbox->ncpw,k.x,k.y,k.z,Knu,Knv,Knw));
				  *pitere=(iv)->second->v;
	//			  nsu=Sur_deriv(1,1,Cb,1,1,k.x,k.y,Knu,Knv,Para,true,false);
	//			  nsv=Sur_deriv(1,1,Cb,1,1,k.x,k.y,Knu,Knv,Para,false,true);
//				  ns=nsu*nsv;
//				  iv->setnormal(ns);
			  }
			  i++;
		   }
		 //  mesh.RUpdate();

		}
	}
}



void CBezier::updateffd()
{
	if(FFDbox==NULL) return;
		FFDbox->init();
		if(!surf)
		{
		   for(int iter=0;iter<=N;iter++)
		   {
			  if(FFDbox->box.containpts(Mr[iter]))
			  {
					  CVector k=FFDbox->box.getParam(Mr[iter]);
					  FFDbox->Para[iter]=k;	
			  }
			  else
			  {
				  CVector k(-1,-1,-1);
				  FFDbox->Para[iter]=k;
			  }
		  }
		}
		else
		{
//			ptbegin=mesh.vertexlist;
//			ptend=mesh.vertexlist;
		   CMesh::ivertex iv=mesh.vbegin();int i=0;
		   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
		   {
			  if(FFDbox->box.containpts(*iv->second))//Mr[i]))
			  {
					  CVector k=FFDbox->box.getParam(*iv->second);
					  FFDbox->Para[i]=k;//FFDbox->box.getParam(*iv);//Mr[i]);
			  }
			  else
			  {
				  CVector k(-1,-1,-1);
				  FFDbox->Para[i]=k;
			  }
			  i++;
		   }

		}

}



void CBezier::computesurfacep()
{

  CVector nsu;
  CVector nsv;
  CVector ns;
  int i=0;
//u direction  
  for(int kiter=0;kiter<=N2;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=N1;jiter++)
	 {
	   for(int iter=0;iter<=N;iter++)
	   {

  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
  ns=nsu*nsv;
  ns=ns/absc(ns);
  nsu=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[kiter],Kn,Kn1,Kn2);
	box.add(nsu);
  CVertex* vertex= new CVertex(nsu,Para[iter],Para1[jiter],N*jiter+iter);
  vertex->setnormal(ns);
	 mesh.addVertex(kiter*(N1+1)*(N+1)+(N+1)*jiter+iter,vertex);
	   }
	   }
 }
}


bool CBezier::isSurface()
{
return surf;
}

void CBezier::Render(CDC *hdc)
{

	render.displayTri(hdc);
}

void CBezier::UpdateTexture(CDC* hdc)
{
	CFigure::UpdateTexture(hdc);
	return;
  //  mesh.updateTri();
	if(tex_vert_mode==backcolor)
	{
		if(mytext!=NULL)
			delete []mytext;
		mytext = NULL;
//		mytext.clear();
		return;
	}

	if(mytext!=NULL) 
	{
		delete mytext;
		mytext=NULL;
	}
	if(texture_file!="")
	{
	CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
	BYTE* text=(BYTE*)texture.GetDIBits();
    pheight=texture.GetHeight();
	pwidth=texture.GetWidth();

	if(mytext!=NULL)
		delete []mytext;
	mytext = NULL;

	mytext =new col[pheight*pwidth];
	int i = 0;
		int x, y,q;
	int r,g,b;
		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
				if(texture.GetBitCount()==32)
				{
				mytext[q].a=text[i++];
				}
			}
			i+=pwidth%4;
		}
	}

}


void CBezier::updatecore()
{
//	if(surf)
	{
	ptbegin.clear();
	ptend.clear();
	for(map<int,CVertex*>::iterator i=mesh.vbegin();i!=mesh.vend();i++)
	{
		ptbegin.push_back((i)->second->v);
	}
	for (piterb=ContP.begin();piterb<ContP.end();piterb++)
	{
		ptbegin.push_back((*piterb));
	}
//	if(ptbegin.size()!=0) ptend.push_back(ptbegin[0]);
	}
		CFigure::updatecore();
}
void CBezier::plane(CVector p1,CVector p2)
{
	CAABB v;
	v.add(p1);
	v.add(p2);

	C[0]=v.corner(0);
	C[1]=v.corner(1);
	C[2]=v.corner(2);
	C[3]=v.corner(3);

	ncp=1;
	ncp1=1;
	ncp2=0;

	deg=1;
	deg1=1;
	deg2=0;

	minpara=0;
	maxpara=1;
	N=1;
	N1=1;
	N2=0;
	Para_universp(0,1,N2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,N,Para);
    Knot_Univer(ncp,deg,Kn,0,1);

	Para_universp(0,1,N1,Para1);
    Knot_Univer(ncp1,deg1,Kn1,0,1);
}
void CBezier::sphere(CVector Ct,float radius)
{
	
	float tetha=pi/2;
	float u=pi/5;
	CVector v,nv;
	CVector vrx,vry,vrz;
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	for(int i=0;i<=5;i++)
	{
	v=Ct+(vry*radius*cos(tetha))+(vrx*radius*sin(tetha));
	CP[i]=v;
	tetha-=u;
	}

	ncp=5;
	ncp1=8;
	ncp2=0;

	deg=1;
	deg1=2;
	deg2=0;

	minpara=0;
	maxpara=1;
	N=ncp;
	N1=ncp1;
	N2=0;
	Para_universp(0,1,ncp2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,ncp,Para);
    Knot_Univer(ncp,deg,Kn,0,1);


		Kn1[0]=0;
		Kn1[1]=0;
		Kn1[2]=0;
		Kn1[3]=(double)1/4;
		Kn1[4]=(double)1/4;
		Kn1[5]=(double)1/2;
		Kn1[6]=(double)1/2;
		Kn1[7]=(double)3/4;
		Kn1[8]=(double)3/4;
		Kn1[9]=1;
		Kn1[10]=1;
		Kn1[11]=1;


	CVector d1=vrx;
	d1.w=0;
	for(i=0;i<=5;i++)
	{

	CVector pt=CP[i]-Ct;

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;


	pt=CP[i];
	pd=Ct+pd;
	CVector pt1=pd-d;

	C[i*(8+1)]=pt;
	C[i*(8+1)+1]=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	C[i*(8+1)+4]=pt1;
	C[i*(8+1)+5]=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	C[i*(8+1)+8]=pt;
	}


	CMatrix mathelp;
	mathelp.Transpose(C,9,6);
}

void CBezier::displaysphere(CVector p,CDC* hdc)
{
 smesh->translate(pCt,p);
// pCt=p;
 smesh->display(hdc);
 smesh->translate(p,pCt);
}

void CBezier::sphere(CMesh *s)
{
	float radius=10;
	s->select=s->all;
	CVector Ct(0,0,0);
	pCt=Ct;
	float tetha=pi/2;
	float u=pi/5;
	CVector v,nv;
	CVector vrx,vry,vrz;
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	for(int i=0;i<=5;i++)
	{
	v=Ct+(vry*radius*cos(tetha))+(vrx*radius*sin(tetha));
	CP[i]=v;
	tetha-=u;
	}

	ncp=5;
	ncp1=8;
	ncp2=0;

	deg=1;
	deg1=2;
	deg2=0;

	minpara=0;
	maxpara=1;
	N=3;
	N1=3;
	N2=0;
	Para_universp(0,1,N2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,N,Para);
    Knot_Univer(ncp,deg,Kn,0,1);


		Kn1[0]=0;
		Kn1[1]=0;
		Kn1[2]=0;
		Kn1[3]=(double)1/4;
		Kn1[4]=(double)1/4;
		Kn1[5]=(double)1/2;
		Kn1[6]=(double)1/2;
		Kn1[7]=(double)3/4;
		Kn1[8]=(double)3/4;
		Kn1[9]=1;
		Kn1[10]=1;
		Kn1[11]=1;


	CVector d1=vrx;
	d1.w=0;
	for(i=0;i<=5;i++)
	{

	CVector pt=CP[i]-Ct;

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;


	pt=CP[i];
	pd=Ct+pd;
	CVector pt1=pd-d;
	C[i*(8+1)]=pt;
	C[i*(8+1)+1]=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	C[i*(8+1)+4]=pt1;
	C[i*(8+1)+5]=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	C[i*(8+1)+8]=pt;
	}


	CMatrix mathelp;
	mathelp.Transpose(C,9,6);

  CVector nsu;
  CVector nsv;
  CVector ns;
  i=0;

  	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);

  //u direction  
  s->resizevertex((N+1)*(N1+1));
  for(int kiter=0;kiter<=N2;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=N1;jiter++)
	 {
	   for(int iter=0;iter<=N;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
		  ns=nsu*nsv;
		  ns=ns/absc(ns);

		  nsu=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[kiter],Kn,Kn1,Kn2);
		  CVertex* vertex=new CVertex(nsu,Para[iter],Para1[jiter],N*jiter+iter);
		  vertex->setnormal(ns);
          s->addVertex(kiter*(N1+1)*(N+1)+(N+1)*jiter+iter,vertex);
	   }
	   }
 }


   i=0;
   for(kiter=0;kiter<=N2;kiter=kiter+N2+1)
   {
   for(int jiter=0;jiter<N1;jiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4));
		  i+=5;
	   }
   }
   }
   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  s->addTri(new CTriangle(s->Edge(i),s->Edge(i+1),s->Edge(i+4)));
  		  s->Triangle(s->Tcount()-1)->Edge(2)->flip();

		  s->addTri(new CTriangle(s->Edge(i+2),s->Edge(i+3),s->Edge(i+4)));
	   }





	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=255;//GetRValue(bcolor);
	int gh1=0;//GetGValue(bcolor);
	int gh2=0;//GetBValue(bcolor);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);
	M_spec=M_spec/255;
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	

	int pheight;
	int pwidth;
	l.S_spec=S_spec;
	l.S_diff=S_diff;
	l.M_spec=M_spec;
	l.M_diff=M_diff;
	l.M_amb=M_amb;
	l.lsou=lsou;
	l.view=view;
	l.alpha=alpha;

	s->updateShadingpara(lit,mytext,pwidth,pheight,&l);

}


void CBezier::sphere(CMesh *s,CVector Co)
{
	float radius=3;
	s->select=s->all;
	pCt=Co;
	float tetha=pi/2;
	float u=pi/5;
	CVector v,nv;
	CVector vrx,vry,vrz;
	vrx.getcoorx();
	vry.getcoory();
	vrz.getcoorz();
	for(int i=0;i<=5;i++)
	{
	v=Co+(vry*radius*cos(tetha))+(vrx*radius*sin(tetha));
	CP[i]=v;
	tetha-=u;
	}

	ncp=5;
	ncp1=8;
	ncp2=0;

	deg=1;
	deg1=2;
	deg2=0;

	minpara=0;
	maxpara=1;
	N=5;
	N1=8;
	N2=0;
	Para_universp(0,1,N2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,N,Para);
    Knot_Univer(ncp,deg,Kn,0,1);


		Kn1[0]=0;
		Kn1[1]=0;
		Kn1[2]=0;
		Kn1[3]=(double)1/4;
		Kn1[4]=(double)1/4;
		Kn1[5]=(double)1/2;
		Kn1[6]=(double)1/2;
		Kn1[7]=(double)3/4;
		Kn1[8]=(double)3/4;
		Kn1[9]=1;
		Kn1[10]=1;
		Kn1[11]=1;


	CVector d1=vrx;
	d1.w=0;
	for(i=0;i<=5;i++)
	{

	CVector pt=CP[i]-Co;

	CVector pd=d1*(pt.dot(d1)/(absc(d1)*absc(d1)));
    CVector d=pt-pd;
	double dd=absc(d1);
	CVector ud=d1/dd;
	CVector d2=ud*d;d2.w=0;


	pt=CP[i];
	pd=Co+pd;
	CVector pt1=pd-d;
	C[i*(8+1)]=pt;
	C[i*(8+1)+1]=pt+d2;
	C[i*(8+1)+2]=pd+d2;
	C[i*(8+1)+3]=pt1+d2;
	C[i*(8+1)+4]=pt1;
	C[i*(8+1)+5]=pt1-d2;
	C[i*(8+1)+6]=pd-d2;
	C[i*(8+1)+7]=pt-d2;
	C[i*(8+1)+8]=pt;
	}


	CMatrix mathelp;
	mathelp.Transpose(C,9,6);

  CVector nsu;
  CVector nsv;
  CVector ns;
  i=0;

  	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);

  //u direction 
	int h=s->Vcount();
  s->resizevertex(s->Vcount()+(N+1)*(N1+1));
  for(int kiter=0;kiter<=N2;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=N1;jiter++)
	 {
	   for(int iter=0;iter<=N;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
		  ns=nsu*nsv;
		  ns=ns/absc(ns);

		  nsu=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[kiter],Kn,Kn1,Kn2);
		  CVertex* vertex=new CVertex(nsu,Para[iter],Para1[jiter],N*jiter+iter);
		  vertex->setnormal(ns);
          s->addVertex(h+kiter*(N1+1)*(N+1)+(N+1)*jiter+iter,vertex);
	   }
	   }
 }


   i=0;
   int ho=s->Ecount();
   for(kiter=0;kiter<=N2;kiter=kiter+N2+1)
   {
   for(int jiter=0;jiter<N1;jiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  s->addEdge(new CEdge(s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter));
		  s->addEdge(new CEdge(s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1));
		  s->addEdge(new CEdge(s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2));
		  s->addEdge(new CEdge(s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3));
		  s->addEdge(new CEdge(s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex(h+(N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4));
		  i+=5;
	   }
   }
   }
   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  s->addTri(new CTriangle(s->Edge(ho+i),s->Edge(ho+i+1),s->Edge(ho+i+4)));
  		  s->Triangle(s->Tcount()-1)->Edge(2)->flip();

		  s->addTri(new CTriangle(s->Edge(ho+i+2),s->Edge(ho+i+3),s->Edge(ho+i+4)));
	   }





	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=255;//GetRValue(bcolor);
	int gh1=0;//GetGValue(bcolor);
	int gh2=0;//GetBValue(bcolor);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);
	M_spec=M_spec/255;
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	

	int pheight;
	int pwidth;
	l.S_spec=S_spec;
	l.S_diff=S_diff;
	l.M_spec=M_spec;
	l.M_diff=M_diff;
	l.M_amb=M_amb;
	l.lsou=lsou;
	l.view=view;
	l.alpha=alpha;

	s->updateShadingpara(lit,mytext,pwidth,pheight,&l);

}






void CBezier::smooth(int u, int v, int w)
{
  if(u!=-1) N=u;
  if(v!=-1) N1=v;
  if(w!=-1) N2=w;
  CVector nsu;
  CVector nsv;
  CVector ns;
  int i=0;

  	Para_universp(minpara,maxpara,N,Para);
	Para_universp(minpara1,maxpara1,N1,Para1);
	Para_universp(minpara1,maxpara1,N2,Para2);

  //u direction  
	mesh.empty();
  mesh.resizevertex((N+1)*(N1+1)*(N2+1));
  for(int kiter=0;kiter<=N2;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=N1;jiter++)
	 {
		   for(int iter=0;iter<=N;iter++)
		   {
			  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
			  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
			  ns=nsu*nsv;
			  ns=ns/absc(ns);
			  nsu=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[kiter],Kn,Kn1,Kn2);
			  CVertex* vertex=new CVertex(nsu,Para[iter],Para1[jiter],N*jiter+iter);
			  vertex->setnormal(ns);
			  mesh.addVertex(kiter*(N1+1)*(N+1)+(N+1)*jiter+iter,vertex);
		   }
	   }
 }


   i=0;
   for(kiter=0;kiter<=N2;kiter=kiter+N2)
   {
	   for(int jiter=0;jiter<N1;jiter++)
	   {
		 for(int iter=0;iter<N;iter++)
		 {
			  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
			  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
			  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
			  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
			  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
			  i+=5;
		   }
	   }
	   if(N2==0) kiter++;
   }
   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  mesh.addTri(new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4)));
  		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();

		  mesh.addTri(new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4)));
	   }

	//v direction
   i=ed;
   for(int jiter=0;jiter<=N1;jiter=jiter+N1)
   {
   for(int kiter=0;kiter<N2;kiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
		  i+=5;
	   }
   }
   if(N1==0) jiter++;
   }
   int ed1=ed;
   ed=i;
  	   for(i=ed1;i<ed;i+=5)
	   {
		  mesh.addTri(new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4)));
  		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();
		  mesh.addTri(new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4)));
	   }
	//w direction
	i=ed;
   for(int iter=0;iter<=N;iter=iter+N)
   {
   for(int kiter=0;kiter<N2;kiter++)
   {
	   for(jiter=0;jiter<N1;jiter++)
	   {
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3);
		  new CEdge(mesh.Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),mesh.Vertex((N1+1)*(N+1)*(kiter+1)+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4);
		  i+=5;
	   }
   }
   if(N==0) iter++;
   }
   ed1=ed;
   ed=i;
  	   for(i=ed1;i<ed;i+=5)
	   {
		  mesh.addTri(new CTriangle(mesh.Edge(i),mesh.Edge(i+1),mesh.Edge(i+4)));
  		  mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();
		  mesh.addTri(new CTriangle(mesh.Edge(i+2),mesh.Edge(i+3),mesh.Edge(i+4)));
	   }

		updatecore();

	if(ffd)
	{
		FFDbox->update();

		   CMesh::ivertex iv=mesh.vbegin();int i=0;
		   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
		   {
			  if(box.containpts(*iv->second))
			  {
					  CVector k=box.getParam(*iv->second);
					  FFDbox->Para[i]=k;
			  }
			  else
			  {
				  CVector k(-1,-1,-1);
				  FFDbox->Para[i]=k;
			  }
			  i++;
		   }

	}
}

void CBezier::cube(CVector Ct, float radius)
{

	CAABB v;
	v.add(Ct);
	v.inflate(radius);
	C[0]=v.corner(0);
	C[1]=v.corner(1);
	C[2]=v.corner(2);
	C[3]=v.corner(3);
	C[4]=v.corner(4);
	C[5]=v.corner(5);
	C[6]=v.corner(6);
	C[7]=v.corner(7);

	ncp=1;
	ncp1=1;
	ncp2=1;

	deg=1;
	deg1=1;
	deg2=1;

	minpara=0;
	maxpara=1;
	N=1;
	N1=1;
	N2=1;
	Para_universp(0,1,N2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,N,Para);
    Knot_Univer(ncp,deg,Kn,0,1);

	Para_universp(0,1,N1,Para1);
    Knot_Univer(ncp1,deg1,Kn1,0,1);
}

void CBezier::cube(CMesh *s)
{
	float radius=10;
	s->select=s->all;
	CVector Ct(0,0,0);
	pCt=Ct;

	cube(Ct,radius);


  CVector nsu;
  CVector nsv;
  CVector ns;

  //u direction  
  s->resizevertex((N+1)*(N1+1)*(N2+1));
  for(int kiter=0;kiter<=N2;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=N1;jiter++)
	 {
	   for(int iter=0;iter<=N;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,C,ncp,ncp1,Para[iter],Para1[jiter],Kn,Kn1,Para,false,true);
		  ns=nsu*nsv;
		  ns=ns/absc(ns);		
		  nsu=NURBS(deg,deg1,deg2,C,ncp,ncp1,ncp2,Para[iter],Para1[jiter],Para2[kiter],Kn,Kn1,Kn2);
		  CVertex* vertex=new CVertex(nsu,Para[iter],Para1[jiter],N*jiter+iter);
		  vertex->setnormal(ns);
          s->addVertex(kiter*(N1+1)*(N+1)+(N+1)*jiter+iter,vertex);
	   }
	   }
 }


   int i=0;
   for(kiter=0;kiter<=N2;kiter=kiter+N2+1)
   {
   for(int jiter=0;jiter<N1;jiter++)
   {
	 for(int iter=0;iter<N;iter++)
	 {
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+1));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+2));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+3));
		  s->addEdge(new CEdge(s->Vertex((N1+1)*(N+1)*kiter+(N+1)*jiter+iter),s->Vertex((N1+1)*(N+1)*kiter+(N+1)*(jiter+1)+iter+1),(N1+1)*(N+1)*kiter+(N+1)*jiter+iter+4));
		  i+=5;
	   }
   }
   }
   int ed=i;
  	   for(i=0;i<ed;i+=5)
	   {
		  s->addTri(new CTriangle(s->Edge(i),s->Edge(i+1),s->Edge(i+4)));
  		  s->Triangle(s->Tcount()-1)->Edge(2)->flip();
		  s->addTri(new CTriangle(s->Edge(i+2),s->Edge(i+3),s->Edge(i+4)));
	   }





	CVector p[5];
	CPoint ppo[5];
	double m_gls=2;
	int gh=255;//GetRValue(bcolor);
	int gh1=0;//GetGValue(bcolor);
	int gh2=0;//GetBValue(bcolor);
	CCVector M_spec(gh*.1,gh1*.1,gh2*.1);
	M_spec=M_spec/255;
	CCVector M_diff((int)GetRValue(bcolor),(int)GetGValue(bcolor),(int)GetBValue(bcolor));
	M_diff=M_diff/255;
	CCVector M_amb(M_diff);
	M_amb=M_amb/255;
	

	int pheight;
	int pwidth;
	l.S_spec=S_spec;
	l.S_diff=S_diff;
	l.M_spec=M_spec;
	l.M_diff=M_diff;
	l.M_amb=M_amb;
	l.lsou=lsou;
	l.view=view;
	l.alpha=alpha;

	s->updateShadingpara(lit,mytext,pwidth,pheight,&l);


}

void CBezier::cap(bool vctop,bool vcbot)
{

	updatecore();

	if(vcbot)
	{

	set<double> ku,kv;
	int m=ncp;
	vector<double> Knu(50),Knv(50),Knw(50);
	int ncpu,ncpv,ncpw,degu,degv,degw;
	ncpu=1;
	ncpv=1;
	ncpw=1;
	degu=1;
	degv=1;
	degw=1;
	vector<CVector> Cb,Mb,Co,Mbe;
	Cb.resize(10);
	CAABB box1;
	CVector v;
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();vrz.getcoorz();
		
		
		
		
	for(int iter=0;iter<=N;iter++)
	{
	CVector v=*mesh.Vertex(iter);
	v=vrx*v.x+vrz*v.z+vry*v.y;
	 box1.add(v);
	 Mb.push_back(v);
	}

	Cb[0]=box1.corner(0);
	Cb[1]=box1.corner(1);
	Cb[2]=box1.corner(2);
	Cb[3]=box1.corner(3);
	Cb[4]=box1.corner(4);
	Cb[5]=box1.corner(5);
	Cb[6]=box1.corner(6);
	Cb[7]=box1.corner(7);

	Knot_Univer(1,1,Knu,0,1);
    Knot_Univer(1,1,Knv,0,1);
//    Knot_Univer(1,1,Knw,0,1);

	CMatrix mat;


	int boh=0;
		 for(iter=0;iter<=N;iter++)
		 {
			  CVector k=box1.getParam(Mb[iter]);
			  if(find(Knu.begin(),Knu.end(),k.x)==Knu.end())
			  {
				  if(k.x!=1E15)
					Bohms(k.x,0,0,degu,degv,degw,Knu,Knv,Knw,Cb,ncpu,ncpv,ncpw);
			  }
			  if(find(Knv.begin(),Knv.end(),k.y)==Knv.end())
			  {
				  if(k.y!=1E15)
					Bohms(0,k.y,0,degu,degv,degw,Knu,Knv,Knw,Cb,ncpu,ncpv,ncpw);
			  }
		 }
		 ptbegin=Mb;
		 ptend=ptbegin;
//		 rotate(ptend.begin(),ptend.begin()+1,ptend.end());

CVector nsu,nsv,ns;
	int vc=mesh.Vcount();
//	mesh.resizevertex(vc+(ncpu+1)*(ncpv+1));
  for(int kiter=0;kiter<=0;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=ncpv;jiter++)
	 {
	   for(int iter=0;iter<=ncpu;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,Cb,ncpu,ncpv,Knu[iter],Knv[jiter],Knu,Knv,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,Cb,ncpu,ncpv,Knu[iter],Knv[jiter],Knu,Knv,Para,false,true);
		  ns=nsu*nsv;
		  ns=ns/absc(ns);
		  nsu=Cb[(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter];
		  nsv=nsu;
		  nsu=vrx*nsu.x+vry*nsu.y+vrz*nsu.z;
		  box.add(nsu);
		  CVertex *vertex=new CVertex(nsu,Knu[iter],Knv[jiter],N*jiter+iter);
		  vertex->setnormal(ns);
  
			  if(!isInside(nsv))
			  {
				  vertex->visible=true;
//				  vertex->display(hdc);
			  }
			  else
			  {
				  vertex->visible=false;
			  }
		  mesh.addVertex(vertex);
	   }
	   }
  }


	   int el=mesh.Ecount();
	   int i=0;
	   for(kiter=0;kiter<=ncpw;kiter++)
	   {
	   for(int jiter=0;jiter<ncpv;jiter++)
	   {
		 for(int iter=0;iter<ncpu;iter++)
		 {
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+2));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+3));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+4));
			  i+=5;
		 }
	   }
	   if(N2==0) kiter++;
	   }
		
//	   mesh.displayEdge(hdc);
	   vector<CTriangle*> M;
	   int ed=i;
  		   for(i=0;i<ed;i+=5)
		   {
			   CEdge et=*mesh.Edge(el+i+4);
			   et.flip();
			  CTriangle t(mesh.Edge(el+i),mesh.Edge(el+i+1),mesh.Edge(el+i+4));
			  M.push_back(new CTriangle(t));
			  M[M.size()-1]->Edge(2)->flip();

/*			  CVector v=t.getcent();
			  CRect r(v,v);
			  r.InflateRect(5,5,5,5);
			  if((t.Vertex(0)->visible)&&(t.Vertex(1)->visible)&&(t.Vertex(2)->visible))
			  {

			  hdc->Ellipse(r);
		        mesh.addTri(new CTriangle(mesh.Edge(el+i),mesh.Edge(el+i+1),mesh.Edge(el+i+4)));
                mesh.Triangle(mesh.Tcount()-1)->Edge(2)->flip();

			  }
			  else
			  if((!t.Vertex(0)->visible)&&(!t.Vertex(1)->visible)&&(!t.Vertex(2)->visible))
			  {

			  }*/
			  CTriangle t1(CTriangle(mesh.Edge(el+i+2),mesh.Edge(el+i+3),mesh.Edge(el+i+4)));
			  M.push_back(new CTriangle(t1));
			  
			 /* CVector v1=t1.getcent();
			  CRect r1(v1,v1);
			  r1.InflateRect(5,5,5,5);
			  if(!isInside(v1))
			  {
				  hdc->Ellipse(r1);
				  mesh.addTri(new CTriangle(mesh.Edge(el+i+2),mesh.Edge(el+i+3),mesh.Edge(el+i+4)));
			  }*/
		   }
			clipTriangle(M);
}
	if(vctop)
	{

	set<double> ku,kv;
	int m=ncp;
	vector<double> Knu(50),Knv(50),Knw(50);
	int ncpu,ncpv,ncpw,degu,degv,degw;
	ncpu=1;
	ncpv=1;
	ncpw=1;
	degu=1;
	degv=1;
	degw=1;
	vector<CVector> Cb,Mb,Co,Mbe;
	Cb.resize(10);
	CAABB box1;
	CVector v;
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();vrz.getcoorz();

		
	box1.empty();
	Mb.clear();
	   for(int iter=0;iter<=N;iter++)
	   {
		 CVector v=*mesh.Vertex(N2*(N1+1)*(N+1)+N1*(N+1)+iter);
		 v=vrx*v.x+vrz*v.z+vry*v.y;
		 box1.add(v);
		 Mb.push_back(v);
	   }

	Cb[0]=box1.corner(0);
	Cb[1]=box1.corner(1);
	Cb[2]=box1.corner(2);
	Cb[3]=box1.corner(3);
	Cb[4]=box1.corner(4);
	Cb[5]=box1.corner(5);
	Cb[6]=box1.corner(6);
	Cb[7]=box1.corner(7);

	Knot_Univer(1,1,Knu,0,1);
    Knot_Univer(1,1,Knv,0,1);
//    Knot_Univer(1,1,Knw,0,1);

	CMatrix mat;


	int boh=0;
		 for(iter=0;iter<=N;iter++)
		 {
			  CVector k=box1.getParam(Mb[iter]);
			  if(find(Knu.begin(),Knu.end(),k.x)==Knu.end())
			  {
				  if(k.x!=1E15)
					Bohms(k.x,0,0,degu,degv,degw,Knu,Knv,Knw,Cb,ncpu,ncpv,ncpw);
			  }
			  if(find(Knv.begin(),Knv.end(),k.y)==Knv.end())
			  {
				  if(k.y!=1E15)
					Bohms(0,k.y,0,degu,degv,degw,Knu,Knv,Knw,Cb,ncpu,ncpv,ncpw);
			  }
		 }
		 ptbegin=Mb;
		 ptend=ptbegin;
//		 rotate(ptend.begin(),ptend.begin()+1,ptend.end());

CVector nsu,nsv,ns;
	int vc=mesh.Vcount();
  for(int kiter=0;kiter<=0;kiter++)//=kiter+N2-1)
  {
    for(int jiter=0;jiter<=ncpv;jiter++)
	 {
	   for(int iter=0;iter<=ncpu;iter++)
	   {
		  nsu=Sur_deriv(deg,deg1,Cb,ncpu,ncpv,Knu[iter],Knv[jiter],Knu,Knv,Para,true,false);
		  nsv=Sur_deriv(deg,deg1,Cb,ncpu,ncpv,Knu[iter],Knv[jiter],Knu,Knv,Para,false,true);
		  ns=nsu*nsv;
		  ns=ns/absc(ns);
		  nsu=Cb[(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter];
		  nsv=nsu;
		  nsu=vrx*nsu.x+vry*nsu.y+vrz*nsu.z;
		  box.add(nsu);
		  CVertex *vertex=new CVertex(nsu,Knu[iter],Knv[jiter],N*jiter+iter);
		  vertex->setnormal(ns);
  
			  if(!isInside(nsv))
			  {
				  vertex->visible=true;
			  }
			  else
			  {
				  vertex->visible=false;
			  }
		  mesh.addVertex(vertex);
	   }
	   }
  }


	   int el=mesh.Ecount();
	   int i=0;
	   for(kiter=0;kiter<=ncpw;kiter++)
	   {
	   for(int jiter=0;jiter<ncpv;jiter++)
	   {
		 for(int iter=0;iter<ncpu;iter++)
		 {
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+1));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+2));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+3));
			  mesh.addEdge(new CEdge(mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter),mesh.Vertex(vc+(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*(jiter+1)+iter+1),(ncpv+1)*(ncpu+1)*kiter+(ncpu+1)*jiter+iter+4));
			  i+=5;
		 }
	   }
	   if(N2==0) kiter++;
	   }
		
	   vector<CTriangle*> M;
	   int ed=i;
  		   for(i=0;i<ed;i+=5)
		   {
			   CEdge et=*mesh.Edge(el+i+4);
			   et.flip();
			  CTriangle t(mesh.Edge(el+i),mesh.Edge(el+i+1),mesh.Edge(el+i+4));
			  M.push_back(new CTriangle(t));
			  M[M.size()-1]->Edge(2)->flip();

			  CTriangle t1(CTriangle(mesh.Edge(el+i+2),mesh.Edge(el+i+3),mesh.Edge(el+i+4)));
			  M.push_back(new CTriangle(t1));
			  
		   }
			clipTriangle(M);
	}
	updatecore();

}

void CBezier::cap0(bool vctop,bool vcbot)
{

	updatecore();
	set<double> ku,kv;
	int m=ncp;
	vector<double> Knu(50),Knv(50),Knw(50);
	int ncpu,ncpv,ncpw,degu,degv,degw;
	ncpu=1;
	ncpv=1;
	ncpw=1;
	degu=1;
	degv=1;
	degw=1;
	vector<CVector> Cb,Mb,Co,Mbe;
	Cb.resize(10);
	CAABB box1;
	CVector v;
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();vrz.getcoorz();

	if(vcbot)
	{
   for(int iter=0;iter<=N;iter++)
   {
	 Mb.push_back(*mesh.Vertex(iter));
   }

    CPolygon p1(Mb);
	CPolygon p2;
	p1.Triangulate(&p2);
	Cb=p2.getpoint();
	int h=Cb.size();
	int i=0;

	for(i=0;i<h-2;i+=3)
	{
		mesh.addTri(new CTriangle(mesh.Vertex(Cb[i].ws),mesh.Vertex(Cb[i+1].ws),mesh.Vertex(Cb[i+2].ws)));
	}
	}
	box1.empty();
	Mb.clear();
	if(vctop)
	{

	   for(int iter=0;iter<=N;iter++)
	   {
		 box1.add(CVector(*mesh.Vertex(N2*(N1+1)*(N+1)+N1*(N+1)+iter)));
	   }

	   for(iter=0;iter<=N;iter++)
	   {
		 v=box1.getParam(*mesh.Vertex(N2*(N1+1)*(N+1)+N1*(N+1)+iter));
		 Mb.push_back(v);
	   }

		CPolygon p1(Mb);
		CPolygon p2;
		p1.Triangulate(&p2);
		Cb=p2.getpoint();
		int h=Cb.size();
		int i=0;
		int k=N2*(N1+1)*(N+1)+N1*(N+1);
		for(i=0;i<h-2;i+=3)
		{
			mesh.addTri(new CTriangle(mesh.Vertex(k+Cb[i].ws),mesh.Vertex(k+Cb[i+1].ws),mesh.Vertex(k+Cb[i+2].ws)));
		}
	}
	updatecore();
}


bool CBezier::clipTriangle(vector<CTriangle*>& Mb)
{
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();vrz.getcoorz();
	int k=Mb.size();
 for(int i=0;i<k;i++)
 {
 CTriangle* t=Mb[i];

	
 if(t->Vertex(0)->visible &&t->Vertex(1)->visible && t->Vertex(2)->visible)
 {
	 CVector v(t->getcent());
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
	     mesh.addTri(t);
	 }
 }
 else 
 if(!t->Vertex(0)->visible &&!t->Vertex(1)->visible && !t->Vertex(2)->visible)
 {
	 continue;
 }else
 {
 CVector v1=*t->Vertex(0);
 CVector v2=*t->Vertex(1);
 CVector v3=*t->Vertex(2);
 CVector ve,vb;
 for(vector<CVector>::iterator iterb=ptbegin.begin(),itere=ptend.begin();iterb!=ptbegin.end();iterb++,itere++)
 {
	 ve=vrx*itere->x+vry*itere->y+vrz*itere->z;
	 vb=vrx*iterb->x+vry*iterb->y+vrz*iterb->z;

	 CVector v=ve-vb;
	 CVector vo=v1-vb;
 CVector p0=v*vo;
	 vo=v2-vb;
 CVector p1=v*vo;
	 vo=v3-vb;
 CVector p2=v*vo;

 if(p1==CVector(0,0,0))
 {
	 Clipconfiguration0(&vb,&ve,t->Vertex(1),t->Vertex(2),t->Vertex(0));
 }else
 if(p2==CVector(0,0,0))
 {
	 Clipconfiguration0(&vb,&ve,t->Vertex(2),t->Vertex(1),t->Vertex(0));
 }else
 if(p0==CVector(0,0,0))
 {
	 Clipconfiguration0(&vb,&ve,t->Vertex(0),t->Vertex(2),t->Vertex(1));
 }else
 if(p0.dot(p1)<0)
 {
	 Clipconfiguration(&vb,&ve,t->Vertex(0),t->Vertex(1),t->Vertex(2));
 }else
 if(p0.dot(p2)<0)
 {
	 Clipconfiguration(&vb,&ve,t->Vertex(2),t->Vertex(0),t->Vertex(1));
 }else
 if(p1.dot(p2)<0)
 {
	 Clipconfiguration(&vb,&ve,t->Vertex(1),t->Vertex(2),t->Vertex(0));
 }

 }
 }
 }
 return false;
}
void CBezier::Clipconfiguration0(CVector* b,CVector* e,CVertex* vi0,CVertex* vi1,CVertex* vi2)
{
 CVector vrx,vry,vrz;
 vrx.getcoorx();vry.getcoory();vrz.getcoorz();
 


 CRay v(*b,*e,1);
 CRay bi(CVector(*vi1),CVector(*vi2),1);
 CVector vco=v.Intersect(bi);
 if(vco.x==1E-10) return;
/* if((!vi1->visible)&&(!vi2->visible))
 {
	 vi1->v=vco;
	 vi1->visible=true;
	 return;
 }
*/
// vco->v=vc;

 if(vi0->visible)
 {
/*	 if((vi2->visible)&&(vi1->visible))
	 {
/*	 CTriangle t1(vi0,vc1,vi1);
		 if(!isInside(t1.getcent()))
		 {
			CTriangle* t=new CTriangle(vi0,vc1,vi1);
			mesh.addTri(t);
		 }*/
/*	 mesh.addTri(new CTriangle(vi0,vi1,vi2));
	 }
	 else
	 if((!vi2->visible)&&(!vi1->visible))
	 {
		 return;
	 }
	 else
	 {*/
	 CRay bi(CVector(*vi1),CVector(*vi2),1);
	 CVector vc=v.Intersect(bi);
	 if(vc.x==1E-10) return;
	 CVector v;

	 if(vi1->visible)
	 {
	 v=(vi0->v+vc+vi1->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
		 if(!isInside(v))
		 {

			 CVertex* vc1=new CVertex;
			vc1->v=vc;

			 float zv=absc(vi1->v-vc)/absc(vi1->v-vi2->v);
			 vc1->un=(1-zv)*vi1->un+zv*vi2->un;
			 vc1->vn=(1-zv)*vi1->vn+zv*vi2->vn;
			 vc1->n=vi1->n*(1-zv)+vi2->n*zv;

			
			
			mesh.addVertex(vc1);
			CTriangle* t=new CTriangle(vi0,vc1,vi1);
			mesh.addTri(t);
		 }
	 }
	if(vi2->visible)
	{
	 v=(vi0->v+vc+vi2->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
		 if(!isInside(v))
		 {
			CVertex* vc1=new CVertex;
			vc1->v=vc;

			 float zv=absc(vi1->v-vc)/absc(vi1->v-vi2->v);
			 vc1->un=(1-zv)*vi1->un+zv*vi2->un;
			 vc1->vn=(1-zv)*vi1->vn+zv*vi2->vn;
			 vc1->n=vi1->n*(1-zv)+vi2->n*zv;

			
			mesh.addVertex(vc1);
			CTriangle* t=new CTriangle(vi0,vc1,vi2);
			mesh.addTri(t);
		 }
	}
 }

}
void CBezier::Clipconfiguration(CVector* b,CVector* e,CVertex* vi0,CVertex* vi1,CVertex* vi2)
{
// CVertex* vco=new CVertex;
// CVertex* vc1=new CVertex;
// mesh.addVertex(vco);
// mesh.addVertex(vc1);
 CVector vrx,vry,vrz;
 vrx.getcoorx();vry.getcoory();vrz.getcoorz();


 CRay vo(*b,*e,1);
 CRay bi(CVector(*vi0),CVector(*vi1),1);
 CVector vci=vo.Intersect(bi);
 CVector v;
 if(vci.x==1E-10) return;
/* if((!vi0->visible)&&(!vi1->visible))
 {
	 vi1->v=vci;
	 vi1->visible=true;
	 return;
 }*/

 // vco->v=vc;

 if(vi0->visible)
 {
	 if(vi2->visible)
	 {
	 CRay bi1(CVector(*vi1),CVector(*vi2),1);
	 CVector vc=vo.Intersect(bi1);
	 if(vc.x==1E-10) return;

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;

	 mesh.addVertex(vco);
	 mesh.addVertex(vc1);
	 vc1->v=vc;
	 vco->v=vci;

	 float zv=absc(vi1->v-vc)/absc(vi1->v-vi2->v);
	 vc1->un=(1-zv)*vi1->un+zv*vi2->un;
	 vc1->vn=(1-zv)*vi1->vn+zv*vi2->vn;
	 vc1->n=vi1->n*(1-zv)+vi2->n*zv;

	 zv=absc(vi0->v-vci)/absc(vi0->v-vi1->v);
	 vco->un=(1-zv)*vi0->un+zv*vi1->un;
	 vco->vn=(1-zv)*vi0->vn+zv*vi1->vn;
	 vco->n=vi0->n*(1-zv)+vi1->n*zv;


	 v=(vc+vci+vi0->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
			  mesh.addTri(new CTriangle(vco,vc1,vi0));
	 }
	 v=(vc+vi2->v+vi0->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
		 mesh.addTri(new CTriangle(vc1,vi2,vi0));
	 }
	 }
	 else 
	 {
	 CRay bi1(CVector(*vi0),CVector(*vi2),1);
	 CVector vc=vo.Intersect(bi1);
	 if(vc.x==1E-10) return;

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh.addVertex(vco);
	 mesh.addVertex(vc1);
	 vc1->v=vc;
	 vco->v=vci;

	 float zv=absc(vi0->v-vc)/absc(vi0->v-vi2->v);
	 vc1->un=(1-zv)*vi0->un+zv*vi2->un;
	 vc1->vn=(1-zv)*vi0->vn+zv*vi2->vn;
	 vc1->n=vi0->n*(1-zv)+vi2->n*zv;

	 zv=absc(vi0->v-vci)/absc(vi0->v-vi1->v);
	 vco->un=(1-zv)*vi0->un+zv*vi1->un;
	 vco->vn=(1-zv)*vi0->vn+zv*vi1->vn;
	 vco->n=vi0->n*(1-zv)+vi1->n*zv;


	 v=(vc+vci+vi0->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
			  mesh.addTri(new CTriangle(vco,vc1,vi0));
		}
	 }
 }
 else
 {
	 if(vi2->visible)
	 {
	 CRay bi1(CVector(*vi0),CVector(*vi2),1);
	 CVector vc=vo.Intersect(bi1);
//	 vc1->v=vc;
	 if(vc.x==1E-10) return;
	 
	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh.addVertex(vco);
	 mesh.addVertex(vc1);
	 vc1->v=vc;
	 vco->v=vci;

	 float zv=absc(vi0->v-vc)/absc(vi0->v-vi2->v);
	 vc1->un=(1-zv)*vi0->un+zv*vi2->un;
	 vc1->vn=(1-zv)*vi0->vn+zv*vi2->vn;
	 vc1->n=vi0->n*(1-zv)+vi2->n*zv;

	 zv=absc(vi0->v-vci)/absc(vi0->v-vi1->v);
	 vco->un=(1-zv)*vi0->un+zv*vi1->un;
	 vco->vn=(1-zv)*vi0->vn+zv*vi1->vn;
	 vco->n=vi0->n*(1-zv)+vi1->n*zv;

	 
	 v=(vi1->v+vci+vi2->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
			 mesh.addTri(new CTriangle(vco,vi1,vi2));
	 }

	 v=(vc+vci+vi2->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
		 mesh.addTri(new CTriangle(vco,vi2,vc1));
	 }
	 }
	 else
	 {
	 CRay bi1(CVector(*vi1),CVector(*vi2),1);
	 CVector vc=vo.Intersect(bi1);
//	 vc1->v=vc;
	 if(vc.x==1E-10)  return;

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh.addVertex(vco);
	 mesh.addVertex(vc1);
	 vc1->v=vc;
	 vco->v=vci;

	 float zv=absc(vi1->v-vc)/absc(vi1->v-vi2->v);
	 vc1->un=(1-zv)*vi1->un+zv*vi2->un;
	 vc1->vn=(1-zv)*vi1->vn+zv*vi2->vn;
	 vc1->n=vi1->n*(1-zv)+vi2->n*zv;

	 zv=absc(vi1->v-vc)/absc(vi1->v-vi0->v);
	 vco->un=(1-zv)*vi1->un+zv*vi0->un;
	 vco->vn=(1-zv)*vi1->vn+zv*vi0->vn;
	 vco->n=vi1->n*(1-zv)+vi0->n*zv;
	 


	 v=(vc+vci+vi1->v)/3;
	 v=vrx*v.x+vry*v.y+vrz*v.z;
	 if(!isInside(v))
	 {
	 mesh.addTri(new CTriangle(vco,vi1,vc1));
 
	 }
	 }

 }

}

CMesh* CBezier::getsphere()
{
 return smesh;
}

void CBezier::setFFDon()
{
	if(ffd) 
		updateffd();
	select=pnt;
}
void CBezier::setBlockon()
{
	int ncp0=ContP.size();
	if(ncp0>0)
	{
		if(lstate==L1){
	if(ContP[ncp-1]==ContP[ncp-2])
	{
		ContP.resize(ncp-3);
		lstate=L0;
	}
	addtovecBezier();
		}
	}
	select=full;
}

CFigure* CBezier::generateCopy()
{
	CBezier* l=new CBezier;
	l->copy(this);
	return l;

}

void CBezier::plane(CFigure *r)
{
    CMesh m;
	m.copy (r->getMesh ());
	C[0]=m.Vector(0);
	C[1]=m.Vector(1);
	C[2]=m.Vector(3);
	C[3]=m.Vector(2);

	ncp=1;
	ncp1=1;
	ncp2=0;

	deg=1;
	deg1=1;
	deg2=0;

	minpara=0;
	maxpara=1;
	N=1;
	N1=1;
	N2=0;
	Para_universp(0,1,N2,Para2);
    Knot_Univer(ncp2,deg2,Kn2,0,1);

	Para_universp(0,1,N,Para);
    Knot_Univer(ncp,deg,Kn,0,1);

	Para_universp(0,1,N1,Para1);
    Knot_Univer(ncp1,deg1,Kn1,0,1);

}

CVector CBezier::RefVec(float u)
{
	int i0= u * (N-1);
	int i1= i0>0?i0-1:i0;
	int i2= i0<N?i0+1:i0;
	refl.clear();
	refl.push_back((float)i1/N);
	refl.push_back((float)i2/N);
	return CFigure::RefVec();
  
}

CVector CBezier::getPoint(float u)
{
	return CFigure::getPoint(u);
	CVector v=Bspline(deg,CP,ncp,u,Kn);//NURBS(deg,CP,ncp,u,Kn);
	if(u==1)
	{
		int j=0;
	}
	return v;
}
