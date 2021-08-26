// DxfParser.cpp: implementation of the CDxfParser class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "DxfParser.h"
#include "DxfArrayScanner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDxfParser::CDxfParser()
{

}

CDxfParser::~CDxfParser()
{

}

void CDxfParser::parseSync(string source)
{
	if(source.empty()) {
		_parse(source);
	}else {
		TRACE("Cannot read dxf source");
	}

}

void CDxfParser::_parse(string dxfString)
{
	vector<string> lines;
	string result=strtok(&*dxfString.begin(),"\r\n|\r|\n/g");
	while(result.length()!=0)
	{
		lines.push_back(result);
		result=strtok(NULL,"\r\n|\r|\n/g");
	}
	CDxfArrayScanner scanner(lines);
//	if(!scanner.hasNext()) throw Error('Empty file');

}
