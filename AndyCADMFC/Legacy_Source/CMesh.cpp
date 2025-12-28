//
//  CMesh.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//
#include "pch.h"
#include "CMesh.h"
// Mesh.cpp: implementation of the CMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "CRender.h"
#include "CClipper.h"
#include "CTVector.h"
#include <queue>
using namespace std;


CCadView* CMesh::view=NULL;
//BYTE* CMesh::bits=NULL;*******
float* CMesh::zbuffer=NULL;
CRender* CMesh::render=NULL;
int bwidth,bheight;
//HWND hwnd;*******
//HDC hd=NULL;*******
//BITMAP bit;*******
int mapmode;
CSize winext;
CSize viewpext;
CPoint winorg;
CPoint vieworg;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMesh::CMesh(): tricount(0),stricount(0),edgecount(0),vertexcount(0),svertexcount(0),eit(0),vit(0)
{
	redraw=false;select=none;
}

CMesh::~CMesh()
{
	for(vector<CTriangle*>::iterator iter=strilist.begin();iter!=strilist.end();iter++)
	{
		if(!(*iter)->visible)
			delete *iter;
		else
        {
			int op=12;
        }
	}
	for(vector<CTriangle*>::iterator iter=trilist.begin();iter!=trilist.end();iter++)
	{
		delete *iter;
	}
	trilist.clear();
	for(iedge iter1=edgelist.begin();iter1!=edgelist.end();iter1++)
	{
		try{
            delete iter1->second;
		}catch(...)
		{
		}
	}
	edgelist.clear();
    
	for(ivertex iter2=vertexlist.begin();iter2!=vertexlist.end();iter2++)
	{
		try{
            delete iter2->second;
		}catch(...)
		{
		}
	}
	vertexlist.clear();
	for(ivertex  iter2=svertexlist.begin();iter2!=svertexlist.end();iter2++)
	{
		delete iter2->second;
	}
	svertexlist.clear();
	render->removeRegion(this);
}

int CMesh::addTri()
{
	trilist.resize(trilist.size()+1);
	tricount++;
	return trilist.size();
}
int CMesh::addTri(CTriangle* t)
{
	trilist.push_back(t);
	trilist[tricount]->updateAdj();
	trilist[tricount]->it=tricount;
	trilist[tricount]->setMesh(this);
	tricount++;
	return trilist.size();
}

int CMesh::SaddTri(CTriangle* t)
{
	strilist.push_back(t);
	strilist[stricount]->updateAdj();
	strilist[stricount]->setMesh(this);
	stricount++;
	return strilist.size();
}

void CMesh::addEdge(vector<CVector>& v1)
{
	CVertex* vs=NULL,*ve=NULL;
	CEdge* e;
	bool _b=false,_e=false;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(pointinRegion(iter->second->v,v1[0]))
		{
			vs=iter->second;
			_b=true;
		}
		if(pointinRegion(iter->second->v,v1[1]))
		{
			ve=iter->second;
			_e=true;
		}
        
	}
	if(_b&&_e)
	{
        if(vs->EdgesTarget().size()==1)
            e=new CEdge(vs,ve);
        else if(vs->EdgesSource().size()==1)
            e=new CEdge(ve,vs);
	}
    //	edgelist.insert(make_pair(eit,e));
    //	edgelist[eit]->it=eit;
    //	edgelist[eit]->setMesh(this);
    //	eit++;
    //	edgecount++;
	
}

int CMesh::addEdge()
{
    //	edgelist.resize(edgelist.size()+1);
	edgelist.insert(make_pair(eit, new CEdge()));
	eit++;
	edgecount++;
	return edgelist.size();
}
int CMesh::addEdge(CEdge* e,bool _ready)
{
	if(_ready)
	{
        edgelist.insert(make_pair(e->it,e));
        edgelist[e->it]->setMesh(this);
	}else
	{
        iedge vi;
        int i=0;
        if(edgelist.size()>0)
        {
            vi=edgelist.find(i);
            while(vi!=edgelist.end())
            {
                vi=edgelist.find(i);
                i++;
            }
        }
        i=i>0?i:i+1;
        if(i==5)
        {
            int j=0;
        }
        edgelist.insert(make_pair(i-1,e));
        edgelist[i-1]->it=i-1;
        edgelist[i-1]->setMesh(this);
        eit++;
	}
	edgecount++;
	return edgelist.size();
}
int CMesh::addVertex()
{
    //	vertexlist.resize(vertexlist.size()+1);
	vertexcount++;
	vertexlist.insert(make_pair(vertexcount, new CVertex()));
	return vertexlist.size();
}
CVertex* CMesh::addVertex(CVertex* v,bool _ready)
{
	CVertex* result;
	if(_ready)
	{
        vertexlist.insert(make_pair(v->sit,v));
        vertexlist[v->sit]->setMesh(this);
        result=vertexlist[v->sit];
	}else
	{
        ivertex vi;
        int i=0;
        if(vertexlist.size()>0)
        {
            vi=vertexlist.find(i);
            while(vi!=vertexlist.end())
            {
                vi=vertexlist.find(i);
                i++;
            }
        }
        i=i>0?i:i+1;
        vertexlist.insert(make_pair(i-1,v));
        vertexlist[i-1]->sit=i-1;
        vertexlist[i-1]->setMesh(this);
        result=vertexlist[i-1];
	}
	vertexcount++;
	return result;
}
int CMesh::SaddVertex(CVertex* v)
{
	svertexlist.insert(make_pair(v->sit,v));
	svertexlist[v->sit]->setMesh(this);
	svertexcount++;
	return svertexlist.size();
}

void CMesh::empty()
{
	emptyscreen();
    trilist.clear();
    edgelist.clear();
    vertexlist.clear();
    s_vertex.clear();
    vertexcount=0;
    edgecount=0;
    tricount=0;
    eit=0;
    vit=0;
}
/*
void CMesh::displayTri(CDC *hdc,CVector loc[2],CCVector lit[6],col* mytext,int pwidth,int pheight,light *l)
{
    
	int c=displaytrilist.size();
    
	if(zbuffer==NULL)
	{
		return;
	}
    
	DWORD tick=GetTickCount();
	DWORD prevtick=0;
    
	int i=0;int w=0;
	hd=hdc->GetSafeHdc();
    
	CBitmap* bmp=view->bmp;
	HBITMAP jj=(HBITMAP)bmp->GetSafeHandle();
    
	BITMAP nb;
	int j=GetObject(jj,sizeof(BITMAP),NULL);
	int h=GetObject(jj,j,&nb);
	if(h==0)
	{
		return;
	}
    //	bmp->GetObject(&nb);
	DWORD d=nb.bmWidth*nb.bmHeight*4;
    
    
	bits=new BYTE[d];
	memset(bits,0,d);
	bmp->GetBitmapBits(d,bits);
    
	
	for(vector<CTriangle*>::iterator iter=trilist.begin();iter!=trilist.end();iter++)
	{
        (*iter)->isDegenerate(hd);
        (*iter)->rasterizeTriangle(hd,bits,zbuffer,bheight,bwidth,mytext,pwidth,pheight,l);//display(hdc,loc,lit);
        
	}
	view->bmp->SetBitmapBits(bwidth*bheight*4,bits);
    
	delete [] bits;
    
    
}*///*********

