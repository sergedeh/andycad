/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Aug 26 16:03:17 2021
 */
/* Compiler settings for C:\Users\Administrator\source\repos\andycad\andy\CadAddIn.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "CadAddIn.h"

#define TYPE_FORMAT_STRING_SIZE   985                               
#define PROC_FORMAT_STRING_SIZE   47                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IAndyCad, ver. 0.0,
   GUID={0x0A7F1349,0xF18E,0x43D0,{0xBD,0x22,0x77,0x4D,0xB1,0x32,0xB9,0x66}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_LoadAllAdins_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strAddinLoadingInfo)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strAddinLoadingInfo,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strAddinLoadingInfo,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_LoadAllAdins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_strAddinLoadingInfo;
    BSTR strAddinLoadingInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_strAddinLoadingInfo = &strAddinLoadingInfo;
    MIDL_memset(
               _p_strAddinLoadingInfo,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strAddinLoadingInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> LoadAllAdins((IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,strAddinLoadingInfo);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strAddinLoadingInfo,
                            &__MIDL_TypeFormatString.Format[26] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAndyCad_get_MainWindow_Proxy( 
    IAndyCad __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        if(!pVal)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
            *pVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[36],
                         ( void __RPC_FAR * )pVal);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_get_MainWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    long _M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pVal;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( long __RPC_FAR * )pVal = 0;
    RpcTryFinally
        {
        pVal = &_M0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_MainWindow((IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,pVal);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pVal;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SendStatus_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strStatus)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strStatus,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strStatus,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_SendStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_strStatus;
    BSTR strStatus;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_strStatus = &strStatus;
    MIDL_memset(
               _p_strStatus,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strStatus,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SendStatus((IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,strStatus);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strStatus,
                            &__MIDL_TypeFormatString.Format[26] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetAddInInfo_Proxy( 
    IAndyCad __RPC_FAR * This,
    long lSessionID,
    long lInstanceHandle,
    BSTR strXMLMenuToolbarIDCmdInfo,
    long lToobarRes)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U + 8U + 11U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strXMLMenuToolbarIDCmdInfo,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lSessionID;
            
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lInstanceHandle;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strXMLMenuToolbarIDCmdInfo,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lToobarRes;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_SetAddInInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_strXMLMenuToolbarIDCmdInfo;
    long lInstanceHandle;
    long lSessionID;
    long lToobarRes;
    BSTR strXMLMenuToolbarIDCmdInfo;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_strXMLMenuToolbarIDCmdInfo = &strXMLMenuToolbarIDCmdInfo;
    MIDL_memset(
               _p_strXMLMenuToolbarIDCmdInfo,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[12] );
        
        lSessionID = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        lInstanceHandle = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strXMLMenuToolbarIDCmdInfo,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        lToobarRes = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetAddInInfo(
                (IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,
                lSessionID,
                lInstanceHandle,
                strXMLMenuToolbarIDCmdInfo,
                lToobarRes);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strXMLMenuToolbarIDCmdInfo,
                            &__MIDL_TypeFormatString.Format[26] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetAddinToolbar_Proxy( 
    IAndyCad __RPC_FAR * This,
    long lAddinIndex,
    VARIANT varValue)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&varValue,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[974] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( long __RPC_FAR * )_StubMsg.Buffer)++ = lAddinIndex;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&varValue,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[974] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_SetAddinToolbar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_varValue;
    long lAddinIndex;
    VARIANT varValue;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_varValue = &varValue;
    MIDL_memset(
               _p_varValue,
               0,
               sizeof( VARIANT  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[24] );
        
        lAddinIndex = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_varValue,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[974],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetAddinToolbar(
                   (IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,
                   lAddinIndex,
                   varValue);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&varValue,
                            &__MIDL_TypeFormatString.Format[974] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAndyCad_SetViewHeading_Proxy( 
    IAndyCad __RPC_FAR * This,
    BSTR strHeading1,
    BSTR strHeading2,
    BSTR strHeading3)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U + 15U + 15U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strHeading1,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strHeading2,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&strHeading3,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strHeading1,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strHeading2,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&strHeading3,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IAndyCad_SetViewHeading_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_strHeading1;
    void __RPC_FAR *_p_strHeading2;
    void __RPC_FAR *_p_strHeading3;
    BSTR strHeading1;
    BSTR strHeading2;
    BSTR strHeading3;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_strHeading1 = &strHeading1;
    MIDL_memset(
               _p_strHeading1,
               0,
               sizeof( BSTR  ));
    _p_strHeading2 = &strHeading2;
    MIDL_memset(
               _p_strHeading2,
               0,
               sizeof( BSTR  ));
    _p_strHeading3 = &strHeading3;
    MIDL_memset(
               _p_strHeading3,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strHeading1,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strHeading2,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_strHeading3,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[26],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IAndyCad*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetViewHeading(
                  (IAndyCad *) ((CStdStubBuffer *)This)->pvServerObject,
                  strHeading1,
                  strHeading2,
                  strHeading3);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strHeading1,
                            &__MIDL_TypeFormatString.Format[26] );
        
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strHeading2,
                            &__MIDL_TypeFormatString.Format[26] );
        
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&strHeading3,
                            &__MIDL_TypeFormatString.Format[26] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

CINTERFACE_PROXY_VTABLE(13) _IAndyCadProxyVtbl = 
{
    &IID_IAndyCad,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch_GetTypeInfoCount_Proxy */ ,
    0 /* IDispatch_GetTypeInfo_Proxy */ ,
    0 /* IDispatch_GetIDsOfNames_Proxy */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    IAndyCad_LoadAllAdins_Proxy ,
    IAndyCad_get_MainWindow_Proxy ,
    IAndyCad_SendStatus_Proxy ,
    IAndyCad_SetAddInInfo_Proxy ,
    IAndyCad_SetAddinToolbar_Proxy ,
    IAndyCad_SetViewHeading_Proxy
};


