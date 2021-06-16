// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "AndyCADMFCHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CAndyCADMFCHandlersModule _AtlModule;

class CAndyCADMFCHandlersApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAndyCADMFCHandlersApp, CWinApp)
END_MESSAGE_MAP()

CAndyCADMFCHandlersApp theApp;

BOOL CAndyCADMFCHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, nullptr))
		return FALSE;
	return CWinApp::InitInstance();
}

int CAndyCADMFCHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
