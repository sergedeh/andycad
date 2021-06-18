// Vertex.h: interface for the CVertex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTEX_H__D96773BE_DE0A_4CDF_BE19_8382AEAE2FBC__INCLUDED_)
#define AFX_VERTEX_H__D96773BE_DE0A_4CDF_BE19_8382AEAE2FBC__INCLUDED_

#include "Vector.h"	// Added by ClassView
#include "cvector.h"
#include <map>
//#include "line.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct col
{
	float r,g,b,a;
	LONG Readfile(CFile &file)
	{
		file.Seek(sizeof(float),CFile::current);
		file.Seek(sizeof(float),CFile::current);
		file.Seek(sizeof(float),CFile::current);
		return file.Seek(sizeof(float),CFile::current);
	}
	void openfile(CFile &file)
	{
		file.Read(&r, sizeof(float));
		file.Read(&g, sizeof(float));
		file.Read(&b, sizeof(float));
		file.Read(&a, sizeof(float));
	}
	void savefile(CFile &file)
	{
		file.Write(&r, sizeof(float));
		file.Write(&g, sizeof(float));
		file.Write(&b, sizeof(float));
		file.Write(&a, sizeof(float));
	}
};
struct light
{
	float alpha,m_gls;
	CVector view;
	CVector lsou;
	CCVector S_spec,\
		     M_spec,\
			 S_diff,\
			 M_diff,\
			 G_amb,\
			 M_amb;
}; 
struct vertex
{
	CPoint p;
	double u,v,alpha;
	int r,g,b;
	CVector pv;
	CVector n;
	vertex(CVector pb,CVector nn,CPoint p1,double uu,double vv):pv(pb),n(nn),p(p1),u(uu),v(vv){};
	vertex(CPoint pp,double uu=0,double vv=0):p(pp),u(uu),v(vv){};
	vertex(){};
	~vertex()
	{
		u=v=alpha=0;
		r=g=b=0;
	}
	operator CPoint() {return p;}
	operator CVector() {return pv;}
	operator ==(vertex e) {return p==e.p;}
};

class CMesh;
class CTriangle;
class CEdge;
class CVertex 
{
public:
	bool operator==(CVertex v1) {return (v.absc(v1.v-v)<10);}
	operator =(CVertex vx);

//	CVertex(CFigure* fig);
	CVertex(CFile&file);
	double getDepth();
	CVector getNormal();
	void setnormal(CVector vec);
	inline operator CVector() {return v;}
	CVertex(CVector vr): constrained(false),v(vr),adje(0),adjt(0),select(false),visible(false),sit(-1),checked(false){	adjE.clear();
};
	CVertex(CVector vr,float u,float v,int i=-1): constrained(false),visible(false),v(vr),un(u),vn(v),sit(i),adje(0),adjt(0),select(false),checked(false){adjE.clear();
};
	CVertex(CMesh* m=NULL):constrained(false),mesh(m),adje(0),adjt(0),select(false),visible(false),sit(-1),checked(false){adjE.clear();
};
	void operator+=(CVertex vert) {
		v+=vert.v;}
	void assign(CVertex vertex);
	virtual ~CVertex();
public:
	void setConstrained(bool t);
	vector<CVertex*> EdgesTarget();
	bool isConnectedTo2(CVertex *v);
	void RemoveFwdEdge(CVertex* v);
	int orientation_3d_sos(CVertex* b,CVertex* c, CVertex* d);
	bool checked;
	vector<CVertex*> EdgesSource();
	void DeleteAdjEdge(CEdge* i);
	void DeleteAdjTri(CTriangle* i);
	void Disconnect();
	void initcopy(CVertex* v);
	void RemoveAdjTri(CTriangle* t);
	void RemoveAdjTri();
	void RemoveAdjTrii(CTriangle* i);
	void RemoveAdjEdge();
	bool RemoveAdjEdgei(CEdge* i);
	CVector getEdgeOffset(float u);
	CVector getEdgeNormal(float u);
	CMesh* getMesh();
	bool isBoundary();
	bool isConnectedTo(CVertex* v);
	vector<CVertex*> getAdjv();
	void display(CDC*hdc);
	void setMesh(CMesh* m);
	void RemoveAdjEdge(CEdge* e);
	int getAdje();
	vector<CEdge*> getAdjE();
	vector<int*> getAdjEi();
	int getAdjt();
	vector<CTriangle*> getAdjT();
	void toScreen(HDC hdc);
	int getValence();
	void addAdjT(CTriangle* t);
	void addAdjE(CEdge* e);
	void updatev(CVector m);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void savefile(CFile &file);
	bool isOn();
	CVector v;
	CVector n;
	CPoint p; 
	float un,vn;
	float pun,pvn;
	CCVector vc;
	col rgbdiff,rgbspec;
	float alpha;
	float z;
	int valency;
	int sit;
	bool select;
	bool visible;
private:
	vector<int*> adjTi;
	vector<int*> adjEi;
	vector<CTriangle*> adjT;
	map<int,CEdge*> adjE;
	int adje,adjt;
	bool constrained;
	CMesh* mesh;
};

#endif // !defined(AFX_VERTEX_H__D96773BE_DE0A_4CDF_BE19_8382AEAE2FBC__INCLUDED_)
