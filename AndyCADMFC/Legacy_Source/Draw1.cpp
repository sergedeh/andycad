// Draw.cpp: implementation of the CDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Draw.h"
#include "render.h"
#include <algorithm>
#include "spline.h"
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
	fit=0;
	sfit=0;
	sefit=0;
	bck=false;
//	fig=NULL;
//	sfig=NULL;
	m=0;ms=0;
//	fig[fit]=&pLine;
	cdel=false;

	initVect();
	VinitVect();
	B=false;
	Bminus=false;
	positions[1]=v0;ita=0;
	rzoom=0.5;
	
	selected=false;
	menuselect=false;

/*	Line.clear();
	selected_Lines.clear();
	fiter=Figure.begin();
	citer=Cercle.begin();*/
	endDraw=FALSE;
	change=false;
//	pBezier=new CBezier;
	nbc=0;
	valid=false;
	currlayer.clear=false;
	currlayer.on=true;
	currlayer.lock=false;
	currlayer.name="Normal";
	veclayer.push_back(currlayer);

	CVector k(0,0,0,1);
	CVector kt(k.getscrtop()/2,k.getscrb()/2);
	k=k-kt;
	pBezier=new CBezier;
//	Translate(k);
//	VendT();
//	Translate(k);
//	endT();

}

CDraw::~CDraw()
{
	for(int i=0;i<fit;i++)
	{
	delete fig[i];
	}
	fit=0;

	delete pBezier;
	while(!rmemento.empty())
	{
//		CMemento* m=rmemento.top();
		rmemento.pop();
//		delete m;
	}
	while(!redoList.empty())
		redoList.pop();
	while(!vmemento.empty())
	{
//		CMemento* m=vmemento.top();
		vmemento.pop();
//		delete m;
	}
	while(!undoList.empty())
		undoList.pop();


}

