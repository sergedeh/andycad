// Draw.cpp: implementation of the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Draw.h"
#include "render.h"
#include "aabb.h"
#include <algorithm>
#include "spline.h"
#include "dimtext.h"
#include <string>


#define line 1
#define cercle 2
#define rectangle 3
#define bezier 4
#define qline 5

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool CDraw::snap=false;

CRender* render=new CRender;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDraw::CDraw()
{
	version=0;
	count=0;
	CVector v(0,0,1);
	v0=v;
	v_current=v0;
	fit=0;
	mouseon=false;
	sfit=0;
	sefit=0;
	bck=false;
	m=0;ms=0;
	cdel=false;
	fittopage=false;
	initVect();
	VinitVect();
	cam.initCam();
	veclayer.clear();

	B=false;
	Bminus=false;
	positions[1]=v0;ita=0;
	rzoom=0.5;
	curr_fig=NULL;
	
	selected=false;
	menuselect=false;

	endDraw=FALSE;
	change=false;
	nbc=0;
	valid=false;
	candraw = true;
	currlayer.clear=false;
	currlayer.on=true;
	currlayer.lock=false;
	currlayer.name="Normal";
	veclayer.push_back(currlayer);

	CVector k(0,0,0,1);
	CVector kt(k.getscrtop()/2,k.getscrb()/2);
	k=k-kt;
	pBezier=new CBezier;
	Dim=NULL;
	DimL= NULL;
	snap_fig=NULL;

}

CDraw::~CDraw()
{
//	for(int i=0;i<fit;i++)
//	{
//	delete fig[i];
//	}
	fig.clear();
	fit=0;

//	delete pBezier;
	int j=rmemento.size();
//	for(int i=0;i<j;i++)
//	{
//	delete rmemento[i];
//	}
	rmemento.clear();

	while(!redoList.empty())
		redoList.pop();
	j=vmemento.size();
//	for(i=0;i<j;i++)
//	{
//	delete vmemento[i];
//	}
	vmemento.clear();

	while(!undoList.empty())
		undoList.pop();


}

bool CDraw::add(CString figure,bool fPrevLine,CDC* hdc,CVector point)
{
	if(fit>0)
		curr_fig=fig[fit-1];

	if (figure=="Line")
	{
		pLine.setMove(true,point);
		endDraw=pLine.draw(fPrevLine,hdc,point);
		return true;
	} 
	else
	if (figure=="Box")
	{
		return true;
	} 
	else
	if (figure=="Plane")
	{
		pRectangle.setMove(true,point);
		endDraw=pRectangle.draw(fPrevLine,hdc,point);
		return true;
	} 
	else
	if (figure=="Image")
	{
		image.setMove(true,point);		
		endDraw=image.draw(fPrevLine,hdc,point);
		return true;
	} 
	else
	if (figure=="QLine")
	{
		pQLine.setMove(true,point);
		endDraw=pQLine.draw(fPrevLine,hdc,point);
		return true;
	} 	
	else 
	if (figure=="Bezier")
	{
		pBezier->setMove(true,point);
		endDraw=pBezier->draw(fPrevLine,hdc,point);
		return true;
	}
	else 
	if (figure=="BezierFree")
	{
		pBezier->setFreeMove(true,point);
		endDraw=pBezier->draw(fPrevLine,hdc,point);
		return true;
	} else 
	if (figure=="Rectangle")
	{
		pRectangle.setMove(true,point);
		endDraw=pRectangle.draw(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="3DotCircle")
	{
		endDraw=pCircle.Draw3DotCircle(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="2DotCircle")
	{
		endDraw=pCircle.Draw2DotCircle(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="Circle")
	{
		endDraw=pCircle.DrawCircle(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="Ellipse")
	{
		endDraw=pCircle.DrawEllipse(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="Arc")
	{
		endDraw=pArc.DrawArc(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="2DotArc")
	{
		endDraw=pArc.Draw2DotArc(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="3DotArc")
	{
		endDraw=pArc.Draw3DotArc(fPrevLine,hdc,point);
		return true;
	}else
	if (figure=="3DotArc2")
	{
		endDraw=pArc.Draw3DotArc2(fPrevLine,hdc,point);
		return true;
	}else
	if ((figure=="select")&&(bck==false))
	{
		pSelect.setPtsBegin(point);
		pSelect.setstyle(1);
		bck=true;
	}else
	if ((figure=="select")&&(bck==true))
	{
		pSelect.setMove(true,point);
		endDraw=pSelect.draw(fPrevLine,hdc,point);
		return true;
	}
	else 
	if (figure=="Text")
	{
		
		textcad->setMove(true,point);
		endDraw=textcad->draw(fPrevLine,hdc,point);
		return true;
	}
	else
	if ((figure=="multline")||(figure=="leader")||(figure=="DimA")||(figure=="DimF")||(figure=="DimV")||(figure=="DimH")||(figure=="DimD")||(figure=="DimR"))
	{
//		if(candraw)
			endDraw=((CDim*)fig[fit-1])->draw(fPrevLine,hdc,point);
			curr_fig=fig[fit-1];
		return true;
	}
	else
	if ((figure=="DimL")||(figure=="DimLH")||(figure=="DimLV"))
	{
//		if(candraw)
			endDraw=((CDimL*)fig[fit-1])->draw(fPrevLine,hdc,point);
			curr_fig=fig[fit-1];
		return true;
	}
	
return false;	
}


void CDraw::display(CDC *rhdc,CDC* hdc)
{

	try{
	pLine.setRDC(rhdc);
	
	CMesh m;
//	m.Bdraw();
	box.empty();
	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	v1=v0.sgetscrtop();
	CPoint p(v0.x,v0.y);
    v0 = p;
	p.x=v1.x;
	p.y=v1.y;
	v1 =p;
	CRectangle r(v0,v1);
	sc_box.empty();
	sc_box.add(r.getbox(hdc));
	DWORD tick=GetTickCount();
	int j=0;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(!it->clear)
		{

			for (int i=0;i<fit;i++) 
			{
				if(fig[i]->getLayer().name==it->name)
				{
				if(!sc_box.intersectAABB2(fig[i]->box)/*getbox(hdc))*/) continue;
				//if(fig[i]->ptbegin.size()!=0)
				//{
					fig[i]->draw(hdc);
					box.add(fig[i]->box);
					j++;
				//}
				}
			}
		}
	}
		DWORD ptick=GetTickCount()-tick;
		CString s;
		s.Format("time spend to Display:%d for %d number of elements\n",ptick,j);
		TRACE(s);
//	m.Edraw(hdc);
	}catch(...)
	{
		AfxMessageBox("Display Error");
	}	
	candraw=false;
}

void CDraw::Create(CDC *hdc,CString figure,CVector point)
{
	if(snap)
	{
			fsnapPoint(point,hdc);
	}
	v_current =point;

	if(figure=="Line")
	{
		pLine.setPtsBegin(point);

	}else
	if(figure=="Box")
	{
		fig.resize(fig.size()+1);
		fig[fit]=new CBezier;
		((CBezier*)fig[fit])->cube(point,100);
		fig[fit]->surface(hdc);fit++;

	}else
	if(figure=="Sphere")
	{
		fig.resize(fig.size()+1);
		fig[fit]=new CBezier;
		((CBezier*)fig[fit])->sphere(point,100);
		fig[fit]->surface(hdc);fit++;

	}else
	if(figure=="Plane")
	{
		pRectangle.setPtsBegin(point);

	}else
	if(figure=="Image")
	{	
		image.setPtsBegin(point);

	}else
	if((figure=="DimD")||(figure=="DimR"))
	{	

		if(!valid)
		{
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=new CDim;
		fit++;
		sfit++;
		count++;
		((CDim*)fig[fit-1])->setstyle(figure);
		fig[fit-1]->setPtsBegin(point);
		candraw = true;
		valid =true;
		CCercle cerc;
		for(int i=0;i<fit-1;i++)
		{
			vector<CVector> test;
			if((fig[i]->getName()==cerc.getName())&&(fig[i]->inRegion(point)))
			{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
//				test[0]=fig[i]->getCenter();

				((CDim*)fig[fit-1])->addSL(test);
				((CDim*)fig[fit-1])->getCharge(hdc);

				string scount;
				CString f;
				f.Format(_T("%d"),count);
				scount=f;
				fig[fit-1]->setHandle(scount);
				fig[fit-1]->setLayer(currlayer);
				fig[fit-1]->setcorevecor();
				break;
				}
	
			}
		}
		
		}
		
	}else
	if((figure=="multline")||(figure=="leader")||(figure=="DimF")||(figure=="DimV")||(figure=="DimH"))
	{	
		if(!valid)
		{
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=new CDim;
		fit++;
		sfit++;
		count++;
		((CDim*)fig[fit-1])->setstyle(figure);
			vector<CFigure*> fb,fe;
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->inBox(point))
					fb.push_back(fig[i]);
			}
			int t=fb.size();
			vector<CVector> test;

			CVector v=point,vl=point;
			fig[fit-1]->fsnap(v,vl,"endpoint",hdc);
			for(i=0;i<t;i++)
			{
					test=fig[i]->getSelectvec(point);
					if(test.size()!=0)
						if(test[0]!=test[2])
						{
							fig[fit-1]->setInterest(fig[i]);
							((CDim*)fig[fit-1])->drivingParam(fig[i],test);
						}
			}
		fig[fit-1]->setPtsBegin(vl);
		candraw = true;
		}
	}else
	if((figure=="DimL")||(figure=="DimLH")||(figure=="DimLV"))
	{	
		if(!valid)
		{
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=new CDimL;
		fit++;
		sfit++;
		count++;
		((CDimL*)fig[fit-1])->setstyle(figure);
		fig[fit-1]->setPtsBegin(point);
		candraw = true;
		}
	}else
	if(figure=="DimA")
	{
		vector<CVector> test;
		if(nbc==0)
		{
			CLine pl;
			CRectangle pR;
			for(int i=0;i<fit;i++)
			{
				if((fig[i]->getName()==pl.getName())||(fig[i]->getName()==pR.getName()))
				{
				test=fig[i]->getSelectvec(point);
				if(!test.empty())
				{
					if(test[0]!=test[2])
					{
						if(!valid)
						{
						string scount;
						CString f;
						f.Format(_T("%d"),count);
						scount=f;
						vhan.push_back(scount);
						fig.resize(fig.size()+1);
						fig[fit]=new CDim;
						fit++;
						sfit++;
						count++;
						((CDim*)fig[fit-1])->setstyle(figure);
						fig[fit-1]->setPtsBegin(point);
						((CDim*)fig[fit-1])->addSL(test);
						nbc++;
						}
					break;
					}
				}
				}
			}
		}
		else
		if(nbc==1)
		{
			CLine pl;
			CRectangle pR;
			for(int i=0;i<fit-1;i++)
			{
				if((fig[i]->getName()==pl.getName())||(fig[i]->getName()==pR.getName()))
				{
				test=fig[i]->getSelectvec(point);
				if (test.empty()) continue;
				if(test[0]!=test[2])
				{
				((CDim*)fig[fit-1])->addSL(test);
				((CDim*)fig[fit-1])->getCharge(hdc);
				test.clear();
				nbc=0;
				fig[fit-1]->draw(hdc);

				string scount;
				CString f;
				f.Format(_T("%d"),count);
				scount=f;
				fig[fit-1]->setHandle(scount);
				fig[fit-1]->setLayer(currlayer);
				fig[fit-1]->setcorevecor();
				candraw=true;
				valid = true;
				Bminus=true;
				break;
				}
				}
			}
		}

	}else
	if(figure=="Chamfer")
	{
		vector<CVector> test;
		if(nbc==0)
		{

			for(int i=0;i<fit;i++)
			{
				CRectangle pR;
				CLine pL;
				CQLine pQ;
				if((fig[i]->getName()==pL.getName())||(fig[i]->getName()==pR.getName())||(fig[i]->getName()==pQ.getName()))
				{
					test=fig[i]->getSelectvec(point);
					if(test.size()!=0)
					{
						if(test[0]!=test[2])
						{
						/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
						sfit++;
						IA=new CDimA;
						IA->addSLChamf(test,fig[i]);
						nbc++;
						break;
						}
					}
				}
			}
		}
		else
		if(nbc==1)
		{
			for(int i=0;i<fit;i++)
			{
				CRectangle pR;
				CLine pL;
				CQLine pQ;
				if((fig[i]->getName()==pL.getName())||(fig[i]->getName()==pR.getName())||(fig[i]->getName()==pQ.getName()))
				{
				test=fig[i]->getSelectvec(point);
					if(test.size()!=0)
					{
						if(test[0]!=test[2])
						{
			
						IA->addSLChamf(test,fig[i]);
						forundo(i,"delete");
						CFigure* lk=IA->getChargeChamf();
							if(lk!=0)
							{
							CLine* llg=new CLine(lk->Vector(0),lk->Vector(1));
//							llg->createobj(lk->ptbegin,lk->ptend);
							llg->clear();
							llg->setInit();
							string scount;
							CString f;
							f.Format(_T("%d"),count);
							scount=f;
							llg->setHandle(scount);
							llg->setLayer(currlayer);
							llg->setcorevecor();
							vhan.push_back(scount);

							fig.resize(fig.size()+1);
							fig[fit]=llg;
							forundo(fit,"create line");
							fit++;

							sfit++;
							count++;
							Bminus=true;

							}
						delete lk;
						delete IA;

						nbc=0;
						valid=true;
						candraw=true;
						break;
						}
					}
				}
			}
		}

	}else
	if(figure=="Fillet")
	{
		vector<CVector> test;
		if(nbc==0)
		{

			for(int i=0;i<fit;i++)
			{
				CRectangle pR;
				CLine pL;
				CQLine pQ;
				if((fig[i]->getName()==pL.getName())||(fig[i]->getName()==pR.getName())||(fig[i]->getName()==pQ.getName()))
				{
					test=fig[i]->getSelectvec(point);
					if(test.size()!=0)
					{
						if(test[0]!=test[2])
						{
							/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
							vhan.push_back(fig[i]->gethandle());
							sfit++;
							IA=new CDimA;
							IA->addSLChamf(test,fig[i]);
							nbc++;
							break;
						}
					}
				}
			}
		}
		else
		if(nbc==1)
		{
			for(int i=0;i<fit;i++)
			{
				CRectangle pR;
				CLine pL;
				CQLine pQ;
				if((fig[i]->getName()==pL.getName())||(fig[i]->getName()==pR.getName())||(fig[i]->getName()==pQ.getName()))
				{
				test=fig[i]->getSelectvec(point);
				if(test.size()!=0)
				{
					if(test[0]!=test[2])
					{
						forundo(i,"Memento");
						IA->addSLChamf(test,fig[i]);
						CCercle* lk=new CCercle;
						bool ko=IA->getChargeFilt(lk);
						delete IA;
						if(ko)
						{
							/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
							sfit++;
							lk->clear();
							lk->setInit();
							string scount;
							CString f;
							f.Format(_T("%d"),count);
							scount=f;
							lk->setHandle(scount);
						//	undoList.push("create");
							lk->setLayer(currlayer);
							lk->setcorevecor();

							/*vhan[sfit]=count;*/vhan.push_back(scount);

							fig.resize(fig.size()+1);
							fig[fit]=lk;
							forundo(fit,"create arc");
							fit++;
							sfit++;
							count++;
							Bminus=true;

						}
						else
						{
							delete lk;
						}
					nbc=0;
					valid=true;
					candraw=true;
					break;
					}
				}
				}
			}
		}
	}else
	if(figure=="2CLine")
	{
		vector<CVector> test;
		if(nbc==0)
		{

			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getName()=="CCercle")
				{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
				IA=new CDimA;
				IA->addSLChamf(test,fig[i]);
				nbc++;
				break;
				}
				}
			}
		}
		else
		if(nbc==1)
		{
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getName()=="CCercle")
				{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
					IA->addSLChamf(test,fig[i]);
					CLine* lk=new CLine;
					bool ko=IA->getCharge2CLine(lk);
					delete IA;
					if(ko)
					{
						fig[fit]=lk;
						fit++;
					}
					else
					{
						delete lk;
					}
				nbc=0;
				valid=true;
				break;
				}
				}
			}
		}
	}else

	if(figure=="QLine")
	{	
		CPoint p=point;
		CPoint p1=p;
		p1.y+=1;
		pQLine.setstyle("qline");
		pQLine.setRefRay(CVector(p),CVector(p1));
		pQLine.setPtsBegin(point);

	}else
	if(figure=="QPLine")
	{
		pQLine.setstyle("qpline");
		pQLine.setPtsBegin(point);
		for(int i=0;i<fit;i++)
		{
			if(fig[i]->transselectedstate())
			{
		      if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
			  {

//				fig[i]->setLcolor(hdc,PALETTEINDEX(150),PALETTEINDEX(10));
				pQLine.setRefRay(fig[i]->selectvec[0],fig[i]->selectvec[2]);
				break;
			  }
			}
		}
	}else
	if(figure=="QTLine")
	{
		for(int i=0;i<fit;i++)
		{
	      if(fig[i]->getName()==pCircle.getName())
		  {
			if(fig[i]->PtinRegion(point))
			{
//				fig[i]->setLcolor(hdc,PALETTEINDEX(150),PALETTEINDEX(10));
				pQLine.setstyle("qtline");
				pQLine.setRefRay(fig[i]->selectvec[0],fig[i]->selectvec[1]);
				pQLine.setPtsBegin(fig[i]->selectvec[1]);

				break;
			}
		  }
		}
	}else
	if(figure=="Bezier")
	{	
		pBezier->setPtsBegin(point);
		endDraw=true;
	}else
	if(figure=="Text")
	{
		textcad=new CTextCad;
//		textcad->setview(render->view);
		textcad->setPtsBegin(point);
	}else
	if (figure=="Rectangle")
	{
		pRectangle.setPtsBegin(point);
	}else

	if ((figure=="Circle")||(figure=="2DotCircle")||(figure=="3DotCircle")||(figure=="Ellipse"))
	{
		pCircle.setPtsBegin(point);
	}
	else
	if ((figure=="Arc")||(figure=="2DotArc")||(figure=="3DotArc")||(figure=="3DotArc2"))
	{
		pArc.setPtsBegin(point);
	} 
}

