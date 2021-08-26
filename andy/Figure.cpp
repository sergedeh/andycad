// Figure.cpp: implementation of the CFigure class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Figure.h"
#include <algorithm>
//#include <typeinfo.h>
#include "unclick.h"
#include "ray.h"
#include "bezier.h"
#include "mouse.h"
#include "image.h"
#include "cximage/ximage.h"
#include "Cadview.h"
#include "rectangle.h"

#include <set>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//bool CFigure::snapb=false;
//CVector CFigure::snapvec;
CVector CFigure::corepoint;
CDC * CFigure::rhdc;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFigure::CFigure()
{
	spline=false;
	snapPrev=false;
	lpStyle=NULL;
	layer.clear=false;
	layer.on=true;
	layer.name="";
	handle="";
	hatch=NULL;
	libst=false;
	intersectv=false;
	snap=false;
	snapstate=O;
	uncount=1;
	lwidth=1;
	lstyle=PS_SOLID|PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_ROUND;
	bcolor=NULL;
	v0.nullvec();
	prevrotateCenter=v0;
	refline=v0;
	cl=false; brk=false;
	colchange=false;
	OpClstate=open;
	linestate=D0;
	multiselect=false;
	core.clear();
	rotstate=R0;
	ptbegin.clear();
	ptend.clear();
//	setUndoparam();
	name="CFigure";
	glinee=false;glineb=false;
lstate=L1; down=false;Up=false;
	//	p0=core.begin();


	ptsBegin=v0;
	ptsEnd=v0;
	prevVangle=v0;
	mytext = NULL;
	pheight=0;
	pwidth=0;
	ptend.clear();
	ptbegin.clear();
	core.clear();
	piterb=ptbegin.end();
	pitere=ptend.begin();
	
	
	click=false;
	Bisclick=false;
	inReg=false;
	distprec=5;
	transref=false;

	alpha=1;

	lplb.lbStyle=BS_SOLID;
	lplb.lbColor=PALETTERGB(15,15,15);
	lplb.lbHatch=NULL;
	
	dwStyleCount=0;
	angle=0;
	multcore=false;
	
	fPrevB=false;
	texture_file.Empty();
	mode_texture=none;
	tex_vert_mode=backcolor;
	box.empty();
//	m_clickstate=new CUnclick(this);
}

CFigure::~CFigure()
{
	delete[] mytext;
	mytext=NULL;
//	free(lpStyle);
/*	dele
	selectvec.clear();
	ptbegin.clear();
	prevptbegin.clear();
	ptend.clear();
	prevptend.clear();
	undovecb.clear();
	undovece.clear();
	redovecb.clear();
	redovece.clear();
	core.clear();
	coreprec.clear();*/
}

bool CFigure::draw(bool fPrevLine, CDC *hdc,CVector point)
 {
                 return TRUE;
 }


void CFigure::setPtsBegin(CVector point)
{
	ptsBegin=point;
		
}


void CFigure::draw(CDC *hdc)
{

/*	pitere=ptend.begin();
	
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
	ptsBegin=*piterb;
	ptsEnd=*pitere;

	
	drawinit(hdc,ptsBegin,ptsEnd);
	
	pitere=pitere+1;
	}
	if (Isrotate)
	{
	hdc->MoveTo(rotateCenter.x,rotateCenter.y-25);
	hdc->LineTo(rotateCenter.x,rotateCenter.y+25);
	hdc->MoveTo(rotateCenter.x-25,rotateCenter.y);
	hdc->LineTo(rotateCenter.x+25,rotateCenter.y);
	}
*/

}

bool CFigure::PtinRegion(CVector point)
{
/*	ptbegin=mesh.getVectors();
	ptend=ptbegin;
	ptbegin.pop_back();
	ptend.erase(ptend.begin());
	
	pitere=ptend.begin();
	CVector uv;
	if((Rectangleselect(point))&&(!multcore))
	{
		click=true;
		select=st;
		return true;
	}
	else
	{
		float f;
		if(mesh.PtonEdge(point,hitpoint,f,uv))
		{
			click=true;
			select=full;
			jpetit=f+uv.x;
			selectvec.clear();
			rotateCenter=box.center();
			CVector v1=mesh.Vector(uv.x);
			selectvec.push_back(v1);
			selectvec.push_back(hitpoint);
			v1=mesh.Vector(uv.y);
			selectvec.push_back(v1);
			return true;
		}
		else
		{
			CVector v0(0,0);
			selectvec.clear();
			selectvec.push_back(v0);
			selectvec.push_back(v0);
			selectvec.push_back(v0);
			click=false;
		}
	}
		return false;
	*/

  if (Rectangleselect(point))
   {
		if((recselectpoint!=rotsca)&&(recselectpoint!=rotmsca))
		{
	   rotateCenter=box.getclosestOpCorner(point);
		}else
		{
			if(recselectpoint==rotsca)
			{
				angle=0;
				if(prevrotateCenter==v0)
				{
				rotateCenter=box.center();
				}
			}
		}
	   click=true;
	   select=st;
	   return true;
   }
	CAABB box2=box;
	box2.inflate(20);
	if(!box2.ccontainpts(point)) 
	{
		click=false;
		prevrotateCenter=v0;
		return false;
	}
		float f;
		CVector uv;

			CFigure* _f=new CLine;
			_f->copy(this);
			CVector v0,v1,v2,v3;
			v0=v0.sgetscrb();
			v1=v0.sgetscrtop();
			CPoint p(v0.x,v0.y);
			v0 = p;
			p.x=v1.x;
			p.y=v1.y;
			v1 =p;
		//	v1.z=0;
		//	v0.z=0;
			CRectangle r(v0,v1);
			clipshape.push_back(&r);
			   for(int i=0;i<clipshape.size();i++)
			   {
				   _f->Clip(clipshape[i],true);
			   }
			clipshape.erase(std::find(clipshape.begin(),clipshape.end(),&r));

		if(_f->mesh.PtonEdge(point,hitpoint,f,uv))
		{
			click=true;
			select=full;
			jpetit=f;//+uv.x;
			selectvec.clear();
			rotateCenter=box.center();
			CVector v1=_f->mesh.Vector(uv.x);
			selectvec.push_back(v1);
			selectvec.push_back(hitpoint);
			v1=_f->mesh.Vector(uv.y);
			selectvec.push_back(v1);
			return true;
		}
		else
		{
			CVector v0(0,0);
			selectvec.clear();
			selectvec.push_back(v0);
			selectvec.push_back(v0);
			selectvec.push_back(v0);
			click=false;
		}
		prevrotateCenter=v0;

	return false;
	
}

bool CFigure::inRegion(CVector point)
{

	bool g=false;
	updatecore();

	if((Rectangleselect(point))&&(!multcore))
	{
		select=st;
		g=true;
	}

	float f;
	CVector uv;
	if(mesh.PtonEdge(point,hitpoint,f,uv))
	{
		click=true;
		select=full;
		jpetit=f+uv.x;
		selectvec.clear();

		selectvec.push_back(mesh.Vertex(uv.x)->v);
		selectvec.push_back(hitpoint);
		selectvec.push_back(mesh.Vertex(uv.y)->v);
		CVector iv(uv.x,uv.y,jpetit);
		selectvec.push_back(iv);
		return true;
	}
	else
	{
		CVector v0(0,0);
		selectvec.clear();
/*		selectvec.push_back(v0);
		selectvec.push_back(v0);
		selectvec.push_back(v0);*/
		click=false;
	}
	
		return false;
}

void CFigure::create()
{
//	x=ptsEnd.x-ptsBegin.x;
//	y=ptsEnd.y-ptsBegin.y;

}

bool CFigure::getSelect()
{	

	return Bisclick;//selected;
}

void CFigure::translate(CWnd* wnd,CDC *hdc,CVector prevpos, CVector postpos)
{

	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);
	int irop=hdc->SetROP2(R2_NOTXORPEN);
		move=true;
		draw(hdc);
		move=false;
	int i=0;
	for(vector<CConstraint*>::iterator it=vconstraint.begin();it!=vconstraint.end();it++)
	{
		(*it)->done=false;
	}


	if(getRotstate()) InitRotState();
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);

/*	if((linestate==D4)||(select==st))
	{
		prevptend=ptend;
		prevptbegin=ptbegin;

		TransformRect(prevpos,postpos);
		if(!multcore) 
		{
			drawTrans(hdc);
		}

	}*/

	if((linestate==D4)||(select==st))
	{
		prevptend=ptend;
		prevptbegin=ptbegin;
		if(recselectpoint==rotsca)
		{
			CFigure::Rotate(-1,prevpos,postpos);
			
		}else
		if(recselectpoint==rotmsca)
		{
			CFigure::moveRotCenter(hdc,prevpos,postpos);
			return;
			
		}else
		{
		int d=(recselectpoint==vsca)?2:(recselectpoint==hsca)?1:-1;
		Scale(d,prevpos,postpos);
		}
		{
			void* param[2];
			param[0]=this;
//			param[1]=true;
			for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
			{
				(*it)->SendNotify("move",param);
			}
			if(!getmultcore()) 
			{
				move=true;
				draw(hdc);
				move=false;
			//	draw(fPrevB,hdc,CVector(0,0));
				return;
			}
		}

	}
	else
	{
		
	prevptbegin=ptbegin;
	prevptend=ptend;

	int  b=10;
	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);//vro.getcooro();
	CVector v;
	CTVector vt;
	CVector vd(prevpos,postpos);
	CVector gre;
	if(transref)
		gre=polarc(absc(vd),argu(refline));
	else
		gre=vd;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(gre);
	vt.endT();

	if((!libst)&&(select==pnt))
		mesh.UpdateSelectedVertex();
	else
	if((libst)||(select==full))
		UpdateMesh();

	vt.popTransform();
	}
//	updatecore();
		move=true;
		draw(hdc);
		move=false;
//	draw(fPrevB,hdc,CVector(0,0));
	hdc->SetROP2(irop);
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
	void* param[2];
	param[0]=this;
	param[1]=hdc;
	for(vector<CObserver*>::iterator it1=observers.begin();it1!=observers.end();it1++)
	{
		(*it1)->SendNotify("move",param);
	}
	
 
}

void CFigure::drawTrans(CDC *hdc)
{
/*	int old=hdc->SetROP2(R2_NOTXORPEN);    
		
		if((!multiselect)||(!libst))
		{
	
		updatecore();	

		vector<CVector>::iterator bonbon=coreprec.begin();

		if(!coreprec.empty())
		{

		for (bonbon=coreprec.begin();bonbon<coreprec.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		CRect R(CVector(bonbon->x-3, bonbon->y+3),CVector(bonbon->x+3, bonbon->y-3));
		hdc->Rectangle(R);
		}

		for (bonbon=core.begin();bonbon<core.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		CRect R(CVector(bonbon->x-3, bonbon->y+3),CVector(bonbon->x+3, bonbon->y-3));
		hdc->Rectangle(R);
		}
		}
		}
	hdc->SetROP2(old);  */  

}



void CFigure::Rotate(CVector point)
{

	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	CVector ptb,pte;	
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector piv=(core[0]+core[4])/2;
	piv=rotateCenter-piv;
	point=rotateCenter-point;
	//piv=point;

	double alphab=argu(point);//-argu(piv);
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptb=*piterb;
		pte=*pitere;

		CVector vb,ve;
		vb=ptb;
		vb=rotateCenter-vb;
		ve=pte;
		ve=rotateCenter-ve;
		angle=argu(vb);
		CVector vbprime;
		CVector veprime;

		vbprime=rotateCenter-polarc(absc(vb),argu(vb)+(-argu(vb)+alphab)/*argu(vb)+pi/32*/);
		veprime=rotateCenter-polarc(absc(ve),argu(ve)+(-argu(vb)+alphab)/*argu(ve)+pi/32*/);

		ptb.x=vbprime.x;
		ptb.y=vbprime.y;
		pte.x=veprime.x;
		pte.y=veprime.y;

		piterb=ptbegin.erase(piterb);
		piterb=ptbegin.insert(piterb,ptb);
		
		pitere=ptend.erase(pitere);
		pitere=ptend.insert(pitere,pte);

	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}

	}
	
		create();


}

void CFigure::Rotate(int sens,CVector prevpoint,CVector postpoint)
{

	postpoint=postpoint-rotateCenter;

	double mi3=argu(postpoint);

	rotate(-angle,sens);
	rotate(mi3,sens);
	angle=mi3;
	updatecore();	


}

void CFigure::Scale(int sens,CVector prevpoint,CVector postpoint)
{

	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	CVector ptb,pte;	
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector piv=(core[0]+core[4])/2;
	piv=rotateCenter-piv;
//	prevpoint=rotateCenter-prevpoint;
//	postpoint=rotateCenter-postpoint;
	
	CVector vx=core[10]-core[8];
	CVector pvx,vx1=vx;
	vx.ppprojection(postpoint-core[8],&pvx);
	double dx=absc(pvx)/absc(vx1);

	CVector vy=core[9]-core[8];
	CVector pvy,vy1=vy;
	vy.ppprojection(postpoint-core[8],&pvy);
	double dy=absc(pvy)/absc(vy1);

	postpoint.v2D();
	prevpoint.v2D();

	CVector n=prevpoint/absc(prevpoint);
	float d=absc(prevpoint)/absc(postpoint);


	CVector vc(core[8],v0);//vc.viewi();
	CVector va(core[0],core[1]);//va.viewi();
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(vc);
	vt.TRotate(argu(va));
	vc.assign(v0,core[8]);//vc.viewi();
//			vt.Translate(vc);
	vt.endT();
	
	vt.pushUnit();
	vt.Translate(-rotateCenter);


	if(sens==1)
	{
	vt.Scale(dx,1,1);
	}else
	if(sens==2)
	{
	vt.Scale(1,dy,1);
	}
	else if(sens==3)
	{
	vt.Scale(1,1,d);
	}
	else
	vt.Scale(dx,dy,d);
	
	vt.Translate(rotateCenter);
	vt.endT();
	UpdateMesh();
	postTranslate(vc);
	vt.popTransform();
	updatecore();	
		create();


}


void CFigure::setRotateCenter(CVector point)
{
	prevrotateCenter=rotateCenter;
	rotateCenter=point;
	setcore();

/*	hdc->MoveTo(rotateCenter.x,rotateCenter.y-25);
	hdc->LineTo(rotateCenter.x,rotateCenter.y+25);
	hdc->MoveTo(rotateCenter.x-25,rotateCenter.y);
	hdc->LineTo(rotateCenter.x+25,rotateCenter.y);*/

}

void CFigure::createobj(vector<CVector> begin, vector<CVector> end)
{
	ptbegin.swap(begin);
	ptend.swap(end);
	updatecore();
	setInit();

}


void CFigure::createvec()
{
	ptbegin.push_back(ptsBegin);
	ptend.push_back(ptsEnd);
	updatecore();

}

void CFigure::drawpoint(CDC *hdc,vector<CVector>::iterator test)
{
	vector<CVector>::iterator ptb, pte;
	int old=hdc->SetROP2(R2_NOTXORPEN);

	if(cl) hdc->BeginPath();

	for (ptb=ptbegin.begin();ptb<ptbegin.end();ptb++)
	{
		if(ptb==test)
		{
		piterpe=prevptend.begin();
		pte=ptend.begin();
		piterpb=prevptbegin.begin();

		ptsBegin=*ptb;
		ptsEnd=*(pte+(ptb-ptbegin.begin()));
		ptsPrevBegin=*(piterpb+(ptb-ptbegin.begin()));
		ptsPrevEnd=*(piterpe+(ptb-ptbegin.begin()));

		drawpointdyna(hdc,ptsPrevBegin,ptsPrevEnd); //virtual fonction
		}
	}

	
	for (pte=ptend.begin();pte<ptend.end();pte++)
	{
		if(pte==test)
		{
		piterpe=prevptend.begin();
		piterpb=prevptbegin.begin();
		ptb=ptbegin.begin();

		ptsBegin=*(ptb+(pte-ptend.begin()));
		ptsEnd=*pte;
		ptsPrevBegin=*(piterpb+(pte-ptend.begin()));
		ptsPrevEnd=*(piterpe+(pte-ptend.begin()));
		
	
		drawpointdyna(hdc,ptsPrevBegin,ptsPrevEnd);

		}
	}

	if(cl)
	{
		hdc->EndPath();
		hdc->StrokeAndFillPath();
	}

	if(cl) hdc->BeginPath();
	for (ptb=ptbegin.begin();ptb<ptbegin.end();ptb++)
	{
		if(ptb==test)
		{
		piterpe=prevptend.begin();
		pte=ptend.begin();
		piterpb=prevptbegin.begin();

		ptsBegin=*ptb;
		ptsEnd=*(pte+(ptb-ptbegin.begin()));
		ptsPrevBegin=*(piterpb+(ptb-ptbegin.begin()));
		ptsPrevEnd=*(piterpe+(ptb-ptbegin.begin()));
		
		drawpointdyna(hdc,ptsBegin,ptsEnd); //virtual fonction
		}
	}

	
	for (pte=ptend.begin();pte<ptend.end();pte++)
	{
		if(pte==test)
		{
		piterpe=prevptend.begin();
		piterpb=prevptbegin.begin();
		ptb=ptbegin.begin();

		ptsBegin=*(ptb+(pte-ptend.begin()));
		ptsEnd=*pte;
		ptsPrevBegin=*(piterpb+(pte-ptend.begin()));
		ptsPrevEnd=*(piterpe+(pte-ptend.begin()));
	
		drawpointdyna(hdc,ptsBegin,ptsEnd);

		}
	}
	
	if(cl)
	{
		hdc->EndPath();
		hdc->StrokeAndFillPath();
	}
	
	
	updatecore();	

		vector<CVector>::iterator bonbon=coreprec.begin();

		if(!coreprec.empty())
		{

		for (bonbon=coreprec.begin();bonbon<coreprec.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		hdc->Rectangle(bonbon->x-3, bonbon->y+3,bonbon->x+3, bonbon->y-3);
		}

		for (bonbon=core.begin();bonbon<core.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		hdc->Rectangle(bonbon->x-3, bonbon->y+3,bonbon->x+3, bonbon->y-3);
		}

	}

		hdc->SetROP2(old);    

}

CVector CFigure::addnode(CVector point, CDC *hdc)
{
	return addnode(point);
}

void CFigure::deletenode(CVector point, CDC *hdc)
{
	PtinNode(point,0);
	mesh.deleteSVertex();
}


void CFigure::cleancurve()
{
	mesh.cleanCurve();
}

void CFigure::closecurve(CVector point,CDC *hdc)
{
	if(!mesh.Vcount()) return;
	if(!mesh.isClosed())
	{
		mesh.Close();//new CEdge(mesh.LastVertex(),mesh.FirstVertex(),mesh.Ecount());
	}
//	cl=true;
//	if(hdc!=NULL)
//	draw(hdc);
}

void CFigure::breakcurve(CVector v1,CVector v2) 
{
	mesh.breakEdge(v1,v2);
}
vector<CFigure*> CFigure::breakcurve2(CVector v1,CVector v2) 
{
	return vector<CFigure*>();
}

