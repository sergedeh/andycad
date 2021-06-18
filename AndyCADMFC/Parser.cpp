// Parser.cpp: implementation of the CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Parser.h"
#include "ParserVar.h"
#include "Verb.h"
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

void CParser::Execute()
{
//	stack<CParseObject*>::iterator t=stk;
    while(!stk.empty())
    {
     
	if(topStack(CParserObject::FLOAT, CParserObject::VAR))
     {
       //reduce (Var Var) to Multvar
       addArgsToValue();
	}else
	if(topStack(CParserObject::VAR, CParserObject::VAR))
     {
       //reduce (Var Var) to Multvar
       CParserVar* v = (CParserVar*)stk.top();stk.pop();
       CParserVar* v1 = (CParserVar*)stk.top();stk.pop();
       CMultVar* mv = new CMultVar(v1, v);
       stk.push(mv);
     }else
     //reduce MULTVAR VAR to MULTVAR
	if(topStack(CParserObject::MULTVAR, CParserObject::VAR))
    {
       CMultVar* mv =  new CMultVar();
       CMultVar* mvo = (CMultVar*)stk.top();stk.pop();
       CParserVar* v = (CParserVar*)stk.top();stk.pop();
       mv->add(v);
       vector<CParserObject*> mvec = mvo->getVector();
       for (int i = 0; i< mvec.size(); i++)
          mv->add((CParserVar*)mvec[i]);
       stk.push(mv);
    }else
	if(topStack(CParserObject::VAR, CParserObject::MULTVAR))
    {
     //reduce (Multvar Var) to Multvar
        CParserVar* v = (CParserVar*)stk.top();stk.pop();
        CMultVar* mv = (CMultVar*)stk.top();stk.pop();
        mv->add(v);
        stk.push(mv);
    }else
     //reduce Verb Var to Verb containing vars
	if (topStack(CParserObject::VAR, CParserObject::VERB)) 
    {
        addArgsToVerb();
    }else
     //reduce Verb MultVar to Verb containing vars
    if (topStack(CParserObject::MULTVAR, CParserObject::VERB)) 
    {
       addArgsToVerb();
    }else
    if (topStack(CParserObject::FLOAT, CParserObject::VERB)) 
    {
       addArgsToVerb();
    }
     //move top verb to action list
    if(stk.top()->getType() == CParserObject::VERB)
    {
          actionList.push_back(stk.top());stk.pop();
    }
     
    }//while
    //now execute the verbs
    //data.setData(kdata.getData());
    //for (int i = actionList.size() -1; i >= 0; i--)
    for (int i =0; i< actionList.size() ; i++)
    {
      CVerb* v = (CVerb*)actionList[i];
      v->setData(figure);
      v->Execute();
    }

}

void CParser::addArgsToVerb()
{
		CParserObject* v = stk.top();stk.pop();
        CParserVerb* verb = (CParserVerb*)stk.top();stk.pop();
        verb->addArgs(v);
        stk.push(verb);
}
void CParser::addArgsToValue()
{
		CParserObject* v = stk.top();stk.pop();
        CParserVar* var = (CParserVar*)stk.top();stk.pop();
        var->addArgs(v);
        stk.push(var);
}

bool CParser::topStack(int c1, int c2)
{
	if(stk.size()>1)
	{
	CParserObject* t=stk.top();stk.pop();
	CParserObject* t1=stk.top();
	stk.push(t);
	return (t->getType() == c1) && (t1->getType()== c2);
	}
	return false;

}

CParserObject* CParser::tokenize(string s)
{
	   CParserObject* obj = getVerb(s);
         if (obj == NULL)
		 {
            obj = getVar(s);
		 }
         if (obj == NULL)
		 {
            obj = getFloat(s);
		 }
         return obj;
}

CParserVerb* CParser::getVerb(string s)
{
	   CParserVerb* v;
         v = new CParserVerb(s.c_str());
         if (v->isLegal()) 
            return v->getVerb(atoi(s.c_str()));
        else
            return NULL;

}

CParserVar* CParser::getVar(string s)
{
		CParserVar* v;
         v = new CParserVar(s.c_str());
         if (v->isLegal()) 
            return v;
         else
            return NULL;
}
CParserFloat* CParser::getFloat(string s)
{
		CParserFloat* v;
         v = new CParserFloat(s.c_str());
         if (v->isLegal()) 
            return v;
         else
            return NULL;
}

void CParser::execute(CString &input, CString &output, CParseDlg* dlg)
{
	if(!dlg)
	{
	char* cin=(char*) malloc(input.GetLength());
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
	input=com;
	
	if(!out.IsEmpty())
	{
		output+=out + "\r\n";
		input= "Command: ";		
	}
	if(input.IsEmpty())
		input= "Command: ";	
	

	ins=input;
	outs=output;
	return;
	}else
	if(input!=dlg->com)
	{
	char* cin=(char*) malloc(input.GetLength());
	strcpy(cin,input);
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	pDoc = (CCadDoc*) pFrame->GetActiveDocument ();
	pView = (CCadView *) pFrame->GetActiveView();
	pView->change=true;
	out=output;
	yy_scan_string(cin);
	yyparse();
	output+=input + "\r\n";
	input=com;
	dlg->com=com;
	
	if(!out.IsEmpty())
	{
		output+=out + "\r\n";
		input= "Command: ";		
	}
	if(input.IsEmpty())
		input= "Command: ";	
	

	ins=input;
	outs=output;
	}
	void* pp[2];
	pp[0]=&input;
	pp[1]=&output;

	for(vector<CObserver*>::iterator it=observers.begin();it!=observers.end();it++)
	{
	(*it)->SendNotify("Parser",pp);
	}

}
void CParser::executeFile(CStdioFile &file,CString &output)
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
