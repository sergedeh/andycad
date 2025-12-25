// AndyCadAddin.h : Declaration of the CAndyCadAddin

#ifndef __ANDYCADADDIN_H_
#define __ANDYCADADDIN_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAndyCadAddin
class ATL_NO_VTABLE CAndyCadAddin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAndyCadAddin, &CLSID_AndyCadAddin>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAndyCadAddin>,
	public IDispatchImpl<IAndyCadAddin, &IID_IAndyCadAddin, &LIBID_CADADDINLib>
{
public:
	CAndyCadAddin()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ANDYCADADDIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAndyCadAddin)
	COM_INTERFACE_ENTRY(IAndyCadAddin)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CAndyCadAddin)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAndyCadAddin
public:
	STDMETHOD(Uninitialize)(long lSessionID);
	STDMETHOD(Initialize)(long lSessionID, IAndyCad *pApp, VARIANT bFirstTime);
};

#endif //__ANDYCADADDIN_H_