bool CDraw::add(CString figure,bool fPrevLine,CDC* hdc,CVector point)
{

	if (figure=="Line")
	{
//		pLine.setMove(true,point);
		endDraw=pLine.draw(fPrevLine,hdc,point);
		return true;
	} 
	else
	if (figure=="Box")
	{
//		pLine.setMove(true,point);
		
/*		pRectangle.setMove(true,point);
		endDraw=pRectangle.draw(fPrevLine,hdc,point);
//		pRectangle.create(point);
		pRectangle.getchargeL();
		CBezier l1(pRectangle.ptbegin[0],pRectangle.ptbegin[1]);
		CBezier l2(pRectangle.ptbegin[3],pRectangle.ptbegin[2]);


		vector<CBezier*> fg(2);
		fg[0]=&l1;
		fg[1]=&l2;
		pBezier->surface("loft",fg,2,0);
		pBezier->surface(hdc);
//		fig[fit-1]=&pBezier;*/
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
	if ((figure=="DimF")||(figure=="DimV")||(figure=="DimH"))
	{
		endDraw=Dim->draw(fPrevLine,hdc,point);
		return true;
	}
	else
	if ((figure=="DimL")||(figure=="DimLH")||(figure=="DimLV"))
	{
		endDraw=DimL->draw(fPrevLine,hdc,point);
		return true;
	}
	
return false;	
}


void CDraw::display(CDC *rhdc,CDC* hdc)
{
	pLine.setRDC(rhdc);
	
	CMesh m;
	m.Bdraw();
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
	m.Edraw(hdc);

}

void CDraw::Create(CDC *hdc,CString figure,CVector point)
{
	if(snap) fsnap(point,hdc);

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
	if(figure=="Image")
	{	
		image.setPtsBegin(point);

	}else
	if(figure=="DimF")
	{	
		Dim=new CDim;
		Dim->setstyle("DimF");
		Dim->setPtsBegin(point);
	}else
	if(figure=="DimV")
	{	
		Dim=new CDim;
		Dim->setstyle("DimV");
		Dim->setPtsBegin(point);
	}else
	if(figure=="DimH")
	{	
		Dim=new CDim;
		Dim->setstyle("DimH");
		Dim->setPtsBegin(point);
	}else
	if(figure=="DimD")
	{	
		Dim=new CDim;
		Dim->setstyle("DimD");
		Dim->setPtsBegin(point);
		Dim->create(point);
		CCercle cerc;
		for(int i=0;i<fit;i++)
		{
			vector<CVector> test;
			if((fig[i]->getName()==cerc.getName())&&(fig[i]->inRegion(point)))
			{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
				test[0]=fig[i]->getCenter();

				Dim->addSL(test);
				Dim->getCharge(hdc);

				Dim->clear();
				Dim->sethandle(count);
				undoList.push("create");
				//Dim->setUndoparam();
				Dim->setcorevecor();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				
				fig[fit]=Dim;
				nbc=0;
				valid=true;
				fit++;
				break;
				}
	
			}
		}
		//Dim->setPtsBegin(point);
	}else
	if(figure=="DimR")
	{	
		Dim=new CDim;
		Dim->setstyle("DimR");
		Dim->setPtsBegin(point);
		Dim->create(point);
		CCercle cerc;
		for(int i=0;i<fit;i++)
		{
			vector<CVector> test;
			if((fig[i]->getName()==cerc.getName())&&(fig[i]->inRegion(point)))
			{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
				test[0]=fig[i]->getCenter();

				Dim->addSL(test);
				Dim->getCharge(hdc);

				Dim->clear();
				Dim->sethandle(count);
				undoList.push("create");
			
				//Dim->setUndoparam();
				Dim->setcorevecor();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				
				fig[fit]=Dim;
				nbc=0;
				valid=true;
				fit++;
				break;
				}
	
			}
		}
		//Dim->setPtsBegin(point);
	}else
	if(figure=="DimL")
	{	
		DimL=new CDimL;
		DimL->setstyle("DimF");
		DimL->setPtsBegin(point);
	}else
	if(figure=="DimLH")
	{	
		DimL=new CDimL;
		DimL->setstyle("DimH");
		DimL->setPtsBegin(point);
	}else
	if(figure=="DimLV")
	{	
		DimL=new CDimL;
		DimL->setstyle("DimV");
		DimL->setPtsBegin(point);
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
				if(test[0]!=test[2])
				{
				DimA=new CDimA;
				DimA->addSL(test);
				nbc++;
				break;
				}
				}
			}
		}
		else
		if(nbc==1)
		{
			CLine pl;
			CRectangle pR;
			for(int i=0;i<fit;i++)
			{
				if((fig[i]->getName()==pl.getName())||(fig[i]->getName()==pR.getName()))
				{
				test=fig[i]->getSelectvec(point);
				if(test[0]!=test[2])
				{
				DimA->addSL(test);
				DimA->getCharge(hdc);

				DimA->clear();
				DimA->sethandle(count);
				undoList.push("create");
				//DimA->setUndoparam();
				DimA->setLayer(currlayer);
				DimA->setcorevecor();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				//m=_msize(fig);
				fig[fit]=DimA;
				nbc=0;
				valid=true;
				fit++;
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
						undoList.push("create");
						//fig[i]->setUndoparam();
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
						undoList.push("create");
						//fig[i]->setUndoparam();
						/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
						sfit++;
			
						IA->addSLChamf(test,fig[i]);
						CFigure* lk=IA->getChargeChamf();
							if(lk!=0)
							{
							CLine* llg=new CLine;
							llg->createobj(lk->ptbegin,lk->ptend);
							llg->clear();
							llg->setInit();
							llg->sethandle(count);
							undoList.push("create");
//llg->setUndoparam();
							llg->setLayer(currlayer);
							llg->setcorevecor();
							
							
							/*vhan[sfit]=count;*/vhan.push_back(count);

							/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
							////m=_msize(fig);
							fig[fit]=llg;fit++;
							sfit++;
							count++;
							Bminus=true;

							}
						delete lk;
						delete IA;

						nbc=0;
						valid=true;

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
							undoList.push("create");
							//fig[i]->setUndoparam();
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
						IA->addSLChamf(test,fig[i]);
						CCercle* lk=new CCercle;
						bool ko=IA->getChargeFilt(lk);
						delete IA;
						if(ko)
						{
							undoList.push("create");
//fig[i]->setUndoparam();
							/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
							sfit++;
							lk->clear();
							lk->setInit();
							lk->sethandle(count);
							undoList.push("create");
			//				lk->setUndoparam();
							lk->setLayer(currlayer);
							lk->setcorevecor();

							/*vhan[sfit]=count;*/vhan.push_back(count);

							/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
							////m=_msize(fig);
							fig[fit]=lk;fit++;
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
	if (endDraw)
	{
	if(snap) fsnap(pos2,hdc);
		if(figure=="Line")
		{
		pLine.create(pos2);
		if (pLine.getCharge())
		{
//		pLine.draw(hdc);
		CLine *ftp= new CLine;
		
		pLine.clear();
		pLine.sethandle(count);
		undoList.push("create");
//pLine.setUndoparam();
		pLine.setLayer(currlayer);
		pLine.setcorevecor();
		*ftp=pLine;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		pLine.initL();
		}
		else
		{
//		pLine.draw(hdc);
		*fig[fit-1]=pLine;
		pLine.setcorevecor();
		undoList.push("create");
//		fig[fit-1]->updateUndoparam();
		}
		}
		if(figure=="QLine")
		{
		pQLine.create(pos2);
		if (pQLine.getCharge())
		{
//		pQLine.draw(hdc);
		CQLine *ftp= new CQLine;
		pQLine.clear();
		pQLine.sethandle(count);
		undoList.push("create");
//		pQLine.setUndoparam();
		pQLine.setLayer(currlayer);
		pQLine.setcorevecor();
		*ftp=pQLine;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		//pQLine.initL();
		}
		else
		{
//		pQLine.draw(hdc);
		*fig[fit-1]=pQLine;
		pQLine.setcorevecor();
		undoList.push("create");
//		fig[fit-1]->updateUndoparam();
		}
		}
		else
		if(figure=="Bezier")
		{
		pBezier->create(pos2);
		if (pBezier->getCharge())
		{
//		pBezier->draw(hdc);
		//CBezier *ftp1= new CBezier;
		pBezier->clear();
		pBezier->sethandle(count);
		undoList.push("create");
//		pBezier->setUndoparam();
		pBezier->setLayer(currlayer);
		pBezier->setcorevecor();
	
		//*ftp1=pBezier;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=new CBezier;//ftp1;
	
		fig[fit]->copy(pBezier);	
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pBezier->initL();
		}
		else
		{
//		pBezier->draw(hdc);
//		CBezier *btp= new CBezier;
//		btp->copy(pBezier);
//		btp->setcorevecor();
		delete fig[fit-1];
		fig[fit-1]=new CBezier;//btp;
		fig[fit-1]->copy(pBezier);
		fig[fit-1]->setcorevecor();
		undoList.push("create");
//		fig[fit-1]->updateUndoparam();
		}
		}else
		if(figure=="Box")
		{
		
		}else
		if(figure=="Rectangle")
		{
		pRectangle.create(pos2);
		if(pRectangle.getCharge())
		{
//		pRectangle.draw(hdc);
		CRectangle *ftp= new CRectangle;
		pRectangle.clear();
		pRectangle.sethandle(count);
		undoList.push("create");
//		pRectangle.setUndoparam();
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		*ftp=pRectangle;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;
		fit++;
		sfit++;
		count++;
		Bminus=true;
		pRectangle.initL();
		}
		}else
		if(figure=="Image")
		{
		image.create(pos2);
		if(image.getCharge())
		{
		if(image.LoadBitmap(hdc))
		{
		image.draw(hdc);
		CImage *ftp= new CImage;
		image.clear();
		image.sethandle(count);
		undoList.push("create");
//		image.setUndoparam();
		image.setLayer(currlayer);
		image.setcorevecor();

		*ftp=image;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		image.initL();
		}
		}
		}else
		if((figure=="DimF")||(figure=="DimV")||(figure=="DimH"))
		{
		Dim->create(pos2);
		if(Dim->getCharge(hdc))
		{
		Dim->draw(hdc);
		CDim *ftp= new CDim;
		Dim->clear();
		Dim->sethandle(count);
		undoList.push("create");
//		Dim->setUndoparam();
		Dim->setLayer(currlayer);
		Dim->setcorevecor();

		*ftp=*Dim;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		}
		}else
		if((figure=="DimL")||(figure=="DimLH")||(figure=="DimLV"))
		{
		DimL->create(pos2);
		if(DimL->getCharge(hdc))
		{
		DimL->draw(hdc);
		CDimL *ftp= new CDimL;
		DimL->clear();
		DimL->sethandle(count);
		undoList.push("create");
//		DimL->setUndoparam();
		DimL->setLayer(currlayer);
		DimL->setcorevecor();

		*ftp=*DimL;
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		}
		}else
		if(figure=="Text")
		{
		textcad->initL();
		textcad->create(pos2);
		textcad->getCharge();
		
		CTextCad *ftp= new CTextCad;
		textcad->clear();
		textcad->sethandle(count);
		undoList.push("create");
//		textcad->setUndoparam();
		textcad->IsOn();
		textcad->setLayer(currlayer);

		*ftp=*textcad;
//		ftp->updatecopy();
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;fit++;
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
				fig[i]->Select(hdc,pos2);
				fig[i]->setMultselect(true);
				fig[i]->setclick(true);
				fig[i]->selectSM(hdc);

				vs.push_back(fig[i]);
		/*		sfig=(CFigure**) realloc(sfig,ms+sizeof(CFigure*));
				ms=_msize(sfig);
				sfig[sefit]=fig[i];
				sefit++;*/
				}
			}
			}
		bck=false;
		if(hdc->GetROP2()!=R2_NOTXORPEN)
		{
		hdc->SetROP2(R2_NOTXORPEN);
		}
		pSelect.draw(hdc);
		}
		else
		if((figure=="Circle")||(figure=="2DotCircle"))
		{
		pCircle.setType("Circle");
		pCircle.addtovec();
		CCercle *ftp= new CCercle;
		pCircle.clear();
		pCircle.sethandle(count);
		undoList.push("create");
//		pCircle.setUndoparam();
		pCircle.setLayer(currlayer);
		pCircle.setcorevecor();
//		pCircle.draw(hdc);

		ftp->copy(pCircle);
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;
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
		pArc.addtovec();
		CCercle *ftp= new CCercle;
		pArc.clear();
		pArc.sethandle(count);
		undoList.push("create");
//		pArc.setUndoparam();
		pArc.setLayer(currlayer);
		pArc.setcorevecor();
//		pArc.draw(hdc);

//		*ftp=pArc;
		ftp->copy(pArc);
		/*vhan[sfit]=count;*/vhan.push_back(count);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		////m=_msize(fig);
		fig[fit]=ftp;
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
			pCircle.addtovec();
			CCercle *ftp= new CCercle;
			pCircle.clear();
			pCircle.sethandle(count);
			undoList.push("create");
//			pCircle.setUndoparam();
			pCircle.setLayer(currlayer);
			pCircle.setcorevecor();
//			pCircle.draw(hdc);

//			*ftp=pCircle;
			ftp->copy(pCircle);
			/*vhan[sfit]=count;*/vhan.push_back(count);
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
			fig[fit]=ftp;
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
			pCircle.sethandle(count);
			undoList.push("create");
//			pCircle.setUndoparam();
			pCircle.setLayer(currlayer);
			pCircle.setcorevecor();
//			pCircle.draw(hdc);

//			*ftp=pCircle;
			ftp->copy(pCircle);
			/*vhan[sfit]=count;*/vhan.push_back(count);
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
			fig[fit]=ftp;
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
			pArc.addtovec();
			CCercle *ftp= new CCercle;
			pArc.clear();
			pArc.sethandle(count);
			undoList.push("create");
//			pArc.setUndoparam();
			pArc.setLayer(currlayer);
			pArc.setcorevecor();
//			pArc.draw(hdc);

			//*ftp=pArc;
			ftp->copy(pArc);
			/*vhan[sfit]=count;*/vhan.push_back(count);
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
			fig[fit]=ftp;
			fit++;
			sfit++;
			count++;
			Bminus=true;
			pArc.initL();
			}

		}
/*		for (int i=0;i<fit;i++) 
		{
			if ((fig[i]->transselectedstate())&&(fig[i]->getName()==image.getName()))
			{
			fig[i]->draw(hdc);
			}
		}
*/
		
		
		//	sefit=1;

/*		if((figure=="3DotCircle")||("Eclipse"))
		{
			if (pCircle.getCharge())
			{
			pCircle.setType("Circle");
			pCircle.addtovec();
			CCercle *ftp= new CCercle;
			pCircle.clear();
			pCircle.sethandle(count);
			pCircle.setUndoparam();
			
			*ftp=pCircle;
			vhan[sfit]=count;
			fig[fit]=ftp;fit++;
			sfit++;
			count++;
			Bminus=true;
			pCircle.initL();
			}

		}*/

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
	

	
	bool locale=false;

	bool c=false;
	for (int i=0;i<sefit;i++) 
	{
		if(!spoint)
		{
			if(!(sfig[i]->getLayer()).clear)
			{
             bool g=sfig[i]->PtinRegion(point);;
			 c|=g;
			}
		}else
		{
			if(!(sfig[i]->getLayer()).clear)
			{
			c|=sfig[i]->PtinNode(point,multiselect);
			}
		}
	}
	if(!c)
	{
	for (i=0;i<sefit;i++) 
	{
		if(!(sfig[i]->getLayer()).clear)
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
			if(spoint)
			{
			   B=fig[i]->PtinNode(point,multiselect);
			}
			else
			{
			B=fig[i]->PtinRegion(point);
			if(B) 
			{
				if(find(vs.begin(),vs.end(),fig[i])==vs.end())
				vs.push_back(fig[i]);
			}
	//		fig[i]->selectSM(hdc);
			}
			locale|=B;
		}
	}
	}
	
	int j=vs.size();
	if(!locale)
	{
		for(i=0;i<j;i++)
		{
			vs[i]->setMultselect(false);
			vs[i]->setclick(false);
			vs[i]->selectSM(hdc);
			vs[i]->getLayer().lock;
		    vs[i]->getLayer().clear;
		}
		vs.clear();
	}
	
	j=vs.size();
	for(i=0;i<j;i++)
	{
		vs[i]->setMultselect(true);
		vs[i]->setclick(true);
		vs[i]->selectSM(hdc);
		vs[i]->getLayer().lock;
		vs[i]->getLayer().clear;
	}

/*		for (i=fit-1;i>=0;i--)//(liter=Line.begin();liter<Line.end();liter++) 
		{
		//	if(liter->i
		if(fig[i]->ptbegin.size()!=0)
		{

		if(!(fig[i]->getLayer()).clear)
		{
			if(spoint)
			{
			   B=fig[i]->PtinNode(point);
			}
			else
			{
			B=fig[i]->PtinRegion(point);
			}
			locale|=B;
			if((!B)&&(Bminus))
			{
				fig[i]->setSelect(Bminus);
			}
	//		fig[i]->setMultselect(true);
			fig[i]->selectSM(hdc);
		
			//grace
			change=false;

 			if(fig[i]->unselectedstate())

			{
				
			}

			fig[i]->setSelect(false);
			if (B)
			{

				for(int j=i-1; j>=0;j--)
				{
				if(!(fig[i]->getLayer()).clear)
				{
					if(fig[j]->inselectedstate())
					{
					//	fig[i]->setMultselect(true);
						B=false;
						locale|=B;
						if((!B)&&(Bminus))
						{
							fig[j]->setSelect(Bminus);
						}
						fig[j]->setclick(false);//selected_Lines.push_back(*fig[i]);
						fig[j]->selectSM(hdc);
						fig[j]->setSelect(false);
					}
				}
				}
				break;
			}
		}
		}
		}*/
	
    getBinfo(point);
			
	Bminus=locale;

	bck=false;
	
	return Bminus;
}


