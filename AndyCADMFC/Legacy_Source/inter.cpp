// Inter.cpp: implementation of the CInter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Inter.h"
//#include "Tvector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInter::CInter()
{

}

CInter::~CInter()
{

}

bool CInter::inReg(CFigure *c1, CFigure *r1)
{
	CAABB r01;
	r01.add(CPoint(c1->box.corner(0)));
	r01.add(CPoint(c1->box.corner(1)));
	r01.add(CPoint(c1->box.corner(2)));
	r01.add(CPoint(c1->box.corner(3)));
	r01.add(CPoint(c1->box.corner(4)));
	r01.add(CPoint(c1->box.corner(5)));
	r01.add(CPoint(c1->box.corner(6)));
	r01.add(CPoint(c1->box.corner(7)));

	CAABB r02;
	r02.add(CPoint(r1->box.corner(0)));
	r02.add(CPoint(r1->box.corner(1)));
	r02.add(CPoint(r1->box.corner(2)));
	r02.add(CPoint(r1->box.corner(3)));
	r02.add(CPoint(r1->box.corner(4)));
	r02.add(CPoint(r1->box.corner(5)));
	r02.add(CPoint(r1->box.corner(6)));
	r02.add(CPoint(r1->box.corner(7)));
	CAABB r03;
	r02.intersectAABB(r01,&r03);


	return (r03==&r01);
}

void CInter::Updateselect()
{
	for(int i=0;i<0;i++)
	{
	}
}

void CInter::mirror(CFigure *base, CFigure *line,CFigure *result)
{

	
	vector<CVector>* presult[2];
 	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	
	base->prevptend=base->ptend;
	base->prevptbegin=base->ptbegin;
	base->pitere=base->ptend.begin();
	
	for (base->piterb=base->ptbegin.begin();base->piterb<base->ptbegin.end();base->piterb++)
	{
		base->ptsBegin=*base->piterb;
		base->ptsEnd=*base->pitere;
		CVector pl=(*base->piterb).intersect(*base->pitere);

		CRay VMainb(base->ptsBegin,base->ptsEnd);
 		CVector p=VMainb.getclosestPoint(*line->ptbegin.begin());
		CVector n=*line->ptbegin.begin()-p;
		n=n/absc(n);
		CVector V(base->ptsBegin,base->ptsEnd);
		V.dot(n);
		
		CTVector v;
		v.pushTransform();
		v.pushUnit();
		v.Translate(-p);
		v.Reflect(n);
		v.Translate(p);
		v.endT();
	
		vector<CVector>::iterator piterbex;
		vector<CVector>::iterator pitereex=line->ptend.begin();
	
		for(piterbex=line->ptbegin.begin();piterbex<line->ptbegin.end();piterbex++)
		{

		CVector ptStart=*piterbex;
		CVector ptEnd=*pitereex;
	

		ptStart.assign(*piterbex,true);
		ptEnd.assign(*pitereex,true);

		testb.push_back(ptStart);
 		teste.push_back(ptEnd);
	
		if ((pitereex+1)<line->ptend.end())
		{
		pitereex=pitereex+1;
		}
	}
		v.popTransform();
 		
		
	if ((base->pitere+1)<base->ptend.end())
		{
		base->pitere=base->pitere+1;
		}

	}

	result->addvec(testb,teste);

}
void CInter::copybyL(CFigure *base, CFigure *line,CFigure *result)
{

	
	vector<CVector>* presult[2];
 	vector<CVector> testb,teste;
	testb.clear();teste.clear();
	
	base->prevptend=base->ptend;
	base->prevptbegin=base->ptbegin;
	base->pitere=base->ptend.begin();
	line->updatecore();

	
	for (base->piterb=base->ptbegin.begin();base->piterb<base->ptbegin.end();base->piterb++)
	{
		base->ptsBegin=*base->piterb;
		base->ptsEnd=*base->pitere;
		CVector pl=(*base->piterb).intersect(*base->pitere);

		CRay VMainb(base->ptsBegin,base->ptsEnd);
 		CVector p=VMainb.getclosestPoint(line->getCenter());
		CVector n=line->getCenter()-p;
		n+=n;
		CVector V(base->ptsBegin,base->ptsEnd);
		V.dot(n);
		
		CTVector v;
		v.pushTransform();
		v.pushUnit();
		v.Translate(-n);
		v.endT();
	
		vector<CVector>::iterator piterbex;
		vector<CVector>::iterator pitereex=line->ptend.begin();
	
		for(piterbex=line->ptbegin.begin();piterbex<line->ptbegin.end();piterbex++)
		{

		CVector ptStart=*piterbex;
		CVector ptEnd=*pitereex;
	

		ptStart.assign(*piterbex,true);
		ptEnd.assign(*pitereex,true);

		testb.push_back(ptStart);
 		teste.push_back(ptEnd);
	
		if ((pitereex+1)<line->ptend.end())
		{
		pitereex=pitereex+1;
		}
	}
		v.popTransform();
 		
		
	if ((base->pitere+1)<base->ptend.end())
		{
		base->pitere=base->pitere+1;
		}

	}

	result->addvec(testb,teste);

}

