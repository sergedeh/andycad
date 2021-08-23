// cadDoc.cpp : implementation of the CCadDoc class
//

#include "Stdafx.h"
#include "cad.h"
#include "Draw.h"	// Added by ClassView
#include "cadview.h"
#include "cadDoc.h"
//#include "CADSrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCadDoc

IMPLEMENT_DYNCREATE(CCadDoc, CDocument)

BEGIN_MESSAGE_MAP(CCadDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	//{{AFX_MSG_MAP(CCadDoc)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CCadDoc, CDocument)
    //{{AFX_DISPATCH_MAP(CCadDoc)
	DISP_PROPERTY_EX(CCadDoc, "Window", GetWindow, SetWindow, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadDoc, "Canvas", GetCanvas, SetCanvas, VT_DISPATCH)
	DISP_PROPERTY_EX(CCadDoc, "Utils", GetUtils, SetUtils, VT_DISPATCH)
	DISP_FUNCTION(CCadDoc, "Quit", Quit, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
//AD3DA4F5-9353-44E5-BB40-D3CBA5B83F86
// {A3633A45-08E7-4000-867A-4004BCA57A1B}
static const IID IID_ICad =
{ 0xad3da4f5, 0x9353, 0x44e5, { 0xbb, 0x40, 0xd3, 0xcb, 0xa5, 0xb8, 0x3f, 0x86 } };

BEGIN_INTERFACE_MAP(CCadDoc, CDocument)
	INTERFACE_PART(CCadDoc, IID_ICad, Dispatch)
END_INTERFACE_MAP()

//IMPLEMENT_OLECREATE(CCadAutoWnd, "AndyCAD.Window", 0x343f6c50, 0x8f61, 0x4375, 0x9b, 0x4a, 0xa4, 0xd8, 0xb, 0xd3, 0xe3, 0xce)


/////////////////////////////////////////////////////////////////////////////
// CCadDoc construction/destruction
bool start=false;
CCadDoc::CCadDoc()
{
	m_objects=new CDraw;
	m_parser = new CParser;
	m_parserdxf=new CParserDxf;
	m_nMapMode = MM_LOENGLISH;
	m_paperColor = RGB(255, 255, 255);
	EnableAutomation();
	AfxOleLockApp();

//
//m_szText="This is just a test string";
//	m_nCaretIndex=0;
//	m_nSelIndexBgn=-1;
//	m_nSelIndexEnd=-1;
//	m_nSelIndexEndOld=-1;

//
}

CCadDoc::~CCadDoc()
{
	delete m_objects;
	AfxOleUnlockApp();
}

/////////////////////////////////////////////////////////////////////////////
// CCadDoc serialization

void CCadDoc::Serialize(CArchive& ar)
{

}

/////////////////////////////////////////////////////////////////////////////
// CCadDoc diagnostics

#ifdef _DEBUG
void CCadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCadDoc commands
BOOL CCadDoc::OnNewDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_objects->Init();
	delete m_parser;
	m_parser=new CParser;
 	CFrameWnd *pFrame = 
 				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	if(start)
	{
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
	pView->change=true;
	pView->Invalidate(TRUE);
	}
	start=true;
	return CDocument::OnNewDocument();
}




void CCadDoc::setcolor(COLORREF l, COLORREF b)
{

}

 void CCadDoc::OnFileImport() 
 {
 	CFrameWnd *pFrame = 
 				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
 
 	// Get the active view attached to the active MDI child
 	// window.
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
 
 
 	CFileDialog dllg(TRUE);
 	dllg.m_ofn.lpstrDefExt="aff";
 	dllg.m_ofn.lpstrFilter="AndyCad Files(*.aff)\0*.aff\0DXF Files(*.dxf)\0*.dxf\0DIB Files(*.BMP)\0*.BMP\0SVG Files(*.svg)\0*.svg\0";
 	dllg.m_ofn.nFilterIndex=1;
 
 	if(dllg.DoModal()==IDOK)
 	{
 
 		try
 		{
 			if(dllg.m_ofn.nFilterIndex==2)//(dllg.GetFileExt()=="svg")
 			{
			
 			CStdioFile file(dllg.GetPathName(),CFile::modeRead);
 			pView->import(dllg.m_ofn.nFilterIndex,file);
 			file.Close();
			}else
 			if(dllg.m_ofn.nFilterIndex==1)//(dllg.GetFileExt()=="svg")
 			{
			
 			CFile file(dllg.GetPathName(),CFile::modeRead);
 			pView->import(dllg.m_ofn.nFilterIndex,file);
 			file.Close();
			}

// 			fstr=dllg.GetPathName();
 //			exti=dllg.m_ofn.nFilterIndex;
 
 		}		
 		catch(CFileException * fx)
 		{
 			 TCHAR buf[255];
 			 fx->GetErrorMessage(buf, 255);
 			 CString strPrompt(buf);
 			 AfxMessageBox(strPrompt);
 		}
 
 	}
 }


/*void CCadDoc::OnFileSaveAs() 
{

	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();


	CFileDialog dllg(FALSE);
	dllg.m_ofn.lpstrDefExt="deh";
	dllg.m_ofn.lpstrFilter="AndyCad Files(*.deh)\0*.deh\0DIB Files(*.BMP)\0*.BMP\0SVG Files(*.svg)\0*.svg\0";
	dllg.m_ofn.nFilterIndex=1;

	if(dllg.DoModal()==IDOK)
	{

		try
		{
			CFile file(dllg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
 		
 			if(dllg.m_ofn.nFilterIndex==2)//(dllg.GetFileExt()=="svg")
 			{
 				dllg.m_ofn.lpstrDefExt="bmp";
 			}
 			else
 			if(dllg.m_ofn.nFilterIndex==3)//(dllg.GetFileExt()=="deh")
 			{
 				dllg.m_ofn.lpstrDefExt="svg";
 			}
 
			pView->Save(dllg.m_ofn.nFilterIndex,file);
			file.Close();
		
		}		
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}

	pView->libupdate();	
	
}
*/
 void CCadDoc::OnFileOpen() 
 {
 
 	CFrameWnd *pFrame = 
 				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;
 
 	// Get the active view attached to the active MDI child
 	// window.
 	CCadView *pView = (CCadView *) pFrame->GetActiveView();
 
 
 	CFileDialog dllg(TRUE);
 	dllg.m_ofn.lpstrDefExt="aff";
 	dllg.m_ofn.lpstrFilter="AndyCad Files(*.aff)\0*.aff\0DIB Files(*.BMP)\0*.BMP\0SVG Files(*.svg)\0*.svg\0";
 	dllg.m_ofn.nFilterIndex=1;
 
 	if(dllg.DoModal()==IDOK)
 	{
 
 		try
 		{
 			CFile file(dllg.GetPathName(),CFile::modeRead);
 			DeleteContents();
 			SetModifiedFlag();  // dirty during de-serialize
 			pView->Open(dllg.m_ofn.nFilterIndex,file);
 			file.Close();
 			fstr=dllg.GetPathName();
 			exti=dllg.m_ofn.nFilterIndex;
 
 		}		
 		catch(CFileException * fx)
 		{
 			 TCHAR buf[255];
 			 fx->GetErrorMessage(buf, 255);
 			 CString strPrompt(buf);
 			 AfxMessageBox(strPrompt);
 		}
 
 	}
 	SetModifiedFlag(FALSE); 
 	// TODO: Add your command handler code here
 	
 }





BOOL CCadDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here

	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	if(pFrame!=NULL)
	{
	CCadView *pView = (CCadView *) pFrame->GetActiveView();

	CFile file(lpszPathName,CFile::modeRead);
	exti=3;
	pView->Open(1,file);
	file.Close();
	}
	return TRUE;
}