static const PRPC_STUB_FUNCTION IAndyCad_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    IAndyCad_LoadAllAdins_Stub,
    IAndyCad_get_MainWindow_Stub,
    IAndyCad_SendStatus_Stub,
    IAndyCad_SetAddInInfo_Stub,
    IAndyCad_SetAddinToolbar_Stub,
    IAndyCad_SetViewHeading_Stub
};

CInterfaceStubVtbl _IAndyCadStubVtbl =
{
    &IID_IAndyCad,
    0,
    13,
    &IAndyCad_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/*  4 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 10 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 16 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 18 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/* 20 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 22 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 26 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x4,		/* x86, MIPS & PPC Stack size = 4 */
#else
			0x4,		/* Alpha Stack size = 4 */
#endif
/* 28 */	NdrFcShort( 0x3ce ),	/* Type Offset=974 */
/* 30 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 34 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/* 36 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 38 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/* 40 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 42 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/* 44 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xc ),	/* Offset= 12 (16) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 16 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x8 ),	/* 8 */
/* 20 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (6) */
/* 22 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 24 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 38 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x12, 0x0,	/* FC_UP */
/* 42 */	NdrFcShort( 0x390 ),	/* Offset= 912 (954) */
/* 44 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 46 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 48 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 50 */	NdrFcShort( 0x2 ),	/* Offset= 2 (52) */
/* 52 */	NdrFcShort( 0x10 ),	/* 16 */
/* 54 */	NdrFcShort( 0x2b ),	/* 43 */
/* 56 */	NdrFcLong( 0x3 ),	/* 3 */
/* 60 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 62 */	NdrFcLong( 0x11 ),	/* 17 */
/* 66 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 68 */	NdrFcLong( 0x2 ),	/* 2 */
/* 72 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 74 */	NdrFcLong( 0x4 ),	/* 4 */
/* 78 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 80 */	NdrFcLong( 0x5 ),	/* 5 */
/* 84 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 86 */	NdrFcLong( 0xb ),	/* 11 */
/* 90 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 92 */	NdrFcLong( 0xa ),	/* 10 */
/* 96 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 98 */	NdrFcLong( 0x6 ),	/* 6 */
/* 102 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (316) */
/* 104 */	NdrFcLong( 0x7 ),	/* 7 */
/* 108 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 110 */	NdrFcLong( 0x8 ),	/* 8 */
/* 114 */	NdrFcShort( 0xffffff90 ),	/* Offset= -112 (2) */
/* 116 */	NdrFcLong( 0xd ),	/* 13 */
/* 120 */	NdrFcShort( 0xca ),	/* Offset= 202 (322) */
/* 122 */	NdrFcLong( 0x9 ),	/* 9 */
/* 126 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (340) */
/* 128 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 132 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (358) */
/* 134 */	NdrFcLong( 0x24 ),	/* 36 */
/* 138 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (886) */
/* 140 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 144 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (886) */
/* 146 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 150 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (890) */
/* 152 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 156 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (894) */
/* 158 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 162 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (898) */
/* 164 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 168 */	NdrFcShort( 0x2de ),	/* Offset= 734 (902) */
/* 170 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 174 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (906) */
/* 176 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 180 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (894) */
/* 182 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 186 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (898) */
/* 188 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 192 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (910) */
/* 194 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 198 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (906) */
/* 200 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 204 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (914) */
/* 206 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 210 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (918) */
/* 212 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 216 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (922) */
/* 218 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 222 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (926) */
/* 224 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 228 */	NdrFcShort( 0x2be ),	/* Offset= 702 (930) */
/* 230 */	NdrFcLong( 0x10 ),	/* 16 */
/* 234 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 236 */	NdrFcLong( 0x12 ),	/* 18 */
/* 240 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 242 */	NdrFcLong( 0x13 ),	/* 19 */
/* 246 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 248 */	NdrFcLong( 0x16 ),	/* 22 */
/* 252 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 254 */	NdrFcLong( 0x17 ),	/* 23 */
/* 258 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 260 */	NdrFcLong( 0xe ),	/* 14 */
/* 264 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (938) */
/* 266 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 270 */	NdrFcShort( 0x2a8 ),	/* Offset= 680 (950) */
/* 272 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 276 */	NdrFcShort( 0x266 ),	/* Offset= 614 (890) */
/* 278 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 282 */	NdrFcShort( 0x264 ),	/* Offset= 612 (894) */
/* 284 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 288 */	NdrFcShort( 0x262 ),	/* Offset= 610 (898) */
/* 290 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 294 */	NdrFcShort( 0x25c ),	/* Offset= 604 (898) */
/* 296 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 300 */	NdrFcShort( 0x256 ),	/* Offset= 598 (898) */
/* 302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 306 */	NdrFcShort( 0x0 ),	/* Offset= 0 (306) */
/* 308 */	NdrFcLong( 0x1 ),	/* 1 */
/* 312 */	NdrFcShort( 0x0 ),	/* Offset= 0 (312) */
/* 314 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (313) */
/* 316 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 320 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 322 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 332 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 334 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 336 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 338 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 340 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 342 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 352 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 354 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 356 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 358 */	
			0x12, 0x0,	/* FC_UP */
/* 360 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (868) */
/* 362 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 364 */	NdrFcShort( 0x18 ),	/* 24 */
/* 366 */	NdrFcShort( 0xa ),	/* 10 */
/* 368 */	NdrFcLong( 0x8 ),	/* 8 */
/* 372 */	NdrFcShort( 0x58 ),	/* Offset= 88 (460) */
/* 374 */	NdrFcLong( 0xd ),	/* 13 */
/* 378 */	NdrFcShort( 0x78 ),	/* Offset= 120 (498) */
/* 380 */	NdrFcLong( 0x9 ),	/* 9 */
/* 384 */	NdrFcShort( 0x94 ),	/* Offset= 148 (532) */
/* 386 */	NdrFcLong( 0xc ),	/* 12 */
/* 390 */	NdrFcShort( 0xbc ),	/* Offset= 188 (578) */
/* 392 */	NdrFcLong( 0x24 ),	/* 36 */
/* 396 */	NdrFcShort( 0x114 ),	/* Offset= 276 (672) */
/* 398 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 402 */	NdrFcShort( 0x130 ),	/* Offset= 304 (706) */
/* 404 */	NdrFcLong( 0x10 ),	/* 16 */
/* 408 */	NdrFcShort( 0x148 ),	/* Offset= 328 (736) */
/* 410 */	NdrFcLong( 0x2 ),	/* 2 */
/* 414 */	NdrFcShort( 0x160 ),	/* Offset= 352 (766) */
/* 416 */	NdrFcLong( 0x3 ),	/* 3 */
/* 420 */	NdrFcShort( 0x178 ),	/* Offset= 376 (796) */
/* 422 */	NdrFcLong( 0x14 ),	/* 20 */
/* 426 */	NdrFcShort( 0x190 ),	/* Offset= 400 (826) */
/* 428 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (427) */
/* 430 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 432 */	NdrFcShort( 0x4 ),	/* 4 */
/* 434 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 440 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 442 */	NdrFcShort( 0x4 ),	/* 4 */
/* 444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 446 */	NdrFcShort( 0x1 ),	/* 1 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	0x12, 0x0,	/* FC_UP */
/* 454 */	NdrFcShort( 0xfffffe4a ),	/* Offset= -438 (16) */
/* 456 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 458 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 460 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 464 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 466 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 468 */	NdrFcShort( 0x4 ),	/* 4 */
/* 470 */	NdrFcShort( 0x4 ),	/* 4 */
/* 472 */	0x11, 0x0,	/* FC_RP */
/* 474 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (430) */
/* 476 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 478 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 480 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 492 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 494 */	NdrFcShort( 0xffffff54 ),	/* Offset= -172 (322) */
/* 496 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 498 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x6 ),	/* Offset= 6 (510) */
/* 506 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 508 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 510 */	
			0x11, 0x0,	/* FC_RP */
/* 512 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (480) */
/* 514 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 526 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 528 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (340) */
/* 530 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 532 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x6 ),	/* Offset= 6 (544) */
/* 540 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 542 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 544 */	
			0x11, 0x0,	/* FC_RP */
/* 546 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (514) */
/* 548 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 550 */	NdrFcShort( 0x4 ),	/* 4 */
/* 552 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 558 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 560 */	NdrFcShort( 0x4 ),	/* 4 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x1 ),	/* 1 */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	0x12, 0x0,	/* FC_UP */
/* 572 */	NdrFcShort( 0x17e ),	/* Offset= 382 (954) */
/* 574 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 578 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x6 ),	/* Offset= 6 (590) */
/* 586 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 588 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 590 */	
			0x11, 0x0,	/* FC_RP */
/* 592 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (548) */
/* 594 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 596 */	NdrFcLong( 0x2f ),	/* 47 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 606 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 608 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 610 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 612 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 614 */	NdrFcShort( 0x1 ),	/* 1 */
/* 616 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 618 */	NdrFcShort( 0x4 ),	/* 4 */
/* 620 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 622 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 624 */	NdrFcShort( 0x10 ),	/* 16 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0xa ),	/* Offset= 10 (638) */
/* 630 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 632 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 634 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (594) */
/* 636 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 638 */	
			0x12, 0x0,	/* FC_UP */
/* 640 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (612) */
/* 642 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 644 */	NdrFcShort( 0x4 ),	/* 4 */
/* 646 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 652 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 654 */	NdrFcShort( 0x4 ),	/* 4 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcShort( 0x1 ),	/* 1 */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	0x12, 0x0,	/* FC_UP */
/* 666 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (622) */
/* 668 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 670 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 672 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 674 */	NdrFcShort( 0x8 ),	/* 8 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x6 ),	/* Offset= 6 (684) */
/* 680 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 682 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 684 */	
			0x11, 0x0,	/* FC_RP */
/* 686 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (642) */
/* 688 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 692 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 694 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 696 */	NdrFcShort( 0x10 ),	/* 16 */
/* 698 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 700 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 702 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (688) */
			0x5b,		/* FC_END */
/* 706 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 708 */	NdrFcShort( 0x18 ),	/* 24 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0xa ),	/* Offset= 10 (722) */
/* 714 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 716 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 718 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (694) */
/* 720 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 722 */	
			0x11, 0x0,	/* FC_RP */
/* 724 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (480) */
/* 726 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 730 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 736 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 740 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 742 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 744 */	NdrFcShort( 0x4 ),	/* 4 */
/* 746 */	NdrFcShort( 0x4 ),	/* 4 */
/* 748 */	0x12, 0x0,	/* FC_UP */
/* 750 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (726) */
/* 752 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 754 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 756 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 758 */	NdrFcShort( 0x2 ),	/* 2 */
/* 760 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 766 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 772 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 774 */	NdrFcShort( 0x4 ),	/* 4 */
/* 776 */	NdrFcShort( 0x4 ),	/* 4 */
/* 778 */	0x12, 0x0,	/* FC_UP */
/* 780 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (756) */
/* 782 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 784 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 786 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 796 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 800 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 802 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 804 */	NdrFcShort( 0x4 ),	/* 4 */
/* 806 */	NdrFcShort( 0x4 ),	/* 4 */
/* 808 */	0x12, 0x0,	/* FC_UP */
/* 810 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (786) */
/* 812 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 814 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 816 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 818 */	NdrFcShort( 0x8 ),	/* 8 */
/* 820 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 824 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 826 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 830 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 832 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 834 */	NdrFcShort( 0x4 ),	/* 4 */
/* 836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 838 */	0x12, 0x0,	/* FC_UP */
/* 840 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (816) */
/* 842 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 844 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 846 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 850 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 852 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 854 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 860 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 862 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 864 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (846) */
/* 866 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 868 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 870 */	NdrFcShort( 0x28 ),	/* 40 */
/* 872 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (854) */
/* 874 */	NdrFcShort( 0x0 ),	/* Offset= 0 (874) */
/* 876 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 878 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 880 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 882 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (362) */
			0x5b,		/* FC_END */
/* 886 */	
			0x12, 0x0,	/* FC_UP */
/* 888 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (622) */
/* 890 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 892 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 894 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 896 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 898 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 900 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 902 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 904 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 906 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 908 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x12, 0x0,	/* FC_UP */
/* 912 */	NdrFcShort( 0xfffffdac ),	/* Offset= -596 (316) */
/* 914 */	
			0x12, 0x10,	/* FC_UP */
/* 916 */	NdrFcShort( 0xfffffc6e ),	/* Offset= -914 (2) */
/* 918 */	
			0x12, 0x10,	/* FC_UP */
/* 920 */	NdrFcShort( 0xfffffdaa ),	/* Offset= -598 (322) */
/* 922 */	
			0x12, 0x10,	/* FC_UP */
/* 924 */	NdrFcShort( 0xfffffdb8 ),	/* Offset= -584 (340) */
/* 926 */	
			0x12, 0x10,	/* FC_UP */
/* 928 */	NdrFcShort( 0xfffffdc6 ),	/* Offset= -570 (358) */
/* 930 */	
			0x12, 0x10,	/* FC_UP */
/* 932 */	NdrFcShort( 0x2 ),	/* Offset= 2 (934) */
/* 934 */	
			0x12, 0x0,	/* FC_UP */
/* 936 */	NdrFcShort( 0xfffffc58 ),	/* Offset= -936 (0) */
/* 938 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 940 */	NdrFcShort( 0x10 ),	/* 16 */
/* 942 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 944 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 946 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 948 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 950 */	
			0x12, 0x0,	/* FC_UP */
/* 952 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (938) */
/* 954 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 956 */	NdrFcShort( 0x20 ),	/* 32 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 960 */	NdrFcShort( 0x0 ),	/* Offset= 0 (960) */
/* 962 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 964 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 966 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 968 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 970 */	NdrFcShort( 0xfffffc62 ),	/* Offset= -926 (44) */
/* 972 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 974 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 976 */	NdrFcShort( 0x1 ),	/* 1 */
/* 978 */	NdrFcShort( 0x10 ),	/* 16 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0xfffffc52 ),	/* Offset= -942 (40) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _CadAddIn_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IAndyCadProxyVtbl,
    0
};

const CInterfaceStubVtbl * _CadAddIn_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IAndyCadStubVtbl,
    0
};

PCInterfaceName const _CadAddIn_InterfaceNamesList[] = 
{
    "IAndyCad",
    0
};

const IID *  _CadAddIn_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _CadAddIn_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _CadAddIn, pIID, n)

int __stdcall _CadAddIn_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_CadAddIn_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo CadAddIn_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _CadAddIn_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _CadAddIn_StubVtblList,
    (const PCInterfaceName * ) & _CadAddIn_InterfaceNamesList,
    (const IID ** ) & _CadAddIn_BaseIIDList,
    & _CadAddIn_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
