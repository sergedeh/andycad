//
//  CCam.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CCam__
#define __testcommand__CCam__

#include <iostream>
// CAM.h: interface for the CCAM class.
//
//////////////////////////////////////////////////////////////////////

#include "caabb.h"
#include "cVector.h"	// Added by ClassView
#include "cfigure.h"	// Added by ClassView

class CCAM:public CFigure
{
public:
	long Readfile(fstream &file);
	void savefile(fstream &file);
	void openfile(fstream& file);
	void Update();
	void copy(const CFigure *fig);
	CFigure* generateCopy();
	void initZoom();
	CVector getScreen();
	void undo();
	void init(CFigure* f);
	void initCam();
	void Translate(CVector v);
	float getnearplane();
	float getfarplane();
	void setnearplane(float n);
	void setfarplane(float f);
	float getfov();
	float getzoom();
	void setfov(float f);
	CVector gettarget();
	CVector getcamor();
	void zoom(float zr);
	void setcamvector(CVector v,CVector t,CVector vright,CVector vup);
	void setcam(CVector vo,CVector vt);
	void setcamorigin(CAABB* b);
	void setCamview(string s,CAABB& box);
	void setPerspective(CAABB& box);
	void draw(CDC *hdc);
	CCAM();
	virtual ~CCAM();
	void Translate(int sens,CVector prevpoint,CVector postpoint);
	void Rotate(int sens,CVector prevpoint,CVector postpoint,bool b=false);
	void Rotate(int sens,float angle,bool b=false);
	CVector getpos(){return camor;}
	void setpos(CVector v){camor=v;}
	void setcamtopleft(CAABB* b);
    
private:
	CVector camor,target,vrx,vry,vrz;
	CVector worldor;
	CVector xvec;
	CVector yvec;
	CVector zvec;
	float fov;
	static float zoom_r;
	static float zoom_pr;
};

#endif /* defined(__testcommand__CCam__) */
