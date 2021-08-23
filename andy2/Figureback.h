// Figure.h: interface for the CFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIGURE_H__588FB84D_F1E5_4D69_A02C_7393C8571DED__INCLUDED_)
#define AFX_FIGURE_H__588FB84D_F1E5_4D69_A02C_7393C8571DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mouse.h"
#include "TVector.h"
#include <vector>
#include "Vector.h"	// Added by ClassView
#include "imagex.h"	// Added by ClassView
#include "observer.h"	// Added by ClassView
#include "subject.h"	// Added by ClassView
#include "Ray.h"	// Added by ClassView
#include "AABB.h"	// Added by ClassView

using namespace std;

	enum SELECT{pnt=0,full=1,st=2,null=3};
class isfarV
{
public:
bool operator ()(CVector v1,CVector v2)
{
	CVector v01=v1.getDepth();
	CVector v02=v2.getDepth();
	return v01.z>v02.z;
}
};
class CMesh;
class CState;
class CFigure : public CObserver,public CSubject 
{
public:
	int x;
	CVector rotateCenter;
	bool transref;
	CVector lrefen;
	CVector refline;
	enum {close,open} OpClstate;
	enum {art,tech} mode;
	SELECT select;
	static CVector snapvec;
	static bool snapb;
	static CVector corepoint;
	
	CImagex texture;
	CVector blend_p;
	double alpha;
	double blend_radius;
	CVector blend_plane;
	float current_alpha;
	enum {circularb,linearb} blend_mode;
	enum {backcolor,image_texture,replace,decal,multiply,multiply_alpha,inv_multiply} tex_vert_mode;
	enum {tmultiply,tmultiply_inv,tadd,tprimary_alpha_blend,\
		tsecondary_alpha_blend,tmultiply_alpha,tmultiply_alpha_add_color,\
		tmultiply_color_add_aplha} tex_text_mode;
	enum {wrap,none} mode_texture;
	CString texture_file;
	CAABB box;
//	CMesh* mesh;

public:
	virtual void connectTo(CFigure *f, float u1,float u2);
	virtual void TranslateTo(CVector v);
	virtual void editobj(CDC* hdc);
	virtual CFigure* copy2(float d,CFigure* pbulk);
	virtual void scale(float u, short sens);
	virtual void rotate(float u, short sens);
	CVector getPoint(float u);
	virtual void Translate(CVector v, int node);
	virtual void Translate(CVector v);
	void select_node(int i);
	void select_full();
	virtual void Scale(int sens,CVector prevpoint,CVector postpoint);
	CAABB getbox();
	virtual void UpdateTexture(CDC* hdc);
	void init();
	bool isInside(CVector v,bool t=false);
	vector<CVector>* getpt();
	virtual void postTranslate(CVector v);
	void keytranslate(CWnd *wnd, CDC* hdc,int key);
	void getdisplayparam(CFigure* f);
	virtual CVector* getVector();
	virtual void UpdateTransparency();
	SELECT getselectmode();
	void setspline(bool s);
	void v2D();
	void v3D();
	void setRefRay(CVector begin,CVector end);
	CRay getRefRay();
	void selectMP(CVector point);
	void sendclickNotify();
	void setclickstate(CState* s);
	void setTexture(CString s,CDC* hdc);
	virtual void SendNotify(CString s, void* param[7]);
	void setInterest(CSubject *sub);
	CDC* getDC();
	void setRDC(CDC *hdc);
	void setfillpoint(CVector p);
	bool isClose();
	virtual bool PtinNode(CVector point,int multi);
	virtual void degel();
	virtual void copy(CFigure* fig);
	virtual void surface(CDC *hdc);
	CString getInfName();
	void setinfo(FINFO f);
	virtual bool fsnap(CVector& v,CDC *hdc);
	virtual void unfill(CDC *hdc);
	virtual void setLibstatusV(bool b);
	SELECT selecttoint();
	virtual void setselectmode(SELECT j);
	virtual void deleteobj();
	void setcorevecor();
	virtual bool inRegion(CVector point);
	void updatepts();
	void lclear(bool b);
	virtual void setLibstatus(bool sv);
	bool getLibstatus();
	bool getMultselect();
	CVector getRotateCenter();
	bool getmultcore();
	virtual void setrecselect(int rd);
	virtual void setmultcore(bool co);
	void setintvec(vector<CVector> vec);
	vector<CVector> getSSvec();
	virtual vector<CVector> getSvec();
	virtual void* Trim(vector<CVector> vec);

