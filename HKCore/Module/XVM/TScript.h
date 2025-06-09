/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 31 16:41:42 2009
 */
/* Compiler settings for D:\ATL\PATS\TScript\TScript.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __TScript_h__
#define __TScript_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITScript_FWD_DEFINED__
#define __ITScript_FWD_DEFINED__
typedef interface ITScript ITScript;
#endif 	/* __ITScript_FWD_DEFINED__ */


#ifndef __ITAsm_FWD_DEFINED__
#define __ITAsm_FWD_DEFINED__
typedef interface ITAsm ITAsm;
#endif 	/* __ITAsm_FWD_DEFINED__ */


#ifndef __ISyntaxs_FWD_DEFINED__
#define __ISyntaxs_FWD_DEFINED__
typedef interface ISyntaxs ISyntaxs;
#endif 	/* __ISyntaxs_FWD_DEFINED__ */


#ifndef __ISyntax_FWD_DEFINED__
#define __ISyntax_FWD_DEFINED__
typedef interface ISyntax ISyntax;
#endif 	/* __ISyntax_FWD_DEFINED__ */


#ifndef __TScript_FWD_DEFINED__
#define __TScript_FWD_DEFINED__

#ifdef __cplusplus
typedef class TScript TScript;
#else
typedef struct TScript TScript;
#endif /* __cplusplus */

#endif 	/* __TScript_FWD_DEFINED__ */


#ifndef __TAsm_FWD_DEFINED__
#define __TAsm_FWD_DEFINED__

#ifdef __cplusplus
typedef class TAsm TAsm;
#else
typedef struct TAsm TAsm;
#endif /* __cplusplus */

#endif 	/* __TAsm_FWD_DEFINED__ */


#ifndef __Syntaxs_FWD_DEFINED__
#define __Syntaxs_FWD_DEFINED__

#ifdef __cplusplus
typedef class Syntaxs Syntaxs;
#else
typedef struct Syntaxs Syntaxs;
#endif /* __cplusplus */

#endif 	/* __Syntaxs_FWD_DEFINED__ */


#ifndef __Syntax_FWD_DEFINED__
#define __Syntax_FWD_DEFINED__

#ifdef __cplusplus
typedef class Syntax Syntax;
#else
typedef struct Syntax Syntax;
#endif /* __cplusplus */

#endif 	/* __Syntax_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITScript_INTERFACE_DEFINED__
#define __ITScript_INTERFACE_DEFINED__

