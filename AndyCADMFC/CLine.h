//
//  CLine.h
//  testcommand
//
//  Created by Serge Deh on 10/16/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CLine__
#define __testcommand__CLine__

#include <iostream>
#include "CFigure.h"
// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "CVector.h"
#include "CRay.h"
#include "CCVector.h"

#include <vector>

using namespace std;
//class CPlane;


struct Edges{
    vertex b,e;
    CRect r;
    int x_current;
    int it;
    double u_current;
    double v_current;
    double du;
    double dv;
    double v_top,v_bottom;
    double u_top,u_bottom;
    void operator =(Edges v)
    {
        e=v.e;
        b=v.b;
        r=v.r;
        x_current=v.x_current;
        u_current=v.u_current;
        v_current=v.v_current;
        it=v.it;
        du=v.du;
        dv=v.dv;
    }
    Edges(vertex k,vertex i,CRect t):b(k),e(i),r(t)
    {
        u_current=gettop().x;
        v_current=gettop().y;
        it=0;
        u_bottom=getbottom().x;
        v_bottom=getbottom().y;
        double ytop=gettop().z;
        
        v_top=gettop().y;
        u_top=gettop().x;
        double ybottom=getbottom().z;
        
        
        double dy=(double)1/(ytop-ybottom);
        //		double dx=(double)(r.right-r.left);
        //		double dd=(double)1/sqrt(dx*dx+dy*dy);
        du=-(u_top-u_bottom)*dy;
        dv=-(v_top-v_bottom)*dy;
        
    };
    Edges(){};
    ~Edges()
    {
        x_current=0;
        u_current=0;
        v_current=0;
        du=0;
        dv=0;
        r.SetRectEmpty();
        it=0;;
    }
    CVector gettop()
    {
        if(r.top==CGPoint(b).y)
            return CVector(b.u,b.v,r.top);
        else
            return CVector(e.u,e.v,r.top);
    }
    CVector getbottom()
    {
        if(r.bottom==CGPoint(b).y)
            return CVector(b.u,b.v,r.bottom);
        else
            return CVector(e.u,e.v,r.bottom);
    }
    bool operator ==(Edges v){
		return ((e==v.e)&&(b==v.b)&&(r==v.r));
    };
    bool operator ==(Edges* v){
		return ((e==v->e)&&(b==v->b)&&(r==v->r));
    };
};


typedef vector<Edges>::iterator eiterator;
typedef vector<CVector>::iterator viterator;

void updatexw(vector<Edges>::iterator e, int y,double width,int xleft);
void updatex(vector<Edges>::iterator e, int y,double width,int xleft);
bool isVybig(CGPoint v1, CGPoint v2);
bool isPbig(Edges e1,Edges e2);
bool isysmall(Edges e1,Edges e2);
bool sortx(Edges e1,Edges e2);
bool isytop(CVector e1,CVector e2);
bool isxleft(CVector e1,CVector e2);
bool isybottom(CVector e1,CVector e2);
bool isxright(CVector e1,CVector e2);

class CLine: public CFigure
{
public:
	vector<CFigure*> breakcurve2(CVector v1,CVector v2);
	void breakcurve(CVector v1,CVector v2);
	void setMove(bool mv,CVector pos);
	void addextranode(CVector point);
	void setMesh();
	virtual CFigure* generateCopy();
	CVector getptsBegin();
	void RegisterInterest(CObserver *obs);
	void SendNotify(string s,void* param[7]);
	float computealpha(int x,int y,CPlane *pl,float init=0,float end=1);
	virtual void surface(CDC *hdc);
	CLine(fstream& file);
	CLine(CVector b,CVector e);
	CLine(vector<CVector> v);
	void setMenuSelect(bool menu);
	void initL();
	bool getCharge();
	void create(CVector pos);
	void addtovec();
	void setPtsBegin(CVector pos);
	CGPoint getptsEnd();
	CVector CopybyLine(CFigure *object);
	long Readfile(fstream &file);
	void openfile(fstream& file);
	void savefile(fstream& file);
	//void savefiledxf(CStdioFile& file);********
	virtual void drawpointdyna(CDC *hdc,CVector pbb,CVector pbe);
	CFigure * mirror(CDC* hdc, CFigure *line);
	virtual void drawinit(CDC *hdc,CVector begin, CVector end);
	void draw(CDC *hdc);
	virtual bool draw(bool fPrevLine,CDC* hdc,CVector point);
	double pointtoVector(CVector line,CVector Point);
	friend class CInter;
	friend class CDim;
	friend class CDimL;
	friend class CDimA;
    
	bool edge_on;
    
    
	CLine();
	virtual ~CLine();
    
	
protected: //attribute
	void Fill (CDC* hdc,CGPoint p , COLORREF newVal);
    //	bool menusel;
	virtual void polystate(CVector pos);
    //	enum {L0,L1,L2,L3,L4,L5,L6} lstate;
	CVector precEnd,prevpos;
	bool /*cancharge,*//*Up,*/down,UfromL2;
	vector <CVector> ptbvir,ptevir;
};
#endif /* defined(__testcommand__CLine__) */
