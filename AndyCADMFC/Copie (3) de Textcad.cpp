// TextCad.cpp: implementation of the CTextCad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "TextCad.h"

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

	CFont gf;
	gf.CreateStockObject(ANSI_VAR_FONT);
	gf.GetLogFont(&pfont);
	TCHAR nd[32]="Times New Roman";
	
	pfont.lfOrientation=0;
	pfont.lfCharSet=ANSI_CHARSET;
	pfont.lfClipPrecision=CLIP_LH_ANGLES;
	pfont.lfEscapement=0;
	strcpy(pfont.lfFaceName,"Time New Roman");
	pfont.lfHeight=-16;
	pfont.lfItalic=FALSE;
	pfont.lfOutPrecision=OUT_TT_PRECIS;
	pfont.lfPitchAndFamily=FF_ROMAN|DEFAULT_PITCH;
	pfont.lfQuality=DEFAULT_QUALITY;
	pfont.lfStrikeOut=FALSE;
	pfont.lfUnderline=FALSE;
	pfont.lfWeight=FW_NORMAL;
	pfont.lfWidth=0;

	iter=vecpos.end()-1;
	titer=vectext.end()-1;
	liter=vlpos.end()-1;
	fPrevB=false;
	curspos.yhit=0;
	selmode=false;
	lcolor=RGB(0,0,0);
	str=new CString;
}
CTextCad::CTextCad(CFile &file)
{
	name="CTextCad";
	rec.setdistprec(5);

	CFont gf;
	gf.CreateStockObject(ANSI_VAR_FONT);
	gf.GetLogFont(&pfont);
	TCHAR nd[32]="Times New Roman";
	
	pfont.lfOrientation=0;
	pfont.lfCharSet=ANSI_CHARSET;
	pfont.lfClipPrecision=CLIP_LH_ANGLES;
	pfont.lfEscapement=0;
	strcpy(pfont.lfFaceName,"Time New Roman");
	pfont.lfHeight=-16;
	pfont.lfItalic=FALSE;
	pfont.lfOutPrecision=OUT_TT_PRECIS;
	pfont.lfPitchAndFamily=FF_ROMAN|DEFAULT_PITCH;
	pfont.lfQuality=DEFAULT_QUALITY;
	pfont.lfStrikeOut=FALSE;
	pfont.lfUnderline=FALSE;
	pfont.lfWeight=FW_NORMAL;
	pfont.lfWidth=0;

	fPrevB=false;
	curspos.yhit=0;
	selmode=false;
	lcolor=RGB(0,0,0);

	openfile(file);
}

CTextCad::~CTextCad()
{
	delete str;

}



CRectangle* CTextCad::getRectangle()
{
	return &rec;

}

bool CTextCad::draw(bool fPrevLine, CDC *hdc, CVector point)
{
	return true;//rec.draw(fPrevLine,hdc,point);
}

void CTextCad::setPtsBegin(CVector point)
{
	rec.setPtsBegin(point);

}

bool CTextCad::getCharge()
{
	bool b=rec.getCharge();
//	ptbegin=rec.ptbegin;
//	ptend=rec.ptend;
	return true;
}

void CTextCad::FillText()
{


}

void CTextCad::setMove(bool b, CVector point)
{
//`	rec.setMove(b,point);

}

void CTextCad::initL()
{
	rec.initL();
	ptbegin.clear();
	ptend.clear();
	vecpos.clear();
	vectext.clear();
	vlpos.clear();
	iter=vecpos.end()-1;
	biter=vecpos.begin();
	titer=vectext.end()-1;
	liter=vlpos.end()-1;
	fPrevB=false;
	curspos.yhit=0;
	selmode=false;
	stk.push_back(str);
//	stk.push_back(str);
	is=stk.begin();
}

void CTextCad::getTextrec(CWnd* wnd,CDC *hdc)
{
//	setgline(false,false);
	wnd->CreateSolidCaret(1,15);
	CPoint pp=rec.ptbegin[0];//(rec.ptbegin[0].x/*+rec.getdistprec()*/,rec.ptbegin[0].y/*+rec.getdistprec()+1*/);
	curspos=rec.ptbegin[0];
	curspos.yhit=0;
	if(iter+1!=vecpos.end())
	{
	iter=vecpos.insert(iter+1,curspos);
//	iter++;
	}
	else
	{
		iter=vecpos.insert(iter+1,curspos);
//		iter++;
	}
	ssiter=iter;
	seiter=iter;
	ptbegin.push_back(curspos);
	ptend.push_back(curspos);
	updatecore();

	hdc->LPtoDP(&pp);
	rec.setdistprec(10);
	wnd->SetCaretPos(pp);
	wnd->ShowCaret();
//	iter=vecpos.begin();

/*	CRect mfcrec(rec.ptbegin[0],rec.ptbegin[2]);
	hdc->LPtoDP(mfcrec);
	return mfcrec;
*/
}

