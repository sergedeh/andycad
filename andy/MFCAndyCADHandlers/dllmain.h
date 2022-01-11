// dllmain.h : Declaration of module class.

class CMFCAndyCADHandlersModule : public ATL::CAtlDllModuleT<CMFCAndyCADHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_MFCAndyCADHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MFCANDYCADHANDLERS, "{a1d8b411-65a8-4aa5-b13b-4f54ff47d9f7}")
};

extern class CMFCAndyCADHandlersModule _AtlModule;