	vector<CFigure>* translatepArray(bool of,int nbrow,int nbcol, double distx,double disty,int level,double distl,vector<CFigure>* pbulk);
	vector<CFigure>* RotateCopyP(CDC *hdc,double ang,int nnb,int nblevel,int dlevel,vector<CFigure>* pbulk, bool align);
	virtual bool takeinfo(CVector point);
	void updateinfo();
	virtual void computesurface();
	virtual void computeangle(CVector begin,CVector end);
	virtual void computedist();
	void setintersect(bool x, CVector point);
	virtual bool snapok(CVector point);
	virtual void drawsnap(CDC *hdc,CString mode);
	virtual CPoint textend(CDC* hdc);
	virtual CPoint deletetext(CDC *hdc);
	virtual CPoint texthome(CDC *hdc);
	void setliwidth(double ls);
	void setlistyle(DWORD ls);
	void setclick(bool s);
	virtual void setTransref(bool b);
	virtual CPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl);
	void translatepoint(CDC *hdc, CVector prevpos, CVector postpos);
	CVector getRefLine();
	CVector getRefPt();
	virtual void cursorOn(CWnd *wnd, CDC *hdc);
	virtual CPoint kbmovecurs(CDC *hdc, CString& d);
	virtual CPoint entertext(CDC *hdc);
	virtual CPoint deleteback(CDC *hdc);
	virtual CPoint drawtext(CDC *hdc, UINT nchar);
	double getdistprec();
	void setdistprec(double b);
	virtual void orient(double angle);
	void setgline(bool b,bool e);
	CVector hitpoint;
	vector<CVector> getSelectvec(CVector point);
	CString ntype;
	virtual void setType(CString type);
	virtual void setReflineP(CVector begin,CVector end);
	void setClstate(bool state);
	void InitRotState();
	bool getRotstate();
	bool getRotClick();
	virtual void setcore(vector<CVector> co);
	void clearundo(CWnd* win,CDC *hdc);
	void updateUndoparam();
	virtual void clear();
	virtual bool Redo();
	int countUnd();
	virtual void setUndoparam();
	virtual bool Undo();
	int gethandle();
	void sethandle(int hn);

	LOGBRUSH lplb;
	DWORD dwStyleCount;    // length of array containing custom style bits
	DWORD *lpStyle;   // optional array of custom style bits
	int lstyle;
	int lwidth;
	int petit;
	double jpetit;
	CVector p0,p01,p1,p12,p2,p23,p3,p30,pc; 
	double angle;
	COLORREF lcolor,bcolor;
	bool colchange;
	virtual void setLcolor(CDC *hdc,COLORREF color,COLORREF bkcolor);
	virtual CVector CopybyLine(CFigure *figure);

	virtual CFigure * mirror(CDC* hdc, CFigure *line);
	CString getName();
	virtual void create(CVector pos);
	CFigure* alignbyL(CDC *hdc, CVector line, CVector projectline, CVector center);
	CVector getstartPoint();
	CFigure* copybyC(CDC *hdc,CVector center, CFigure *pbulk);
	vector<CFigure>* RotateCopyP(CDC *hdc,CVector point,vector<CFigure>* pbulk,bool align);
	vector<CVector>* translatep(CVector prevpos, CVector postpos);
	CVector getCenter();
	void drawdel(CDC *hdc);
	void CheckinRG(CVector point);
	virtual void moveRotCenter(CDC* hdc, CVector prevpoint, CVector postpoint);
	virtual void setRotClick(bool value);
	virtual bool rotateSM(CDC* hdc, int sens,CVector prevpoint, CVector postpoint,bool b);
	bool recselect;
	void TransformRect(CVector prevpos, CVector postpos);
	bool Rectangleselect(CVector point);
	friend class CInter;

	int centercote(CVector point);
	bool computeA(CVector point1,CVector point2,CVector point);
	int cote(CVector point);
	bool Notincore(CVector mpoint, CVector x);
	virtual void updatecore();
	virtual void drawpointdyna(CDC *hdc,CVector pbb, CVector pbe);
	virtual void drawinit(CDC *hdc,CVector begin, CVector end);
	bool getSelect();
	virtual bool PtinRegion(CVector point);
	virtual bool draw(bool fPrevLine,CDC* hdc,CPen pen,CVector point);
	virtual void draw(CDC* hdc);

	virtual LONG Readfile(CFile& file);
	virtual void openfile(CFile& file);
	virtual void openfile(CDC *hdc,CFile& file);
	virtual void savefile(CDC *hdc,CFile& file);
	virtual void savefile(CFile& file);
	virtual void setInit();
	virtual void setMultselect(bool mult);
	bool unselectedstate();
	bool transselectedstate();

	bool inselectedstate();
	void selectSM(CDC *hdc);
	void UpdateSM();

	bool getIsready();
	void setIsready(bool stat);

	bool IsOff();
	bool IsOn();
	void setSelect(bool sel);
	virtual void addvec(vector<CVector> vectb, vector<CVector> vecte);

	virtual void drawselect(CDC *hdc);
	void createobj(vector<CVector> begin, vector<CVector> end);
	virtual void* breakcurve(CVector point);
	virtual void closecurve(CVector point,CDC*hdc);
	virtual void deletenode(CVector point,CDC *hdc);
	virtual void addnode(CVector point,CDC *hdc);
	void drawpoint(CDC *hdc,vector<CVector>::iterator test);
	virtual void createvec();
	virtual void setRotateCenter(CVector point);
	virtual void Rotate(CVector point);
	virtual void Rotate(int sens,CVector prevpoint,CVector postpoint);
	virtual void drawTrans(CDC *hdc);
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	void Select(CDC *hdc, CVector pos);

	void create();

	virtual void setPtsBegin(CVector point);
	vector<CVector> selectvec,intvec;
	vector<CVector> snapv;
	vector<CVector> ptbegin;
	vector<CVector> ptend;
	vector<vector<CVector> > undovecb,undovece,redovecb,redovece;
	vector<FLAYER> undolayer,redolayer;

	FINFO info;
	FINFO getInfo();
	FLAYER layer;
	FLAYER getLayer();
	virtual void setLayer(FLAYER& lay);

	CFigure();
	virtual ~CFigure();
	
		 
