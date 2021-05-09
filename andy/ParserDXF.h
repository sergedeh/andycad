// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERDXF_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_)
#define AFX_PARSERDXF_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//  using namespace boost;
  using namespace std;

class CParserDxf  
{
public:
	CParserDxf();
	void executeFile(CDC* hdc,CStdioFile &file,CString &output,bool _block=false);
	virtual ~CParserDxf();

};



#endif // !defined(AFX_PARSERDXF_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_)
