#include "StdAfx.h"
#include "XScript_XVM.h"
#include "GbScript_GlobalDefine.h"
#include "SmartTestXvm.h"
#include "../../../../Module/XVM/TScriptParser.h"
#include "../../../../Module/XVM/TAsmParser.h"
#include "../../../../Module/System/TickCount32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXScript_XVM::CXScript_XVM()
{
	m_bHasLoadScript = FALSE;
}

CXScript_XVM::~CXScript_XVM()
{

}


BOOL CXScript_XVM::InitScript()
{
	//InitScript(&m_oSmartTestXvm, NULL);

	//return TRUE;

	return xvm_InitScrpitEngine();
}

BOOL CXScript_XVM::InitScript(CSmartTestXvm *pXvm, CExBaseObject *pRefObject)
{
// 	pXvm->TS_Init();
// 	pXvm->RegisterHostAPIFuncs();
// 	pXvm->TS_StartScript();
// 	pXvm->SetRefData(pRefObject);
// 
// 	return TRUE;

	return xvm_InitScrpitEngine(pXvm, pRefObject);
}


BOOL CXScript_XVM::CloseScript()
{
// 	m_oSmartTestXvm.TS_ShutDown();
// 
// 	return TRUE;

// 	if (m_bHasLoadScript)
// 	{
// 		Gb_UnloadScript();
// 		m_bHasLoadScript = FALSE;
// 	}
	
	xvm_CloseScrpitEngine();
	m_bHasLoadScript = FALSE;
	
	return TRUE;
}


long CXScript_XVM::RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
{
// 	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);
// 
// 	long nErr = 0;
// 	CAutoSimpleLock oLock(&(_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oAutoCriticSection));
// 
// 	if (pScript == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	char *pszFuncName = NULL;
// 
// 	if (pScript->m_nIsRef)
// 	{
// 		CScriptText *pRef = pScript->GetRefScriptText();
// 
// 		if(pRef != NULL)
// 		{
// 			if (pRef->m_pszFuncName[0] != 0)
// 			{
// 				pszFuncName = pRef->m_pszFuncName;
// 			}
// 		}
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileNewest.GetString()/*_T("引用脚本【%s】不存在，请检查脚本库文件是否为最新版本")*/, pScript->m_strID.GetString());
// 		}
// 	}
// 	else
// 	{
// 		if (pScript->m_pszFuncName[0] != 0)
// 		{
// 			pszFuncName = pScript->m_pszFuncName;
// 		}
// 	}
// 
// 	if (pszFuncName == NULL)
// 	{
// 		return 1;
// 	}
// 
// 	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SetScriptText( pScript );
// 
// 	CSmartTestXvm *pXvm = &m_oSmartTestXvm;
// 
// 	if (bInitFilter)
// 	{
// 		GBS_FilterInit(pXvm);
// 	}
// 
// 	pXvm->TS_StartScript();
// 	pXvm->TS_CallScriptFunc ( pszFuncName );
// 	int dwReturnType = pXvm->m_Script._RetVal.iType;
// 	int dwReturn = pXvm->TS_GetReturnValueAsInt( );
// 
// 	//返回没有错误
// 	return 0;

	if (!m_bHasLoadScript)
	{
		CGuideBook *pGuideBook = (CGuideBook *)pScript->GetAncestor(GBCLASSID_GUIDEBOOK);
		Gb_LoadScript(pGuideBook);
		m_bHasLoadScript = TRUE;
	}
	return xvm_RunScript(pScript, strSyntaxError, bInitFilter);
}

long CXScript_XVM::CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
// 	if (pScript->m_strScriptText.GetLength() < 6)
// 	{
// 		return 1;
// 	}
// 
// 	if (Gb_BuildScript(pScript))
// 	{
// 		RunScript(pScript, strSyntaxError, FALSE);
// 	}
// 
// 	return 0;
	return xvm_CompileScript(pScript, strSyntaxError);
}


BOOL CXScript_XVM::Gb_BuildScript(CExBaseObject *pGbObj)
{
	return xvm_BuildScript(pGbObj);
}

BOOL CXScript_XVM::Gb_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer)
{
	return xvm_BuildScript(pGbObj, oBuffer);
}


BOOL CXScript_XVM::Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen)
{
	CSmartTestXvm *pSmartXvm = xvm_GetSmartTestXvm();
	return xvm_BuildScript(pSmartXvm, pszScript, nBufferLen);
}

BOOL CXScript_XVM::Gb_BuildScript(LPVOID pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer)
{
	CSmartTestXvm *pSmartXvm = xvm_GetSmartTestXvm();

	return Gb_BuildScript(pSmartXvm, pszScript, nBufferLen, oBuffer);
}


BOOL CXScript_XVM::Gb_BuildScript_GuideBook(CExBaseObject *pGuideBook)
{
	CGuideBook *p = (CGuideBook*)pGuideBook;

	long nLen = 0;
	char *pBuffer = NULL;
	CWSerializeBuff oBuffer;

	BOOL b = Gb_BuildScript(pGuideBook, oBuffer);

	if (b)
	{
		oBuffer.GetBuffer(&pBuffer, &nLen);
		p->SetXvmTasmBuffer((BYTE*)pBuffer, nLen);
	}

	return b;
}

BOOL CXScript_XVM::Gb_LoadScript(CExBaseObject *pGuideBook)
{
	CGuideBook *p = (CGuideBook*)pGuideBook;

	if (p->m_pXvmTasmBuffer == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] 没有发布"), p->m_strGbXmlFile.GetString());
		return FALSE;
	}

	CSmartTestXvm *pSmartXvm = xvm_GetSmartTestXvm();
	pSmartXvm->TS_LoadScriptFromBuffer((char *)p->m_pXvmTasmBuffer, p->m_nXvmLength);

	return TRUE;
}

BOOL CXScript_XVM::Gb_UnloadScript()
{
	CSmartTestXvm *pSmartXvm = xvm_GetSmartTestXvm();

	if (m_bHasLoadScript)
	{
		pSmartXvm->TS_UnloadScript();
		m_bHasLoadScript = FALSE;
	}

	return TRUE;
}