void CDraw::displayselect(CDC *hdc)
{

}

bool CDraw::translate(CWnd *wnd,CDC *hdc,CVector PrevPos,CVector PostPos,int key)
{
	bool sel=false;
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
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

	return sel;
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


	int pk=fit;
	bool sel=false;

	for(int i=0;i<fit;i++)
	{
//		if(fig[i]->getLayer()==currlayer)
//		{

		if (fig[i]->getName()==pLine.getName())
		{
			if (fig[i]->PtinRegion(point))
			{

			for (int j=0;j<fit;j++) 
				{
					if (fig[j]->inselectedstate())
					{
						fig[j]->sethandle(count);
						undoList.push("create");
		//				fig[j]->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
						sfit++;
						count++;
						fig[j]->setMultselect(false);
						if(fig[j]->getName()==pLine.getName())
						{
						pLine=*(CLine*)fig[j];
						pInt.copybyL(fig[i],fig[j],&pLine);
						pLine.draw(hdc);
						CLine *ftp= new CLine;
						*ftp=pLine;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);

						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.copybyL(fig[i],fig[j],&pRectangle);
						pRectangle.draw(hdc);
						CRectangle *ftp= new CRectangle;
						*ftp=pRectangle;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
//ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.copybyL(fig[i],fig[j],&pC);
						pC.draw(hdc);
						CCercle *ftp= new CCercle;
						ftp->copy(pC);
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
//ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.copybyL(fig[i],fig[j],pBezier);
						CBezier *ftp= new CBezier;
						ftp->copy(pBezier);
						ftp->draw(hdc);
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pLib=pInt.copybyL(fig[i],(CLibS*)fig[j]);
						pLib->draw(hdc);
//						CLibS *ftp= new CLibS;
//						*ftp=pLib;
						if(!cp)
						{
						pLib->clear();
						pLib->sethandle(count);
						pLib->setLayer(currlayer);
						undoList.push("create");
		//				pLib->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.copybyL(fig[i],fig[j],&textc);
						textc.draw(hdc);
						CTextCad *ftp= new CTextCad;
						*ftp=textc;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
		}
	}

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
//	pBezier->create(point);
//	pLine.create(point);
//	pRectangle.create(point);
	CCercle *pC;
	CTextCad textc;
	CLibS pl;
	CLibS *pLib=NULL;//=new CLibS;


	int pk=fit;
	bool sel=false;

	for(int i=0;i<fit;i++)
	{
//		if(fig[i]->getLayer()==currlayer)
//		{

		if (fig[i]->getName()==pLine.getName())
		{
			if (fig[i]->PtinRegion(point))
			{

			for (int j=0;j<fit;j++) 
				{
					if (fig[j]->inselectedstate())
					{
						fig[j]->sethandle(count);
						undoList.push("create");
		//				fig[j]->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
						sfit++;
						count++;
						fig[j]->setMultselect(false);
						if(fig[j]->getName()==pLine.getName())
						{
						pLine=*(CLine*)fig[j];
						pInt.mirror(fig[i],fig[j],&pLine);
						pLine.draw(hdc);
						CLine *ftp= new CLine;
						*ftp=pLine;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.mirror(fig[i],fig[j],&pRectangle);
						pRectangle.draw(hdc);
						CRectangle *ftp= new CRectangle;
						*ftp=pRectangle;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
//						ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.mirror(fig[i],fig[j],&pCircle);
					//	pCircle.draw(hdc);
						CCercle *ftp= new CCercle;
						ftp->copy(pCircle);
						ftp->draw(hdc);
						//*ftp=pC;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.mirror(fig[i],fig[j],pBezier);
						CBezier *ftp= new CBezier;
						ftp->copy(pBezier);
						ftp->draw(hdc);
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pLib=pInt.mirror(fig[i],(CLibS*)fig[j]);
						pLib->draw(hdc);
//						CLibS *ftp= new CLibS;
//						*ftp=pLib;
						if(!cp)
						{
						pLib->clear();
						pLib->sethandle(count);
						pLib->setLayer(currlayer);
						undoList.push("create");
		//				pLib->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
						pInt.mirror(fig[i],fig[j],&textc);
						textc.draw(hdc);
						CTextCad *ftp= new CTextCad;
						*ftp=textc;
						if(!cp)
						{
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						undoList.push("create");
		//				ftp->setUndoparam();
						/*vhan[sfit]=count;*/vhan.push_back(count);
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
		}
	}

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
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{

		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=tex.getName()))
		{
			fig[i]->addnode(point,hdc);
			b=true;
		}
//	}
	}
	return b;

}

bool CDraw::deletenode(CVector point, CDC *hdc)
{
	bool b=false;
	CTextCad tex;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=tex.getName()))
		{
			fig[i]->deletenode(point,hdc);
//			fig[i]->setInit();
			b=true;
		}
//	}
	}

 return b;
}

void CDraw::breakcurve(CVector point)
{
	CInter pInt;
	vector<CVector> *arr;
	vector<CVector> test;
	IA=new CDimA;
	CTextCad tex;
	int pk=fit;
	bool b=false;

	for (int i=0;i<fit;i++)
	{
		if ((fig[i]->inselectedstate())&&(fig[i]->getName()!=tex.getName()))
		{

				if((fig[i]->getName()==pBezier->getName())||(fig[i]->getName()==pCircle.getName()))
				{
					for (int j=0;j<fit;j++)
					{
						if ((fig[j]->PtinRegion(point))&&((fig[j]->getName()==pLine.getName())||(fig[j]->getName()==pRectangle.getName())))
						{
							fig[i]->setintvec(fig[j]->selectvec);
						}
					}

				}

			test=fig[i]->getSvec();
			if(test[0]!=test[2])
			{
				IA->addSLChamf(test,fig[i]);
			}
			else
			{
				test=fig[i]->getSSvec();
				IA->addSLChamf(test,fig[i]);
			}
		}
	}


	for (i=0;i<fit;i++)
	{
		if (fig[i]->PtinRegion(point))
		{
			b=true;
					
				if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
				{
				arr=(vector<CVector> *)fig[i]->Trim(IA->getlselch());
				for(int h=0;h<arr->size();h++)//!=0)
				{
				pLine.createobj(*arr,*(arr+1));
				CLine *ftp= new CLine;
				*ftp=pLine;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
				delete[] arr;
				}else

				if(fig[i]->getName()==pCircle.getName())
				{
				fig[i]->setintvec(IA->getlselch());
			
				fig[i]->setClstate(false);
				CCercle *ftp;
				ftp=(CCercle*)fig[i]->Trim(fig[i]->getSvec());
				ftp->setClstate(false);
//				if(ftp->x!=-1)
				for(int h=0;h<arr->size();h++)//!=0)
				{
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
	//			delete[] arr;
				}else
				
				if(fig[i]->getName()==pBezier->getName())
				{
				fig[i]->setintvec(IA->getlselch());
				fig[i]->setClstate(false);
				CBezier *ftp;
				ftp=(CBezier*)fig[i]->Trim(fig[i]->getSvec());
				ftp->setClstate(false);
				if(ftp->x!=-1)
				{
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
		//		delete[] arr;
				}
			}
	}

	fit=pk;
	delete IA;
//	return b;



/*	CInter pInt;
	vector<CVector> *arr;

	int pk=fit;
	bool b;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{

		if (fig[i]->PtinRegion(point))
		{
			b=true;
					
				if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
				{
				arr=(vector<CVector> *)fig[i]->breakcurve(point);
				//pLine=*(CLine*)fig[i];
				//fig[i]=&pLine;
				pLine.createobj(*arr,*(arr+1));
				delete[] arr;
				CLine *ftp= new CLine;
				*ftp=pLine;
				fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
				//m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				ftp->setUndoparam();
				vhan[sfit]=count;
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
				CCercle *ftp;
				ftp=(CCercle*)fig[i]->breakcurve(point);
				fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
				//m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setUndoparam();
				vhan[sfit]=count;
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
				CBezier *ftp;
				ftp=(CBezier*)fig[i]->breakcurve(point);
				fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
				//m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setUndoparam();
				vhan[sfit]=count;
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
			}
//	}
	}

	fit=pk;
	//return b;*/
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
		
	int pk=fit;

		for(int i=0;i<fit;i++)
		{
			if(fig[i]->transselectedstate())
			{
						
				if((fig[i]->getName()==pL.getName())\
					||(fig[i]->getName()==pR.getName())\
					||(fig[i]->getName()==pli.getName()))
				{
					fig[i]->closecurve(point,hdc);
					fig[i]->setInit();
					b=true;
				}else
				if((fig[i]->getName()==pC.getName())\
					||(fig[i]->getName()==pB.getName())\
					)
				{
					fig[i]->closecurve(point,hdc);
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
	int j;
	int ffit=fit;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (fig[i]->inselectedstate())
		{
            fig[i]->drawdel(hdc);
//			delete fig[i];
			fig[i]->lclear(true);
/*			j=i;
//			fit--;
		
			CFigure **tfig=(CFigure**) new CFigure[fit-1];
			for (i=0;i<j;i++)
			{
				tfig[i]=fig[i];
			}
			for (i=j+1;i<fit;i++)
			{
				tfig[i-1]=fig[i];
			}
			fit--;
			for (i=0;i<fit;i++)
			{
				fig[i]=tfig[i];
			}
			i=j-1;
			sefit=0;*/
		}
//	}
	}


/*	for (int i=fit-1;i>=0;i--)
	{
		if (fig[i]->inselectedstate())
		{
			 fig[i]->drawdel(hdc);
			 delete fig[i];
			 fit--;
		}
	}*/
}

void CDraw::pastearray(CDC *hdc, bool of,int nbrow,int nbcol, double distx,double disty,int nblevel,double lspacing)
{

	CInter pInter;
	vector<CFigure> *arr;
	vector<CFigure>* pbulk=new vector<CFigure>;
	vector<CFigure>::iterator fiter;
	CLibS* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CTextCad textc;
	CImage image;

	int pk=fit;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{

		if (fig[i]->inselectedstate())
		{
		if(fig[i]->getName()!=pLibs.getName())
		{
			arr=fig[i]->translatepArray(of,nbrow,nbcol,distx,disty,nblevel,lspacing,pbulk);
			fig[i]->setMultselect(false);
			for(fiter=arr->begin();fiter<arr->end();fiter++)
			{

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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==image.getName())
				{
				image=*(CImage*)fig[i];
				image.createobj(fiter->ptbegin,fiter->ptend);
				image.draw(hdc);
				image.setInit();
				CImage *ftp= new CImage;
				*ftp=image;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)fig[i]);
				pCircle.addvec(fiter->ptbegin,fiter->ptend);
				pCircle.draw(hdc);
				pCircle.setInit();
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
				pBezier->copy((CBezier*)fig[i]);
				pBezier->addvec(fiter->ptbegin,fiter->ptend);
				pBezier->draw(hdc);
				pBezier->setInit();
				CBezier *ftp= new CBezier;
				ftp->copy(pBezier);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
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
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				fig[pk]=ftp;
				pk++;
				}
			}
		}
		else
		{
	
			lib=pInter.pasteArray(fig[i]->getCenter(),(CLibS*)fig[i],of,nbrow,nbcol,distx,disty,nblevel,lspacing);
			int k=lib[0].x;
			for(int i=0;i<k;lib++,i++)
			{
			lib->draw(hdc);
			CLibS *ftp= new CLibS;
			*ftp=*lib;
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
			fig[pk]=ftp;
			pk++;
			}		}
	}
//	}
	}

	fit=pk;

	delete pbulk;

	
/*	
	
	vector<CVector> *arr,*crr,*rrr;

	CVector center;
	CLine pliter;
	CCercle pciter;
	CRectangle priter;
	CLibS pLibs;
	CInter pInter;

	int pk=fit;
	for (int i=0;i<fit;i++)
	{
		fig[i]->selectSM(hdc);
		if (fig[i]->inselectedstate())
		{
			if(fig[i]->getName()!=pLibs.getName())
			{
				arr=fig[i]->translatepArray(nbrow,nbcol,distx,disty);
				if(fig[i]->getName()==pLine.getName())
				{
					pLine=*(CLine*)fig[i];
					pLine.createobj(*arr,*(arr+1));
					pLine.draw(hdc);
					delete[] arr;
					CLine *ftp= new CLine;
					*ftp=pLine;
					fig[pk]=ftp;
					pk++;
				}
				else
				if(fig[i]->getName()==pRectangle.getName())
				{
					pRectangle=*(CRectangle*)fig[i];
					pRectangle.createobj(*arr,*(arr+1));
					pRectangle.draw(hdc);
					delete[] arr;
					CRectangle *ftp= new CRectangle;
					*ftp=pRectangle;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
					pCircle=*(CCercle*)fig[i];
					pCircle.addvec(*arr,*(arr+1));
					pCircle.draw(hdc);
					CCercle *ftp= new CCercle;
					*ftp=pCircle;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
					pBezier=*(CBezier*)fig[i];
					pBezier->addvec(*arr,*(arr+1));
					pBezier->draw(hdc);
					CBezier *ftp= new CBezier;
					*ftp=pBezier;
					fig[pk]=ftp;
					pk++;
				}
			}
			else
			{
				pLibs=pInter.pasteArray((CLibS*)fig[i],nbrow,nbcol,distx,disty);
				pLibs.draw(hdc);
				CLibS *ftp= new CLibS;
				*ftp=pLibs;
				fig[pk]=ftp;
				pk++;
			}
		}		
	}
	fit=pk;*/

}


void CDraw::paste(CDC *hdc, CVector point)
{
	vector<CVector> *arr,*crr,*rrr;

	CVector center;
	CLine pliter;
	CCercle pciter;
	CRectangle priter;
	CImage image;
	CTextCad textc;
	CLibS* pLibs=new CLibS;
	CInter pInter;

	int pk=fit;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{

//]		fig[i]->selectSM(hdc);
		if (fig[i]->inselectedstate())
		{
			if(fig[i]->getName()!=pLibs->getName())
			{
			arr=fig[i]->translatep(fig[i]->getCenter(),point);
			fig[i]->setMultselect(false);
				if(fig[i]->getName()==pLine.getName())
				{
					pLine=*(CLine*)fig[i];
					pLine.createobj(*arr,*(arr+1));
					pLine.draw(hdc);
					delete[] arr;
					CLine *ftp= new CLine;
					*ftp=pLine;
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					ftp->clear();
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					undoList.push("create");
	//				ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
				}
				else
				if(fig[i]->getName()==pRectangle.getName())
				{
					pRectangle=*(CRectangle*)fig[i];
					pRectangle.createobj(*arr,*(arr+1));
					pRectangle.draw(hdc);
					delete[] arr;
					CRectangle *ftp= new CRectangle;
					*ftp=pRectangle;
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					ftp->clear();
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					undoList.push("create");
	//				ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==image.getName())
				{
					image=*(CImage*)fig[i];
					image.createobj(*arr,*(arr+1));
					image.draw(hdc);
					delete[] arr;
					CImage *ftp= new CImage;
					*ftp=image;
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					ftp->clear();
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					undoList.push("create");
	//				ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
					pCircle.copy(*(CCercle*)fig[i]);
					pCircle.addvec(*arr,*(arr+1));
					pCircle.draw(hdc);
					pCircle.setInit();
					CCercle *ftp= new CCercle;
					ftp->copy(pCircle);
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					ftp->clear();
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					undoList.push("create");
	//				ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
					pBezier->copy((CBezier*)fig[i]);
					pBezier->addvec(*arr,*(arr+1));
					pBezier->draw(hdc);
					pBezier->setInit();
					CBezier *ftp= new CBezier;
					ftp->copy(pBezier);
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//			ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
					fig[pk]=ftp;
					pk++;
				}else
				if(fig[i]->getName()==textc.getName())
				{
					textc=*(CTextCad*)fig[i];
					textc.addvec(*arr,*(arr+1));
					textc.draw(hdc);
					CTextCad *ftp= new CTextCad;
					*ftp=textc;
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					ftp->clear();
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					undoList.push("create");
	//				ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
					sfit++;
					count++;
					fig[pk]=ftp;
					pk++;
				}
			}
			else
			{
				pLibs=pInter.paste(fig[i]->getCenter(),point,(CLibS*)fig[i]);
				pLibs->draw(hdc);
//				CLibS *ftp= new CLibS;
//				*ftp=pLibs;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				pLibs->clear();
				pLibs->sethandle(count);
				pLibs->setLayer(currlayer);
				undoList.push("create");
//				pLibs->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=pLibs;
				pk++;
			}
		}
//	}
	}
	fit=pk;

}

void CDraw::Init()
{
/*	CBezier pb;
	CCercle pC;
	pCircle=pC;
	pArc=pC;

	CRectangle pR;
	pRectangle=pR;

	CLine pL;
	pLine=pL;
	//	CLibS pLib;
	CQLine pQ,pQLineprev;
	pQLine=pQ;
	pQLineprev=pQ;

	pBezier=pb;*/
/*	B=false;
	Bminus=false;
	
	selected=false;

/*	for(int i=0;i<fit;i++)
	{
	free(fig[i]);
	}*/
/*	free(fig);
	fig=NULL;
	DimA=NULL;
	DimL=NULL;
	Dim=NULL;
	fit=0;
	m=0
	endDraw=FALSE;
*/
	count=0;
	CVector v(0,0,1);
	v0=v;
	fit=0;
	sfit=0;
	sefit=0;
	bck=false;
//	fig=NULL;
//	sfig=NULL;
	m=0;ms=0;
//	fig[fit]=&pLine;
	cdel=false;

	initVect();
	B=false;
	Bminus=false;
	positions[1]=v0;ita=0;
	rzoom=0.5;
	
	selected=false;
	menuselect=false;

/*	Line.clear();
	selected_Lines.clear();
	fiter=Figure.begin();
	citer=Cercle.begin();*/
	endDraw=FALSE;
	change=false;
//	pBezier=new CBezier;
	nbc=0;
	valid=false;
	currlayer.clear=false;
	currlayer.on=true;
}
 struct INDEX 
 {
	DWORD pos;
	CString name;
 };

void CDraw::save(CDC *hdc,CFile& file)
{
 vector<INDEX> index(fit);
///////////////////////////////////////////////////////////
		char result[MAX_PATH],dir[MAX_PATH];

		GetTempPath(MAX_PATH,dir);

		 /* Attempt to find a unique filename: */
		GetTempFileName(dir, // dir. for temp. files 
		"andyc",                // temp. filename prefix 
		0,                    // create unique name 
		result);          // buffer for name 

		CFile filo(result,CFile::modeCreate|CFile::modeReadWrite);

		CFigure **tfig=NULL;
		tfig=(CFigure**) realloc(tfig,sizeof(CFigure*)*fit);
		int j=fit;
		fit=0;
		for (int i=0;i<j;i++)
		{
			if(fig[i]->ptbegin.size()!=0)
			{
			tfig[fit]=fig[i];
			fit++;
			}
		}
		for (i=0;i<fit;i++)
		{
			fig[i]=tfig[i];
		}

	//	file.Write(&version,sizeof(int));
	//	file.Write(&fit,sizeof(int));
		filo.Write(&version,sizeof(int));
		filo.Write(&fit,sizeof(int));
		CTVector tv;
		tv.savefile(file);
		CString nm;
		int sz;
		
		for(i=0;i<fit;i++)
		{
			nm=fig[i]->getName();
			index[i].pos=file.GetPosition();
			index[i].name=fig[i]->getInfName();
			filo.Write(&index[i].pos,sizeof(index[i].pos));
			int lop=index[i].name.GetLength();
			filo.Write(&lop,sizeof(index[i].name));
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

	filo.Seek(sizeof(i)*2,CFile::begin);
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

		file.Read(&version,sizeof(int));
		if(version==0)
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
			CTVector tv;
			tv.openfile(file);
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
					fig[i]=new CLibS(file);
				}
				else
				if(sz==6)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CTextCad(file);
				}
				else
				if(sz==7)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i]=new CImage(hdc,file);
				}

//				fig[i]->sethandle(count);
				undoList.push("create");
//				fig[i]->setUndoparam();
				fig[i]->setcorevecor();

				/*vhan[sfit]=count;*/vhan.push_back(count);
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
		if(version==0)
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
			CTVector tv;
			tv.Readfile(file);

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
					fig[i+fit]=new CLibS(file);
				}
				else
				if(sz==6)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CTextCad(file);
				}
				else
				if(sz==7)
				{
					/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
					////m=_msize(fig);
					fig[i+fit]=new CImage(hdc,file);
				}

				fig[i]->sethandle(count);
				undoList.push("create");
//				fig[i]->setUndoparam();
				fig[i]->setcorevecor();

				/*vhan[sfit]=count;*/vhan.push_back(count);
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
		   vmemento.push(m);
		   undoList.push("delete");
			vhan.push_back(vs[i]->gethandle());
			sfit++;
			iter=find(fig.begin(),fig.end(),vs[i]);
			if(iter!=fig.end())
			{
			fig.erase(iter);fit--;
			}
	}
/*			vector<CFigure*> f(fit+1);;
			for(i=0;i<fit;i++)
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

*/
	vs.clear();
/*	CFigure **tfig;
	for (i=0;i<j;i++)
	{
		tfig[i]=fig[i];
	}
	for (i=j+1;i<fit;i++)
	{
		tfig[i-1]=fig[i];
	}
	fit--;
	for (i=0;i<fit;i++)
	{
		fig[i]=tfig[i];
	}*/

}

/*bool CDraw::copyl(CDC *hdc, CVector point,bool cp)
{

	CInter pInt;CVector center;
	CLine pL;
	CRectangle pR;
	CCercle pC;
	CBezier pB;
	CImage image;
	CTextCad textc;

	CLibS* pLibs=new CLibS;
	CInter pInter;
	vector<CVector> *arr;

	int pk=fit;
	bool b;
	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (fig[i]->getName()==pL.getName())
		{
			if (fig[i]->PtinRegion(point))
			{
				b=true;
				for (int j=0;j<fit;j++) 
				{
					if (fig[j]->inselectedstate())
					{
					center=fig[i]->CopybyLine(fig[j]);
					fig[j]->setMultselect(false);
					if(fig[j]->getName()!=pLibs->getName())
					{
					arr=fig[j]->translatep(fig[j]->getCenter(),center);
					
						if(fig[j]->getName()==pL.getName())
						{
						pL=*(CLine*)fig[j];
						pL.createobj(*arr,*(arr+1));
						pL.draw(hdc);
						delete[] arr;
						CLine *ftp= new CLine;
						*ftp=pL;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						//m=_msize(fig);
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pR.getName())
						{
						pR=*(CRectangle*)fig[j];
						pR.createobj(*arr,*(arr+1));
						pR.draw(hdc);
						delete[] arr;
						CRectangle *ftp= new CRectangle;
						*ftp=pR;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						//m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==image.getName())
						{
						image=*(CImage*)fig[j];
						image.createobj(*arr,*(arr+1));
						image.draw(hdc);
						delete[] arr;
						CImage *ftp= new CImage;
						*ftp=image;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						//m=_msize(fig);
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pC.getName())
						{
						pC=*(CCercle*)fig[j];
						pC.addvec(*arr,*(arr+1));
						pC.draw(hdc);
						delete[] arr;
						CCercle *ftp= new CCercle;
						*ftp=pC;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						//m=_msize(fig);
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==pB.getName())
						{
						pB=*(CBezier*)fig[j];
						pB.addvec(*arr,*(arr+1));
						delete[] arr;
						CBezier *ftp= new CBezier;
						ftp->copy(&pB);
						ftp->draw(hdc);
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						//m=_msize(fig);
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						}else
						if(fig[j]->getName()==textc.getName())
						{
						textc=*(CTextCad*)fig[j];
						textc.addvec(*arr,*(arr+1));
						textc.draw(hdc);
						delete[] arr;
						CTextCad *ftp= new CTextCad;
						*ftp=textc;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						//m=_msize(fig);
						ftp->clear();
						ftp->sethandle(count);
						ftp->setLayer(currlayer);
						ftp->setUndoparam();
						vhan[sfit]=count;
						sfit++;
						count++;
						fig[pk]=ftp;
						pk++;
						}
						else
						{
							fig[j]=ftp;
						}
						} 
					}
					else
					{
					b=true;
					pLibs=pInter.paste(fig[j]->getCenter(),center,(CLibS*)fig[j]);
					pLibs->draw(hdc);
   //					CLibS *ftp= new CLibS;
	//				*ftp=pLibs;
						if(!cp)
						{
						fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
						//m=_msize(fig);
				pLibs->clear();
				pLibs->sethandle(count);
				pLibs->setLayer(currlayer);
				pLibs->setUndoparam();
				vhan[sfit]=count;
				sfit++;
				count++;
						fig[pk]=pLibs;
						pk++;
						}
						else
						{
							fig[j]=pLibs;
						}
					}
					}
				}
			}
		}
//		}
	}

	fit=pk;
	return b;
}
*/
void CDraw::copyRSparam(CDC *hdc,double angle, int nbcopy,int nblevel,int dlevel,bool align)
{
	angle=(angle*2*pi)/360;

	CInter pInter;
	vector<CFigure> *arr;
	vector<CFigure>* pbulk=new vector<CFigure>;
	vector<CFigure>::iterator fiter;
	CLibS* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CTextCad textc;

	int pk=fit;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{

		if (fig[i]->inselectedstate())
		{
		if(fig[i]->getName()!=pLibs.getName())
		{
			arr=fig[i]->RotateCopyP(hdc,angle,nbcopy,nblevel,dlevel,pbulk,align);
			fig[i]->setMultselect(false);
			for(fiter=arr->begin();fiter<arr->end();fiter++)
			{

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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);			
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)fig[i]);
				pCircle.addvec(fiter->ptbegin,fiter->ptend);
				pCircle.draw(hdc);
				pCircle.setInit();
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				//fig[pk]=ftp;
				fig.push_back(ftp);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
			}
		}
		else
		{
			lib=pInter.RotateCopyP(hdc,angle,nbcopy,nblevel,dlevel,align,(CLibS*)fig[i]);
			int k=lib[0].x;
			for(int i=0;i<k;lib++,i++)
			{
			lib->draw(hdc);
			CLibS *ftp= new CLibS;
			*ftp=*lib;
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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

	delete pbulk;

}

void CDraw::copyRS(CDC *hdc,CVector center,bool align)
{

	CInter pInter;
	vector<CFigure> *arr;
	vector<CFigure>* pbulk=new vector<CFigure>;
	vector<CFigure>::iterator fiter;
	CLibS* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CTextCad textc;

	int pk=fit;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (fig[i]->inselectedstate())
		{
		if(fig[i]->getName()!=pLibs.getName())
		{
			arr=fig[i]->RotateCopyP(hdc,center,pbulk,align);
			fig[i]->setMultselect(false);
			for(fiter=arr->begin();fiter<arr->end();fiter++)
			{

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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
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

	delete pbulk;
}

void CDraw::copybyCenter(CDC *hdc, CVector point)
{
	CInter pInter;
	vector<CLibS>* lib;
	vector<CLibS>::iterator plib;
	CLibS pLibs;
	CImage im;

	CFigure *arr;
	CFigure* pbulk=new CFigure;

	int pk=fit;

	for (int i=0;i<fit;i++)
	{
//	if(fig[i]->getLayer()==currlayer)
//	{
		if (fig[i]->inselectedstate())
		{
			if(fig[i]->getName()==im.getName()) continue;

			if(fig[i]->getName()!=pLibs.getName())
			{
				arr=fig[i]->copybyC(hdc,point,pbulk);
				fig[i]->setMultselect(false);

				if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
				{
				pLine=*(CLine*)fig[i];
				pLine.createobj(arr->ptbegin,arr->ptend);
				pLine.draw(hdc);
				CLine *ftp= new CLine;
				*ftp=pLine;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)fig[i]);
				pCircle.addvec(arr->ptbegin,arr->ptend);
				pCircle.draw(hdc);
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
//				*ftp=pCircle;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				if(fig[i]->getName()==pBezier->getName())
				{
				pBezier->copy((CBezier*)fig[i]);
				pBezier->addvec(arr->ptbegin,arr->ptend);
				CBezier *ftp= new CBezier;
				ftp->copy(pBezier);
				ftp->draw(hdc);
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
			}
			else
			{
			CLibS *ftp;

			ftp=pInter.copybyC(hdc,fig[i]->getCenter(),point,pbulk,(CLibS*)fig[i]);
			ftp->draw(hdc);
	//		CLibS *ftp= new CLibS;
	//		*ftp=pLibs;
			/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
			////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				undoList.push("create");
//				ftp->setUndoparam();
				/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
			fig[pk]=ftp;
			pk++;
			}
			}
//	}
		}

	fit=pk;

	delete pbulk;

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
	
	for (int i=0;i<fit;i++)
	{
		if (fig[i]->inselectedstate())
		{
			fig[i]->setLcolor(hdc,color,bcolor);
			s=true;
			
		}
	}
	if((!s)&&(fit>0))
	{
		fig[fit-1]->setLcolor(hdc,color,bcolor);
	}

}



void CDraw::forundo(CWnd *wnd,CDC *hdc)
{
	int j=vs.size();
	for (int i=0;i<j;i++)
	{
		   CMemento* m=new CMemento(vs[i]);
		   vmemento.push(m);
		   undoList.push("Memento");
//			fig[i]->setUndoparam();
//			/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
//			sfit++;
	}
}

void CDraw::undo(CDC *hdc)
{
/*	if(sfit>0)
	{
		for(int i=0;i<fit;i++)
		{
			if(fig[i]->gethandle()==vhan[sfit-1])
			{
				if(fig[i]->Undo())
					sfit--;
				break;
			}
			
		}
	}*/
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
        CMemento* m1 = new CMemento(fig[fit-1]);
	    rmemento.push(m1);
	    redoList.push("delete");
		fit--;count--;
		}
		}
		if (obj=="delete")
		{
		//get the Memento
		CMemento* m = vmemento.top();vmemento.pop();
		fig.resize(fit+1);
		fig[fit]=m->getM(); //and restore the old position
		delete m;
        CMemento* m1 = new CMemento(fig[fit]);
	    rmemento.push(m1);
	    redoList.push("create");
		fit++;count++;
		}
		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = vmemento.top();vmemento.pop();
        CMemento* m1 = new CMemento(m->getM());
		m->Restore(); //and restore the old position
		delete m;
	    rmemento.push(m1);
	    redoList.push("Memento");
		}
	}

}

void CDraw::redo(CDC *hdc)
{
/*		for(int i=0;i<fit;i++)
		{
			if(fig[i]->gethandle()==vhan[sfit])
			{
				if(fig[i]->Redo())
					sfit++;
				break;
				
			}
		}*/
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
		CMemento* m = rmemento.top();rmemento.pop();
		fig[fit]=m->getM(); //and restore the old position
		delete m;
        CMemento* m1 = new CMemento(fig[fit]);
	    vmemento.push(m1);
	    undoList.push("create");
		fit++;count++;

		}
		//if this is a Memento, the last action was a move
		if(obj=="Memento")
		{
		//get the Memento
		CMemento* m = rmemento.top();rmemento.pop();
		CFigure *f=m->getM();
        CMemento* m1 = new CMemento(f);
		m->Restore(); //and restore the old position
		delete m;
	    vmemento.push(m1);
	    undoList.push("Memento");
		}
	}

}

