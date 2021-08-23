

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for cad.odl:
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


#ifndef __cad_h_h__
#define __cad_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICad_FWD_DEFINED__
#define __ICad_FWD_DEFINED__
typedef interface ICad ICad;

#endif 	/* __ICad_FWD_DEFINED__ */


#ifndef __Document_FWD_DEFINED__
#define __Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class Document Document;
#else
typedef struct Document Document;
#endif /* __cplusplus */

#endif 	/* __Document_FWD_DEFINED__ */


#ifndef __ICadAutoWnd_FWD_DEFINED__
#define __ICadAutoWnd_FWD_DEFINED__
typedef interface ICadAutoWnd ICadAutoWnd;

#endif 	/* __ICadAutoWnd_FWD_DEFINED__ */


#ifndef __Window_FWD_DEFINED__
#define __Window_FWD_DEFINED__

#ifdef __cplusplus
typedef class Window Window;
#else
typedef struct Window Window;
#endif /* __cplusplus */

#endif 	/* __Window_FWD_DEFINED__ */


#ifndef __ICadAutoCanvas_FWD_DEFINED__
#define __ICadAutoCanvas_FWD_DEFINED__
typedef interface ICadAutoCanvas ICadAutoCanvas;

#endif 	/* __ICadAutoCanvas_FWD_DEFINED__ */


#ifndef __CadAutoCanvas_FWD_DEFINED__
#define __CadAutoCanvas_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoCanvas CadAutoCanvas;
#else
typedef struct CadAutoCanvas CadAutoCanvas;
#endif /* __cplusplus */

#endif 	/* __CadAutoCanvas_FWD_DEFINED__ */


#ifndef __ICadAutoDrawing_FWD_DEFINED__
#define __ICadAutoDrawing_FWD_DEFINED__
typedef interface ICadAutoDrawing ICadAutoDrawing;

#endif 	/* __ICadAutoDrawing_FWD_DEFINED__ */


#ifndef __CadAutoDrawing_FWD_DEFINED__
#define __CadAutoDrawing_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoDrawing CadAutoDrawing;
#else
typedef struct CadAutoDrawing CadAutoDrawing;
#endif /* __cplusplus */

#endif 	/* __CadAutoDrawing_FWD_DEFINED__ */


#ifndef __ICadAutoUtils_FWD_DEFINED__
#define __ICadAutoUtils_FWD_DEFINED__
typedef interface ICadAutoUtils ICadAutoUtils;

#endif 	/* __ICadAutoUtils_FWD_DEFINED__ */


#ifndef __CadAutoUtils_FWD_DEFINED__
#define __CadAutoUtils_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoUtils CadAutoUtils;
#else
typedef struct CadAutoUtils CadAutoUtils;
#endif /* __cplusplus */

#endif 	/* __CadAutoUtils_FWD_DEFINED__ */


#ifndef __ICadAutoVector_FWD_DEFINED__
#define __ICadAutoVector_FWD_DEFINED__
typedef interface ICadAutoVector ICadAutoVector;

#endif 	/* __ICadAutoVector_FWD_DEFINED__ */


#ifndef __CadAutoVector_FWD_DEFINED__
#define __CadAutoVector_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoVector CadAutoVector;
#else
typedef struct CadAutoVector CadAutoVector;
#endif /* __cplusplus */

#endif 	/* __CadAutoVector_FWD_DEFINED__ */


#ifndef __ICadAutoCollection_FWD_DEFINED__
#define __ICadAutoCollection_FWD_DEFINED__
typedef interface ICadAutoCollection ICadAutoCollection;

#endif 	/* __ICadAutoCollection_FWD_DEFINED__ */


#ifndef __CadAutoCollection_FWD_DEFINED__
#define __CadAutoCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoCollection CadAutoCollection;
#else
typedef struct CadAutoCollection CadAutoCollection;
#endif /* __cplusplus */

#endif 	/* __CadAutoCollection_FWD_DEFINED__ */


#ifndef __ICadAutoEdit_FWD_DEFINED__
#define __ICadAutoEdit_FWD_DEFINED__
typedef interface ICadAutoEdit ICadAutoEdit;

#endif 	/* __ICadAutoEdit_FWD_DEFINED__ */


#ifndef __CadAutoEdit_FWD_DEFINED__
#define __CadAutoEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoEdit CadAutoEdit;
#else
typedef struct CadAutoEdit CadAutoEdit;
#endif /* __cplusplus */

#endif 	/* __CadAutoEdit_FWD_DEFINED__ */


