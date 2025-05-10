//
//  CVertex.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CVertex__
#define __testcommand__CVertex__

#include <iostream>
#include "../vector/CVector.h"	// Added by ClassView
#include "../cvector/CCVector.h"
#include <map>
#include <vector>
//#include "CDC.h"
using namespace std;
struct col
{
	float r,g,b,a;
    void saveTo(std::ofstream& file) const {
        file.write(reinterpret_cast<const char*>(&r), sizeof(float));
        file.write(reinterpret_cast<const char*>(&g), sizeof(float));
        file.write(reinterpret_cast<const char*>(&b), sizeof(float));
        file.write(reinterpret_cast<const char*>(&a), sizeof(float));
    }

    void loadFrom(std::ifstream& file) {
        file.read(reinterpret_cast<char*>(&r), sizeof(float));
        file.read(reinterpret_cast<char*>(&g), sizeof(float));
        file.read(reinterpret_cast<char*>(&b), sizeof(float));
        file.read(reinterpret_cast<char*>(&a), sizeof(float));
    }

    long skipRead(std::ifstream& file) {
        file.seekg(sizeof(double) * 4, std::ios::cur);
        return static_cast<long>(file.tellg());
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
	bool operator ==(vertex e) {return p == e.p;}
    };
    
    class CMesh;
    class CTriangle;
    class CEdge;
    class CVertex
    {
    public:
        bool operator==(CVertex v1) {return (v.absc(v1.v-v)<10);}
        void operator =(CVertex vx);
        
        //	CVertex(CFigure* fig);
        CVertex(ifstream& file);
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
        void setMesh(CMesh* m);
        void RemoveAdjEdge(CEdge* e);
        int getAdje();
        vector<CEdge*> getAdjE();
        vector<int*> getAdjEi();
        int getAdjt();
        vector<CTriangle*> getAdjT();
//        void toScreen(HDC hdc);
//        void display(CDC* hdc);
        int getValence();
        void addAdjT(CTriangle* t);
        void addAdjE(CEdge* e);
        void updatev(CVector m);
        long skipRead(ifstream& file);
        void loadFrom(ifstream& file);
        void saveTo(ofstream& file);
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

#endif /* defined(__testcommand__CVertex__) */
