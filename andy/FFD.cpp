// FFD.cpp: implementation of the CFFD class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "FFD.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFFD::CFFD()
{

}

CFFD::~CFFD()
{

}

CFFD::CFFD(CBezier *bezier,CString option)
{
	type=option;
	b=bezier;
	Knu.resize(20);
	Knv.resize(20);
	Knw.resize(20);
	ncpu=1;
	ncpv=1;
	ncpw=1;
	degu=1;
	degv=1;
	degw=1;
	Para.resize(b->mesh.Vcount());


	b->updatecore();
	if(!b->surf)
	{
	if(b->Mr==NULL) return;
	for(int j=0;j<=b->N;j++)
	{
		box.add(b->Mr[j]);
	}
	}
	else
	{
	   CMesh::ivertex iv=b->mesh.vbegin();int i=0;
	   for(iv=b->mesh.vbegin();iv!=b->mesh.vend();iv++)
	   {
		   box.add(CVector(*iv->second));
	   }

	}
	
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(1));
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(2));
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(4));

	ptbegin.push_back(box.corner(1));
	ptend.push_back(box.corner(5));
	ptbegin.push_back(box.corner(1));
	ptend.push_back(box.corner(3));
	
	ptbegin.push_back(box.corner(3));
	ptend.push_back(box.corner(2));
	ptbegin.push_back(box.corner(3));
	ptend.push_back(box.corner(7));

	ptbegin.push_back(box.corner(2));
	ptend.push_back(box.corner(6));

	ptbegin.push_back(box.corner(4));
	ptend.push_back(box.corner(5));
	ptbegin.push_back(box.corner(4));
	ptend.push_back(box.corner(6));

	ptbegin.push_back(box.corner(7));
	ptend.push_back(box.corner(6));
	ptbegin.push_back(box.corner(7));
	ptend.push_back(box.corner(5));

	CP.clear();
	CP.resize(20);
	CP[0]=ptbegin[0];
	CP[1]=ptend[0];
	CP[2]=ptend[1];
	CP[3]=ptend[4];
	CP[4]=ptend[2];
	CP[5]=ptend[3];
	CP[6]=ptend[7];
	CP[7]=ptend[6];
	ptbegin=CP;
	ptend=CP;

/*	CP[0]=ptbegin[0];
	CP[1]=ptend[0];
	CP[2]=ptend[1];
	CP[3]=ptend[4];
	CP[4]=ptend[2];
	CP[5]=ptend[3];
	CP[6]=ptend[7];
	CP[7]=ptend[6];
*/
    
	b->Knot_Univer(1,1,Knu,0,1);
    b->Knot_Univer(1,1,Knv,0,1);
    b->Knot_Univer(1,1,Knw,0,1);
	CMatrix m;
//	m.Transpose(CP,2,2);
	
	bcolor=RGB(0,255,0);

}

void CFFD::movepoint(CBezier *b,CVector*M)
{

/*	if(b->box.intersectAABB(box))
	{
	   for(int iter=0;iter<=b->N;iter++)
	   {
		  if(box.containpts(M[iter]))
		  {
			  if(Isinside(M[iter]))
			  {
				  M[iter]=M[iter]+b->NURBS();

			  }
		  }
	  }

	}*/
}

vector<CVector>& CFFD::getPoint()
{
	int i=0;
	int m=mesh.Vcount();
	for(CMesh::ivertex iter=mesh.vbegin();i<m;iter++)
	{
		CP[i]=*iter->second;
		i++;
	}
	prevptbegin=ptbegin;
	prevptend=ptend;
	ptbegin=CP;
	ptend=ptbegin;
	std::rotate(ptend.begin(),ptend.begin()+1,ptend.end());
	return CP;
}
vector<double>& CFFD::getKnu()
{
	return Knu;
}
vector<double>& CFFD::getKnv()
{
	return Knv;
}
vector<double>& CFFD::getKnw()
{
	return Knw;
}

