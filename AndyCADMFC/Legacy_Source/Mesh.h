// Mesh.h: interface for the CMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESH_H__59BF5E79_B4AE_4F0E_985C_E7088666B1D6__INCLUDED_)
#define AFX_MESH_H__59BF5E79_B4AE_4F0E_985C_E7088666B1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include "triangle.h"
#include <set>
#include <map>
#include "CVector.h"	// Added by ClassView

using namespace std;
class CCadView;
class isfar
{
public:
bool operator ()(CTriangle* v1,CTriangle* v2)
{
	CVector v01=v1->getcent();
	CVector v02=v2->getcent();
	v01=v01.getDepth();
	v02=v02.getDepth();
	return v01.z>v02.z;
}
};
class CRender;
class CMesh //: public CTriangle  
{
public:
	void setEdge(CVector v,int i,int j=-1);
	CVector getEdge(int i,int j=-1);
	void setConstrainedEdge(int i);
	CVertex* getVertex(float u);
	float getSUVertex();
	bool Close();
	void cleanCurve();
	void addEdge(vector<CVector>& v1);
	float getU(CVector v1);
	void breakEdge(CVector v1);
	void breakEdge2(CVector v1);
	bool isClosed();
	void extendEdge(CMesh* m);
	bool inPolygon3(CEdge* e,bool st=false);
	void updateBoxUV(CAABB& box);
	CMesh* clip(CDC* hdc,CMesh* m);
	CMesh* clip2(CDC* hdc,CMesh* m,bool side=false);
	CMesh* clip3(CDC *hdc,CMesh* m,bool side);
	int SaddEdge(CEdge* e);
	bool isEdge(int i1, int i2);
	bool inPolygon2(CEdge* e);
	bool inPolygon(CEdge* v);
	void TrimEdge(vector<CVector>&vn,CMesh* m,bool side=false,bool st=false);
	void TrimEdge2(vector<CVector>&vn,CMesh* m,bool side=false,bool st=false);
	void TrimEdge3(CVector v,CMesh *m);
	void IntersectEdge(CMesh* m,bool side=false);
	void IntersectEdge2(CMesh* m,bool side=false);
	void intersect(CQuadTree* q1,CQuadTree*q2,string option);
	typedef vector<CTriangle*>::iterator itri;
	typedef map<int,CEdge*>::iterator iedge;
	typedef map<int,CVertex*>::iterator ivertex;

	vector<CEdge*> getCurve(CVertex* v1,CVertex* v2);
	void breakEdge(CVector v1,CVector v2);
	int iVertex(int i);
	int iEdge(int i);
	int* Tri(int i);
	void deleteSVertex();
	float min_dist_toEdge(CVector v,int* n=NULL);
	void offset(float u,CMesh* f);
	CVector Vector(int i);
	void operator = ( CMesh* m);
	void operator = ( CMesh m);
	bool PtonEdge(CVector point,CVector& v,float& u, CVector& uv);
	CVertex* addVertexonEdge(CVector v);
	void copy(const CMesh& m);
	void add(const CMesh *m);
	void UpdateVertex();
	void UpdateSelectedVertex();
	vector<CVector> getVectors();
	vector<CVertex*> getVertexList();
	vector<CEdge*> getEdgeList();
	void emptyscreen();
	void copy(const CMesh* m);
	bool PtonCol(CVector point);
	bool PtonRow(CVector point);
	void Rotate(int sens,CVector prevpoint,CVector postpoint,CVector rotateCenter);
	void display(CDC* hdc);
	void setConstrainedVertex(int i);
	bool PtonVertex(CVector point,int& i);
	void translate(CVector prevpos,CVector postpos);
	void addtoRender();
	void setRender(CRender* r);
	void RUpdate(HDC hdc);
	void RWRender();
	void Edraw(CDC* hdc);
	void Bdraw();
	void updateShadingpara(CCVector lit[6],col* mytext,int pwidth,int pheight,light *l);
	void setWnd(CCadView* cad);
	void UpdateNormal(int i, CVector v);
	void resizevertex(int i);
	CMesh(int i);
	void addVertex(int i,CVertex* v);
	CMesh(CFile&file);
	void savefile(CFile &file);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void displayVertex(CDC *hdc);
	void updateTri();
	CMesh();
	virtual ~CMesh();
	int Tcount() const { return tricount;}
	int Ecount() const { return edgecount;}
	int Vcount() const { return vertexcount;}

	CTriangle* Triangle( int triIndex) {return trilist[triIndex];}
	const CTriangle* Triangle(int triIndex) const {return trilist[triIndex];}

	CEdge* Edge( int edgeIndex) {return edgelist[edgeIndex];}
//	const CEdge* Edge(int edgeIndex) const {return edgelist[edgeIndex];}
	CVector getVector(float u);

	CVertex* Vertex(int vertexIndex) {return vertexlist[vertexIndex];}
//	CVertex* Vertex(int vertexIndex) const {return vertexlist[vertexIndex];}

	void empty();
//	void setTriCount(int tc){trilist.resize(tc);}
//	void setEdgeCount(int ec){edgelist.resize(ec);}
//	void setVertexCount(int vc){vertexlist.resize(vc);}

	int addTri();
	int addTri(CTriangle* t);
	int SaddTri(CTriangle* t);
	int addEdge();
	int addEdge(CEdge* e,bool _ready=false);
	int addVertex();
	CVertex* addVertex(CVertex* v,bool _ready=false);
	int SaddVertex(CVertex* v);

	itri DeleteTri(int triIndex);
	iedge DeleteEdge(int edgeIndex);
	ivertex DeleteVertex(int vertexIndex);

	void displayTri(CDC *hdc,CVector loc[2],CCVector lit[6],col* mytext,int pwidth,int pheight,light *l);
	void displayEdge(CDC *hdc);

	itri tbegin(){ return trilist.begin();}
	iedge ebegin(){ return edgelist.begin();}
	ivertex vbegin(){ return vertexlist.begin();}
	itri tend(){ return trilist.end();}
	iedge eend(){ return edgelist.end();}
	ivertex vend(){ return vertexlist.end();}
	ivertex svend(){ return s_vertex.end();}
	ivertex svbegin(){ return s_vertex.begin();}
	friend DWORD WINAPI TrilistDisplayp(LPVOID m);
	friend class CRender;

	col* texture;
	int t_pwidth;
	int t_pheight;
	light* s_light;
	bool redraw;
	enum{all,vertex,triangle,none} select;
	static CCadView *view;
	CAABB box;
private:
	void make_move(int i,vector<CEdge*>& ev);
	bool next_move(CVertex** v1,vector<CEdge*>& ev);
	bool is_answer(CVertex *v1,CVertex* v2);
	void DelaunayTri();
	int tricount,stricount;
	int edgecount,sedgecount;
	int vertexcount,svertexcount;
	int it,eit,vit;

	multiset<CTriangle*,isfar> displaytrilist;
	vector<CTriangle*> trilist;
	vector<CTriangle*> strilist;
	map<int,CEdge*> edgelist;
	map<int,CEdge*> sedgelist;

	map<int,CVertex*> vertexlist;
	map<int,CVertex*> svertexlist;
	map<int,CVertex*> s_vertex;

	static BYTE* bits;
	static float* zbuffer;
	static CRender* render;

protected:
	void intersect_near(int u, int& jiter,CMesh* m, CVector &v, int& iter);
};

#endif // !defined(AFX_MESH_H__59BF5E79_B4AE_4F0E_985C_E7088666B1D6__INCLUDED_)