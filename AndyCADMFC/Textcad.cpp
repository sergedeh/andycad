// TextCad.cpp: implementation of the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "AndyCADMFC.h"
#include "TextCad.h"
#include "bezier.h"
#include "textdi.h"
#include "cam.h"
#include "libs.h"
#include "Cadview.h"
#include "Caddoc.h"





#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CWnd * CTextCad::wd;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextCad::CTextCad()
{
	name="CTextCad";
	rec.setdistprec(5);
	pfont=new CFont;
	tfont=new CFont;
	z_prev=1;
//	CFont gf;
//	pfont->CreateStockObject(ANSI_VAR_FONT);
	liter=0;
//	gf.GetLogFont(pfont);
	
	HFONT hSystemFont=(HFONT)GetStockObject(SYSTEM_FONT);
	LOGFONT systemFont;
	VERIFY(::GetObject(hSystemFont,sizeof(LOGFONT),(void*)&systemFont));

	TCHAR nd[32]=(_T("Times New Roman"));
	liter=0;
	LOGFONT font;memset(&font,0,sizeof(LOGFONT));
//	font.lfOrientation=0;
	font.lfCharSet=DEFAULT_CHARSET;
//	font.lfClipPrecision=CLIP_LH_ANGLES;
//	font.lfEscapement=0;
	lstrcpy(font.lfFaceName, _T("Times New Roman"));
	font.lfHeight=systemFont.lfHeight;//-21;
//	font.lfItalic=FALSE;
//	font.lfOutPrecision=OUT_TT_PRECIS;
//	font.lfPitchAndFamily=FF_ROMAN|DEFAULT_PITCH;
//	font.lfQuality=DEFAULT_QUALITY;
//	font.lfStrikeOut=FALSE;
//	font.lfUnderline=FALSE;
	font.lfWeight=systemFont.lfWeight;//FW_NORMAL;
//	font.lfWidth=0;
	pfont->CreateFontIndirect(&font);//CreateStockObject(ANSI_VAR_FONT);

	iter=0;
	sbiter=seiter=0;
	fPrevB=false;
	selmode=false;
	lcolor=RGB(0,0,0);
//	str=new CString;
	edge_on = true;
	rich=new CTxtED;
}
CTextCad::CTextCad(CFile &file,CDC* hdc)
{
	rec.setdistprec(5);
	pfont=new CFont;

/*
	TCHAR nd[32]="Times New Roman";
	liter=0;
	LOGFONT font;
	font.lfOrientation=0;
	font.lfCharSet=ANSI_CHARSET;
	font.lfClipPrecision=CLIP_LH_ANGLES;
	font.lfEscapement=0;
	strcpy(font.lfFaceName,"Time New Roman");
	font.lfHeight=-16;
	font.lfItalic=FALSE;
	font.lfOutPrecision=OUT_TT_PRECIS;
	font.lfPitchAndFamily=FF_ROMAN|DEFAULT_PITCH;
	font.lfQuality=DEFAULT_QUALITY;
	font.lfStrikeOut=FALSE;
	font.lfUnderline=FALSE;
	font.lfWeight=FW_NORMAL;
	font.lfWidth=0;
	pfont->CreateFontIndirect(&font);//CreateStockObject(ANSI_VAR_FONT);
*/
	fPrevB=false;
	curspos.yhit=0;
	selmode=false;
	lcolor=RGB(0,0,0);
	rich=new CTxtED;

	openfile(file,hdc);
	name="CTextCad";
	
}

CTextCad::~CTextCad()
{
//	delete str;
	delete pfont;

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
	mesh.copy(rec.getMesh());
	ptbegin=rec.ptbegin;
	ptend=rec.ptend;
	updatecore();
	CVector vlo=mesh.getVector(1)-mesh.getVector(0);
	ppvlo=vlo;

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
	vecpos.clear();
	vectext.clear();
	vlpos.clear();
	iter=0;
	fPrevB=false;
	selmode=false;
}

void CTextCad::getTextrec(CWnd* wnd,CDC *hdc)
{
	wd=wnd;
//	setgline(false,false);
/*	wnd->CreateSolidCaret(1,15);
	ssiter=iter;
	seiter=iter;
	ptbegin.push_back(curspos);
	ptend.push_back(curspos);
	updatecore();

	hdc->LPtoDP(&pp);
	rec.setdistprec(10);
	wnd->SetCaretPos(pp);
	wnd->ShowCaret();*/
}

void CTextCad::create(CVector pos)
{
	rec.create(pos);

}
struct Tselected 
	{
	auto operator()(tpair t)
		  {
			return t.second.s;
		  }
	}tselected;

void CTextCad::updatepos()
{
	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();
	CVector vi=vl;	
	itmap j,j1;

	for(itmap i=ltext.begin();i!=ltext.end();i++)
		{
//This part deals with the positionning of the text, taking care of the '\n'
// and other special character, freeing the other parts from dealing with
// positionning
// This allow a dynamic positionning of the element in conjunction with 
// the box
			if(i->second.c=='\n')
			{
				j=i;
				j--;
				if(i==ltext.begin())
					i->second.v=vl;
				else if(j->second.c!='\n')
					i->second.v=j->second.v;

				j=i;
				j++;
				char d=j->second.c;
				if(j!=ltext.end())
				{
					j->second.v.x=vl.x;
					j->second.v.y=i->second.v.y+fmap[ltext[i->first].f].tm.tmAscent+fmap[ltext[i->first].f].tm.tmExternalLeading+fmap[ltext[i->first].f].tm.tmInternalLeading;
				}
				else
					continue;
				if(j->second.c=='\n') continue;
				i++;
			}
			else if(i==ltext.begin())
			{
				i->second.v=vl;
			}
			else
			{
				j=i;
				j--;
				i->second.v=j->second.v;
				i->second.v.x=j->second.v.x+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfA+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfB+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfC;
				if(i->second.v.x>vr.x)
				{
					i->second.v.x=vl.x;
					i->second.v.y+=fmap[ltext[j->first].f].tm.tmAscent+fmap[ltext[j->first].f].tm.tmExternalLeading+fmap[ltext[j->first].f].tm.tmInternalLeading;
				}

			}
	}
}

itmap CTextCad::uptext(int i)
{
	itmap prev=ltext.find(i-1),prev1;
	CVector v;
	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();

	if(prev!=ltext.end())
	{
	mytext2 mf;
	itmap st=ltext.find(i-1);
	int j=1;
	float jk=st->second.v.y;
//	while((st->second.v.y==prev->second.v.y)&&(st!=ltext.begin()))
	while(st->second.v.x!=vl.x)
	{
		j++;
		st--;//=ltext.lower_bound(i);
		float gk=st->second.v.y;
	}
	if(st!=ltext.begin()) 
		st--;
	
	prev1=st;
	int k=0;
	while(st->second.v.x>prev->second.v.x)
	{
		k++;
		st--;
	}
	st++;
	liter++;
	return st;
	}
	else
		return ltext.find(i);
		
}

itmap CTextCad::downtext(int i)
{
	itmap prev=ltext.find(i+1),prev1;
	CVector v;
	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();

	if(prev!=ltext.end())
	{
	mytext2 mf;
	itmap st=ltext.find(i+1);
	int j=1;
	float jk=st->second.v.y;
//	while((st->second.v.y==prev->second.v.y)&&(st!=ltext.end()))
	while((st->second.v.x!=vl.x)&&(st!=ltext.end()))
	{
		j++;
		st++;//=ltext.lower_bound(i);
	}
	prev1=st;
	int k=0;
	while((st->second.v.x<prev->second.v.x)&&(st!=ltext.end()))
	{
		k++;
		jk=st->second.v.x;
		st++;
	}
	if(st==ltext.end()) 
		st--;
	return st;
	}
	else
		return ltext.find(i);
}

CPoint CTextCad::updatecurs(int i)
{
	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();
	itmap prev=ltext.find(i);
	vl.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
	CVector v;
/*	if(prev!=ltext.end())
	{
	v=prev->second.v;
	v=ltext[(*prev).first].v;
	if(prev->second.c=='\n') 
	{
		v.x=vl.x;
		v.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
	}
	else
		v.x+=fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfB+fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfC;
	if(v.x>vr.x)
	{
		v.x=vl.x;
		v.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
	}
	}
	else
	{
		if(i<0)
			{
			if(ltext.find(0)!=ltext.end())
				v=ltext[0].v;
			}
		else
			{
			if(ltext.find(ltext.size())!=ltext.end())
				v=ltext[ltext.size()].v;
			}
	}*/
	return v;
}
CPoint CTextCad::drawtext(CDC *hdc, UINT nchar)
{
	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();

	//CFont ft;
	//ft.CreateFontIndirect(pfont);

	CFont *oldf=(CFont*)hdc->SelectObject(pfont);
	mytext2 t;

	itmap i1,i2;
	itmap i;
	if(sbiter!=seiter)
		{
		int k=seiter;
		int j=sbiter;
		j=seiter>sbiter?sbiter:seiter;
		k=seiter>sbiter?seiter:sbiter;
		itmap i0=ltext.find(j);
		itmap i1=ltext.find(k);
		for(i=i0;i1!=ltext.end();i++,i1++)
			{
			i->second=i1->second;
			}
		
		ltext.erase(i,ltext.end());
		sbiter=seiter;
//		updatepos(j-1);
		iter=j--;
		sbiter=seiter;
		}
	mytext2 mf,mfo;
	mf.c=nchar;
	mf.f=pfont;
	mf.s=false;
	itmap prev=ltext.find(iter-1);
	int kj=prev->first;
	ifmap it=fmap.find(pfont);

	CVector v;
	
		if(prev!=ltext.end())
		{
			if(prev->second.c!='\n')
			{
//			v=ltext[(*prev).first].v;
//			v.x+=fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfA+fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfB+fmap[ltext[(*prev).first].f].abc[ltext[(*prev).first].c].abcfC;
			if(v.x>vr.x)
				{

//				v.x=vl.x;
//				v.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
				}
			}
			else
			{
//				v=ltext[(*prev).first].v;
//				v.x=vl.x;
//				v.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;
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
			fmap.insert(make_pair(pfont,m));

			v=vl;
			ifmap it=fmap.find(pfont);
			v.y+=it->second.tm.tmAscent+it->second.tm.tmExternalLeading+it->second.tm.tmInternalLeading;
		}
//	mf.v=v;
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

		}
	iter++;
 //   hdc->draw
	updatepos();
	hdc->SelectObject(oldf);
	CPoint pp;
	pp=updatecurs(iter-1);
	hdc->LPtoDP(&pp);

	return pp;
}