#ifndef __ICAdAutoShape_FWD_DEFINED__
#define __ICAdAutoShape_FWD_DEFINED__
typedef interface ICAdAutoShape ICAdAutoShape;

#endif 	/* __ICAdAutoShape_FWD_DEFINED__ */


#ifndef __CAdAutoShape_FWD_DEFINED__
#define __CAdAutoShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAdAutoShape CAdAutoShape;
#else
typedef struct CAdAutoShape CAdAutoShape;
#endif /* __cplusplus */

#endif 	/* __CAdAutoShape_FWD_DEFINED__ */


#ifndef __ICadAutoDrawingCollection_FWD_DEFINED__
#define __ICadAutoDrawingCollection_FWD_DEFINED__
typedef interface ICadAutoDrawingCollection ICadAutoDrawingCollection;

#endif 	/* __ICadAutoDrawingCollection_FWD_DEFINED__ */


#ifndef __CadAutoDrawingCollection_FWD_DEFINED__
#define __CadAutoDrawingCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoDrawingCollection CadAutoDrawingCollection;
#else
typedef struct CadAutoDrawingCollection CadAutoDrawingCollection;
#endif /* __cplusplus */

#endif 	/* __CadAutoDrawingCollection_FWD_DEFINED__ */


#ifndef __ICadAutoTransform_FWD_DEFINED__
#define __ICadAutoTransform_FWD_DEFINED__
typedef interface ICadAutoTransform ICadAutoTransform;

#endif 	/* __ICadAutoTransform_FWD_DEFINED__ */


#ifndef __CadAutoTransform_FWD_DEFINED__
#define __CadAutoTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoTransform CadAutoTransform;
#else
typedef struct CadAutoTransform CadAutoTransform;
#endif /* __cplusplus */

#endif 	/* __CadAutoTransform_FWD_DEFINED__ */


#ifndef __ICadAutoSurface_FWD_DEFINED__
#define __ICadAutoSurface_FWD_DEFINED__
typedef interface ICadAutoSurface ICadAutoSurface;

#endif 	/* __ICadAutoSurface_FWD_DEFINED__ */


#ifndef __CadAutoSurface_FWD_DEFINED__
#define __CadAutoSurface_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoSurface CadAutoSurface;
#else
typedef struct CadAutoSurface CadAutoSurface;
#endif /* __cplusplus */

#endif 	/* __CadAutoSurface_FWD_DEFINED__ */


#ifndef __ICadAutoCamera_FWD_DEFINED__
#define __ICadAutoCamera_FWD_DEFINED__
typedef interface ICadAutoCamera ICadAutoCamera;

#endif 	/* __ICadAutoCamera_FWD_DEFINED__ */


#ifndef __CadAutoCamera_FWD_DEFINED__
#define __CadAutoCamera_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadAutoCamera CadAutoCamera;
#else
typedef struct CadAutoCamera CadAutoCamera;
#endif /* __cplusplus */

#endif 	/* __CadAutoCamera_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Cad_LIBRARY_DEFINED__
#define __Cad_LIBRARY_DEFINED__

/* library Cad */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Cad;

#ifndef __ICad_DISPINTERFACE_DEFINED__
#define __ICad_DISPINTERFACE_DEFINED__

/* dispinterface ICad */
/* [uuid] */ 


