// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__FB88EA45_D942_4B22_93F9_980B71E05411__INCLUDED_)
#define AFX_VECTOR_H__FB88EA45_D942_4B22_93F9_980B71E05411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<vector>
#include <math.h>
using namespace std;



class CVector
{
public:
	enum PLANESNAP {front,left,top,snapnull};
	double xc,yc,zc;
private:
	void snapcoortoplane(CVector &v,int i);
	static PLANESNAP planesnap;
	
	static double n,f,r,l,t,b;
	static double Sx,Sy,zstore,wstore;
	static bool perspec;
	struct V
	{
		double x;
		double y;
		double z;
		double w;
		void savefile(CFile& file)
		{
			file.Write(&x,sizeof(double));
			file.Write(&y,sizeof(double));
			file.Write(&z,sizeof(double));
			file.Write(&w,sizeof(double));
		}
		void openfile(CFile& file)
		{
			file.Read(&x,sizeof(double));
			file.Read(&y,sizeof(double));
			file.Read(&z,sizeof(double));
			file.Read(&w,sizeof(double));
		}
		LONG Readfile(CFile& file)
		{
			file.Seek(sizeof(double),CFile::current);
			file.Seek(sizeof(double),CFile::current);
			file.Seek(sizeof(double),CFile::current);
			return file.Seek(sizeof(double),CFile::current);
		}
	};
	V vb,ve;
	static V vecx,vecy,vecz,vec0,\
			 vecix,veciy,veciz,veci0,\
			 pvecx,pvecy,pvecz,pvec0,\
			 pvecix,pveciy,pveciz,pveci0;
	CVector (const V vec);


public:
	CSize getScreen();
	CVector getscrbot();
	CVector sgetscrtop();
	CVector sgetscrb();
	void Scale(double f);
	void Normalise();
	void worldi();
	float getnearplane();
	float getfarplane();
	void setnearplane(float v);
	void setfarplane(float v);
	void world();
	LONG Readfile(CFile &file);
	void openfile(CFile& file);
	void savefile(CFile& file);
	void zoom(double zr);
	void assignF();
	bool snaptoplane(CVector& v);
	PLANESNAP getplanesnap();
	CString setplanesnap(CString s);
	void getcooro();
	void getcoorz();
	void getcoory();
	void getcoorx();
	void v3D();
	void v2D();
	bool isOn();
	bool getPerspective();
	void setScreen(int w,int h);
	void assignInv(CVector v);
	void translatecamz(CVector v);
	void translatecamxy(CVector v);
	void setperspective();
	CVector getDepth();
	CVector camxyz();
	void viewi();
	void initz();
	CPoint cP();
	void setcamor(CVector v);
	CVector getscrb();
	CVector getscrtop();
	CVector getcamz();
	CVector getcamy();
	CVector getcamx();
	CVector getcamor();
	double pointtoVector(CVector line,CVector point,CVector* hitpoint=NULL);
	void assignLP(CVector v);
	void assignPL(CVector v);
	void polarcvec(double absci, double argo);
	void assign(CVector v);
	void assign(CVector begin, CVector end);
	void assign(CVector vec,bool point);
	friend class CTVector; 
	friend class CCAM; 

	CVector();
	//CVector (CVector& v) {x=v.x;y=v.y;}
//	CVector(double fx,double fy,double fz=1);
	CVector(double fx,double fy,double fz=0,double fw=1);
	CVector(const CPoint point);
	CVector(const CVector begin,const CVector end);

	CPoint divideVect(CVector ptDebut, CVector ptEnd);
	
	bool pointinRegion(CVector point,CVector region);
	CVector ppprojection(CVector point,CVector* v1=NULL);
	CVector scalarMult(double value);
//	virtual double pointtoVector(CVector line,CVector Point);
	CVector operator *(CVector v);
	CVector operator *(double v);
	CVector intersect (CVector v,bool b=false);
	
