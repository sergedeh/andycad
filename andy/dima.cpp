// DimA.cpp: implementation of the CDimA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "DimA.h"
#include "ray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
double CDimA::la,CDimA::ra;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDimA::CDimA()
{
	v1sel=false;
	v2sel=false;
	straight=true;
	name="CDimA";
	it=0;
	tsel=false;

}

CDimA::~CDimA()
{

}
CDimA::CDimA(CFile &file,CDC* hdc)
{
	openfile(file,hdc);
	name="CDimA";
}

bool CDimA::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	return pline.draw(fPrevLine,hdc,point);

}
void CDimA::setPtsBegin(CVector pos)
{
	pline.setPtsBegin(pos);
}
void CDimA::create(CVector pos)
{
	pline.create(pos);
}
bool CDimA::getCharge(CDC *hdc)
{
	bool result;

	linesel[0].v2D();
	linesel[1].v2D();
	linesel[2].v2D();
	linesel[3].v2D();
	linesel[4].v2D();
	pline.v2D();


 	CVector v1=linesel[0].intersect(linesel[1],true);
	CVector v2=linesel[3].intersect(linesel[4],true);
	CVector center=v1.intersect(v2,true);
	center.v3D();
	CString sp;
	if(center.w==0) return false;
	if(!straight)
	{
	CVector vv(center,linesel[1]);

	pline.setType("Arc");
	pline.drawArc2(center,linesel[4],linesel[1]);//argu(vv));
	sp.Format(_T("%.3f"),(360*argu(vv))/(2*pi));//*delta);
	}
	else
	{
	linesel[1].v3D();
	linesel[4].v3D();

	CVector vv(center,linesel[4]);
	CVector vv1(center,linesel[1]);
	pline.setType("Arc");
	pline.drawArc2(center,linesel[4],linesel[1]);//argu(vv));
		
	double g=pline.computeAngle();
	g=(360*g)/(2*pi);

	sp.Format(_T("%.3f"),g);//*delta);
	}
	CVector pr=pline.getCenter();
	pline.computedist();
	text.assign(hdc,pline.pc,sp+"deg");
	pline.selectvec[0].v2D();
	pline.selectvec[1].v2D();
	pline.selectvec[2].v2D();
	pline.selectvec[3].v2D();


  CVector v0(pline.selectvec[0],pline.selectvec[1]);


	CVector v(pline.selectvec[0],pline.selectvec[1]);

	arrow1.ptbegin.clear();
	arrow1.ptend.clear();
	arrow1.ptbegin.push_back(pline.selectvec[0]);
	arrow1.ptend.push_back(pline.selectvec[0]+polarc(20,argu(v,true)+pi/16,true));arrow1.ptbegin.push_back(pline.selectvec[0]+polarc(20,argu(v,true)+pi/16,true));
	arrow1.ptend.push_back(pline.selectvec[0]+polarc(20,argu(v,true)-pi/16,true));arrow1.ptbegin.push_back(pline.selectvec[0]+polarc(20,argu(v,true)-pi/16,true));
	arrow1.ptend.push_back(pline.selectvec[0]);
	arrow1.setClstate(true);
	arrow1.setInit();

	v1line.ptbegin.clear();
	v1line.ptend.clear();
	v1line.ptbegin.push_back(pline.selectvec[0]+polarc(20,argu(v,true)+pi/2,true));
	v1line.ptend.push_back(pline.selectvec[0]+polarc(20,argu(v,true)-pi/2,true));
	v1line.setInit();

	v.assign(pline.selectvec[2],pline.selectvec[3]);

	arrow2.ptbegin.clear();
	arrow2.ptend.clear();
	arrow2.ptbegin.push_back(pline.selectvec[3]);
	arrow2.ptend.push_back(pline.selectvec[3]-polarc(20,argu(v,true)+pi/16,true));arrow2.ptbegin.push_back(pline.selectvec[3]-polarc(20,argu(v,true)+pi/16,true));
	arrow2.ptend.push_back(pline.selectvec[3]-polarc(20,argu(v,true)-pi/16,true));arrow2.ptbegin.push_back(pline.selectvec[3]-polarc(20,argu(v,true)-pi/16,true));
	arrow2.ptend.push_back(pline.selectvec[3]);
	arrow2.setClstate(true);
	arrow2.setInit();
	
	v2line.ptbegin.clear();
	v2line.ptend.clear();
	v2line.ptbegin.push_back(pline.selectvec[3]+polarc(20,argu(v,true)+pi/2,true));
	v2line.ptend.push_back(pline.selectvec[3]+polarc(20,argu(v,true)-pi/2,true));
	v2line.setInit();


	init();

	v1line.v3D();
	v2line.v3D();
//	pline.v3D();
	arrow1.v3D();
	arrow2.v3D();
//	text.v3D();


	add(&arrow1);
	add(&v1line);
	add(&v2line);
	add(&arrow2);
	add(&pline);
	add(&text);
	setInit();
	return result;
}

