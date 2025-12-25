//
//  CSnap.h
//  testcommand
//
//  Created by Serge Deh on 10/18/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CSnap__
#define __testcommand__CSnap__

#include <iostream>
// Snap.h: interface for the CSnap class.
//
//////////////////////////////////////////////////////////////////////
#include "cvector.h"
#include <vector>
#include "cObserver.h"
#include "cproperty.h"

#include "ccommand.h"
#include "ctextcad.h"
#include "csnappara.h"
#include "csnapperp.h"
#include "csnapendp.h"
#include "csnapmidp.h"
#include "csnapintp.h"
#include "csnapnearp.h"
#include "csnapcentp.h"
#include "csnapgridp.h"
#include "csnapparagrid.h"


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
        bool getSnapPoint(CVector& v,CVector &vl,CDC* hdc,string type="");
        void init();
        void executePoint(CVector &v, CDC *hdc);
        void setval(vector<CProperty *>dlg);
        void displaygrid(CDC* hdc,CDraw* draw);
        void init(vector<CProperty *> dlg,CDraw* f,CDC *hdc);
        void execute(CVector& v, CDC* hdc);
        void clear(CDC *hdc);
        void display(CVector v, CDC* hdc);
        void checksnap(CVector v,CDC*hdc);
        void SendNotify(string s, void* param[7]);
        CSnap();
        ~CSnap();
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
        bool	m_appint;
        bool	m_center;
        bool	m_endpoint;
        bool	m_exten;
        bool	m_inter;
        bool	m_midpoint;
        bool	m_nearest;
        bool	m_para;
        bool	m_perp;
        bool	m_snaponobj;
        bool	m_tangent;
        bool	m_trackingon;
        //Grid
        bool	m_gridon;
        bool	m_snapongrid;
        float	m_angle;
        float	m_gridxspacing;
        float	m_gridyspacing;
        float	m_polardistance;
        float	m_xbase;
        float	m_ybase;
        float	m_snapxspacing;
        float	m_snapyspacing;
        
        
    };
    

#endif /* defined(__testcommand__CSnap__) */
