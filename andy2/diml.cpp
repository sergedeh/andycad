// DimL.cpp: implementation of the CDimL class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "DimL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimL::CDimL()
{

	name="CDimL";
	state=false;
}

CDimL::~CDimL()
{

}
CDimL::CDimL(CFile &file,CDC* hdc)
{
	name="CDimL";
	state=false;
	openfile(file,hdc);

}
const CAABB CDimL::getbox(CDC* hdc) 
{
	bool b=multiselect;
	multiselect=false;
	SELECT s=select;
	updatecore();
	select=s;
	multiselect=b;
	return box;
}
 
bool CDimL::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	if(!state)
	{
//		ptsPrevBegin=point;
//		return pline.draw(fPrevLine,hdc,point);
				pline.setMove(true,point);
				ptsPrevBegin=point;
				return pline.draw(fPrevLine,hdc,point);
	}
	else
	{
			CVector v;
			if(style==horiz)
			{
			v=CVector(0,point.y-ptsPrevBegin.y);
			}else
			if(style==vert)
			{
			v=CVector(point.x-ptsPrevBegin.x,0);
			}
			else
			if(style==free)
			{
			CVector v1;
			v=ptsPrevEnd.ppprojection(point);
			v1=ptsPrevEnd.ppprojection(ptsPrevBegin);
			v=v1-v;
			}
			// 0 --> pl1 ; 1 --> arrow1 ; 2 -->v1line
			// 3 --> v2line ; 4 --> arrow2 ; 5 --> pl2 ; 6 --> text
			int t=hdc->SetROP2(R2_NOTXORPEN);
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);
			getEl(5)->draw(hdc);
//			getEl(6)->draw(hdc);
			
			getEl(1)->Translate(v);
			getEl(4)->Translate(v);

			getEl(0)->Translate(v);
			getEl(5)->Translate(v);
			getEl(0)->connectNodeTo(bl,0,false);
			getEl(5)->connectNodeTo(bf,0,false);
			getEl(0)->connectNodeToL(getEl(1)->Vector(1),30,1);
			getEl(5)->connectNodeToL(getEl(4)->Vector(1),30,1);
	
			getEl(2)->Translate(v);
			getEl(3)->Translate(v);
			getEl(6)->Translate(v);
			
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);
			getEl(5)->draw(hdc);
//			getEl(6)->draw(hdc);
			ptsPrevBegin=point;
			hdc->SetROP2(t);
	}

}
void CDimL::setPtsBegin(CVector pos)
{
	pline.setPtsBegin(pos);
}
void CDimL::create(CVector pos)
{
	pline.create(pos);
}
bool CDimL::getCharge(CDC *hdc)
{
	if(!state) 
	{
	state=true;

	bool result;
	result=pline.getCharge();
	pline.v2D();

	CVector pbf;
	bl=pline.Vector(0);
	bf=pline.Vector(1);
	pbf=bf;
	if(style==horiz)
	{
		bf.y=bl.y;
		pline.setVector(1,bf);
		bf =pbf;
	}
	else
	if(style==vert)
	{
		bf.x=bl.x;
		pline.setVector(1,bf);
		bf = pbf;
	}
	pline.v3D();
	pline.updatecore();
	CVector pr=pline.getCenter();
	pline.computedist();
//	CString sp;
//	sp.Format(_T("%.3f"),pline.info.distance*0.01);//*delta);
//	text.assign(hdc,pr,sp);
	text2.initText("linear-meter",hdc,pr,pline.myinfo.distance);

	pline.v2D();
	CVector vp0(pline.Vector(0),pline.Vector(1));
    ptsPrevEnd =vp0;
	pline.setRefLine(0,1);
	pl1= CLine(CVector(0,0),CVector(0,100));
	pl2 = pl1;
	pl1.setRefLine(0,1);
	pl2.setRefLine(0,1);
	pl1.connectTo(&pline,0,0,1);
	pl2.connectTo(&pline,1,0,1);


	CVector v(pl1.Vector(0),pl1.Vector(1));
/*	vector<CVector> va;
	va.push_back(CVector(7,0));
	va.push_back(CVector(-7,2));
	va.push_back(CVector(-7,-2));

    arrow1= CLine(va);
	arrow1.closecurve(arrow1.Vector(0),hdc);
	arrow2 = arrow1;
	arrow1.setRefLine(0,1.5);
	arrow2.setRefLine(0,1.5);

	arrow1.connectTo(&pl1,0,0,1);
	arrow2.connectTo(&pl2,0,0,1);
	arrow2.rotate(pi,0);
*/
	arrow11.initArrow(0,pline,0,1,2);
	pline.setRefLine(1,0);
	arrow22.initArrow(0,pline,1,1,2);

	v1line = CLine(CVector(-30,0),CVector(30,0));
	v1line.setRefLine(0,1);
	v2line= v1line;
	v1line.connectTo(&arrow11,1,1,2);
	v2line.rotate(pi,0);
	v2line.connectTo(&arrow22,1,1,2);

	if((style==vert)||(style==horiz))
	{
	pl2.connectNodeTo(pbf);

	}
	
	init();
	pline.v3D();
	pl2.v3D();
	pl1.v3D();
	v1line.v3D();
	v2line.v3D();
	arrow1.v3D();
	arrow2.v3D();

	add(&pl1);
	add(&arrow11);
	add(&v1line);
	add(&v2line);
	add(&arrow22);
	add(&pl2);
	add(&text2);
	return result;
	}
}

void CDimL::initL()
{
	pl1.initL();
	pl2.initL();
	v1line.initL();
	v2line.initL();
	arrow1.initL();
	arrow2.initL();
	text.initL();
}
void CDimL::translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos)
{
	CLibS::translate(wnd,hdc,prevpos,postpos);
}



bool CDimL::PtinRegion(CVector point)
{

	return CLibS::PtinRegion(point);
}

void CDimL::setstyle(CString st)
{
	if(st=="DimL") style=vert;
	if(st=="DimLH") style=horiz;
	if(st=="DimLV") style=free;
}

void CDimL::draw(CDC *hdc)
{
	CLibS::draw(hdc);

}

bool CDimL::isReady()
{
	return (!state);

}
void CDimL::savefile(CFile &file)
{
	file.Write(&style,sizeof(STYLE));
	CLibS::savefile(file);
}

void CDimL::openfile(CFile &file,CDC* hdc)
{
	file.Read(&style,sizeof(STYLE));
	CLibS::openfile(file,hdc);
	name="CDimL";
}

LONG CDimL::ReadFike(CFile &file)
{
	file.Seek(sizeof(STYLE),CFile::current);
	return CLibS::Readfile(file);
}
