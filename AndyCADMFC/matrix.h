// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__39C96620_42E0_4B53_B893_C6C7D479CE33__INCLUDED_)
#define AFX_MATRIX_H__39C96620_42E0_4B53_B893_C6C7D479CE33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatrix  
{
public:
	CMatrix();
	virtual ~CMatrix();
	double* searchmat(double *C,int r,int s,int i1,int j1,int i2,int j2);
	int switchrow(double *C, int r, int s, int i, int j, int k, int l);
	int switchcol(double *C, int r, int s, int i, int j, int k, int l);
	int pivot(double *C, int r, int s, int i, int k, int u);
	double scale(double *C, int r, int s, int i, int u);
	int  scramble(double *C,int r, int s, int n);
	int ident(double *C,int r, int s,int i, int j, int n, int q);
	double scaler(double *C,double *R,int r,int s,int i,int u);
	
	void matalg(double *C, int r, int s,int m, int n, int p, int opt, double eps);
	void pivotr(double *C,double *R,int r,int s,int i,int k,int u);

};

#endif // !defined(AFX_MATRIX_H__39C96620_42E0_4B53_B893_C6C7D479CE33__INCLUDED_)
