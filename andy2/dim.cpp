// Dim.cpp: implementation of the CDim class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Dim.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDim::CDim()
{
	name="CDim";
	state=false;

}

CDim::~CDim()
{

}
CDim::CDim(CFile &file,CDC* hdc)
{
	state=false;
	openfile(file,hdc);
	name="CDim";

}

bool CDim::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	point.z=0;
	if(!state)
	{
		switch(style)
		{
		case multline:
			{
				int t=hdc->SetROP2(R2_NOTXORPEN);
				draw(hdc);

				getEl(0)->connectNodeTo(point,1,false);
				getEl(1)->offset(getEl(0),5);
				
				draw(hdc);
				hdc->SetROP2(t);
				return true;
				break;

			}
		case leader:
			{
				int t=hdc->SetROP2(R2_NOTXORPEN);
				draw(hdc);

				getEl(1)->connectNodeTo(point,1,false);
//				getEl(1)->setRefLine(0,1);
//				getEl(2)->setRefLine(0,1);
				getEl(0)->connectTo(getEl(1),0,0,2);
				getEl(2)->connectTo(getEl(1),1,0,0);
			    getEl(0)->connectTo(getEl(1),0,1,2);
				CVector vw=getEl(2)->getPoint(1)+polarc(100,argu(getEl(2)->getRefLine()));
//				getEl(3)->TranslateTo(vw);
				
				draw(hdc);
				hdc->SetROP2(t);
				return true;
				break;
			}
		default:
			{
				pline.setMove(true,point);
				ptsPrevBegin=point;
				pline.draw(fPrevLine,hdc,point);
				return true;
//				return pline.draw(fPrevLine,hdc,point);
			}
		}

	}
	else
	{
		if((style==horiz)||(style==vert)||(style==free))
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
			int t=hdc->SetROP2(R2_NOTXORPEN);
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);

			getEl(0)->Translate(v);
			getEl(1)->Translate(v);
			getEl(2)->Translate(v);
			getEl(3)->Translate(v);//,1);
			getEl(4)->Translate(v);//,0);

			getEl(3)->connectNodeTo(bl,0,false);
			getEl(4)->connectNodeTo(bf,0,false);
			
			getEl(3)->connectNodeToL(getEl(0)->Vector(1),30,1);
			getEl(4)->connectNodeToL(getEl(2)->Vector(1),30,1);

			getEl(5)->Translate(v);
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);
//			draw(hdc);
			ptsPrevBegin=point;
			hdc->SetROP2(t);
		}
		else
		if((style==diam)||(style==radius)||(style==leader))
		{
			int t=hdc->SetROP2(R2_NOTXORPEN);
			CVector p1=point-ptsPrevEnd;
			CVector p2=ptsPrevBegin-ptsPrevEnd;
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
//			getEl(3)->draw(hdc);
			float f=argu(p1)-argu(p2);

			CVector v=point-linesel[0];
			CVector r = linesel[2] - linesel[0];
			v= linesel[0] + polarc(absc(r),argu(v));

			getEl(1)->connectTo(v,0);
			getEl(1)->connectNodeTo(point,1);
			getEl(2)->connectTo(getEl(1),1,0,0);
		    getEl(0)->connectTo(getEl(1),0,1,2);
		//    getEl(3)->connectTo(getEl(2),0,0,0);
			CVector vw=getEl(2)->getPoint(1)+polarc(100,argu(getEl(2)->getRefLine()));
			getEl(3)->TranslateTo(vw);
			
			
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
//			getEl(3)->draw(hdc);
			ptsPrevBegin=point;
			hdc->SetROP2(t);

		}
		else
		if(style==ang)
		{
			
			CVector center;
			CVector c1,c2;
		//CVector point = linesel[1] + linesel[4],c1,c2,center;
//		point = point / 2;
//			point=ppoint;
			getArc(center,c1,c2,point);
			if((center==c1)||(center==c2)) return false;

			int t=hdc->SetROP2(R2_NOTXORPEN);
			getEl(2)->draw(hdc);
			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);