void CDraw::finaladd( CDC *hdc,CString figure, CVector pos2,CString option)
{

//	CBezier vert;
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
	if(((figure=="select")||(figure=="spoint"))&&(!endDraw))
	{
	bool sel=false;
	int g=vs.size();
	candraw=false;
//	if(!g) candraw=false;
			CAABB box;
			CLibS pl;

			if((g>0)&&(vs[0]->getMultselect()))
			{
				box.empty();
				for (int i=0;i<g;i++)
				{
//					vs[i]->getCharge(hdc);
					box.add(vs[i]->getbox(hdc));
				}
				for (i=0;i<g;i++)
				{
					vs[i]->setbox(box);
					vs[i]->setRotateCenter(box.center());
					vs[i]->setMultselect(true);
				}
			}
			else if((g==1)&&(vs[0]->getName()==pl.getName()))
			{
				vs[0]->getbox(hdc);
			}

	for (int i=0;i<g;i++)
	{
		bool b=vs[i]->getMultselect();
		vs[i]->setclick(true);
		vs[i]->setup(true);
		SELECT b1=vs[i]->getselectmode();
		if(b1!=pnt)
			vs[i]->setselectmode(full);
		vs[i]->selectSM(hdc);
		if(vs[i]->getName()!="CDim")
			vs[i]->getCharge(hdc);
		vs[i]->setup(true);
		vs[i]->setclick(true);
		if(b1==pnt)
			vs[i]->setselectmode(b1);
		else
			vs[i]->setselectmode(full);
		vs[i]->setMultselect(b);
		vs[i]->selectSM(hdc);
	}
/*		if(!prevsbox.isEmpty() && !(prevsbox==&vs[0]->box))
		{
			grid(hdc,prevsbox);
		}
		if(curr_fig!=NULL)
		{
			CTextCad txt;
		if(curr_fig->getName()==txt.getName())
		{
			CTextCad* txt=(CTextCad*)curr_fig;
			txt->InitZoom();
//			grid(hdc,txt->box);
//			txt->draw(hdc);
			candraw=true;
		}
		CDimL dlxt;
		CDim dxt;
		CBezier bxt;
		if((curr_fig->getName()==dlxt.getName())||(curr_fig->getName()==dxt.getName())||(curr_fig->getName()==bxt.getName()))
		{
//			CTextCad* txt=(CTextCad*)curr_fig;
//			txt->InitZoom();
//			grid(hdc,txt->box);
//			txt->draw(hdc);
			candraw=true;
		}
		}*/
		candraw=true;
	}
	if (endDraw)
	{
		candraw=true;
	if(snap) fsnapPoint(pos2,hdc);
	v_current =pos2;
		if(figure=="Line")
		{
		pLine.create(pos2);
		if (pLine.getCharge())
		{
//		pLine.draw(hdc);
		CLine *ftp= new CLine;
		
		pLine.clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		pLine.setHandle(scount);
		pLine.setLayer(currlayer);
		pLine.setcorevecor();
		ftp->copy(&pLine);
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;
		forundo(fit,"create line");
		fit++;
		sfit++;
		count++;
		Bminus=true;
	//	pLine.initL();
		}
		else
		{
//		pLine.draw(hdc);
		fig[fit-1]->copy(&pLine);
		pLine.setcorevecor();
		forundo(fit-1,"create update line");
		}
		}
		if(figure=="QLine")
		{
		pQLine.create(pos2);
		if (pQLine.getCharge())
		{
		CQLine *ftp= new CQLine;
		pQLine.clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		pQLine.setHandle(scount);
		pQLine.setLayer(currlayer);
		pQLine.setcorevecor();
		ftp->copy(&pQLine);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		forundo(fit,"create line");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		}
		else
		{
		fig[fit-1]->copy(&pQLine);
		pQLine.setcorevecor();
		forundo(fit-1,"create update line");
		}
		}
		else
		if(figure=="Bezier")
		{
		pBezier->create(pos2);
		if (pBezier->getCharge(hdc))
		{
		pBezier->clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		pBezier->setHandle(scount);
		pBezier->setLayer(currlayer);
		pBezier->setcorevecor();
	
		//*ftp1=pBezier;
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=new CBezier;//ftp1;
	
		fig[fit]->copy(pBezier);	
		forundo(fit,"create spline");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pBezier->initL();
		}
		else
		{
		delete fig[fit-1];
		fig[fit-1]=new CBezier;//btp;
		fig[fit-1]->copy(pBezier);
		fig[fit-1]->setcorevecor();
		forundo(fit-1,"create update spline");
		return;
		}
		}else
		if(figure=="Box")
		{
		
		}else
		if(figure=="Plane")
		{
		pRectangle.create(pos2);
		if(pRectangle.getCharge())
		{
		fig.resize(fig.size()+1);
		fig[fit]=new CBezier;
		((CBezier*)fig[fit])->plane(&pRectangle);
		fig[fit]->surface(hdc);
		
		fig[fit]->clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		fig[fit]->setHandle(scount);
		fig[fit]->setLayer(currlayer);
		vhan.push_back(scount);
		forundo(fit,"create");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pRectangle.initL();
		}	
		}else
		if(figure=="Rectangle")
		{
		pRectangle.create(pos2);
		if(pRectangle.getCharge())
		{
		CRectangle *ftp= new CRectangle;
		pRectangle.clear();
		pRectangle.setHandle(scount);
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		ftp->copy(&pRectangle);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		forundo(fit,"create rectangle");
		fit++;
		sfit++;
		count++;
		Bminus=true;
//		pRectangle.initL();
		}
		}else
		if(figure=="Image")
		{
		image.create(pos2);
		if(image.getCharge())
		{
		if(image.LoadBitmap(hdc))
		{
//		image.draw(hdc);
		CImage *ftp= new CImage;
		image.clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		image.setHandle(scount);
		image.setLayer(currlayer);
		image.setcorevecor();
		ftp->copy(&image);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
//		forundo(fit,"create");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		image.initL();
		}
		}
		}else
		if((figure=="DimD")||(figure=="DimR"))
		{
			if(valid)
			{
				valid = false;
				candraw =false;
				forundo(fit-1,"create dimd");
			}
		}else
		if(figure=="DimA")
		{
			if(valid)
			{
				valid = false;
				candraw =false;
				forundo(fit-1,"create dima");
			}
		}else
	if((figure=="multline")||(figure=="leader")||(figure=="DimV")||(figure=="DimH")||(figure=="DimF"))
		{
		if(!valid)
		{
		if(((CDim*)fig[fit-1])->isReady())
		{
			vector<CFigure*> fb,fe;
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->inBox(pos2))
					fb.push_back(fig[i]);
			}
			int t=fb.size();
			vector<CVector> test;
			CVector v=pos2,vl=pos2;
			fig[fit-1]->fsnap(v,vl,"endpoint",hdc);

			for(i=0;i<t;i++)
			{
					test=fig[i]->getSelectvec(pos2);
					if(test.size()!=0)
						if(test[0]!=test[2])
						{
							fig[fit-1]->setInterest(fig[i]);
							((CDim*)fig[fit-1])->drivingParam(fig[i],test);
						}
			}
		fig[fit-1]->create(vl);
		((CDim*)fig[fit-1])->getCharge(hdc);
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		fig[fit-1]->setHandle(scount);
		fig[fit-1]->setLayer(currlayer);
		fig[fit-1]->setcorevecor();
		fig[fit-1]->draw(hdc);
		forundo(fit-1,"create dim");
		Bminus=true;
		if(figure!="leader")
		{
		valid = true;
		}
			}
		}
		else
		{
			valid = false;
			candraw =false;
			if(figure=="leader")
				((CDim*)fig[fit-1])->getCharge(hdc);
		}
		}else		
		if((figure=="DimL")||(figure=="DimLH")||(figure=="DimLV"))
		{
		if(!valid)
		{
		if(((CDimL*)fig[fit-1])->isReady())
		{
		fig[fit-1]->create(pos2);
		((CDimL*)fig[fit-1])->getCharge(hdc);
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		fig[fit-1]->setHandle(scount);
		fig[fit-1]->setLayer(currlayer);
		fig[fit-1]->setcorevecor();
		fig[fit-1]->draw(hdc);
		forundo(fit-1,"create diml");
		Bminus=true;
		valid = true;
			}
		}
		else
		{
			valid = false;
			candraw =false;
		}
		}else
		if(figure=="Text")
		{
	//	textcad->initL();
		textcad->create(pos2);
		textcad->getCharge();
		
		CTextCad *ftp= new CTextCad;
		textcad->clear();
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;
		textcad->setHandle(scount);
		textcad->IsOn();
		textcad->setLayer(currlayer);

		ftp->copy(textcad);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		forundo(fit,"create text");
//		ftp->assign(hdc,CVector(0,0),"Hello");
		curr_fig=ftp;

		fit++;
		sfit++;
		count++;
		Bminus=true;
		}else
		if((figure=="select")&&(bck==true))
		{
		int as=0;
		slib;
		pSelect.create(pos2);
		pSelect.setClstate(false);
		pSelect.getCharge();
		pSelect.draw(hdc);

			for (int i=0;i<fit;i++)
			{

				if(!(fig[i]->getLayer()).clear)
				{
					CInter pInter;
					if(pInter.inReg(fig[i],&pSelect))
					{
					fig[i]->setMultselect(true);

					vs.push_back(fig[i]);
					}
				}
			}
			int fit0=vs.size();
			CAABB box;
			for (i=0;i<fit0;i++)
			{
				box.add(vs[i]->getbox());
			}
			for (i=0;i<fit0;i++)
			{
				vs[i]->setbox(box);
				vs[i]->setRotateCenter(box.center());
				vs[i]->Select(hdc,pos2);
			}


		bck=false;
		if(hdc->GetROP2()!=R2_NOTXORPEN)
		{
		hdc->SetROP2(R2_NOTXORPEN);
		}
		pSelect.draw(hdc);
		candraw=false;
		}
		else
		if((figure=="Circle")||(figure=="2DotCircle"))
		{
		pCircle.setType("Circle");
		pCircle.addtovec(hdc);
		CCercle *ftp= new CCercle;
		pCircle.clear();
		pCircle.setHandle(scount);
		pCircle.setLayer(currlayer);
		pCircle.setcorevecor();

		ftp->copy(pCircle);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		forundo(fit,"create circle");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pCircle.initL();
		}
		else
		if(figure=="2DotArc")
		{
		pArc.setType("2DotArc");
		pArc.addtovec(hdc);
		CCercle *ftp= new CCercle;
		pArc.clear();
		pArc.setHandle(scount);
		pArc.setLayer(currlayer);
		pArc.setcorevecor();

		ftp->copy(pArc);
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		forundo(fit,"create 2p arc");
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pArc.initL();
		}

	endDraw=FALSE;
	}
    	if(figure=="3DotCircle")
		{
			if (pCircle.getCharge())
			{
			pCircle.setType("Circle");
			pCircle.addtovec(hdc);
			CCercle *ftp= new CCercle;
			pCircle.clear();
			pCircle.setHandle(scount);
			pCircle.setLayer(currlayer);
			pCircle.setcorevecor();

			ftp->copy(pCircle);
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=ftp;
			forundo(fit,"create circle");
			fit++;
			sfit++;
			count++;
			Bminus=true;
			pCircle.initL();
			}

		}
    	if(figure=="Ellipse")
		{
			if (pCircle.getCharge())
			{
			pCircle.setType("Ellipse");
			pCircle.addtovec();
			CCercle *ftp= new CCercle;
			pCircle.clear();
			pCircle.setHandle(scount);
			pCircle.setLayer(currlayer);
			pCircle.setcorevecor();
			ftp->copy(pCircle);
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=ftp;
			forundo(fit,"create ellipse");
			fit++;
			sfit++;
			count++;
			Bminus=true;
			pCircle.initL();
			}

		}
		if((figure=="3DotArc")||(figure=="3DotArc2")||(figure=="Arc"))
		{
			if (pArc.getCharge())
			{
			if(figure=="3DotArc") 	pArc.setType("3DotArc");
			if(figure=="3DotArc2") 	pArc.setType("3DotArc2");
			if(figure=="Arc") 		pArc.setType("Arc");
			pArc.addtovec(hdc);
			CCercle *ftp= new CCercle;
			pArc.clear();
			pArc.setHandle(scount);
			pArc.setLayer(currlayer);
			pArc.setcorevecor();

			ftp->copy(pArc);
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=ftp;
			forundo(fit,"create arc");
			fit++;
			sfit++;
			count++;
			Bminus=true;
			pArc.initL();
			}

		}

}
void CDraw::cleardraw(CDC* hdc)
{
	int j=vs.size();
		CAABB sbox;
		for(int i=0;i<j;i++)
		{
			sbox.add(vs[i]->box);
		}
		if(!prevsbox.isEmpty())
			grid(hdc,prevsbox);
		grid(hdc,sbox);
		prevsbox=sbox;
}
bool CDraw::select(bool spoint,int multiselect,CVector point,CDC *hdc)
{
/////////////////////////////////////////////////////////////////////////
/// Partie selection base sur machine selectSM dans line.cpp
///Reste a faire la selection avec le rectangle
//////////////////////////////////////////////////////////////////////////

/*	for (int  i=0;i<fit;i++) 
		{
			fig[i]->selectMP(point);
		}
/**************************************************************/
	
	if(snap) fsnap(point,hdc);
	v_current =point;


	int pj=vs.size();
	bool locale=false;

	bool c=false;
	for (int i=0;i<sefit;i++) 
	{
		if(!spoint)
		{
			if((sfig[i]->getLayer()).on)
			{
             bool g=sfig[i]->PtinRegion(point);;
			 c|=g;
			}
		}else
		{
			if((sfig[i]->getLayer()).on)
			{
			c|=sfig[i]->PtinNode(point,multiselect);
			}
		}
	}
	if(!c)
	{
	for (i=0;i<sefit;i++) 
	{
		if((sfig[i]->getLayer()).on)
		{
		sfig[i]->setMultselect(false);
		}
	}
	sefit=0;

	}
	for ( i=0;i<fit;i++) 
		{
		if(fig[i]->ptbegin.size()!=0)
		{
		if((fig[i]->getLayer()).on)
		{

			if(fig[i]->getRotstate())
			{
				fig[i]->InitRotState();
				fig[i]->setMultselect(false);
			}
		}
		}
		}
//	vector<CFigure*> vs;
	DWORD tick=GetTickCount();
	CAABB p_box;
	CTextCad textc;
	p_box.add(point);
	p_box.inflate(50);
	for(i=0;i<fit;i++)
	{
		if((fig[i]->getLayer()).on)
		{
//		if(!(fig[i]->getLayer()).lock)
		{
			if(!sc_box.intersectAABB2(fig[i]->box)) continue;
			if(spoint)
			{
			   B=fig[i]->PtinNode(point,multiselect);
			}
			else
			{
			if(!p_box.intersectAABB2(fig[i]->box))
			{
				if(fig[i]->getName()==textc.getName())
					fig[i]->PtinRegion(point);
				continue;
			}
			B=fig[i]->PtinRegion(point);
			if(B) 
			{
				if(find(vs.begin(),vs.end(),fig[i])==vs.end())
				vs.push_back(fig[i]);
			}
			fig[i]->selectSM(hdc);
			}
			locale|=B;
		}
	}
	}
	DWORD ptick=GetTickCount()-tick;
	CString s;
	s.Format("time spend to Select:%d \n",ptick);
	TRACE(s);
	
	int j=vs.size();
	if(!locale)
	{
		CAABB sbox;
		for(i=0;i<j;i++)
		{
			vs[i]->setMultselect(false);
			vs[i]->setclick(false);
			vs[i]->selectSM(hdc);
			vs[i]->getLayer().lock;
		    vs[i]->getLayer().clear;
			sbox.add(vs[i]->getbox());
		}
//		if(!prevsbox.isEmpty())
//			grid(hdc,prevsbox);
//		grid(hdc,sbox);
		vs.clear();
	}else
	{
		CAABB sbox;
		for(i=0;i<j;i++)
		{
			sbox.add(vs[i]->box);
		}
		prevsbox=sbox;
	}
	
	j=vs.size();
	if(j>1){
	for(i=0;i<j;i++)
	{
		SELECT _st=vs[i]->getselectmode();
		if(_st==st)
		{
		int _rt=vs[i]->getrecselect();
		CVector _rot=vs[i]->getRotateCenter();
		for(i=0;i<j;i++)
		{
			vs[i]->setselectmode(st);
			vs[i]->setrecselect(_rt);
			vs[i]->setRotateCenter(_rot);
		}
		break;
		}
	}
	for(i=0;i<j;i++)
	{
		vs[i]->setMultselect(true);
		vs[i]->setclick(true);
		vs[i]->selectSM(hdc);
//		vs[i]->getLayer().lock;
//		vs[i]->getLayer().clear;
	}
	}
//	if(pj!=j) candraw=true;
    getBinfo(point);
			
	Bminus=locale;

	bck=false;
	
	return candraw;
}


void CDraw::displayselect(CDC *hdc)
{
/*			CAABB box;
			int g=vs.size();
			for (int i=0;i<g;i++)
			{
				box.add(vs[i]->getbox());
			}
			for (i=0;i<g;i++)
			{
				vs[i]->setbox(box);
			}
			}
*/
}

bool CDraw::translate(CWnd *wnd,CDC *hdc,CVector PrevPos,CVector PostPos,int key)
{
	bool sel=false;
	int g=vs.size();
			CAABB box;
			if((g>0)&&(vs[0]->getMultselect()))
			{
			for (int i=0;i<g;i++)
			{
				box.add(vs[i]->getbox());
			}
			for (i=0;i<g;i++)
			{
				vs[i]->setbox(box);
			}
			}
	for (int i=0;i<g;i++)
	{
		vs[i]->setMove(true);
		sel=true;
		if(key==0)
			vs[i]->translate(wnd,hdc,PrevPos,PostPos);//mouse.getPrevPos(),mouse.getPostPos());
		else
		{
		vs[i]->keytranslate(wnd,hdc,key);//mouse.getPrevPos(),mouse.getPostPos());
		}
		change=true;
	}
	getBinfo(PostPos);
		mouse.setPrevPos(mouse.getPostPos());

		return sel;
}
bool CDraw::translatecam(int sens,CVector prevpoint,CVector postpoint)
{
	bool sel=true;

/*	CVector v1=PostPos-PrevPos,v;

//	v.setcamor(v1);
	CVector v00(0,0,0,1);
	CVector cen=v.getcamor();
	v.assign(v00,cen);
	Translate(v);

	Translate(v1);

	v.assign(cen,v00);
	Translate(v);
	VendT();*/
	cam.Translate(sens,prevpoint,postpoint);
	
	mouse.setPrevPos(mouse.getPostPos());
	candraw=true;
	return sel;
}
void CDraw::translatecam(CVector v)
{
	cam.Translate(v);
}

void CDraw::rotatecam(int sens,CVector prevpoint,CVector postpoint,bool b)
{
///////////////////////////////////////////////////////////////////////////
/// Partie rotation; travaille restant a faire:
/// controler les variables d'angle et ajouter les tangentes
/// mieux controler le curseur 
///	************pourquoi ne pas faire un logiciel se mouvant dans la memoire  
/// comme un vers;
//////////////////////////////////////////////////////////////////////////
/*    CVector v;
	double alphab=v.argu(postpoint)-v.argu(prevpoint);//-argu(piv);
//	alphab=pi/2;

	CVector v00(0,0,0,1);
	CVector cen=v.getcamor();
	v.assign(v00,cen);
	Translate(v);

	if(sens==1)
	{
	TRotatex(alphab);
	}else
	if(sens==2)
	{
	TRotatey(alphab);
	}
	else
	{
	TRotate(alphab);
	}
	v.assign(cen,v00);
	Translate(v);
	VendT();*/
	cam.Rotate(sens,prevpoint,postpoint,b);

	mouse.setPrevPos(mouse.getPostPos());
		
}

void CDraw::rotatecam(int sens, float angle,bool b)
{
///////////////////////////////////////////////////////////////////////////
/// Partie rotation; travaille restant a faire:
/// controler les variables d'angle et ajouter les tangentes
/// mieux controler le curseur 
///	************pourquoi ne pas faire un logiciel se mouvant dans la memoire  
/// comme un vers;
//////////////////////////////////////////////////////////////////////////
	CVector v00(0,0,0,1);
	setCenter(v00);
	cam.Rotate(sens,angle,b);
	
}


void CDraw::rotate(CDC *hdc,int sens,CVector prevpoint,CVector postpoint)
{
///////////////////////////////////////////////////////////////////////////
/// Partie rotation; travaille restant a faire:
/// controler les variables d'angle et ajouter les tangentes
/// mieux controler le curseur 
///	************pourquoi ne pas faire un logiciel se mouvant dans la memoire  
/// comme un vers;
//////////////////////////////////////////////////////////////////////////

	
	bool change=false;
	
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		vs[i]->setRotClick(true);
		vs[i]->setMultselect(true);
		change=vs[i]->rotateSM(hdc,sens,prevpoint,postpoint,false);
	 } 
	getBinfo(postpoint);

	mouse.setPrevPos(mouse.getPostPos());
		
}
void CDraw::scale(CDC *hdc,int sens,CVector prevpoint,CVector postpoint)
{
///////////////////////////////////////////////////////////////////////////
/// Partie rotation; travaille restant a faire:
/// controler les variables d'angle et ajouter les tangentes
/// mieux controler le curseur 
///	************pourquoi ne pas faire un logiciel se mouvant dans la memoire  
/// comme un vers;
//////////////////////////////////////////////////////////////////////////

	
	bool change=false;
	
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		vs[i]->setRotClick(true);
		vs[i]->setMultselect(true);
		change=vs[i]->rotateSM(hdc,sens,prevpoint,postpoint,true);
	 } 
	getBinfo(postpoint);

	mouse.setPrevPos(mouse.getPostPos());
		
}

bool CDraw::copyl(CDC *hdc, CVector point,bool cp)
{
//////////////////////////////////////////////////////////////////////
// Perform the mirroring of an element;
// what need to be done: control the parameter to customize the action;
////////////////////////////////////////////////////////////////////////

	CInter pInt;
	CCercle pC;
	CTextCad textc;
	CLibS pl;
	CLibS *pLib=NULL;//=new CLibS;
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;


	int pk=fit;
	bool sel=false;

	for(int i=0;i<fit;i++)
	{

		if (fig[i]->getName()==pLine.getName())
		{
			if (fig[i]->PtinRegion(point))
			{

				for (int j=0;j<fit;j++) 
				{
					if (fig[j]->inselectedstate())
					{
						fig[j]->setHandle(scount);
						undoList.push("create");
						vhan.push_back(scount);
						sfit++;
						count++;
						fig[j]->setMultselect(false);
						CFigure* ftp=fig[i]->copybyL(fig[j]);

						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
						vhan.push_back(scount);
						sfit++;
						count++;

						fig.resize(fig.size()+1);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}

					}
				}
			}
		}
	}

	candraw=true;
	fit=pk;
	return sel;
}

bool CDraw::mirrorselect(CDC *hdc,CVector point,bool cp)
{
//////////////////////////////////////////////////////////////////////
// Perform the mirroring of an element;
// what need to be done: control the parameter to customize the action;
////////////////////////////////////////////////////////////////////////

	CInter pInt;
	CCercle *pC;
	CTextCad textc;
	CLibS pl;
	CLibS *pLib=NULL;//=new CLibS;
		string scount;
		CString f;
		f.Format(_T("%d"),count);
		scount=f;


	int pk=fit;
	bool sel=false;

	for(int i=0;i<fit;i++)
	{

		if (fig[i]->getName()==pLine.getName())
		{
			if (fig[i]->PtinRegion(point))
			{

			for (int j=0;j<fit;j++) 
				{
					if (fig[j]->inselectedstate())
					{
						fig[j]->setHandle(scount);
						undoList.push("create");
						vhan.push_back(scount);
						sfit++;
						count++;
						fig[j]->setMultselect(false);
						CFigure* ftp=fig[i]->mirror(hdc,fig[j]);

						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
						vhan.push_back(scount);
						sfit++;
						count++;

						fig.resize(fig.size()+1);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}

					}
				}
			}
		}
	}

	candraw=true;
	fit=pk;
	return sel;
}


void CDraw::selectRotateCenter(CDC *hdc,CVector prevpoint,CVector postpoint)
{

	int g=vs.size();

	for (int i=0;i<g;i++)
	{
			vs[i]->setRotClick(true);
			 vs[i]->rotateSM(hdc,0,prevpoint,postpoint,false);
	}
	
	mouse.setPrevPos(mouse.getPostPos());

}

void CDraw::movepoint(CDC *hdc, CVector point)
{

}

bool CDraw::addnode(CVector point,CDC* hdc)
{
	bool b=false;
	CTextCad tex;
	if(vs.size()!=1) return false;
	if(vs[0]->getName()==tex.getName()) return false;
	vs[0]->addnode(point,hdc);
	return true;

}

bool CDraw::deletenode(CVector point, CDC *hdc)
{
	CTextCad tex;
	if(vs.size()!=1) return false;
	if(vs[0]->getName()==tex.getName()) return false;
	vs[0]->deletenode(point,hdc);
	return true;

}

bool CDraw::breakcurve(CVector point)
{
 if(vs.size()!=1) return false;
 	static vector<CVector> vp;
	vector<CVector> cp;
	cp=vs[0]->getSelectvec(point);
	if(!cp.empty())
		vp.push_back(cp[1]);
	if(vp.size()==2)
	{
		vector<CFigure*> figh;
		figh=vs[0]->breakcurve2(vp[0],vp[1]);
		vp.clear();
		if(figh.size()!=0)
		{
		forundo(vs[0],"delete");
		fig.erase(find(fig.begin(),fig.end(),vs[0]));
		vs.clear();;
		fit--;
		int jfit=figh.size();
		for(int j=0;j<jfit;j++)
		{
			create(figh[j]);
		}
		return true;
		}

	}
	return false;
}
bool CDraw::pointconstraint(CVector point)
{
 if(vs.size()==0) return false;
 	static vector<CVector> vp;
	vector<CVector> cp;
	static vector<pair<CFigure*,int> > vp1;
	int i=-1;
	static int icp=0;
	int j=vs.size();
	int i1;
	for(i1=0;i1<j;i1++)
	{
	vs[i1]->PtinNode2(point,i);
	if(i!=-1)
	{
//		CVector v=cp[3];
//		float i=((v.z-v.x)<(v.y-v.z))?v.x:v.y;
///		int i1=(i==v.x)?0:2;
//		vp.push_back(cp[i1]);
		vs[i1]->setConstrainedPoint(i);
		vp1.push_back(make_pair(vs[i1],i));

		icp++;
		break;
	}
	}
	if(icp==2)
	{
//		vector<CFigure*> figh;
		vs[i1]->pointconstraint(vp1[0],vp1[1]);
		icp=0;
//		vp.clear();
		vp1.clear();
		return true;
/*		if(figh.size()!=0)
		{
		forundo(vs[0],"delete");
		fig.erase(find(fig.begin(),fig.end(),vs[0]));
		vs.clear();;
		fit--;
		int jfit=figh.size();
		for(int j=0;j<jfit;j++)
		{
			create(figh[j]);
		}
		return true;
		}
*/
	}
	return false;
}
bool CDraw::vectorconstraint(CVector point,int mode)
{
 if(vs.size()==0) return false;
 	static vector<CVector> vp;
	vector<CVector> cp;
	static vector<pair<CFigure*,int> > vp1;
	int i=-1;
	static int icp=0;
	int j=vs.size();
	int i1;
	for(i1=0;i1<j;i1++)
	{
	vs[i1]->PtinEdge(point,i);
	if(i!=-1)
	{
		vs[i1]->setConstrainedEdge(i);
		vp1.push_back(make_pair(vs[i1],i));

		icp++;
		break;
	}
	}
	if((icp==2)&&(mode==-1))
	{
//		vector<CFigure*> figh;
		vs[i1]->edgeconstraint(vp1[0],vp1[1]);
		icp=0;
//		vp.clear();
		vp1.clear();
		return true;
	}
	if((icp==1)&&(mode==0))
	{
//		vector<CFigure*> figh;
		vs[i1]->edgehorizontalconstraint(vp1[0]);
		icp=0;
//		vp.clear();
		vp1.clear();
		return true;
	}
	if((icp==1)&&(mode==1))
	{
//		vector<CFigure*> figh;
		vs[i1]->edgeverticalconstraint(vp1[0]);
		icp=0;
//		vp.clear();
		vp1.clear();
		return true;
	}
	if((icp==2)&&(mode==2))
	{
//		vector<CFigure*> figh;
		vs[i1]->edgeperpendicularconstraint(vp1[0],vp1[1]);
		icp=0;
//		vp.clear();
		vp1.clear();
		return true;
	}
	return false;
}

bool CDraw::closecurve(CVector point,CDC *hdc)
{
	bool b=false;
	CTextCad textc;
/*	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=textc.getName()))
		{
			fig[i]->closecurve(point,hdc);
			fig[i]->setInit();
			b=true;
			
		}
//	}
	}*/
		CLine pL;
		CRectangle pR;
		CCercle pC;
		CBezier pB;
		CLibS pli;
		CImage image;
		
	int pk=fit,l=vs.size();
	
		for(int i=0;i<l;i++)
		{
//			if(fig[i]->transselectedstate())
			{
						
				if((vs[i]->getName()==pL.getName())\
					||(vs[i]->getName()==pR.getName())\
					||(vs[i]->getName()==pli.getName()))
				{
					vs[i]->closecurve(point,hdc);
					vs[i]->setInit();
					b=true;
				}else
				if((vs[i]->getName()==pC.getName())\
					||(vs[i]->getName()==pB.getName())\
					)
				{
					vs[i]->closecurve(point,hdc);
/*					CSpline *spline=new CSpline;
					spline->sethandle(fig[i]->gethandle());
					undoList.push("create");
	//				spline->setUndoparam();
					spline->add(fig[i]);
					spline->closecurve();
					fig[i]=spline;*/
					b=true;
				}		
			}
	}
		fit=pk;
	return b;
}

void CDraw::copyf()
{
/*	Line_copied=selected_Lines;
	Cercle_copied=Cercleselected;
	Rectangle_copied=Rectangleselected;

	selected_Lines.clear();
	Rectangleselected.clear();
	Cercleselected.clear();*/
}

bool CDraw::getselect()
{
	return Bminus;

}

void CDraw::cut(CDC *hdc)
{
	copy();
	deleteObject(hdc);
}

void CDraw::pastearray(CDC *hdc, bool of,int nbrow,int nbcol,double distx,double disty,int nblevel,double lspacing)
{

	CInter pInter;
	vector<CFigure*> arr;
	vector<CFigure*>::iterator fiter;

	int pk=vs.size();
	if(nbrow<=1 && nbcol<=1) return;
	for (int i=0;i<pk;i++)
	{

//		if (fig[i]->inselectedstate())
		{
			arr=vs[i]->translatepArray(of,nbrow,nbcol,distx,disty,nblevel,lspacing);
			vs[i]->setMultselect(false);
			for(fiter=arr.begin();fiter!=arr.end();fiter++)
			{
				create(*fiter);
			}
		}
	}

	candraw=true;

	

}


void CDraw::paste(CDC *hdc, CVector point)
{
	CFigure* arr;

	int pk=cpy.size();

	for (int i=0;i<pk;i++)
	{
		cpy[i]->setMultselect(false);
		arr=cpy[i]->translatep(cpy[i]->getCenter(),point);
		create(arr);
	}
	candraw=true;

}

void CDraw::Init()
{
	for(int i=0;i<fit;i++)
	{
		try{
	delete fig[i];
		}catch(...)
		{
		}
	fig[i]=NULL;
	}
	fit=0;
	fig.clear();
	vs.clear();
	blocks.clear();

	delete pBezier;
	int j=rmemento.size();
	for(i=0;i<j;i++)
	{
	delete rmemento[i];
	rmemento[i]=NULL;
	}
	rmemento.clear();

	while(!redoList.empty())
		redoList.pop();
	j=vmemento.size();
	for(i=0;i<j;i++)
	{
	delete vmemento[i];
	vmemento[i]=NULL;
	}
	vmemento.clear();
	while(!undostack.empty())
		undostack.pop();
	while(!redostack.empty())
		redostack.pop();
	while(!undoList.empty())
		undoList.pop();

	version=0;
	count=0;
	CVector v(0,0,1);
	v0=v;
	v_current=v0;
	fit=0;
	mouseon=false;
	sfit=0;
	sefit=0;
	bck=false;
	m=0;ms=0;
	cdel=false;

	initVect();
	VinitVect();
	cam.initCam();
	veclayer.clear();

	B=false;
	Bminus=false;
	positions[1]=v0;ita=0;
	rzoom=0.5;
	
	selected=false;
	menuselect=false;

	endDraw=FALSE;
	change=false;
	nbc=0;
	valid=false;
	candraw = true;
	currlayer.clear=false;
	currlayer.on=true;
	currlayer.lock=false;
	currlayer.name="Normal";
	veclayer.push_back(currlayer);

	CVector k(0,0,0,1);
	CVector kt(k.getscrtop()/2,k.getscrb()/2);
	k=k-kt;
	pBezier=new CBezier;
	Dim=NULL;
	DimL= NULL;
	snap_fig=NULL;

}
 struct INDEX 
 {
	DWORD pos;
	CString name;
 };
#include "dxf_file.cpp"

