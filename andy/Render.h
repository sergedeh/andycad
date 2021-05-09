// Render.h: interface for the CRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENDER_H__863516A7_636A_4970_A262_E01A40838E45__INCLUDED_)
#define AFX_RENDER_H__863516A7_636A_4970_A262_E01A40838E45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mesh.h"
using namespace std;
class CCadView;
//class CMesh;
class CRender  
{
public:
	void removeRegion(CMesh* m);
	void Update(HDC hd);
	void setWnd(CCadView *cad);
	void displayTri(CDC *hdc);
	CRender();
	virtual ~CRender();
	void addRegion(CMesh* m);
	static CCadView *view;
private:
	bool clipTriangle(vector<CTriangle*>& Mb,HDC hdc,CMesh* mesh,CAABB& bol);
	void Clipconfiguration(float pi0,float pi1,float pi2,CVertex* vi0,CVertex* vi1,CVertex* vi2,HDC hdc,CMesh* mesh);
	vector<CMesh*> region;
	multiset<CTriangle*,isfar> tri;
	int updatecount;

	vector<CVector> ptbegin,ptend;
};

#endif // !defined(AFX_RENDER_H__863516A7_636A_4970_A262_E01A40838E45__INCLUDED_)
