// ParserObject.h: interface for the CParserObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSEROBJECT_H__420BDD57_599B_445B_AA53_419423C6595A__INCLUDED_)
#define AFX_PARSEROBJECT_H__420BDD57_599B_445B_AA53_419423C6595A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParserObject  
{
public:
	CParserObject();
	virtual ~CParserObject();

	static int VERB, VAR, MULTVAR,FLOAT,POINT;
protected:
	int value;
	int type;
public:
	int getValue() {return value;}
	int getType() {return type;}


};

#endif // !defined(AFX_PARSEROBJECT_H__420BDD57_599B_445B_AA53_419423C6595A__INCLUDED_)
