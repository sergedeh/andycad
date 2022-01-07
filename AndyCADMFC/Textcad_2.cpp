// TextCad.cpp: implementation of the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "AndyCADMFC.h"
#include "TextCad.h"
#include "render.h"
#include "cadview.h"
#include "rtftype.h"
#include "rtfdecl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CWnd* CTextCad::view=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextCad::CTextCad()
{
	name="CTextCad";
	rec.setdistprec(5);
	bm=NULL;
	in=false;
		CMesh* m=new CMesh;
		view=m->view;
		rich=new CRichEditCtrl;
		CRect r0(0,0,0,0);
		rich->Create(ES_LEFT|ES_MULTILINE|ES_WANTRETURN|WS_CHILD,r0,m->view,ID_RICHT);
		rich->SetRect(&r0);
		delete m;

}
CTextCad::CTextCad(CFile &file)
{
	name="CTextCad";
	rec.setdistprec(5);


	fPrevB=false;

	openfile(file);
}

CTextCad::~CTextCad()
{
	delete rich;
}



CRectangle* CTextCad::getRectangle()
{
	return &rec;

}

bool CTextCad::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	return rec.draw(fPrevLine,hdc,point);
}

void CTextCad::setPtsBegin(CVector point)
{
	rec.setPtsBegin(point);

}

bool CTextCad::getCharge()
{
	bool b=rec.getCharge();
	ptbegin=rec.ptbegin;
	ptend=rec.ptend;
	updatecore();
	CPoint p1=ptbegin[0];
	CPoint p2=ptbegin[2];
	CRect rect(p1,p2);
	CRect r0(0,0,10,10);

	CDC* phdc=view->GetDC();
	((CCadView*)view)->OnPrepareDC(phdc);
	phdc->LPtoDP(&rect);
	view->ReleaseDC(phdc);
//	rect.NormalizeRect();
	rich->MoveWindow(rect);
	rich->ShowWindow(SW_SHOW);
//	rich->SetRect(&r0);
	rich->BeginWaitCursor();
	N=1;
	N1=1;
	ncp=1;
	ncp1=1;
	ncp2=0;
	deg=1;
	deg1=1;
	deg2=0;
	ncp2=0;
	N2=0;
	Knot_Univer(ncp,deg,Kn,0,1);
	Kn1=Kn;

	return true;
}

void CTextCad::FillText()
{


}

void CTextCad::setMove(bool b, CVector point)
{
	rec.setMove(b,point);

}

void CTextCad::initL()
{
	rec.initL();
	ptbegin.clear();
	ptend.clear();
	fPrevB=false;
}

void CTextCad::getTextrec(CWnd* wnd,CDC *hdc)
{
}

void CTextCad::create(CVector pos)
{
	rec.create(pos);

}


void CTextCad::draw(CDC *hdc)
{
	if(!rich->IsWindowVisible())
	{
	CBrush b;
	b.CreateSolidBrush(RGB(0,0,0));
	for(itmap i=ltext.begin();i!=ltext.end();i++)
		{

			CFont *oldfont=(CFont*)hdc->SelectObject((*i).second.f);
			hdc->SetBkMode(TRANSPARENT);
			CBrush *bold=hdc->SelectObject(&b);
	//		hdc->SetTextColor(fmap[(*i).first].f].col);


			CPoint v=(*i).second.v;
			hdc->TextOut(v.x,v.y,(*i).second.c);

			b.DeleteObject();
			hdc->SelectObject(bold);
			hdc->SelectObject(oldfont);
			
		}
	 if(in)
		{
//			surf=false;
		
		 }
			edittext0();

		CBezier::surface(hdc);
		}
}

void CTextCad::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{

	CBezier::translate(wnd,hdc,prevpos,postpos);
}

void CTextCad::drawTrans(CDC *hdc)
{
	CFigure::drawTrans(hdc);	

}
DWORD CALLBACK EditStreamCallback(
  DWORD dwCookie, // application-defined value
  LPBYTE pbBuff,  // pointer to a buffer
  LONG cb,        // number of bytes to read or write
  LONG *pcb       // pointer to number of bytes transferred
)
{
	FILE* f=fopen("rtftest.rtf", "w+");
	fwrite(pbBuff,sizeof(char),cb,f);
	fclose(f);
	parsertf(f);

 return (DWORD) true;
}

