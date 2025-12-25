// Render.cpp: implementation of the CRender class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Render.h"
#include "Cadview.h"
#include "plane.h"
#include "image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CCadView* CRender::view=NULL;
vector<CPlane> plane(4);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRender::CRender()
{
	ptbegin.resize(4);
	ptend.resize(4);

 CMesh m;
 m.setRender(this);
}

CRender::~CRender()
{

}
void CRender::displayTri(CDC *hdc)
{
	if(CMesh::zbuffer==NULL)
	{
		return;
	}

	
	int i=0;int w=0;
	HDC hd=hdc->GetSafeHdc();

	
	CBitmap* bmp=view->bmp;
	HBITMAP jj=(HBITMAP)bmp->GetSafeHandle();

	BITMAP nb;
	int j=GetObject(jj,sizeof(BITMAP),NULL);
	int h=GetObject(jj,j,&nb);
	if(h==0)
	{
		return;
	}
	Update(hd);
	DWORD d=nb.bmWidth*nb.bmHeight*nb.bmBitsPixel;
	int bpp=4;

/*	BYTE* bits=new BYTE[d];
	memset(bits,0,d);
	bmp->GetBitmapBits(d,bits);
*/	CImage im;
	PBITMAPINFO pbmi=im.CreateBMPInfo((HBITMAP)bmp->GetSafeHandle(),true);
    LPBYTE bits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbmi->bmiHeader.biSizeImage);


    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    int o=GetDIBits(hdc->GetSafeHdc(),(HBITMAP) bmp->GetSafeHandle(), 0, (WORD) nb.bmHeight, bits, pbmi,DIB_RGB_COLORS);
	bits=bits+pbmi->bmiHeader.biClrUsed * sizeof (RGBQUAD);
//	LocalFree(pbmi);
	int p1height=nb.bmHeight;
	int p1width=nb.bmWidth;
	bool on=false;
	for(multiset<CTriangle*,isfar>::iterator iter=tri.begin();iter!=tri.end();iter++)
	{
//	(*iter)->isDegenerate(hd);
	(*iter)->rasterizeTriangle(hd,bits,CMesh::zbuffer,p1height,p1width,NULL,bpp,0,NULL);//display(hdc,loc,lit);
	on=true;
	}
//	bmp->SetBitmapBits(d,bits);
	if(on)
		SetDIBits(hdc->GetSafeHdc(),(HBITMAP) bmp->GetSafeHandle(), 0, (WORD) nb.bmHeight, bits, pbmi,DIB_RGB_COLORS);
	GlobalFree(bits);//delete [] bits;
	LocalFree(pbmi);

}
void CRender::setWnd(CCadView *cad)
{
	view=cad;
}
void CRender::Update(HDC hd)
{
	CAABB bol;
	CPoint pl;
	CVector vrx(1,0,0),vry(0,1,0);
//	vrx.getcoorx();
//	vry.getcoory();

	CVector v0,v1,v2,v3;
	v0=v0.sgetscrb();
	pl.x=v0.x;
	pl.y=v0.y;
	LPtoDP(hd,&pl,1);

	v0.x=pl.x;
	v0.y=pl.y;
	bol.add(pl);
	v0=v0.sgetscrtop();
	pl.x=v0.x;
	pl.y=v0.y;
	LPtoDP(hd,&pl,1);

	v0.x=pl.x;
	v0.y=pl.y;
	bol.add(pl);
//	bol.inflate(10);

	v0=bol.corner(0);
	v1=bol.corner(1);
	v2=bol.corner(2);
	v3=bol.corner(3);
	CVector v00(0,0,0);

	CPlane p1(v0.dot(vrx),vrx);
	CPlane p2(v1.dot(-vrx),-vrx);
	
//	v0=bol.corner(2);
//	v1=bol.corner(2);
	CPlane p3(v0.dot(vry),vry);
	CPlane p4(v2.dot(-vry),-vry);
	plane[0]=p1;
	plane[1]=p2;
	plane[2]=p3;
	plane[3]=p4;


	tri.clear();
	for(vector<CMesh*>::iterator ir=region.begin();ir!=region.end();ir++)
	{
		if((*ir)->redraw)
		{
		(*ir)->emptyscreen();
		for(map<int,CVertex*>::iterator iter1=(*ir)->vertexlist.begin();iter1!=(*ir)->vertexlist.end();iter1++)
		{
		(iter1)->second->toScreen(hd);
//		(*iter1)->visible=bol.containpts(CVector((*iter1)->p.x,(*iter1)->p.y,0));
		}
		clipTriangle((*ir)->trilist,hd,*ir,bol);
		int i=0;
		for(vector<CTriangle*>::iterator iter=(*ir)->strilist.begin();iter!=(*ir)->strilist.end();iter++)
		{
		tri.insert(*iter);
		i++;
		}
		(*ir)->redraw=false;
		}
	}
}

