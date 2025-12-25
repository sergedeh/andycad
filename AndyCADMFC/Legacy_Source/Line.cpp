// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Line.h"
#include <math.h>
#include <stack>
#include <list>
#include <algorithm>
#include <functional>
#include "edge.h"
#include "plane.h"
#include "mesh.h"
#include "Cadview.h"
#include "rectangle.h"
#include "ximage.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{
//	handle=0;
	lstate=L1; move=false;down=false;Up=false;UfromL2=false;
	CVector v0(0,0);
	precEnd=v0;menusel=false;
	name="CLine";
	edge_on = true;
//	deg=2;
	
}
CLine::CLine(CVector b,CVector e)
{
//	handle=0;
	lstate=L1; move=false;down=false;Up=false;UfromL2=false;
	CVector v0(0,0);
	precEnd=v0;menusel=false;
	name="CLine";
	ptbegin.clear();
	ptbegin.push_back(b);
	ptend.clear();
		box.empty();
		box.add(b);
		box.add(e);

		mesh.empty();

		CVector uv=box.getParam(b);
		mesh.addVertex(new CVertex(b,0,0));//uv.x,uv.y));
		uv=box.getParam(e);
		mesh.addVertex(new CVertex(e,1,0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
}

CLine::CLine(vector<CVector> v)
{
	lstate=L1; move=false;down=false;Up=false;UfromL2=false;
	CVector v0(0,0);
	precEnd=v0;menusel=false;
	name="CLine";
	ptbegin.clear();
	ptend.clear();
		box.empty();
		for(vector<CVector>::iterator piterbex=v.begin();piterbex!=v.end();piterbex++)
			box.add(*piterbex);

		mesh.empty();
		int i=0;
		for(piterbex=v.begin();piterbex!=v.end();piterbex++)
		{
		CVector uv=box.getParam(*piterbex);
		mesh.addVertex(new CVertex(*piterbex,i,0));//uv.y));
		if(mesh.Vcount ()>1)
			new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		i++;
		}
}

CLine::~CLine()
{

}
void CLine::setMove(bool mv,CVector pos)
{
	move=mv;
//	if(!cancharge)
	polystate(pos);

}

bool CLine::draw(bool fPrevLine, CDC *hdc,CVector point)
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
//                 if (fPrevB) 
                 { 
 					hdc->MoveTo(ptsBegin); 
                     hdc->LineTo(ptsPrevEnd); 
 					
                 } 
  
                 // Convert the current cursor coordinates to a 
                 // POINTS structure, and then draw a new line. 
 				//ptsBegin=point;
/*				 int np=mesh.Vcount();
				 if(np!=0)
				 {
				 if((np==2)&&(mesh.Vector(0)==mesh.Vector(1)))
					 ptsBegin=mesh.Vector(0);		
				 else
					 ptsBegin=mesh.Vector(np-1);		
				 }*/
//                 ptsEnd =point;
//				 CVector n;n.assignPL(ptsBegin);
				 hdc->MoveTo(ptsBegin); 
                 hdc->LineTo(ptsEnd); 
 
                 // Set the previous line flag, save the ending 
                 // point of the new line, and then release the DC. 
				 hdc->SelectObject(oldp);
				 ptsPrevBegin=ptsBegin; 
                 ptsPrevEnd = ptsEnd; 
//				 move=true;
//				 polystate(point);
//				 fPrevB=true;
                 return TRUE;
 }




void CLine::draw(CDC *hdc)
{
	DWORD tick=GetTickCount();
	CLine* f=new CLine;
	f->copy(this);
	DWORD ptickc=GetTickCount()-tick;
	DWORD tickc=GetTickCount();
	CString sc;
	sc.Format("time spend to Copy a line:%d \n",ptickc);
	TRACE(sc);
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
//	clipshape.push_back(&r);
	   for(int i=0;i<clipshape.size();i++)
	   {
		   f->Clip(clipshape[i]);
	   }
//	clipshape.erase(std::find(clipshape.begin(),clipshape.end(),&r));
	DWORD ptickcc=GetTickCount()-tickc;
	CString scc;
	scc.Format("time spend to Clip a line:%d \n",ptickcc);
	TRACE(scc);

	CPen pen;
	bool b=pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen* oldp=hdc->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);
		if(cl && !move) 
		{
//	hdc->BeginPath();
//			Fill(hdc,fill_p,bcolor);
			if(texture_file!="")
			{
			CImagex texture;//(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
				updatevcore();
				f->vbox=vbox;
			if(mode_texture==wrap)
			{
				f->Hatch(hdc);
			}
//			mode_texture=none;
			f->ScanPolygon(hdc,bcolor,&texture);
//			f->Fill(hdc,box.center(),bcolor);
			}
			else
			{

			f->ScanPolygon(hdc,bcolor,NULL);
//			f->Fill(hdc,box.center(),bcolor);
			}

//		f->mesh.displayEdge(hdc);
//		hdc->EndPath();
//		hdc->CloseFigure();
//		hdc->FillPath();
		}
	if(edge_on && (!(move&&getLibstatus())))
		f->mesh.displayEdge(hdc);
//	CVector vi=mesh.Vector(0);
	if(/*(!multiselect)&&*/(!getLibstatus()))
	{
	selectSM(hdc);
//	if(transselectedstate()) drawselect(hdc);
	}
	if (getRotstate())
	{
	CPoint r(rotateCenter);
	hdc->MoveTo(r.x,r.y-15);
	hdc->LineTo(r.x,r.y+15);
	hdc->MoveTo(r.x-15,r.y);
	hdc->LineTo(r.x+15,r.y);
	}
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
	delete f;

	DWORD ptick=GetTickCount()-tick;
	CString s;
	s.Format("time spend to Draw a line:%d \n",ptick);
	TRACE(s);
//	}
	//rotateSM(hdc,);

//	if(!colchange) setInit();


}

