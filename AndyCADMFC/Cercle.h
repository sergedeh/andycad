// Cercle.h: interface for the CCercle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CERCLE_H__8491740A_B766_4C5D_A00F_15FF223B372B__INCLUDED_)
#define AFX_CERCLE_H__8491740A_B766_4C5D_A00F_15FF223B372B__INCLUDED_
#include "Bezier.h"	// Added by ClassView
#include "Vector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	CCercle(CFile& file);
	LONG Readfile(CFile &file);
	void openfile(CFile &file);
	void savefile(CFile &file);
	void savefiledxf(CStdioFile& file);
	void* Trim(vector<CVector> vec);
	void computeangle(CVector begin,CVector end);
	void computedist();
	void computesurface();

	void closecurve(CVector pt, CDC *hdc);
	bool DrawEllipse(bool fPrevB,CDC *hdc, CVector p);
//void drawselect( CDC *hdc);
	bool PtinRegion(CVector point);
	void setRadius(CVector radius);
	void setType(CString type);
	void drawArc(CVector center,CVector startpoint,double angle);
	//void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	void addvec(vector<CVector> vectb, vector<CVector> vecte);
	bool DrawCircle(bool fPrevB,CDC *hdc, CVector p2);
	bool DrawArc(bool fPrevB,CDC *hdc, CVector p2);
	bool Draw2DotCircle(bool fPrevB,CDC *hdc, CVector p);
	bool Draw2DotArc(bool fPrevB,CDC *hdc, CVector p);
	bool Draw3DotCircle(bool fPrevB,CDC *hdc, CVector p);
	bool Draw3DotArc(bool fPrevB,CDC *hdc, CVector p);
	void draw3Dot(CPoint first, CPoint second, CPoint third);
	bool getCharge();
	void initL();
	void setPtsBegin(CVector point);
	CCercle mirror(CDC *hdc, CCercle *citer);
	void DrawDynaBspline(CDC *hdc);
	void DrawBSpline(CDC *hdc);	
	friend class CInter;
	friend class CDimA;
	CCercle();
	virtual ~CCercle();
protected:
	bool inRegionSnap(CVector &point);

private:
	CString prevf;
	void updateCP(CString s);
	CVector Ct,r,pt,control1,control2,control3, startpoint, endpoint, epoint, spoint;
	int it;
	int start,end;
	int handle;

	
};

#endif // !defined(AFX_CERCLE_H__8491740A_B766_4C5D_A00F_15FF223B372B__INCLUDED_)
