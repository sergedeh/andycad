

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for CadAddIn.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CadAddIn_h_h__
#define __CadAddIn_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAndyCad_FWD_DEFINED__
#define __IAndyCad_FWD_DEFINED__
typedef interface IAndyCad IAndyCad;

#endif 	/* __IAndyCad_FWD_DEFINED__ */


#ifndef ___IAndyCadEvents_FWD_DEFINED__
#define ___IAndyCadEvents_FWD_DEFINED__
typedef interface _IAndyCadEvents _IAndyCadEvents;

#endif 	/* ___IAndyCadEvents_FWD_DEFINED__ */


#ifndef __IAndyCadAddin_FWD_DEFINED__
#define __IAndyCadAddin_FWD_DEFINED__
typedef interface IAndyCadAddin IAndyCadAddin;

#endif 	/* __IAndyCadAddin_FWD_DEFINED__ */


#ifndef __AndyCad_FWD_DEFINED__
#define __AndyCad_FWD_DEFINED__

#ifdef __cplusplus
typedef class AndyCad AndyCad;
#else
typedef struct AndyCad AndyCad;
#endif /* __cplusplus */

#endif 	/* __AndyCad_FWD_DEFINED__ */


#ifndef ___IAndyCadAddinEvents_FWD_DEFINED__
#define ___IAndyCadAddinEvents_FWD_DEFINED__
typedef interface _IAndyCadAddinEvents _IAndyCadAddinEvents;

#endif 	/* ___IAndyCadAddinEvents_FWD_DEFINED__ */


#ifndef __AndyCadAddin_FWD_DEFINED__
#define __AndyCadAddin_FWD_DEFINED__

#ifdef __cplusplus
typedef class AndyCadAddin AndyCadAddin;
#else
typedef struct AndyCadAddin AndyCadAddin;
#endif /* __cplusplus */

#endif 	/* __AndyCadAddin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAndyCad_INTERFACE_DEFINED__
#define __IAndyCad_INTERFACE_DEFINED__

