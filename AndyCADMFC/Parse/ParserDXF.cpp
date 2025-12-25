// Parser.cpp: implementation of the CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cad.h"
#include "Parserdxf.h"
#include "cadview.h"
#include "caddoc.h"
//#include "dxftab.h"
#include "dxf_tab.h"
#include "dxf.c"
#include "dxf_tab.c"
//#include "dxf.cc"
//#include "dxf.tab.cpp"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CParserDxf::~CParserDxf()
{

}
CParserDxf::CParserDxf()
{

}

void CParserDxf::executeFile(CDC* hdc,CStdioFile &file,CString &output,bool _block)
{
	dxfin=file.m_pStream;
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd ();
	dxfpDoc = (CCadDoc*) pFrame->GetActiveDocument ();
	dxfpView = (CCadView *) pFrame->GetActiveView();
	dxfpView->change=true;
	dxfHdc=hdc;
	dxfBlock=_block;

	DWORD tick=GetTickCount();

	dxfparse();

	DWORD ptick=GetTickCount()-tick;
	CString s;
	s.Format("time spend to Parse DXF:%d \n",ptick);
	TRACE(s);

	dxfpView->Invalidate(TRUE);
	YY_FLUSH_BUFFER;
	if(!_out.IsEmpty())
	{
		output+=_out + "\r\n";
	}
}
