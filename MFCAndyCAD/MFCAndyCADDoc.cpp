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

// MFCAndyCADDoc.cpp : implementation of the CMFCAndyCADDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAndyCAD.h"
#endif

#include "MFCAndyCADDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCAndyCADDoc

IMPLEMENT_DYNCREATE(CMFCAndyCADDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCAndyCADDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCAndyCADDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IMFCAndyCAD to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {d46c6b20-2a8f-4cf2-9ac3-66e0dce12882}
static const IID IID_IMFCAndyCAD =
{0xd46c6b20,0x2a8f,0x4cf2,{0x9a,0xc3,0x66,0xe0,0xdc,0xe1,0x28,0x82}};

BEGIN_INTERFACE_MAP(CMFCAndyCADDoc, CDocument)
	INTERFACE_PART(CMFCAndyCADDoc, IID_IMFCAndyCAD, Dispatch)
END_INTERFACE_MAP()


// CMFCAndyCADDoc construction/destruction

CMFCAndyCADDoc::CMFCAndyCADDoc() noexcept
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CMFCAndyCADDoc::~CMFCAndyCADDoc()
{
	AfxOleUnlockApp();
}

BOOL CMFCAndyCADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCAndyCADDoc serialization

void CMFCAndyCADDoc::Serialize(CArchive& ar)
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
void CMFCAndyCADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCAndyCADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCAndyCADDoc::SetSearchContent(const CString& value)
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

// CMFCAndyCADDoc diagnostics

#ifdef _DEBUG
void CMFCAndyCADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCAndyCADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCAndyCADDoc commands