void CDraw::saveDXF(CDC *hdc,CStdioFile& file)
{
//	if(!candraw) return;
//		initdxf(file);
		file.WriteString("0");file.WriteString("\n");
		file.WriteString("SECTION");file.WriteString("\n");
		file.WriteString("2");file.WriteString("\n");
		file.WriteString("TABLES");file.WriteString("\n");
		writedxf_table_vport(file,cam);
		writedxf_table_linetype(file);
		writedxf_table_layer(file,veclayer);
		writedxf_table_style(file);
		writedxf_table_view(file);
		writedxf_table_ucs(file);
		writedxf_table_appid(file);
		writedxf_table_dim(file);
		writedxf_table_block(file);
		file.WriteString("0");file.WriteString("\n");
		file.WriteString("ENDSEC");file.WriteString("\n");
//		file.WriteString("0");file.WriteString("\n");
//		file.WriteString("SECTION");file.WriteString("\n");
//		file.WriteString("2");file.WriteString("\n");
//		file.WriteString("BLOCKS");file.WriteString("\n");
//		writedxf_block_init(file);
//		file.WriteString("0");file.WriteString("\n");
//		file.WriteString("ENDSEC");file.WriteString("\n");
		file.WriteString("0");file.WriteString("\n");
		file.WriteString("SECTION");file.WriteString("\n");
		file.WriteString("2");file.WriteString("\n");
		file.WriteString("ENTITIES");file.WriteString("\n");
		for(int i=0;i<fit;i++)
		{
			fig[i]->savefiledxf(file);
		}
		file.WriteString("0");file.WriteString("\n");
		file.WriteString("ENDSEC");file.WriteString("\n");
		file.WriteString("0");file.WriteString("\n");
		file.WriteString("EOF");file.WriteString("\n");
}

void CDraw::save(CDC *hdc,CFile& file)
{
//	if(!candraw) return;
 vector<INDEX> index(fit);
///////////////////////////////////////////////////////////
		char result[MAX_PATH],dir[MAX_PATH];

		GetTempPath(MAX_PATH,dir);

		 /* Attempt to find a unique filename: */
		GetTempFileName(dir, // dir. for temp. files 
		_T("andyc"),                // temp. filename prefix 
		0,                    // create unique name 
		result);          // buffer for name 

		CFile filo(result,CFile::modeCreate|CFile::modeReadWrite);

		CFigure **tfig=NULL;
		tfig=(CFigure**) realloc(tfig,sizeof(CFigure*)*fit);
		int j=fit;
		filo.Write(&version,sizeof(int));
		filo.Write(&fit,sizeof(int));
		cam.savefile(file);
		CString nm;
		int sz;
		try{		
		for(int i=0;i<fit;i++)
		{
			nm=fig[i]->getName();
			index[i].pos=file.GetPosition();
			index[i].name=fig[i]->getInfName();
			filo.Write(&index[i].pos,sizeof(index[i].pos));
			int lop=index[i].name.GetLength();
			filo.Write(&lop,sizeof(int));
			for(int j=0;j<lop;j++)
			{
			char c=index[i].name[j];
			filo.Write(&c,sizeof(c));
			}
			if(nm=="CLine")
			{
				sz=0;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			if(nm=="CRectangle")
			{
				sz=1;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CQLine")
			{
				sz=2;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CBezier")
			{
				sz=3;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CCercle")
			{
				sz=4;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CLibS")
			{
				sz=5;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CDim")
			{
				sz=8;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CDimA")
			{
				sz=9;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CDimL")
			{
				sz=10;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CTextCad")
			{
				sz=6;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(file);
			}
			else
			if(nm=="CImage")
			{
				sz=7;
			filo.Write(&sz,sizeof(sz));
			file.Write(&sz,sizeof(sz));
			fig[i]->savefile(hdc,file);
			}

		}
		}catch(...)
			{
			int j=0;
		}
		int ii=currlayer.name.GetLength();
		file.Write(&ii,sizeof(int));
		for(int jj=0;jj<ii;jj++)
		{
		char c=currlayer.name[jj];
		file.Write(&c,sizeof(char));
		}
		file.Write(&currlayer.handle,sizeof(int));
		file.Write(&currlayer.on,sizeof(bool));
		file.Write(&currlayer.clear,sizeof(bool));
		file.Write(&currlayer.lock,sizeof(bool));

		int siz=veclayer.size();
		file.Write(&siz,sizeof(int));
		for(vector<FLAYER>::iterator iter=veclayer.begin();iter<veclayer.end();iter++)
		{
			int i=iter->name.GetLength();
			file.Write(&i,sizeof(int));
			for(int j=0;j<i;j++)
			{
			char c=iter->name[j];
			file.Write(&c,sizeof(c));
			}
			file.Write(&iter->handle,sizeof(int));
			file.Write(&iter->on,sizeof(bool));
			file.Write(&iter->clear,sizeof(bool));
			file.Write(&iter->lock,sizeof(bool));
		}
/////////////////////////////////////////////////////////////
	DWORD length=file.GetLength();
	DWORD lengtho=filo.GetLength();
	BYTE* b=new BYTE[length];
	file.SeekToBegin();
	file.Read(b,length);
	filo.Write(b,length);
	filo.SeekToBegin();

	filo.Seek(sizeof(int)*2,CFile::begin);
	DWORD lpos;
	LPSTR sb;
	for(int i=0;i<fit;i++)
	{
		index[i].pos+=lengtho;
		filo.Write(&index[i].pos,sizeof(lpos));
		int lpo;
		filo.Read(&lpo,sizeof(lpo));
		char c;
		for(int j=0;j<lpo;j++)
		{
		filo.Read(&c,sizeof(c));
		}
		filo.Read(&lpo,sizeof(lpo));
	}
	
	delete b;
	length=filo.GetLength();
	b=new BYTE[length];
	filo.SeekToBegin();
	file.SeekToBegin();
	filo.Read(b,length);
	file.Write(b,length);
	filo.Close();
	CFile::Remove(result);
	delete b;
}


void CDraw::open(CDC *hdc,CFile& file)
{

	candraw=false;
//	try{
		file.Read(&version,sizeof(int));
//		if(version==0)
		{
			file.Read(&fit,sizeof(int));
			DWORD lpos;
			LPSTR sb;
			for(int i=0;i<fit;i++)
			{
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				}
				file.Read(&lpo,sizeof(lpo));
			}
//			CTVector tv;
			cam.openfile(file);
			cam.Update();
			string nm;
			int sz;
			for(i=0;i<fit;i++)
			{
				file.Read(&sz,sizeof(sz));
				if(sz==0)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CLine(file);
				}
				if(sz==1)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CRectangle(file);
				}
				else
				if(sz==2)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CQLine(file);
				}
				else
				if(sz==3)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CBezier(file);
				}
				else
				if(sz==4)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CCercle(file);
				}
				else
				if(sz==5)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CLibS(file,hdc);
				}
				else
				if(sz==6)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CTextCad(file,hdc);
				}
				else
				if(sz==7)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CImage(hdc,file);
				}
				else
				if(sz==8)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDim(file,hdc);
				}
				else
				if(sz==9)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDimA(file,hdc);
				}
				else
				if(sz==10)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDimL(file,hdc);
				}

//				fig[i]->sethandle(count);
				undoList.push("create");
//				fig[i]->setUndoparam();
				fig[i]->setcorevecor();

				string scount;
				CString f;
				f.Format(_T("%d"),count);
				scount=f;
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				Bminus=true;

			}
//			file.Read(&currlayer,sizeof(FLAYER));
			int ii;
			file.Read(&ii,sizeof(int));
			char c;
			currlayer.name.Empty();
			for(int jj=0;jj<ii;jj++)
			{
			file.Read(&c,sizeof(c));
			currlayer.name.Insert(jj,c);
			}
			file.Read(&currlayer.handle,sizeof(int));
			file.Read(&currlayer.on,sizeof(bool));
			file.Read(&currlayer.clear,sizeof(bool));
			file.Read(&currlayer.lock,sizeof(bool));
			
			
			int siz;
			file.Read(&siz,sizeof(int));
			veclayer.clear();
			for(int j=0;j<siz;j++)
			{
				FLAYER fl;
				int i;
				file.Read(&i,sizeof(int));
				char c;
				for(int j=0;j<i;j++)
				{
				file.Read(&c,sizeof(c));
				fl.name.Insert(j,c);
				}
				file.Read(&fl.handle,sizeof(int));
				file.Read(&fl.on,sizeof(bool));
				file.Read(&fl.clear,sizeof(bool));
				file.Read(&fl.lock,sizeof(bool));
				veclayer.push_back(fl);
			}
//		cam.initCam();
		candraw=true;
		}
//		}catch(...)
//			{
//			AfxMessageBox("Problem with Openning of File");
//		}

}


void CDraw::save00(CDC *hdc,CFile& file)
{
//	if(!candraw) return;
 vector<INDEX> index(fit);
///////////////////////////////////////////////////////////
		char result[MAX_PATH],result1[MAX_PATH],dir[MAX_PATH];

		GetTempPath(MAX_PATH,dir);

		 /* Attempt to find a unique filename: */
		GetTempFileName(dir, // dir. for temp. files 
		"andyc",                // temp. filename prefix 
		0,                    // create unique name 
		result);          // buffer for name 

		 /* Attempt to find a unique filename: */
		GetTempFileName(dir, // dir. for temp. files 
		"andyc",                // temp. filename prefix 
		0,                    // create unique name 
		result1);          // buffer for name 

		CFile filo(result,CFile::modeCreate|CFile::modeReadWrite);
		CFile filo1(result1,CFile::modeCreate|CFile::modeReadWrite);

		CFigure **tfig=NULL;
		tfig=(CFigure**) realloc(tfig,sizeof(CFigure*)*fit);
		int j=fit;
		file.Write(&version,sizeof(int));
		file.Write(&fit,sizeof(int));
		cam.savefile(file);
		CString nm;
		int sz;
		
		for(int i=0;i<fit;i++)
		{
			nm=fig[i]->getName();
			index[i].pos=filo.GetPosition();
			index[i].name=fig[i]->getInfName();
			filo1.Write(&index[i].pos,sizeof(index[i].pos));
			int lop=index[i].name.GetLength();
			filo1.Write(&lop,sizeof(int));
			for(int j=0;j<lop;j++)
			{
			char c=index[i].name[j];
			filo1.Write(&c,sizeof(c));
			}
			if(nm=="CLine")
			{
				sz=0;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			if(nm=="CRectangle")
			{
				sz=1;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CQLine")
			{
				sz=2;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CBezier")
			{
				sz=3;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CCercle")
			{
				sz=4;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CLibS")
			{
				sz=5;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CDim")
			{
				sz=8;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CDimA")
			{
				sz=9;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CDimL")
			{
				sz=10;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CTextCad")
			{
				sz=6;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(filo);
			}
			else
			if(nm=="CImage")
			{
				sz=7;
//			filo.Write(&sz,sizeof(sz));
			filo.Write(&sz,sizeof(sz));
			fig[i]->savefile(hdc,filo);
			}

		}
		int ii=currlayer.name.GetLength();
		filo.Write(&ii,sizeof(int));
		for(int jj=0;jj<ii;jj++)
		{
		char c=currlayer.name[jj];
		filo.Write(&c,sizeof(char));
		}
		filo.Write(&currlayer.handle,sizeof(int));
		filo.Write(&currlayer.on,sizeof(bool));
		filo.Write(&currlayer.clear,sizeof(bool));
		filo.Write(&currlayer.lock,sizeof(bool));

		int siz=veclayer.size();
		filo.Write(&siz,sizeof(int));
		for(vector<FLAYER>::iterator iter=veclayer.begin();iter<veclayer.end();iter++)
		{
			int i=iter->name.GetLength();
			filo.Write(&i,sizeof(int));
			for(int j=0;j<i;j++)
			{
			char c=iter->name[j];
			filo.Write(&c,sizeof(c));
			}
			filo.Write(&iter->handle,sizeof(int));
			filo.Write(&iter->on,sizeof(bool));
			filo.Write(&iter->clear,sizeof(bool));
			filo.Write(&iter->lock,sizeof(bool));
		}
/////////////////////////////////////////////////////////////
	DWORD length=filo1.GetLength();
	DWORD lengtho=filo.GetLength();
	BYTE* b=new BYTE[length];
	filo1.SeekToBegin();
	filo1.Read(b,length);
	file.Write(b,length);
	BYTE* b1=new BYTE[lengtho];
	filo.SeekToBegin();
	filo.Read(b1,lengtho);
	file.Write(b1,lengtho);

/*	filo.Seek(sizeof(i)*2,CFile::begin);
	DWORD lpos;
	LPSTR sb;
	for(i=0;i<fit;i++)
	{
		index[i].pos+=lengtho;
		filo.Write(&index[i].pos,sizeof(lpos));
		int lpo;
		filo.Read(&lpo,sizeof(lpo));
		char c;
		for(int j=0;j<lpo;j++)
		{
		filo.Read(&c,sizeof(c));
		}
		filo.Read(&lpo,sizeof(lpo));
	}
*/	
	delete b;
	delete b1;
/*	length=filo.GetLength();
	b=new BYTE[length];
	filo.SeekToBegin();
	file.SeekToBegin();
	filo.Read(b,length);
	file.Write(b,length);
	filo.Close();*/
	filo.Close();
	filo1.Close();
	CFile::Remove(result1);
	CFile::Remove(result);
}


void CDraw::open00(CDC *hdc,CFile& file)
{

	try{
	candraw=false;
		file.Read(&version,sizeof(int));
		if(version==0)
		{
			int _fit=0;
			file.Read(&_fit,sizeof(int));
			cam.openfile(file);
//			::AfxMessageBox("Open Camera");
			cam.Update();
			DWORD lpos;
			LPSTR sb;
			for(int i=0;i<_fit;i++)
			{
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				}
//				file.Read(&lpo,sizeof(lpo));
			}
//			CTVector tv;
//			::AfxMessageBox("Open Header");
			CString ps;
			ps.Format(_T("We have %i objects to load"),_fit);
//			::AfxMessageBox(ps);
			string nm;
			int sz;
			for(i=0;i<_fit;i++)
			{
				file.Read(&sz,sizeof(sz));
				if(sz==0)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CLine(file);
				}
				if(sz==1)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CRectangle(file);
				}
				else
				if(sz==2)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CQLine(file);
				}
				else
				if(sz==3)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					try{
					fig[i]=new CBezier(file);
					}catch(...)
					{

					}
				}
				else
				if(sz==4)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CCercle(file);
				}
				else
				if(sz==5)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CLibS(file,hdc);
				}
				else
				if(sz==6)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CTextCad(file,hdc);
				}
				else
				if(sz==7)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CImage(hdc,file);
				}
				else
				if(sz==8)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDim(file,hdc);
				}
				else
				if(sz==9)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDimA(file,hdc);
				}
				else
				if(sz==10)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CDimL(file,hdc);
				}

//				fig[i]->setHandle(scount);
				undoList.push("create");
//				fig[i]->setUndoparam();
				fig[i]->setcorevecor();

				string scount;
				CString f;
				f.Format(_T("%d"),count);
				scount=f;
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				Bminus=true;

			}
//			::AfxMessageBox("Finish Loading Objects");
//			file.Read(&currlayer,sizeof(FLAYER));
			int ii;
			file.Read(&ii,sizeof(int));
			char c;
			currlayer.name.Empty();
//			CString ps;
			ps.Format(_T("We have %i layers to load"),ii);
//			::AfxMessageBox(ps);
			for(int jj=0;jj<ii;jj++)
			{
			file.Read(&c,sizeof(c));
			currlayer.name.Insert(jj,c);
			}
			file.Read(&currlayer.handle,sizeof(int));
			file.Read(&currlayer.on,sizeof(bool));
			file.Read(&currlayer.clear,sizeof(bool));
			file.Read(&currlayer.lock,sizeof(bool));
			
			
			int siz;
			file.Read(&siz,sizeof(int));
			veclayer.clear();
			for(int j=0;j<siz;j++)
			{
				FLAYER fl;
				int i;
				file.Read(&i,sizeof(int));
				char c;
				for(int j=0;j<i;j++)
				{
				file.Read(&c,sizeof(c));
				fl.name.Insert(j,c);
				}
				file.Read(&fl.handle,sizeof(int));
				file.Read(&fl.on,sizeof(bool));
				file.Read(&fl.clear,sizeof(bool));
				file.Read(&fl.lock,sizeof(bool));
				veclayer.push_back(fl);
			}
			fit=_fit;
//		cam.initCam();
		}
		candraw=true;
}
catch(...)
{
	AfxMessageBox("Error Opening File");
}
}


void CDraw::import(CDC *hdc,CFile& file)
{

		int ccount,ssfit,ffit;
	
//		file.Seek(sizeof(bool)*3,CFile::begin);

//		file.Read(&ccount, sizeof(int));
//		count+=ccount;
//		file.Read(&ssfit, sizeof(int));
//		for(int u=0; u<ssfit;u++);
//		{
//			file.Read(&vhan[u+sfit],sizeof(int));
//		}
//		sfit+=ssfit;
		file.Read(&version,sizeof(int));
//		if(version==0)
		{
			file.Read(&ffit,sizeof(int));
			DWORD lpos;
			LPSTR sb;
			for(int i=0;i<ffit;i++)
			{
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				}
				file.Read(&lpo,sizeof(lpo));
			}
//			CTVector tv;
			cam.Readfile(file);

			string nm;
			int sz;
			for(i=0;i<ffit;i++)
			{
				file.Read(&sz,sizeof(sz));
				if(sz==0)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CLine(file);
				}
				if(sz==1)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CRectangle(file);
				}
				else
				if(sz==2)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CQLine(file);
				}
				else
				if(sz==3)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CBezier(file);
				}
				else
				if(sz==4)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CCercle(file);
				}
				else
				if(sz==5)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CLibS(file,hdc);
				}
				else
				if(sz==6)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CTextCad(file,hdc);
				}
				else
				if(sz==7)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CImage(hdc,file);
				}
				else
				if(sz==8)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CDim(file,hdc);
				}
				else
				if(sz==9)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CDimA(file,hdc);
				}
				else
				if(sz==10)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CDimL(file,hdc);
				}

				string scount;
				CString f;
				f.Format(_T("%d"),count);
				scount=f;
				fig[i]->setHandle(scount);
				undoList.push("create");
//				fig[i]->setUndoparam();
				fig[i]->setcorevecor();

				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				Bminus=true;

			}
			fit+=ffit;

			int ii;
			file.Read(&ii,sizeof(int));
			char c;
			currlayer.name.Empty();
			for(int jj=0;jj<ii;jj++)
			{
			file.Read(&c,sizeof(c));
			currlayer.name.Insert(jj,c);
			}
			file.Seek(sizeof(int),CFile::current);
			file.Seek(sizeof(bool),CFile::current);
			file.Seek(sizeof(bool),CFile::current);
			file.Seek(sizeof(bool),CFile::current);
			
			
			int siz;
			file.Read(&siz,sizeof(int));
			veclayer.clear();
			for(int j=0;j<siz;j++)
			{
				FLAYER fl;
				int i;
				file.Read(&i,sizeof(int));
				char c;
				for(int j=0;j<i;j++)
				{
				file.Read(&c,sizeof(c));
				fl.name.Insert(j,c);
				}
				file.Read(&fl.handle,sizeof(int));
				file.Read(&fl.on,sizeof(bool));
				file.Read(&fl.clear,sizeof(bool));
				file.Read(&fl.lock,sizeof(bool));
				veclayer.push_back(fl);
			}

		}
		candraw=true;
}



void CDraw::SelectRotState(bool value)
{
/*	liter=Line.begin();
	citer=Cercle.begin();
	riter=Rectangle.begin();*/
	CVector v(0,0,1);
	
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (fig[i]->inselectedstate())
		{
			fig[i]->setRotClick(value);
			fig[i]->rotateSM(NULL,0,v,v,false);
			 
		}
//	}
	}
	
}

void CDraw::deleteObject(CDC *hdc)
{
	int j=0;
	vector<CFigure*>::iterator iter;
	int j1=vs.size();
	for (int i=0;i<j1;i++)
	{
		   CMemento* m = new CMemento(vs[i]);
		   vmemento.push_back(m);
		   undoList.push("delete");
			vhan.push_back(vs[i]->gethandle());
			sfit++;
			iter=find(fig.begin(),fig.end(),vs[i]);
			if(iter!=fig.end())
			{
			delete *iter;
			fig.erase(iter);fit--;
			}
	}
	vs.clear();
	candraw=true;

}
void CDraw::copyRSparam2(CDC *hdc,double angle, int nbcopy,int nblevel,int dlevel,bool align,CVector v)
{
	int pk=vs.size();

	for (int i=0;i<pk;i++)
	{
		vs[i]->setRotateCenter(v);
	}
	copyRSparam(hdc,angle,nbcopy,nblevel,dlevel,align);
}
void CDraw::copyRSparam(CDC *hdc,double angle, int nbcopy,int nblevel,int dlevel,bool align)
{
	angle=(angle*2*pi)/360;

	CInter pInter;
	vector<CFigure*> arr;
	vector<CFigure*>::iterator fiter;

	int pk=vs.size();

	for (int i=0;i<pk;i++)
	{

//		if ([i]->inselectedstate())
		{
			arr=vs[i]->RotateCopyP(hdc,angle,nbcopy,nblevel,dlevel,align);
			vs[i]->setMultselect(false);
			for(fiter=arr.begin();fiter!=arr.end();fiter++)
			{
				create(*fiter);
			}
		}
	}
	candraw=true;
}

void CDraw::copyRS(CDC *hdc,CVector center,bool align)
{

	AfxMessageBox("I am in CopyRS");
	CInter pInter;
	vector<CFigure> *arr;
	vector<CFigure>* pbulk=new vector<CFigure>;
	vector<CFigure>::iterator fiter;
	CLibS* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CTextCad textc;

	string scount;
	CString f;
	int pk=fit;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		f.Format(_T("%d"),count);
		scount=f;
		if (fig[i]->inselectedstate())
		{
		if(fig[i]->getName()!=pLibs.getName())
		{
			arr=fig[i]->RotateCopyP(hdc,center,pbulk,align);
			fig[i]->setMultselect(false);
			for(fiter=arr->begin();fiter<arr->end();fiter++)
			{

				f.Format(_T("%d"),count);
				scount=f;
				if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
				{
				pLine=*(CLine*)fig[i];
				pLine.createobj(fiter->ptbegin,fiter->ptend);
				pLine.draw(hdc);
				pLine.setInit();
				CLine *ftp= new CLine;
				*ftp=pLine;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
				/*	CCercle pC;
				pC=*(CCercle*)fig[i];
				pC.addvec(fiter->ptbegin,fiter->ptend);
				pC.draw(hdc);
				pC.setInit();*/
				CCercle *ftp= new CCercle;
				ftp->copy(*(CCercle*)fig[i]);//pC;
				ftp->addvec(fiter->ptbegin,fiter->ptend);
				ftp->draw(hdc);
				ftp->setInit();

				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
				pBezier->copy((CBezier*)fig[i]);
				pBezier->addvec(fiter->ptbegin,fiter->ptend);
				CBezier *ftp= new CBezier;
				ftp->copy(pBezier);
				ftp->draw(hdc);
				ftp->setInit();
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==textc.getName())
				{
				textc=*(CTextCad*)fig[i];
				textc.addvec(fiter->ptbegin,fiter->ptend);
				textc.draw(hdc);
				textc.setInit();
				CTextCad *ftp= new CTextCad;
				*ftp=textc;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
			}
		}
		else
		{
			lib=pInter.RotateCopyP(hdc,fig[i]->getRotateCenter(),center,align,(CLibS*)fig[i]);
			int k=lib[0].x;
			for(int i=0;i<k;lib++,i++)
			{
			lib->draw(hdc);
			CLibS *ftp= new CLibS;
			*ftp=*lib;
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
			fig[pk]=ftp;
			pk++;
			}
		}
		}
//	}
	}

	fit=pk;

	candraw=true;
	delete pbulk;
}

void CDraw::copybyCenter(CDC *hdc, CVector point)
{
	AfxMessageBox("I am in copybyCenter");
	CFigure* arr;

	int pk=vs.size();

	for (int i=0;i<pk;i++)
	{

//		if (fig[i]->inselectedstate())
		{
			arr=vs[i]->copybyC(hdc,point);
			vs[i]->setMultselect(false);
			create(arr);
		}
	}
	candraw=true;

}

void CDraw::alignbyLine(CDC *hdc, CVector point)
{

}

void CDraw::setEndPoly(bool end)
{
	menuselect=end;

}

void CDraw::setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor)
{
	bool s=false;
	CTextCad textc;
	int j=vs.size();
	for (int i=0;i<j;i++)
	{
		if (vs[i]->getName()!=textc.getName())
		{
			vs[i]->setLcolor(hdc,color,bcolor);
			s=true;
			
		}else
		if (vs[i]->getName()==textc.getName())
		{
			CTextCad *text=(CTextCad*)fig[i];
			if (text->WndVisible())
			{
				text->setLcolor(hdc,color,bcolor);
				break;
			}
		}
		candraw=true;
		//grid(hdc,vs[i]->box);
	}
//	if((!s)&&(fit>0))
//	{
//		fig[fit-1]->setLcolor(hdc,color,bcolor);
//s	}

}



void CDraw::forundo(CWnd *wnd,CDC *hdc)
{
	int j=vs.size();
	if(fit==0) return;
	for (int i=0;i<j;i++)
	{
		if(vs[i]->getName()!="CImage")
		{
		   CMemento* m=new CMemento(vs[i]);
		   vmemento.push_back(m);
		   undoList.push("Memento");
		}
	}
}

void CDraw::undo(string& cmd,bool rdo)
{
/*	if(undostack.empty()) return;
	cmd = undostack.top().second;
	redostack.push(undostack.top());
	undostack.pop();
	return;*/
	vs.clear();
	if(undoList.size()>0)
	{
		//get last element in undo list
		string obj = undoList.top();
		undoList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		if (obj=="create")
		{
		if(fit>0)
		{
		//remove last created rectangle
		CMemento* m = vmemento.back();vmemento.pop_back();
		//delete m;
		if(rdo)
		{
        CMemento* m1 = new CMemento(fig[fit-1]);
	    rmemento.push_back(m1);
	    redoList.push("delete");
		}
		delete fig[fit-1];
		fig.pop_back();
		fit--;count--;
		}
		}
		if (obj=="delete")
		{
		//get the Memento
		CMemento* m = vmemento.back();vmemento.pop_back();
		fig.resize(fit+1);
		fig[fit]=m->getM(); //and restore the old position
		CFigure* f=m->getF();
		vector<CMemento*>::iterator pi;
		for(pi=vmemento.begin();pi!=vmemento.end();pi++)
		{
			if((*pi)->getF()==f)
				(*pi)->setF(fig[fit]);
		}
		for(pi=rmemento.begin();pi!=rmemento.end();pi++)
		{
			if((*pi)->getF()==f)
				(*pi)->setF(fig[fit]);
		}
		delete m;
		if(rdo)
		{
        CMemento* m1 = new CMemento(fig[fit]);
	    rmemento.push_back(m1);
	    redoList.push("create");
		}
		fit++;count++;
		}
		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = vmemento.back();vmemento.pop_back();
		if(rdo)
		{
        CMemento* m1 = new CMemento(m->getM());
	    rmemento.push_back(m1);
	    redoList.push("Memento");
		}
		m->Restore(); //and restore the old position
		delete m;
		}
	}

}

