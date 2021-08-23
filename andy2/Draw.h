// Draw.h: interface for the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAW_H__B950D749_7065_4C5D_ABC3_B8B8FBA2A264__INCLUDED_)
#define AFX_DRAW_H__B950D749_7065_4C5D_ABC3_B8B8FBA2A264__INCLUDED_

#include "DimA.h"	// Added by ClassView
#include "DimL.h"	// Added by ClassView
#include "Dim.h"	// Added by ClassView
#pragma warning(disable:4786)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
//#include <queue>
#include<deque>
#include "line.h"
#include "Cercle.h"
#include "Rectangle.h"
#include"TVector.h"
#include "Bezier.h"	// Added by ClassView
#include "QLine.h"
#include "TextCad.h"	// Added by ClassView
#include "inter.h"
#include "Vector.h"	// Added by ClassView
#include "image.h"
#include "cam.h"
#include "memento.h"
#include "snap.h"
#include "property.h"
#include "Libdialog.h"
#include <stack>
using namespace std;


class CDraw:public CTVector,public CSubject,public CObserver
{
public:
	bool mouseon;
	bool valid, candraw;
	float getFitPrintRatio();
	void fitToPage(bool _fit);
public:
	bool vectorconstraint(CVector point,int mode=-1);
	bool pointconstraint(CVector point);
	void grid(CDC *hdc,CAABB _box);
	void setdimA(int length_type,int precision);
	void getdimA(int& length_type,int& precision);
	void setdimL(int length_type,int length_name,int precision);
	void getdimL(int& length_type,int& length_name,int& precision);
	void saveDXF(CDC *hdc,CStdioFile& file);
	void savePNG(CDC *hdc,CBitmap* bitmap, CFile &file);
	void saveJPG(CDC *hdc,CBitmap* bitmap, CFile &file);
	bool fsnapInit();
	void setBmode(CDC* hdc);
	CRect getPrintPage();
	void getfont(CHARFORMAT& lf);
	bool setpara(CString l);
	void setPrintPage(CRect r, float f);
	void getsnap(vector<CProperty*> v);
	void getSnapTangent(CVector& v,CDC* hdc);
	bool getSnapPerp(CVector  vl,CVector vs,CVector& v,CDC* hdc);
	bool getSnapPara(CVector vl,CVector& vs,CVector &v,CDC* hdc);
	bool getSnapNearest(CVector& v,CVector &vl,CDC *hdc);
	bool getSnapMidPoint(CVector& v,CVector &vl,CDC* hdc);
	bool getSnapInter(CVector& v,CDC* hdc);
	bool getSnapExten(CVector& v,CDC* hdc);
	bool getSnapEndPoint(CVector& v,CVector &vl,CDC* hdc);
	bool getSnapCenter(CVector& v,CDC* hdc);
	void getAppInt(CVector& v);
	void setsnap(vector<CProperty *> dlg,CDC* hdc);
	void getPoint(CPoint p,float& u1,float& u2,float& u3,CDC* hdc);
	void addLine2(vector<CVector> v);
	void getfromPoint(CVector& v);
	void getfromPoint(vector<CVector> &vp);
	void setcurrPoint(CVector v);
	void extend(CVector v);
	void clip(CVector v);
	void Offset(float u);
	void copy();
	void forundo(int i,string t);
	void forundo(CFigure* i, string t);
	void forundoc(CFigure* i, string t);
	void MoveTo(CFigure *f, int node, CVector v);
	void MoveTo(CFigure *f, CVector v);
	void rotate(float u, short sens, CVector c);
	void scale(float u, short sens, CVector c);
	void setmouse(bool t);
	void clearmouse(CDC* hdc);
	void drawmouse(CDC* hdc,CPoint mouse,bool in=false);
	void displaygrid(CDC* hdc,float r);
	void endPrint();
	CPoint PreparePrint();
	CPoint PrepareImage();
	CRect getPage();
	void setPage(CSize p);
	void editobj(CDC* hdc);
	void editobj(CVector point);

