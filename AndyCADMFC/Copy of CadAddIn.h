/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 02 04:26:32 2008
 */
/* Compiler settings for C:\Documents and Settings\Administrator\Desktop\cadsoftware engine\CadAddIn.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CadAddIn_h__
#define __CadAddIn_h__

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

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
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAndyCad __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAndyCad __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAndyCad __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAndyCad __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAndyCad __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAndyCad __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAndyCad __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadAllAdins )( 
            IAndyCad __RPC_FAR * This,
            BSTR strAddinLoadingInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MainWindow )( 
            IAndyCad __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStatus )( 
            IAndyCad __RPC_FAR * This,
            BSTR strStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAddInInfo )( 
            IAndyCad __RPC_FAR * This,
            long lSessionID,
            long lInstanceHandle,
            BSTR strXMLMenuToolbarIDCmdInfo,
            long lToobarRes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAddinToolbar )( 
            IAndyCad __RPC_FAR * This,
            long lAddinIndex,
            VARIANT varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetViewHeading )( 
            IAndyCad __RPC_FAR * This,
            BSTR strHeading1,
            BSTR strHeading2,
            BSTR strHeading3);
        
        END_INTERFACE
    } IAndyCadVtbl;

    interface IAndyCad
    {
        CONST_VTBL struct IAndyCadVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAndyCad_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAndyCad_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAndyCad_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAndyCad_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAndyCad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAndyCad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAndyCad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAndyCad_LoadAllAdins(This,strAddinLoadingInfo)	\
    (This)->lpVtbl -> LoadAllAdins(This,strAddinLoadingInfo)

#define IAndyCad_get_MainWindow(This,pVal)	\
    (This)->lpVtbl -> get_MainWindow(This,pVal)

#define IAndyCad_SendStatus(This,strStatus)	\
    (This)->lpVtbl -> SendStatus(This,strStatus)

#define IAndyCad_SetAddInInfo(This,lSessionID,lInstanceHandle,strXMLMenuToolbarIDCmdInfo,lToobarRes)	\
    (This)->lpVtbl -> SetAddInInfo(This,lSessionID,lInstanceHandle,strXMLMenuToolbarIDCmdInfo,lToobarRes)

#define IAndyCad_SetAddinToolbar(This,lAddinIndex,varValue)	\
    (This)->lpVtbl -> SetAddinToolbar(This,lAddinIndex,varValue)

#define IAndyCad_SetViewHeading(This,strHeading1,strHeading2,strHeading3)	\
    (This)->lpVtbl -> SetViewHeading(This,strHeading1,strHeading2,strHeading3)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_LoadAllAdins_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strAddinLoadingInfo);


void __RPC_STUB IAndyCad_LoadAllAdins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAndyCad_get_MainWindow_Proxy( 
    IAndyCad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IAndyCad_get_MainWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SendStatus_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strStatus);


void __RPC_STUB IAndyCad_SendStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetAddInInfo_Proxy( 
    IAndyCad __RPC_FAR * This,
    long lSessionID,
    long lInstanceHandle,
    BSTR strXMLMenuToolbarIDCmdInfo,
    long lToobarRes);


void __RPC_STUB IAndyCad_SetAddInInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetAddinToolbar_Proxy( 
    IAndyCad __RPC_FAR * This,
    long lAddinIndex,
    VARIANT varValue);


void __RPC_STUB IAndyCad_SetAddinToolbar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetViewHeading_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strHeading1,
    BSTR strHeading2,
    BSTR strHeading3);


void __RPC_STUB IAndyCad_SetViewHeading_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IAndyCadEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IAndyCadEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IAndyCadEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IAndyCadEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IAndyCadEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IAndyCadEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IAndyCadEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IAndyCadEventsVtbl;

    interface _IAndyCadEvents
    {
        CONST_VTBL struct _IAndyCadEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAndyCadEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAndyCadEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAndyCadEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAndyCadEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAndyCadEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAndyCadEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAndyCadEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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
            IAndyCad __RPC_FAR *pApp,
            VARIANT bFirstTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uninitialize( 
            long lSessionID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAndyCadAddinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAndyCadAddin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAndyCadAddin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAndyCadAddin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAndyCadAddin __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAndyCadAddin __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAndyCadAddin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAndyCadAddin __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAndyCadAddin __RPC_FAR * This,
            long lSessionID,
            IAndyCad __RPC_FAR *pApp,
            VARIANT bFirstTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Uninitialize )( 
            IAndyCadAddin __RPC_FAR * This,
            long lSessionID);
        
        END_INTERFACE
    } IAndyCadAddinVtbl;

    interface IAndyCadAddin
    {
        CONST_VTBL struct IAndyCadAddinVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAndyCadAddin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAndyCadAddin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAndyCadAddin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAndyCadAddin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAndyCadAddin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAndyCadAddin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAndyCadAddin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAndyCadAddin_Initialize(This,lSessionID,pApp,bFirstTime)	\
    (This)->lpVtbl -> Initialize(This,lSessionID,pApp,bFirstTime)

#define IAndyCadAddin_Uninitialize(This,lSessionID)	\
    (This)->lpVtbl -> Uninitialize(This,lSessionID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCadAddin_Initialize_Proxy( 
    IAndyCadAddin __RPC_FAR * This,
    long lSessionID,
    IAndyCad __RPC_FAR *pApp,
    VARIANT bFirstTime);


void __RPC_STUB IAndyCadAddin_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCadAddin_Uninitialize_Proxy( 
    IAndyCadAddin __RPC_FAR * This,
    long lSessionID);


void __RPC_STUB IAndyCadAddin_Uninitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IAndyCadAddinEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IAndyCadAddinEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IAndyCadAddinEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IAndyCadAddinEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IAndyCadAddinEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IAndyCadAddinEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IAndyCadAddinEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IAndyCadAddinEventsVtbl;

    interface _IAndyCadAddinEvents
    {
        CONST_VTBL struct _IAndyCadAddinEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAndyCadAddinEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAndyCadAddinEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAndyCadAddinEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAndyCadAddinEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAndyCadAddinEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAndyCadAddinEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAndyCadAddinEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
