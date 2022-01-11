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

// MFCAndyCADView.cpp : implementation of the CMFCAndyCADView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAndyCAD.h"
#endif

#include "MFCAndyCADDoc.h"
#include "MFCAndyCADView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAndyCADView

IMPLEMENT_DYNCREATE(CMFCAndyCADView, CView)

BEGIN_MESSAGE_MAP(CMFCAndyCADView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAndyCADView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCAndyCADView construction/destruction

CMFCAndyCADView::CMFCAndyCADView() noexcept
{
	// TODO: add construction code here

}

CMFCAndyCADView::~CMFCAndyCADView()
{
}

BOOL CMFCAndyCADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCAndyCADView drawing

void CMFCAndyCADView::OnDraw(CDC* /*pDC*/)
{
	CMFCAndyCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCAndyCADView printing


void CMFCAndyCADView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAndyCADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCAndyCADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCAndyCADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCAndyCADView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCAndyCADView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCAndyCADView diagnostics

#ifdef _DEBUG
void CMFCAndyCADView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAndyCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAndyCADDoc* CMFCAndyCADView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAndyCADDoc)));
	return (CMFCAndyCADDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAndyCADView message handlers