void CTextCad::create(CVector pos)
{
	rec.create(pos);

}

CPoint CTextCad::drawtext(CDC *hdc, UINT nchar)
{

	CFont ft;
	ft.CreateFontIndirect(&pfont);
	CFont *oldfont=hdc->SelectObject(&ft);
	text ptext;
	ptext.start=false;
	rec.setdistprec(5);


		vector<CVector>::size_type sts=ssiter-vecpos.begin();
		vector<CVector>::size_type ste=seiter-vecpos.begin();
		if(ssiter!=seiter)
		{ 
			if(sts<ste)
			{
			(*is)->Delete(sts,ste-sts);
			iter=ssiter;
			seiter=ssiter;
			}
			else
			{
			(*is)->Delete(ste,sts-ste);
			iter=seiter;
			ssiter=seiter;
			}
			vecpos.erase(vecpos.end()-abs(sts-ste),vecpos.end());
			curspos=*iter;
			vector<CVector>::iterator pib=vecpos.begin()+1;
			CString st;
			for(int i=0;i<(*is)->GetLength();i++)
			{
				CSize cs=hdc->GetTextExtent((*is)->Left(i+1));//[i]);
				if(pib->y==(pib-1)->y)
				{
				CPoint pu=*vecpos.begin();//*iter;
				pu.x+=cs.cx;CVector v=pu;
				pib->x=v.x;//(pib-1)->x+cs.cx;
				}

			
			
/*				if(pib->y==(pib-1)->y)
				{
				st+=str[i];
				CSize cs=hdc->GetTextExtent(st);//r[i]);
				pib->x=(pib-1)->x+cs.cx-textmet.tmOverhang;
				}
*/				pib++;
			}


		}



	vector<CVector>::size_type st;//=iter-vecpos.begin();

	for(vector<CVector>::iterator pib=vecpos.begin();pib<vecpos.end();pib++)
	{
	   if(pib->y==iter->y)
	   {
			st=iter-pib;
			biter=pib;
			break;
	   }
	}
	

	int s1;
	int s2;


	(*is)->Insert(st,nchar);
	CVector b=*biter;
	CVector b1=*biter;
	CPoint pu=*biter;//*iter;
//	hdc->TextOut(pu.x,pu.y,*(*is));//pu.x,pu.y,nchar);
	pu.x+=hdc->GetTextExtent((*is)->Left(st+1)).cx;
	CVector bo=pu;
	b.x=bo.x;
	iter=vecpos.insert(iter+1,b);
	

	int ncbuf;
	ABCFLOAT bb;
	hdc->GetCharWidth(nchar,nchar,&ncbuf);
	hdc->GetCharABCWidths(nchar,nchar,&bb);
	hdc->GetOutputTextMetrics(&textmet); 
	CSize cs=hdc->GetTextExtent(*(*is));
	

	curspos=pu;


	if(iter!=vecpos.end()-1)
	{
	if(iter->y!=(iter-1)->y)
	{
		for(vector<CVector>::iterator pib=iter+1;pib<vecpos.end();pib++)
		{
				pib->x-=(iter->x-pib->x);
		}
	}

	}
	pib=iter;
	if(iter!=vecpos.end()-1)
	{
			for(int i=st;i<(*is)->GetLength();i++)
			{
				CSize cs=hdc->GetTextExtent((*is)->Left(i+1));//[i]);
				if(pib->y==(pib-1)->y)
				{
				CPoint pu=b1;
				pu.x+=cs.cx;CVector v=pu;
				pib->x=v.x;
				
				}
				else
				{
					break;
				}
				pib++;
			}
	}


	ptbegin.clear();
	ptend.clear();

	for(vector<CVector>::iterator pit=vecpos.begin();pit<vecpos.end();pit++)
	{
		ptbegin.push_back(*pit);
		ptend.push_back(*pit);
	}

	updatecore();
	CPoint pp;
	pp=*iter;
	hdc->LPtoDP(&pp);
	ft.DeleteObject();	
	hdc->SelectObject(oldfont);

	return pp;
}