	void setText(CString text);
	void LookAt(CVector pos,CVector target);
	void translatecam(CVector v);
	void surface2(CString type,float vthick,short cap=0,int ext=0);
	void copy2(float d);
	void copy(CFigure* f, bool cp);
	void mirror(CFigure* f,bool v);
	void rotate(float u, short sens);
	void scale(float u, short sens);
//	bool Trim(CFigure* f1, CFigure* f2, CVector v);
	void Group(CFigure* f1,CFigure* f2);
	void Fillet(CFigure *f1, float u1, CFigure *f2, float u2,float length);
	void Chamfer(CFigure* f1, float u1, CFigure* f2, float u2,float length);
	void Close(CFigure* f, CDC* hdc);
	void Move(CFigure* f, int node, CVector v);
	void Move(CFigure* f, CVector v);
	void Select(CFigure* f, CDC* hdc,bool full=true);
	short getFigures();
	CFigure* getFigure(int i);
	void AddBreak(float u1,float u2);
	void Delete(int i);
	void AddToBlock();
	void AddBlock(string& name);
	void AddBlock2(string& name,string& layer,string& handle,CVector vo);
	void AddBlock3(string& name,float rot_angle,CVector vscale,CVector vo,CVector col_row_count,CVector col_row_spacing);
	void AddArc(CVector p1, CVector p2);
	void AddArc(CVector p1, CVector p2, CVector p3);
	void AddArc(CVector p1,CVector p2, float radius);
	void AddArc(CVector p1,float radius,float startangle, float endangle);
	void AddCircle(CVector p1,CVector p2);
	void AddCircle(CVector p1,CVector p2, CVector p3);
	void AddCircle(CVector v, float radius);
	void AddSpline(vector<CVector>& v,bool _fit=true,CDC* hdc=NULL);
	void AddSpline2(vector<CVector> &v,vector<float> &fv,bool _fit,CDC *hdc=NULL);
	void AddLayer(string& layer_name,int layer_status,int layer_color,string& layer_linetype,int layer_lineweight);
	void AddText(CDC *hdc,CVector &v,string& _text,float yheight,string facename);
	void AddTextStyle(string& style_name,string font_file, float fixed_height,float width_factor);
	void AddViewport(CDC *hdc,CVector &v0_wcs,CVector &v0_dcs,CVector& vo_ucs,CVector& vox_ucs,CVector& voy_ucs,float zoom_pc,float paper_width,float paper_height);
	void AddSpline2(vector<CVector> v);
	void AddLine(vector<CVector>& v);
	void AddRectangle(CVector v1,CVector v2);
	void AddRectangle(float left, float top, float right, float bottom);
	void AddLine(float left, float top, float right, float bottom);
	void edittext();
	void join(bool del,CDC *hdc);
	void cap(bool top,bool bot,bool g,CDC* hdc);
	void scale(CDC *hdc,int sens,CVector prevpoint,CVector postpoint);
	void setVmode(CDC* hdc);
	void setCurrentLayer(string& txt);
	void unlockcurlayer(CListCtrl& tcl,CString txt);
	void lockcurlayer(CListCtrl& tcl,CString txt);

