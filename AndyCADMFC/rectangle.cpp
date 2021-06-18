// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
{
	name="CRectangle";
	OpClstate=close;
	bcolor=NULL;
	cl=false;
	tprect=rect;
}

CRectangle::~CRectangle()
{

}



bool CRectangle::draw(bool fPrevLine, CDC *hdc, CVector point)
{
				CPen pen;
				pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
				CPen *oldp=hdc->SelectObject(&pen);
				
				CBrush brush;
				brush.CreateSolidBrush(bcolor);
				CBrush *oldb=hdc->SelectObject(&brush);

				int u=hdc->GetROP2();
//				if(u!=R2_NOTXORPEN)
				{
					u=hdc->SetROP2(R2_NOTXORPEN);
				}
 
				CPoint prev=ptsPrevEnd;
				CPoint pb=ptsBegin;
				CPoint pe=ptsEnd;


				if(tprect==rect)
				{
				CVector v1=ptsEnd;
				CVector vrx;vrx.getcoorx();
				CVector vry;vry.getcoory();
				CVector vrz;vrz.getcoorz();
				CVector vro;vro.getcooro();
				
				CVector v2=ptsBegin;
				CVector v3=v1-v2;
				
				vrx=vrx*(v3.dot(vrx));
				vry=vry*(v3.dot(vry));

				CVector v3x=v2+vrx;
				CVector v3y=v2+vry;//(v3.dot(vry));
				CVector e=v3x+vry;//(v3.dot(vry));
				pb=v1;
				pe=e;


                // If a line was drawn during an earlier WM_MOUSEMOVE 
                // message, draw over it. This erases the line by 
                // setting the color of its pixels to white. 
				 
				if(cl) hdc->BeginPath(); 

                if (fPrevLine) 
                { 
					hdc->MoveTo(prev_v2);
                   	hdc->LineTo(prev_v3x);
					hdc->LineTo(prev_e);
                   	hdc->LineTo(prev_v3y);
					hdc->LineTo(prev_v2);
                } 
				if(cl)
				{
					hdc->EndPath();
					hdc->FillPath();
				}
 
                // Convert the current cursor coordinates to a 
                // POINTS structure, and then draw a new line. 
				//	ptsEnd=point;
				if(cl) hdc->BeginPath();

					hdc->MoveTo(v2);
                   	hdc->LineTo(v3x);
					hdc->LineTo(e);
                   	hdc->LineTo(v3y);
					hdc->LineTo(v2);
			
				if(cl) 
				{
					hdc->EndPath();
					hdc->FillPath();
				}
					prev_v2=v2;
                   	prev_v3x=v3x;
					prev_e=e;
                   	prev_v3y=v3y;

				}
				else
				{

                // If a line was drawn during an earlier WM_MOUSEMOVE 
                // message, draw over it. This erases the line by 
                // setting the color of its pixels to white. 
				 
				if(cl) hdc->BeginPath(); 

                if (fPrevLine) 
                { 
					hdc->MoveTo(pb);
					CPoint p1(prev.x,pb.y);	
                   	hdc->LineTo(p1);

					hdc->LineTo(prev);
					CPoint p2(pb.x,prev.y);	

                   	hdc->LineTo(p2);

					hdc->LineTo(pb);
                } 
				if(cl)
				{
					hdc->EndPath();
					hdc->FillPath();
				}
 
                // Convert the current cursor coordinates to a 
                // POINTS structure, and then draw a new line. 
				//	ptsEnd=point;
				if(cl) hdc->BeginPath();

					hdc->MoveTo(pb);

					CPoint p1(pe.x,pb.y);	
                   	hdc->LineTo(p1);
                   	hdc->LineTo(pe);

					CPoint p2(pb.x,pe.y);	
                   	hdc->LineTo(p2);
					hdc->LineTo(pb);
			
				if(cl) 
				{
					hdc->EndPath();
					hdc->FillPath();
				}
                ptsPrevEnd = ptsEnd; 
				}
 
                // Set the previous line flag, save the ending 
                // point of the new line, and then release the DC.
				hdc->SelectObject(oldb);
                hdc->SelectObject(oldp);
				hdc->SetROP2(u);
//				fPrevB = TRUE; 
				return TRUE;
}

void CRectangle::draw(CDC *hdc)
{
/*	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	hdc->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	hdc->SelectObject(&brush);
	
	if(cl) hdc->BeginPath();
	pitere=ptend.begin();
	hdc->MoveTo(ptbegin.front());
	for(piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
	ptsBegin=*piterb;;
	ptsEnd=*pitere;
	hdc->MoveTo(ptsBegin.x, ptsBegin.y); 
	hdc->LineTo(ptsEnd.x, ptsEnd.y); 
	pitere=pitere+1;
	}
	if(cl)
	{
		hdc->EndPath();
		hdc->StrokeAndFillPath();
	}
	setInit();
	selectSM(hdc);*/
	CLine::draw(hdc);
//	bez->draw(hdc);

}


void CRectangle::drawinit(CDC *hdc, CVector begin, CVector end)
{

    hdc->MoveTo(begin); 
	hdc->LineTo(end); 
}