//			getEl(5)->draw(hdc);

			((CCercle*)getEl(2))->drawArc2(center,c1,c2);//argu(vv));
			((CCercle*)getEl(2))->addtovec(hdc);

			getEl(0)->connectTo(getEl(2),0,1,2);
		    getEl(1)->connectTo(getEl(2),1,1,2);
			getEl(3)->connectTo(getEl(2),0,0,0);
			getEl(4)->connectTo(getEl(2),1,0,0);

			getEl(3)->connectNodeTo(center,0);
			getEl(4)->connectNodeTo(center,0);
			getEl(3)->connectNodeToL(getEl(2)->Vector(0),30,1);
			getEl(4)->connectNodeToL(getEl(2)->LVector(),30,1);

			double g=((CCercle*)getEl(2))->computeAngle();
			g=(360*g)/(2*pi);
			CString sp;

			sp.Format(_T("%.2f"),g);//*delta);

		//	((CTextCad*)getEl(5))->setText(sp+"deg",hdc);
			getEl(5)->connectTo(getEl(2),0.5,0);


			getEl(0)->draw(hdc);
			getEl(1)->draw(hdc);
			getEl(2)->draw(hdc);
			getEl(3)->draw(hdc);
			getEl(4)->draw(hdc);
//			getEl(5)->draw(hdc);
			
			ptsPrevBegin=point;
			hdc->SetROP2(t);

		}
		else
		if(style==leader)
		{
			int t=hdc->SetROP2(R2_NOTXORPEN);
			draw(hdc);

			getEl(1)->connectNodeTo(point,2,false);
			
			draw(hdc);
			hdc->SetROP2(t);

		}
	}

}
void CDim::setPtsBegin(CVector pos)
{
	switch(style)
	{
	case leader:
	{
/*	v1line= CLine(CVector(0,0),CVector(0,10));
	v1line.setRefLine(0,1);
	v1line.connectTo(pos,0);
//	v1line.connectNodeTo(pos,1);

	vector<CVector> va;
	va.push_back(CVector(7,0));
	va.push_back(CVector(-7,2));
	va.push_back(CVector(-7,-2));

    arrow1= CLine(va);
	arrow1.closecurve(arrow1.Vector(0),NULL);
	arrow1.setRefLine(0,1.5);
    arrow1.connectTo(&v1line,0,0,2);

	add(&arrow1);
	add(&v1line);*/
	v1line= CLine(CVector(0,0),CVector(60,0));
	v2line = v1line;
	v1line.setRefLine(0,1);
	v2line.setRefLine(0,1);
	v1line.connectTo(pos,0);
	v2line.connectTo(&v1line,1,0,0);

		v1line.setRefLine(1,0);
		arrow11.initArrow(0,v1line,0,2.5,2);
	


//		add(&pline);
		add(&arrow11);
		add(&v1line);
		add(&v2line);

	break;
	}
	case multline:
		{
			v1line= CLine(CVector(0,0),CVector(0,10));
			v1line.setRefLine(0,1);
			v1line.connectNodeTo(pos,0);
			v2line = v1line;
			v2line.Translate(CVector(0,10));
			add(&v1line);
			add(&v2line);
			break;
		}
	default:
		pline.setPtsBegin(pos);
	}
}
void CDim::create(CVector pos)
{
	pline.create(pos);
}
const CAABB CDim::getbox(CDC* hdc) 
{
	bool b=multiselect;
	multiselect=false;
	SELECT s=select;
	updatecore();
	select=s;
	multiselect=b;
	return box;
}
void CDim::UpdateDim(CFigure* f,CDC* hdc)
{
	vector< vector<CVector> > pvv=d_params[f];
	int j=pvv.size();
	float u=pvv[0][3].z;
	float v=pvv[1][3].z;
	bl=f->getPoint(pvv[0][3].z);
	bf=f->getPoint(pvv[1][3].z);
//	pline=CLine(v1,v2);
//	pline.ptbegin[0]=v1;
//	pline.ptend.push_back(v2);
//	init();
	buildDim(hdc,u,v);
}
void CDim::buildDim(CDC* hdc,float u, float v)
{
	CVector ve;
	CVector vb;
	if((style==horiz)||(style==vert)||(style==free))
	{
//	pline.create(pos);
//	vb=pline.ptbegin[0];
//	ve=pline.ptend[0];
//	bl=vb;
//	bf = ve;
		int t=hdc->SetROP2(R2_NOTXORPEN);
		draw(hdc);
			vb=getEl(3)->TranslateTo(bl,0,1);
			ve=getEl(4)->TranslateTo(bf,0,1);
			getEl(0)->Translate(vb);
			getEl(2)->Translate(ve);
			getEl(1)->connectNodeTo(getEl(0)->Vector(0),0);
			getEl(1)->connectNodeTo(getEl(0)->Vector(0),0.5);
			getEl(1)->connectNodeTo(getEl(2)->Vector(0),1);
			CVector pr=getEl(1)->getCenter();
			getEl(1)->computedist();
			((CDimText*)getEl(5))->initText(_T("linear-meter"),hdc,pr,getEl(1)->myinfo.distance);

//			getEl(5)->Translate(vb);//,1);
			getEl(3)->connectNodeToL(getEl(0)->Vector(1),30,1);
			getEl(4)->connectNodeToL(getEl(2)->Vector(1),30,1);
			
			
//			getEl(3)->connectNodeToL(getEl(0)->Vector(1),30,1);
//			getEl(4)->connectNodeToL(getEl(2)->Vector(1),30,1);
		draw(hdc);
		hdc->SetROP2(t);
		return;

	}
	if((style==horiz)||(style==vert)||(style==free))
	{
		if(style==horiz)
		{
		pline.ptbegin[0].y=pline.ptend[0].y;
		}
		else
		if(style==vert)
		{
		pline.ptbegin[0].x=pline.ptend[0].x;
		}
		pline.setMesh();

		CVector v(pline.ptbegin[0],pline.ptend[0]);
		ptsPrevEnd=v;
		float arrow_length;//=3mm
		float arrow_width=arrow_length/3;

		pline.setRefLine(1,0);
		arrow11.initArrow(0,pline,0,1,2);
		pline.setRefLine(0,1);
		arrow22.initArrow(0,pline,1,1,2);

		v1line.ptbegin.clear();
		v1line.ptend.clear();
		v2line.ptbegin.clear();
		v2line.ptend.clear();

		v1line.ptbegin.push_back(vb);
		v1line.ptend.push_back(pline.ptbegin[0]);
		v2line.ptbegin.push_back(ve);
		v2line.ptend.push_back(pline.ptend[0]);
		v1line.setMesh();
		v2line.setMesh();


		CVector pr=pline.getCenter();
		pline.computedist();
		text2.initText(_T("linear-meter"),hdc,pr,pline.myinfo.distance);


		add(&arrow11);
		add(&pline);
		add(&arrow22);
		add(&v1line);
		add(&v2line);
		add(&text2);
		draw(hdc);
	}
	else
	if((style==diam)||(style==radius))
	{

	v1line= CLine(CVector(0,0),CVector(60,0));
	v2line = v1line;
	v1line.setRefLine(0,1);
	v2line.setRefLine(0,1);
	if(style!=leader)
	{
	v1line.connectTo(linesel[2],0);
	v1line.connectNodeTo(linesel[0],1);
	}
	v2line.connectTo(&v1line,1,0,0);

		v1line.setRefLine(1,0);
		arrow11.initArrow(0,v1line,0,2.5,2);
	
		CString sp;
		float r;
		CVector vw=v2line.getPoint(1)+polarc(100,argu(v2line.getRefLine()));
		if(style==radius)
		{
			r=absc(linesel[1]);
//			sp.Format(_T("%.2f"),r*0.01);
//			text.assign(hdc,vw,"R"+sp);
			text2.initText("radius-meter",hdc,vw,r);
		}
		else
		if(style==diam)
		{
			r=absc(linesel[1])*2;
//			char c= 'D';
//			sp.Format(_T("%c%.2f"),c,r*0.01);
//			text.assign(hdc,vw,sp);
			text2.initText("diameter-meter",hdc,vw,r);
		}
		else
		{
			char c= 'D';
			sp="Leader text";
			text.assign(hdc,vw,sp);

		}


//		add(&pline);
		add(&arrow11);
		add(&v1line);
		add(&v2line);
		if(style==leader)
			add(&text);
		else
			add(&text2);
		draw(hdc);
		return ;

	}
	else
	if(style==ang)
	{
		CString sp;
		CVector point = linesel[1] + linesel[4],c1,c2,center;
		point = point / 2;
		ppoint=point;
		c1=ppoint;
//		point=linesel[4];
		getArc(center,c1,c2,point);
		cline.setType("Arc");
		if((center==c1)||(center==c2)) return ;
		cline.drawArc2(center,c1,c2);//argu(vv));
		cline.addtovec(hdc);
		double g=cline.computeAngle();
/*		g=(360*g)/(2*pi);
//		if(g==0) return true;;

		sp.Format(_T("%.2f"),g);//*delta);

		CVector pr=cline.getCenter();
		cline.computedist();
		text.assign(hdc,cline.getPoint(0.5),sp+"deg");*/
		text2.initText("angle-degree",hdc,cline.getPoint(0.5),g);
		ptsPrevBegin=cline.pc;

	    CVector v0(cline.selectvec[0],cline.selectvec[1]);


		arrow11.initArrow(0,cline,0,1,2,true);
		arrow22.initArrow(0,cline,1,1,2);

		v1line= CLine(CVector(0,0),CVector(0,10));
		v2line = v1line;
		v1line.setRefLine(0,1);
		v2line.setRefLine(0,1);
		v1line.connectTo(&arrow11,0,0,0);
		v2line.connectTo(&arrow22,0,0,0);

		v2line.connectNodeTo(center,1);
		v1line.connectNodeTo(center,1);


		add(&arrow11);
		add(&arrow22);
		add(&cline);
		add(&v1line);
		add(&v2line);
		add(&text2);
		draw(hdc);

	}
	else
	if(style==leader)
	{
		CString sp;
		float r;
		CVector vw=getEl(1)->getPoint(1)+polarc(100,argu(getEl(1)->getRefLine()));
		char c= 'D';
		sp="Leader text";
		text.assign(hdc,vw,sp);

		add(&text);
		draw(hdc);
	}
	else if(style==leader)
		{
			text.assign(hdc,getEl(1)->Vector(2));
	//		text.connectTo(getEl(1),2,false);
			add(&text);
			draw(hdc);
		}
}
void CDim::SendNotify(CString s, void *param[])
{
	if(s=="move")
	{
		CFigure* f=(CFigure*)param[0];
		CDC* hdc=(CDC*)param[1];
		if(d_params.find(f)!=d_params.end())
		{
			UpdateDim(f,hdc);
		}
	}

}

