// Triangle.cpp: implementation of the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Triangle.h"
#include "mesh.h"

//#include "tritest.h"

/*
#include "renderer/rasterizer_subdivaffine.h"
#include "renderer/geometry_processor.h"
#include "renderer/span.h"
#include "democommon.h"
#include "fixedpoint/fixed_func.h"
#include "vector_math.h"
*/


#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HANDLE 	hdcmutex=CreateMutex( 
    NULL,                       // no security attributes
    FALSE,                      // initially not owned
    "MutexToHDC");  // name of mutex




CTriangle::~CTriangle()
{
/*	edge1
	if(edge1!=NULL)
	{
		edge1->RemoveAdjT(this);
		if(edge1->getAdjt()==NULL)
		{
			delete edge1;
			edge1=NULL;
		}
	}
	if(edge2!=NULL)
	{
		edge2->RemoveAdjT(this);
		if(edge2->getAdjt()==NULL)
		{
			delete edge2;
			edge2=NULL;
		}
	}
	if(edge3!=NULL)
	{
		edge3->RemoveAdjT(this);
		if(edge3->getAdjt()==NULL)
		{
			delete edge3;
			edge3=NULL;
		}
	}*/
}

CTriangle::CTriangle(CEdge* f, CEdge* s, CEdge* t): eit(f->it),ejt(s->it),ekt(t->it),cent(((CVector)*f->Start()+(CVector)*s->Start()+(CVector)*t->Start())/3),\
											sit(f->sit),sjt(s->sit),skt(t->sit)
{
	if(sit==skt)
	{
		t->flip();
		skt=t->sit;
		cent=((CVector)*f->Start()+(CVector)*s->Start()+(CVector)*t->Start())/3;
	}
	mesh=f->getMesh();
	mesh->Edge(eit)->addAdjT(this);
	mesh->Edge(ejt)->addAdjT(this);
	mesh->Edge(ekt)->addAdjT(this);
	sit->addAdjT(this);
	sjt->addAdjT(this);
	skt->addAdjT(this);
	mesh->addTri(this);
	
}

CTriangle::CTriangle(CVertex* f, CVertex* s, CVertex* t)
{

	ASSERT((f->sit!=-1)&&(s->sit!=-1)&&(t->sit!=-1));


	sit=f;
	sjt=s;
	skt=t;
	mesh=f->getMesh();

	new CEdge(f,s);
	int i=mesh->Ecount()-1;
	CEdge* e=mesh->Edge(i);
	eit=e->it;

	new CEdge(s,t);
	i=mesh->Ecount()-1;
	e=mesh->Edge(i);
	ejt=e->it;

	new CEdge(t,f);
	i=mesh->Ecount()-1;
	e=mesh->Edge(i);
	ekt=e->it;
	


	mesh->Edge(eit)->addAdjT(this);
	mesh->Edge(ejt)->addAdjT(this);
	mesh->Edge(ekt)->addAdjT(this);
	sit->addAdjT(this);
	sjt->addAdjT(this);
	skt->addAdjT(this);
	it=-1;
	mesh->addTri(this);

}

CTriangle::CTriangle(CEdge f, CEdge s, CEdge t)
{
	
	eit=f.it;
	ejt=s.it;
	ekt=t.it;
	cent=((CVector)*f.Start()+(CVector)*s.Start()+(CVector)*t.Start())/3;
	sit=f.sit;
	sjt=s.sit;
	skt=t.sit;
	mesh=f.getMesh();

	mesh->Edge(eit)->addAdjT(this);
	mesh->Edge(ejt)->addAdjT(this);
	mesh->Edge(ekt)->addAdjT(this);
	sit->addAdjT(this);
	sjt->addAdjT(this);
	skt->addAdjT(this);
	mesh->addTri(this);

}
CTriangle::CTriangle(CVertex f, CVertex s, CVertex t)
{
	ASSERT((f.sit!=-1)&&(s.sit!=-1)&&(t.sit!=-1));
	sit=new CVertex(f);
	sjt=new CVertex(s);
	skt=new CVertex(t);
	mesh=f.getMesh();

	new CEdge(f,s);
	int i=mesh->Ecount()-1;
	CEdge* e=mesh->Edge(i);
	eit=e->it;

	new CEdge(s,t);
	i=mesh->Ecount()-1;
	e=mesh->Edge(i);
	ejt=e->it;

	new CEdge(t,f);
	i=mesh->Ecount()-1;
	e=mesh->Edge(i);
	ekt=e->it;


	mesh->Edge(eit)->addAdjT(this);
	mesh->Edge(ejt)->addAdjT(this);
	mesh->Edge(ekt)->addAdjT(this);
	sit->addAdjT(this);
	sjt->addAdjT(this);
	skt->addAdjT(this);
	it=-1;
	mesh->addTri(this);
}





void CTriangle::display(CDC *hdc,CVector loc[2],CCVector lit[6])
{

	struct pointc 
	{
		CPoint p;
		double z;
		CCVector c;
	};
	CEdge* edge1=mesh->Edge(eit);
	CEdge* edge2=mesh->Edge(ejt);
	CEdge* edge3=mesh->Edge(ekt);
	pointc v[4];
	v[0].p=(CVector)*edge1->Start();
	v[1].p=(CVector)*edge2->Start();
	v[2].p=(CVector)*edge3->Start();
	v[0].z=(*edge1->Start()).getDepth();
	v[1].z=(*edge2->Start()).getDepth();
	v[2].z=(*edge3->Start()).getDepth();
	v[3]=v[0];

	if((v[0].p==v[1].p)||(v[0].p==v[2].p)||(v[1].p==v[2].p))
	{
		return;
	}

	CVector view=loc[0],lsou=loc[1];
	CCVector S_spec=lit[0],M_spec=lit[1],S_diff=lit[2],M_diff=lit[3],\
			G_amb=lit[4],M_amb=lit[5];

	CVector po=(view-(CVector)*edge1->Start())/(view.absc(view-(CVector)*edge1->Start()));
	CVector l=(lsou-(CVector)*edge1->Start())/(view.absc(lsou-(CVector)*edge1->Start()));
	CVector n=(*edge1->Start()).getNormal();//-(CVector)*edge3->Start())*((CVector)*edge1->Start()-(CVector)*edge2->Start());
	n=n/view.absc(n);
	double j=n.dot(l);

	CVector r=n*(2*(n.dot(l)))-l;
		 
	double b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	CCVector clit1=(S_spec*b0)*M_spec;
	CCVector clit2=(S_diff*max(n.dot(l),0))*M_diff;
	CCVector clit=clit1+clit2+G_amb*M_amb;
//	(*edge1->Start()).setcol(clit);
	v[0].c=clit;

	po=(view-(CVector)*edge2->Start())/(view.absc(view-(CVector)*edge2->Start()));
	l=(lsou-(CVector)*edge2->Start())/(view.absc(lsou-(CVector)*edge2->Start()));
	n=(*edge2->Start()).getNormal();//((CVector)*edge2->Start()-(CVector)*edge1->Start())*((CVector)*edge2->Start()-(CVector)*edge3->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l)))-l;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
//	(*edge2->Start()).setcol(clit);
	v[1].c=clit;

	po=(view-(CVector)*edge3->Start())/(view.absc(view-(CVector)*edge3->Start()));
	l=(lsou-(CVector)*edge3->Start())/(view.absc(lsou-(CVector)*edge3->Start()));
	n=(*edge3->Start()).getNormal();//((CVector)*edge3->Start()-(CVector)*edge2->Start())*((CVector)*edge3->Start()-(CVector)*edge1->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l)))-l;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
//	(*edge3->Start()).setcol(clit);
	v[2].c=clit;


	
	int xmin, xmax, ymin, ymax;

	ymin=v[0].p.y;
	ymin=(ymin>v[1].p.y)?v[1].p.y:ymin;
	ymin=(ymin>v[2].p.y)?v[2].p.y:ymin;

	xmin=v[0].p.x;
	xmin=(xmin>v[1].p.x)?v[1].p.x:xmin;
	xmin=(xmin>v[2].p.x)?v[2].p.x:xmin;

	ymax=v[0].p.y;
	ymax=(ymax>v[1].p.y)?ymax:v[1].p.y;
	ymax=(ymax>v[2].p.y)?ymax:v[2].p.y;

	xmax=v[0].p.x;
	xmax=(xmax>v[1].p.x)?xmax:v[1].p.x;
	xmax=(xmax>v[2].p.x)?xmax:v[2].p.x;

	int L=ymax-ymin;

/*y = y of first non empty entry in ET
AET = null
repeat
	move all ET entries in slot y to AET
	sort AET entries according to x min
	fill spans using pairs of AET entries
	for all AET members
		if y max = y then remove from AET
		y = y+1
		for all AET members
			update numerator
			if numerator>denominator
				numerator=numerator-denominator
				x = x+1
	until AET and ET empty*/

	pointc *xl,*xr,v0,v1,v2;
	bool bh=false;
	int yr=0;
	if(ymin==v[1].p.y)
	{
		v0=v[1];v1=v[0];v2=v[2];
	}
	else
	if(ymin==v[0].p.y)
	{
		v0=v[0];v1=v[1];v2=v[2];
	}
	else
	if(ymin==v[2].p.y)
	{
		v0=v[2];v1=v[0];v2=v[1];
	}

		if (v1.p.x<v2.p.x)
		{
			xl=&v1;xr=&v2;
		} else
		{
			xl=&v2;xr=&v1;
		}

		float xL=xl->p.x, xR=xr->p.x,alphal,alphar;
		CCVector cL=xl->c,cR=xr->c,betal,betar;
		double zL=xl->z,zR=xr->z,zetal,zetar;
		if(v0.p.y==xl->p.y)
		{
			alphal=0;
//		betal=0;
		}else
		{
			alphal=(float)(v0.p.x-xL)/(v0.p.y-xl->p.y);
			betal=(v0.c-cL)/(v0.p.y-xl->p.y);
			zetal=(v0.z-zL)/(v0.p.y-xl->p.y);
		}
	
		if(v0.p.y==xr->p.y)
		{
			alphar=0;
//		betar=0;
		}else
		{
			alphar=(float)(v0.p.x-xR)/(v0.p.y-xr->p.y);
			betar=(v0.c-cR)/(v0.p.y-xr->p.y);
			zetar=(v0.z-zR)/(v0.p.y-xr->p.y);
		}


		xL=v0.p.x;
		xR=v0.p.x;
		
		cL=v0.c;
		cR=v0.c;

		zL=v0.z;
		zR=v0.z;

		CCVector vc;
		double zc=0;
		
		b0=zR*ymax-xr->z*ymin;
		int b1=zR-xr->z;
		int t0=zR*xr->z;
		int t1=xr->z*zR;
		int c0=t1*ymax-t0*ymin;
		int c1=t0-t1;

		int b01=zL*ymax-xl->z*ymin;
		int b11=zL-xl->z;
		int t01=zL*xl->z;
		int t11=xl->z*zL;
		int c01=t11*ymax-t01*ymin;
		int c11=t01-t11;
		bool b=false;
		if((v0.p.y==v1.p.y)&&(v1.p.y==v2.p.y))
		{
			int g;
			g=3;
		}
		for(int y=ymin;y<=ymax;y++)
		{
			CCVector mv=(cR-cL)/(xR-xL);
			vc=cL;
			double zv=(zR-zL)/(xR-xL);
			zc=zL;
			
			int b00=zR*xR-zL*xL;
			int b10=zR-zL;
			int t00=zR*zL;
			int t10=zL*zR;
			int c00=t10*xR-t00*xL;
			int c10=t00-t10;

			for (int x = xL; x <= xR; x++)
			{
				if((zc>=-1)&&(zc<=1)&&(!b)) 
				{
				hdc->SetPixel(x,y,vc.toRGB());
				}
				vc+=mv;
				if((b00+b10*x)!=0)
				{
				zc=(c00+c10*x)/(b00+b10*x);
				b=false;
				}
				else
				{
				b=true;
				}
			zc+=zv;
			}
/*			if(y==ymax)
			{
				break;
			}
*/
//			if(((xL==xR)&&(y!=v[1].p.y))||(y==ymax)) break;
				if (y==xl->p.y)
				{
					alphal=(float)(xL-xr->p.x)/(xl->p.y-xr->p.y);
					xL=xl->p.x;
					betal=(cL-xr->c)/(xl->p.y-xr->p.y);
					cL=xl->c;
					zetal=(zL-xr->z)/(xl->p.y-xr->p.y);
					zL=xl->z;

					b01=zL*ymax-xl->z*ymin;
					b11=zL-xl->z;
					t01=zL*xl->z;
					t11=xl->z*zL;
					c01=t11*ymax-t01*ymin;
					c11=t01-t11;
				}
				else if(y==xr->p.y)
				{
					alphar=(float)(xR-xl->p.x)/(xr->p.y-xl->p.y);
					xR=xr->p.x;
					betar=(cR-xl->c)/(xr->p.y-xl->p.y);
					cR=xr->c;
					zetar=(zR-xl->z)/(xr->p.y-xl->p.y);
					zR=xr->z;

					b0=zR*ymax-xr->z*ymin;
					b1=zR-xr->z;
					t0=zR*xr->z;
					t1=xr->z*zR;
					c0=t1*ymax-t0*ymin;
					c1=t0-t1;
				}
				xL += alphal;
				xR += alphar;
				cL += betal;
				cR += betar;
				zL += zetal;
				zR += zetar;

				if((b00+b10*y)!=0)
				{
				zR=(c00+c10*y)/(b00+b10*y);
				b=false;
				}
				else
				{
				b=true;
				}
				if((b01+b11*y)!=0)
				{
				zR=(c01+c11*y)/(b01+b11*y);
				b=false;
				}
				else
				{
				b=true;
				}


//			tc=cR-cL;

			if(xL>xR)
			{
				pointc h=*xl;
				*xl=*xr;
				*xr=h;
				float k=xL;
				xL=xR;
				xR=k;
				k=alphal;
				alphal=alphar;
				alphar=k;

				CCVector kc=betal;
				betal=betar;
				betar=kc;
			
				kc=cL;
				cL=cR;
				cR=kc;

				double kzc=zetal;
				zetal=zetar;
				zetar=kzc;
			
				kzc=zL;
				zL=zR;
				zR=kzc;
			}

		}
/*	}
	else
	if(ymin==v[0].p.y)
	{
		if (v[1].p.x<v[2].p.x)
		{
			xl=v+1;xr=v+2;
		} else
		{
			xl=v+2;xr=v;
		}

		float xL=xl->p.x, xR=xr->p.x,alphal,alphar;
		CCVector cL=xl->c,cR=xr->c,betal,betar;
		if(v[0].p.y==xl->p.y)
		{
			alphal=0;
//		betal=0;
		}else
		{
			alphal=(float)(v[0].p.x-xL)/(v[0].p.y-xl->p.y);
			betal=(v[0].c-cL)/(v[0].p.y-xl->p.y);
		}
	
		if(v[0].p.y==xr->p.y)
		{
			alphar=0;
//		betar=0;
		}else
		{
			alphar=(float)(v[0].p.x-xR)/(v[0].p.y-xr->p.y);
			betar=(v[0].c-cR)/(v[0].p.y-xr->p.y);
		}


		xL=v[0].p.x;
		xR=v[0].p.x;
		cL=v[0].c;
		cR=v[0].c;

		CCVector vc;
		for(int y=ymin;y<=ymax;y++)
		{
			CCVector mv=(cR-cL)/(xR-xL);
			vc=cL;
			for (int x = xL; x <= xR; x++)
			{
				hdc->SetPixel(x,y,vc.toRGB());
				vc+=mv;
			}
			if(y==ymax)
			{
				break;
			}
			if(xL>xR)
			{
				break;
			}

//			if((xL==xR)&&(y!=v[0].p.y)) break;
				if (y==xl->p.y)
				{
					alphal=(float)(xL-xr->p.x)/(xl->p.y-xr->p.y);
					xL=xl->p.x;
					betal=(cL-xr->c)/(xl->p.y-xr->p.y);
					cL=xl->c;
				}
				else if(y==xr->p.y)
				{
					alphar=(float)(xR-xl->p.x)/(xr->p.y-xl->p.y);
					xR=xr->p.x;
					betar=(cR-xl->c)/(xr->p.y-xl->p.y);
					cR=xr->c;
				}
				xL += alphal;
				xR += alphar;
				cL += betal;
				cR += betar;
//			tc=cR-cL;

			if(xL>xR)
			{
				pointc h=*xl;
				*xl=*xr;
				*xr=h;
				float k=xL;
				xL=xR;
				xR=k;
				k=alphal;
				alphal=alphar;
				alphar=k;

				CCVector kc=betal;
				betal=betar;
				betar=kc;
			
				kc=cL;
				cL=cR;
				cR=kc;

			}

		}
	}else
	if(ymin==v[2].p.y)
	{

		if (v[0].p.x<v[1].p.x)
		{
			xl=v;xr=v+1;
		} else
		{
			xl=v+1;xr=v;
		}
		float xL=xl->p.x, xR=xr->p.x;
		float alphal;
		CCVector cL=xl->c,cR=xr->c,betal,betar;

		if(v[2].p.y==xl->p.y)
		{
			alphal=0;
		}else
		{
			alphal=(float)(v[2].p.x-xL)/(v[2].p.y-xl->p.y);
			betal=(v[2].c-cL)/(v[2].p.y-xl->p.y);
		}
		float alphar;
		if(v[2].p.y==xr->p.y)
		{
			alphar=0;
		}else
		{
			alphar=(float)(v[2].p.x-xR)/(v[2].p.y-xr->p.y);
			betar=(v[2].c-cR)/(v[2].p.y-xr->p.y);
		}
		xL=v[2].p.x;
		xR=v[2].p.x;
		cL=v[2].c;
		cR=v[2].c;

		CCVector vc;
		for(int y=ymin;y<=ymax;y++)
		{
			CCVector mv=(cR-cL)/(xR-xL);
			vc=cL;
			for (int x = xL; x <= xR; x++)
			{
				hdc->SetPixel(x,y,vc.toRGB());
				vc+=mv;
			}
			if(y==ymax)
			{
				break;
			}
			if(xL>xR)
			{
				break;
			}
//			if(((xL==xR)&&(y!=v[2].p.y))||(y==ymax)) break;
			if (y==xl->p.y)
			{
				alphal=(float)(xL-xr->p.x)/(xl->p.y-xr->p.y);
				xL=xl->p.x;
				betal=(cL-xr->c)/(xl->p.y-xr->p.y);
				cL=xl->c;
			}
			else if(y==xr->p.y)
			{
				alphar=(float)(xR-xl->p.x)/(xr->p.y-xl->p.y);
				xR=xr->p.x;
				betar=(cR-xl->c)/(xr->p.y-xl->p.y);
				cR=xr->c;
			}
			xL += alphal;
			xR += alphar;
			cL += betal;
			cR += betar;
			if(xL>xR)
			{
				pointc h=*xl;
				*xl=*xr;
				*xr=h;
				float k=xL;
				xL=xR;
				xR=k;
				k=alphal;
				alphal=alphar;
				alphar=k;

				CCVector kc=betal;
				betal=betar;
				betar=kc;
			
				kc=cL;
				cL=cR;
				cR=kc;
			}
		}*/

//}
//	hdc->Polygon(v,4);
}