void CDraw::redo(CDC *hdc,string& cmd)
{
/*	if(redostack.empty()) return;
	cmd = redostack.top().first;
	undostack.push(redostack.top());
	redostack.pop();
	
	return;*/
	vs.clear();
	if(redoList.size()>0)
	{
		//get last element in undo list
		string obj = redoList.top();
		redoList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		if (obj=="delete")
		{
		//remove last created rectangle
		CMemento* m = rmemento.back();rmemento.pop_back();
		fig.resize(fit+1);
		fig[fit]=m->getM(); //and restore the old position
		delete m;
        CMemento* m1 = new CMemento(fig[fit]);
	    vmemento.push_back(m1);
	    undoList.push("create");
		fit++;count++;
		}
		if (obj=="create")
		{
			if(fit>0)
			{
			CMemento* m = rmemento.back();rmemento.pop_back();
			delete m;
			//remove last created rectangle
			CMemento* m1 = new CMemento(fig[fit-1]);
			vmemento.push_back(m1);
			undoList.push("delete");
			delete fig[fit-1];
			fig.pop_back();
			fit--;count--;
			}
		}

		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = rmemento.back();rmemento.pop_back();
		CFigure *f=m->getM();
        CMemento* m1 = new CMemento(f);
		m->Restore(); //and restore the old position
		delete m;
	    vmemento.push_back(m1);
	    undoList.push("Memento");
		}
	}

}

void CDraw::undoc(bool rdo)
{
	if(undocList.size()>0)
	{
		//get last element in undo list
		string obj = undocList.top();
		undocList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		//if this is a Memento, the last action was a move
		//get the Memento
		CMemento* m = vcmemento.back();vcmemento.pop_back();
		if(rdo)
		{
        CMemento* m1 = new CMemento(m->getM());
	    rcmemento.push_back(m1);
	    redocList.push(obj);
		}
		m->Restore(); //and restore the old position
//		CCAM * c=(CCAM*)m->getF();
//		c->Update();
		delete m;
	}

}

void CDraw::redoc(CDC *hdc)
{
	if(redocList.size()>0)
	{
		//get last element in undo list
		string obj = redocList.top();
		redocList.pop(); //and remove it
		//if this is an Integer,
		//the last action was a new rectangle
		//get the Memento
		CMemento* m = rcmemento.back();rcmemento.pop_back();
		CFigure *f=m->getM();
        CMemento* m1 = new CMemento(f);
		m->Restore(); //and restore the old position
		delete m;
	    vcmemento.push_back(m1);
	    undocList.push(obj);
	}

}
void CDraw::grid(CDC *hdc,CAABB _box)
{
	HBRUSH br,bold;
	br=(HBRUSH)GetStockObject(WHITE_BRUSH);
	bold=(HBRUSH)SelectObject(hdc->GetSafeHdc(),br);

	CPen pat;
	pat.CreatePen(PS_NULL,2,RGB(12,12,0));
	CPen* pOldPen=hdc->SelectObject(&pat);

	CRect p=_box;
	p.NormalizeRect();
	p.InflateRect(50,50);

//	hdc->Rectangle(p);
	candraw=true;return;
		for(int i=0;i<fit;i++)
		{
			if(_box.intersectAABB2(fig[i]->box))
			{
				bool b=fig[i]->move;
				fig[i]->move=true;
				fig[i]->draw(hdc);
				fig[i]->move=b;
			}
		}
	SelectObject(hdc->GetSafeHdc(),bold);
	SelectObject(hdc->GetSafeHdc(),pOldPen);
}
CRect CDraw::grid(CDC *rhdc,CDC *hdc,CSize cp)
{
	if(!candraw) return CRect(0,0,0,0);
//	pushUnit();
//	CVector v(30,0);
 //	Translate(v);
//	VendT();
	CVector k;
	CVector ktl(k.getscrtop()),kbr(k.getscrb());
	CVector ktr(kbr.x,ktl.y,0,1),kbl(ktl.x,kbr.y,0,1);

//	CVector v1(-(cp.cx/2),-(cp.cy/2)),v2((cp.cx/2),-(cp.cy/2)),\
			v3((cp.cx/2),(cp.cy/2)),v4(-(cp.cx/2),(cp.cy/2));
	
	HBRUSH br,bold;
	br=(HBRUSH)GetStockObject(WHITE_BRUSH);
	bold=(HBRUSH)SelectObject(hdc->GetSafeHdc(),br);

	CPen pat;
	pat.CreatePen(PS_SOLID,2,RGB(12,12,0));
	CPen* pOldPen=hdc->SelectObject(&pat);



	CVector v0(k.getcamor()),vx(100,0,0,0),vy(0,100,0,0),v1,vz(0,0,100,0);
	CRect p(0,0,cp.cx,cp.cy);

//	hdc->BeginPath();
//	page.draw(hdc);
//	hdc->EndPath();
//	hdc->CloseFigure();
//	hdc->StrokeAndFillPath();
	hdc->Rectangle(p);
	SelectObject(hdc->GetSafeHdc(),bold);
	snappy.displaygrid(hdc,this);
//	displaygrid(hdc,10);
	CVector t0(v1.getcamor()),tx(v1.getcamx()),ty(v1.getcamy()),tz(v1.getcamz());


	hdc->MoveTo(v0);
//	hdc->TextOut(CPoint(v0).x,CPoint(v0).y,"O");
	vx=v0+vx;
	hdc->LineTo(vx);
	hdc->TextOut(CPoint(vx).x,CPoint(vx).y,"X");
	hdc->MoveTo(v0);
	vy=vy+v0;
	hdc->LineTo(vy);
	hdc->TextOut(CPoint(vy).x,CPoint(vy).y,"Y");
	hdc->MoveTo(v0);
	vz=v0+vz;
	hdc->LineTo(vz);
	hdc->TextOut(CPoint(vz).x,CPoint(vz).y,"Z");
	display(rhdc,hdc);

	
	return CRect(ktl,kbr);
//	pushUnit();


}

void CDraw::group(CDC *hdc)
{
	int l=vs.size(),i;
//	for(int i=0;i<fit;i++)
//	{
//		if(fig[i]->transselectedstate())
///		{
//			l++;
//		}
//	}

	if(l>1)
	{

		candraw=true;
		CLibS *lib=new CLibS;

		for(i=0;i<l;i++)
		{
//			if(fig[i]->transselectedstate())
			{
				CFigure* ftp=vs[i]->translatep(vs[i]->getCenter(),vs[i]->getCenter());
				lib->add(ftp);
				forundo(i,"delete");
			}
		}
		for(int j=0;j<l;j++)
		{
			for(i=0;i<fit;i++)
			{
				if(vs[j]==fig[i])
				{
				delete fig[i];
				fig.erase(fig.begin()+i);
				fit--;
				break;
				}
			}
		}
		create(lib);
		vs.clear();
		sefit=0;

	}
}

void CDraw::group(CLibS &lib)
{
	CLine pL;
	CRectangle pR;
	CImage image;
	CCercle pC;
	CBezier pB;
	CLibS pli;
	CTextCad textc;
	
	vector<CVector> *arr;
	bool connect=false;
	int j=vs.size();
	for(int i=0;i<j;i++)
	{
//			arr=fig[i]->translatep(fig[i]->getCenter(),fig[i]->getCenter()); To check back
					
			if(vs[i]->getName()==pL.getName())
			{
				pL=*(CLine*)vs[i];
				pL.createobj(*arr,*(arr+1));
				delete[] arr;
				CLine *ftp= new CLine;
				*ftp=pL;
				lib.add(ftp);
			}else
			if(vs[i]->getName()==pR.getName())
			{
				pR=*(CRectangle*)vs[i];
				pR.addvec(*arr,*(arr+1));
				delete[] arr;
				CRectangle *ftp= new CRectangle;
				*ftp=pR;
				lib.add(ftp);
			}else
			if(vs[i]->getName()==pC.getName())
			{
				pC.copy(*(CCercle*)vs[i]);
				pC.addvec(*arr,*(arr+1));
				delete[] arr;
				CCercle *ftp= new CCercle;
				ftp->copy(pC);
				lib.add(ftp);
			}else
			if(vs[i]->getName()==pB.getName())
			{
				pB.copy((CBezier*)vs[i]);
				pB.addvec(*arr,*(arr+1));
				delete[] arr;
				CBezier *ftp= new CBezier;
				ftp->copy(&pB);
				lib.add(ftp);
			}else
			if(vs[i]->getName()==textc.getName())
			{
				textc=*(CTextCad*)vs[i];
				textc.addvec(*arr,*(arr+1));
				delete[] arr;
				CTextCad *ftp= new CTextCad;
				*ftp=textc;
				lib.add(ftp);
			}else
			if(vs[i]->getName()==image.getName())
			{
				image=*(CImage*)vs[i];
				image.addvec(*arr,*(arr+1));
				delete[] arr;
				CImage *ftp= new CImage;
				*ftp=image;
				lib.add(ftp);
			}else
			if(vs[i]->getName()==lib.getName())
			{
				pli.Copy(*(CLibS*)vs[i]);
				pli.addvec(*arr,*(arr+1));
				delete[] arr;
				CLibS *ftp= new CLibS;
				ftp->Copy(pli);
				lib.add(ftp);
			}			
				connect=true;
		}
}



bool CDraw::straightDimA(bool st)
{
	for(int i=fit-1;i>=0;i--)
	{
		if((fig[i]->transselectedstate())&&(fig[i]->getName()=="CDimA"))
		{
			fig[i]->orient(1);
			return true;
		}
	}

	for(i=fit-1;i>=0;i--)
	{
		if(fig[i]->getName()=="CDimA")
		{
			fig[i]->orient(1);
			return true;
		}
	}

}

bool CDraw::finDimA()
{
	if (valid)
	{
		valid=false;
		return true;
	}
	else
	{
		return false;
	}

}

void CDraw::GetTextrec(CWnd* wnd,CDC *hdc)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textcad->getName())
		{
			if(fig[i]->transselectedstate())
			{
				CTextCad *tcad=(CTextCad*)fig[i];
//				tcad->getTextrec(wnd,hdc);
				fig[i]=tcad;
			}
		}
	}

}

CPoint CDraw::drawtext(CDC *hdc, UINT nchar)
{
	CTextCad textc;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textc.getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->drawtext(hdc,nchar);

			}
		}
	}
}

void CDraw::inittext()
{
	CTextCad textc;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textc.getName())
		{
			if(fig[i]->transselectedstate())
			{
				fig[i]->setInit();

			}
		}
	}
}

CPoint CDraw::txthome(CDC *hdc)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textcad->getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->texthome(hdc);
			}
		}
	}
}

CPoint CDraw::deletetxt(CDC *hdc)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textcad->getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->deletetext(hdc);
			}
		}
	}
}


CPoint CDraw::txtend(CDC *hdc)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textcad->getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->textend(hdc);
			}
		}
	}
}


CPoint CDraw::deletebk(CDC *hdc)
{
	CTextCad test;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==test.getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->deleteback(hdc);
			}
		}
	}
}

CPoint CDraw::entertxt(CDC *hdc)
{
	CTextCad test;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==test.getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->entertext(hdc);
			}
		}
	}

}

CPoint CDraw::movecurskb(CDC *hdc, CString dir)
{
	CTextCad textc;
	for(int i=0;i<fit;i++)
	{
		if(*fig[i]->getName()==*textc.getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->kbmovecurs(hdc,dir);
			}
		}
	}
	return CPoint(-10,-10);

}

CPoint CDraw::setFont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf)
{
	CTextCad textc;
	int j1=vs.size();
	bool c=false;
	for (int j=0;j<j1;j++)
	{
		if (vs[j]->getName()==textc.getName())
		{
			CTextCad *text=(CTextCad*)vs[j];
			text->setfont(hdc,font,ccl,cf);
			if(text->WndVisible())
			{
				return CPoint(1,0);
			}
			return CPoint(0,0);
			
		}
	}
	for (j=0;j<fit;j++)
	{
		if (fig[j]->getName()==textc.getName())
		{
			CTextCad *text=(CTextCad*)fig[j];
			if(text->WndVisible())
			{
				text->setfont(hdc,font,ccl,cf);
				return CPoint(1,0);
			}
			
		}
	}

}

void CDraw::slide(CDC *hdc,CVector pos)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->PtinRegion(pos))
		{
		if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
		{
			fig[i]->setLcolor(hdc,PALETTEINDEX(150),PALETTEINDEX(10));
			for(int j=0;j<fit;j++)
			{
			if((fig[j]->transselectedstate())&&(fig[j]!=fig[i]))
			{
			fig[j]->setTransref(true);
			fig[j]->setReflineP(fig[i]->selectvec[0],fig[i]->selectvec[2]);
			}

			}
			break;
		}
		}
	}
}

bool CDraw::flip(bool vert)
{

	bool b=false;
	CVector i(0,1);
	CVector j(1,0);
	CVector v1;
	CVector v2;

	if(vert)
	{
	v1=i;
	v2=j;
	}
	else
	{
	v1=j;
	v2=i;
	}
	int l=vs.size();
	for(int k=0;k<l;k++)
	{
//		if(fig[k]->transselectedstate())
		{
//			CVector v=fig[k]->getCenter();
//			fig[k]->setRotateCenter(v);
			if(vert)
				vs[k]->rotate(pi/2,0);
			else
				vs[k]->rotate(-pi/2,0);

		}
	}
	candraw=true;
	return b;
}


void CDraw::ungroup(CDC *hdc)
{
	CLibS *lib=new CLibS;
	int l=vs.size();
	for(int i=0;i<l;i++)
	{
//		if(fig[i]->transselectedstate())
		{
			if(vs[i]->getName()==lib->getName())
			{
				delete lib;
				vector<CFigure*> figh;
				lib=(CLibS*)vs[i];
				figh=lib->degroup();
				for(int j=0;j<fit;j++)
				{
					if(vs[i]==fig[j])
					{
						forundo(j,"delete");
						delete fig[j];
						fig.erase(fig.begin()+j);
						fit--;
						int jfit=figh.size();
						for(int j1=0;j1<jfit;j1++)
						{
							create(figh[j1]);
						}
						j--;
						break;
					}
				}
				break;
			}
		}
	}
	vs.clear();
}

void CDraw::pos(CString posit)
{
	for(int i=0;i<fit;i++)
	{
		if (fig[i]->inselectedstate())
		{
			if(posit=="front")
			{
				CFigure *fg=fig[i];
				fig[i]=fig[fit-1];
				fig[fit-1]=fg;
			}
			else
			if(posit=="back")
			{
				CFigure *fg=fig[i];
				fig[i]=fig[0];
				fig[0]=fg;
			}
			else
			if(posit=="front1")
			{
				if((i+1)<fit)
				{
				CFigure *fg=fig[i];
				fig[i]=fig[i+1];
				fig[i+1]=fg;
				}
			}
			else
			if(posit=="back1")
			{
				if((i-1)>=0)
				{
				CFigure *fg=fig[i];
				fig[i]=fig[i-1];
				fig[i-1]=fg;
				}
			}
			break;
		}
	}

}

void CDraw::setlinestyle(DWORD lst)
{
	for(int k=0;k<fit;k++)
	{
		if(fig[k]->transselectedstate())
		{
			fig[k]->setlistyle(lst);

		}
	}

}

void CDraw::setlinewidth(double sl)
{
	for(int k=0;k<fit;k++)
	{
		if(fig[k]->transselectedstate())
		{
			fig[k]->setliwidth(sl);

		}
	}

}



void CDraw::getBinfo(CVector point)
{
	float length=-1;
	float angle=-1;
	float area=-1;
	float xp=point.x,yp=point.y,zp=point.z;
	CString name;
   void* pp[7];
	pp[0]=&length;
	pp[1]=&angle;
	pp[2]=&area;
	pp[3]=&name;
	pp[4]=&xp;
	pp[5]=&yp;
	pp[6]=&zp;

	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		vs[i]->takeinfo(point);
		
				length=vs[i]->getInfo().distance;
				angle=(360*vs[i]->getInfo().angle)/(2*pi);
				area=vs[i]->getInfo().surface;
				CString name=vs[i]->getInfo().name;
				CVector v=vs[i]->box.center();
				xp=v.x;
				yp=v.y;
				zp=v.z;

				for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
				{
						(*it)->SendNotify("selectinfo",pp);
				}

				return;
	}
}


void CDraw::setChamfparam(double ld)
{
	CDimA kj;
	kj.setChamfParam(ld);

}

void CDraw::setFiltparam(double lk)
{
	CDimA kj;
	kj.setFiltParam(lk);
}
void CDraw::setzoomrat(double zr,CFigure* f)
{
	candraw=true;
	forundoc(&cam,"Scale");
	if(f==NULL)
	{
		if(vs.size()==0) ;
		//	cam.setcamorigin(&box);
		else
		{
			int g=vs.size();
			CAABB _box;
			for (int i=0;i<g;i++)
			{
				_box.add(vs[i]->getbox());
			}
			if(g>0)
				cam.setcamorigin(&_box);
		}

//	CVector v00(0,0,0,1);
//	setCenter(v00);
	}
	else
		cam.setcamorigin(&f->box);
//	cam.initZoom();
	cam.zoom(zr);

}

void CDraw::setCenter(CVector p)
{
	for (int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
		if(fig[i]->transselectedstate())
		{
			cam.setcamorigin(&fig[i]->box);
			return;
		}
		}
	}
//	cam.setcamorigin(NULL);


}
void CDraw::setinitzoom()
{
	candraw=true;
	forundoc(&cam,"Init");
	cam.initZoom();
	cam.setcamorigin(NULL);
	cam.zoom(1);
}
void CDraw::setfitzoom(double& d)
{
	candraw=true;
	forundoc(&cam,"Extent");
	cam.initZoom();
	cam.setcamorigin(NULL);
	cam.zoom(1);

	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	v1=v0.sgetscrtop();
	CPoint p(v0.x,v0.y);
    v0 = p;
	p.x=v1.x;
	p.y=v1.y;
	v1 =p;
	CRectangle r2(v0,v1);
	CAABB fb,fe=r2.getbox();
	fb.empty();
	for (int i=0;i<fit;i++) 
	{
		if(!(fig[i]->getLayer().clear))
		{
			fb.add(fig[i]->getbox());
		}
	}
	fb.add(page.getbox());
	v0=fb.corner(0);
	v1=fb.corner(2);
	float f1=absc(CVector(v0,v1));
	v0=fe.corner(0);
	v1=fe.corner(2);
	float f2=absc(CVector(v0,v1));
	float uy=f1/f2;

	v0=fb.corner(0);
	v1=fb.corner(1);
	f1=absc(CVector(v0,v1));
	v0=fe.corner(0);
	v1=fe.corner(1);
	f2=absc(CVector(v0,v1));
	float ux=f1/f2;

	float  u=ux>uy?ux:uy;
	rzoom=u;
	d=u;
	cam.setcamorigin(&fb);
	cam.zoom(u);
}

CRect CDraw::getgrid(CSize p)
{
		CVector v1(-(p.cx/2),-(p.cy/2)),v2((p.cx/2),-(p.cy/2)),\
			v3((p.cx/2),(p.cy/2)),v4(-(p.cx/2),(p.cy/2));//-425,550),v2(425,550),v3(425,-550),v4(-425,-550);
// CVector v1(0,0),v3(p.cx,p.cy);
	return CRect(v1,v3);
}

CPoint CDraw::getCenter()
{
	return cp;
}


double CDraw::getzoomrat()
{
	CTVector v;
	return cam.getzoom();//v.getzoomrat();
}



CVector CDraw::getMouse(CVector v)
{
	return v;

}
void CDraw::savePNG(CDC *hdc,CBitmap* bitmap, CFile &file)
{
	CImage img;
	FILE* hFile;	//file handle to write the image
	CString fpath=file.GetFilePath();
	const TCHAR* filename=(LPCTSTR)fpath;
	file.Close();
	
	bool h1=img.CreateFromHBITMAP((HBITMAP)*bitmap);
	bool h=img.Save(filename,CXIMAGE_FORMAT_PNG);
}
void CDraw::saveJPG(CDC *hdc,CBitmap* bitmap, CFile &file)
{
	CImage img;
	FILE* hFile;	//file handle to write the image
	CString fpath=file.GetFilePath();
	const TCHAR* filename=(LPCTSTR)fpath;
	file.Close();
	
	bool h1=img.CreateFromHBITMAP((HBITMAP)*bitmap);
	bool h=img.Save(filename,CXIMAGE_FORMAT_JPG);
}
void CDraw::saveBMP(CDC *hdc,CBitmap* bitmap, CFile &file)
{
	CImage img;
	FILE* hFile;	//file handle to write the image
	CString fpath=file.GetFilePath();
	const TCHAR* filename=(LPCTSTR)fpath;
	file.Close();
	
	bool h1=img.CreateFromHBITMAP((HBITMAP)*bitmap);
	bool h=img.Save(filename,CXIMAGE_FORMAT_BMP);
/*	HGLOBAL hDib;
	BITMAPFILEHEADER bmf;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpBi;
	DWORD dwSizeCT;
	
	hDib=img.ConvertDDBtoDIB(bitmap,hdc);
	ASSERT(hDib);
	bmf.bfType='MB';
	bmf.bfSize=sizeof(bmf)+::GlobalSize(hDib);
	bmf.bfReserved1=0;
	bmf.bfReserved2=0;
	lpBi=(LPBITMAPINFOHEADER)::GlobalLock(hDib);
	
	bi=*lpBi;
	dwSizeCT=img.GetColorTableSize(bi.biBitCount);
	bmf.bfOffBits=sizeof(bmf)+bi.biSize+dwSizeCT*sizeof(RGBQUAD);
	file.Write((char *)&bmf, sizeof(bmf));
	file.Write((LPSTR)lpBi, bi.biSize+dwSizeCT*sizeof(RGBQUAD)+bi.biSizeImage);
	::GlobalUnlock(hDib);
	::GlobalFree(hDib);
	*/
//	delete hmdc;

}