	inline double dot(const CVector v) {return (x*v.x+y*v.y+z*v.z);}
	inline double absc(const CVector v){return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);}
	inline double argu(const CVector v){return atan2(v.y,v.x);}
	inline CVector polarc(double absc,double argu){ return CVector(absc*cos(argu),absc*sin(argu));}

	inline void nullvec(){x=0;y=0;z=0;w=0;}
	
	virtual ~CVector();
	

	//inline CPoint operator+(CPoint v){ return CPoint((int)x+v.x,(int)y+v.y);}
	operator CPoint () ;//{ return CPoint(x,y);}

	/*inline*/ void operator -=(const CVector v);//{x=x-v.x;y=y-v.y;w-=v.w;}	

	/*inline*/ void operator +=(const CVector v);//{x=x+v.x;y=y+v.y;w+=v.w;}
	/*inline*/ CVector operator +(CVector v);//{ return CVector(x+v.x,y+v.y,w+v.w);}
	/*inline*/ CVector operator -(CVector v);//{ return CVector(x-v.x,y-v.y,w-v.w);}
	inline CVector operator -(){ return CVector(-x,-y,-z);}
	inline CVector operator -(int i){return CVector(x-i,y-i,z-i);}
	inline CVector operator +(int i){return CVector(x+i,y+i,z+i);}
	/*inline*/ CVector operator /(double i);//{return CVector(x/i,y/i,w/i);}
	inline bool operator >(const CVector v){ return((x>v.x)&&(y>v.y));}
	inline bool operator <(const CVector v){ return ((x<v.x)&&(y<v.y));}
	inline bool operator <=(const CVector v){ return ((x<=v.x)&&(y<=v.y));}
	inline bool operator >=(const CVector v){ return((x>=v.x)&&(y>=v.y));}
	

	inline bool operator !=(const CVector v) const { return ((sqrt((z-v.z)*(z-v.z))>1E-5)||(sqrt((x-v.x)*(x-v.x))>1E-5)||(sqrt((y-v.y)*(y-v.y))>1E-5));}
	inline bool operator ==(const CVector& v) const { return ((sqrt(pow(z-v.z,2))<1E-6)&&(sqrt(pow(x-v.x,2))<1E-6)&&(sqrt(pow(y-v.y,2))<1E-6));}

	inline CPoint getCenter(){return CPoint(x/2,y/2);}

	CPoint ptsBegin;        // beginning point 
	CPoint ptsEnd;// new endpoint

	double x,y,z,w,ws;
	double xhit,yhit,zhit;


protected:

};

	struct FINFO
	{
		CString name;
		CString description;
		CString author;
		double cost;
		double distance;
		double angle;
		double surface;
		FINFO()
		{
			name="";
			description="";
			author="";
			cost=-1;
			distance=-1;
			angle=-1;
			surface=-1;

		}
	};
	struct FSTYLE
	{
		string name;
		string font;
		int handle;
		float fixed_height;
		float width_factor;
		FSTYLE()
		{
			handle=0;
			name="";
			font="";
			fixed_height=0;
			width_factor=1;
		}
	};
	struct FLAYER
	{
		CString name;
		int handle;
		bool on;
		bool lock;
		bool clear;
		CString line_type;
		int line_color;
		FLAYER()
		{
			handle=0;
			on=false;
			clear=true;
			lock=false;
			name="";
			line_type="";
			line_color=0;
		}
	};
	double angleBetween(CVector v1,CVector v2);
	double absc(const CVector v,bool b=false);
	double argu(const CVector v,bool b=false);
	bool pointinRegion(CVector point, CVector region);
	double pointtoVector(CVector line,CVector point,CVector* hitpoint=NULL);
	CVector polarc(double absc,double argu,bool b=false);
	CVector getcamor();
	int orientation(CVector v1,CVector v2, CVector v3);

class isclose
{
public:
	isclose(CVector p):v(p){};
	bool operator ()(CVector v1,CVector v2)
	{
		return (v1.absc(CVector(v1,v))<v1.absc(CVector(v2,v)));
	}
private:
	CVector v;
};

#endif // !defined(AFX_VECTOR_H__FB88EA45_D942_4B22_93F9_980B71E05411__INCLUDED_)
