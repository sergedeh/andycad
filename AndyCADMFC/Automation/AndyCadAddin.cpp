// AndyCadAddin.cpp : Implementation of CAndyCadAddin
#include "stdafx.h"
#include "CadAddIn.h"
#include "AndyCadAddin.h"

/////////////////////////////////////////////////////////////////////////////
// CAndyCadAddin

STDMETHODIMP CAndyCadAddin::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAndyCadAddin
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAndyCadAddin::Initialize(long lSessionID, IAndyCad *pApp, VARIANT bFirstTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAndyCadAddin::Uninitialize(long lSessionID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}