CPoint CTextCad::deleteback(CDC *hdc)
{

	if(iter>vecpos.begin())
	{
//		vector<CVector>::size_type st;//=iter-1-vecpos.begin();
		CFont ft;
		ft.CreateFontIndirect(&pfont);
		CFont *oldfont=hdc->SelectObject(&ft);

    	vector<CVector>::size_type sts=ssiter-vecpos.begin();
		vector<CVector>::size_type ste=seiter-vecpos.begin();

		vector<CVector>::iterator eiter;
		
		size_t st;

		for(vector<CVector>::iterator pib=vecpos.begin();pib<vecpos.end();pib++)
		{
		   if(pib->y==iter->y)
		   {
				st=iter-pib-1;
				biter=pib;
				eiter=biter+(*is)->GetLength();
				break;
		   }
		}


		if(ssiter==seiter)
		{
			if(iter!=biter)
			{
			(*is)->Delete(st);
			iter=vecpos.erase(iter);

			hdc->GetOutputTextMetrics(&textmet); 
			vector<CVector>::iterator pib=iter,ppib=iter;//vecpos.begin()+1;
			CVector ppb=*iter;

				for(int i=st;i<(*is)->GetLength();i++)
				{
					CSize cs=hdc->GetTextExtent((*is)->Left(i+1));
					if(pib->y==(pib-1)->y)
					{
					CPoint pu=*biter;
					pu.x+=cs.cx;CVector v=pu;
					pib->x=v.x;
					
					}
					else
					{
						break;
					}
					pib++;
				}
				iter--;
			}else
			{
				vecpos.erase(biter);
//				biter-=((*(is-1))->GetLength()-2);
				**(is-1)+=**is;
				is--;
				stk.erase(is+1);

				for(vector<CVector>::iterator ib=vecpos.begin();ib<vecpos.end();ib++)
				{
				   if(ib->y==(biter-1)->y)
				   {
						biter=ib;
						break;
				   }
				}



				vector<CVector>::iterator ptiter=biter;
				vector<CVector>::iterator pib=biter+1;
				for(vector<CString*>::iterator j=is;j<stk.end();j++)
				{
					for(int i=0;i<(*j)->GetLength();i++)
					{
						*pib=*biter;
						CSize cs=hdc->GetTextExtent((*j)->Left(i+1));//str[i]);
						CPoint pu=*ptiter;//*iter;
						pu.x+=cs.cx;CVector v=pu;
						pib->x=v.x;//(pib-1)->x+cs.cx;
					pib++;
					}
//					*pib=*(pib-1);
					biter+=((*j)->GetLength()+1);
                    biter->y+=max(textmet.tmAscent,textmet.tmDescent);
					*pib=*biter;
					pib++;
//					pib=ptiter+1;
				}
			iter--;
			}
	//	}
/*				if((ppb.y+max(textmet.tmAscent,textmet.tmDescent))==pib->y)
				{
				CSize cs=hdc->GetTextExtent(str[i]);
				pib->y=(pib-1)->y;
				pib->x=(pib-1)->x+cs.cx-textmet.tmOverhang;
				}
					else
				{
				pib->y-=max(textmet.tmAscent,textmet.tmDescent);
				}
			pib++;
			}*/
		}
		else
		{
			if(sts<ste)
			{
			(*is)->Delete(sts-1,ste-sts+1);
			iter=ssiter;
			}
			else
			{
			(*is)->Delete(ste-1,sts-ste+1);
			iter=seiter;
			}
			vecpos.erase(vecpos.end()-abs(sts-ste)-1,vecpos.end());
			ssiter=iter;
			seiter=iter;

		}

//	iter--;

	
/*	hdc->GetOutputTextMetrics(&textmet); 
		pib=biter+1;

		for(int i=0;i<(*is)->GetLength();i++)
		{
			CSize cs=hdc->GetTextExtent((*is)->Left(i+1));
			if(pib->y==(pib-1)->y)
			{
//			CSize cs=hdc->GetTextExtent(str[i]);
//			pib->x=(pib-1)->x+cs.cx-textmet.tmOverhang;
			CPoint pu=*vecpos.begin();//*iter;
			pu.x+=cs.cx;CVector v=pu;
			pib->x=v.x;//(pib-1)->x+cs.cx;
			}
			pib++;
		}
*/
	ptbegin.clear();
	ptend.clear();


	for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
	{
		ptbegin.push_back(*vpit);
		ptend.push_back(*vpit);
	}
	updatecore();
	hdc->SelectObject(oldfont);
	}
	CPoint pp;
	pp=*iter;
	curspos=*iter;
	hdc->LPtoDP(&pp);
	return pp;

}