bool CTextCad::PtinRegion(CVector point)
{
	updatecore();

	if(rich->IsWindowVisible())
	{

	if(!box.containpts(point))
	{
/*				EDITSTREAM es;
				es.pfnCallback=EditStreamCallback;
				rich->StreamOut(SF_RTF,es);*/
				rich->HideCaret();
				CRect r0(box.corner(0),box.corner(3)),r1;
				rich->GetClientRect(&r0);
				rich->InvalidateRect(NULL);
				CDC *hdc=rich->GetDC();
				rich->GetUpdateRect(&r1);
				if(r0!=r1)
					{
					in=true;
//					pw=pwidth;
//					ph=pheight;

					}
					else
						{
						in=false;
						}
				r0=r1;
				
				((CCadView*)view)->OnPrepareDC(hdc);
//				view->GetClientRect(&r1);
			
				r1=r0;
				hdc->DPtoLP(&r0);
				CVector v0=r0.TopLeft();
				CVector v1=r0.BottomRight();
				r0=CRect(v0,v1);
				r0.NormalizeRect();
				r1.NormalizeRect();
				hdc->SetMapMode(MM_TEXT);

				
			
				CDC* phdc=new CDC;
				phdc->CreateCompatibleDC(hdc);
				/*if(bm==NULL) 
					{
					 bm=new CBitmap;
		             bm->CreateCompatibleBitmap(hdc,r1.Width(),r1.Height());
					}
				*/
				if(bm!=NULL) bm->DeleteObject();
				else
					bm=new CBitmap;

				bm->CreateCompatibleBitmap(hdc,r1.Width(),r1.Height());
				
				CBitmap* o=phdc->SelectObject(bm);
				
				phdc->BitBlt(0,0,r1.Width(),r1.Height(),hdc,r1.left,r1.top,SRCCOPY);
				
				BITMAP bl;
				bm->GetBitmap(&bl);
				BYTE* text=new BYTE[(bl.bmWidth)*(bl.bmHeight)*4];
				int d=bl.bmWidth*bl.bmHeight*4;
	/*			for(int k=0;k<bl.bmWidth*bl.bmHeight*4;k++)
					{
						text[k]=-1;
					}*/
				memset(text,0,bl.bmWidth*bl.bmHeight*4);
			
				bm->GetBitmapBits(d,text);
				pheight=bl.bmHeight;
				pwidth=bl.bmWidth;
				CRect ab;

				int i = 0;
				int x, y,q;
				int xmax=0,ymax=0;
				int r,g,b,a;
/*				for(y = 0;y<pheight;y++)//-1;y>-1;y--)//-1; y > -1; y--)
//				for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
				{
						for(x = 0; x < pwidth; x++)
						{
							r=text[i++];
							g=text[i++];
							b=text[i++];
							a=text[i++];
							if((r!=255)&&(g!=255)&&(b!=255))
								{
								xmax=x>xmax?x:xmax;
								ymax=y>ymax?y:ymax;
								}
						}
		//				i+=pwidth%4;
					}
				pw1=pwidth;
				pwidth=xmax+2;
				pheight=ymax+2;*/
				if(mytext!=NULL) delete mytext;
				mytext=new col[pheight*pwidth];
				i=0;
				for(y = 0;y<pheight;y++)//-1;y>-1;y--)//-1; y > -1; y--)
//				for(y = pheight-1;y>-1;y--)//-1; y > -1; y--)
				{
						for(x = 0; x < pwidth; x++)
						{
							q = x + y * pwidth;
							mytext[q].r=text[i++];
							mytext[q].g=text[i++];
							mytext[q].b=text[i++];
							mytext[q].a=text[i++];
						}
					//	i+=pwidth%4;
					}

				delete []text;
				CRect m(-1,-1,pwidth,pheight);
				((CCadView*)view)->OnPrepareDC(hdc);
				hdc->DPtoLP(&m);
				m.OffsetRect(ptbegin[0]);
			//	m.NormalizeRect();

			//	rich->GetWindowRect(&r0);
				if(!surf)
					{
				v1=m.TopLeft();
				CVector v2=m.BottomRight();
				CRectangle Tr(v1,v2);
				Tr.updatecore();
				C[0]=Tr.ptbegin[0];
				C[1]=Tr.ptbegin[1];
				C[2]=Tr.ptbegin[3];
				C[3]=Tr.ptbegin[2];
					}
				phdc->SelectObject(o);
				delete phdc;
				rich->ReleaseDC(hdc);
				rich->ShowWindow(SW_HIDE);
			//	surf=true;
				if(in) return false;
			}
		
		}
	
	return CBezier::PtinRegion(point);

}