void CLine::drawinit(CDC *hdc,CVector begin, CVector end)
{

	hdc->MoveTo(begin); 
	hdc->LineTo(end);
}

double CLine::pointtoVector(CVector line,CVector point)
{
	//effectue l'operation
	//   point dot this
	//d=---------------- dot point
	//   point dot point
	//

	CVector orpoint=point;
	double proj1=point.dot(line)/line.dot(line);
	point=line*proj1;
	
	hitpoint=point;

	point.operator -=(orpoint);

	double result=absc(point);
	return	result;

}



CFigure * CLine::mirror(CDC *hdc, CFigure *line)
{
	return CFigure::mirror(hdc,line);

	CFigure *result=new CFigure;
	vector<CVector>* presult[2];
 	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptsBegin=*piterb;
		ptsEnd=*pitere;

	
		vector<CVector>::iterator piterbex;
		vector<CVector>::iterator pitereex=line->ptend.begin();
	
		for(piterbex=line->ptbegin.begin();piterbex<line->ptbegin.end();piterbex++)
		{

		CVector ptStart=*piterbex;
		CVector ptEnd=*pitereex;
	

		CVector VMainb(ptsBegin,ptStart);
 		CVector VMaine(ptsEnd,ptEnd);
		
		CVector Vlineb(ptsBegin,ptsEnd);
		CVector Vlinee(ptsBegin,ptsEnd);

		CVector VOlineb=VMainb;
		CVector VOlinee=VMaine;
		
		double proj1=VMainb.dot(Vlineb)/Vlineb.dot(Vlineb);
		VMainb=Vlineb.scalarMult(proj1);

	
		VMainb.operator -=(VOlineb);
	
		VMainb+=VMainb;
		
 		VOlineb+=(VMainb);
		ptStart=ptsBegin;
		ptStart+=VOlineb;

		double proj2=VMaine.dot(Vlinee)/Vlinee.dot(Vlinee);
		VMaine=Vlinee.scalarMult(proj2);

	
		VMaine.operator -=(VOlinee);
		
		VMaine=VMaine+VMaine;
		VOlinee+=(VMaine);
		ptEnd=ptsEnd;
 		ptEnd+=VOlinee;

	
		testb.push_back(ptStart);
 		teste.push_back(ptEnd);
	
		if ((pitereex+1)<line->ptend.end())
		{
		pitereex=pitereex+1;
		}
	}
 		
		
	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}

	}

	result->addvec(testb,teste);
	result->create();
	return result;

}