void CFigure::drawselect(CDC *hdc)
{
/*	if((!multiselect)||(!libst))
	{
	updatecore();	
	box.draw(hdc);
	}*/
	if((click)&&(!spline))
	{
		pitere=ptend.begin();

		if(select==full)
		{
			box.draw(hdc);
		}
		int jj=hdc->SetROP2(R2_COPYPEN);    			
		CPoint pb,pe;

		if((!multiselect)&&(!libst))
			updatecore();	
	
		CPen pen;
		pen.CreatePen(PS_COSMETIC,5,RGB(255,0,0));
		CPen *oldp=hdc->SelectObject(&pen);
		CBrush brush;
		brush.CreateSolidBrush(RGB(42,112,219));
		CBrush *oldb=hdc->SelectObject(&brush);

		vector<CVector>::iterator bonbon;
			if(select==pnt)
			{
				int io=0;
				for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
				{

					ptsBegin=*piterb;
					pb=ptsBegin;
	
					hdc->MoveTo(ptsBegin); 
//					hdc->Ellipse(CRect(CPoint(pb.x-13, pb.y+13),CPoint(pb.x+13, pb.y-13)));
				}
				mesh.displayVertex(hdc);
		
			}
		hdc->SelectObject(oldp);
		CPen pen1;
		pen1.CreatePen(PS_COSMETIC,5,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen1);

		if(!core.empty())
		{
			if(select==full)
			{
				for (piterb=core.begin();piterb<core.end()-3;piterb++)
				{
					hdc->MoveTo(*piterb); 
					CPoint pbonbon=*piterb;
					CVector vbonbon;
					vbonbon.x=pbonbon.x;
					vbonbon.y=pbonbon.y;
					vbonbon.z=0;
					if(*piterb!=core[8])
					{
						hdc->Ellipse(CRect(CPoint(pbonbon.x-13, pbonbon.y+13),CPoint(pbonbon.x+13, pbonbon.y-13)));
					}
				}
				CPoint pt0(rotateCenter);
				hdc->MoveTo(pt0);
		//		hdc->TextOut(pt0.x,pt0.y,"Ol");
				CPoint pt1(core[13]);
				hdc->SelectObject(oldp);
				CPen pen3;
				pen3.CreatePen(PS_GEOMETRIC,5,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen3);
				hdc->Ellipse(CRect(CPoint(pt0.x-13, pt0.y+13),CPoint(pt0.x+13, pt0.y-13)));

				hdc->SelectObject(oldp);
				CPen pen0;
				CBrush brush0;
				LOGBRUSH lb;
				lb.lbStyle=BS_HOLLOW;
				brush0.CreateBrushIndirect(&lb);
				oldb=hdc->SelectObject(&brush0);
				pen0.CreatePen(PS_COSMETIC,4,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen0);
				hdc->Ellipse(CRect(CPoint(pt1.x-17, pt1.y+17),CPoint(pt1.x+17, pt1.y-17)));

				hdc->SelectObject(oldp);
				CPen pen2;
				pen2.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
				oldp=hdc->SelectObject(&pen2);
				
				hdc->LineTo(pt1);
			}

		}

	hdc->SelectObject(oldb);
	hdc->SetROP2(jj);    
	hdc->SelectObject(oldp);

	}

}


void CFigure::addvec(vector<CVector> vectb, vector<CVector> vecte)
{
	ptbegin=vectb;
	ptend=vecte;
	updatecore();

}

void CFigure::Select(CDC*hdc,CVector pos)
{
	click=true;
	select=full;
	selectSM(hdc);
}


void CFigure::setSelect(bool sel)
{
	Bisclick=sel;

}

bool CFigure::IsOn()
{
	linestate=D1;
 return false;

}

bool CFigure::IsOff()
{
	if (!click)
	return true;
	else return false;
}





void CFigure::setIsready(bool stat)
{
//	D0=stat;

}

bool CFigure::getIsready()
{
	return true;//D0;

}

void CFigure::setMove(bool mv)
{
	move=mv;
	click=false;
}


void CFigure::selectSM(CDC *hdc)
{
	switch(linestate)
		{
		case D0:
		{
			if ((click)||(multiselect))//||libst))
			{
				linestate=D1;
				drawselect(hdc);
				click=false;
			}
			else linestate=D0;
			break;
		}
		case D1:
		{
			if (click||multiselect||libst)
//			if (click||libst)
			{
				linestate=D1; 
				drawselect(hdc);
		//		click=false;
			}
			else 
				if(!click)
				{
					if(recselect||multiselect)
					{
						linestate=D4;
					}
					else if(move)
					{
						linestate=D1;
						move=false;
					}
					else
					{
					linestate=D3;
					drawselect(hdc);
					}
					
					
				}

			break;
		}
		case D2:
		{
			if(click||((multiselect||libst)&&Bisclick)) 
			{
				linestate=D3;
				drawselect(hdc);
			}
			else if (Bisclick)
			{
				linestate=D3;
				drawselect(hdc);
			}else
			if(recselect)
			{
				linestate=D4;
			}
			else
			{
				linestate=D0;
				drawselect(hdc);
			}

			break;
		}
		case D3:
		{
			if (Bisclick)
			{
				linestate=D0; 
			}
			else 
				if (click&&(!Bisclick)) 
				{
				linestate=D1;
				drawselect(hdc);
				}

			break;
		}
		case D4:
		{
			if ((Bisclick)||(!click))
			{
				linestate=D0; 
				drawselect(hdc);
			}else
			if(recselect)
			{
				linestate=D4;
			}
			else	
			if (click) 
				{
				linestate=D2;
				}

			break;
		}

//		default:
		}

}

bool CFigure::inselectedstate()
{
if((linestate==D1)||(linestate==D2)||(linestate==D4)) return true; else return false;

}


bool CFigure::transselectedstate()
{

	if((linestate==D1)||(linestate==D2)||(linestate==D4)) return true; else return false;

}

bool CFigure::unselectedstate()
{
	if(linestate==D3)
	{
		return true;
	}
	else return false;

}

void CFigure::setMultselect(bool mult)
{
	multiselect=mult;

}
bool CFigure::getMultselect()
{
	return multiselect;

}
void CFigure::setInit()
{
/*	linestate=D0;
	click=false;
	multiselect=false;
	multcore=false;
	select=null;*/
}

void CFigure::UpdateSM()
{
	switch(OpClstate)
	{
	case open:
		if (cl) OpClstate=close;
		break;
	case close:
		if(brk) OpClstate=open;
		if(!cl) OpClstate=open;
		break;
	}
}



void CFigure::drawinit(CDC *hdc,CVector begin, CVector end)
{

}

void CFigure::drawpointdyna(CDC *hdc,CVector pbb, CVector pbe)
{
	hdc->MoveTo(pbb); 
	hdc->LineTo(pbe);
}
void CFigure::ScanPolygon(CDC *hdc, COLORREF rgba,CImagex *texture)
{
	try{
//	updatevcore();
	int i = 0;
	int x, y,q;
	int r,g,b;
	HDC hd = hdc->GetSafeHdc();
	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = mesh.view;
	CBitmap* bmp=pView->getBitmap();
	CRect wcr=pView->getClientRect();
	bool ispp=pView->isPrint;
	double xRes=pView->xRes;
	double yRes=pView->yRes;
//	HBITMAP jj=(HBITMAP)bmp->GetSafeHandle();

	BITMAP nb;
	int j=bmp->GetBitmap(&nb);//GetObject(jj,sizeof(BITMAP),NULL);
//	int h=GetObject(jj,j,&nb);
//	if(h==0)
//	{
//		return;
//	}
//	bmp->GetObject(&nb);
	DWORD d=nb.bmWidth*nb.bmHeight*4;
	int bheight= nb.bmHeight ;
	int bwidth = nb.bmWidth ;
	int bpp = 4 ;


	BYTE* bits=new BYTE[d];
	memset(bits,0,d);
	bmp->GetBitmapBits(d,bits);
		CSize bn=wcr.Size();

//	int o=hdc->SetMapMode(MM_TEXT);
	int ar,ag,ab;
	ar= GetRValue(trans_col);
	ag= GetGValue(trans_col);
	ab= GetBValue(trans_col);
	int width=0;
	int height=0;

	vector <Edges> v;
	vector<Edges> vl;
	double u,vv;
	ptbegin=mesh.getVectors();

	int _sz=ptbegin.size();
	if(!mesh.isClosed())
	{
//		new CEdge(mesh.Vertex(mesh.Vcount()-1),mesh.Vertex(0),mesh.Ecount());
		if(!mesh.Close()) return;//new CEdge(mesh.LastVertex(),mesh.FirstVertex(),mesh.Ecount());
	}
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	int ytop=vi->y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=vi->x;
	int ixleft=xleft;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=vi->y;
	int iybot=ybot;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=vi->x;

	CVector tl(xleft,ytop,0);
	CVector lb(xright,ybot,0);
//	hdc->LPtoDP(&tl);
//	hdc->LPtoDP(&lb);
	xleft=tl.x;
	ytop=tl.y;
	float xd;
	float yd;
	width=lb.x-tl.x;
	height=tl.y-lb.y;
	width=(width>0)?width:-width;
	height=(height>0)?height:-height;
	int ouy=hdc->GetMapMode();
	if(mytext!=NULL)
	{
	xd=(float)width/pwidth;
	yd=(float)height/pheight;
	}
	double ph,pw;
	CPoint blend(blend_p);
	hdc->LPtoDP(&blend);
	blend.x=xleft;
	blend.y=ytop;
	CPoint nblend(blend_plane);
	hdc->LPtoDP(&nblend);
	nblend.x=width;
	nblend.y=0;
	blend_radius=width;
//	CPlane pl(CVector(blend.x,blend.y,0),CVector(nblend.x,nblend.y,0));
	float initalpha=0;
	float endalpha=1;
//	blend_mode=linearb;
//	tex_vert_mode=decal;
	TRACE("Starting to clip the shape");
//	CMesh* ms=clipShape(hdc);
//	vector<CEdge*> vel=ms->getEdgeList();
	vector<CEdge*> vel=mesh.getEdgeList();
	CRect rbox=vbox;
	CRect rbox2=box;
	CRect rbox3=box;
	CSize bn3=rbox3.Size();
	hdc->LPtoDP(&rbox);
	hdc->LPtoDP(&rbox2);
	int xxleft=rbox2.left;
	CSize bn2=rbox2.Size();
	BITMAPINFO bmInfo;
	memset(&bmInfo.bmiHeader,0,sizeof(BITMAPINFOHEADER));
	bmInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth=bn2.cx;
	bmInfo.bmiHeader.biHeight=-bn2.cy;
	bmInfo.bmiHeader.biPlanes=1;
	bmInfo.bmiHeader.biBitCount=24;
/*	BYTE* pbase;
	BYTE * pdst;
		HDC TmpDC=CreateCompatibleDC(hdc->GetSafeHdc());
		HBITMAP TmpBmp=CreateDIBSection(hdc->GetSafeHdc(),&bmInfo,DIB_RGB_COLORS,(void**)&pbase,0,0);
		HGDIOBJ TmpObj=SelectObject(TmpDC,TmpBmp);
		BitBlt(TmpDC,0,0,bn3.cx,bn3.cy,hdc->GetSafeHdc(),rbox3.left,rbox3.bottom,SRCCOPY);
	
	long ew = ((((24 * bn2.cx) + 31) / 32) * 4);
*/		if(rbox.top<rbox.bottom)
		{
			int xc=rbox.top;
			rbox.top=rbox.bottom;
			rbox.bottom=xc;
		}
		iybot=rbox.bottom;
		ixleft=rbox.left;
	for(vector<CEdge*>::iterator it=vel.begin();it!=vel.end();it++)
	{
		if(!(*it)) continue;
		CVertex* vx=(*it)->Start();
		CVector t=*vx;
		t.z=0;
		CPoint p1(t);
		hdc->LPtoDP(&p1);
/*		if(ispp)
		{
			p1.x=p1.x*xRes*5;
			p1.y=p1.y*yRes*5;
		}
*/		vertex v1(p1,vx->pun,vx->pvn);

		vx=(*it)->End();
		t=*vx;
		t.z=0;
		CPoint p2(t);
		hdc->LPtoDP(&p2);
/*		if(ispp)
		{
			p2.x=p2.x*xRes;
			p2.y=p2.y*yRes;
		}
*/		vertex v2(p2,vx->pun,vx->pvn);

		CRect r(p1,p2);
		if(r.top<r.bottom)
		{
			int xc=r.top;
			r.top=r.bottom;
			r.bottom=xc;
		}
		if(r.top!=r.bottom)
		{
			Edges s(v1,v2,r);
			if(mode_texture==wrap)
			{
//			Edges s1(v1,v2,rbox);
			s.dv=/*-(float)1/pheight;*/-(s.v_top-s.v_bottom)/pheight;
			s.du=0;///*-(float)1/pwidth;*/-(s.u_top-s.u_bottom)/pheight;
//			s.dv=-(s1.v_top-s1.v_bottom)/pheight;
			}else
			{
//			Edges s1(v1,v2,rbox);
		//	s.dv=-(float)1/pheight;//-(s.v_top-s.v_bottom)/pheight;
		//	s.du=0;/*-(float)1/pwidth;//-(s.u_top-s.u_bottom)/pwidth;*/
//			s.dv=-(s1.v_top-s1.v_bottom)/pheight;
			}
			v.push_back(s);

		}

	}
//   delete ms;
if(v.size()!=0)
   {

   	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	ytop=v.begin()->r.top;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.bottom;
	double u_bottom=gi->getbottom().x;
	double v_bottom=gi->getbottom().y;

	double v_top=v.begin()->gettop().y;
	double u_top=v.begin()->gettop().x;

	
	int fr=	GetRValue(rgba);
	int fg=	GetGValue(rgba);
	int fb=	GetBValue(rgba);
//	ytop=(wcr.bottom<ytop)?wcr.bottom:ytop;
//	ybottom=(wcr.top>ybottom)?ybottom:wcr.top;
	int o=hdc->SetMapMode(MM_TEXT);
	v.begin()->r.top=ytop;
	gi->r.bottom=ybottom;
	for (y=ytop;y>=ybottom;y--) {
//	pdst = pbase+(ytop-y)*ew;

	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y<=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),*i);
				if(il!=vl.end()) 
					vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	insert/remove edges from “active edge list”
	if(mode_texture!=wrap)
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatex(ip,y,width,xleft);//update x coordinate of every active edge
	}
	else
	{
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatexw(ip,y,pwidth,xleft);//update x coordinate of every active edge
	}
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate
	int yt;
	
		int br;
		int bg;
		int bb;

	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	double vleft=ik->v_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double vright=(ik+1)->v_current;
	double du,dv;
	if(mode_texture!=wrap)
	{
	du=(uright-uleft)/(xright-xleft);
	dv=(vright-vleft)/(xright-xleft);
	}else
	{
//		uright=1;uleft=0;
//		vright=1;vleft=1;
	du=(float)1/pwidth;//(uright-uleft)/pwidth;
	dv=0;
	}
	double dx=(double)1/(xright-xleft);

//	double alpha=1;
	xleft=(wcr.left<xleft)?xleft:wcr.left;
	xright=(wcr.right<xright)?wcr.right:xright;
//	pdst=pdst+(xleft-xxleft)*3;
	try{
	for (int x=xleft;x<=xright;x++)
	{
//		if(((bheight-y)*bwidth+x)*bpp>d) 
//			continue;
			COLORREF clo=GetPixel(hd,x,y);
		br=GetRValue(clo);//bits[((bheight-y)*bwidth+x)*bpp+0];
		bg=GetGValue(clo);//bits[((bheight-y)*bwidth+x)*bpp+1];
		bb=GetBValue(clo);//bits[((bheight-y)*bwidth+x)*bpp+2];


		float oldalpha = alpha;

		//		int yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		if(tex_vert_mode==replace)
		{
		 r=mytext[yt].r;
		 g=mytext[yt].g;
		 b=mytext[yt].b;
		//hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		}else
		if(tex_vert_mode==decal)
		{
		//alpha=computealpha(x,y,&pl,initalpha,endalpha);
		 r=(1-alpha)*mytext[yt].r+alpha*fr;
		 g=(1-alpha)*mytext[yt].g+alpha*fg;
		 b=(1-alpha)*mytext[yt].b+alpha*fb;
		}else
		if(tex_vert_mode==multiply)
		{
		 r=(mytext[yt].r/255*fr/255)*255;
		 g=(mytext[yt].g/255*fg/255)*255;
		 b=(mytext[yt].b/255*fb/255)*255;
		}
		else
		if(tex_vert_mode==image_texture)
		{
		float u_wrap;
		float v_wrap;
/*		if(mode_texture!=wrap)
		{
		float g=xd*uleft;
		unsigned t=g;
		long iyd=yd;
		long ixd=xd;
		u_wrap=g-t;

		g=yd*vleft;
		t=g;
		v_wrap=g-t;

		ph=(pheight-1)*v_wrap;
		pw=(pwidth-1)*u_wrap;
//		ph=((iyd%pheight)/pheight)*vleft;
//		pw=((ixd%pwidth)/pwidth)*uleft;
		yt=ph*pwidth+pw;
//		yt=floor((pheight-1)*v_wrap)*pwidth+floor((pwidth-1)*u_wrap);
		}
*/
		if(mode_texture==wrap)
		{
		ph=(pheight-1)*vleft;
		pw=(pwidth-1)*uleft;
		yt=ph*pwidth+pw;
//		yt=floor((pheight-1)*vleft)*pwidth+floor((pwidth-1)*uleft);
		r=hatch[(y-ybottom)*width+x-ixleft].r;
		g=hatch[(y-ybottom)*width+x-ixleft].g;
		b=hatch[(y-ybottom)*width+x-ixleft].b;
//		r=mytext[(y-ybottom)*width+x-ixleft].r;
//		g=mytext[(y-ybottom)*width+x-ixleft].g;
//		b=mytext[(y-ybottom)*width+x-ixleft].b;
		}else
		{
		ph=(pheight-1)*vleft;
		pw=(pwidth-1)*uleft;
		yt=ph*pwidth+pw;

		if ((mytext[yt].r== ar) && (mytext[yt].g== ag) && (mytext[yt].b== ab))
		{
			alpha = 0;
		}
		float _alpha=1;//(float)mytext[yt].a/255;
		r=(1-_alpha)*br+_alpha*mytext[yt].r;
		g=(1-_alpha)*bg+_alpha*mytext[yt].g;
		b=(1-_alpha)*bb+_alpha*mytext[yt].b;

//		r=(1-alpha)*r;
//		g=(1-alpha)*g;
//		b=(1-alpha)*b;
//		r=(1-alpha)*br+alpha*mytext[yt].r;
//		g=(1-alpha)*bg+alpha*mytext[yt].g;
//		b=(1-alpha)*bb+alpha*mytext[yt].b;
		}
		}
		else 
		if(tex_vert_mode==backcolor)
		{
		
		r=(1-alpha)*br+alpha*fr;
		g=(1-alpha)*bg+alpha*fg;
		b=(1-alpha)*bb+alpha*fb;
		}
		if(ispp)
		{
			SetPixelV(hd,x,y,RGB(r,g,b));
		}else
		{
			SetPixelV(hd,x,y,RGB(r,g,b));
		}

				//pdst=pdst+(x-xxleft);
//				*pdst++=b;
//				*pdst++=g;
//				*pdst++=r;

//				bits[(((bheight)-y)*bwidth+x)*bpp+0]=b;
//				bits[(((bheight)-y)*bwidth+x)*bpp+1]=g;
//				bits[(((bheight)-y)*bwidth+x)*bpp+2]=r;

		alpha = oldalpha;
		uleft+=du;
		vleft+=dv;
		if(uleft>1) uleft=0;
		if(vleft>1) vleft=0;
		if(uleft<0) uleft=1;
		if(vleft<0) vleft=1;
	}
	}catch(...)
	{
	CString sp;
	sp.Format(_T("xleft is %i and xright is %i"),&xleft,&xright);
//	AfxMessageBox(sp);
	}
	//	vleft+=dv;
		if(vleft<0) vleft=1;
		if(vleft>1) vleft=0;
	}
//		SetDIBitsToDevice(hdc->GetSafeHdc(),xleft,ytop,xright-xleft,ytop-ybottom,0,0,0,ytop-ybottom,bits,&bmInfo,0);


	if(mode_texture!=wrap)
	{
//	vleft+=dyv;
//	uleft+=dyu;
	}else
	{
//		vleft++;
	}
	}
	hdc->SetMapMode(o);
	}
		rbox=box;
		int tp=rbox.top;
