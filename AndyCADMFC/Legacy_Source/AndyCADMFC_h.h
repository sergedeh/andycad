

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for AndyCADMFC.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
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


#ifndef __AndyCADMFC_h_h__
#define __AndyCADMFC_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAndyCADMFC_FWD_DEFINED__
#define __IAndyCADMFC_FWD_DEFINED__
typedef interface IAndyCADMFC IAndyCADMFC;

#endif 	/* __IAndyCADMFC_FWD_DEFINED__ */


#ifndef __CAndyCADMFCDoc_FWD_DEFINED__
#define __CAndyCADMFCDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAndyCADMFCDoc CAndyCADMFCDoc;
#else
typedef struct CAndyCADMFCDoc CAndyCADMFCDoc;
#endif /* __cplusplus */

#endif 	/* __CAndyCADMFCDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __AndyCADMFC_LIBRARY_DEFINED__
#define __AndyCADMFC_LIBRARY_DEFINED__

/* library AndyCADMFC */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AndyCADMFC;

#ifndef __IAndyCADMFC_DISPINTERFACE_DEFINED__
#define __IAndyCADMFC_DISPINTERFACE_DEFINED__

/* dispinterface IAndyCADMFC */
/* [uuid] */ 


EXTERN_C const IID DIID_IAndyCADMFC;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3b01f89c-d2ca-419c-a126-5836138a9b71")
    IAndyCADMFC : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAndyCADMFCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAndyCADMFC * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAndyCADMFC * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAndyCADMFC * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAndyCADMFC * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAndyCADMFC * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAndyCADMFC * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAndyCADMFC * This,
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
    } IAndyCADMFCVtbl;

    interface IAndyCADMFC
    {
        CONST_VTBL struct IAndyCADMFCVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAndyCADMFC_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAndyCADMFC_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAndyCADMFC_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAndyCADMFC_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAndyCADMFC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAndyCADMFC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAndyCADMFC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAndyCADMFC_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAndyCADMFCDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("1c9a84ac-1cb5-4fdb-8d8d-a790eaa9d743")
CAndyCADMFCDoc;
#endif
#endif /* __AndyCADMFC_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


