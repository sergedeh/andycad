// ParserVerb.cpp: implementation of the CParserVerb class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "cad.h"
#include "ParserVerb.h"
#include "chamfer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserVerb::~CParserVerb()
{

}


CParserVerb::CParserVerb(CString s)
{
   s.MakeLower();
   value = -1;
   type = VERB;
   /*if (s=="print") value = PRINT;
   if (s=="sortby") value = SORTBY;
   if (s=="gamma") value = GAMMA;
*/
}



CParserVerb* CParserVerb::getVerb(int s)
{
  /* if(value==PRINT)
   {
       // return new CPrint(s);
   }
   if(value==SORTBY)
   {
 //        return new CSort(s);
   }*/
   if(value==CHAMFER)
   {
	   CString ss;
	   ss.Format("%d", s);
         return new CChamfer(ss);
   }
   return NULL;
}

void CParserVerb::addArgs(CMultVar* mv)
{
 args = mv->getVector();
}

void CParserVerb::addArgs(CParserObject* p)
{
	args.push_back(p);
}

bool CParserVerb::isLegal()
{
	return (value >= 0);
}