CVector CTriangle::getcent()
{
	updatecent();
	return cent;
}

void CTriangle::updatecent()
{
	cent=((CVector)*sit+(CVector)*sjt+(CVector)*skt)/3;
}

void CTriangle::DrawTriangleFill(CDC *hdc,CVector loc[2],CCVector lit[6])
{
	CEdge *edge1=mesh->Edge(eit);
	CEdge *edge2=mesh->Edge(ejt);
	CEdge *edge3=mesh->Edge(ekt);

	double x1=CPoint(CVector(*edge1->Start())).x;
	double y1=CPoint(CVector(*edge1->Start())).y;
	double x2=CPoint(CVector(*edge2->Start())).x;
	double y2=CPoint(CVector(*edge2->Start())).y;
	double x3=CPoint(CVector(*edge3->Start())).x;
	double y3=CPoint(CVector(*edge3->Start())).y;

	double dist1 = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	double dist2 = sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
	double dist3 = sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
	double s = (dist1+dist2+dist3)/2;
	double h = 2 * sqrt(s * (s-dist1) * (s-dist2) * (s - dist3));
	double px1,px2,py1,py2,dx1,dx2,dy1,dy2;
	int j;

	if(dist1>dist2)
	{
		if(dist1>dist3)
		{//dist1 greatest
			h=h*2/dist1;
			px1=x1;
			px2=x2;
			py1=y1;
			py2=y2;

			dx1 = (x1-x2)/h;
			dx2 = (x1-x3)/h;
			dy1 = (y1-y2)/h;
			dy2 = (y1-y3)/h;
		}
		else
		{//dist3 greatest
			h=h*2/dist3;
			px1=x2;
			px2=x3;
			py1=y2;
			py2=y3;

			dx1 = (x3-x1)/h;
			dx2 = (x3-x2)/h;
			dy1 = (y3-y1)/h;
			dy2 = (y3-y2)/h;
		}
	}
	else
	{
		if(dist2>dist3)
		{//dist2 greatest
			h=h*2/dist2;
			px1=x1;
			px2=x3;
			py1=y1;
			py2=y3;

			dx1 = (x2-x1)/h;
			dx2 = (x2-x3)/h;
			dy1 = (y2-y1)/h;
			dy2 = (y2-y3)/h;
		}
		else
		{//dist3 greatest
			h=h*2/dist3;
			px1=x2;
			px2=x3;
			py1=y2;
			py2=y3;

			dx1 = (x3-x1)/h;
			dx2 = (x3-x2)/h;
			dy1 = (y3-y1)/h;
			dy2 = (y3-y2)/h;
		}
	}

	for(j=0;j<h;j++)
	{
		DrawLine(hdc,px1,py1,px2,py2,RGB(0,0,0));
		px1+=dx1;
		px2+=dx2;
		py1+=dy1;
		py2+=dy2;
	}
}

void CTriangle::DrawLine(CDC* hdc,double x,double y,double x2,double y2,COLORREF c)
{
	double dist = sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
	double dx = (x2-x)/dist;
	double dy = (y2-y)/dist;
	for(int j=0;j<dist;j++)
	{
		hdc->SetPixel(x,y,c);
		x+=dx;
		y+=dy;
	}
}

