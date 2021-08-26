// Edge.h: interface for the CEdge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGE_H__CB64BBE7_D5D7_4110_B3DE_10AF335CE0AD__INCLUDED_)
#define AFX_EDGE_H__CB64BBE7_D5D7_4110_B3DE_10AF335CE0AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vertex.h"
#include "Vector.h"	// Added by ClassView

class CEdge  
{
public:
	void setVector(CVector v,int i=-1);
	CVector getVector(int i=-1);
	void operator =(CEdge e);
	void RemoveAdjT(CTriangle* t);
	void savefile(CFile &file);
	void openfile(CFile &file);
	LONG Readfile(CFile &file);
	void display(CDC *hdc);
	CVertex* Start();
	CVertex* End();
	CVertex* Mate(CVertex* v);
	CEdge (CVertex b, CVertex e);
	CEdge (CVertex* b, CVertex* e,int i=-1);
	CEdge (): constrained(false),sit(NULL),sjt(NULL),adjt(0),ofile(false){};
	CEdge operator - ();
	bool operator ==(CEdge v){ return ((sit==v.sit)&&(sjt==v.sjt));}
//	CEdge();
	virtual ~CEdge();
public:
	void setConstrained(bool t);
	int intersect2(CEdge* e, CVector& v);
	bool onRight(CVector v);
	int intersect(CEdge* e,CVector& v);
	void DeleteAdjTri(int i);
	bool Disconnect();
	void initcopy(CEdge* e);
	void initcopy2(CEdge* e,int j);
	void RemoveAdjTri();
	void RemoveAdjTri(int i);
	float project(CVector v, CVector* n=NULL);
	CVector vDir();
	CVector getNormal();
	CMesh* getMesh();
	CVertex* splitEdge(float u);
	CVector VertexPos(int n);
	CVertex* Vertex(int n);
	float onEdge(CVector v, CVector& v1);
	void setMesh(CMesh* m);
	int getAdjt();
	void flip();
	bool isBorder();
	void addAdjT(CTriangle*t);
//	CVertex* begin;
//	CVertex* end;
	CVertex *sit,*sjt;
	int it;
private:
	vector<int*> adjT;
	int adjt;
	bool ofile;
	CMesh* mesh;
	bool constrained;
	CVector v1_cur,v0_cur;

};
#endif // !defined(AFX_EDGE_H__CB64BBE7_D5D7_4110_B3DE_10AF335CE0AD__INCLUDED_)
