// Vertex.cpp: implementation of the CVertex class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Vertex.h"
#include "mesh.h"
#include "Cadview.h"
#include "Caddoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertex::~CVertex()
{
	adje=0;
	adjt=0;
	adjE.clear();
	adjT.clear();
}
void CVertex::assign(CVertex vertex)
{
	v.assign(vertex.v,true);
	n.assign(vertex.n,true);
	n=n/absc(n);
}


void CVertex::setnormal(CVector vec)
{
	n=vec;
}

CVector CVertex::getNormal()
{
	return n;
}

double CVertex::getDepth()
{
	return true;//v.getDepth();

}

bool CVertex::isOn()
{
  return v.isOn();
}
void CVertex::setConstrained(bool t)
{
  constrained=t;
}

void CVertex::savefile(CFile &file)
{
	n.savefile(file);
	v.savefile(file);
	vc.savefile(file);
	file.Write(&un, sizeof(un));
	file.Write(&vn, sizeof(vn));
	file.Write(&pun, sizeof(un));
	file.Write(&pvn, sizeof(vn));
	file.Write(&valency, sizeof(valency));
	file.Write(&alpha, sizeof(alpha));
	if(mesh->view->GetDocument()->m_objects->version>0)
		file.Write(&sit, sizeof(sit));
	

}

void CVertex::openfile(CFile &file)
{

	n.openfile(file);
	v.openfile(file);
	vc.openfile(file);
	file.Read(&un, sizeof(un));
	file.Read(&vn, sizeof(vn));
	file.Read(&pun, sizeof(un));
	file.Read(&pvn, sizeof(vn));
	file.Read(&valency, sizeof(valency));
	file.Read(&alpha, sizeof(alpha));
	if(mesh->view->GetDocument()->m_objects->version>0)
		file.Read(&sit, sizeof(sit));
}
LONG CVertex::Readfile(CFile &file)
{

	n.Readfile(file);
	v.Readfile(file);
	vc.Readfile(file);
	file.Seek(sizeof(un),CFile::current);
	file.Seek(sizeof(vn),CFile::current);
	file.Seek(sizeof(valency),CFile::current);
	file.Seek(sizeof(alpha),CFile::current);
	if(mesh->view->GetDocument()->m_objects->version>0)
		file.Seek(sizeof(sit),CFile::current);
	return file.Seek(sizeof(alpha),CFile::current);
}

void CVertex::updatev(CVector m)
{
	v=m;	
}

void CVertex::addAdjE(CEdge *e)
{
	CMesh::iedge vi=CMesh::iedge();//vertexlist.find(vertexcount);
/*	int i=0;
	if(adjE.size()>0)
	{
		vi=adjE.find(i);
	while(vi!=adjE.end())
	{
		vi=adjE.find(i);
		i++;
	}
	}
	i=i>0?i:i+1;
*/
	adjE.insert(make_pair(e->it,e));
	adje++;
	valency++;
}

void CVertex::addAdjT(CTriangle *t)
{
	adjT.push_back(t);
	adjt++;
}

int CVertex::getValence()
{
	try{
	return adjE.size();//adje;
	}catch(...)
	{
		return -1;
	}
}
CPoint p1;
CVector pv1;
float yx,yo;
float yy;
float yz;
float d;
float xpo;
float ypo;
float zpo;
float xl1;
float yl1;
float zl1;
float dnl1;
float xr;
float yr;
float zr;
double b0;
float rdiff;
float gdiff;
float bdiff;

float rspec;
float gspec;
float bspec;

