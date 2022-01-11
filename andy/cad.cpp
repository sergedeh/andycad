// cad.cpp : Defines the class behaviors for the application.
//

#include "Stdafx.h"
#include "cad.h"
#include "regdialog.h"
#include "MainFrm.h"
#include "cadDoc.h"
#include "cadView.h"
#include "splash.h"
#include <locale.h>
#include <dos.h>
#include <direct.h>
#include <initguid.h>

#include "cadaddin_i.c"
//#include "andycad.h"
//#include "AndyCadAddin.h"
//#include "FrameworkAddin1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCadApp
IMPLEMENT_DYNCREATE(CCadApp, CWinApp)

//CAddinManager CCadApp::m_AddinManager;

BEGIN_MESSAGE_MAP(CCadApp, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	//{{AFX_MSG_MAP(CCadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
//	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCadApp construction

CCadApp::CCadApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one a1nd only CCadApp object

CCadApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {E8559014-9D11-4C7B-B17A-1C966E9A13DA}
static const CLSID clsid =
{ 0xe8559014, 0x9d11, 0x4c7b, { 0xb1, 0x7a, 0x1c, 0x96, 0x6e, 0x9a, 0x13, 0xda } };

/////////////////////////////////////////////////////////////////////////////
// CCadApp initialization

BOOL CCadApp::InitInstance()
{


	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("AnddyCAD"));

	


	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	CRegDialog RegistrationDialog;

//	RegistrationDialog.Check();
	{
		//Set up date and time defaults so they're the same as system defaults
		setlocale(LC_ALL, "");
	}



	{

		CCommandLineInfo cmdInfo;

		ParseCommandLine(cmdInfo);

//    _Module.UpdateRegistryFromResource(IDR_CAD1, TRUE);
//	_Module.RegisterServer(TRUE);


		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	if (!InitATL()) 
		return FALSE;

	AfxEnableControlContainer();
	EnableAutomation();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCadView));
//	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);
	RegisterShellFileTypes();

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);

	// Enable DDE Execute open
	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);	
	
	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
//	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
//		REGCLS_MULTIPLEUSE);


		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}	
	COleObjectFactory::UpdateRegistryAll();

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);

	// Dispatch commands specified on the command line
//	cmdInfo.m_nShellCommand=CCommandLineInfo::FileOpen;
//	cmdInfo.m_strFileName="12.deh";

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	((CMainFrame*)m_pMainWnd)->LoadAditionalAccelerators();

	
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	if(cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen)
	{
	CFrameWnd *pFrame = 
				 (CFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active view attached to the active MDI child
	// window.
	CCadView *pView = (CCadView *) pFrame->GetActiveView();


	CFile file(cmdInfo.m_strFileName,CFile::modeRead);
	pView->Open(1,file);
	file.Close();
	}
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();


		// CG: This line inserted by 'Tip of the Day' component.
	ShowTipAtStartup();

	// CG: This block was added by the MAPI component
	{
		// TODO: Add a menu item for sending mail:
		//   1. In ResourceView, open your application's menu resource
		//   2. Select the File submenu
		//   3. Double-click on the blank item at the bottom of the submenu
		//   4. Assign the new item an ID: ID_FILE_SEND_MAIL
		//   5. Assign the item a Caption: Sen&d...

		// TODO: Delete this entire block of code.
		// The code below is only for temporary use, until the above
		// instructions have been carried out. This code will not work
		// correctly if your application has multiple menus or is an
		// MDI application and starts up maximized.

		CMenu* pMenu = NULL;
		CMenu* pFileMenu = NULL;
		if ((m_pMainWnd != NULL) &&
			((pMenu = m_pMainWnd->GetMenu()) != NULL) &&
			((pFileMenu = pMenu->GetSubMenu(0)) != NULL))
		{
			// Locate the "Sen&d..." menu item
			int i, nLength;
			for (i = 0, nLength = pFileMenu->GetMenuItemCount();
				i<nLength; i++)
			{
				CString strSend;
				pFileMenu->GetMenuString(i, strSend, MF_BYPOSITION);
				if (strSend == _T("Sen&d...")) break;
			}

			if (i == nLength)
			{
				// Didn't find Sen&d... menu item, so add one.
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION);
				pFileMenu->InsertMenu(nLength-1, MF_BYPOSITION,
				ID_FILE_SEND_MAIL, _T("Sen&d..."));
			}
		}
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

    class CAboutDlg : public CDialog
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
BOOL CCadApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

void CCadApp::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}

}

void CCadApp::ShowTipOfTheDay(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CTipDlg dlg;
	dlg.DoModal();

}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	// CG:  This was added by System Info Component.

	// CG: Following block was added by System Info Component.
	{
		CString strFreeDiskSpace;
		CString strFreeMemory;
		CString strFmt;

		// Fill available memory
		MEMORYSTATUS MemStat;
		MemStat.dwLength = sizeof(MEMORYSTATUS);
		GlobalMemoryStatus(&MemStat);
		strFmt.LoadString(CG_IDS_PHYSICAL_MEM);
		strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

		//TODO: Add a static control to your About Box to receive the memory
		//      information.  Initialize the control with code like this:
		// SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory);

		// Fill disk free information
		struct _diskfree_t diskfree;
		int nDrive = _getdrive(); // use current default drive
		if (_getdiskfree(nDrive, &diskfree) == 0)
		{
			strFmt.LoadString(CG_IDS_DISK_SPACE);
			strFreeDiskSpace.Format(strFmt,
				(DWORD)diskfree.avail_clusters *
				(DWORD)diskfree.sectors_per_cluster *
				(DWORD)diskfree.bytes_per_sector / (DWORD)1024L,
				nDrive-1 + _T('A'));
		}
		else
			strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);

		//TODO: Add a static control to your About Box to receive the memory
		//      information.  Initialize the control with code like this:
		// SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);
	}

	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), "<text>");
	}
	return TRUE;	// CG:  This was added by System Info Component.

}



BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

CCadModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_AndyCad, CAndyCad)
//OBJECT_ENTRY(CLSID_AndyCadAddin, CAndyCadAddin)
END_OBJECT_MAP()

LONG CCadModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CCadModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CCadModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}


int CCadApp::ExitInstance()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
		CoUninitialize();
	}
	
	return CWinApp::ExitInstance();

}

BOOL CCadApp::InitATL()
{
	m_bATLInited = TRUE;
/*	
#if _WIN32_WINNT >= 0x0400
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else*/
	HRESULT hRes = CoInitialize(NULL);
//#endif

	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");

	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_CAD1, FALSE);
			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_CAD1, TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if (!bRun)
	{
		m_bATLInited = FALSE;
		_Module.Term();
		CoUninitialize();
		return FALSE;
	}

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		CoUninitialize();
		return FALSE;
	}	

	return TRUE;

}

void CCadApp::OnNotifyStatus(LPTSTR strStatus)
{
	//Please do the processing here
	//Should be call only after the window creation
//	((CMainFrame*)m_pMainWnd)->SetStatusText(strStatus);   

}