void CDraw::Initlib(CLibdialog& lbtctl)
{
	CTreeCtrl* tctl=(CTreeCtrl*)lbtctl.GetDlgItem(IDC_LIBT1);
	if(tctl->GetCount()!=-1) tctl->DeleteAllItems();
	HTREEITEM it2=tctl->InsertItem("In Memory Blocks",0,1);
	HTREEITEM it3=tctl->InsertItem("Local Blocks",0,1);
	HTREEITEM it4=tctl->InsertItem("Remote Blocks",0,1);
/*	CFileFind finder;
	bool bWorking=finder.FindFile("*.aff");
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	int tversion;
	HTREEITEM t;
	HTREEITEM it1=tctl->InsertItem(file.GetFileTitle(),0,1,it3);
	t=it1;

		file.Read(&tversion,sizeof(int));
		if(tversion==0)
		{
			int tfit;
			file.Read(&tfit,sizeof(int));
			for(int i=0;i<tfit;i++)
			{
				int lpos;
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				CString m;
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				m+=c;
				}
				t=tctl->InsertItem(m,2,2,it1,t);
				file.Read(&lpo,sizeof(lpo));
			}
		file.Close();
		}
	}*/
	_lbtctl=&lbtctl;
}
void CDraw::InitlibDxf(CLibdialog& lbtctl,CFile& file)
{

	_tctl=(CTreeCtrl*)_lbtctl->GetDlgItem(IDC_LIBT1);
	ASSERT(::IsWindow(_tctl->m_hWnd));
	try{
	if(::IsWindow(_tctl->m_hWnd))
	{
	HTREEITEM t=_tctl->GetFirstVisibleItem();
	if(_tctl->GetItemText(t)==_T("Local Blocks"))
	{
		HTREEITEM it1=_tctl->InsertItem(file.GetFileTitle(),0,1,t);
		int ffit=vblocks.size();
		int j0=0;
		CFigure* fg;
		for(int i=0;i<ffit;i++)
		{
			_tctl->InsertItem(vblocks[i]->getLibName().c_str(),2,2,it1);
		}
		return;

	}
	t=_tctl->GetNextVisibleItem(t);
	while(t!=NULL)
	{
		if(_tctl->GetItemText(t)==_T("Local Blocks"))
		{
			HTREEITEM it1=_tctl->InsertItem(file.GetFileTitle(),0,1,t);
			int ffit=vblocks.size();
			int j0=0;
			CFigure* fg;
			for(int i=0;i<ffit;i++)
			{
				_tctl->InsertItem(vblocks[i]->getLibName().c_str(),2,2,it1);
			}
			return;
		}
	}
	}
	}
	catch(...)
	{
	}
	vblocks.clear();
}
void CDraw::InitlibAff(CLibdialog& lbtctl,CFile& file)
{

	_tctl=(CTreeCtrl*)_lbtctl->GetDlgItem(IDC_LIBT1);
	int tversion;
	ASSERT(::IsWindow(_tctl->m_hWnd));
	try{
	if(::IsWindow(_tctl->m_hWnd))
	{
	HTREEITEM t=_tctl->GetFirstVisibleItem();
	if(_tctl->GetItemText(t)==_T("Local Blocks"))
	{
		HTREEITEM it1=_tctl->InsertItem(file.GetFileTitle(),0,1,t);
		t=it1;

		file.Read(&tversion,sizeof(int));
		if(tversion==0)
		{
			int tfit;
			file.Read(&tfit,sizeof(int));
			for(int i=0;i<tfit;i++)
			{
				int lpos;
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				CString m;
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				m+=c;
				}
				t=_tctl->InsertItem(m,2,2,it1,t);
				file.Read(&lpo,sizeof(lpo));
			}
		file.Close();
		}
		return;

	}
	t=_tctl->GetNextVisibleItem(t);
	while(t!=NULL)
	{
		if(_tctl->GetItemText(t)==_T("Local Blocks"))
		{
			HTREEITEM it1=_tctl->InsertItem(file.GetFileTitle(),0,1,t);
	t=it1;

		file.Read(&tversion,sizeof(int));
		if(tversion==0)
		{
			int tfit;
			file.Read(&tfit,sizeof(int));
			for(int i=0;i<tfit;i++)
			{
				int lpos;
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				CString m;
				char c;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				m+=c;
				}
				t=_tctl->InsertItem(m,2,2,it1,t);
				file.Read(&lpo,sizeof(lpo));
			}
		file.Close();
		}
			return;
		}
	}
	}
	}
	catch(...)
	{
	}
	vblocks.clear();
}
void CDraw::AddBlock(string& name)
{
	CLibS *lib=new CLibS(name.c_str());
	blocks.push_back(lib);
	vblocks.resize(vblocks.size()+1);
	vblocks[vblocks.size()-1]=lib;

}
void CDraw::AddBlock2(string& name,string& layer,string& handle,CVector vo)
{
	CLibS *lib=new CLibS(name.c_str());
	FLAYER blayer;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==layer.c_str())
		{
			blayer=*it;
			break;
		}
	}
	bool find=false;
	for(vector<CLibS*>::iterator it1=blocks.begin();it1!=blocks.end();it1++)
	{
		if((*it1)->getLibName()==name.c_str())
		{
			(*it1)->setLayer(blayer);
			(*it1)->setHandle(handle);
			(*it1)->setModelOrigin(vo);
			find=true;
			current_block=*it1;
		}
	}
	if(!find)
	{
		lib->setLayer(blayer);
		lib->setHandle(handle);
		lib->setModelOrigin(vo);
		vblocks.push_back(lib);
		current_block=lib;
	}
	_tctl=(CTreeCtrl*)_lbtctl->GetDlgItem(IDC_LIBT1);
	ASSERT(::IsWindow(_tctl->m_hWnd));
	try{
	if(::IsWindow(_tctl->m_hWnd))
	{
	HTREEITEM t=_tctl->GetFirstVisibleItem();
	if(_tctl->GetItemText(t)==_T("In Memory Blocks"))
	{
		_tctl->InsertItem(name.c_str(),2,2,t);
		return;

	}
	t=_tctl->GetNextVisibleItem(t);
	while(t!=NULL)
	{
		if(_tctl->GetItemText(t)==_T("In Memory Blocks"))
		{
			_tctl->InsertItem(name.c_str(),2,2,t);
			return;
		}
	}
	}
	}
	catch(...)
	{
	}

}
void CDraw::AddBlock3(string& name,float rot_angle,CVector vscale,CVector vo,CVector col_row_count,CVector col_row_spacing)
{
	int ffit=vblocks.size();
	int j0=0;
	CFigure* fg;
	for(int i=0;i<ffit;i++)
	{
		if(vblocks[i]->getLibName().c_str()==name)
		{
			fg=vblocks[i];
			
			string scount;
			CString sf;
			sf.Format(_T("%d"),count);
			scount=sf;
			fg->setHandle(scount);
			fg->setLayer(currlayer);
			fg->setcorevecor();
			fg->updatecore();
			SELECT s=full;
			fg->setselectmode(s);
			fg->setclick(true);
			fg->TranslateTo(vo);
			fg->scale(vscale.x,1);
			fg->scale(vscale.y,2);
			fg->scale(vscale.z,3);
			fg->rotate(rot_angle,3);
			create(fg);
			vs.push_back(fig[fit-1]);
			pastearray(NULL,false,col_row_count.x,col_row_count.y,col_row_spacing.x,col_row_spacing.y,1,0);
		}
	}
}

void CDraw::AddToBlock()
{
//	CLibS *lib=vblocks.back();
	if(fit==0) return;
	current_block->add(fig.back());
	fig[fit-1]=NULL;
	fig.resize(fit-1);
	fit--;
	sfit--;
	count--;
}
void CDraw::AddBreak(float u1,float u2)
{
	if(vs.empty()) return;
	vector<CVector> vec=vs[0]->getSvec();
	CVector uv=vec[2]-vec[0];
	float auv=absc(uv);
	if((u1>auv)||(u2>auv)) return;
	CVector v1=polarc(u1,argu(uv))+vec[0];
	CVector v2=polarc(u2,argu(uv))+vec[0];
//	breakcurve(v1);//vs[0]->getPoint(u1));
//	breakcurve(v2);//vs[0]->getPoint(u2));
	vs[0]->breakcurve(v1,v2);
//	breakcurve(vs[0]->getPoint(u1));
//	breakcurve(vs[0]->getPoint(u2));
	
}
void CDraw::Insertlib(CDC *hdc,CString &f, CString &l,CVector pos)
{
	CLibS *pLibs;
	CInter pInter;
	CFigure* fg;
	int ffit=vblocks.size();
	int j0=0;
	for(int i=0;i<ffit;i++)
	{
		if(vblocks[i]->getLibName().c_str()==l)
		{
			fg=vblocks[i];	
			string scount;
			CString sf;
			sf.Format(_T("%d"),count);
			scount=sf;
			fg->setHandle(scount);
			fg->setLayer(currlayer);
			fg->setcorevecor();
			fg->updatecore();
			SELECT s=full;
			fg->setselectmode(s);
			fg->setclick(true);
			fg->TranslateTo(pos);
			create(fg);
			vs.push_back(fig[fit-1]);
		}
	}
//	return;
	if(f==_T("In Memory Blocks"))
	{
			int ffit=vblocks.size();
			int j0=0;
			for(int i=0;i<ffit;i++)
			{
				if(vblocks[i]->getLibName().c_str()==l)
				{
					fg=vblocks[i];	
					string scount;
					CString sf;
					sf.Format(_T("%d"),count);
					scount=sf;
					fg->setHandle(scount);
					fg->setLayer(currlayer);
					fg->setcorevecor();
					fg->updatecore();
					SELECT s=full;
					fg->setselectmode(s);
					fg->setclick(true);
					fg->TranslateTo(pos);
					create(fg);
					vs.push_back(fig[fit-1]);
				}
			}

	}else
	{
	CFileFind finder;
	bool bWorking=finder.FindFile(_T("Library\/"+f+".aff"));
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	
		int ccount,ssfit,ffit;
	
		file.Read(&version,sizeof(int));
		if(version==0)
		{
			file.Read(&ffit,sizeof(int));
			int j0=0;

			for(int i=0;i<ffit;i++)
			{
				DWORD lpos,lpos1;
				file.Read(&lpos,sizeof(lpos));
				int lpo;
				file.Read(&lpo,sizeof(lpo));
				char c;
				CString m;
				for(int j=0;j<lpo;j++)
				{
				file.Read(&c,sizeof(c));
				m+=c;
				}
				lpos1=file.Read(&lpo,sizeof(lpo));
				if(m==l)
				{
					int hj;
					file.Seek(lpos,CFile::begin);
					file.Read(&hj,sizeof(hj));
					CFigure* f=NULL;
					switch(lpo)
					{
					case 0:
						{
							CLine* fl=new CLine(file);
							f=fl;
							break;
						}
					case 1:
						{
							CRectangle* fl=new CRectangle(file);
							f=fl;
							break;
						}
					case 2:
						{
							CQLine* fl=new CQLine(file);
							f=fl;
							break;
						}
					case 3:
						{
							CBezier* fl=new CBezier(file);
							f=fl;
							break;
						}
					case 4:
						{
							CCercle* fl=new CCercle(file);
							f=fl;
							break;
						}
					case 5:
						{
							CLibS* fl=new CLibS(file,hdc);
							f=fl;
							break;
						}
					case 6:
						{
							CTextCad* fl=new CTextCad(file,hdc);
							f=fl;
							break;
						}
					case 7:
						{
							CImage* fl=new CImage(hdc,file);
							f=fl;
							break;
						}
					case 8:
						{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					CDim* fl=new CDim(file,hdc);
					f=fl;
						}
					case 9:
						{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					CDimA* fl=new CDimA(file,hdc);
					f=fl;
					}
					case 10:
						{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					CDimL* fl=new CDimL(file,hdc);
					f=fl;
				}

					}
					file.Seek(lpos1,CFile::begin);

						string scount;
						CString sf;
						sf.Format(_T("%d"),count);
						scount=sf;
						f->setHandle(scount);
						f->setLayer(currlayer);
//						f->setUndoparam();
						f->setcorevecor();
						f->updatecore();
						SELECT s=full;
						f->setselectmode(s);
						f->setclick(true);
//						f->setMultselect(true);
//						f->selectSM(hdc);

/*						CFigure* h=pInter.paste(f->getCenter(),pos,f);
						delete f;
						h->draw(hdc);
						SELECT s=full;
						h->setselectmode(s);
						h->setclick(true);
						h->setMultselect(true);
						h->selectSM(hdc);
*/
						f->TranslateTo(pos);
						f->updatecore();
						create(f);
						vs.push_back(fig[fit-1]);
	/*					vhan.push_back(scount);
						sfit++;
						count++;
						Bminus=true;
						fig.resize(fig.size()+1);
						fig[j0+fit]=h;
						vs.push_back(fig[j0+fit]);
						j0++;*/
						break;

				}
			}
//			fit+=j0;
		}
		file.Close();
		candraw=true;
	}
}
}

void CDraw::unfill(CDC *hdc)
{
	for (int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
			if(fig[i]->transselectedstate())
			{
				fig[i]->unfill(hdc);

			}
		}
	}

}
bool CDraw::fsnapPoint(CVector &p, CDC* hdc)
{

	snappy.executePoint(p,hdc);
	return true;
}
bool CDraw::fsnapInit()
{

	snappy.init();
	return true;
}
bool CDraw::fsnap(CVector &p, CDC* hdc)
{

	snappy.execute(p,hdc);
/*	bool r=false;
	for(int i=0;i<fit;i++)
	{
		if(!fig[i]->transselectedstate())
		{
		r=r || fig[i]->fsnap(p,hdc,""); 
		if (r) return r;
		}
	}
	p.x-=fmod(p.x,10);
	p.y-=fmod(p.y,10);
	p.z-=fmod(p.z,10);
	return r;*/
	return false;
}

void CDraw::setsnap(bool b)
{
	snap=b;
}

void CDraw::initlayer(CListCtrl &tcl)
{
	laylist=&tcl;
	LVITEM it;
	it.mask=LVIF_TEXT|LVIF_IMAGE;
	tcl.DeleteAllItems();
	int i=0;
	for(vector<FLAYER>::iterator iter=veclayer.begin();iter<veclayer.end();iter++)
	{
		it.pszText=(LPTSTR)(LPCTSTR)iter->name;
		it.iItem=i;
		it.iSubItem=0;
		it.iImage=(iter->on==true)?0:1;
		tcl.InsertItem(&it);
	}
	_tcl=&tcl;
	setcurlayer(tcl,currlayer.name);
}

void CDraw::addlayer(CListCtrl &tcl,CString ltext)
{
	LVITEM it;
	it.mask=LVIF_TEXT|LVIF_IMAGE|\
			LVIF_STATE;
	it.iItem=tcl.GetItemCount();
	it.iSubItem=0;
	it.stateMask=LVIS_SELECTED;
	it.state=INDEXTOSTATEIMAGEMASK(1);
	it.iImage=0;
	it.pszText=(LPTSTR)(LPCTSTR)ltext;
	tcl.InsertItem(&it);
	_tcl=&tcl;
	FLAYER g;
	g.handle++;
	g.name=ltext;
	g.on=true;
	g.clear=false;
	g.lock=false;
	veclayer.push_back(g);

}

void CDraw::removelayer(CString &txt)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==txt)
		{
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getLayer().name==txt)
				{
					free(fig[i]);
					fig[i]=NULL;
				}
			}
			CFigure** j=(CFigure**)calloc(fit,sizeof(CFigure*));
			int t=0;
			for(i=0;i<fit;i++)
			{
				if(fig[i]!=NULL)
				{
					j[t]=fig[i];
					t++;
				}
			}
			fit=t;
			for(i=0;i<fit;i++)
			{
				fig[i]=j[i];
			}
			veclayer.erase(it);
			return;
		}
	}

}
void CDraw::uplayer(CString &txt)
{
	FLAYER fl;
	for(vector<FLAYER>::iterator it=veclayer.begin()+1;it<veclayer.end();it++)
	{
		if(it->name==txt)
		{
			fl=*(it-1);
			*(it-1)=*it;
			*it=fl;
		}

	}
}
void CDraw::downlayer(CString &txt)
{
	FLAYER fl;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end()-1;it++)
	{
		if(it->name==txt)
		{
			fl=*(it+1);
			*(it+1)=*it;
			*it=fl;
		}

	}
	candraw=true;
}

void CDraw::setclayer(CString txt,int state)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==txt)
		{
//			it->on=(state==0)?true:false;
			it->clear=!(it->clear);
//			it->lock=!(it->on);

			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getLayer().name==txt)
				{
					fig[i]->setLayer(*it);
				}
			}
			candraw=true;
			return;
		}
	}

}

void CDraw::setcurlayer(CListCtrl& tcl,CString txt)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==txt)
		{
			it->lock=false;
			it->clear=false;
			it->on=true;
			currlayer=*it;
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getLayer().name==txt)
				{
					fig[i]->setLayer(*it);
				}else
				{
					FLAYER yt=fig[i]->getLayer();
					yt.on=false;
					fig[i]->setLayer(yt);
				}

			}
			break;
		}else{
			it->on=false;		
		}
	}
	  LVITEM rl;
//	  CString st;
	  rl.mask=LVIF_IMAGE;
	  rl.iSubItem=0;
	for(int i=0;i<tcl.GetItemCount();i++)
	{
	  rl.iItem=i;
	  tcl.GetItem(&rl);
	  if(tcl.GetItemText(i,0)==txt)
	  {
		  rl.iImage=2;
		  tcl.SetItem(&rl);
	  }
	  if((tcl.GetItemText(i,0)!=txt)&&(rl.iImage==2))
	  {
		  rl.iImage=0;
		  tcl.SetItem(&rl);
	  }
	}

}
void CDraw::setCurrentLayer(string& txt)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==txt.c_str())
		{
			it->lock=false;
			it->clear=false;
			it->on=true;
			currlayer=*it;
			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getLayer().name==txt.c_str())
				{
					fig[i]->setLayer(*it);
				}else
				{
					FLAYER yt=fig[i]->getLayer();
					yt.on=false;
					fig[i]->setLayer(yt);
				}
			}
			break;
		}
	}
}

void CDraw::lockcurlayer(CListCtrl &tcl, CString txt)
{
   
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
		{
			if(it->name==txt)
			{
				it->clear=false;
				it->on=false;
				it->lock=true;
				currlayer=*it;
							
				for(int i=0;i<fit;i++)
				{
					if(fig[i]->getLayer().name==txt)
					{
											
						fig[i]->setLayer(*it);
						
					}
				}
				break;
			}
		}
		  LVITEM rl;
	//	  CString st;
		  rl.mask=LVIF_IMAGE;
		  rl.iSubItem=0;
	
		for(int i=0;i<tcl.GetItemCount();i++)
		{
		  rl.iItem=i;
		  tcl.GetItem(&rl);
		  if(tcl.GetItemText(i,0)==txt)
		  {
			  rl.iImage=3;
			  tcl.SetItem(&rl);
		  }
		 		
		}




}

void CDraw::unlockcurlayer(CListCtrl &tcl, CString txt)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
		{
			if(it->name==txt)
			{
				it->clear=false;
				it->on=true;
				it->lock=false;
				currlayer=*it;
				for(int i=0;i<fit;i++)
				{
					if(fig[i]->getLayer().name==txt)
					{
						fig[i]->setLayer(*it);
					}
				}
				break;
			}
		}
		  LVITEM rl;
	//	  CString st;
		  rl.mask=LVIF_IMAGE;
		  rl.iSubItem=0;
		for(int i=0;i<tcl.GetItemCount();i++)
		{
		  rl.iItem=i;
		  tcl.GetItem(&rl);
		  if(tcl.GetItemText(i,0)==txt)
		  {
			  rl.iImage=4;
			  tcl.SetItem(&rl);
		  }
		 
		}


}



void CDraw::initlayer()
{
	LVITEM it;
	it.mask=LVIF_TEXT|LVIF_IMAGE;
	laylist->DeleteAllItems();
	int i=0;
	for(vector<FLAYER>::iterator iter=veclayer.begin();iter<veclayer.end();iter++)
	{
		it.pszText=(LPTSTR)(LPCTSTR)iter->name;
		it.iItem=i;
		it.iSubItem=0;
		it.iImage=(iter->on==true)?0:1;
		laylist->InsertItem(&it);
	}
	_tcl=laylist;
	setcurlayer(*laylist,currlayer.name);

}

void CDraw::setobjinfo(CString aut, CString desc, CString name, double cost)
{
//	for(int i=0;i<fit;i++)
//	{
//		if(fig[i]->transselectedstate())
//		{
			FINFO k;
			if(aut!="") k.author=aut;
			if(desc!="") k.description=desc;
			if(name!="") k.name=name;
			if(cost!=0) k.cost=cost;
			vs[0]->setinfo(k);
//		}
//	}

}