CLibS* CInter::mirror(CFigure *base, CLibS* line)
{

	CLibS *result=new CLibS;
	CLibS *pLibs;
	CTextCad textc;
	CLine pLine;//=new CLine;
	CRectangle pRectangle;//=new CRectangle;
	CBezier pBezier1;//=new CBezier;
	CCercle pCircle;//=new CCercle;;
	
  for(int i=0;i<line->iter;i++)
	{
		if(line->elem[i]->getName()==pLine.getName())
		{
			pLine=*(CLine*)line->elem[i];
			mirror(base,line->elem[i],&pLine);
			CLine *ftp= new CLine;
			*ftp=pLine;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pRectangle.getName())
		{
			pRectangle=*(CRectangle*)line->elem[i];
			mirror(base,line->elem[i],&pRectangle);
			CRectangle *ftp= new CRectangle;
			*ftp=pRectangle;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pCircle.getName())
		{
			pCircle=*(CCercle*)line->elem[i];
			mirror(base,line->elem[i],&pCircle);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pBezier1.getName())
		{
			pBezier1=*(CBezier*)line->elem[i];
			mirror(base,line->elem[i],&pBezier1);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==textc.getName())
		{
			textc=*(CTextCad*)line->elem[i];
			mirror(base,line->elem[i],&textc);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==result->getName())
		{
			pLibs=(CLibS*)line->elem[i];
			pLibs=mirror(base,(CLibS*)line->elem[i]);
			CLibS *ftp= new CLibS;
			*ftp=*pLibs;
			result->add(pLibs);
		}
	}
//  delete pLibs;
  return result;

}
CLibS* CInter::copybyL(CFigure *base, CLibS* line)
{

	CLibS *result=new CLibS;
	CLibS *pLibs;
	CTextCad textc;
	CLine pLine;//=new CLine;
	CRectangle pRectangle;//=new CRectangle;
	CBezier pBezier1;//=new CBezier;
	CCercle pCircle;//=new CCercle;;
	
  for(int i=0;i<line->iter;i++)
	{
		if(line->elem[i]->getName()==pLine.getName())
		{
			pLine=*(CLine*)line->elem[i];
			mirror(base,line->elem[i],&pLine);
			CLine *ftp= new CLine;
			*ftp=pLine;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pRectangle.getName())
		{
			pRectangle=*(CRectangle*)line->elem[i];
			mirror(base,line->elem[i],&pRectangle);
			CRectangle *ftp= new CRectangle;
			*ftp=pRectangle;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pCircle.getName())
		{
			pCircle=*(CCercle*)line->elem[i];
			mirror(base,line->elem[i],&pCircle);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pBezier1.getName())
		{
			pBezier1=*(CBezier*)line->elem[i];
			mirror(base,line->elem[i],&pBezier1);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==textc.getName())
		{
			textc=*(CTextCad*)line->elem[i];
			mirror(base,line->elem[i],&textc);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==result->getName())
		{
			pLibs=(CLibS*)line->elem[i];
			pLibs=mirror(base,(CLibS*)line->elem[i]);
			CLibS *ftp= new CLibS;
			*ftp=*pLibs;
			result->add(pLibs);
		}
	}
//  delete pLibs;
  return result;

}

