// TextCad.cpp: implementation of the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "TextCad.h"
#include "bezier.h"
#include "textdi.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextCad::CTextCad()
{
	name="CTextCad";
	rec.setdistprec(5);
	pfont=new CFont;
	nNumPts=-1;
//	CFont gf;
//	pfont->CreateStockObject(ANSI_VAR_FONT);
	liter=0;
//	gf.GetLogFont(pfont);
		
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

	iter=0;
	sbiter=seiter=0;
	fPrevB=false;
	selmode=false;
	lcolor=RGB(0,0,0);
	str=new CString;
	lpPoints=NULL;
    lpTypes=NULL;
}
CTextCad::CTextCad(CFile &file)
{
	name="CTextCad";
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
	selmode=false;
	lcolor=RGB(0,0,0);

	openfile(file);

}

CTextCad::~CTextCad()
{
	delete str;
	delete pfont;
  // Release the memory we used
	if(lpPoints!=NULL)
	{
	   delete [] lpPoints;
	   delete [] lpTypes;
	 }

}



CRectangle* CTextCad::getRectangle()
{
	return &rec;

}

bool CTextCad::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	return true;//rec.draw(fPrevLine,hdc,point);
}

void CTextCad::draw(CDC *hdc)
{
	CBezier::draw(hdc);
//	PolyDraw(hdc);
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

	return true;
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
	iter=0;
	fPrevB=false;
	selmode=false;
}


void CTextCad::create(CVector pos)
{
	rec.create(pos);

}