void CTriangle::Draw_Top_Tri(HDC hdc,BYTE* bits,int bheight,int bwidth,vertex v1,vertex v2, vertex v3,col* mytext,int pwidth,int pheight,light *l)
{

	//this function draws a triangle that has a flat top
	float dx_right,//the dx/dy ratio of the right edge of line
	dx_left,//the dx/dy ratio of the left edge of line
	xs,xe,//the starting and ending points of the edges
	height;//the height of the triangle
	int temp_x,//used during sorting as temps
	temp_y,
	right,//used by clipping
	left;
	float temp_u,temp_v,temp_r,temp_g,temp_b,u_left,u_right,v_left,v_right,\
		   r_left,g_left,b_left,r_right,g_right,b_right;
	vertex temp;
	//destination address of next scanline
	UCHAR *dest_addr =NULL;

	double alpha=l->alpha;	
	CVector view=l->view,lsou=l->lsou;//view.viewi();lsou.viewi();
	CCVector S_spec=l->S_spec,M_spec=l->M_spec,S_diff=l->S_diff,M_diff=l->M_diff,\
			G_amb=l->G_amb,M_amb=l->M_amb;

	CVector po=(view-v1)/(view.absc(view-v1));
	CVector l1=(lsou-v1)/(view.absc(lsou-v1));
	CVector n=v1.n;//-(CVector)*edge3->Start())*((CVector)*edge1->Start()-(CVector)*edge2->Start());
	n=n/view.absc(n);
	double j=n.dot(l1);

	CVector r=n*(2*(n.dot(l1)))-l1;
		 
	double b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	CCVector clit1=(S_spec*b0)*M_spec;
	CCVector clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	CCVector clit=clit1+clit2+G_amb*M_amb;
	v1.r=GetRValue(clit.toRGB());
	v1.g=GetGValue(clit.toRGB());
	v1.b=GetBValue(clit.toRGB());

	po=(view-v2)/(view.absc(view-v2));
	l1=(lsou-v2)/(view.absc(lsou-v2));
	n=v2.n;//((CVector)*edge2->Start()-(CVector)*edge1->Start())*((CVector)*edge2->Start()-(CVector)*edge3->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l1)))-l1;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
	v2.r=GetRValue(clit.toRGB());
	v2.g=GetGValue(clit.toRGB());
	v2.b=GetBValue(clit.toRGB());

	po=(view-v3)/(view.absc(view-v3));
	l1=(lsou-v3)/(view.absc(lsou-v3));
	n=v3.n;//((CVector)*edge3->Start()-(CVector)*edge2->Start())*((CVector)*edge3->Start()-(CVector)*edge1->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l1)))-l1;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
	v3.r=GetRValue(clit.toRGB());
	v3.g=GetGValue(clit.toRGB());
	v3.b=GetBValue(clit.toRGB());
	
	
	
	//test order of x1 and x2
	if (v2.p.x<v1.p.x)//x2 <x1)
	{
	temp=v2;
	v2=v1;
	v1=temp;
	}//end if swap
	//compute delta ’s
	height =-v3.p.y+v1.p.y;//y3-y1;
	dx_left =(v3.p.x-v1.p.x)/height;//(x3-x1)/height;
	dx_right =(v3.p.x-v2.p.x)/height;//(x3-x2)/height;

	r_left=(v3.r-v1.r)/height;
	g_left=(v3.g-v1.g)/height;
	b_left=(v3.b-v1.b)/height;
	v_left =(v3.v-v1.v)/height;
	u_left =(v3.u-v1.u)/height;
	
	v_right =(v3.v-v2.v)/height;
	u_right =(v3.u-v2.u)/height;
	r_right =(v3.r-v2.r)/height;
	g_right =(v3.g-v2.g)/height;
	b_right =(v3.b-v2.b)/height;
	float dv=v_left;//uleft;
	double vt;

	//set starting points
	xs =(float)v1.p.x;//x1;
	float us=v1.u;
	float vs=v1.v;
	float rs=v1.r;
	float gs=v1.g;
	float bs=v1.b;
//	u_right=u1;
	xe =(float)v2.p.x;//(float)x2+(float)0.5;
	float ue=v2.u;
	float ve=v2.v;
	float re=v2.r;
	float ge=v2.g;
	float be=v2.b;
//	u_left=u2;

	//draw the triangle
	if(v1.p.y<0) v1.p.y=0;
	if(v3.p.y<0) v3.p.y=0;
	if(v1.p.y>=bheight) v1.p.y=bheight-1;
	if(v3.p.y>=bheight) v3.p.y=bheight-1;
	for (temp_y=v1.p.y;temp_y>v3.p.y;temp_y--)//y1;temp_y<=y3;temp_y++)
	{

		float uleft=us;
		float vleft=vs;
		float rleft=rs;
		float gleft=gs;
		float bleft=bs;
			int r,g,b;

		if(xe!=xs)
		{
			float du=(float)(ue-us)/(xe-xs);
			float dv=(float)(ve-vs)/(xe-xs);
			float dr=(float)(re-rs)/(xe-xs);
			float dg=(float)(ge-gs)/(xe-xs);
			float db=(float)(be-bs)/(xe-xs);

			int xxs=floor(xs);
			int xxe=floor(xe);

/*			float ilt=xs-xxs;
	
			du-=du*ilt;
			dv-=dv*ilt;
			dr-=dr*ilt;
			dg-=dg*ilt;
			db-=db*ilt;
*/
			float ap=1;
			if(xxs<0) xxs=0;
			if(xxe<0) xxe=0;
			if(xxs>=bwidth) xxs=bwidth-1;
			if(xxe>=bwidth) xxe=bwidth-1;

			for(int x=xxs;x<xxe;x++)
			{
			
				if(mytext==NULL)
				{
/*				COLORREF back=GetPixel(hdc,x,temp_y);

				int br1=	GetRValue(back);
				int bg1=	GetGValue(back);
				int bb1=	GetBValue(back);
*/
				int bb=bits[(temp_y*bwidth+x)*4+0];
				int gb=bits[(temp_y*bwidth+x)*4+1];
				int rb=bits[(temp_y*bwidth+x)*4+2];
				
				r=(1-alpha)*rb+alpha*rleft;
				g=(1-alpha)*gb+alpha*gleft;
				b=(1-alpha)*bb+alpha*bleft;
/*				r=(1-alpha)*br1+alpha*rleft;
				g=(1-alpha)*bg1+alpha*gleft;
				b=(1-alpha)*bb1+alpha*bleft;
*/				}else
				{
				int yt=__max(floor((pheight-1)*vleft),0)*pwidth+floor(pwidth*uleft);
				if(yt<0) yt=0;
		//		yt=__min(yt,pwidth*pheight);
		//		if(yt>0)
		//		{

//				COLORREF back=GetPixel(hdc,x,temp_y);
				int bb=bits[(temp_y*bwidth+x)*4+0];
				int gb=bits[(temp_y*bwidth+x)*4+1];
				int rb=bits[(temp_y*bwidth+x)*4+2];

				r=(1-alpha)*rb+alpha*mytext[yt].r;
				g=(1-alpha)*gb+alpha*mytext[yt].g;
				b=(1-alpha)*bb+alpha*mytext[yt].b;
/*				r=(1-alpha)*GetRValue(back)+alpha*mytext[yt].r;
				g=(1-alpha)*GetGValue(back)+alpha*mytext[yt].g;
				b=(1-alpha)*GetBValue(back)+alpha*mytext[yt].b;
*/		//		}
				}
//			SetPixelV(hdc,x,temp_y,RGB(r,g,b));
			bits[(temp_y*bwidth+x)*4+0]=b;
			bits[(temp_y*bwidth+x)*4+1]=g;
			bits[(temp_y*bwidth+x)*4+2]=r;
			bits[(temp_y*bwidth+x)*4+3]=0;

			uleft+=du;
			vleft+=dv;
			rleft+=dr;
			gleft+=dg;
			bleft+=db;

			vleft=__min(vleft,1);
			uleft=__min(uleft,1);
			}
		}
		else
		{/*
		if(mytext==NULL)
		{
		COLORREF back=GetPixel(hdc,xe,temp_y);

		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*rleft;
		g=(1-alpha)*bg1+alpha*gleft;
		b=(1-alpha)*bb1+alpha*bleft;
		}else
		{
		int yt=__max(floor((pheight-1)*vleft),0)*pwidth+__max(floor(pwidth*uleft),0);

		COLORREF back=GetPixel(hdc,xe,temp_y);
		int br=GetRValue(back),bg=GetGValue(back),bb=GetBValue(back);
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;
		}
		SetPixelV(hdc,xe,temp_y,RGB(r,g,b));

*/
		}


	//adjust starting point and ending point
	xs+=dx_left;
	us+=u_left;
	vs+=v_left;
	rs+=r_left;
	gs+=g_left;
	bs+=b_left;


	xe+=dx_right;
	ue+=u_right;
	ve+=v_right;
	re+=r_right;
	ge+=g_right;
	be+=b_right;
	}//end for
}//end Draw_Top_Tri


