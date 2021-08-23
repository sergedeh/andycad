// Face.h: interface for the CFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE_H__946575E9_0F6A_4FA5_97F8_FC1AF5FA6E3D__INCLUDED_)
#define AFX_FACE_H__946575E9_0F6A_4FA5_97F8_FC1AF5FA6E3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vertex.h"

class CFace  
{
public:
	vector< CVertex> vlist;
	CFace();
	virtual ~CFace();

};

#endif // !defined(AFX_FACE_H__946575E9_0F6A_4FA5_97F8_FC1AF5FA6E3D__INCLUDED_)