CPoint CTextCad::deleteback(CDC *hdc)
{
	if(sbiter!=seiter)
		{
		int k=seiter;
		int j=sbiter;
		j=seiter>sbiter?sbiter:seiter;
		k=seiter>sbiter?seiter:sbiter;
		itmap i0=ltext.find(j);
		itmap i1=ltext.find(k);
		itmap i;
		for(i=i0;i1!=ltext.end();i++,i1++)
			{
			i->second=i1->second;
			}
		
		ltext.erase(i,ltext.end());
		sbiter=seiter;
	//	updatepos(j-1);
		iter=sbiter--;
		sbiter=seiter;
		}
	else
		{
		itmap i=ltext.find(iter-1);
		if(i!=ltext.end())
		{
		int k;
		char c;
		itmap o;
		for(o=i;o!=ltext.end();o++)
			{
				k=o->first;
				c=o->second.c;
				o->second=ltext.upper_bound(o->first)->second;
				c=o->second.c;
			}
		o--;
		k=o->first;
		ltext.erase((o));
		iter--;
	//	updatepos(iter-1);
		}
		}
	CPoint pp;
	pp=updatecurs(iter-1);
	hdc->LPtoDP(&pp);
	return pp;

}
/*
 Deal with the user stricking the "ENTER key"
 1. In the case we are at the end of the line a new line should be created=> line feed
 2. In the case text are after the ENTER position, all these text should be send down one 
	line starting at the beginning of the new line.
 3. In the case text were selected, these text should be eliminated before doing 1 or 2
 Input: the HDC to work on top of
 Output: the next poition of the cursor
*/
CPoint CTextCad::entertext(CDC *hdc)
{
	return drawtext(hdc,'\n');
/*	CRect ro(box.corner(0),box.corner(3));
	CVector vr=ro.BottomRight();
	CVector vl=ro.TopLeft();

	//Are text selected?
	if(sbiter!=seiter)
		{
			int k=seiter;
			int j=sbiter;
			j=seiter>sbiter?sbiter:seiter;
			k=seiter>sbiter?seiter:sbiter;
			itmap i0=ltext.find(j);
			itmap i1=ltext.find(k);
			for(itmap i=i0;i1!=ltext.end();i++,i1++)
				{
				i->second=i1->second;
				}
			
			ltext.erase(i,ltext.end());
			sbiter=seiter;
			updatepos(j-1);
			iter=j;
		}
	else
		{
			CRect ro(box.corner(0),box.corner(3));
			CVector vr=ro.BottomRight();
			CVector vl=ro.TopLeft();
			CVector v;
/*			if(ltext.find(iter)!=ltext.end())
			{
			float kl=ltext[iter].v.y;
			for(itmap j=ltext.find(iter);j!=ltext.end();j++)
			{
				if(kl!=j->second.v.y)
				{
					 v=j->second.v;
					 v.y+=fmap[ltext[j->first-1].f].tm.tmAscent+fmap[ltext[j->first-1].f].tm.tmExternalLeading+fmap[ltext[j->first-1].f].tm.tmInternalLeading;
 					 j->second.v=v;
				}
			}
			for(j=ltext.find(iter);j!=ltext.end();j++)
			{
				if(kl==j->second.v.y)
				{
					if(j==ltext.find(iter))
					{
     				 v.x=vl.x;
					}else
					{
					 v.x+=fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfA+fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfB+fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfC;
					}
		             v.y=j->second.v.y;
					 v.y+=fmap[ltext[j->first-1].f].tm.tmAscent+fmap[ltext[j->first-1].f].tm.tmExternalLeading+fmap[ltext[j->first-1].f].tm.tmInternalLeading;
 					 j->second.v=v;
				}
			}

			}

			itmap prev=ltext.find(iter-1);

			v=ltext[(*prev).first].v;
			v.x=vl.x;
			v.y+=fmap[ltext[(*prev).first].f].tm.tmAscent+fmap[ltext[(*prev).first].f].tm.tmExternalLeading+fmap[ltext[(*prev).first].f].tm.tmInternalLeading;

			int m=ltext.size();
			int i=m;
			while(i>=iter)
			{
				ltext[i]=ltext[i-1];
				i--;
			}
			mytext mf,mfo;
			mf.c='\n';
			mf.f=pfont;
			ltext[iter-1]=mf;
*/
/*			mytext mf;
			mf.c='\n';
			mf.f=pfont;
			itmap st=ltext.upper_bound(iter);
			int m=ltext.size();
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
			}
//			ltext[iter].v=ltext[iter-1].v;
			m=ltext.size();
			iter++;

			CPoint pp=v;
			hdc->LPtoDP(&pp);
			return pp;
		}

/*		itmap i=ltext.find(iter-1),j=ltext.end();
		if(i!=j) //Are we at the end of the line?
		{
		mytext mf,mfo;
		mf.c=' ';
		mf.f=pfont;
		mf.s=false;
//		ltext[ltext.size()]=mf;
		int k;
		char c;
		--j;
		for(itmap o=j;o!=i;--o)
		{
			k=o->first;
			mfo=o->second;
			o->second=ltext.lower_bound(o->first-1)->second;
			mfo=o->second;
		}
//		++o;
		CVector v;
		v=ltext[o->first-1].v;
		v.x+=fmap[ltext[o->first].f].abc[ltext[o->first].c].abcfA+fmap[ltext[o->first].f].abc[ltext[o->first].c].abcfB+fmap[ltext[o->first].f].abc[ltext[o->first].c].abcfC;
		mf.v=v;
		o->second=mf;
		o++;
		v.x=vl.x;

		v.y+=fmap[ltext[o->first].f].tm.tmAscent+fmap[ltext[o->first].f].tm.tmExternalLeading+fmap[ltext[o->first].f].tm.tmInternalLeading;
		k=o->second.v.y;
		o->second.v=v;
		o->second.f=pfont;
		float kl=v.y;
		o++;
		mfo=o->second;
		kl=o->second.v.y;
		for(j=o;j!=ltext.end();j++)
		{
			if(kl==j->second.v.y)
			{
				 v=ltext[j->first-1].v;
				 v.x+=fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfA+fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfB+fmap[ltext[j->first-1].f].abc[ltext[j->first-1].c].abcfC;
				 j->second.v=v;
			}
			else
				{
				 v=j->second.v;
	             v.y+=fmap[ltext[j->first-1].f].tm.tmAscent+fmap[ltext[j->first-1].f].tm.tmExternalLeading+fmap[ltext[j->first-1].f].tm.tmInternalLeading;
 				 j->second.v=v;
				}
		}
		}

//		iter--;
//		updatepos(o->first);
		}
	CPoint pp;
	pp=updatecurs(iter-1);
	hdc->LPtoDP(&pp);
	return pp;*/

}

