// Cercle.cpp: implementation of the CCercle class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "Cercle.h"
#include "plane.h"
#include <math.h>
#include "ffd.h"
#include "textcad.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCercle::CCercle()
{
	handle=0;
	prevref=N;
	prevstart=0;
	prevf="NULL";
	it=0;
	name="CCercle";
	start=0;
	cl=false;
	lstyle=PS_GEOMETRIC;
//	mode=tech;

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;
		deg=2;
		ncp=8;

	   selectvec.push_back(v0);
	   selectvec.push_back(v0);
	   selectvec.push_back(v0);
	   selectvec.push_back(v0);
	

}

CCercle::~CCercle()
{

}


void CCercle::addvec(vector<CVector> vectb, vector<CVector> vecte)
{
	CBezier::addvec(vectb,vecte);
	return;
	int i=0;
	ptbegin=vectb;
	ptend=vecte;
	CP=ptbegin;
/*	for(pitere=ptbegin.begin();pitere<ptbegin.end();pitere++)
	{
//		CP[i].x=(*pitere).x;
		CP[i]=*pitere;
		i++;
	}*/
//	CP[i].x=ptend.back().x;
//	CP[i]=ptend.back();
//	Ct=(CP[1]*CP[5])*(CP[3]*CP[7]);	
//	Ct.w=1;

/*	CP[1].w=(1/sqrt(2));
	CP[3].w=(1/sqrt(2));
	CP[5].w=(1/sqrt(2));
	CP[7].w=(1/sqrt(2));*/



//	updatecore();

}




void CCercle::DrawBSpline(CDC *hdc)
{
	CBezier::DrawBSpline(hdc);
	return;
  if(!surf)
  {
  //point on the line

   addvec(ptbegin,ptend);

   
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];
//   Para=new double [N+1];
   Para_universp(minpara,maxpara,N,Para);
   lk=0;
   lh=N;///maxpara);

  if(redraw)
  {
   for(int iter=0;iter<=N;iter++)
   {
	  Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
//	  M[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
   }
   redraw=false;
  }
   if(ffd)
   {
	   setFFD(Mr);
   }

   CPoint *Pt=new CPoint[N+1];
   int s=0;
   for(int iter=lk;iter<=lh;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   s++;
	}


    CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

   
   if(cl)
   {
	if(texture_file!="")
	{
		CImagex texture(hdc->GetSafeHdc(),texture_file.GetBuffer(10));
        ScanPolygon(hdc,bcolor,Mr,s,&texture);
    }
	else
	{
        ScanPolygon(hdc,bcolor,Mr,s,NULL);
	}

   }
 	hdc->Polyline(&Pt[0],s);

	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);


/*   hdc->MoveTo(M[prevref]);
   for(iter=prevref;iter<=N;iter++)
   {
	hdc->LineTo(M[iter]);
   }*/

/*	if((!multiselect)&&(!getLibstatus()))
	{
//	selectSM(hdc);
	if(transselectedstate()) drawselect(hdc);

	if (getRotstate())
	{
	hdc->MoveTo(rotateCenter.x,rotateCenter.y-15);
	hdc->LineTo(rotateCenter.x,rotateCenter.y+15);
	hdc->MoveTo(rotateCenter.x-15,rotateCenter.y);
	hdc->LineTo(rotateCenter.x+15,rotateCenter.y);
	}
	}
*/ 

   delete [] M;
//   delete []Para;
   delete []Pt;
   }
   else
   {
	   CBezier::surface(hdc);
   }

}

void CCercle::DrawDynaBspline(CDC *hdc)
{
	CBezier::DrawDynaBspline(hdc);
	return;
	if(!surf)
	{
	addvec(ptbegin,ptend);
    //point on the line
   CVector *M;
   M=new CVector[N+1];
//   if(Mr==NULL) Mr=new CVector[N+1];


    CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen *oldp=hdc->SelectObject(&pen);
    Para_universp(minpara,maxpara,N,Para);

	if(redraw)
	{
   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);

   }
   redraw=false;
	}

   if(ffd)
   {
	   setFFD(Mr);
   }
   
	   selectvec[0]=Mr[start];
	   selectvec[1]=Mr[start+1];
	   selectvec[2]=Mr[N-1];
	   selectvec[3]=Mr[N];

   CPoint *Pt=new CPoint [N+1];
   int s=0;
   for(int iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   s++;
	}
	s=N-prevref-1;
   

	int jj=hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
 
	hdc->Polyline(&Pprev[0],N);
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
	
 	hdc->Polyline(&Pt[0],N);


	for (int i=0; i<=N;i++)
	{
	Pprev[i]=Pt[i];
	}
	hdc->SelectObject(oldp);

   hdc->SetROP2(jj); 

	fPrevB=true;
	delete [] M;
//	delete []Para;
	delete []Pt;
	}
	else
	{
		CBezier::DrawDynaBspline(hdc);
	}


}

bool CCercle::getCharge()
{
//	addtovec();

	if (it==2)
	{
		it=0;
		return true;
	}
	else 
	{
		it++;
		return false;
	}
	delete []Pprev;

}


void CCercle::setPtsBegin(CVector point)
{
/*	if ((abs((snapvec.x-point.x)<=20)&&(abs(snapvec.y-point.y)<=20)))
	{
		point=snapvec;
	}*/
	if(it==0)
	{
		control1=point;
	}
	if(it==1)
	{
		control2=point;
	}

}

void CCercle::initL()
{
	fPrevB=false;
	prevref=0;
	prevstart=0;
	minpara=0;
	maxpara=1;
	ncp=8;
//	  CVector v(0,0),
//	  control1=v;
//	  control2=v;
}

bool CCercle::DrawEllipse(bool fPrevB,CDC *hdc, CVector p)
{
	pt=p;


				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
	if(it>1)
	{

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;



/*	 CVector b1,b2,bi,ba,l1,l2;

	 Ct=control1;

	 CPoint pCt(Ct);

	 CPoint ppt(pt);
	 CVector vppt(ppt.x,ppt.y);
	 CPoint pc2(control2);
	 CVector vpc2(pc2.x,pc2.y);

	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 r=vpCt-vpc2;
	 CVector r3=vpCt-vppt;

	 r=Ct-control2;
	 r3=Ct-pt;
	 
	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=control1;
	 p1=p8-vry*absc(r3);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r3);
	 p5=p4+vry*absc(r3);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);


	 CPoint p1l(p1.x,p1.y),p2l(p2.x,p2.y),p3l(p3.x,p3.y),p4l(p4.x,p4.y),p5l(p5.x,p5.y),p6l(p6.x,p6.y),p7l(p7.x,p7.y),p8l(p8.x,p8.y);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;
*/
	 CVector b1,b2,bi,ba,l1,l2;
/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/
	 Ct=control1;

	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	
	 r=Ct-control2;
	 b1=Ct-pt;
	 control3=Ct-pt;

	 double alpha=pi/4;

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(absc(control3-r),argu(control3-r));
	 p2=Ct+polarc(absc(control3),argu(control3));
	 p3=Ct+polarc(absc(control3+r),argu(control3+r));
	 p8=Ct+polarc(absc(r*(-1)),argu(r*(-1)));
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(absc((control3*(-1))-r),argu((control3*(-1))-r));
	 p6=Ct+polarc(absc(control3),argu(control3*(-1)));
	 p5=Ct+polarc(absc((control3*(-1))+r),argu((control3*(-1))+r));
	 

	 CP[0]=p8;
   	 CP[1]=p1;
   	 CP[2]=p2;
   	 CP[3]=p3;
   	 CP[4]=p4;
   	 CP[5]=p5;
   	 CP[6]=p6;
   	 CP[7]=p7;
   	 CP[8]=p8;

	double ang=argu(r)-argu(b1);
 	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
 	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2); 


	degel();
	double a=4*(sqrt(2)-1)/3;
	for(int jo=0;jo<13;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<13)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(13);
	for(int ji=0;ji<13;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
	return CBezier::draw(fPrevB,hdc,p);
	
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);
   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }



     CPoint *Pt=new CPoint[N+1];
   int ss;
   for(iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   ss=iter;
	}
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    if(cl)    hdc->BeginPath();
 
	hdc->Polyline(Pprev,ss);
    
	if(cl)
    {
     hdc->EndPath();
	 hdc->FillPath();
    }
	
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
    if(cl)    hdc->BeginPath();
 	hdc->Polyline(Pt,ss);

   if(cl)
   {
    hdc->EndPath();
	hdc->FillPath();
   }

	for (i=0; i<=ss;i++)
	{
	Pprev[i]=Pt[i];
	}

	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);


	fPrevB=true;
    delete [] M;
//	delete []Para;
	delete []Pt;
	}
	
	return true;

}



bool CCercle::DrawCircle(bool fPrevB,CDC *hdc, CVector p)
{
	pt=p;
	Ct=control1;

//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn.resize(12);
		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;


	 r=Ct-pt;


	 double alpha=pi/4;

	 CPoint pCt(Ct);

	 CPoint ppt(pt);
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 
/*	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=vpCt+polarc(sqrt(2)*absc(vpr),5*alpha);
	 p2=vpCt+polarc(absc(vpr),6*alpha);
	 p3=vpCt+polarc(sqrt(2)*absc(vpr),7*alpha);
	 p8=vpCt+polarc(absc(vpr),pi);
	 p4=vpCt+polarc(absc(vpr),0);
	 p7=vpCt+polarc(sqrt(2)*absc(vpr),3*alpha);
	 p6=vpCt+polarc(absc(vpr),pi/2);
	 p5=vpCt+polarc(sqrt(2)*absc(vpr),alpha);
	 
	 CPoint p1l(p1.x,p1.y),p2l(p2.x,p2.y),p3l(p3.x,p3.y),p4l(p4.x,p4.y),p5l(p5.x,p5.y),p6l(p6.x,p6.y),p7l(p7.x,p7.y),p8l(p8.x,p8.y);
*/

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();
	double a=4*(sqrt(2)-1)/3;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=Ct-vrx*absc(r);
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);

	degel();
	for(int jo=0;jo<13;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<13)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}

	ContP.clear();
	ContP.resize(13);
	for(int ji=0;ji<13;ji++)
	{
		
		ContP[ji]=CP[ji];
	}

/*	ContP[0]=CP[0];
	ContP[1]=CP[1];
	ContP[2]=CP[3];	
	ContP[3]=CP[4];
	ContP[4]=CP[5];
	ContP[5]=CP[7];
	ContP[6]=CP[8];*/

//	return CBezier::draw(fPrevB,hdc,p);
    
   CVector *M;
   M=new CVector[N+1];

   if(Mr==NULL) Mr=new CVector[N+1];

   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
//   Para.resize(N+1);
   Para_universp(0,1,N,Para);
   double g=Para[50];

   for(int iter=0;iter<N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
//	   M[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
   }



   CPoint *Pt=new CPoint[N+1];
   int s;//=0;
   for(iter=0;iter<N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   s=iter;
	}
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    if(cl)    hdc->BeginPath();
 
	hdc->Polyline(Pprev,s);
    
	if(cl)
    {
     hdc->EndPath();
	 hdc->FillPath();
    }
	
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
	
    if(cl)    hdc->BeginPath();
 	hdc->Polyline(Pt,s);

   if(cl)
   {
    hdc->EndPath();
	hdc->FillPath();
   }

	for (i=0; i<=s;i++)
	{
	Pprev[i]=Pt[i];
	}

	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);


   delete [] M;
//   delete []Para;
   delete []Pt;
	
   return true;

}


