// Edge.cpp: implementation of the CEdge class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Edge.h"
#include "triangle.h"
#include "mesh.h"
#include "ray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdge::~CEdge()
{
	try{
	sit->RemoveAdjEdge(this);
	sjt->RemoveAdjEdge(this);
	}
	catch(...)
	{
	}
	if(ofile)
	{
		delete sit;
		delete sjt;
//		if(it!=NULL)
//			delete it;
	}
	
	sit=NULL;
	sjt=NULL;
	it=NULL;
	adjT.clear();
	adjt=0;
}
/*CEdge::CEdge()
{
 CVertex vg;
 begin=vg;
 end=vg;
}*/

CVertex* CEdge::Mate(CVertex* v)
{
	if (v==Start())
		return End();
	else
	if (v==End())
		return Start();
		else
			return NULL;

}
CVertex* CEdge::Start()
{
	return sit;
}

CVertex* CEdge::End()
{
	return sjt;
}
CEdge CEdge::operator - ()
{
	return CEdge(sjt,sit,it);
}

void CEdge::savefile(CFile &file)
{
	int _sit=sit->sit;
	int _sjt=sjt->sit;
	file.Write(&_sit,sizeof(int));
	file.Write(&_sjt,sizeof(int));
}
void CEdge::openfile(CFile &file)
{
	ofile=true;
	int _sit=0;//=sit->sit;//new CVertex();
	int _sjt=0;//=sjt->sit;// new CVertex();
	file.Read(&_sit,sizeof(int));
	file.Read(&_sjt,sizeof(int));
	sit=mesh->Vertex(_sit);
	sjt=mesh->Vertex(_sjt);
	adjt=0;
	sit->getMesh()->addEdge(this);
	sit->addAdjE(this);
	sjt->addAdjE(this);
}
LONG CEdge::Readfile(CFile &file)
{
	LONG g;
	file.Seek(sizeof(sit->sit),CFile::current);
	g=file.Seek(sizeof(sjt->sit),CFile::current);
	return g;
}
void CEdge::setConstrained(bool t)
{
  constrained=t;
}

void CEdge::display(CDC *hdc)
{
	v0_cur=VertexPos(0);
	v1_cur=VertexPos(1);
	static int i=0;
	if(i>=mesh->Vcount())
		i=0;
	CPoint p0=v0_cur;
	CPoint p1=v1_cur;
	hdc->LPtoDP(&p0);
	hdc->LPtoDP(&p1);

	CPen pen;
	CPen* oldp;

	if(constrained)
	{
	LOGBRUSH lplb;
	lplb.lbStyle=BS_SOLID;
	lplb.lbColor=PALETTERGB(19,219,49);
	lplb.lbHatch=NULL;

	pen.CreatePen(1,1,&lplb,0,NULL);
	oldp=hdc->SelectObject(&pen);

	}
	hdc->MoveTo(VertexPos(0));
	hdc->LineTo(VertexPos(1));
	if(constrained)
	{
		hdc->SelectObject(oldp);

	}

	/*	CString s2;
	s2.Format(_T("%d"),mesh->Vcount());
	hdc->TextOut(0,0,s2);
	if(sit->un==0)
	{
	double g=sit->un;
	CString sp;
	sp.Format(_T("%.3f"),g);
	CPoint p=VertexPos(0);
	hdc->TextOut(p.x,p.y,sp);
	}

	if(sjt->un==1)
	{
	double g1=sjt->un;
	CString sp1;
	sp1.Format(_T("%.3f"),g1);
	CPoint p1=VertexPos(0);
	hdc->TextOut(p1.x,p1.y,sp1);
	
//	CString sp2;
//	int g2=it;
//	sp2.Format(_T("%d"),g2);
//	CPoint p2=(VertexPos(0)+VertexPos(1))/2;
//	hdc->TextOut(p2.x,p2.y,sp2);
	}*/
	i++;
	/*
	int x1 = CPoint(CVector(*begin)).x;
	int y1 = CPoint(CVector(*begin)).y;
	int z1;// = CVector(*begin).getDepth();
	int x = x1;                       // Start x off at the first pixel
	int y = y1;						  // Start y off at the first pixel
	int z = z1;
	int x2 = CPoint(CVector(*end)).x;
	int y2 = CPoint(CVector(*end)).y;
	int z2 =0;// CVector(*end).getDepth();

	int xinc1,xinc2,yinc1,yinc2;      // Increasing values
	int den, num, numadd,numpixels;   
	int deltax = abs(x2 - x1);        // The difference between the x's
	int deltay = abs(y2 - y1);        // The difference between the y's

	// Get Increasing Values
	if (x2 >= x1) {                // The x-values are increasing
		xinc1 = 1;
		xinc2 = 1;
	} else {                         // The x-values are decreasing
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {                // The y-values are increasing
		yinc1 = 1;
		yinc2 = 1;
	} else {                         // The y-values are decreasing
		yinc1 = -1;
		yinc2 = -1;
	}

	// Actually draw the line
	if (deltax >= deltay)         // There is at least one x-value for every y-value
	{
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else                          // There is at least one y-value for every x-value
	{
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
	
	int b0=z2*y2-z1*y1;
	int b1=z2-z1;
	int t0=z2*z1;
	int t1=z1*z2;
	int c0=t1*y2-t0*y1;
	int c1=t0-t1;
	
	bool b=false;
	for (int curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		// Draw the current pixel

		if((z>-1)&&(z<1)&&(!b))
		{
		hdc->SetPixel(x,y,RGB(0,0,0));
		}
		if((b0+b1*y)!=0)
		{
		z=(c0+c1*y)/(b0+b1*y);
		b=false;
		}
		else
		{
		b=true;
		}

		
		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den)             // Check if numerator >= denominator
		{
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
*/
}