CBezier* CInter::subdivide(double t, int p,double *U,CVector *P,int n)
{

	/*Input: knot t in [uk, uk+1) with initial multiplicity s to be inserted h times, 
			where h+s is less than or equal to p, the degree of the given B-spline curve 
	  Output: a new set of control points after t is inserted h times 

	  Let control points Pk, Pk-1, ..., Pk-p be renamed as Pk,0, Pk-1,0, ..., Pk-p,0 by adding a second subscript 0. 

		for r := 1 to h do 

		for i := k-p+r to k-s do 

		begin 

		Let ai,r = (t - ui) / ( ui+p-r+1 - ui ) 
		Let Pi,r = (1 - ai,r) Pi-1,r-1 + ai,r Pi,r-1 

		end 

		The new set of control points are constructed from the original ones from P0 to Pk-p,
		followed by the top edge of the diagram above (i.e., Pk-p+1,1, Pk-p+2,2, ..., Pk-p+h,h),
		followed by the right edge of the diagram (i.e., Pk-p+h+1,h, Pk-p+h+2,h, ...., Pk-s,h),
		followed by the bottom edge of the diagram (i.e., Pk-s,h-1, Pk-s,h-2, ...., Pk-s,1), 
		followed by the original control points Pk-s, ..., Pk, ..., Pn. 

	*/

	CBezier *result=new CBezier[2];

	int ncp1,ncp2;
	double Uc1[100],Uc2[100];
	CVector P1[100],P2[100];
//	n=n+h;

	int h=0;
	int s=0;
	int m=n+p+1;
	int c=n;
//	n=n+h;

	int k;
	int l=0;

	for(int iter=0;iter<=m;iter++)
	{
		if((U[iter]<t)&&(t<U[iter+1]))
		{
			s=0;
			h=p;
			k=iter;
		}
		if(U[iter]==t)
		{
			s++;
			h=p-s;
			k=iter;
		}
	}

	if ((h>0)&&(k-p>=0))
	{
	CVector *PV;
	PV=new CVector [(n+3)*(n+3)];

	double *arv;
	arv=new double[(n+3)*(n+3)];
	
	for(iter=0;iter<=n;iter++)
	{
	PV[iter*(n+1)]=P[iter];
	}

		
	for(int r=1; r<=h;r++)
	{
		for(int i=k-p+r; i<=k-s; i++)
		{
			arv[(n+1)*i+r]=(t-U[i])/(U[i+p-r+1]-U[i]);
			PV[(n+1)*i+r].x=(1-arv[(n+1)*i+r])*PV[(n+1)*(i-1)+(r-1)].x+arv[(n+1)*i+r]*PV[(n+1)*i+(r-1)].x;
			PV[(n+1)*i+r].y=(1-arv[(n+1)*i+r])*PV[(n+1)*(i-1)+(r-1)].y+arv[(n+1)*i+r]*PV[(n+1)*i+(r-1)].y;
		}
	}

	int hi;
	int hh=0;
	for(hi=0;hi<k;hi++)
	{
		Uc1[hi]=U[hh];hh++;

	}
	for(hi=k;hi<=k+p;hi++)
	{
	Uc1[hi]=t;
	}


	for(hi=0;hi<=p;hi++)
	{
		Uc2[hi]=t;
	}

	hh=0;
	for(hi=p+1;hi<m;hi++)
	{
		Uc2[hi]=U[hi+1];
		hh++;
	}


	r=0;
	int j=0;
	for(iter=0;iter<=k-p;iter++)
	{
	P1[j].x=PV[(n+1)*r+iter].x/PV[(n+1)*r+iter].w;
	P1[j].y=PV[(n+1)*r+iter].y/PV[(n+1)*r+iter].w;
	P1[j].w=PV[(n+1)*r+iter].w;
	j++;
	}


	for(iter=1;iter<=h;iter++)
	{
	P1[j].x=PV[(n+1)*iter+(k-p+iter)].x/PV[(n+1)*iter+(k-p+iter)].w;
	P1[j].y=PV[(n+1)*iter+(k-p+iter)].y/PV[(n+1)*iter+(k-p+iter)].w;
	P1[j].w=PV[(n+1)*iter+(k-p+iter)].w;
	j++;
	}
	ncp1=j-1;
	j=1;
	P2[0]=P1[ncp1-1];
	for(iter=k-p+h+1;iter<=k-s;iter++)
	{
	P2[j].x=PV[(n+1)*h+iter].x/PV[(n+1)*h+iter].w;
	P2[j].y=PV[(n+1)*h+iter].y/PV[(n+1)*h+iter].w;
	P2[j].w=PV[(n+1)*h+iter].w;
	j++;
	}

	for(iter=h-1;iter>=1;iter--)
	{
	P2[j].x=PV[(n+1)*iter+(k-s)].x/PV[(n+1)*iter+(k-s)].w;
	P2[j].y=PV[(n+1)*iter+(k-s)].y/PV[(n+1)*iter+(k-s)].w;
	P2[j].w=PV[(n+1)*iter+(k-s)].w;
	j++;
	}

	r=0;
	for(iter=k-s;iter<=n;iter++)
	{
	P2[j].x=PV[(n+1)*r+iter].x/PV[(n+1)*r+iter].w;
	P2[j].y=PV[(n+1)*r+iter].y/PV[(n+1)*r+iter].w;
	P2[j].w=PV[(n+1)*r+iter].w;
	j++;
	}
	ncp2=j-2;
	
//	delete [] a;
	}
//	ncp+=h;
	CBezier bez1,bez2;

	for(int i=0;i<ncp1+p+1;i++)
	{
	bez1.Kn[i]=Uc1[i];
	}
	for(i=0;i<ncp2+p+1;i++)
	{
	bez2.Kn[i]=Uc2[i];
	}

	for(i=0;i<ncp2;i++)
	{
	bez2.CP[i]=P2[i];
	}
	for(i=0;i<ncp1;i++)
	{
	bez1.CP[i]=P1[i];
	}
	bez1.ncp=ncp1;
	bez2.ncp=ncp2;
	result[0]=bez1;
	result[1]=bez2;
	return result;

}