/* interface ITScript */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITScript;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B34EBF4-E4F8-418C-909C-AE9F136C0B12")
    ITScript : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BuildFile( 
            /* [in] */ BSTR bstrTssFile,
            /* [retval][out] */ long __RPC_FAR *pnErrors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BuildText( 
            /* [in] */ BSTR bstrTssText,
            /* [retval][out] */ long __RPC_FAR *pnErrors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSyntaxErrors( 
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTseBuffer( 
            /* [in] */ LPDISPATCH pBBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTseBuffer2( 
            /* [in] */ VARIANT __RPC_FAR *pvBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTasmBuffer( 
            /* [in] */ LPDISPATCH pSBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTasmBuffer2( 
            /* [in] */ VARIANT __RPC_FAR *pvBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterHostApiFunc( 
            /* [in] */ BSTR strName,
            /* [in] */ long nParaCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterHostApiFuncPara( 
            /* [in] */ long nFuncIndex,
            /* [in] */ long nParaIndex,
            /* [in] */ long nParaType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteTasmFile( 
            /* [in] */ BSTR bstrTasmFile,
            /* [retval][out] */ long __RPC_FAR *pReturn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteTseFile( 
            /* [in] */ BSTR bstrTseFile,
            /* [retval][out] */ long __RPC_FAR *pReturn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITScriptVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITScript __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITScript __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITScript __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITScript __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITScript __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITScript __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITScript __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BuildFile )( 
            ITScript __RPC_FAR * This,
            /* [in] */ BSTR bstrTssFile,
            /* [retval][out] */ long __RPC_FAR *pnErrors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BuildText )( 
            ITScript __RPC_FAR * This,
            /* [in] */ BSTR bstrTssText,
            /* [retval][out] */ long __RPC_FAR *pnErrors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSyntaxErrors )( 
            ITScript __RPC_FAR * This,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTseBuffer )( 
            ITScript __RPC_FAR * This,
            /* [in] */ LPDISPATCH pBBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTseBuffer2 )( 
            ITScript __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTasmBuffer )( 
            ITScript __RPC_FAR * This,
            /* [in] */ LPDISPATCH pSBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTasmBuffer2 )( 
            ITScript __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterHostApiFunc )( 
            ITScript __RPC_FAR * This,
            /* [in] */ BSTR strName,
            /* [in] */ long nParaCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterHostApiFuncPara )( 
            ITScript __RPC_FAR * This,
            /* [in] */ long nFuncIndex,
            /* [in] */ long nParaIndex,
            /* [in] */ long nParaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteTasmFile )( 
            ITScript __RPC_FAR * This,
            /* [in] */ BSTR bstrTasmFile,
            /* [retval][out] */ long __RPC_FAR *pReturn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteTseFile )( 
            ITScript __RPC_FAR * This,
            /* [in] */ BSTR bstrTseFile,
            /* [retval][out] */ long __RPC_FAR *pReturn);
        
        END_INTERFACE
    } ITScriptVtbl;

    interface ITScript
    {
        CONST_VTBL struct ITScriptVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITScript_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITScript_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITScript_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITScript_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITScript_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITScript_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITScript_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITScript_BuildFile(This,bstrTssFile,pnErrors)	\
    (This)->lpVtbl -> BuildFile(This,bstrTssFile,pnErrors)

#define ITScript_BuildText(This,bstrTssText,pnErrors)	\
    (This)->lpVtbl -> BuildText(This,bstrTssText,pnErrors)

#define ITScript_GetSyntaxErrors(This,pSyntaxs)	\
    (This)->lpVtbl -> GetSyntaxErrors(This,pSyntaxs)

#define ITScript_GetTseBuffer(This,pBBuffer)	\
    (This)->lpVtbl -> GetTseBuffer(This,pBBuffer)

#define ITScript_GetTseBuffer2(This,pvBuffer)	\
    (This)->lpVtbl -> GetTseBuffer2(This,pvBuffer)

#define ITScript_GetTasmBuffer(This,pSBuffer)	\
    (This)->lpVtbl -> GetTasmBuffer(This,pSBuffer)

#define ITScript_GetTasmBuffer2(This,pvBuffer)	\
    (This)->lpVtbl -> GetTasmBuffer2(This,pvBuffer)

#define ITScript_RegisterHostApiFunc(This,strName,nParaCount)	\
    (This)->lpVtbl -> RegisterHostApiFunc(This,strName,nParaCount)

#define ITScript_RegisterHostApiFuncPara(This,nFuncIndex,nParaIndex,nParaType)	\
    (This)->lpVtbl -> RegisterHostApiFuncPara(This,nFuncIndex,nParaIndex,nParaType)

#define ITScript_WriteTasmFile(This,bstrTasmFile,pReturn)	\
    (This)->lpVtbl -> WriteTasmFile(This,bstrTasmFile,pReturn)

#define ITScript_WriteTseFile(This,bstrTseFile,pReturn)	\
    (This)->lpVtbl -> WriteTseFile(This,bstrTseFile,pReturn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_BuildFile_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ BSTR bstrTssFile,
    /* [retval][out] */ long __RPC_FAR *pnErrors);


void __RPC_STUB ITScript_BuildFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_BuildText_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ BSTR bstrTssText,
    /* [retval][out] */ long __RPC_FAR *pnErrors);


void __RPC_STUB ITScript_BuildText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_GetSyntaxErrors_Proxy( 
    ITScript __RPC_FAR * This,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs);


void __RPC_STUB ITScript_GetSyntaxErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_GetTseBuffer_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ LPDISPATCH pBBuffer);


void __RPC_STUB ITScript_GetTseBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_GetTseBuffer2_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvBuffer);


void __RPC_STUB ITScript_GetTseBuffer2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_GetTasmBuffer_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ LPDISPATCH pSBuffer);


void __RPC_STUB ITScript_GetTasmBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_GetTasmBuffer2_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvBuffer);


void __RPC_STUB ITScript_GetTasmBuffer2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_RegisterHostApiFunc_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ BSTR strName,
    /* [in] */ long nParaCount);


void __RPC_STUB ITScript_RegisterHostApiFunc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_RegisterHostApiFuncPara_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ long nFuncIndex,
    /* [in] */ long nParaIndex,
    /* [in] */ long nParaType);


void __RPC_STUB ITScript_RegisterHostApiFuncPara_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_WriteTasmFile_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ BSTR bstrTasmFile,
    /* [retval][out] */ long __RPC_FAR *pReturn);


void __RPC_STUB ITScript_WriteTasmFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITScript_WriteTseFile_Proxy( 
    ITScript __RPC_FAR * This,
    /* [in] */ BSTR bstrTseFile,
    /* [retval][out] */ long __RPC_FAR *pReturn);


void __RPC_STUB ITScript_WriteTseFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITScript_INTERFACE_DEFINED__ */


#ifndef __ITAsm_INTERFACE_DEFINED__
#define __ITAsm_INTERFACE_DEFINED__

/* interface ITAsm */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITAsm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("290904A5-52EA-46F5-BC36-149C1874CF26")
    ITAsm : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BuildFile( 
            /* [in] */ BSTR bstrTasmFile,
            /* [retval][out] */ long __RPC_FAR *pnErrors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BuildText( 
            /* [in] */ BSTR bstrTasmText,
            /* [retval][out] */ long __RPC_FAR *pnErrors) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSyntaxErrors( 
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTseBuffer( 
            /* [in] */ LPDISPATCH pBBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTseBuffer2( 
            /* [in] */ VARIANT __RPC_FAR *pvBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteTseFile( 
            /* [in] */ BSTR bstrTseFile,
            /* [retval][out] */ long __RPC_FAR *pReturn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITAsmVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITAsm __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITAsm __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITAsm __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BuildFile )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ BSTR bstrTasmFile,
            /* [retval][out] */ long __RPC_FAR *pnErrors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BuildText )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ BSTR bstrTasmText,
            /* [retval][out] */ long __RPC_FAR *pnErrors);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSyntaxErrors )( 
            ITAsm __RPC_FAR * This,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTseBuffer )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ LPDISPATCH pBBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTseBuffer2 )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteTseFile )( 
            ITAsm __RPC_FAR * This,
            /* [in] */ BSTR bstrTseFile,
            /* [retval][out] */ long __RPC_FAR *pReturn);
        
        END_INTERFACE
    } ITAsmVtbl;

    interface ITAsm
    {
        CONST_VTBL struct ITAsmVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITAsm_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITAsm_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITAsm_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITAsm_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITAsm_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITAsm_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITAsm_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITAsm_BuildFile(This,bstrTasmFile,pnErrors)	\
    (This)->lpVtbl -> BuildFile(This,bstrTasmFile,pnErrors)

#define ITAsm_BuildText(This,bstrTasmText,pnErrors)	\
    (This)->lpVtbl -> BuildText(This,bstrTasmText,pnErrors)

#define ITAsm_GetSyntaxErrors(This,pSyntaxs)	\
    (This)->lpVtbl -> GetSyntaxErrors(This,pSyntaxs)

#define ITAsm_GetTseBuffer(This,pBBuffer)	\
    (This)->lpVtbl -> GetTseBuffer(This,pBBuffer)

#define ITAsm_GetTseBuffer2(This,pvBuffer)	\
    (This)->lpVtbl -> GetTseBuffer2(This,pvBuffer)

#define ITAsm_WriteTseFile(This,bstrTseFile,pReturn)	\
    (This)->lpVtbl -> WriteTseFile(This,bstrTseFile,pReturn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_BuildFile_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [in] */ BSTR bstrTasmFile,
    /* [retval][out] */ long __RPC_FAR *pnErrors);


void __RPC_STUB ITAsm_BuildFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_BuildText_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [in] */ BSTR bstrTasmText,
    /* [retval][out] */ long __RPC_FAR *pnErrors);