void CTriangle::Draw_Bottom_Tri(HDC hdc,BYTE* bits,int bheight,int bwidth,vertex v1,vertex v2, vertex v3,col* mytext,int pwidth,int pheight,light *l
)
{
	//this function draws a triangle that has a flat bottom
	float dx_right,//the dx/dy ratio of the right edge of line
	dx_left,//the dx/dy ratio of the left edge of line
	xs,xe,//the starting and ending points of the edges
	height;//the height of the triangle
	int temp_x,//used during sorting as temps
	temp_y,
	right,//used by clipping
	left;
	float temp_u,temp_v,temp_r,temp_g,temp_b,u_left,u_right,v_left,v_right,\
		   r_left,g_left,b_left,r_right,g_right,b_right;
	vertex temp;
//destination address of next scanline
UCHAR *dest_addr;

	double alpha=l->alpha;
	CVector view=l->view,lsou=l->lsou;
	CCVector S_spec=l->S_spec,M_spec=l->M_spec,S_diff=l->S_diff,M_diff=l->M_diff,\
			G_amb=l->G_amb,M_amb=l->M_amb;

	CVector po=(view-v1)/(view.absc(view-v1));
	CVector l1=(lsou-v1)/(view.absc(lsou-v1));
	CVector n=v1.n;//-(CVector)*edge3->Start())*((CVector)*edge1->Start()-(CVector)*edge2->Start());
	n=n/view.absc(n);
	double j=n.dot(l1);

	CVector r=n*(2*(n.dot(l1)))-l1;
		 
	double b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	CCVector clit1=(S_spec*b0)*M_spec;
	CCVector clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	CCVector clit=clit1+clit2+G_amb*M_amb;
	v1.r=GetRValue(clit.toRGB());
	v1.g=GetGValue(clit.toRGB());
	v1.b=GetBValue(clit.toRGB());

	po=(view-v2)/(view.absc(view-v2));
	l1=(lsou-v2)/(view.absc(lsou-v2));
	n=v2.n;//((CVector)*edge2->Start()-(CVector)*edge1->Start())*((CVector)*edge2->Start()-(CVector)*edge3->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l1)))-l1;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
	v2.r=GetRValue(clit.toRGB());
	v2.g=GetGValue(clit.toRGB());
	v2.b=GetBValue(clit.toRGB());

	po=(view-v3)/(view.absc(view-v3));
	l1=(lsou-v3)/(view.absc(lsou-v3));
	n=v3.n;//((CVector)*edge3->Start()-(CVector)*edge2->Start())*((CVector)*edge3->Start()-(CVector)*edge1->Start());
	n=n/view.absc(n);
	r=n*(2*(n.dot(l1)))-l1;
		 
	b0=pow(max((po.x*r.x+po.y*r.y+po.z*r.z),0),2);	 	
	clit1=(S_spec*b0)*M_spec;
	clit2=(S_diff*max(n.dot(l1),0))*M_diff;
	clit=clit1+clit2+G_amb*M_amb;
	v3.r=GetRValue(clit.toRGB());
	v3.g=GetGValue(clit.toRGB());
	v3.b=GetBValue(clit.toRGB());




//test order of x1 and x2
if (v3.p.x<v2.p.x)//x3 <x2)
{
	temp=v2;
	v2=v3;
	v3=temp;
}//end if swap
	//compute delta ’s
	height =-v3.p.y+v1.p.y;//y3-y1;
	dx_left =(v2.p.x-v1.p.x)/height;//x2-x1)/height;
	dx_right =(v3.p.x-v1.p.x)/height;//(x3-x1)/height;
	
	r_left=(v2.r-v1.r)/height;
	g_left=(v2.g-v1.g)/height;
	b_left=(v2.b-v1.b)/height;
	r_right =(v3.r-v1.r)/height;
	g_right =(v3.g-v1.g)/height;
	b_right =(v3.b-v1.b)/height;

	u_left =(v2.u-v1.u)/height;//u2-u1)/height;
	u_right =(v3.u-v1.u)/height;//(u3-u1)/height;
	v_left =(v2.v-v1.v)/height;//(v2-v1)/height;
	v_right =(v3.v-v1.v)/height;//(v3-v1)/height;

	float dv=v_left;//uleft;
	double vt;

//set starting points
xs =v1.p.x;//(float)x1;
xe =v1.p.x;//(float)x1;//+(float)0.5;
float us=v1.u;
float rs=v1.r;
float gs=v1.g;
float bs=v1.b;

float ue=v1.u;
float re=v1.r;
float ge=v1.g;
float be=v1.b;

float vs=v1.v;
float ve=v1.v;

//draw the triangle
//	int g=ceil(v3.p.y);
if(v1.p.y<0) v1.p.y=0;
if(v3.p.y<0) v3.p.y=0;
if(v1.p.y>=bheight) v1.p.y=bheight-1;
if(v3.p.y>=bheight) v3.p.y=bheight-1;

for (temp_y=v1.p.y;temp_y>v3.p.y;temp_y--)
{

	float uleft=us;
	float vleft=vs;
	float rleft=rs;
	float gleft=gs;
	float bleft=bs;
	int r,g,b;
	if(xe!=xs)
	{

	float du=(float)(ue-us)/(xe-xs);
	float dv=(float)(ve-vs)/(xe-xs);
	float dr=(float)(re-rs)/(xe-xs);
	float dg=(float)(ge-gs)/(xe-xs);
	float db=(float)(be-bs)/(xe-xs);
	
	int xxs=floor(xs);
	int xxe=floor(xe);

/*	float ilt=xs-xxs;

	du-=du*ilt;
	dv-=dv*ilt;
	dr-=dr*ilt;
	dg-=dg*ilt;
	db-=db*ilt;
*/	
	float ap=1;
	if(xxs<0) xxs=0;
	if(xxe<0) xxe=0;
	if(xxs>=bwidth) xxs=bwidth-1;
	if(xxe>=bwidth) xxe=bwidth-1;

	for(int x=xxs;x<xxe;x++)
	{
		if(mytext==NULL)
		{
/*		COLORREF back=GetPixel(hdc,x,temp_y);

		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*rleft;
		g=(1-alpha)*bg1+alpha*gleft;
		b=(1-alpha)*bb1+alpha*bleft;
*/
		int bb=bits[(temp_y*bwidth+x)*4+0];
		int gb=bits[(temp_y*bwidth+x)*4+1];
		int rb=bits[(temp_y*bwidth+x)*4+2];
		
		r=(1-alpha)*rb+alpha*rleft;
		g=(1-alpha)*gb+alpha*gleft;
		b=(1-alpha)*bb+alpha*bleft;
		
		
		}else
		{
		int yt=__max(floor((pheight-1)*vleft),0)*pwidth+__max(floor(pwidth*uleft),0);
//		yt=__min(yt,pwidth*pheight);
		if((yt>pwidth*pheight)||(yt<0))
		{
			int yuo=0;
		}
/*		COLORREF back=GetPixel(hdc,x,temp_y);
		int br=GetRValue(back),bg=GetGValue(back),bb=GetBValue(back);
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;
*/
		int bb=bits[(temp_y*bwidth+x)*4+0];
		int gb=bits[(temp_y*bwidth+x)*4+1];
		int rb=bits[(temp_y*bwidth+x)*4+2];

		r=(1-alpha)*rb+alpha*mytext[yt].r;
		g=(1-alpha)*gb+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;
		}
//		SetPixelV(hdc,x,temp_y,RGB(r,g,b));
		bits[(temp_y*bwidth+x)*4+0]=b;
		bits[(temp_y*bwidth+x)*4+1]=g;
		bits[(temp_y*bwidth+x)*4+2]=r;
		bits[(temp_y*bwidth+x)*4+3]=0;
		
		uleft+=du;
		vleft+=dv;
		rleft+=dr;
		gleft+=dg;
		bleft+=db;
		vleft=__min(vleft,1);
		uleft=__min(uleft,1);
	}
	}
	else
	{
		if(mytext==NULL)
		{
		COLORREF back=GetPixel(hdc,xe,temp_y);

		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*rleft;
		g=(1-alpha)*bg1+alpha*gleft;
		b=(1-alpha)*bb1+alpha*bleft;
		}else
		{
		int yt=__max(floor((pheight-1)*vleft),0)*pwidth+__max(floor(pwidth*uleft),0);

		COLORREF back=GetPixel(hdc,xe,temp_y);
		int br=GetRValue(back),bg=GetGValue(back),bb=GetBValue(back);
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;
		}
		SetPixelV(hdc,xe,temp_y,RGB(r,g,b));

	}
	//adjust starting point and ending point
	xs+=dx_left;
	us+=u_left;
	vs+=v_left;
	rs+=r_left;
	gs+=g_left;
	bs+=b_left;

	xe+=dx_right;
	ue+=u_right;
	ve+=v_right;
	re+=r_right;
	ge+=g_right;
	be+=b_right;

}//end for

}//end Draw_Bottom_Tri
void CTriangle::Draw_Triangle_2D(HDC hdc,BYTE* bits,int bheight,int bwidth,col* mytext,int pwidth,int pheight,light *l)
{
	CVertex* vert1=sit;
	CVertex* vert2=sjt;
	CVertex* vert3=skt;
	CVertex *lkj=new CVertex;

	CPoint p1(vert1->p);
//	LPtoDP(hdc,&p1,1);

	float u1=vert1->un;
	float v1=vert1->vn;
	vertex vv1(vert1->v,vert1->n,p1,u1,v1);
	CPoint p2(vert2->p);

//	LPtoDP(hdc,&p2,1);
	float u2=vert2->un;
	float v2=vert2->vn;
	vertex vv2(vert2->v,vert2->n,p2,u2,v2);
	CPoint p3(vert3->p);

//	LPtoDP(hdc,&p3,1);
	float u3=vert3->un;
	float v3=vert3->vn;
	vertex vv3(vert3->v,vert3->n,p3,u3,v3);



	//this function draws a triangle on the destination buffer
	//it decomposes all triangles into a pair of flat top,flat bottom
	int temp_x,//used for sorting
	temp_y,
	new_x;
	vertex temp;
	float temp_u,temp_v;

//test for h lines and v lines
if ((vv1.p.x==vv2.p.x &&vv2.p.x==vv3.p.x)||(vv1.p.y==vv2.p.y &&vv2.p.y==vv3.p.y))
{
return;
}
//sort p1,p2,p3 in ascending y order
if (vv2.p.y>vv1.p.y)
{
	temp=vv2;
	vv2=vv1;
	vv1=temp;
}//end if
//now we know that p1 and p2 are in order
if (vv3.p.y>vv1.p.y)//y3<y1)
{
	temp=vv3;
	vv3=vv1;
	vv1=temp;
}//end if
//finally test y3 against y2
if (vv3.p.y>vv2.p.y)//y3<y2)
{
	temp=vv3;
	vv3=vv2;
	vv2=temp;
}//end if

int o=SetMapMode(hdc,MM_TEXT);

//test if top of triangle is flat
if (vv1.p.y==vv2.p.y)
{
	Draw_Top_Tri(hdc,bits,bheight,bwidth,vv1,vv2,vv3,mytext,pwidth,pheight,l);
}//end if
else
if (vv2.p.y==vv3.p.y)
{
	Draw_Bottom_Tri(hdc,bits,bheight,bwidth,vv1,vv2,vv3,mytext,pwidth,pheight,l);
}//end if bottom is flat
else
{
	//general triangle that ’s needs to be broken up along long edge
	temp=vv2;
	temp.p.x=vv1.p.x+(int)(0.5+(float)(vv2.p.y-vv1.p.y)*(float)(vv3.p.x-vv1.p.x)/(float)(vv3.p.y-vv1.p.y));
//	new_x =x1 +(int)(0.5+(float)(y2-y1)*(float)(x3-x1)/(float)(y3-y1));
/*	temp.u=(vv1.u*temp.p.x)/vv1.p.x;
	if(vv1.u==0) temp.u=(vv2.u*temp.p.x)/vv2.p.x;
	if(vv2.u==0) temp.u=(vv3.u*temp.p.x)/vv3.p.x;*/
	temp.u=((vv1.u-vv3.u)/(vv1.p.y-vv3.p.y))*(vv1.p.y-vv2.p.y)+vv3.u;
	temp.v=((vv1.v-vv3.v)/(vv1.p.y-vv3.p.y))*(vv1.p.y-vv2.p.y)+vv3.v;

/*
	double ux=(u1*new_x)/x1;
	if(u1==0) ux=(u2*new_x)/x2;
	if(u2==0) ux=(u3*new_x)/x3;
*/	
	//draw each sub-triangle
	Draw_Bottom_Tri(hdc,bits,bheight,bwidth,vv1,temp,vv2,/*x1,y1,new_x,y2,x2,y2,u1,v1,ux,v2,u2,v2,*/mytext,pwidth,pheight,l);
	Draw_Top_Tri(hdc,bits,bheight,bwidth,vv2,temp,vv3,/*x2,y2,new_x,y2,x3,y3,u1,v1,ux,v2,u3,v3,*/mytext,pwidth,pheight,l);
}//end else
	SetMapMode(hdc,o);
}//end Draw_Triangle_2D

void CTriangle::savefile(CFile &file)
{
	n.savefile(file);
	file.Write(sit,sizeof(sit));
	file.Write(sjt,sizeof(sit));
	file.Write(skt,sizeof(sit));
	
//	file.Write(*eit,sizeof(sit));
//	file.Write(*ejt,sizeof(sit));
//	file.Write(*ekt,sizeof(sit));
}

void CTriangle::openfile(CFile &file)
{
	n.openfile(file);
	int i,j,k;
	file.Read(&i,sizeof(sit));
	file.Read(&j,sizeof(sit));
	file.Read(&k,sizeof(sit));
	new CTriangle(mesh->Vertex(i),mesh->Vertex(j),mesh->Vertex(k));
/*	file.Read(sit,sizeof(sit));
	file.Read(sjt,sizeof(sjt));
	file.Read(skt,sizeof(skt));

	file.Read(eit,sizeof(sit));
	file.Read(ejt,sizeof(sjt));
	file.Read(ekt,sizeof(skt));
*/
}
LONG CTriangle::Readfile(CFile &file)
{
	LONG g;
	n.Readfile(file);
	file.Seek(sizeof(sit),CFile::current);
	file.Seek(sizeof(sjt),CFile::current);
	file.Seek(sizeof(skt),CFile::current);

	file.Seek(sizeof(eit),CFile::current);
	file.Seek(sizeof(ejt),CFile::current);
	g=file.Seek(sizeof(ekt),CFile::current);
	return g;
}

bool CTriangle::isDegenerate(HDC hdc)
{
	CVertex* vertex1=sit;
	CVertex* vertex2=sjt;
	CVertex* vertex3=skt;

	CVector v1=vertex1->v;
	CPoint p1=v1;
	CVector v2=vertex2->v;
	CPoint p2=v2;
	CVector v3=vertex3->v;
	CPoint p3=v3;
	LPtoDP(hdc,&p1,1);
	LPtoDP(hdc,&p2,1);
	LPtoDP(hdc,&p3,1);
	CVector pv1(p1.x,p1.y);
	CVector pv2(p2.x,p2.y);
	CVector pv3(p3.x,p3.y);

	vertex1->p=p1;
	vertex2->p=p2;
	vertex3->p=p3;

	vertex1->z=(vertex1->v.getDepth()).z;
	vertex2->z=(vertex2->v.getDepth()).z;
	vertex3->z=(vertex3->v.getDepth()).z;

	bool b=false;
/*	if(absc(CVector(pv1,pv2))<1)
	{
		vertex1->p=p1;
		vertex2->p=p1;
		b=true;
	}
	if(absc(CVector(pv1,pv3))<1)
	{
		vertex1->p=p1;
		vertex3->p=p1;
//		vertex1->p=vertex3->p=p1;
		b=true;
	}
	if(absc(CVector(pv2,pv3))<1)
	{
		vertex3->p=p2;
		vertex2->p=p2;
//		vertex2->p=vertex3->p=p2;
		b=true;
	}
	if(b)
	{
		int hg=0;
	}
*/
	return b;
}

int CTriangle::findvertex(CVertex &v)
{
	if(v.sit==sit->sit) return 1;
	if(v.sit==sjt->sit) return 2;
	if(v.sit==skt->sit) return 3;
	return -1;

}


	// this structure is used internally to store
	// rasterization stuff as slopes, initial values and etc.

	typedef struct {
		int		left;				// 0 if major edge is left, else 1
		float	invDeltaY[3],		// inversed edge delta y
				slopeX[2],			// x slope along the edges
				slopeZ[2],			// z slope along the edges
				z[2],
				x[2];				// x coordinate
		col 	slopeCd[2],			// color slope
				cd[2];				// color values
		col 	slopeCs[2],			// color slope
				cs[2];				// color values
		float 	slopeU[2],slopeV[2],			// parameter slope
				u[2],v[2];				// parameter values
	} ScanConvData;

	// this structure is passed to the scanline drawing routine
	// and actually the start/ending values, height pos and etc

	typedef struct {
		long	y;					// y position of the scanline
		float	x[2];				// x start and end positions
		float	z[2];				// z start and end positions
		col 	cd[2];				// r, g, b, a color start and end positions
		col 	cs[2];				// r, g, b, a color start and end positions
		float   u[2],v[2];			// u,v parameters start and end
	} Scanline;

	ScanConvData	scan;			// used internally in the scanconverting process
	Scanline		scanline;		// information about the current scanline

/* TESTING of TRIANGLE*/
#define FLT_ERROR		1e-4

#define COPY_RGBA(dst, src) {			\
	dst.r = src.r;						\
	dst.g = src.g;						\
	dst.b = src.b;						\
	dst.a = src.a;						\
}
typedef BYTE dword;

