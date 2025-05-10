//
//  CShape.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CFigure__
#define __testcommand__CFigure__

#include <iostream>
// Figure.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////


//#include "mouse.h"
//#include "CTVector.h"
#include <vector>
#include <string>
#include "../vector/CVector.h"	// Added by ClassView
#include "CImagex.h"	// Added by ClassView
#include "../observer/CObserver.h"	// Added by ClassView
#include "../subject/CSubject.h"	// Added by ClassView
#include "../ray/CRay.h"	// Added by ClassView
#include "../aabb/CAABB.h"	// Added by ClassView
#include "../mesh/CMesh.h"	// Added by ClassView
#include "../ximage/CxImage.h"
#include "../constraint/CConstraint.h"
#include "CWnd.h"
#include "CBitmap.h"
using namespace std;

typedef int32_t COLORREF;
struct LOGBRUSH {
    COLORREF lbColor;
    
};
 typedef int32_t DWORD;

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
//class CMesh;
class CState;
class CShape : public CObserver,public CSubject
{
public:
	int x;
	bool fPrevB;
	COLORREF trans_col;
	vector<CShape*> clipshape;
	CVector rotateCenter;
	bool transref;
	CVector lrefen;
	CVector refline;
	enum {close,open} OpClstate;
    //	enum {art,tech} mode;
	SELECT select;
    //	static CVector snapvec;
    //	static bool snapb;
	static CVector corepoint;
	
    //	CImagex texture;
	CVector blend_p;
	bool move;
    
	double alpha;
	bool snapPrev;
	double blend_radius;
	CVector blend_plane;
	float current_alpha;
	enum {circularb,linearb} blend_mode;
	enum {backcolor,image_texture,replace,decal,multiply,multiply_alpha,inv_multiply} tex_vert_mode;
	enum {tmultiply,tmultiply_inv,tadd,tprimary_alpha_blend,\
		tsecondary_alpha_blend,tmultiply_alpha,tmultiply_alpha_add_color,\
		tmultiply_color_add_aplha} tex_text_mode;
	enum {wrap,none,newone} mode_texture;
	string texture_file;
	CAABB box,vbox;
    //	CMesh* mesh;
    
public:
	void setEdge(CVector v,int i,int j=-1);
	CVector getEdge(int i,int j=-1);
	float getSUVec();
	CVertex* getPoint2(int u);
	bool PtinEdge(CVector point,int& i);
	bool PtinNode2(CVector point,int& i);
	void setConstrainedEdge(float i);
	void setConstrainedPoint(float i);
	bool edgeperpendicularconstraint(pair<CShape*,int> f1,pair<CShape*,int> f2);
	bool edgeverticalconstraint(pair<CShape*,int> f1);
	bool edgehorizontalconstraint(pair<CShape*,int> f1);
	bool edgeconstraint(pair<CShape*,int> f1,pair<CShape*,int> f2);
	bool pointconstraint(pair<CShape*,int> f1,pair<CShape*,int> f2);
	void cleancurve();
	void AddEdge(vector<CVector>& v1);
	int getrecselect();
	//void Hatch(CDC *hdc);****************
	//void ScanPolygon(CDC *hdc, COLORREF rgba,CImagex *texture=NULL);*********
	void setPtOn();
	void setMove(bool mv);
	virtual bool getCharge(CDC* hdc);
	bool snappara(CVector  vl,CVector& vs, CVector &v);
	bool snapperp(CVector vl,CVector vs, CVector& v);
	void intersect(CShape* f, CVector& v);
	bool inBox(CVector v);
	void Extend(CShape* f);
	void offset(CShape* f, float u);
	virtual void addextranode(CVector point);
	void TranslateNodeTo(CVector v, int node);
	void connectNodeToL(CVector v, float l, float i);
	void connectNodeTo(CVector v);
	CMesh* clipShape(CDC* hdc);
	virtual CMesh* Clip(CShape* f,bool side=false);
	virtual CMesh* Clip0(CShape* f);
	void connectNodeTo(CVector v, float i, bool c=false);
	void setVector(int i, CVector v);
	CVector getRefLine();
	void setRefLine(float u1, float u2);
	CVector Vector(int i);
	CVector LVector();
	void UpdateTexture(CDC* hdc, CBitmap* bmp);
	CMesh* getMesh();
	virtual vector<CShape*>  Trim(vector<CVector>& v1,CShape* f,bool side=false,bool st=false);
	CShape* Offset(float u);
	virtual float Min_dist_toEdge(CVector v);
	virtual void OffsetMesh(float u, CShape* f);
	CShape* copybyL(CShape* line);
	virtual void UpdateMesh();
	virtual void setbox(CAABB b);
	virtual CShape* generateCopy();
	void operator =(const CShape& f);
	CShape(const CShape& f);
	void createobj(CMesh* m);
	void setDir(float u1,float u2);
	virtual void connectTo(CShape *f, float u1,float u2, int al=0);
	virtual void connectTo(CVector p, float u1,bool ref=false);
    //	virtual void alignWithC(CShape *f, bool withx=true,bool withy=true,bool withz=true);
	virtual void alignWith(CShape *f, float u=-1);
	virtual void TranslateTo(CVector v);
	CVector TranslateTo(CVector v,float n,int n1=0);
	virtual void editobj(CDC* hdc);
	virtual void editobj(CVector point);
	virtual CShape* copy2(float d,CShape* pbulk);
	virtual void scale(float u, short sens);
	virtual void rotate(float u, short sens);
	virtual CVector getPoint(float u);
	virtual void Translate(CVector v, float node);
	virtual void Translate(CVector v);
	void select_node(int i);
	void select_full();
	virtual void Scale(int sens,CVector prevpoint,CVector postpoint);
	virtual const CAABB getbox(CDC* hdc=NULL);
	virtual void UpdateTexture(CDC* hdc);
	void init();
	bool isInside(CVector v,bool t=false);
	vector<CVector>* getpt();
	virtual void postTranslate(CVector v);
	void keytranslate(CWnd *wnd, CDC* hdc,int key);
	void getdisplayparam(CShape* f);
	virtual CVector* getVector();
	virtual void UpdateTransparency();
	SELECT getselectmode();
	void setspline(bool s);
	void v2D();
	void v3D();
	void setRefRay(CVector begin,CVector end);
	CRay getRefRay();
    //	void selectMP(CVector point);
	void sendclickNotify();
	void setTexture(string s,CDC* hdc);
	virtual void SendNotify(string s, void* param[7]);
	void setInterest(CSubject *sub);
	CDC* getDC();
	void setRDC(CDC *hdc);
	void setfillpoint(CVector p);
	bool isClose();
	virtual bool PtinNode(CVector point,int multi);
	virtual void degel();
	virtual void copy(const CShape* fig);
	virtual void add(const CShape *fig);
	virtual void surface(CDC *hdc);
	string getInfName();
	void setinfo(FINFO f);
	virtual bool fsnap(CVector& v,CVector &vl,string snapmode,CDC* hdc);
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
    