void CLine::drawpointdyna(CDC *hdc, CVector pbb, CVector pbe)
{
	hdc->MoveTo(pbb); 
	hdc->LineTo(pbe);
}
void CLine::savefiledxf(CStdioFile& file)
{
	int n=mesh.Vcount();
	int e=mesh.Ecount();
	if(n==2)
	{
	file.WriteString("  0");file.WriteString("\n");
	file.WriteString("LINE");file.WriteString("\n");
	file.WriteString("  5");file.WriteString("\n");
	file.WriteString(gethandle().c_str());file.WriteString("\n");
	file.WriteString("330");file.WriteString("\n");
	file.WriteString("78");file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbEntity");file.WriteString("\n");
	file.WriteString(" 67");file.WriteString("\n");
	file.WriteString("     1");file.WriteString("\n");
	file.WriteString("  8");file.WriteString("\n");
	file.WriteString(getLayer().name);file.WriteString("\n");
	file.WriteString("  6");file.WriteString("\n");
	file.WriteString("LT_0");file.WriteString("\n");
	file.WriteString(" 62");file.WriteString("\n");
	file.WriteString("   178");file.WriteString("\n");
	file.WriteString("420");file.WriteString("\n");
	file.WriteString("        0");file.WriteString("\n");
	file.WriteString("440");file.WriteString("\n");
	file.WriteString(" 33554687");file.WriteString("\n");
	file.WriteString(" 48");file.WriteString("\n");
	file.WriteString("0.5");file.WriteString("\n");
	file.WriteString("370");file.WriteString("\n");
	file.WriteString("    15");file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbLine");file.WriteString("\n");
	file.WriteString(" 10");file.WriteString("\n");
	CString ps;
	ps.Format(_T("%f"),ptbegin[0].x);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 20");file.WriteString("\n");
	ps.Format(_T("%f"),ptbegin[0].y);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 30");file.WriteString("\n");
	ps.Format(_T("%f"),ptbegin[0].z);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 11");file.WriteString("\n");
	ps.Format(_T("%f"),ptbegin[1].x);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 21");file.WriteString("\n");
	ps.Format(_T("%f"),ptbegin[1].y);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 31");file.WriteString("\n");
	ps.Format(_T("%f"),ptbegin[1].z);
	file.WriteString(ps);file.WriteString("\n");
	}else
	{
	file.WriteString("  0");file.WriteString("\n");
	file.WriteString("LWPOLYLINE");file.WriteString("\n");
	file.WriteString("  5");file.WriteString("\n");
	file.WriteString(gethandle().c_str());file.WriteString("\n");
	file.WriteString("330");file.WriteString("\n");
	file.WriteString("1F");file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbEntity");file.WriteString("\n");
	file.WriteString("  8");file.WriteString("\n");
	file.WriteString(getLayer().name);file.WriteString("\n");
	file.WriteString("100");file.WriteString("\n");
	file.WriteString("AcDbPolyline");file.WriteString("\n");
	file.WriteString(" 90");file.WriteString("\n");
	CString ps;
	ps.Format(_T("%i"),e+1);
	file.WriteString(ps);file.WriteString("\n");
	file.WriteString(" 70");file.WriteString("\n");
	file.WriteString("   128");file.WriteString("\n");
	file.WriteString(" 43");file.WriteString("\n");
	file.WriteString("0.0");file.WriteString("\n");
	vector<CVector> vf=mesh.getVectors();
	for(piterb=vf.begin();piterb!=vf.end();piterb++)
	{
		file.WriteString(" 10");file.WriteString("\n");
		CString ps;
		ps.Format(_T("%f"),piterb->x);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 20");file.WriteString("\n");
		ps.Format(_T("%f"),piterb->y);
		file.WriteString(ps);file.WriteString("\n");
	}
	if(e==n)
	{
		piterb=vf.begin();
		file.WriteString(" 10");file.WriteString("\n");
		CString ps;
		ps.Format(_T("%f"),piterb->x);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 20");file.WriteString("\n");
		ps.Format(_T("%f"),piterb->y);
		file.WriteString(ps);file.WriteString("\n");
	}
	}

}

