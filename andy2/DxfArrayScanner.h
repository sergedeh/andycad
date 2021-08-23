// DxfArrayScanner.h: interface for the CDxfArrayScanner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXFARRAYSCANNER_H__F3F13F0B_6747_43F1_87DD_0BA69DD4A7B9__INCLUDED_)
#define AFX_DXFARRAYSCANNER_H__F3F13F0B_6747_43F1_87DD_0BA69DD4A7B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <vector>
using namespace std;
class CDxfArrayScanner  
{
public:
	bool hasNext();
	CDxfArrayScanner();
	CDxfArrayScanner(vector<string> lines);
	virtual ~CDxfArrayScanner();

};

#endif // !defined(AFX_DXFARRAYSCANNER_H__F3F13F0B_6747_43F1_87DD_0BA69DD4A7B9__INCLUDED_)
