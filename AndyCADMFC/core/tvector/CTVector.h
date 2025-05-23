//
//  CTVector.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CTVector__
#define __testcommand__CTVector__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../vector/CVector.h"
#include "../aabb/CAABB.h"
using namespace std;
class CTVector//: public CVector
{
public:
	void VpopTransform();
	void VpushTransform();
	void create();
	void TCam(CVector v1x,CVector v1y,CVector v1z,CVector v1o);
	void TRotate(CVector n,double angle);
	long Readfile(fstream &file);
	void openfile(fstream& file);
	void savefile(fstream& file);
	void Scale(CVector n,float f);
	void Reflect(CVector n);
	void Project(CVector n);
	void setsnapplane(string s);
	void InitCamView(string s,CAABB& box);
	void LendT();
	void VpushUnit();
	void VinitVect();
	void VendT();
	double getzoomrat();
	void endT();
	void initVect();
	void updateMatrix(bool v);
	void pushTransform();
	void pushUnit();
	CTVector();
	virtual ~CTVector();
    
	CVector unitvector(CVector v);
	void popTransform();
	void Shear(double shx,double shy,double shz=1);
	void TRotate(double angle);
	void TRotatex(double angle);
	void TRotatey(double angle);
	void Scale(double scx, double scy,double scz=1);
	void Translate(CVector vt);
	void SetWindowOrig(CVector vvx, CVector vvy, CVector vv0);
	void setCam(CVector vx=CVector(1,0,0,0),CVector vy=CVector(0,1,0,0),CVector vz=CVector(0,0,1,0),CVector vo=CVector(0,0,0,1));
	void setWorld(CVector vx=CVector(1,0,0,0),CVector vy=CVector(0,1,0,0),CVector vz=CVector(0,0,1,0),CVector vo=CVector(0,0,0,1));
    
	
	
private:
	static vector<CVector> b1,bo,bi1,bio,vbo,vbio;
	enum {local, view, world} vi;
	static CVector vx,vy,vz;
	static CVector v0r;
	static vector<CVector> base,basei;
	static vector<CVector>::iterator itbase;
	double v[9];
    
	CVector unitx,unity,unitz;
    
};

#endif /* defined(__testcommand__CTVector__) */