	vector<CShape*> translatepArray(bool of,int nbrow,int nbcol, double distx,double disty,int level,double distl);
	vector<CShape*> RotateCopyP(CDC *hdc,double ang,int nnb,int nblevel,int dlevel, bool align);
	virtual bool takeinfo(CVector point);
	void updateinfo();
	virtual void computesurface();
	virtual void computeangle(CVector begin,CVector end);
	virtual void computedist();
	void setintersect(bool x, CVector point);
	virtual CGPoint textend(CDC* hdc);
	virtual CGPoint deletetext(CDC *hdc);
	virtual CGPoint texthome(CDC *hdc);
	void setliwidth(double ls);
	void setlistyle(DWORD ls);
	void setclick(bool s);
	void setup(bool s);
	virtual void setTransref(bool b);
//	virtual CGPoint setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf);**********
	void translatepoint(CDC *hdc, CVector prevpos, CVector postpos);
	virtual CVector RefVec(float u=0);
	CVector getRefPt();
//	virtual void cursorOn(CWnd *wnd, CDC *hdc);**************
	virtual CGPoint kbmovecurs(CDC *hdc, string& d);
	virtual CGPoint entertext(CDC *hdc);
	virtual CGPoint deleteback(CDC *hdc);
	virtual CGPoint drawtext(CDC *hdc, int nchar);
	double getdistprec();
	void setdistprec(double b);
	virtual void orient(double angle);
	void setgline(bool b,bool e);
	CVector hitpoint;
	virtual vector<CVector> getSelectvec(CVector point);
	string ntype;
	virtual void setType(string type);
	virtual void setReflineP(CVector begin,CVector end);
	void setClstate(bool state);
	void InitRotState();
	bool getRotstate();
	bool getRotClick();
	void setcore();
	void setvcore();
	virtual void setcore(vector<CVector> co);
	virtual void clear();
	string gethandle();
	void setHandle(string& hn);
    
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
	virtual CVector CopybyLine(CShape *figure);
    
