// Bezier.h: interface for the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIER_H__5FB86C16_272C_4795_A037_98B4AD95B919__INCLUDED_)
#define AFX_BEZIER_H__5FB86C16_272C_4795_A037_98B4AD95B919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "figure.h"
#include "mesh.h"
#include "QuadTree.h"	// Added by ClassView
//#include "ffd.h"	// Added by ClassView

using namespace std;

class CFFD;

class CBezier : public CFigure  
{
public:
	virtual CFigure* generateCopy();
	void UpdateTexture(CDC* hdc,CBitmap* bmp);
	void plane(CVector p1,CVector p2);
	void setFFDon();
	CMesh* getsphere();
	void sphere(CMesh *s,CVector C);
	void Clipconfiguration0(CVector* b,CVector* e,CVertex* vi0,CVertex* vi1,CVertex* vi2);
	void Clipconfiguration(CVector* b,CVector* e,CVertex* vi0,CVertex* vi1,CVertex* vi2);
	bool clipTriangle(vector<CTriangle*>& Mb);
	void cap(bool vctop,bool vcbot);
	void cap0(bool vctop,bool vcbot);
	void cube(CMesh* s);
	void cube(CVector Ct,float radius);
	void smooth(int u=-1,int v=-1,int w=-1);
	void sphere(CMesh* s);
	void displaysphere(CVector p,CDC* hdc);
	void sphere(CVector Ct,float radius);
	void updatecore();
	CFigure* translatep(CVector prevpos, CVector postpos);
	void UpdateTexture(CDC* hdc);
	void Render(CDC* hdc);
	bool isSurface();
	void computesurfacep();
	void updateffd();
	void setFFDon(CString option);
	void init();
	CBezier(CVector begin,CVector end,int d=1);
	CBezier(CFigure* fig);
	void buildspline(vector<CBezier*>* fg);
	void postTranslate(CVector v);
	CVector * getVector();
	void polystate(CVector pos);
	bool PtinNode(CVector point,int multi);
	void volume(CDC *hdc);
	void degel(int &ncp0,int &deg0,vector<double> V,vector<CVector>CP0,vector<CVector>&P0);
	void SUdegel(int du, int dv);
	void loftsurface(vector<CBezier*>& fg, int l,int h=-1);
	void revolsurface(vector<CBezier*> fg, int l,bool simple);
	void extrussurface(vector<CBezier*> fg, int l);
	void surface(CString type,vector<CBezier*> fg,int l,float vthick);
	void degel();
	void copy(CFigure *fig);
	void surface(CBezier *fig1, CFigure *fig2);
	void surface(CBezier* fig1,CBezier* fig2);
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void saddvec(vector<CVector> vectb, vector<CVector> vecte);
	CVector NURBS( int p, vector<CVector> P,int n,double u,double v,vector<double> U);
	CVector NURBS( int p,int p1, vector<CVector> P,int n,int n1,double u,double v,vector<double> U,vector<double> V);
	CVector NURBS( int p,int p1,int p2, vector<CVector> P,int n,int n1,int n2,double u,double v,double w,vector<double> U,vector<double> V,vector<double> W);
	void surface(CDC *hdc);
	bool fsnap(CVector& v,CDC*hdc);
	bool Redo();
	bool Undo();
	void deleteobj();
	virtual bool inRegion(CVector point);
	CBezier(CFile&file);
	CBezier(int degree,vector<CVector> mpoint);
	virtual void* Trim(vector<CVector> vec);
	virtual vector<CVector> getSvec();
	bool takeinfo(CVector point);
	bool snapok(CVector point);
	void deletenode(CVector point, CDC *hdc);
	CBezier();
	virtual ~CBezier();

	CPoint *Pprev,*Ptr,*Pt1r;

	void computeLagrange(CDC *hdc);
	void computeBezier(CDC *hdc,CVector *U);
	void computePieceBezier(CDC *hdc);
	void computePieceSpline(CDC *hdc);
	void computeSpline(CDC *hdc,double *U, vector<CVector> C,int i);
	void computeBspline(CDC *hdc,CVector p1,CVector p2,CVector p2p, CVector p1p);
	void computeHermite(CDC *hdc,CVector p1, CVector p2, CVector p1p, CVector p2p);
	void setMove(bool mv,CVector pos);
	void setMenuSelect(bool menu);
	void initL();
	bool getCharge();
	void create(CVector pos);
	void addtovec();
	void setPtsBegin(CPoint pos);
	LONG Readfile(CFile &file);
	void openfile(CFile& file);
	void savefile(CFile& file);
	virtual void drawinit(CDC *hdc,CVector begin, CVector end);
	void draw(CDC *hdc);
	virtual bool draw(bool fPrevLine,CDC* hdc,CVector point);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	bool PtinRegion(CVector point);
	void setselectmode(SELECT j);
	friend class CInter;
	void drawTrans(CDC *hdc);
	virtual void addvec(vector<CVector> vectb, vector<CVector> vecte);
	void addnode(CVector point, CDC *hdc);
	void drawselect(CDC *hdc);
	void closecurve(CVector point,CDC *hdc);
	void Oslo(int p,vector<double> B,vector<double> T,vector<CVector> P,int n,int m);
	void* breakcurve(CVector point);
	void Bohms(double t, int p,vector<double>& U,vector<CVector>& P,int &n);
	void Bohms(double u,double v,double w, int pu,int pv,int pw,vector<double>& U,vector<double>& V,vector<double>& W,vector<CVector>& P,int &nu,int &nv,int &nw);
	friend class CSpline;
	friend DWORD WINAPI NURBSp(LPVOID t);
	friend class CFFD;
	bool redraw;