void CMesh::displayEdge(CDC *hdc)
{
    //	box.empty();
	for(iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
	{
		if(!iter->second) continue;
		iter->second->display(hdc);
		
	}
}
void CMesh::updateTri()
{
	displaytrilist.clear();
	for(vector<CTriangle*>::iterator iter=trilist.begin();iter!=trilist.end();iter++)
	{
		(*iter)->setMesh(this);
	}
    
	for(ivertex i=vertexlist.begin();i!=vertexlist.end();i++)
	{
		i->second->setMesh(this);
	}
    
}
void CMesh::setConstrainedVertex(int i)
{
	vertexlist[i]->setConstrained(true);
}
void CMesh::setConstrainedEdge(int i)
{
	edgelist[i]->setConstrained(true);
}

void CMesh::displayVertex(CDC *hdc)
{
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
	//	iter->second->display(hdc);*******
	}
    //	DelaunayTri();
    //	displayEdge(hdc);
}


void CMesh::DelaunayTri()
{/*
  // 2D Delauney triangulation in the X-Y plane. (Z coordinates of polygon vertices ignored)
  int	i, j, k, m;					// indices of four points
  double xn, yn, zn;				// outward vector normal to (i,j,k)
  int	flag;						// TRUE if m above of (i,j,k)
  double *z;
  
  ASSERT(vertexcount > 2);
  
  //	if (!TriPoly->SetSize((vertexcount-2)*3)) // Resize to max size needed, but set
  //		return FALSE;						// TriPoly.m_n=0 so it can be incremented
  //	TriPoly->m_n = 0;						// in the loop.
  
  z = new double[vertexcount];
  if (z == NULL) return FALSE;
  
  for (i=0; i<vertexcount; i++)
  z[i] = vertexlist[i].x*vertexlist[i].x + vertexlist[i].y*vertexlist[i].y;
  
  // For each triple (i,j,k)
  for ( i = 0; i < vertexcount - 2; i++ )
  for ( j = i + 1; j < vertexcount; j++ )
  for ( k = i + 1; k < vertexcount; k++ )
  if ( j != k ) {
  
  // Compute normal to triangle (i,j,k).
  xn = (vertexlist[j].y-vertexlist[i].y)*(z[k]-z[i]) - (vertexlist[k].y-vertexlist[i].y)*(z[j]-z[i]);
  yn = (vertexlist[k].x-vertexlist[i].x)*(z[j]-z[i]) - (vertexlist[j].x-vertexlist[i].x)*(z[k]-z[i]);
  zn = (vertexlist[j].x-vertexlist[i].x)*(vertexlist[k].y-vertexlist[i].y)
  - (vertexlist[k].x-vertexlist[i].x)*(vertexlist[j].y-vertexlist[i].y);
  flag = (zn < 0);
  if (flag)		// Only examine faces on bottom of paraboloid: zn < 0.
  for (m = 0; m < vertexcount; m++)	// For each other point m check if m above (i,j,k).
  flag = flag &&
  ((vertexlist[m].x-vertexlist[i].x)*xn +
  (vertexlist[m].y-vertexlist[i].y)*yn + (z[m]-z[i])*zn <= 0);
  if (flag) {
  (*TriPoly)[TriPoly->m_n++] = vertexlist[i];
  (*TriPoly)[TriPoly->m_n++] = vertexlist[j];
  (*TriPoly)[TriPoly->m_n++] = vertexlist[k];
  }
  }
  delete [] z;
  TriPoly->SetSize(TriPoly->m_n);		// Now resize to the actual size needed.
  return TRUE;*/
}

void CMesh::savefile(CFile &file)
{
    
	file.Write(&vertexcount, sizeof(int));
	file.Write(&edgecount, sizeof(int));
	file.Write(&tricount, sizeof(int));
	int i=0;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		iter->second->savefile(file);
		i++;
	}
	for(vector<CTriangle*>::iterator iter2=trilist.begin();iter2!=trilist.end();iter2++)
	{
		(*iter2)->savefile(file);
	}
	if(tricount==0)
	{
        for(iedge iter3=edgelist.begin();iter3!=edgelist.end();iter3++)
        {
            (iter3)->second->savefile(file);
        }
	}
}

struct vsame
{
	bool operator() (CVertex v1,CVertex v2)
	{
		return (v1.v==v2.v);
	}
};
void CMesh::openfile(CFile &file)
{
    
	int edcount=0,tcount=0,_vcount=0;
	tricount=0;
	file.Read(&_vcount, sizeof(int));
	file.Read(&edcount, sizeof(int));
	file.Read(&tcount, sizeof(int));
	vertexlist.clear();
	edgelist.clear();
	trilist.clear();
	bool b=false;
//	if(view->GetDocument()->m_objects->version>0) b=true;*******
	for(int i=0;i<_vcount;i++)
	{
        
		CVertex* t=new CVertex(this);
		t->openfile(file);
		addVertex(t,b);
        
        //		vertexlist.insert(make_pair(i,t));
        //		vertexlist[i]->sit=i;
		t=NULL;
	}
	for(int i=0;i<tcount;i++)
	{
		CTriangle t(this);
		t.openfile(file);
        //		CTriangle* t1=new CTriangle(Vertex(*t.sit),Vertex(*t.sjt),Vertex(*t.skt));
        //		t1->n=t.n;
        //		trilist.push_back(t1);
	}
	updateTri();
	if(tricount==0)
	{
		for(int i=0;i<edcount;i++)
		{
			CEdge* e=new CEdge;
			e->setMesh(this);
			e->openfile(file);
            //			new CEdge(e.sit,e.sjt);
		}
        
	}
    
}

long CMesh::Readfile(CFile &file)
{
	long  g;
	int edcount;
	file.Read(&vertexcount, sizeof(vertexcount));
	file.Read(&edcount, sizeof(edgecount));
	file.Read(&tricount, sizeof(tricount));
	trilist.clear();
	for(int i=0;i<vertexcount;i++)
	{
		CVertex t;
		g=t.Readfile(file);
	}
	for(int i=0;i<tricount;i++)
	{
		CTriangle t;
		g=t.Readfile(file);
	}
	if(tricount==0)
	{
        for(int i=0;i<edcount;i++)
        {
            CEdge e;
            g=e.Readfile(file);
        }
	}
	return g;
    
}


