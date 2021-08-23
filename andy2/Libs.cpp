// LibS.cpp: implementation of the CLibS class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "LibS.h"
#include "inter.h"
//#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLibS::CLibS()
{
//	handle=0;
	iter=0;
	name="CLibS";
//	elem=(CFigure**) malloc(sizeof(CFigure*));

//	CLine *v=new CLine;
	elem.clear();
	sel=NULL;
	m=0;
	bc=0;


}
CLibS::CLibS(CString _name)
{
//	handle=0;
	iter=0;
	name="CLibS";
	libname=_name;
	myinfo.name=_name;
//	elem=(CFigure**) malloc(sizeof(CFigure*));

//	CLine *v=new CLine;
	elem.clear();
	sel=NULL;
	m=0;
	bc=0;


}

void CLibS::Copy(CLibS& v)
{
	copy(&v);

}

CLibS::~CLibS()
{
	if(iter!=0)
	{
//	free(elem);
	for(int i=0;i<iter;i++)
	{
		delete elem[i];
	}
	elem.clear();
	elem.clear();
	if(sel!=NULL)
	free(sel);
	}
	iter=0;
}
void CLibS::create(vector<CFigure*> el,int i)
{
	elem=el;
}
void CLibS::add(CFigure *el)
{
		el=el->generateCopy();
	    elem.push_back(el);
		elem[iter]->setLibstatus(true);
		elem[iter]->setMultselect(false);
		elem[iter]->setspline(true);
			
/*		elem=(CFigure**) realloc(elem,m+sizeof(el));
		sel=(bool*) realloc(sel,bc+sizeof(bool));

		m=_msize(elem);
		bc=_msize(sel);
		
		elem[iter]=el;
		elem[iter]->setLibstatus(true);
		elem[iter]->setspline(true);

		ptbegin.insert(ptbegin.end(),el->ptbegin.begin(),el->ptbegin.end());
		ptend.insert(ptend.end(),el->ptend.begin(),el->ptend.end());*/
		updatecore();
		iter++;

}

void CLibS::drawinit(CDC *hdc,CVector begin, CVector end)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->drawinit(hdc,begin,end);
	}
}

bool CLibS::PtinRegion(CVector point)
{
	click=false;
	for(int i=0;i<iter;i++)
	{
		bool vt;
		vt=elem[i]->inRegion(point);
		click|=vt;
		if(click)
		{
			select=full;
			for(int i=0;i<iter;i++)
			{
				elem[i]->setselectmode(selecttoint());
			}
			break;
		}
	}
	   rotateCenter=box.center();
	if((Rectangleselect(point))&&(!getmultcore()))
	{
		if((recselectpoint!=rotsca)&&(recselectpoint!=rotmsca))
		{
	   rotateCenter=box.getclosestOpCorner(point);
		}else
		{
			if(recselectpoint==rotsca)
			{
				angle=0;
				if(prevrotateCenter==v0)
				{
				rotateCenter=box.center();
				}
			}
		}
		select=st;
//		if(!multiselect)
//		{
		CVector _rot=getRotateCenter();
			for(int i=0;i<iter;i++)
			{
		//		elem[j]->setrecselect(i);
				elem[i]->setbox(box);
				elem[i]->setmultcore(true);
				elem[i]->setselectmode(selecttoint());
				elem[i]->setrecselect(recselectpoint);
				elem[i]->setRotateCenter(_rot);
			}
//		}
	click=true;
	}
	else
	{
		if(!multiselect)
		{
			for(int i=0;i<iter;i++)
			{
				elem[i]->setmultcore(false);
			}	
		}
	}
	if(!multiselect)
	{
		for(i=0;i<iter;i++)
		{
			elem[i]->setMultselect(click);
		}
	}
			rotateCenter=box.center();
	return click;
}

void CLibS::setrecselect(int rd)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setrecselect(rd);
	}
	CFigure::setrecselect(rd);
}

void CLibS::setMultselect(bool mult)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setMultselect(mult);
	}
	CFigure::setMultselect(mult);
}


void CLibS::setcore(vector<CVector> co)
{
	core.clear();
	for(int i=0;i<iter;i++)
	{
		elem[i]->setcore(co);
	}
	CFigure::setcore(co);
	p0=core[0];
	p01=core[1];
	p1=core[2];
	p12=core[3];
	p2=core[4];
	p23=core[5];
	p3=core[6];
	p30=core[7];
	pc=core[8];


}

