// TVector.h: interface for the CTVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVECTOR_H__349F593A_3995_41D6_8832_F4E476C56D8B__INCLUDED_)
#define AFX_TVECTOR_H__349F593A_3995_41D6_8832_F4E476C56D8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"
#include "aabb.h"
#include<vector>
using namespace std;

class CTVector//: public CVector   
{
public:
	void VpopTransform();
	void VpushTransform();
	void create();
	void TCam(CVector v1x,CVector v1y,CVector v1z,CVector v1o);
	void TRotate(CVector n,double angle);
	LONG Readfile(CFile &file);
	void openfile(CFile& file);
	void savefile(CFile& file);
	void Scale(CVector n,float f);
	void Reflect(CVector n);
	void Project(CVector n);
	void setsnapplane(CString s);
	void InitCamView(CString s,CAABB& box);
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

#endif // !defined(AFX_TVECTOR_H__349F593A_3995_41D6_8832_F4E476C56D8B__INCLUDED_)