void CMesh::addVertex(int i,CVertex* v)
{
	ivertex vi=vertexlist.find(i);
	//if(vi==NULL) vertexcount++;*******
	vertexlist[i]=v;
	vertexlist[i]->sit=i;
	vertexlist[i]->setMesh(this);
    //	vertexcount++;
}

CMesh::CMesh(int i)
{
	for(int u=0;u<i;u++)
        vertexlist.insert(make_pair(u,new CVertex()));
}

void CMesh::resizevertex(int i)
{
	int h=vertexlist.size();
    //	vertexlist.resize(i);** need to update it to map
    vertexcount=i;
}

void CMesh::UpdateNormal(int i, CVector v)
{
	vertexlist[i]->n=v;
}

void CMesh::setWnd(CCadView *cad)
{
	view=cad;
}

void CMesh::updateShadingpara(CCVector lit[6],col* mytext,int pwidth,int pheight,light *l)
{
	texture=mytext;
	t_pwidth=pwidth;
	t_pheight=pheight;
	s_light=l;
}
/*
void CMesh::Bdraw()
{
	CBitmap* bmp=view->bmp;
	HBITMAP jj=(HBITMAP)bmp->GetSafeHandle();
    
	BITMAP nb;
    
	int j=GetObject(jj,sizeof(BITMAP),NULL);
	int h=GetObject(jj,j,&nb);
	if(h==0)
	{
		return;
	}
	DWORD d=nb.bmWidth*nb.bmHeight*4;
    
    
	zbuffer=new float[nb.bmWidth*nb.bmHeight];
	bwidth=nb.bmWidth;
	bheight=nb.bmHeight;
	memset(zbuffer,0,nb.bmWidth*nb.bmHeight*4);
	d=nb.bmWidth*nb.bmHeight;
	CVector v;
}

void CMesh::Edraw(CDC* hdc)
{
    render->displayTri(hdc);
    delete [] zbuffer;
    zbuffer=NULL;
}


void CMesh::RUpdate(HDC hdc)
{
	render->Update(hdc);
}
*///***********
void CMesh::RWRender()
{
	render->addRegion(this);
}
void CMesh::setRender(CRender* r)
{
    render=r;
}

void CMesh::addtoRender()
{
    
}
void CMesh::updateBoxUV(CAABB& box)
{
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		CVector v=box.getParam(iter->second->v);
		iter->second->pun=v.x;
		iter->second->pvn=v.y;
        
	}
	
}

void CMesh::translate(CVector prevpos, CVector postpos)
{
	CVector m(prevpos,postpos);
    //	m.snaptoplane(m);
	if(select==all)
	{
        for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
        {
            iter->second->v+=m;
        }
	}
	else
	{
        for(ivertex iter=s_vertex.begin();iter!=s_vertex.end();iter++)
        {
            iter->second->v+=m;
        }
	}
}

void CMesh::Rotate(int sens,CVector prevpoint,CVector postpoint,CVector rotateCenter)
{
    
	CTVector vh;
    
    
	double alphab=argu(postpoint)-argu(prevpoint);//-argu(piv);
	float angle=alphab;
    
	CVector v00,v01;
	CTVector vt;
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
	vt.Translate(rotateCenter);
	vt.endT();
	ivertex iv=vbegin();
	if(select==all)
	{
        for(iv=vbegin();iv!=vend();iv++)
        {
            iv->second->assign(*iv->second);
        }
	}
	else if(select==vertex)
	{
		for(iv=svbegin();iv!=svend();iv++)
		{
            iv->second->assign(*iv->second);
		}
        
	}
    
	vt.popTransform();
    
}
CVertex* CMesh::getVertex(float u)
{
	CVertex* u1;
	CVertex* u2;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(iter->second->un==u)
		{
			return iter->second;
		}
	}
}
CVector CMesh::getVector(float u)
{
	CVertex* u1;
	CVertex* u2;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(iter->second->un==u)
		{
			return iter->second->v;
		}
	}
	for(iedge iter1=edgelist.begin();iter1!=edgelist.end();iter1++)
	{
		float vun=iter1->second->End()->un;
		vun=(vun==0)?1:vun;
		if((iter1->second->Start()->un<u)&&(vun>=u))
		{
			float _u1=iter1->second->Start()->un;
			CVector vb=iter1->second->Start()->v;
			CVector ve=iter1->second->End()->v;
			CVector v=vb+polarc((u-_u1)*absc(ve-vb),argu(ve-vb));
			return v;
		}
	}
	return CVector(1E-10,1E-10);
    
    
}

bool CMesh::PtonVertex(CVector point,int& i)
{
	bool mv=false;
	s_vertex.clear();
	int j=0;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(pointinRegion(point,iter->second->v))
		{
			if(find(s_vertex.begin(),s_vertex.end(),*iter)==s_vertex.end())
			{
                s_vertex.insert(*iter);
				i=j;
			}
			mv=true;
		}
		j++;
	}
    
	if(!mv) s_vertex.clear();
	if(mv) select=vertex;
	return mv;
    
}

void CMesh::display(CDC* hdc)
{
/*	int c=displaytrilist.size();
    
	if(zbuffer==NULL)
	{
		return;
	}
    
	DWORD tick=GetTickCount();
	DWORD prevtick=0;
    
	int i=0;int w=0;
	hd=hdc->GetSafeHdc();
    
	CBitmap* bmp=view->bmp;
	HBITMAP jj=(HBITMAP)bmp->GetSafeHandle();
    
	BITMAP nb;
	int j=GetObject(jj,sizeof(BITMAP),NULL);
	int h=GetObject(jj,j,&nb);
	if(h==0)
	{
		return;
	}
	DWORD d=nb.bmWidth*nb.bmHeight*4;
    
    
	bits=new BYTE[d];
	memset(bits,0,d);
	bmp->GetBitmapBits(d,bits);
    
	for(ivertex iter1=vertexlist.begin();iter1!=vertexlist.end();iter1++)
	{
        iter1->second->toScreen(hd);
	}
	
	for(vector<CTriangle*>::iterator iter=trilist.begin();iter!=trilist.end();iter++)
	{
        //	(*iter)->isDegenerate(hd);
        (*iter)->rasterizeTriangle(hd,bits,zbuffer,bheight,bwidth,NULL,0,0,NULL);//display(hdc,loc,lit);
	}
	bmp->SetBitmapBits(d,bits);
	delete [] bits;*///***************************
}