void CLibS::setmultcore(bool co)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setmultcore(co);
	}
	CFigure::setmultcore(co);

}



void CLibS::draw(CDC* hdc)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->draw(hdc);
	}
	
	if(/*(!multiselect)&&*/(!getLibstatus()))
	{
//	selectSM(hdc);
	if(transselectedstate()) drawselect(hdc);
	}
	if (getRotstate())
	{
	hdc->MoveTo(CVector(rotateCenter.x,rotateCenter.y-15));
	hdc->LineTo(CVector(rotateCenter.x,rotateCenter.y+15));
	hdc->MoveTo(CVector(rotateCenter.x-15,rotateCenter.y));
	hdc->LineTo(CVector(rotateCenter.x+15,rotateCenter.y));
	}
	
	
}

void CLibS::createvec()
{

}

void CLibS::translate(CWnd *wnd,CDC *hdc,CVector prevpos, CVector postpos)
{
//	if((click)||(multiselect))
	{
	int irop=hdc->SetROP2(R2_NOTXORPEN);
		box.draw(hdc);
		for(int i=0;i<iter;i++)
		{
			elem[i]->translate(wnd,hdc,prevpos,postpos);

		}

		updatecore();
		if(!getLibstatus())
		{
			for(int i=0;i<iter;i++)
			{
				elem[i]->setbox(box);
			}
		}
		box.draw(hdc);
	hdc->SetROP2(irop);
//		if(!getLibstatus()) drawTrans(hdc);
	}

}

void CLibS::Translate(CVector v)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->Translate(v);
	}
}
void CLibS::TranslateTo(CVector v)
{
	CVector v10=box.center();
	CVector v1=v-v10;
	CVector v2,v20;
	CAABB boc;
	for(int i=0;i<iter;i++)
	{
		boc=elem[i]->getbox();
		v20=boc.center();
		v2=v20+v1;
		elem[i]->TranslateTo(v2);
	}
	CFigure::TranslateTo(v);
}


void CLibS::Rotate(CVector point)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setRotateCenter(rotateCenter);
		elem[i]->Rotate(point);
	}
	CFigure::setRotateCenter(rotateCenter);
	if(!multiselect) CFigure::Rotate(point);
}
CMesh* CLibS::Clip0(CFigure* f)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->Clip0(f);
	}
	return NULL;
}

void CLibS::rotate(float u, short sens)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setRotateCenter(rotateCenter);
		elem[i]->rotate(u,sens);
	}
	updatecore();
//	CFigure::setRotateCenter(rotateCenter);
//	if(!multiselect) CFigure::rotate(u,sens);
}

void CLibS::Rotate(int sens,CVector prevpoint,CVector postpoint)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->Rotate(sens,prevpoint,postpoint);
	}
	if(!multiselect) CFigure::Rotate(sens,prevpoint,postpoint);
}
void CLibS::Scale(int sens,CVector prevpoint,CVector postpoint)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->Scale(sens,prevpoint,postpoint);
	}
	if(!multiselect) CFigure::Scale(sens,prevpoint,postpoint);
}
void CLibS::scale(float u, short sens)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->scale(u,sens);
	}
	if(!multiselect) CFigure::scale(u,sens);
}

CFigure* CLibS::copy2(float d, CFigure *pbulk)
{
	for(int i=0;i<iter;i++)
	{
//		create(elem[i]->copy2(d,pbulk),i);
	}
	return NULL;
}

void CLibS::setRotateCenter(CVector point)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setRotateCenter(point);
	}
	/*if(!multiselect)*/ CFigure::setRotateCenter(point);
}

bool CLibS::rotateSM(CDC* hdc, int sens,CVector prevpoint, CVector postpoint)
{
 return CFigure::rotateSM(hdc,sens,prevpoint,postpoint,false);
}

void CLibS::moveRotCenter(CDC *hdc, CVector prevpoint, CVector postpoint)
{
	CFigure::moveRotCenter(hdc,prevpoint,postpoint);
	for(int i=0;i<iter;i++)
	{
		elem[i]->setRotateCenter(getRotateCenter());
	}


}
void CLibS::drawTrans(CDC *hdc)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->drawTrans(hdc);
	}
	CFigure::drawTrans(hdc);
}



void CLibS::setLcolor(CDC *hdc, COLORREF color, COLORREF bcolor)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setLcolor(hdc,color,bcolor);
	}
	CFigure::setLcolor(hdc,color,bcolor);

}