bool CFFD::PtinNode(CVector point,int multi)
{

	bool b=false;int i=-1;
	if(multi==0) b=mesh.PtonVertex(point,i);
	else
		if(multi==1) b=mesh.PtonRow(point);
	else
		if(multi==2) b=mesh.PtonCol(point);

	if(!b) select=null;
	return b;
}
bool CFFD::PtinRegion(CVector point)
{

	bool bo=CFigure::PtinRegion(point);
	if(!bo) 
		select=null;
	else mesh.select=mesh.all;
	return bo;
}
void CFFD::Rotate(int sens,CVector prevpoint,CVector postpoint)
{
	if(mesh.select==mesh.all)
	{

	CFigure::Rotate(sens,prevpoint,postpoint);
	CP=ptbegin;
	for(int i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
			  *mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k)=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			}
		}
	}

	i=0;
	for(CMesh::ivertex iter=mesh.vbegin();iter!=mesh.vend();iter++)
	{
		sphere[i].select=mesh.all;
		sphere[i].Rotate(sens,prevpoint,postpoint,rotateCenter);
		i++;
	}
	}
	else
	{
	mesh.Rotate(sens,prevpoint,postpoint,b->rotateCenter);
		int i=0;
	for(CMesh::ivertex iter=mesh.svbegin();iter!=mesh.svend();iter++)
	{
		sphere[(iter)->second->sit].select=mesh.all;
		sphere[(iter)->second->sit].Rotate(sens,prevpoint,postpoint,b->rotateCenter);
		i++;
	}
	}

/*	for(int i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
			  *mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k)=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			}
		}
	}
*/
}
void CFFD::translate(CWnd *wnd, CDC *hdc, CVector prevpos, CVector postpos)
{
	if(mesh.select==mesh.all)
	{
//	CFigure::translate(wnd,hdc,prevpos,postpos);
	
//	CP=ptbegin;
/*	for(int i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
			  *mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k)=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			}
		}
	}*/
	}
	mesh.translate(prevpos,postpos);

	CVector m(prevpos,postpos);
//	m.snaptoplane(m);
	int i=0;
	if(mesh.select==mesh.all)
	{
	for(CMesh::ivertex iter=mesh.vbegin();iter!=mesh.vend();iter++)
	{
		sphere[i].select=mesh.all;
		sphere[i].translate(prevpos,postpos);
		i++;
	}
	}
	else if(mesh.select==mesh.vertex)
	{
	for(CMesh::ivertex iter=mesh.svbegin();iter!=mesh.svend();iter++)
	{
		sphere[(iter)->second->sit].select=mesh.all;
		sphere[(iter)->second->sit].translate(prevpos,postpos);
		i++;
	}
	}
}