CLibS* CInter::pasteArray(CVector cent,CLibS *line,bool of,int nbrow,int nbcol, double distx,double disty,int nblevel,double lspacing)
{
	vector<CFigure> *arr;
	vector<CFigure>::iterator fiter;
	CFigure *fig[50];
	CLibS pLibs;
	CLibS *lib;
	
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;
	int k=0,j=0,t=0;
	
	for(int i=0;i<line->iter;i++)
	{
		k=0;
	  line->elem[i]->setcore(line->core);
	  if(line->elem[i]->getName()!=pLibs.getName())
	  {

		vector<CFigure>* pbulk=new vector<CFigure>;
//	arr=line->elem[i]->translatepArray(of,nbrow,nbcol,distx,disty,nblevel,lspacing,pbulk); To see later March 2008
		for(fiter=arr->begin();fiter<arr->end();fiter++)
		{
			if(line->elem[i]->getName()==pLine.getName())
			{
			pLine=*(CLine*)line->elem[i];
			pLine.createobj(fiter->ptbegin,fiter->ptend);
			CLine *ftp= new CLine;
			*ftp=pLine;
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==pRectangle.getName())
			{
			pRectangle=*(CRectangle*)line->elem[i];
			pRectangle.createobj(fiter->ptbegin,fiter->ptend);
			CRectangle *ftp= new CRectangle;
			*ftp=pRectangle;
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==pCircle.getName())
			{
			pCircle.copy(*(CCercle*)line->elem[i]);
			pCircle.addvec(fiter->ptbegin,fiter->ptend);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==pBezier1.getName())
			{
			pBezier1.copy((CBezier*)line->elem[i]);
			pBezier1.addvec(fiter->ptbegin,fiter->ptend);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==textc.getName())
			{
			textc=*(CTextCad*)line->elem[i];
			textc.addvec(fiter->ptbegin,fiter->ptend);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			fig[t]=ftp;
			k++;t++;
			}
		}
			j++;
		}
		else
		{
			lib=pasteArray(cent,(CLibS*)line->elem[i],of,nbrow,nbcol, distx,disty,nblevel,lspacing);
			int kk=lib[0].x;
			for(int i=0;i<kk;lib++,i++)
			{
			CLibS *ftp= new CLibS;
			*ftp=*lib;
		//	fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
		//	m=_msize(fig);
			fig[t]=ftp;
			k++;t++;
			}
			j++;

		}
			
	}		
			
			
			//	vector<CLibS>* result=new vector<CLibS>;
	CLibS *llib=new CLibS[k];
	
	for(int jj=0;jj<k;jj++)
	{
	
	for(int i=0;i<j;i++)
	{
		llib[jj].add(fig[i*k+jj]);
	}
	}
	llib[0].x=k;
	return llib;


}


