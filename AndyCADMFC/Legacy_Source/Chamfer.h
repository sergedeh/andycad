// Chamfer.h: interface for the CChamfer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAMFER_H__DB4616E9_0408_4227_B251_24629FF09FC1__INCLUDED_)
#define AFX_CHAMFER_H__DB4616E9_0408_4227_B251_24629FF09FC1__INCLUDED_

#include "Verb.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChamfer:  public CVerb
{
public:
	void Execute();
	CChamfer(CString s);
	virtual ~CChamfer();

};

#endif // !defined(AFX_CHAMFER_H__DB4616E9_0408_4227_B251_24629FF09FC1__INCLUDED_)