void interpolate(CVertex* ve,CTriangle *t,CVector v)
{
	 ve->un=v.x*t->Vertex(0)->un+v.y*t->Vertex(1)->un+v.z*t->Vertex(2)->un;
	 ve->vn=v.x*t->Vertex(0)->vn+v.y*t->Vertex(1)->vn+v.z*t->Vertex(2)->vn;
	 ve->n=t->Vertex(0)->n*v.x+t->Vertex(1)->n*v.y+t->Vertex(2)->n*v.z;
	 ve->z=v.x*t->Vertex(0)->z+v.y*t->Vertex(1)->z+v.z*t->Vertex(2)->z;
	 ve->rgbdiff.r=v.x*t->Vertex(0)->rgbdiff.r+v.y*t->Vertex(1)->rgbdiff.r+v.z*t->Vertex(2)->rgbdiff.r;
	 ve->rgbdiff.g=v.x*t->Vertex(0)->rgbdiff.g+v.y*t->Vertex(1)->rgbdiff.g+v.z*t->Vertex(2)->rgbdiff.g;
	 ve->rgbdiff.b=v.x*t->Vertex(0)->rgbdiff.b+v.y*t->Vertex(1)->rgbdiff.b+v.z*t->Vertex(2)->rgbdiff.b;
	 ve->rgbspec.r=v.x*t->Vertex(0)->rgbspec.r+v.y*t->Vertex(1)->rgbspec.r+v.z*t->Vertex(2)->rgbspec.r;
	 ve->rgbspec.g=v.x*t->Vertex(0)->rgbspec.g+v.y*t->Vertex(1)->rgbspec.g+v.z*t->Vertex(2)->rgbspec.g;
	 ve->rgbspec.b=v.x*t->Vertex(0)->rgbspec.b+v.y*t->Vertex(1)->rgbspec.b+v.z*t->Vertex(2)->rgbspec.b;
}


bool CRender::clipTriangle(vector<CTriangle*>& Mb,HDC hdc,CMesh* mesh,CAABB& bol)
{
	CVector vrx,vry,vrz;
	vrx.getcoorx();vry.getcoory();vrz.getcoorz();
	int k=Mb.size();
 for(int i=0;i<k;i++)
 {
 CTriangle* t=Mb[i];
 t->visible=true;
 int h=0;

	
 if(t->Vertex(0)->visible &&t->Vertex(1)->visible && t->Vertex(2)->visible)
 {
	     mesh->SaddTri(t);
			 h=1;
 }
 else 
 if(!t->Vertex(0)->visible &&!t->Vertex(1)->visible && !t->Vertex(2)->visible)
	 continue;


 else
 {
 CVector v1((*t).Vertex(0)->p.x,(*t).Vertex(0)->p.y);
 CVector v2(t->Vertex(1)->p.x,t->Vertex(1)->p.y);
 CVector v3(t->Vertex(2)->p.x,t->Vertex(2)->p.y);
 CVector ve,vb;
 for(vector<CPlane>::iterator iterb=plane.begin();iterb!=plane.end();iterb++)
 {

	 float p0=v1.dot(iterb->n)-iterb->d;
	 float p1=v2.dot(iterb->n)-iterb->d;
	 float p2=v3.dot(iterb->n)-iterb->d;

		 if(p0*p1<=0)
		 {
			 Clipconfiguration(p0,p1,p2,t->Vertex(0),t->Vertex(1),t->Vertex(2),hdc,mesh);
			 h=1;
			 break;
		 }else
		 if(p0*p2<=0)
		 {
			 Clipconfiguration(p2,p0,p1,t->Vertex(2),t->Vertex(0),t->Vertex(1),hdc,mesh);
			 h=1;
			 break;
		 }else
		 if(p1*p2<=0)
		 {
			 Clipconfiguration(p1,p2,p0,t->Vertex(1),t->Vertex(2),t->Vertex(0),hdc,mesh);
			 h=1;
			 break;
		 }
		 if((p0>0)&&(p1>0)&&(p2>0))
		 {
	     mesh->SaddTri(t);
		 }
	 }
 }
if (!h) return false; 
}
}

void interpolate(CVertex* vc1,CVertex* vi1,CVertex* vi2,CVector vc)
{
	CVector v01(vi1->p.x,vi1->p.y);
	CVector v02(vi2->p.x,vi2->p.y);

	 float zv=absc(v01-vc)/absc(v01-v02);
	 vc1->un=(1-zv)*vi1->un+zv*vi2->un;
	 vc1->vn=(1-zv)*vi1->vn+zv*vi2->vn;
	 vc1->n=vi1->n*(1-zv)+vi2->n*zv;
	 vc1->z=vi1->z*(1-zv)+vi2->z*zv;
	 vc1->rgbdiff.r=vi1->rgbdiff.r*(1-zv)+vi2->rgbdiff.r*zv;
	 vc1->rgbdiff.g=vi1->rgbdiff.g*(1-zv)+vi2->rgbdiff.g*zv;
	 vc1->rgbdiff.b=vi1->rgbdiff.b*(1-zv)+vi2->rgbdiff.b*zv;
	 vc1->rgbspec.r=vi1->rgbspec.r*(1-zv)+vi2->rgbspec.r*zv;
	 vc1->rgbspec.g=vi1->rgbspec.g*(1-zv)+vi2->rgbspec.g*zv;
	 vc1->rgbspec.b=vi1->rgbspec.b*(1-zv)+vi2->rgbspec.b*zv;
}