CPoint CTextCad::kbmovecurs(CDC *hdc,CString& d)
{
	
	if(d=="left")
		{
			iter--;
			if(iter<0) iter=0;
			if(selmode)
			{
				
				int k=seiter;
				int j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=false;
				}
				seiter=iter;
				k=iter;
				j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=true;
				}
			}
			else
			{
				if(sbiter!=seiter)
				{
					int k=seiter;
					int j=sbiter;
					j=seiter>sbiter?sbiter:seiter;
					k=seiter>sbiter?seiter:sbiter;
					for(int l=j;l<k;l++)
					{
						ltext[l].s=false;
					}
					iter=j;
					sbiter=seiter;
					selmode=false;
				}
			}

		}
	else
	if(d=="right")
		{
			iter++;
			if(iter>ltext.size())
				iter=ltext.size();
			if(selmode)
			{
				int k=seiter;
				int j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				if(j<0)
					{
					int jhg=0;
					}
				for(int l=j;l<k;l++)
				{
					ltext[l].s=false;
				}
				seiter=iter;
				k=iter;
				j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=true;
				}
			}
			else
			{
			if(sbiter!=seiter)
				{
					int k=seiter;
					int j=sbiter;
					j=seiter>sbiter?sbiter:seiter;
					k=seiter>sbiter?seiter:sbiter;
					for(int l=j;l<=k;l++)
					{
						ltext[l].s=false;
					}
//					iter=sbiter;
					sbiter=seiter;
					selmode=false;
				}
			}
		}
	else
	if(d=="end")
		{
/*			itmap i;//=find_if(ltext.begin(),ltext.end(),endtext);
			iter=(*i).first;
			if(selmode)
			{
				seiter=iter;
				int j=sbiter;
				sbiter=seiter>sbiter?sbiter:seiter;
				seiter=seiter>j?seiter:j;
			}
			else
			{
			if(sbiter!=seiter)
				{
					sbiter=seiter;
				}
			}*/
		}
	else
	if(d=="home")
		{
/*			itmap i;//=find_if(ltext.begin(),ltext.end(),hometext);
			iter=(*i).first;
			if(selmode)
			{
				seiter=iter;
				int j=sbiter;
				sbiter=seiter>sbiter?sbiter:seiter;
				seiter=seiter>j?seiter:j;
			}
			else
			{
			if(sbiter!=seiter)
				{
					sbiter=seiter;
				}
			}*/
		}
	else
	if(d=="up")
		{
			itmap i=uptext(iter);
			iter=(*i).first;
			if(iter<0) iter=0;
			if(selmode)
			{
				int k=seiter;
				int j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=false;
				}
				seiter=iter;
				k=seiter;
				j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=true;
				}

			}
			else
			{
			if(sbiter!=seiter)
				{
					int k=seiter;
					int j=sbiter;
					j=seiter>sbiter?sbiter:seiter;
					k=seiter>sbiter?seiter:sbiter;
					for(int l=j;l<k;l++)
					{
						ltext[l].s=false;
					}
//					iter=sbiter;
					sbiter=seiter;
					selmode=false;
				}
			}
				}
	else
	if(d=="down")
		{
			itmap i=downtext(iter),j;
			iter=(*i).first;
			if(iter>=ltext.size())
				iter=ltext.size()-1;
			if(selmode)
			{
				int k=seiter;
				int j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=false;
				}
				seiter=iter;
				k=seiter;
				j=sbiter;
				j=seiter>sbiter?sbiter:seiter;
				k=seiter>sbiter?seiter:sbiter;
				for(int l=j;l<k;l++)
				{
					ltext[l].s=true;
				}
			}
			else
			{
			if(sbiter!=seiter)
				{
					int k=seiter;
					int j=sbiter;
					j=seiter>sbiter?sbiter:seiter;
					k=seiter>sbiter?seiter:sbiter;
					for(int l=j;l<k;l++)
					{
						ltext[l].s=false;
					}
//					iter=sbiter;
					sbiter=seiter;
					selmode=false;
				}
			}
		}
	else
	if(d=="selStart")
		{
			if(!selmode)
			{
			if(ltext.find(iter)!=ltext.end())
				{
			sbiter=iter;
			seiter=iter;
			selmode=true;
				}
			}
		}
	else
	if(d=="selStop")
		{
			for(int j=sbiter;j<seiter;j++)
			{
				ltext[j].s=false;
			}
			selmode=false;
		}
	else
	if(d=="delete")
		{

			if(sbiter!=seiter)
				{
					int k=seiter;
					int j=sbiter;
					j=seiter>sbiter?sbiter:seiter;
					k=seiter>sbiter?seiter:sbiter;
					itmap i0=ltext.find(j);
					itmap i1=ltext.find(k);
					itmap i;
					for(i=i0;i1!=ltext.end();i++,i1++)
						{
						i->second=i1->second;
						}
					
					ltext.erase(i,ltext.end());
					sbiter=seiter;
				//	updatepos(j-1);
					iter=j;
				}
			else
				{
				itmap i=ltext.find(iter);
				if(i!=ltext.end())
				{
				int k;
				char c;
				itmap o;
				for(o=i;o!=ltext.end();o++)
					{
						k=o->first;
						c=o->second.c;
						o->second=ltext.upper_bound(o->first)->second;
						c=o->second.c;
					}
				o--;
				k=o->first;
				ltext.erase((o));
			//	updatepos(iter-1);
				}
				}
		}
	CPoint pp;
	pp=updatecurs(iter-1);
	hdc->LPtoDP(&pp);
	return pp;
}
void drawAsPath()
{
/*
		bool b=hdc->BeginPath();
		um=hdc->SetMapMode(rhdc->GetMapMode());
		vector<long> line;
		line.resize(rich->GetLineCount());
		for(int i=0;i<length;i++)
		{
			rich->SetSel(i,i+1);
			rich->GetSelectionCharFormat(cf);

			cf.yHeight*=1/z_prev;
			cf.yHeight*=zm;
			rich->SetSelectionCharFormat(cf);
			rich->GetSelectionCharFormat(cf);
			dlg.FillInLogFont(cf);
			CFont ffont;
			ffont.CreateFontIndirect(&dlg.m_lf);
			line[rich->LineFromChar(i)]=(line[rich->LineFromChar(i)]<dlg.m_lf.lfHeight?line[rich->LineFromChar(i)]:dlg.m_lf.lfHeight);
		}
		CPoint _pi;
		CVector vpi,vpi2;
		vector<CVector> mvec;
		double u=-ang*1800/pi;
		pol=po;
		hdc->DPtoLP(&pol);
		for(i=0;i<length;i++)
		{
			rich->SetSel(i,i+1);
			_pi=rich->GetCharPos(i);
			_pi.y-=line[rich->LineFromChar(i)]-1;
			hdc->DPtoLP(&_pi);
			vpi2=pol;
			vpi=_pi;
			vpi=vpi-CVector(CPoint(0,0));
			vpi=polarc(absc(vpi),argu(vpi)+ang);
			vpi=vpi2+vpi;
			mvec.push_back(vpi);
		}
		CVector v00,v01;

		for(i=0;i<length;i++)
		{
			vpi=mvec[i];
//			vpi.assign(vpi);
			_pi=vpi;
			char cc=ci[i];
			rich->GetSelectionCharFormat(cf);
			dlg.FillInLogFont(cf);
			dlg.m_lf.lfHeight-=1;
			dlg.m_lf.lfQuality=DRAFT_QUALITY;
//			dlg.m_lf.lfWeight=FW_NORMAL;
			dlg.m_lf.lfClipPrecision=CLIP_STROKE_PRECIS;
			dlg.m_lf.lfOutPrecision=OUT_STROKE_PRECIS;
			dlg.m_lf.lfOrientation=-u;
			dlg.m_lf.lfEscapement=-u;
			CFont ffont;
			ffont.CreateFontIndirect(&dlg.m_lf);
			CFont *oldfont=(CFont*)hdc->SelectObject(&ffont);
			hdc->SetTextAlign(TA_BASELINE);
			hdc->SetBkMode(TRANSPARENT);
			hdc->SetBkColor(cf.crTextColor);
			hdc->SetTextColor(cf.crTextColor);
			CBrush brush;
			CBrush *ob;
			brush.CreateSolidBrush(cf.crTextColor);
			ob=hdc->SelectObject(&brush);
			
		//	char c='i';
			hdc->TextOut(_pi.x,_pi.y,&cc,1);//&cc,1);
			hdc->SelectObject(oldfont);
			hdc->SelectObject(ob);
		}
//		vt.popTransform();
		hdc->SetMapMode(um);

		b=hdc->EndPath();
//		b=hdc->FlattenPath();
		vector<CPoint>_p;
		vector<BYTE> _b;
		vector <CVector> vMr;
		int n_p=hdc->GetPath(NULL,NULL,NULL);
		if(n_p>0){
		_p.resize(n_p);
		_b.resize(n_p);
		if(hdc->GetPath(_p.begin(),_b.begin(),n_p)){
			CLibS line;
			vector<CPoint> vec;
	//		vec.resize(n_p);
			int i=0;
		   for(iter=0;iter<n_p;iter++)
		   {
			   switch(_b[iter])
			   {
			   case PT_BEZIERTO:
				   vec.push_back(_p[iter]);
				   i++;
					break;
			   case PT_LINETO:
				   vec.push_back(_p[iter]);
				   i++;
					break;
			   case PT_MOVETO:
				   if(i==0)
				   {
				   vec.push_back(_p[iter]);
				   i++;
				   }else
				   {
//					line.add(new CLine(vec));
					vec.clear();
					i=0;
				   vec.push_back(_p[iter]);
				   i++;
				   }
				   break;
			   case PT_CLOSEFIGURE:
//					CLine l(vec);
//					line.add(new CLine(vec));
					vec.clear();
					i=0;
					break;
			   }
		   }
//		hdc->PolyDraw(_p.begin(),_b.begin(),n_p);
//		line.draw(hdc);
		hdc->StrokeAndFillPath();

		}
		}*/

}
void drawAsMetafile()
{
/*
//		hdc->Rectangle(rt2);
		CMetaFileDC mdc;
		LONG um=hdc->GetMapMode();
		CRect r4=*rt2;
		hdc->LPtoDP(rt2);
		CSize sz=rt2->Size();
		hdc->DPtoHIMETRIC(&sz);

		r4=CRect(CPoint(0,0),sz);
		BOOL ub=mdc.CreateEnhanced(hdc,NULL,&r4,NULL);
		LONG uy=::GetLastError();
		mdc.SetAttribDC(hdc->m_hDC);

		hdc->SetMapMode(MM_TWIPS);
		hdc->DPtoLP(rt2);
		CSize sz1=rt2->Size();
		sz1.cy=-sz1.cy;
		FORMATRANGE stFR;
		stFR.hdcTarget=stFR.hdc=hdc->m_hDC;//mdc.m_hDC;
		stFR.rcPage=stFR.rc=CRect(CPoint(0,0),sz1);
		stFR.chrg.cpMin=0;
		stFR.chrg.cpMax=-1;
		hdc->LPtoDP(rt2);
		hdc->BeginPath();

		hdc->SetMapMode(MM_TEXT);
		rich->FormatRange(&stFR,TRUE);
		rich->FormatRange(NULL,TRUE);
		hdc->EndPath();
		hdc->FlattenPath();
		vector<CPoint>_p;
		vector<BYTE> _b;
		int n_p=hdc->GetPath(NULL,NULL,NULL);

		HENHMETAFILE hMetaFile=mdc.CloseEnhanced();
		hdc->DPtoLP(rt20);
		CRect rt5=*rt20;
//		rt5.UnionRect(rt5,rt2);
//		hdc->PlayMetaFile(hMetaFile,rt5);
		EnumEnhMetaFile(hdc->m_hDC,hMetaFile,(ENHMFENUMPROC)metafileProc,&ang,rt5);
		hdc->SetBkMode(TRANSPARENT);
		DeleteEnhMetaFile(hMetaFile);
		hdc->SetMapMode(um);
*/
}
int CALLBACK metafileProc(HDC hDC,HANDLETABLE * lpHTable,const ENHMETARECORD *lpEMFR,int nObj,LPARAM lpData)
{
	BOOL bOK;
	float* v=(float*)lpData;
	float ang=*v;
	if(lpEMFR->iType==EMR_EXTCREATEFONTINDIRECTW)
	{
		EMREXTCREATEFONTINDIRECTW *s=(EMREXTCREATEFONTINDIRECTW*)lpEMFR;
		s->elfw.elfLogFont.lfOrientation=ang*1800/pi;
		s->elfw.elfLogFont.lfEscapement=ang*1800/pi;
		
		bOK=PlayEnhMetaFileRecord(hDC,lpHTable,lpEMFR,(UINT)nObj);
		return bOK;
	}
	if(lpEMFR->iType==EMR_EXTTEXTOUTW)
	{
		EMREXTTEXTOUTW *s=(EMREXTTEXTOUTW*)lpEMFR;
		
		bOK=PlayEnhMetaFileRecord(hDC,lpHTable,lpEMFR,(UINT)nObj);
		return bOK;
	}
	if(lpEMFR->iType==EMR_SETTEXTALIGN)
	{
		EMRSETTEXTALIGN *s=(EMRSETTEXTALIGN*)lpEMFR;
		
		bOK=PlayEnhMetaFileRecord(hDC,lpHTable,lpEMFR,(UINT)nObj);
		return bOK;
	}
	bOK=PlayEnhMetaFileRecord(hDC,lpHTable,lpEMFR,(UINT)nObj);
	return bOK;

}
void CTextCad::setpara(CString l)
{
	PARAFORMAT m_paraformat;
	m_paraformat.cbSize = sizeof(PARAFORMAT);
	rich->GetParaFormat(m_paraformat);
	WORD wAlign;
	m_paraformat.dwMask = PFM_ALIGNMENT;

	if(l=="left")
	{
		wAlign=PFA_LEFT;
	}
	if(l=="right")
	{
		wAlign=PFA_RIGHT;
	}
	if(l=="center")
	{
		wAlign=PFA_CENTER;
	}
	m_paraformat.wAlignment = wAlign;
	rich->SetParaFormat(m_paraformat);
}
bool CTextCad::WndVisible()
{
	return ((rich->m_hWnd!=NULL)&&(rich->IsWindowVisible()));
}
void CTextCad::draw3D(CDC *hdc)
{
	edge_on=true;
	
	CCAM cam;
	CVector vlo=mesh.getVector(1)-mesh.getVector(0);
	CVector pvlo=vlo;
//	float zm=absc(CVector(ppvlo.x,ppvlo.y,0))/absc(CVector(pvlo.x,pvlo.y,0));//cam.getzoom();
	float ub1=absc(pvlo);
	float ub2=absc(ppvlo);
	float zm=cam.getzoom();
//	ppvlo=pvlo;
	zm=1/zm;
//	updatecore();
	CVector vr=box.corner(3);//rop.BottomRight();
	CVector vl=box.corner(0);//rop.TopLeft();
	BOOL b1;
	CFontDialog dlg;
	CDC* rhdc;
	CPoint p1=CPoint(mesh.Vertex(1)->v)-CPoint(mesh.Vertex(0)->v);
	CVector v2(p1.x,p1.y,0);
	float ang=-argu(v2);
	CLine l2;
	l2.edge_on=true;
	l2.copy(this);
	l2.setRotateCenter(box.center());
	l2.rotate(ang,-1);
	CRect* rt2= new CRect(l2.getMesh()->Vector(0),l2.getMesh()->Vector(2));
//	rt2->
	CRect rt20(getMesh()->Vector(0),getMesh()->Vector(2));
//	hdc->Rectangle(*rt2);
//	return;
	hdc->LPtoDP(&rt20);
	CRect rt3;
	rt3=*rt2;
	
	if(rich->m_hWnd==NULL){
		hdc->LPtoDP(rt2);
		b1 = rich->Create(ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_VISIBLE | WS_BORDER | WS_OVERLAPPED | WS_CHILD, *rt2, wd, ID_RICHT);
//		rich->SetRect(rt2);
		rhdc=rich->GetDC();
		rhdc->SetMapMode(hdc->GetMapMode());
		rich->SetOptions(ECOOP_OR,ECO_AUTOWORDSELECTION);
		PARAFORMAT2 pf;
		pf.cbSize = sizeof(PARAFORMAT2);
		pf.dwMask=PFM_ALL2|PFM_ALL;
		pf.dxOffset=50;	
		rich->SetParaFormat(pf);
		CHARFORMAT cf;
		cf.cbSize=60;
		cf.dwMask=3892314127;
		cf.dwEffects=0;
		cf.yHeight=200;
		cf.yOffset=0;
		cf.crTextColor=0;
		cf.bPitchAndFamily='"';
		lstrcpy(cf.szFaceName,(_T("Tahoma")));
		rich->SetDefaultCharFormat(cf);
		CPoint pyheight=CVector(cf.yHeight,0);
		CPoint pyheight1=CVector(0,0);
		pyheight=pyheight-pyheight1;
		curspos=CVector(cf.yHeight,0);
		u_prev=sqrt(pyheight.x*pyheight.x+pyheight.y+pyheight.y);
		rich->SetFocus();
		zm=1;
		hdc->DPtoLP(rt2);
	}
		else if((zm!=z_prev)){//&&(rich->IsWindowVisible())){
		
		hdc->LPtoDP(rt2);
		long length=rich->GetTextLength();

		CHARFORMAT cf;
		rich->ShowWindow(TRUE);
		rich->MoveWindow(rt2);
		CPoint pyheight=curspos;
		CPoint pyheight1=CVector(0,0);
		pyheight=pyheight-pyheight1;
		float ur=sqrt(pyheight.x*pyheight.x+pyheight.y+pyheight.y)/u_prev;
		for(int i=0;i<length;i++)
		{
			rich->SetSel(i,i+1);
			rich->GetSelectionCharFormat(cf);
//			cf.yHeight*=1/z_prev;
///			cf.yHeight*=zm;
			cf.yHeight=curspos.x*ur;
			rich->SetSelectionCharFormat(cf);
		}
		rich->SetSel(-1,-1);
		rich->RequestResize();
		rich->Invalidate(TRUE);
		rich->ShowWindow(FALSE);
		int ti=rich->GetLineCount();
		hdc->DPtoLP(rt2);
	}else if(rich->IsWindowVisible()){
		hdc->LPtoDP(rt2);
		rich->MoveWindow(rt2);	
		hdc->DPtoLP(rt2);
		rich->SetFocus();	
	}
	if(transselectedstate()) CLine::drawselect(hdc);
	long length=rich->GetTextLength();
	if(!rich->IsWindowVisible())
	{
		rich->ShowWindow(TRUE);
		hdc->LPtoDP(rt2);
		rich->MoveWindow(rt2);	
		hdc->DPtoLP(rt2);
		rich->ShowWindow(FALSE);
		int ti=rich->GetLineCount();
		
		CHARFORMAT cf;
		rich->SetSel(0,-1);
		CString ci=rich->GetSelText();
		length=ci.GetLength();

		hdc->LPtoDP(rt2);
		CPoint pol=mesh.Vertex(0)->v;
		hdc->LPtoDP(&pol);
		CPoint po=mesh.Vertex(0)->v;//rt2->TopLeft()
		hdc->LPtoDP(&po);

		LONG um=hdc->GetMapMode();
		CDC* rhdc=rich->GetDC();

		um=hdc->SetMapMode(rhdc->GetMapMode());
		//rich->
		vector<long> line;
		line.resize(rich->GetLineCount()+1);
		for(int i=0;i<length;i++)
		{
			rich->SetSel(i,i+1);
			rich->GetSelectionCharFormat(cf);
			dlg.FillInLogFont(cf);
			CFont ffont;
			ffont.CreateFontIndirect(&dlg.m_lf);
			line[rich->LineFromChar(i)]=(line[rich->LineFromChar(i)]<dlg.m_lf.lfHeight?line[rich->LineFromChar(i)]:dlg.m_lf.lfHeight);
		}
		CPoint _pi;
		CVector vpi,vpi2;
		vector<CVector> mvec;
		double u=-ang*1800/pi;
		pol=po;
		hdc->DPtoLP(&pol);
		for(int i=0;i<length;i++)
		{
			rich->SetSel(i,i+1);
			_pi=rich->GetCharPos(i);
			_pi.y-=line[rich->LineFromChar(i)]-1;
			hdc->DPtoLP(&_pi);
			vpi2=pol;
			vpi=_pi;
			vpi=vpi-CVector(CPoint(0,0));
			vpi=polarc(absc(vpi),argu(vpi)+ang);
			vpi=vpi2+vpi;
			mvec.push_back(vpi);
		}
		CVector v00,v01;
		CTVector vt;
//		hdc->BeginPath();
		for(int i=0;i<length;i++)
		{
			vpi=mvec[i];
			_pi=vpi;
			char cc=ci[i];
			rich->SetSel(i,i+1);
			rich->GetSelectionCharFormat(cf);
			dlg.FillInLogFont(cf);
//			dlg.m_lf.lfHeight-=1;
			dlg.m_lf.lfQuality=DRAFT_QUALITY;
//			dlg.m_lf.lfWeight=FW_NORMAL;
			dlg.m_lf.lfClipPrecision=CLIP_STROKE_PRECIS;
			dlg.m_lf.lfOutPrecision=OUT_STROKE_PRECIS;
//			dlg.m_lf.lfOrientation+=uprev;
//			dlg.m_lf.lfEscapement+=uprev;
			dlg.m_lf.lfOrientation=u;
			dlg.m_lf.lfEscapement=u;
			CFont ffont;
			ffont.CreateFontIndirect(&dlg.m_lf);
			CFont *oldfont=(CFont*)hdc->SelectObject(&ffont);
			hdc->SetTextAlign(TA_BASELINE);
			hdc->SetBkMode(TRANSPARENT);
			hdc->SetBkColor(cf.crTextColor);
			hdc->SetTextColor(cf.crTextColor);
			CBrush brush;
			CBrush *ob;
			brush.CreateSolidBrush(cf.crTextColor);
			ob=hdc->SelectObject(&brush);
			
			hdc->TextOut((int)_pi.x,(int)_pi.y,CString(cc),1);//&cc,1);
			hdc->SelectObject(oldfont);
			hdc->SelectObject(ob);
		}
		hdc->SetMapMode(um);
//		hdc->EndPath();

//		hdc->StrokeAndFillPath();

	}
		z_prev=zm;
//		uprev=u;
	delete rt2;
	rt2=NULL;
	return;
	//This vector is to shift the screen to start at the bottom left of the bounding box
	//The x represent the bottom of the screen while the y is the left side
	//(check the CVEctor content
	CVector vv2(vr.getscrb().x,vr.getscrtop().y);

	//We move from the left top of the bounding box to the origin of the world
	//Coordinate then from the origin of the screen coordinate to the new screen
	//starting at the top left of the bounding box
	CTVector vt;
/*	vt.VpushTransform();
	vt.VpushUnit();
	vt.VinitVect();
	vt.VendT();


	vt.pushTransform();
	vt.pushUnit();
//	vt.Translate(vl);//box.corner(0));
//	vt.Translate(vv2);
	vt.endT();*/



	CRect ro(vl,vr),rop;
	rop=ro;
	ro.NormalizeRect();
	CVector vv=box.size();
	CPoint pv=/*ro.Size();//*/box.size();
//	hdc->LPtoDP(&ro);
	CSize pvn=ro.Size();
//	hdc->LPtoDP(&pv);
//	hdc->LPtoDP(&pvn);
	
//	CDC *hmdc=new CDC;

//	hmdc->CreateCompatibleDC(hdc);
//	hmdc->SetMapMode(hdc->GetMapMode());

//	CBitmap* bmp=new CBitmap,*oldbmp;
//	bmp->CreateCompatibleBitmap(hdc,pvn.cx,pvn.cy);
//	oldbmp=(CBitmap*)hmdc->SelectObject(bmp);
	CBrush b;
	b.CreateSolidBrush(RGB(0,0,0));
	COLORREF rfb,rft;
	hdc->SetTextAlign(TA_BASELINE);

	CVector vv1;
	vv1.getcamor();
	vv1.getcooro();


	hdc->SelectObject(b);//GetStockObject(GRAY_BRUSH));

	
	CRect rt(vl,vr),r2;
	r2=rt;
	r2.InflateRect(25,-25);
	CRectTracker rt1(r2,CRectTracker::hatchedBorder);
	CPoint pol=box.corner(0);
//	hdc->SetBkMode(TRANSPARENT);
// 	hdc->Rectangle(rt);
	CLine::draw(hdc);

	if(rich->m_hWnd==NULL){
		rich->Create(ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_CHILD, rt, (CWnd*)::AfxGetMainWnd(),ID_RICHT);
		rich->ShowWindow(SW_SHOWNORMAL);
	}
	
//	box.draw(hmdc);
	CPoint ng=vl;
//	vl.y=vr.y;
//	CVector vi=vl;	
	itmap j,j1;
	LOGFONT font;
	CVector vg2(1,1);
	CVector vg3=vg2;
	vg3.v3D();
	int hj=fmap.size();
	vg3=vg3.getcamx();
	vg3.x=1/vg3.x;
	ifmap mb=fmap.begin();
	ifmap me=fmap.end();
	pfmap.clear();
	ifmap l;
		for(l=mb;l!=me;l++)
		{
			LOGFONT* ft= new LOGFONT;;
			l->first->GetLogFont(ft);
			myfont m;
			m.pf=new LOGFONT;
			*m.pf=*ft;
			CVector v0(vg3.getcamor()),vx(100,0,0,0),vy(0,ft->lfHeight,0,0),v1,vz(0,0,100,0);
			vy=v0+vy;
			ft->lfHeight*=zm;
			
			l->first->Detach();
			l->first->CreateFontIndirect(ft);
			TEXTMETRIC tm;
			hdc->GetTextMetrics(&tm);
			
			m.tm=tm;
			ABCFLOAT* abc=new ABCFLOAT[tm.tmLastChar-tm.tmFirstChar+1];
			GetCharABCWidthsFloat(hdc->GetSafeHdc(),tm.tmFirstChar,tm.tmLastChar,abc);
			for(int i=tm.tmFirstChar;i<=tm.tmLastChar;i++)
			{
			m.abc[i].abcfA=abc[i-tm.tmFirstChar].abcfA*zm;
			m.abc[i].abcfB=abc[i-tm.tmFirstChar].abcfB*zm;
			m.abc[i].abcfC=abc[i-tm.tmFirstChar].abcfC*zm;
			}
			l->second=m;

		}

	for(itmap i=ltext.begin();i!=ltext.end();i++)
		{
//This part deals with the positionning of the text, taking care of the '\n'
// and other special character, freeing the other parts from dealing with
// positionning
// This allow a dynamic positionning of the element in conjunction with 
// the box
			if(i->second.c=='\n')
			{
				j=i;
				j--;
				if(i==ltext.begin())
					i->second.v=vl;
				else if(j->second.c!='\n')
				{
					i->second.v=j->second.v;
				}

				j=i;
				j++;
				char d=j->second.c;
				if(j!=ltext.end())
				{
					j->second.v.x=CPoint(vl).x;
					j->second.v.y=i->second.v.y-(fmap[ltext[i->first].f].tm.tmAscent)*zm;//+fmap[ltext[i->first].f].tm.tmExternalLeading+fmap[ltext[i->first].f].tm.tmInternalLeading)*zm;
				//	i->second.v.y=j->second.v.y;
				}
				else
					continue;
				if(j->second.c=='\n') continue;
				i++;
			}
			else if(i==ltext.begin())
			{
				i->second.v=vl;
				i->second.v.y-=(fmap[ltext[i->first].f].tm.tmAscent)*zm;//+fmap[ltext[i->first].f].tm.tmExternalLeading+fmap[ltext[i->first].f].tm.tmInternalLeading)*zm;
			}
			else
			{
				j=i;
				j--;
				i->second.v=j->second.v;
				i->second.v.x=j->second.v.x+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfA+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfB+fmap[ltext[j->first].f].abc[ltext[j->first].c].abcfC;
				if(i->second.v.x>CPoint(vr).x)
				{
					i->second.v.x=CPoint(vl).x;
					i->second.v.y-=(fmap[ltext[j->first].f].tm.tmAscent)*zm;//+fmap[ltext[j->first].f].tm.tmExternalLeading+fmap[ltext[j->first].f].tm.tmInternalLeading)*zm;
				}

			}

			CFont tmp;
		/*	(*i).second.f->GetLogFont(&font);
		//	font.lfHeight*=vg3.x;
			tmp.CreateFontIndirect(&font);
		*/	CFont *oldfont=(CFont*)hdc->SelectObject((*i).second.f);
			if(!i->second.s)
				{
				hdc->SetBkMode(TRANSPARENT);
				hdc->SetTextColor(fmap[ltext[(*i).first].f].col);
				}
			else
				{
				hdc->SetBkMode(TRANSPARENT);
			//	rfb=hmdc->SetBkColor(RGB(255,255,255));
				rft=hdc->SetTextColor(RGB(0,0,0));
				}
//			CBrush *bold=hdc->SelectObject(&b);

			CPoint v((*i).second.v);
			hdc->TextOut(v.x,v.y,CString((*i).second.c),1);

			//i->first->Detach();
			//i->first->CreateFontIndirect((*i).second.pf);
//			b.DeleteObject();
//			hdc->SelectObject(bold);
			hdc->SelectObject(oldfont);
			if(i->second.s)
			{
			hdc->SetBkColor(rfb);
			hdc->SetTextColor(rft);
			}
			
		}
		for(l=mb;l!=me;l++)
		{
			l->first->Detach();
			l->first->CreateFontIndirect(l->second.pf);
			delete l->second.pf;
/*			TEXTMETRIC tm;
			hdc->GetTextMetrics(&tm);
			myfont m;
			m.tm=tm;
			ABCFLOAT* abc=new ABCFLOAT[tm.tmLastChar-tm.tmFirstChar+1];
			GetCharABCWidthsFloat(hdc->GetSafeHdc(),tm.tmFirstChar,tm.tmLastChar,abc);
			for(int i=tm.tmFirstChar;i<=tm.tmLastChar;i++)
			{
			m.abc[i].abcfA=abc[i-tm.tmFirstChar].abcfA;
			m.abc[i].abcfB=abc[i-tm.tmFirstChar].abcfB;
			m.abc[i].abcfC=abc[i-tm.tmFirstChar].abcfC;
			}
			l->second=m;
*/
		}

//	vt.popTransform();
//	vt.VpopTransform();

//	hdc->BitBlt(rop.TopLeft().x,rop.TopLeft().y,rop.Size().cx,rop.Size().cy,hmdc,0,0,SRCCOPY);
//	bz.plane(box.corner(0),box.corner(3));
//	bz.UpdateTexture(hdc,bmp);
//	bz.surface(hdc);
//	bz.draw(hdc);
//	hdc->SelectObject(oldbmp);


//	delete hmdc;
//	delete hmdc1;

	if (getRotstate())
	{
	hdc->MoveTo(CVector(rotateCenter.x,rotateCenter.y-25));
	hdc->LineTo(CVector(rotateCenter.x,rotateCenter.y+25));
	hdc->MoveTo(CVector(rotateCenter.x-25,rotateCenter.y));
	hdc->LineTo(CVector(rotateCenter.x+25,rotateCenter.y));
	}
}

