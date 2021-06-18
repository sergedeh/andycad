// dllmain.h : Declaration of module class.

class CAndyCADMFCHandlersModule : public ATL::CAtlDllModuleT<CAndyCADMFCHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_AndyCADMFCHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ANDYCADMFCHANDLERS, "{a292a402-cd49-4b3c-b8df-3a7580037c4b}")
};

extern class CAndyCADMFCHandlersModule _AtlModule;