	CVector getobject(CDC* hdc,CVector pos);
	void getcampara(void** param[]);
	void setcamInterest(CSubject* s);
	void getlightpara(void** param[]);
	void SendNotify(CString s,void* param[]);
	void setgeneralInterest(CSubject* s);
	void smooth(int u,int v,int w);
	void drawforbmp(CDC *hdc);
	void setWnd(CCadView * cad);
	void setFFD(CString option);
	void setsnapplane(CString plane);
	const int * getVFint();
	const CFigure** getFvec();
	void setTexture(CString s,CDC* hdc);
	void setInterest(CSubject* s);
	void setpixel(int w,int h);
	CSize setpixel0(int w,int h);
	void fill(CDC *hdc,CPoint pos);
	void perpective(CString s);
	void volume( CDC *hdc);
	void degel(CDC *hdc);
	void surface(CString type,float vthick=0,bool vctop=false,bool vcbot=false,CDC *hdc=NULL,int ext=100);
	FINFO getobif();
	void removeobject(CTreeCtrl& mtree,CDC* hdc);
	void addobject(CTreeCtrl& mtree,CDC* hdc);
	void setobjinfo(CString aut,CString desc,CString name, double cost);
	void setcurlayer(CListCtrl& tcl,CString txt);
	void setclayer(CString txt,int state);
	void uplayer(CString &txt);
	void downlayer(CString &txt);
	void removelayer(CString& txt);
	void addlayer(CListCtrl &tcl,CString ltext);
	void initlayer(CListCtrl &tcl);
	void setsnap(bool b);
	void unfill(CDC *hdc);
	void Insertlib(CDC *hdc,CString& f,CString& l,CVector pos);
	void Initlib(CLibdialog& tctl);
	void InitlibDxf(CLibdialog& lbtctl,CFile& file);
	void InitlibAff(CLibdialog& lbtctl,CFile& file);
//	LOGFONT getFont();
	int version;
	void saveBMP(CDC *hdc,CBitmap *bmp, CFile &file);
	void import(CDC *hdc,CFile& file);
	void inittext();
	CVector getMouse(CVector v);
	double getzoomrat();
	CRect getBox();
	
	CPoint getCenter();
	CRect getgrid(CSize p);
	void setfitzoom(double& d);
	void setinitzoom();
	CRect getAllBox();
	void setCenter(CVector p);
	void setzoomrat(double zr,CFigure* f=NULL);
	bool Trim(CDC* hdc,CVector v,bool side);
	void setFiltparam(double lk);
	void setChamfparam(double ld);
	void pastearray(CDC *hdc, bool of,int nbrow,int nbcol,double distx,double disty,int nblevel,double lspacing);
	void copyRSparam2(CDC *hdc,double angle, int nbcopy,int nblevel,int dlevel,bool align,CVector v);
	void copyRSparam(CDC *hdc,double angle, int nbcopy,int nblevel,int dlevel,bool align);
	void getBinfo(CVector point);
	CPoint txtend(CDC *hdc);
	CPoint txthome(CDC *hdc);
	CPoint deletetxt(CDC *hdc);
	void setlinewidth(double sl);
	void setlinestyle(DWORD lst);
	void pos(CString posit);
	void ungroup(CDC *hdc);
	bool flip(bool vert);
	void slide(CDC *hdc,CVector pos);
	CPoint setFont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf);
	CPoint movecurskb(CDC *hdc,CString dir);
	CPoint entertxt(CDC *hdc);
	CPoint deletebk(CDC *hdc);
	CPoint drawtext(CDC *hdc, UINT nchar);
	void GetTextrec(CWnd* wnd,CDC *hdc);
	bool finDimA();
	bool straightDimA(bool st);

	bool change;
	void group(CDC *hdc);
	CRect grid(CDC *rhdc,CDC *hdc,CSize cp);
	void redo(CDC *hdc,string& cmd);
	void undo(string& cmd,bool rdo=true);
	void redoc(CDC *hdc);
	void undoc(bool rdo=true);
	void forundo(CWnd* wnd,CDC *hdc);
	void setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor);
	COLORREF lcolor;
	void setEndPoly(bool end);
	void alignbyLine(CDC *hdc,CVector point);
	void copybyCenter(CDC *hdc,CVector point);
	void copyRS(CDC *hdc, CVector center, bool align);
	bool copyl(CDC *hdc, CVector point,bool cp);
	void deleteObject(CDC *hdc);
	void SelectRotState(bool value);
	void open00(CDC *hdc,CFile& file);
	void save00(CDC* hdc,CFile& file);
	void open(CDC *hdc,CFile& file);
	void save(CDC* hdc,CFile& file);
	void Init();
	void paste(CDC *hdc,CVector point);
	void cut(CDC *hdc);
	bool getselect();
	void copyf();
	bool closecurve(CVector point,CDC *hdc);
	bool breakcurve(CVector point);
	bool deletenode(CVector point,CDC *hdc);
	bool addnode(CVector point,CDC *hdc);
	void movepoint(CDC *hdc,CVector point);
	void selectRotateCenter(CDC *hdc,CVector prevpoint,CVector postpos);
	bool mirrorselect(CDC *hdc,CVector point,bool cp);
	void rotate (CDC *hdc,int sens,CVector prevpoint,CVector postpoint);
	void rotatecam (int sens,CVector prevpoint,CVector postpoint,bool b=false);
	void rotatecam (int sens,float angle,bool b=false);
	bool translate(CWnd *wnd,CDC *hdc,CVector PrevPos, CVector PostPos,int key);
	bool translatecam(int sens,CVector prevpoint,CVector postpoint);