CPoint CTextCad::entertext(CDC *hdc)
{
	CFont ft;
	ft.CreateFontIndirect(&pfont);
	CFont *oldfont=hdc->SelectObject(&ft);
//	CString g;
//	stk.push_back(g);

	hdc->GetOutputTextMetrics(&textmet); 
/*	curspos.yhit++;
	drawtext(hdc,32);
	vector<CVector*> vpos;

	   for(vector<CVector>::iterator pib=iter;pib>=vecpos.begin();pib--)
		{
		   if(pib->y==iter->y)
		   {
			   vpos.push_back(iter);
		   }
		   else
		   {
			   liter=vlpos.insert(liter+1,vpos);

		   }
		}

//	vlpos.push_back(vecpos);

	CVector ct=*iter;
	ssiter=iter;
	seiter=iter;

	   for(pib=iter;pib<vecpos.end();pib++)
		{
		   if(pib->y==ct.y)
		   {
				pib->x=vecpos.front().x+abs(ct.x-pib->x);
		   }
				pib->y-=max(textmet.tmAscent,textmet.tmDescent);
		}

	curspos.x=iter->x;
	curspos.y=iter->y;
	ptbegin.clear();
	ptend.clear();

	for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
	{
		ptbegin.push_back(*vpit);
		ptend.push_back(*vpit);
	}

	updatecore();
	CPoint pp;
	pp=*iter;
	hdc->LPtoDP(&pp);*/

	CString* g=new CString;
	if(is==stk.end()-1)
	{
		is=stk.insert(is+1,g);
//		is++;
	}
	else
	{
		is=stk.insert(is+1,g);
//		(*is)->Insert((*is)->GetLength(),"\n");
	}

	CVector ct=*iter;
	ssiter=iter;
	seiter=iter;
	size_t ht;

   for(vector<CVector>::iterator pib=vecpos.begin();pib<vecpos.end();pib++)
	{
	   if(pib->y==iter->y)
	   {
			ht=iter-pib;
			break;
	   }
	}

	bool c=false;
		
	iter=vecpos.insert(iter+1,*iter);
	
	   for(pib=iter;pib<vecpos.end();pib++)
		{
		   if(pib->y==ct.y)
		   {
				pib->x=vecpos.front().x+abs(ct.x-pib->x);
				c=true;
		   }
		   CPoint p(0,max(textmet.tmAscent,textmet.tmDescent));
//		   CPoint po(0,0);
		   CVector v=p;
		   pib->y+=max(textmet.tmAscent,textmet.tmDescent);
		}
	   if(c)
	   {
	   CString sh=(*(is-1))->Right((*(is-1))->GetLength()-ht);
	   (*(is-1))->Delete(ht,sh.GetLength());
	   (*is)->Insert(0,sh);
	   biter+=ht;
	   }

	curspos=*iter;
	ptbegin.clear();
	ptend.clear();

	for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
	{
		ptbegin.push_back(*vpit);
		ptend.push_back(*vpit);
	}
	CPoint pp=*iter;
	hdc->SelectObject(oldfont);
	return pp;

}