/* interface IAndyCad */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAndyCad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A7F1349-F18E-43D0-BD22-774DB132B966")
    IAndyCad : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadAllAdins( 
            BSTR strAddinLoadingInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MainWindow( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendStatus( 
            BSTR strStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAddInInfo( 
            long lSessionID,
            long lInstanceHandle,
            BSTR strXMLMenuToolbarIDCmdInfo,
            long lToobarRes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAddinToolbar( 
            long lAddinIndex,
            VARIANT varValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetViewHeading( 
            BSTR strHeading1,
            BSTR strHeading2,
            BSTR strHeading3) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAndyCadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAndyCad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAndyCad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAndyCad * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAndyCad * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAndyCad * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAndyCad * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAndyCad * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadAllAdins )( 
            IAndyCad * This,
            BSTR strAddinLoadingInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainWindow )( 
            IAndyCad * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendStatus )( 
            IAndyCad * This,
            BSTR strStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAddInInfo )( 
            IAndyCad * This,
            long lSessionID,
            long lInstanceHandle,
            BSTR strXMLMenuToolbarIDCmdInfo,
            long lToobarRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAddinToolbar )( 
            IAndyCad * This,
            long lAddinIndex,
            VARIANT varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetViewHeading )( 
            IAndyCad * This,
            BSTR strHeading1,
            BSTR strHeading2,
            BSTR strHeading3);
        
        END_INTERFACE
    } IAndyCadVtbl;

    interface IAndyCad
    {
        CONST_VTBL struct IAndyCadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAndyCad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAndyCad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAndyCad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAndyCad_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAndyCad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAndyCad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAndyCad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAndyCad_LoadAllAdins(This,strAddinLoadingInfo)	\
    ( (This)->lpVtbl -> LoadAllAdins(This,strAddinLoadingInfo) ) 

#define IAndyCad_get_MainWindow(This,pVal)	\
    ( (This)->lpVtbl -> get_MainWindow(This,pVal) ) 

#define IAndyCad_SendStatus(This,strStatus)	\
    ( (This)->lpVtbl -> SendStatus(This,strStatus) ) 

#define IAndyCad_SetAddInInfo(This,lSessionID,lInstanceHandle,strXMLMenuToolbarIDCmdInfo,lToobarRes)	\
    ( (This)->lpVtbl -> SetAddInInfo(This,lSessionID,lInstanceHandle,strXMLMenuToolbarIDCmdInfo,lToobarRes) ) 

#define IAndyCad_SetAddinToolbar(This,lAddinIndex,varValue)	\
    ( (This)->lpVtbl -> SetAddinToolbar(This,lAddinIndex,varValue) ) 

#define IAndyCad_SetViewHeading(This,strHeading1,strHeading2,strHeading3)	\
    ( (This)->lpVtbl -> SetViewHeading(This,strHeading1,strHeading2,strHeading3) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAndyCad_INTERFACE_DEFINED__ */



#ifndef __CADADDINLib_LIBRARY_DEFINED__
#define __CADADDINLib_LIBRARY_DEFINED__

/* library CADADDINLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CADADDINLib;

#ifndef ___IAndyCadEvents_DISPINTERFACE_DEFINED__
#define ___IAndyCadEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAndyCadEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAndyCadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("53D2ED37-09C2-437D-8DED-1D4D70C47D28")
    _IAndyCadEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAndyCadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAndyCadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAndyCadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAndyCadEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAndyCadEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAndyCadEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAndyCadEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAndyCadEvents * This,
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
    } _IAndyCadEventsVtbl;

    interface _IAndyCadEvents
    {
        CONST_VTBL struct _IAndyCadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAndyCadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAndyCadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAndyCadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAndyCadEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAndyCadEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAndyCadEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAndyCadEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAndyCadEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IAndyCadAddin_INTERFACE_DEFINED__
#define __IAndyCadAddin_INTERFACE_DEFINED__

/* interface IAndyCadAddin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAndyCadAddin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A29432CA-CD10-412D-BA94-40EF2D528921")
    IAndyCadAddin : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            long lSessionID,
            IAndyCad *pApp,
            VARIANT bFirstTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uninitialize( 
            long lSessionID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAndyCadAddinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAndyCadAddin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAndyCadAddin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAndyCadAddin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAndyCadAddin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAndyCadAddin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAndyCadAddin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAndyCadAddin * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IAndyCadAddin * This,
            long lSessionID,
            IAndyCad *pApp,
            VARIANT bFirstTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Uninitialize )( 
            IAndyCadAddin * This,
            long lSessionID);
        
        END_INTERFACE
    } IAndyCadAddinVtbl;

    interface IAndyCadAddin
    {
        CONST_VTBL struct IAndyCadAddinVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAndyCadAddin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAndyCadAddin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAndyCadAddin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAndyCadAddin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAndyCadAddin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAndyCadAddin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAndyCadAddin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAndyCadAddin_Initialize(This,lSessionID,pApp,bFirstTime)	\
    ( (This)->lpVtbl -> Initialize(This,lSessionID,pApp,bFirstTime) ) 

#define IAndyCadAddin_Uninitialize(This,lSessionID)	\
    ( (This)->lpVtbl -> Uninitialize(This,lSessionID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAndyCadAddin_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AndyCad;

#ifdef __cplusplus

class DECLSPEC_UUID("243E5A7B-E5AD-4337-9C3F-44E27D554E24")
AndyCad;
#endif

#ifndef ___IAndyCadAddinEvents_DISPINTERFACE_DEFINED__
#define ___IAndyCadAddinEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAndyCadAddinEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAndyCadAddinEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6D929F85-25BA-475D-BB9F-9F12D2F699D3")
    _IAndyCadAddinEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAndyCadAddinEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAndyCadAddinEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAndyCadAddinEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAndyCadAddinEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAndyCadAddinEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAndyCadAddinEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAndyCadAddinEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAndyCadAddinEvents * This,
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
    } _IAndyCadAddinEventsVtbl;

    interface _IAndyCadAddinEvents
    {
        CONST_VTBL struct _IAndyCadAddinEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAndyCadAddinEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IAndyCadAddinEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IAndyCadAddinEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IAndyCadAddinEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IAndyCadAddinEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IAndyCadAddinEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IAndyCadAddinEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAndyCadAddinEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AndyCadAddin;

#ifdef __cplusplus

class DECLSPEC_UUID("B34E1702-B70A-48EB-AAAD-473E634680B0")
AndyCadAddin;
#endif
#endif /* __CADADDINLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