protected:
	bool spline;
	CRay refRay;
	CVector fill_p;
	CVector prevrotateCenter;
	bool Isselect,Isrotate;
	CVector ptsPrevEnd,ptsPrevBegin;
	CMouse mouse;
	CVector ptsBegin,ptsEnd;

	enum {D0,D1,D2,D3,D4}linestate;
	enum {L0,L1,L2,L3,L4,L5,L6} lstate;
	enum {O,D,hD} snapstate;
	bool snap;
	bool cancharge,down,Up;
	bool menusel;

	
	enum {fsca,vsca,hsca,dsca} recselectpoint;
	enum {R0,R1,R2,R3,R4} rotstate;
	bool click,multiselect,cl,brk;
	bool Bisclick;
	CString name;
	vector<CVector>::iterator  piterb,pitere,piterpb,piterpe;
	
	vector<CVector> prevptbegin,ptbegin1,ptend1;
	vector<CVector> prevptend;
	vector<CVector> core,coreprec;
	vector<int> vs;
	
	CVector v0;
	
 
protected:
	CMesh* mesh;

private:
	CState* m_clickstate;
	static CDC* rhdc;
	bool multcore;
	bool libst;
	CVector vintersect;
	bool intersect;
	CVector addnode(CVector point);
	
	double distprec;

	bool glinee,glineb;
	CRect updateundocore(vector<CVector> ptb, vector<CVector> pte);
	int uncount;
	bool inReg;
	bool rotclick;
	int handle;

};

#endif // !defined(AFX_FIGURE_H__588FB84D_F1E5_4D69_A02C_7393C8571DED__INCLUDED_)
