// CAM.h: interface for the CCAM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAM_H__E66A044C_2188_42BB_88AA_453C68561526__INCLUDED_)
#define AFX_CAM_H__E66A044C_2188_42BB_88AA_453C68561526__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "aabb.h"
#include "Vector.h"	// Added by ClassView
#include "figure.h"	// Added by ClassView

class CCAM
{
public:
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
	void setfov(float f);
	CVector gettarget();
	CVector getcamor();
	void zoom(float zr);
	void setcamvector(CVector v,CVector t,CVector vright,CVector vup);
	void setcam(CVector vo,CVector vt);
	void setcamorigin(CAABB* b);
	void setCamview(CString s,CAABB& box);
	void setPerspective(CAABB& box);
	void draw(CDC *hdc);
	CCAM();
	virtual ~CCAM();
	void Translate(int sens,CVector prevpoint,CVector postpoint);
	void Rotate(int sens,CVector prevpoint,CVector postpoint,bool b=false);
	void Rotate(int sens,float angle,bool b=false);
	CVector getpos(){return camor;}
	void setpos(CVector v){camor=v;}

private:
	static CVector camor,target,vrx,vry,vrz;
	CVector worldor;
	CVector xvec;
	CVector yvec;
	CVector zvec;
	float fov;
	float zoom_r;
};

#endif // !defined(AFX_CAM_H__E66A044C_2188_42BB_88AA_453C68561526__INCLUDED_)