//	void deplace(CPoint point);
	void displayselect(CDC *hdc);
	bool select(bool pselect,int multiselect,CVector point,CDC *hdc);
	void finaladd(CDC *hdc,CString figure,CVector pos2,CString option);
	void Create(CDC *hdc,CString figure,CVector point);
	void display(CDC *rhdc,CDC *hdc);
	bool add(CString figure,bool fPrevLine,CDC* hdc,CVector point);
	bool fsnap(CVector& p,CDC* hdc);
	bool fsnapPoint(CVector &p, CDC* hdc);
	CDraw();
	virtual ~CDraw();
	bool fittopage;
	void cleardraw(CDC* hdc);

protected:
	void initlayer();
	void group(CLibS &lib);
	void create(CFigure* f,int i=-1);

	
private:
	CRectangle printpage;
	CAABB box,prevsbox;
	CAABB sc_box;
	CCAM cam;
	CSnap snappy;
	CFigure* snap_fig,*curr_fig;

	CListCtrl* laylist;
	static bool snap;
	CVector cp;
	double rzoom;
	float print_scale;
	FLAYER currlayer;
	CDimA *DimA;
	CDimL *DimL;
	CDim *Dim;
	bool cancharge;
	int sefit;
	vector<string> vhan;
	int count;
	CTextCad *textcad;
	bool cdel;
	bool bck;
	CBezier *pBezier;
	bool menuselect;
	
	bool B;
	bool Bminus;
	bool selected;
	bool endDraw;
	CPoint prevmouse;
	size_t m,ms;
	int fit,sfit;
	CCercle pCircle,pArc,pc;
	CRectangle pRectangle,pSelect;
	CRectangle page;
	CImage image;
	CLine pLine;
	CDimA *IA;
	CLibS slib;
	CQLine pQLine,pQLineprev;
	CMouse mouse;
	FLAYER curlayer;
	vector<FLAYER> veclayer;
	vector<FSTYLE> vecstyle;
	vector<CFigure*> fig,sfig;
	vector<CFigure*> vs;
	vector<CLibS*> blocks,vblocks;
	vector<CFigure*> cpy;

	//Shape Undo redo
//	CUndo fundo,cundo;
	vector<CMemento*> vmemento;
	vector<CMemento*> rmemento;
	stack<string> undoList;
	stack<string> redoList;
	stack<pair<string,string> > undostack,actionstack,redostack;

	//Camera Undo redo
	vector<CMemento*> vcmemento;
	vector<CMemento*> rcmemento;
	stack<string> undocList;
	stack<string> redocList;

	CVector positions[2]; int ita; 
	CVector v0,v_current;
	int nbc,i,j,iter,jiter,jj;
	//layer management
	CListCtrl* _tcl;
	CTreeCtrl* _tctl;
	CLibdialog* _lbtctl;
	CLibS* current_block;
};

/*class vec
{
	push_back();
	remove();
	iter;
}*/

#endif // !defined(AFX_DRAW_H__B950D749_7065_4C5D_ABC3_B8B8FBA2A264__INCLUDED_)