CLibS* CInter::paste(CVector cent,CVector point,CLibS *line)
{
	vector<CVector> *arr;
	CLibS* result=new CLibS;
	CLibS* pLibs=new CLibS;;
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;
	
  for(int i=0;i<line->iter;i++)
	{
	  if(line->elem[i]->getName()!=pLibs->getName())
	  {
//			arr=line->elem[i]->translatep(cent,point); To check back
				if(line->elem[i]->getName()==pLine.getName())
				{
					pLine=*(CLine*)line->elem[i];
					pLine.createobj(*arr,*(arr+1));
					delete[] arr;
					CLine *ftp= new CLine;
					*ftp=pLine;
					result->add(ftp);
				}
				else
				if(line->elem[i]->getName()==pRectangle.getName())
				{
					pRectangle=*(CRectangle*)line->elem[i];
					pRectangle.createobj(*arr,*(arr+1));
					delete[] arr;
					CRectangle *ftp= new CRectangle;
					*ftp=pRectangle;
					result->add(ftp);
				}else
				if(line->elem[i]->getName()==pCircle.getName())
				{
					pCircle.copy(*(CCercle*)line->elem[i]);
					pCircle.addvec(*arr,*(arr+1));
					CCercle *ftp= new CCercle;
					ftp->copy(pCircle);
					result->add(ftp);
				}else
				if(line->elem[i]->getName()==pBezier1.getName())
				{
					pBezier1.copy((CBezier*)line->elem[i]);
					pBezier1.addvec(*arr,*(arr+1));
					CBezier *ftp= new CBezier;
					ftp->copy(&pBezier1);
					result->add(ftp);
				}
				else
				if(line->elem[i]->getName()==textc.getName())
				{
					textc=*(CTextCad*)line->elem[i];
					textc.addvec(*arr,*(arr+1));
					CTextCad *ftp= new CTextCad;
					*ftp=textc;
					result->add(ftp);
				}
		}
	  else
	  {
			pLibs=paste(cent, point,(CLibS*)line->elem[i]);
//			CLibS *ftp= new CLibS;
//			*ftp=pLibs;
			result->add(pLibs);

	  }
  }
  return result;

}

