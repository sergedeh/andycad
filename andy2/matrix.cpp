// Matrix.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Matrix.h"
#include<math.h>

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

}
double* CMatrix::searchmat(double *C,int r,int s,int i1,int j1,int i2,int j2)
{
	int j=j1;
	double ju;
	double *d;
	d=new double[3];

	d[0]=__max(C[s*i1+j1],C[s*i1+j1+1]);
	d[1]=j1;
	d[2]=i1;

	for(int i=i1;i<=i2;i++)
	{
		j=j1;
		d[0]=__max(d[0],C[s*i+j]);
		if(d[0]==C[s*i+j])
		{
			d[1]=j;
			d[2]=i;
			ju=d[0];
		}
		for (j=j1;j<j2;j++)
		{
			d[0]=__max(d[0],C[s*i+j+1]);
			if(d[0]==C[s*i+j+1])
			{
				d[1]=j+1;
				d[2]=i;
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
			inter=C[s*i+iter];
			C[s*i+iter]=C[s*j+iter];
			C[s*j+iter]=inter;
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
		C[s*r+k]+=(l-k);
		C[s*r+l]+=(l-k);


		for(int iter=i;iter<=j;iter++)
		{
			inter=C[s*iter+k],
			C[s*iter+k]=C[s*iter+l];
			C[s*iter+l]=inter;
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
	if(C[s*i+i]==1)
	{
		double tm=C[s*k+i];
		C[s*k+i]=0;
		for(int q=u; q<=s;q++)
		{
			C[k*s+q]=C[k*s+q]-tm*C[i*s+q];
		}

	}
	return 1;

}

double CMatrix::scale(double *C, int r, int s, int i, int u)
{
	double piv=C[s*i+i];
	for(int j=u; j<=s;j++)
	{
		C[i*s+j]=C[i*s+j]/piv;
	}
	return piv;
}

int  CMatrix::scramble(double *C,int r, int s, int n)
{
	double *Cs;
	Cs=new double[(r+1)*(s+1)];
	for(int i=0;i<=r;i++)
	{
		for(int j=0;j<=s;j++)
		{
			Cs[s*i+j]=0;
		}
	}


	for(int iter=1;iter<=n;iter++)
	{
		for (int jiter=1;jiter<=s;jiter++)
		{
		 Cs[s*(int)C[s*r+iter]+jiter]=C[s*iter+jiter];
		}
	}
	for(i=1;i<=r;i++)
	{
		for(int j=1;j<=s;j++)
		{
			C[s*i+j]=Cs[s*i+j];
		}
	}

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
		D[sp*iti+itj]=0;
		}
	}
		for(int itj=1;itj<=sp;itj++)
		{
		D[sp*itj+itj]=q;
		}

	for(iti=i;iti<=i+(n-j);iti++)
	{
		for(itj=j;itj<=j+(n-j);itj++)
		{
		C[s*iti+itj]=D[n*iti+itj];
		}
	}
	return 1;

}

double CMatrix::scaler(double *C,double *R,int r,int s,int i,int u)
{
	double piv=C[s*i+i];
	for(int j=u; j<=s;j++)
	{
		R[i*s+j]=(R[i*s+j]/piv)-((R[i*s+j]*C[s*i+j])/(piv*piv));
	}
	return piv;


}

void CMatrix::pivotr(double *C,double *R,int r,int s,int i,int k,int u)
{
	if(C[s*i+i]==1)
	{
		
	//	C[s*k+i]=0;
		for(int q=u; q<=s;q++)
		{
			R[k*s+q]=R[k*s+q]-C[k*s+i]*R[i*s+q]-R[k*s+i]*C[i*s+q];
		}

	}
//	return 1;
}





void CMatrix::matalg(double *C, int r, int s,int m, int n, int p, int opt, double eps)
{
	double *R,*Z;
	int i,j,Det, ii,jj, k, psrank;
	bool Done;
	if (opt==1) //inverse calculation;
	{
		ident(C,r,s,1,n+1,n,1);
	}
	R=new double[(r)*(s)];
	Z=new double[3];
	for(i=1;i<=r;i++) //random error initialization
	{
		for(int j=1;j<=s;j++)
		{
			R[s*i+j]=0.000000000001*(rand()-500000000000)*eps*C[s*i+j];
		}
	}
	for(j=1;j<=n;j++) // Set row permutation matrix to identity
	{
		C[s*r+j]=j;
	}
	//forward solution
	Det=1; Done=false; i=0;
	while((i<m)&&(!Done))
	{
		Z=searchmat(C,r,s,i+1,i+1,m,n);jj=Z[1];ii=Z[2];
		if(sqrt(Z[0]*Z[0])>sqrt(R[s*ii+jj]*R[s*ii+jj]))
		{
			i++;
		//switch row
		Det=Det*switchrow(C,r,s,i,ii,i,s);
		switchrow(R,r,s,i,ii,i,s);
		// switch columns
		Det=Det*switchcol(C,r,s,i,jj,1,r);
		switchcol(R,r,s,i,jj,1,r);
		// divide by pivot element
		scaler(C,R,r,s,i,i);
		Det=Det*scale(C,r,s,i,i);
			for (int k=i+1 ;k<=m; k++)
			{
			// reduce row k against row i
				pivotr(C,R,r,s,i,k,i+1);
				pivot(C,r,s,i,k,i+1);
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
			for (j=1;j<=p;j++)
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
		for (j=psrank;j>=2;j--)
		{
			for(i=1;i<=j-1;i++)
			{				
				pivotr(C,R,r,s,j,i,psrank+1);
				pivot(C,r,s,j,i,psrank+1);
				C[(s)*i+j]=0; R[(s)*i+j]=0;
			}
		}
	// end back solution, insert minus identity in basis
	if (psrank<n)
	{
	// fill bottom of basis matrix with -I
		ident(C,r,s,psrank+1,psrank+1,n-psrank,-1);
	// fill under right-hand sides with zeroes
		for(i=psrank+1 ;i<=n;i++)
		{
			for (j=n+1 ;j<=s;j++)
			{
				C[s*i+j]=0; 
			}
		}
	// fill under R matrix with zeroes
		for(i=psrank+1;i<=n;i++)
		{
			for(j=n-psrank;j<=s;j++)
			{
				R[s*i+j]=0;
			}
		}
	}
	// permute rows prior to output
	*Z=scramble(C,r,s,n);
	// copy row r of C to row r of R
	for(j=1;j<=n;j++)
	{
		R[(s)*r+j]=C[(s)*r+j];
	}
	scramble(R,r,s,n);
//	return(Det,psrank,evalm(R));
	
	}