void scanline32(Scanline *data,\
				HDC hdc,BYTE* bits,\
				int bheight,int bwidth,col* mytext,int pwidth,int pheight,light *l)
 {
/*	double alpha=l->alpha;
	dword	*bitsFrame;
	float	invDeltaX, 
			sub;
	col		slopeC;
	long	xe, xs;
	dword	r, g, b;
	int		i;

	// we cannot render without a frame buffer, aight ?


	// apply top-left fill-convention to scanline

	xs = ceil(data->x[0]);
	xe = ceil(data->x[1]) - 1;

	if(xe < xs)
		return;

	// calculate slopes

	invDeltaX = data->x[1] - data->x[0];

	if(invDeltaX < FLT_ERROR) invDeltaX = 1.0f;
	else invDeltaX = 1.0f / invDeltaX; 

	sub = (float)xs - data->x[0];

	slopeC.r = (data->c[1].r - data->c[0].r) * invDeltaX;
	slopeC.g = (data->c[1].g - data->c[0].g) * invDeltaX;
	slopeC.b = (data->c[1].b - data->c[0].b) * invDeltaX;

//	data->c[0].r += slopeC.r * sub;
//	data->c[0].g += slopeC.g * sub;
//	data->c[0].b += slopeC.b * sub;


	// rasterize line
	if(xs<0) xs=0;
	if(xe<0) xe=0;
	if(xs>=bwidth) xs=bwidth-1;
	if(xe>=bwidth) xe=bwidth-1;

	for(i = xs; i <= xe; i++) {
		r = (dword) (data->c[0].r);
		g = (dword) (data->c[0].g);
		b = (dword) (data->c[0].b);

//		*bitsFrame++ = 0xFF000000 | (r << 16) | (g << 8) | b;
		int bb=bits[(data->y*bwidth+i)*4+0];
		int gb=bits[(data->y*bwidth+i)*4+1];
		int rb=bits[(data->y*bwidth+i)*4+2];
		
		r=(1-alpha)*rb+alpha*r;
		g=(1-alpha)*gb+alpha*g;
		b=(1-alpha)*bb+alpha*b;

		bits[(data->y*bwidth+i)*4+0]=b;
		bits[(data->y*bwidth+i)*4+1]=g;
		bits[(data->y*bwidth+i)*4+2]=r;
		bits[(data->y*bwidth+i)*4+3]=0;


		data->c[0].r += slopeC.r;
		data->c[0].g += slopeC.g;
		data->c[0].b += slopeC.b;
	}*/
}


		float	xe, xs,xxe,xxs;
		int	r, g, b;
		int		i;
		float rss,rsd;//=scan.c[scan.left].r;
		float gss,gsd;//=scan.c[scan.left].g;
		float bss,bsd;//=scan.c[scan.left].b;
		float res,red;//=scan.c[!scan.left].r;
		float ges,ged;//=scan.c[!scan.left].g;
		float bes,bed;//=scan.c[!scan.left].b;
		float	invDeltaX;
		float du,us,ue;
		float dv,vs,ve;
		float dz,zs,ze;
		float drs,dsrs,drd,dsrd;//=scan.slopeC[scan.left].r,der=scan.slopeC[!scan.left].r;
		float dgs,dsgs,dgd,dsgd;//=scan.slopeC[scan.left].g,deg=scan.slopeC[!scan.left].g;
		float dbs,dsbs,dbd,dsbd;//=scan.slopeC[scan.left].b,deb=scan.slopeC[!scan.left].b;
		float dsx;//=scan.slopeX[scan.left],dex=scan.slopeX[!scan.left];

		float rlefts,glefts,blefts,rrights,grights,brights;
		float rleftd,gleftd,bleftd,rrightd,grightd,brightd;
		float uleft,vleft,uright,vright;
		float zleft,zright;
		int bb;
		int gb;
		int rb;
		int yt;
        float jb,jr,jg;