CRect CDraw::grid(CDC *rhdc,CDC *hdc,CSize cp)
{
//	pushUnit();
//	CVector v(30,0);
 //	Translate(v);
//	VendT();
	CVector k;
	CVector ktl(k.getscrtop()),kbr(k.getscrb());
	CVector ktr(kbr.x,ktl.y,0,1),kbl(ktl.x,kbr.y,0,1);

//	CVector v1(-(cp.cx/2),-(cp.cy/2)),v2((cp.cx/2),-(cp.cy/2)),\
			v3((cp.cx/2),(cp.cy/2)),v4(-(cp.cx/2),(cp.cy/2));
	
	CBrush br,*bold;
	br.CreateSolidBrush(RGB(255,255,255));
	bold=hdc->SelectObject(&br);

	CPen pat;
	pat.CreatePen(PS_SOLID,2,RGB(12,12,0));
	CPen* pOldPen=hdc->SelectObject(&pat);

	hdc->BeginPath();
	
/*	hdc->MoveTo(v1);
	hdc->LineTo(v2);
	hdc->LineTo(v3);
	hdc->LineTo(v4);
	*/
//	CRect cb(kt,kb);
	hdc->MoveTo(ktl);
	hdc->LineTo(ktr);
	hdc->LineTo(kbr);
	hdc->LineTo(kbl);
	hdc->LineTo(ktl);
	hdc->EndPath();
	hdc->StrokeAndFillPath();
	hdc->SelectObject(pOldPen);
	hdc->SelectObject(bold);


	CVector v0(k.getcamor()),vx(100,0,0,0),vy(0,100,0,0),v1,vz(0,0,100,0);

	display(rhdc,hdc);
/*	CVector t0(v1.getcamor()),tx(v1.getcamx()),ty(v1.getcamy()),tz(v1.getcamz());

	CPoint pt0(t0);
	hdc->MoveTo(pt0);
	hdc->TextOut(pt0.x,pt0.y,"O");
	CPoint pt1((tx*150+t0));
	hdc->LineTo(pt1);
	hdc->TextOut(pt1.x,pt1.y,"X");
	hdc->MoveTo(pt0);
	CPoint pt2((ty*150+t0));
	hdc->LineTo(pt2);
	hdc->TextOut(pt2.x,pt2.y,"Y");
	hdc->MoveTo(pt0);
	CPoint pt3((tz*150+t0));
	hdc->LineTo(pt3);
	hdc->TextOut(pt3.x,pt3.y,"Z");
*/
	
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

	
	return CRect(ktl,kbr);
//	pushUnit();


}