void CFFD::draw(CDC *hdc)
{
	int old;
/*	if(select==null)
	{
		return;
	}
*/
	if((select==full)||(select==pnt)||(b->click==true))
	{
	if((ptbegin.size()!=0)&&(ptbegin.size()==ptend.size()))
	{
	pitere=ptend.begin();
	CPen pen;
	pen.CreatePen(lstyle,lwidth,&lplb,dwStyleCount,lpStyle);
	CPen* oldp=hdc->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(bcolor);
	CBrush *oldb=hdc->SelectObject(&brush);

/*	for (piterb=ptbegin.begin();piterb<ptbegin.end()-1;piterb++)
	{
	hdc->MoveTo(*piterb);
	hdc->LineTo(*pitere+1);
	
	pitere=pitere+1;
	}*/
	mesh.displayEdge(hdc);
	int i=0;
	for(CMesh::ivertex iter=mesh.vbegin();iter!=mesh.vend();iter++)
	{
		sphere[i].redraw=true;
		i++;
	}

/*	   CMesh::ivertex iv=mesh.vbegin();
	   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
	   {
		b->displaysphere((*iv)->v,hdc);
	   }
*/
	if((!getLibstatus()))
	{
	if(transselectedstate()) drawselect(hdc);
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
	
	}
	}

}

void CFFD::savefile(CFile &file)
{
	int i=type.GetLength();
	file.Write(&i,sizeof(int));
	for(int j=0;j<i;j++)
	{
	char c=type[j];
	file.Write(&c,sizeof(c));
	}


	file.Write(&b->N, sizeof(b->N));
	file.Write(&b->N1, sizeof(b->N1));
	file.Write(&ncpu, sizeof(ncpu));
	file.Write(&ncpv, sizeof(ncpv));
	file.Write(&ncpw, sizeof(ncpw));
	file.Write(&degu,sizeof(degu));
	file.Write(&degv,sizeof(degv));
	file.Write(&degw,sizeof(degw));
	
	for(int it=0;it<((ncpu+1)*(ncpv+1)*(ncpw+1));it++)
	{
		CP[it].savefile(file);
	}
	for(it=0;it<ncpu+degu+2;it++)
	{
		file.Write(&Knu[it], sizeof(double));
	}
	
	for(it=0;it<=ncpv+degv+2;it++)
	{
		file.Write(&Knv[it], sizeof(double));
	}
	
	for(it=0;it<=ncpw+degw+2;it++)
	{
		file.Write(&Knw[it], sizeof(double));
	}
	for(it=0;it<=b->N;it++)
	{
		for(int i=0;i<=b->N1;i++)
		{
		Para[it*(b->N1+1)+i].savefile(file);
		}
	}
	CFigure::savefile(file);

}

void CFFD::openfile(CFile &file)
{
	int i=0;
	file.Read(&i,sizeof(int));
	type.Empty();
	for(int j=0;j<i;j++)
	{
	char c;
	file.Read(&c,sizeof(c));
	type.Insert(j,c);
	}
	int N=0,N1=0;
	file.Read(&N, sizeof(N));
	file.Read(&N1, sizeof(N1));
	file.Read(&ncpu, sizeof(ncpu));
	file.Read(&ncpv, sizeof(ncpv));
	file.Read(&ncpw, sizeof(ncpw));
	file.Read(&degu,sizeof(degu));
	file.Read(&degv,sizeof(degv));
	file.Read(&degw,sizeof(degw));
	CP.resize((ncpu+1)*(ncpv+1)*(ncpw+1));
	for(int it=0;it<((ncpu+1)*(ncpv+1)*(ncpw+1));it++)
	{
		CVector v;
		v.openfile(file);
		CP[it]=v;
	}
	Knu.resize(ncpu+degu+2);
	for(it=0;it<ncpu+degu+2;it++)
	{
		file.Read(&Knu[it], sizeof(double));
	}
	
	Knv.resize(ncpv+degv+2);
	for(it=0;it<=ncpv+degv+2;it++)
	{
		file.Read(&Knv[it], sizeof(double));
	}
	
	Knw.resize(ncpw+degw+2);
	for(it=0;it<=ncpw+degw+2;it++)
	{
		file.Read(&Knw[it], sizeof(double));
	}

	Para.resize((N+1)*(N1+1));
	for(it=0;it<=N;it++)
	{
		for(int i=0;i<=N1;i++)
		{
		CVector v;
		v.openfile(file);
		Para[it*(N1+1)+i]=v;
		}
	}
	CFigure::openfile(file);
//	init();
	updatecore();
	Mesh();

	sphere.resize((ncpu+1)*(ncpv+1)*(ncpw+1));
	CMesh* sph=b->getsphere();
	for(i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
//			  b->sphere(&sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k],CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]);
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].copy(sph);			  
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].select=CMesh::all;
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].translate(CVector(0,0,0),CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]);			  
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].select=CMesh::none;


			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].RWRender();
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].redraw=true;
			}
		}
	}


}
LONG CFFD::Readfile(CFile &file)
{
	LONG g;
	int i=0;
	file.Read(&i,sizeof(int));
	type.Empty();
	for(int j=0;j<i;j++)
	{
	char c;
	file.Read(&c,sizeof(c));
	type.Insert(j,c);
	}
	int N=0,N1=0;
	file.Read(&N, sizeof(N));
	file.Read(&N1, sizeof(N1));
	file.Read(&ncpu, sizeof(ncpu));
	file.Read(&ncpv, sizeof(ncpv));
	file.Read(&ncpw, sizeof(ncpw));
	file.Read(&degu,sizeof(degu));
	file.Read(&degv,sizeof(degv));
	g=file.Read(&degw,sizeof(degw));
	CP.resize((ncpu+1)*(ncpv+1)*(ncpw+1));
	for(int it=0;it<((ncpu+1)*(ncpv+1)*(ncpw+1));it++)
	{
		CVector v;
		g=v.Readfile(file);
	}
	Knu.resize(ncpu+degu+2);
	for(it=0;it<ncpu+degu+2;it++)
	{
		g=file.Seek(sizeof(double),CFile::current);
	}
	
	Knv.resize(ncpv+degv+2);
	for(it=0;it<=ncpv+degv+2;it++)
	{
		g=file.Seek(sizeof(double),CFile::current);
	}
	
	Knw.resize(ncpw+degw+2);
	for(it=0;it<=ncpw+degw+2;it++)
	{
		g=file.Seek(sizeof(double),CFile::current);
	}

	Para.resize((N+1)*(N1+1));
	for(it=0;it<=N;it++)
	{
		for(int i=0;i<=N1;i++)
		{
		CVector v;
		v.openfile(file);
		Para[it*(N1+1)+i]=v;
		}
	}
	return CFigure::Readfile(file);

}