void CDimA::initL()
{
	pline.initL();
	v1line.initL();
	v2line.initL();
	arrow1.initL();
	arrow2.initL();
	text.initL();

}
void CDimA::translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos)
{
	if(tsel)
	{
		getEl(5)->translate(wnd,hdc,prevpos,postpos);
	}
	else
	{
	CLibS::translate(wnd,hdc,prevpos,postpos);
	}

}


void CDimA::addSL(vector<CVector> vec)
{
	vector<CVector>::iterator pt;
	for(pt=vec.begin();pt<vec.end();pt++)
	{
		linesel.push_back(*pt);
	}

}

bool CDimA::PtinRegion(CVector point)
{
	bool v1selb=false,v2selb=false;
	bool v1sele=false,v2sele=false;
	if(pointinRegion(v1line.ptend[0],point))
	{
	v1sel=true;
	v2sel=false;
	v1sele=true;
	}
	else
	if(pointinRegion(v1line.ptbegin[0],point))
	{
	v1sel=true;v2sel=false;
	v1selb=true;
	}
	else
	if(pointinRegion(v2line.ptend[0],point))
	{
	v2sel=true;v1sel=false;
	v2sele=true;
	}
	else
	if(pointinRegion(v2line.ptbegin[0],point))
	{
	v2sel=true;v1sel=false;
	v2selb=true;
	}
	else
	{
	v2sel=false;v1sel=false;
	}

	if(getEl(5)->inRegion(point))
	{
		tsel=true;
	}


	v1line.setgline(v1selb,v1sele);
	v2line.setgline(v2selb,v2sele);

	return CLibS::PtinRegion(point);

}

void CDimA::orient(double angle)
{
//	straight=!straight;
//	getChargeplus();

}



CFigure * CDimA::getChargeChamf()
{
//	vector<CVector> *arr= new vector<CVector>[2];

	CLine* result=new CLine;

	CRay v1(lineselch[0],lineselch[2]);
	CRay v2(lineselch[3],lineselch[5]);
	CVector center=v1.Intersect(v2);
	if(center.x!=1E-10)
	{


		CVector l1(center,lineselch[1]);
		CVector v11=(l1/absc(l1))*la;
		l1=center+v11;
		double r1=absc(l1-center);
		CVector l2(center,lineselch[4]);
		CVector v12=(l2/absc(l2))*la;
		l2=center+v12;
		double r2=absc(l2-center);
		CVector center2=center+v12+v11;
		CVector l0=l2-l1;
		CVector l01=center-l1;
		CVector vz=l0*l01;
		if(vz.z>0)
		{
			l0=l1;
			l1=l2;
			l2=l0;
		}
		result->ptbegin.clear();
		result->ptend.clear();
		result->ptbegin.push_back(l1);
		result->ptend.push_back(l2);
		result->setMesh();
		CLine ltrim(l1,l2);
		vector<CVector> vv1,vv2,vv3;
		if(vecfig[0]!=vecfig[1])
		{
		vecfig[0]->Trim(vv1,&ltrim);
		vecfig[0]->Extend(&ltrim);
		vecfig[1]->Trim(vv2,&ltrim);
		vecfig[1]->Extend(&ltrim);
		}
		else
		{
			vecfig[0]->Trim(vv3,&ltrim,false,true);//breakcurve(l1,l2);
			vecfig[0]->AddEdge(vv3);
			vecfig[0]->cleancurve();
			return 0;
		}

		return result;
	}
	else
	{
		return 0;
	}

}