CFigure* CInter::paste(CVector cent,CVector point,CFigure *line)
{
	vector<CVector> *arr;
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;
	CLibS* lb=new CLibS;
	
	  if(line->getName()!=lb->getName())
	  {
//			arr=line->translatep(cent,point); To check back
				if(line->getName()==pLine.getName())
				{
					pLine.copy(line);
					pLine.createobj(*arr,*(arr+1));
					delete[] arr;
					CLine *ftp= new CLine;
					ftp->copy(&pLine);
					return ftp;
				}
				else
				if(line->getName()==pRectangle.getName())
				{
					pRectangle.copy(line);
					pRectangle.createobj(*arr,*(arr+1));
					delete[] arr;
					CRectangle *ftp= new CRectangle;
					ftp->copy(&pRectangle);
					return ftp;
				}else
				if(line->getName()==pCircle.getName())
				{
					pCircle.copy(*(CCercle*)line);
					pCircle.addvec(*arr,*(arr+1));
					CCercle *ftp= new CCercle;
					ftp->copy(pCircle);
					return ftp;
				}else
				if(line->getName()==pBezier1.getName())
				{
					pBezier1.copy((CBezier*)line);
					pBezier1.addvec(*arr,*(arr+1));
					CBezier *ftp= new CBezier;
					ftp->copy(&pBezier1);
					return ftp;
				}
				else
				if(line->getName()==textc.getName())
				{
					textc=*(CTextCad*)line;
					textc.addvec(*arr,*(arr+1));
					CTextCad *ftp= new CTextCad;
					*ftp=textc;
					return ftp;
				}
		}
	  else
	  {
			CLibS* pLibs=new CLibS;;
			pLibs=paste(cent, point,(CLibS*)line);
			return pLibs;

	  }
	  delete lb; 
}


CLibS* CInter::RotateCopyP(CDC *hdc,CVector cent,CVector point, bool align, CLibS *line)
{
	vector<CFigure> *arr;
	vector<CFigure>::iterator fiter;
	CFigure* fig[50];
	CLibS pLibs;
	CLibS *lib;
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;
	int k=0,j=0,t=0;
	for(int i=0;i<line->iter;i++)
	{
		k=0;
		line->elem[i]->setRotateCenter(cent);
		line->elem[i]->setcore(line->core);
		if(line->elem[i]->getName()!=pLibs.getName())
		{
		vector<CFigure>* pbulk=new vector<CFigure>;

   		pbulk=line->elem[i]->RotateCopyP(hdc,point,pbulk,align);
		for(fiter=pbulk->begin();fiter<pbulk->end();fiter++)
		{
			if((line->elem[i]->getName()==pLine.getName())||(line->elem[i]->getName()==pRectangle.getName()))
			{
			pLine=*(CLine*)line->elem[i];
			pLine.createobj(fiter->ptbegin,fiter->ptend);
			CLine *ftp= new CLine;
			*ftp=pLine;
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==pCircle.getName())
			{
			pCircle.copy(*(CCercle*)line->elem[i]);
			pCircle.addvec(fiter->ptbegin,fiter->ptend);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==pBezier1.getName())
			{
			pBezier1.copy((CBezier*)line->elem[i]);
			pBezier1.addvec(fiter->ptbegin,fiter->ptend);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			fig[t]=ftp;
			k++;t++;
			}else
			if(line->elem[i]->getName()==textc.getName())
			{
			textc=*(CTextCad*)line->elem[i];
			textc.addvec(fiter->ptbegin,fiter->ptend);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			fig[t]=ftp;
			k++;t++;
			}
		}
			j++;
		}
		else
		{
			lib=RotateCopyP(hdc,cent,point,align,(CLibS*)line->elem[i]);
			int kk=lib[0].x;
			for(int i=0;i<kk;lib++,i++)
			{
			lib->draw(hdc);
			CLibS *ftp= new CLibS;
			*ftp=*lib;
		//	fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
		//	m=_msize(fig);
			fig[t]=ftp;
			k++;t++;
			}
			j++;
		}
	}

	vector<CLibS>* result=new vector<CLibS>;
	
	CLibS *llib=new CLibS[k];
	
	for(int jj=0;jj<k;jj++)
	{
	
	for(int i=0;i<j;i++)
	{
		llib[jj].add(fig[i*k+jj]);
	}
	}
	llib[0].x=k;
	return llib;
}

