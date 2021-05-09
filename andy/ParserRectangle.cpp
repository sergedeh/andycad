// ParserRectangle.cpp: implementation of the CParserRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "ParserRectangle.h"
#include "Parserfloat.h"
#include "typeinfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserRectangle::CParserRectangle(CString s):CVerb(s)
{
 value = RECTANGLE;
}

CParserRectangle::~CParserRectangle()
{

}

void CParserRectangle::Execute()
{

	 for (int j = 0; j < args.size(); j++)
      {
         
         CParserFloat* v = (CParserFloat*)args[j];
         if(typeid(v)==typeid(CMultVar))
         {  
            CMultVar* mv = (CMultVar*)v;
            vector<CParserObject*> vlist = mv->getVector();
            for(int k=0; k < vlist.size(); k++)
            {
            CParserVar* pv = (CParserVar*)vlist[k];
            }
         }
         else
         {
//			 figure->rectangle(v->getValue());
         }
      }

}