bool CCercle::DrawArc(bool fPrevB,CDC *hdc, CVector p)
{
	ntype="Arc";
	pt=p;
	Ct=control1;

	if(it>1)
	{

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(9);
//	Kn.resize(12);

	try
	{
		Kn.at(0) = 0;
		Kn.at(1) = 0;
		Kn.at(2) = 0;
		Kn.at(3) = (double)1 / 4;
		Kn.at(4) = (double)1 / 4;
		Kn.at(5) = (double)1 / 2;
		Kn.at(6) = (double)1 / 2;
		Kn.at(7) = (double)3 / 4;
		Kn.at(8) = (double)3 / 4;
		Kn.at(9) = 1;
		Kn.at(10) = 1;
		Kn.at(11) = 1;
	}
	catch (...)
	{

	}

/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/
	 CString fg=control1.setplanesnap("front");

	 alpha = pi/4;
	 r=control2-Ct;
	 CVector r2= pt - Ct;
	 r2.Normalise();
	 pt=Ct + r2*absc(r);



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control2.assign(control2);
	 r=Ct-control2;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control2.assignInv(control2);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
	CP[0]=p4;
   	CP[1]=p5;//p3;
   	CP[2]=p6;//p2;
   	CP[3]=p7;//p1;
   	CP[4]=p8;
   	CP[5]=p1;//p7;
   	CP[6]=p2;//p6;
   	CP[7]=p3;//p5;
   	CP[8]=p4;
	 
	for (int i=0;i<ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
	 r2= pt - Ct;
	 r2.Normalise();
    setArc(control2,pt); 
	if(ncp==1)
	{
		int degp=1;
		return TRUE;

	}
	  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	vector<CVector> vcenter;
	vcenter.push_back(p4);
	vcenter.push_back(p6);
	vcenter.push_back(p8);
	vcenter.push_back(p2);

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			//CVector* n=&(*find(vcenter.begin(),vcenter.end(),CP[jo]));
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}

	CBezier::draw(fPrevB,hdc,p);
	CString sp;
	float g=(360*angle)/(2*pi);
	sp.Format(_T("Angle:%.2f"),g);//*delta);
	CPoint pv=Ct;
	hdc->TextOut(pv.x,pv.y,sp);
	return TRUE; 
	  
/*	  CVector ng=Ct+polarc(absc(r),argu(Ct-pt)-pi);

	 double alpha=pi/4;

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),argu(r)-5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)-6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),argu(r)-7*alpha);
	 p4=Ct+polarc(absc(r),argu(r)-8*alpha);
	 p5=Ct+polarc(sqrt(2)*absc(r),argu(r)-alpha);
	 p6=Ct+polarc(absc(r),argu(r)-2*alpha);
	 p7=Ct+polarc(sqrt(2)*absc(r),argu(r)-3*alpha);
	 p8=Ct+polarc(absc(r),argu(r)-4*alpha);
	 
	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

  //  INT_curve(CP,ncp,deg,Kn,Kn,CP);
  //  ncp+=2;
 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
*/    

   if(Mr==NULL) Mr=new CVector[N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg+1]*N;
start = lk;
end= lh;

   Para_universp(0,1,N,Para);
   for(int iter=lk;iter<=lh;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }


/*	 r=Ct-control2;r.z=0;//pt;
	CString sw=r.setplanesnap("front");
	 CVector ng=Ct+polarc(absc(r),argu(Ct-pt)-pi);

	 double alpha=pi/4;

	 CPoint pCt(Ct);

	 CPoint ppt(control2);
	 CVector pct2(ppt.x,ppt.y);
	 
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 CTVector t;
	 CVector vpr1=-pct2;
	 t.Translate(vpr1);
	 t.TRotate(-argu(vpr));
	 t.endT();
	 vpCt.assign(vpCt);
	 vpr.assign(vpr);
	 pct2.assign(pct2);
	 vpr=vpCt-pct2;
	 
	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=vpCt+polarc(sqrt(2)*absc(vpr),5*alpha);
	 p2=vpCt+polarc(absc(vpr),6*alpha);
	 p3=vpCt+polarc(sqrt(2)*absc(vpr),7*alpha);
	 p8=vpCt+polarc(absc(vpr),pi);
	 p4=vpCt+polarc(absc(vpr),0);
	 p7=vpCt+polarc(sqrt(2)*absc(vpr),3*alpha);
	 p6=vpCt+polarc(absc(vpr),pi/2);
	 p5=vpCt+polarc(sqrt(2)*absc(vpr),alpha);
	 
	 p5.setplanesnap(sw);
	 
	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 
	 CPoint p1l(p1.x,p1.y),p2l(p2.x,p2.y),p3l(p3.x,p3.y),p4l(p4.x,p4.y),p5l(p5.x,p5.y),p6l(p6.x,p6.y),p7l(p7.x,p7.y),p8l(p8.x,p8.y);
	 t.pushUnit();

	CP[0]=p8l;
   	CP[1]=p1l;
   	CP[2]=p2l;
   	CP[3]=p3l;
   	CP[4]=p4l;
   	CP[5]=p5l;
   	CP[6]=p6l;
   	CP[7]=p7l;
   	CP[8]=p8l;

 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
    
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg]*N;
 //  Para=new double [N+1];
   Para_universp(0,1,N,Para);
   for(int iter=0;iter<N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
 
   vector<int> bv;
	   indexpos.clear();
	   indexpos.resize(2);
	   indexpos[0]=control2;
	for(iter=0;iter<N;iter++)
   {
	   CRay l1(Mr[iter],Mr[iter+1],1);
	   CVector v(control1,Mr[iter+1]);
	   CVector vl(control1,pt);
	   float f=v.dot(vl);

	   CRay l(control1,pt);
	   CRay l2(control1,control2);
		CVector i=l1.Intersect(l);
	   if((i.x!=1E-10)&&(f>0))
	   {
		   indexpos[1]=i;
		   bv.push_back(iter);
	   }
       CVector i1=l1.Intersect(l2);
	   if(i1.x!=1E-10)
	   {
		   indexpos[0]=i1;
		   bv.push_back(iter);
	   }

   }
*/
	

   
   CPoint *Pt=new CPoint[N+1];
   int s=0;
   for(iter=lk;iter<=lh;iter++)
	 {
	   Pt[iter]=Mr[iter];
	}
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    s=prevref-prevstart;
	hdc->Polyline(&Pprev[prevstart],s);//-prevstart);
	hdc->MoveTo(control1);
	hdc->LineTo(endpoint);
	}
	else
	{
	Pprev=new CPoint[N+1];
	hdc->MoveTo(control1);
	hdc->LineTo(control2);
	}
//	s=max(ref,start)-min(start,ref);
	s=end-start;
 	hdc->Polyline(&Pt[start],s);//min(start,ref)],s);
	hdc->MoveTo(control1);
	hdc->LineTo(Mr[lh]);

	for (i=0; i<=N;i++)
	{
	Pprev[i]=Pt[i];
	}

	prevref=end;
	prevstart=start;
   lk=prevstart;
   lh=prevref;

	startpoint=control1;
	endpoint=Mr[lh];


   	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);

   delete []Pt;
   }
   return true;

}




bool CCercle::Draw2DotCircle(bool fPrevB,CDC *hdc, CVector p)
{
	pt=p;
	control2=control1;

//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;


/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/
/*	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=Ct-pt;
	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p3=Ct+polarc(absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p1=Ct+polarc(absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(absc(r),alpha);
*/

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	CVector v1=pt;
	CVector v2=control1;
	CVector v3=v1-v2;
	
	vrx1=vrx*(v3.dot(vrx));
	vry1=vry*(v3.dot(vry));

	CVector v3x=v2+vrx1;
	CVector v3y=v2+vry1;//(v3.dot(vry));


	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=pt-Ct;
	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=control1;
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);


	 
	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);


	degel();
	double a=4*(sqrt(2)-1)/3;
	for(int jo=0;jo<13;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<13)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(13);
	for(int ji=0;ji<13;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
	return CBezier::draw(fPrevB,hdc,p);
    
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
//	   M[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
   }


  
   CPoint *Pt=new CPoint [N+1];
   int s;
   for(iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   s=iter;
	}
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    if(cl)    hdc->BeginPath();
 
	hdc->Polyline(&Pprev[0],s);
    
	if(cl)
    {
     hdc->EndPath();
	 hdc->FillPath();
    }
	
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
	
    if(cl)    hdc->BeginPath();
 	hdc->Polyline(Pt,s);

   if(cl)
   {
    hdc->EndPath();
	hdc->FillPath();
   }

	for (i=0; i<=s;i++)
	{
	Pprev[i]=Pt[i];
	}

	hdc->SelectObject(oldb);
	hdc->SelectObject(oldp);

   delete [] M;
//   delete []Para;
   delete []Pt;
	
   return true;

}

bool CCercle::Draw2DotArc(bool fPrevB,CDC *hdc, CVector p)
{
	ntype="Arc";
/*	pt=p;
	control2=control1;


				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	


		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;




	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=Ct-pt;

	 CVector ng=Ct+polarc(absc(r),argu(r)-pi);
	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CPoint pCt(Ct);

	 CPoint ppt(pt);
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 
	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=control1;
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
    
	start=0;
	end=N-1;
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];


   lk=Kn[deg]*N;

   lh=Kn[ncp+deg]*N;
	
   Para_universp(0,1,N,Para);
   for(int iter=0;iter<N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
*/
	pt=p;
	control2=control1;

//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(9);

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);
	try {
		Kn.at(0) = 0;
		Kn.at(1) = 0;
		Kn.at(2) = 0;
		Kn.at(3) = (double)1 / 4;
		Kn.at(4) = (double)1 / 4;
		Kn.at(5) = (double)1 / 2;
		Kn.at(6) = (double)1 / 2;
		Kn.at(7) = (double)3 / 4;
		Kn.at(8) = (double)3 / 4;
		Kn.at(9) = 1;
		Kn.at(10) = 1;
		Kn.at(11) = 1;
	}
	catch (...)
	{

	}



/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	CVector v1=pt;
	CVector v2=control1;
	CVector v3=v1-v2;
	
	vrx1=vrx*(v3.dot(vrx));
	vry1=vry*(v3.dot(vry));

	CVector v3x=v2+vrx1;
	CVector v3y=v2+vry1;//(v3.dot(vry));


	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=pt-Ct;

	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	CVector t=r;//vrx*r.x+vry*r.y+vrz*r.z;
	CVector dt=polarc(absc(t),argu(t)+pi/2);
//	dt=vrx*dt.x+vry*dt.y+vrz*dt.z;
	double ff=dt.dot(t);
	 p8=control1;
	 p1=p8-dt;//vry*absc(r);
	 p2=p1+t;//vrx*absc(r)*f;
	 p3=p2+t;//vrx*absc(r)*f;
	 p4=p3+dt;//vry*absc(r);
	 p5=p4+dt;//vry*absc(r);
	 p6=p5-t;//vrx*absc(r)*f;
	 p7=p6-t;//vrx*absc(r)*f;

	 
	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
	
	degel();
    setArc(control1,p);
	double a=4*(sqrt(2)-1)/3;
	int d=CP.size();

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}

	return CBezier::draw(fPrevB,hdc,p);

   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   start = lk;
   end = lh;

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<=lh;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
//	   M[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
   }
   
   
   
/*   
   vector<int> bv;
   indexpos.clear();
   indexpos.resize(2);
   for(iter=0;iter<N;iter++)
   {
	   CRay l1(Mr[iter],Mr[iter+1],1);

	   CRay l(control1,pt,1);
		CVector i=l1.Intersect(l);
	   if(i.x!=1E-10)
	   {
		   indexpos[1]=pt;
		   indexpos[0]=control1;
		   bv.push_back(iter);
	   }

   }
   start=bv[0];
   end=bv[1];
   int g=start;
   start=(start>end)?end:start;
   end=(end>g)?end:g;
  if(start!=g)
   {
	   CVector j;
	   j=indexpos[0];
	   indexpos[0]=indexpos[1];
	   indexpos[1]=j;
   }
 
   lk=start;
   lh=end;
*/
   CPoint *Pt=new CPoint[N+1];
   int s=0;
   for(iter=0;iter<=lh;iter++)
	 {
	   Pt[iter]=Mr[iter];
	}
   s=prevref-prevstart;
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	hdc->Polyline(&Pprev[prevstart],s);
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
	s=end-start;
 	hdc->Polyline(&Pt[start],s);
	
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);

	for (i=0; i<=lh;i++)
	{
	Pprev[i]=Pt[i];
	}

	prevref=end;//max(start,ref);
	prevstart=start;//min(start,ref);

	startpoint=control2;
    CVector ng=Ct+polarc(absc(r),argu(r)-pi);
	endpoint=ng;

   if(prevstart!=start)
   {
		CVector m=endpoint;
		endpoint=startpoint;
		startpoint=m;
   }

   delete [] M;
//   delete []Para;
   delete []Pt;
	redraw=true;
   return true;

}