CLibS* CInter::RotateCopyP(CDC *hdc,double ang,int nnb, bool align,int nblevel,int dlevel, CLibS *line)
{
	vector<CFigure>::iterator fiter;
	CFigure* fig[50];
	CLibS pLibs;
	CLibS *lib;
	CLine pLine;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;
	CTextCad textc;

	int k=0,j=0,t=0;
	for(int i=0;i<line->iter;i++)
	{
		k=0;
		line->elem[i]->setRotateCenter(line->rotateCenter);
		line->elem[i]->setcore(line->core);

		if(line->elem[i]->getName()!=pLibs.getName())
		{

			vector<CFigure>* pbulk=new vector<CFigure>;
	//		pbulk=line->elem[i]->RotateCopyP(hdc,ang,nnb,nblevel,dlevel,pbulk,align); To see 30/03/2008
			for(fiter=pbulk->begin();fiter<pbulk->end();fiter++)
			{
				if((line->elem[i]->getName()==pLine.getName())||(line->elem[i]->getName()==pRectangle.getName()))
				{
				pLine=*(CLine*)line->elem[i];
				pLine.createobj(fiter->ptbegin,fiter->ptend);
				CLine *ftp= new CLine;
				*ftp=pLine;
				fig[t]=ftp;
				k++;t++;
				}else
				if(line->elem[i]->getName()==pCircle.getName())
				{
				pCircle.copy(*(CCercle*)line->elem[i]);
				pCircle.addvec(fiter->ptbegin,fiter->ptend);
				CCercle *ftp= new CCercle;
				ftp->copy(pCircle);
				fig[t]=ftp;
				k++;t++;
				}else
				if(line->elem[i]->getName()==pBezier1.getName())
				{
				pBezier1.copy((CBezier*)line->elem[i]);
				pBezier1.addvec(fiter->ptbegin,fiter->ptend);
				CBezier *ftp= new CBezier;
				ftp->copy(&pBezier1);
				fig[t]=ftp;
				k++;t++;
				}else
				if(line->elem[i]->getName()==textc.getName())
				{
				textc=*(CTextCad*)line->elem[i];
				textc.addvec(fiter->ptbegin,fiter->ptend);
				CTextCad *ftp= new CTextCad;
				*ftp=textc;
				fig[t]=ftp;
				k++;t++;
				}
			}
			j++;
		}
		else
		{
			lib=RotateCopyP(hdc,ang,nnb,align,nblevel,dlevel,(CLibS*)line->elem[i]);
			int kk=lib[0].x;
			for(int i=0;i<kk;lib++,i++)
			{
			lib->draw(hdc);
			CLibS *ftp= new CLibS;
			*ftp=*lib;
		//	fig=(CFigure**) realloc(fig,m+sizeof(CFigure*));
		//	m=_msize(fig);
			fig[t]=ftp;
			k++;t++;
			}
			j++;
		}
	}

	vector<CLibS>* result=new vector<CLibS>;
	
	CLibS *llib=new CLibS[k];
	
	for(int jj=0;jj<k;jj++)
	{
	
	for(int i=0;i<j;i++)
	{
		llib[jj].add(fig[i*k+jj]);
	}
	}
	llib[0].x=k;
	return llib;
}