void CEdge::addAdjT(CTriangle *t)
{
	adjT.push_back(&t->it);
	adjt++;
}
CEdge::CEdge (CVertex b, CVertex e):it(-1)
{
	constrained=false;
	ofile=false;
	ASSERT((b.sit!=-1)&&(b.sit!=-1));
	b.getMesh()->addEdge(this);
	b.addAdjE(this);
	e.addAdjE(this);
	sit=new CVertex(b);
	sjt=new CVertex(e);
	adjt=0;
	v0_cur=b.v;
	v1_cur=e.v;
}
CEdge::CEdge (CVertex* b, CVertex* e,int i)
{
	constrained=false;
	ofile=false;
//	ASSERT((b->sit!=-1)&&(b->sit!=-1));
	adjt=0;
	sit=b;
	sjt=e;
	b->getMesh()->addEdge(this);
	b->addAdjE(this);
	e->addAdjE(this);
	v0_cur=b->v;
	v1_cur=e->v;

}

bool CEdge::isBorder()
{
	return (adjt==1);
}

void CEdge::flip()
{
	CVertex* v;
	v=sit;
	sit=sjt;
	sjt=v;

}

int CEdge::getAdjt()
{
	return adjt;
}
void CEdge::RemoveAdjT(CTriangle* t)
{
	vector<int*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(**iter2==t->it)
		{
			iter=iter2;
			break;
		}
		iter2++;
	}
	if(iter!=adjT.end())
	{
		mesh->DeleteTri(**iter);
		adjT.erase(iter);
		adjt--;
	}
}

void CEdge::setMesh(CMesh *m)
{
	mesh=m;
}

float CEdge::onEdge(CVector v, CVector &v1)
{
	CVector vor=VertexPos(0);
	vor.v2D();
	CVector ven=VertexPos(1);
	ven.v2D();
	CVector vp=v;
	vp.v2D();
	CVector vl(vor,ven);
	CVector vpoint(vor,vp);
		
	if (pointtoVector(vl,vpoint,&v1)<10)
	{
		CAABB box;
		box.add(vor);
		box.add(ven);
		v1+=vor;
		if(box.containpts(v1))
		{
			vpoint=v1-vor;
			v1.v3D();
			float u=absc(vpoint)/absc(vl);
			if(u==0||u==1)
				return -1;
			else
			{
				float u1=Vertex(1)->un;
				float u0=Vertex(0)->un;
				u1=u1==0?1:u1;
				u=(u1-u0)*u+u0;
			return u;
			}
		}
		else
			return -1;
	}
	else
		return -1;

}