bool CCercle::Draw3DotCircle(bool fPrevB,CDC *hdc, CVector p)
{
	pt=p;


//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
	if(it>1)
	{

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;
/*
	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/

	 CVector b1,b2,bi,ba,l1,l2;
	 CVector t1(-400,0),t2(600,0),t3(-500,80);



/*	 b1=(control2+control1)/2;


	 CVector ra=b1-control1;
	 
	 CPoint pb1(b1);
	 CVector vpb1(pb1.x,pb1.y);

	 CPoint pc1(control1);
	 CVector vpc1(pc1.x,pc1.y);

	 ra=vpb1-vpc1;

	 ba=vpb1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=vpb1.intersect(ba);

	 b2=(pt+control1)/2;
	 
	 CVector r1=b2-control1;

	 CPoint pb2(b2);
	 CVector vpb2(pb2.x,pb2.y);

		
	 r1=vpb2-vpc1;


	 bi=vpb2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(vpb2);
	 
	 Ct=l1.intersect(l2);
	 
	 CPoint pCt1(Ct.x,Ct.y);
	 Ct=pCt1;
	
	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	

	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);


	 CPlane tri(control1,control2,pt);

//	 Ct=tri.getCircumC();
	 double rC=tri.getCircumR();
	 r=Ct-pt;




	 CPoint pCt(Ct);

	 CPoint ppt(pt);
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=control1;
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);
*/


	 b1=(control2+control1)/2;

	 CVector ra=b1-control1;
	 ba=b1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=b1.intersect(ba);

	 b2=(pt+control1)/2;
	 CVector r1=b2-control1;
	 bi=b2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(b2);
	 
	 Ct=l1.intersect(l2);

	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	
	 r=Ct-pt;

	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(absc(r),argu(r)+5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)+6*alpha);
	 p3=Ct+polarc(absc(r),argu(r)+7*alpha);
	 p8=Ct+polarc(absc(r),argu(r)+pi);
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(absc(r),argu(r)+3*alpha);
	 p6=Ct+polarc(absc(r),argu(r)+pi/2);
	 p5=Ct+polarc(absc(r),argu(r)+alpha);

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();
	 p8=Ct-vrx*absc(r);
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;




  //  INT_curve(CP,ncp,deg,Kn,Kn,CP);
  //  ncp+=2;
 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;

	degel();
	double a=4*(sqrt(2)-1)/3;
	for(int jo=0;jo<13;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<13)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(13);
	for(int ji=0;ji<13;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
	return CBezier::draw(fPrevB,hdc,p);
    
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);
   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
//	   M[iter]=Bspline(deg,CP,ncp,Para[iter],Kn);
   }



     CPoint *Pt=new CPoint[N+1];
   int ss;
   lk=0;
   lh=N;
   for(iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	   ss=iter;
	}
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush* oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    if(cl)    hdc->BeginPath();
 
	hdc->Polyline(Pprev,ss);
    
	if(cl)
    {
     hdc->EndPath();
	 hdc->FillPath();
    }
	
	}
	else
	{
	Pprev=new CPoint[N+1];
	}
    if(cl)    hdc->BeginPath();
 	hdc->Polyline(Pt,ss);

   if(cl)
   {
    hdc->EndPath();
	hdc->FillPath();
   }

	for (i=0; i<=ss;i++)
	{
	Pprev[i]=Pt[i];
	}
	
	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);

	fPrevB=true;
    delete [] M;
//	delete []Para;
	delete []Pt;
	//ptsBegin
	}
	
	return true;

}


bool CCercle::Draw3DotArc(bool fPrevB,CDC *hdc, CVector p)
{
	ntype="Arc";
	pt=p;


//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
	if(it>1)
	{

		CP.resize(9);
  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);
		try {
			Kn.at(0) = 0;
			Kn.at(1) = 0;
			Kn.at(2) = 0;
			Kn.at(3) = (double)1 / 4;
			Kn.at(4) = (double)1 / 4;
			Kn.at(5) = (double)1 / 2;
			Kn.at(6) = (double)1 / 2;
			Kn.at(7) = (double)3 / 4;
			Kn.at(8) = (double)3 / 4;
			Kn.at(9) = 1;
			Kn.at(10) = 1;
			Kn.at(11) = 1;
		}
		catch (const std::exception& ex)
		{

		}



	 CVector b1,b2,bi,ba,l1,l2;
	 CVector t1(-400,0),t2(600,0),t3(-500,80);

	 CString fg=b1.setplanesnap("front");
	 CVector v2=control1-control2;
	 CVector vt=pt-control2;
	 CVector vc=v2*vt;
	 if(vc.z<0)
	 {
		 v2=control2;
		 control2=control1;
		 control1=v2;
	 }


	 b1=(control2+control1)/2;


	 CVector ra=b1-control1;

	 ba=b1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=b1.intersect(ba);
	 
	 b2=(pt+control1)/2;
	 
	 CVector r1=b2-control1;

	 bi=b2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(b2);
	 Ct=l1.intersect(l2);
	 b2 = Ct;



	 alpha = pi/4;
	 r=control1-Ct;



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control1.assign(control1);
	 r=Ct-control1;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control1.assignInv(control1);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
	CP[0]=p4;
   	CP[1]=p5;
   	CP[2]=p6;
   	CP[3]=p7;
   	CP[4]=p8;
   	CP[5]=p1;
   	CP[6]=p2;
   	CP[7]=p3;
   	CP[8]=p4;
	 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;

//	pt=p5;
    setArc (control2,control1);  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	vector<CVector> vcenter;
	vcenter.push_back(p4);
	vcenter.push_back(p6);
	vcenter.push_back(p8);
	vcenter.push_back(p2);

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			//CVector* n=&(*find(vcenter.begin(),vcenter.end(),CP[jo]));
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
/*	CString sp;
	float g=(360*angle)/(2*pi);
	sp.Format(_T("Angle:%.2f"),g);//*delta);
	CPoint pv=control1;
	hdc->TextOut(pv.x,pv.y,sp);*/

	return CBezier::draw(fPrevB,hdc,p);
	
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];
   Para_universp(0,1,N,Para);

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg+1]*N;
start = lk;
end= lh;
   int ref=0,vref=0;
   for(int iter=lk;iter<=lh;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
   if(Mr[lh]!=control2)
   {
	   int i=0;
   }

   CPoint *Pt=new CPoint[N+1];

   for(iter=lk;iter<=lh;iter++)
	 {
	   Pt[iter]=Mr[iter];
	}
   int ss=prevref-prevstart;//N-prevstart;
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	hdc->Polyline(&Pprev[prevstart],ss);
    hdc->Rectangle(CRect(endpoint,CSize(10,10)));
	}else
	{
		Pprev=new CPoint[N+1];
	}

	ss=end-start;//N-min(ref,vref);
 	hdc->Polyline(&Pt[start],ss);
    hdc->Rectangle(CRect(Ct,CSize(10,10)));

	for (i=lk; i<=lh;i++)
	{
	Pprev[i]=Pt[i];
	}

	prevref=end;//N;
	prevstart=start;//min(ref,vref);
   lk=prevstart;
   lh=prevref;
	fPrevB=true;

	startpoint=control2;
	endpoint=Ct;

   if(prevstart!=start)//vref)
   {
		startpoint=control1;
   }

   	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);

	delete []Pt;
	}
	
	return true;

}
bool CCercle::Draw3DotArc2(bool fPrevB,CDC *hdc, CVector p)
{
	ntype="Arc";
	pt=p;


//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
	if(it>1)
	{

  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;


	   	CVector vrx,vry,vrz;
		vrx.getcoorx();
		vry.getcoory();
		vrz.getcoorz();

/*	   control2=vrx*control2.x+vry*control2.y+vrz*control2.z;
	   control1=vrx*control1.x+vry*control1.y+vrz*control1.z;
	   pt=vrx*pt.x+vry*pt.y+vrz*pt.z;
*/
/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/
	 CVector b1,b2,bi,ba,l1,l2;
	 CVector t1(-400,0),t2(600,0),t3(-500,80);
//	  CString fg=b1.setplanesnap("front");

	/* control2=t1;
	 control1=t2;
	 p2=t3;*/

	 b1=(control2+control1)/2;
/*	 b1=(t1+t2)/2;
	 l1=b1*t3;
	 l2=t1*t2;
	 b2=l1*l2;
	 b2=polarc(absc(b1-t1),0);*/

	 CVector ra=b1-control1;
	 ba=b1+polarc(absc(ra),argu(ra)+pi/2);
	 CRay ll1(ba,b1,0);
	 l1=b1.intersect(ba);

	 b2=(pt+control1)/2;
	 CVector r1=b2-control1;
	 bi=b2+polarc(absc(r1),argu(r1)+pi/2);
	 CRay ll2(bi,b2,0);
	 l2=bi.intersect(b2);
	 
	 Ct=l1.intersect(l2);
	 Ct=ll1.Intersect(ll2);

	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	
	 r=Ct-pt;

	 double alpha=pi/4;

	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),argu(r)+5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)+6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),argu(r)+7*alpha);
	 p8=Ct+polarc(absc(r),argu(r)+pi);
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(sqrt(2)*absc(r),argu(r)+3*alpha);
	 p6=Ct+polarc(absc(r),argu(r)+pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),argu(r)+alpha);

//	 b1.setplanesnap(fg);
	 
//	   control2=vrx*control2.x+vry*control2.y+vrz*control2.z;

	 CP[0]=p8;//vrx*p8.x+vry*p8.y+vrz*p8.z;
   	 CP[1]=p1;//vrx*p1.x+vry*p1.y+vrz*p1.z;
   	 CP[2]=p2;//vrx*p2.x+vry*p2.y+vrz*p2.z;
   	 CP[3]=p3;//vrx*p3.x+vry*p3.y+vrz*p3.z;
   	 CP[4]=p4;//vrx*p4.x+vry*p4.y+vrz*p4.z;
   	 CP[5]=p5;//vrx*p5.x+vry*p5.y+vrz*p5.z;
   	 CP[6]=p6;//vrx*p6.x+vry*p6.y+vrz*p6.z;
   	 CP[7]=p7;//vrx*p7.x+vry*p7.y+vrz*p7.z;
   	 CP[8]=p8;//vrx*p8.x+vry*p8.y+vrz*p8.z;

  //  INT_curve(CP,ncp,deg,Kn,Kn,CP);
  //  ncp+=2;
 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
    
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   int lk=Kn[deg]*N;

   int lh=Kn[ncp]*N;

   Para_universp(0,1,N,Para);
   int ref=0,vref=0;
   	   indexpos.clear();
	   indexpos.resize(2);

	   

	   indexpos[0]=control2;
	   indexpos[1]=pt;

   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);

	   if(pointinRegion(Mr[iter],control1)) 
	   {
		   ref=iter;
	   }
	   if (pointinRegion(Mr[iter],control2))
	   {
		   vref=iter;
	   }
   }

	if(vref>ref) indexpos[0]=control1;


   CPoint *Pt=new CPoint[N+1];
   int ss=0;
   for(iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	}
   ss=N-prevstart;
	

	CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
    if(cl)    hdc->BeginPath();
 
	hdc->Polyline(&Pprev[prevstart],ss);
    
	if(cl)
    {
     hdc->EndPath();
	 hdc->FillPath();
    }
	
	}
	{
		Pprev=new CPoint[N+1];
	}

	ss=N-min(ref,vref);
    if(cl)    hdc->BeginPath();
 	hdc->Polyline(&Pt[min(ref,vref)],ss);
	start=min(ref,vref);
	end=N;

   if(cl)
   {
    hdc->EndPath();
	hdc->FillPath();
   }

	for (i=0; i<=N;i++)
	{
	Pprev[i]=Pt[i];
	}

	prevref=N;
	prevstart=min(ref,vref);
		
	fPrevB=true;

	startpoint=control2;
	endpoint=pt;

   if(prevstart!=vref)
   {
	/*	CVector m=endpoint;
		endpoint=startpoint;*/
		startpoint=control1;
   }

   	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);

	delete []Pt;
	//ptsBegin
	}
	
	return true;

