//
//  CRender.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CRender__
#define __testcommand__CRender__

#include <iostream>
// Render.h: interface for the CRender class.
//
//////////////////////////////////////////////////////////////////////

#include "CMesh.h"
using namespace std;
class CCadView;
//class CMesh;
class CRender
{
public:
	void removeRegion(CMesh* m);
//	void Update(HDC hd);*******
	void setWnd(CCadView *cad);
	void displayTri(CDC *hdc);
	CRender();
	virtual ~CRender();
	void addRegion(CMesh* m);
	static CCadView *view;
private:
//	bool clipTriangle(vector<CTriangle*>& Mb,HDC hdc,CMesh* mesh,CAABB& bol);*******
//	void Clipconfiguration(float pi0,float pi1,float pi2,CVertex* vi0,CVertex* vi1,CVertex* vi2,HDC hdc,CMesh* mesh);********
	vector<CMesh*> region;
	multiset<CTriangle*,isfar> tri;
	int updatecount;
    
	vector<CVector> ptbegin,ptend;
};

#endif /* defined(__testcommand__CRender__) */
