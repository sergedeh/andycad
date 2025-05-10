//
//  CQuadTree.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//
#include "pch.h"
#include "CQuadTree.h"
//#include "CAABB.h"

// QuadTree.cpp: implementation of the CQuadTree class.
//
//////////////////////////////////////////////////////////////////////
#include "CMesh.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuadTree::CQuadTree(CAABB b)
{
	bounds=b;num=0;
	bsplit=true;
}
CQuadTree::CQuadTree()
{
	num=0;
	bsplit=true;
	bounds.empty();
}

CQuadTree::~CQuadTree()
{
    
}

void CQuadTree::query(vector<CRay>*seg, CAABB range)
{
	CAABB t;
	if (bounds.intersectAABB(range))
	{
		if (num == 1)
		{
			CAABB d;
			d.add(segment.getPhead());
			d.add(segment.getPorg());
			if (range.intersectAABB(d))
			{
                seg->push_back(segment);
			}
		} else if (num > 1)
		{
			for (int i=0; i<8; i++)
			{
                sub[i]->query(seg,range);
			}
		}
	}
}

void CQuadTree::query(vector<CRay>*seg, CPoint point)
{
	CAABB t;
	if (bounds.containpts(point))
	{
		if (num == 1)
		{
            //			CRect d(segment.getPhead(),segment.getPorg());
            //			d.NormalizeRect();
            //			if (d.PtInRect(point))
            //			{
			seg->push_back(segment);
            //			}
		} else if (num > 1)
		{
			for (int i=0; i<8; i++)
			{
                sub[i]->query(seg,point);
			}
		}
	}
}

void CQuadTree::insert(CRay p)
{
	if (num == 0)
	{
        segment = p;
	} else if (num == 1)
	{
        split();
        sub[quadrant(segment)]->insert(segment);
        //	segment = null;
        sub[quadrant(p)]->insert(p);
	} else
	{
        sub[quadrant(p)]->insert(p);
	}
	num++;
}

int CQuadTree::quadrant(CRay m)
{
	vector<CRay>seg;
	CAABB range;
	range.add(m.getPhead());
	range.add(m.getPorg());
    
	int i=-1;
	for (i=0; i<8;++i)
	{
		if(range.intersectAABB(sub[i]->bounds))
		{
			return i;
		}
	}
    
    /*	}
     int i=-1;
     for (i=0; i<4;++i)
     {
     CRect t;
     if (t.IntersectRect(&range,sub[i]->bounds))
     {
     return i;
     }
     }*/
}

void CQuadTree::split()
{
    CAABB fsw;
    fsw.add(bounds.corner(0));
    fsw.add(bounds.center());
    CAABB fse;
    fse.add(bounds.corner(1));
    fse.add(bounds.center());
    CAABB fnw;
    fnw.add(bounds.corner(3));
    fnw.add(bounds.center());
    CAABB fne;
    fne.add(bounds.corner(2));
    fne.add(bounds.center());
    
    CAABB bsw;
    bsw.add(bounds.corner(4));
    bsw.add(bounds.center());
    CAABB bse;
    bse.add(bounds.corner(5));
    bse.add(bounds.center());
    CAABB bnw;
    bnw.add(bounds.corner(7));
    bnw.add(bounds.center());
    CAABB bne;
    bne.add(bounds.corner(6));
    bne.add(bounds.center());
    
    
    CQuadTree* qfne=new CQuadTree(fne);
    CQuadTree* qfse=new CQuadTree(fse);
    CQuadTree* qfnw=new CQuadTree(fnw);
    CQuadTree* qfsw=new CQuadTree(fsw);
    
    CQuadTree* qbne=new CQuadTree(bne);
    CQuadTree* qbse=new CQuadTree(bse);
    CQuadTree* qbnw=new CQuadTree(bnw);
    CQuadTree* qbsw=new CQuadTree(bsw);
    
    sub.push_back(qfne);
    sub.push_back(qfse);
    sub.push_back(qfnw);
    sub.push_back(qfsw);
    sub.push_back(qbne);
    sub.push_back(qbse);
    sub.push_back(qbnw);
    sub.push_back(qbsw);
}

void CQuadTree::empty()
{
	if(num>0)
	{
        for (int i=0; i<8; i++)
        {
            sub[i]->empty();
            delete sub[i];
        }
        sub.clear();
        num=0;
	}
}

void CQuadTree::assign(CAABB r)
{
	bounds.empty();
	bounds.add(CPoint(r.corner(0)));
	bounds.add(CPoint(r.corner(1)));
	bounds.add(CPoint(r.corner(2)));
	bounds.add(CPoint(r.corner(3)));
	bounds.add(CPoint(r.corner(4)));
	bounds.add(CPoint(r.corner(5)));
	bounds.add(CPoint(r.corner(6)));
	bounds.add(CPoint(r.corner(7)));
    //	num=0;
}

void CQuadTree::insert(CTriangle *p)
{
	CAABB range;
	range.add(p->Vertex(0)->v);
	range.add(p->Vertex(1)->v);
	range.add(p->Vertex(2)->v);
    
	int i;
	if (num == 0)
	{
        triangle = p;
        if(bounds.isEmpty())
            bounds=range;
	} else if (num == 1)
	{
        splitq(range);
        
        CAABB range1;
        range1.add(triangle->Vertex(0)->v);
        range1.add(triangle->Vertex(1)->v);
        range1.add(triangle->Vertex(2)->v);
        
        i=quadrant(range1);
        if(i!=-1)
            sub[i]->insert(triangle);
        
        triangle = NULL;
        i=quadrant(range);
        if(i!=-1)
            sub[i]->insert(p);
	}
	else
	{
        i=quadrant(range);
        if(i!=-1)
            sub[i]->insert(p);
	}
	num++;
}