void CRectangle::drawpointdyna(CDC *hdc, CVector pbb, CVector pbe)
{
	CLine::drawpointdyna(hdc,pbb,pbe);

//	 hdc->MoveTo(pbb); 
//	 hdc->LineTo(pbe); 

}

CRectangle CRectangle::mirror(CDC *hdc, CRectangle *rectangle)
{
	return *rectangle;
}

void CRectangle::createvec()
{
	ptbegin.clear();
	ptend.clear();
	CPoint pe=ptsEnd;
	CPoint pb=ptsBegin;
	CPoint p1(pe.x,pb.y);
	CPoint p3(pb.x,pe.y);
	ptbegin.push_back(ptsBegin);
	ptbegin.push_back(p1);
	ptbegin.push_back(ptsEnd);
	ptbegin.push_back(p3);
	ptend.push_back(p1);
	ptend.push_back(ptsEnd);
	ptend.push_back(p3);
	ptend.push_back(ptsBegin);
//	updatecore();
}



void CRectangle::setType(CString option)
{

}

void CRectangle::polystate(CVector pos)
{
	cancharge=false;
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
	}

}

bool CRectangle::getCharge()
{
	
 if (cancharge)
 {

	ptbegin.clear();
	ptend.clear();
	CVector v1=ptevir.back();
	CVector vrx;vrx.getcoorx();
	CVector vry;vry.getcoory();
	CVector vrz;vrz.getcoorz();
	CVector vro;vro.getcooro();
	
	CVector v2=ptbvir.back();
	CVector v3=v1-v2;
	
	vrx=vrx*(v3.dot(vrx));
	vry=vry*(v3.dot(vry));

	CVector v3x=v2+vrx;
	CVector v3y=v2+vry;//(v3.dot(vry));
	CVector e=v3x+vry;//(v3.dot(vry));

	CVector ve1(v1.x,v2.y);
	CVector vb1(v2.x,v1.y);
	
	CPoint p11(ptevir.back());
	CPoint p22(ptbvir.back());
	CVector vp11(p11.x,p11.y);

	
	ptbegin.push_back(v2);
	ptbegin.push_back(v3x);//p1);
	ptbegin.push_back(e);//ptevir.back());
	ptbegin.push_back(v3y);//p3);
	ptend.push_back(v3x);//p1);
	ptend.push_back(e);//ptevir.back());
	ptend.push_back(v3y);//p3);
	ptend.push_back(v2);
//	updatecore();
	box.empty();
	box.add(v2);
	box.add(v3x);
	box.add(e);
	box.add(v3y);

	mesh.empty();
	CVector uv=box.getParam(ptbegin[0]);
	mesh.addVertex(new CVertex(ptbegin[0],0,0));//uv.x,uv.y));
	uv=box.getParam(ptbegin[1]);
	mesh.addVertex(new CVertex(ptbegin[1],0.25,0));//uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

	uv=box.getParam(ptbegin[2]);
	mesh.addVertex(new CVertex(ptbegin[2],0.5,0));//uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
	uv=box.getParam(ptbegin[3]);
	mesh.addVertex(new CVertex(ptbegin[3],0.75,0));//uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
	new CEdge(mesh.Vertex(mesh.Vcount()-1),mesh.Vertex(mesh.Vcount()-4),mesh.Ecount());

	mesh.updateBoxUV(box);

//	bez=new CBezier(this);

  return cancharge;
 }

 else 
 {
	 return false;
 }

}

void CRectangle::setMove(bool mv,CVector pos)
{
	move=mv;
	click=false;
//	if(!cancharge)
	polystate(pos);

}





void CRectangle::savefile(CFile &file)
{
	 file.Write(&tprect, sizeof(tprect));

	 CLine::savefile(file);

}

void CRectangle::openfile(CFile &file)
{
	 file.Read(&tprect, sizeof(TP));
	 CLine::openfile(file);
	 name="CRectangle";
}
LONG CRectangle::Readfile(CFile &file)
{
	 file.Seek(sizeof(TP),CFile::current);
	 return CLine::Readfile(file);
}
CRectangle::CRectangle(CFile &file)
{
	OpClstate=close;
	bcolor=NULL;
	cl=false;
	openfile(file);
	name="CRectangle";
}


/*void CRectangle::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);
	int i=0;
//	updatecore();
/*	CRect pt(p0,p2);
	pt.InflateRect(10,10);
	hdc->LPtoDP(pt);

//	wnd->InvalidateRect(&pt,TRUE);
//	wnd->ValidateRect(&pt);
	wnd->RedrawWindow(&pt,NULL,RDW_INVALIDATE|RDW_NOERASE);
*/