//		rbox.top=rbox.bottom;
//		rbox.bottom=tp;
		bn=rbox.Size();
//		hdc->LPtoDP(&rbox);
//		hdc->DPtoLP(&wcr);
//		wcr.NormalizeRect();
//		bn=wcr.Size();
		hdc->LPtoDP(&bn);
//		SetDIBitsToDevice(hdc->GetSafeHdc(),rbox.left,rbox.bottom,bn.cx,bn.cy,0,0,0,bn.cy,pbase,&bmInfo,0);
//		bmp->SetBitmapBits(bwidth*bheight*4,bits);
//		pView->change=true;
//		pView->bmpchange=true;
//		pView->Invalidate();
//		SetDIBitsToDevice(hdc->GetSafeHdc(),0,0,bn.cx,bn.cy,0,0,0,bn.cy,bmp->pbase,&bmInfo,0);
/*		CDC* hmdc= new CDC;
		hmdc->CreateCompatibleDC(hdc);
		pView->OnPrepareDC(hmdc);
		CBitmap* oldb=hmdc->SelectObject(bmp);
		hdc->DPtoLP(&wcr);
		wcr.NormalizeRect();
		bn=wcr.Size();
		hdc->LPtoDP(&bn);
//		hdc->BitBlt(0,0,bn.cx,bn.cy,hmdc,0,0,SRCCOPY);
//		hdc->StretchBlt(xleft,ytop,xright-xleft,ytop-ybottom,hmdc,xleft,ytop,xright-xleft,ytop-ybottom,SRCCOPY);
		hmdc->SelectObject(oldb);
		delete hmdc;*/
		

	delete [] bits;
	}catch(...)
	{
	CString sp;
	sp.Format(_T("Problem in the Image function"));
	AfxMessageBox(sp);
	}
}	
void CFigure::Hatch(CDC *hdc)
{
/*	CPoint p1=CPoint(mesh.Vertex(1)->v)-CPoint(mesh.Vertex(0)->v);
	CVector v22(p1.x,p1.y,0);
	float ang=argu(v22);
	rotate(prevVangle.x-ang,0);
	prevVangle.x=ang;*/

	updatevcore(true);
	try{
	int i = 0;
	int _w,_h;
	int x, y,q;
	int r,g,b;
	HDC hd = hdc->GetSafeHdc();
	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = mesh.view;
	CBitmap* bmp=pView->getBitmap();
	CRect wcr=pView->getClientRect();

	BITMAP nb;
	int j=bmp->GetBitmap(&nb);//GetObject(jj,sizeof(BITMAP),NULL);
	DWORD d=nb.bmWidth*nb.bmHeight*4;
	int bheight= nb.bmHeight ;
	int bwidth = nb.bmWidth ;
	int bpp = 4 ;


	BYTE* bits=new BYTE[d];
	memset(bits,0,d);
	bmp->GetBitmapBits(d,bits);


	int ar,ag,ab;
	ar= GetRValue(trans_col);
	ag= GetGValue(trans_col);
	ab= GetBValue(trans_col);
	int width=0;
	int height=0;

	vector <Edges> v;
	vector<Edges> vl;
	double u,vv;

	ptend.clear();
	ptend.resize(8);
	for(i=0;i<8;i++)
	{
		ptend[i]=vcore[i];
	}
	CPoint p1=CPoint(ptend[1])-CPoint(ptend[0]);
	CVector v22(p1.x,p1.y,0);
	float ang=argu(v22);
	float cors_a=cos(ang);
	float sin_a=sin(ang);
	CLine lg(ptend);
//	lg.setMultselect(multiselect);
	lg.updatevcore(true);
//	ptbegin=mesh.getVectors();
	viterator vi=min_element(ptend.begin(),ptend.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	double ytop=vi->y;
	vi=min_element(ptend.begin(),ptend.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=vi->x;
	vi=min_element(ptend.begin(),ptend.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=vi->y;
	vi=min_element(ptend.begin(),ptend.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=vi->x;

	CVector tl(xleft,ytop,0);
	CVector lb(xright,ybot,0);
	xleft=tl.x;
	ytop=tl.y;
	float xd;
	float yd;
	width=lb.x-tl.x;
	height=tl.y-lb.y;
	width=(width>0)?width:-width;
	height=(height>0)?height:-height;
	static bool _ps=false;

	if(mytext!=NULL)
	{
	xd=(float)width/pwidth;
	yd=(float)height/pheight;
	}
	double ph,pw;
	CPoint blend(blend_p);
	hdc->LPtoDP(&blend);
	blend.x=xleft;
	blend.y=ytop;
	CPoint nblend(blend_plane);
	hdc->LPtoDP(&nblend);
	nblend.x=width;
	nblend.y=0;
	blend_radius=width;
//	CPlane pl(CVector(blend.x,blend.y,0),CVector(nblend.x,nblend.y,0));
	float initalpha=0;
	float endalpha=1;
	COLORREF clo;
//	blend_mode=linearb;
//	tex_vert_mode=decal;
	TRACE("Starting to clip the shape");
//	CMesh* ms=clipShape(hdc);
//	vector<CEdge*> vel=ms->getEdgeList();
	vector<CEdge*> vel=lg.mesh.getEdgeList();
	CRect rbox=vbox;	
		hdc->LPtoDP(&rbox);
		if(rbox.top<rbox.bottom)
		{
			int xc=rbox.top;
			rbox.top=rbox.bottom;
			rbox.bottom=xc;
		}
	for(vector<CEdge*>::iterator it=vel.begin();it!=vel.end();it++)
	{
		CVertex* vx=(*it)->Start();
		CVector t=*vx;
		CPoint p1(t);
		hdc->LPtoDP(&p1);
		vertex v1(p1,vx->pun,vx->pvn);

		vx=(*it)->End();
		t=*vx;
		CPoint p2(t);
		hdc->LPtoDP(&p2);
		vertex v2(p2,vx->pun,vx->pvn);

		CRect r(p1,p2);
		if(r.top<r.bottom)
		{
			int xc=r.top;
			r.top=r.bottom;
			r.bottom=xc;
		}
		if(r.top!=r.bottom)
		{
			Edges s(v1,v2,r);
			if(mode_texture==wrap)
			{
			Edges s1(v1,v2,rbox);
			s.dv=(float)-1/pheight;
//			s.dv=s.dv/cors_a;//-(s.v_top-s.v_bottom)/pheight;
			s.du=0;//-((s.u_top-s.u_bottom)/pheight)/cors_a;
//			s.dv=(-(s.v_top-s.v_bottom)/pheight);
			}
			v.push_back(s);

		}

	}
//   delete ms;
if(v.size()!=0)
   {

    
	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	ytop=v.begin()->r.top;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.bottom;
	double u_bottom=gi->getbottom().x;
	double v_bottom=gi->getbottom().y;

	double v_top=v.begin()->gettop().y;
	double u_top=v.begin()->gettop().x;


	
	col* text;
	int o=hdc->SetMapMode(MM_TEXT);
//	int fr=	GetRValue(rgba);
//	int fg=	GetGValue(rgba);
//	int fb=	GetBValue(rgba);
	ytop=(wcr.bottom<ytop)?wcr.bottom:ytop;
	ybottom=(wcr.top>ybottom)?ybottom:wcr.top;
	v.begin()->r.top=ytop;
	gi->r.bottom=ybottom;
	_h=ytop-ybottom;
//	vi=min_element(v.begin(),v.end(),pointer_to_binary_function<CPoint,CPoint,bool>(isxleft));
//	double xleft=vi->x;
//	vi=min_element(v.begin(),v.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
//	double xright=vi->x;
	_w=width;
	try{
	if(hatch)
	{
		delete []hatch;
		hatch=NULL;
	}

	hatch= new col[height*width];
	int gb=pheight*pwidth;

/*	text=new col[gb];
	if(!_ps)
	{
	for (int io=0;io<gb;io++)
	{
		text[io]=mytext[io];
	}
	if(mytext!=NULL)
		delete []mytext;
	mytext=new col[_w*_h];
	}
	*/
	
	}catch(...)
	{
		AfxMessageBox("Problem with getting memory for hatch");
	}

	for (y=ytop;y>=ybottom;y--) {
	
	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y<=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),*i);
				if(il!=vl.end()) 
					vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	insert/remove edges from “active edge list”
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatexw(ip,y,ang,xleft);//update x coordinate of every active edge
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate
	int yt;
	
		int br;
		int bg;
		int bb;

	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	double vleft=ik->v_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double vright=(ik+1)->v_current;
	double du,dv;
	du=((float)1/pwidth);//(uright-uleft)/pwidth;
	dv=0;//-((float)(vright-vleft)/pwidth)/cors_a;

	xleft=(wcr.left<xleft)?xleft:wcr.left;
	xright=(wcr.right<xright)?wcr.right:xright;
	try{
	for (int x=xleft;x<=xright;x++)
	{
//		if(((bheight-y)*bwidth+x)*bpp>d) 
//			continue;
//		br=bits[((bheight-y)*bwidth+x)*bpp+0];
//		bg=bits[((bheight-y)*bwidth+x)*bpp+1];
//		bb=bits[((bheight-y)*bwidth+x)*bpp+2];
		clo=hdc->GetPixel(x,y);
		br=GetRValue(clo);
		bg=GetGValue(clo);
		bb=GetBValue(clo);
	
		ph=(pheight-1)*vleft;
		pw=(pwidth-1)*uleft;
		yt=ph*pwidth+pw;
//		yt=(x-xleft)+(y-ybottom)*(xright-xleft);
//		if(!_ps)
		{
		float _alpha=(float)mytext[yt].a/255;
		r=hatch[(y-ybottom)*_w+x-xleft].r=(1-_alpha)*br+_alpha*mytext[yt].r;
		g=hatch[(y-ybottom)*_w+x-xleft].g=(1-_alpha)*bg+_alpha*mytext[yt].g;
		b=hatch[(y-ybottom)*_w+x-xleft].b=(1-_alpha)*bb+_alpha*mytext[yt].b;
		}
/*		else
		{
		r=mytext[(y-ybottom)*_w+x-xleft].r;
		g=mytext[(y-ybottom)*_w+x-xleft].g;
		b=mytext[(y-ybottom)*_w+x-xleft].b;
		}*/
//		SetPixelV(hdc->GetSafeHdc(),x,y,RGB(r,g,b));
//		bits[((bheight-y)*bwidth+x)*bpp+0]=(BYTE)(1-_alpha)*br+_alpha*mytext[yt].r;
//		bits[((bheight-y)*bwidth+x)*bpp+1]=(BYTE)(1-_alpha)*bg+_alpha*mytext[yt].g;
//		bits[((bheight-y)*bwidth+x)*bpp+2]=(BYTE)(1-_alpha)*bb+_alpha*mytext[yt].b;

		uleft+=du;
		vleft+=dv;
		if(uleft>1) uleft=0;
		if(vleft>1) vleft=0;
		if(uleft<0) uleft=1;
		if(vleft<0) vleft=1;
	}
	}catch(...)
	{
	CString sp;
	sp.Format(_T("Hatch xleft is %i and xright is %i"),&xleft,&xright);
//	AfxMessageBox(sp);
	}
	//	vleft+=dv;
//		if(vleft<0) vleft=1;
//		if(vleft>1) vleft=0;

	}
	}
	hdc->SetMapMode(o);
	}
//	bmp->SetBitmapBits(d,bits);
	delete [] bits;
	_ps=true;
	}catch(...)
	{
		AfxMessageBox("Problem with the function Hatch");
	}
}	


///////////////////////////////////////////////////////////////////////////////////////////////////////
////
//// Tracker Management used by CRectangle
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CFigure::updatecore()
{
	if((!multiselect))
	{
	ptbegin=mesh.getVectors();
	if(ptbegin.size()==NULL) return;
	vector<CVector>::iterator coreitb,coreite;
	if(!multiselect) 
		box.empty();
	for (coreitb=ptbegin.begin();coreitb!=ptbegin.end();coreitb++)
	{
		box.add(*coreitb);
	}
	}
//	mesh.updateBoxUV(box);
	setcore();
	
}
void CFigure::updatevcore(bool _u)
{
	if((!multiselect))
	{
	ptend=mesh.getVectors();
	if(ptend.size()==NULL) return;
	vector<CVector>::iterator coreitb,coreite;
	vbox.empty();
	for (coreitb=ptend.begin();coreitb!=ptend.end();coreitb++)
	{
		vbox.add(*coreitb);
	}
	}
	if(_u)
		mesh.updateBoxUV(vbox);
	setvcore();
	
}
 void CFigure::setvcore()
 {
 	CVector interm;
 	vcore.clear();
 	p0=vbox.corner(0);
 //	p01=P01;
 	p1=vbox.corner(1);
 //	p12=P12;
 	p2=vbox.corner(2);
 //	p23=P23;
 	p3=vbox.corner(3);
 //	p30=P30;
 //	pc=(P0+P2)/2;
 //	pc=(P0+P6)/2;
 	pc=vbox.center();
 	vcore.resize(16);
 	vcore[0]=vbox.corner(0);
 	vcore[1]=vbox.corner(1);
 	vcore[2]=vbox.corner(3);
 	vcore[3]=vbox.corner(2);
 	vcore[4]=vbox.corner(4);
 	vcore[5]=vbox.corner(5);
 	vcore[6]=vbox.corner(7);
 	vcore[7]=vbox.corner(6);
 	vcore[8]=pc;
	vcore[9]=(vcore[0]+vcore[1])/2;
	vcore[10]=(vcore[1]+vcore[2])/2;
	vcore[11]=(vcore[2]+vcore[3])/2;
	vcore[12]=(vcore[3]+vcore[0])/2;
 	vcore[13]=rotateCenter + CVector(100,0,0);
 	vcore[14]=pc + CVector(0,100,0);
 	vcore[15]=pc + CVector(0,0,100);

 }

 void CFigure::setcore()
 {
 	CVector interm;
 	if (!core.empty())
 		coreprec=core;
 	core.clear();
 	p0=box.corner(0);
 //	p01=P01;
 	p1=box.corner(1);
 //	p12=P12;
 	p2=box.corner(2);
 //	p23=P23;
 	p3=box.corner(3);
 //	p30=P30;
 //	pc=(P0+P2)/2;
 //	pc=(P0+P6)/2;
 	pc=box.center();
 	core.resize(16);
 	core[0]=box.corner(0);
 	core[1]=box.corner(1);
 	core[2]=box.corner(3);
 	core[3]=box.corner(2);
 	core[4]=box.corner(4);
 	core[5]=box.corner(5);
 	core[6]=box.corner(7);
 	core[7]=box.corner(6);
 	core[8]=pc;
	core[9]=(core[0]+core[1])/2;
	core[10]=(core[1]+core[2])/2;
	core[11]=(core[2]+core[3])/2;
	core[12]=(core[3]+core[0])/2;
	CPoint cr=rotateCenter;
	cr.x+=100;
 	core[13]=cr;//rotateCenter + CPoint(100,0);
 	core[14]=pc + CVector(0,100,0);
 	core[15]=pc + CVector(0,0,100);

 }



///////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// File Management section
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CFigure::savefiledxf(CStdioFile& file)
{

}
void CFigure::savefile(CFile& file)
{

		file.Write(&libst,sizeof(libst));
		file.Write(&OpClstate,sizeof(OpClstate));
		file.Write(&brk,sizeof(brk));
		file.Write(&cl,sizeof(cl));

		file.Write(&bcolor,sizeof(bcolor));
		file.Write(&lplb,sizeof(lplb));
		file.Write(&dwStyleCount, sizeof(dwStyleCount));
//		file.Write(&lpStyle, sizeof(lpStyle));
		file.Write(&lstyle,sizeof(lstyle));
		file.Write(&lwidth,sizeof(lwidth));

		//andycad update begin

		file.Write(&alpha, sizeof(alpha));
		file.Write(&angle, sizeof(angle));
//		file.Write(&blend_p, sizeof(blend_p));
//		file.Write(&blend_mode, sizeof(blend_mode));
//		file.Write(&blend_plane, sizeof(blend_plane));
//		file.Write(&blend_radius, sizeof(blend_radius));

		file.Write(&current_alpha, sizeof(current_alpha));
		file.Write(&tex_text_mode, sizeof(tex_text_mode));
		file.Write(&tex_vert_mode, sizeof(tex_vert_mode));
		file.Write(&mode_texture, sizeof(mode_texture));
		file.Write(&spline, sizeof(spline));

		if(tex_vert_mode==image_texture)
		{
			file.Write(&pheight, sizeof(pheight));
			file.Write(&pwidth, sizeof(pheight));
			int ci=pheight*pwidth;//_msize(mytext)/sizeof(col);//.size();
	//		file.Write(&ci, sizeof(int));
		
			for(int cit=0;cit<ci;cit++)
			{
				mytext[cit].savefile(file);
			}
		}
		int i=texture_file.GetLength();
		if(tex_vert_mode==image_texture)
		{
		file.Write(&i,sizeof(i));
		for(int j=0;j<i;j++)
		{
		char c=texture_file[j];
		file.Write(&c,sizeof(c));
		}
		}
//		file.Write(&handle, sizeof(handle));
		i=handle.length();
		file.Write(&i,sizeof(i));
		for(int j=0;j<i;j++)
		{
		char c=handle[j];
		file.Write(&c,sizeof(c));
		}

		int bi=ptbegin.size();
		int ei=ptend.size();
		file.Write(&bi, sizeof(bi));
		file.Write(&ei, sizeof(bi));
		CString sg;
		sg.Format(_T("%d"),bi);
//		AfxMessageBox(sg+" begin points");
		sg.Format(_T("%d"),ei);
//		AfxMessageBox(sg+" end points");
//end andycad update


		vector<CVector>::iterator it;
		for(it=ptbegin.begin();it!=ptbegin.end();it++)
		{
			it->savefile(file);
		}
		for(it=ptend.begin();it!=ptend.end();it++)
		{
			it->savefile(file);
		}
		i=layer.name.GetLength();
		file.Write(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c=layer.name[j];
		file.Write(&c,sizeof(c));
		}
		file.Write(&layer.handle,sizeof(int));
		file.Write(&layer.on,sizeof(bool));
		file.Write(&layer.clear,sizeof(bool));


		i=myinfo.name.GetLength();
		file.Write(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c=myinfo.name[j];
		file.Write(&c,sizeof(c));
		}

		i=myinfo.author.GetLength();
		file.Write(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c=myinfo.author[j];
		file.Write(&c,sizeof(c));
		}

		i=myinfo.description.GetLength();
		file.Write(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c=myinfo.description[j];
		file.Write(&c,sizeof(c));
		}

		file.Write(&myinfo.cost,sizeof(double));
		mesh.savefile(file);

}
void CFigure::savefile(CDC *hdc,CFile& file)
{

}

void CFigure::openfile(CDC *hdc,CFile& file)
{

}


void CFigure::openfile(CFile& file)
{
	init();
		file.Read(&libst,sizeof(libst));
		file.Read(&OpClstate,sizeof(OpClstate));
		file.Read(&brk,sizeof(brk));
		file.Read(&cl,sizeof(cl));

		file.Read(&bcolor,sizeof(bcolor));
		file.Read(&lplb,sizeof(lplb));
		file.Read(&dwStyleCount, sizeof(dwStyleCount));
//		file.Read(&lpStyle, sizeof(lpStyle));
		file.Read(&lstyle,sizeof(lstyle));
		file.Read(&lwidth,sizeof(lwidth));

		//andycad update begin

		file.Read(&alpha, sizeof(alpha));
		file.Read(&angle, sizeof(angle));
//		file.Read(&blend_p, sizeof(blend_p));
//		file.Read(&blend_mode, sizeof(blend_mode));
//		file.Read(&blend_plane, sizeof(blend_plane));
//		file.Read(&blend_radius, sizeof(blend_radius));

		file.Read(&current_alpha, sizeof(current_alpha));
		file.Read(&tex_text_mode, sizeof(tex_text_mode));
		file.Read(&tex_vert_mode, sizeof(tex_vert_mode));
		file.Read(&mode_texture, sizeof(mode_texture));
		file.Read(&spline, sizeof(spline));

//		file.Read(&ci, sizeof(int));
		if(tex_vert_mode==image_texture)
		{
			file.Read(&pheight, sizeof(int));
			file.Read(&pwidth, sizeof(int));

			int ci=pwidth*pheight;
			mytext=new col[ci];	
			for(int i0=0;i0<ci;i0++)
			{
				mytext[i0].openfile(file);
			}
		}
		
		int text;
//		file.Read(&text, sizeof(texture_file));
		if(tex_vert_mode==image_texture)
		{
		texture_file="";
		int i;//=texture_file.GetLength();
		i=0;
		file.Read(&i,sizeof(i));
		for(int j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		texture_file.Insert(j,c);
		}

		}
//		int _handle;
//		file.Read(&_handle, sizeof(_handle));
		int i=0;
		file.Read(&i,sizeof(i));
		handle.resize(i);
		CString sg1;
		sg1.Format(_T("%d"),i);
//		AfxMessageBox(sg1+" handle characters");
		for(int j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		handle[j]=c;
		}
		sg1=handle.c_str();
//		AfxMessageBox(sg1+" is the handle");
//		CString sp;
//		sp.Format(_T("%i"),_handle);
//		handle=sp;
//end andycad update

		int bi=0;
		int ei=0;
		file.Read(&bi, sizeof(bi));
		file.Read(&ei, sizeof(bi));
		CString sg;
		sg.Format(_T("%d"),bi);
//		AfxMessageBox(sg+" begin points");
		sg.Format(_T("%d"),ei);
//		AfxMessageBox(sg+" end points");

		ptbegin.clear();
		for( i=0;i<bi;i++)
		{
			CVector v;
			v.openfile(file);
			ptbegin.push_back(v);
		}
		ptend.clear();
		for(i=0;i<ei;i++)
		{
			CVector v;
			v.openfile(file);
			ptend.push_back(v);
		}
	//	i=layer.name.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		layer.name.Insert(j,c);
		}
		file.Read(&layer.handle,sizeof(int));
		file.Read(&layer.on,sizeof(bool));
		file.Read(&layer.clear,sizeof(bool));


	//	i=myinfo.name.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;//=myinfo.name[j];
		file.Read(&c,sizeof(c));
		myinfo.name.Insert(j,c);
		}

	//	i=myinfo.author.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		myinfo.author.Insert(j,c);
		}

	//	i=myinfo.description.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		myinfo.description.Insert(j,c);
		}

		file.Read(&myinfo.cost,sizeof(double));
		mesh.openfile(file);

}