void CDimA::addSLChamf(vector<CVector> vec,CFigure* fih)
{
	vector<CVector>::iterator pt;
	for(pt=vec.begin();pt<vec.end();pt++)
	{
		lineselch.push_back(*pt);
	}

	vecfig[it]=fih;
	it++;
	if (it>1) it=0;
}

void CDimA::setchamfparam(double t)
{
	la=t; 
}

void CDimA::setChamfParam(double l)
{
	la=l;
}

void CDimA::setFiltParam(double lk)
{

	ra=lk;
}

bool CDimA::getChargeFilt(CCercle *pl)
{
//	vector<CVector> *arr= new vector<CVector>[2];

	CRay v1(lineselch[0],lineselch[2]);
	CRay v2(lineselch[3],lineselch[5]);
	CVector center=v1.Intersect(v2);
	if(center.x!=1E-10)
	{


		CVector l1(center,lineselch[1]);
		CVector l2(center,lineselch[4]);

		float af=argu(l1)-argu(l2);
		af=af/2;
		float raf=ra;
		ra = ra/tan(af);
		if(ra<0)
		{
		CVector r=l1;
		l1=l2;
		l2=r;
		ra = -ra;
		}
		CVector v11=(l1/absc(l1))*ra;
		CVector v1=l1,v2;
		l1=center+v11;
		v2.assign(center,l1);
		float w1=v2.dot(v1);
/*		if(w1<0)
		{
			v11=-v11;
		l1=center+v11;
		}
*/		double r1,r2;
		CVector v12=(l2/absc(l2))*ra;
		v1=l2;
		l2=center+v12;
		v2.assign(center,l2);
		float w2=v2.dot(v1);
/*		if(w2<0)
		{
		v12=-v12;
		l2=center+v12;
		}
*/
		CVector center2;

		center2=l1+ polarc(raf,argu(v11)- pi/2);
		center=l2+ polarc(raf,argu(v12)+ pi/2);

		r1=absc(l1-center2);
		r2=absc(l2-center2);

		pl->setRadius(v12);
		pl->setType("Arc");

		CVector vv1(center2,l1);
		CVector vv2(center2,l2);
	
		pl->drawArc2(center2,l1,l2);

		CLine ltrim(l1,l2);
		vector<CVector> _vv1,_vv2,_vv3;
		if(vecfig[0]!=vecfig[1])
		{
		vecfig[0]->Trim(_vv1,&ltrim);
		vecfig[0]->Extend(&ltrim);
		vecfig[1]->Trim(_vv2,&ltrim);
		vecfig[1]->Extend(&ltrim);
		}
		else
		{
			vecfig[0]->Trim(_vv3,&ltrim);
//			vecfig[0]->AddEdge(_vv3);
			vecfig[0]->cleancurve();
		}
	return true;
	}
	else
	{
		pl=0;
		return false;
	}
}

vector<CVector> CDimA::getlselch()
{
	return lineselch;
}

bool CDimA::getCharge2CLine(CLine *pl)
{
	CVector vl(lineselch[0],lineselch[3]);
	CVector vr1(lineselch[5],lineselch[3]);
	CVector vr2(lineselch[2],lineselch[0]);
	
	double d1=sqrt(pow(absc(vl),2)-pow(absc(vr1)-absc(vr2),2));
	CVector vf=lineselch[0]+polarc(d1,atan((absc(vr1)-absc(vr2))/d1));
//	CVector vb=lineselch[0]-;
//	double lk=absc(vb);

	pl->setPtsBegin(lineselch[0]);
	pl->create(vf);
	bool result=pl->getCharge();
	return true;
	
}
