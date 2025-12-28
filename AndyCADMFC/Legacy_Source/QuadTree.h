// QuadTree.h: interface for the CQuadTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUADTREE_H__BE2CC36F_76DB_442E_A5C8_F73974D57436__INCLUDED_)
#define AFX_QUADTREE_H__BE2CC36F_76DB_442E_A5C8_F73974D57436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ray.h"
#include "aabb.h"
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

#endif // !defined(AFX_QUADTREE_H__BE2CC36F_76DB_442E_A5C8_F73974D57436__INCLUDED_)