bool CMesh::PtonRow(CVector point)
{
	bool mv=false;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(pointinRegion(point,(iter)->second->v))
		{
			if(find(s_vertex.begin(),s_vertex.end(),*iter)==s_vertex.end())
			{
				for(ivertex itero=vertexlist.begin();itero!=vertexlist.end();itero++)
					if((itero)->second->un==(iter)->second->un)
						s_vertex.insert(*itero);
			}
			mv=true;
		}
	}
    
	if(!mv) s_vertex.clear();
	if(mv) select=vertex;
	return mv;
}

bool CMesh::PtonCol(CVector point)
{
	bool mv=false;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(pointinRegion(point,(iter)->second->v))
		{
			if(find(s_vertex.begin(),s_vertex.end(),*iter)==s_vertex.end())
			{
				for(ivertex itero=vertexlist.begin();itero!=vertexlist.end();itero++)
					if((itero)->second->vn==(iter)->second->vn)
						s_vertex.insert(*itero);
			}
			mv=true;
		}
	}
    
	if(!mv) s_vertex.clear();
	if(mv) select=vertex;
	return mv;
    
}

void CMesh::copy(const CMesh *m)
{
	empty();
	s_light=m->s_light;
	texture=m->texture;
	t_pwidth=m->t_pwidth;
	t_pheight=m->t_pheight;
    
	int i=0,j=0;
	CAABB box;
	for(i=0;i<m->vertexcount;i++)
	{
        //		CVertex* v1=new CVertex(this);
        //		v1->initcopy(m->vertexlist[i]);
        //		addVertex(v1);
        //		box.add(v1->v);
	}
    /*	CQuadTree qt;
     for(i=0;i<m->edgecount;i++)
     {
     qt.insert(m->edgelist[i]);
     CEdge* e1=new CEdge();
     *e1=*m->edgelist[i];
     addEdge(e1);
     }
     */
	for(i=0;i<m->edgecount;i++)
	{
        //		CEdge* e1=new CEdge();
        //		e1->initcopy(m->edgelist[i]);
        //		addEdge(e1);
	}
	for(i=0;i<m->tricount;i++)
	{
        //		CTriangle* t1=new CTriangle();//Vertex(t->sit),Vertex(t->sjt),Vertex(t->skt));
        //		*t1=*m->trilist[i];
        //		addTri(t1);
	}
    //	trilist.resize(m->trilist.size());
	for(i=0;i<tricount;i++)
	{
		CTriangle *tx=new CTriangle();
		*tx=*m->trilist[i];
		tx->initcopy(m->trilist[i]);
		addTri(tx);
	}
    
    //	vertexlist.resize(m->vertexlist.size());
	map<int,CVertex*> mv=m->vertexlist;
	map<int,CEdge*> me=m->edgelist;
	for(ivertex v=mv.begin();v!=mv.end();v++)
	{
		CVertex* vx=new CVertex(this);
		
		//		CVertex* vb=vertexlist[i];
		*vx=*v->second;//(mv[i]);
		vx->initcopy(v->second);//mv[i]);
		addVertex(vx,true);
		box.add(vx->v);
	}
    //	edgelist.resize(m->edgelist.size());
	for(iedge e=me.begin();e!=me.end();e++)
	{
		CEdge* ex=new CEdge();
        //		*ex=*e->second;
		ex->setMesh(this);
		ex->initcopy(e->second);
		addEdge(ex,true);
        //		addEdge(ex);
	}
	updateTri();
    
}
void CMesh::add(const CMesh *m)
{
	s_light=m->s_light;
	texture=m->texture;
	t_pwidth=m->t_pwidth;
	t_pheight=m->t_pheight;
    
	int i=0,j=vertexlist.size();
	CAABB box;
	for(i=0;i<tricount;i++)
	{
		CTriangle *tx=new CTriangle();
		*tx=*m->trilist[i];
		tx->initcopy(m->trilist[i]);
		addTri(tx);
	}
    
	//CVector v0=vertexlist[j-1],v1=m->vertexlist[0],v2=m->vertexlist[1];
    
    //	vertexlist.resize(m->vertexlist.size());
	map<int,CVertex*> mv=m->vertexlist;
	map<int,CEdge*> me=m->edgelist;
	for(ivertex v=mv.begin();v!=mv.end();v++)
	{
		CVertex* vx=new CVertex(this);
		
		//		CVertex* vb=vertexlist[i];
		*vx=*v->second;//(mv[i]);
		vx->initcopy(v->second);//mv[i]);
		vx->sit=j+v->second->sit;
		addVertex(vx,true);
		box.add(vx->v);
	}
    //	edgelist.resize(m->edgelist.size());
    
	for(iedge e=me.begin();e!=me.end();e++)
	{
		CEdge* ex=new CEdge();
        //		*ex=*e->second;
		ex->setMesh(this);
		ex->initcopy2(e->second,j);
        //		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		addEdge(ex,false);
        //		addEdge(ex);
	}
	updateTri();
    
}

void CMesh::emptyscreen()
{
	for(vector<CTriangle*>::iterator iter=strilist.begin();iter!=strilist.end();iter++)
	{
		if(!(*iter)->visible)
			delete *iter;
	}
    
	for(iedge iter1=sedgelist.begin();iter1!=sedgelist.end();iter1++)
	{
        delete iter1->second;
	}
	for(ivertex iter2=svertexlist.begin();iter2!=svertexlist.end();iter2++)
	{
		delete iter2->second;
	}
	strilist.clear();
	sedgelist.clear();
	svertexlist.clear();
	stricount=0;
	svertexcount=0;
	eit=0;
	vit=0;
}

vector<CVertex*> CMesh::getVertexList()
{
	vector<CVertex*> _v;
	_v.resize(vertexlist.size());
	int i=0;
	for(ivertex v=vertexlist.begin();v!=vertexlist.end();v++)
	{
		_v[i]=v->second;
		i++;
	}
	return _v;//vertexlist;
}
void CMesh::setEdge(CVector v,int i,int j)
{
	edgelist[i]->setVector(v,j);
}
CVector CMesh::getEdge(int i,int j)
{
	return edgelist[i]->getVector(j);
}
vector<CEdge*> CMesh::getEdgeList()
{
	vector<CEdge*> _v;
	_v.resize(edgelist.size());
	int i=0;
	for(iedge v=edgelist.begin();v!=edgelist.end();v++)
	{
		_v[i]=v->second;
		i++;
	}
	return _v;
}