LONG CFigure::Readfile(CFile& file)
{
		init();
		file.Seek(sizeof(libst),CFile::current);
		file.Seek(sizeof(OpClstate),CFile::current);
		file.Seek(sizeof(brk),CFile::current);
		file.Seek(sizeof(cl),CFile::current);

		file.Seek(sizeof(bcolor),CFile::current);
		file.Seek(sizeof(lplb),CFile::current);
		file.Seek(sizeof(dwStyleCount),CFile::current);
		file.Seek(sizeof(lpStyle),CFile::current);
		file.Seek(sizeof(lstyle),CFile::current);
		file.Seek(sizeof(lwidth),CFile::current);

		//andycad update begin

		file.Seek(sizeof(alpha),CFile::current);
		file.Seek(sizeof(angle),CFile::current);
		file.Seek(sizeof(blend_p),CFile::current);
		file.Seek(sizeof(blend_mode),CFile::current);
		file.Seek(sizeof(blend_plane),CFile::current);
		file.Seek(sizeof(blend_radius),CFile::current);

		file.Seek(sizeof(current_alpha),CFile::current);
		file.Seek(sizeof(tex_text_mode),CFile::current);
		file.Seek(sizeof(tex_vert_mode),CFile::current);
		file.Read(&mode_texture, sizeof(mode_texture));
		file.Seek(sizeof(spline),CFile::current);

		file.Seek(sizeof(int),CFile::current);
		file.Seek(sizeof(int),CFile::current);

		int ci;
		file.Read(&ci, sizeof(int));
	
		for(int i0=0;i0<ci;i0++)
		{
			col c;
			c.Readfile(file);
		}

		
		
		if(mode_texture!=none)
		{
		texture_file="";
		int i;//=texture_file.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(int j=0;j<i;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		texture_file.Insert(j,c);
		}

		}
		file.Seek(sizeof(handle),CFile::current);
//end andycad update

		int bi=0;
		int ei=0;
		file.Read(&bi, sizeof(int));
		file.Read(&ei, sizeof(int));

		ptbegin.clear();
		for(int i=0;i<bi;i++)
		{
			CVector v;
			v.Readfile(file);
		}
		ptend.clear();
		for(i=0;i<ei;i++)
		{
			CVector v;
			v.Readfile(file);
		}
//		i=layer.name.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(int j=0;j<i;j++)
		{
		char c;
		file.Seek(sizeof(c),CFile::current);
		}
		file.Seek(sizeof(int),CFile::current);
		file.Seek(sizeof(bool),CFile::current);
		file.Seek(sizeof(bool),CFile::current);


//		i=myinfo.name.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;//=myinfo.name[j];
		file.Seek(sizeof(c),CFile::current);
		}

//		i=myinfo.author.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;
		file.Seek(sizeof(c),CFile::current);
		}

	//	i=myinfo.description.GetLength();
		i=0;
		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c;
		file.Seek(sizeof(c),CFile::current);
		}

		file.Seek(sizeof(double),CFile::current);
		return mesh.Readfile(file);

}

bool CFigure::Rectangleselect(CVector point)
{
	if((!multiselect)&&(!libst))
		updatecore();
	else
		setcore();
	if(core.size()==0) return false;
	if(ptbegin.size()==2)
	{
		CVector be=ptbegin[0];
		CVector ee=ptbegin[1];
		if ((((be==core[11])||(ee==core[11]))&&(pointinRegion(core[11],point)))||
			(((be==core[9])||(ee==core[9]))&&(pointinRegion(core[9],point)))||
			(pointinRegion(core[9],point))||(pointinRegion(core[11],point)))
		{
			recselectpoint=vsca;
			recselect=true;
			return recselect;
		}else
		if ((((be==core[10])||(ee==core[10]))&&(pointinRegion(core[10],point)))||
			(((be==core[12])||(ee==core[12]))&&(pointinRegion(core[12],point)))||
			(pointinRegion(core[10],point))||(pointinRegion(core[12],point)))
		{
			recselectpoint=hsca;
			recselect=true;
			return recselect;
		}
		else
		{
			select=full;
		}
	}
		if ((pointinRegion(box.corner(0),point))||(pointinRegion(box.corner(1),point))||(pointinRegion(box.corner(2),point))\
			||(pointinRegion(box.corner(3),point))||(pointinRegion(box.corner(4),point))||(pointinRegion(box.corner(5),point))\
			||(pointinRegion(box.corner(6),point))||(pointinRegion(box.corner(7),point)))
		{
			recselectpoint=fsca;
			recselect=true;
			return recselect;

		}else
		if ((pointinRegion(core[14],point))||(pointinRegion(core[9],point))||(pointinRegion(core[11],point)))
		{
			recselectpoint=vsca;
			recselect=true;
			return recselect;

		}else
		if ((pointinRegion(core[10],point))||(pointinRegion(core[12],point)))
		{
			recselectpoint=hsca;
			recselect=true;
			return recselect;

		}else
/*		if (pointinRegion(core[15],point))
		{
			recselectpoint=dsca;
			recselect=true;
			return recselect;

		}else*/
		if (pointinRegion(core[13],point))
		{
			recselectpoint=rotsca;
			recselect=true;
			return recselect;

		}else
		if (pointinRegion(rotateCenter,point))
		{
			recselectpoint=rotmsca;
			recselect=true;
			return recselect;

		}
		recselect=false;
		return false;

}

void CFigure::TransformRect(CVector prevpos, CVector postpos)
{

	CVector MouseVec(postpos,prevpos);
//	MouseVec+=pc;

			CVector vc(core[8],v0);//vc.viewi();
			CVector va(core[0],core[1]);//va.viewi();
			CTVector vt;
			vt.pushTransform();
			vt.pushUnit();
			vt.Translate(vc);
			vt.TRotate(argu(va));
			vc.assign(v0,core[8]);//vc.viewi();
			vt.endT();

			va.assign(pc);
			prevpos.assign(prevpos);
			postpos.assign(postpos);
			int b=(absc(prevpos)>absc(postpos))?-1:1;

			MouseVec.assign(MouseVec);
			CVector vg;
			vg.assign(core[0]);
			vt.pushUnit();
			va.assign(pc);
			vc.assign(core[8],v0);//vc.viewi();
			va.assign(core[0],core[1]);//va.viewi();
			vt.Translate(vc);
			vt.TRotate(argu(va));
			if((vg.y!=0)&&(vg.x!=0))
			{
			double d;
			d=1+(b*sqrt(pow(MouseVec.x,2)+pow(MouseVec.y,2)+pow(MouseVec.z,2)))/sqrt(pow(vg.x,2)+pow(vg.y,2)+pow(vg.z,2));
			if(recselectpoint==fsca)
			{

			vt.Scale(d,d,d);
			}
			else
			if(recselectpoint==vsca)
			{
			vt.Scale(1,d,1);
			}
			else
			if(recselectpoint==hsca)
			{
			vt.Scale(d,1,1);
			}
			else
			if(recselectpoint==dsca)
			{
			vt.Scale(1,1,d);
			}

			}
			vc.assign(v0,core[8]);//vc.viewi();
			vt.Translate(vc);
			vt.endT();

			UpdateMesh();
			postTranslate(vc);
			vt.popTransform();

}
		


CFigure * CFigure::mirror(CDC* hdc, CFigure *line)
{
	vector<CVector>* presult[2];
 	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	
	line->updatecore();

	ptsBegin=selectvec[0];
	ptsEnd=selectvec[2];

	CRay VMainb(ptsBegin,ptsEnd);
 	CVector p=VMainb.getclosestPoint(line->getCenter());
	CVector n=line->getCenter()-p;
	n=n/absc(n);
	CVector V(ptsBegin,ptsEnd);
	V.dot(n);
	
	CFigure* f;
	f=line->generateCopy();

	CTVector v;
	v.pushTransform();
	v.pushUnit();
	v.Translate(-p);
	v.Reflect(n);
	v.Translate(p);
	v.endT();
	selectvec.clear();
	f->UpdateMesh();
	v.popTransform();
	f->updatecore();

	return f; 

}




bool CFigure::rotateSM(CDC* hdc,int sens, CVector prevpoint, CVector postpoint,bool b)
{
	bool change=false;
	CheckinRG(prevpoint);
	switch(rotstate)
	{
	case R0:
		{
			if (rotclick)
			{
				rotstate=R1;
				moveRotCenter(hdc,prevpoint,postpoint);
			}
			break;
		}
	case R1:
		{
			if ((rotclick)&&(inReg))
			{
				moveRotCenter(hdc,prevpoint,postpoint);
			}
			else if (!rotclick)
			{
			rotstate=R2;
			}
			break;
		}
	case R2:
		{
			if (rotclick &&(inReg))
			{
				rotstate=R1;
				moveRotCenter(hdc,prevpoint,postpoint);
			}
			else if(rotclick&&(!inReg))
			{
				rotstate=R4;
				change=true;
			}
			break;
		}
	case R4:
	{
		if((rotclick)&&(!inReg))
		{
			change=true;
			rotstate=R3;
		}
		else if (!rotclick)
		{
			rotstate=R2;
		}
		break;
	}
	case R3:
	{
		if((rotclick)&&(!inReg))
		{
			if(!b) 
				CFigure::Rotate(sens,prevpoint,postpoint);
			else
				Scale(sens,prevpoint,postpoint);
			drawTrans(hdc);
			change=true;
		}
		else if (!rotclick)
		{
			rotstate=R2;
		}
		break;
	}
	}
	return change;

}

CVector CFigure::getRotateCenter()
{
	return rotateCenter;
}

void CFigure::setRotClick(bool value)
{
	rotclick=value;

}

void CFigure::moveRotCenter(CDC *hdc, CVector prevpoint, CVector postpoint)
{
	CVector v(0,0);
	CVector vo(prevrotateCenter);
	vo.v2D();
	CVector ro(prevpoint);//rotateCenter);
	ro.v2D();

	if (prevrotateCenter==v)
	{
	updatecore();
	rotateCenter=box.center();
	prevrotateCenter=rotateCenter;
	core[14]=core[13];
/*	CPoint r(rotateCenter);
	hdc->MoveTo(r.x,r.y-25);
	hdc->LineTo(r.x,r.y+25);
	hdc->MoveTo(r.x-25,r.y);
	hdc->LineTo(r.x+25,r.y);
*/

		CPoint pt0(rotateCenter);
		hdc->MoveTo(pt0);
//		hdc->TextOut(pt0.x,pt0.y,"Ol");
		CPoint pt1(core[13]);
		CPen pen3;
		pen3.CreatePen(PS_GEOMETRIC,5,RGB(42,112,219));
		CPen* oldp=hdc->SelectObject(&pen3);
		hdc->Ellipse(CRect(CPoint(pt0.x-13, pt0.y+13),CPoint(pt0.x+13, pt0.y-13)));

		hdc->SelectObject(oldp);
		CPen pen0;
		CBrush brush0;
		LOGBRUSH lb;
		lb.lbStyle=BS_HOLLOW;
		brush0.CreateBrushIndirect(&lb);
		CBrush *oldb=hdc->SelectObject(&brush0);
		pen0.CreatePen(PS_COSMETIC,4,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen0);
		hdc->Ellipse(CRect(CPoint(pt1.x-17, pt1.y+17),CPoint(pt1.x+17, pt1.y-17)));

		hdc->SelectObject(oldp);
		CPen pen2;
		pen2.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen2);
		
		hdc->LineTo(pt1);

	}
	else
//	if (absc(CVector(ro,vo))<25)//((rotateCenter-25).operator <(prevpoint))&&(prevpoint.operator <(rotateCenter+25)))
	{
	prevrotateCenter=rotateCenter;
	rotateCenter=postpoint;

	int old=hdc->SetROP2(R2_NOTXORPEN);
	CPoint pr(prevrotateCenter);
	CPoint r(rotateCenter);

	{
		CPoint pt0=pr;//(rotateCenter);
		hdc->MoveTo(pt0);
//		hdc->TextOut(pt0.x,pt0.y,"Ol");
		CPoint pt1(core[14]);
		CPen pen3;
		pen3.CreatePen(PS_GEOMETRIC,5,RGB(42,112,219));
		CPen* oldp=hdc->SelectObject(&pen3);
		hdc->Ellipse(CRect(CPoint(pt0.x-13, pt0.y+13),CPoint(pt0.x+13, pt0.y-13)));

		hdc->SelectObject(oldp);
		CPen pen0;
		CBrush brush0;
		LOGBRUSH lb;
		lb.lbStyle=BS_HOLLOW;
		brush0.CreateBrushIndirect(&lb);
		CBrush* oldb=hdc->SelectObject(&brush0);
		pen0.CreatePen(PS_COSMETIC,4,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen0);
		hdc->Ellipse(CRect(CPoint(pt1.x-17, pt1.y+17),CPoint(pt1.x+17, pt1.y-17)));

		hdc->SelectObject(oldp);
		CPen pen2;
		pen2.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen2);
		
		hdc->LineTo(pt1);
	}
	{
		CPoint pt0=r;//(rotateCenter);
		hdc->MoveTo(pt0);
//		hdc->TextOut(pt0.x,pt0.y,"Ol");
		CPoint pt1(core[13]);
		CPen pen3;
		pen3.CreatePen(PS_GEOMETRIC,5,RGB(42,112,219));
		CPen* oldp=hdc->SelectObject(&pen3);
		hdc->Ellipse(CRect(CPoint(pt0.x-13, pt0.y+13),CPoint(pt0.x+13, pt0.y-13)));

		hdc->SelectObject(oldp);
		CPen pen0;
		CBrush brush0;
		LOGBRUSH lb;
		lb.lbStyle=BS_HOLLOW;
		brush0.CreateBrushIndirect(&lb);
		CBrush* oldb=hdc->SelectObject(&brush0);
		pen0.CreatePen(PS_COSMETIC,4,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen0);
		hdc->Ellipse(CRect(CPoint(pt1.x-17, pt1.y+17),CPoint(pt1.x+17, pt1.y-17)));

		hdc->SelectObject(oldp);
		CPen pen2;
		pen2.CreatePen(PS_COSMETIC,3,RGB(42,112,219));
		oldp=hdc->SelectObject(&pen2);
		
		hdc->LineTo(pt1);
	}	
	/*	hdc->MoveTo(pr.x,pr.y-25);
	hdc->LineTo(pr.x,pr.y+25);
	hdc->MoveTo(pr.x-25,pr.y);
	hdc->LineTo(pr.x+25,pr.y);

	hdc->MoveTo(r.x,r.y-25);
	hdc->LineTo(r.x,r.y+25);
	hdc->MoveTo(r.x-25,r.y);
	hdc->LineTo(r.x+25,r.y);
*/
	hdc->SetROP2(old);

	}


}



void CFigure::CheckinRG(CVector point)
{
	CVector ro(rotateCenter);
	ro.v2D();
	CVector p(point);
	p.v2D();

	if (absc(CVector(ro,p))<10)//((rotateCenter-10).operator <(point))&&(point.operator <(rotateCenter+10)))
	{
		inReg=true;

	}
	else inReg=false;
	
}