void CLibS::init()
{
	for(int i=0;i<iter;i++)
	{
		delete elem[i];
	}
	elem.clear();
	iter=0;
}

void CLibS::copy(vector<CFigure*> el,int it)
{

}

void CLibS::update(CFigure *el, int pos)
{
	elem[pos]=el;
}

bool CLibS::getsel(int i)
{
	return sel[i];
}

vector<CFigure*> CLibS::degroup()
{
	vector<CFigure*> l;
	l.resize(iter);
	for(int i=0;i<iter;i++)
	{
		l[i]=elem[i]->generateCopy();
		l[i]->setMultselect(false);
		l[i]->setLibstatus(false);
		l[i]->setspline(false);
		l[i]->setInit();
	}
	return l;
}

int CLibS::getnblibelemt()
{
	return iter;
}

void CLibS::setRotClick(bool value)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setRotClick(value);
	}
	CFigure::setRotClick(value);
}

void CLibS::setTransref(bool b)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setTransref(b);
	}
	CFigure::setTransref(b);
}
void CLibS::setReflineP(CVector begin, CVector end)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setReflineP(begin,end);
	}
	CFigure::setReflineP(begin,end);
}


void CLibS::clear()
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->clear();
	}
	CFigure::clear();
}

void CLibS::setLibstatus(bool sv)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setLibstatus(sv);
	}
	CFigure::setLibstatus(sv);
}



/*int CLibS::gethandle()
{
//	return handle;

}*/
void CLibS::savefiledxf(CStdioFile& file)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->savefiledxf(file);
	}
}
void CLibS::savefile(CFile &file)
{
		file.Write(&iter,sizeof(int));
		
		CString nm;
		int sz;
		for(int i=0;i<iter;i++)
		{
			nm=elem[i]->getName();
			if(nm=="CLine")
			{
				sz=0;
			}
			if(nm=="CRectangle")
			{
				sz=1;
			}
			else
			if(nm=="CQLine")
			{
				sz=2;
			}
			else
			if(nm=="CBezier")
			{
				sz=3;
			}
			else
			if(nm=="CCercle")
			{
				sz=4;
			}
			else
			if(nm=="CLibS")
			{
				sz=5;
			}
			else
			if(nm=="CTextCad")
			{
				sz=6;
			}
			else
			if(nm=="CImage")
			{
				sz=7;
			}
			file.Write(&sz,sizeof(sz));
			elem[i]->savefile(file);
		}

/*	for(int j=0; j<iter;j++)
	{
		file.Write(&sel[j],sizeof(bool));
	}
*/
		i=libname.GetLength();
		file.Write(&i,sizeof(int));
		for(int j=0;j<i;j++)
		{
		char c=libname[j];
		file.Write(&c,sizeof(c));
		}

		i=libfunct.GetLength();
		file.Write(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		char c=libfunct[j];
		file.Write(&c,sizeof(c));
		}

	CFigure::savefile(file);
}


void CLibS::openfile(CFile &file,CDC* hdc)
{

		file.Read(&iter,sizeof(int));
//		file.Read(&fig, sizeof(CFigure**)*fit);
		string nm;
		int sz;
		for(int i=0;i<iter;i++)
		{
			file.Read(&sz,sizeof(sz));
			if(sz==0)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CLine(file);
				elem.push_back(new CLine(file));
			}
			if(sz==1)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CRectangle(file);
				elem.push_back(new CRectangle(file));
			}
			else
			if(sz==2)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CQLine(file);
				elem.push_back(new CQLine(file));

			}
			else
			if(sz==3)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CBezier(file);
				elem.push_back(new CBezier(file));
			}
			else
			if(sz==4)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CCercle(file);
				elem.push_back(new CCercle(file));
			}
			else
			if(sz==5)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
///				m=_msize(elem);
//				elem[i]=new CLibS(file);
				elem.push_back(new CLibS(file,hdc));
			}
			else
			if(sz==6)
			{
//				elem=(CFigure**) realloc(elem,m+sizeof(CFigure*));
//				m=_msize(elem);
//				elem[i]=new CTextCad(file);
				elem.push_back(new CTextCad(file,hdc));
			}
		}
 bc=0; 