void CLine::savefile(CFile &file)
{
	CFigure::savefile(file);

}

void CLine::openfile(CFile &file)
{
	CFigure::openfile(file);
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptbvir.push_back(*piterb);
	}
	for (piterb=ptend.begin();piterb<ptend.end();piterb++)
	{
		ptevir.push_back(*piterb);
	}
	updatecore();
	name="CLine";

}
LONG CLine::Readfile(CFile &file)
{
	return CFigure::Readfile(file);

}

CLine::CLine(CFile &file)
{
	lstate=L1; move=false;down=false;Up=false;;UfromL2=false;
	CVector v0(0,0);
	precEnd=v0;menusel=false;
	name="CLine";
	openfile(file);
}


CVector CLine::CopybyLine(CFigure *object)
{
	CVector ptStart=object->getCenter();
	
		CVector VMainb(ptsBegin,ptStart);
 		
		CVector Vlineb(ptsBegin,ptsEnd);
	
		CVector VOlineb=VMainb;
		
		double proj1=VMainb.dot(Vlineb)/Vlineb.dot(Vlineb);
		VMainb=Vlineb.scalarMult(proj1);
	
		VMainb.operator -=(VOlineb);
	
		//ptStart=VMainb+(CVector)ptsBegin;

	
		VMainb+=VMainb;
		
 		VOlineb+=(VMainb);

		ptStart=ptsBegin;
		ptStart+=VOlineb;

		return ptStart;
}

CPoint CLine::getptsEnd()
{
	return ptsEnd;

}
CVector CLine::getptsBegin()
{
	return ptsBegin;

}

void CLine::setPtsBegin(CVector pos)
{
//	ptsBegin=pos;
//	snapb=false; 
	down=true;
	polystate(pos);

}