void CFigure::drawdel(CDC *hdc)
{
	int old=hdc->SetROP2(R2_NOTXORPEN);    			
	ptbegin=mesh.getVectors();
	pitere=ptbegin.begin()+1;
	
	for (piterb=ptbegin.begin();piterb<ptbegin.end()-1;piterb++)
	{

		ptsBegin=*piterb;
		ptsEnd=*pitere;
	
	hdc->MoveTo(ptsBegin.x, ptsBegin.y); 
	hdc->Rectangle(ptsBegin.x-2, ptsBegin.y+2,ptsBegin.x+2, ptsBegin.y-2);
	hdc->MoveTo(ptsEnd.x, ptsEnd.y); 
	hdc->Rectangle(ptsEnd.x-2, ptsEnd.y+2,ptsEnd.x+2, ptsEnd.y-2);

	/*if (Isrotate)
	{
	hdc->MoveTo(rotateCenter.x,rotateCenter.y-5);
	hdc->LineTo(rotateCenter.x,rotateCenter.y+5);
	hdc->MoveTo(rotateCenter.x-5,rotateCenter.y);
	hdc->LineTo(rotateCenter.x+5,rotateCenter.y);
	}*/

	drawinit(hdc,ptsBegin,ptsEnd);
	
	pitere=pitere+1;
	}

	updatecore();	
		vector<CVector>::iterator bonbon;

		if(!core.empty())
		{
	
		for (bonbon=core.begin();bonbon<core.end();bonbon++)
		{
		hdc->MoveTo(*bonbon); 
		hdc->Rectangle(bonbon->x-3, bonbon->y+3,bonbon->x+3, bonbon->y-3);
		}

		}
	hdc->SetROP2(old);    			

}

CVector CFigure::getCenter()
{
	updatecore();
	return pc;

}
bool CFigure::getCharge(CDC* hdc)
{
	return false;
}

vector<CFigure*> CFigure::translatepArray(bool of,int nbrow,int nbcol, double distx,double disty,int level,double distl)
{
	vector<CFigure*> bulk;
	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);//vro.getcooro();

	for(int l=0;l<level;l++)
	{
	for(int u=0;u<nbrow;u++)
	{
		for(int v=0;v<nbcol;v++)
		{
			if((!((u==0)&&(v==0)))||(l!=0))
			{
			CFigure* f;
			f=generateCopy();
			f->multiselect=false;
			CTVector vt;
			vt.pushTransform();
			vt.pushUnit();
			vt.Translate(vrx*distx*v+vry*disty*u+vrz*distl*l);
			vt.endT();
			f->UpdateMesh();
			f->updatecore();
			vt.popTransform();
			bulk.push_back(f);
			}
		}

	}
	}
	return bulk;
}


CFigure* CFigure::translatep(CVector prevpos, CVector postpos)
{

	CFigure* l=generateCopy();
	CVector v=postpos-prevpos;
	l->Translate(v);
	l->updatecore();
	return l;
}


vector<CFigure>* CFigure::RotateCopyP(CDC *hdc,CVector point,vector<CFigure>* pbulk, bool align)
{

	vector<CFigure> bulk;
//	bulk.clear();
	ptbegin=mesh.getVectors();
	pitere=ptbegin.begin()+1;

	CVector ptb,pte;	
	prevptend=ptend;
	prevptbegin=ptbegin;
	//if(!multiselect) updatecore();
	CVector bg=*ptbegin.begin();
	CVector eg=*ptend.begin();
	CVector piv=(core[0]+core[4])/2;
	bg-=rotateCenter;
	eg-=rotateCenter;
	piv-=rotateCenter;
	point-=rotateCenter;

	double alphab;
	double pi=3.14159265358979;
	double diff=(argu(piv)<argu(point))?2*pi-(argu(piv)-argu(point)):2*pi+(argu(piv)-argu(point));
	for(alphab=argu(point)-argu(piv);abs(alphab)<diff;alphab +=argu(point)-argu(piv))
	{

		CFigure result;
		vector<CVector> resultb, resulte;
//		pitere=ptend.begin();
		for (piterb=ptbegin.begin();piterb<ptbegin.end()-1;piterb++)
		{
		ptb=*piterb;
		pte=*pitere;
		
//		rotateCenter= pte;

		CVector vb,ve;
		vb=ptb;
		vb-=rotateCenter;
		ve=pte;
		ve-=rotateCenter;
		
		CVector vbprime=vb;
		CVector veprime=ve;
		
		if(!align)
		{		
		vbprime=polarc(absc(vb),argu(vb)+alphab);
		veprime=polarc(absc(ve),argu(ve)+alphab);
		}
		else
		{
			CVector rotateCenter2=piv;
			vbprime-=rotateCenter2;
			veprime-=rotateCenter2;
			rotateCenter2=polarc(absc(rotateCenter2),argu(rotateCenter2)+alphab);
			vbprime+=rotateCenter2;
			veprime+=rotateCenter2;
		}


		vbprime+=rotateCenter;
		veprime+=rotateCenter;
		

		ptb.x=vbprime.x;
		ptb.y=vbprime.y;
		pte.x=veprime.x;
		pte.y=veprime.y;
	
		resultb.push_back(ptb);
		resulte.push_back(pte);


	if ((pitere+1)<ptbegin.end())
		{
		pitere=pitere+1;
		}
	}
			result.createobj(resultb,resulte);
			result.updatecore();
			bulk.push_back(result);
	}

	*pbulk=bulk;

		return pbulk;

}

vector<CFigure*> CFigure::RotateCopyP(CDC *hdc,double ang,int nnb,int nblevel,int dlevel, bool align)
{

	vector<CFigure*> bulk;

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);//vro.getcooro();

	double alphab;
	double diff=nnb*ang;
	int hhj=0;
	CVector piv=box.center();//(core[0]+core[4])/2;
	piv-=rotateCenter;
	for(int l=0;l<nblevel;l++)
	{

	for(alphab=ang;alphab<=diff;alphab +=ang)
	{

	CFigure* f;
	f=generateCopy();
	f->multiselect=false;

		CFigure result;
		vector<CVector> resultb, resulte;
			CVector v00,v01;

	v00.assign(rotateCenter,v0);

	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(-rotateCenter);
	vt.Translate(vrz*dlevel*l);

	if(align)
	{
	vt.Translate(-piv);
	if(v00.getplanesnap()==CVector::left)
	{
	vt.TRotatex(-alphab);
	}else
	if(v00.getplanesnap()==CVector::top)
	{
	vt.TRotatey(-alphab);
	}
	else
	{
	vt.TRotate(-alphab);
	}
	vt.Translate(piv);
	}
	
	
	if(v00.getplanesnap()==CVector::left)
	{
	vt.TRotatex(alphab);
	}else
	if(v00.getplanesnap()==CVector::top)
	{
	vt.TRotatey(alphab);
	}
	else
	{
	vt.TRotate(alphab);
	}
	
//	v01.assign(v0,rotateCenter);
	vt.Translate(rotateCenter);
	vt.endT();
	f->UpdateMesh();
	vt.popTransform();
	f->updatecore();
	bulk.push_back(f);
	}
	}

	return bulk;

}




CFigure* CFigure::copybyC(CDC *hdc, CVector center)
{
	float u=Min_dist_toEdge(center);
	CFigure* f;
	f=generateCopy();
	f->multiselect=false;
	OffsetMesh(u,f);
	f->updatecore();
	return f;
/*
	vector<CVector> resultb,rresultb, resulte,rresulte;

//	if((!multiselect)||(!libst)) updatecore();
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();
   	CVector radx(core[8],(core[3]+core[2])/2);//p12);
	CVector	rady(core[8],(core[3]+core[4])/2);//p23);
	CVector extp(core[8],center);
	double dist1=pointtoVector(radx,extp)/pointtoVector(radx,rady);
	double dist2=pointtoVector(rady,extp)/pointtoVector(rady,radx);
	double dist=max(dist1,dist2);
	CVector v00=v0;
	CVector v01=v0;


	v00.assign(core[8]);//CVector(0,0,0,1));
	v00=core[8];
	v00.worldi();

	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(-core[8]);
	vt.Scale(dist,dist,dist);
	vt.Translate(core[8]);
	vt.endT();
	f->UpdateMesh();

	vt.popTransform();

	return f;*/
}


CVector CFigure::getstartPoint()
{
//	return *ptbegin.begin();
	return *(CVector*)mesh.Vertex(0);

}

CFigure* CFigure::alignbyL(CDC *hdc, CVector line, CVector projectline, CVector center)
{
/*	vector<CVector> resultb, resulte;
	updatecore();


	CVector pcc(center,pc);
		CVector line1(pcc,p12);
		CVector line2(pcc,p23);
		CVector centerc(pcc,center);
		CVector p23c(pcc,p23);
		CVector p12c(pcc,p12);
		CVector p1c(pcc,p1);
		CVector p2c(pcc,p2);
		CVector p3c(pcc,p3);
		CVector p0c(pcc,p0);


		double dist1=pointtoVector(line1,centerc)-pointtoVector(line1,p23c);
		double dist2=pointtoVector(line2,centerc)-pointtoVector(line2,p12c);
		double dist=max(dist1,dist2);
		
		CVector transy(0,dist);
		CVector transx(dist,0);
		CVector trans(dist,dist);


//		p0c=p0c-transx+transy;p1c+=trans;
//		p2c=p2c+transx-transy;p3c-=trans;

		CVector ptb,pte,test;
		for(piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
		{
			ptb=*piterb;
			ptb-=pcc;
			if((p0c<=ptb)&&(ptb<v0))
			{
				ptb=ptb-transx;
				ptb-=transy;
//				ptb=(ptb-transx)+transy;
			}
			else if((v0.x<ptb.x)&&(v0.y>ptb.y)&&(ptb<=p1c))
			{
				ptb+=transx;
				ptb-=transy;
			}
			else if((v0<ptb)&&(ptb<=p2c))
			{
				ptb=ptb+transx;//-transy;
				ptb+=transy;

			}
			else if((p3c<=ptb)&&(v0.x>ptb.x)&&(v0.y<ptb.y))
			{
				ptb-=transx;
				ptb+=transy;
			}
			ptb+=pcc;
			ptb+=pc;
			resultb.push_back(ptb);
		}
		for(pitere=ptend.begin();pitere<ptend.end();pitere++)
		{
			pte=*pitere;
			pte-=pcc;
			if((p0c<=pte)&&(pte<v0))
			{
				pte-=transx;
				pte-=transy;				
				//pte=(pte-transx)+transy;
			}
			else if((v0.x<pte.x)&&(v0.y>pte.y)&&(pte<=p1c))
			{
				pte+=transx;
				pte-=transy;
			}
			else if((v0<pte)&&(pte<=p2c))
			{
				pte+=transx;//-transy;
				pte+=transy;
			}
			else if((p3c<=pte)&&(v0.x>pte.x)&&(v0.y<pte.y))
			{
				pte-=transx;
				pte+=transy;
			}
			pte+=pcc;
			pte+=pc;
			resulte.push_back(pte);
		}

			pbulk->createobj(resultb,resulte);
*/
	CFigure *pbulk;
		return pbulk;


}

void CFigure::create(CVector pos)
{

}

CString CFigure::getName()
{
	return name;

}

CVector CFigure::CopybyLine(CFigure *figure)
{
	CVector v;
	return v;

}

void CFigure::setLcolor(CDC *hdc,COLORREF color,COLORREF bkcolor)
{
	lplb.lbColor=color;
	lcolor=color;
	bcolor=bkcolor;
	texture_file="";
	mode_texture=none;
	tex_vert_mode=backcolor;
	cl=true;
	UpdateTexture(hdc);
}



void CFigure::setHandle(string& hn)
{
	handle=hn;
}

string CFigure::gethandle()
{
	return handle;
}

//DEL void CFigure::setUndoparam()
//DEL {
//DEL  
//DEL  ptbegin1.resize(ptbegin.size());
//DEL  std::copy(ptbegin.begin(),ptbegin.end(),ptbegin1.begin());
//DEL  ptend1.resize(ptend.size());
//DEL  std::copy(ptend.begin(),ptend.end(),ptend1.begin());
//DEL 
//DEL  undovecb.push_back(ptbegin1);
//DEL  undovece.push_back(ptend1);
//DEL  undolayer.push_back(layer);
//DEL }

//DEL void CFigure::updateUndoparam()
//DEL {
//DEL  ptbegin1.resize(ptbegin.size());
//DEL  std::copy(ptbegin.begin(),ptbegin.end(),ptbegin1.begin());
//DEL  ptend1.resize(ptend.size());
//DEL  std::copy(ptend.begin(),ptend.end(),ptend1.begin());
//DEL 
//DEL  undovecb.back()=ptbegin1;
//DEL  undovece.back()=ptend1;
//DEL  undolayer.back()=layer;
//DEL }


//DEL bool CFigure::Undo()
//DEL {
//DEL 	bool a=false;
//DEL 	if(undovecb.size()>1)
//DEL 	{
//DEL 		a=true;
//DEL 
//DEL 	 vector<CVector> ptbegin1;
//DEL 	 ptbegin1.resize(ptbegin.size());
//DEL 	 std::copy(ptbegin.begin(),ptbegin.end(),ptbegin1.begin());
//DEL 	 vector<CVector> ptend1;
//DEL 	 ptend1.resize(ptend.size());
//DEL 	 std::copy(ptend.begin(),ptend.end(),ptend1.begin());
//DEL 
//DEL 
//DEL 	redovecb.push_back(ptbegin1);
//DEL 	redolayer.push_back(layer);
//DEL 
//DEL 	vector<CVector> ptbegin2;
//DEL 	ptbegin2=*(undovecb.end()-2);
//DEL     std::copy(ptbegin2.begin(),ptbegin2.end(),ptbegin.begin());
//DEL 	
//DEL 	layer=*(undolayer.end()-1);
//DEL 	undovecb.pop_back();
//DEL 	undolayer.pop_back();
//DEL 	
//DEL 	redovece.push_back(ptend1);
//DEL 
//DEL 	vector<CVector> ptend2;
//DEL 	ptend2=*(undovece.end()-2);
//DEL     std::copy(ptend2.begin(),ptend2.end(),ptend.begin());
//DEL 
//DEL 	undovece.pop_back();
//DEL 	}
//DEL 	return a;
//DEL }

//DEL bool CFigure::Redo()
//DEL {
//DEL 	bool a=false;
//DEL 	if(redovecb.size()>0)
//DEL 	{
//DEL 	a=true;
//DEL 
//DEL 	vector<CVector> ptbegin2;
//DEL 	ptbegin2=*(redovecb.end()-1);
//DEL     std::copy(ptbegin2.begin(),ptbegin2.end(),ptbegin.begin());
//DEL 
//DEL 	layer=*(redolayer.end()-1);
//DEL 	redolayer.pop_back();
//DEL 	redovecb.pop_back();
//DEL 	
//DEL 	undovecb.push_back(ptbegin2);
//DEL 
//DEL 	vector<CVector> ptend2;
//DEL 	ptend2=*(redovece.end()-1);
//DEL     std::copy(ptend2.begin(),ptend2.end(),ptend.begin());
//DEL 
//DEL 	redovece.pop_back();
//DEL 
//DEL 	undovece.push_back(ptend2);
//DEL 	if(ptbegin.size()!=0)
//DEL 	{
//DEL 		layer.clear=false;
//DEL 	}
//DEL 	}
//DEL 
//DEL return a;
//DEL }


//DEL int CFigure::countUnd()
//DEL {
//DEL   return undovecb.size();
//DEL }


void CFigure::clear()
{

/*	if(undovecb.size()>1)
	{
	undovecb.erase(undovecb.end()-1);
	undovece.erase(undovece.end()-1);
	}
*/
}


//DEL CRect CFigure::updateundocore(vector<CVector> ptb, vector<CVector> pte)
//DEL {
//DEL 	vector<CVector>::iterator coreitb,coreite;
//DEL 	CVector interm;
//DEL 	coreite=pte.begin();
//DEL 	int minx=coreite->x;int miny=coreite->y;int maxx=coreite->x;int maxy=coreite->y;
//DEL 	int minxi,minyi,maxxi,maxyi;
//DEL 	for (coreitb=ptb.begin();coreitb<ptb.end();coreitb++)
//DEL 	{
//DEL 		minxi=min(coreitb->x,coreite->x);
//DEL 		minx=min(minxi,minx);
//DEL 		
//DEL 		
//DEL 		minyi=min(coreitb->y,coreite->y);
//DEL 		miny=min(miny,minyi);
//DEL 		
//DEL 
//DEL 		maxxi=max(coreitb->x,coreite->x);
//DEL 		maxx=max(maxxi,maxx);
//DEL 		
//DEL 
//DEL 		maxyi=max(coreitb->y,coreite->y);
//DEL 		maxy=max(maxyi,maxy);
//DEL 		
//DEL 	coreite++;
//DEL 	}
//DEL 		CVector P0(minx,miny,1),
//DEL 			   P2(maxx,maxy);
//DEL 				
//DEL 	CRect v(P0,P2);
//DEL 	v.InflateRect(10,10);
//DEL 	return v;
//DEL 
//DEL }

//DEL void CFigure::clearundo(CWnd* win,CDC *hdc)
//DEL {
//DEL 	CRect pt=updateundocore(undovecb.back(),undovece.back());
//DEL 	hdc->LPtoDP(pt);
//DEL 	win->RedrawWindow(&pt,NULL,RDW_INVALIDATE);
//DEL 	CRect vc(p0,p2);
//DEL 	hdc->LPtoDP(vc);
//DEL 	win->RedrawWindow(&vc,NULL,RDW_INVALIDATE);
//DEL 
//DEL 
//DEL }



void CFigure::setcore(vector<CVector> co)
{
	core.clear();
	for(vector<CVector>::iterator it=co.begin();it<co.end();it++)
	{
		core.push_back(*it);
	}
	p0=core[0];
	p01=core[1];
	p1=core[2];
	p12=core[3];
	p2=core[4];
	p23=core[5];
	p3=core[6];
	p30=core[7];
	pc=core[8];


}

bool CFigure::getRotClick()
{
	return rotclick;

}

bool CFigure::getRotstate()
{
	if (rotstate!=R0) return true; else return false;
 
}

void CFigure::InitRotState()
{
	rotstate=R0;

}

void CFigure::setClstate(bool state)
{
	cl=state;

}

void CFigure::setReflineP(CVector begin, CVector end)
{
	lrefen=end;
	refline.assign(begin,end);
}
void CFigure::setModelOrigin(CVector _vo)
{
	model_v0=_vo;
}

void CFigure::setType(CString type)
{

}

vector<CVector> CFigure::getSelectvec(CVector point)
{
	inRegion(point);
	return selectvec;
}

void CFigure::setgline(bool b,bool e)
{
	glineb=b;
	glinee=e;

}

void CFigure::orient(double angle)
{

}

void CFigure::setdistprec(double b)
{
	distprec=b;
}

double CFigure::getdistprec()
{
	return distprec;

}

CPoint CFigure::drawtext(CDC *hdc, UINT nchar)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::deleteback(CDC *hdc)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::texthome(CDC *hdc)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::deletetext(CDC *hdc)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::textend(CDC *hdc)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::entertext(CDC *hdc)
{
	CPoint p(0,0);
	return p;

}

CPoint CFigure::kbmovecurs(CDC *hdc, CString& d)
{
	CPoint p(0,0);
	return p;

}

void CFigure::cursorOn(CWnd *wnd, CDC *hdc)
{

}

CVector CFigure::getRefPt()
{
	return lrefen;

}

CVector CFigure::getRefLine()
{
	return refline;
}