void CFFD::init()
{
	box.empty();
	ptbegin.clear();
	ptend.clear();
	ncpu=1;
	ncpv=1;
	ncpw=1;
	degu=1;
	degv=1;
	degw=1;
	if(!b->surf)
	{
	for(int j=0;j<=b->N;j++)
	{
		box.add(b->Mr[j]);
	}
	}
	else
	{
	   CMesh::ivertex iv=b->mesh.vbegin();int i=0;
	   for(iv=b->mesh.vbegin();iv!=b->mesh.vend();iv++)
	   {
		   box.add(CVector(*iv->second));
	   }
	}
	
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(1));
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(2));
	ptbegin.push_back(box.corner(0));
	ptend.push_back(box.corner(4));

	ptbegin.push_back(box.corner(1));
	ptend.push_back(box.corner(5));
	ptbegin.push_back(box.corner(1));
	ptend.push_back(box.corner(3));
	
	ptbegin.push_back(box.corner(3));
	ptend.push_back(box.corner(2));
	ptbegin.push_back(box.corner(3));
	ptend.push_back(box.corner(7));

	ptbegin.push_back(box.corner(2));
	ptend.push_back(box.corner(6));

	ptbegin.push_back(box.corner(4));
	ptend.push_back(box.corner(5));
	ptbegin.push_back(box.corner(4));
	ptend.push_back(box.corner(6));

	ptbegin.push_back(box.corner(7));
	ptend.push_back(box.corner(6));
	ptbegin.push_back(box.corner(7));
	ptend.push_back(box.corner(5));

	CP.clear();
	CP.resize(50);
	CP[0]=ptbegin[0];
	CP[1]=ptend[0];
	CP[2]=ptend[1];
	CP[3]=ptend[4];
	CP[4]=ptend[2];
	CP[5]=ptend[3];
	CP[6]=ptend[7];
	CP[7]=ptend[6];
//	mesh.resizevertex(50);
	mesh.empty();
	if(type=="2x2x2")
	{
	mesh.resizevertex(8);
	subdivide(2,2,2);
	}
	else if (type=="3x3x3")
	{
	mesh.resizevertex(27);
	subdivide(3,3,3);
	}
	else if (type=="4x4x4")
	{
	CP.resize(70);
	mesh.resizevertex(64);
	subdivide(4,4,4);
	}

	for(int i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
			  mesh.addVertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k,new CVertex(CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k],Knu[k],Knv[j]));
			}
		}
	}

	for(i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<ncpu;k++)
			{
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1)));
			  if(j+1<=ncpv)
			  {
				 mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+(j+1)*(ncpu+1)+k)));
				 mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+(j+1)*(ncpu+1)+k+1)));
			  }
			  if(i+1<=ncpw)
			  {
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex((i+1)*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k)));
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1),mesh.Vertex((i+1)*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1)));
			  }
			}
		}
	}
	sphere.resize((ncpu+1)*(ncpv+1)*(ncpw+1));
	CMesh* sph=b->getsphere();
	for(i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
//			  b->sphere(&sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k],CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]);
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].copy(sph);			  
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].select=CMesh::all;
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].translate(CVector(0,0,0),CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]);			  
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].select=CMesh::none;


			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].RWRender();
			  sphere[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k].redraw=true;
			}
		}
	}

//	b->sphere(&sph);
	
/*	   for(iv=mesh.vbegin();iv!=mesh.vend();iv++)
	   {
		b->addsphere((*iv)->v,&mesh);
	   }
*/		
	ptbegin=CP;
	ptend=CP;

    
	b->Knot_Univer(ncpu,degu,Knu,0,1);
    b->Knot_Univer(ncpv,degv,Knv,0,1);
    b->Knot_Univer(ncpw,degw,Knw,0,1);

}

