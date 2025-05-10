//
//  CMatrix.cpp
//  testcommand
//
//  Created by Serge Deh on 10/15/20.
//  Copyright (c) 2020 Serge Deh. All rights reserved.
//

#include "CMatrix.h"
// Matrix1.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix()
{
    
}

CMatrix::~CMatrix()
{
    //	delete R;
    
}

double* CMatrix::searchmat(double *C,int r,int s,int i1,int j1,int i2,int j2)
{
	int j=j1;
	double ju,jb;
	double h1,h2;
	double d[3];
	
	if ((j1+1)!=s)
	{
		h1=(C[(s+1)*i1+j1]>0)?C[(s+1)*i1+j1]:-C[(s+1)*i1+j1];
		h2=(C[(s+1)*i1+j1+1]>0)?C[(s+1)*i1+j1+1]:-C[(s+1)*i1+j1+1];
        d[0]=h1>h2? C[(s+1)*i1+j1]:C[(s+1)*i1+j1+1];
		if(d[0]==C[(s+1)*i1+j1])
		{
			d[1]=j1;
			d[2]=i1;
		}else
            if(d[0]==C[(s+1)*i1+j1+1])
            {
                d[1]=j1+1;
                d[2]=i1;
            }
        
	}
	else
	{
		d[0]=C[(s+1)*i1+j1];
		d[1]=j1;
		d[2]=i1;
        
	}
    
    
	for(int i=i1;i<=i2;i++)
	{
		j=j1;
		ju=d[0];
		h1=(d[0]>0)?d[0]:-d[0];
		h2=(C[(s+1)*i+j]>0)?C[(s+1)*i+j]:-C[(s+1)*i+j];
        
		d[0]=(h1>h2)? d[0]:C[(s+1)*i+j];
		jb=d[0];
		if(d[0]==C[(s+1)*i+j])
		{
			h1=(ju-jb>0)?ju-jb:jb-ju;
			if (h1>1E-15)
			{
                d[1]=j;
                d[2]=i;
                ju=d[0];
			}
		}
		for (j=j1;j<j2;j++)
		{
			ju=d[0];
            
			h1=(d[0]>0)?d[0]:-d[0];
			h2=(C[(s+1)*i+j+1]>0)?C[(s+1)*i+j+1]:-C[(s+1)*i+j+1];
			
			d[0]=h1>h2? d[0]:C[(s+1)*i+j+1];
			jb=d[0];
			if(d[0]==C[(s+1)*i+j+1])
			{
				h1=(ju-jb>0)?ju-jb:jb-ju;
				if (h1>1E-15)
				{
                    d[1]=j+1;
                    d[2]=i;
				}
			}
		}
	}
	return d;
}