void CTriangle::rasterizeTriangle(HDC hdc,BYTE* bits,float* zbuffer,\
					   int bheight,int bwidth,col* mytext1,int pwidth,int pheight,light *l)
 {
	Point	sp[3], temp;
	float	v1[2], v2[2], sub;
	long	yStart, yEnd;
	int		i;
	int bpp=pwidth;

/*	if((vertex1->z<0)&&(vertex2->z<0)&&(vertex3->z<0)) 
	{
		return;
	}
*/
	CVertex* vertex1=sit;
	CVertex* vertex2=sjt;
	CVertex* vertex3=skt;

	CPoint po1(vertex1->p);
	float u1=vertex1->un;
	float vo1=vertex1->vn;
//	vertex vv1(vertex1->v,vertex1->n,po1,u1,vo1);

	CPoint po2(vertex2->p);
	float u2=vertex2->un;
	float vo2=vertex2->vn;
//	vertex vv2(vertex2->v,vertex2->n,po2,u2,vo2);

	CPoint po3(vertex3->p);
	float u3=vertex3->un;
	float v3=vertex3->vn;
//	vertex vv3(vertex3->v,vertex3->n,po3,u3,v3);

	Point p1,p2,p3;
	sp[0].pos=vertex1->v;
	sp[0].n=vertex1->n;
	sp[0].u=vertex1->un;
	sp[0].v=vertex1->vn;
//	if(vertex1->z!=0) 
//		p1.z=(float)1/vertex1->z;
//	else
//		p1.z=0;
	sp[0].z=vertex1->z;
//	p1.z=(float)1/vert1->z;
	sp[0].scr[0]=vertex1->p.x;
	sp[0].scr[1]=vertex1->p.y;

	sp[1].pos=vertex2->v;
	sp[1].n=vertex2->n;
	sp[1].u=vertex2->un;
	sp[1].v=vertex2->vn;
//	if(vertex2->z!=0) 
//		p2.z=(float)1/vertex2->z;
//	else
//		p2.z=0;
//	p2.z=(float)1/vert2->z;
	sp[1].z=vertex2->z;
	sp[1].scr[0]=vertex2->p.x;
	sp[1].scr[1]=vertex2->p.y;

	sp[2].pos=vertex3->v;
	sp[2].n=vertex3->n;
	sp[2].u=vertex3->un;
	sp[2].v=vertex3->vn;
//	if(vertex3->z!=0) 
//		p3.z=(float)1/vertex3->z;
//	else
//		p3.z=0;
	sp[2].z=vertex3->z;

	

	sp[2].scr[0]=vertex3->p.x;
	sp[2].scr[1]=vertex3->p.y;

	double alpha=mesh->s_light->alpha;
	double mdiffr=mesh->s_light->M_diff.r;
	double mdiffg=mesh->s_light->M_diff.g;
	double mdiffb=mesh->s_light->M_diff.b;

	double mspecr=mesh->s_light->M_spec.r;
	double mspecg=mesh->s_light->M_spec.g;
	double mspecb=mesh->s_light->M_spec.b;
	mytext=mesh->texture;
	pheight=mesh->t_pheight;
	pwidth=mesh->t_pwidth;
	sp[0].cols=vertex1->rgbspec;
	sp[1].cols=vertex2->rgbspec;
	sp[2].cols=vertex3->rgbspec;

	sp[0].cold=vertex1->rgbdiff;
	sp[1].cold=vertex2->rgbdiff;
	sp[2].cold=vertex3->rgbdiff;


	// order in increasing y order

	if(sp[0].scr[1] > sp[1].scr[1]) {
		temp	= sp[0];
		sp[0]	= sp[1];
		sp[1]	= temp;
	}
	if(sp[0].scr[1] > sp[2].scr[1]) {
		temp	= sp[0];
		sp[0]	= sp[2];
		sp[2]	= temp;
	}
	if(sp[1].scr[1] > sp[2].scr[1]) {
		temp	= sp[1];
		sp[1]	= sp[2];
		sp[2]	= temp;
	}

	// calculate delta y of the edges

	scan.invDeltaY[0] = sp[2].scr[1] - sp[0].scr[1];
	
	if(scan.invDeltaY[0] < FLT_ERROR)
		return;

	scan.invDeltaY[1] = sp[1].scr[1] - sp[0].scr[1];
	scan.invDeltaY[2] = sp[2].scr[1] - sp[1].scr[1];

	scan.invDeltaY[0] = 1.0f / scan.invDeltaY[0];
	if(scan.invDeltaY[1] >= FLT_ERROR) scan.invDeltaY[1] = 1.0f / scan.invDeltaY[1];
	if(scan.invDeltaY[2] >= FLT_ERROR) scan.invDeltaY[2] = 1.0f / scan.invDeltaY[2];

	// find if the major edge is left or right aligned

	v1[0] = sp[0].scr[0] - sp[2].scr[0];
	v1[1] = sp[0].scr[1] - sp[2].scr[1];
	v2[0] = sp[1].scr[0] - sp[0].scr[0];
	v2[1] = sp[1].scr[1] - sp[0].scr[1];

	if(v1[0] * v2[1] - v1[1] * v2[0] > 0) scan.left = 0;
	else scan.left = 1;

	// calculate slopes for the major edge

	scan.slopeX[0]		= (sp[2].scr[0] - sp[0].scr[0]) * scan.invDeltaY[0];
	scan.x[0]			= sp[0].scr[0];

	scan.slopeCd[0].r	= (sp[2].cold.r - sp[0].cold.r) * scan.invDeltaY[0];
	scan.slopeCd[0].g	= (sp[2].cold.g - sp[0].cold.g) * scan.invDeltaY[0];
	scan.slopeCd[0].b	= (sp[2].cold.b - sp[0].cold.b) * scan.invDeltaY[0];
	scan.cd[0].r			= sp[0].cold.r;
	scan.cd[0].g			= sp[0].cold.g;
	scan.cd[0].b			= sp[0].cold.b;

	scan.slopeCs[0].r	= (sp[2].cols.r - sp[0].cols.r) * scan.invDeltaY[0];
	scan.slopeCs[0].g	= (sp[2].cols.g - sp[0].cols.g) * scan.invDeltaY[0];
	scan.slopeCs[0].b	= (sp[2].cols.b - sp[0].cols.b) * scan.invDeltaY[0];
	scan.cs[0].r			= sp[0].cols.r;
	scan.cs[0].g			= sp[0].cols.g;
	scan.cs[0].b			= sp[0].cols.b;

	scan.slopeU[0]			= (sp[2].u - sp[0].u) * scan.invDeltaY[0];
	scan.u[0]			= sp[0].u;

	scan.slopeV[0]			= (sp[2].v - sp[0].v) * scan.invDeltaY[0];
	scan.v[0]			= sp[0].v;

	scan.slopeZ[0]			= (sp[2].z - sp[0].z) * scan.invDeltaY[0];
	scan.z[0]			= sp[0].z;

	// rasterize upper sub-triangle

	if(scan.invDeltaY[1] >= FLT_ERROR) {
		
		// calculate slopes for top edge

		scan.slopeX[1]		= (sp[1].scr[0] - sp[0].scr[0]) * scan.invDeltaY[1];
		scan.x[1]			= sp[0].scr[0];

		scan.slopeU[1]		= (sp[1].u - sp[0].u) * scan.invDeltaY[1];
		scan.u[1]			= sp[0].u;

		scan.slopeV[1]		= (sp[1].v - sp[0].v) * scan.invDeltaY[1];
		scan.v[1]			= sp[0].v;

		scan.slopeZ[1]		= (sp[1].z - sp[0].z) * scan.invDeltaY[1];
		scan.z[1]			= sp[0].z;

		scan.slopeCd[1].r	= (sp[1].cold.r - sp[0].cold.r) * scan.invDeltaY[1];
		scan.slopeCd[1].g	= (sp[1].cold.g - sp[0].cold.g) * scan.invDeltaY[1];
		scan.slopeCd[1].b	= (sp[1].cold.b - sp[0].cold.b) * scan.invDeltaY[1];
		scan.cd[1].r			= sp[0].cold.r;
		scan.cd[1].g			= sp[0].cold.g;
		scan.cd[1].b			= sp[0].cold.b;

		scan.slopeCs[1].r	= (sp[1].cols.r - sp[0].cols.r) * scan.invDeltaY[1];
		scan.slopeCs[1].g	= (sp[1].cols.g - sp[0].cols.g) * scan.invDeltaY[1];
		scan.slopeCs[1].b	= (sp[1].cols.b - sp[0].cols.b) * scan.invDeltaY[1];
		scan.cs[1].r			= sp[0].cols.r;
		scan.cs[1].g			= sp[0].cols.g;
		scan.cs[1].b			= sp[0].cols.b;

//		yStart				= ceil(sp[0].scr[1]);
		r=sp[0].scr[1];
		if(sp[0].scr[1]>0)
			yStart=(sp[0].scr[1]-r)>0?r+1:r;
		else
			yStart=r;

		r=sp[1].scr[1];
		if(sp[1].scr[1]>0)
			yEnd=(sp[1].scr[1]-r)>0?r+1:r;
		else
			yEnd=r;
		yEnd=yEnd-1;
		if(yEnd<0) goto next;
		if(yStart>bheight) goto next;
		if(yEnd>=bheight) yEnd=bheight-1;

		sub					= (float)yStart - sp[0].scr[1];

		scan.x[0]			+= scan.slopeX[0] * sub;

		scan.u[0]			+= scan.slopeU[0] * sub;

		scan.v[0]			+= scan.slopeV[0] * sub;

		scan.z[0]			+= scan.slopeZ[0] * sub;

		scan.cd[0].r			+= scan.slopeCd[0].r * sub;
		scan.cd[0].g			+= scan.slopeCd[0].g * sub;
		scan.cd[0].b			+= scan.slopeCd[0].b * sub;

		scan.cs[0].r			+= scan.slopeCs[0].r * sub;
		scan.cs[0].g			+= scan.slopeCs[0].g * sub;
		scan.cs[0].b			+= scan.slopeCs[0].b * sub;

		scan.x[1]			+= scan.slopeX[1] * sub;		

		scan.u[1]			+= scan.slopeU[1] * sub;

		scan.v[1]			+= scan.slopeV[1] * sub;

		scan.z[1]			+= scan.slopeZ[1] * sub;

		scan.cd[1].r			+= scan.slopeCd[1].r * sub;
		scan.cd[1].g			+= scan.slopeCd[1].g * sub;
		scan.cd[1].b			+= scan.slopeCd[1].b * sub;

		scan.cs[1].r			+= scan.slopeCs[1].r * sub;
		scan.cs[1].g			+= scan.slopeCs[1].g * sub;
		scan.cs[1].b			+= scan.slopeCs[1].b * sub;

		// rasterize the edge scanlines

		for(int y = yStart; y <= yEnd; y++) {
		
			// apply top-left fill-convention to scanline
			{
			xs =(float)scan.x[scan.left];
			xe =(float)scan.x[!scan.left];
		
			us =(float)scan.u[scan.left];
			ue =(float)scan.u[!scan.left];
			
			vs =(float)scan.v[scan.left];
			ve =(float)scan.v[!scan.left];
			
			zs =(float)scan.z[scan.left];
			ze =(float)scan.z[!scan.left];

			rss=scan.cs[scan.left].r;
			gss=scan.cs[scan.left].g;
			bss=scan.cs[scan.left].b;
			res=scan.cs[!scan.left].r;
			ges=scan.cs[!scan.left].g;
			bes=scan.cs[!scan.left].b;

			rsd=scan.cd[scan.left].r;
			gsd=scan.cd[scan.left].g;
			bsd=scan.cd[scan.left].b;
			red=scan.cd[!scan.left].r;
			ged=scan.cd[!scan.left].g;
			bed=scan.cd[!scan.left].b;

			rlefts=rss;glefts=gss;blefts=bss;rrights=res;grights=ges;brights=bes;
			rleftd=rsd;gleftd=gsd;bleftd=bsd;rrightd=red;grightd=ged;brightd=bed;

			uleft=us;vleft=vs;uright=ue;vright=ve;
			zleft=zs;zright=ze;
//			xxs = ceil(xs);
			r=xs;
			if(xs>0)
				xxs=(xs-r)>0?r+1:r;
			else
				xxs=r;

			r=xe;
			if(xe>0)
				xxe=(xe-r)>0?r+1:r;
			else
				xxe=r;
			xxe=xxe-1;
			if(xxe>=bwidth) xxe=bwidth-1;

			if((xxe < xxs)||(xxe<0)||(xxs>bwidth)||(y<0))
			{
			scan.x[0]	+= scan.slopeX[0];
			scan.cs[0].r += scan.slopeCs[0].r;
			scan.cs[0].g += scan.slopeCs[0].g;
			scan.cs[0].b += scan.slopeCs[0].b;
			scan.cd[0].r += scan.slopeCd[0].r;
			scan.cd[0].g += scan.slopeCd[0].g;
			scan.cd[0].b += scan.slopeCd[0].b;
			scan.u[0] += scan.slopeU[0];
			scan.v[0] += scan.slopeV[0];
			scan.z[0] += scan.slopeZ[0];
		
			scan.x[1]	+= scan.slopeX[1];
			scan.cs[1].r += scan.slopeCs[1].r;
			scan.cs[1].g += scan.slopeCs[1].g;
			scan.cs[1].b += scan.slopeCs[1].b;
			scan.cd[1].r += scan.slopeCd[1].r;
			scan.cd[1].g += scan.slopeCd[1].g;
			scan.cd[1].b += scan.slopeCd[1].b;
			scan.u[1] += scan.slopeU[1];
			scan.v[1] += scan.slopeV[1];
			scan.z[1] += scan.slopeZ[1];
			continue;
			}


			// calculate slopes

			invDeltaX = xe - xs;

			if(invDeltaX < FLT_ERROR) invDeltaX = 1.0f;
			else invDeltaX = 1.0f / invDeltaX; 

			sub = (float)xxs - xs;

			drs = (rrights - rlefts) * invDeltaX;
			dgs = (grights - glefts) * invDeltaX;
			dbs = (brights - blefts) * invDeltaX;
			drd = (rrightd - rleftd) * invDeltaX;
			dgd = (grightd - gleftd) * invDeltaX;
			dbd = (brightd - bleftd) * invDeltaX;
			du = (uright - uleft) * invDeltaX;
			dv = (vright - vleft) * invDeltaX;
			dz = (zright - zleft) * invDeltaX;

			// rasterize line
			for(i = xxs; i <= xxe; i++) {
			if(i<0)
			{
				if(mytext!=NULL)
				{
				uleft += du;
				vleft += dv;
				}

				zleft += dz;
				rlefts += drs;
				glefts += dgs;
				blefts += dbs;
				rleftd += drd;
				gleftd += dgd;
				bleftd += dbd;
				continue;
			}
				bb=bits[((bheight-y)*bwidth+i)*bpp+0];
				gb=bits[((bheight-y)*bwidth+i)*bpp+1];
				rb=bits[((bheight-y)*bwidth+i)*bpp+2];
				
				if(mytext==NULL)
				{
				jr=rleftd*mdiffr+rlefts*mspecr;
				jr=(jr*255);
				jr=(jr>255)?255:jr;
				jr=(jr<0)?0:jr;

				jg=gleftd*mdiffg+glefts*mspecg;
				jg=(jg*255);
				jg=(jg>255)?255:jg;
				jg=(jg<0)?0:jg;

				jb=bleftd*mdiffb+blefts*mspecb;
				jb=(jb*255);
				jb=(jb>255)?255:jb;
				jb=(jb<0)?0:jb;

				r=(1-alpha)*rb+alpha*jr;
				g=(1-alpha)*gb+alpha*jg;
				b=(1-alpha)*bb+alpha*jb;

				}
				else
				{

				jr=(pheight-1)*vleft;
				r=jr;
				if(jr<0)
					jr=(jr-r)<0?r-1:r;
				else
					jr=r;
				jr=jr>0?jr:0;
				jg=pwidth*uleft;
				r=jg;
				if(jg<0)
					jg=(jg-r)<0?r-1:r;
				else
					jg=r;
				jg=jg>0?jg:0;

				yt=jr*pwidth+jg;
				jr=pwidth*pheight;
				yt=yt<jr?yt:jr;

				jr=rleftd*(mytext[yt].r/255)+rlefts*mspecr;
				jr=(jr*255);
				jr=(jr>255)?255:jr;
				jr=(jr<0)?0:jr;

				jg=gleftd*(mytext[yt].g/255)+glefts*mspecg;
				jg=(jg*255);
				jg=(jg>255)?255:jg;
				jg=(jg<0)?0:jg;

				jb=bleftd*(mytext[yt].b/255)+blefts*mspecb;
				jb=(jb*255);
				jb=(jb>255)?255:jb;
				jb=(jb<0)?0:jb;

				
				r=(1-alpha)*rb+alpha*jr;
				g=(1-alpha)*gb+alpha*jg;
				b=(1-alpha)*bb+alpha*jb;

				uleft += du;
				vleft += dv;
				}				
				
				float z_cur=zbuffer[(y*bwidth+i)];
				if(z_cur>=zleft)
				{
				zbuffer[(y*bwidth+i)]=zleft;
				//SetPixelV(hdc,i,y,RGB(r,g,b));

				bits[((bheight-y)*bwidth+i)*bpp+0]=b;
				bits[((bheight-y)*bwidth+i)*bpp+1]=g;
				bits[((bheight-y)*bwidth+i)*bpp+2]=r;
				bits[((bheight-y)*bwidth+i)*bpp+3]=0;
				}

				zleft += dz;
				rlefts += drs;
				glefts += dgs;
				blefts += dbs;
				rleftd += drd;
				gleftd += dgd;
				bleftd += dbd;
			}
					
			}
			scan.x[0]	+= scan.slopeX[0];
			scan.cs[0].r += scan.slopeCs[0].r;
			scan.cs[0].g += scan.slopeCs[0].g;
			scan.cs[0].b += scan.slopeCs[0].b;
			scan.cd[0].r += scan.slopeCd[0].r;
			scan.cd[0].g += scan.slopeCd[0].g;
			scan.cd[0].b += scan.slopeCd[0].b;
			scan.u[0] += scan.slopeU[0];
			scan.v[0] += scan.slopeV[0];
			scan.z[0] += scan.slopeZ[0];
		
			scan.x[1]	+= scan.slopeX[1];
			scan.cs[1].r += scan.slopeCs[1].r;
			scan.cs[1].g += scan.slopeCs[1].g;
			scan.cs[1].b += scan.slopeCs[1].b;
			scan.cd[1].r += scan.slopeCd[1].r;
			scan.cd[1].g += scan.slopeCd[1].g;
			scan.cd[1].b += scan.slopeCd[1].b;
			scan.u[1] += scan.slopeU[1];
			scan.v[1] += scan.slopeV[1];
			scan.z[1] += scan.slopeZ[1];
		}
	}

	// rasterize lower sub-triangle

next:	if(scan.invDeltaY[2] >= FLT_ERROR) {

		// advance major edge attirubtes to middle point (if we have process the other edge)

		if(scan.invDeltaY[1] >= FLT_ERROR) {
			float dy = sp[1].scr[1] - sp[0].scr[1];
			scan.x[0] = sp[0].scr[0] + scan.slopeX[0] * dy;
			scan.cs[0].r = sp[0].cols.r + scan.slopeCs[0].r * dy;
			scan.cs[0].g = sp[0].cols.g + scan.slopeCs[0].g * dy;
			scan.cs[0].b = sp[0].cols.b + scan.slopeCs[0].b * dy;
			scan.cd[0].r = sp[0].cold.r + scan.slopeCd[0].r * dy;
			scan.cd[0].g = sp[0].cold.g + scan.slopeCd[0].g * dy;
			scan.cd[0].b = sp[0].cold.b + scan.slopeCd[0].b * dy;
			scan.u[0] = sp[0].u + scan.slopeU[0] * dy;
			scan.v[0] = sp[0].v + scan.slopeV[0] * dy;
			scan.z[0] = sp[0].z + scan.slopeZ[0] * dy;
		}

		// calculate slopes for bottom edge

		scan.slopeX[1]		= (sp[2].scr[0] - sp[1].scr[0]) * scan.invDeltaY[2];
		scan.x[1]			= sp[1].scr[0];

		scan.slopeU[1]		= (sp[2].u - sp[1].u) * scan.invDeltaY[2];
		scan.u[1]			= sp[1].u;

		scan.slopeV[1]		= (sp[2].v - sp[1].v) * scan.invDeltaY[2];
		scan.v[1]			= sp[1].v;

		scan.slopeZ[1]		= (sp[2].z - sp[1].z) * scan.invDeltaY[2];
		scan.z[1]			= sp[1].z;

		scan.slopeCs[1].r	= (sp[2].cols.r - sp[1].cols.r) * scan.invDeltaY[2];
		scan.slopeCs[1].g	= (sp[2].cols.g - sp[1].cols.g) * scan.invDeltaY[2];
		scan.slopeCs[1].b	= (sp[2].cols.b - sp[1].cols.b) * scan.invDeltaY[2];
		scan.cs[1].r			= sp[1].cols.r;
		scan.cs[1].g			= sp[1].cols.g;
		scan.cs[1].b			= sp[1].cols.b;

		scan.slopeCd[1].r	= (sp[2].cold.r - sp[1].cold.r) * scan.invDeltaY[2];
		scan.slopeCd[1].g	= (sp[2].cold.g - sp[1].cold.g) * scan.invDeltaY[2];
		scan.slopeCd[1].b	= (sp[2].cold.b - sp[1].cold.b) * scan.invDeltaY[2];
		scan.cd[1].r			= sp[1].cold.r;
		scan.cd[1].g			= sp[1].cold.g;
		scan.cd[1].b			= sp[1].cold.b;

		r=sp[1].scr[1];
		if(sp[1].scr[1]>0)
			yStart=(sp[1].scr[1]-r)>0?r+1:r;
		else
			yStart=r;

		r=sp[2].scr[1];
		if(sp[2].scr[1]>0)
			yEnd=(sp[2].scr[1]-r)>0?r+1:r;
		else
			yEnd=r;
		yEnd=yEnd-1;
		if(yEnd<0) return;
		if(yStart>bheight) return;
		if(yEnd>=bheight) yEnd=bheight-1;

		sub					= (float)yStart - sp[1].scr[1];
		
		scan.x[0] 			+= scan.slopeX[0] * sub;

		scan.z[0] 			+= scan.slopeZ[0] * sub;

		scan.u[0]			+= scan.slopeU[0] * sub;

		scan.v[0]			+= scan.slopeV[0] * sub;

		scan.cs[0].r			+= scan.slopeCs[0].r * sub;
		scan.cs[0].g			+= scan.slopeCs[0].g * sub;
		scan.cs[0].b			+= scan.slopeCs[0].b * sub;

		scan.cd[0].r			+= scan.slopeCd[0].r * sub;
		scan.cd[0].g			+= scan.slopeCd[0].g * sub;
		scan.cd[0].b			+= scan.slopeCd[0].b * sub;

		scan.x[1] 			+= scan.slopeX[1] * sub;

		scan.z[1] 			+= scan.slopeZ[1] * sub;

		scan.u[1]			+= scan.slopeU[1] * sub;

		scan.v[1]			+= scan.slopeV[1] * sub;

		scan.cs[1].r			+= scan.slopeCs[1].r * sub;
		scan.cs[1].g			+= scan.slopeCs[1].g * sub;
		scan.cs[1].b			+= scan.slopeCs[1].b * sub;

		scan.cd[1].r			+= scan.slopeCd[1].r * sub;
		scan.cd[1].g			+= scan.slopeCd[1].g * sub;
		scan.cd[1].b			+= scan.slopeCd[1].b * sub;
		// rasterize the edge scanlines

		for(int y = yStart; y <= yEnd; y++) {
			{
			xs =(float)scan.x[scan.left];
			xe =(float)scan.x[!scan.left];
			us =(float)scan.u[scan.left];
			ue =(float)scan.u[!scan.left];
			vs =(float)scan.v[scan.left];
			ve =(float)scan.v[!scan.left];
			zs =(float)scan.z[scan.left];
			ze =(float)scan.z[!scan.left];
			
			rss=scan.cs[scan.left].r;
			gss=scan.cs[scan.left].g;
			bss=scan.cs[scan.left].b;
			res=scan.cs[!scan.left].r;
			ges=scan.cs[!scan.left].g;
			bes=scan.cs[!scan.left].b;
			
			rsd=scan.cd[scan.left].r;
			gsd=scan.cd[scan.left].g;
			bsd=scan.cd[scan.left].b;
			red=scan.cd[!scan.left].r;
			ged=scan.cd[!scan.left].g;
			bed=scan.cd[!scan.left].b;

			rlefts=rss;glefts=gss;blefts=bss;rrights=res;grights=ges;brights=bes;
			rleftd=rsd;gleftd=gsd;bleftd=bsd;rrightd=red;grightd=ged;brightd=bed;
			uleft=us;vleft=vs;uright=ue;vright=ve;
			zleft=zs;zright=ze;
			
//			xxs = ceil(xs);
			r=xs;
			if(xs>0)
				xxs=(xs-r)>0?r+1:r;
			else
				xxs=r;

			r=xe;
			if(xe>0)
				xxe=(xe-r)>0?r+1:r;
			else
				xxe=r;
			xxe=xxe-1;
			if(xxe>=bwidth) xxe=bwidth-1;

			if((xxe < xxs)||(xxe<0)||(xxs>bwidth)||(y<0))
			{
			scan.x[0]	+= scan.slopeX[0];
			scan.cs[0].r += scan.slopeCs[0].r;
			scan.cs[0].g += scan.slopeCs[0].g;
			scan.cs[0].b += scan.slopeCs[0].b;
			scan.cd[0].r += scan.slopeCd[0].r;
			scan.cd[0].g += scan.slopeCd[0].g;
			scan.cd[0].b += scan.slopeCd[0].b;
			scan.u[0] += scan.slopeU[0];
			scan.v[0] += scan.slopeV[0];
			scan.z[0] += scan.slopeZ[0];
		
			scan.x[1]	+= scan.slopeX[1];
			scan.cs[1].r += scan.slopeCs[1].r;
			scan.cs[1].g += scan.slopeCs[1].g;
			scan.cs[1].b += scan.slopeCs[1].b;
			scan.cd[1].r += scan.slopeCd[1].r;
			scan.cd[1].g += scan.slopeCd[1].g;
			scan.cd[1].b += scan.slopeCd[1].b;
			scan.u[1] += scan.slopeU[1];
			scan.v[1] += scan.slopeV[1];
			scan.z[1] += scan.slopeZ[1];
			continue;
			}

			// calculate slopes

			invDeltaX = xe - xs;

			if(invDeltaX < FLT_ERROR) invDeltaX = 1.0f;
			else invDeltaX = 1.0f / invDeltaX; 

			sub = (float)xxs - xs;

			drs = (rrights - rlefts) * invDeltaX;
			dgs = (grights - glefts) * invDeltaX;
			dbs = (brights - blefts) * invDeltaX;
			drd = (rrightd - rleftd) * invDeltaX;
			dgd = (grightd - gleftd) * invDeltaX;
			dbd = (brightd - bleftd) * invDeltaX;
			du = (uright - uleft) * invDeltaX;
			dv = (vright - vleft) * invDeltaX;
			dz = (zright - zleft) * invDeltaX;


			// rasterize line

			for(i = xxs; i <= xxe; i++) {
			if(i<0)
			{
				if(mytext!=NULL)
				{
				uleft += du;
				vleft += dv;
				}

				zleft += dz;
				rlefts += drs;
				glefts += dgs;
				blefts += dbs;
				rleftd += drd;
				gleftd += dgd;
				bleftd += dbd;
				continue;
			}

				
				bb=bits[((bheight-y)*bwidth+i)*bpp+0];
				gb=bits[((bheight-y)*bwidth+i)*bpp+1];
				rb=bits[((bheight-y)*bwidth+i)*bpp+2];

				if(mytext==NULL)
				{
				jr=rleftd*mdiffr+rlefts*mspecr;
				jr=(jr*255);
				jr=(jr>255)?255:jr;
				jr=(jr<0)?0:jr;

				jg=gleftd*mdiffg+glefts*mspecg;
				jg=(jg*255);
				jg=(jg>255)?255:jg;
				jg=(jg<0)?0:jg;

				jb=bleftd*mdiffb+blefts*mspecb;
				jb=(jb*255);
				jb=(jb>255)?255:jb;
				jb=(jb<0)?0:jb;

				r=(1-alpha)*rb+alpha*jr;
				g=(1-alpha)*gb+alpha*jg;
				b=(1-alpha)*bb+alpha*jb;
				}
				else
				{
				jr=(pheight-1)*vleft;
				r=jr;
				if(jr<0)
					jr=(jr-r)<0?r-1:r;
				else
					jr=r;
				jr=jr>0?jr:0;
				jg=pwidth*uleft;
				r=jg;
				if(jg<0)
					jg=(jg-r)<0?r-1:r;
				else
					jg=r;
				jg=jg>0?jg:0;

				yt=jr*pwidth+jg;
				jr=pwidth*pheight;
				yt=yt<jr?yt:jr;


				jr=rleftd*(mytext[yt].r/255)+rlefts*mspecr;
				jr=(jr*255);
				jr=(jr>255)?255:jr;
				jr=(jr<0)?0:jr;

				jg=gleftd*(mytext[yt].g/255)+glefts*mspecg;
				jg=(jg*255);
				jg=(jg>255)?255:jg;
				jg=(jg<0)?0:jg;

				jb=bleftd*(mytext[yt].b/255)+blefts*mspecb;
				jb=(jb*255);
				jb=(jb>255)?255:jb;
				jb=(jb<0)?0:jb;
				
				r=(1-alpha)*rb+alpha*jr;
				g=(1-alpha)*gb+alpha*jg;
				b=(1-alpha)*bb+alpha*jb;

				uleft += du;
				vleft += dv;

				}				
				float z_cur=zbuffer[(y*bwidth+i)];
				if(z_cur>=zleft)
				{
				zbuffer[(y*bwidth+i)]=zleft;
			//	SetPixelV(hdc,i,y,RGB(r,g,b));
				bits[((bheight-y)*bwidth+i)*bpp+0]=b;
				bits[((bheight-y)*bwidth+i)*bpp+1]=g;
				bits[((bheight-y)*bwidth+i)*bpp+2]=r;
				bits[((bheight-y)*bwidth+i)*bpp+3]=0;
				}

				zleft += dz;
				rlefts += drs;
				glefts += dgs;
				blefts += dbs;
				rleftd += drd;
				gleftd += dgd;
				bleftd += dbd;
			}
					
			}
			scan.x[0]	+= scan.slopeX[0];
			scan.cs[0].r += scan.slopeCs[0].r;
			scan.cs[0].g += scan.slopeCs[0].g;
			scan.cs[0].b += scan.slopeCs[0].b;
			scan.cd[0].r += scan.slopeCd[0].r;
			scan.cd[0].g += scan.slopeCd[0].g;
			scan.cd[0].b += scan.slopeCd[0].b;
			scan.u[0]	+= scan.slopeU[0];
			scan.v[0]	+= scan.slopeV[0];
			scan.z[0]	+= scan.slopeZ[0];
		
			scan.x[1]	+= scan.slopeX[1];
			scan.cs[1].r += scan.slopeCs[1].r;
			scan.cs[1].g += scan.slopeCs[1].g;
			scan.cs[1].b += scan.slopeCs[1].b;
			scan.cd[1].r += scan.slopeCd[1].r;
			scan.cd[1].g += scan.slopeCd[1].g;
			scan.cd[1].b += scan.slopeCd[1].b;
			scan.u[1]	+= scan.slopeU[1];
			scan.v[1]	+= scan.slopeV[1];
			scan.z[1]	+= scan.slopeZ[1];
		}

		}
}