CPoint CTextCad::kbmovecurs(CDC *hdc,CString& d)
{
	
	if(d=="left")
		{
			CVector precv=*iter;
			if(iter>vecpos.begin())
			{
				iter--;
				if(precv.y!=iter->y) is--;
			}
			titer--;
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}
			if(precv.y>iter->y)
			{
				liter++;
			}
			else
			if(precv.y<iter->y)
			{
				liter--;
			}
			
		}
	else
	if(d=="right")
		{
			CVector precv=*iter;
			if(iter<vecpos.end()-1)
			{
				iter++;
				if(precv.y!=iter->y) is++;
			}
			titer++;
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}
			if(precv.y>iter->y)
			{
				liter++;
			}
			else
			if(precv.y<iter->y)
			{
				liter--;
			}
		}
	else
	if(d=="end")
		{
			vector<CVector>::iterator piter=iter;
			piter=vecpos.end()-1;
			iter =piter;
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}
//			titer =piter;
		}
	else
	if(d=="home")
		{
			vector<CVector>::iterator piter=iter;
			piter=vecpos.begin();
			iter =piter;
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}
		//	titer =piter;
		}
	else
	if(d=="up")
		{
		liter--;
			for(vector<CVector>::iterator piter=iter;piter>=vecpos.begin();piter--)
			{
				if((piter->x<=iter->x)&&(piter->y!=iter->y))
				{
					iter=piter;
					is--;
					break;
				}
			}
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}

		}
	else
	if(d=="down")
		{
		liter++;
		 double yh=iter->y;
		 double xh=iter->x;
			for(vector<CVector>::iterator piter=iter;piter<vecpos.end();piter++)
			{
				if((piter->x<=xh)&&(piter->y==yh+max(textmet.tmAscent,textmet.tmDescent)))
				{
					iter=piter;
					is++;
			//		break;
				}
			}
			if(selmode)
			{
				seiter=iter;
			}
			else
			{
			ssiter=iter;
			seiter=iter;
			}
			
		}
	else
	if(d=="selStart")
		{
			ssiter=iter;
			seiter=iter;
			selmode=true;
		}
	else
	if(d=="selStop")
		{
			selmode=false;
		}
	else
	if(d=="delete")
		{
		CFont ft;
		ft.CreateFontIndirect(&pfont);
		CFont *oldfont=hdc->SelectObject(&ft);

		vector<CVector>::size_type sts=ssiter-vecpos.begin();
		vector<CVector>::size_type ste=seiter-vecpos.begin();
		vector<CVector>::iterator eiter;
		
		size_t st;

		for(vector<CVector>::iterator pib=vecpos.begin();pib<vecpos.end();pib++)
		{
		   if(pib->y==iter->y)
		   {
				st=iter-pib;
				biter=pib;
				eiter=biter+(*is)->GetLength();
				break;
		   }
		}
		
	//	liter->
		if(ssiter==seiter)
		{
			if(iter!=eiter)
			{
			(*is)->Delete(st);
			double sx;
			bool p=false;
				if(iter->x==biter->x)
				{
				sx=(iter)->x;
				p=true;
				}                                                                                                                          
				vecpos.erase(eiter);
				if(((iter+1)->x==biter->x)&&(iter->x==biter->x)&&(vecpos.size()!=1))
				{
				iter--;
				}
				else
				if((iter->x==biter->x)&&(iter!=biter))
				{
				iter--;
				}
				else
				if(p)
				{
				iter->x=sx;
				}
				else
				{
				//iter--;
				}

			hdc->GetOutputTextMetrics(&textmet); 
			vector<CVector>::iterator ptiter=biter;
			vector<CVector>::iterator pib=biter+1,ppib=iter+1;//vecpos.begin()+1;
			CVector ppb=*(iter+1);

/*				if(pib->y!=(pib+1)->y)
				{
					pib=pib+1;
					if (st==0) st=1;
					
					for(int i=st-1;i<(*is)->GetLength();i++)
					{
						CSize cs=hdc->GetTextExtent((*is)->Left(i+1));//str[i]);
						pib->y-=max(textmet.tmAscent,textmet.tmDescent);
					
						if(pib->y==ppib->y)
						{
	//						pib->x=(pib-1)->x+cs.cx;//-textmet.tmOverhang;
							CPoint pu=*biter;//*iter;
							pu.x+=cs.cx;CVector v=pu;
							pib->x=v.x;//(pib-1)->x+cs.cx;
						}
						pib++;
					}
				}
				else
				{
	*/			
					for(int i=0;i<(*is)->GetLength();i++)
					{
						if(pib->y==(pib-1)->y)
						{

							CSize cs=hdc->GetTextExtent((*is)->Left(i+1));//str[i]);
							CPoint pu=*ptiter;
							pu.x+=cs.cx;CVector v=pu;
							pib->x=v.x;
						}
						else
						{
							break;
						}
						pib++;
					}
//					iter--;
//				}
			}
			else
			{
				vecpos.erase(eiter+1);
				**is+=**(is+1);
				stk.erase(is+1);

				vector<CVector>::iterator ptiter=biter;
				vector<CVector>::iterator pib=biter+1;
				for(vector<CString*>::iterator j=is;j<stk.end();j++)
				{
					for(int i=0;i<(*j)->GetLength();i++)
					{
						*pib=*ptiter;
						CSize cs=hdc->GetTextExtent((*j)->Left(i+1));//str[i]);
						CPoint pu=*ptiter;//*iter;
						pu.x+=cs.cx;CVector v=pu;
						pib->x=v.x;//(pib-1)->x+cs.cx;
					pib++;
					}
//					*pib=*(pib-1);
					ptiter+=((*j)->GetLength()+1);
                    ptiter->y-=max(textmet.tmAscent,textmet.tmDescent);
					*pib=*ptiter;
					pib++;
//					pib=ptiter+1;
				}



			}
		}
		else
		{
			if(sts<ste)
			{
			(*is)->Delete(sts,ste-sts);
			iter=ssiter;
			}
			else
			{
			(*is)->Delete(ste,sts-ste);
			iter=seiter;
			}
			vecpos.erase(vecpos.end()-abs(sts-ste),vecpos.end());
			ssiter=iter;
			seiter=iter;

		}
/*	if(iter->x==vecpos.begin()->x)
	{
		if((iter+1)->x==vecpos.begin()->x)
		{
			iter++;
		}
	}
	else
	{
		iter++;
	}*/
//		vecpos.pop_back();
/*		CFont ft;
		ft.CreateFontIndirect(&pfont);
		CFont *oldfont=hdc->SelectObject(&ft);

		hdc->GetOutputTextMetrics(&textmet); 
		pib=biter+1;
		vector<CVector>::iterator ptiter=biter;

/*		for(vector<CString*>::iterator j=is;j<stk.end();j++)
		{
			for(int i=0;i<(*j)->GetLength();i++)
			{
				if(pib->y==(pib-1)->y)
				{
				CSize cs=hdc->GetTextExtent((*j)->Left(i+1));//str[i]);
	//			pib->x=(pib-1)->x+cs.cx;//-textmet.tmOverhang;
				CPoint pu=*ptiter;//*iter;
				pu.x+=cs.cx;CVector v=pu;
				pib->x=v.x;//(pib-1)->x+cs.cx;
				}
			pib++;
			}
			ptiter+=((*j)->GetLength()+1);
		}
*/
		ptbegin.clear();
		ptend.clear();

		for(vector<CVector>::iterator vpit=vecpos.begin();vpit<vecpos.end();vpit++)
		{
			ptbegin.push_back(*vpit);
			ptend.push_back(*vpit);
		}
		updatecore();
		}
	curspos=*iter;

	CPoint pp;
	pp=curspos;
	hdc->LPtoDP(&pp);
	return pp;
}