void CVertex::toScreen(HDC hdc)
{
	visible=true;
	pv1=v.getDepth();
	p1.x=pv1.x;
	p1.y=pv1.y;
	if(pv1.w==0) visible=false;
//	visible=PtVisible(hdc,p1.x,p1.y);
/*	CSize sz,sz1;
	CPoint pw,pv,po1=p1;
	GetViewportExtEx(hdc,&sz);
	GetWindowExtEx(hdc,&sz1);
	GetWindowOrgEx(hdc,&pw);
	GetViewportOrgEx(hdc,&pv);
	p1.x=(p1.x-pw.x)*(sz.cx/(float)sz1.cx)+pv.x;
	p1.y=(p1.y-pw.y)*(sz.cy/(float)sz1.cy)+pv.y;
*/
	LPtoDP(hdc,&p1,1);

//	pv1.x=p1.x;
//	pv1.y=p1.y;

	p.x=p1.x;
	p.y=p1.y;
	if(visible==false)
		{
		CPoint h=p;
		}

	z=pv1.z;//(v.getDepth()).z;
	light* l=mesh->s_light;

//	CVector view=l->view,lsou=l->lsou;
//	double alpha=l->alpha;
//	l->S_spec,M_spec=l->M_spec,S_diff=l->S_diff,M_diff=l->M_diff,\
//			G_amb=l->G_amb,M_amb=l->M_amb;

	yx=v.x-l->view.x;
	yy=v.y-l->view.y;
	yz=v.z-l->view.z;

	d=yo*yo+yy*yy+yz*yz;
	d=sqrt(d);
//	CVector po;
	xpo=(v.x-l->view.x)/d;//(absc(view-v));
	ypo=(v.y-l->view.y)/d;
	zpo=(v.z-l->view.z)/d;
	
	yx=l->lsou.x-v.x;
	yy=l->lsou.y-v.y;
	yz=l->lsou.z-v.z;
	d=yx*yx+yy*yy+yz*yz;
	d=sqrt(d);
	
//	CVector l1=(lsou-v)/(absc(lsou-v));
	xl1=(v.x-l->lsou.x)/d;//(absc(view-v));
	yl1=(v.y-l->lsou.y)/d;
	zl1=(v.z-l->lsou.z)/d;

	dnl1=n.x*xl1+n.y*yl1+n.z*zl1*2;
	xr=n.x*dnl1-xl1;
	yr=n.y*dnl1-yl1;
	zr=n.z*dnl1-zl1;

//	CVector r=n*(2*(n.dot(l1)))-l1;
	yx=xpo*xr+ypo*yr+zpo*zr;
	yx=yx>0?yx:0;

	b0=pow(yx,l->m_gls);	 	

	//CCVector clit1;
//	double r1=((l->S_spec.r)*b0)*(l->M_spec.r);
//	double g1=((l->S_spec.g)*b0)*(l->M_spec.g);
//	double b1=((l->S_spec.b)*b0)*(l->M_spec.b);
	//CCVector clit2;
	d=dnl1>0?dnl1:0;
//	double r2=((l->S_diff.r)*d)*(l->M_diff.r);
//	double g2=((l->S_diff.g)*d)*(l->M_diff.g);
//	double b2=((l->S_diff.b)*d)*(l->M_diff.b);
	//CCVector clit;
	
//	double rr=r1+r2+(l->G_amb.r)*(l->M_amb.r);
//	double rg=g1+g2+(l->G_amb.g)*(l->M_amb.g);
//	double rb=b1+b2+(l->G_amb.b)*(l->M_amb.b);

	float rdiff=l->G_amb.r+d*l->S_diff.r;
	float gdiff=l->G_amb.g+d*l->S_diff.g;
	float bdiff=l->G_amb.b+d*l->S_diff.b;

	float rspec=b0*l->S_spec.r;
	float gspec=b0*l->S_spec.g;
	float bspec=b0*l->S_spec.b;
	
	rgbdiff.r=rdiff;
	rgbdiff.g=gdiff;
	rgbdiff.b=bdiff;

	rgbspec.r=rspec;
	rgbspec.g=gspec;
	rgbspec.b=bspec;

}

int CVertex::getAdje()
{
	try{
	return adjE.size();//adje;
	}catch(...)
	{
		return -1;
	}
}
int CVertex::getAdjt()
{
	return adjt;
}
vector<int*> CVertex::getAdjEi()
{
	return adjEi;
}
vector<CEdge*> CVertex::getAdjE()
{
	vector<CEdge*> ve;
	for(CMesh::iedge iter=adjE.begin();iter!=adjE.end();iter++)
	{
//		ve.push_back(mesh->Edge(**iter));
		ve.push_back(iter->second);
	}
	return ve;
}
vector<CTriangle*> CVertex::getAdjT()
{
	vector<CTriangle*> ve;
	for(vector<CTriangle*>::iterator iter=adjT.begin();iter!=adjT.end();iter++)
	{
//		ve.push_back(mesh->Triangle(**iter));
		ve.push_back(*iter);
	}
	return ve;
}

void CVertex::RemoveAdjEdge(CEdge *e)
{
	if(adjE.erase(e->it))
		adje--;

}

void CVertex::setMesh(CMesh *m)
{
mesh=m;
}

void CVertex::display(CDC *hdc)
{
	CBrush brush;
	CBrush *oldb;
	if(constrained)
	{
		brush.CreateSolidBrush(RGB(19,219,49));
		oldb=hdc->SelectObject(&brush);

	}
	CRect r(v,v);
	r.InflateRect(15,15,15,15);
	hdc->Ellipse(r);
	int g=sit;
	CString sp;
	sp.Format(_T("%d"),g);
	CPoint p=v;
	hdc->TextOut(p.x,p.y,sp);
	if(constrained)
	{
		hdc->SelectObject(oldb);

	}

}

vector<CVertex*> CVertex::getAdjv()
{
	vector<CVertex*> v;
	CEdge* e;
	for(CMesh::iedge iter=adjE.begin();iter!=adjE.end();iter++)
	{
		e=iter->second;
		v.push_back(e->Mate(this));
	}
	return v;

}