void CFigure::translatepoint(CDC *hdc, CVector prevpos, CVector postpos)
{
	CMouse mouse;
	CPen pen;
//	if(lstyle!=PS_USERSTYLE) *lpStyle=NULL;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);
	int i=0;

	if(getRotstate()) InitRotState();
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptsBegin=*piterb;
		ptsEnd=*pitere;

		CVector vpoint(ptsBegin,prevpos);
		CVector v(ptsBegin,ptsEnd);
	
	if ((pointinRegion(ptsBegin,prevpos))||(glineb))
	{
		multiselect=false;
		if(piterb==ptbegin.begin())
		{
		(*piterb)=absc((*pitere)-postpos)<absc((*pitere)-prevpos)?(*piterb)+polarc(absc(mouseVect),argu(v)):(*piterb)-polarc(absc(mouseVect),argu(v));
		drawTrans(hdc);
		} else
		{
		piterb=ptbegin.erase(piterb);
		piterb=ptbegin.insert(piterb,postpos);
		drawpoint(hdc,piterb);
		}
	}
	else if ((pointinRegion(ptsEnd,prevpos))||(glinee))
	{
		multiselect=false;
		if(pitere==ptend.end()-1)
		{
		(*pitere)=absc((*piterb)-postpos)>absc((*piterb)-prevpos)?(*pitere)+polarc(absc(mouseVect),argu(v)):(*pitere)-polarc(absc(mouseVect),argu(v));
		drawTrans(hdc);
		}
		else
		{
		pitere=ptend.erase(pitere);
		pitere=ptend.insert(pitere,postpos);
		drawpoint(hdc,pitere);
		}
		
		
	}else
	if ((pointtoVector(v,vpoint)<5)&&(!(pointinRegion(ptsEnd,prevpos))&&(!(pointinRegion(ptsBegin,prevpos))))||(multiselect||libst))
	{
		if ((ptsBegin.x<mouse.getPrevPos().x)&&(ptsEnd.x>mouse.getPrevPos().x)||
			(ptsBegin.x>mouse.getPrevPos().x)&&(ptsEnd.x<mouse.getPrevPos().x)||
			(ptsBegin.y<mouse.getPrevPos().y)&&(ptsEnd.y>mouse.getPrevPos().y)||
			(ptsBegin.y>mouse.getPrevPos().y)&&(ptsEnd.x<mouse.getPrevPos().y)||
			(multiselect||libst))
		{
			vector<CVector>::iterator  pite,pitb;
			pite=ptend.begin();
			for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb=pitb+1)
			{
				
				(*pitb)=argu(lrefen-postpos)<argu(lrefen-prevpos)?\
					(*pitb)+polarc(absc(mouseVect),argu(refline)):(*pitb)-polarc(absc(mouseVect),argu(refline));		
	
				(*pite)=argu(lrefen-postpos)<argu(lrefen-prevpos)?\
					(*pite)+polarc(absc(mouseVect),argu(refline)):(*pite)-polarc(absc(mouseVect),argu(refline));		

				if ((pite+1)<ptend.end())
				{
				pite=pite+1;
				}

			}
			drawTrans(hdc);
			break;
		}
	}
	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}
	}
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);


}

CPoint CFigure::setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf)
{
	CPoint p;
	return p;

}

void CFigure::setTransref(bool b)
{
	transref=b;

}

CVector CFigure::addnode(CVector point)
{
	bool isOK=false;
	vector<CVector>::iterator testb, teste;
	pitere=ptend.begin();
	mesh.addVertexonEdge(point);
	return point;
}

void CFigure::setup(bool s)
{
	Up=s;
}
void CFigure::setclick(bool s)
{
	click=s;
}

void CFigure::setlistyle(DWORD ls)
{
//	lstyle=PS_GEOMETRIC;
	lstyle=PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_ROUND;
	lstyle|=ls;
/*	if(ls==PS_DOT)
	{
	
	lstyle|=PS_USERSTYLE;	

	dwStyleCount=2;
	lpStyle=(DWORD*)realloc(lpStyle,sizeof(DWORD)*dwStyleCount);
	lpStyle[0]=3;
	lpStyle[1]=2;
	}
	else
	if(ls==PS_DASH)
	{
	lstyle|=PS_USERSTYLE;	

	dwStyleCount=2;
	lpStyle=(DWORD*)realloc(lpStyle,sizeof(DWORD)*dwStyleCount);
	lpStyle[0]=10;
	lpStyle[1]=2;
	}
	else
	if(ls==PS_DASHDOT)
	{
	dwStyleCount=4;

	lstyle|=PS_USERSTYLE;	

	lpStyle=(DWORD*)realloc(lpStyle,sizeof(DWORD)*dwStyleCount);
	lpStyle[0]=10;
	lpStyle[1]=3;
	lpStyle[2]=3;
	lpStyle[3]=3;
	}
	else
	if(ls==PS_DASHDOTDOT)
	{
	dwStyleCount=6;

	lstyle|=PS_USERSTYLE;	

	lpStyle=(DWORD*)realloc(lpStyle,sizeof(DWORD)*dwStyleCount);

	lpStyle[0]=10;
	lpStyle[1]=3;
	lpStyle[2]=3;
	lpStyle[3]=3;
	lpStyle[4]=3;
	lpStyle[5]=3;
	}
	else
	{
	dwStyleCount=0;
	lstyle=PS_SOLID|PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_ROUND;
	lpStyle=NULL;

	}*/
}

void CFigure::setliwidth(double ls)
{
	lwidth=ls;
}


//DEL bool CFigure::snapok(CVector point)
//DEL {
//DEL 	snap=false;
//DEL 		pitere=ptend.begin();
//DEL 
//DEL 	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
//DEL 	{
//DEL 	
//DEL 			CVector vpoint(*piterb,point);
//DEL 			CVector v(*piterb,*pitere);
//DEL 			CVector v2=(*piterb)+(*pitere);
//DEL 			v2=v2/2;
//DEL 			
//DEL 			double v11=absc(v2-(*piterb));
//DEL 			double v12=absc(v2-point);
//DEL     		if ((pointtoVector(v,vpoint)<=25)&&
//DEL 				(v12<=v11+20))
//DEL 				
//DEL 			{
//DEL 				hitpoint=hitpoint+(*piterb);
//DEL 				Rectangleselect(point);
//DEL 				selectvec.clear();
//DEL 
//DEL 				snapvec=hitpoint;
//DEL 				snapb=true;
//DEL 				if ((abs((piterb->x-point.x)<=20)&&(abs(piterb->y-point.y)<=20)))
//DEL 				{
//DEL 					snapvec=*piterb;
//DEL 					snapb=true;
//DEL 				}
//DEL 				if ((abs((pitere->x-point.x)<=20)&&(abs(pitere->y-point.y)<=20)))
//DEL 				{
//DEL 					snapvec=*pitere;
//DEL 					snapb=true;
//DEL 				}
//DEL 				if ((abs((pc.x-point.x)<=20)&&(abs(pc.y-point.y)<=20)))
//DEL 				{
//DEL 					snapvec=pc;
//DEL 					snapb=true;
//DEL 				}
//DEL 				snapv.clear();
//DEL 				snapv.push_back(*piterb);
//DEL 				snapv.push_back(hitpoint);
//DEL 				snapv.push_back(*pitere);
//DEL 				snap=true;
//DEL 			} else
//DEL 			{
//DEL 				snap|=false;
//DEL 				snapb=false;
//DEL 			/*	CVector v0(0,0);
//DEL 				selectvec.clear();
//DEL 				selectvec.push_back(v0);
//DEL 				selectvec.push_back(v0);
//DEL 				selectvec.push_back(v0);*/
//DEL 			}
//DEL 			if ((pitere+1)<ptend.end())
//DEL 			{
//DEL 			pitere=pitere+1;
//DEL 			} 
//DEL 		}
//DEL 	return snap;
//DEL }

void CFigure::setintersect(bool x, CVector point)
{
	intersectv=x;
	snapv.push_back(point);
	vintersect=point;
}

void CFigure::computedist()
{
	CVector v(0,0);
	myinfo.distance=0;
	ptbegin=mesh.getVectors();
	vector<CVector>::iterator eiter=ptbegin.begin()+1;
	
	for(vector<CVector>::iterator iter=ptbegin.begin();iter<ptbegin.end()-1;iter++,eiter++)
	{
		v.x=eiter->x-iter->x;
		v.y=eiter->y-iter->y;
		v.z=eiter->z-iter->z;
		myinfo.distance+=sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
	}

}

void CFigure::computeangle(CVector begin, CVector end)
{
	CVector v=end-begin;
	myinfo.angle=argu(v)-argu(refline);
}

void CFigure::computesurface()
{
	double v=0;

	ptbegin=mesh.getVectors();
	vector<CVector>::iterator eiter=ptbegin.begin()+1;

	for(vector<CVector>::iterator iter=ptbegin.begin();iter<ptbegin.end()-1;iter++,eiter++)
	{
		v+=(eiter->x-iter->x)*(eiter->y+iter->y);
	}
	myinfo.surface=v/2;
}

void CFigure::updateinfo()
{
//	myinfo.name=name;
	computedist();
	computesurface();
}

bool CFigure::takeinfo(CVector point)
{
	updateinfo();
	ptbegin=mesh.getVectors();
	pitere=ptbegin.begin()+1;

	for (piterb=ptbegin.begin();piterb<ptbegin.end()-1;piterb++,pitere++)
	{
	
			CVector vpoint(*piterb,point);
			CVector v(*piterb,*pitere);
			CVector v2=(*piterb)+(*pitere);
			v2=v2/2;
			
			double v11=absc(v2-(*piterb));
			double v12=absc(v2-point);
    		if ((pointtoVector(v,vpoint)<=25)&&
				(v12<=v11+20))
				
			{
				computeangle(*piterb,*pitere);
				return true;
			}
		}
	return false;

}

FINFO CFigure::getInfo()
{
 return myinfo;
}

void* CFigure::Trim(vector<CVector> vec)
{
	return NULL;
/*	vector<CVector> *arr= new vector<CVector>[2];
	vector<CVector> resultb, resulte;

	vector<CRay> lvec;
	vector<CVector> lpsvec,llp;
	vector<double>indexdv;

	indexdv.push_back(jpetit);
	CVector plvec(selectvec[0],selectvec[2]);
	for(vector<CVector>::iterator its=vec.begin();its<vec.end();its=its+3)
	{
		lvec.push_back(CRay(*its,*(its+2)));
	}
	
	lpsvec.push_back(selectvec[1]);
	double bp;
	vector<CVector>::iterator k=vec.begin();
	for(vector<CRay>::iterator it=lvec.begin();it<lvec.end();it++)
	{
		int gp=0;
		pitere=ptend.begin();
		for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
			{
//				CVector v=(*piterb).intersect(*pitere);
				CVector v(*piterb,*pitere);
				CRay l1(*piterb,*pitere,1);
			
				CVector nv=l1.Intersect(*it);//v.intersect((*(it)));
				CVector v2=*k+*(k+2);
				v2=v2/2;
				CVector v3=*pitere+(*piterb);
				v3=v3/2;
			
			
				double v11=absc(v2-*k);
				double v12=absc(v2-nv);
				double v13=absc(v3-nv);
				double v22=absc(v3-*piterb);
   				if(nv.x!=1E-10)
				{
						v=*piterb-(*pitere);
						bp=gp+(absc(CVector(*piterb,nv))/absc(v));
						indexdv.push_back(bp);
						lpsvec.push_back(nv);
				}
				pitere++;
				gp++;
			}
		k=k+3;
	}
	plvec=lpsvec[0];


	CVector minv=lpsvec[0];
	CVector mxmin;
	double dmin,dmax;


	for(int j=0;j<lpsvec.size();j++)
	{
			for(int i=0;i<lpsvec.size()-1;i++)
			{
				minv=lpsvec[i];dmin=indexdv[i];
				mxmin=lpsvec[i+1];dmax=indexdv[i+1];
				if(dmin>dmax)
				{
					CVector mmv=minv;
					minv=mxmin;
					mxmin=mmv;
					
					double dd=dmin;
					dmin=dmax;
					dmax=dd;

				}
				lpsvec[i]=minv;indexdv[i]=dmin;
				lpsvec[i+1]=mxmin;indexdv[i+1]=dmax;
			}
	
	}

	CVector n1,n2;
	n1.w=-1;n2.w=-1;
	for(piterb=lpsvec.begin();piterb<lpsvec.end();piterb++)
	{
		if(plvec==*piterb)
		{
			if(piterb>lpsvec.begin())
			{
				n1=*(piterb-1);
			}
			else
			{
				n1.w=-1;
			}
			if(piterb<lpsvec.end()-1)
			{
				n2=*(piterb+1);
			}
			else
			{
				n2.w=-1;
			}
		}
	}

	vector<CVector>::iterator bite1,bite2,bit,bitb1,bitb2,eit,ite=ptend.begin();

	int lp=0;
	bit=lpsvec.begin();
	for(vector<CVector>::iterator it1=ptbegin.begin();it1<ptbegin.end();it1++)
	{
		bit=lpsvec.begin();
		for(int i=0;i<indexdv.size();i++)
		{
			if((indexdv[i]<lp+1)&&(indexdv[i]>lp))
			{
				it1=ptbegin.insert(it1+1,*bit);
				ite=ptend.insert(ite,*bit); ite++;
			}
			bit++;
		}
		lp++;
		ite++;
	}
	k=ptend.begin();
	n1.ws=-1;
	n2.ws=-1;
	for(vector<CVector>::iterator i=ptbegin.begin();i<ptbegin.end();i++)
	{
		if(n1.w!=-1)
		{
			if(*i==n1)
				{
					bitb1=i;
					n1.ws=0;
				}
			if(*k==n1)
				{
					bite1=k;
					n1.ws=0;
				}
		}
		if(n2.w!=-1)
		{
			if(*i==n2)
				{
					n2.ws=0;
					bitb2=i;
				}
			if(*k==n2)
				{
					n2.ws=0;
					bite2=k;
				}
		}
		k++;
	}

	if((n1.w!=-1)&&(n1.ws==0))
	{
		for(vector<CVector>::iterator itt=ptbegin.begin();itt<bitb1;itt++)
		{
			resultb.push_back(*itt);
		}
		for(itt=ptend.begin();itt<=bite1;itt++)
		{
			resulte.push_back(*itt);
		}
	}

	vector<CVector> resultb1,resulte1;
	if((n2.w!=-1)&&(n2.ws==0))
	{
		for(vector<CVector>::iterator itt=bitb2;itt<ptbegin.end();itt++)
		{
			resultb1.push_back(*itt);
		}
		for(itt=bite2+1;itt<ptend.end();itt++)
		{
			resulte1.push_back(*itt);
		}

		ptbegin.clear();
		ptend.clear();
		for(itt=resultb1.begin();itt<resultb1.end();itt++)
		{
			ptbegin.push_back(*itt);
		}
		for(itt=resulte1.begin();itt<resulte1.end();itt++)
		{
			ptend.push_back(*itt);
		}
	}

	if(n2.w==-1)
	{
		ptbegin.clear();
		ptend.clear();
		for(vector<CVector>::iterator itt=resultb.begin();itt<resultb.end();itt++)
		{
			ptbegin.push_back(*itt);
		}
		for(itt=resulte.begin();itt<resulte.end();itt++)
		{
			ptend.push_back(*itt);
		}
		resultb.clear();
		resulte.clear();
		
	}

	if((resultb.size()!=0)&&(resulte.size()!=0)&&(plvec!=lpsvec[0]))
	{
	arr[0]=resultb;
	arr[1]=resulte;
	}
	else
	{
		arr=0;
	}

	return arr;*/
}

vector<CVector> CFigure::getSvec()
{
 return selectvec;
}
float CFigure::getSUVec()
{
	return mesh.getSUVertex();
}
vector<CVector> CFigure::getSSvec()
{
	selectvec.clear();
	ptbegin=mesh.getVectors();
	pitere=ptbegin.begin()+1;
	for (piterb=ptbegin.begin();piterb<ptbegin.end()-1;piterb++,pitere++)
		{
			selectvec.push_back(*piterb);
			selectvec.push_back(*piterb);
			selectvec.push_back(*pitere);
		}
	return selectvec;
}

void CFigure::setintvec(vector<CVector> vec)
{
	intvec.clear();
	for(vector<CVector>::iterator iter=vec.begin();iter<vec.end();iter++)
	{
	intvec.push_back(*iter);
	}
}

void CFigure::setmultcore(bool co)
{
	multcore=co;

}
int CFigure::getrecselect()
{
	return recselectpoint; 
}
void CFigure::setrecselect(int rd)
{

	switch(rd)
	{
	case 0:
		{
		recselectpoint=fsca; 
		break;
		}
	case 1:
		{
		recselectpoint=vsca; 
		break;
		}
	case 2:
		{
		recselectpoint=hsca; 
		break;
		}
	}
}

bool CFigure::getmultcore()
{
	return multcore;

}

bool CFigure::getLibstatus()
{
 return libst;
}

void CFigure::setLibstatus(bool sv)
{
 libst=sv;
}

FLAYER CFigure::getLayer()
{
	return layer;
}
void CFigure::setLayer(FLAYER& lay)
{
	layer=lay;
}

void CFigure::lclear(bool b)
{

	layer.clear=b;
}

void CFigure::updatepts()
{
	vector<CVector>::iterator it;
	for(it=ptbegin.begin();it<ptbegin.end();it++)
	{
		it->assignPL(*it);
	}
	for(it=ptend.begin();it<ptend.end();it++)
	{
		it->assignPL(*it);
	}

}

void CFigure::setcorevecor()
{
	corepoint=pc;

}

void CFigure::deleteobj()
{
	mesh.empty();
	ptbegin.clear();
	ptend.clear();
	linestate=D0;
	layer.clear=true;
	layer.on=false;
	click=false;

}

void CFigure::setselectmode(SELECT j)
{
	select=j;

	
}

SELECT CFigure::selecttoint()
{
	return select;

}

void CFigure::setLibstatusV(bool b)
{

}

