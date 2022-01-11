// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "MFCAndyCADHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CMFCAndyCADHandlersModule _AtlModule;

class CMFCAndyCADHandlersApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMFCAndyCADHandlersApp, CWinApp)
END_MESSAGE_MAP()

CMFCAndyCADHandlersApp theApp;

BOOL CMFCAndyCADHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CMFCAndyCADHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