int CQuadTree::quadrant(CTriangle *m)
{
	vector<CRay>seg;
	CAABB range;
	range.add(CPoint(m->Vertex(0)->v));
	range.add(CPoint(m->Vertex(1)->v));
	range.add(CPoint(m->Vertex(2)->v));
	CPoint p=m->getcent();
    
	int i=-1;
	for (i=0; i<4;++i)
	{
		if(sub[i]->bounds.ccontainpts(p))
		{
			return i;
		}
	}
    
}

void CQuadTree::splitq()
{
    CAABB bsw;
    bsw.add(bounds.corner(4));
    bsw.add(bounds.center());
    CAABB bse;
    bse.add(bounds.corner(5));
    bse.add(bounds.center());
    CAABB bnw;
    bnw.add(bounds.corner(7));
    bnw.add(bounds.center());
    CAABB bne;
    bne.add(bounds.corner(6));
    bne.add(bounds.center());
    
    
    CQuadTree* qbne=new CQuadTree(bne);
    CQuadTree* qbse=new CQuadTree(bse);
    CQuadTree* qbnw=new CQuadTree(bnw);
    CQuadTree* qbsw=new CQuadTree(bsw);
    
    sub.push_back(qbne);
    sub.push_back(qbse);
    sub.push_back(qbnw);
    sub.push_back(qbsw);
}

void CQuadTree::splitq(CAABB range)
{
    CAABB b=bounds;
    b.add(range);
    CAABB bsw;
    bsw.add(b.corner(2));
    bsw.add(b.center());
    CAABB bse;
    bse.add(b.corner(3));
    bse.add(b.center());
    CAABB bnw;
    bnw.add(b.corner(1));
    bnw.add(b.center());
    CAABB bne;
    bne.add(b.corner(0));
    bne.add(b.center());
    
    
    CQuadTree* qbne=new CQuadTree(bne);
    CQuadTree* qbse=new CQuadTree(bnw);
    CQuadTree* qbnw=new CQuadTree(bse);
    CQuadTree* qbsw=new CQuadTree(bsw);
    
    sub.push_back(qbne);
    sub.push_back(qbse);
    sub.push_back(qbnw);
    sub.push_back(qbsw);
}

void CQuadTree::query(vector<CTriangle>*seg,CPoint point)
{
	CAABB t;
	if (bounds.containpts(point))
	{
		if (num == 1)
		{
			seg->push_back(*triangle);
		} else if (num > 1)
		{
			for (int i=0; i<8; i++)
			{
                sub[i]->query(seg,point);
			}
		}
	}
}

void CQuadTree::insert(CEdge *e)
{
	CAABB range;
	range.add(e->Start()->v);
	range.add(e->End()->v);
    
	int i;
	if (num == 0)
	{
        edge = e;
        if(bounds.isEmpty())
            bounds=range;
	} else if (num == 1)
	{
        splitq(range);
        
        CAABB range1;
        range1.add(edge->Start()->v);
        range1.add(edge->End()->v);
        
        i=quadrant(range1);
        if(i!=-1)
            sub[i]->insert(edge);
        
        edge = NULL;
        i=quadrant(range);
        if(i!=-1)
            sub[i]->insert(e);
	}
	else
	{
        i=quadrant(range);
        if(i!=-1)
            sub[i]->insert(e);
	}
	num++;
    
}

int CQuadTree::quadrant(CAABB range)
{
    
	int j=0;
	for (int i=0; i<4;++i)
	{
		if(sub[i]->bounds.containpts(range.center()))
		{
			return i;
		}
	}
	return -1;
}

void CQuadTree::stabbed(vector<CQuadTree*>& sv, CVector v)
{
    if (!bounds.is_stabbed (v))
        return ;
    if (sub.empty()) /* leaf node */
    {
        sv.push_back(this);
        return;
    }
    
	for (int i=0; i<4;++i)
	{
		sub[i]->stabbed(sv,v);
	}
}

void CQuadTree::overlap(vector<CQuadTree*>& sv, CAABB b)
{
    if (!bounds.intersectAABB(b))
        return ;
    if (sub.empty()) /* leaf node */
    {
        sv.push_back(this);
        return;
    }
    
	for (int i=0; i<4;++i) 
	{
		sub[i]->overlap(sv,b);
	}
}

bool CQuadTree::is_overlapping(CAABB b)
{
    if (!bounds.intersectAABB(b))
        return false;
    if (sub.empty()) /* leaf node */
        return true;
    
	for (int i=0; i<4;++i) 
	{
		if(sub[i]->is_overlapping(b))
			return true;
	}
	return false;
}

void CQuadTree::traverse_overlapping(CQuadTree* q,CMesh* mesh,string option)
{
    if (!bounds.intersectAABB(q->bounds))
        return ;
    if (sub.empty()&&q->sub.empty()) /* leaf node */
    {
        mesh->intersect(this,q,option);
        return;
    }
    else if (q->sub.empty() || 
             (!sub.empty() && 
              bounds.volume() > q->bounds.volume()))
    { 
        for (int i=0; i<4;++i) 
        {
            sub[i]->traverse_overlapping(q,mesh,option);
        }
    }
    else
    {
        for (int i=0; i<4;++i) 
        {
            q->sub[i]->traverse_overlapping(this,mesh,option);
        }
    }
}