void CFigure::unfill(CDC *hdc)
{
	cl=false;
}
class isfarv
{
public:
bool operator ()(CVector v1,CVector v2) const
{
	CVector v01=v1.getDepth();
	CVector v02=v2.getDepth();
	return v01.z>v02.z;
}
};
bool CFigure::fsnap(CVector &v,CVector &vl, LPCTSTR snapmode,CDC *hdc)
{
	CString snm=snapmode;
	CVector h;
	bool hb=false;
	set<CVector,isfarv> zvec;
	ptbegin=mesh.getVectors();
	pitere=ptbegin.begin()+1;

	if(snm=="endpoint")
	{
		ptbegin=mesh.getVectors();
		pitere=ptbegin.begin()+1;
		bool gut=false;
		for (piterb=ptbegin.begin();piterb!=ptbegin.end();piterb++)
		{
			ptsBegin=*piterb;
			CVector v1(v,*piterb);
			CVector _vp=v;_vp.v2D();
			CVector _vb=*piterb;_vb.v2D();
			v1=_vp-_vb;
			CVector v2=CPoint(0,20);
			v2.v3D();
    		if (absc(v1)<20)
			{
				  v=*piterb;
				  if(piterb+1!=ptbegin.end())
				  {
					  vl=*piterb-*(piterb+1);
				  }
				  else
				  {
					  vl=*(piterb-1)-*(piterb);
				  }

				  return true;
			}
		}
	}else
	if(snm=="midpoint")
	{

		ptbegin=mesh.getVectors();
		pitere=ptbegin.begin()+1;
		bool gut=false;
		for (piterb=ptbegin.begin();piterb!=ptbegin.end();piterb++,pitere++)
		{
		  h=(*piterb+*pitere)/2;

		  CVector vh(h,v);
			CVector _vp=v;_vp.v2D();
			CVector _vb=h;_vb.v2D();
			vh=_vp-_vb;
          if (absc(vh)<20)
		  {
			  v=h;
			  if(piterb+1!=ptbegin.end())
				  vl=*piterb-*(piterb+1);
			  else
				  vl=*(piterb-1)-*(piterb);

			  return true;
		  }
		}
	}else
	if(snm=="center")
	{
		  CVector vh(core[8],v);
			CVector _vp=v;_vp.v2D();
			CVector _vb=core[8];_vb.v2D();
			vh=_vp-_vb;
          if (absc(vh)<20)
		  {
			  v=core[8];

			  return true;
		  }
	}else
	if(snm=="nearest")
	{
	float f;
	CVector uv;
	CVector rv;
	if(mesh.PtonEdge(v,rv,f,uv))
	{
		CVector v1=mesh.Vector(uv.x);
		CVector v2=mesh.Vector(uv.y);
		v=rv;
		vl=v2-v1;
		return true;
	}

/*	for (piterb=ptbegin.begin();piterb!=ptbegin.end();piterb++,pitere++)
		{

		    CVector nb=*piterb;//NURBS(deg,ContP,ncp,Para[iter0],Kn);
		    CVector nbplus=*pitere;//NURBS(deg,ContP,ncp,Para[iter0+1],Kn);//vMr[iter0+1];
			CVector vpoint(nb,v);
			CVector v9(nb,nbplus);
			CVector v2=nb+v9/2;
//			v2=v2/2;

			double v11=absc(v2-nb);
			double v12=absc(v2-v);
			double vp0=pointtoVector(v9,vpoint);
			double r=absc(vpoint);

			  if ((vp0<10)&&(v12<v11))
			  {
				CVector d1=*pitere-*piterb;
				CVector pt=v-*piterb;
				CVector pd=*piterb+d1*((pt.dot(d1))/(absc(d1)*absc(d1)));
				v=pd;
				return true;
			}
		}*/

	}
	return false;
 if(hb) 
  {
//	  v=*zvec.begin();
	  return true;
  }

  return false;
}

void CFigure::setinfo(FINFO f)
{
	myinfo=f;

}

CString CFigure::getInfName()
{
	return myinfo.name;

}



void CFigure::surface(CDC *hdc)
{

}

void CFigure::copy(const CFigure *fig)
{

		libst=fig->libst;
		OpClstate=fig->OpClstate;
		brk=fig->brk;
		cl=fig->cl;
		handle=fig->handle;
		layer=fig->layer;
		myinfo=fig->myinfo;
		name=fig->name;
		ntype=fig->ntype;
		multiselect=fig->multiselect;

		bcolor=fig->bcolor;
		lplb=fig->lplb;
		dwStyleCount=fig->dwStyleCount;
		lpStyle=fig->lpStyle;
		lstyle=fig->lstyle;
		lwidth=fig->lwidth;
		lrefen=fig->lrefen;
		refline=fig->refline;
		refl.resize(fig->refl.size());
		std::copy(fig->refl.begin(),fig->refl.end(),refl.begin());
		transref=fig->transref;
		alpha=fig->alpha;
		angle=fig->angle;
		multcore=fig->multcore;
		if(!fig->texture_file.IsEmpty())
		{
			texture_file=fig->texture_file;
		}
		mode_texture=fig->mode_texture;
		tex_vert_mode=fig->tex_vert_mode;
		layer=fig->layer;
		

		linestate=fig->linestate;



		ptbegin.clear();
		int m=fig->ptbegin.size();
		for(int i=0;i<m;i++)
		{
			ptbegin.push_back(fig->ptbegin[i]);
		}
		ptend.clear();
		m=fig->ptend.size();
		for(i=0;i<m;i++)
		{
			ptend.push_back(fig->ptend[i]);
		}

		clipshape.clear();
		m=fig->clipshape.size();
		for(i=0;i<m;i++)
		{
			clipshape.push_back(fig->clipshape[i]);
		}

		m=fig->core.size();
		core.clear();
		for(i=0;i<m;i++)
		{
			core.push_back(fig->core[i]);
		}
		box=fig->box;
		vbox=fig->vbox;
		if(fig->mytext!=NULL)
		{
		if(mytext!=NULL)
		{
			delete mytext;
			mytext=NULL;
			pheight=0;
			pwidth=0;
		}
		int c=_msize(fig->mytext)/sizeof(col);
		mytext =new col[c];
		memcpy(mytext,fig->mytext,_msize(fig->mytext));
		pheight= fig->pheight;
		pwidth= fig->pwidth;
		trans_col =fig->trans_col;
		}
		mesh.empty();
		mesh.copy(fig->mesh);

}
void CFigure::add(const CFigure *fig)
{


		int m=fig->ptbegin.size();
		for(int i=0;i<m;i++)
		{
			ptbegin.push_back(fig->ptbegin[i]);
		}
		m=fig->ptend.size();
		for(i=0;i<m;i++)
		{
			ptend.push_back(fig->ptend[i]);
		}

		m=fig->clipshape.size();
		for(i=0;i<m;i++)
		{
			clipshape.push_back(fig->clipshape[i]);
		}

		m=fig->core.size();
		for(i=0;i<m;i++)
		{
			core.push_back(fig->core[i]);
		}
		box=fig->box;
		vbox=fig->vbox;
		mesh.add(&fig->mesh);

}

void CFigure::degel()
{

}

bool CFigure::PtinNode(CVector point,int multi)
{
	int i=-1;
	if(mesh.PtonVertex(point,i))
	{
		click=true;
		select=pnt;
		recselect=false;
		return true;
	}
	return false;
}
bool CFigure::PtinNode2(CVector point,int& i)
{
	if(mesh.PtonVertex(point,i))
	{
		click=true;
		select=pnt;
		recselect=false;
		return true;
	}
	return false;
}
bool CFigure::PtinEdge(CVector point,int& i)
{
	CVector v,v1;
	float u;
	if(mesh.PtonEdge(point,v1,u,v))
	{
		click=true;
		i=v.z;
		select=pnt;
		recselect=false;
		return true;
	}
	return false;
}

bool CFigure::isClose()
{
 return cl;
}

void CFigure::setfillpoint(CVector p)
{
 fill_p=p;
}

void CFigure::setRDC(CDC *hdc)
{
	rhdc=hdc;

}

CDC* CFigure::getDC()
{
  return rhdc;
}

void CFigure::setInterest(CSubject *sub)
{
	sub->RegisterInterest(this);
}

void CFigure::SendNotify(CString s, void *param[])
{
	if(s=="Transparency")
	{
		float *a=(float*)param[0];
		alpha=__max(*a,0);
		alpha=__min(alpha,1);
		UpdateTransparency();
	}
	if(s=="move")
	{
	for(vector<CConstraint*>::iterator it=vconstraint.begin();it!=vconstraint.end();it++)
	{
		bool b=(bool*)param[1];
		if(!(*it)->done)
			(*it)->Update(this);
	}
	}

}

void CFigure::setTexture(CString s,CDC* hdc)
{
 cl=true;
 texture_file=s;
 mode_texture=none;//wrap;
 tex_vert_mode=image_texture;
 if(s!="")
	 UpdateTexture(hdc);
}

//DEL void CFigure::setclickstate(CState *s)
//DEL {
//DEL m_clickstate=s;
//DEL }

void CFigure::sendclickNotify()
{
	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
			(*it)->SendNotify("click",NULL);
	}
  
}

/*void CFigure::selectMP(CVector point)
{
	m_clickstate->processpoint(point);
}
*/
CRay CFigure::getRefRay()
{
 return refRay;
}

void CFigure::setRefRay(CVector begin, CVector end)
{
	refRay.assign(begin,end);
}

void CFigure::v3D()
{
CVector vrx,vry,vrz;
vrx.getcoorx();
vry.getcoory();
vrz.getcoorz();
CMesh::ivertex pt;
	for(pt=mesh.vbegin();pt!=mesh.vend();pt++)
	{
		(pt)->second->v=vrx*(pt)->second->v.x+vry*(pt)->second->v.y+vrz*(pt)->second->v.z;

	}

}

void CFigure::v2D()
{
CVector vrx,vry,vrz;
vrx.getcoorx();
vry.getcoory();
vrz.getcoorz();
CMesh::ivertex pt;
	for(pt=mesh.vbegin();pt!=mesh.vend();pt++)
	{
		(pt)->second->v=vrx*(pt)->second->v.x+vry*(pt)->second->v.y+vrz*(pt)->second->v.z;

	}

}

void CFigure::setspline(bool s)
{
spline=s;
}

SELECT CFigure::getselectmode()
{
return select;
}

void CFigure::UpdateTransparency()
{

}

CVector* CFigure::getVector()
{
return NULL;
}

void CFigure::getdisplayparam(CFigure *f)
{
	ptbegin=f->ptbegin;
	ptend=f->ptend;
	CVector blend_p;
	alpha=f->alpha;
	blend_radius=f->blend_radius;
	blend_plane=f->blend_plane;
	current_alpha=f->current_alpha;
	blend_mode=f->blend_mode;
	tex_vert_mode=f->tex_vert_mode;
	tex_text_mode=f->tex_text_mode;
	mode_texture=f->mode_texture;
	bcolor=f->bcolor;
	lplb=f->lplb;
	dwStyleCount=f->dwStyleCount;
	lpStyle=f->lpStyle;
	lstyle=f->lstyle;
	lwidth=f->lwidth;
	lrefen=f->lrefen;
	refline=f->refline;
	transref=f->transref;

	//	copy(f);



}

void CFigure::keytranslate(CWnd *wnd, CDC *hdc, int key)
{
	prevptbegin=ptbegin;
	prevptend=ptend;

   int  b=10;
	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);//vro.getcooro();
	CVector v;
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	if(key==02)
	{
    v=vrx*b;
	vt.Translate(vrx*b);//v0-v1);//camor+=v1;
	vt.endT();

	}
	else if(key==01)
	{
	    v=vrx*(-b);
		vt.Translate(vrx*(-b));//camor.z+=b*5;
		vt.endT();
	}
	else if(key==11)
	{
	    v=vry*b;
		vt.Translate(vry*b);//camor.z+=b*5;
		vt.endT();
	}
	else if(key==12)
	{
	    v=vry*(-b);
		vt.Translate(vry*(-b));//camor.z+=b*5;
		vt.endT();
	}
	else if(key==21)
	{
	    v=vrz*b;
		vt.Translate(vrz*b);//camor.z+=b*5;
		vt.endT();
	}
	else if(key==22)
	{
	    v=vrz*(-b);
		vt.Translate(vrz*(-b));//camor.z+=b*5;
		vt.endT();
	}
	UpdateMesh();
/*	if(ptend.size()==ptbegin.size())
	{
	for (piterb=ptbegin.begin(),pitere=ptend.begin();piterb<ptbegin.end();piterb++,pitere++)
	{
		piterb->assign(*piterb,true);
		pitere->assign(*pitere,true);
	}
	}
	else
	{
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		piterb->assign(*piterb,true);
	}

	}*/
	postTranslate(v);
	vt.popTransform();
//	updatecore();
//	drawTrans(hdc);


}

void CFigure::postTranslate(CVector v)
{
	   CMesh::ivertex iv=mesh.vbegin();
	   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
	   {
//		   (iv)->second->v.assign((iv)->second->v,true);
	   }

}

vector<CVector>* CFigure::getpt()
{
	vector<CVector>* v=new vector<CVector>;
	*v=mesh.getVectors();//ptbegin;
//	v->push_back(ptend.back());
	return v;
}
struct isunique
{
	bool operator ()(CVector v1,CVector v2) const
	{
		return v1!=v2;
	}
};

bool CFigure::isInside(CVector v,bool t)
{
	CRay r1(box.corner(0),box.corner(2));
	CVector v1(box.corner(0),box.corner(2)),v2,vry,vrx;
	v1.getcoorx();vry.getcoory();vrx.getcoorx();
	CRay r2(v,v+v1);
	bool j=0;
	vector<CVector>::iterator it,ite;

	for(it=ptbegin.begin(),ite=ptend.begin();it!=ptbegin.end();it++,ite++)
	{	CVector v1(*it,*ite);
		v1=v1/absc(v1);
		CVector v2(*it,v);
		v2=v2/absc(v2);
		float g=0;
		float gb=v1.dot(v2);
		if((gb==1)||(gb==-1))
		{
			CVector vj=(*it+*ite)/2;
			v1=v-vj;
			v2=*it-vj;
			if(absc(v1)<=absc(v2)) g=1;
		}
		if((*it==v)||(g==1)) return false;
	}

	set<CVector,isunique> pt;
	enum {cor,nocor,end} state;
	state=cor;
	int k=0;
	while(state==cor)
	{
		vrx=polarc(1,pi/12*k,true);
		r2.assign(v,v+vrx);
		pt.clear();
		k++;

	for(it=ptbegin.begin(),ite=ptend.begin();it!=ptbegin.end();it++,ite++)
	{	

		CRay r1(*it,*ite,1);
		CVector i=r1.Intersect(r2);
		if(i.x!=1E-10)
		{
			if((i==*it)||(i==*ite))
			{
				state=cor;
				break;
			}
			v2=i-v;
			if(v1.dot(v2)>=0)
			{
				pt.insert(i);
			}
		}
	if(it==ptbegin.end()-1) state=end;
	}
	}
	int jk=pt.size();
	for(int i=0;i<jk;i++)
		j=!j;

	return (!j);
}


void CFigure::init()
{
	spline=false;
	lpStyle=NULL;
	layer.clear=false;
	layer.on=true;
	layer.name="";
	handle="";
	libst=false;
	intersectv=false;
	snap=false;
	snapstate=O;
	uncount=1;
	lwidth=1;
	lstyle=PS_SOLID|PS_GEOMETRIC|PS_ENDCAP_FLAT|PS_JOIN_ROUND;
	bcolor=NULL;
	v0.nullvec();
	prevrotateCenter=v0;
	refline=v0;
	cl=false; brk=false;
	colchange=false;
	OpClstate=open;
	linestate=D0;
	multiselect=false;
	core.clear();
	rotstate=R0;
//	setUndoparam();
//	name="CFigure";
	glinee=false;glineb=false;
lstate=L1; down=false;Up=false;
	//	p0=core.begin();


	ptsBegin=v0;
	ptsEnd=v0;
	
	ptend.clear();
	ptbegin.clear();
	core.clear();
	piterb=ptbegin.end();
	pitere=ptend.begin();
	
	
	click=false;
	Bisclick=false;
	inReg=false;
	distprec=5;
	transref=false;

	alpha=1;

	lplb.lbStyle=BS_SOLID;
	lplb.lbColor=PALETTERGB(15,15,15);
	lplb.lbHatch=NULL;
	
	dwStyleCount=0;
	angle=0;
	multcore=false;
	
	texture_file="";
	mode_texture=none;
	tex_vert_mode=backcolor;
	mytext=NULL;
	pheight=0;
	pwidth=0;
	fPrevB=false;
	current_alpha=0;
	box.empty();
	mesh.empty();

}

void CFigure::UpdateTexture(CDC* hdc)
{
  //  mesh.updateTri();
	if(tex_vert_mode==backcolor)
	{
		if(mytext!=NULL)
		{
			try{
			delete []mytext;
			}catch(...)
			{
			}
			mytext=NULL;
			pheight=0;
			pwidth=0;
		}

//		mytext.clear();
		return;
	}

	if(mytext!=NULL) 
	{
		try{
		delete []mytext;
		}catch(...)
		{
		}
		mytext=NULL;
		pheight=0;
		pwidth=0;
	}
	if(texture_file!="")
	{
	CxImage im;
	im.Load(texture_file);
	im.Flip();
	LPBYTE alpha=im.AlphaGetPointer();
	LPBYTE lpBits=im.GetBits();
	
	pheight=im.GetHeight();
	pwidth=im.GetWidth();
	int np=im.GetBpp();
	if(mytext!=NULL)
		try{
		delete []mytext;
		}catch(...)
		{
		}
		mytext=new col[pheight*pwidth];
		int i = 0;
		int x, y,q;
		int r,g,b;
		if(np>8)
		{
		for(y =0;y<pheight;y++)//-1;y>-1;y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=lpBits[i++];
				mytext[q].g=lpBits[i++];
				mytext[q].r=lpBits[i++];
				mytext[q].a=alpha[q];
			}
		}
		}else
		{
		for(y =0;y<pheight;y++)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=mytext[q].g=mytext[q].r=lpBits[i++];
				mytext[q].a=alpha[q];
				if(mytext[q].b!=0)
				{
					int io=0;
				}
			}
		}

		}
	tex_vert_mode=image_texture;
	mode_texture=wrap;
	}	
/*	
//	CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
//	BYTE* text=(BYTE*)texture.GetDIBits();
  //  pheight=texture.GetHeight();
//	pwidth=texture.GetWidth();


	mytext=new col[pheight*pwidth];
	int i = 0;
		int x, y,q;
	int r,g,b;
		for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
//				if(texture.GetBitCount()==32)
				if(im.GetBpp()==32)
				{
				mytext[q].a=text[i++];
				}
			}
			i+=pwidth%4;
		}
	}
*/
}

const CAABB CFigure::getbox(CDC* hdc) 
{
	bool b=multiselect;
	multiselect=false;
	SELECT s=select;
//	if(hdc!=NULL)
//		getCharge(hdc);
	CFigure* f =new CFigure;
	f->copy(this);
	if((!multiselect))
		f->updatecore();
	select=s;
	multiselect=b;
	CAABB bo=f->box;
	delete f;
	return bo;
}

void CFigure::select_full()
{
	click=true;
	select=full;
}

void CFigure::select_node(int i)
{
	click=true;
	select=pnt;
	recselect=false;
	vs.push_back(i);
}
void CFigure::setPtOn()
{
	click=true;
	select=pnt;
	recselect=false;
}

void CFigure::Translate(CVector v)
{
	prevptbegin=ptbegin;
	prevptend=ptend;

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
    v=vrx*v.x+vry*v.y+vrz*v.z;
	vt.Translate(v);
	vt.endT();
	UpdateMesh();

	postTranslate(v);
	vt.popTransform();

}

void CFigure::Translate(CVector v, float node)
{
	prevptbegin=ptbegin;
	prevptend=ptend;

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro(0,0,0,1);
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
    v=vrx*v.x+vry*v.y+vrz*v.z;
	vt.Translate(v);
	vt.endT();
	CVertex* vx=mesh.getVertex(node);
	vx->v.assign(vx->v,true);
//	UpdateMesh();
	postTranslate(v);
	vt.popTransform();

}
void CFigure::TranslateNodeTo(CVector v, int node)
{
	CVertex* vx=mesh.Vertex(node);
	vx->v=v;

}
CVector CFigure::getEdge(int i,int j)
{
	return mesh.getEdge(i,j);
}
CVertex* CFigure::getPoint2(int u)
{
/*	if(u>1)
	{
		u=u/mesh.Ecount();
	}*/
	return mesh.Vertex(u);
}
CVector CFigure::getPoint(float u)
{
/*	if(u>1)
	{
		u=u/mesh.Ecount();
	}*/
	return mesh.getVector(u);
/*	vector<CVector> vs=mesh.getVector(u);
	
	//=mesh.getVectors();//ptbegin;
//	vs.push_back(ptend.back());
	int s =vs.size();
	if(u>vs.size()) 
		return CVector(0,0);
	float w;//=vs.size()*u;
	int i=floor(u);
	w=u-i;
	int j=i+1>=s?i:i+1;
	CVector v=vs[j]-vs[i];
	v=vs[i]+v*w;
	return v;
	*/
}