void CTriangle::triangle_template()
{
/*//		using namespace detail;

	Vertex v1,v2,v3;
	v1.x=vertex1->p.x;
	v1.y=vertex1->p.y;
	v1.z=vertex1->z;

	v2.x=vertex2->p.x;
	v2.y=vertex2->p.y;
	v2.z=vertex2->z;

	v3.x=vertex3->p.x;
	v3.y=vertex3->p.y;
	v3.z=vertex3->z;
		
		// Early bounds test. Skip triangle if outside clip rect. 
		// This is intended for the special case when the clip_rect is smaller
		// than the whole screen as is the case in dual cpu rendering, when each 
		// cpu renders only part of the screen.
		int minx = min(min(v1.x, v2.x), v3.x) >> 4;
		int miny = min(min(v1.y, v2.y), v3.y) >> 4;
		int maxx = max(max(v1.x, v2.x), v3.x) >> 4;
		int maxy = max(max(v1.y, v2.y), v3.y) >> 4;

		if (minx >= clip_rect_.x1 || miny >= clip_rect_.y1 || 
			maxx < clip_rect_.x0 || maxy < clip_rect_.y0)
			return;

		// Deltas
		const int DX12 = v1.x - v2.x;
		const int DX31 = v3.x - v1.x;

		const int DY12 = v1.y - v2.y;
		const int DY31 = v3.y - v1.y;

		// this is actually twice the area
		const int area = DX12 * DY31 - DX31 * DY12;

		if (area <= 0xf)
			return;

		// Execute per triangle function. This can be used to compute the mipmap
		// level per primitive. To support mipmap per pixel at least one varying 
		// attributes would need to be written by this function but this isn't 
		// possible for now as the vertices are declared const.
//		FragSpan::begin_triangle(v1, v2, v3, area);
	
		// inv_area in 8.24
		const int inv_area = invert(area);

		// sort vertices in y and determine on which side the middle vertex lies
		const Vertex *top, *middle, *bottom;
		bool middle_is_left;

		if (v1.y < v2.y) {
			if (v1.y < v3.y) {
				top = &v1;
				if (v2.y < v3.y) {
					middle = &v2;
					bottom = &v3;
					middle_is_left = true;
				} 
				else {
					middle = &v3;
					bottom = &v2;
					middle_is_left = false;
				}
			} 
			else {
				top = &v3;
				middle = &v1;
				bottom = &v2;
				middle_is_left = true;
			}			
		}
		else {
			if (v2.y < v3.y) {
				top = &v2;
				if (v1.y < v3.y) {
					middle = &v1;
					bottom = &v3;
					middle_is_left = false;
				} 
				else {
					middle = &v3;
					bottom = &v1;
					middle_is_left = true;
				}
			}
			else {
				top = &v3;
				middle = &v2;
				bottom = &v1;
				middle_is_left = false;
			}
		}

		if (perspective_correction_ && (
			(maxx - minx) > perspective_threshold_.w || 
			(maxy - miny) > perspective_threshold_.h ))
		{
			Gradients grad(v1, v2, v3, DX12, DY12, DX31, DY31, inv_area);
			Edge top_middle(grad, top, middle);
			Edge top_bottom(grad, top, bottom);
			Edge middle_bottom(grad, middle, bottom);

			Edge *left, *right;
			if (middle_is_left) {
				left = &top_middle;
				right = &top_bottom;
			}
			else {
				left = &top_bottom;
				right = &top_middle;
			}


			int height = middle_is_left ? left->height : right->height;

			// draw top triangle
			while (height) {
				int y = left->y;
				if (ilace_drawit(y) && y >= clip_rect_.y0 && y < clip_rect_.y1) 
					Scanline::draw(left, right, clip_rect_.x0, clip_rect_.x1);
				left->step(true);
				right->step(false);
				height--;
			}

			if (middle_is_left) {
				left = &middle_bottom;
				height = left->height;
			}
 			else {
				right = &middle_bottom;
				height = right->height;
			}

			// draw bottom triangle
			while (height) {
				int y = left->y;
				if (ilace_drawit(y) && y >= clip_rect_.y0 && y < clip_rect_.y1) 
					Scanline::draw(left, right, clip_rect_.x0, clip_rect_.x1);
				left->step(true);
				right->step(false);
				height--;
			}
		}
		// affine interpolation and rendering
		else {
			// computes the gradients of the varyings to be used for stepping
			struct Gradients {
				FragmentData dx;
				FragmentData dy;

				Gradients(const Vertex &v1, const Vertex &v2, const Vertex &v3,
					int DX12, int DY12, int DX31, int DY31, int inv_area)
				{
					if (FragSpan::interpolate_z)
						compute_gradients(DX12, DY12, DX31, DY31, 
							inv_area, v1.z, v2.z, v3.z, dx.z, dy.z);

					for (unsigned i = 0; i < FragSpan::varying_count; ++i)
						compute_gradients(DX12, DY12, DX31, DY31, 
						inv_area, v1.varyings[i], v2.varyings[i], v3.varyings[i], 
						dx.varyings[i], dy.varyings[i]);
				}
			};

			// Edge structure used to walk the edge of the triangle and fill the
			// scanlines
			struct Edge {
				int x, x_step, numerator, denominator, error_term; // DDA info for x
				int y, height;

				FragmentData fragment_data;
				FragmentData fragment_step;

				const Gradients& grad;		

				Edge(const Gradients &grad_, const Vertex* top, const Vertex *bottom)
					: grad(grad_)
				{
					y = ceil28_4(top->y);
					int yend = ceil28_4(bottom->y);
					height = yend - y;

					if (height) {
						int dn = bottom->y - top->y;
						int dm = bottom->x - top->x;

						int initial_numerator = dm*16*y - dm*top->y + 
							dn*top->x - 1 + dn*16;
						floor_divmod(initial_numerator, dn*16, &x, &error_term);
						floor_divmod(dm*16, dn*16, &x_step, &numerator);
						denominator = dn*16;

						int y_prestep = y*16 - top->y;
						int x_prestep = x*16 - top->x;

						#define PRESTEP(VAR) \
							(((y_prestep * grad.dy.VAR) >> 4) + \
							((x_prestep * grad.dx.VAR) >> 4))
							
						#define STEP(VAR) \
							(x_step * grad.dx.VAR + grad.dy.VAR)

						if (FragSpan::interpolate_z) {
							fragment_data.z = top->z + PRESTEP(z);
							fragment_step.z = STEP(z);
						}

						for (unsigned i = 0; i < FragSpan::varying_count; ++i) {
							fragment_data.varyings[i] = top->varyings[i] + PRESTEP(varyings[i]);
							fragment_step.varyings[i] = STEP(varyings[i]);
						}

						#undef PRESTEP
						#undef STEP
					}
				}

				void step(bool step_varyings)
				{
					x += x_step; y++; height--;

					if (step_varyings)
						FRAGMENTDATA_APPLY(FragSpan, fragment_data, +=, fragment_step);

					error_term += numerator;
					if (error_term >= denominator) {
						x++;
						if (step_varyings)
							FRAGMENTDATA_APPLY(FragSpan, fragment_data, +=, grad.dx);
						error_term -= denominator;
					}
				}
			};

			Gradients grad(v1, v2, v3, DX12, DY12, DX31, DY31, inv_area);
			Edge top_middle(grad, top, middle);
			Edge top_bottom(grad, top, bottom);
			Edge middle_bottom(grad, middle, bottom);

			Edge *left, *right;
			if (middle_is_left) {
				left = &top_middle;
				right = &top_bottom;
			}
			else {
				left = &top_bottom;
				right = &top_middle;
			}

			struct Scanline {
				static void draw(const Edge *left, const Edge *right, int cl, int cr)
				{
					int y = left->y;
					int l = left->x;
					int r = std::min(right->x, cr);
					const Gradients &grad = left->grad;

					if (r - l <= 0) return;

					FragmentData fd;
					FRAGMENTDATA_APPLY(FragSpan, fd, =, left->fragment_data);

					// skip pixels left of the clipping rectangle
					if (l < cl) {
						int d = cl - l;
						FRAGMENTDATA_APPLY(FragSpan, fd, += d *, grad.dx);
						l = cl;
					}

					// draw the scanline up until the right side
					FragSpan::affine_span(l, y, fd, grad.dx, r - l);
				}
			};

			int height = middle_is_left ? left->height : right->height;

			// draw top triangle
			while (height) {
				int y = left->y;
				if (ilace_drawit(y) && y >= clip_rect_.y0 && y < clip_rect_.y1) 
					Scanline::draw(left, right, clip_rect_.x0, clip_rect_.x1);
				left->step(true);
				right->step(false);
				height--;
			}

			if (middle_is_left) {
				left = &middle_bottom;
				height = left->height;
			}
			else {
				right = &middle_bottom;
				height = right->height;
			}

			// draw bottom triangle
			while (height) {
				int y = left->y;
				if (ilace_drawit(y) && y >= clip_rect_.y0 && y < clip_rect_.y1) 
					Scanline::draw(left, right, clip_rect_.x0, clip_rect_.x1);
				left->step(true);
				right->step(false);
				height--;
			}
		}
*/}

