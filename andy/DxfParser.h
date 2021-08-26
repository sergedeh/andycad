// DxfParser.h: interface for the CDxfParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXFPARSER_H__7D83DE7A_E330_495E_8E2C_3FD8772B1F4E__INCLUDED_)
#define AFX_DXFPARSER_H__7D83DE7A_E330_495E_8E2C_3FD8772B1F4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <vector>
using namespace std;
class CDxfParser  
{
public:
	void _parse(string dxfString);
	void parseSync(string source);
	CDxfParser();
	virtual ~CDxfParser();

};
const int BLOCK_ANONYMOUS_FLAG = 1;
const int BLOCK_NON_CONSTANT_FLAG = 2;
const int BLOCK_XREF_FLAG = 4;
const int BLOCK_XREF_OVERLAY_FLAG = 8;
const int BLOCK_EXTERNALLY_DEPENDENT_FLAG = 16;
const int BLOCK_RESOLVED_OR_DEPENDENT_FLAG = 32;
const int BLOCK_REFERENCED_XREF = 64;

#endif // !defined(AFX_DXFPARSER_H__7D83DE7A_E330_495E_8E2C_3FD8772B1F4E__INCLUDED_)