/*	if(getRotstate()) InitRotState();
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);
	if(!getmultcore())
	{
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptsBegin=*piterb;
		ptsEnd=*pitere;

		CVector vpoint(ptsBegin,prevpos);
		CVector v(ptsBegin,ptsEnd);
	
	if ((select==full)||multiselect||getLibstatus())
	{
		if ((ptsBegin.x<prevpos.x)&&(ptsEnd.x>prevpos.x)||
			(ptsBegin.x>prevpos.x)&&(ptsEnd.x<prevpos.x)||
			(ptsBegin.y<prevpos.y)&&(ptsEnd.y>prevpos.y)||
			(ptsBegin.y>prevpos.y)&&(ptsEnd.x<prevpos.y)||
			multiselect||getLibstatus())
		{
			vector<CVector>::iterator  pite,pitb;
			pite=ptend.begin();
			for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb=pitb+1)
			{
					if(transref)
					{
						CVector begi=ptsBegin;
						CVector v1(prevpos,postpos);
						CVector vv0(v0,(*pitb));
						double gre =argu(refline);
						Translate(vv0);
						TRotate(gre);
						endT();
						CVector vr,vo;
						vr.assignPL(v1);
						vo.assignPL(v0);
					
						int c,b;
						c=(vr.y>0)?1:-1;
						b=(vr.x>0)?1:-1;

						(*pitb)=(*pitb)+polarc(absc(vr),0)*b;

						(*pite)=(*pite)+polarc(absc(vr),0)*b;

						pushUnit();
					}
					else
					{
						*pitb+=mouseVect;
						*pite+=mouseVect;
					}
				if ((pite+1)<ptend.end())
				{
					pite=pite+1;
				}

			}
//			drawdel(hdc);
			if((!multiselect)||(!getLibstatus()))
			{
				drawTrans(hdc);
			}
			break;
		}
	}
	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}
	}
	}
	if((linestate==D4)||(getmultcore())||(select==st))
	{
		prevptend=ptend;
		prevptbegin=ptbegin;

		TransformRect(prevpos,postpos);
//		drawdel(hdc);
		if(!getmultcore()) 
		{
			drawTrans(hdc);
		}

	}
	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);
}
*/

void CRectangle::setstyle(int i)
{
	if(i==0)
		tprect=rect;
	else if(i==1)
		tprect=select;

}

void CRectangle::getchargeL()
{
	ptbegin.clear();
	ptend.clear();
	CVector v1=ptsEnd;
	CVector vrx;vrx.getcoorx();
	CVector vry;vry.getcoory();
	CVector vrz;vrz.getcoorz();
	CVector vro;vro.getcooro();
	
	CVector v2=ptbvir.back();
	CVector v3=v1-v2;
	
	vrx=vrx*(v3.dot(vrx));
	vry=vry*(v3.dot(vry));

	CVector v3x=v2+vrx;
	CVector v3y=v2+vry;//(v3.dot(vry));
	CVector e=v3x+vry;//(v3.dot(vry));

	CVector ve1(v1.x,v2.y);
	CVector vb1(v2.x,v1.y);
	
	CPoint p11(ptsEnd);
	CPoint p22(ptsBegin);
	CVector vp11(p11.x,p11.y);

	
	ptbegin.push_back(v2);
	ptbegin.push_back(v3x);//p1);
	ptbegin.push_back(e);//ptevir.back());
	ptbegin.push_back(v3y);//p3);
	ptend.push_back(v3x);//p1);
	ptend.push_back(e);//ptevir.back());
	ptend.push_back(v3y);//p3);
	ptend.push_back(v2);
//	bez=new CBezier(this);
	updatecore();


}

CRectangle::CRectangle(CVector b, CVector e)
{

	ptbvir.push_back(b);
	ptevir.push_back(e);
	cancharge=true;
	getCharge();

}

void CRectangle::drawMesh(CDC *hdc,float r)
{
	CVector v=box.size();
	float count=v.x/r;
	int dcount=count/2;
	CVector v01=(ptbegin[0]+ptbegin[1])/2;
	CVector v02=(ptbegin[2]+ptbegin[3])/2;

	CVector vxunit;
	vxunit.getcoorx();
	vxunit=vxunit*r;
	CVector vyunit;
	vyunit.getcoory();
	vyunit=vyunit*r;

	CVector v001=v01;
	CVector v002=v02;

	for(int i=0;i<dcount;i++)
	{
		hdc->MoveTo(v01);
		hdc->LineTo(v02);
		v01=v01+vxunit;
		v02=v02+vxunit;
	}
	v01=v001;
	v02=v002;
	for(i=0;i<dcount;i++)
	{
		hdc->MoveTo(v01);
		hdc->LineTo(v02);
		v01=v01-vxunit;
		v02=v02-vxunit;
	}
	v01=(ptbegin[0]+ptbegin[3])/2;
	v02=(ptbegin[1]+ptbegin[2])/2;

	v001=v01;
	v002=v02;
	count=v.y/r;
	dcount=count/2;

	for(i=0;i<dcount;i++)
	{
		hdc->MoveTo(v01);
		hdc->LineTo(v02);
		v01=v01+vyunit;
		v02=v02+vyunit;
	}
	v01=v001;
	v02=v002;
	for(i=0;i<dcount;i++)
	{
		hdc->MoveTo(v01);
		hdc->LineTo(v02);
		v01=v01-vyunit;
		v02=v02-vyunit;
	}

}

CFigure* CRectangle::generateCopy()
{
	CRectangle* l=new CRectangle;
	l->copy(this);
	return l;

}
