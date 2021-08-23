// AndyCad.h : Declaration of the CAndyCad

#ifndef __ANDYCAD_H_
#define __ANDYCAD_H_

#include "resource.h"       // main symbols
#include "CadAddInCP.h"



#import "msxml.dll" named_guids raw_interfaces_only
using namespace MSXML;

/////////////////////////////////////////////////////////////////////////////
// CAndyCad
class ATL_NO_VTABLE CAndyCad : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAndyCad, &CLSID_AndyCad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAndyCad>,
	public CProxy_IAndyCadEvents< CAndyCad >,
	public IDispatchImpl<IAndyCad, &IID_IAndyCad, &LIBID_CADADDINLib>
{
public:
	CAndyCad()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ANDYCAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAndyCad)
	COM_INTERFACE_ENTRY(IAndyCad)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CAndyCad)
CONNECTION_POINT_ENTRY(DIID__IAndyCadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAndyCad
public:
	STDMETHOD(SetViewHeading)(BSTR strHeading1, BSTR strHeading2,BSTR strHeading3);
	STDMETHOD(SetAddinToolbar)(long lAddinIndex, VARIANT varValue);
	STDMETHOD(SetAddInInfo)(long lSessionID, long lInstanceHandle, BSTR strXMLMenuToolbarIDCmdInfo, long lToobarRes);
	STDMETHOD(SendStatus)(BSTR strStatus);
	STDMETHOD(get_MainWindow)(/*[out, retval]*/ long *pVal);
	STDMETHOD(LoadAllAdins)(BSTR strAddinLoadingInfo);
	BOOL GetAllCommandsInfo(CAddinInfo& AddinInfo, IXMLDOMNodeList* pXMLDOMNodeList);
	BOOL ParseAndLoadCommandInfo(BSTR strXMLCommand, CAddinInfo& AddinInfo);

};

#endif //__ANDYCAD_H_