bool CVertex::isConnectedTo(CVertex *v)
{
	CEdge* e;
	CVertex* v1;

	for(CMesh::iedge iter=adjE.begin();iter!=adjE.end();iter++)
	{
		e=iter->second;
		v1=e->Mate(this);

		if(v==e->Mate(this))
			return true;
	}
	return false;

}

bool CVertex::isConnectedTo2(CVertex *v)
{
	CEdge* e;
	CVertex* v1;
	try{
		v1 = EdgesSource().at(0);
		if(v1==v){
			if(v->n.xhit==v->n.yhit)
				return true;
			else
				return false;
		}
		else 
		{
			v->n.xhit+=1;
			if(v->n.xhit>v->n.yhit) return false;
			v1->isConnectedTo2(v);
		}
	}catch(...)
	{
		return false;
	}

}

bool CVertex::isBoundary()
{
	CEdge* e;
	for(CMesh::iedge iter=adjE.begin();iter!=adjE.end();iter++)
	{
		e=iter->second;
		if(e->isBorder())
			return true;
	}
	return false;

}

CMesh* CVertex::getMesh()
{
	return mesh;
}

void CVertex::operator =(CVertex vx)
{
	v=vx.v;
	n=vx.n;
	p=vx.p; 
	un=vx.un;
	vn=vx.vn;
	pun=vx.pun;
	pvn=vx.pvn;
	vc=vx.vc;
	rgbdiff=vx.rgbdiff;
	rgbspec=vx.rgbspec;
	alpha=vx.alpha;
	z=vx.z;
	valency=vx.valency;
	sit=vx.sit;
	select=vx.select;
	visible=vx.visible;
}

CVector CVertex::getEdgeNormal(float u)
{
	CVector v1(0,0,0);
	CEdge* e;
	for(CMesh::iedge iter=adjE.begin();iter!=adjE.end();iter++)
	{
		e=iter->second;
		v1+=e->getNormal();
	}
	v1.Normalise();
	return v1;
}



CVector CVertex::getEdgeOffset(float u)
{
	CVector v1(0,0,0);
	CEdge* e;
	vector<CEdge*> me=getAdjE();
	e=me[0];
	CVector op=e->getNormal(),op1;
	CVector vg0=e->vDir(),vg1,vg;
	vg=op*u;//vg0+op*u;
	CVector e1=e->VertexPos(0)+vg;
	CVector e2=e->VertexPos(1)+vg;
	CRay u1(e1,e2);
	if(adjE.size()>1)
	{
	e=me[1];
	op1=e->getNormal();
	vg1=e->vDir();
	}
	
	if((adjE.size()>1)&&(me[1]->VertexPos(0)!=me[1]->VertexPos(1))&&(!(absc(vg1-vg0)<0.1)))
	{
	vg=op1*u;//vg1+op1*u;
	e1=e->VertexPos(0)+vg;
	e2=e->VertexPos(1)+vg;
	CRay u2(e1,e2);
	v1=u1.Intersect(u2);
	return v1;
	}
	else if((adjE.size()>1)&&(absc(vg1-vg0)<0.1))
	{
		e=me[0];
		if(sit==e->sit->sit)
		{
			e1=e->sjt->getEdgeOffset(u);
			e=me[1];
			if(sit==e->sit->sit)
			{
			e2=e->sjt->getEdgeOffset(u);
			}else
			{
			e2=e->sit->getEdgeOffset(u);
			}
			CVector v2=e2-e1;
			v2=v2/2;

			return e1+v2;
		}
		else
		if(sit==e->sjt->sit)
		{
			e1=e->sit->getEdgeOffset(u);
			e=me[1];
			if(sit==e->sit->sit)
			{
			e2=e->sjt->getEdgeOffset(u);
			}else
			{
			e2=e->sit->getEdgeOffset(u);
			}
			CVector v2=e2-e1;
			v2=v2/2;

			return e1+v2;
		}
	}else
	{
		if(sit==e->sit->sit)
			return e1;
		else
		if(sit==e->sjt->sit)
			return e2;

	}

}

bool CVertex::RemoveAdjEdgei(CEdge* i)
{
	CMesh::iedge _i;
	for(_i=adjE.begin();_i!=adjE.end();_i++)
	{
		if(_i->second==i)
		{
			adjE.erase(_i);
			adje--;
			return true;
		}
	}
	_i=adjE.find(i->it);
	if(_i!=adjE.end())
	{
//		adjE[i->it]=NULL;
		adjE.erase(_i);//i->it);
		adje--;
		return true;
	}else
		return false;
}

