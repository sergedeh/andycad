// FFD.h: interface for the CFFD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFD_H__6E4B66E9_1781_4F57_B0DB_77DF97A7A095__INCLUDED_)
#define AFX_FFD_H__6E4B66E9_1781_4F57_B0DB_77DF97A7A095__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Bezier.h"
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
	LONG Readfile(CFile &file);
	void openfile(CFile& file);
	void savefile(CFile& file);
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
	CFFD(CBezier*bezier,CString option);
	CFFD();
	CString type;
	virtual ~CFFD();
private:
	void Mesh();
	CBezier *b;
	CMesh mesh;
	vector<CMesh> sphere;

};

#endif // !defined(AFX_FFD_H__6E4B66E9_1781_4F57_B0DB_77DF97A7A095__INCLUDED_)