void CDraw::addobject(CTreeCtrl &mtree,CDC *hdc)
{
	CLibS lib;
	for(int i=0;i<fit;i++)
	{
		if((fig[i]->transselectedstate())&&(fig[i]->getName()==lib.getName()))
		{
			HTREEITEM it=mtree.GetSelectedItem();
			int im=-1,imsel=-1;
			mtree.GetItemImage(it,im,imsel);
			if(im!=2)
			{
				mtree.InsertItem(fig[i]->getInfName(),2,2,it);

				CFileFind finder;
				bool bWorking=finder.FindFile(mtree.GetItemText(it)+".aff");
				while(bWorking)
				{
					bWorking=finder.FindNextFile();
					CFile file(finder.GetFilePath(),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
					int g=fit+1;
					file.Seek(sizeof(int),CFile::begin);

					int ffit;
					file.Read(&ffit,sizeof(int));
					file.Seek(sizeof(int),CFile::begin);
					g=ffit+1;
					file.Write(&g,sizeof(int));
					CTVector tv;
					tv.openfile(file);

					int sz;
					int j=0;
					LONG ofs;
					for(int ih=0;ih<ffit;ih++)
					{
						ofs=file.Read(&sz,sizeof(sz));
						if(sz==0)
						{
							CLine f;
							ofs=f.Readfile(file);
//							ofs=file.Seek(sizeof(CLine),CFile::current);
						}
						if(sz==1)
						{
							CRectangle f;
							ofs=f.Readfile(file);
//							ofs=file.Seek(sizeof(CRectangle),CFile::current);
						}
						else
						if(sz==2)
						{
							CQLine f;
							ofs=f.Readfile(file);
//							ofs=file.Seek(sizeof(CQLine),CFile::current);
						}
						else
						if(sz==3)
						{
							CBezier f;
							ofs=f.Readfile(file);
//							ofs=file.Seek(sizeof(CBezier),CFile::current);
						}
						else
						if(sz==4)
						{
							CCercle f;
							ofs=f.Readfile(file);
//							ofs=file.Seek(sizeof(CCercle),CFile::current);
						}
						else
						if(sz==5)
						{
							CLibS *ls=new CLibS(file,hdc);
							ofs=file.GetPosition();
							delete ls;
						}
						else
						if(sz==6)
						{
							ofs=file.Seek(sizeof(CTextCad),CFile::current);
						}
						else
						if(sz==7)
						{
							ofs=file.Seek(sizeof(CImage),CFile::current);
						}

					}
					int k=file.SeekToEnd()-ofs;
					BYTE* b=new BYTE[k];

					file.Seek(ofs,CFile::begin);
					file.Read(b,k);
					CString nm;
					sz=5;
					file.Seek(ofs,CFile::begin);
					file.Write(&sz,sizeof(int));
					fig[i]->savefile(file);
					file.Write(b,k);
					delete b;

					int ii;
					file.Read(&ii,sizeof(int));
					char c;
					FLAYER vcurrlayer;
					vcurrlayer.name.Empty();
					for(int jj=0;jj<ii;jj++)
					{
					file.Read(&c,sizeof(c));
					vcurrlayer.name.Insert(jj,c);
					}
					file.Read(&vcurrlayer.handle,sizeof(int));
					file.Read(&vcurrlayer.on,sizeof(bool));
					file.Read(&vcurrlayer.clear,sizeof(bool));
					file.Read(&vcurrlayer.lock,sizeof(bool));
					int siz;
					vector<FLAYER> vveclayer;
					file.Read(&siz,sizeof(int));
					vveclayer.clear();
					for(j=0;j<siz;j++)
					{
						FLAYER fl;
						int i;
						file.Read(&i,sizeof(int));
						char c;
						for(int j=0;j<i;j++)
						{
						file.Read(&c,sizeof(c));
						fl.name.Insert(j,c);
						}
						file.Read(&fl.handle,sizeof(int));
						file.Read(&fl.on,sizeof(bool));
						file.Read(&fl.clear,sizeof(bool));
						file.Read(&fl.lock,sizeof(bool));
						vveclayer.push_back(fl);
					}

					file.Seek(ofs,CFile::begin);

					//CString nm;
					sz=5;
					file.Write(&sz,sizeof(int));
					fig[i]->savefile(file);

					file.Write(&ii,sizeof(int));
					for(jj=0;jj<ii;jj++)
					{
					char c=vcurrlayer.name[jj];
					file.Write(&c,sizeof(char));
					}
					file.Write(&vcurrlayer.handle,sizeof(int));
					file.Write(&vcurrlayer.on,sizeof(bool));
					file.Write(&vcurrlayer.clear,sizeof(bool));
					file.Write(&vcurrlayer.lock,sizeof(bool));
					file.Write(&siz,sizeof(int));

					for(vector<FLAYER>::iterator iter=vveclayer.begin();iter<vveclayer.end();iter++)
					{
						int i=iter->name.GetLength();
						file.Write(&i,sizeof(int));
						for(int j=0;j<i;j++)
						{
							char c=iter->name[j];
							file.Write(&c,sizeof(c));
						}
						file.Write(&iter->handle,sizeof(int));
						file.Write(&iter->on,sizeof(bool));
						file.Write(&iter->clear,sizeof(bool));
						file.Write(&iter->lock,sizeof(bool));
					}
					file.Close();
				}

			}
		}
	}
}

void CDraw::removeobject(CTreeCtrl &mtree,CDC* hdc)
{
	CLibS lib;
	bool del=false;

			HTREEITEM it=mtree.GetSelectedItem();
			int im=-1,imsel=-1;
			mtree.GetItemImage(it,im,imsel);
			if(im!=0)
			{

				CFileFind finder;
				HTREEITEM pit=mtree.GetParentItem(it);
				bool bWorking=finder.FindFile(mtree.GetItemText(pit)+".aff");
				while(bWorking)
				{
					bWorking=finder.FindNextFile();
					CFile file(finder.GetFilePath(),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
					int g=fit+1;
					file.Seek(sizeof(int),CFile::begin);
					CFile* df=file.Duplicate();

					int ffit;
					file.Read(&ffit,sizeof(int));
					file.Seek(sizeof(int),CFile::begin);
					g=ffit-1;
					file.Write(&g,sizeof(int));
					CTVector tv;
					tv.Readfile(file);

					int sz;
					int j=0;
					LONG ofs,tof1,tof2;
					for(int ih=0;ih<ffit;ih++)
					{
						if(!del)
						{
							ofs=file.Read(&sz,sizeof(sz));
						}
						else
						{
							df->Read(&sz,sizeof(int));
							file.Write(&sz,sizeof(int));
						}
						if(sz==0)
						{
							CLine f;
							ofs=f.Readfile(file);
							//ofs=file.Seek(sizeof(CLine),CFile::current);
						}
						if(sz==1)
						{
							CRectangle f;
							ofs=f.Readfile(file);
					//		ofs=file.Seek(sizeof(CRectangle),CFile::current);
						}
						else
						if(sz==2)
						{
							CQLine f;
							ofs=f.Readfile(file);
							//ofs=file.Seek(sizeof(CQLine),CFile::current);
						}
						else
						if(sz==3)
						{
							CBezier f;
							ofs=f.Readfile(file);
						//	ofs=file.Seek(sizeof(CBezier),CFile::current);
						}
						else
						if(sz==4)
						{
							CCercle f;
							ofs=f.Readfile(file);
						//	ofs=file.Seek(sizeof(CCercle),CFile::current);
						}
						else
						if(sz==5)
						{
							if(!del)
							{
							ofs=file.GetPosition();
							CLibS *ls=new CLibS(file,hdc);

								if(ls->getInfName()==mtree.GetItemText(it))
								{
									DWORD gt=file.GetPosition();
									tof1=df->Seek(file.GetPosition(),CFile::begin);
									gt=df->GetPosition();
									tof2=file.Seek(ofs,CFile::begin);
									del=true;
									mtree.DeleteItem(it);
								}
							delete ls;

							}
							else
							{
								
								CLibS *ls=new CLibS(*df,hdc);
								ls->savefile(file);
								delete ls;

							}
						}
						else
						if(sz==6)
						{
							ofs=file.Seek(sizeof(CTextCad),CFile::current);
						}
						else
						if(sz==7)
						{
							ofs=file.Seek(sizeof(CImage),CFile::current);
						}

					}
					int ii;
					df->Read(&ii,sizeof(int));
					char c;
					FLAYER vcurrlayer;
					vcurrlayer.name.Empty();
					for(int jj=0;jj<ii;jj++)
					{
					df->Read(&c,sizeof(c));
					vcurrlayer.name.Insert(jj,c);
					}
					df->Read(&vcurrlayer.handle,sizeof(int));
					df->Read(&vcurrlayer.on,sizeof(bool));
					df->Read(&vcurrlayer.clear,sizeof(bool));
					df->Read(&vcurrlayer.lock,sizeof(bool));
					
					int siz;
					vector<FLAYER> vveclayer;
					df->Read(&siz,sizeof(int));
					vveclayer.clear();
					for(j=0;j<siz;j++)
					{
						FLAYER fl;
						int i;
						df->Read(&i,sizeof(int));
						char c;
						for(int j=0;j<i;j++)
						{
						df->Read(&c,sizeof(c));
						fl.name.Insert(j,c);
						}
						df->Read(&fl.handle,sizeof(int));
						df->Read(&fl.on,sizeof(bool));
						df->Read(&fl.clear,sizeof(bool));
						df->Read(&fl.lock,sizeof(bool));
						vveclayer.push_back(fl);
					}

					CString nm;

					file.Write(&ii,sizeof(int));
					for(jj=0;jj<ii;jj++)
					{
					char c=vcurrlayer.name[jj];
					file.Write(&c,sizeof(char));
					}
					file.Write(&vcurrlayer.handle,sizeof(int));
					file.Write(&vcurrlayer.on,sizeof(bool));
					file.Write(&vcurrlayer.clear,sizeof(bool));
					file.Write(&vcurrlayer.lock,sizeof(bool));

					file.Write(&siz,sizeof(int));

					for(vector<FLAYER>::iterator iter=vveclayer.begin();iter<vveclayer.end();iter++)
					{
						int i=iter->name.GetLength();
						file.Write(&i,sizeof(int));
						for(int j=0;j<i;j++)
						{
							char c=iter->name[j];
							file.Write(&c,sizeof(c));
						}
						file.Write(&iter->handle,sizeof(int));
						file.Write(&iter->on,sizeof(bool));
						file.Write(&iter->clear,sizeof(bool));
						file.Write(&iter->lock,sizeof(bool));
					}
					file.Close();
					df->Close();
				}

			}
}

FINFO CDraw::getobif()
{
	FINFO f;
	int l=vs.size();
//	for(int i=0;i<l;i++)
//	{
//		if(fig[i]->transselectedstate())
//		{
			f=vs[0]->getInfo();
//		}
//	}
	return f;

}

void CDraw::surface(CString type,float vthick,bool vctop,bool vcbot,CDC *hdc,int ext)
{
	int l=0;
	int pk=fit;
	vector<CBezier*> fg(50);
	CBezier pB;

	int j=vs.size();
	CLine pLine1;
	CString line_name=pLine1.getName();
	CString rectangle_name=pRectangle.getName();

	for(int i=0;i<j;i++)
	{
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		if(!(vs[i]->getLayer()).clear)
		{
				if((vs[i]->getName()==line_name)\
					||(vs[i]->getName()==rectangle_name))
				{
				//	vector<CVector> *v=fig[i]->getpt();
					fg[l]=new CBezier(vs[i]);
					l++;

				//	delete v;
				}else if((vs[i]->getName()==pCircle.getName())\
					||(vs[i]->getName()==pB.getName()))
				{
				fg[l]=new CBezier;
				fg[l]->copy((CBezier*)vs[i]);
				if(fg[l]->isSurface())
				{
					delete fg[l];
					continue;
				}
					l++;
				}
		}
	}
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;

	if(l>0)
	{
		if(type=="simplerevol")
		{
		vector<CBezier*> fga(2);
		fga[0]=fg[0];
		for(int i=1;i<l;i++)
		{
		CBezier *ftp=new CBezier;
		fga[1]=fg[i];

		ftp->surface(type,fga,2,vthick);

		ftp->surface(hdc);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}
		else
		if(type=="extrus2")
		{
		int n=2;
		vector<CBezier*> fga(2);
		fga[n-1]=fg[l-1];
		for(int i=0;i<l-1;i++)
		{
		CBezier *ftp=new CBezier;
		fga[0]=fg[i];

		ftp->surface(type,fga,2,vthick);

		ftp->surface(hdc);
		ftp->cap(vctop,vcbot);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}
		else
		if(type=="extrus")
		{
		vector<CBezier*> fga(2);
		for(int i=0;i<l;i++)
		{
		CBezier *ftp=new CBezier;
		fga[0]=fg[i];
		ftp->EXTRUSC=ext;

		ftp->surface(type,fga,1,vthick);

		ftp->surface(hdc);
		ftp->cap(vctop,vcbot);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}else
		if(type=="gextrusion")
		{
//		int n=l;
//		vector<CBezier*> fga(l);
//		fga[n-1]=fg[l-1];
//		for(int i=0;i<l-1;i++)
//		{
		CBezier *ftp=new CBezier;
//		fga[0]=fg[i];

		ftp->surface(type,fg,l,vthick);

		ftp->surface(hdc);
		ftp->cap(vctop,vcbot);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
//		}
		}else
		{
		CBezier *ftp=new CBezier;
		ftp->surface(type,fg,l,vthick);
		ftp->surface(hdc);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		for(int j=0;j<l;j++)
		{
			delete fg[j];
		}



	}
}


void CDraw::join(bool del,CDC *hdc)
{
	int l=0;
	int pk=fit;
	vector<CBezier*> fg(50);
	CBezier pB;

	int j=vs.size();
	CLine pLine1;
	CString line_name=pLine1.getName();
	CString rectangle_name=pRectangle.getName();

	for(int i=0;i<j;i++)
	{
		if(!(vs[i]->getLayer()).clear)
		{
				if((vs[i]->getName()==line_name)\
					||(vs[i]->getName()==rectangle_name))
				{
				//	vector<CVector> *v=fig[i]->getpt();
					fg[l]=new CBezier(vs[i]);

				//	delete v;
				}else if((vs[i]->getName()==pCircle.getName())\
					||(vs[i]->getName()==pB.getName()))
				{
				fg[l]=new CBezier;
				fg[l]->copy((CBezier*)vs[i]);
				if(fg[l]->isSurface())
				{
					delete fg[l];
					continue;
				}
				}
			l++;
		}
	}

	if(l>0)
	{
		fg.resize(l);
		CBezier *ftp=new CBezier;
		ftp->buildspline(&fg);
		ftp->surface(hdc);

		fig.resize(fig.size()+1);
		ftp->clear();
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		for(int j=0;j<l;j++)
		{
			delete fg[j];
		}
	}
}





void CDraw::degel(CDC *hdc)
{
	int pk=fit;

	for(int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
			if(fig[i]->transselectedstate())
			{
				if((fig[i]->getName()==CString("CBezier"))||(fig[i]->getName()==CString("CCercle")))
				{
					CBezier *ftp=new CBezier;
			
					ftp->copy((CBezier*)fig[i]);
					ftp->degel();

					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					//m=_msize(fig);
					ftp->clear();
					string scount;
					CString sf;
					sf.Format(_T("%d"),count);
					scount=sf;
					ftp->setHandle(scount);
					ftp->setLayer(currlayer);
//					ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(scount);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
					fit=pk;


				}
			}
		}
	}


}

void CDraw::volume(CDC *hdc)
{
	int l=0;
	int pk=fit;
	vector<CBezier*> fg(50);
	for(int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
			if(fig[i]->transselectedstate())
			{
				fg[l]=new CBezier;
			fg[l]->copy((CBezier*)fig[i]);
			l++;
			}
		}
	}
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;

	if(l>1)
	{
		CBezier *ftp=new CBezier;

/*		if((fg[0]->getName()==pBezier->getName())||(fg[0]->getName()==pCircle.getName()))
		{
		if((fg[1]->getName()==pBezier->getName())||(fg[1]->getName()==pCircle.getName()))
		{
		CBezier *nh=new CBezier;
		nh->copy((CBezier*)fg[0]);
		delete nh;

		CBezier *f1=new CBezier;
		f1->copy((CBezier*)fg[0]);
		CBezier *f2=new CBezier;
		f2->copy((CBezier*)fg[1]);

		ftp->surface(f1,f2);
		delete f1;
		delete f2;
		}
		}
		if((fg[0]->getName()==pBezier->getName())||(fg[0]->getName()==pCircle.getName()))
		{
		if(fg[1]->getName()==CString("CLine"))
		{
		CBezier *f1=(CBezier*)fg[0];
		CLine *f2=(CLine*)fg[1];

		ftp->surface(f1,f2);
		}
		}
		if(fg[0]->getName()==CString("CLine"))
		{
		if((fg[1]->getName()==pBezier->getName())||(fg[1]->getName()==pCircle.getName()))
		{
		CLine *f1=(CLine*)fg[0];
		CBezier *f2=(CBezier*)fg[1];

		ftp->surface(f2,f1);
		}
		}

		ftp->surface(hdc);
		fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		ftp->setUndoparam();
		vhan[sfit]=count;
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;*/

		//ftp->surface(type,fg,l);

		ftp->volume(hdc);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;


	}
	else
	if(l==1)
	{
		CBezier *ftp=new CBezier;
      fg[0]->volume(hdc);
  		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=fg[0];
		pk++;
		fit=pk;

	}

}

void CDraw::perpective(CString s)
{
 CCAM v;
 CAABB box;
 for (int i=0;i<fit;i++)
 {
	 box.add(fig[i]->getbox());
 }
 if(s=="perspective")
 {
 v.setPerspective(box);
 }else
 {
	 v.setCamview(s,box);
 }
 candraw=true;
}

void CDraw::fill(CDC *hdc, CPoint pos)
{
	bool b=false;
	CTextCad textc;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=textc.getName()))
		{
			fig[i]->setfillpoint(pos);
			if(!fig[i]->isClose()) fig[i]->closecurve(pos,hdc);
			fig[i]->setInit();
			b=true;
			
		}
//	}
	}

}

void CDraw::setpixel(int w, int h)
{
 CVector v;
 v.setScreen(w,h);
 CCAM m;
 CTVector vt;
 vt.initVect();
}
CSize CDraw::setpixel0(int w, int h)
{
 CVector v;
 CSize wh=v.getScreen();
 v.setScreen(w,h);
 return wh;
/* CCAM m;
 CTVector vt;
 vt.initVect();*/
}

void CDraw::setInterest(CSubject *s)
{
	CTextCad textc;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=textc.getName()))
		{
			fig[i]->setInterest(s);
			
		}
//	}
	}

}

void CDraw::setTexture(CString s,CDC* hdc)
{
	CTextCad textc;
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (vs[i]->getName()!=textc.getName())
		{
			vs[i]->setTexture(s,hdc);
			grid(hdc,vs[i]->box);
		}
//	}
	}

}

const CFigure** CDraw::getFvec()
{
 return NULL;//fig;
}

const int * CDraw::getVFint()
{
	return &fit;
}

void CDraw::setsnapplane(CString plane)
{
	CTVector v;
	v.setsnapplane(plane);
}

void CDraw::setFFD(CString option)
{
	CTextCad textc;
//	CBezier bz;
//	CCercle cl;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=textc.getName()))
		{
			if((fig[i]->getName()==pBezier->getName())||(fig[i]->getName()==pCircle.getName()))
			{
			CBezier* b=(CBezier*) fig[i];
			b->setFFDon(option);
			}
			
		}
//	}
	}

}

void CDraw::setWnd(CCadView *cad)
{
	CMesh m;
	m.setWnd(cad);
	render->setWnd(cad);
	CTextCad text;
	text.setWnd((CWnd*)cad);
}
CRect CDraw::getBox()
{
	CVector v0=box.corner(2);
	CVector v1=box.corner(1);
	return CRect(v0,v1);
}
CRect CDraw::getAllBox()
{
	CAABB box2;
	int j=0;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(!it->clear)
		{

			for (int i=0;i<fit;i++) 
			{
				if(fig[i]->getLayer().name==it->name)
				{
					box2.add(fig[i]->box);
					j++;
				}
			}
		}
	}
	return CRect(box2.corner(2),box2.corner(1));
}
void CDraw::drawforbmp(CDC *hdc)
{

	pLine.setRDC(hdc);
	
	CMesh m;
//	m.Bdraw();
//	box.draw(hdc);
	for (int i=0;i<fit;i++) 
		{
		if(!(fig[i]->getLayer().clear))
		{
			//if(fig[i]->ptbegin.size()!=0)
			//{
			fig[i]->draw(hdc);
			//}
		}
		}
//	m.Edraw(hdc);

/*	CLibS slib;
	group(slib);
	slib.updatecore();
	slib.draw(hdc);*/
}

void CDraw::smooth(int u, int v, int w)
{
	CTextCad textc;
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (vs[i]->getName()==pBezier->getName())
		{
			((CBezier*)vs[i])->smooth(u,v,w);
		}
//	}
	}

}

void CDraw::setgeneralInterest(CSubject *s)
{
	s->RegisterInterest(this);
}

void CDraw::SendNotify(CString s, void *param[])
{
	if(s=="Light")
	{
		float *spec=(float*)param[0];
		CBezier::M_spec.r=*spec;
		CBezier::M_spec.g=*spec;
		CBezier::M_spec.b=*spec;spec++;
		CBezier::m_gls=*spec;spec++;
		
		spec=(float*)param[1];
		CBezier::G_amb.r=*spec;spec++;
		CBezier::G_amb.g=*spec;spec++;
		CBezier::G_amb.b=*spec;spec++;

		spec=(float*)param[2];
		CBezier::S_diff.r=*spec;spec++;
		CBezier::S_diff.g=*spec;spec++;
		CBezier::S_diff.b=*spec;spec++;

		spec=(float*)param[3];
		CBezier::lsou.x=*spec;spec++;
		CBezier::lsou.y=*spec;spec++;
		CBezier::lsou.z=*spec;spec++;
	}else
	if(s=="Camera")
	{
		float *spec=(float*)param[0];
		float xp,yp,zp;
		xp=*spec;spec++;
		yp=*spec;spec++;
		zp=*spec;spec++;
		
		float xt,yt,zt;
		spec=(float*)param[1];
		xt=*spec;spec++;
		yt=*spec;spec++;
		zt=*spec;spec++;

		spec=(float*)param[2];
		CVector v1;
		cam.setfarplane(*spec);spec++;
		cam.setnearplane(*spec);

		float *ispec=(float*)param[3];
		cam.setfov(*ispec);
	
		CVector v(xp,yp,zp);
		CVector vt(xt,yt,zt);
		cam.setcam(v,vt);//vx,vy,vz,v);




		void* param[4];
		v=cam.getcamor();
		float pos[3];
		pos[0]=v.x;
		pos[1]=v.y;
		pos[2]=v.z;
		v=cam.gettarget();
		float target[3];
		target[0]=v.x;
		target[1]=v.y;
		target[2]=v.z;
		
		v.x=cam.getnearplane();
		v.y=cam.getfarplane();
		float plane[2];
		plane[0]=v.y;
		plane[1]=v.x;
		
		v.x=cam.getfov();
		float fov[1];
		fov[0]=v.x;

		param[0]=pos;
		param[1]=target;
		param[2]=plane;
		param[3]=fov;


		for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
		{
			(*it)->SendNotify("Camera",param);
		}

	}

}

void CDraw::getlightpara(void **param[])
{
		int **spec=(int**)param[0];
		**spec=CBezier::S_spec.r*255;spec++;
		**spec=CBezier::S_spec.g*255;spec++;
		
		spec=(int**)param[1];
		**spec=CBezier::G_amb.r*255;spec++;
		**spec=CBezier::G_amb.g*255;spec++;
		**spec=CBezier::G_amb.b*255;spec++;

		spec=(int**)param[2];
		**spec=CBezier::S_diff.r*255;spec++;
		**spec=CBezier::S_diff.g*255;spec++;
		**spec=CBezier::S_diff.b*255;spec++;

		float **spec1=(float**)param[3];
		**spec1=CBezier::lsou.x;spec1++;
		**spec1=CBezier::lsou.y;spec1++;
		**spec1=CBezier::lsou.z;spec1++;
}



void CDraw::setcamInterest(CSubject *s)
{
	setgeneralInterest(s);
}

void CDraw::getcampara(void **param[])
{
	CVector v;
		float **spec=(float**)param[0];
		v=cam.getcamor();
//		v.worldi();

		**spec=v.x;spec++;
		**spec=v.y;spec++;
		**spec=v.z;spec++;
		
		spec=(float**)param[1];
		v=cam.gettarget();
		**spec=v.x;spec++;
		**spec=v.y;spec++;
		**spec=v.z;spec++;

		spec=(float**)param[2];
		**spec=v.getfarplane();spec++;
		**spec=v.getnearplane();

		int** ispec=(int**)param[3];
		**ispec=cam.getfov();


}

CVector CDraw::getobject(CDC *hdc, CVector pos)
{
	CVector v;
	for(int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
			if(fig[i]->inRegion(pos))
			{
				v=fig[i]->box.center();
				v.worldi();
				return v;
			}
		}
	}
	pos.worldi();
	return pos; 


}

void CDraw::setVmode(CDC* hdc)
{
	CTextCad textc;
	CLibS pl;

	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		if (vs[i]->getName()==pBezier->getName())
		{
			((CBezier*)vs[i])->setFFDon();
		}
		if (vs[i]->getName()==pCircle.getName())
		{
			((CBezier*)vs[i])->setFFDon();
		}
		if((vs[i]->getName()!=pl.getName())&&(vs[i]->getName()!=textc.getName()))
		{
			vs[i]->setPtOn();
		}
	}
	cleardraw(hdc);


}
void CDraw::setBmode(CDC* hdc)
{
	if(fit==0) return;
	CTextCad textc;
	CBezier pB;
	CLibS pl;
	if(snap) fsnapInit();	
	int g=vs.size();
	
		if(fig[fit-1]->getName()==textc.getName())
		{
			((CTextCad*)fig[fit-1])->PtinRegion(CVector(-1E100,-1E100));
		}
	if(g==0 && endDraw)
	{
		if(fig[fit-1]->getName()==pB.getName())
		{
			pBezier->initLBezier();
			((CBezier*)fig[fit-1])->setBlockon();
//			forundo(fit-1,"create update spline");

		}
		if(fig[fit-1]->getName()==pCircle.getName())
		{
			((CBezier*)fig[fit-1])->initLBezier();
			((CBezier*)fig[fit-1])->setBlockon();
		}
		
	}
	endDraw=false;
	for (int i=0;i<g;i++)
	{
		if (vs[i]->getName()==pBezier->getName())
		{
			((CBezier*)vs[i])->setBlockon();
		}
		if (vs[i]->getName()==pCircle.getName())
		{
			((CBezier*)vs[i])->setBlockon();
		}
//		if(vs[i]->getName()==pl.getName())
//		{
//			vs[i]->getbox(hdc);
//		}
		if((vs[i]->getName()!=pl.getName())&&(vs[i]->getName()!=textc.getName()))
		{
			vs[i]->select_full();
		}
	}
	cleardraw(hdc);

}

void CDraw::cap(bool top, bool bot, bool g,CDC *hdc)
{
	int l=0;
	int pk=fit;
	CBezier pB;

	int j=vs.size();

	for(int i=0;i<j;i++)
	{
		if(!(vs[i]->getLayer()).clear)
		{
				if((vs[i]->getName()==pCircle.getName())\
					||(vs[i]->getName()==pB.getName()))
				{
					if(((CBezier*)vs[i])->isSurface())
					{
						if(g)
							((CBezier*)vs[i])->cap(top,bot);
						else
							((CBezier*)vs[i])->cap0(top,bot);
					}
				}
		}
	}


}

void CDraw::edittext()
{
	int l=0;
	int pk=fit;
	CBezier pB;

	int j=vs.size();

	for(int i=0;i<j;i++)
	{
		if(!(vs[i]->getLayer()).clear)
		{
		if(vs[i]->getName()=="CTextCad")
			{
				((CTextCad*)vs[i])->edittext();
				return;
			}
		}
	}

}

void CDraw::AddLine(float left, float top, float right, float bottom)
{
		CVector begin(left,top);
		CVector end(right,bottom);

		pLine.setPtsBegin(begin);
		pLine.create(end);
		if (pLine.getCharge())
		{
		CLine *ftp= new CLine;
		
		pLine.clear();
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		pLine.setHandle(scount);
		undoList.push("create");
		pLine.setLayer(currlayer);
		pLine.setcorevecor();
		*ftp=pLine;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		pLine.initL();
		}

}

void CDraw::AddRectangle(float left, float top, float right, float bottom)
{
		CVector begin(left,top);
		CVector end(right,bottom);

		pRectangle.setPtsBegin(begin);
		pRectangle.create(end);

		if (pRectangle.getCharge())
		{
		CRectangle *ftp= new CRectangle;
		pRectangle.clear();
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		pRectangle.setHandle(scount);
		undoList.push("create");
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		*ftp=pRectangle;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pRectangle.initL();
		}
}

void CDraw::AddRectangle(CVector v1, CVector v2)
{
		CVector begin(v1);
		CVector end(v2);

		pRectangle.setPtsBegin(begin);
		pRectangle.create(end);

		if (pRectangle.getCharge())
		{
		CRectangle *ftp= new CRectangle;
		pRectangle.clear();
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		pRectangle.setHandle(scount);
		undoList.push("create");
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		*ftp=pRectangle;
		vhan.push_back(scount);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pRectangle.initL();
		}

}

void CDraw::AddLine(vector<CVector> &v)
{
	v_current=v.back();
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CLine(v);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;

}

void CDraw::AddSpline(vector<CVector> &v,bool _fit,CDC *hdc)
{
	v_current=v.back();
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CBezier(3,v,_fit,hdc);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}
void CDraw::AddSpline2(vector<CVector> &v,vector<float> &fv,bool _fit,CDC *hdc)
{
	v_current=v.back();
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CBezier(3,v,fv,_fit,hdc);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}
void CDraw::AddLayer(string& layer_name,int layer_status,int layer_color,string& layer_linetype,int layer_lineweight)
{
	try{
	if(::IsWindow(_tcl->m_hWnd))
	{
	LVITEM it;
	it.mask=LVIF_TEXT|LVIF_IMAGE|\
			LVIF_STATE;
	it.iItem=_tcl->GetItemCount();
	it.iSubItem=0;
	it.stateMask=LVIS_SELECTED;
	it.state=INDEXTOSTATEIMAGEMASK(1);
	it.iImage=0;
	it.pszText=(LPTSTR)(LPCTSTR)layer_name.c_str();
	_tcl->InsertItem(&it);
	}
	}catch(...)
	{
	}
	FLAYER g;
	g.handle++;
	g.name=layer_name.c_str();
	g.on=(layer_color>0);
	g.clear=false;
	g.line_color=layer_color;
	g.line_type=layer_linetype.c_str();
	g.lock=layer_status;
	
	veclayer.push_back(g);
}
void CDraw::AddTextStyle(string& style_name,string font_file, float fixed_height,float width_factor)
{
	FSTYLE g;
	g.handle++;
	g.name=style_name;
	g.font=(font_file!="")?font_file:style_name;
	g.fixed_height=fixed_height;
	g.width_factor=width_factor;
	
	vecstyle.push_back(g);
}
void CDraw::AddText(CDC *hdc,CVector &v,string& _text,float yheight,string facename)
{
	v_current=v;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CTextCad();
	CHARFORMAT cf;
	((CTextCad*)fig[fit])->getfont(cf);
	bool find=false;
	for(vector<FSTYLE>::iterator iter=vecstyle.begin();iter<vecstyle.end();iter++)
	{

		if(iter->name==facename)
		{
			yheight=(iter->fixed_height==0)?yheight:iter->fixed_height;
			CDC dc;
			dc.CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
			LONG yPerInch1=dc.GetDeviceCaps(LOGPIXELSY);
			LONG yPerInch=1;
			cf.dwMask=3892314127;
			cf.dwEffects=0;
			cf.yOffset=0;
			cf.crTextColor=0;
			cf.yHeight=yheight*1440*iter->width_factor/yPerInch;
			strcpy(cf.szFaceName,iter->font.c_str());
			find=true;
			((CTextCad*)fig[fit])->setFStyle(&*iter);
			break;
		}
	}
	if(!find)
	{
	cf.dwMask=3892314127;
	cf.dwEffects=0;
	cf.yOffset=0;
	cf.crTextColor=0;
	cf.yHeight=yheight*1440;
	strcpy(cf.szFaceName,facename.c_str());
	}
//	CString sf=_text.c_str();
//	sf.
//	_text="";
	((CTextCad*)fig[fit])->assign(hdc,v,CString(_text.c_str()),&cf);
	LOGFONT font;
	COLORREF ccl;
	((CTextCad*)fig[fit])->setfont(NULL,font,ccl,cf);
		
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}
void CDraw::AddViewport(CDC *hdc,CVector &v0_wcs,CVector &v0_dcs,CVector& vo_ucs,CVector& vox_ucs,CVector& voy_ucs,float zoom_pc,float paper_width,float paper_height)
{
	CSize p(paper_width,paper_height);
//	setpixel(paper_width,paper_height);
//	setPage(p);
	CTVector vt;
	CVector v;
	float u1=v.getscrtop().x-v.getscrbot().x;
//	m.setcam(vo_ucs,CVector(0,0,1,0));
	vt.setWorld(CVector(1,0,0,0),CVector(0,1,0,0),CVector(0,0,1,0),v0_wcs);
//	vt.setCam(vox_ucs,voy_ucs,CVector(0,0,1,0),vo_ucs);
	float u=u1/paper_width;
	u=u<0?-u:u;
//	cam.initCam();
	setzoomrat(1/u);
//	cam.zoom(1/u);

}

void CDraw::AddCircle(CVector v, float radius)
{
	v_current=v;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle(v,radius);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;

}

void CDraw::AddCircle(CVector p1, CVector p2, CVector p3)
{
	v_current=p3;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle(p1,p2,p3);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;

}

void CDraw::AddCircle(CVector p1, CVector p2)
{
	v_current=p2;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle(p1,p2);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}
