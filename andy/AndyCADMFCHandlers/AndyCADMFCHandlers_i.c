

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for AndyCADMFCHandlers.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IPreview,0xdf2e3311,0x0108,0x439c,0xbc,0xd8,0x98,0xc9,0x6e,0xdb,0x40,0xa3);


MIDL_DEFINE_GUID(IID, IID_IThumbnail,0xad4c740e,0xc730,0x4a0a,0x91,0x25,0xf4,0x28,0x4e,0x55,0x97,0xa3);


MIDL_DEFINE_GUID(IID, LIBID_AndyCADMFCHandlersLib,0x39473e66,0x79b7,0x41b4,0x91,0x31,0x18,0x6a,0xe4,0xfd,0x8d,0xf3);


MIDL_DEFINE_GUID(CLSID, CLSID_Preview,0x0828f1c3,0xecfc,0x4c3a,0x84,0x07,0x9e,0x30,0x3d,0x23,0xc4,0x67);


MIDL_DEFINE_GUID(CLSID, CLSID_Thumbnail,0x079d0216,0x7987,0x4ffb,0xac,0x51,0xd7,0x28,0x15,0xae,0x8f,0xfe);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