void CFigure::rotate(float u, short sens)
{
	angle=u;

	CVector v00,v01;
	v00.assign(-rotateCenter);
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(-rotateCenter);
	if(sens==1)
	{
	vt.TRotatex(angle);
	}else
	if(sens==2)
	{
	vt.TRotatey(angle);
	}
	else
	{
	vt.TRotate(angle);
	}
	v01.assign(rotateCenter);
	vt.Translate(rotateCenter);
	vt.endT();
	UpdateMesh();
	vt.popTransform();
	create();

}
void CFigure::scale(float u, short sens)
{

	CVector vc(core[8],v0);//vc.viewi();
	CVector va(core[0],core[1]);//va.viewi();
	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(vc);
	vt.TRotate(argu(va));
	vc.assign(v0,core[8]);//vc.viewi();
//			vt.Translate(vc);
	vt.endT();
	
	vt.pushUnit();
	vt.Translate(-rotateCenter);


	if(sens==1)
	{
	vt.Scale(u,1,1);
	}else
	if(sens==2)
	{
	vt.Scale(1,u,1);
	}
	else if(sens==3)
	{
	vt.Scale(1,1,u);
	}
	else
	vt.Scale(u,u,u);
	
	vt.Translate(rotateCenter);
	vt.endT();
	UpdateMesh();
	postTranslate(vc);
	vt.popTransform();
	create();

}

CFigure* CFigure::copy2(float d, CFigure *pbulk)
{
	vector<CVector> resultb,rresultb, resulte,rresulte;
//	pushUnit();

	if((!multiselect)||(!libst)) updatecore();
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();
	double dist=d;
	CVector v00=v0;
	CVector v01=v0;

	v00.assign(core[8]);//CVector(0,0,0,1));
	v00=core[8];
	v00.worldi();

	CTVector vt;
	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(-core[8]);
	vt.Scale(dist,dist,dist);
	vt.Translate(core[8]);
	vt.endT();
	v00.assign(CVector(0,0,0,1));
	v01.assign(core[8],true);
	CVector ptb,pte,test;
	UpdateMesh();
	resultb=mesh.getVectors();
	resulte=resultb;
	resultb.pop_back();
	resulte.erase(resulte.begin());
	vt.popTransform();
	v01.assign(core[8],true);

	pbulk->createobj(resultb,resulte);
	return pbulk;

}

void CFigure::editobj(CDC* hdc)
{

}
void CFigure::editobj(CVector point)
{

}

void CFigure::TranslateTo(CVector v)
{
	updatecore();
	CVector c=box.center();
	CVector vp=v-c;
	Translate(vp);
}
CVector CFigure::TranslateTo(CVector v,float n,int n1)
{
	updatecore();
	CVector c=getPoint(n);
	CVector vp=v-c;
	if(!n1)
	{
		Translate(vp,n);
	for(vector<CConstraint*>::iterator it=vconstraint.begin();it!=vconstraint.end();it++)
	{
		if(!(*it)->done)
		(*it)->Update(this);
	}
	}
	else
		if(n1==1)
		{
			Translate(vp);
		}
	return vp;
}
void CFigure::alignWith(CFigure* f,float u)
{
	updatecore();
	CVector fdir_v=f->getPoint(f->dir[1])-f->getPoint(f->dir[0]);
	float dir_f=argu(fdir_v);
	CVector c=box.center();
	CVector vp=getPoint(u)-c;
	float my_dir=argu(vp);
	rotate(my_dir-dir_f,0);
}
void CFigure::setEdge(CVector v,int i,int j)
{
	mesh.setEdge(v,i,j);
	for(vector<CConstraint*>::iterator it=vconstraint.begin();it!=vconstraint.end();it++)
	{
		if(!(*it)->done)
		(*it)->Update(this);
	}
}
void CFigure::setDir(float u1,float u2)
{
	dir[0]=u1;
	dir[1]=u2;
}

void CFigure::connectTo(CFigure *f, float u1,float u2,int al)
{
		CVector v1=f->getPoint(u1);
		CVector v=getPoint(u2);
		CVector v2=v1-v;
		Translate(v2);
		v=getPoint(u2);
		CPoint pol=mesh.Vertex(0)->v;
		if(sqrt(pol.x*pol.x+pol.y*pol.y)<1)
		{
			int uy=0;
		}
		setRotateCenter(v);
		if(al ==1)
		rotate(pi/2+argu(f->RefVec(u1))-argu(RefVec()),0);
		else if(al==2)
		rotate(argu(f->RefVec(u1))-argu(RefVec()),0);
//		setInterest(f);
//		con=true;
//		f->setConnected(true);
}
void CFigure::connectTo(CVector p, float u1, bool ref)
{
		CVector v1=getPoint(u1);
		CVector v2=p-v1;
		Translate(v2);
		if (ref)
		{
			rotate(pi,0);
		}
//		con=true;
//		f->setConnected(true);
}

void CFigure::createobj(CMesh *m)
{
	mesh.copy(m);
	updatecore();
	setInit();
}

void CFigure::operator =(const CFigure& f)
{
	copy(&f);
}
CFigure::CFigure(const CFigure& f)
{
	copy(&f);
}

CFigure* CFigure::generateCopy()
{
	CFigure* l=new CFigure;
	l->copy(this);
	return l;
}

void CFigure::setbox(CAABB b)
{
	box=b;
	vbox=b;
//	updatecore();
	setcore();
	setvcore();
}

void CFigure::UpdateMesh()
{
	mesh.UpdateVertex();
	rotateCenter.assign(rotateCenter,true);
}

CFigure* CFigure::copybyL(CFigure *line)
{
	vector<CVector>* presult[2];
 	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	
	line->updatecore();

	ptsBegin=selectvec[0];
	ptsEnd=selectvec[2];
	
	CRay VMainb(ptsBegin,ptsEnd);
 	CVector p=VMainb.getclosestPoint(line->getCenter());
	CVector n=line->getCenter()-p;
	n+=n;
	CVector V(ptsBegin,ptsEnd);
	V.dot(n);
	
	CFigure* f;//=new CFigure;
//	f->copy(line);
	f=line->generateCopy();

	CTVector v;
	v.pushTransform();
	v.pushUnit();
	v.Translate(-n);
	v.endT();
	selectvec.clear();
	f->UpdateMesh();
	v.popTransform();
	f->updatecore();
	return f; 

}

void CFigure::OffsetMesh(float u, CFigure *f)
{
	mesh.offset(u,&f->mesh);
}

float CFigure::Min_dist_toEdge(CVector v)
{
	float u=mesh.min_dist_toEdge(v);
	return u;

}

CFigure* CFigure::Offset(float u)
{
	CFigure* f;
	f=generateCopy();
	f->multiselect=false;
	OffsetMesh(u,f);
	updatecore();
	return f;
}

vector<CFigure*>  CFigure::Trim(vector<CVector>& v1,CFigure *f,bool side,bool st)
{
	mesh.TrimEdge3(v1[0],&f->mesh);//,side,st);
	updatecore();
	return vector<CFigure*>();
}

CMesh* CFigure::getMesh()
{
 return &mesh;
}

void CFigure::UpdateTexture(CDC *hdc, CBitmap *bmp)
{
	BITMAP bn;
	bmp->GetBitmap(&bn);
	int d=bn.bmHeight*bn.bmWidth*4;
	int j=bn.bmHeight*bn.bmWidthBytes;
	BYTE* tex;//=new BYTE[d];//bn.bmWidthBytes];
//	memset(tex,0,d);
//	bmp->GetBitmapBits(d,tex);
//	CImage im;
//	tex=(BYTE*)im.ConvertDDBtoDIB(bmp,hdc);
	ASSERT(tex);

//	PBITMAPINFO pbmi=im.CreateBMPInfo((HBITMAP)bmp->GetSafeHandle(),true);
	BITMAPINFO bitinfo1;
	
	BITMAPINFOHEADER bitinfo;

	bitinfo.biSize=sizeof(BITMAPINFOHEADER);
	bitinfo.biWidth=bn.bmWidth;
	bitinfo.biHeight=bn.bmHeight;
	bitinfo.biPlanes = 1;
	bitinfo.biBitCount = 32;
	bitinfo.biCompression = BI_RGB;
    bitinfo.biXPelsPerMeter = 0;
    bitinfo.biYPelsPerMeter = 0;
    bitinfo.biClrUsed       = 0;
    bitinfo.biClrImportant  = 0;

	bitinfo1.bmiHeader=bitinfo;

    GetDIBits(hdc->GetSafeHdc(),(HBITMAP) bmp->GetSafeHandle(), 0, (WORD) bn.bmHeight, NULL, &bitinfo1,DIB_RGB_COLORS);
    LPBYTE lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED,bitinfo1.bmiHeader.biSizeImage);


    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    int o=GetDIBits(hdc->GetSafeHdc(),(HBITMAP) bmp->GetSafeHandle(), 0, (WORD) bn.bmHeight, lpBits, &bitinfo1,DIB_RGB_COLORS);
	DWORD f=GetLastError();
//	bmp->GetBitmapBits(pbmi->bmiHeader.biSizeImage,lpBits);
	lpBits=lpBits+bitinfo1.bmiHeader.biClrUsed * sizeof (RGBQUAD);
    pheight=bn.bmHeight;
	pwidth=bn.bmWidth;

	if(mytext!=NULL)
		delete mytext;
		mytext=new col[pheight*pwidth];
		int i = 0;
		int x, y,q;
		int r,g,b;
		for(y = pheight-1;y>-1;y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=lpBits[i++];
				mytext[q].g=lpBits[i++];
				mytext[q].r=lpBits[i++];
				mytext[q].a=lpBits[i++];
			}
		}
	GlobalFree(lpBits);
}

CVector CFigure::Vector(int i)
{
 return mesh.Vector(i);
}
CVector CFigure::LVector()
{
 return mesh.Vector(mesh.Vcount()-1);
}

void CFigure::setRefLine(float u1, float u2)
{
	refl.clear();
 refl.push_back(u1);
 refl.push_back(u2);
}

CVector CFigure::RefVec(float u)
{
	ASSERT(refl.size()!=0);
	CVector vb=getPoint(refl[0]);
	CVector ve=getPoint(refl[1]);
	return CVector(vb,ve);

}

void CFigure::setVector(int i, CVector v)
{
	ASSERT(i<mesh.Vcount());
	mesh.Vertex(i)->v =v;
}

void CFigure::connectNodeTo(CVector v, float i, bool c)
{
	vector<CVector> vs=mesh.getVectors();//ptbegin;
	int s =vs.size()-1;
	if(i>vs.size()) 
		return ;
	int i1=floor(i);
	int j=i1+1>s?i1:i1+1;

	CVector c0=getPoint(i);
	CVector c1=getPoint(j-1);
	float b;
	if(i == 0)
	{
		j=0;
		b=1;
	}
	else
		b=1/i;
	CVector r = v - c1;
	r = r * b;
	CVector vp=c1 + r;
 //   vp = v;
	TranslateTo(vp,j);
}
CMesh* CFigure::Clip0(CFigure* f)
{
	if(std::find(clipshape.begin(),clipshape.end(),f)==clipshape.end())
		clipshape.push_back(f);
	return NULL;
}

CMesh* CFigure::Clip(CFigure* f,bool side)
{
	if(std::find(clipshape.begin(),clipshape.end(),f)==clipshape.end())
		clipshape.push_back(f);
	if((!multiselect)&&(!libst))
		updatecore();
	if(f->box.containpts(box.max)&& f->box.containpts(box.min)){
	    CMesh* m2=new CMesh;
		m2->copy(mesh);
		return m2;
	}
	else
		if(box.containpts(f->box.max)&& box.containpts(f->box.min))
		{
	    CMesh* m2=new CMesh;
		m2->copy(f->getMesh());
		mesh.copy(f->getMesh());
			return m2;
		}
	    CMesh* m2=new CMesh;
		m2->copy(f->getMesh());
	CMesh* m = mesh.clip2(NULL,m2,side);
	mesh.copy(m);
	return m;
}

CMesh* CFigure::clipShape(CDC* hdc)
{
	updatecore();
	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	v1=v0.sgetscrtop();
	CPoint p(v0.x,v0.y);
    v0 = p;
	p.x=v1.x;
	p.y=v1.y;
	v1 =p;
//	v1.z=0;
//	v0.z=0;
	CRectangle r(v0,v1);
	if(r.box.containpts(box.max)&& r.box.containpts(box.min)){
	    CMesh* m2=new CMesh;
		m2->copy(mesh);
		return m2;
	}
	else
		if(box.containpts(r.box.max)&& box.containpts(r.box.min))
		{
	    CMesh* m2=new CMesh;
		m2->copy(r.getMesh());
			return m2;
		}
	    CMesh* m2=new CMesh;
		m2->copy(r.getMesh());
	CMesh* m = mesh.clip(hdc,m2);
	return m;
}

void CFigure::connectNodeTo(CVector v)
{
	ptbegin=mesh.getVectors();
	isclose p(v);
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),p);
	int i = vi - ptbegin.begin();
	TranslateTo(v,i);	

}

void CFigure::connectNodeToL(CVector v, float l, float i)
{
	//Check this function later
	vector<CVector> vs=mesh.getVectors();//ptbegin;
	int s =vs.size()-1;
	if(i>vs.size()) 
		return ;
	int i1=floor(i);
	int j=i1+1>s?i1:i1+1;

	CVector c0=getPoint(i1-1);
	CVector c1=getPoint(j);
	float b;
	if(i == 0)
	{
		j=0;
		b=1;
	}
	else
		b=1/i;
	CVector r = c1 - c0;
	r.Normalise();
	r = r * l;
	CVector vp=v + r;
 //   vp = v;
	TranslateTo(vp,j);

}

void CFigure::addextranode(CVector point)
{

}

void CFigure::offset(CFigure *f, float u)
{
	copy(f->Offset(u));  
}

void CFigure::Extend(CFigure *f)
{
  mesh.extendEdge(&f->mesh);
}
void CFigure::AddEdge(vector<CVector>& v1)
{
  mesh.addEdge(v1);
}

bool CFigure::inBox(CVector v)
{
	updatecore();
	CAABB ab=box;
	ab.inflate(100);
	return ab.containpts(v);
}

void CFigure::intersect(CFigure *f, CVector &v)
{
	CRay v1(selectvec[0],selectvec[2]);
	CRay v2(f->selectvec[0],f->selectvec[2]);
	v=v1.Intersect(v2);
}

bool CFigure::snapperp(CVector  vl,CVector vs, CVector &v)
{
	CMesh::iedge pt;
//	for(pt=mesh.ebegin();pt!=mesh.eend();pt++)
	{
//		CVector vo=(*pt)->Start()->v;
//		CVector ve=(*pt)->End()->v;
//		vl=ve-vo;
		vl=polarc(absc(vl),argu(vl)+pi/2);
		CVector vo,ve;
		ve=vl.ppprojection(v-vs,&vo);
		double d=absc(ve);
		if((d<10)&&(d>=0))
		{
			v=vs+vo;
			return true;
		}

	}
		return false;
/*	if(selectvec.size()==0)
	{

	CMesh::iedge pt;
	for(pt=mesh.ebegin();pt!=mesh.eend();pt++)
	{
		CVector vo=(*pt)->Start()->v;
		CVector ve=(*pt)->End()->v;

		CRay v1(vo,ve);
		CVector vv1(vo,ve);
		float f1=argu(vv1)+pi/2;
		CVector vr=polarc(1,f1);

		CVector vom=f->mesh.Vector(f->mesh.Vcount()-1);
		CVector v01=vom+vr;
		CVector v02(vom,v01);
		CVector vr1(vom,v);

		CVector v03=v02.ppprojection(vr1,&v01);
		if(absc(v03)<20)
		{
			v=vom+v01;
			return true;
		}

	}
	return false;
	
	}
	CRay v1(selectvec[0],selectvec[2]);
	CVector vv1(selectvec[0],selectvec[2]);
	float f1=argu(vv1)+pi/2;
	CVector vr=polarc(1,f1);
	CVector vom=f->mesh.Vector(f->mesh.Vcount()-1);
	CVector v01=vom+vr;
	CRay v2(vom,v01);
	CVector v02=v;	
	CVector v03=v02.ppprojection(v,&v);
	
	CVector v0=v1.Intersect(v2);
	
	if(absc(v0-v)<20)
	{
		v=v0;
		return true;
	}
	v=v02;
	return false;*/
}

bool CFigure::snappara(CVector  vl,CVector& vs, CVector &v)
{
		CVector vl1=vl,v1=v;
		vl=polarc(absc(vl),argu(vl)+pi/2);
		CVector vo,ve;
		ve=vl.ppprojection(v-vs,&vo);
		v=vs+vo;
//		vl1=polarc(absc(vl1),argu(vl1)+pi/2);
		ve=vl1.ppprojection(v1-v,&vo);
		double d=absc(ve);
		if((d<10)&&(d>=0))
		{
			vs=v;
			v=v+vo;
			return true;
		}

		return false;
	CMesh::iedge pt;
	for(pt=mesh.ebegin();pt!=mesh.eend();pt++)
	{
		CVector vo=(pt)->second->Start()->v;
		CVector ve=(pt)->second->End()->v;
		vl=ve-vo;
		return true;

	}
		return false;

}

bool CFigure::pointconstraint(pair<CFigure*,int> f1,pair<CFigure*,int> f2)
{
	constraint=new CConstraint(f1.first,f2.first);
	constraint->PointToPoint(f1.first,f1.second,f2.first,f2.second);
	vconstraint.push_back(constraint);
	return true;
}
bool CFigure::edgeconstraint(pair<CFigure*,int> f1,pair<CFigure*,int> f2)
{
	constraint=new CConstraint(f1.first,f2.first);
	constraint->EdgeToEdge(f1.first,f1.second,f2.first,f2.second);
	vconstraint.push_back(constraint);
	return true;
}
bool CFigure::edgeperpendicularconstraint(pair<CFigure*,int> f1,pair<CFigure*,int> f2)
{
	constraint=new CConstraint(f1.first,f2.first);
	constraint->EdgeToPerpendicular(f1.first,f1.second,f2.first,f2.second);
	vconstraint.push_back(constraint);
	constraint->Update(f1.first);
	return true;
}
bool CFigure::edgehorizontalconstraint(pair<CFigure*,int> f1)
{
	constraint=new CConstraint(f1.first,f1.first);
	constraint->EdgeToHorizontal(f1.first,f1.second);
	vconstraint.push_back(constraint);
	constraint->Update(f1.first);
	return true;
}
bool CFigure::edgeverticalconstraint(pair<CFigure*,int> f1)
{
	constraint=new CConstraint(f1.first,f1.first);
	constraint->EdgeToVertical(f1.first,f1.second);
	vconstraint.push_back(constraint);
	constraint->Update(f1.first);
	return true;
}

void CFigure::setConstrainedPoint(float i)
{
	mesh.setConstrainedVertex(i);
}
void CFigure::setConstrainedEdge(float i)
{
	mesh.setConstrainedEdge(i);
}