EXTERN_C const IID DIID_ICad;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AD3DA4F5-9353-44E5-BB40-D3CBA5B83F86")
    ICad : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICad * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICad * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICad * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICad * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICad * This,
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
    } ICadVtbl;

    interface ICad
    {
        CONST_VTBL struct ICadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICad_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICad_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICad_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICad_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICad_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Document;

#ifdef __cplusplus

class DECLSPEC_UUID("3D3D1503-7A2F-4608-A563-100B1747CB9C")
Document;
#endif

#ifndef __ICadAutoWnd_DISPINTERFACE_DEFINED__
#define __ICadAutoWnd_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoWnd */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoWnd;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6CE928A1-E790-4E91-AFCC-0E22993746F0")
    ICadAutoWnd : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoWndVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoWnd * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoWnd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoWnd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoWnd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoWnd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoWnd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoWnd * This,
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
    } ICadAutoWndVtbl;

    interface ICadAutoWnd
    {
        CONST_VTBL struct ICadAutoWndVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoWnd_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoWnd_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoWnd_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoWnd_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoWnd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoWnd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoWnd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoWnd_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Window;

#ifdef __cplusplus

class DECLSPEC_UUID("343F6C50-8F61-4375-9B4A-A4D80BD3E3CE")
Window;
#endif

#ifndef __ICadAutoCanvas_DISPINTERFACE_DEFINED__
#define __ICadAutoCanvas_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoCanvas */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoCanvas;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("49302417-D30F-4DA6-B973-8F65E12E9223")
    ICadAutoCanvas : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoCanvasVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoCanvas * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoCanvas * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoCanvas * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoCanvas * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoCanvas * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoCanvas * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoCanvas * This,
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
    } ICadAutoCanvasVtbl;

    interface ICadAutoCanvas
    {
        CONST_VTBL struct ICadAutoCanvasVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoCanvas_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoCanvas_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoCanvas_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoCanvas_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoCanvas_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoCanvas_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoCanvas_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoCanvas_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoCanvas;

#ifdef __cplusplus

class DECLSPEC_UUID("DB23BECE-E5FB-48C2-9B9C-525DDE4CE8EB")
CadAutoCanvas;
#endif

#ifndef __ICadAutoDrawing_DISPINTERFACE_DEFINED__
#define __ICadAutoDrawing_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoDrawing */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoDrawing;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("980538BD-C145-4413-B2D2-B314017871A1")
    ICadAutoDrawing : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoDrawingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoDrawing * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoDrawing * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoDrawing * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoDrawing * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoDrawing * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoDrawing * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoDrawing * This,
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
    } ICadAutoDrawingVtbl;

    interface ICadAutoDrawing
    {
        CONST_VTBL struct ICadAutoDrawingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoDrawing_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoDrawing_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoDrawing_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoDrawing_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoDrawing_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoDrawing_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoDrawing_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoDrawing_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoDrawing;

#ifdef __cplusplus

class DECLSPEC_UUID("96BE50F4-201C-4F20-B6DF-C0F36777E89F")
CadAutoDrawing;
#endif

#ifndef __ICadAutoUtils_DISPINTERFACE_DEFINED__
#define __ICadAutoUtils_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoUtils */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoUtils;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6C92039F-CB9A-42DB-B245-B1808E87FCA2")
    ICadAutoUtils : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoUtilsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoUtils * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoUtils * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoUtils * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoUtils * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoUtils * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoUtils * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoUtils * This,
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
    } ICadAutoUtilsVtbl;

    interface ICadAutoUtils
    {
        CONST_VTBL struct ICadAutoUtilsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoUtils_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoUtils_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoUtils_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoUtils_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoUtils_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoUtils_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoUtils_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoUtils_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoUtils;

#ifdef __cplusplus

class DECLSPEC_UUID("FEDF4497-243E-4E4B-867A-3504FC734C1C")
CadAutoUtils;
#endif

#ifndef __ICadAutoVector_DISPINTERFACE_DEFINED__
#define __ICadAutoVector_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoVector */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoVector;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("14A4B89B-0C9A-43D5-A875-CCBF6E652716")
    ICadAutoVector : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoVectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoVector * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoVector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoVector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoVector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoVector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoVector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoVector * This,
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
    } ICadAutoVectorVtbl;

    interface ICadAutoVector
    {
        CONST_VTBL struct ICadAutoVectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoVector_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoVector_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoVector_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoVector_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoVector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoVector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoVector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoVector_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoVector;

#ifdef __cplusplus

class DECLSPEC_UUID("E3D9A88F-A045-4FB5-BD40-0D6999C29DA1")
CadAutoVector;
#endif

#ifndef __ICadAutoCollection_DISPINTERFACE_DEFINED__
#define __ICadAutoCollection_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoCollection */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("016DF3A9-1221-4263-8F09-890A79F35F56")
    ICadAutoCollection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoCollection * This,
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
    } ICadAutoCollectionVtbl;

    interface ICadAutoCollection
    {
        CONST_VTBL struct ICadAutoCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoCollection_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("06DB5DC7-A5D7-420D-AE56-E66FA5171FA8")
CadAutoCollection;
#endif

#ifndef __ICadAutoEdit_DISPINTERFACE_DEFINED__
#define __ICadAutoEdit_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoEdit */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0F6000FC-1C78-4F7F-9A12-94B592ADEA01")
    ICadAutoEdit : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoEdit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoEdit * This,
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
    } ICadAutoEditVtbl;

    interface ICadAutoEdit
    {
        CONST_VTBL struct ICadAutoEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoEdit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoEdit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoEdit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoEdit_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoEdit_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("1AC877AB-56D3-4E03-B69D-1E1C251B38B4")
CadAutoEdit;
#endif

#ifndef __ICAdAutoShape_DISPINTERFACE_DEFINED__
#define __ICAdAutoShape_DISPINTERFACE_DEFINED__

/* dispinterface ICAdAutoShape */
/* [uuid] */ 


EXTERN_C const IID DIID_ICAdAutoShape;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C38283A1-8AAE-4CDA-9B74-88BE60301D93")
    ICAdAutoShape : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICAdAutoShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICAdAutoShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICAdAutoShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICAdAutoShape * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICAdAutoShape * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICAdAutoShape * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICAdAutoShape * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICAdAutoShape * This,
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
    } ICAdAutoShapeVtbl;

    interface ICAdAutoShape
    {
        CONST_VTBL struct ICAdAutoShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICAdAutoShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICAdAutoShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICAdAutoShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICAdAutoShape_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICAdAutoShape_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICAdAutoShape_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICAdAutoShape_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICAdAutoShape_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAdAutoShape;

#ifdef __cplusplus

class DECLSPEC_UUID("EAC43A93-64DF-4109-8A22-FE2D3F036813")
CAdAutoShape;
#endif

#ifndef __ICadAutoDrawingCollection_DISPINTERFACE_DEFINED__
#define __ICadAutoDrawingCollection_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoDrawingCollection */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoDrawingCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4AA11FC0-F053-40D0-AD60-2B0B2DD3F342")
    ICadAutoDrawingCollection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoDrawingCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoDrawingCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoDrawingCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoDrawingCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoDrawingCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoDrawingCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoDrawingCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoDrawingCollection * This,
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
    } ICadAutoDrawingCollectionVtbl;

    interface ICadAutoDrawingCollection
    {
        CONST_VTBL struct ICadAutoDrawingCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoDrawingCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoDrawingCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoDrawingCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoDrawingCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoDrawingCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoDrawingCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoDrawingCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoDrawingCollection_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoDrawingCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("12858D08-AC5B-49E5-B66A-093F36EC5C13")
CadAutoDrawingCollection;
#endif

#ifndef __ICadAutoTransform_DISPINTERFACE_DEFINED__
#define __ICadAutoTransform_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoTransform */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EB970C20-A88E-4440-BA4B-A2F7476B3079")
    ICadAutoTransform : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoTransform * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoTransform * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoTransform * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoTransform * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoTransform * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoTransform * This,
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
    } ICadAutoTransformVtbl;

    interface ICadAutoTransform
    {
        CONST_VTBL struct ICadAutoTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoTransform_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoTransform_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoTransform_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoTransform_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoTransform_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoTransform;

#ifdef __cplusplus

class DECLSPEC_UUID("B78C5E30-D664-47CA-A82F-0336B47733A6")
CadAutoTransform;
#endif

#ifndef __ICadAutoSurface_DISPINTERFACE_DEFINED__
#define __ICadAutoSurface_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoSurface */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoSurface;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("164D0D08-3145-4901-BE22-84C48469A330")
    ICadAutoSurface : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoSurfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoSurface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoSurface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoSurface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoSurface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoSurface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoSurface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoSurface * This,
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
    } ICadAutoSurfaceVtbl;

    interface ICadAutoSurface
    {
        CONST_VTBL struct ICadAutoSurfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoSurface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoSurface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoSurface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoSurface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoSurface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoSurface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoSurface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoSurface_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoSurface;

#ifdef __cplusplus

class DECLSPEC_UUID("0E4E8E5D-7983-42FB-A92E-8AE0A95C838F")
CadAutoSurface;
#endif

#ifndef __ICadAutoCamera_DISPINTERFACE_DEFINED__
#define __ICadAutoCamera_DISPINTERFACE_DEFINED__

/* dispinterface ICadAutoCamera */
/* [uuid] */ 


EXTERN_C const IID DIID_ICadAutoCamera;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7822402F-3215-4B6C-8B6E-EB9DB14EA2D3")
    ICadAutoCamera : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ICadAutoCameraVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICadAutoCamera * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICadAutoCamera * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICadAutoCamera * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICadAutoCamera * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICadAutoCamera * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICadAutoCamera * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICadAutoCamera * This,
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
    } ICadAutoCameraVtbl;

    interface ICadAutoCamera
    {
        CONST_VTBL struct ICadAutoCameraVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICadAutoCamera_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICadAutoCamera_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICadAutoCamera_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICadAutoCamera_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICadAutoCamera_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICadAutoCamera_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICadAutoCamera_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ICadAutoCamera_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CadAutoCamera;

#ifdef __cplusplus

class DECLSPEC_UUID("8957AC98-8D97-4A7E-BE5D-BDFC28C0F1C6")
CadAutoCamera;
#endif
#endif /* __Cad_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


