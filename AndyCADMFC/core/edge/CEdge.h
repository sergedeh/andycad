//
//  CEdge.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CEdge__
#define __testcommand__CEdge__

#include <iostream>

#include "../vertex/CVertex.h"
#include "../vector/CVector.h"	// Added by ClassView

class CEdge
{
public:
	void setVector(CVector v,int i=-1);
	CVector getVector(int i=-1);
	void operator =(CEdge e);
	void RemoveAdjT(CTriangle* t);
	long skipRead(ifstream& file);
	void loadFrom(ifstream& file);
	void saveTo(ofstream& file);
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
#endif /* defined(__testcommand__CEdge__) */