void CDraw::group(CDC *hdc)
{
	int l=0;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->transselectedstate())
		{
			l++;
		}
	}

	if(l>1)
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

		for(i=0;i<fit;i++)
		{
			if(fig[i]->transselectedstate())
			{
				arr=fig[i]->translatep(fig[i]->getCenter(),fig[i]->getCenter());
						
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
		lib->sethandle(count);
		lib->setUndoparam();
		lib->setLayer(currlayer);
		/*vhan[sfit]=count;*/vhan.push_back(count);
		sfit++;
		count++;

			fig[fit]=lib;
			fit++;
			vs.clear();
			sefit=0;
		}
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
	for(int i=0;i<fit;i++)
	{
			arr=fig[i]->translatep(fig[i]->getCenter(),fig[i]->getCenter());
					
			if(fig[i]->getName()==pL.getName())
			{
				pL=*(CLine*)fig[i];
				pL.createobj(*arr,*(arr+1));
				delete[] arr;
				CLine *ftp= new CLine;
				*ftp=pL;
				lib.add(ftp);
			}else
			if(fig[i]->getName()==pR.getName())
			{
				pR=*(CRectangle*)fig[i];
				pR.addvec(*arr,*(arr+1));
				delete[] arr;
				CRectangle *ftp= new CRectangle;
				*ftp=pR;
				lib.add(ftp);
			}else
			if(fig[i]->getName()==pC.getName())
			{
				pC.copy(*(CCercle*)fig[i]);
				pC.addvec(*arr,*(arr+1));
				delete[] arr;
				CCercle *ftp= new CCercle;
				ftp->copy(pC);
				lib.add(ftp);
			}else
			if(fig[i]->getName()==pB.getName())
			{
				pB.copy((CBezier*)fig[i]);
				pB.addvec(*arr,*(arr+1));
				delete[] arr;
				CBezier *ftp= new CBezier;
				ftp->copy(&pB);
				lib.add(ftp);
			}else
			if(fig[i]->getName()==textc.getName())
			{
				textc=*(CTextCad*)fig[i];
				textc.addvec(*arr,*(arr+1));
				delete[] arr;
				CTextCad *ftp= new CTextCad;
				*ftp=textc;
				lib.add(ftp);
			}else
			if(fig[i]->getName()==image.getName())
			{
				image=*(CImage*)fig[i];
				image.addvec(*arr,*(arr+1));
				delete[] arr;
				CImage *ftp= new CImage;
				*ftp=image;
				lib.add(ftp);
			}else
			if(fig[i]->getName()==lib.getName())
			{
				pli.Copy(*(CLibS*)fig[i]);
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
				tcad->getTextrec(wnd,hdc);
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

CPoint CDraw::setFont(CDC *hdc,LOGFONT font,COLORREF ccl)
{
	CTextCad test;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->getName()==test.getName())
		{
			if(fig[i]->transselectedstate())
			{
			return fig[i]->setfont(hdc,font,ccl);
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

	for(int k=0;k<fit;k++)
	{
		if(fig[k]->transselectedstate())
		{
//			fig[k]->setUndoparam();
//			vhan[sfit]=fig[k]->gethandle();
//			sfit++;
			b=true;
			CVector v=fig[k]->getCenter();
			fig[k]->setRotateCenter(v);
			v1=v-v1;
			v2=v-v2;

			fig[k]->Rotate(0,v1,v2);
		}
	}

	return b;
}


void CDraw::ungroup(CDC *hdc)
{
	CLibS *lib=new CLibS;
	vector<CVector> *arr;
	bool connect=false;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->transselectedstate())
		{
			if(fig[i]->getName()==lib->getName())
			{
				CFigure **figh;
				lib=(CLibS*)fig[i];
				figh=lib->degroup();
				for(int j=i;j<fit;j++)
				{
					fig[j]=fig[j+1];
				}
				fit--;
				int jfit=lib->getnblibelemt();
				for(j=0;j<jfit;j++)
				{
					fig[fit+j]=figh[j];
				}
				fit+=jfit;
				break;
			}
		}
	}
	vs.clear();
	delete lib;
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

void CDraw::showsnap(CDC *hdc, CVector point,CString mode)
{
	int j=0;
	CVector v1,v2;
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->snapok(point))
		{
			j++;
			if(j==1)
			{
				v1=fig[i]->snapv[0].intersect(fig[i]->snapv[2]);
			}
			if(j==2)
			{
				v2=fig[i]->snapv[0].intersect(fig[i]->snapv[2]);
				CVector v=v2.intersect(v1);
				fig[i]->setintersect(true,v);
			}
		}
		fig[i]->drawsnap(hdc,mode);

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
				for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
				{
						(*it)->SendNotify("selectinfo",pp);
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

bool CDraw::Trim(CVector point)
{
	CInter pInt;
	vector<CVector> *arr;
	vector<CVector> test;
	CDimA gIA;

	int pk=fit;
	bool b=false;

	for (int i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
		if(fig[i]->transselectedstate())
		{

				if((fig[i]->getName()==pBezier->getName())||(fig[i]->getName()==pCircle.getName()))
				{
					for (int j=0;j<fit;j++)
					{
						if ((fig[j]->inRegion(point))&&((fig[j]->getName()==pLine.getName())||(fig[j]->getName()==pRectangle.getName())))
						{
							fig[i]->setintvec(fig[j]->selectvec);
						}
					}

				}

			test=fig[i]->getSvec();
			if((test.size()!=0)&&(test[0]!=test[2]))
			{
				gIA.addSLChamf(test,fig[i]);
			}
			else
			{
				test=fig[i]->getSSvec();
				gIA.addSLChamf(test,fig[i]);
			}
		}
		}
	}


	for (i=0;i<fit;i++)
	{
		if(!(fig[i]->getLayer()).clear)
		{
		if (fig[i]->inRegion(point))
		{
			fig[i]->setUndoparam();
			/*vhan[sfit]=fig[i]->gethandle();*/vhan.push_back(fig[i]->gethandle());
			sfit++;

			b=true;
					
				if((fig[i]->getName()==pLine.getName())||(fig[i]->getName()==pRectangle.getName()))
				{
		//		fig[i]->setintvec(IA->getlselch());
				arr=(vector<CVector> *)fig[i]->Trim(gIA.getlselch());
				if(arr!=0)
				{
				pLine.createobj(*arr,*(arr+1));
				CLine *ftp= new CLine;
				*ftp=pLine;
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				ftp->setUndoparam();
			//	/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
				delete[] arr;
				}else

				if(fig[i]->getName()==pCircle.getName())
				{
				fig[i]->setintvec(gIA.getlselch());
			
				fig[i]->setClstate(false);
				CCercle *ftp;
				vector<CVector> lm=fig[i]->getSvec();
				if(lm.size()==0) continue;
				ftp=(CCercle*)fig[i]->Trim(lm);
				ftp->setClstate(false);
				if(ftp->x!=-1)
				{
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
			//	ftp->setUndoparam();
			//	/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}
				else
				delete ftp;
				}else
				
				if(fig[i]->getName()==pBezier->getName())
				{
				fig[i]->setintvec(gIA.getlselch());
				fig[i]->setClstate(false);
				CBezier *ftp;
				vector<CVector> lm=fig[i]->getSvec();
				if(lm.size()==0) continue;
				ftp=(CBezier*)fig[i]->Trim(lm);
				ftp->setClstate(false);
				if(ftp->x!=-1)
				{
				/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
				////m=_msize(fig);
				ftp->clear();
				ftp->sethandle(count);
				ftp->setLayer(currlayer);
				ftp->setUndoparam();
			//	/*vhan[sfit]=count;*/vhan.push_back(count);
				sfit++;
				count++;
				fig[pk]=ftp;
				pk++;
				}else
				delete ftp;
				}
			}
		}
	}

	fit=pk;
//	delete IA;
	return b;
}

void CDraw::setzoomrat(double zr)
{
	CVector v00(0,0,0,1);

	cam.zoom(zr);
/*	CVector v;
	v.zoom(zr);
	rzoom=zr;*/

}

void CDraw::setCenter(CVector p)
{
//	cp=p;
//	pushUnit();
//	cp.assignPL(cp);
//	cp+=v0;
 //	Translate(cp);
//	Scale(rzoom,rzoom);
//	VendT();
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
	cam.setcamorigin(NULL);


}

void CDraw::setfitzoom(double d)

{
	rzoom=d;
//	cp=cp*d;
	VinitVect();
// 	Translate(cp);
//	Scale(d,d);
//	VendT();
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
	return v.getzoomrat();
}



CVector CDraw::getMouse(CVector v)
{
	return v;

}

void CDraw::saveBMP(CDC *hdc,CBitmap* bitmap, CFile &file)
{
/*	CDC *hmdc=new CDC;
	hmdc->CreateCompatibleDC(hdc);

	CImage img;
	CLibS slib;
	group(slib);
	slib.updatecore();

	CBitmap bmp,amp;
	double rh=hdc->GetDeviceCaps(HORZRES)/hdc->GetDeviceCaps(HORZSIZE);
	double rv=hdc->GetDeviceCaps(VERTRES)/hdc->GetDeviceCaps(VERTSIZE);

	CRect wcr(slib.p0,slib.p2);
	hdc->LPtoDP(&wcr);
	wcr.NormalizeRect();
	bmp.CreateCompatibleBitmap(hdc,wcr.Width(),wcr.Height());
	CBitmap *oldb=hmdc->SelectObject(&bmp);

	hmdc->SetMapMode(hdc->GetMapMode());
	hmdc->SetWindowExt(hdc->GetWindowExt());
	hmdc->SetViewportExt(hdc->GetViewportExt());
	hmdc->SetWindowOrg(hdc->GetWindowOrg());
	slib.draw(hdc);
	CPalette *pl=hmdc->SelectPalette(hdc->GetCurrentPalette(),0);
	hmdc->SelectObject(pl);
	hmdc->RealizePalette();


	CPoint k(0,0);

	hmdc->DPtoLP(&wcr);
	hmdc->BitBlt(0,0,wcr.Width(),wcr.Height(),hdc,wcr.left,wcr.top,SRCCOPY);
	hmdc->SelectObject(oldb);
	DWORD j=GetLastError();
	BITMAP bb;
	bmp.GetBitmap(&bb);
	j=GetLastError();

*/
	CImage img;
	HGLOBAL hDib;
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
	
//	delete hmdc;

}

/*
LOGFONT CDraw::getFont()
{
	CTextCad t;
	for (int i=0;i<fit;i++)
	{
		if((!(fig[i]->getLayer()).clear)&&(fig[i]->getName()==t.getName()))
		{
		if(fig[i]->transselectedstate())
		{
			CTextCad *tcad=(CTextCad*)fig[i];
			return tcad->getFont();
		}
		}
	}


}
*/
void CDraw::Initlib(CTreeCtrl &tctl)
{
	if(tctl.GetCount()!=-1) tctl.DeleteAllItems();
	CFileFind finder;
	bool bWorking=finder.FindFile("*.deh");
	while(bWorking)
	{
	bWorking=finder.FindNextFile();
	CFile file(finder.GetFilePath(),CFile::modeRead);
	int tversion;
	HTREEITEM t;
	HTREEITEM it1=tctl.InsertItem(file.GetFileTitle(),0,1);
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
				t=tctl.InsertItem(m,2,2,it1,t);
				file.Read(&lpo,sizeof(lpo));
			}
/*			CTVector tv;
			tv.Readfile(file);
			string nm;
			int sz;
			for(int i=0;i<tfit;i++)
			{
				int tsz;
				file.Read(&tsz,sizeof(sz));
				if(tsz==0)
				{
					CLine f;
					f.Readfile(file);
				//	file.Seek(sizeof(CLine),CFile::current);
				}else
				if(tsz==1)
				{
					CRectangle f;
					f.Readfile(file);
				//	file.Seek(sizeof(CRectangle),CFile::current);
				}
				else
				if(tsz==2)
				{
					CQLine f;
					f.Readfile(file);
//					file.Seek(sizeof(CQLine),CFile::current);
				}
				else
				if(tsz==3)
				{
					CBezier f;
					f.Readfile(file);
//					file.Seek(sizeof(CBezier),CFile::current);
				}
				else
				if(tsz==4)
				{
					CCercle f;
					f.Readfile(file);
//					file.Seek(sizeof(CCercle),CFile::current);
				}
				else
				if(tsz==5)
				{
					CLibS *lb1=new CLibS(file);
					t=tctl.InsertItem(lb1->getInfName(),2,2,it1,t);
					delete lb1;
				}
				else
				if(tsz==6)
				{
					file.Seek(sizeof(CTextCad),CFile::current);
				}
				else
				if(tsz==7)
				{
					file.Seek(sizeof(CImage),CFile::current);
				}

			}
			file.Seek(sizeof(FLAYER),CFile::current);*/
		file.Close();
		}
	}
}

void CDraw::Insertlib(CDC *hdc,CString &f, CString &l,CVector pos)
{
	CLibS *pLibs;
	CInter pInter;

	CFileFind finder;
	bool bWorking=finder.FindFile(f+".deh");
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
							CLibS* fl=new CLibS(file);
							f=fl;
							break;
						}
					case 6:
						{
							CTextCad* fl=new CTextCad(file);
							f=fl;
							break;
						}
					case 7:
						{
							CImage* fl=new CImage(hdc,file);
							f=fl;
							break;
						}
					}
					file.Seek(lpos1,CFile::begin);

						f->sethandle(count);
						f->setLayer(currlayer);
						f->setUndoparam();
						f->setcorevecor();
						f->updatecore();
						CFigure* h=pInter.paste(f->getCenter(),pos,f);
						delete f;
						h->draw(hdc);
						SELECT s=full;
						h->setselectmode(s);
						h->setclick(true);
						h->setMultselect(true);
						h->selectSM(hdc);

						vhan.push_back(count);
						sfit++;
						count++;
						Bminus=true;
						fig.resize(fig.size()+1);
						fig[j0+fit]=h;
						vs.push_back(fig[j0+fit]);
						j0++;
						break;

				}
			}
			fit+=j0;
