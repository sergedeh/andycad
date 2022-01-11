//
//  CFFD.h
//  testcommand
//
//  Created by Serge Deh on 10/17/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CFFD__
#define __testcommand__CFFD__

#include <iostream>
// FFD.h: interface for the CFFD class.
//
//////////////////////////////////////////////////////////////////////

#include "CBezier.h"
#include "CVector.h"	// Added by ClassView

class CFFD :public CFigure
{
public:
	void postTranslate(CVector v);
	bool PtinNode(CVector point,int multi);
	void update();
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void copy(CFFD* box);
	void subdivide(int u, int v,int w);
	void init();
	long Readfile(fstream &file);
	void openfile(fstream& file);
	void savefile(fstream& file);
	void draw(CDC* hdc);
	void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	bool PtinRegion(CVector point);
	vector<CVector>& getPoint();
	vector<double>& getKnu();
	vector<double>& getKnv();
	vector<double>& getKnw();
	vector<CVector> CP;
	vector<CVector> Para;
    
	vector<double> Knu,Knv,Knw;
	int degu,degv,degw;
	int ncpu,ncpv,ncpw;
	void movepoint(CBezier* b,CVector* M);
	CFFD(CBezier*bezier,string option);
	CFFD();
	string type;
	virtual ~CFFD();
private:
	void Mesh();
	CBezier *b;
	CMesh mesh;
	vector<CMesh> sphere;
    
};

#endif /* defined(__testcommand__CFFD__) */
