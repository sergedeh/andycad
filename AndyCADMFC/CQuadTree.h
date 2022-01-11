//
//  CQuadTree.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CQuadTree__
#define __testcommand__CQuadTree__

#include <iostream>
// QuadTree.h: interface for the CQuadTree class.
//
//////////////////////////////////////////////////////////////////////
#include "CAABB.h"
#include "CRay.h"
#include <vector>
class CTriangle;
class CEdge;
class CMesh;
using namespace std;
class CQuadTree
{
public:
	void overlap(vector<CQuadTree*>& sv, CAABB b);
	bool is_overlapping(CAABB b);
	void traverse_overlapping(CQuadTree* q,CMesh* mesh,string option);
	void stabbed(vector<CQuadTree*>& sv, CVector v);
	void insert(CEdge* e);
	void query(vector<CTriangle>*seg,CPoint point);
	void splitq();
	void insert(CTriangle* p);
	void assign(CAABB r);
	void empty();
	void insert(CRay p);
	void query(vector<CRay>*seg, CAABB range);
	void query(vector<CRay>*seg, CPoint point);
	CAABB bounds;
	int num;
	CRay segment;
	CTriangle* triangle;
	CEdge* edge;
	CQuadTree(CAABB b);
	CQuadTree();
	virtual ~CQuadTree();
	vector<CQuadTree*> sub;
    
private:
	void split();
	int quadrant(CRay m);
	int quadrant(CAABB range);
	void splitq(CAABB range);
	bool bsplit;
protected:
	int quadrant(CTriangle* m);
};
#endif /* defined(__testcommand__CQuadTree__) */