int CMatrix::switchrow(double *C, int r, int s, int i, int j, int k, int l)
{
	double inter=0;
    
	if(i!=j)
	{
		for(int iter=k;iter<=l;iter++)
		{
			inter=C[(s+1)*i+iter];
			C[(s+1)*i+iter]=C[(s+1)*j+iter];
			C[(s+1)*j+iter]=inter;
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

int CMatrix::switchcol(double *C, int r, int s, int k, int l, int i, int j)
{
	double inter;
    
	if(k!=l)
	{
        
        //	C[(s+1)*r+l]=C[(s+1)*r+k];
        //	C[(s+1)*r+k]=l;
        
		for(int iter=i;iter<=j;iter++)
		{
			inter=C[(s+1)*iter+k];
			C[(s+1)*iter+k]=C[(s+1)*iter+l];
			C[(s+1)*iter+l]=inter;
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

int CMatrix::pivot(double *C, int r, int s, int i, int k, int u)
{
	if(C[(s+1)*i+i]==1)
	{
		double tm=C[(s+1)*k+i];
		C[(s+1)*k+i]=0;
		for(int q=u; q<=s;q++)
		{
			C[k*(s+1)+q]=C[k*(s+1)+q]-tm*C[i*(s+1)+q];
		}
        
	}
	return 1;
    
}

double CMatrix::scale(double *C, int r, int s, int i, int u)
{
	double piv=C[(s+1)*i+i];
	for(int j=u; j<=s;j++)
	{
		C[i*(s+1)+j]=(double)C[i*(s+1)+j]/piv;
	}
	return piv;
}

int  CMatrix::scramble(double *Cv,int r, int s, int n)
{
	double *Cs;
	Cs=new double [(r+1)*(s+1)];
	
	for(int i=0;i<=r;i++)
	{
		for(int j=0;j<=s;j++)
		{
			Cs[(s+1)*i+j]=0;
		}
	}
    
    
	for(int iter=0;iter<=n;iter++)
	{
		for (int jiter=0;jiter<=s;jiter++)
		{
            Cs[(s+1)*(int)Cv[(s+1)*r+iter]+jiter]=Cv[(s+1)*iter+jiter];
		}
	}
	for(int i=0;i<=r;i++)
	{
		for(int j=0;j<=s;j++)
		{
			Cv[(s+1)*i+j]=Cs[(s+1)*i+j];
		}
	}
	delete []Cs;
    
	return 1;
}

int CMatrix::ident(double *C,int r, int s,int i, int j, int n, int q)
{
	double *D;
	D=new double[(n+1)*(n+1)];
	int rp=n;
	int sp=n;
	for(int iti=0;iti<=rp;iti++)
	{
		for(int itj=0;itj<=sp;itj++)
		{
            D[(sp+1)*iti+itj]=0;
		}
	}
    for(int itj=0;itj<=sp;itj++)
    {
		D[(sp+1)*itj+itj]=q;
    }
    
	for(int iti=i;iti<=i+(n-j);iti++)
	{
		for(int itj=j;itj<=j+(n-j);itj++)
		{
            C[(s+1)*iti+itj]=D[(n+1)*iti+itj];
		}
	}
	delete [] D;
	return 1;
    
}

double CMatrix::scaler(double *C,double *R,int r,int s,int i,int u)
{
	double piv=C[(s+1)*i+i];
	for(int j=u; j<=s;j++)
	{
		R[i*(s+1)+j]=(R[i*(s+1)+j]/piv)-((R[i*(s+1)+j]*C[(s+1)*i+j])/(piv*piv));
	}
	return piv;
    
    
}

void CMatrix::pivotr(double *C,double *R,int r,int s,int i,int k,int u)
{
	if(C[(s+1)*i+i]==1)
	{
		
        //	C[(s+1)*k+i]=0;
		for(int q=u; q<=s;q++)
		{
			R[k*(s+1)+q]=R[k*(s+1)+q]-C[k*(s+1)+i]*R[i*(s+1)+q]-R[k*(s+1)+i]*C[i*(s+1)+q];
		}
        
	}
    //	return 1;
}





void CMatrix::matalg(double *C, int r, int s,int m, int n, int p, int opt, double eps)
{
	double *Z;
	int i,j,Det, ii,jj, k, psrank;
	bool Done;
	
	if (opt==1) //inverse calculation;
	{
		ident(C,r,s,1,n+1,n,1);
	}
	R=new double[(r+1)*(s+1)];
	
	for(i=0;i<=r;i++) //random error initialization
	{
		for(int j=0;j<=s;j++)
		{
            R[(s+1)*i+j]=0.000000000001*(rand()-500000000000)*eps*C[(s+1)*i+j];
		}
	}
	for(j=0;j<=n;j++) // Set row permutation matrix to identity
	{
		C[(s+1)*r+j]=j;
	}
	//forward solution
	Det=1; Done=false; i=0;
	while((i<m+1)&&(!Done))
	{
		Z=searchmat(C,r,s,i,i,m,n);jj=Z[1];ii=Z[2];
		if(sqrt(Z[0]*Z[0])>sqrt(R[(s+1)*ii+jj]*R[(s+1)*ii+jj]))
		{
			i++;
            //switch row
            Det=Det*switchrow(C,r,s,i-1,ii,i-1,s);
            switchrow(R,r,s,i-1,ii,i-1,s);
            // switch columns
            Det=Det*switchcol(C,r,s,i-1,jj,0,r);
            switchcol(R,r,s,i-1,jj,0,r);
            // divide by pivot element
            scaler(C,R,r,s,i-1,i-1);
            Det=Det*scale(C,r,s,i-1,i-1);
			for (int k=i ;k<=m; k++)
			{
                // reduce row k against row i
				pivotr(C,R,r,s,i-1,k,i);
				pivot(C,r,s,i-1,k,i);
			}
		}
		else
		{
			Done=true ;
		}
	}
	psrank=i;
    // end forward solution; begin consistency check
    if (psrank<m)
    {
        Det=0;
        for (j=0;j<=p;j++)
        {
            
            // check that right hand sides are 0 for i>psrank
            Z=searchmat(C,r,s,psrank+1,n+j,m,n+j);
            int a=Z[1];
            int b=Z[2];
            
            if(sqrt(Z[0]*Z[0])>sqrt(R[a*s+b]*R[a*s+b]))
            {		;//printf("Right hand side %d is inconsistent",j);
                
            }
        }
    }
	// equations are consistent, do back solution
    for (j=psrank-1;j>=1;j--)
    {
        for(i=1;i<=j;i++)
        {
            pivotr(C,R,r,s,j,j-1,psrank);
            pivot(C,r,s,j,i-1,psrank);
        }
    }
	// end back solution, insert minus identity in basis
	if (psrank<n+1)
	{
        // fill bottom of basis matrix with -I
		ident(C,r,s,psrank,psrank,n-psrank,-1);
        // fill under right-hand sides with zeroes
		for(i=psrank ;i<=n;i++)
		{
			for (j=n+1 ;j<=s;j++)
			{
				C[(s+1)*i+j]=0;
			}
		}
        // fill under R matrix with zeroes
		for(i=psrank;i<=n;i++)
		{
			for(j=n-psrank;j<=s;j++)
			{
				R[(s+1)*i+j]=0;
			}
		}
	}
	// permute rows prior to output
	scramble(C,r,s,n);
	// copy row r of C to row r of R
	for(j=0;j<=n;j++)
	{
		R[(s+1)*r+j]=C[(s+1)*r+j];
	}
	scramble(R,r,s,n);
	
    //	return(Det,psrank,evalm(R));
	delete [] R;
    
	
}


void CMatrix::LUG(double *D, double *N, int m, int n, int p)
{
	double *Cv;
    
	Cv=new double[(n+3)*(m+3)];
    
	int s=m+1;
	int r=n+1;
    int i,j;
	for (i=0; i<=n; i++)
	{
		for(j=0;j<=m;j++)
		{
			Cv[(s+1)*i+j]=N[s*i+j];
		}
		Cv[(s+1)*i+j]=D[i];
		Cv[(s+1)*r+i]=123;
	}
    
	
	matalg(Cv,r,s,n,m,p,2,0.00005);
    
	for (i=0; i<=n; i++)
	{
		D[i]=Cv[(s+1)*i+s];
	}
	delete []Cv;
}



void CMatrix::Transpose(CVector* C, int col, int row)
{
    CVector *CP;
    CP=new CVector[col*row];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            CP[i*row+j]=C[i*row+j];
        }
    }
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            C[i*row+j]=CP[j*col+i];
        }
    }
    delete []CP;
    
}

void CMatrix::Transpose(vector<CVector> &C, int col, int row)
{
    CVector *CP;
    CP=new CVector[col*row];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            CP[i*row+j]=C[i*row+j];
        }
    }
    CVector f;
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            C[i*row+j]=CP[j*col+i];
        }
    }
    delete []CP;
    
}