void CLine::addtovec()
{
	ptbegin.push_back(ptsBegin);
	ptend.push_back(ptsEnd);

}
/*
void CLine::polystate(CVector pos)
{
	cancharge=false;
//	if ((abs((snapvec.x-pos.x)<=20)&&(abs(snapvec.y-pos.y)<=20)))
//	{
//		pos=snapvec;
//	}

	switch (lstate)
	{
	case(L1):
		{
			ptsBegin=pos;
			if (down)
			{
				ptbvir.push_back(pos);
				lstate=L2;
				Up=false;
				move=false;
				down=false;
			}
			break;
		}
	case(L2):
		{
		ptsEnd=pos;
			if(Up)
			{
			ptevir.push_back(pos);
			lstate=L1;
			cancharge=true;
			}
		Up=false;
		move=false;
		down=false;
		break;
		}
	case(L3):
		ptsBegin=pos;
			if (down)
			{
				if(!pointinRegion(pos,ptsEnd)||menusel)
				{
				cancharge=true;
				ptsBegin=pos;
				}
				else
				{
					ptsBegin=ptsEnd;
				}
				ptbvir.push_back(pos);
				lstate=L2;
				down=false;
				Up=false;
				move=false;
			}
			break;

	case(L4):
		ptsEnd=pos;
		ptbegin.push_back(pos);
		if(Up)
		{
		ptend.push_back(ptsEnd);
		lstate=L3;
		Up=false;
		}
		break;

	}

}
*/
void CLine::polystate(CVector pos)
{
	switch (lstate)
	{
	case(L1):
		{
			ptsBegin=pos;
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
			ptsEnd=pos;
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
		ptsEnd=pos;
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

void CLine::create(CVector pos)
{
	Up=true;
	polystate(pos);

}

bool CLine::getCharge()
{
 if (cancharge)
 {
	 float u,v;
	 if (ptbegin.size()!=0)
	 {
		if(pointinRegion(ptbvir.back(),ptend.back()))
		{
		ptbegin.push_back(ptbvir.back());
		ptend.push_back(ptevir.back());
		box.add(ptbvir.back());
		box.add(ptevir.back());

   //     updatecore();
		CVector uv=box.getParam(ptbvir.back());
//		mesh.addVertex(new CVertex(ptbvir.back(),uv.x,uv.y));
		uv=box.getParam(ptevir.back());
		mesh.addVertex(new CVertex(ptevir.back(),ptbegin.size(),0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		mesh.updateBoxUV(box);
		updatecore();
		return false;
		}
		else
		{
		ptbegin.clear();
		ptend.clear();
		ptbegin.push_back(ptbvir.back());
		ptend.push_back(ptevir.back());
		box.empty();
		box.add(ptbvir.back());
		box.add(ptevir.back());
//        updatecore();
		mesh.empty();
		CVector uv=box.getParam(ptbvir.back());
		mesh.addVertex(new CVertex(ptbvir.back(),ptbvir.size()-1,0));//uv.x,uv.y));
		uv=box.getParam(ptevir.back());
		mesh.addVertex(new CVertex(ptevir.back(),ptbvir.size(),0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		mesh.updateBoxUV(box);
		updatecore();
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
		mesh.updateBoxUV(box);
		updatecore();

	 }
  return cancharge;
 }

 else 
 {
	 return false;
 }

}

void CLine::initL()
{

// ptbegin.clear();
// ptend.clear();
//	snapb=false; 
	mesh.empty();
	ptbvir.clear ();
	ptevir.clear ();
 ptsEnd=v0;
// ptsEnd.y=0;
 ptsBegin=v0;
// ptsBegin.y=0;

}

void CLine::setMenuSelect(bool menu)
{
	menusel=menu;
	lstate=L3;
	CVector vtest(0,0);
	polystate(vtest);
}

/*void CLine::sethandle(int hn)
{
	handle=hn;

}

int CLine::gethandle()
{
	return handle;

}

*/

void CLine::surface(CDC *hdc)
{

}


//Flood Fill Algorithm
void CLine::Fill (CDC*hdc,CPoint p , COLORREF newVal)
{
CPoint h=p;
hdc->LPtoDP(&p);
int l=hdc->SetMapMode(MM_TEXT);
hdc->DPtoLP(&p);
CDC *rh=getDC();
CRect r;
hdc->PtVisible(p);
//hdc->getClipRect();
if (rh==NULL) return;
//hdc->LPtoDP(&p);
COLORREF oldVal=hdc->GetPixel(p);
if(oldVal==CLR_INVALID)
{
	return;
}
stack <CPoint> pstack;
pstack.push(p);
while (pstack.size()!=0)
{
p =pstack.top();
pstack.pop();
bool open_up = FALSE;
bool open_down = FALSE;
	while ((hdc->GetPixel(p) == oldVal)&&(p.x>0))
	{
		p.x--;
	}

		/* move to most left pixel */
	    p.x++;
		while (hdc->GetPixel(p) == oldVal)
		{
			hdc->SetPixel(p,newVal);
			if (open_up == FALSE)
			{
				if (hdc->GetPixel(p.x, p.y+1) == oldVal)
				{
					pstack.push (CPoint(p.x,p.y+1));
					open_up = TRUE;
				}
			}
			else 
			if (hdc->GetPixel(p.x, p.y+1)!=oldVal)
			{
			open_up = FALSE;
			}
			if (open_down == FALSE)
			{
				if (hdc->GetPixel(p.x, p.y-1) == oldVal)
				{
					pstack.push(CPoint(p.x,p.y-1));
					open_down = TRUE;
				}
			}
			else if (hdc->GetPixel(p.x, p.y-1)!=oldVal)
			{
				open_down = FALSE;
			}
			p.x++;
	}
}
hdc->SetMapMode(l);
}

/*and determine insideness with odd parity rule
.Takes advantage of scanline coherence
*/


void updatex(vector<Edges>::iterator e, int y,double width,int xleft)
{
	CRay v1(CVector(0,y,0),CVector(1,y,0));
	CVector ee=CVector(e->e.p.x,e->e.p.y,0);
	CVector eb=CVector(e->b.p.x,e->b.p.y,0);
	CRay v2(eb,ee,true);
	
	CVector inter=v2.Intersect(v1);
	if(inter.x!=1E-10)
	{
		e->x_current=inter.x;
		if(e->it!=0)
		{
		e->u_current+=e->du;//(inter.x==ee.x)?e->e.u:e->b.u;//(double)(inter.x-xleft)/width;
		e->v_current+=e->dv;//(inter.x==ee.x)?e->e.v:e->b.v;//(double)(inter.x-xleft)/width;
		if(e->v_current<0)
			e->v_current=1;
		if(e->v_current>1)
			e->v_current=0;
		}
		e->it++;
	}

}
void updatexw(vector<Edges>::iterator e, int y,double width,int xleft)
{
	double ay=tan(width);
	CRay v1(CVector(0,y,0),CVector(1,y,0));
	CVector ee=CVector(e->e.p.x,e->e.p.y,0);
	CVector eb=CVector(e->b.p.x,e->b.p.y,0);
	CRay v2(eb,ee,true);
	
	CVector inter=v2.Intersect(v1);
	if(inter.x!=1E-10)
	{
		e->x_current=inter.x;
		if(e->it!=0)
		{
		e->u_current+=e->du;//(inter.x==ee.x)?e->e.u:e->b.u;//(double)(inter.x-xleft)/width;
		e->v_current+=e->dv;//(inter.x==ee.x)?e->e.v:e->b.v;//(double)(inter.x-xleft)/width;
		if(e->v_current<0)
			e->v_current=1;
		if(e->v_current>1)
			e->v_current=0;
		if(e->u_current<0)
			e->u_current=1;
		if(e->u_current>1)
			e->u_current=0;

		}
		e->it++;
	}

}
bool isVybig(CPoint v1, CPoint v2)
{
	return v1.y>v2.y;
}

bool isPbig(Edges e1,Edges e2)
{
	return e1.r.top>e2.r.top;	
}
bool isysmall(Edges e1,Edges e2)
{
	return e1.r.bottom<e2.r.bottom;
}
bool isytop(CVector e1,CVector e2)
{
	return e1.y>e2.y;
}
bool isxleft(CVector e1,CVector e2)
{
	return e1.x<e2.x;
}
bool isxleft(CPoint e1,CPoint e2)
{
	return e1.x<e2.x;
}
bool isybottom(CVector e1,CVector e2)
{
	return e1.y<e2.y;
}
bool isxright(CVector e1,CVector e2)
{
	return e1.x>e2.x;
}
bool sortx(Edges e1,Edges e2)
{
	return (e1.x_current<e2.x_current);
}
/*
void CLine::ScanPolygon(CDC *hdc, COLORREF rgba,CImagex *texture)
{
	
	BYTE* text=(BYTE*)texture->GetDIBits();
    int pheight=texture->GetHeight();
	int pwidth=texture->GetWidth();
	col* mytext=new col[pheight*pwidth];
	auto_ptr <col> m(mytext);
	int i = 0;
		int x, y,q;
	int r,g,b;

	int width;
	int height;

	vector <Edges> v;
	vector<Edges> vl;
	double u,vv;
	CVector ev=ptend.back();
	viterator vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isytop));
	double ytop=(vi->y>ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxleft));
	double xleft=(vi->x<ev.x)?vi->x:ev.x;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isybottom));
	double ybot=(vi->y<ev.y)?vi->y:ev.y;
	vi=min_element(ptbegin.begin(),ptbegin.end(),pointer_to_binary_function<CVector,CVector,bool>(isxright));
	double xright=(vi->x>ev.x)?vi->x:ev.x;

	CPoint tl(CVector(xleft,ytop,0));
	CPoint lb(CVector(xright,ybot,0));
	hdc->LPtoDP(&tl);
	hdc->LPtoDP(&lb);
	xleft=tl.x;
	ytop=tl.y;
	width=lb.x-tl.x;
	height=tl.y-lb.y;

	CPoint blend(blend_p);
	hdc->LPtoDP(&blend);
	blend.x=xleft;
	blend.y=ytop;
	CPoint nblend(blend_plane);
	hdc->LPtoDP(&nblend);
	nblend.x=width;
	nblend.y=0;
	blend_radius=width;
	CPlane pl(CVector(blend.x,blend.y,0),CVector(nblend.x,nblend.y,0));
	float initalpha=0;
	float endalpha=1;
//	blend_mode=linearb;
//	tex_vert_mode=decal;


	for(vector<CVector>::iterator it=ptbegin.begin(),ite=ptend.begin();it!=ptbegin.end();it++,ite++)
	{
		CPoint p1(*it);
		hdc->LPtoDP(&p1);
		u=(double)(p1.x-xleft)/width;
		vv=(double)(ytop-p1.y)/height;
		vertex v1(p1,u,vv);

		CPoint p2(*ite);
		hdc->LPtoDP(&p2);
		u=(double)(p2.x-xleft)/width;
		vv=(double)(ytop-p2.y)/height;
		vertex v2(p2,u,vv);

		CRect r(p1,p2);
		r.NormalizeRect();
		if(r.top!=r.bottom)
			v.push_back(Edges(v1,v2,r));
	}
   if(v.size()!=0)
   {

	for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
		{
			for(x = 0; x < pwidth; x++)
			{
				q = x + y * pwidth;
				mytext[q].b=text[i++];
				mytext[q].g=text[i++];
				mytext[q].r=text[i++];
			}
			i+=pwidth%4;
		}

	sort(v.begin(),v.end(),pointer_to_binary_function<Edges, Edges,bool>(isPbig));//sort edges by maxy
	
	if(v.begin()==NULL)
	{
		int hello=5;
	}
	ytop=v.begin()->r.top;
	double vt=0;

	eiterator gi=min_element(v.begin(),v.end(),pointer_to_binary_function<Edges,Edges,bool>(isysmall));
	int ybottom=gi->r.bottom;
	int vb=1;
	int prevyt=0;

	double dv=(double)1/(ybottom-ytop);
	
	int o=hdc->SetMapMode(MM_TEXT);
	int br=	GetRValue(rgba);
	int bg=	GetGValue(rgba);
	int bb=	GetBValue(rgba);

	for (y=ytop;y<=ybottom;y++) {

	for(vector<Edges>::iterator i=v.begin();i!=v.end();i++)
	{
		if(y==i->r.top)
			vl.push_back(*i);
		else
			if(y>=i->r.bottom)
			{
				eiterator il=find(vl.begin(),vl.end(),*i);
				if(il!=vl.end()) vl.erase(il);
			}
	}
				//update x coordinate of every active edge
	
//	insert/remove edges from “active edge list”
	for(vector<Edges>::iterator ip=vl.begin();ip!=vl.end();ip++)
		updatex(ip,y,width,xleft);//update x coordinate of every active edge
	sort(vl.begin(),vl.end(),pointer_to_binary_function<Edges,Edges,bool> (sortx));//sort active edges by x coordinate
	
	for(eiterator ik=vl.begin();ik<vl.end()-1;ik+=2)
	{
	int xleft=ik->x_current;
	double uleft=ik->u_current;
	int xright=(ik+1)->x_current;
	double uright=(ik+1)->u_current;
	double du=(uright-uleft)/(xright-xleft);
//	double alpha=1;
	for (int x=xleft;x<=xright;x++)
	{
		int yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
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
		 r=(1-alpha)*mytext[yt].r+alpha*br;
		 g=(1-alpha)*mytext[yt].g+alpha*bg;
		 b=(1-alpha)*mytext[yt].b+alpha*bb;
		}else
		if(tex_vert_mode==multiply)
		{
		 r=(mytext[yt].r/255*br/255)*255;
		 g=(mytext[yt].g/255*bg/255)*255;
		 b=(mytext[yt].b/255*bb/255)*255;
		}
		else
		if(tex_vert_mode==multiply)
		{
		yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		COLORREF back=hdc->GetPixel(x,y);
		
		br=	GetRValue(back);
		bg=	GetGValue(back);
		bb=	GetBValue(back);
		
		r=(1-alpha)*br+alpha*mytext[yt].r;
		g=(1-alpha)*bg+alpha*mytext[yt].g;
		b=(1-alpha)*bb+alpha*mytext[yt].b;

		}
		else
		{
//		yt=floor(pheight*vt)*(pwidth)+floor(pwidth*uleft);
		COLORREF back=hdc->GetPixel(x,y);
		
		int br1=	GetRValue(back);
		int bg1=	GetGValue(back);
		int bb1=	GetBValue(back);
		
		r=(1-alpha)*br1+alpha*br;
		g=(1-alpha)*bg1+alpha*bg;
		b=(1-alpha)*bb1+alpha*bb;
		}
		hdc->SetPixel(x,y,RGB(r,g,b));

//		hdc->SetPixel(x,y,RGB(mytext[yt].r,mytext[yt].g,mytext[yt].b));
		uleft+=du;
	}
	}
	vt+=dv;
	}
	hdc->SetMapMode(o);
	}
}
*/
void CLine::breakcurve(CVector v1,CVector v2)
{
	mesh.breakEdge(v1,v2);
//	return bo;
}
vector<CFigure*> CLine::breakcurve2(CVector v1,CVector v2)
{
	CLine *b=new CLine();
	b->copy(this);
	CLine *c=new CLine();
	c->copy(this);
	float u1=mesh.getU(v1);
	float u2=mesh.getU(v2);

	if(u1<u2)
	{
		c->mesh.breakEdge(v1);
		b->mesh.breakEdge2(v2);
	}else
	{
		c->mesh.breakEdge(v2);
		b->mesh.breakEdge2(v1);
	}
	vector<CFigure*> bo;
	bo.push_back(b);
	bo.push_back(c);
	return bo;
}

float CLine::computealpha(int x, int y,CPlane *pl,float init,float end)
{
	float alpha;
	if(blend_mode==linearb)
	{
		alpha=pl->dist_to_point(CVector(x,y,0));

	
	}else
	{
//		CVector n(x,y,0);CVector o();
//		alpha=n.absc(n-o);
	}

	if(alpha<0)
	{
		if(blend_mode==linearb) return 1;
			else if(blend_mode==circularb)
			{
				alpha=-alpha;
			}
	}
	else
	{
		return __min(init+alpha/blend_radius,end);
	}
}

void CLine::SendNotify(CString s, void *param[7])
{
	CFigure::SendNotify(s,param);
	if(s=="Transparency")
	{
		float *a=(float*)param[0];
		alpha=__max(*a,0);
		alpha=__min(alpha,1);
	}

}


void CLine::RegisterInterest(CObserver *obs)
{
	CFigure::RegisterInterest(obs);
	for(vector<CObserver*>::iterator i=observers.begin();i!=observers.end();i++)
	{
		void*param[2];
		param[0]=&ptbegin;
		param[1]=&ptend;
		(*i)->SendNotify("vertices",param);
	}

}

CFigure* CLine::generateCopy()
{
	CLine* l=new CLine;
	l->copy(this);
	return l;
}

void CLine::setMesh()
{
	mesh.empty();
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		box.add(*piterb);
	}
	box.add(ptend.back());
	int i=0;
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		CVector uv=box.getParam(*piterb);
		mesh.addVertex(new CVertex(*piterb,i,0));//uv.x,uv.y));
		if (mesh.Vcount()>1)
		{
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		}
		i++;
	}
		CVector uv=box.getParam(ptend.back());
		mesh.addVertex(new CVertex(ptend.back(),i,0));//uv.x,uv.y));
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

}

void CLine::addextranode(CVector point)
{
	ptbegin=mesh.getVectors();
    ptbegin.push_back(point);
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		box.add(*piterb);
	}
	float uvx=0;
	int xsize=ptbegin.size();
	int i=0;
	mesh.empty();
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		//CVector uv=box.getParam(*piterb);
		uvx=(float)(i+1)/xsize;
		mesh.addVertex(new CVertex(*piterb,uvx,0));//uv.x,uv.y));
		if (mesh.Vcount()>1)
		{
		new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
		}
		i++;
	}

}