void CTextCad::draw(CDC *hdc)
{
		draw3D(hdc);

}


void CTextCad::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);
	int irop=hdc->SetROP2(R2_NOTXORPEN);
	CLine::draw(hdc);
	int i=0;


	if(getRotstate()) InitRotState();
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);


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
			if(!getmultcore()) 
			{
				CLine::draw(hdc);
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

	UpdateMesh();

	vt.popTransform();
	}
	CLine::draw(hdc);
	hdc->SetROP2(irop);
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
}
void CTextCad::Rotate(int sens,CVector prevpoint,CVector postpoint)
{
	CFigure::Rotate(sens,prevpoint,postpoint);
	rec.Rotate(sens,prevpoint,postpoint);
	vecpos=ptbegin;
	updatecore();
}
void CTextCad::drawTrans(CDC *hdc)
{
	CLine::drawTrans(hdc);
	return;
	int old=hdc->SetROP2(R2_NOTXORPEN);    

	rec.draw(hdc);

	hdc->SetROP2(old);    
	if (getRotstate())
	{
	hdc->MoveTo(CVector(rotateCenter.x,rotateCenter.y-25));
	hdc->LineTo(CVector(rotateCenter.x,rotateCenter.y+25));
	hdc->MoveTo(CVector(rotateCenter.x-25,rotateCenter.y));
	hdc->LineTo(CVector(rotateCenter.x+25,rotateCenter.y));
	}


}