void __RPC_STUB ITAsm_BuildText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_GetSyntaxErrors_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pSyntaxs);


void __RPC_STUB ITAsm_GetSyntaxErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_GetTseBuffer_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [in] */ LPDISPATCH pBBuffer);


void __RPC_STUB ITAsm_GetTseBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_GetTseBuffer2_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvBuffer);


void __RPC_STUB ITAsm_GetTseBuffer2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAsm_WriteTseFile_Proxy( 
    ITAsm __RPC_FAR * This,
    /* [in] */ BSTR bstrTseFile,
    /* [retval][out] */ long __RPC_FAR *pReturn);


void __RPC_STUB ITAsm_WriteTseFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITAsm_INTERFACE_DEFINED__ */


#ifndef __ISyntaxs_INTERFACE_DEFINED__
#define __ISyntaxs_INTERFACE_DEFINED__

/* interface ISyntaxs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISyntaxs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8F62F940-98A1-4305-95C2-00195D08C838")
    ISyntaxs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            long nIndex,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyntaxsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISyntaxs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISyntaxs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISyntaxs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISyntaxs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISyntaxs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISyntaxs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISyntaxs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ISyntaxs __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ISyntaxs __RPC_FAR * This,
            long nIndex,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal);
        
        END_INTERFACE
    } ISyntaxsVtbl;

    interface ISyntaxs
    {
        CONST_VTBL struct ISyntaxsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyntaxs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISyntaxs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISyntaxs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISyntaxs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISyntaxs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISyntaxs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISyntaxs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISyntaxs_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ISyntaxs_get_Item(This,nIndex,pVal)	\
    (This)->lpVtbl -> get_Item(This,nIndex,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISyntaxs_get_Count_Proxy( 
    ISyntaxs __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISyntaxs_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISyntaxs_get_Item_Proxy( 
    ISyntaxs __RPC_FAR * This,
    long nIndex,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal);


void __RPC_STUB ISyntaxs_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyntaxs_INTERFACE_DEFINED__ */