/*
void CCadDoc::OnFileSave() 
{
	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();


	CFileDialog dllg(FALSE);
	dllg.m_ofn.lpstrDefExt="deh";
	dllg.m_ofn.lpstrFilter="AndyCad Files(*.deh)\0*.deh\0DIB Files(*.BMP)\0*.BMP\0SVG Files(*.svg)\0*.svg\0";
	dllg.m_ofn.nFilterIndex=1;


	if(fstr.IsEmpty())
	{
	if(dllg.DoModal()==IDOK)
	{

		try
		{
			CFile file(dllg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
 		
 			if(dllg.m_ofn.nFilterIndex==2)//(dllg.GetFileExt()=="svg")
 			{
 				dllg.m_ofn.lpstrDefExt="bmp";
 			}
 			else
 			if(dllg.m_ofn.nFilterIndex==3)//(dllg.GetFileExt()=="deh")
 			{
 				dllg.m_ofn.lpstrDefExt="svg";
 			}
 
			pView->Save(dllg.m_ofn.nFilterIndex,file);
			file.Close();
		
			fstr=dllg.GetPathName();
			exti=dllg.m_ofn.nFilterIndex;

		}		
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}
	}
	else
	{
		try
		{

			CFile file(fstr,CFile::modeCreate | CFile::modeWrite);
 			pView->Save(exti,file);
			file.Close();
		}		
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}
	pView->libupdate();	
}
*/
//DEL COleServerItem* CCadDoc::OnGetEmbeddedItem()
//DEL {
//DEL 	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
//DEL 	//  that is associated with the document.  It is only called when necessary.
//DEL 
//DEL 	CCADSrvrItem* pItem = new CCADSrvrItem(this);
//DEL 	ASSERT_VALID(pItem);
//DEL 	return pItem;
//DEL }

/////////////////////////////////////////////////////////////////////////////
// CMyCADAppDoc Active Document server implementation

/*CDocObjectServer *CCadDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}*/


