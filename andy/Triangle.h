// Triangle.h: interface for the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__2773CF3D_5F0B_4E98_859E_7903377D5FFA__INCLUDED_)
#define AFX_TRIANGLE_H__2773CF3D_5F0B_4E98_859E_7903377D5FFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "edge.h"
//#include "Vertex.h"	// Added by ClassView
//#include "Vector.h"	// Added by ClassView
//#include "line.h"	// Added by ClassView
//#include "Figure.h"
#include "quadtree.h"
	typedef struct {
		CVector	pos;				// point's position
		float	scr[2];				// point's position in screen space
		col 	cold,cols;				// point's color
		CVector n;
		float u,v;
		float z;
	} Point;

class CMesh;
class CTriangle
{
public:
	operator = (CTriangle t);
	void triangle_template();
	void updateShadingpara(CCVector lit[6],col* my,int pwidth,int pheight,light *l);
	void rasterizeTriangle(HDC hdc,BYTE* bits,float* zbuffer,\
					   int bheight,int bwidth,col* mytext1,int pwidth,int pheight,light *l);
//	CTriangle(CFigure* fig);
	CTriangle(CFile&file);
	void Draw_Triangle_2D(HDC hdc,BYTE* bits,int bheight,int bwidth,col* mytext,int pwidth,int pheight,light *l);
	void Draw_Bottom_Tri(HDC hdc,BYTE* bits,int bheight,int bwidth,vertex v1,vertex v2, vertex v3,/*int x1,int y1,int x2,int y2,int x3,int y3,double u1,double v1,double u2,double v2,double u3,double v3,*/col* mytext,int pwidth,int pheight,light *l);
	void Draw_Top_Tri(HDC hdc,BYTE* bits,int bheight,int bwidth,vertex v1,vertex v2, vertex v3,/*int x1,int y1,int x2,int y2,int x3,int y3,double u1,double v1,double u2,double v2,double u3,double v3,*/col* mytext,int pwidth,int pheight,light *l);
	void DrawTriangleFill(CDC *hdc,CVector loc[2],CCVector lit[6]);
	void DrawLine(CDC* hdc,double x,double y,double x2,double y2,COLORREF c);
	void updatecent();
	CVector getcent();
	void display(CDC *hdc,CVector loc[2],CCVector lit[6]);
	CTriangle(CEdge* f, CEdge* s, CEdge* t);
	CTriangle(CEdge f, CEdge s, CEdge t);
	CTriangle(CVertex f, CVertex s, CVertex t);
	CTriangle(CMesh* m=NULL): mesh(m),sit(NULL),sjt(NULL),skt(NULL),eit(NULL),ejt(NULL),ekt(NULL),it(-1){};
	CTriangle(CVertex* f, CVertex* s, CVertex* t);
	virtual ~CTriangle();
	int surface();
	bool inside();
public:
	CVertex* intersect(CEdge* e);
	void Disconnect();
	void initcopy(CTriangle* t);
	CMesh* getMesh();
	CEdge* Edge(int n);
	CVertex* Vertex(int n);
	void updateAdj();
	void setMesh(CMesh* m);
	int findvertex(CVertex& v);
	bool isDegenerate(HDC hdc);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void savefile(CFile &file);

	CMesh *mesh;
	CVertex *sit,*sjt,*skt;
	int eit,ejt,ekt;
	int it;

	CVector n;
	CVector cent;
	CCVector vc;
	float un,vn;
	bool visible;
//	float* alpha;
	CCVector *S_spec,*M_spec,*S_diff,*M_diff,*G_amb,*M_amb;
	col* mytext;

	CQuadTree q_tri;
	CQuadTree oc_tri;

};
#endif // !defined(AFX_TRIANGLE_H__2773CF3D_5F0B_4E98_859E_7903377D5FFA__INCLUDED_)