/* for(int j=0; j<iter;j++)
 {
	sel=(bool*) realloc(sel,bc+sizeof(sel));
	bc=_msize(sel);
   file.Read(&sel[j],sizeof(sel));
 }
*/
		file.Read(&i,sizeof(int));
		char c;
		for(int j=0;j<i;j++)
		{
		file.Read(&c,sizeof(c));
		libname.Insert(j,c);
		} 

		file.Read(&i,sizeof(int));
		for(j=0;j<i;j++)
		{
		file.Read(&c,sizeof(c));
		libfunct.Insert(j,c);
		} 

		CFigure::openfile(file);
		updatecore();
		name="CLibS";
}

CLibS::CLibS(CFile &file, CDC* hdc)
{
	iter=0;
	name="CLibS";
	elem.clear();
	sel=NULL;
	m=0;
	bc=0;
	openfile(file,hdc);

}

CFigure * CLibS::getEl(int i)
{
	return elem[i];
}
string CLibS::getLibName()
{
	return libname;
}

void CLibS::setselectmode(SELECT j)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setselectmode(j);
	}
	CFigure::setselectmode(j);
}

void CLibS::setInit()
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setInit();
	}
	CFigure::setInit();
}

void CLibS::setLibstatusV(bool b)
{
	CFigure::setLibstatusV(b);
}

void CLibS::setLayer(FLAYER &lay)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setLayer(lay);
	}
	CFigure::setLayer(lay);

}

void CLibS::closecurve(CVector point, CDC *hdc)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->closecurve(point,hdc);
	}
	CFigure::closecurve(point,hdc);

}

void CLibS::setMult(bool b)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->setMultselect(b);
	}
}

bool CLibS::takeinfo(CVector point)
{
 return false;
}

void CLibS::connectTo(CLibS *f, int f1, int f2, float u1, float u2)
{
		CVector v1=f->getEl(f2)->getPoint(u1);
		CVector v=getEl(f1)->getPoint(u2);
		CVector v2=v-v1;
		Translate(v2);
}

CFigure* CLibS::generateCopy()
{
	CLibS* l=new CLibS;
	l->copy(this);
	return l;

}
void CLibS::setbox(CAABB b)
{
	for(int i=0;i<iter;i++)
	{
			elem[i]->setbox(b);
	}
}

const CAABB CLibS::getbox(CDC* hdc) 
{
	CAABB bo;
	for(int i=0;i<iter;i++)
	{
			bo.add(elem[i]->getbox(hdc));
	}
	return bo;
}
void CLibS::copy(CLibS *l)
{
	elem.resize(l->iter);
	iter=l->iter;
	for(int i=0;i<iter;i++)
	{
			elem[i]=l->elem[i]->generateCopy();
	}
	CFigure::copy(l);
}
void CLibS::UpdateMesh()
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->UpdateMesh();
	}
}

void CLibS::updatecore()
{
	box.empty();
	for(int i=0;i<iter;i++)
	{
			box.add(elem[i]->getbox());
	}
	CFigure::setcore();
}

void CLibS::editobj(CVector point)
{
	for(int i=0;i<iter;i++)
	{
			elem[i]->editobj(point);
	}
}

bool CLibS::inRegion(CVector point)
{
	bool g=false;	
	for(int i=0;i<iter;i++)
	{
			g=elem[i]->inRegion(point);
			if (g) return true;
	}
	return false;

}

//DEL void CLibS::UpdateMesh()
//DEL {
//DEL 	for(int i=0;i<iter;i++)
//DEL 	{
//DEL 			elem[i]->UpdateMesh();
//DEL 	}
//DEL 
//DEL }

void CLibS::OffsetMesh(float u, CFigure *f)
{
	CLibS* fv=(CLibS*) f;
	for(int i=0;i<iter;i++)
	{
			elem[i]->OffsetMesh(u,fv->getEl(i));
	}

}

float CLibS::Min_dist_toEdge(CVector v)
{
	float u=1E5,u1,v1,v2;
	for(int i=0;i<iter;i++)
	{
		u1=elem[i]->Min_dist_toEdge(v);
		v1=(u1>0)?u1:-u1;
		v2=(u>0)?u:-u;
		u=(v2<v1)?u:u1;
	}
	return u;

}

void CLibS::breakcurve(CVector v1,CVector v2)
{
	for(int i=0;i<iter;i++)
	{
		elem[i]->breakcurve(v1,v2);
	}

}

vector<CVector> CLibS::getSelectvec(CVector point)
{
	vector<CVector> cp;
	cp.clear();
	for(int i=0;i<iter;i++)
	{
		cp=elem[i]->getSelectvec(point);
		if(!cp.empty())
			return cp;
	}
	return cp;
	
}