void CVertex::RemoveAdjEdge()
{
	for(CMesh::iedge i=adjE.begin();i!=adjE.end();next(i))
	{
		i->second->Mate(this)->RemoveAdjEdgei(i->second);
		mesh->DeleteEdge(i->second->it);
//		if (i == end(adjE)) break;
		i->second=NULL;
	}
	adjE.clear();
	adje=0;
}
void CVertex::RemoveFwdEdge(CVertex* v)
{
	vector<int> verase;
	for(CMesh::iedge i=adjE.begin();i!=adjE.end();i++)
	{
		if((i->second->Start()==this)&&(i->second->Start()!=v))
		{
		try{
			CVertex* m=i->second->Mate(this);
			m->RemoveAdjEdgei(i->second);
			mesh->DeleteEdge(i->second->it);
			i->second=NULL;
			verase.push_back(i->first);
			m->RemoveFwdEdge(v);
			i++;
		}catch(...)
		{
			break;
		}
		i--;
		}
	}
	for(int i1=0;i1<verase.size();i1++)
	{
		adjE.erase(verase[i1]);
		adje--;
	}
}

void CVertex::RemoveAdjTrii(CTriangle* i)
{
	vector<CTriangle*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(*iter2==i)
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

void CVertex::RemoveAdjTri()
{
	vector<CTriangle*>::iterator iter;

	iter=adjT.begin();
	while(iter!=adjT.end())
	{
//		t=mesh->Triangle(**iter);
//		int i=**iter;
		mesh->DeleteTri((*iter)->it);
	}

}

void CVertex::RemoveAdjTri(CTriangle *t)
{
	vector<CTriangle*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(*iter2==t)
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

void CVertex::initcopy(CVertex* v)
{
/*	vector<CTriangle*>::iterator it=v->adjT.begin();
	adjT.resize(v->adjt);
	int j=0;
	while(it!=v->adjT.end())
	{
		adjT[j]=v->adjT[j];//mesh->Tri(**it);
		it++;
		j++;
	}
	adjt=v->adjt;


	vector<CEdge*>::iterator it1=v->adjE.begin();
//	adjE.resize(v->adje);
/*	int i=0;
	while(it1!=v->adjE.end())
	{
		adjE[i]=v->adjE[i];//mesh->iEdge(**it);
		it1++;
		i++;
	}*/
//	adje=v->adje;
	constrained=v->constrained;
}

void CVertex::Disconnect()
{
/*	vector<CTriangle*>::iterator it=adjT.begin();
	while(it!=adjT.end())
	{
		*it=NULL;
		it++;
	}

	CMesh::iedge it1=adjE.begin();
	while(it1!=adjE.end())
	{
		*it1=NULL;
		it1++;
	}*/

	adjT.clear();
	adjt=0;
	adjE.clear();
	adje=0;
}

void CVertex::DeleteAdjTri(CTriangle* i)
{
	vector<CTriangle*>::iterator iter2=adjT.begin(),iter=adjT.end();
	while(iter2!=adjT.end())
	{
		if(*iter2==i)
		{
			iter=iter2;
			break;
		}
		iter2++;
	}
	if(iter!=adjT.end())
	{
//		CTriangle* t;
//		t=mesh->Triangle(**iter);
//		int i=**iter;
		mesh->DeleteTri((*iter)->it);
	}
}

void CVertex::DeleteAdjEdge(CEdge* i)
{
	if(adjE.find(i->it)!=adjE.end())
	{
		adjE[i->it]=NULL;
		adjE.erase(i->it);
		adje--;
	}
/*	vector<CEdge*>::iterator iter2=adjE.begin(),iter=adjE.end();
	while(iter2!=adjE.end())
	{
		if(*iter2==i)
		{
			iter=iter2;
			break;
		}
		iter2++;
	}
	if(iter!=adjE.end())
	{
//		CEdge* e;
//		e=mesh->Edge(**iter);
//		int i=**iter;
		mesh->DeleteEdge(*(*iter)->it);
	}
*/
}

vector<CVertex*> CVertex::EdgesSource()
{
	CMesh::iedge iter2=adjE.begin();
	CEdge* e;
	vector<CVertex*> vi;
	while(iter2!=adjE.end())
	{
//		e=mesh->Edge(**iter2);
		if((iter2)->second->Start()==this)
		{
			vi.push_back((iter2)->second->End());
		}
		iter2++;
	}
	return vi;
}
vector<CVertex*> CVertex::EdgesTarget()
{
	CMesh::iedge iter2=adjE.begin();
	CEdge* e;
	vector<CVertex*> vi;
	while(iter2!=adjE.end())
	{
//		e=mesh->Edge(**iter2);
		if((iter2)->second->End()==this)
		{
			vi.push_back((iter2)->second->Start());
		}
		iter2++;
	}
	return vi;
}

int CVertex::orientation_3d_sos(CVertex *b, CVertex *c, CVertex *d)
{
  double o;

  if(b== NULL && c == NULL && 
			d == NULL) return 0;

}