vector<CVector> CMesh::getVectors()
{
	vector<CVector> vl;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		vl.push_back((iter)->second->v);
	}
	return vl;
}
float CMesh::getSUVertex()
{
	return s_vertex.begin()->second->un;
}
void CMesh::UpdateSelectedVertex()
{
	if(select==all)
	{
        for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
        {
            (iter)->second->v.assign((iter)->second->v,true);
        }
	}
	else
        if(select==vertex)
        {
            for(ivertex iter=s_vertex.begin();iter!=s_vertex.end();iter++)
            {
                (iter)->second->v.assign((iter)->second->v,true);
            }
        }
    
}
void CMesh::UpdateVertex()
{
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		(iter)->second->v.assign((iter)->second->v,true);
	}
    
}

void CMesh::copy(const CMesh &m)
{
	copy(&m);
}

CVertex* CMesh::addVertexonEdge(CVector v)
{
	CVector v1;
	CVertex* vx=NULL;;
	float u;
	int n;
	for(iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
	{
		u=(iter)->second->onEdge(v,v1);
		if(u!=-1)
		{
			n=(iter)->second->it;
			vx=(iter)->second->splitEdge(u);
			DeleteEdge(n);
			return vx;
		}else
		{
            
			int j=0;
		}
		
	}
	return false;
    
}

bool CMesh::PtonEdge(CVector point, CVector &v,float& u, CVector& uv)
{//
//	DWORD tick=GetTickCount();******
	for(iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
	{
		u=(iter)->second->onEdge(point,v);
		uv.x=(iter)->second->Start()->sit;
		uv.y=(iter)->second->End()->sit;
		uv.z=(iter)->first;
		if(u!=-1)
		{
            //			addVertex(vertexcount+1,new CVertex(v));
			select=all;
			return true;
		}
		
	}
	select=none;
//	DWORD ptick=GetTickCount()-tick;
//	CString s;
//	s.Format("time spend to Select an Edge:%d \n",ptick);
//	TRACE(s);*************
    
	return false;
    
}
void CMesh::operator = ( CMesh* m)
{
    copy(m);
}
void CMesh::operator = ( CMesh m)
{
    copy(&m);
}

CVector CMesh::Vector(int i)
{
	return *vertexlist[i];
}

void CMesh::offset(float u,CMesh* f)
{
	CVector v;
	ivertex iter1=f->vertexlist.begin();
	ivertex iter2;
	CVector prv;
	vector<CVertex*> col;
	col.push_back(vertexlist.begin()->second);
	bool clip=false;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++,iter1++)
	{
		v=(iter)->second->getEdgeOffset(u);
		(iter1)->second->v=v;
		iter2=iter;
		iter2--;
		if((iter!=vertexlist.begin())&&((iter2)->second->v==iter->second->v))
			(iter1)->second->v=prv;
		vector<CEdge*> e1=iter1->second->getAdjE();
		vector<CEdge*> e2=iter->second->getAdjE();
		if(iter!=vertexlist.begin())
		{
			iter2=iter1;
			if(clip)
			{
				iter2--;
				iter2--;
				vector<CEdge*> e3=iter2->second->getAdjE();
				CVector v;
				if(e1[0]->intersect2(e3[0],v))
				{
                    iter2->second->v=v;
                    iter2++;
                    iter2->second->v=v;
                    clip=false;
				}
			}
		}
        
		if(e1[0]->vDir()==-e2[0]->vDir())
		{
			clip=true;
		}
		prv=v;
	}
    
}

float CMesh::min_dist_toEdge(CVector v, int *n)
{
	float u=1E10,u1;
	float v1,v2;
	CVector n1;
	vector<float> vf;
	for(iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
	{
		u1=(iter)->second->project(v,&n1);
		v1=(u1>0)?u1:-u1;
		v2=(u>0)?u:-u;
		u=(v2<v1)?u:u1;
	}
	return u;
    
}

void CMesh::deleteSVertex()
{
	if(select==vertex)
	{
        for(ivertex iter=s_vertex.begin();iter!=s_vertex.end();iter++)
        {
            DeleteVertex((iter)->second->sit);
        }
        s_vertex.clear();
	}
    
}

CMesh::ivertex CMesh::DeleteVertex(int vertexIndex)
{
	try{
        if(vertexIndex<vertexcount)
        {
            //		ivertex v1=vertexlist.erasefind(vertexlist.begin()
            vertexlist[vertexIndex]->RemoveAdjEdge();
            vertexlist[vertexIndex]->RemoveAdjTri();
            ivertex v=vertexlist.erase(vertexlist.find(vertexIndex));
            //	ivertex v=vertexlist.erase(vertexIndex);//&vertexlist[vertexIndex]);
            //	while(v!=vertexlist.end())
            //	{
            //		(*v)->sit--;
            //		v++;
            //	}
            vertexcount--;
            return v;
        }
	}catch(...)
	{
	}
	return vertexlist.end();
    
}

CMesh::itri CMesh::DeleteTri(int triIndex)
{
	if(triIndex<tricount)
	{
        trilist[triIndex]->Disconnect();
        delete trilist[triIndex];
        itri v=trilist.erase(trilist.begin()+triIndex);
     //   itri v=trilist.erase(&trilist[triIndex]);
        while(v!=trilist.end())
        {
            (*v)->it--;
            v++;
        }
        tricount--;
        return v;
	}
	return trilist.end();
}

CMesh::iedge CMesh::DeleteEdge(int edgeIndex)
{
	if(edgelist.find(edgeIndex)!=edgelist.end())
	{
        edgelist[edgeIndex]->RemoveAdjTri();
        edgelist[edgeIndex]->Disconnect();
        iedge e=edgelist.erase(edgelist.find(edgeIndex));//edgelist[edgeIndex]);
        edgecount--;
        
        return e;
	}else
        return edgelist.end();
    
}

int* CMesh::Tri(int i)
{
	return &trilist[i]->it;
}

int CMesh::iEdge(int i)
{
	return edgelist[i]->it;
}

int CMesh::iVertex(int i)
{
	return vertexlist[i]->sit;
}
void CMesh::breakEdge(CVector v1)
{
	CMesh m;
	m.copy(this);
	CVertex* v=addVertexonEdge(v1);
	CVertex* ve=Vertex(Vcount()-2);
	if(v)
		v->RemoveFwdEdge(ve);
}
void CMesh::breakEdge2(CVector v1)
{
	CMesh m;
	m.copy(this);
	CVertex* v=addVertexonEdge(v1);
	CVertex* vb=Vertex(0);
	if(v)
		vb->RemoveFwdEdge(v);
}
float CMesh::getU(CVector v1)
{
	CMesh m;
	m.copy(this);
	CVertex* v=m.addVertexonEdge(v1);
	return v->un;
}
void CMesh::breakEdge(CVector v1, CVector v2)
{
	CMesh m;
	m.copy(this);
	CVertex* v=addVertexonEdge(v1);
	CVertex* v11=addVertexonEdge(v2);
	if(v->un<v11->un)
		v->RemoveFwdEdge(v11);
	else
		v11->RemoveFwdEdge(v);
    
    /*
     vector<CEdge*> e=getCurve(v,v11);
     vector<CEdge*>::iterator i=e.begin();
     if(i==e.end())
     {
     copy(&m);
     return;
     
     }
     while(i!=e.end())
     {
     DeleteEdge((*i)->it);
     i++;
     }
     */
    
}
bool CMesh::Close()
{
	CVertex *vs=NULL,*ve=NULL;
	CEdge* e;
	vector<CVertex*> unvs;
	vector<CVertex*> unve;
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(iter->second->getValence()==1)
		{
			vector<CVertex*> iv=iter->second->EdgesSource();
			if(iv.size()==1)
			{
				vs=iter->second;//iv[0];
				unve.push_back(vs);
				continue;
			}
			iv=iter->second->EdgesTarget();
			if(iv.size()==1)
			{
				ve=iter->second;//iv[0];
				unvs.push_back(ve);
				continue;
			}
            
		}
	}
	int i0=unvs.size();
	int _u=-1;
	float _f,_f1;
	vector<int> _uv;
	for(int i=0;i<i0;i++)
	{
		_f=10E5;
		_u=-1;
		for(int j=0;j<i0;j++)
		{
			if(find(_uv.begin(),_uv.end(),j)!=_uv.end()) continue;
			_f1=absc(unvs[i]->v-unve[j]->v);
			if(_f1<_f)
			{
				if(unvs[i]->isConnectedTo(unve[j])) continue;
				_u=j;
				_f=_f1;
			}
		}
		if(_u!=-1)
		{
			_uv.push_back(_u);
			new CEdge(unvs[i],unve[_u],Ecount());
		}
	}
    if(isClosed()) return true;
    return false;
    /*	while(true)
     {
     random_shuffle(unve.begin(),unve.end());
     for(int i=0;i<i0;i++)
     {
     new CEdge(unvs[i],unve[i],Ecount());
     }
     if(isClosed()) return;
     else
     {
     for(int i=0;i<i0;i++)
     {
     DeleteEdge(Ecount()-1);
     }
     }
     
     }*/
}

bool CMesh::isClosed()
{
	CEdge* e=edgelist[Ecount()-1];
	CVertex *vs=vertexlist.begin()->second;//[0];
    //	CVertex *ve=vertexlist[Vcount()-1];
    //	return ((e->Start()==ve)&&(e->End()==vs));
	vs->n.xhit=0;
	vs->n.yhit=Vcount()-1;
	return vs->isConnectedTo2(vs);
}
void CMesh::cleanCurve()
{
	for(ivertex iter=vertexlist.begin();iter!=vertexlist.end();iter++)
	{
		if(!(iter->second->getValence()))
		{
			iter=DeleteVertex(iter->second->sit);
		}
	}
}
vector<CEdge*> CMesh::getCurve(CVertex *v1, CVertex *v2)
{
	vector<CEdge*> ev;
	int i=0;
	CVertex* vo=v1;
	vector<CVertex*> iv=v1->EdgesSource();
	queue<CVertex*> vb;
	vb.push(iv[i]);
	CEdge* e=Edge(iv[i]->sit);
	vo=e->Mate(v1);
	ev.push_back(e);
    
	if(is_answer(vo,v2)) return ev;
    
    //	while(!vb.empty())
    //	{
    //		prepare_move();
    while(next_move(&vo,ev))
    {
        if(is_answer(vo,v2)) return ev;
        //			vb.push(iv[i++]);
    }
    ev.clear();
    return ev;
    //		int m=vb.front();
    //		vb.pop();
    //		make_move(vo,ev);
    //	}
    
}

bool CMesh::is_answer(CVertex *v1,CVertex* v2)
{
	return v1==v2;
}

bool CMesh::next_move(CVertex** v1,vector<CEdge*>& ev)
{
	vector<CVertex*> iv=(*v1)->EdgesSource();
	CVertex* vo;
	for(vector<CVertex*>::iterator i=iv.begin();i!=iv.end();i++)
	{
		CEdge* e=Edge((*i)->sit);
		vo=e->Mate(*v1);
		if(!vo->checked)
		{
			*v1=vo;
			(*v1)->checked=true;
			make_move((*i)->sit,ev);
			return true;
		}
	}
	return false;
}

void CMesh::make_move(int i,vector<CEdge*>& ev)
{
	CEdge* e=Edge(i);
	ev.push_back(e);
}

void CMesh::intersect(CQuadTree *q1, CQuadTree *q2, string option)
{
    
}

void CMesh::TrimEdge(vector<CVector> &vn,CMesh *m,bool side,bool st)
{
	vector<CEdge*> vedge;//=edgelist;
    //	vector<int,CEdge*> vmedge=m->edgelist;
	vector<CVector> vmn;
	CVector v;
	
	int u;
    
    
	for(CMesh::iedge iter2=m->edgelist.begin();iter2!=m->edgelist.end();iter2++)
	{
		for(CMesh::iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
		{
			u=iter->second->intersect(iter2->second,v);
			if(u!=0)
			{
				float r=0,r0=0;
				bool cd=false;
				for(vector<CVector>::iterator rd=vn.begin();rd<vn.end();rd++)
				{
					r0=absc(*rd-v);
					if(r0<1)
					{
						cd=true;
					}
				}
				if(!cd)
					vn.push_back(v);
			}
		}
	}
    
    
	vector<CVector>::iterator it=vn.begin(),jt=vn.end();
	while(it!=jt)
	{
		addVertexonEdge(*it);
		m->addVertexonEdge(*it);
		it++;
	}
	vedge.resize(edgelist.size());
	//vedge=edgelist;
	vector<CEdge*>::iterator ie=vedge.begin(),j=vedge.end();
	iedge i1=edgelist.begin();
	int i=0;
	while(ie!=j)
	{
		CEdge* ex=new CEdge();
        //		*ex=*edgelist[i];
		ex->setMesh(i1->second->getMesh());
		ex->initcopy(i1->second);
		vedge[i]=ex;
		ie++;i1++;i++;
	}
	ie=vedge.begin(),j=vedge.end();
    //	while(ie!=j)
    //	{
    //		(*ie)->flip();
    //		ie++;
    //	}
	vector<CEdge*>::iterator ie1=vedge.begin();
	j=vedge.end();
	i1=edgelist.begin();
	while(ie1!=j)
	{
		if(side)
		{
			if(!m->inPolygon2(*ie1))
			{
				i1=DeleteEdge((i1)->second->it);
			}else
			{
				i1++;
			}
		}
		else
		{
			if(m->inPolygon3(*ie1,st))
			{
				i1=DeleteEdge((i1)->second->it);
			}else{
                i1++;
			}
		}
		ie1++;
	}
    
}
void CMesh::TrimEdge3(CVector v,CMesh *m)
{
	vector<CEdge*> vedge;//=edgelist;
    //	vector<int,CEdge*> vmedge=m->edgelist;
	vector<CVector> vn;
	CVector vm;
	CVector v01=v;
	int u;
    CEdge* eg=NULL;
    for(CMesh::iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
    {
        if(iter->second->onEdge(v01,vm)!=-1)
            eg=iter->second;
        
    }
	for(CMesh::iedge iter2=m->edgelist.begin();iter2!=m->edgelist.end();iter2++)
	{
        u=eg->intersect(iter2->second,v);
        if(u!=0)
        {
            float r=0,r0=0;
            bool cd=false;
            for(vector<CVector>::iterator rd=vn.begin();rd<vn.end();rd++)
            {
                r0=absc(*rd-v);
                if(r0<1)
                {
                    cd=true;
                }
            }
            if(!cd)
                vn.push_back(v);
        }
	}
    
    
	vector<CVector>::iterator it=vn.begin(),jt=vn.end();
	while(it!=jt)
	{
		addVertexonEdge(*it);
		m->addVertexonEdge(*it);
		it++;
	}
	try{
		for(CMesh::iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
		{
			if(iter->second->onEdge(v01,vm)!=-1)
			{
				DeleteEdge(iter->second->it);
				return;
			}
		}
	}catch(...)
	{
//		AfxMessageBox(_T("Trim Delete Egde Problem"));
	}
}

void CMesh::TrimEdge2(vector<CVector> &vn,CMesh *m,bool side,bool st)
{
	vector<CEdge*> vedge;//=edgelist;
    //	vector<int,CEdge*> vmedge=m->edgelist;
	vector<CVector> vmn;
	CVector v;
	
	int u;
    
    
	for(CMesh::iedge iter2=m->edgelist.begin();iter2!=m->edgelist.end();iter2++)
	{
		for(CMesh::iedge iter=edgelist.begin();iter!=edgelist.end();iter++)
		{
			u=iter->second->intersect(iter2->second,v);
			if(u!=0)
			{
				float r=0,r0=0;
				bool cd=false;
				for(vector<CVector>::iterator rd=vn.begin();rd<vn.end();rd++)
				{
					r0=absc(*rd-v);
					if(r0<1)
					{
						cd=true;
					}
				}
				if(!cd)
					vn.push_back(v);
			}
		}
	}
    
    
	vector<CVector>::iterator it=vn.begin(),jt=vn.end();
	while(it!=jt)
	{
		addVertexonEdge(*it);
		m->addVertexonEdge(*it);
		it++;
	}
	vedge.resize(edgelist.size());
	//vedge=edgelist;
	vector<CEdge*>::iterator ie=vedge.begin(),j=vedge.end();
	iedge i1=edgelist.begin();
	int i=0;
	while(ie!=j)
	{
		CEdge* ex=new CEdge();
        //		*ex=*edgelist[i];
		ex->setMesh(i1->second->getMesh());
		ex->initcopy(i1->second);
		vedge[i]=ex;
		ie++;i1++;i++;
	}
	ie=vedge.begin(),j=vedge.end();
    //	while(ie!=j)
    //	{
    //		(*ie)->flip();
    //		ie++;
    //	}
	vector<CEdge*>::iterator ie1=vedge.begin();
	j=vedge.end();
	i1=edgelist.begin();
	while(ie1!=j)
	{
		if(side)
		{
			if(!m->inPolygon2(*ie1))
			{
				i1=DeleteEdge((i1)->second->it);
			}else
			{
				i1++;
			}
		}
		else
		{
			if(m->inPolygon3(*ie1,st))
			{
				i1=DeleteEdge((i1)->second->it);
			}else{
                i1++;
			}
		}
		ie1++;
	}
    
}
void CMesh::IntersectEdge(CMesh *m,bool side)
{
    CMesh* m2 = new CMesh;
	m2->copy(this);
    CMesh* m3 = new CMesh;
	m3->copy(m);
	vector<CVector> v1;
	TrimEdge(v1,m);
	vector<CVector> v2;
	m3->TrimEdge(v2,m2);
	for(iedge iter2=m3->edgelist.begin();iter2!=m3->edgelist.end();iter2++)
	{
		addEdge(iter2->second);
	}
    
}
void CMesh::IntersectEdge2(CMesh *m,bool side)
{
    CMesh* m2 = new CMesh;
	m2->copy(this);
    CMesh* m3 = new CMesh;
	m3->copy(m);
	vector<CVector> v1;
	TrimEdge2(v1,m,side);
    
}

bool CMesh::inPolygon(CEdge *e)
{
	CVector v=e->Start()->v+e->End()->v;
	v=v/2;
	CVector vc=v;
    bool result = false;
    if (vertexlist.size() < 3) return false;
    
	iedge i=edgelist.begin(),j=edgelist.end();
	CVector v1,v2;
	while(i!=j)
	{
		v1=(i)->second->VertexPos(0);
		v2=(i)->second->VertexPos(1);
        if (((v1.y <= vc.y) && (vc.y < v2.y)) || // an upward crossing
            ((v2.y <= vc.y) && (vc.y < v1.y)))   // a downward crossing
        {
            /* compute the edge-ray intersect @ the x-coordinate */
            if (vc.x - v1.x < ((v2.x - v1.x) * (vc.y - v1.y) / (v2.y - v1.y)))
            {
                result = !result;
            }
        }
        
		i++;
	}
    return result;
    
}



bool CMesh::inPolygon2(CEdge *e)
{
	CVector v=e->Start()->v+e->End()->v;
	v=v/2;
	CVector vc=v;
    
    int winding_number = 0;
    int j = edgelist.size();//polygon.size() - 1;
    CVector v1,v2;
    for(iedge i = edgelist.begin(); i!=edgelist.end() ; i++)
    {
        v1=i->second->VertexPos(0);
        v2=i->second->VertexPos(1);
        if (v1.y <= vc.y)
        {
            if ((v2.y >= vc.y) &&
                (orientation(v1,v2,vc) == -1))
            {
                winding_number++;
            }
        }
        else
        {
            if ((v2.y <= vc.y) &&
                (orientation(v1,v2,vc) == 1))
            {
                winding_number--;
            }
        }
    }
    return (winding_number != 0);
    
}



bool CMesh::isEdge(int i1, int i2)
{
	CVertex* v1= Vertex(i1);
	CVertex* v2= Vertex(i2);
    
	return v1->isConnectedTo(v2);
    
}

int CMesh::SaddEdge(CEdge *e)
{
	sedgelist.insert(make_pair(e->it,e));
	if(sedgelist.find(e->it)!=sedgelist.end())
		sedgecount++;
	return sedgelist.size();
    
}

CMesh* CMesh::clip(CDC *hdc,CMesh* m)
{
    CMesh* m2 = new CMesh;
	m2->copy(this);
    //	m2->TrimEdge(m,false);
	m2->IntersectEdge(m,false);
	return m2;
    
}
CMesh* CMesh::clip2(CDC *hdc,CMesh* m,bool side)
{
    CMesh* m2 = new CMesh;
	m2->copy(this);
    //	m2->TrimEdge(m,false);
	m2->IntersectEdge2(m,side);//false);
	return m2;
    
}
/*
CMesh* CMesh::clip3(CDC *hdc,CMesh* m,bool side)
{
    CMesh* m2 = new CMesh;
    //	m2->copy(this);
    //	m2->TrimEdge(m,false);
	ClipperLib::Path cb;
	cb.resize(vertexlist.size());
	for(int i=0;i<vertexlist.size();i++)
	{
		cb[i]=ClipperLib::IntPoint(vertexlist[i]->v.x*1000,vertexlist[i]->v.y*1000);
	}
	ClipperLib::Paths sub(1);
	sub[0]=cb;
	cb.clear();
	cb.resize(m->vertexlist.size());
	for(i=0;i<m->vertexlist.size();i++)
	{
		cb[i]=ClipperLib::IntPoint(m->vertexlist[i]->v.x*1000,m->vertexlist[i]->v.y*1000);
	}
	ClipperLib::Paths clp(1);
	clp[0]=cb;
	//get the intersection of the subject and clip polygons ...
    ClipperLib::Clipper clpr;
    clpr.AddPaths(sub, ClipperLib::ptSubject, true);
    clpr.AddPaths(clp, ClipperLib::ptClip, true);
    ClipperLib::Paths solution;
    clpr.Execute(ClipperLib::ctIntersection, solution, ClipperLib::pftEvenOdd, ClipperLib::pftEvenOdd);
	ClipperLib::Path cb1=solution[0];
	map<int,CVertex*> mv=m->vertexlist;
	map<int,CEdge*> me=m->edgelist;
	for(int i2=0;i2<cb1.size();i2++)
	{
		CVertex* vx=new CVertex(m2);
		
		//		CVertex* vb=vertexlist[i];
		*vx=CVector(cb1[i2].X/1000,cb1[i2].Y/1000);//(mv[i]);
		m2->addVertex(vx,true);
		box.add(vx->v);
	}
    
    //	edgelist.resize(m->edgelist.size());
	for(int i3=0;i3<cb1.size()-1;i3++)
	{
		m2->addEdge(new CEdge(m2->Vertex(i3),m2->Vertex(i3+1),m2->Ecount()));
	}
	
	return m2;
    
}
*///***************
bool CMesh::inPolygon3(CEdge *e,bool st)
{
	CVector v=e->Start()->v+e->End()->v;
	v=v/2;
	CVector vc=v;
    
    int winding_number = 0;
    int j = edgelist.size();//polygon.size() - 1;
    CVector v1,v2;
    bool b=true;
    for(iedge i = edgelist.begin(); i!=edgelist.end(); i++)
    {
        v1=i->second->VertexPos(1)-i->second->VertexPos(0);
        v2=vc - i->second->VertexPos(0);
        v= v1 * v2;
        if(v.z<=0)
        {
            if(st)
            {
                if(e->intersect(i->second,v1))
                    return true;
            }
            else
            {
                b=true;
                //			return true;
            }
        }else
        {
            //		if(!(box.containpts(i->second->VertexPos(1))&&box.containtpts(i->second->VertexPos(0))))
            return false;
        }
    }
    return true;
    
}

struct Ei 
{
    CVector v;
    int i1,i2;
    float f;
    Ei(int i11,float f1, int i22, CVector v2)
    {
        i1=i11;
        i2=i22;
        f=f1;
        v=v2;
    };
    
};
bool operator < (const Ei e1, const Ei e2)
{
    return e1.f<e2.f;
}


void CMesh::extendEdge(CMesh *m)
{
	map<int,CEdge*> vedge=edgelist;
	map<int,CEdge*> vmedge=m->edgelist;
	vector<CVector> vn,vmn;
	CVector v;
	CVector v1,v2;
	
	int u,iter2,jiter2;
	int nb= edgelist.size();
    //	Ei m;
    
    intersect_near(0,jiter2,m,v,iter2);
    if((iter2!=-1)&&(jiter2==0))
    {
        v1=edgelist[0]->VertexPos(0)-edgelist[0]->VertexPos(1);
        v2=v - edgelist[0]->VertexPos(1);
        if(absc(v1)<absc(v2))
            edgelist[0]->Start()->v=v;
    }
    //		if(nb>1)
    {
		intersect_near(edgecount-1,jiter2,m,v,iter2);
        if((iter2!=-1)&&(jiter2==1))
        {
            v1=edgelist[edgecount-1]->VertexPos(0)-edgelist[edgecount-1]->VertexPos(1);
            v2=v - edgelist[edgecount-1]->VertexPos(0);
            if(absc(v1)<absc(v2))
                edgelist[edgecount-1]->End()->v=v;
        }
    }
}


void CMesh::intersect_near(int u, int& jiter,CMesh *m, CVector &v, int &iter)
{
	map<int,CEdge*> vedge=edgelist;
	map<int,CEdge*> vmedge=m->edgelist;
	vector<CVector> vn,vmn;
    
	CVector v1,v2;
	float f1,f2;
	int u1;
	set<Ei> jh;
	int nb= edgelist.size();
    
	for(int iter2=0;iter2<m->edgelist.size();iter2++)
	{
        
		u1=edgelist[u]->intersect2(m->edgelist[iter2],v);
        
        if(u1!=0)
        {
            v1=m->edgelist[iter2]->VertexPos(1)-m->edgelist[iter2]->VertexPos(0);
            v2=v - m->edgelist[iter2]->VertexPos(0);
            if(v1.dot(v2)>-1E-5)
            {
                f1 = absc(CVector(edgelist[u]->VertexPos(0),v));
                f2 = absc(CVector(edgelist[u]->VertexPos(1),v));
                if(f1<f2)
                    jh.insert(Ei(0,f1,iter2,v));
                else
                    jh.insert(Ei(1,f2,iter2,v));
                
            }
        }
	}
	if(!jh.empty())
	{
		jiter=(*jh.begin()).i1;
		v=(*jh.begin()).v;
		iter=(*jh.begin()).i2;
	}
	else
	{
		iter=-1;
	}
}
