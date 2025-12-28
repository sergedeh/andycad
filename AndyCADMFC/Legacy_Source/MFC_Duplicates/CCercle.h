//
//  CCercle.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CCercle__
#define __testcommand__CCercle__

#include <iostream>
// Cercle.h: interface for the CCercle class.
//
//////////////////////////////////////////////////////////////////////
#include "cBezier.h"	// Added by ClassView
#include "cVector.h"	// Added by ClassView
using namespace std;
class CCercle  : public CBezier
{
public:
	float getRadius();
	void copy(CCercle* c);
	CFigure* generateCopy();
	void setArc(CVector v1,CVector v2,CVector v3);
	void setArc(CVector v1, CVector v2);
	CCercle(CVector v1,CVector v2,bool arc=false);
	CCercle(CVector v1,CVector v2,CVector v3,bool arc=false);
	CCercle(CVector v, float radius,bool arc=false);
	void copy(CCercle& cercle);
    
	bool Draw3DotArc2(bool fPrevB,CDC *hdc, CVector p);
	bool fsnap(CVector& v,CDC* hdc);
	bool inRegion(CVector point);
	double computeAngle();
	CVector getCenter();
	void drawArc2(CVector center,CVector vstart, CVector vend);
	void drawArc(CVector start,CVector mid, CVector end);
	void drawArc(CVector start, CVector end);
	void addtovec(CDC* hdc=NULL);
	CCercle(fstream& file);
	long Readfile(fstream &file);
	void openfile(fstream &file);
	void savefile(fstream &file);
//	void savefiledxf(CStdioFile& file);**********
	void* Trim(vector<CVector> vec);
	void computeangle(CVector begin,CVector end);
	void computedist();
	void computesurface();
    
	void closecurve(CVector pt, CDC *hdc);
	bool DrawEllipse(bool fPrevB,CDC *hdc, CVector p);
    //void drawselect( CDC *hdc);
	bool PtinRegion(CVector point);
	void setRadius(CVector radius);
	void setType(string type);
	void drawArc(CVector center,CVector startpoint,double angle);
	//void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	void addvec(vector<CVector> vectb, vector<CVector> vecte);
	bool DrawCircle(bool fPrevB,CDC *hdc, CVector p2);
	bool DrawArc(bool fPrevB,CDC *hdc, CVector p2);
	bool Draw2DotCircle(bool fPrevB,CDC *hdc, CVector p);
	bool Draw2DotArc(bool fPrevB,CDC *hdc, CVector p);
	bool Draw3DotCircle(bool fPrevB,CDC *hdc, CVector p);
	bool Draw3DotArc(bool fPrevB,CDC *hdc, CVector p);
	void draw3Dot(CGPoint first, CGPoint second, CGPoint third);
	bool getCharge();
	void initL();
	void setPtsBegin(CVector point);
	CCercle mirror(CDC *hdc, CCercle *citer);
	void DrawDynaBspline(CDC *hdc);
	void DrawBSpline(CDC *hdc);
	friend class CInter;
	friend class CDimA;
	CCercle();
	~CCercle();
protected:
	bool inRegionSnap(CVector &point);
    
private:
	string prevf;
	void updateCP(string s);
	CVector Ct,r,pt,control1,control2,control3, startpoint, endpoint, epoint, spoint;
	int it;
	int start,end;
	int handle;
    
	
};

#endif /* defined(__testcommand__CCercle__) */