void CDim::drivingParam(CFigure* f,vector<CVector> vv)
{
	if(d_params.find(f)==d_params.end())
	{
		vector< vector<CVector> > vvv;
		vvv.push_back(vv);
		d_params.insert(make_pair(f,vvv));
	}
	else
	{
		vector< vector< CVector> > pvv;
		pvv=d_params[f];
		int j=pvv.size();
		for(int i=0;i<j;i++)
		{
			if(pvv[i]==vv)
				return;
		}
		d_params[f].push_back(vv);
	}
}
bool CDim::getCharge(CDC *hdc)
{
	if(!state) 
	{
	state=true;
	CVector ve;
	CVector vb;
	if((style==horiz)||(style==vert)||(style==free))
	{
//	pline.create(pos);
	pline.getCharge();
	vb=pline.ptbegin[0];
	ve=pline.ptend[0];
	bl=vb;
	bf = ve;

	}
	
	if((style==horiz)||(style==vert)||(style==free))
	{
		if(style==horiz)
		{
		pline.ptbegin[0].y=pline.ptend[0].y;
		}
		else
		if(style==vert)
		{
		pline.ptbegin[0].x=pline.ptend[0].x;
		}
		pline.setMesh();

		CVector v(pline.ptbegin[0],pline.ptend[0]);
		ptsPrevEnd=v;
		float arrow_length;//=3mm
		float arrow_width=arrow_length/3;

		pline.setRefLine(1,0);
		arrow11.initArrow(0,pline,0,1,2);
		pline.setRefLine(0,1);
		arrow22.initArrow(0,pline,1,1,2);

		v1line.ptbegin.clear();
		v1line.ptend.clear();
		v2line.ptbegin.clear();
		v2line.ptend.clear();

		v1line.ptbegin.push_back(vb);
		v1line.ptend.push_back(pline.ptbegin[0]);
		v2line.ptbegin.push_back(ve);
		v2line.ptend.push_back(pline.ptend[0]);
		v1line.setMesh();
		v2line.setMesh();


		CVector pr=pline.getCenter();
		pline.computedist();
//		CString sp;

//		sp.Format(_T("%.2f"),pline.info.distance*0.01);
//		text.assign(hdc,pr,sp);
		text2.initText(_T("linear-meter"),hdc,pr,pline.myinfo.distance);

//		arrow11.constrainedBy(pline,0,0);
//		arrow22.constrainedBy(pline,1,1);
//		constraint=new CConstraint(&v1line,&v1line);
		add(&arrow11);
		add(&pline);
		add(&arrow22);
		add(&v1line);
		add(&v2line);
		add(&text2);
		draw(hdc);
		return true;
	}
	else
	if((style==diam)||(style==radius))
	{

	v1line= CLine(CVector(0,0),CVector(60,0));
	v2line = v1line;
	v1line.setRefLine(0,1);
	v2line.setRefLine(0,1);
	if(style!=leader)
	{
	v1line.connectTo(linesel[2],0);
	v1line.connectNodeTo(linesel[0],1);
	}
	v2line.connectTo(&v1line,1,0,0);

		v1line.setRefLine(1,0);
		arrow11.initArrow(0,v1line,0,2.5,2);
	
		CString sp;
		float r;
		CVector vw=v2line.getPoint(1)+polarc(100,argu(v2line.getRefLine()));
		if(style==radius)
		{
			r=absc(linesel[1]);
//			sp.Format(_T("%.2f"),r*0.01);
//			text.assign(hdc,vw,"R"+sp);
			text2.initText("radius-meter",hdc,vw,r);
		}
		else
		if(style==diam)
		{
			r=absc(linesel[1])*2;
//			char c= 'D';
//			sp.Format(_T("%c%.2f"),c,r*0.01);
//			text.assign(hdc,vw,sp);
			text2.initText("diameter-meter",hdc,vw,r);
		}
		else
		{
			char c= 'D';
			sp="Leader text";
			text.assign(hdc,vw,sp);

		}


//		add(&pline);
		add(&arrow11);
		add(&v1line);
		add(&v2line);
		if(style==leader)
			add(&text);
		else
			add(&text2);
		draw(hdc);
		return true;

	}
	else
	if(style==ang)
	{
/*		linesel[0].v2D();
		linesel[1].v2D();
		linesel[2].v2D();
		linesel[3].v2D();
		linesel[4].v2D();
		cline.v2D();
*/
		CString sp;
		CVector point = linesel[1] + linesel[4],c1,c2,center;
		point = point / 2;
		ppoint=point;
		c1=ppoint;
//		point=linesel[4];
		getArc(center,c1,c2,point);
		cline.setType("Arc");
		if((center==c1)||(center==c2)) return false;
		cline.drawArc2(center,c1,c2);//argu(vv));
		cline.addtovec(hdc);
		double g=cline.computeAngle();
/*		g=(360*g)/(2*pi);
//		if(g==0) return true;;

		sp.Format(_T("%.2f"),g);//*delta);

		CVector pr=cline.getCenter();
		cline.computedist();
		text.assign(hdc,cline.getPoint(0.5),sp+"deg");*/
		text2.initText("angle-degree",hdc,cline.getPoint(0.5),g);
		ptsPrevBegin=cline.pc;
 /*		cline.selectvec[0].v2D();
		cline.selectvec[1].v2D();
		cline.selectvec[2].v2D();
		cline.selectvec[3].v2D();
*/

	    CVector v0(cline.selectvec[0],cline.selectvec[1]);


/*		CVector v(cline.selectvec[0],cline.selectvec[1]);
		vector<CVector> va;
		va.push_back(CVector(10,0));
		va.push_back(CVector(-10,5));
		va.push_back(CVector(-10,-5));

    arrow1= CLine(va);
	arrow1.closecurve(arrow1.Vector(0),hdc);
	arrow2 = arrow1;
	arrow1.setRefLine(0,1.5);
	arrow2.setRefLine(1.5,0);
    arrow1.connectTo(&cline,0,0,2);
    arrow2.connectTo(&cline,1,0,2);
*/
	arrow11.initArrow(0,cline,0,1,2,true);
	arrow22.initArrow(0,cline,1,1,2);

	v1line= CLine(CVector(0,0),CVector(0,10));
	v2line = v1line;
	v1line.setRefLine(0,1);
	v2line.setRefLine(0,1);
	v1line.connectTo(&arrow11,0,0,0);
	v2line.connectTo(&arrow22,0,0,0);

	v2line.connectNodeTo(center,1);
	v1line.connectNodeTo(center,1);

/*		v1line.v3D();
		v2line.v3D();
		cline.v3D();
		arrow1.v3D();
		arrow2.v3D();
	//	text.v3D();
*/

		add(&arrow11);
		add(&arrow22);
		add(&cline);
		add(&v1line);
		add(&v2line);
		add(&text2);
		draw(hdc);
		return true;

	}
	else
	if(style==leader)
	{
		CString sp;
		float r;
		CVector vw=getEl(1)->getPoint(1)+polarc(100,argu(getEl(1)->getRefLine()));
		char c= 'D';
		sp="Leader text";
		text.assign(hdc,vw,sp);

		add(&text);
		draw(hdc);
		state=false;
		return true;
	}
	}
	else
	{
		if(style==leader)
		{
			text.assign(hdc,getEl(1)->Vector(2));
	//		text.connectTo(getEl(1),2,false);
			add(&text);
		}
		state=false;
		return true;
	}
}