CPoint CTextCad::setfont(CDC *hdc,LOGFONT font,COLORREF ccl)
{
	bool b=false;
	CFont *oldf;
/*	CFont* h;
	int k,j;
	if(sbiter!=seiter)
	{
	b=true;
	h=new CFont;
	h->CreateFontIndirect(&font);
	oldf=(CFont*)hdc->SelectObject(h);
	k=seiter;
	j=sbiter;
	j=seiter>sbiter?sbiter:seiter;
	k=seiter>sbiter?seiter:sbiter;
	for(int l=j;l<k;l++)
	{
		ltext[l].f=h;
	}
	}
	else
		{*/
		delete pfont;
		pfont=new CFont;
		pfont->CreateFontIndirect(&font);
		oldf=(CFont*)hdc->SelectObject(pfont);
		setText(mtext,hdc);
/*		}


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
		fmap.insert(make_pair(h,m));

	hdc->SelectObject(oldf);
	if(b) 
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
	CFont *oldfont=(CFont*)hdc->SelectObject(pfont);
	CRect rt;
	rt.SetRectEmpty();
	rt.OffsetRect(p);
	hdc->DrawText(mtext,&rt,DT_CALCRECT);
	hdc->SelectObject(oldfont);
	box.add(CVector(rt.BottomRight()));
	box.add(CVector(rt.TopLeft()));
	setText(mtext,hdc);

}
/*
bool CTextCad::inRegion(CVector point)
{
	updatecore();
	CVector pr2=p2;
	pr2.y=p2.y-max(textmet.tmAscent,textmet.tmDescent);
	CVector r(p0,pr2);
	CVector pk=(p0+pr2)/2;


	if(absc(CVector(pk,point))<absc(CVector(pk,p0)))
	{
		return true;
	}

	return false;
}
*/
CFont* CTextCad::getFont()
{
	return pfont;
}

void CTextCad::updatecopy()
{
//	is=stk.end()-1;

}

void CTextCad::setText(CString vtext,CDC* hdc)
{

	CRect cr;
	cr.SetRectEmpty();
	CFont *oldfont=(CFont*)hdc->SelectObject(pfont);
	hdc->SetBkMode(TRANSPARENT);
	CString ht=vtext+"\n";
	hdc->DrawText(ht,&cr,DT_CALCRECT);
	hdc->SelectObject(oldfont);
	mtext=vtext;
	
	CVector vr=box.corner(3);//rop.BottomRight();
	vr.v2D();
	CVector vl=box.corner(0);//rop.TopLeft();
	vl.v2D();

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
	vt.Translate(vl);//box.corner(0));
	vt.Translate(vv2);
	vt.endT();



	CRect ro(vl,vr),rop;
	rop=ro;
	cr.NormalizeRect();
	//ro.NormalizeRect();
	CVector vv=box.size();
	CPoint pv=/*ro.Size();//*/box.size();
//	hdc->LPtoDP(&ro);
	CSize pvn=cr.Size();
	hdc->LPtoDP(&pv);
	hdc->LPtoDP(&pvn);
	
	CDC *hmdc=new CDC;

	hmdc->CreateCompatibleDC(hdc);
	hmdc->SetMapMode(hdc->GetMapMode());

	CBitmap* bmp=new CBitmap,*oldbmp;
	bmp->CreateCompatibleBitmap(hdc,pvn.cx,pvn.cy);
	oldbmp=(CBitmap*)hmdc->SelectObject(bmp);
	CBrush b;
	b.CreateSolidBrush(RGB(255,255,255));
	COLORREF rfb,rft;

	CVector vv1;
	vv1.getcamor();
	vv1.getcooro();


	hmdc->SelectObject(b);//GetStockObject(GRAY_BRUSH));

	
	CRect rt(vl,vr),r2;
	r2=cr;
	r2.InflateRect(5,5);
	CRectTracker rt1(r2,CRectTracker::hatchedBorder);
	CPoint pol=box.corner(0);
 	hmdc->Rectangle(r2);
//	rt1.Draw(hmdc);



//	box.draw(hmdc);
	CPoint ng=vl;
//	vl.y=vr.y;
//	CVector vi=vl;	
//	itmap j,j1;
	LOGFONT font;
	CVector vg2(1,1);
	CVector vg3=vg2;
	vg3.v3D();
//	int hj=fmap.size();


	oldfont=(CFont*)hmdc->SelectObject(pfont);
	hmdc->SetBkMode(TRANSPARENT);
	hmdc->DrawText(mtext,&rt,DT_NOCLIP );
	hmdc->SelectObject(oldfont);
			

	vt.popTransform();
	vt.VpopTransform();

//	hdc->BitBlt(rop.TopLeft().x,rop.TopLeft().y,rop.Size().cx,rop.Size().cy,hmdc,0,0,SRCCOPY);
	cr.OffsetRect(box.corner(0));
	plane(cr.TopLeft(),cr.BottomRight());//box.corner(0),box.corner(3));
	UpdateTexture(hdc,bmp);
	surf=false;
	surface(hdc);
	draw(hdc);
	hmdc->SelectObject(oldbmp);


	delete hmdc;

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

// This OnDraw() implementation uses GDI paths to draw the outline of
// some text in a TrueType font. The path is used to record the way
// the TrueType font would be drawn. Then, the function uses the data
// returned from CDC::GetPath() to draw the font--without filling it.

void CTextCad::setText1(CString vtext,CDC* pDC)
{
   // Describe a 24-point truetype font of normal weight
/*   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));
   lf.lfHeight = -MulDiv(24, pDC->GetDeviceCaps(LOGPIXELSY), 72);
   lf.lfWeight = FW_NORMAL;
   lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
*/
   // create and select it
/*   CFont newFont;
   if (!newFont.CreateFontIndirect(&lf))
      return;
   CFont* pOldFont = pDC->SelectObject(&newFont);
*/
	mtext=vtext;
   CFont *oldfont=(CFont*)pDC->SelectObject(pfont);
   CPoint p=box.corner(0);
	CVector vr=box.corner(3);//rop.BottomRight();
	CVector vl=box.corner(0);//rop.TopLeft();
	CRect rt(vl,vr);
   // use a path to record how the text was drawn
   pDC->SetBkMode(TRANSPARENT);
   pDC->BeginPath();
   pDC->DrawText(vtext,&rt,NULL);//TextOut(p.x, p.y, vtext);
   pDC->EndPath();

   // Find out how many points are in the path. Note that
   // for long strings or complex fonts, this number might be
   // gigantic!
   nNumPts = pDC->GetPath(NULL, NULL, 0);
   if (nNumPts == 0)
      return;

   // Allocate memory to hold points and stroke types from
   // the path.
   if(lpPoints!=NULL) delete [] lpPoints;
   lpPoints = new POINT[nNumPts];
   if (lpPoints == NULL)
      return;
   if(lpTypes!=NULL) delete [] lpTypes;
   lpTypes = new BYTE[nNumPts];
   if (lpTypes == NULL)
   {
      delete [] lpPoints;
      return;
   }

   // Now that we have the memory, really get the path data.
   nNumPts = pDC->GetPath(lpPoints, lpTypes, nNumPts);
   ptbegin.clear();
   int state=0;
   for(int i=0;i<nNumPts;i++)
   {
	   ptbegin.push_back(CPoint(lpPoints[i]));
   }
	ptend=ptbegin;
	updatecore();
   // If it worked, draw the lines. Win95 and Win98 don't support
   // the PolyDraw API, so we use our own member function to do
   // similar work. If you're targeting only Windows NT, you can
   // use the PolyDraw() API and avoid the COutlineView::PolyDraw()
   // member function.

//   if (nNumPts != -1)
//      PolyDraw(pDC);

 
   // Put back the old font
   pDC->SelectObject(oldfont);

   return;
}

void CTextCad::PolyDraw(CDC* pDC)
{
	if(nNumPts==-1) return;
   int nIndex;
   CPoint* pptLastMoveTo = NULL;
   CPoint* p=new CPoint[nNumPts];
   for(int i=0;i<nNumPts;i++)
   {
	  p[i]= ptbegin[i];
   }
	CVector vr=box.corner(3);//rop.BottomRight();
	CVector vl=box.corner(0);//rop.TopLeft();
	CRect rt(vl,vr);


	pDC->BeginPath();
	i=0;
   // for each of the points we have...
   for (nIndex = 0; nIndex < nNumPts; nIndex++)
   {
      switch(lpTypes[nIndex])
      {
      // React to information from the path by drawing the data
      // we received. For each of the points, record our own
      // "last active point" so we can close figures, lines, and
      // Beziers.

      case PT_MOVETO:
         if (pptLastMoveTo != NULL && nIndex > 0)
            pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
         pDC->MoveTo(p[nIndex].x, p[nIndex].y);
         pptLastMoveTo = &p[nIndex];
         break;

      case PT_LINETO | PT_CLOSEFIGURE:
         pDC->LineTo(p[nIndex].x, p[nIndex].y);
         if (pptLastMoveTo != NULL)
            pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
         pptLastMoveTo = NULL;
         break;

      case PT_LINETO:
         pDC->LineTo(p[nIndex].x, p[nIndex].y);
         break;

      case PT_BEZIERTO | PT_CLOSEFIGURE:
         ASSERT(nIndex + 2 <= nNumPts);
         pDC->PolyBezierTo(&p[nIndex], 3);
         nIndex += 2;
         if (pptLastMoveTo != NULL)
            pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
         pptLastMoveTo = NULL;
         break;

      case PT_BEZIERTO:
         ASSERT(nIndex + 2 <= nNumPts);
         pDC->PolyBezierTo(&p[nIndex], 3);
         nIndex += 2;
         break;
      }
   }

   // If the figure was never closed and should be,
   // close it now.
   if (pptLastMoveTo != NULL && nIndex > 1)
      pDC->LineTo(pptLastMoveTo->x, pptLastMoveTo->y);
   delete [] p;
   pDC->EndPath();
   // Just say "no" to outlines       
   HBRUSH hBrush =(HBRUSH) SelectObject(pDC->GetSafeHdc(), GetStockObject(BLACK_BRUSH)); 
   // Paint It Black          
   pDC->StrokeAndFillPath();
   // Restore the DC to its previous state
   SelectObject(pDC->GetSafeHdc(), hBrush); 
}

void CTextCad::drawselect(CDC *hdc)
{

	if((!getLibstatus())||(!getMultselect()))
	{
	updatecore();	
	box.draw(hdc);
	pitere=ptend.begin();
	int old=hdc->SetROP2(R2_NOTXORPEN);    			
	
	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	box.draw(hdc);

	hdc->SetROP2(old);    			
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);
	}

}
