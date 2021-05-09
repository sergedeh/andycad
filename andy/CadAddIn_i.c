/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 02 06:29:33 2015
 */
/* Compiler settings for C:\Program Files(uac)\MyProjects\andycad\CadAddIn.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IAndyCad = {0x0A7F1349,0xF18E,0x43D0,{0xBD,0x22,0x77,0x4D,0xB1,0x32,0xB9,0x66}};


const IID LIBID_CADADDINLib = {0xDFA3EF53,0x6256,0x4A0A,{0xA6,0x26,0x6F,0x62,0x86,0xCD,0x83,0x12}};


const IID DIID__IAndyCadEvents = {0x53D2ED37,0x09C2,0x437D,{0x8D,0xED,0x1D,0x4D,0x70,0xC4,0x7D,0x28}};


const IID IID_IAndyCadAddin = {0xA29432CA,0xCD10,0x412D,{0xBA,0x94,0x40,0xEF,0x2D,0x52,0x89,0x21}};


const CLSID CLSID_AndyCad = {0x243E5A7B,0xE5AD,0x4337,{0x9C,0x3F,0x44,0xE2,0x7D,0x55,0x4E,0x24}};


const IID DIID__IAndyCadAddinEvents = {0x6D929F85,0x25BA,0x475D,{0xBB,0x9F,0x9F,0x12,0xD2,0xF6,0x99,0xD3}};


const CLSID CLSID_AndyCadAddin = {0xB34E1702,0xB70A,0x48EB,{0xAA,0xAD,0x47,0x3E,0x63,0x46,0x80,0xB0}};


#ifdef __cplusplus
}
#endif