CLibS* CInter::copybyC(CDC *hdc, CVector cent,CVector point, CFigure *pbulk, CLibS *line)
{
	CInter pInter;
	CLibS *result=new CLibS;
	result->Copy(*line);
	result->init();
	CLibS pLibs;
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;

	CFigure *arr;

	for (int i=0;i<line->iter;i++)
	{
	line->elem[i]->setRotateCenter(cent);//line->rotateCenter);
	line->elem[i]->setcore(line->core);
	  if(line->elem[i]->getName()!=pLibs.getName())
	  {
//		arr=line->elem[i]->copybyC(hdc,point,pbulk); To see 31/03/2008

		if(line->elem[i]->getName()==pLine.getName())
		{
			pLine=*(CLine*)line->elem[i];
			pLine.createobj(arr->ptbegin,arr->ptend);
			CLine *ftp= new CLine;
			*ftp=pLine;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pRectangle.getName())
		{
			pRectangle=*(CRectangle*)line->elem[i];
			pRectangle.createobj(arr->ptbegin,arr->ptend);
			CRectangle *ftp= new CRectangle;
			*ftp=pRectangle;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pCircle.getName())
		{
			pCircle.copy(*(CCercle*)line->elem[i]);
			pCircle.addvec(arr->ptbegin,arr->ptend);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pBezier1.getName())
		{
			pBezier1.copy((CBezier*)line->elem[i]);
			pBezier1.addvec(arr->ptbegin,arr->ptend);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==textc.getName())
		{
			textc=*(CTextCad*)line->elem[i];
			textc.addvec(arr->ptbegin,arr->ptend);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			result->add(ftp);
		}
		}
	else
	{
		CLibS *ftp;//= new CLibS;
		ftp=copybyC(hdc, cent,point,pbulk,(CLibS*)line->elem[i]);
//		*ftp=pLibs;
		result->add(ftp);
	}
	}
	return result;
}


CLibS* CInter::copy2(CVector cent, float d, CFigure *pbulk, CLibS *line)
{
	CInter pInter;
	CLibS *result=new CLibS;
	result->Copy(*line);
	result->init();
	CLibS pLibs;
	CLine pLine;
	CTextCad textc;
	CRectangle pRectangle;
	CBezier pBezier1;
	CCercle pCircle;

	CFigure *arr;

	for (int i=0;i<line->iter;i++)
	{
	line->elem[i]->setRotateCenter(cent);//line->rotateCenter);
	line->elem[i]->setcore(line->core);
	  if(line->elem[i]->getName()!=pLibs.getName())
	  {
		arr=line->elem[i]->copy2(d,pbulk);

		if(line->elem[i]->getName()==pLine.getName())
		{
			pLine=*(CLine*)line->elem[i];
			pLine.createobj(arr->ptbegin,arr->ptend);
			CLine *ftp= new CLine;
			*ftp=pLine;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pRectangle.getName())
		{
			pRectangle=*(CRectangle*)line->elem[i];
			pRectangle.createobj(arr->ptbegin,arr->ptend);
			CRectangle *ftp= new CRectangle;
			*ftp=pRectangle;
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pCircle.getName())
		{
			pCircle.copy(*(CCercle*)line->elem[i]);
			pCircle.addvec(arr->ptbegin,arr->ptend);
			CCercle *ftp= new CCercle;
			ftp->copy(pCircle);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==pBezier1.getName())
		{
			pBezier1.copy((CBezier*)line->elem[i]);
			pBezier1.addvec(arr->ptbegin,arr->ptend);
			CBezier *ftp= new CBezier;
			ftp->copy(&pBezier1);
			result->add(ftp);
		}else
		if(line->elem[i]->getName()==textc.getName())
		{
			textc=*(CTextCad*)line->elem[i];
			textc.addvec(arr->ptbegin,arr->ptend);
			CTextCad *ftp= new CTextCad;
			*ftp=textc;
			result->add(ftp);
		}
		}
	else
	{
		CLibS *ftp;//= new CLibS;
		ftp=copy2(cent,d,pbulk,(CLibS*)line->elem[i]);
		result->add(ftp);
	}
	}
	return result;
}