void CTextCad::draw(CDC *hdc)
{
		if(ptbegin.size()!= 0)
		{

			updatecore();
			vector<CVector>::iterator bv=ptbegin.begin(),be=ptbegin.begin(),\
									  bb=ptbegin.begin();
			
			for(vector<CString*>::iterator j=stk.begin();j<stk.end();j++)
			{
				if(!((*j)->IsEmpty()))
				{
					bb=bv;
					be=bv+1;
					break;
				}
				bv++;
			}

			CVector vb=(*be)-(*bv);
			double angl=-argu(vb);

			CFont ft;
			pfont.lfOrientation=(angl*1800)/pi;
			pfont.lfEscapement=pfont.lfOrientation;;//pfont.lfOrientation;
			ft.CreateFontIndirect(&pfont);
		

			CFont *oldfont=hdc->SelectObject(&ft);
			hdc->SetBkMode(TRANSPARENT);
			
			vector<CVector>::iterator ptiter=ptbegin.begin();
			vector<CVector>::iterator ptiss=ptbegin.begin()+(ssiter-vecpos.begin());
			vector<CVector>::iterator ptise=ptbegin.begin()+(seiter-vecpos.begin());

			CBrush b;
			b.CreateSolidBrush(RGB(0,0,0));
			CBrush *bold=hdc->SelectObject(&b);
			hdc->SetTextColor(lcolor);

			CSize cs=hdc->GetTextExtent((*is)->Left(st+1));//str[i]);

			if(ptiss<ptise)
			{
				if((ptiter>=ptiss)&&(ptiter<ptise)&&(ptiss!=ptise))
				{
					hdc->SetTextColor(PALETTERGB(255,255,255));
					hdc->Rectangle(CRect(CVector(ptiter->x,ptiter->y-cs.cy),CVector(ptiter->x+cs.cx,ptiter->y)));				
				}
			}
			else
			{
				if((ptiter>=ptise)&&(ptiter<ptiss)&&(ptiss!=ptise))
				{
					hdc->SetTextColor(PALETTERGB(255,255,255));
					hdc->Rectangle(CRect(CVector(ptiter->x,ptiter->y-cs.cy),CVector(ptiter->x+cs.cx,ptiter->y)));				
				}

			}

			for(j=stk.begin();j<stk.end();j++)
			{
			CPoint pu=*ptiter;
			hdc->TextOut(pu.x,pu.y,*(*j));
			ptiter+=((*j)->GetLength()+1);
			}
			ft.DeleteObject();
			b.DeleteObject();
			hdc->SelectObject(bold);
			hdc->SelectObject(oldfont);
		}

}