#ifndef __ISyntax_INTERFACE_DEFINED__
#define __ISyntax_INTERFACE_DEFINED__

/* interface ISyntax */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISyntax;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("180ECB97-D23A-44BE-A5DC-6F0E0B8ECD5A")
    ISyntax : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SyntaxMsg( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyntaxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISyntax __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISyntax __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISyntax __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISyntax __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISyntax __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISyntax __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISyntax __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SyntaxMsg )( 
            ISyntax __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LineIndex )( 
            ISyntax __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ISyntaxVtbl;

    interface ISyntax
    {
        CONST_VTBL struct ISyntaxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyntax_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISyntax_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISyntax_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISyntax_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISyntax_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISyntax_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISyntax_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISyntax_get_SyntaxMsg(This,pVal)	\
    (This)->lpVtbl -> get_SyntaxMsg(This,pVal)

#define ISyntax_get_LineIndex(This,pVal)	\
    (This)->lpVtbl -> get_LineIndex(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISyntax_get_SyntaxMsg_Proxy( 
    ISyntax __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISyntax_get_SyntaxMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISyntax_get_LineIndex_Proxy( 
    ISyntax __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISyntax_get_LineIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyntax_INTERFACE_DEFINED__ */



#ifndef __TScript_LIBRARY_DEFINED__
#define __TScript_LIBRARY_DEFINED__

/* library TScript */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TScript;

EXTERN_C const CLSID CLSID_TScript;

#ifdef __cplusplus

class DECLSPEC_UUID("571AB2FA-E416-4BAB-AE6C-9AA47B876CCA")
TScript;
#endif

EXTERN_C const CLSID CLSID_TAsm;

#ifdef __cplusplus

class DECLSPEC_UUID("819B8F74-C1BA-4312-8035-DE9673525B32")
TAsm;
#endif

EXTERN_C const CLSID CLSID_Syntaxs;

#ifdef __cplusplus

class DECLSPEC_UUID("3BDB6CF1-AEFA-4927-841F-D628B15AE326")
Syntaxs;
#endif

EXTERN_C const CLSID CLSID_Syntax;

#ifdef __cplusplus

class DECLSPEC_UUID("FC9784BD-ED09-4CF5-AE2E-780169723B46")
Syntax;
#endif
#endif /* __TScript_LIBRARY_DEFINED__ */

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
