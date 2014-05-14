

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __EasyPDFidl_h__
#define __EasyPDFidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DEasyPDF_FWD_DEFINED__
#define ___DEasyPDF_FWD_DEFINED__
typedef interface _DEasyPDF _DEasyPDF;
#endif 	/* ___DEasyPDF_FWD_DEFINED__ */


#ifndef ___DEasyPDFEvents_FWD_DEFINED__
#define ___DEasyPDFEvents_FWD_DEFINED__
typedef interface _DEasyPDFEvents _DEasyPDFEvents;
#endif 	/* ___DEasyPDFEvents_FWD_DEFINED__ */


#ifndef __EasyPDF_FWD_DEFINED__
#define __EasyPDF_FWD_DEFINED__

#ifdef __cplusplus
typedef class EasyPDF EasyPDF;
#else
typedef struct EasyPDF EasyPDF;
#endif /* __cplusplus */

#endif 	/* __EasyPDF_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __EasyPDFLib_LIBRARY_DEFINED__
#define __EasyPDFLib_LIBRARY_DEFINED__

/* library EasyPDFLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_EasyPDFLib;

#ifndef ___DEasyPDF_DISPINTERFACE_DEFINED__
#define ___DEasyPDF_DISPINTERFACE_DEFINED__

/* dispinterface _DEasyPDF */
/* [uuid] */ 


EXTERN_C const IID DIID__DEasyPDF;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7D6957D9-8EC9-40F2-8597-857062AF5FE5")
    _DEasyPDF : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEasyPDFVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEasyPDF * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEasyPDF * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEasyPDF * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEasyPDF * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEasyPDF * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEasyPDF * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEasyPDF * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEasyPDFVtbl;

    interface _DEasyPDF
    {
        CONST_VTBL struct _DEasyPDFVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEasyPDF_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEasyPDF_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEasyPDF_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEasyPDF_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEasyPDF_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEasyPDF_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEasyPDF_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEasyPDF_DISPINTERFACE_DEFINED__ */


#ifndef ___DEasyPDFEvents_DISPINTERFACE_DEFINED__
#define ___DEasyPDFEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DEasyPDFEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DEasyPDFEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5BAE4438-FE58-4131-BEF4-74374FE20812")
    _DEasyPDFEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DEasyPDFEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DEasyPDFEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DEasyPDFEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DEasyPDFEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DEasyPDFEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DEasyPDFEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DEasyPDFEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DEasyPDFEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DEasyPDFEventsVtbl;

    interface _DEasyPDFEvents
    {
        CONST_VTBL struct _DEasyPDFEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DEasyPDFEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DEasyPDFEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DEasyPDFEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DEasyPDFEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DEasyPDFEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DEasyPDFEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DEasyPDFEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DEasyPDFEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EasyPDF;

#ifdef __cplusplus

class DECLSPEC_UUID("52805E94-07A4-42C9-9CF8-C83CCBD9C0C1")
EasyPDF;
#endif
#endif /* __EasyPDFLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


