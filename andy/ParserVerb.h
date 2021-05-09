// ParserVerb.h: interface for the CParserVerb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERVERB_H__5D343E13_302F_49EB_BB75_50666F4D5AF1__INCLUDED_)
#define AFX_PARSERVERB_H__5D343E13_302F_49EB_BB75_50666F4D5AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserObject.h"
#include "multvar.h"

class CParserVerb : public CParserObject  
{
public:
	int Grace;
	int CIRCLE2POINT;
	bool isLegal();
	void addArgs(CParserObject* p);
	void addArgs(CMultVar* mv);
	CParserVerb* getVerb(int s);
	CParserVerb(CString s);
	virtual ~CParserVerb();
	int  LINE, RECTANGLE, CIRCLE,  SPLINE, PERPENDICULARLINE;
	int TRIM, CHAMFER, FILLET, SLIDE;
	int ADDNODE, DELETENODE, RECARRAYCOPY,POLARCOPY, PARRELLCOPY;
	int ANGULARCOPY, ARC, POLYLINE,MIRRORWITHCOPY, MIRRORWITHOUTCOPY;
	int SYMMETRICCOPY, SYMWITHOUTCOPY;

protected:
	vector<CParserObject*> args;

	
};

#endif // !defined(AFX_PARSERVERB_H__5D343E13_302F_49EB_BB75_50666F4D5AF1__INCLUDED_)
