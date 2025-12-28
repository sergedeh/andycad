// Parser.cpp: implementation of the CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "cadview.h"
#include "caddoc.h"
#include "andy_tab.h"
#include "andy.cc"
#include "andy_tab.cc"
#include "parsedlg.h"	// Added by ClassView


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParser::~CParser()
{

}

void CParser::execute(const CString &input, CString &output, CParseDlg* dlg)
{
	if(!dlg)
	{
	char* cin=(char*) malloc(input.GetLength() + 1); // +1 for null terminator
	strcpy(cin,input);
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
	pView = (CCadView *) pFrame->GetActiveView();
	pView->change=true;
	pDoc->m_objects->candraw=true;
	out=output;
	yy_scan_string(cin);
	yyparse();
	output+=input + "\r\n";

	if(!out.IsEmpty())
	{
		output+=out + "\r\n";
		this->ins= "Command: ";		
	}
	else if(!com.IsEmpty())
	{
		this->ins = com;
	}
	else
	{
		this->ins = "Command: ";
	}
	
	this->outs=output;
	free(cin);
	return;
	}else
	if(input!=dlg->com)
	{
	char* cin=(char*) malloc(input.GetLength() + 1); // +1 for null terminator
	strcpy(cin,input);
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
	pView = (CCadView *) pFrame->GetActiveView();
	pView->change=true;
	out=output;
	yy_scan_string(cin);
	yyparse();
	output+=input + "\r\n";
	dlg->com=com; // This line seems to be where dlg->com gets updated, so it should remain.
	
	if(!out.IsEmpty())
	{
		output+=out + "\r\n";
		this->ins = "Command: ";		
	}
	else if (!com.IsEmpty())
	{
		this->ins = com;
	}
	else
	{
		this->ins = "Command: ";
	}
	this->outs=output;
	free(cin);
	}
}void CParser::executeFile(CStdioFile &file,CString &output)
{
	DWORD tick=GetTickCount();

	yyin=file.m_pStream;
	yyparse();

	DWORD ptick=GetTickCount()-tick;
	CString s;
	s.Format("time spend to Load DXF:%d \n",ptick);
	TRACE(s);
	
	if(!out.IsEmpty())
	{
		output+=out + "\r\n";
	}
}

CParser::CParser()
{

}


CString CParser::getInput()
{
 return ins;
}

CString CParser::getOutput()
{
 return outs;
}