void CTriangle::updateShadingpara(CCVector lit[6],col* my,int pwidth,int pheight,light *l)
{
/*	alpha=&l->alpha;
	M_spec=&l->M_spec;
	M_diff=&l->M_diff;
	M_amb=&l->M_amb;

	diff_map.bits=my;
	diff_map.cx=pwidth;
	diff_map.cy=pheight;

	gloss_map.bits=NULL;
	gloss_map.cx=pwidth;
	gloss_map.cy=pheight;*/
}

void CTriangle::setMesh(CMesh *m)
{
	mesh=m;
}

void CTriangle::updateAdj()
{
/*	edge1->addAdjT(this);
	edge2->addAdjT(this);
	edge3->addAdjT(this);
	vertex1->addAdjT(this);
	vertex2->addAdjT(this);
	vertex3->addAdjT(this);*/
}

CVertex* CTriangle::Vertex(int n)
{
	switch(n)
	{
	case 0:
		return sit;
	case 1:
		return sjt;
	case 2:
		return skt;
	default:
		ASSERT(FALSE);
	}

}

CEdge* CTriangle::Edge(int n)
{
	switch(n)
	{
	case 0:
		return mesh->Edge(eit);
	case 1:
		return mesh->Edge(ejt);
	case 2:
		return mesh->Edge(ekt);
	default:
		ASSERT(FALSE);
	}

}

CMesh* CTriangle::getMesh()
{
	return mesh;
}

void CTriangle::operator = (CTriangle t)
{
	it=t.it;
	n=t.n;
	cent=t.cent;
	un=t.un;
	vn=t.vn;

}

void CTriangle::initcopy(CTriangle* t)
{
	sit=t->sit;
	sjt=t->sjt;
	skt=t->skt;
	eit=mesh->iEdge(t->eit);
	ejt=mesh->iEdge(t->ejt);
	ekt=mesh->iEdge(t->ekt);
}

void CTriangle::Disconnect()
{
	CVertex* v=sit;
	v->RemoveAdjTri(this);
	v=sjt;
	v->RemoveAdjTri(this);
	v=skt;
	v->RemoveAdjTri(this);

	CEdge* e=mesh->Edge(eit);
	e->RemoveAdjTri(it);
	e=mesh->Edge(ejt);
	e->RemoveAdjTri(it);
	e=mesh->Edge(ekt);
	e->RemoveAdjTri(it);
}



CVertex* CTriangle::intersect(CEdge *e)
{
  if(e==NULL) return NULL;

/*  CVertex * A=Vertex(0), * B=Vertex(1), * C=Vertex(2), * D=e->Start(), * E=e->End();
  int ABCE, ABCD, ADCE, ABDE, BCDE;
  CEdge * AB=Edge(0), * BC=Edge(1), * CA=Edge(2);
  double a, b, c;


  ABCE = gts_point_orientation_3d_sos (A, B, C, E);
  ABCD = gts_point_orientation_3d_sos (A, B, C, D);
  if (ABCE < 0 || ABCD > 0) {
    GtsPoint * tmpp;
    gint tmp;

    tmpp = E; E = D; D = tmpp;
    tmp = ABCE; ABCE = ABCD; ABCD = tmp;
  }
  if (ABCE < 0 || ABCD > 0)
    return NULL;
  ADCE = gts_point_orientation_3d_sos (A, D, C, E);
  if (ADCE < 0)
    return NULL;
  ABDE = gts_point_orientation_3d_sos (A, B, D, E);
  if (ABDE < 0)
    return NULL;
  BCDE = gts_point_orientation_3d_sos (B, C, D, E);
  if (BCDE < 0)
    return NULL;
  a = gts_point_orientation_3d (A, B, C, E);
  b = gts_point_orientation_3d (A, B, C, D);
  if (a != b) {
    c = a/(a - b);
    return gts_point_new (klass,
			  E->x + c*(D->x - E->x),
			  E->y + c*(D->y - E->y),
			  E->z + c*(D->z - E->z));
  }
  /* D and E are contained within ABC */
/*#ifdef DEBUG
  fprintf (stderr, 
	   "segment: %p:%s triangle: %p:%s intersection\n"
	   "D and E contained in ABC\n",
	   s, GTS_NEDGE (s)->name, t, GTS_NFACE (t)->name);
#endif /* DEBUG */  
/*  g_assert (a == 0.); 
  return gts_point_new (klass,
			(E->x + D->x)/2.,
			(E->y + D->y)/2.,
			(E->z + D->z)/2.);

*/}