void CTextCad::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
	CPen pen;
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
	if(!getmultcore())
	{
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptsBegin=*piterb;
		ptsEnd=*pitere;

		CVector vpoint(ptsBegin,prevpos);
		CVector v(ptsBegin,ptsEnd);
	
	if ((pointtoVector(v,vpoint)<5)&&(!(pointinRegion(ptsEnd,prevpos))&&(!(pointinRegion(ptsBegin,prevpos))))||multiselect||getLibstatus())
	{

			vector<CVector>::iterator  pite,pitb;
			pite=ptend.begin();
			CTVector vt;
			vt.pushTransform();
			for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb=pitb+1)
			{
					if(transref)
					{
						CVector begi=ptsBegin;
						CVector v1(prevpos,postpos);
						CVector vv0(v0,(*pitb));
						double gre =argu(refline);
						vt.pushUnit();
						vt.Translate(vv0);
						vt.TRotate(gre);
						vt.endT();
						CVector vr,vo;
						vr.assignPL(v1);
						vo.assignPL(v0);
					
						int c,b;
						c=(vr.y>0)?1:-1;
						b=(vr.x>0)?1:-1;

						(*pitb)=(*pitb)+polarc(absc(vr),0)*b;

						(*pite)=(*pite)+polarc(absc(vr),0)*b;

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

			if(transref)
			{
				CVector begi=ptsBegin;
				CVector v1(prevpos,postpos);
				CVector vv0(v0,(*pitb));
				double gre =argu(refline);
				vt.pushUnit();
				vt.Translate(vv0);
				vt.TRotate(gre);
				vt.endT();
				CVector vr,vo;
				vr.assignPL(v1);
				vo.assignPL(v0);
			
				int c,b;
				c=(vr.y>0)?1:-1;
				b=(vr.x>0)?1:-1;

				(*iter)=(*iter)+polarc(absc(vr),0)*b;

				(*pite)=(*pite)+polarc(absc(vr),0)*b;

			}
			else
			{
				*iter+=mouseVect;
			}
				vt.popTransform();

//		vecpos.clear();
		vector<CVector>::iterator pib=vecpos.begin();

		for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb=pitb+1)
		{
			*pib=*pitb;
			pib++;
		}

//			drawdel(hdc);
			if((!multiselect)||(!getLibstatus()))
			{
				drawTrans(hdc);
			}
			break;
	
	}
	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}
	}
		hdc->SelectObject(oldp);
		hdc->SelectObject(oldb);

	}

}