bool CTextCad::PtinRegion(CVector point)
{
	updatecore();//rec.updatecore();
	if(CLine::PtinRegion(point))
		return true;//rec.PtinRegion(point);
	point.z=box.max.z;
	if(box.containpts(point))
	{

		click=true;
		select=full;
		rotateCenter=box.center();
		return true;
	}
	if(rich->m_hWnd!=NULL){
		rich->ShowWindow(SW_HIDE);
	}
	click=false;
	select=null;
	return false;

}
void CTextCad::getfont(CHARFORMAT& cf)
{
	if(rich->m_hWnd!=NULL){
		long u=-1,v=-1;
		rich->GetSel(u,v);
		if(u!=v){
			rich->GetSelectionCharFormat(cf);
		}
		else
		{
			long length=rich->GetTextLength();
			rich->SetSel(length,length);
			rich->GetSelectionCharFormat(cf);
		}
	}
}
void CTextCad::setLcolor(CDC *hdc,COLORREF color,COLORREF bcolor)
{
	CHARFORMAT cf;
	if(rich->m_hWnd!=NULL){
		long u=-1,v=-1;
		rich->GetSel(u,v);
		rich->GetSelectionCharFormat(cf);
		cf.dwMask=CFM_COLOR;
		cf.crTextColor=color;
		if((u!=v)&&(rich->IsWindowVisible()))
			rich->SetSelectionCharFormat(cf);
		else
		{
			long length=rich->GetTextLength();
			if(rich->IsWindowVisible()){
			rich->SetSel(length,length);
			rich->SetSelectionCharFormat(cf);
			}else{
			rich->SetSel(0,length);
			rich->SetSelectionCharFormat(cf);			
			}
		}
	}
}
CPoint CTextCad::setfont(CDC *hdc,LOGFONT font,COLORREF ccl,CHARFORMAT cf)
{
	if(rich->m_hWnd!=NULL){
		long u=-1,v=-1;
		rich->GetSel(u,v);
		if((u!=v)&&(rich->IsWindowVisible()))
			rich->SetSelectionCharFormat(cf);
		else
		{
			long length=rich->GetTextLength();
			if(rich->IsWindowVisible()){
			rich->SetSel(length,length);
			rich->SetSelectionCharFormat(cf);
			}else{
			rich->SetSel(0,length);
			rich->SetSelectionCharFormat(cf);			
			}
		}
	}
		CPoint pyheight=CVector(cf.yHeight,0);
		CPoint pyheight1=CVector(0,0);
		pyheight=pyheight-pyheight1;
		curspos=CVector(cf.yHeight,0);
		u_prev=sqrt(pyheight.x*pyheight.x+pyheight.y+pyheight.y);

	return CPoint(0,0);
	bool b=false;
	CFont *oldf;
	CFont* h;
	int k,j;
	if(sbiter!=seiter)
	{
	b=true;
	pfont=new CFont;
	pfont->CreateFontIndirect(&font);
	oldf=(CFont*)hdc->SelectObject(pfont);
	LOGFONT pp;
	pfont->GetLogFont(&pp);
	k=seiter;
	j=sbiter;
	j=seiter>sbiter?sbiter:seiter;
	k=seiter>sbiter?seiter:sbiter;
		for(int l=j;l<k;l++)
		{
			ltext[l].f=pfont;
		}
	}
	else
		{
		delete pfont;
		pfont=new CFont;
		pfont->CreateFontIndirect(&font);
		oldf=(CFont*)hdc->SelectObject(pfont);
		k=ltext.size();
		for(int l=0;l<k;l++)
		{
			ltext[l].f=pfont;
		}
//		setText(mtext,hdc);
		}


	TEXTMETRIC tm;
	hdc->GetTextMetrics(&tm);
	myfont m;
	m.tm=tm;
	m.col=ccl;
	ABCFLOAT* abc=new ABCFLOAT[tm.tmLastChar-tm.tmFirstChar+1];
	GetCharABCWidthsFloat(hdc->GetSafeHdc(),tm.tmFirstChar,tm.tmLastChar,abc);
	for(int i=tm.tmFirstChar;i<=tm.tmLastChar;i++)
	{
	m.abc[i].abcfA=abc[i-tm.tmFirstChar].abcfA;
	m.abc[i].abcfB=abc[i-tm.tmFirstChar].abcfB;
	m.abc[i].abcfC=abc[i-tm.tmFirstChar].abcfC;
	}
	if(!b) fmap.insert(make_pair(pfont,m));
	else
		fmap.insert(make_pair(pfont,m));

	hdc->SelectObject(oldf);
//	if(b) 
		updatepos();
	
/*	pfont=font;
	lcolor=ccl;

	CFont ft;
	ft.CreateFontIndirect(&pfont);
	CFont *oldfont=hdc->SelectObject(&ft);
	hdc->GetOutputTextMetrics(&textmet); 
	
	vector<CVector>::iterator ptiter=vecpos.begin();
	vector<CVector>::iterator pib=vecpos.begin()+1;
	for(vector<CString*>::iterator j=stk.begin();j<stk.end();j++)
	{
		for(int i=0;i<(*j)->GetLength();i++)
		{
			if(pib->y==(pib-1)->y)
			{
			CSize cs=hdc->GetTextExtent((*j)->Left(i+1));//str[i]);
			CPoint pu=*ptiter;//*iter;
			pu.x+=cs.cx;CVector v=pu;
			pib->x=v.x;//(pib-1)->x+cs.cx;
			}
		pib++;
		}
			ptiter+=((*j)->GetLength()+1);
			pib=ptiter+1;
	}

	ptbegin.clear();
	ptend.clear();

	for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
	{
		ptbegin.push_back(*vpit);
		ptend.push_back(*vpit);
	}
	updatecore();*/
	CPoint pp;
//	pp=updatecurs(iter-1);
//	hdc->LPtoDP(&pp);
	return pp;
}