/*			CTVector tv;
			tv.Readfile(file);
			string nm;
			int sz;
			int j=0;
			for(i=0;i<ffit;i++)
			{
				file.Read(&sz,sizeof(sz));
				if(sz==0)
				{
					CLine f;
					f.Readfile(file);
				}
				if(sz==1)
				{
					CRectangle f;
					f.Readfile(file);
				}
				else
				if(sz==2)
				{
					CQLine f;
					f.Readfile(file);
				}
				else
				if(sz==3)
				{
					CBezier f;
					f.Readfile(file);
				}
				else
				if(sz==4)
				{
					CCercle f;
					f.Readfile(file);
				}
				else
				if(sz==5)
				{
					CLibS *h=new CLibS(file);
					if(h->getInfName()==l)
					{
						fig.resize(fig.size()+1);
						h->sethandle(count);
						h->setUndoparam();
						h->setcorevecor();
						h->updatecore();
						h=pInter.paste(h->getCenter(),pos,h);
						h->draw(hdc);
						SELECT s=full;
						h->setselectmode(s);
						h->setclick(true);
						h->setMult(true);
						h->selectSM(hdc);

						vhan.push_back(count);
						sfit++;
						count++;
						Bminus=true;
						fig[j+fit]=h;
						j++;
						break;
					}
					else
					{
						delete h;
					}
				}
				else
				if(sz==6)
				{
					file.Seek(sizeof(CTextCad),CFile::current);
				}
				else
				if(sz==7)
				{
					file.Seek(sizeof(CImage),CFile::current);
				}

			}
			fit+=j;*/
		}
		file.Close();
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