CVector CEdge::VertexPos(int n)
{
	switch(n)
	{
	case 0:
		{
		CVertex* t=sit;
		CVector v=t->v;
		return v;
		}
	case 1:
		{
		CVertex* t=sjt;
		CVector v=t->v;
		return v;
		}
	default:
		ASSERT(FALSE);
	}

}
CVertex* CEdge::Vertex(int n)
{
	switch(n)
	{
	case 0:
		{
			CVertex *v=sit;
		return v;//mesh->Vertex(*sit);
		}
	case 1:
		return sjt;
	default:
		ASSERT(FALSE);
	}

}

CVertex* CEdge::splitEdge(float u)
{
 CVector vl=VertexPos(1)-VertexPos(0);
 float uv1=Vertex(1)->un;
 uv1=uv1==0?1:uv1;
 float uv0=Vertex(0)->un;
 CVector v=VertexPos(0)+vl*((u-uv0)/(uv1-uv0));

 float ud=uv1-Vertex(0)->un;
 float u1=u;//Vertex(0)->un+ud*u;

 float vd=Vertex(1)->vn-Vertex(0)->vn;
 float v1=Vertex(0)->vn+vd*u;

 CVector vn=Vertex(1)->n-Vertex(0)->n;
 CVector n=Vertex(0)->n+vn*u;
 CVertex* vx=new CVertex(v,u1,v1);
 vx->setnormal(n);
 vx=mesh->addVertex(vx);
 sit->RemoveAdjEdge(this);
 sjt->RemoveAdjEdge(this);
 new CEdge(Vertex(0),vx);
 new CEdge(vx,Vertex(1));
 return vx;
}

CMesh* CEdge::getMesh()
{
	return mesh;
}
void CEdge::operator =(CEdge e)
{
	it=e.it;
	v0_cur=e.v0_cur;
	v1_cur=e.v1_cur;
}

CVector CEdge::getNormal()
{
	CVector v=vDir();
	float u=argu(v)+ pi/2;
	v=polarc(1,u);
	return v;
}
void CEdge::setVector(CVector v,int i)
{
 CVector vi=VertexPos(1);
 CVector vo=VertexPos(0);
 //if(i==-1)
 //{
 if(i<1)
 {
	CVector v1=vo+v;
	v1_cur=v1;
	v0_cur=vo;
	sjt->v=v1;
 }else 
	 if(i==1)
 {
	CVector v1=vi-v;
	v0_cur=v1;
	v1_cur=vi;
	sit->v=v1;
 }
}

CVector CEdge::getVector(int i)
{
	if(i==0) return VertexPos(0);
	if(i==1) return VertexPos(1);
 CVector vi=VertexPos(1);
 CVector vo=VertexPos(0);

 CVector v1=vi-vo;
 if(vi==vo) return CVector(0,0,0);
 return v1;
}

CVector CEdge::vDir()
{
 CVector vi=VertexPos(1);
 CVector vo=VertexPos(0);

 CVector v1=vi-vo;
 if(vi==vo) return CVector(0,0,0);
 v1.Normalise();
 return v1;
}

float CEdge::project(CVector v, CVector *n)
{
	CVector t=vDir();
	float u=pointtoVector(t,v,n);
	return u;
/*	CVector vor=VertexPos(0);
	CVector ven=VertexPos(1);
	CAABB box;
	box.add(vor);
	box.add(ven);
	if(n!=NULL)
	{
		if(box.containpts(*n))
			return u;
	}
	else
		return 1E10;*/
}

