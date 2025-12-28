// Texts.cpp : implementation file
//

#include "stdafx.h"
#include "cad.h"
#include "Texts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTexts

CTexts::CTexts()
{
}

CTexts::~CTexts()
{
}


BEGIN_MESSAGE_MAP(CTexts, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTexts)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTexts message handlers

int CTexts::DrawText( )
{
	CDC dc;
	CString str;
	CRect Rec;

  return 1;
}