void CDraw::Delete(int i)
{
	vector<CFigure*>::iterator iter;
			iter=find(fig.begin(),fig.end(),fig[i]);
			if(iter!=fig.end())
			{
			delete *iter;
			fig.erase(iter);fit--;
			}
			candraw=true;
}
void CDraw::AddArc(CVector p1,float radius,float startangle,  float endangle)
{
	float start_a=(startangle*2*pi)/360;
	CVector vstart=p1+polarc(radius,start_a);
	float end_a=endangle;
	end_a=(end_a*2*pi)/360;;
	float angle=end_a-start_a;
	AddArc(p1,vstart,angle);
}
void CDraw::AddArc(CVector p1,CVector p2,  float radius)
{
	v_current=p1;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle();
	((CCercle*)fig[fit])->drawArc(p1,p2,radius);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}

void CDraw::AddArc(CVector p1, CVector p2, CVector p3)
{
	v_current=p3;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle();//p1,p2,p3,true);
	((CCercle*)fig[fit])->drawArc(p1,p2,p3);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}

void CDraw::AddArc(CVector p1, CVector p2)
{
	v_current=p2;
	undoList.push("create");
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	vhan.push_back(scount);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle();//p1,p2,true);
	((CCercle*)fig[fit])->drawArc(p1,p2);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}

CFigure* CDraw::getFigure(int i)
{
	return fig[i];
}

short CDraw::getFigures()
{
	return fig.size();
}

void CDraw::Select(CFigure *f,CDC* hdc,bool full)
{
	
	bool locale=false;

	for (int i=0;i<fit;i++) 
		{
		if(fig[i]->ptbegin.size()!=0)
		{
		if(!(fig[i]->getLayer()).clear)
		{

			if(fig[i]->getRotstate())
			{
				fig[i]->InitRotState();
				fig[i]->setMultselect(false);
			}
		}
		}
		}
//	vector<CFigure*> vs;
	for(i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
		if(!(fig[i]->getLayer()).lock)
		{
			if(fig[i]==f)
			{
				if (full) fig[i]->select_full();
				else
					fig[i]->select_node(i);
				if(find(vs.begin(),vs.end(),fig[i])==vs.end())
				vs.push_back(fig[i]);
			}
		}
		}
	}
	
	int j=vs.size();

	for(i=0;i<j;i++)
	{
		vs[i]->setMultselect(true);
		vs[i]->setclick(true);
		vs[i]->selectSM(hdc);
		vs[i]->getLayer().lock;
		vs[i]->getLayer().clear;
	}

//    getBinfo(point);
}

void CDraw::Move(CFigure *f, CVector v)
{
	v_current=v_current+v;

	if(f!=NULL)
		f->Translate(v);
	else
	{
		int j=vs.size();
		for (int i=0;i<j;i++)
		{
			vs[i]->Translate(v);
		}
	}
}
void CDraw::MoveTo(CFigure *f, CVector v)
{
	v_current=v;

	if(f!=NULL)
	{
		CVector v1=f->box.center();
		v1=v-v1;
		f->Translate(v1);
	}
	else
	{
		int j=vs.size();
		for (int i=0;i<j;i++)
		{
			CVector v1=vs[i]->box.center();
			v1=v-v1;
			vs[i]->Translate(v1);
		}
	}
}

void CDraw::Move(CFigure *f, int node, CVector v)
{
	v_current=v_current+v;
	if(f!=NULL)
		f->Translate(v,node);
	else
	{
		int j=vs.size();
		for (int i=0;i<j;i++)
		{
			vs[i]->Translate(v,node);
			return;
		}
	}
}
void CDraw::MoveTo(CFigure *f, int node, CVector v)
{
	v_current=v;
	if(f!=NULL)
	{
		CVector v1=f->box.center();
		v1=v-v1;
		f->TranslateNodeTo(v,node);
	}
	else
	{
		int j=vs.size();
		for (int i=0;i<j;i++)
		{
			CVector v1=vs[i]->box.center();
			v1=v-v1;
			vs[i]->TranslateNodeTo(v,node);
			return;
		}
	}
}

void CDraw::Close(CFigure *f, CDC *hdc)
{
	f->closecurve(CVector(0,0),hdc);
}



void CDraw::Chamfer(CFigure *f1, float u1, CFigure *f2, float u2,float length)
{
		if(((u1<0)||(u1>1))||((u2<0)||(u2>1)))
		{
			AfxMessageBox("The two parameter values should be in the Interval [0,1]");
			return;
		}
		setChamfparam(length);
		int nbc=0;
		CVector point;
		CRectangle pR;
		CLine pL;
		CQLine pQ;
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		if((f1->getName()==pL.getName())||(f1->getName()==pR.getName())||(f1->getName()==pQ.getName()))
		{
			vector<CVector> test;
			point=f1->getPoint(u1);
			test=f1->getSelectvec(point);
			if(test.size()!=0)
			{
				if(test[0]!=test[2])
				{
				undoList.push("create");
				vhan.push_back(f1->gethandle());
				sfit++;
				IA=new CDimA;
				IA->addSLChamf(test,f1);
				nbc++;
				}
			}
		}
		else
		{
			AfxMessageBox("You can chamfer only line");
			return;
		}
		if(nbc==0) return;
		if((f2->getName()==pL.getName())||(f2->getName()==pR.getName())||(f2->getName()==pQ.getName()))
		{
		vector<CVector> test;
		point=f2->getPoint(u2);
		test=f2->getSelectvec(point);
			if(test.size()!=0)
			{
				if(test[0]!=test[2])
				{
				undoList.push("create");
				vhan.push_back(f2->gethandle());
				sfit++;
				IA->addSLChamf(test,f2);
				CFigure* lk=IA->getChargeChamf();
					if(lk!=0)
					{
					CLine* llg=new CLine;
					llg->createobj(lk->ptbegin,lk->ptend);
					llg->clear();
					llg->setInit();
					llg->setHandle(scount);
					undoList.push("create");
					llg->setLayer(currlayer);
					llg->setcorevecor();
					
					
					vhan.push_back(scount);

					fig.resize(fig.size()+1);
					fig[fit]=llg;fit++;
					sfit++;
					count++;
					Bminus=true;
					}
				delete lk;
				delete IA;

				valid=true;
				}
			}
		}
		else
		{
			AfxMessageBox("You can chamfer only line");
			return;
		}

}
void CDraw::Fillet(CFigure *f1, float u1, CFigure *f2, float u2,float length)
{
		if(((u1<0)||(u1>1))||((u2<0)||(u2>1)))
		{
			AfxMessageBox("The two parameter values should be in the Interval [0,1]");
			return;
		}
		setFiltparam(length);
		int nbc=0;
		CVector point;
		CRectangle pR;
		CLine pL;
		CQLine pQ;
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		if((f1->getName()==pL.getName())||(f1->getName()==pR.getName())||(f1->getName()==pQ.getName()))
		{
			vector<CVector> test;
			point=f1->getPoint(u1);
			test=f1->getSelectvec(point);
			if(test.size()!=0)
			{
				if(test[0]!=test[2])
				{
				undoList.push("create");
				vhan.push_back(f1->gethandle());
				sfit++;
				IA=new CDimA;
				IA->addSLChamf(test,f1);
				nbc++;
				}
			}
		}
		else
		{
			AfxMessageBox("You can Fillet only line");
			return;
		}
		if(nbc==0) return;
		if((f2->getName()==pL.getName())||(f2->getName()==pR.getName())||(f2->getName()==pQ.getName()))
		{
		vector<CVector> test;
		point=f2->getPoint(u2);
		test=f2->getSelectvec(point);
			if(test.size()!=0)
			{
				if(test[0]!=test[2])
				{
				IA->addSLChamf(test,f2);
				CCercle* lk=new CCercle;
				bool ko=IA->getChargeFilt(lk);
				delete IA;
				if(ko)
				{
				undoList.push("create");
				vhan.push_back(f2->gethandle());
				sfit++;
				lk->clear();
				lk->setInit();
				lk->setHandle(scount);
				undoList.push("create");
				lk->setLayer(currlayer);
				lk->setcorevecor();
					
				vhan.push_back(scount);

				fig.resize(fig.size()+1);
				fig[fit]=lk;fit++;
				sfit++;
				count++;
				Bminus=true;
				}
				else
					delete lk;

				valid=true;
				}
			}
		}
		else
		{
			AfxMessageBox("You can chamfer only line");
			return;
		}

}

void CDraw::Group(CFigure *f1, CFigure *f2)
{
	
		CLibS *lib=new CLibS;
		CLine pL;
		CRectangle pR;
//		CCercle pC;
		CBezier pB;
		CLibS pli;
		CTextCad textc;
		CImage image;
		
		vector<CVector> *arr;
		bool connect=false;

		for(int i=0;i<fit;i++)
		{
//				arr=fig[i]->translatep(fig[i]->getCenter(),fig[i]->getCenter()); To check back
						
				if(fig[i]->getName()==pL.getName())
				{
					pL=*(CLine*)fig[i];
					pL.createobj(*arr,*(arr+1));
					delete[] arr;
					CLine *ftp= new CLine;
					*ftp=pL;
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==pR.getName())
				{
					pR=*(CRectangle*)fig[i];
					pR.addvec(*arr,*(arr+1));
					delete[] arr;
					CRectangle *ftp= new CRectangle;
					*ftp=pR;
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==image.getName())
				{
					image=*(CImage*)fig[i];
					image.addvec(*arr,*(arr+1));
					delete[] arr;
					CImage *ftp= new CImage;
					*ftp=image;
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
					pCircle.copy(*(CCercle*)fig[i]);
					pCircle.addvec(*arr,*(arr+1));
					delete[] arr;
					CCercle *ftp= new CCercle;
					ftp->copy(pCircle);
//					*ftp=pCircle;
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==pB.getName())
				{
				//	pBezier=*(CBezier*)fig[i];
				//	pBezier->addvec(*arr,*(arr+1));
					delete[] arr;
					CBezier *ftp= new CBezier;
					ftp->copy(fig[i]);//pBezier);
					lib->add(ftp);
				//	pBezier->initVect();
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==textc.getName())
				{
					textc=*(CTextCad*)fig[i];
					textc.addvec(*arr,*(arr+1));
					delete[] arr;
					CTextCad *ftp= new CTextCad;
					*ftp=textc;
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}else
				if(fig[i]->getName()==lib->getName())
				{
					pli.Copy(*(CLibS*)fig[i]);
					pli.addvec(*arr,*(arr+1));
					delete[] arr;
					CLibS *ftp= new CLibS;
					ftp->Copy(pli);
					lib->add(ftp);
					delete fig[i];
					fig[i]=NULL;
				}			
					connect=true;
			}
		if (!connect)
		{
			delete lib;
		}
		else
		{
			CFigure *f[50];
			int j=0;
			for(int i=0;i<fit;i++)
			{
				if(fig[i]!=NULL)
				{
					f[j]=fig[i];
					j++;
				}
			}
			fit=j;
			for(i=0;i<fit;i++)
			{
				fig[i]=f[i];
			}
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		lib->setHandle(scount);
//		lib->setUndoparam();
		lib->setLayer(currlayer);
		/*vhan[sfit]=count;*/vhan.push_back(scount);
		sfit++;
		count++;

			fig[fit]=lib;
			fit++;
			vs.clear();
			sefit=0;
		}
}

bool CDraw::Trim(CDC* hdc,CVector v,bool side)
{
	int j1=vs.size();
	vector<CVector> v1;
	v1.push_back(v);
	int fit2=fit;
	CFigure * ft=new CFigure;
	CAABB aabb;
			for (int i=0;i<j1;i++)
			{
				aabb.add(vs[i]->box);
				ft->add(vs[i]);
			}
//			ft->closecurve(CVector(0,0),NULL);
	for (int j=0;j<fit2;j++)
	{
		if (fig[j]->inRegion(v))
		{
			aabb.add(fig[j]->box);
//			for (int i=0;i<j1;i++)
			{
//				fig[j]->Trim(vs[i],side);
//				if(fig[j]==vs[i]) continue;
				vector<CFigure*> figh;
//				figh=fig[j]->Trim(v1,vs[i],side);
				figh=fig[j]->Trim(v1,ft,side);
				try{
				if(figh.size()!=0)
				{
					forundo(vs[0],"delete");
					fig.erase(find(fig.begin(),fig.end(),fig[j]));
					fit--;
					fit2=fit;
					int jfit=figh.size();
					for(int j=0;j<jfit;j++)
					{
						create(figh[j]);
					}
				}
				}catch(...)
				{
				AfxMessageBox(_T("Trim Undo and Object Creation Error"));
				}
			}
			grid(hdc,aabb);
			return true;
		}
	}

	return true;
}
bool CDraw::setpara(CString l)
{
	CTextCad textc;
	int j1=vs.size();
	bool c=false;
	for (int j=0;j<j1;j++)
	{
		if (vs[j]->getName()==textc.getName())
		{
			CTextCad *text=(CTextCad*)fig[j];
			text->setpara(l);
			c=true;
			
		}
	}
	if(c) return true;
	for (j=0;j<fit;j++)
	{
	if (fig[j]->getName()==textc.getName())
	{
		CTextCad *text=(CTextCad*)fig[j];
		if (text->WndVisible())
		{
			text->setpara(l);
			break;
		}
	}
	}
	return false;

}
void CDraw::getfont(CHARFORMAT& lf)
{
	CTextCad textc;
	int j1=vs.size();
	bool c=false;
	for (int j=0;j<j1;j++)
	{
		if (vs[j]->getName()==textc.getName())
		{
			CTextCad *text=(CTextCad*)vs[j];
			text->getfont(lf);
			return;
		}
	}
	for (j=0;j<fit;j++)
	{
	if (fig[j]->getName()==textc.getName())
	{
		CTextCad *text=(CTextCad*)fig[j];
		if (text->WndVisible())
		{
			text->getfont(lf);
			return;
		}
	}
	}
}
void CDraw::rotate(float u, short sens)
{
	int g=vs.size();
	CAABB bo;
	for (int i=0;i<g;i++)
	{
		bo.add(vs[i]->box);
	 } 
	u=(u*2*pi)/360;
	for (i=0;i<g;i++)
	{
//		vs[i]->setRotateCenter(bo.center());
		vs[i]->rotate(u,sens);
	 } 
}
void CDraw::scale(float u, short sens)
{
	int g=vs.size();

	CAABB bo;
	for (int i=0;i<g;i++)
	{
		bo.add(vs[i]->box);
	 } 
	for (i=0;i<g;i++)
	{
		vs[i]->setRotateCenter(bo.center());
		vs[i]->scale(u,sens);
	 } 
}

void CDraw::mirror(CFigure* f,bool v)
{
	CInter pInt;
	CCercle *pC;
	CTextCad textc;
	CLibS pl;
	CLibS *pLib=NULL;//=new CLibS;


	int pk=fit;
	bool sel=false;
	
	if (f->getName()==pLine.getName())
	{

	for (int j=0;j<fit;j++) 
		{
			string scount;
			CString sf;
			sf.Format(_T("%d"),count);
			scount=sf;
			if (fig[j]->inselectedstate())
			{
				fig[j]->setHandle(scount);
				undoList.push("create");
	//				fig[j]->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				fig[j]->setMultselect(false);
				if(fig[j]->getName()==pLine.getName())
				{
				pLine=*(CLine*)fig[j];
				pInt.mirror(f,fig[j],&pLine);
				CLine *ftp= new CLine;
				*ftp=pLine;
				if(!v)
				{
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
	//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;

				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=ftp;
				}
				}else
				if(fig[j]->getName()==pRectangle.getName())
				{
				pRectangle=*(CRectangle*)fig[j];
				pInt.mirror(f,fig[j],&pRectangle);
				CRectangle *ftp= new CRectangle;
				*ftp=pRectangle;
				if(!v)
				{
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
	//						ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=ftp;
				}
				}else
				if(fig[j]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)fig[j]);
				pInt.mirror(f,fig[j],&pCircle);
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
				if(!v)
				{
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
	//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=ftp;
				}
				}else
				if(fig[j]->getName()==pBezier->getName())
				{
				pBezier->copy((CBezier*)fig[j]);
				pInt.mirror(f,fig[j],pBezier);
				CBezier *ftp= new CBezier;
				ftp->copy(pBezier);
				if(!v)
				{
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
	//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=ftp;
				}
				}else
				if(fig[j]->getName()==pl.getName())
				{
				pLib=(CLibS*)fig[j];
				pLib=pInt.mirror(f,(CLibS*)fig[j]);
				if(!v)
				{
				pLib->clear();
				pLib->setHandle(scount);
				pLib->setLayer(currlayer);
				undoList.push("create");
	//				pLib->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=pLib;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=pLib;
				}
				}
				else
				if(fig[j]->getName()==textc.getName())
				{
				textc=*(CTextCad*)fig[j];
				pInt.mirror(f,fig[j],&textc);
				CTextCad *ftp= new CTextCad;
				*ftp=textc;
				if(!v)
				{
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
	//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(scount);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
				else
				{
					sel=true;
					fig[j]=pLib;
				}
				}
			}
		}
	}
	fit=pk;
	candraw=true;
}

