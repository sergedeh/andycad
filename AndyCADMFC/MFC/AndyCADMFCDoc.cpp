// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// AndyCADMFCDoc.cpp : implementation of the CAndyCADMFCDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AndyCADMFC.h"
#endif

#include "AndyCADMFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAndyCADMFCDoc

IMPLEMENT_DYNCREATE(CAndyCADMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CAndyCADMFCDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAndyCADMFCDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IAndyCADMFC to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {3b01f89c-d2ca-419c-a126-5836138a9b71}
static const IID IID_IAndyCADMFC =
{0x3b01f89c,0xd2ca,0x419c,{0xa1,0x26,0x58,0x36,0x13,0x8a,0x9b,0x71}};

BEGIN_INTERFACE_MAP(CAndyCADMFCDoc, CDocument)
	INTERFACE_PART(CAndyCADMFCDoc, IID_IAndyCADMFC, Dispatch)
END_INTERFACE_MAP()


// CAndyCADMFCDoc construction/destruction

CAndyCADMFCDoc::CAndyCADMFCDoc() noexcept
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CAndyCADMFCDoc::~CAndyCADMFCDoc()
{
	AfxOleUnlockApp();
}

BOOL CAndyCADMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAndyCADMFCDoc serialization

void CAndyCADMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CAndyCADMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CAndyCADMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAndyCADMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAndyCADMFCDoc diagnostics

#ifdef _DEBUG
void CAndyCADMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAndyCADMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAndyCADMFCDoc commands