/*	pt=p;


				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
	if(it>1)
	{


		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;



	 CVector b1,b2,bi,ba,l1,l2;
	 CVector t1(-400,0),t2(600,0),t3(-500,80);

	 b1=(control2+control1)/2;


	 CVector ra=b1-control1;
	 
	 CPoint pb1(b1);
	 CVector vpb1(pb1.x,pb1.y);

	 CPoint pc1(control1);
	 CVector vpc1(pc1.x,pc1.y);

	 ra=vpb1-vpc1;

	 CString sw=r.setplanesnap("front");

	 ba=vpb1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=vpb1.intersect(ba);

	 b2=(pt+control1)/2;
	 
	 CVector r1=b2-control1;

	 CPoint pb2(b2);
	 CVector vpb2(pb2.x,pb2.y);

		
	 r1=vpb2-vpc1;


	 bi=vpb2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(vpb2);
	 
	 Ct=l1.intersect(l2);
	 
	 CPoint pCt1(Ct.x,Ct.y);
	 Ct=pCt1;



	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	
	 r=Ct-pt;

	 double alpha=pi/4;

	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CPlane tri(control1,control2,pt);

//	 Ct=tri.getCircumC();
	 double ol1=absc(CVector(Ct,pt));
	 double ol2=absc(CVector(Ct,control1));
	 double ol3=absc(CVector(Ct,control2));
	 double rC=tri.getCircumR();
	 r=Ct-pt;


	 CPoint pCt(Ct);

	 CPoint ppt(control1);
	 CVector pct1(ppt.x,ppt.y);//control1);
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 CTVector t;
	 CVector vpr1=-pct1;
	 t.Translate(vpr1);
	 t.TRotate(-argu(vpr));
	 t.endT();
	 vpCt.assign(vpCt);
	 vpr.assign(vpr);
	 pct1.assign(pct1);
	 vpr=vpCt-pct1;
	 
	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=vpCt+polarc(sqrt(2)*absc(vpr),5*alpha);
	 p2=vpCt+polarc(absc(vpr),6*alpha);
	 p3=vpCt+polarc(sqrt(2)*absc(vpr),7*alpha);
	 p8=vpCt+polarc(absc(vpr),pi);
	 p4=vpCt+polarc(absc(vpr),0);
	 p7=vpCt+polarc(sqrt(2)*absc(vpr),3*alpha);
	 p6=vpCt+polarc(absc(vpr),pi/2);
	 p5=vpCt+polarc(sqrt(2)*absc(vpr),alpha);

 	 p5.setplanesnap(sw);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 
	 CPoint p1l(p1.x,p1.y),p2l(p2.x,p2.y),p3l(p3.x,p3.y),p4l(p4.x,p4.y),p5l(p5.x,p5.y),p6l(p6.x,p6.y),p7l(p7.x,p7.y),p8l(p8.x,p8.y);

	 t.pushUnit();
	CP[0]=p8l;
   	CP[1]=p1l;
   	CP[2]=p2l;
   	CP[3]=p3l;
   	CP[4]=p4l;
   	CP[5]=p5l;
   	CP[6]=p6l;
   	CP[7]=p7l;
   	CP[8]=p8l;
	 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
    
   CVector *M;
   M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   Para=new double [N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);
   int ref=0,vref=0;
   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }

   vector<int> bv,bo;
   indexpos.clear();
   indexpos.resize(2);
   for(iter=0;iter<N;iter++)
   {
	   CRay l1(Mr[iter],Mr[iter+1],1);
	   CRay l(control1,control2,1);
	   CRay lo(control1,pt,1);

	   CVector v(control1,Mr[iter+1]);
	   CVector vl(control1,pt);
	   float f=v.dot(vl);

	   CVector i=l1.Intersect(l);
	   if((i.x!=1E-10)&&(iter!=0))
	   {
		   indexpos[1]=i;
		   indexpos[0]=control1;
		   bv.push_back(iter);
	   }
	   CVector io=l1.Intersect(lo);
	   if((io.x!=1E-10)&&(iter!=0))
	   {
		   bo.push_back(iter);
	   }

   }
   end=N;
   if(bo.size()>0)
	   end=bo[0];
   start=0;//(end>bo[0])?0:N;

   CPoint *Pt=new CPoint[N+1];
   int ss=0;
   for(iter=0;iter<=N;iter++)
	 {
	   Pt[iter]=Mr[iter];
	}
   ss=prevref-prevstart;//N-prevstart;
	
    CPen pen;
	pen.CreatePen(PS_SOLID,lwidth,lcolor);
	CPen *oldp=hdc->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

	hdc->SetROP2(R2_NOTXORPEN); 
   
	if (fPrevB)
	{
	hdc->Polyline(&Pprev[prevstart],ss);
	}else
	{
		Pprev=new CPoint[N+1];
	}

	ss=end-start;//N-min(ref,vref);
 	hdc->Polyline(&Pt[start],ss);//min(ref,vref)],ss);


	for (i=0; i<=N;i++)
	{
	Pprev[i]=Pt[i];
	}

	prevref=end;//N;
	prevstart=start;//min(ref,vref);
   lk=prevstart;
   lh=prevref;
	fPrevB=true;

	startpoint=control2;
	endpoint=pt;

   if(prevstart!=start)//vref)
   {
		startpoint=control1;
   }

   	hdc->SelectObject(oldp);
	hdc->SelectObject(oldb);

	delete [] M;
	delete []Pt;
	}
	
	return true;
*/
}

CCercle CCercle::mirror(CDC *hdc, CCercle *citer)
{
	CCercle result;
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
		vector<CVector>::iterator pitereex=citer->ptend.begin();
	
		for(piterbex=citer->ptbegin.begin();piterbex<citer->ptbegin.end();piterbex++)
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
	
		if ((pitereex+1)<citer->ptend.end())
		{
		pitereex=pitereex+1;
		}
	}
 		
		
	if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}

	}

	result.addvec(testb,teste);
	result.draw(hdc);
//	result.create();
	return result;
}


//DEL void CCercle::sethandle(int hn)
//DEL {
//DEL 	handle=hn;
//DEL 
//DEL }

//DEL int CCercle::gethandle()
//DEL {
//DEL 	return handle;
//DEL 
//DEL }

/*void CCercle::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
if(!surf)
{
	if((linestate==D4)||(getmultcore()))
	{
		prevptend=ptend;
		prevptbegin=ptbegin;
//		updatecore();
		TransformRect(prevpos,postpos);

		drawTrans(hdc);


	}
	else
	{
	bool alr=false,ale=false;
	prevptend=ptend;
	prevptbegin=ptbegin;
	pitere=ptend.begin();
	CVector mouseVect(prevpos,postpos);
	if(mode==art)
	{
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{
		ptsBegin=*piterb;
		ptsEnd=*pitere;

		CVector vpoint(ptsBegin,prevpos);
		CVector v(ptsBegin,ptsEnd);
	
		if (pointinRegion(ptsBegin,prevpos))
		{
		multiselect=false;
				piterb=ptbegin.erase(piterb);
				piterb=ptbegin.insert(piterb,postpos);
		}
		
		else if (pointinRegion(ptsEnd,prevpos))
		{
		multiselect=false;
		pitere=ptend.erase(pitere);
		pitere=ptend.insert(pitere,postpos);
		}

		if ((pitere+1)<ptend.end())
		{
		pitere=pitere+1;
		}

	}
	}
	else
	if((select==pnt)||(getmultcore()))
	{
		if((ntype=="Circle")||(ntype=="Ellipse"))
		{
	/*		CVector v1(Ct,prevpos);
			CVector v2(Ct,postpos);
			multiselect=false;
			r=absc(v2)>absc(v1)?r+polarc(absc(mouseVect),argu(r)):r-polarc(absc(mouseVect),argu(r));
			control3=absc(v2)>absc(v1)?control3+polarc(absc(mouseVect),argu(control3)):control3-polarc(absc(mouseVect),argu(control3));
			updateCP("rayon");
			drawTrans(hdc);*/
/*
		}
		else
		{
	/*	multiselect=false;
		CVector v(Ct,postpos);
		drawArc(Ct,control1,argu(v));*/
/*}
	} else
	if(select==st)
	{
			CVector v1(Ct,prevpos);
			CVector v2(Ct,postpos);
			multiselect=false;
			r=absc(v2)>absc(v1)?r+polarc(absc(mouseVect),argu(r)):r-polarc(absc(mouseVect),argu(r));
			control3=absc(v2)>absc(v1)?control3+polarc(absc(mouseVect),argu(control3)):control3-polarc(absc(mouseVect),argu(control3));
			updateCP("rayon");
			drawTrans(hdc);
	}

	else if ((select==full)||(multiselect))
	{

	//	if ((pointinRegion(pc,prevpos))||(multiselect))
	//	{
			vector<CVector>::iterator  pite,pitb;
			pite=ptend.begin();
		/*	for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb++)
			{
				
				
				(*pitb).x+=mouseVect.x;
				(*pitb).y+=mouseVect.y;
				(*pite).x+=mouseVect.x;
				(*pite).y+=mouseVect.y;

				//Translate(mouseVect);
				CVector vb=*pitb;
				CVector ve=*pite;
				pitb=ptbegin.erase(pitb);
				pitb=ptbegin.insert(pitb,vb);
		
				pite=ptend.erase(pite);
				pite=ptend.insert(pite,ve);
				if ((pite+1)<ptend.end())
				{
				pite=pite+1;
				}


			}*/
/*				if(transref)
				{
			
					Ct=mouseVect.x>0?\
					Ct+polarc(absc(mouseVect),argu(refline)):Ct-polarc(absc(mouseVect),argu(refline));		
					if(ntype=="Ellipse")
					{
					pt=mouseVect.x>0?\
					pt+polarc(absc(mouseVect),argu(refline)):pt-polarc(absc(mouseVect),argu(refline));		
					}

				}
				else
				{

				Ct+=mouseVect;
				pite=ptend.begin();
				for (pitb=ptbegin.begin();pitb<ptbegin.end();pitb++)
				{
					(*pitb).x+=mouseVect.x;
					(*pitb).y+=mouseVect.y;
					(*pite).x+=mouseVect.x;
					(*pite).y+=mouseVect.y;
					pite++;
				}
				
/*				for (int i=0;i<=ncp;i++)
				{
					CP[i].x+=mouseVect.x;
					CP[i].y+=mouseVect.y;
				}
				addtovec();*/
/*
				if(ntype=="Ellipse") pt+=mouseVect;
				}
//			Ct+=mouseVect;
//			if(ntype=="Ellipse") pt+=mouseVect;
//			pt=postpos;
//			updateCP("centre");
				startpoint=CP[0];
				endpoint=CP[ncp];
				spoint.x+=mouseVect.x;
				spoint.y+=mouseVect.y;

				epoint.x+=mouseVect.x;
				epoint.y+=mouseVect.y;
			   selectvec.clear();
			   selectvec.push_back(startpoint);
			   selectvec.push_back(spoint);
			   selectvec.push_back(epoint); 
			   selectvec.push_back(endpoint); 
			 
				if(!multiselect)
				{
					drawTrans(hdc);
				}
		
		}
	}
			int i=0;
}
else
{
	CBezier::translate(wnd,hdc,prevpos,postpos);

}

}
*/
void CCercle::updateCP(CString s)
{


	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);
	 CVector p1,p3,p4,p5,p6,p7,p8;
	 if(ntype=="Arc")
	 {
	 p1=Ct+polarc(sqrt(2)*absc(r),argu(r)-5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)-6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),argu(r)-7*alpha);
	 p4=Ct+polarc(absc(r),argu(r)-8*alpha);
	 p5=Ct+polarc(sqrt(2)*absc(r),argu(r)-alpha);
	 p6=Ct+polarc(absc(r),argu(r)-2*alpha);
	 p7=Ct+polarc(sqrt(2)*absc(r),argu(r)-3*alpha);
	 p8=Ct+polarc(absc(r),argu(r)-4*alpha);

	 }
	 else
     if(ntype=="Ellipse")
	 {
	 p1=Ct+polarc(absc(control3-r),argu(control3-r));
	 p2=Ct+polarc(absc(control3),argu(control3));
	 p3=Ct+polarc(absc(control3+r),argu(control3+r));
	 p8=Ct+polarc(absc(r*(-1)),argu(r*(-1)));
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(absc((control3*(-1))-r),argu((control3*(-1))-r));
	 p6=Ct+polarc(absc(control3),argu(control3*(-1)));
	 p5=Ct+polarc(absc((control3*(-1))+r),argu((control3*(-1))+r));
	 }
	 else
	 {
	 p1=Ct+polarc(sqrt(2)*absc(r),argu(r)+5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)+6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),argu(r)+7*alpha);
	 p8=Ct+polarc(absc(r),argu(r)+pi);
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(sqrt(2)*absc(r),argu(r)+3*alpha);
	 p6=Ct+polarc(absc(r),argu(r)+pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),argu(r)+alpha);
	 }	 

	 CP[0]=p8;
   	 CP[1]=p1;
   	 CP[2]=p2;
   	 CP[3]=p3;
   	 CP[4]=p4;
   	 CP[5]=p5;
   	 CP[6]=p6;
   	 CP[7]=p7;
   	 CP[8]=p8;

  //  INT_curve(CP,ncp,deg,Kn,Kn,CP);
  //  ncp+=2;
 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
 	CP[1].w=1/sqrt(2);
 	CP[3].w=1/sqrt(2);
 	CP[5].w=1/sqrt(2);
 	CP[7].w=1/sqrt(2);
 
 	addtovec();
}