void CDraw::copy(CFigure *f, bool cp)
{
	CInter pInt;
	CCercle pC;
	CTextCad textc;
	CLibS pl;
	CLibS *pLib=NULL;//=new CLibS;


	int pk=fit;
	bool sel=false;


		if (f->getName()==pLine.getName())
		{
			for (int j=0;j<fit;j++) 
				{
					string scount;
					CString sf;
					sf.Format(_T("%d"),count);
					scount=sf;
					if (fig[j]->inselectedstate())
					{
						fig[j]->setHandle(scount);
						undoList.push("create");
		//				fig[j]->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						fig[j]->setMultselect(false);
						if(fig[j]->getName()==pLine.getName())
						{
						pLine=*(CLine*)fig[j];
						pInt.copybyL(f,fig[j],&pLine);
						CLine *ftp= new CLine;
						*ftp=pLine;
						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);

						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;

						/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
						////m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pRectangle.getName())
						{
						pRectangle=*(CRectangle*)fig[j];
						pInt.copybyL(f,fig[j],&pRectangle);
						CRectangle *ftp= new CRectangle;
						*ftp=pRectangle;
						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
//ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
						////m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pC.getName())
						{
						pC.copy(*(CCercle*)fig[j]);
						pInt.copybyL(f,fig[j],&pC);
						CCercle *ftp= new CCercle;
						ftp->copy(pC);
						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
//ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
						////m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pBezier->getName())
						{
						pBezier->copy((CBezier*)fig[j]);
						pInt.copybyL(f,fig[j],pBezier);
						CBezier *ftp= new CBezier;
						ftp->copy(pBezier);
						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
						////m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pl.getName())
						{
						pLib=(CLibS*)fig[j];
						pLib=pInt.copybyL(f,(CLibS*)fig[j]);
						if(!cp)
						{
						pLib->clear();
						pLib->setHandle(scount);
						pLib->setLayer(currlayer);
						undoList.push("create");
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						fig.resize(fig.size()+1);
						fig[pk]=pLib;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=pLib;
						}
						}
						else
						if(fig[j]->getName()==textc.getName())
						{
						textc=*(CTextCad*)fig[j];
						pInt.copybyL(f,fig[j],&textc);
						CTextCad *ftp= new CTextCad;
						*ftp=textc;
						if(!cp)
						{
						ftp->clear();
						ftp->setHandle(scount);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(scount);
						sfit++;
						count++;
						/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
						////m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							sel=true;
							fig[j]=pLib;
						}
						}
					}
				}
			}
	fit=pk;
	candraw=true;

}

void CDraw::copy2(float d)
{
	if(vs.empty()) return;
	CInter pInter;
	vector<CLibS>* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CImage im;

	CFigure *arr;
	CFigure* pbulk=new CFigure;

	int pk=vs.size();

	for (int i=0;i<fit;i++)
	{
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
//		if (fig[i]->inselectedstate())
		{
			if(vs[i]->getName()==im.getName()) continue;

			if(vs[i]->getName()!=pLibs.getName())
			{
				arr=vs[i]->copy2(d,pbulk);
				vs[i]->setMultselect(false);

				if((vs[i]->getName()==pLine.getName())||(vs[i]->getName()==pRectangle.getName()))
				{
				pLine=*(CLine*)vs[i];
				pLine.createobj(arr->ptbegin,arr->ptend);
				CLine *ftp= new CLine;
				*ftp=pLine;
				fig.resize(fig.size()+1);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
				vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(vs[i]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)vs[i]);
				pCircle.addvec(arr->ptbegin,arr->ptend);
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
				fig.resize(fig.size()+1);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
				vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(vs[i]->getName()==pBezier->getName())
				{
				pBezier->copy((CBezier*)vs[i]);
				pBezier->addvec(arr->ptbegin,arr->ptend);
				CBezier *ftp= new CBezier;
				ftp->copy(pBezier);
				fig.resize(fig.size()+1);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
				vhan.push_back(scount);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
			}
			else
			{
			CLibS *ftp;

			ftp=pInter.copy2(vs[i]->getCenter(),d,pbulk,(CLibS*)vs[i]);
			fig.resize(fig.size()+1);
				ftp->clear();
				ftp->setHandle(scount);
				ftp->setLayer(currlayer);
				undoList.push("create");
				vhan.push_back(scount);
				sfit++;
				count++;
			fig[pk]=ftp;
			pk++;
			}
			}
		}

	fit=pk;
	candraw=true;

	delete pbulk;
}

void CDraw::surface2(CString type,float vthick,short cap,int ext)
{
	bool vctop=cap&&1;
	bool vcbot=cap&&2;
	int l=0;
	int pk=fit;
	vector<CBezier*> fg(50);
	CBezier pB;

	int j=vs.size();
	CLine pLine1;
	CString line_name=pLine1.getName();
	CString rectangle_name=pRectangle.getName();

	for(int i=0;i<j;i++)
	{
		if(!(vs[i]->getLayer()).clear)
		{
				if((vs[i]->getName()==line_name)\
					||(vs[i]->getName()==rectangle_name))
				{
					fg[l]=new CBezier(vs[i]);
					l++;
				}else if((vs[i]->getName()==pCircle.getName())\
					||(vs[i]->getName()==pB.getName()))
				{
				fg[l]=new CBezier;
				fg[l]->copy((CBezier*)vs[i]);
				if(fg[l]->isSurface())
				{
					delete fg[l];
					continue;
				}
					l++;
				}
		}
	}

	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	if(l>0)
	{
		if(type=="simplerevol")
		{
		vector<CBezier*> fga(2);
		fga[0]=fg[0];
		for(int i=1;i<l;i++)
		{
		CBezier *ftp=new CBezier;
		fga[1]=fg[i];

		ftp->surface(type,fga,2,vthick);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}
		else
		if(type=="extrus2")
		{
		int n=2;
		vector<CBezier*> fga(2);
		fga[n-1]=fg[l-1];
		for(int i=0;i<l-1;i++)
		{
		CBezier *ftp=new CBezier;
		fga[0]=fg[i];
		ftp->surface(type,fga,2,vthick);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}
		else
		if(type=="extrus")
		{
		vector<CBezier*> fga(2);
		for(int i=0;i<l;i++)
		{
		CBezier *ftp=new CBezier;
		fga[0]=fg[i];
		ftp->EXTRUSC=ext;

		ftp->surface(type,fga,1,vthick);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		}else
		if(type=="gextrusion")
		{
		CBezier *ftp=new CBezier;
		ftp->surface(type,fg,l,vthick);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}else
		{
		CBezier *ftp=new CBezier;
		ftp->surface(type,fg,l,vthick);
		ftp->cap(vctop,vcbot);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->setHandle(scount);
		ftp->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig[pk]=ftp;
		pk++;
		fit=pk;
		}
		for(int j=0;j<l;j++)
		{
			delete fg[j];
		}
	}
}

void CDraw::LookAt(CVector pos, CVector target)
{
	
		cam.setcam(pos,target);//vx,vy,vz,v);

		void* param[4];
		CVector v=cam.getcamor();
		float vpos[3];
		vpos[0]=v.x;
		vpos[1]=v.y;
		vpos[2]=v.z;
		v=cam.gettarget();
		float vtarget[3];
		vtarget[0]=v.x;
		vtarget[1]=v.y;
		vtarget[2]=v.z;
		
		v.x=cam.getnearplane();
		v.y=cam.getfarplane();
		float plane[2];
		plane[0]=v.y;
		plane[1]=v.x;
		
		v.x=cam.getfov();
		float fov[1];
		fov[0]=v.x;

		param[0]=vpos;
		param[1]=vtarget;
		param[2]=plane;
		param[3]=fov;

		for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
		{
			(*it)->SendNotify("Camera",param);
		}

}

void CDraw::setText(CString text)
{
/*	CTextCad textc;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==textc.getName())
		{
			if(fig[i]->transselectedstate())
			{
			 ((CTextCad*)fig[i])->setText(text);

			}
		}
	}
*/	
}

void CDraw::editobj(CDC* hdc)
{

	for(int i=0;i<fit;i++)
	{
		if(fig[i]->transselectedstate())
		{
		 fig[i]->editobj(hdc);

		}
	}

}
void CDraw::editobj(CVector point)
{

	for(int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
		if(!(fig[i]->getLayer()).lock)
		{
			B=fig[i]->PtinRegion(point);
			if(B) 
			{
			fig[i]->editobj(point);
			break;
			}
		}
		}
	}

}

void CDraw::setPage(CSize p)
{
//	setpixel(p.cx,p.cy);
	CTVector tv;
	tv.pushTransform();
	tv.initVect();
	tv.endT();
	tv.VpushTransform();
	tv.VinitVect();
	tv.VendT();
	CPoint p0=CPoint(0,0);
	CPoint p1=p0+p;
	page=CRectangle(p0,p1);
	page.TranslateTo(getcamor());
	tv.VpopTransform();
	tv.popTransform();

}

CRect CDraw::getPage()
{
	CRect r;
	page.updatecore();
	r.SetRect(page.ptbegin[0],page.ptbegin[2]);
	return r;
}
CPoint CDraw::PrepareImage()
{
//	printpage.updatecore();
//	page.updatecore();

	forundo(&page,"Memento");
//	page.TranslateTo(printpage.box.center());
	CVector v1=printpage.ptbegin[0];//box.center();
	v1.z=0;
	CPoint po1=v1;

//	CVector v2=page.ptbegin[3];//.box.center();
	CAABB box2;
	int j=0;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(!it->clear)
		{

			for (int i=0;i<fit;i++) 
			{
				if(fig[i]->getLayer().name==it->name)
				{
					box2.add(fig[i]->box);
					j++;
				}
			}
		}
	}
	CVector v2=box2.corner(2);
	CAABB box3=box;
	box=box2;
	v2=v2;
	CPoint po3=v2;

	cam.initCam();
	box2.empty();
	box2.add(v2);
	cam.setcamtopleft(&box2);
//	cam.initZoom();
//	if(fittopage)
//		print_scale=getFitPrintRatio();
	setzoomrat(print_scale);
	box=box3;
//	cam.Translate(CVector(v1.x-v2.x,v2.y-v1.y));
//	cam.Translate(CVector(v2.x-v1.x,v1.y-v2.y));
	CPoint p09=v1;
	CPoint p08=v2;
	return p08;
}

CPoint CDraw::PreparePrint()
{
//	printpage.updatecore();
//	page.updatecore();

	forundo(&page,"Memento");
//	page.TranslateTo(printpage.box.center());
	CVector v1=printpage.ptbegin[0];//box.center();
	v1.z=0;
	CPoint po1=v1;

//	CVector v2=page.ptbegin[3];//.box.center();
	CAABB box2;
	int j=0;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(!it->clear)
		{

			for (int i=0;i<fit;i++) 
			{
				if(fig[i]->getLayer().name==it->name)
				{
					box2.add(fig[i]->box);
					j++;
				}
			}
		}
	}
	CVector v2=box2.corner(2);
	CAABB box3=box;
	box=box2;
	CPoint po3=v2;
	cam.initCam();
	box2.empty();
	box2.add(v2);
	cam.setcamorigin(&box2);
//	cam.initZoom();
//	if(fittopage)
//		print_scale=getFitPrintRatio();
	setzoomrat(print_scale);
	box=box3;
//	cam.Translate(CVector(v1.x-v2.x,v2.y-v1.y));
//	cam.Translate(CVector(v2.x-v1.x,v1.y-v2.y));
	CPoint p09=v1;
	CPoint p08=v2;
	return p08;
	CPoint p00=CVector(0,0,0);
	CPoint p07=p09-p08;
	CVector v07=p07;

	cam.Translate(CVector(-v07.x,v07.y));
//	cam.Translate(CVector(v2.x-v1.x,v1.y-v2.y));
/*	 CTVector t;
	 t.VpushTransform();
	 t.VpushUnit();
	 t.Translate(CVector(0,0,0));
	 t.Scale(print_scale,print_scale);
	 t.VendT();
	 CVector v22,v11;
	 v22.assign(v2);
	 v11.assign(v1);
	 v22.z=0;
	 v11.z=0;
	 t.Translate(CVector(v22.x-v11.x,v11.y-v22.y));
	 t.VendT();*/
	CVector v3,v4;
//	v3.assign(v22);
	CPoint po5=v3;
//	v4.assign(v11);
	CPoint po6=v4;
//	cam.init(&printpage);
}

void CDraw::endPrint()
{
	undo(string(""),false);
	undoc(false);
	undoc(false);
//	 CTVector t;
//	 t.VpopTransform();
	cam.Update();
}

void CDraw::displaygrid(CDC *hdc,float r)
{
//	HPEN pe=(HPEN)SelectObject(hdc->GetSafeHdc(),GetStockObject(BLACK_PEN));
	CPen pen(PS_COSMETIC,0.1,RGB(192,192,192));
	CPen* oldpen=hdc->SelectObject(&pen);

	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	v1=v0.sgetscrtop();
	CPoint p(v0.x,v0.y);
    v0 = p;
	p.x=v1.x;
	p.y=v1.y;
	v1 =p;
	v0.x-=fmod(v0.x,r);
	v0.x-=r;
	v0.y-=fmod(v0.y,r);
	v0.y-=r;
	v0.z-=fmod(v0.z,r);
	v0.z-=r;

	v1.x-=fmod(v1.x,r);
	v1.x-=r;
	v1.y-=fmod(v1.y,r);
	v1.y-=r;
	v1.z-=fmod(v1.z,r);
	v1.z-=r;
	CRectangle r2(v0,v1);

//	r2.drawMesh(hdc,r);
	page.drawMesh(hdc,r);
	hdc->SelectObject(oldpen);
	clearmouse(hdc);
//	SelectObject(hdc->GetSafeHdc(),pe);
	return;
	CRect rec=getPage();
	CVector vs=cam.getScreen();
	CTVector tv;
	tv.pushTransform();
	tv.initVect();
	tv.endT();
	tv.VpushTransform();
	tv.VinitVect();
	tv.VendT();
	CPoint pp=vs;
	tv.VpopTransform();
	tv.popTransform();
	CRect scr(CPoint(0,0),CSize(CPoint(pp)));
	scr.NormalizeRect();
	CVector v;
	
	CVector vxunit;
	vxunit.getcoorx();
	CVector vyunit;
	vyunit.getcoory();
	CVector v01;
	v01.getcooro();

	CVector vb=CVector(pp)-v01;
	float d=absc(vb);
	CVector vx=vxunit*d;
	CVector vy=vyunit*d;
	CVector vx0=vxunit*d;
	CVector vy0=vyunit*d;
	
	CPoint p0=vx0;
	CPoint p00=CVector(0,0);
	CPoint p01=p0-p00;
	float r1=absc(CVector(p01.x,p01.y));
	if (r1<2) return;

//	HPEN pe=(HPEN)SelectObject(hdc->GetSafeHdc(),GetStockObject(BLACK_PEN));

	CVector v00=v0;
	int l=0;
	CVector v10;
	rec.NormalizeRect();
	int count=rec.Size().cx/p01.x;
	int dcount=count/2;
	for(int i=0;i<dcount;i++)
	{
		v10=v0+vy;
		hdc->MoveTo(v0);
		hdc->SetPixelV(v0,RGB(0,0,0));//LineTo(v1);
//		hdc->MoveTo(v0);
		v10=v0-vy;
		hdc->SetPixelV(v10,RGB(0,0,0));
//		hdc->LineTo(v1);
		v0=v0+vx0;
	}
	l=0;
	v0=v00;
	for(i=0;i<dcount;i++)
	{
		v1=v0+vy;
		hdc->MoveTo(v0);
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		hdc->MoveTo(v0);
		v1=v0-vy;
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		v0=v0-vx0;
	}
	l=0;
	v0=v00;
	count=rec.Size().cy/p01.x;
	dcount=count/2;
	for(i=0;i<dcount;i++)
	{
		v1=v0+vx;
		hdc->MoveTo(v0);
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		hdc->MoveTo(v0);
		v1=v0-vx;
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		v0=v0-vy0;
	}
	l=0;
	v0=v00;
	for(i=0;i<dcount;i++)
	{
		v1=v0+vx;
		hdc->MoveTo(v0);
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		hdc->MoveTo(v0);
		v1=v0-vx;
		hdc->SetPixelV(v1,RGB(0,0,0));//hdc->LineTo(v1);
		v0=v0+vy0;
	}
//	SelectObject(hdc->GetSafeHdc(),pe);

}

void CDraw::drawmouse(CDC *hdc,CPoint mouse,bool in)
{
	CVector vs=cam.getScreen();
//	CLine l1(CVector(CVectoPoint(mouse.x,
	CTVector tv;
	tv.pushTransform();
	tv.initVect();
	tv.endT();
	tv.VpushTransform();
	tv.VinitVect();
	tv.VendT();
	CPoint pp=vs;
	tv.VpopTransform();
	tv.popTransform();
	CRect scr(CPoint(0,0),CSize(CPoint(pp)));
	CPen pen(PS_COSMETIC,0.1,RGB(255,0,0));
	CPen* oldpen=hdc->SelectObject(&pen);
	int oldr2=hdc->SetROP2(R2_NOTXORPEN);
/*	CRect rt;
	rt.SetRectEmpty();
	hdc->DrawText("Hello",&rt,DT_CALCRECT);
	rt.OffsetRect(mouse);
	hdc->DrawText("Hello",&rt,DT_WORDBREAK|DT_NOCLIP);
*/	if(mouseon)
	{
	hdc->MoveTo(prevmouse.x,0);
	hdc->LineTo(prevmouse.x,pp.y);
	hdc->MoveTo(0,prevmouse.y);
	hdc->LineTo(pp.x,prevmouse.y);

/*	CRect rt;
	rt.SetRectEmpty();
	hdc->DrawText("Hello",&rt,DT_CALCRECT);
	rt.OffsetRect(prevmouse);
	hdc->DrawText("Hello",&rt,DT_WORDBREAK|DT_NOCLIP);
*/	}
	hdc->MoveTo(mouse.x,0);
	hdc->LineTo(mouse.x,pp.y);
	hdc->MoveTo(0,mouse.y);
	hdc->LineTo(pp.x,mouse.y);


	prevmouse=mouse;
	hdc->SelectObject(oldpen);
	hdc->SetROP2(oldr2);
	mouseon=true;

}

void CDraw::clearmouse(CDC* hdc)
{
	CVector vs=cam.getScreen();
//	CLine l1(CVector(CVectoPoint(mouse.x,
	CTVector tv;
	tv.pushTransform();
	tv.initVect();
	tv.endT();
	tv.VpushTransform();
	tv.VinitVect();
	tv.VendT();
	CPoint pp=vs;
	tv.VpopTransform();
	tv.popTransform();
	CRect scr(CPoint(0,0),CSize(CPoint(pp)));
	CPen pen(PS_COSMETIC,0.1,RGB(255,0,0));
	CPen* oldpen=hdc->SelectObject(&pen);
	int oldr2=hdc->SetROP2(R2_NOTXORPEN);
	if(mouseon)
	{
	hdc->MoveTo(prevmouse.x,0);
	hdc->LineTo(prevmouse.x,pp.y);
	hdc->MoveTo(0,prevmouse.y);
	hdc->LineTo(pp.x,prevmouse.y);
	}
	hdc->SelectObject(oldpen);
	hdc->SetROP2(oldr2);

}

void CDraw::setmouse(bool t)
{
	mouseon=t;
}

void CDraw::rotate(float u, short sens, CVector c)
{
	int g=vs.size();

	u=(u*2*pi)/360;
	for (int i=0;i<g;i++)
	{
		vs[i]->setRotateCenter(c);
		vs[i]->rotate(u,sens);
	 } 

}
void CDraw::scale(float u, short sens, CVector c)
{
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		vs[i]->setRotateCenter(c);
		vs[i]->rotate(u,sens);
	 } 

}

void CDraw::forundo(int i, string t)
{
if(fig[i]->getName()!="CImage")
{
  CMemento* m=new CMemento(fig[i]);
   vmemento.push_back(m);
   undoList.push(t);
}
/*	if(t=="create line")
	{
		vector<CVector> vv=fig[i]->getMesh()->getVectors();
		string cmd1="line ",cmd;
		CString input="";
		for(int i=0;i<vv.size();i++){
		input.Format("<%f,%f,%f>",vv[i].x,vv[i].y,vv[i].z);
		cmd1+=input + " ";
		}
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}else
	if(t=="create update line")
	{
		vector<CVector> vv=fig[i]->getMesh()->getVectors();
		string cmd="line ";
		CString input="";
		for(int i=0;i<vv.size();i++){
		input.Format("<%f,%f,%f>",vv[i].x,vv[i].y,vv[i].z);
		cmd+=input + " ";
		}
		pair<string, string> m1=undostack.top();
		m1.first=cmd;
		undostack.pop();
		undostack.push(m1);
	}else
	if(t=="create spline")
	{
		vector<CVector> vv=((CBezier*)fig[i])->getCP();
		vector<double> vk=((CBezier*)fig[i])->getKn();
		string cmd1="spline2 ",cmd;
		CString input="";
		for(int i=0;i<vv.size()-1;i++){
		input.Format("<%f,%f,%f>",vv[i].x,vv[i].y,vv[i].z);
		cmd1+=input + " ";
		}
		CString input1="",cc="";
		for(i=0;i<vv.size()-1;i++){
		cc.Format("%f ",vk[i]);
		input1+=cc + " ";
		}
		cmd1+=" [ " + input1 + " ]";
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}else
	if(t=="create update spline")
	{
		vector<CVector> vv=((CBezier*)fig[i])->getCP();
		vector<double> vk=((CBezier*)fig[i])->getKn();
		string cmd="spline2 ";
		CString input="";
		for(int i=0;i<vv.size()-1;i++){
		input.Format("<%f,%f,%f>",vv[i].x,vv[i].y,vv[i].z);
		cmd+=input + " ";
		}
		CString input1="",cc="";
		for(i=0;i<vk.size()-1;i++){
		cc.Format("%f ",vk[i]);
		input1+=cc + " ";
		}
		cmd+=" [ " + input1 + " ]";
		pair<string, string> m1=undostack.top();
		m1.first=cmd;
		undostack.pop();
		undostack.push(m1);
	}else
	if(t=="create rectangle")
	{
		vector<CVector> vv=fig[i]->getMesh()->getVectors();
		string cmd1="rect ",cmd;
		CString input="";
		for(int i=1;i<vv.size();i=i+2){
		input.Format("<%f,%f,%f>",vv[i].x,vv[i].y,vv[i].z);
		cmd1+=input + " ";
		}
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}else
	if(t=="create circle")
	{
		CVector vv=((CCercle*)fig[i])->getCenter();
		double vk=((CCercle*)fig[i])->getRadius();
		string cmd1="circle ",cmd;
		CString input="";
		input.Format("<%f,%f,%f>",vv.x,vv.y,vv.z);
		cmd1+=input + " ";
		CString cc="";
		cc.Format("%f ",vk);
		cmd1+= cc;
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}else
	if(t=="create 2p arc")
	{
		vector<CVector> vv1=((CBezier*)fig[i])->getCP();
		CVector v1=vv1[0];
		CVector v2=vv1[vv1.size()-2];
		string cmd1="arc ",cmd;
		CString input="";
		input.Format("<%f,%f>",v1.x,v1.y);
		cmd1+=input + " ";
		input.Format("<%f,%f>",v2.x,v2.y);
		cmd1+=input;
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}else
	if(t=="create arc")
	{
		CVector vv=((CCercle*)fig[i])->getCenter();
		double vk=((CCercle*)fig[i])->getRadius();
		vector<CVector> vv1=((CBezier*)fig[i])->getCP();
		CVector v1=vv1[0];
		double startangle=argu(v1-vv)*360/(2*pi);
		CVector v2=vv1[vv1.size()-2];
		double endangle=argu(v2-vv)*360/(2*pi);
		string cmd1="arc ",cmd;
		CString input="";
		input.Format("<%f,%f>",vv.x,vv.y);
		cmd1+=input + " ";
		input.Format("%f",vk);
		cmd1+=input + " ";
		input.Format("%f",endangle);
		cmd1+=input + " ";
		input.Format("%f",startangle);
		cmd1+=input;
		input.Format("%d",fit);
		cmd="delete "+ input;
		undostack.push(pair<string,string>(cmd1,cmd));
	}
*/
}
void CDraw::forundo(CFigure* i, string t)
{
	for(int _i=0;_i<fit;_i++)
	{
		if(fig[_i]==i)
			forundo(_i,t);
	}
	return;
	if(i->getName()!="CImage")
	{

   CMemento* m=new CMemento(i);
   vmemento.push_back(m);
   undoList.push(t);
	}
}
void CDraw::forundoc(CFigure* i, string t)
{
if(i->getName()!="CImage")
{
  CMemento* m=new CMemento(i);
   vcmemento.push_back(m);
   undocList.push(t);
}
}
void CDraw::create(CFigure* f,int i)
{
	if(i==-1)
	{
		string scount;
		CString sf;
		sf.Format(_T("%d"),count);
		scount=sf;
		f->setHandle(scount);
		f->setLayer(currlayer);
		vhan.push_back(scount);
		sfit++;
		count++;
		fig.push_back(f);
		fit++;
		forundo(fit-1,"create");
	}
}

void CDraw::copy()
{
	int pk=cpy.size();

	for (int i=0;i<pk;i++)
	{
		delete cpy[i];
	}
	cpy.clear();


	int j=vs.size();
	CFigure* arr;
	for (i=0;i<j;i++)
	{
		arr=vs[i]->translatep(vs[i]->getCenter(),vs[i]->getCenter());
//		create(arr);
		cpy.push_back(arr);
	}

}

void CDraw::Offset(float u)
{

	int j=vs.size();
	CFigure* arr;
	for (int i=0;i<j;i++)
	{
		arr=vs[i]->Offset(u);
		create(arr);
	}
	candraw=true;

}

void CDraw::extend(CVector v)
{
	int j1=vs.size();
	for (int j=0;j<fit;j++)
	{
		if (fig[j]->inRegion(v))
		{
			for (int i=0;i<j1;i++)
			{
				fig[j]->Extend(vs[i]);
			}
		}
	}
}
void CDraw::clip(CVector v)
{
	int j1=vs.size();
	for (int j=0;j<fit;j++)
	{
		if (fig[j]->inRegion(v))
		{
			for (int i=0;i<j1;i++)
			{
				fig[j]->Clip0(vs[i]);
			}
		}
	}
	candraw=true;
}

void CDraw::getfromPoint(CVector &v)
{
  v= v_current+v;
  v_current = v;
}
void CDraw::getfromPoint(vector<CVector> &vp)
{
	int n=vp.size();
	if(n>1)
		vp[n-1]= vp[n-2]+vp[n-1];
}
void CDraw::setcurrPoint(CVector v)
{
  v_current = v;
}

void CDraw::addLine2(vector<CVector> v)
{
	ASSERT(v.size()!=0);
	v_current=v.back();
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	switch(v.size())
	{
	case 1:
		{
			undoList.push("create");
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=new CLine(v_current,v_current);
			fig[fit]->setLayer(currlayer);
			fig[fit]->setcorevecor();
			fit++;
			sfit++;
			count++;
			Bminus=true;
		}
		break;
	case 2:
			fig[fit-1]->TranslateTo(v_current,fig[fit-1]->getMesh()->Vcount()-1);
		break;
	default:
			fig[fit-1]->addextranode(v_current);
		break;
	}

}
void CDraw::AddSpline2(vector<CVector> v)
{
	ASSERT(v.size()!=0);
	v_current=v.back();
	string scount;
	CString sf;
	sf.Format(_T("%d"),count);
	scount=sf;
	switch(v.size())
	{
	case 1:
		{
/*			undoList.push("create");
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=new CLine(v_current,v_current);
			fig[fit]->setLayer(currlayer);
			fig[fit]->setcorevecor();
			fit++;
			sfit++;
			count++;
			Bminus=true;*/
		}
		break;
	case 2:
		{
			undoList.push("create");
			vhan.push_back(scount);
			fig.resize(fig.size()+1);
			fig[fit]=new CBezier(3,v);
			fig[fit]->setLayer(currlayer);
			fig[fit]->setcorevecor();
			fit++;
			sfit++;
			count++;
			Bminus=true;
		}
		break;
	default:
		{
//			delete fig[fit-1]; 
			fig[fit-1]=new CBezier(3,v);
			fig[fit-1]->setLayer(currlayer);
			fig[fit-1]->setcorevecor();
		}
		break;
	}

}

void CDraw::getPoint(CPoint p,float& u1,float& u2,float& u3,CDC *hdc)
{
  CVector v(p);
  if(snap) fsnapPoint(v,hdc);

  u1=v.x;
  u2=v.y;
  u3=v.z;
}

void CDraw::setsnap(vector<CProperty *> dlg,CDC* hdc)
{
 snappy.init(dlg,this,hdc);
}
void CDraw::getdimL(int& length_type,int& length_name,int& precision)
{
	if(CDimText::style==_T("linear-inch"))
	{
		length_type=1;
		length_name=1;
	}else
	if(CDimText::style==_T("linear-feet"))
	{
		length_type=1;
		length_name=2;
	}else
	if(CDimText::style==_T("linear-millimeter"))
	{
		length_type=1;
		length_name=3;
	}else
	if(CDimText::style==_T("linear-centimeter"))
	{
		length_type=1;
		length_name=4;
	}else
	if(CDimText::style==_T("linear-meter"))
	{
		length_type=1;
		length_name=5;
	}
	precision=CDimText::precision_type;
}
void CDraw::setdimL(int length_type,int length_name,int precision)
{
	if(length_type==1)
	{
		if(length_name==1)
			CDimText::style=_T("linear-inch");
		else
		if(length_name==2)
			CDimText::style=_T("linear-feet");
		else
		if(length_name==3)
			CDimText::style=_T("linear-millimeter");
		else
		if(length_name==4)
			CDimText::style=_T("linear-centimeter");
		else
		if(length_name==5)
			CDimText::style=_T("linear-meter");
	}
	else
	if(length_type==2)
	{
		CDimText::style=_T("linear-architect");
	}else
	if(length_type==3)
	{
			CDimText::style=_T("linear-feet");
	}else
	if(length_type==3)
	{
		CDimText::style=_T("linear-fractional");
	}
		CDimText::precision_type=precision;
}
void CDraw::getdimA(int& length_type,int& precision)
{
	if(CDimText::astyle==_T("angle-degree"))
	{
		length_type=2;
	}else
	{
		length_type=1;
	}
	precision=CDimText::aprecision_type;

}
void CDraw::fitToPage(bool _fit)
{
	fittopage=_fit;
}
void CDraw::setdimA(int length_type,int precision)
{
	if(length_type==2)
		CDimText::astyle=_T("angle-degree");
	else
		CDimText::astyle=_T("angle-radian");
	CDimText::aprecision_type=precision;

}

void CDraw::getAppInt(CVector &v)
{

}

bool CDraw::getSnapCenter(CVector &v,CDC* hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->fsnap(v,v0,"center",hdc)) return true; 
	}
	return false;

}

bool CDraw::getSnapEndPoint(CVector &v,CVector &vl,CDC* hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->fsnap(v,vl,"endpoint",hdc))
			return true;
	}
	return false;

}

bool CDraw::getSnapExten(CVector &v,CDC* hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->fsnap(v,v0,"nearest",hdc)) return true; 
	}
	return false;

}

bool CDraw::getSnapInter(CVector &v,CDC* hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->inRegion(v))
			fe.push_back(fb[i]);
		if(fe.size()==2)
		{
			fe[0]->intersect(fe[1],v);
			return true;
		}
	}
	return false;


}

bool CDraw::getSnapMidPoint(CVector &v,CVector &vl,CDC* hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->fsnap(v,vl,"midpoint",hdc)) return true; 
	}
	return false;

}

bool CDraw::getSnapNearest(CVector &v,CVector &vl,CDC * hdc)
{
	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->fsnap(v,vl,"nearest",hdc)) return true; 
	}
	return false;

}

bool CDraw::getSnapPara(CVector vl,CVector& vs,CVector &v,CDC* hdc)
{
		for(int i=0;i<fit;i++)
		{
		if(fig[i]->snappara(vl,vs,v))
		return true;
		}
		return false;
/*		for(int i=0;i<fit;i++)
		{
		if(fig[i]->snappara(vl,v))
		return true;
		}
		return false;*/
}

bool CDraw::getSnapPerp(CVector vl,CVector vs,CVector &v,CDC* hdc)
{
		for(int i=0;i<fit;i++)
		{
		if(fig[i]->snapperp(vl,vs,v))
		return true;
		}
		return false;

/*	vector<CFigure*> fb,fe;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->inBox(v))
			fb.push_back(fig[i]);
	}
	int t=fb.size();
	for(i=0;i<t;i++)
	{
		if(fb[i]->inRegion(v))
			snap_fig=fb[i];
	}
	if(!snap_fig) return;
	fig[fit-1]->inRegion(v);
	if(snap_fig->inRegion(v))
	{
		if(snap_fig->snapperp(fig[fit-1],v))
		return;
	}

	for(i=0;i<fit;i++)
	{
	if(fig[i]->snapperp(fig[fit-1],v))
	return;
	}*/
}

void CDraw::getSnapTangent(CVector &v,CDC* hdc)
{

}

void CDraw::getsnap(vector<CProperty*> v)
{
 snappy.setval(v);

}
float CDraw::getFitPrintRatio()
{
	printpage.updatecore();
// CPoint p00=printpage.ptbegin[0];
// printpage.TranslateTo(getcamor());
	CPoint p01=printpage.box.corner(1);
	CPoint p00=printpage.box.corner(0);
	CAABB box2;
	int j=0;
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(!it->clear)
		{

			for (int i=0;i<fit;i++) 
			{
				if(fig[i]->getLayer().name==it->name)
				{
					box2.add(fig[i]->box);
					j++;
				}
			}
		}
	}
	CVector v01=box2.corner(1);
	CVector v00=box2.corner(0);
	CVector v02=box2.corner(2);

	CPoint ap01=box2.corner(1);
	CPoint ap00=box2.corner(0);
	float u1=sqrt(pow(p01.x-p00.x,2)+pow(p01.y-p00.y,2));
	float u2=sqrt(pow(ap01.x-ap00.x,2)+pow(ap01.y-ap00.y,2));
	u1=u2/u1;
//	CPoint p01=printpage.box.corner(1);
	CPoint p02=printpage.box.corner(2);
//	CPoint ap01=box.corner(1);
	CPoint ap02=box2.corner(2);
	float u3=sqrt(pow(p02.x-p00.x,2)+pow(p02.y-p00.y,2));
	float u4=sqrt(pow(ap02.x-ap00.x,2)+pow(ap02.y-ap00.y,2));
	if(u4>u3*u1)
	{
	u3=u4/u3;
	return u3;
	}
//	float u3=absc(printpage.box.corner(2)-printpage.box.corner(1));
//	float u4=absc(box.corner(2)-box.corner(1));
//	u3=u4/u3;;
	//u1=u1>u3?u3:u1;
	return u1;
}
void CDraw::setPrintPage(CRect r,float f)
{
//	r.NormalizeRect();
	forundoc(&cam,"Init");
	cam.initZoom();
	cam.initCam();
	cam.zoom(1);

 printpage= CRectangle(r.TopLeft(),r.BottomRight());
 print_scale=f;
}

CRect CDraw::getPrintPage()
{
	CRect r;
	printpage.updatecore();
	r.SetRect(printpage.box.corner(0),printpage.box.corner(3));
	return r;

}
