// QLine.cpp: implementation of the CQLine class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "QLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQLine::CQLine()
{
	cancharge=true;
	setReflineP(v0,v0);
}

CQLine::~CQLine()
{

}

void CQLine::polystate(CVector pos)
{
/*	if(snapb)
	{
		pos=snapvec;
		snapb=false;
	}*/
	switch (lstate)
	{
	case(L1):
		{
			ptsBegin=pos;
//			ptsEnd=ptsBegin;
	
//			CRay r(vro,vrx);//=getRefRay();
//			setRefRay(vro,vrx);
			if (down)
			{

				ptbvir.push_back(ptsBegin);
				lstate=L2;
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	case(L2):
		{
			CVector vrx,vrx1;vrx.getcoorx();	
			CVector vry,vry1;vry.getcoory();
			CRay r=getRefRay();
			CVector k=r.getclosestPoint(pos);
			CVector kp=k;
			if((style=="qpline")||(style=="qtline"))
			{
				vrx=r;
				vrx=vrx/absc(vrx);
				vry=pos-k;
				vry=vry/absc(vry);
			}
			if(style=="qtline")
			{
				pos=r.getPhead();
			}

			CVector k1=pos-k;
			CVector vp=pos-ptsBegin;
			CVector vk;
			vk=pos-ptsBegin;

			CVector vpos(pos);
			vpos.v2D();
			CVector vpb(ptsBegin);vpb.v2D();
			CVector vkp=vpos-vpb;




			if(abs(vkp.x)>abs(vkp.y))
			{
				float f=abs(vk.dot(vrx));
				if(f!=0)
				ptsEnd=ptsBegin+vrx*absc(vp)*vk.dot(vrx)/f;
			}
			else
			{
				float f=abs(vk.dot(vry));
				if(f!=0)
				ptsEnd=ptsBegin+vry*absc(vp)*vk.dot(vry)/abs(vk.dot(vry));
			}

			if(Up)
			{
			ptevir.push_back(ptsEnd);
			lstate=L3;
			//setRefRay(ptsBegin,ptsEnd);
			//ptsBegin=ptsEnd;
			prevpos=pos;
			cancharge=true;
			}
		Up=false;
		move=false;
		down=false;
		break;
		}
	case(L3):
		{
			if(down)
			{
				CVector vpos(pos);
				vpos.v2D();
				CVector vprev(prevpos);
				vprev.v2D();

				if(!(absc(vpos-vprev)<=10))
				{
					ptsBegin=pos;
				}
				else
				{
					ptsBegin=ptsEnd;
				}
			//	ptsBegin=ptsEnd;

				ptbvir.push_back(ptsBegin);
				lstate=L2;
				Up=false;
				move=false;
				down=false;
			}
			break;
		}

	case(L4):
		{
		ptsEnd.y=pos.y;
		ptsEnd.x=ptsBegin.x;
			if(Up)
			{
			ptevir.push_back(ptsEnd);
			lstate=L1;
			cancharge=true;
			}
		Up=false;
		move=false;
		down=false;
		break;
		}

	}

}


bool CQLine::getCharge()
{
	
 if (cancharge)
 {
	 if (ptbegin.size()!=0)
	 {
		if(pointinRegion(ptbvir.back(),ptend.back()))
		{
			
		ptbegin.push_back(ptbvir.back());
		ptend.push_back(ptevir.back());
/*		box.add(ptbvir.back());
		box.add(ptevir.back());

		CVector uv=box.getParam(ptbvir.back());
		uv=box.getParam(ptevir.back());
		mesh.addVertex(new CVertex(ptevir.back(),ptbegin.size(),0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());*/
		float uvx=0;
		int xsize=ptbegin.size();
		int i=0;
		mesh.empty();
		for (piterb=ptbegin.begin();piterb!=ptbegin.end();piterb++)
		{
			//CVector uv=box.getParam(*piterb);
			uvx=(float)i/xsize;
			mesh.addVertex(new CVertex(*piterb,uvx,0));//uv.x,uv.y));
			if (mesh.Vcount()>1)
			{
			new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
			}
			i++;
		}
		
		mesh.addVertex(new CVertex(ptevir.back(),1,0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

		cancharge=false;
		return false;
		}
		else
		{
		ptbegin.clear();
		ptend.clear();
		ptbegin.push_back(ptbvir.back());
		ptend.push_back(ptevir.back());
		box.empty();
//        updatecore();
		box.add(ptbvir.back());
		box.add(ptevir.back());

		mesh.empty();
		CVector uv=box.getParam(ptbvir.back());
		mesh.addVertex(new CVertex(ptbvir.back(),0,0));//uv.x,uv.y));
		uv=box.getParam(ptevir.back());
		mesh.addVertex(new CVertex(ptevir.back(),1,0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

		}
	 }
	 else
	 {
		ptbegin.clear();
		ptend.clear();
		ptbegin.push_back(ptbvir.back());
		ptend.push_back(ptevir.back());
//        updatecore();
		box.empty();
		box.add(ptbvir.back());
		box.add(ptevir.back());

		mesh.empty();
		CVector uv=box.getParam(ptbvir.back());
		mesh.addVertex(new CVertex(ptbvir.back(),0,0));//uv.x,uv.y));
		uv=box.getParam(ptevir.back());
		mesh.addVertex(new CVertex(ptevir.back(),1,0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

	 }
  return cancharge;
 }

 else 
 {
	 return false;
 }

}

 
void CQLine::setMove(bool mv,CVector pos)
{
	move=mv;
//	if(!cancharge)
	polystate(pos);

}


bool CQLine::draw(bool fPrevLine, CDC *hdc,CVector point)
 {
  
                 // If a line was drawn during an earlier WM_MOUSEMOVE 
                 // message, draw over it. This erases the line by 
                 // setting the color of its pixels to white. 
  
				// The following function ensures that pixels of 
                 // the previously drawn line are set to white and 
                 // those of the new line are set to black. 
				CPen pen;
				pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
				CPen *oldp=hdc->SelectObject(&pen);
  
                 hdc->SetROP2(R2_NOTXORPEN); 
	
                 if (fPrevLine) 
                 { 
 					hdc->MoveTo(ptsBegin); 
                     hdc->LineTo(ptsPrevEnd); 
 					
                 } 
  
                 // Convert the current cursor coordinates to a 
                 // POINTS structure, and then draw a new line. 
 				//ptsBegin=point;
						
  				 hdc->MoveTo(ptsBegin); 
                 hdc->LineTo(ptsEnd); 
 
                 // Set the previous line flag, save the ending 
                 // point of the new line, and then release the DC. 
  
				 ptsPrevBegin=ptsBegin; 
                 ptsPrevEnd = ptsEnd; 
			 	hdc->SelectObject(oldp);
				//fPrevLine=true;

//				 move=true;
//				 polystate(point);
                 return TRUE;
 }

void CQLine::draw(CDC *hdc)
 {
	CLine::draw(hdc);
  
 }






void CQLine::savefile(CFile &file)
{
	CLine::savefile(file);
}


void CQLine::openfile(CFile &file)
{
	CLine::openfile(file);
	name="CQLine";
}
LONG CQLine::Readfile(CFile &file)
{
	return CLine::Readfile(file);
}
CQLine::CQLine(CFile &file)
{
	 cancharge=true;
     setReflineP(v0,v0);
	 openfile(file);
}

void CQLine::setstyle(CString s)
{
	style=s;
}