void CCercle::drawArc(CVector center, CVector startpoint, double angle)
{
	ntype="Arc";
	CVector v(center,startpoint);
//	prevstart=startpoint;
//	CString sw=v.setplanesnap("front");
    ncp=8;
	deg=2;
	double angle2=angle;
	angle=angle>0?angle:-angle;

	CVector endpoint=center+polarc(absc(v),angle+argu(v));
	Ct=center;

	pt=endpoint;
	Ct=control1;
	Ct=center;
	control2=startpoint;


	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(9);



		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;

	 CString fg=control1.setplanesnap("front");

	 alpha = pi/4;
	 r=control2-Ct;
	 CVector r2= pt - Ct;
	 r2.Normalise();
	 pt=Ct + r2*absc(r);



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control2.assign(control2);
	 r=Ct-control2;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control2.assignInv(control2);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
//	 if(angle>0)
//	 {
	CP[0]=p4;
   	CP[1]=p5;
   	CP[2]=p6;
   	CP[3]=p7;
   	CP[4]=p8;
   	CP[5]=p1;
   	CP[6]=p2;
   	CP[7]=p3;
   	CP[8]=p4;
/*	 }else
	 {

	CP[0]=p4;
   	CP[1]=p3;
   	CP[2]=p2;
   	CP[3]=p1;
   	CP[4]=p8;
   	CP[5]=p7;
   	CP[6]=p6;
   	CP[7]=p5;
   	CP[8]=p4;
	 }*/
	for (int i=0;i<ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);

//	 r2= pt - Ct;
//	 r2.Normalise();
    setArc(control2,pt); 
	if(ncp==1)
	{
		int degp=1;
		return ;//TRUE;

	}
	  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}
	if(angle2<0)
	{

	CRay VMainb(Ct,control2);
 	CVector p=VMainb.getclosestPoint(CP[1]);
	CVector n=CP[1]-p;
	n=n/absc(n);
	CVector V(Ct,control2);
	V.dot(n);
	
	CTVector v;
	v.pushTransform();
	v.pushUnit();
	v.Translate(-p);
	v.Reflect(n);
	v.Translate(p);
	v.endT();
	selectvec.clear();
	for (piterb=CP.begin();piterb<CP.end();piterb++)
	{
		piterb->assign(*piterb,true);
	}
	v.popTransform();

	}
	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
   
   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
	addtovec();
	return;

    CVector *M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//   double *Para=new double[N+1];
   Para_universp(0,1,N,Para);

   int s=N-1,e=0;
   for(iter=0;iter<N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
	   CVector ve(Mr[iter],endpoint);
	   CVector vs(Mr[iter],startpoint);
	   if(absc(vs)<1)//pointinRegion(M[iter],startpoint))
	   {
		   e=iter;
	   }
	   if(absc(ve)<1)
	   {
		   s=iter;
	   }

   }
   prevstart=min(e,s);
   prevref=max(e,s);
   lk=prevstart;
   lh=prevref;
 
//   delete []Para;
   delete []M;
  // addtovec();

}

void CCercle::setType(CString type)
{
	ntype=type;
}

void CCercle::setRadius(CVector radius)
{
	r=radius;

}

bool CCercle::PtinRegion(CVector point)
{
	return 	CBezier::PtinRegion(point);

	if(ffd)
	{
	 if(FFDbox->PtinRegion(point)) return true;
	}
if(!box.ccontainpts(point)) return false;
if(!surf)
{
	   if (Rectangleselect(point)&&(!getmultcore()))
	   {
		   click=true;
		   select=pnt;
		   return true;
	   }

	   else
	   {

	   CVector *M=new CVector[N+1];
   if(Mr==NULL) Mr=new CVector[N+1];

//	   Para=new double[N+1];
	   Para_universp(minpara,maxpara,N,Para);

	   lk=Kn[deg]*N;
  
	   for(int iter=0;iter<N;iter++)
	   {
		   CPoint nb=Mr[iter];//NURBS(deg,CP,ncp,Para[iter],Kn);
		   CPoint nbplus=Mr[iter+1];//NURBS(deg,CP,ncp,Para[iter+1],Kn);

			CPoint vpo=CPoint(point)-nb;
			CVector vpoint(vpo.x,vpo.y);//nb,point);
			CPoint vppo=nbplus-CPoint(nb);
		   CVector v(vppo.x,vppo.y);//nb,nbplus);
			CPoint v2=nb+nbplus,v22;
			v2.x=v2.x/2;
			v2.y=v2.y/2;
			v22=v2;
			v2=v2-nb;
			double v11=absc(CVector(v2.x,v2.y));
			v2=v22-point;
			double v12=absc(CVector(v2.x,v2.y));

	  if ((pointtoVector(CVector(vppo.x,vppo.y),CVector(vpo.x,vpo.y))<5)&&(v12<=v11+20))
	  {
			   click=true;
			   petit=iter;
			   select=full;
	//           hitpoint=hitpoint+(*piterb);
			   Rectangleselect(point);
			   selectvec.clear();
			   selectvec.push_back(Ct);
			   selectvec.push_back(Ct);
			   selectvec.push_back(Mr[iter]);//NURBS(deg,CP,ncp,Para[iter],Kn));
//			   delete []Para;
			   delete []M;
			   return true; 
		  } else
			{
				CVector v0(0,0);
				selectvec.clear();
				selectvec.push_back(v0);
				selectvec.push_back(v0);
				selectvec.push_back(v0);
				click=false;
			}
		}

	   delete []M;
//	   delete []Para;
	   }
		click=false;
		return false;
}
else
{
	CBezier::PtinRegion(point);
}

}

bool CCercle::inRegion(CVector point)
{
	if(!box.ccontainpts(point)) 
	{
		return false;
	}

	if(!surf)
	{
	addvec(ptbegin,ptend);
	select=full;
   

   for(int i=0;i<=ncp;i++)
   {
	   if ((pointinRegion(point,CP[i]))&&(!multiselect))
	   {
		   select=pnt;
		   if(CP[i]==ptbegin[1])
		   {
			   select=st;
			   petit=i;
		   }
//		   okj=true;
		   return true;
	   }
   }	


//   Para=new double[N+1];
   Para_universp(minpara,maxpara,N,Para);

   int lk=Kn[deg]*N;
  
   CVector nb;
   CVector nbplus;
   CVector vn;

   CVector v2,v3;
   double v11,v12,v22,v32;
   CVector ln;	
   CVector intp;

   ln=Ct.intersect(point);	
   v3=Ct+point;
   v3=v3/2;

   v22=absc(v3-Ct);


	CVector v0(0,0,0);
	selectvec.clear();
	selectvec.push_back(v0);
	selectvec.push_back(v0);
	selectvec.push_back(v0);
	isclose p(point);
	set<CVector,isclose> vs(p);
	bool b=false;

  
	   for(int iter=0;iter<N;iter++)
	   {
		   CVector vnb=NURBS(deg,CP,ncp,Para[iter],Kn);
		   CVector vnbplus=NURBS(deg,CP,ncp,Para[iter+1],Kn);
		   CPoint nb=vnb;
		   CPoint nbplus=vnbplus;

			CPoint vpo=CPoint(point)-nb;
			CVector vpoint(vpo.x,vpo.y);//nb,point);
			CPoint vppo=nbplus-CPoint(nb);
		   CVector v(vppo.x,vppo.y);//nb,nbplus);
			CPoint v2=nb+nbplus,v22;
			v2.x=v2.x/2;
			v2.y=v2.y/2;
			v22=v2;
			v2=v2-nb;
			double v11=absc(CVector(v2.x,v2.y));
			v2=v22-point;
			double v12=absc(CVector(v2.x,v2.y));

	  if ((pointtoVector(CVector(vppo.x,vppo.y),CVector(vpo.x,vpo.y))<5)&&(v12<=v11+20))
	  {

	  
		   petit=iter;
		   select=full;
//           hitpoint=hitpoint+(*piterb);
//		   Rectangleselect(point);
//		   selectvec.clear();
			CVector d1=vnb-vnbplus;
			CVector ud1=d1/absc(d1);
			CVector pt=point-vnb;
			CVector pd=vnb+ud1*((pt.dot(ud1))/(absc(ud1)*absc(ud1)));
		   vs.insert(vnb);
		   b=true;
//		   selectvec.push_back(Ct);
//		   selectvec.push_back(CVector(Ct,CP[0]));
//		   selectvec.push_back(v);//NURBS(deg,CP,ncp,Para[iter],Kn));
//		   delete []Para;

//			return true;
			} 
	  }
	if(b)
	{ 
	   selectvec.clear();
	   selectvec.push_back(Ct);
	   selectvec.push_back(CVector(Ct,CP[0]));
	   selectvec.push_back(*vs.begin());
	   return true;
	}
	else
	{return false;}

 
/* if (Rectangleselect(point)&&(!getmultcore()))
   {
	   return true;
   }
   else
   {
	return false;
   }*/ 
   }
   else
   {
	   CBezier::inRegion(point);
   }
   
}

/*void CCercle::drawselect(CDC *hdc)
{
	if((!multiselect)&&(!getLibstatus()))
	{
	pitere=ptend.begin();
	int old=hdc->SetROP2(R2_NOTXORPEN);    			
	
	for (piterb=ptbegin.begin();piterb<ptbegin.end();piterb++)
	{

		ptsBegin=*piterb;
		ptsEnd=*pitere;
	
	hdc->MoveTo(ptsBegin); 
	hdc->Ellipse(CRect(CVector(ptsBegin.x-3, ptsBegin.y+3),CVector(ptsBegin.x+3, ptsBegin.y-3)));
	pitere++;
	}
//	ptsEnd=*pitere;
//	hdc->Ellipse(CRect(CVector(ptsEnd.x-5, ptsEnd.y+5),CVector(ptsEnd.x+5, ptsEnd.y-5)));


	/*if (Isrotate)
	{
	hdc->MoveTo(rotateCenter.x,rotateCenter.y-5);
	hdc->LineTo(rotateCenter.x,rotateCenter.y+5);
	hdc->MoveTo(rotateCenter.x-5,rotateCenter.y);
	hdc->LineTo(rotateCenter.x+5,rotateCenter.y);
	}
	
	pitere=pitere+1;
	}*/
	
/*	
		updatecore();	
		vector<CVector>::iterator bonbon;

	hdc->SetROP2(old);    			
	}  			


}
*/
void CCercle::closecurve(CVector pt, CDC *hdc)
{
	cl=true;
	linestate=D4;
	selectSM(hdc);
	draw(hdc);
}