void CDim::initL()
{
	pline.initL();
	v1line.initL();
	v2line.initL();
	arrow1.initL();
	arrow2.initL();
	text.initL();

}
void CDim::translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos)
{
	CLibS::translate(wnd,hdc,prevpos,postpos);
}



bool CDim::PtinRegion(CVector point)
{
	bool b=CLibS::PtinRegion(point);
	if(b) CLibS::setselectmode(full);
	return b;
}

void CDim::setstyle(CString st)
{
	if(st=="DimV") style=vert;
	else
	if(st=="DimH") style=horiz;
	else
	if(st=="DimF") style=free;
	else
	if(st=="DimD") style=diam;
	else
	if(st=="DimR") style=radius;
	else
	if(st=="DimA") style=ang;
	else
	if(st=="leader") style=leader;
	else
	if(st=="multline") style=multline;

}
void CDim::addSL(vector<CVector> vec)
{
	vector<CVector>::iterator pt;
	for(pt=vec.begin();pt<vec.end();pt++)
	{
		linesel.push_back(*pt);
	}

}

void CDim::draw(CDC *hdc)
{
	CLibS::draw(hdc);

}

bool CDim::isReady()
{
	return (!state);
}

void CDim::getArc(CVector &c, CVector &c1, CVector &c2,CVector point)
{
	int i=0;
//	while(true)
	{
			int go=0;
		    c1=c2;
			CVector v11=linesel[0].intersect(linesel[2]);
			CVector v22=linesel[3].intersect(linesel[5]);
			c=v11.intersect(v22);
			CVector v1,v2,vi1,vi2;
			v1=point;
			v1.y+=5;
			v1.x-=5;
			v1=point.intersect(v1);
			vi1=v1.intersect(v22);
			vi2=v1.intersect(v11);
			if((point.y-vi1.y)*(point.y-vi2.y)<0)
			{
//				c2=polarc(absc(point-c),argu(v11));
//				c1=polarc(absc(point-c),argu(v22));//vi1;
				c2=vi2;
				c1=vi1;
				go++;
			}

			v1=point;
			v1.y+=5;
			v1.x+=5;
			v1=point.intersect(v1);
			vi1=v1.intersect(v22);
			vi2=v1.intersect(v11);
			if((point.x-vi1.x)*(point.x-vi2.x)<0)
			{
//				c2=polarc(absc(point-c),argu(v22));
//				c1=polarc(absc(point-c),argu(v11));//vi1;
				c2=vi1;
				c1=vi2;
				go++;
			}
			
			v1=point - c;
			float fv1=absc(v1);
			c1 = c1 - c;
			c1.Normalise();
			c1=c + c1*fv1;
			c2= c2- c;
			c2.Normalise();
			c2=c + c2*fv1;
//			if(go==1) break;
			if(go!=1)
			{
		    c1=c2;
//			CVector v11=linesel[0].intersect(linesel[2]);
//			CVector v22=linesel[3].intersect(linesel[5]);
//			c=v11.intersect(v22);
//			CVector v1,v2,vi1,vi2;
			v1=point;
			v1.y+=5;
			v1=point.intersect(v1);
			vi1=v1.intersect(v22);
			vi2=v1.intersect(v11);
			if((point.y-vi1.y)*(point.y-vi2.y)<0)
			{
//				c2=polarc(absc(point-c),argu(v11));
//				c1=polarc(absc(point-c),argu(v22));//vi1;
				c2=vi2;
				c1=vi1;
				go++;
			}

			v1=point;
			v1.x+=5;
			v1=point.intersect(v1);
			vi1=v1.intersect(v22);
			vi2=v1.intersect(v11);
			if((point.x-vi1.x)*(point.x-vi2.x)<0)
			{
//				c2=polarc(absc(point-c),argu(v22));
//				c1=polarc(absc(point-c),argu(v11));//vi1;
				c2=vi1;
				c1=vi2;
				go++;
			}
			
			v1=point - c;
			c1 = c1 - c;
			c1.Normalise();
			c1=c + c1*absc(v1);
			c2= c2- c;
			c2.Normalise();
			c2=c + c2*absc(v1);

			}
			i++;
	}
}

void CDim::savefile(CFile &file)
{
	file.Write(&style,sizeof(STYLE));
	CLibS::savefile(file);
}

void CDim::openfile(CFile &file,CDC* hdc)
{
	file.Read(&style,sizeof(STYLE));
	CLibS::openfile(file,hdc);
	name="CDim";
}

LONG CDim::ReadFike(CFile &file)
{
	file.Seek(sizeof(STYLE),CFile::current);
	return CLibS::Readfile(file);
}