CPoint CTextCad::texthome(CDC *hdc)
{
	vectext.begin();
	vecpos.begin();

	CPoint pp;
	pp=curspos;
	hdc->LPtoDP(&pp);
	return pp;	
}

CPoint CTextCad::deletetext(CDC *hdc)
{

/*	titer=vectext.erase(titer-1);
	vecpos.pop_back();
	ptbegin.pop_back();
	ptend.pop_back();
	updatecore();*/
	CPoint pp;
//	pp=*iter;
	hdc->LPtoDP(&pp);
	return pp;
}

CPoint CTextCad::textend(CDC *hdc)
{
	vectext.pop_back();
	vecpos.pop_back();


	CPoint pp;
	pp=curspos;
	hdc->LPtoDP(&pp);
	return pp;
}
void CTextCad::setFStyle(FSTYLE* _fstyle)
{
	fstyle=_fstyle;
}
void CTextCad::savefiledxf(CStdioFile& file)
{
	int n=rich->GetTextLength();
	CString vis;
	rich->GetWindowText(vis);
	if(n<255)
	{
		file.WriteString(_T("  0"));file.WriteString(_T("\n"));
		file.WriteString(_T("TEXT"));file.WriteString(_T("\n"));
		file.WriteString(_T("  5"));file.WriteString(_T("\n"));
		file.WriteString(LPCTSTR(gethandle().c_str()));file.WriteString(_T("\n"));
		file.WriteString(_T("330"));file.WriteString(_T("\n"));
		file.WriteString(_T("1F"));file.WriteString(_T("\n"));
		file.WriteString(_T("100"));file.WriteString(_T("\n"));
		file.WriteString(_T("AcDbEntity"));file.WriteString(_T("\n"));
		file.WriteString(_T("  8"));file.WriteString(_T("\n"));
		file.WriteString(getLayer().name);file.WriteString(_T("\n"));
		file.WriteString(_T("100"));file.WriteString(_T("\n"));
		file.WriteString(_T("AcDbText"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 10"));file.WriteString(_T("\n"));
		CVector v=mesh.getVector(0);
		CString ps;
		ps.Format(_T("%f"),v.x);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 20")); file.WriteString(_T("\n"));
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 30"));file.WriteString(_T("\n"));
		ps.Format(_T("%f"),v.z);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 40"));file.WriteString(_T("\n"));
		CHARFORMAT cf;
		getfont(cf);		
		CDC dc;
		dc.CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
		LONG yPerInch1=dc.GetDeviceCaps(LOGPIXELSY);
		LONG yPerInch=1;
		float yheight=(float)(cf.yHeight*yPerInch)/(1440*1);//fstyle->width_factor);
		ps.Format(_T("%f"),yheight);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T("  1"));file.WriteString(_T("\n"));
		rich->GetWindowText(ps);
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T("  7"));file.WriteString(_T("\n"));
		file.WriteString(cf.szFaceName/*fstyle->name.c_str()*/);file.WriteString(_T("\n"));
		file.WriteString(_T(" 72"));file.WriteString(_T("\n"));
		PARAFORMAT m_paraformat;
		rich->GetParaFormat(m_paraformat);
		if(m_paraformat.wAlignment==PFA_LEFT)
		{
			file.WriteString(_T("     0"));file.WriteString(_T("\n"));
		}
		else
		if(m_paraformat.wAlignment==PFA_CENTER)
		{
			file.WriteString(_T("     1" ));file.WriteString(_T("\n"));
		}
		else
		if(m_paraformat.wAlignment==PFA_RIGHT)
		{
			file.WriteString(_T("     2"));file.WriteString(_T("\n"));
		}

		if(m_paraformat.wAlignment!=PFA_LEFT)
		{
		CVector v=mesh.getVector(1);
		CString ps;
		ps.Format(_T("%f"),v.x);	
		file.WriteString(_T(" 11"));file.WriteString(_T("\n"));
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 21"));file.WriteString(_T("\n"));
		ps.Format(_T("%f"),v.y);
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 31"));file.WriteString(_T("\n"));
		ps.Format(_T("%f"),v.z);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		}
	}else
	{
		file.WriteString(_T("  0"));file.WriteString(_T("\n"));
		file.WriteString(_T("MTEXT"));file.WriteString(_T("\n"));
		file.WriteString(_T("  5"));file.WriteString(_T("\n"));
		file.WriteString(LPCTSTR(gethandle().c_str()));file.WriteString(_T("\n"));
		file.WriteString(_T("330"));file.WriteString(_T("\n"));
		file.WriteString(_T("1F"));file.WriteString(_T("\n"));
		file.WriteString(_T("100"));file.WriteString(_T("\n"));
		file.WriteString(_T("AcDbEntity"));file.WriteString(_T("\n"));
		file.WriteString(_T("  8"));file.WriteString(_T("\n"));
		file.WriteString(getLayer().name);file.WriteString(_T("\n"));
		file.WriteString(_T("100"));file.WriteString(_T("\n"));
		file.WriteString(_T("AcDbMText"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 10"));file.WriteString(_T("\n"));
		CVector v=mesh.getVector(0);
		CString ps;
		ps.Format(_T("%f"),v.x);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 20"));file.WriteString(_T("\n"));
		ps.Format(_T("%f"),v.y);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 30"));file.WriteString(_T("\n"));
		ps.Format(_T("%f"),v.z);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 40"));file.WriteString(_T("\n"));
		CHARFORMAT cf;
		getfont(cf);		
		CDC dc;
		dc.CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
		LONG yPerInch1=dc.GetDeviceCaps(LOGPIXELSY);
		LONG yPerInch=1;
		float yheight=cf.yHeight*yPerInch/(1440*1);//fstyle->width_factor);
		ps.Format(_T("%f"),yheight);	
		file.WriteString(ps);file.WriteString(_T("\n"));
		file.WriteString(_T(" 41"));file.WriteString(_T("\n"));
		file.WriteString(_T("6.843161446901433"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 71"));file.WriteString(_T("\n"));
		file.WriteString(_T("     1"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 72"));file.WriteString(_T("\n"));
		file.WriteString(_T("     5"));file.WriteString(_T("\n"));
		int i = 0;
		for(i=0;(i<n)&&((n-i)>=255);i+=255)
		{
			CString ty;
			for(int j=i;j<i+255;j++)
			{
				ty+=vis[j];
			}
		
		file.WriteString(_T("  3"));file.WriteString(_T("\n"));
		file.WriteString(ty);file.WriteString(_T("\n"));
		}
		CString ty;
		for(int j=i;j<n;j++)
		{
			ty+=vis[i];
		}
		file.WriteString(_T("  1"));file.WriteString(_T("\n"));
		file.WriteString(ty);file.WriteString(_T("\n"));
		file.WriteString(_T("  7"));file.WriteString(_T("\n"));
		file.WriteString(cf.szFaceName/*fstyle->name.c_str()*/);file.WriteString(_T("\n"));
		file.WriteString(_T(" 11"));file.WriteString(_T("\n"));
		file.WriteString(_T("0.0000000000000001"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 21"));file.WriteString(_T("\n"));
		file.WriteString(_T("1.0"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 31"));file.WriteString(_T("\n"));
		file.WriteString(_T("0.0"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 73"));file.WriteString(_T("\n"));
		file.WriteString(_T("     1"));file.WriteString(_T("\n"));
		file.WriteString(_T(" 44"));file.WriteString(_T("\n"));
		file.WriteString(_T("1.0"));file.WriteString(_T("\n"));

	}
}

void CTextCad::savefile(CFile &file)
{
	CLine::savefile(file);
 	long length=rich->GetTextLength();
	file.Write(&length,sizeof(long));
	file.Write(&u_prev,sizeof(float));
	file.Write(&z_prev,sizeof(float));
	if(getMesh()->view->GetDocument()->m_objects->version>1)
		curspos.savefile(file);

	CHARRANGE cr;
	rich->GetSel(cr);

	rich->SetSel(0,-1);
	CString sc=rich->GetSelText();
	for(int i=0;i<length;i++)
	{	
		char c=sc[i];
		file.Write(&c,sizeof(char));
	}

	PARAFORMAT m_paraformat;
	rich->GetParaFormat(m_paraformat);
	file.Write(&m_paraformat.wNumbering,sizeof(WORD));
	file.Write(&m_paraformat.dxStartIndent,sizeof(LONG));
	file.Write(&m_paraformat.dxRightIndent,sizeof(LONG));
	file.Write(&m_paraformat.dxOffset,sizeof(LONG));
	file.Write(&m_paraformat.wAlignment,sizeof(WORD));

	
	for(int i=0;i<length;i++)
	{
		rich->SetSel(i,i+1);
		CHARFORMAT cf;
		rich->GetSelectionCharFormat(cf);
		file.Write(&cf.yHeight,sizeof(LONG));
		file.Write(&cf.yOffset,sizeof(LONG));
		file.Write(&cf.yOffset,sizeof(LONG));
		file.Write(&cf.crTextColor,sizeof(COLORREF));
		file.Write(&cf.bCharSet,sizeof(BYTE));
		file.Write(&cf.bPitchAndFamily,sizeof(BYTE));
		for(int j=0;j<LF_FACESIZE;j++)
		{
		file.Write(&cf.szFaceName[j],sizeof(WCHAR));
		}
//		CString sc=rich->GetSelText();
//		char c=sc[0];
//		file.Write(&c,sizeof(char));
	}
	rich->SetSel(cr);
	
}
void CTextCad::openfile(CFile &file,CDC* hdc)
{
/*	int i,j;
	LOGFONT lf;
	file.Read(&i,sizeof(int));
	file.Read(&j,sizeof(int));
	char* s1=new char[i];
	file.Read(s1,i);
	file.Read(&lf,j);
	mtext.Format("%s",s1);
	delete s1;
	//delete pfont;
	pfont->CreateFontIndirect(&lf);//CreateStockObject(ANSI_VAR_FONT);*/
	CLine::openfile(file);
	draw3D(hdc);
 	long length;
	file.Read(&length,sizeof(long));
	file.Read(&u_prev,sizeof(float));
	file.Read(&z_prev,sizeof(float));
	if(getMesh()->view->GetDocument()->m_objects->version>1)
		curspos.openfile(file);

	CString sc;//=rich->GetSelText();
	for(int i=0;i<length;i++)
	{	
		char c;
		file.Read(&c,sizeof(char));
		sc+=c;
	}
	rich->SetWindowText(sc);

	PARAFORMAT m_paraformat;
	rich->GetParaFormat(m_paraformat);
	file.Read(&m_paraformat.wNumbering,sizeof(WORD));
	file.Read(&m_paraformat.dxStartIndent,sizeof(LONG));
	file.Read(&m_paraformat.dxRightIndent,sizeof(LONG));
	file.Read(&m_paraformat.dxOffset,sizeof(LONG));
	file.Read(&m_paraformat.wAlignment,sizeof(WORD));
	
	for(int i=0;i<length;i++)
	{
		CHARFORMAT cf;
		rich->SetSel(i,i+1);
		rich->GetSelectionCharFormat(cf);
		file.Read(&cf.yHeight,sizeof(LONG));
		file.Read(&cf.yOffset,sizeof(LONG));
		file.Read(&cf.yOffset,sizeof(LONG));
		file.Read(&cf.crTextColor,sizeof(COLORREF));
		file.Read(&cf.bCharSet,sizeof(BYTE));
		file.Read(&cf.bPitchAndFamily,sizeof(BYTE));
		for(int j=0;j<LF_FACESIZE;j++)
		{
		file.Read(&cf.szFaceName[j],sizeof(WCHAR));
		}
//		char c=' ';
//		file.Read(&c,sizeof(char));
//		rich->ReplaceSel(&c);
		rich->SetSelectionCharFormat(cf);
	}
	rich->SetParaFormat(m_paraformat);
	rich->ShowWindow(SW_HIDE);
}
class _afxRichEditCookie
{
public:
	CArchive& m_ar;
	DWORD m_dwError;
	_afxRichEditCookie(CArchive& ar) : m_ar(ar) {m_dwError=0;}
};

// return 0 for no error, otherwise return error code
DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	_afxRichEditCookie* pCookie = (_afxRichEditCookie*)dwCookie;
	CArchive& ar = pCookie->m_ar;
	ar.Flush();
	DWORD dw = 0;
	*pcb = cb;

	TRY
	{

		if (ar.IsStoring())
			ar.GetFile()->Write(pbBuff, cb);
		else
			*pcb = ar.GetFile()->Read(pbBuff, cb);
	}
	CATCH(CFileException, e)
	{

		*pcb = 0;
		pCookie->m_dwError = (DWORD)e->m_cause;
		dw = 1;
//		DELETE_EXCEPTION(e);
	}
	AND_CATCH_ALL(e)
	{
		*pcb = 0;
		pCookie->m_dwError = (DWORD)CFileException::generic; //clashes with future language
		dw = 1;
//		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

	return dw;
}


void CTextCad::assign(CDC *hdc,CVector p,CString s,CHARFORMAT* _cf)
{
/*	*str=s;
	//CFont ft;
	//ft.CreateFontIndirect(&pfont);
	CFont *oldfont=(CFont*)hdc->SelectObject(&pfont);
	hdc->GetOutputTextMetrics(&textmet); 

	stk.push_back(str);
	is=stk.end()-1;

	vecpos.push_back(p);
	vector<CVector>::iterator pib=vecpos.begin()+1;
	CVector pl=p;
	for(int i=0;i<(*is)->GetLength();i++)
	{
		CSize cs=hdc->GetTextExtent((*is)->Left(i+1));//str[i]);
		CPoint pu=*vecpos.begin();//*iter;
		pu.x+=cs.cx;CVector v=pu;
		pl.x=v.x;//(pib-1)->x+cs.cx;

		
		vecpos.push_back(pl);
		pib++;
	}

	ptbegin.clear();
	ptend.clear();

	for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
	{
		ptbegin.push_back(*vpit);
		ptend.push_back(*vpit);
	}
	updatecore();
	iter=i;//vecpos.begin();
	hdc->SelectObject(oldfont);
*/
	mtext=s;
	CRect rt;
	rt.SetRectEmpty();
	CHARFORMAT cf;

	if(_cf==NULL)
	{
	cf.cbSize=60;
	cf.dwMask=3892314127;
	cf.dwEffects=0;
	cf.yHeight=200;
	cf.yOffset=0;
	cf.crTextColor=0;
	cf.bPitchAndFamily='"';
	lstrcpy(cf.szFaceName,(_T("Tahoma")));
	_cf=&cf;	
	}

	CFontDialog dlg;
	dlg.FillInLogFont(*_cf);
	CFont ffont;
	ffont.CreateFontIndirect(&dlg.m_lf);
	CFont *oldfont=(CFont*)hdc->SelectObject(&ffont);
	hdc->SetTextAlign(TA_BASELINE);
	hdc->SetBkMode(OPAQUE);//TRANSPARENT);
	hdc->SetBkColor(cf.crTextColor);
	hdc->SetTextColor(cf.crTextColor);
	CBrush brush;
	CBrush *ob;
	brush.CreateSolidBrush(cf.crTextColor);
	ob=hdc->SelectObject(&brush);
	LONG um=hdc->GetMapMode();

	hdc->DrawText(mtext,&rt,DT_CALCRECT|DT_TOP|DT_LEFT);
	hdc->DPtoLP(rt);
	CPoint por=p;
	rt.OffsetRect(por);
	rt.InflateRect(50,10);

	hdc->SelectObject(oldfont);
	hdc->SelectObject(ob);

//	rt.InvertRect();
	CPoint p1=rt.TopLeft();
	CPoint p3=rt.BottomRight();;
	CPoint p2=CPoint(p3.x,p1.y);
	CPoint p4=CPoint(p1.x,p3.y);
	CVector v1=p1;
	CVector v2=p2;
	CVector v3=p3;
	CVector v4=p4;
	float v1x=(v1.x<v3.x)?v1.x:v3.x;
	float v3x=(v1.x<v3.x)?v3.x:v1.x;
	float v1y=(v1.y>v3.y)?v1.y:v3.y;
	float v3y=(v1.y>v3.y)?v3.y:v1.y;
	v1.x=v1x;
	v1.y=v1y;
	v3.x=v3x;
	v3.y=v3y;
	
	CRectangle rc(v1,v3);
	rec=rc;
	rec.copy(&rc);
	getCharge();
	p1=CPoint(mesh.Vertex(1)->v)-CPoint(mesh.Vertex(0)->v);
	CVector v22(p1.x,p1.y,0);
	float ang=-argu(v22);
	CLine l2;
	l2.edge_on=true;
	l2.copy(this);
	l2.setRotateCenter(box.center());
	l2.rotate(ang,-1);
	CRect rt2= CRect(l2.getMesh()->Vector(0),l2.getMesh()->Vector(2));
	if(rich->m_hWnd==NULL){
		hdc->LPtoDP(rt2);
		
		rich->Create(ES_LEFT | ES_MULTILINE | ES_WANTRETURN | WS_VISIBLE | WS_BORDER | WS_OVERLAPPED | WS_CHILD, rt2, wd, ID_RICHT);
		rich->SetOptions(ECOOP_OR,ECO_AUTOWORDSELECTION);
		PARAFORMAT2 pf;
		pf.cbSize = sizeof(PARAFORMAT2);
		pf.dwMask=PFM_ALL2|PFM_ALL;
		pf.dxOffset=50;	
		CHARFORMAT cf;
		cf.cbSize=60;
		cf.dwMask=3892314127;
		cf.dwEffects=0;
		cf.yHeight=200;
		cf.yOffset=0;
		cf.crTextColor=0;
		cf.bPitchAndFamily='"';
		lstrcpy(cf.szFaceName,(_T("Tahoma")));
		rich->SetDefaultCharFormat(cf);
	
//		rich->MoveWindow(rt);
//		rich->SetFocus();
//		hdc->DrawText(mtext,rt,mtext.Count,0);


//		rich->RequestResize();
//		rich->Invalidate(TRUE);

		CPoint pyheight=CVector(cf.yHeight,0);
		CPoint pyheight1=CVector(0,0);
		pyheight=pyheight-pyheight1;
		curspos=CVector(cf.yHeight,0);
		u_prev=sqrt(pyheight.x*pyheight.x+pyheight.y+pyheight.y);

		rich->SetParaFormat(pf);
		hdc->DPtoLP(rt2);
	}
/*	CStdioFile f("C:\\Users\\sergedeh\\Documents\\testy.rtf",CFile::modeReadWrite);
	f.WriteString(mtext);
	CArchive ar(&f,1);
	EDITSTREAM es;
	es.dwCookie=0;
	es.dwError= 0;
	es.pfnCallback=EditStreamCallBack;
	_afxRichEditCookie cookie(ar);
	es.dwCookie = (DWORD)&cookie;
	rich->StreamIn(SF_RTF,es);
	rich->Invalidate();*/
	rich->SetSel(0,-1);
	rich->ReplaceSel(mtext);
//	rich->RequestResize();
	rich->ShowWindow(SW_HIDE);
	CCAM cam;
	z_prev=cam.getzoom();
	z_prev=1/z_prev;
//	draw(hdc);

/*	
	hdc->SelectObject(oldfont);
	box.add(CVector(rt.BottomRight()));
	box.add(CVector(rt.TopLeft()));

	rec = CRectangle(box.corner(0),box.corner(3));
	getCharge();
	setText(mtext,hdc);
*/
}

bool CTextCad::inRegion(CVector point)
{
/*	updatecore();
	CVector pr2=p2;
	pr2.y=p2.y-max(textmet.tmAscent,textmet.tmDescent);
	CVector r(p0,pr2);
	CVector pk=(p0+pr2)/2;


	if(absc(CVector(pk,point))<absc(CVector(pk,p0)))
	{
		return true;
	}

	return false;*/
	updatecore();//rec.updatecore();
	if(CLine::inRegion(point))
		return true;//rec.PtinRegion(point);
	point.z=box.max.z;
	if(box.containpts(point))
	{

		return true;
	}
	if(rich->m_hWnd!=NULL){
		rich->ShowWindow(SW_HIDE);
	}
	return false;

}

CFont* CTextCad::getFont()
{
	return pfont;
}

void CTextCad::updatecopy()
{
	is=stk.end()-1;

}

void CTextCad::setText(CString vtext,CDC* hdc)
{
	mtext=vtext;
	updatecore();
	CVector vr=box.corner(3);//rop.BottomRight();
//	vr.v2D();
	CVector vl=box.corner(0);//rop.TopLeft();
//	vl.v2D();

	//This vector is to shift the screen to start at the bottom left of the bounding box
	//The x represent the bottom of the screen while the y is the left side
	//(check the CVEctor content
	CVector vv2(vr.getscrb().x,vr.getscrtop().y);

	//We move from the left top of the bounding box to the origin of the world
	//Coordinate then from the origin of the screen coordinate to the new screen
	//starting at the top left of the bounding box
	CTVector vt;
	vt.VpushTransform();
	vt.VpushUnit();
	vt.VinitVect();
	vt.VendT();


	vt.pushTransform();
	vt.pushUnit();
//	vt.Translate(vl);//box.corner(0));
//	vt.Translate(vv2);
	vt.endT();



	CRect ro(vl,vr),rop;
	rop=ro;
	ro.NormalizeRect();
	CVector vv=box.size();
	CPoint pv=/*ro.Size();//*/box.size();
//	hdc->LPtoDP(&ro);
	CSize pvn=ro.Size();
//	hdc->LPtoDP(&pv);
//	hdc->LPtoDP(&pvn);
	
//	CDC *hmdc=new CDC;

//	hmdc->CreateCompatibleDC(hdc);
//	hmdc->SetMapMode(hdc->GetMapMode());

//	CBitmap* bmp=new CBitmap,*oldbmp;
//	bmp->CreateCompatibleBitmap(hdc,pvn.cx,pvn.cy);
//	oldbmp=(CBitmap*)hmdc->SelectObject(bmp);
	CBrush b;
	b.CreateSolidBrush(RGB(255,255,255));
	COLORREF rfb,rft;

	CVector vv1;
	vv1.getcamor();
	vv1.getcooro();


	hdc->SelectObject(b);//GetStockObject(GRAY_BRUSH));

	
	CRect rt(vl,vr),r2;
	r2=rt;
	r2.InflateRect(25,-25);
	CRectTracker rt1(r2,CRectTracker::hatchedBorder);
	CPoint pol=box.corner(0);
	rt.InflateRect (5,-5);
 	hdc->Rectangle(rt);
//	rt1.Draw(hmdc);



//	box.draw(hmdc);
	CPoint ng=vl;
//	vl.y=vr.y;
//	CVector vi=vl;	
	itmap j,j1;
	LOGFONT font;
	CVector vg2(1,1);
	CVector vg3=vg2;
	vg3.v3D();
	int hj=fmap.size();

    rt.InflateRect(-5,5);
	CFont *oldfont=(CFont*)hdc->SelectObject(pfont);
//	hmdc->GetGlyphOutline(
	hdc->DrawText(mtext,&rt,DT_WORDBREAK|DT_NOCLIP );
	hdc->SelectObject(oldfont);
			

	vt.popTransform();
	vt.VpopTransform();

//	hdc->BitBlt(rop.TopLeft().x,rop.TopLeft().y,rop.Size().cx,rop.Size().cy,hmdc,0,0,SRCCOPY);
//	bz.plane(&CRectangle(box.corner(0),box.corner(3)));
//	bz.UpdateTexture(hdc,bmp);
//	bz.surface(hdc);
//	bz.draw(hdc);
	rec = CRectangle(box.corner(0),box.corner(3));
	mesh.copy(rec.getMesh());
	edge_on = false;
//	setTexture("",hdc);
//	UpdateTexture(hdc,bmp);
	trans_col=0xFFFFFF;
//	closecurve(vg3,hdc);
//	hdc->SelectObject(oldbmp);


//	delete hmdc;

}

void CTextCad::edittext()
{
}

void CTextCad::editobj(CDC* hdc)
{
 CTextDi td;
 td.settext(mtext);
 if(td.DoModal()==IDOK)
 {
	 mtext=td.m_text;
	 setText(mtext,hdc);
 }

}
void CTextCad::editobj(CVector point)
{
	if(inRegion(point))
	{
 	if(rich->m_hWnd!=NULL){
		rich->ShowWindow(SW_SHOW);
		rich->SetFocus();
		rich->Invalidate();
	}
	}

}


void CTextCad::Serialize(CArchive& ar)
	// Read and write CTextCad object to archive, with length prefix.
{
	ASSERT(rich->m_hWnd != NULL);
	Stream(ar, FALSE);
}

void CTextCad::Stream(CArchive& ar, BOOL bSelection)
{

	EDITSTREAM es;
	es.dwCookie=0;
	es.dwError= 0;
	//es.pfnCallback = EditStreamCallBack; error:return 0 for no error, otherwise return none.
	_afxRichEditCookie cookie(ar);
	es.dwCookie = (DWORD)&cookie;
	int nFormat = SF_RTF;// GetDocument()->GetStreamFormat();
	if (bSelection)
		nFormat |= SFF_SELECTION;
	if (ar.IsStoring())
		rich->StreamOut(nFormat, es);
	else
	{
		rich->StreamIn(nFormat, es);
		rich->Invalidate();
	}
	if (cookie.m_dwError != 0)
		AfxThrowFileException(cookie.m_dwError);
}



CFigure* CTextCad::generateCopy()
{
   CTextCad* m = new CTextCad;
   m->rec.copy(&rec);
   m->mesh.copy(mesh);

	CRect* rt2= new CRect(mesh.Vector(0),mesh.Vector(2));
	if(rich->m_hWnd)
	{
	rich->GetRect(rt2);
//	hdc->LPtoDP(rt2);

	m->rich->Create(ES_LEFT|ES_MULTILINE|ES_WANTRETURN|WS_VISIBLE|WS_BORDER|WS_OVERLAPPED|WS_CHILD,*rt2,wd,ID_RICHT);
	m->rich->SetOptions(ECOOP_OR,ECO_AUTOWORDSELECTION);
	PARAFORMAT pf;
	rich->GetParaFormat(pf);
	m->rich->SetParaFormat(pf);
	CHARFORMAT cf;
	rich->GetDefaultCharFormat(cf);
	m->rich->SetDefaultCharFormat(cf);

	rich->SetSel(0,-1);
	CString ci=rich->GetSelText();
	m->rich->ReplaceSel(ci);
	int length=ci.GetLength();
	for(int i=0;i<length;i++)
	{
		rich->SetSel(i,i+1);
		rich->GetSelectionCharFormat(cf);
		m->rich->SetSel(i,i+1);
		m->rich->SetSelectionCharFormat(cf);
	}
	m->rich->ShowWindow(SW_HIDE);
	}
   m->alpha = alpha;
   m->curspos=curspos;
   m->u_prev=u_prev;
//   m->rec.copy(&rec);
   m->copy(this);
   return m;
}

void CTextCad::assign(CDC *hdc, CVector p)
{
 CTextDi td;
 td.settext(mtext);
 if(td.DoModal()==IDOK)
 {
	 mtext=td.m_text;
	 assign(hdc,p,mtext);
 }

}
void CTextCad::InitZoom()
{
	z_prev=-1;
}
void CTextCad::setWnd(CWnd *cad)
{
  wd=cad;
}