void CFFD::subdivide(int u, int v,int w)
{
 vector<CVector> vc(CP.size());
 vc=CP;
	 int jj=0;
	 for(int i=0;i<=ncpw;i++)
	 {
		 for(int j=0;j<=ncpv;j++)
		 {
			for(int k=0;k<=ncpu;k++)
			{
//			 vc[jj++]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			 for(int l=0;l<=u-1;l++)
			 {
			 vc[jj++]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]*(1-((float)l/(u-1)))+CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1]*((float)l/(u-1));
			 }
//			 vc[jj++]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1];
			 k++;
			}
		 }
	 }
	 CP=vc;

 ncpu=u-1;

	 jj=0;
	 for(i=0;i<=ncpw;i++)
	 {
		 for(int j=0;j<=ncpv;j++)
		 {
			for(int k=0;k<=ncpu;k++)
			{
			 vc[i*(v)*(ncpu+1)+j*(ncpu+1)+k]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			}
			if(j<ncpv)
			{
			for(k=0;k<=ncpu;k++)
			{
			 for(int l=1;l<=v-1;l++)
			 {
				 vc[i*(v)*(ncpu+1)+l*(ncpu+1)+k]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]*(1-((float)l/(v-1)))+CP[i*(ncpv+1)*(ncpu+1)+(j+1)*(ncpu+1)+k]*((float)l/(v-1));///2;
			 }
			}
			j++;
			}
			
		 }
	 }
	 CP=vc;
 ncpv=v-1;

	 jj=0;
	 for(i=0;i<=ncpw;i++)
	 {
		 for(int j=0;j<=ncpv;j++)
		 {
			for(int k=0;k<=ncpu;k++)
			{
			 vc[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k];
			}
			
		 }
			if(i<ncpw)
			{
			for(j=0;j<=ncpv;j++)
			{
				for(int k=0;k<=ncpu;k++)
				{
				 for(int l=1;l<=w-1;l++)
				 {
				 vc[l*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]=CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]*(1-((float)l/(w-1)))+CP[(i+1)*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]*((float)l/(w-1));///2;
				 }
				}
			}
			i++;
			}
	 }
	 CP=vc;
 ncpw=w-1;

}

void CFFD::Mesh()
{
	mesh.resizevertex((ncpu+1)*(ncpv+1)*(ncpw+1));	
	if (type=="4x4x4")
	{
	mesh.resizevertex(70);
	}

	for(int i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<=ncpu;k++)
			{
				mesh.addVertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k,new CVertex(CP[i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k]));
			}
		}
	}

	for(i=0;i<=ncpw;i++)
	{
		for(int j=0;j<=ncpv;j++)
		{
			for(int k=0;k<ncpu;k++)
			{
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1)));
			  if(j+1<=ncpv)
			  {
				 mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+(j+1)*(ncpu+1)+k)));
				 mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1),mesh.Vertex(i*(ncpv+1)*(ncpu+1)+(j+1)*(ncpu+1)+k+1)));
			  }
			  if(i+1<=ncpw)
			  {
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k),mesh.Vertex((i+1)*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k)));
			  mesh.addEdge(new CEdge(mesh.Vertex(i*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1),mesh.Vertex((i+1)*(ncpv+1)*(ncpu+1)+j*(ncpu+1)+k+1)));
			  }
			}
		}
	}

}

void CFFD::copy(CFFD *box)
{
	ncpu=box->ncpu;
	ncpv=box->ncpv;
	ncpw=box->ncpw;

	degu=box->degu;
	degv=box->degv;
	degw=box->degw;

	type=box->type;


	CP.resize(box->CP.size());
	int kj=box->CP.size();
	for(int i=0; i<kj;i++)
	{
		CP[i]=box->CP[i];
	}

	Para.resize((b->N+1)*(b->N1+1));
	int h=(b->N+1)*(b->N1+1);

	for(i=0; i<h;i++)
	{
		Para[i]=box->Para[i];
	}

	Knu.resize(box->Knu.size());
	h=box->Knu.size();
	for(i=0; i<h;i++)
	{
		Knu[i]=box->Knu[i];
	}
	Knv.resize(box->Knv.size());
	h=box->Knv.size();
	for(i=0; i<h;i++)
	{
		Knv[i]=box->Knv[i];
	}
	Knw.resize(box->Knw.size());
	h=box->Knw.size();
	for(i=0; i<h;i++)
	{
		Knw[i]=box->Knw[i];
	}

	Mesh();
	CFigure::copy(box);
}

void CFFD::update()
{
	Para.resize((b->N+1)*(b->N1+1)*(b->N2+1));

}
void CFFD::postTranslate(CVector v)
{
	   CMesh::ivertex iv=mesh.svbegin();
	   CVector vk;
	   for(iv=mesh.svbegin();iv!=mesh.svend();iv++)
	   {
		   vk=(iv)->second->v;
		   (iv)->second->v.assign((iv)->second->v,true);
		   sphere[(iv)->second->sit].select=mesh.all;
			sphere[(iv)->second->sit].translate(vk,(iv)->second->v);
	   }

}