BOOL CCadDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{

/*	CString newName = lpszPathName;
	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" #%;/\\"));
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			// append the default suffix if there is one
			CString strExt;
			if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
			  !strExt.IsEmpty())
			{
				ASSERT(strExt[0] == '.');
				newName += strExt;
			}
		}

		if (!AfxGetApp()->DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			return FALSE;       // don't even attempt to save
	}

	CWaitCursor wait;

	if (!OnSaveDocument(newName))
	{
		if (lpszPathName == NULL)
		{
			// be sure to delete the file
			TRY
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs.\n");
				DELETE_EXCEPTION(e);
			}
			END_CATCH_ALL
		}
		return FALSE;
	}

	// reset the title and change the document name
	if (bReplace)
		SetPathName(newName);

	return TRUE;        // success

*/



	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();


	CFileDialog dllg(FALSE);
	dllg.m_ofn.lpstrDefExt="aff";
	dllg.m_ofn.lpstrFilter="AndyCAD Pro 0.9(*.aff)\0*.aff\0AndyCAD Pro 0.91(*.aff)\0*.aff\0AndyCAD Pro 0.92(*.aff)\0*.aff\0DXF Format(*.dxf)\0*.dxf\0PNG Format(*.png)\0*.png\0JPEG Format(*.jpeg)\0*.jpeg\0";
	dllg.m_ofn.nFilterIndex=3;

	CString newName = lpszPathName;
	char result[MAX_PATH],dir[MAX_PATH];

	GetTempPath(MAX_PATH,dir);

	 /* Attempt to find a unique filename: */
	GetTempFileName(dir, // dir. for temp. files 
	"andyc",                // temp. filename prefix 
	0,                    // create unique name 
	result);          // buffer for name 


	if (newName.IsEmpty())
	{
		CDocTemplate* pTemplate = GetDocTemplate();
		ASSERT(pTemplate != NULL);

		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
			// check for dubious filename
			int iBad = newName.FindOneOf(_T(" #%;/\\"));
			if (iBad != -1)
				newName.ReleaseBuffer(iBad);

			// append the default suffix if there is one
			CString strExt;
			if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
			  !strExt.IsEmpty())
			{
				ASSERT(strExt[0] == '.');
				newName += strExt;
			}
		}


	if(dllg.DoModal()==IDOK)
	{

		try
		{
 		
 			if(dllg.m_ofn.nFilterIndex==5)//(dllg.GetFileExt()=="svg")
 			{
 				dllg.m_ofn.lpstrDefExt="png";
 			}
 			if(dllg.m_ofn.nFilterIndex==6)//(dllg.GetFileExt()=="svg")
 			{
 				dllg.m_ofn.lpstrDefExt="jpeg";
 			}
 			if(dllg.m_ofn.nFilterIndex==4)//(dllg.GetFileExt()=="deh")
 			{
 				dllg.m_ofn.lpstrDefExt="dxf";
				CStdioFile filo(dllg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
				pView->Save(dllg.m_ofn.nFilterIndex,filo);
 			}else
			{
			
			CFile filo(dllg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);
			pView->Save(dllg.m_ofn.nFilterIndex,filo);
			}
//			CFile file(dllg.GetPathName(),CFile::modeCreate| CFile::modeReadWrite );
		
//			DWORD length=filo.GetLength();
//			BYTE* b=new BYTE[length];
//			filo.SeekToBegin();
//			filo.Read(b,length);
//			filo.Close();
//			file.Write(b,length);
//			file.Remove(result);
//			file.Close();
//			delete b;
		
		
			fstr=dllg.GetPathName();
			exti=dllg.m_ofn.nFilterIndex;

		}		
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}
	}
	else
	{
		try
		{

			CFile filo(lpszPathName,CFile::modeCreate|CFile::modeReadWrite);
 			pView->Save(exti,filo);
/*			CFile file(lpszPathName,CFile::modeCreate|CFile::modeNoTruncate | CFile::modeReadWrite );

			DWORD length=filo.GetLength();
			BYTE* b=new BYTE[length];
			filo.SeekToBegin();
			filo.Read(b,length);
			filo.Close();
			file.Write(b,length);
			file.Remove(result);
			file.Close();
			delete b;*/
		}		
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}
	pView->libupdate();	
	
	if (bReplace)
		SetPathName(newName);
	::AfxMessageBox("File successfully saved");
	return TRUE;

}


void CCadDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
     SetModifiedFlag();
	CDocument::OnCloseDocument();
}

void CCadDoc::OnAppExit() 
{
	// TODO: Add your command handler code here
	 SetModifiedFlag();
	 CDocument::OnCloseDocument();
}


void CCadDoc::Quit() 
{
	// TODO: Add your dispatch handler code here
 AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
}

LPDISPATCH CCadDoc::GetWindow() 
{
	// TODO: Add your property handler here

	return auto_wnd.GetIDispatch(TRUE);
}

void CCadDoc::SetWindow(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();

}

LPDISPATCH CCadDoc::GetCanvas() 
{
	// TODO: Add your property handler here

	return auto_canvas.GetIDispatch(TRUE);
}

void CCadDoc::SetCanvas(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

LPDISPATCH CCadDoc::GetUtils() 
{
	// TODO: Add your property handler here

	return auto_utils.GetIDispatch(TRUE);
}

void CCadDoc::SetUtils(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here
	SetNotSupported();
}