void CDraw::fsnap(CVector &p, CDC* hdc)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->fsnap(p,hdc)) return;
	}

/*	CFigure *f;
	int j=0;
	for(i=0;i<fit;i++)
	{
		if(fig[i]->inRegion(p))
		{
			j++;
			if(j==1)
			{
				f=fig[i];
			}
			if(j==2)
			{
//				p=fig[i]->intersect(f);
				return;
			}
		}
	}*/

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

void CDraw::setclayer(CString txt,int state)
{
	for(vector<FLAYER>::iterator it=veclayer.begin();it<veclayer.end();it++)
	{
		if(it->name==txt)
		{
			it->on=(state==0)?true:false;
			it->clear=!(it->on);
			it->lock=!(it->on);

			for(int i=0;i<fit;i++)
			{
				if(fig[i]->getLayer().name==txt)
				{
					fig[i]->setLayer(*it);
				}
			}
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
	setcurlayer(*laylist,currlayer.name);

}

void CDraw::setobjinfo(CString aut, CString desc, CString name, double cost)
{
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->transselectedstate())
		{
			FINFO k;
			if(aut!="") k.author=aut;
			if(desc!="") k.description=desc;
			if(name!="") k.name=name;
			if(cost!=0) k.cost=cost;
			fig[i]->setinfo(k);
		}
	}

}