CPoint CTextCad::setfont(CDC *hdc,LOGFONT font,COLORREF ccl)
{
	CHARFORMAT chara;
	CHARRANGE charr;

	rich->GetSel(charr);
	if(charr.cpMax!=charr.cpMin)
		{
		rich->GetSelectionCharFormat(chara);
		//chara.
		chara.bCharSet=font.lfCharSet;
		chara.crTextColor=ccl;
		chara.bPitchAndFamily=font.lfPitchAndFamily;
//		chara.szFaceName=font.lfFaceName;
		chara.yOffset=font.lfEscapement;


		}
	else
		rich->GetDefaultCharFormat(chara);


	CPoint pp;
	return pp;
}



void CTextCad::savefile(CFile &file)
{
 
//	file.Write(&rec,sizeof(rec));
/*	int i=stk.size();
	file.Write(&i,sizeof(int));

	for(vector<CString*>::iterator js=stk.begin();js<stk.end();js++)
	{
	i=(*js)->GetLength();
	file.Write(&i,sizeof(int));

		for(int j=0;j<i;j++)
		{
		char c=(*js)->GetAt(j);
		file.Write(&c,sizeof(c));
		}
	}
	
	file.Write(&textmet, sizeof(textmet));
	file.Write(&width,sizeof(width));
	file.Write(&pfont,sizeof(pfont));
*/
 CFigure::savefile(file);
}
void CTextCad::openfile(CFile &file)
{
/*
	int i;
	file.Read(&i,sizeof(int));

	stk.clear();//resize(i);
	
	for(int js=0;js<i;js++)
	{
	int h;
	file.Read(&h,sizeof(int));
	CString *g=new CString;
	stk.push_back(g);
		for(int j=0;j<h;j++)
		{
		char c;
		file.Read(&c,sizeof(c));
		(stk.front())->Insert(j,c);
		}
	}
	is=stk.begin();

	 file.Read(&textmet, sizeof(textmet));
	 file.Read(&width,sizeof(width));
	 file.Read(&pfont,sizeof(pfont));
 
 CFigure::openfile(file);
	
		vecpos.clear();
		vector<CVector>::iterator pib=vecpos.begin(),pitb;
		
		for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb=pitb+1)
		{
			vecpos.push_back(*pitb);
//			pib++;
		}
	iter=vecpos.begin();
*/
}



void CTextCad::assign(CDC *hdc,CVector p,CString s)
{
	
	CFont ft;
}

bool CTextCad::inRegion(CVector point)
{
	updatecore();


	if(box.containpts(point))
	{
		return true;
	}

	return false;
}

void CTextCad::edittext()
{

	updatecore();
	CPoint p1=ptbegin[0];
	CPoint p2=ptbegin[3];
	CRect rect(box.corner(0),box.corner(3));//p1,p2);
	CRect r0(0,0,10,10);
	CRect r1;
	rich->GetClientRect(&r1);

	CDC* phdc=view->GetDC();
	((CCadView*)view)->OnPrepareDC(phdc);
	phdc->LPtoDP(&rect);

//	rect.NormalizeRect();
	r1.OffsetRect(rect.TopLeft());
	rich->MoveWindow(r1);
	rich->ShowWindow(SW_SHOW);
	rich->InvalidateRect(NULL,false);
	rich->GetUpdateRect(&r1);
	rich->SetRect(r1);
//	rich->BringWindowToTop();
	phdc->DPtoLP(&r1);
	phdc->DPtoLP(&rect);
//	rect.InflateRect(CSize(r1.Size()));
//	rect.OffsetRect(ptbegin[0]);
//	r1.NormalizeRect();
	
	CRectangle r(rect.TopLeft(),rect.BottomRight());
	ptbegin=r.ptbegin;
	ptend=r.ptend;

//	surf=false;
	updatecore();
	box.inflate(10);
	box.draw(phdc);


	view->ReleaseDC(phdc);
	
//	rich->SetRect(&r0);
	rich->BeginWaitCursor();

}
CPoint CTextCad::drawtext(CDC *hdc, UINT nchar)
{
/*	CRect ro(box.corner(0),box.corner(3));
	CFont ft;
	ft.CreateFontIndirect(&pfont);
	mytext1 t;

	itmap i1,i2;

	mytext1 mf,mfo;
	mf.c=nchar;
	mf.f=&pfont;
	itmap prev=ltext.find(iter-1);
	int kj=prev->first;

	CPoint v;
		if(prev!=ltext.end())
		{
			v=ltext[(*prev).first].v;
			 v.x+=fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfA+fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfB+fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfC;
			if(v.x>ro.right)
				{
				v.x=ro.left;
				v.y-=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
				}
		}
		else
		{
			TEXTMETRIC tm;
			hdc->GetTextMetrics(&tm);
			myfont m;
			m.tm=tm;
			m.col=lcolor;
			ABCFLOAT* abc=new ABCFLOAT[tm.tmLastChar-tm.tmFirstChar+1];
			GetCharABCWidthsFloat(hdc->GetSafeHdc(),tm.tmFirstChar,tm.tmLastChar,abc);
			for(int i=tm.tmFirstChar;i<=tm.tmLastChar;i++)
			{
			m.abc[i].abcfA=abc[i-tm.tmFirstChar].abcfA;
			m.abc[i].abcfB=abc[i-tm.tmFirstChar].abcfB;
			m.abc[i].abcfC=abc[i-tm.tmFirstChar].abcfC;
			}
			fmap.insert(make_pair(&pfont,m));

			v=ro.TopLeft();
			ifmap it=fmap.find(&pfont);
			v.y-=it->second.tm.tmAscent+it->second.tm.tmExternalLeading+it->second.tm.tmInternalLeading;
		}
	mf.v=v;
	itmap st=ltext.upper_bound(iter);
	if(st==ltext.end())
		ltext[iter]=mf;
	else
		{
		int m=ltext.size();
		int i=m;
		while(i>iter)
			{
				ltext[i]=ltext[i-1];
				i--;
			}
		ltext[iter]=mf;

		updatepos(iter);
		}
	iter++;
*/
	CPoint pp;
//	pp=updatecurs(iter-1);
	hdc->LPtoDP(&pp);

	return pp;
}

