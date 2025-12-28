

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for MFCAndyCAD.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __MFCAndyCAD_h_h__
#define __MFCAndyCAD_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IMFCAndyCAD_FWD_DEFINED__
#define __IMFCAndyCAD_FWD_DEFINED__
typedef interface IMFCAndyCAD IMFCAndyCAD;

#endif 	/* __IMFCAndyCAD_FWD_DEFINED__ */


#ifndef __CMFCAndyCADDoc_FWD_DEFINED__
#define __CMFCAndyCADDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMFCAndyCADDoc CMFCAndyCADDoc;
#else
typedef struct CMFCAndyCADDoc CMFCAndyCADDoc;
#endif /* __cplusplus */

#endif 	/* __CMFCAndyCADDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFCAndyCAD_LIBRARY_DEFINED__
#define __MFCAndyCAD_LIBRARY_DEFINED__

/* library MFCAndyCAD */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFCAndyCAD;

#ifndef __IMFCAndyCAD_DISPINTERFACE_DEFINED__
#define __IMFCAndyCAD_DISPINTERFACE_DEFINED__

/* dispinterface IMFCAndyCAD */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFCAndyCAD;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("d46c6b20-2a8f-4cf2-9ac3-66e0dce12882")
    IMFCAndyCAD : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFCAndyCADVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFCAndyCAD * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFCAndyCAD * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFCAndyCAD * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFCAndyCAD * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFCAndyCAD * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFCAndyCAD * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFCAndyCAD * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMFCAndyCADVtbl;

    interface IMFCAndyCAD
    {
        CONST_VTBL struct IMFCAndyCADVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFCAndyCAD_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFCAndyCAD_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFCAndyCAD_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFCAndyCAD_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFCAndyCAD_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFCAndyCAD_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFCAndyCAD_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFCAndyCAD_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMFCAndyCADDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("4720d6b6-b0a2-4cae-985d-f04b5e3d94cd")
CMFCAndyCADDoc;
#endif
#endif /* __MFCAndyCAD_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


