// Snap.h: interface for the CSnap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAP_H__7A22A102_23DF_4F0B_AA9E_848EF549A655__INCLUDED_)
#define AFX_SNAP_H__7A22A102_23DF_4F0B_AA9E_848EF549A655__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vector.h"
#include <vector>
#include "Observer.h"
#include "property.h"

#include "command.h"
#include "textcad.h"
#include "snappara.h"
#include "snapperp.h"
#include "snapendp.h"
#include "snapmidp.h"
#include "snapintp.h"
#include "snapnearp.h"
#include "snapcentp.h"
#include "snapgridp.h"
#include "snapparagrid.h"


struct S
{
	CVector b,e;
	S(CVector p1,CVector p2):b(p1),e(p2){}
	S(){};
	bool operator ==(S s1) {return ((b==s1.b)&&(e==s1.e));}
	int left()
	{
		int x=(b.x<e.x)?b.x:e.x;
		return x;
	}
	int right()
	{
		int x=(b.x>e.x)?b.x:e.x;
		return x;
	}
	int top()
	{
		int x=(b.y<e.y)?b.y:e.y;
		return x;
	}

};

class point 
{
public:
	point(CVector vv,CVector ss,CVector tt):v(vv),u(ss),l(tt){}
	point(CVector vv):v(vv){}
	point(){};
	operator CVector(){return v;}
	CVector v;
	CVector u,l;
};
class CDraw;
class CFigure;
class CSnap : public CObserver,public CCommand  
{
public:
	bool getSnapPoint(CVector& v,CVector &vl,CDC* hdc,CString type="");
	void init();
	void executePoint(CVector &v, CDC *hdc);
	void setval(vector<CProperty *>dlg);
	void displaygrid(CDC* hdc,CDraw* draw);
	void init(vector<CProperty *> dlg,CDraw* f,CDC *hdc);
	void execute(CVector& v, CDC* hdc);
	void clear(CDC *hdc);
	void display(CVector v, CDC* hdc);
	void checksnap(CVector v,CDC*hdc);
	void SendNotify(CString s, void* param[7]);
	CSnap();
	virtual ~CSnap();
	enum snap_mode {endpoint,midpoint,intersection,apparentinter,extension,from,perpendicular,\
	parallel,nearest,temp_track,center,quadrant,tangent};
protected:
private:
	const int *nbf;
	CSnapPara para_snap;
	CSnapPerp perp_snap;
	CSnapEndP endp_snap;
	CSnapMidP midp_snap;
	CSnapIntP intp_snap;
	CSnapNearP nearp_snap;
	CSnapCentP centp_snap;
	CSnapGridP gridp_snap;
	CSnapParaGrid grid_snap;
	bool snapPrev;
	CVector hitpoint,pvl,xvl,xvp;
//	vector<point> v;
	vector<S> segment,vsegment;
	CVector prev,v_current;
	vector<CVector> snp_v;
	int j;
	bool b_prev,visible;
	vector<snap_mode> vsnap;
	CDraw* draw;
	CVector vprev;
	CFigure* fprev;
	bool bprev;
	CTextCad tool;
//Grid and snap parameters
	vector<CProperty*> val;
//Object snap
	BOOL	m_appint;
	BOOL	m_center;
	BOOL	m_endpoint;
	BOOL	m_exten;
	BOOL	m_inter;
	BOOL	m_midpoint;
	BOOL	m_nearest;
	BOOL	m_para;
	BOOL	m_perp;
	BOOL	m_snaponobj;
	BOOL	m_tangent;
	BOOL	m_trackingon;
//Grid
	BOOL	m_gridon;
	BOOL	m_snapongrid;
	float	m_angle;
	float	m_gridxspacing;
	float	m_gridyspacing;
	float	m_polardistance;
	float	m_xbase;
	float	m_ybase;
	float	m_snapxspacing;
	float	m_snapyspacing;


};

#endif // !defined(AFX_SNAP_H__7A22A102_23DF_4F0B_AA9E_848EF549A655__INCLUDED_)
