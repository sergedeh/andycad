// Matrix1.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX1_H__0AF90D81_D4F7_4456_8531_EDAF4C1CF12E__INCLUDED_)
#define AFX_MATRIX1_H__0AF90D81_D4F7_4456_8531_EDAF4C1CF12E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CVector.h"
#include <vector>
using namespace std;
class CMatrix  
{
public:
	void Inverse(double *N);
	void Transpose(vector< vector<CVector> > &C, int col, int row);
	void Transpose(double *C, int col, int row);
	vector<CVector> mult(vector<CVector> v1, vector<CVector> v2);
	void Transpose(vector<CVector> &C, int col, int row);
	void Transpose(CPoint *C, int col, int row);
	void Transpose(CVector *C, int col, int row);
	void LUG(double *D,double *N, int m, int n, int p);
	CMatrix();
	virtual ~CMatrix();

	double* searchmat(double *C,int r,int s,int i1,int j1,int i2,int j2);
	int switchrow(double *C, int r, int s, int i, int j, int k, int l);
	int switchcol(double *C, int r, int s, int i, int j, int k, int l);
	int pivot(double *C, int r, int s, int i, int k, int u);
	double scale(double *C, int r, int s, int i, int u);
	int  scramble(double *Cv,int r, int s, int n);
	int ident(double *C,int r, int s,int i, int j, int n, int q);
	void matalg(double *C, int r, int s,int m, int n, int p, int opt, double eps);
	double scaler(double *C,double *R,int r,int s,int i,int u);
	void pivotr(double *C,double *R,int r,int s,int i,int k,int u);
	double *R;

};

#endif // !defined(AFX_MATRIX1_H__0AF90D81_D4F7_4456_8531_EDAF4C1CF12E__INCLUDED_)
