// LibS.h: interface for the CLibS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIBS_H__9F6CBED4_EFE1_4E48_9C1D_562781A8A909__INCLUDED_)
#define AFX_LIBS_H__9F6CBED4_EFE1_4E48_9C1D_562781A8A909__INCLUDED_
#include "figure.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;
class CLibS  : public CFigure
{
public:
	const CAABB getbox(CDC* hdc);
	virtual void setbox(CAABB b);
	CMesh* Clip0(CFigure* f);
	string getLibName();
	void editobj(CVector point);
	vector<CVector> getSelectvec(CVector point);
	void breakcurve(CVector v1,CVector v2);
	float Min_dist_toEdge(CVector v);
	void OffsetMesh(float u, CFigure* f);
	bool inRegion(CVector point);
	void updatecore();
	void copy(CLibS* l);
	CFigure* generateCopy();
	void Translate(CVector v);
	void TranslateTo(CVector v);
	void rotate(float u, short sens);
	void scale(float u, short sens);
	CFigure* copy2(float d, CFigure *pbulk);
	void connectTo(CLibS* f, int f1, int f2, float u1, float u2);
	void Scale(int sens,CVector prevpoint,CVector postpoint);
	bool takeinfo(CVector point);
	void setMult(bool b);
	void closecurve(CVector point, CDC *hdc);
	void setLayer(FLAYER& lay);
	void setLibstatusV(bool b);
	void setInit();
	void setselectmode(SELECT j);
	CFigure * getEl(int i);
	CLibS(CFile& file, CDC* hdc);
	void openfile(CFile &file,CDC* hdc);
	void savefile(CFile &file);
	void savefiledxf(CStdioFile& file);
	void UpdateMesh();
//	int gethandle();
	void setLibstatus(bool sv);
	void clear();
	void setReflineP(CVector begin, CVector end);
	void setTransref(bool b);
	void moveRotCenter(CDC *hdc, CVector prevpoint, CVector postpoint);
	void setRotateCenter(CVector point);
	bool rotateSM(CDC* hdc, int sens,CVector prevpoint, CVector postpoint);
	void Rotate(int sens,CVector prevpoint,CVector postpoint);
	void setRotClick(bool value);
	void Rotate(CVector point);

	void Copy(CLibS& v);
	int getnblibelemt();
	vector<CFigure*> degroup();
	bool getsel(int i);
	void update(CFigure *el,int pos);
	void copy(vector<CFigure*> el, int it);
	void init();
	void setLcolor(CDC *hdc, COLORREF color, COLORREF bcolor);
	void drawTrans(CDC *hdc);
	
	CLibS();
	CLibS(CString _name);
	void create(vector<CFigure*> el,int i);
	void add(CFigure *el);
	virtual ~CLibS();

	void drawinit(CDC *hdc,CVector begin, CVector end);
	virtual bool PtinRegion(CVector point);
	void draw(CDC* hdc);
	virtual void createvec();
	virtual void translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos);
	void setMultselect(bool mult);
	friend class CInter;


protected :
	void setcore(vector<CVector> co);
	void setmultcore(bool co);
	void setrecselect(int rd);
	CString libname;
	CString libfunct;
	vector<CFigure*> elem;
	int iter;
	bool *sel;
	size_t m;
	size_t bc;
	

};

#endif // !defined(AFX_LIBS_H__9F6CBED4_EFE1_4E48_9C1D_562781A8A909__INCLUDED_)