void CTextCad::edittext0()
{
/*return;
	if((!rich->IsWindowVisible())&&(surf))
	{
				updatecore();
				CRect r1;
				CPoint p1=ptbegin[0];
				CPoint p2=ptbegin[3];
				CRect rect(box.corner(0),box.corner(3));//p1,p2);
				rich->GetClientRect(&r1);

				CDC* phdc1=view->GetDC();
				((CCadView*)view)->OnPrepareDC(phdc1);
				phdc1->LPtoDP(&rect);
				rect.OffsetRect(1,1);

			//	rect.NormalizeRect();
				r1.OffsetRect(rect.TopLeft());
				rich->MoveWindow(r1);
				view->ReleaseDC(phdc1);

//				rich->ShowWindow(SW_SHOW);
				rich->InvalidateRect(NULL,false);
				CDC *hdc=rich->GetDC();
				rich->GetUpdateRect(&r1);
				rich->UpdateWindow();
				
				r1.NormalizeRect();
//				r1.InflateRect(1,1,1,1);
				
			
				CDC* phdc=new CDC;
				phdc->CreateCompatibleDC(hdc);
				
				if(bm!=NULL) bm->DeleteObject();
				else
					bm=new CBitmap;
		        bm->CreateCompatibleBitmap(hdc,r1.Width(),r1.Height());


				CBitmap* o=phdc->SelectObject(bm);
				
				phdc->BitBlt(0,0,r1.Width(),r1.Height(),hdc,r1.left,r1.top,SRCCOPY);

				BITMAP bl;
				bm->GetBitmap(&bl);
				BYTE* text=new BYTE[(bl.bmWidth)*(bl.bmHeight)*4];
				memset(text,0,bl.bmWidth*bl.bmHeight*4);
			
				bm->GetBitmapBits(bl.bmWidth*bl.bmHeight*4,text);
				pheight=bl.bmHeight;
				pwidth=bl.bmWidth;
				CRect ab;

				int i = 0;
				int x, y,q;
				int xmax=0,ymax=0;
				int r,g,b,a;

				if(mytext!=NULL) delete mytext;
				mytext=new col[pheight*pwidth];
				i=0;
				for(y = 0;y<pheight;y++)//-1;y>-1;y--)//-1; y > -1; y--)
				{
						for(x = 0; x < pwidth; x++)
						{
							q = x + y * pwidth;
							mytext[q].r=text[i++];
							mytext[q].g=text[i++];
							mytext[q].b=text[i++];
							mytext[q].a=text[i++];
						}
						//i+=pwidth%4;
					}

				delete []text;

				phdc->SelectObject(o);
				delete phdc;
				rich->ReleaseDC(hdc);
				rich->ShowWindow(SW_HIDE);
	}*/

}

void CTextCad::setText(CString txt, CDC* hdc)
{

}