void CDraw::addobject(CTreeCtrl &mtree)
{
	CLibS lib;
	for(int i=0;i<fit;i++)
	{
		if((fig[i]->transselectedstate())&&(fig[i]->getName()==lib.getName()));
		{
			HTREEITEM it=mtree.GetSelectedItem();
			int im=-1,imsel=-1;
			mtree.GetItemImage(it,im,imsel);
			if(im!=2)
			{
				mtree.InsertItem(fig[i]->getInfName(),2,2,it);

				CFileFind finder;
				bool bWorking=finder.FindFile(mtree.GetItemText(it)+".deh");
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
							CLibS *ls=new CLibS(file);
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

void CDraw::removeobject(CTreeCtrl &mtree)
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
				bool bWorking=finder.FindFile(mtree.GetItemText(pit)+".deh");
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
							CLibS *ls=new CLibS(file);

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
								
								CLibS *ls=new CLibS(*df);
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
	for(int i=0;i<fit;i++)
	{
		if(fig[i]->transselectedstate())
		{
			f=fig[i]->getInfo();
		}
	}
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
		ftp->cap(vctop,vcbot,hdc);
		fig.resize(fig.size()+1);
		ftp->clear();
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->cap(vctop,vcbot,hdc);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->cap(vctop,vcbot,hdc);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->cap(vctop,vcbot,hdc);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->cap(vctop,vcbot,hdc);
		/*fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));*/fig.resize(fig.size()+1);
		//m=_msize(fig);
		ftp->clear();
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
//		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
					ftp->sethandle(count);
					ftp->setLayer(currlayer);
					ftp->setUndoparam();
					/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->sethandle(count);
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
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
		ftp->sethandle(count);
		ftp->setLayer(currlayer);
		ftp->setUndoparam();
		/*vhan[sfit]=count;*/vhan.push_back(count);
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
void CDraw::setpixel0(int w, int h)
{
 CVector v;
 v.setScreen(w,h);
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
}

void CDraw::drawforbmp(CDC *hdc)
{
	display(hdc,hdc);
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

void CDraw::setVmode()
{
	CTextCad textc;
	int g=vs.size();

	for (int i=0;i<g;i++)
	{
		if (vs[i]->getName()==pBezier->getName())
		{
			((CBezier*)vs[i])->setFFDon();
		}
	}

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
							((CBezier*)vs[i])->cap(top,bot,hdc);
						else
							((CBezier*)vs[i])->cap0(top,bot,hdc);
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
//				((CTextCad*)vs[i])->edittext();
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
		pLine.sethandle(count);
		undoList.push("create");
		pLine.setLayer(currlayer);
		pLine.setcorevecor();
		*ftp=pLine;
		vhan.push_back(count);
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
		pRectangle.sethandle(count);
		undoList.push("create");
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		*ftp=pRectangle;
		vhan.push_back(count);
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
		pRectangle.sethandle(count);
		undoList.push("create");
		pRectangle.setLayer(currlayer);
		pRectangle.setcorevecor();

		*ftp=pRectangle;
		vhan.push_back(count);
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
	vector<CVector>::iterator itb=v.begin(),ite=v.end()-1;
	CLine *ftp= new CLine;
		
	pLine.clear();
	pLine.sethandle(count);
	undoList.push("create");
	pLine.setLayer(currlayer);
	pLine.setcorevecor();

	while(itb!=ite)
	{
		CVector begin(*itb);itb++;
		CVector end(*itb);

		pLine.setPtsBegin(begin);
		pLine.create(end);
		if (pLine.getCharge())
		{
		*ftp=pLine;
		vhan.push_back(count);
		fig.resize(fig.size()+1);
		fig[fit]=ftp;fit++;
		sfit++;
		count++;
		Bminus=true;
		pLine.initL();
		}
		else
		{
		*fig[fit-1]=pLine;
		pLine.setcorevecor();
		undoList.push("create");
		}

	}
}

void CDraw::AddSpline(vector<CVector> &v)
{
	undoList.push("create");
	vhan.push_back(count);
	fig.resize(fig.size()+1);
	fig[fit]=new CBezier(3,v);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}

void CDraw::AddCircle(CVector v, float radius)
{
	undoList.push("create");
	vhan.push_back(count);
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
	undoList.push("create");
	vhan.push_back(count);
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
	undoList.push("create");
	vhan.push_back(count);
	fig.resize(fig.size()+1);
	fig[fit]=new CCercle(p1,p2);
	fig[fit]->setLayer(currlayer);
	fig[fit]->setcorevecor();
	fit++;
	sfit++;
	count++;
	Bminus=true;
}