void CRender::Clipconfiguration(float pi0,float pi1,float pi2,CVertex* vi0,CVertex* vi1,CVertex* vi2,HDC hdc,CMesh* mesh)
{
 CVector vrx,vry,vrz;
 vrx.getcoorx();vry.getcoory();vrz.getcoorz();

 CVector vl2(vi2->p.x,vi2->p.y);
 CVector vl1(vi1->p.x,vi1->p.y);
 CVector vl0(vi0->p.x,vi0->p.y);

 CVector vci=vl0+(vl1-vl0)*(pi0/(pi0-pi1));

 CVector v;

 if(pi0>0)
 {
	 if(pi2>0)
	 {
	 CVector vc=vl1+(vl2-vl1)*(pi1/(pi1-pi2));

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh->SaddVertex(vco);
	 mesh->SaddVertex(vc1);

	 vc1->p.x=vc.x;
	 vc1->p.y=vc.y;
	 vc1->v.x=vc.x;
	 vc1->v.y=vc.y;

	 vco->p.x=vci.x;
	 vco->p.y=vci.y;
	 vco->v.x=vci.x;
	 vco->v.y=vci.y;
	
	 interpolate(vc1,vi1,vi2,vc);
	 interpolate(vco,vi0,vi1,vci);

     mesh->SaddTri(new CTriangle(vco,vc1,vi0));


	 mesh->SaddTri(new CTriangle(vc1,vi2,vi0));
	 }
	 else 
	 {
	 CVector vc=vl0+(vl2-vl0)*(pi0/(pi0-pi2));

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh->SaddVertex(vco);
	 mesh->SaddVertex(vc1);

	 vc1->p.x=vc.x;
	 vc1->p.y=vc.y;
	 vc1->v.x=vc.x;
	 vc1->v.y=vc.y;

	 vco->p.x=vci.x;
	 vco->p.y=vci.y;
	 vco->v.x=vci.x;
	 vco->v.y=vci.y;


	 interpolate(vc1,vi0,vi2,vc);
	 interpolate(vco,vi0,vi1,vci);
     mesh->SaddTri(new CTriangle(vco,vc1,vi0));
	 }
 }
 else
 {
	 if(pi2>0)
	 {
	 CVector vc=vl0+(vl2-vl0)*(pi0/(pi0-pi2));
	 
	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh->SaddVertex(vco);
	 mesh->SaddVertex(vc1);

	 vc1->p.x=vc.x;
	 vc1->p.y=vc.y;
	 vc1->v.x=vc.x;
	 vc1->v.y=vc.y;

	 vco->p.x=vci.x;
	 vco->p.y=vci.y;
	 vco->v.x=vci.x;
	 vco->v.y=vci.y;



	 interpolate(vc1,vi0,vi2,vc);
	 interpolate(vco,vi0,vi1,vci);
	 mesh->SaddTri(new CTriangle(vco,vi1,vi2));

	 mesh->SaddTri(new CTriangle(vco,vi2,vc1));
	 }
	 else
	 {
	 CVector vc=vl1+(vl2-vl1)*(pi1/(pi1-pi2));

	 CVertex* vco=new CVertex;
	 CVertex* vc1=new CVertex;
	 mesh->SaddVertex(vco);
	 mesh->SaddVertex(vc1);

	 vc1->p.x=vc.x;
	 vc1->p.y=vc.y;
	 vc1->v.x=vc.x;
	 vc1->v.y=vc.y;

	 vco->p.x=vci.x;
	 vco->p.y=vci.y;
	 vco->v.x=vci.x;
	 vco->v.y=vci.y;

	 interpolate(vc1,vi1,vi2,vc);
	 interpolate(vco,vi1,vi0,vc);
	 mesh->SaddTri(new CTriangle(vco,vi1,vc1));
	 }

 }

}







void CRender::removeRegion(CMesh *m)
{
	vector<CMesh*>::iterator o=find(region.begin(),region.end(),m);
	if(o!=region.end())
		region.erase(o);
}
void CRender::addRegion(CMesh *m)
{	vector<CMesh*>::iterator o=find(region.begin(),region.end(),m);
	if(o==region.end())
		region.push_back(m);
}