	static CCVector S_spec,M_spec;
	static CCVector S_diff;
	static CCVector G_amb;
	static CVector lsou;
	static CVector view;
	static float m_gls;
	static bool dtri;
	static float EXTRUSC;


protected:

	vector<double> Para,Para1, Para2; //parameter vector
	vector<double> Kn,Kn0,Kn1,Kn2;//[50],Kn0[50]; //Knot vector 
	vector<CVector> CP,C,CPprev;//[50]; // control point vector
	int ncp,ncpe,ncp1,ncp2; //number of control point
	int N,N1,N2; //number of point on the curve
	int deg,deg1,deg2; //degree of the curve
	vector<CVector> P,indexpos;
	vector<int> indexvec;
	int prevref,prevstart;
	double minpara, maxpara,minpara1, maxpara1;
	
protected: //attribute
	CQuadTree quadtree;

	void setFFD(CVector *M);
//	CFFD* ffdbox;
	CFFD* FFDbox;
	void ScanPolygon(CDC* hdc,COLORREF rgba,CVector *K,int s,CImagex *texture);
	int petitj;
	virtual void DrawDynaBspline(CDC *hdc);

	bool fPrevB;
	CVector prevpoint,prevcont;
	bool candrawl,move,surf,surf0,vol, vol0,trans;
	vector<CVector> cont1,cont2,pcont1,pcont2;
	CVector control1,control2,prevcontrol1,prevcontrol2;
	CVector bezier[4],pbezier[4];
	CVector *Mr;
	CVector loc[2];
	CCVector lit[6];

	int lk,lh;
	bool ffd,bffd;
	col* mytext;
	int pwidth,pheight;
	light l;

	
	
	CVector Sur_deriv( int p,int p1, vector<CVector> P,int n,int n1,double u,double v,vector<double> U,vector<double> V,vector<double> T,bool du,bool dv);
	CVector NURBS( int p, vector<CVector> P,int n,double u,vector<double> U);
	CVector Bspline( int p, vector<CVector> P,int n,double u,vector<double> U);
	double compute_base(int p, double u,vector<double> U,int i,int n);
	
	void insertknot(double t, int h, int p,vector<double> U,vector<CVector> P,int n);
	//CVector* insert_DeBoor(double t, int p,double *U,CVector *P,int n);
	void insertknotU(double t, int h, int p,vector<double> U,int n);
	CVector insert_Boor(double t, int p,vector<double> U,vector<CVector> P,int n);

	void Para_universp(double min,double maxu, int n,vector<double>& T);
	double* Para_chord(double min,double max,CVector *point,int n);
	void Para_chord(double min,double max,CVector *point,int n,double* T);
	
	void Knot_deBoor(int n, int p, vector<double> T,vector<double> U);
	double * Grev_knot1(int n, int p, vector<double> T);
	double * Knot_UniverSp(double min,double maxu, int n,int p);
	void Knot_UniverSp(double min,double maxu, int n,int p,double *V);
	void Knot_Univer(int n, int p,vector<double>& U,double min, double max);
	
	void INT_curveI(CVector* point,int n, int p,vector<double> U, vector<double> T,CVector* P);
	void INT_curve(vector<CVector> point,int n, int p,vector<double> U, vector<double> T, vector<CVector>& P);
	CVector  surface_Boor(vector<CVector> P,int m,int n,int p,int q,double u, double v, vector<double> U, vector<double> V);
	vector<CVector>  INT_surface(vector<CVector> point,int n, int m,int q,int p,vector<double> V,vector<double> U,vector<double> Tv,vector<double> Tu);
	
	
	double * surface_KnotCLC(vector<CVector> point,int m,int n);
	double * surface_KnotCLR(vector<CVector> point,int m,int n);
	double * surface_KnotUSR(int m,int n,vector<CVector> point);
	double * surface_KnotUSC(int m,int n,vector<CVector> point);

	double compute_D1base(int pp,int p, double u,vector<double> T,vector<double> U,int i,int n);
	double compute_D2base(int pp,int p, double u,vector<double> T,vector<double> U,int i,int n);
	double computebase(int pp,int p, double u,vector<double> U,int i,int n);


	void IDrawD1BSpline(CDC *hdc, CVector p1, CVector p2, CVector p3);
	virtual void DrawBSpline(CDC *hdc);

	vector<CVector> ContP,ContP1,ContP2;

private:
	void Bdegel(int d, int start, int end, vector<CVector> Po);
	void BSdegelv(CBezier *fig, int d);
	bool tsurf,revol,strans;
	int PtonSpline(CVector point);
	int j;
	int lkp1;
	int lkp;
	int tas;
	int handle;
};

#endif // !defined(AFX_BEZIER_H__5FB86C16_272C_4795_A037_98B4AD95B919__INCLUDED_)
