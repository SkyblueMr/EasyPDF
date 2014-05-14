

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Dec 01 23:38:45 2013
 */
/* Compiler settings for EasyPDF.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_EasyPDFLib,0x19901D3B,0x6D4D,0x4FE8,0x9B,0x74,0xC4,0x8B,0xF2,0xE8,0x05,0x6A);


MIDL_DEFINE_GUID(IID, DIID__DEasyPDF,0x7D6957D9,0x8EC9,0x40F2,0x85,0x97,0x85,0x70,0x62,0xAF,0x5F,0xE5);


MIDL_DEFINE_GUID(IID, DIID__DEasyPDFEvents,0x5BAE4438,0xFE58,0x4131,0xBE,0xF4,0x74,0x37,0x4F,0xE2,0x08,0x12);


MIDL_DEFINE_GUID(CLSID, CLSID_EasyPDF,0x52805E94,0x07A4,0x42C9,0x9C,0xF8,0xC8,0x3C,0xCB,0xD9,0xC0,0xC1);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