void* CCercle::Trim(vector<CVector> vec)
{
//	return CBezier::Trim(vec);
//	vector<CVector> *arr= new vector<CVector>[2];
	vector<CVector> resultb, resulte;

	indexvec.push_back(petit);indexpos.push_back(v0);
	int minv;
	int mxmin;
	CVector minp,maxp;
	redraw=true;
	

	for(int j=0;j<indexvec.size();j++)
	{
		for(int i=0;i<indexvec.size()-1;i++)
		{
			minv=indexvec[i];minp=indexpos[i];
			mxmin=indexvec[i+1];maxp=indexpos[i+1];
			if(minv>mxmin)
			{
				int mmv=minv; CVector mmp=minp;
				minv=mxmin;minp=maxp;
				mxmin=mmv;maxp=mmp;

			}
			indexvec[i]=minv;indexpos[i]=minp;
			indexvec[i+1]=mxmin;indexpos[i+1]=maxp;
		}
		
	}

	int indexpetit;
	for(j=0;j<indexvec.size();j++)
	{
		if(indexvec[j]==petit)
		{
			indexpetit=j;
	
		}
	}
	if((indexpetit!=0)&&(indexpetit<indexvec.size()-1)&&(indexvec.size()>2))
	{
	double T[50];
	CCercle *bs=new CCercle;
	CVector p,pp;
//	petit=PtonSpline(point);
//	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
	p=/*indexpos[indexpetit-1];*/NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	pp=/*indexpos[indexpetit+1];*/NURBS(deg,CP,ncp,Para[indexvec[indexpetit+1]],Kn);
	cl=false;
	//prevref=indexvec[indexpetit+1];
	bs->copy(*this);
	bs->setType("Arc");
	setType("Arc");
	int s=0;
	int g;
		for(int iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	s=0;
		for(iter=0;iter<=ncp+deg+1;iter++)
		{
			if(Kn[iter]==Para[indexvec[indexpetit+1]])
			{
				s++;
			}
		}
		for(g=0;g<deg-s;g++)
		{
			Bohms(Para[indexvec[indexpetit+1]], deg,Kn,CP,ncp);	
		}

	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				bs->Kn[i]=Kn[i];
				h++;
			}
		}
		bs->Kn[h]=bs->Kn[h-1];
		bs->minpara=bs->Kn[0];
		bs->maxpara=bs->Kn[h];
		for(i=0;i<=h;i++)
		{
			bs->Kn[i]=(bs->Kn[i]-bs->minpara)/(bs->maxpara-bs->minpara);
		}
		bs->minpara=0;
		bs->maxpara=1;

	int b;
		for(i=0;i<=deg;i++)
		{
			T[i]=Para[indexvec[indexpetit+1]];
		}
		
		b=i;
		
		for(i=deg;i<=ncp+deg+1;i++)
		{
			if(Kn[i]>Para[indexvec[indexpetit+1]])
			{
				T[b]=Kn[i];
				b++;
			}
		}

	for(i=0;i<b;i++)
	{
		Kn[i]=T[i];
	}
	minpara=Kn[0];
	maxpara=Kn[b-1];

	for(i=0;i<b;i++)
	{
		Kn[i]=(Kn[i]-minpara)/(maxpara-minpara);
	}
	minpara=0;
	maxpara=1;

//	if (!cl)
//	{	
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	bs->CP[nn]=	indexpos[indexpetit-1];//CP[mi];
	if(nn==0)
	{
		bs->x=-1;
	}
//	if(nn==ncp)
	bs->ncp=nn;
	bs->prevf="Trim";
	bs->addtovec();
	bs->deg=deg;

	int kj;
	for(i=0;i<=ncp;i++)
	{
		if(pp==CP[i])
		{
		kj=i;
		break;
		}
	}
	nn=0;
	for(i=kj;i<=ncp;i++)
	{
		CP[i-kj]=CP[i];
		nn++;
	}
	CP[0]=indexpos[indexpetit+1];

//	bs->Para=new double[N+1];
	Para_universp(bs->minpara,bs->maxpara,N,bs->Para);
	ncp=nn-1;
	prevf="Trim";
	addtovec();
//	delete []Para;
//	bs->redraw=true;
	return bs;
	}
	else if(indexpetit==0)
	{
	double T[50];
	CCercle *bs=new CCercle;
	CVector p,pp;
//	petit=PtonSpline(point);
	bs->copy(*this);
//	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
//	p=NURBS(deg,CP,ncp,Para[0],Kn);
	pp=NURBS(deg,CP,ncp,Para[indexvec[indexpetit+1]],Kn);
//	prevref=indexvec[indexpetit+1];
	cl=false;
	
	int s=0;
	int g;
/*		for(int iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[0])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[0], deg,Kn,CP,ncp);	
			}*/
	s=0;
		for(int iter=0;iter<=ncp+deg+1;iter++)
		{
			if(Kn[iter]==Para[indexvec[indexpetit+1]])
			{
				s++;
			}
		}
		for(g=0;g<deg-s;g++)
		{
			Bohms(Para[indexvec[indexpetit+1]], deg,Kn,CP,ncp);	
		}

	int h=0;
/*		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[0])
			{
				bs->Kn[i]=Kn[i];
				h++;
			}
		}
		bs->Kn[h]=bs->Kn[h-1];*/
	int b;
		for(i=0;i<=deg;i++)
		{
			T[i]=Para[indexvec[indexpetit+1]];
		}
		
		b=i;
		
		for(i=deg;i<=ncp+deg+1;i++)
		{
			if(Kn[i]>Para[indexvec[indexpetit+1]])
			{
				T[b]=Kn[i];
				b++;
			}
		}

	for(i=0;i<b;i++)
	{
		Kn[i]=(T[i]-T[0])/(T[b-1]-T[0]);
	}
	minpara=0;
	maxpara=1;

//	if (!cl)
//	{	
	int nn=0;
/*	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else break;
	}
	bs->CP[nn]=p;*/
		bs->x=-1;
//	if(nn==ncp)
	int kj;
	for(i=0;i<=ncp;i++)
	{
		if(pp==CP[i])
		{
		kj=i;
		break;
		}
	}
	nn=0;
	for(i=kj;i<=ncp;i++)
	{
		CP[i-kj]=CP[i];
		nn++;
	}
	CP[0]=indexpos[indexpetit+1];

//	bs->Para=new double[N+1];
	Para_universp(bs->minpara,bs->maxpara,N,bs->Para);
	ncp=nn-1;
	prevf="Trim";
	addtovec();
//	delete []Para;
//	bs->redraw=true;
	return bs;

	}
	else if(indexvec[indexpetit]==indexvec[indexvec.size()-1])
	{
	double T[50];
	CBezier *bs=new CBezier;
	CVector p,pp;
//	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
	p=NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	cl=false;

	int s=0;
	int iter;
	int g;
		for(iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				Kn[i]=Kn[i];
				h++;
			}
		}
		Kn[h]=Kn[h-1];
		minpara=Kn[0];
		maxpara=Kn[h];
		
		for(i=0;i<=h;i++)
		{
			Kn[i]=(Kn[i]-minpara)/(maxpara-minpara);
		}
		minpara=0;
		maxpara=1;



	int b;
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	CP[nn]=	indexpos[indexpetit-1];//CP[mi];

	bs->x=-1;
	
	ncp=nn;
	prevf="Trim";
	addtovec();
//	delete []Para;
//	bs->redraw=true;
	return bs;

	}
	else if((indexpetit==deg)||(indexpetit==1))
	{
	double T[50];
	CCercle *bs=new CCercle;
	CVector p,pp;
//	Para=new double [N+1];
	Para_universp(minpara,maxpara,N,Para);
	int i,k;
//	bs->linestate=linestate;
//	bs-cl
	p=NURBS(deg,CP,ncp,Para[indexvec[indexpetit-1]],Kn);
	cl=false;

	int s=0;
	int iter;
	int g;
		for(iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[indexvec[indexpetit-1]])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[indexvec[indexpetit-1]], deg,Kn,CP,ncp);	
			}
	int h=0;
		for(i=0;i<=ncp+deg+1;i++)
		{
			if(Kn[i]<=Para[indexvec[indexpetit-1]])
			{
				Kn[i]=Kn[i];
				h++;
			}
		}
		Kn[h]=Kn[h-1];
		minpara=Kn[0];
		maxpara=Kn[h];

		for(i=0;i<=h;i++)
		{
			Kn[i]=(Kn[i]-minpara)/(maxpara-minpara);
		}
		minpara=0;
		maxpara=1;

	int b;
	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		bs->CP[i]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
	bs->CP[nn]=	indexpos[indexpetit-1];//CP[mi];

	bs->x=-1;
	
	ncp=nn;
	prevf="Trim";
	addtovec();
//	delete []Para;
//	bs->redraw=true;
	return bs;

	}


}




void CCercle::computesurface()
{
	r=Ct-CP[0];
	myinfo.surface=2*pi*(pow(r.x,2)+pow(r.y,2));
}

void CCercle::computedist()
{
	r=Ct-CP[0];
	myinfo.distance=4*pi*sqrt(pow(r.x,2)+pow(r.y,2));
}

void CCercle::computeangle(CVector begin, CVector end)
{
	myinfo.angle=argu(Ct-startpoint)-argu(Ct-endpoint);
	angle=myinfo.angle;
}

void CCercle::savefiledxf(CStdioFile& file)
{
	if((ntype=="Arc")||(ntype=="2DotArc")||(ntype=="3DotArc")||(ntype=="3DotArc2"))
	{
		CBezier::savefiledxf(file);
/*		file.WriteString("  0");file.WriteString("\n");
		file.WriteString("ARC");file.WriteString("\n");
		file.WriteString("  5");file.WriteString("\n");
		file.WriteString(gethandle().c_str());file.WriteString("\n");
		file.WriteString("330");file.WriteString("\n");
		file.WriteString("1F");file.WriteString("\n");
		file.WriteString("100");file.WriteString("\n");
		file.WriteString("AcDbEntity");file.WriteString("\n");
		file.WriteString("  8");file.WriteString("\n");
		file.WriteString(getLayer().name);file.WriteString("\n");
		file.WriteString("100");file.WriteString("\n");
		file.WriteString("AcDbCircle");file.WriteString("\n");
		file.WriteString(" 10");file.WriteString("\n");
		CString ps;
		ps.Format(_T("%f"),Ct.x);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 20");file.WriteString("\n");
		ps.Format(_T("%f"),Ct.y);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 30");file.WriteString("\n");
		ps.Format(_T("%f"),Ct.z);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 40");file.WriteString("\n");
		ps.Format(_T("%f"),absc(Ct-ContP[0]));
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString("100");file.WriteString("\n");
		file.WriteString("AcDbArc");file.WriteString("\n");
		file.WriteString(" 50");file.WriteString("\n");
		float start=argu(Ct-ContP[0]);
		start=(start*360)/(2*pi);
		float end=argu(Ct-ContP[ncp-1]);
		end=(end*360)/(2*pi);
		float _u=(start<end)?start:end;
		float _v=(start<end)?end:start;
		start=_v;
		end=_u;
		ps.Format(_T("%f"),start);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 51");file.WriteString("\n");
		ps.Format(_T("%f"),end);
		file.WriteString(ps);file.WriteString("\n");*/
	}else
	{
		file.WriteString("  0");file.WriteString("\n");
		file.WriteString("CIRCLE");file.WriteString("\n");
		file.WriteString("  5");file.WriteString("\n");
		file.WriteString(gethandle().c_str());file.WriteString("\n");
		file.WriteString("330");file.WriteString("\n");
		file.WriteString("1F");file.WriteString("\n");
		file.WriteString("100");file.WriteString("\n");
		file.WriteString("AcDbEntity");file.WriteString("\n");
		file.WriteString("  8");file.WriteString("\n");
		file.WriteString(getLayer().name);file.WriteString("\n");
		file.WriteString("100");file.WriteString("\n");
		file.WriteString("AcDbCircle");file.WriteString("\n");
		file.WriteString(" 10");file.WriteString("\n");
		CString ps;
		ps.Format(_T("%f"),Ct.x);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 20");file.WriteString("\n");
		ps.Format(_T("%f"),Ct.y);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 30");file.WriteString("\n");
		ps.Format(_T("%f"),Ct.z);
		file.WriteString(ps);file.WriteString("\n");
		file.WriteString(" 40");file.WriteString("\n");
		ps.Format(_T("%f"),absc(Ct-ContP[0]));
		file.WriteString(ps);file.WriteString("\n");
	}

}
void CCercle::savefile(CFile &file)
{

   
  file.Write(&Ct,sizeof(Ct));
  file.Write(&start, sizeof(start));
  
  CBezier::savefile(file);


}

void CCercle::openfile(CFile &file)
{

   
  file.Read(&Ct,sizeof(Ct));
  file.Read(&start, sizeof(start));
  
  CBezier::openfile(file);
	
  name="CCercle";

}
LONG CCercle::Readfile(CFile &file)
{
  
  file.Read(&Ct,sizeof(Ct));
  file.Read(&start, sizeof(start));
  
  return CBezier::Readfile(file);

}

CCercle::CCercle(CFile &file)
{
	handle=0;
	prevref=0;
	it=0;
	name="CCercle";
	start=0;
	cl=false;
	lstyle=PS_GEOMETRIC;
//	mode=tech;

   selectvec.push_back(v0);
   selectvec.push_back(v0);
   selectvec.push_back(v0);
   selectvec.push_back(v0);
  
  openfile(file);
}

void CCercle::addtovec(CDC* hdc)
{

		CBezier::addtovecBezier(hdc);
return;
//	vector<CVector> *arr= new vector<CVector>[2];
	if(((ntype=="Arc")||(ntype=="2DotArc")||(ntype=="3DotArc")||(ntype=="3DotArc2"))&&(prevf!="Trim"))
	{
	vector<CVector> resultb, resulte;

	int minv;
	int mxmin;
	CVector minp,maxp;

	double T[50];

	CVector p,pp;
//	Para=new double [N+1];
	minpara=(float)prevstart/N;
	maxpara=(float)prevref/N;

	int i,k;
//	prevref=N;
//	prevstart=0;
//	Para_universp(minpara,maxpara,N,Para);
	p=NURBS(deg,CP,ncp,Para[prevref],Kn);
	pp=NURBS(deg,CP,ncp,Para[prevstart],Kn);
	cl=false;
	int st=deg+1,se=deg+1,s=0;
	int g;
		
			for(int iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[prevref])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[prevref], deg,Kn,CP,ncp);	
			}
	s=0;

			for(iter=0;iter<=ncp+deg+1;iter++)
			{
				if(Kn[iter]==Para[prevstart])
				{
					s++;
				}
			}
			for(g=0;g<deg-s;g++)
			{
				Bohms(Para[prevstart], deg,Kn,CP,ncp);	
			}

	int h=0;
//		T[0]=Para[prevstart];
		for(i=0;i<=ncp+deg+1;i++)
		{
			if((Kn[i]>=Para[prevstart])&&(Kn[i]<=Para[prevref]))
			{
				T[h]=Kn[i];
				h++;
			}
		}
//	h=deg;
		for(i=0;i<deg+1;i++)
		{
			if(T[i]==Para[prevstart])
			{
				st--;
			}
		}
		for(i=0;i<h;i++)
		{
			if(T[i]==Para[prevref])
			{
				se--;
			}
		}

		for(i=0;i<st;i++)
		{
			Kn[i]=0;//Para[prevstart];
		}
		for(i=0;i<h;i++)
		{
			Kn[i+st]=(T[i]-Para[prevstart])/(Para[prevref]-Para[prevstart]);
		}
		for(i=h;i<h+se;i++)
		{
			Kn[i+st]=1;//Para[prevref];
		}


		minpara=0;//Para[prevstart];
		maxpara=1;//Para[prevref];


	int nn=0;
	int mi;
	for(i=0;i<=ncp;i++)
	{
		if(pp==CP[i])
		{
			mi=i;
			break;
		}
	}
	for(i=mi;i<=ncp;i++)
	{
		if(p!=CP[i])
		{
		CP[i-mi]=CP[i];
		nn++;
		}
		else
		{
			mi=i;
			break;
		}
	}
//	startpoint.w=CP[0].w;
//	endpoint.w=CP[mi].w;
	if(indexpos.size()!=0)
	{
	CP[0]=indexpos[0];
	CP[nn]=indexpos[1];//CP[mi];
	ncp=nn;
	}