void CEdge::RemoveAdjTri(int i)
{
	vector<int*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(**iter2==i)
		{
			iter=iter2;
			break;
		}
		iter2++;
	}
	if(iter!=adjT.end())
	{
		adjT.erase(iter);
		adjt--;
	}

}

void CEdge::RemoveAdjTri()
{
	vector<int*>::iterator iter;

	iter=adjT.begin();
	CTriangle* t;
	while(iter!=adjT.end())
	{
		t=mesh->Triangle(**iter);
		int i=**iter;
		mesh->DeleteTri(i);
	}

}


void CEdge::initcopy(CEdge* e)
{
	it=e->it;
	sit=mesh->Vertex(e->sit->sit);
	sjt=mesh->Vertex(e->sjt->sit);
	sit->addAdjE(this);
	sjt->addAdjE(this);
	vector<int*>::iterator it=e->adjT.begin();
	int i=0;
	while(it!=e->adjT.end())
	{
		adjT.push_back(e->adjT[i]);//mesh->Tri(**it));
		it++;i++;
	}
	adjt=e->adjt;
	constrained=e->constrained;
	v0_cur=e->v0_cur;
	v1_cur=e->v1_cur;
}
void CEdge::initcopy2(CEdge* e,int j)
{
	it=e->it;
	sit=mesh->Vertex(e->sit->sit+j);
	sjt=mesh->Vertex(e->sjt->sit+j);
	sit->addAdjE(this);
	sjt->addAdjE(this);
	vector<int*>::iterator it=e->adjT.begin();
	int i=0;
	while(it!=e->adjT.end())
	{
		adjT.push_back(e->adjT[i]);//mesh->Tri(**it));
		it++;i++;
	}
	adjt=e->adjt;
	constrained=e->constrained;
	v0_cur=e->v0_cur;
	v1_cur=e->v1_cur;
}

bool CEdge::Disconnect()
{
	bool r=false;
	CVertex* v=sit;
	r|=v->RemoveAdjEdgei(this);
	if(v->getAdje()==0)
	{
		mesh->DeleteVertex(sit->sit);
	}
	v=sjt;
	r|=v->RemoveAdjEdgei(this);
	if(v->getAdje()==0)
	{
		mesh->DeleteVertex(sjt->sit);
	}
	return r;
}

void CEdge::DeleteAdjTri(int i)
{
	vector<int*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(**iter2==i)
		{
			iter=iter2;
			break;
		}
		iter2++;
	}
	if(iter!=adjT.end())
	{
		CTriangle* t;
		t=mesh->Triangle(**iter);
		int i=**iter;
		mesh->DeleteTri(i);
	}

}

int CEdge::intersect(CEdge *e,CVector& v)
{
	CVector v1;
	CRay m1(Vertex(0)->v,Vertex(1)->v,true);
	CRay m2(e->Vertex(0)->v,e->Vertex(1)->v,true);
	v1=m1.Intersect(m2);
	if((v1.x==1E-10)||(v1.y==1E-10))
		return 0;
	v=v1;
	return 1;

	float u=onEdge(v,v1);
	int n=0,p=0;
	if(u!=-1)
	{
		if(u!=0&&u!=1)
		{
			splitEdge(u);
			n=1;
		}
		else
			n=0;
	}

	u=e->onEdge(v,v1);
	if(u!=-1)
	{
		if(u!=0&&u!=1)
		{
			e->splitEdge(u);
			p=2;
		}
		else
			p=0;
	}
	return n+p;

}


bool CEdge::onRight(CVector v)
{
 CVector v1(Vertex(0)->v,Vertex(1)->v);
 CVector v2(Vertex(0)->v,v);
  return v1.dot(v2) >0;

}

int CEdge::intersect2(CEdge *e, CVector &v)
{
	CVector v1;
	CRay m1(Vertex(0)->v,Vertex(1)->v,false);
	CRay m2(e->Vertex(0)->v,e->Vertex(1)->v,true);
	v1=m2.Intersect(m1);
	if((v1.x==1E-10)||(v1.y==1E-10))
		return 0;
	v=v1;
	return 1;
}