void CMatrix::Transpose(vector< vector<CVector> > &C, int col, int row)
{
    CVector *CP;
    CP=new CVector[col*row];
    CVector f;
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            CP[i*row+j]=C[i][j];
            f=C[i][j];
        }
    }
    C.resize(row);
    for(int i=0;i<row;i++)
    {
        C[i].resize(col);
        for(int j=0;j<col;j++)
        {
            C[i][j]=CP[j*row+i];
            //f=CP[j*row+i];
        }
    }
    delete []CP;
    
}


void CMatrix::Transpose(double *C, int col, int row)
{
    double *CP;
    CP=new double[col*row];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            CP[i*row+j]=C[i*row+j];
        }
    }
    double f;
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            C[i*row+j]=CP[j*col+i];
            f=C[i*row+j];
        }
    }
    delete []CP;
    
}


void CMatrix::Transpose(CGPoint *C, int col, int row)
{
    CGPoint *CP;
    CP=new CGPoint[col*row];
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            CP[i*row+j]=C[i*row+j];
        }
    }
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            C[i*row+j]=CP[j*col+i];
        }
    }
    delete []CP;
    
}

vector<CVector> CMatrix::mult(vector<CVector> v1, vector<CVector> v2)
{
    
	int n=v1.size();
	int m=v2.size();
	vector<CVector> vr(n);
    
	int i=0;
	for(int j=0;j<n;j++)
	{
        vr[j].x=v1[j].x*v2[i].x+v1[j].y*v2[i+1].x+v1[j].z*v2[i+2].x+v1[j].w*v2[i+3].x;
        vr[j].y=v1[j].x*v2[i].y+v1[j].y*v2[i+1].y+v1[j].z*v2[i+2].y+v1[j].w*v2[i+3].y;
        vr[j].z=v1[j].x*v2[i].z+v1[j].y*v2[i+1].z+v1[j].z*v2[i+2].z+v1[j].w*v2[i+3].z;
        vr[j].w=v1[j].x*v2[i].w+v1[j].y*v2[i+1].w+v1[j].z*v2[i+2].w+v1[j].w*v2[i+3].w;
	}
	return vr;
}

void CMatrix::Inverse(double *N)
{
    // matalg(N,3,3,3,3,
}
