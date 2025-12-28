// Parser.h: interface for the CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_)
#define AFX_PARSER_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Command.h"
#include "ParserObject.h"	// Added by ClassView
#include "ParserVerb.h"	// Added by ClassView
#include "ParserVar.h"	// Added by ClassView
#include "Parserfloat.h"	// Added by ClassView
#include "figure.h"	// Added by ClassView
#include <stack>	// Added by ClassView
#include <string>
//#include "boost/tokenizer.hpp"

//  using namespace boost;
  using namespace std;

class CParseDlg;
class CParser : public CCommand, public CSubject  
{
public:
	CString getOutput();
	CString getInput();
	CParser();
	void execute(const CString& input, CString &output, CParseDlg* dlg);
	void executeFile(CStdioFile &file,CString &output);
	virtual ~CParser();

	protected:
   stack<CParserObject*> stk;
   vector<CParserObject*> actionList;
   CFigure* figure;

private:
	CString ins,outs;
};



#endif // !defined(AFX_PARSER_H__B6597C15_6F9F_4687_859C_A6FA89F6F15C__INCLUDED_)