//	CP[nn]=CP[mi];
//	delete []Para;
	redraw=true;
	}
	CBezier::addtovec();

}
void CCercle::drawArc(CVector start, CVector end)
{
	ntype="Arc";
	CVector p=end;
	pt=end;
	control2=control1=start;

	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(9);


		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;



	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	CVector v1=pt;
	CVector v2=control1;
	CVector v3=v1-v2;
	
	vrx1=vrx*(v3.dot(vrx));
	vry1=vry*(v3.dot(vry));

	CVector v3x=v2+vrx1;
	CVector v3y=v2+vry1;//(v3.dot(vry));


	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=pt-Ct;

	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	CVector t=r;//vrx*r.x+vry*r.y+vrz*r.z;
	CVector dt=polarc(absc(t),argu(t)+pi/2);
//	dt=vrx*dt.x+vry*dt.y+vrz*dt.z;
	double ff=dt.dot(t);
	 p8=control1;
	 p1=p8-dt;//vry*absc(r);
	 p2=p1+t;//vrx*absc(r)*f;
	 p3=p2+t;//vrx*absc(r)*f;
	 p4=p3+dt;//vry*absc(r);
	 p5=p4+dt;//vry*absc(r);
	 p6=p5-t;//vrx*absc(r)*f;
	 p7=p6-t;//vrx*absc(r)*f;

	 
	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
	
	degel();
    setArc(control1,p);
	double a=4*(sqrt(2)-1)/3;
	int d=CP.size();

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
	addtovec();
}
void CCercle::drawArc(CVector start, CVector mid, CVector end)
{
	pt=mid;
	control1=start;
	control2=end;
	ntype="Arc";
//  int *u;
//  int n,p,i;
	; //point on the line

//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	
//	if(it>1)
//	{

		CP.resize(9);
  //   Para=Para_universp(0,1,ncp+1);
  //   Knot_Univer(ncp,deg,Kn,0,1);

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;



	 CVector b1,b2,bi,ba,l1,l2;
	 CVector t1(-400,0),t2(600,0),t3(-500,80);

	 CString fg=b1.setplanesnap("front");
	 CVector v2=control1-control2;
	 CVector vt=pt-control2;
	 CVector vc=v2*vt;
	 if(vc.z<0)
	 {
		 v2=control2;
		 control2=control1;
		 control1=v2;
	 }


	 b1=(control2+control1)/2;


	 CVector ra=b1-control1;

	 ba=b1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=b1.intersect(ba);
	 
	 b2=(pt+control1)/2;
	 
	 CVector r1=b2-control1;

	 bi=b2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(b2);
	 Ct=l1.intersect(l2);
	 b2 = Ct;



	 alpha = pi/4;
	 r=control1-Ct;



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control1.assign(control1);
	 r=Ct-control1;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control1.assignInv(control1);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
	CP[0]=p4;
   	CP[1]=p5;
   	CP[2]=p6;
   	CP[3]=p7;
   	CP[4]=p8;
   	CP[5]=p1;
   	CP[6]=p2;
   	CP[7]=p3;
   	CP[8]=p4;
	 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;

//	pt=p5;
    setArc (control2,control1);  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	vector<CVector> vcenter;
	vcenter.push_back(p4);
	vcenter.push_back(p6);
	vcenter.push_back(p8);
	vcenter.push_back(p2);

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			CVector* n=&(*find(vcenter.begin(),vcenter.end(),CP[jo]));
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}

   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
	addtovec();
}
void CCercle::drawArc2(CVector center, CVector vstart, CVector vend)
{
	ntype="Arc";

	pt=vend;
	if (isnan(center.x)) return;
	Ct=center;//control1;
	control2=vstart;


//  ncp=2;          // number of control points = n+1; for interpolation purpose add +3 to this number
				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(9);



		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;

/*	   control2.snaptoplane(control2);
	   control2.snaptoplane(control1);
	   control2.snaptoplane(pt);
*/
	 CString fg=control1.setplanesnap("front");

	 alpha = pi/4;
	 r=control2-Ct;
	 CVector r2= pt - Ct;
	 r2.Normalise();
	 pt=Ct + r2*absc(r);



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control2.assign(control2);
	 r=Ct-control2;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control2.assignInv(control2);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
	CP[0]=p4;
   	CP[1]=p5;
   	CP[2]=p6;
   	CP[3]=p7;
   	CP[4]=p8;
   	CP[5]=p1;
   	CP[6]=p2;
   	CP[7]=p3;
   	CP[8]=p4;
	 
	for (int i=0;i<ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
	 r2= pt - Ct;
	 r2.Normalise();
	 control2=CP[0];
    setArc(control2,pt); 
	if(ncp==1)
	{
		int degp=1;
		return ;//TRUE;

	}
	  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	vector<CVector> vcenter;
	vcenter.push_back(p4);
	vcenter.push_back(p6);
	vcenter.push_back(p8);
	vcenter.push_back(p2);

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			auto itf = find(vcenter.begin(), vcenter.end(), CP[jo]);
			if (itf == vcenter.end()) continue;
			CVector* n=&(*itf);
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
	addtovec();
	return ;//CBezier::draw(fPrevB,hdc,p);

	
/*	
	Ct=center;
	control1=Ct;
	control2=vstart;
	pt=vend;
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	CP.resize(ncp+1);
	Kn.resize(ncp+deg+2);



		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;

	 CString fg=control1.setplanesnap("front");

	 alpha = pi/4;
	 r=control2-Ct;
	 CVector r2= pt - Ct;
	 r2.Normalise();
	 pt=Ct + r2*absc(r);



	 CTVector t;
	 t.pushTransform();
	 t.pushUnit();
	 t.Translate(-Ct);
	 float l=-argu(r);
	 t.TRotate(l);
	 t.endT();
	 Ct.assign(Ct);
	 r.assign(r);
	 control2.assign(control2);
	 r=Ct-control2;

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);
	 r.setplanesnap(fg);

	 p1.assignInv(p1);
	 p2.assignInv(p2);
	 p3.assignInv(p3);
	 p4.assignInv(p4);
	 p5.assignInv(p5);
	 p6.assignInv(p6);
	 p7.assignInv(p7);
	 p8.assignInv(p8);
	 control2.assignInv(control2);
	 Ct.assignInv(Ct);
	 

	 t.popTransform();
	CP[0]=p4;
   	CP[1]=p5;
   	CP[2]=p6;
   	CP[3]=p7;
   	CP[4]=p8;
   	CP[5]=p1;
   	CP[6]=p2;
   	CP[7]=p3;
   	CP[8]=p4;
	 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	CP[8].w=1;
//    setArc (control2,pt);     
	  
    setArc (control2,pt);  

	degel();
	double a=4*(sqrt(2)-1)/3;
   Para_universp(0,1,N,Para);

   CVector cp;

	int d=CP.size();
	vector<CVector> vcenter;
	vcenter.push_back(p4);
	vcenter.push_back(p6);
	vcenter.push_back(p8);
	vcenter.push_back(p2);

	for(int jo=0;jo<ncp;jo++)
	{
		if(jo%3==0)
		{
			CVector* n=find(vcenter.begin(),vcenter.end(),CP[jo]);
			if(jo+1<d)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo!=ncp-1))
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if((jo-1>0)&&(jo==ncp-1))
			{
			    CVector vp=CP[jo-1]-CP[jo];
				CVector w1(Ct,CP[jo-3]);
				CVector w2(Ct,CP[jo]);
				float f1 = argu(w2) - argu(w1);
				f1=(f1>0)?f1:f1+2*pi;
				f1=2*f1/pi;
				CP[jo-1]=CP[jo]+polarc(f1*a*absc(r),argu(vp));
				vp=CP[jo-2]-CP[jo-3];
				CP[jo-2]=CP[jo-3]+polarc(f1*a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(d);
	for(int ji=0;ji<d;ji++)
	{
		
		ContP[ji]=CP[ji];
	}

	return ;//CBezier::draw(fPrevB,hdc,p);
	  
	  

   if(Mr==NULL) Mr=new CVector[N+1];

   lk=Kn[deg]*N;

   lh=Kn[ncp+deg+1]*N;

   Para_universp(0,1,N,Para);
   for(int iter=lk;iter<=lh;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }

   CBezier::addtovec();
   */
}

CVector CCercle::getCenter()
{
	return Ct;
}
float CCercle::getRadius()
{
	return absc(Ct-ContP[0]);
}

double CCercle::computeAngle()
{
	return angle;

}

bool CCercle::fsnap(CVector &v,CDC*hdc)
{
	CVector h;
	pitere=ptend.begin();
	bool hb=false;
	set<CVector,isfarV> zvec;

  for(piterb=ptbegin.begin();piterb<ptbegin.end();piterb=piterb+2)
  {
	  CVector vb(*piterb,v);
	  if(absc(vb)<=20)
	  {
		  v=*piterb;
		  zvec.insert(v);
		  hb=true;
//		  return true;
	  }
  }
  CVector vc(Ct,v);
  if(absc(vc)<=20)
  {
	  v=Ct;
	  zvec.insert(v);
	  hb=true;
//	  return true;
  }
  if(hb) 
  {
	  v=*zvec.begin();
	  return true;
  }
  if(inRegion(v))
  {
	  v=selectvec[2];
	  return true;
  }

  return false;

}

bool CCercle::inRegionSnap(CVector &point)
{
return true;
}

void CCercle::copy(CCercle &cercle)
{
 Ct=cercle.Ct;
 CBezier::copy(&cercle);
}

CCercle::CCercle(CVector v, float radius,bool arc)
{
	handle=0;
	prevref=0;
	it=0;
	name="CCercle";
	start=0;
	cl=false;
	lstyle=PS_GEOMETRIC;
//	mode=tech;

   selectvec.push_back(v0);
   selectvec.push_back(v0);
   selectvec.push_back(v0);
   selectvec.push_back(v0);

	pt=v+polarc(radius,0);

    Ct=v;

	deg=2;           // degree of polynomial = t-1
    ncp=8;
	


		Kn.resize(12);
		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;


	 r=Ct-pt;


	 double alpha=pi/4;

	 CPoint pCt(Ct);

	 CPoint ppt(pt);
	 CPoint pr=pCt-ppt;
	 CVector vpCt(pCt.x,pCt.y);
	 CVector vpr(pr.x,pr.y);
	 

	CVector vrx,vrx1;vrx.getcoorx();
	CVector vry,vry1;vry.getcoory();
	CVector vrz,vrz1;vrz.getcoorz();
	CVector vro;vro.getcooro();

	 CVector p1,p2,p3,p4,p5,p6,p7,p8;
	 p8=Ct-vrx*absc(r);
	 p1=p8-vry*absc(r);
	 p2=p1+vrx*absc(r);
	 p3=p2+vrx*absc(r);
	 p4=p3+vry*absc(r);
	 p5=p4+vry*absc(r);
	 p6=p5-vrx*absc(r);
	 p7=p6-vrx*absc(r);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

 
	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
//	addtovec();


	degel();
	double a=4*(sqrt(2)-1)/3;
	for(int jo=0;jo<13;jo++)
	{
		if(jo%3==0)
		{
			if(jo+1<13)
			{
			CVector vp=CP[jo+1]-CP[jo];
			CP[jo+1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
			if(jo-1>0)
			{
		    CVector vp=CP[jo-1]-CP[jo];
			CP[jo-1]=CP[jo]+polarc(a*absc(r),argu(vp));
			}
		}
	}


	ContP.clear();
	ContP.resize(13);
	for(int ji=0;ji<13;ji++)
	{
		
		ContP[ji]=CP[ji];
	}
//	return;
//	return CBezier::draw(fPrevB,hdc,p);

  // if(Mr==NULL) Mr=new CVector[N+1];


   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;
   vMr.resize(N);

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<N;iter++)
   {
	   vMr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
	addtovec();

}

CCercle::CCercle(CVector v1, CVector v2, CVector v3,bool arc)
{
	pt=v3;
	control1=v1;
	control2=v2;

	deg=2;           // degree of polynomial = t-1
    ncp=8;
	

		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;

	 CVector b1,b2,bi,ba,l1,l2;


	 b1=(control2+control1)/2;

	 CVector ra=b1-control1;
	 ba=b1+polarc(absc(ra),argu(ra)+pi/2);
	 l1=b1.intersect(ba);

	 b2=(pt+control1)/2;
	 CVector r1=b2-control1;
	 bi=b2+polarc(absc(r1),argu(r1)+pi/2);
	 l2=bi.intersect(b2);
	 
	 Ct=l1.intersect(l2);

	 double s=absc(Ct-pt);
	 double s2=absc(Ct-control2);
	 double s3=absc(Ct-control1);
	
	 r=Ct-pt;

	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),argu(r)+5*alpha);
	 p2=Ct+polarc(absc(r),argu(r)+6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),argu(r)+7*alpha);
	 p8=Ct+polarc(absc(r),argu(r)+pi);
	 p4=Ct+polarc(absc(r),argu(r));
	 p7=Ct+polarc(sqrt(2)*absc(r),argu(r)+3*alpha);
	 p6=Ct+polarc(absc(r),argu(r)+pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),argu(r)+alpha);

	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;


	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
	addtovec();
   if(Mr==NULL) Mr=new CVector[N+1];


   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }

}

