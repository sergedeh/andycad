//
//  CVector.h
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#ifndef __testcommand__CVector__
#define __testcommand__CVector__

//#define pi 3.14

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "../utils/CPoint.hpp"
#include "../utils/CSize.hpp"
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
	struct V {
		double x = 0;
		double y = 0;
		double z = 0;
		double w = 0;

		void saveTo(std::ofstream& file) const {
			file.write(reinterpret_cast<const char*>(&x), sizeof(x));
			file.write(reinterpret_cast<const char*>(&y), sizeof(y));
			file.write(reinterpret_cast<const char*>(&z), sizeof(z));
			file.write(reinterpret_cast<const char*>(&w), sizeof(w));
		}

		void loadFrom(std::ifstream& file) {
			file.read(reinterpret_cast<char*>(&x), sizeof(x));
			file.read(reinterpret_cast<char*>(&y), sizeof(y));
			file.read(reinterpret_cast<char*>(&z), sizeof(z));
			file.read(reinterpret_cast<char*>(&w), sizeof(w));
		}

		long skipRead(std::ifstream& file) {
			file.seekg(sizeof(double) * 4, std::ios::cur);
			return static_cast<long>(file.tellg());
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
	long skipRead(ifstream& file);
	void loadFrom(ifstream& file);
	void saveTo(ofstream& file);
	void zoom(double zr);
	void assignF();
	bool snaptoplane(CVector& v);
	PLANESNAP getplanesnap();
    std::string setplanesnap(std::string s);
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
//    CVector(CVector& v);
    
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
	operator CPoint();
	/*inline*/ void operator -=(const CVector v);    
	/*inline*/ void operator +=(const CVector v);
	/*inline*/ CVector operator +(CVector v);
	/*inline*/ CVector operator -(CVector v);
	inline CVector operator -(){ return CVector(-x,-y,-z);}
	inline CVector operator -(int i){return CVector(x-i,y-i,z-i);}
	inline CVector operator +(int i){return CVector(x+i,y+i,z+i);}
	/*inline*/ CVector operator /(double i);
	inline bool operator >(const CVector v){ return((x>v.x)&&(y>v.y));}
	inline bool operator <(const CVector v){ return ((x<v.x)&&(y<v.y));}
	inline bool operator <=(const CVector v){ return ((x<=v.x)&&(y<=v.y));}
	inline bool operator >=(const CVector v){ return((x>=v.x)&&(y>=v.y));}
	
    
	inline bool operator !=(const CVector v) const { return ((sqrt((z-v.z)*(z-v.z))>1E-5)||(sqrt((x-v.x)*(x-v.x))>1E-5)||(sqrt((y-v.y)*(y-v.y))>1E-5));}
	inline bool operator ==(const CVector& v) const { return ((sqrt(pow(z-v.z,2))<1E-6)&&(sqrt(pow(x-v.x,2))<1E-6)&&(sqrt(pow(y-v.y,2))<1E-6));}
    
	inline CPoint getCenter(){CPoint v;v.x=x/2;v.y=y/2;return v;}// CPoint(x/2,y/2);}
    
	CPoint ptsBegin;        // beginning point
	CPoint ptsEnd;// new endpoint
    
	double x,y,z,w,ws;
	double xhit,yhit,zhit;
    
    
protected:
    
};

struct FINFO
{
	std::string name;
	std::string description;
	std::string author;
	double cost;
	double distance;
	double angle;
	double surface;
	FINFO()
	{
		name = "";
		description = "";
		author = "";
		cost = -1;
		distance = -1;
		angle = -1;
		surface = -1;

	}
};
struct FLAYER
{
	std::string name;
	int handle;
	bool on;
	bool lock;
	bool clear;
	FLAYER()
	{
		handle = 0;
		on = false;
		clear = true;
		lock = false;
		name = "";
	}
};
double absc(const CVector v,bool b=false);
double argu(const CVector v,bool b=false);
bool pointinRegion(CVector point, CVector region);
double pointtoVector(CVector line,CVector point,CVector* hitpoint=NULL);
CVector polarc(double absc,double argu,bool b=false);
CVector getcamor();
int orientation(CVector v1,CVector v2, CVector v3);

extern CPoint operator - (CPoint p1, CPoint p2);
extern CPoint operator + (CPoint p1, CPoint p2);
extern bool operator == (CPoint p1, CPoint p2);
class isclose
{
public:
	isclose(CVector p) :v(p) {};
	bool operator ()(CVector v1, CVector v2)
	{
		return (v1.absc(CVector(v1, v)) < v1.absc(CVector(v2, v)));
	}
private:
	CVector v;
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
		handle = 0;
		name = "";
		font = "";
		fixed_height = 0;
		width_factor = 1;
	}
};

#endif /* defined(__testcommand__CVector__) */