void CTextCad::drawTrans(CDC *hdc)
{

	int old=hdc->SetROP2(R2_NOTXORPEN);    


	vector<CVector>::iterator bv=ptbegin.begin(),be=ptbegin.begin(),\
							  bb=ptbegin.begin();
	
	for(vector<CString*>::iterator j=stk.begin();j<stk.end();j++)
	{
		if(!((*j)->IsEmpty()))
		{
			bb=bv;
			be=bv+1;
			break;
		}
		bv++;
	}

	CVector vb=(*be)-(*bv);
	double angl=-argu(vb);


	CFont ft;
	pfont.lfOrientation=(angl*1800)/pi;
	pfont.lfEscapement=pfont.lfOrientation;//pfont.lfOrientation;
//	ft.CreateFontIndirect(&pfont);
//	CFont *oldfont=hdc->SelectObject(&ft);

	hdc->SetBkMode(TRANSPARENT);
			
	vector<CVector>::iterator piter=prevptbegin.begin();
	vector<CVector>::iterator ptiss=ptbegin.begin()+(ssiter-vecpos.begin());
	vector<CVector>::iterator ptise=ptbegin.begin()+(seiter-vecpos.begin());

/*	for(int i=0;i<str.GetLength();i++)
	{
//		s+=str[i];
				CSize cs=hdc->GetTextExtent(str[i]);
				hdc->SetTextColor(lcolor);
				if(ptiss<ptise)
				{
					if((piter>=ptiss)&&(piter<ptise)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}
				else
				{
					if((piter>=ptise)&&(piter<ptiss)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}
		CPoint pu=*piter;
		hdc->TextOut(pu.x,pu.y,str[i]);//ptiter->ptext);
		piter++;
	}
*/

				CSize cs=hdc->GetTextExtent((*is)->Left(st+1));//str[i]);

				if(ptiss<ptise)
				{
					if((piter>=ptiss)&&(piter<ptise)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}
				else
				{
					if((piter>=ptise)&&(piter<ptiss)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}

				}

			vector<CVector>::iterator ptiter=ptbegin.begin();

			for(j=stk.begin();j<stk.end();j++)
			{
			CPoint pu=*ptiter;
			hdc->TextOut(pu.x,pu.y,*(*j));
			ptiter+=((*j)->GetLength()+1);
			}

//			CPoint pu=*piter;
//			hdc->TextOut(pu.x,pu.y,*(*is));

		vector<CVector>::iterator  pitb;

    	//ptiter=vectext.begin();

		vb=ptbegin.back()-ptbegin.front();
		angl=-argu(vb);
	
		pfont.lfOrientation=(angl*1800)/pi;
		pfont.lfEscapement=pfont.lfOrientation;;//pfont.lfOrientation;
		ft.Detach();
//		ft.CreateFontIndirect(&pfont);
//		oldfont=hdc->SelectObject(&ft);

		piter=ptbegin.begin();

/*	for(i=0;i<str.GetLength();i++)
	{
				CSize cs=hdc->GetTextExtent(str[i]);
				hdc->SetTextColor(lcolor);
				
				if(ptiss<ptise)
				{
					if((piter>=ptiss)&&(piter<ptise)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}
				else
				{
					if((piter>=ptise)&&(piter<ptiss)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}

				}

		CPoint pu=*piter;
		hdc->TextOut(pu.x,pu.y,str[i]);//ptiter->ptext);
		piter++;
	}*/


				if(ptiss<ptise)
				{
					if((piter>=ptiss)&&(piter<ptise)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}
				else
				{
					if((piter>=ptise)&&(piter<ptiss)&&(ptiss!=ptise))
					{
						hdc->SetTextColor(RGB(255,255,255));
						hdc->Rectangle(CRect(CVector(piter->x,piter->y+cs.cy),CVector(piter->x+cs.cx,piter->y)));				
					}
				}

			for(j=stk.begin();j<stk.end();j++)
			{
			CPoint pu=*ptiter;
			hdc->TextOut(pu.x,pu.y,*(*j));
			ptiter+=((*j)->GetLength()+1);
			}

//			pu=*piter;//*ptiter;
//			hdc->TextOut(pu.x,pu.y,*(*is));


//	hdc->SelectObject(oldfont);

	hdc->SetROP2(old);    

}

bool CTextCad::PtinRegion(CVector point)
{
	updatecore();
	CVector pr2=p2;
	pr2.y=p2.y-max(textmet.tmAscent,textmet.tmDescent);
	CVector r(p0,pr2);
	CVector pk=(p0+pr2)/2;


	if(absc(CVector(pk,point))<absc(CVector(pk,p0)))
	{
		click=true;
		return true;
	}

	click=false;
	return false;

}

CPoint CTextCad::setfont(CDC *hdc,LOGFONT font,COLORREF ccl)
{
	pfont=font;
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
	updatecore();
	CPoint pp;
	pp=*iter;
	curspos=*iter;
	pp=curspos;
	hdc->LPtoDP(&pp);
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
//	vectext.pop_back();
//	vecpos.pop_back();

	titer=vectext.erase(titer-1);
	vecpos.pop_back();
	ptbegin.pop_back();
	ptend.pop_back();
	updatecore();
	CPoint pp;
	pp=*iter;
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


void CTextCad::savefile(CFile &file)
{
 
//	file.Write(&rec,sizeof(rec));
	int i=stk.size();
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
	
/*	i=str->GetLength();
	file.Write(&i,sizeof(int));
	for(int j=0;j<i;j++)
	{
	char c=(*str)[j];
	file.Write(&c,sizeof(c));
	}*/
//	file.Write(&str,sizeof(str)*str.GetLength());
	file.Write(&textmet, sizeof(textmet));
	file.Write(&width,sizeof(width));
	file.Write(&pfont,sizeof(pfont));

 CFigure::savefile(file);
}
void CTextCad::openfile(CFile &file)
{
//	 file.Read(&rec,sizeof(rec));

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

/*	int i;
	file.Read(&i,sizeof(int));
	for(int j=0;j<i;j++)
	{
	char c;
	file.Read(&c,sizeof(c));
	str->Insert(j,c);
	}*/
//	 file.Read(&str,sizeof(str));
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

}



void CTextCad::assign(CDC *hdc,CVector p,CString s)
{
	*str=s;
	CFont ft;
	ft.CreateFontIndirect(&pfont);
	CFont *oldfont=hdc->SelectObject(&ft);
	hdc->GetOutputTextMetrics(&textmet); 

	stk.push_back(str);
	is=stk.end()-1;

	vecpos.push_back(p);
	vector<CVector>::iterator pib=vecpos.begin()+1;
	CVector pl=p;
	for(int i=0;i<(*is)->GetLength();i++)
	{
//		CSize cs=hdc->GetTextExtent(str[i]);
//		pl.x+=cs.cx-textmet.tmOverhang;
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
	iter=vecpos.begin();
	hdc->SelectObject(oldfont);

}

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

LOGFONT CTextCad::getFont()
{
	return pfont;
}

void CTextCad::updatecopy()
{
	is=stk.end()-1;

}

void CTextCad::copy(CTextCad *text)
{
	for(vector<CString*>::iterator i=text->stk.begin();i!=text->stk.end();i++)
	{
		stk.push_back(new CString(**i));
	}
	str=*(stk.end()-1);
	is=stk.end()-1;
	vecpos=text->vecpos;
	if(vecpos.size()>0)
		curspos=vecpos.back();
	rec.copy(&text->rec);
	pfont=text->pfont;
	fPrevB=text->fPrevB;
	CFigure::copy(text);



//	*liter=*text->liter;
//	vectext=text->vectext;
//	liter
//	vector<text>::iterator titer;
}