CCercle::CCercle(CVector v1, CVector v2,bool arc)
{
	pt=v1;
	control2=control1=v2;

				// when calculating the knot vector
	deg=2;           // degree of polynomial = t-1
    ncp=8;
	


		Kn[0]=0;
		Kn[1]=0;
		Kn[2]=0;
		Kn[3]=(double)1/4;
		Kn[4]=(double)1/4;
		Kn[5]=(double)1/2;
		Kn[6]=(double)1/2;
		Kn[7]=(double)3/4;
		Kn[8]=(double)3/4;
		Kn[9]=1;
		Kn[10]=1;
		Kn[11]=1;

	 Ct=control1+pt;
	 Ct=Ct/2;
	 r=Ct-pt;
	 double alpha=pi/4;
	 CVector tr=polarc(sqrt(2)*absc(r),5*alpha);

	 CVector p1,p3,p4,p5,p6,p7,p8;
	 p1=Ct+polarc(sqrt(2)*absc(r),5*alpha);
	 p2=Ct+polarc(absc(r),6*alpha);
	 p3=Ct+polarc(sqrt(2)*absc(r),7*alpha);
	 p8=Ct+polarc(absc(r),pi);
	 p4=Ct+polarc(absc(r),0);
	 p7=Ct+polarc(sqrt(2)*absc(r),3*alpha);
	 p6=Ct+polarc(absc(r),pi/2);
	 p5=Ct+polarc(sqrt(2)*absc(r),alpha);


	 
	CP[0]=p8;
   	CP[1]=p1;
   	CP[2]=p2;
   	CP[3]=p3;
   	CP[4]=p4;
   	CP[5]=p5;
   	CP[6]=p6;
   	CP[7]=p7;
   	CP[8]=p8;

	for (int i=0;i<=ncp;i++)
	{
		CP[i].w=1;
	}
	CP[1].w=1/sqrt(2);
	CP[3].w=1/sqrt(2);
	CP[5].w=1/sqrt(2);
	CP[7].w=1/sqrt(2);
	addtovec();
   if(Mr==NULL) Mr=new CVector[N+1];


   lk=Kn[deg]*N;
   lh=Kn[ncp+deg]*N;

   Para_universp(0,1,N,Para);

   for(int iter=0;iter<=N;iter++)
   {
	   Mr[iter]=NURBS(deg,CP,ncp,Para[iter],Kn);
   }
}

void CCercle::setArc(CVector v1, CVector v2)
{
	CVector w1(Ct,CP[0]);
	CVector w2(Ct,v2);
	float av;
	float aw2= argu(w2);
	float aw1= argu(w1);

	float f1 = aw2-aw1,f2;//argu(w2) - argu(w1),f2;
//	f1=f1>0?f1:-f1;
	av = f1>0 ? f1:-f1;
	if(av<1E-2)
		f1=0;
	if(f1 < 0)
	{
		f1=f1 + 2*pi;
	}
	f1 = fmod(f1,2*pi);
	f1 = (f1)/(2*pi);
	for(int g=0;g!=ncp + deg + 2 && g < Kn.size();g++)
	{
		av = f1-Kn[g] >0 ? f1-Kn[g]:Kn[g] -f1;
		if(av  <1E-2)
		{
			f1=Kn[g];
			break;
		}
	}
	f2=f1;
	vector<double>::iterator it =deg + ncp + 2 > Kn.size() ? Kn.end() : Kn.begin() + deg + ncp + 2;
	int s = count(Kn.begin(),it, f1); 
	CVector mn= NURBS(deg,CP,ncp,f1,Kn);
	for(g=0;g<deg-s;g++)
	{
		Bohms(f1, deg,Kn,CP,ncp);	
	}
	if(s==0)
	{
		for(g=0;g<=ncp;g++)
		{
//			if(absc(CP[g]-mn)<5)
//					CP[g]=v2;	
		}
	}

	mn= NURBS(deg,CP,ncp,f1,Kn);

	CVector w3(Ct,v1);
	f1 = argu(w3) - argu(w1);
	av = f1>0 ? f1:-f1;
	if(av<1E-2)
		f1=0;
	
	if(f1 < 0)
	{
		f1=f1 + 2*pi;
	}
	f1 = fmod(f1,2*pi);
	f1 = (f1)/(2*pi);
	int itp = ncp + deg + 1 > Kn.size() ? Kn.size() : ncp + deg + 1;
	for(g=0;g!= itp;g++)
	{
		av = f1-Kn[g] >0 ? f1-Kn[g]:Kn[g] -f1;
		if(av <1E-2)
		{
			f1=Kn[g];
			break;
		}
	}
	CVector mn1= NURBS(deg,CP,ncp,f1,Kn);
	it = deg + ncp + 1 > Kn.size() ? Kn.end() : Kn.begin() + deg + ncp + 1;
 	s = count(Kn.begin(),it, f1);
	for(g=0;g<deg-s;g++)
	{
		Bohms(f1, deg,Kn,CP,ncp);	
	}
	if(s==0)
	{
		for(g=0;g<=ncp;g++)
		{
//			if(absc(CP[g]-mn1)<5)
//				CP[g]=v1;	
		}
	}
	
	CVector mn2= NURBS(deg,CP,ncp,f1,Kn);


	float fmin =f1<f2?f1:f2;
	float fmax =f1>f2?f1:f2;
    f1=fmin;
	f2=fmax;
    CVector m = NURBS(deg,CP,ncp,f1,Kn);
	CVector m2 = NURBS(deg,CP,ncp,f2,Kn);
	CVector m3 =NURBS(deg,CP,ncp,0,Kn);
	

	if(f1!=0)
	{
		vector<double>::iterator it1 = Kn.begin() + ncp + deg + 2 > Kn.end() ? Kn.end() : Kn.begin() + ncp + deg + 2;
		vector<CVector>::iterator it2 = CP.begin() + ncp + 1 > CP.end() ? CP.end() : CP.begin() + ncp + 1;
		std::reverse(CP.begin(),it2);
	 	std::reverse(Kn.begin(),it1);
//		f2=fmin;
		f1=Kn[0];
		for(int g=0;g!=ncp + deg + 2 && g < Kn.size();g++)
		{
			Kn[g]=(Kn[g]-f2);
			Kn[g]>0?Kn[g]:-Kn[g];
		}
	}
	vector<double>::iterator it1 = deg + ncp + 1 > Kn.size() - 1 ? Kn.end() : Kn.begin() + deg + ncp + 1;
	int s2 = count(Kn.begin(),it1, f2);
	s=find(Kn.begin(),it1,f2) - Kn.begin();
	for(g=0;g<=deg+1-s2;g++)
	{
		Kn.insert(Kn.begin()+s,Kn[s]);
	}
	it1 = deg + ncp + 1 > Kn.size() - 1 ? Kn.end() : Kn.begin() + deg + ncp + 1;
	s=find(Kn.begin(),it1,1) - Kn.begin();
    ncp=find(CP.begin(),CP.end(),m2) - CP.begin();
	ncp=ncp+1;

	CP.resize(ncp);
	if(f1!=f2)
	{
		for(g=0;g!=ncp + deg + 2 && g<Kn.size();g++)
		{
			Kn[g]=(Kn[g]-f1)/(f2-f1);
		}
	}
	angle = (f2-f1)*2*pi;

}

void CCercle::setArc(CVector v1, CVector v2, CVector v3)
{
	CVector w1(Ct,CP[0]);
	CVector w2(Ct,v2);
	float av;
	float f1 = argu(w2) - argu(w1),f2,f3;

	av = f1>0 ? f1:-f1;
	if(av<1E-2)
		f1=0;
	if(f1 < 0)
	{
		f1=f1 + 2*pi;
	}
//		f1 = fmod(f1,2*pi);
	f1 = (f1)/(2*pi);
	for(int g=0;g!=ncp + deg + 2 && g < Kn.size();g++)
	{
		av = f1-Kn[g] >0 ? f1-Kn[g]:Kn[g] -f1;
		if(av  <1E-2)
		{
			f1=Kn[g];
			break;
		}
	}
	f2=f1;
	vector<double>::iterator it1 = deg + ncp + 1 > Kn.size() - 1 ? Kn.end() : Kn.begin() + deg + ncp + 1;
	int s = count(Kn.begin(),it1, f1);
	CVector mn= NURBS(deg,CP,ncp,f1,Kn);
	for(g=0;g<deg-s;g++)
	{
		Bohms(f1, deg,Kn,CP,ncp);	
	}
	if(s==0)
	{
	for(g=0;g<=ncp && g < CP.size();g++)
	{
		if(CP[g]==mn)
			CP[g]=v2;	
	}
	}

	mn= NURBS(deg,CP,ncp,f1,Kn);

	CVector w3(Ct,v1);
	f1 = argu(w3) - argu(w1);
	av = f1>0 ? f1:-f1;
	if(av<1E-2)
		f1=0;
	
	if(f1 < 0)
	{
		f1=f1 + 2*pi;
	}
//		f1 = fmod(f1,2*pi);
	f1 = (f1)/(2*pi);
	for(g=0;g!=ncp + deg + 2 && g< Kn.size();g++)
	{
		av = f1-Kn[g] >0 ? f1-Kn[g]:Kn[g] -f1;
		if(av <1E-2)
		{
			f1=Kn[g];
			break;
		}
	}
	CVector mn1= NURBS(deg,CP,ncp,f1,Kn);
 	s = count(Kn.begin(),it1, f1);
	for(g=0;g<deg-s;g++)
	{
		Bohms(f1, deg,Kn,CP,ncp);	
	}
	if(s==0)
	{
	for(g=0;g<=ncp && g < CP.size();g++)
	{
		if(CP[g]==mn1)
			CP[g]=v1;	
	}
	}
	
	CVector mn2= NURBS(deg,CP,ncp,f1,Kn);

	CVector w4(Ct,v3);
	f3 = argu(w4) - argu(w1);
	
	if(f3 < 0)
	{
		f3=f3 + 2*pi;
	}
//		f3 = fmod(f3,2*pi);

//		f3=f3 + pi;
	f3 = (f3)/(2*pi);
	for(g=0;g!=ncp + deg + 2 && g < Kn.size();g++)
	{
		av = f3-Kn[g] >0 ? f3-Kn[g]:Kn[g] -f3;
		if(av <1E-2)
		{
			f3=Kn[g];
			break;
		}
	}
	s = count(Kn.begin(),it1, f3);
	for(g=0;g<deg-s;g++)
	{
		Bohms(f3, deg,Kn,CP,ncp);	
	}
	

	float fmin =f1<f2?f1:f2;
	float fmax =f1>f2?f1:f2;
    f1=fmin;
	f2=fmax;
    CVector m = NURBS(deg,CP,ncp,f1,Kn);
	CVector m2 = NURBS(deg,CP,ncp,f2,Kn);
	CVector m3 =NURBS(deg,CP,ncp,0,Kn);
	
	vector<double>::iterator it2 = ncp + deg + 2 > Kn.size() - 1 ? Kn.end() : Kn.begin() + ncp + deg + 2;
	if((f3>f2)||(f1!=0))
	{
		std::reverse(CP.begin(),ncp+1 > CP.size() - 1 ? CP.end() : CP.begin() + ncp + 1);
	 	std::reverse(Kn.begin(),it2);
//		f2=fmin;
		f1=Kn[0];
	}
	it1 = deg + ncp + 1 > Kn.size() - 1 ? Kn.end() : Kn.begin() + deg + ncp + 1;

	int s2 = count(Kn.begin(),it1, f2);
	s=find(Kn.begin(),it2,f2) - Kn.begin();
	for(g=0;g<deg+1-s2;g++)
	{
		Kn.insert(Kn.begin()+s,Kn[s]);
	}
	it2 = ncp + deg + 2 > Kn.size() - 1 ? Kn.end() : Kn.begin() + ncp + deg + 2;
	s=find(Kn.begin(),it2,1) - Kn.begin();
    ncp=find(CP.begin(),CP.end(),m2) - CP.begin();
	ncp=ncp+1;

	if(f1!=f2)
	{
	for(g=0;g!=ncp + deg + 2 && g < Kn.size();g++)
	{
		Kn[g]=(Kn[g]-f1)/(f2-f1);
	}
	}

}

CFigure* CCercle::generateCopy()
{
	CCercle* l=new CCercle;
	l->copy(this);
	return l;
}

void CCercle::copy(CCercle *c)
{
 Ct=c->Ct;
 CBezier::copy(c);

}

