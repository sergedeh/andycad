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

// AndyCADMFCView.cpp : implementation of the CAndyCADMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AndyCADMFC.h"
#endif

#include "AndyCADMFCDoc.h"
#include "AndyCADMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAndyCADMFCView

IMPLEMENT_DYNCREATE(CAndyCADMFCView, CView)

BEGIN_MESSAGE_MAP(CAndyCADMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAndyCADMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CAndyCADMFCView construction/destruction

CAndyCADMFCView::CAndyCADMFCView() noexcept
{
	// TODO: add construction code here

}

CAndyCADMFCView::~CAndyCADMFCView()
{
}

BOOL CAndyCADMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAndyCADMFCView drawing

void CAndyCADMFCView::OnDraw(CDC* /*pDC*/)
{
	CAndyCADMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAndyCADMFCView printing


void CAndyCADMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAndyCADMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAndyCADMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAndyCADMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAndyCADMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAndyCADMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAndyCADMFCView diagnostics

#ifdef _DEBUG
void CAndyCADMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CAndyCADMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAndyCADMFCDoc* CAndyCADMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAndyCADMFCDoc)));
	return (CAndyCADMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CAndyCADMFCView message handlers