	virtual CShape * mirror(CDC* hdc, CShape *line);
	string getName();
	virtual void create(CVector pos);
	CShape* alignbyL(CDC *hdc, CVector line, CVector projectline, CVector center);
	CVector getstartPoint();
	CShape* copybyC(CDC *hdc,CVector center);
	vector<CShape>* RotateCopyP(CDC *hdc,CVector point,vector<CShape>* pbulk,bool align);
	CShape* translatep(CVector prevpos, CVector postpos);
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
    
	void updatevcore(bool _u=false);
	virtual void updatecore();
	virtual void drawpointdyna(CDC *hdc,CVector pbb, CVector pbe);
	virtual void drawinit(CDC *hdc,CVector begin, CVector end);
	bool getSelect();
	virtual bool PtinRegion(CVector point);
	virtual bool draw(bool fPrevLine,CDC* hdc,CVector point);
	virtual void draw(CDC* hdc);
    
	virtual long Readfile(fstream& file);
	virtual void openfile(fstream& file);
	virtual void openfile(CDC *hdc,fstream& file);
	virtual void savefile(CDC *hdc,fstream& file);
	virtual void savefile(fstream& file);
//	virtual void savefiledxf(CStdioFile& file);*********
	virtual void setInit();
	virtual void setMultselect(bool mult);
	bool unselectedstate();
	bool transselectedstate();
	void setModelOrigin(CVector _vo);
    
	bool inselectedstate();
	virtual void selectSM(CDC *hdc);
	void UpdateSM();
    
	bool getIsready();
	void setIsready(bool stat);
    
	bool IsOff();
	bool IsOn();
	void setSelect(bool sel);
	virtual void addvec(vector<CVector> vectb, vector<CVector> vecte);
    
	virtual void drawselect(CDC *hdc);
	void createobj(vector<CVector> begin, vector<CVector> end);
	virtual vector<CShape*> breakcurve2(CVector v1,CVector v2);
	virtual void breakcurve(CVector v1,CVector v2);
	virtual void closecurve(CVector point,CDC*hdc);
	virtual void deletenode(CVector point,CDC *hdc);
	virtual CVector  addnode(CVector point,CDC *hdc);
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
    //	vector<vector<CVector> > undovecb,undovece,redovecb,redovece;
    //	vector<FLAYER> undolayer,redolayer;
    
	FINFO myinfo;
	FINFO getInfo();
	FLAYER layer;
	FLAYER getLayer();
	virtual void setLayer(FLAYER& lay);
    
	CShape();
	~CShape();
	
    
protected:
	bool spline;
	CRay refRay;
	CVector fill_p;
	CVector prevrotateCenter,prevVangle;
	bool Isselect,Isrotate;
	CVector ptsPrevEnd,ptsPrevBegin;
	CVector ptsBegin,ptsEnd;
    
	enum {D0,D1,D2,D3,D4}linestate;
	enum {L0,L1,L2,L3,L4,L5,L6} lstate;
	enum {O,D,hD} snapstate;
	bool snap;
	bool cancharge,down,Up;
	bool menusel;
    
	
	enum {fsca,vsca,hsca,dsca,rotsca,rotmsca} recselectpoint;
	enum {R0,R1,R2,R3,R4} rotstate;
	bool click,multiselect,cl,brk;
	bool Bisclick;
	string name;
	vector<CVector>::iterator  piterb,pitere,piterpb,piterpe;
	
	vector<CVector> prevptbegin,ptbegin1,ptend1;
	vector<CVector> prevptend;
	vector<CVector> core,coreprec,vcore;
	vector<int> vs;
	
	CVector v0;
	CVector model_v0;
	CxImage* im;
    
    
protected:
	CMesh mesh;
	int pheight;
	int pwidth;
	col* mytext;
	col* hatch;
    
	vector<float> refl;
    
    
private:
	float dir[2];
    //	CState* m_clickstate;
	static CDC* rhdc;
	bool multcore;
	bool libst;
	CVector vintersect;
	bool intersectv;
	CVector addnode(CVector point);
	
	double distprec;
    
	bool glinee,glineb;
	int uncount;
	bool inReg;
	bool rotclick;
	string handle;
	CConstraint* constraint;
	vector<CConstraint* > vconstraint;
    
};
#endif /* defined(__testcommand__CFigure__) */
