#include "StdAfx.h"
#include "GbScriptFunctions_xvm.h"
#include "GbScript_System.h"
#include "GbScript_Engine.h"
#include "GbScript_GuideBook.h"
#include "../GuideBook.h"

#include "SmartTestXvm.h"
#include "../../../../Module/XVM/TScriptParser.h"
#include "../../../../Module/XVM/TAsmParser.h"
#include "../../../../Module/System/TickCount32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern char g_pLuaReturnString[MAX_PATH];

CSmartTestXvm g_theSmartTestXvm;//先让编译没有语法错误

BOOL xvm_InitScrpitEngine()
{
	xvm_InitScrpitEngine(&g_theSmartTestXvm, NULL);

	return TRUE;
}

BOOL xvm_InitScrpitEngine(CSmartTestXvm *pXvm, CExBaseObject *pRefObject)
{
	pXvm->TS_Init();
	pXvm->RegisterHostAPIFuncs();
	pXvm->TS_StartScript();
	pXvm->SetRefData(pRefObject);

	return TRUE;
}

void xvm_CloseScrpitEngine(CSmartTestXvm *pXvm)
{
	pXvm->TS_ShutDown();
}

void xvm_CloseScrpitEngine()
{
	xvm_CloseScrpitEngine(&g_theSmartTestXvm);
}

CSmartTestXvm* xvm_GetSmartTestXvm(CExBaseObject *p)
{
	return &g_theSmartTestXvm;
}

long xvm_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
{
	ASSERT (_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine != NULL);

	long nErr = 0;

#ifndef _PSX_QT_LINUX_
	CAutoSimpleLock oLock(&(_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->m_oAutoCriticSection));
#endif

	if (pScript == NULL)
	{
		return 0;
	}

	char *pszFuncName = NULL;

	if (pScript->m_nIsRef)
	{
		CScriptText *pRef = pScript->GetRefScriptText();

		if(pRef != NULL)
		{
			if (pRef->m_pszFuncName[0] != 0)
			{
				pszFuncName = pRef->m_pszFuncName;
			}
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FileNewest.GetString()/*_T("引用脚本【%s】不存在，请检查脚本库文件是否为最新版本")*/, pScript->m_strID.GetString());
		}
	}
	else
	{
		if (pScript->m_pszFuncName[0] != 0)
		{
			pszFuncName = pScript->m_pszFuncName;
		}
	}

	if (pszFuncName == NULL)
	{
		return 0;
	}

	_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SetScriptText( pScript );

	CSmartTestXvm *pXvm = xvm_GetSmartTestXvm(pScript);

	if (bInitFilter)
	{
		GBS_FilterInit(pXvm);
	}

	pXvm->TS_StartScript();
	pXvm->TS_CallScriptFunc ( pszFuncName );
	int dwReturnType = pXvm->m_Script._RetVal.iType;
	int dwReturn = pXvm->TS_GetReturnValueAsInt( );

	//返回没有错误
	return 0;
}

BOOL xvm_BuildScript(CExBaseObject *pGbObj, CWSerializeBuff &oBuffer)
{
	//2020-06-02  lijunqing
	g_oGbXvmScriptBuilder.xvm_script_ResetBuffer();

	CTickCount32 oTickCount32;
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer"));

	//2020-06-02  lijunqing
	CStringSerializeBuffer *pBuffer = g_oGbXvmScriptBuilder.xvm_script_StringSerializeBuffer();
	CSmartTestXvm *pXvm = xvm_GetSmartTestXvm(pGbObj);

	pXvm->SerializeHostAPIFuncs(*pBuffer);
	long nScriptIndex = 0;
	const char *pszScript = NULL;

	if (Gb_IsScript(pGbObj))
	{
		//2020-06-02  lijunqing
		pszScript = g_oGbXvmScriptBuilder.xvm_script_SerializeScript(pGbObj, nScriptIndex);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer template"));
		//2020-06-02  lijunqing
		pszScript = g_oGbXvmScriptBuilder.xvm_script_SerializeScript(pGbObj, nScriptIndex);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer project"));
	}

	//2020-06-02  lijunqing
	long nBufferLen = g_oGbXvmScriptBuilder.xvm_script_GetBufferLength();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: Add all script to string buffer finish=%d"), nBufferLen);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: %d"), oTickCount32.GetTickCountLong());

	BOOL bRet = xvm_BuildScript(pXvm, pszScript, nBufferLen, oBuffer);

	return bRet;
}


BOOL xvm_BuildScript(CExBaseObject *pGbObj)
{
	CWSerializeBuff oBuffer;
	return xvm_BuildScript(pGbObj, oBuffer);
}

BOOL xvm_BuildScript(CSmartTestXvm *pXvm, const char *pszScript, long nBufferLen, CWSerializeBuff &oBuffer)
{
	CTScriptParser oTScriptParser;
	CTAsmParser oTasmParser;
	CTickCount32 oTickCount32;

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: parse script......"));

#ifdef GUIDEBOOK_DEV_MODE
	long nErrors = oTScriptParser.ParseText(pszScript, "GbDev");
#else
	long nErrors = oTScriptParser.ParseText(pszScript, "SmartTest");
#endif

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: parse script:[%d]"), oTickCount32.GetTickCountLong(TRUE));

	if (nErrors > 0)
	{
		CTSyntaxs *pSyntaxs = oTScriptParser.GetTSyntaxs();
		CString strSyntax;
		//pSyntax->GetSyntax(strSyntax);
		POS pos = pSyntaxs->GetHeadPosition();
		CTSyntax *pSyntax = NULL;

		while (pos != NULL)
		{
			strSyntax.Empty();
			pSyntax = (CTSyntax*)pSyntaxs->GetNext(pos);
			pSyntax->GetSyntax(strSyntax);
			CLogPrint::LogString(pSyntax, XLOGLEVEL_TRACE, strSyntax);
		}

		return FALSE;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: ParseAsm......"));
	oTScriptParser.ParseAsm(&oTasmParser);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: ParseAsm [%d]"), oTickCount32.GetTickCountLong(TRUE));
	oTasmParser.WriteToBuffer(oBuffer);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: WriteToBuffer [%d]"), oTickCount32.GetTickCountLong(TRUE));

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Build script: Load script......"));
	pXvm->TS_UnloadScript();
	int iErrorCode = pXvm->TS_LoadScriptFromBuffer(oBuffer);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Build script: Load script:%d"), oTickCount32.GetTickCountLong(TRUE));

	if ( iErrorCode != TS_LOAD_OK )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL xvm_BuildScript(CSmartTestXvm *pXvm, const char *pszScript, long nBufferLen)
{
	CWSerializeBuff oBuffer;
	return xvm_BuildScript(pXvm, pszScript, nBufferLen, oBuffer);
}

long xvm_CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
	if (pScript->m_strScriptText.GetLength() < 6)
	{
		return 1;
	}

	if (xvm_BuildScript(pScript))
	{
		xvm_RunScript(pScript, strSyntaxError, FALSE);
	}

	return 0;
}

BOOL xvm_BuildScript_GuideBook(CExBaseObject *pGuideBook)
{
	CGuideBook *p = (CGuideBook*)pGuideBook;

	long nLen = 0;
	char *pBuffer = NULL;
	CWSerializeBuff oBuffer;

	BOOL b = xvm_BuildScript(pGuideBook, oBuffer);

	if (b)
	{
		oBuffer.GetBuffer(&pBuffer, &nLen);
		p->SetXvmTasmBuffer((BYTE*)pBuffer, nLen);
	}

	return b;
}


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
extern CStringSerializeBuffer g_oBinaryBuffer;
CGbXvmScriptBuilder g_oGbXvmScriptBuilder;

CGbXvmScriptBuilder::CGbXvmScriptBuilder()
{

}
CGbXvmScriptBuilder::~CGbXvmScriptBuilder()
{

}

void CGbXvmScriptBuilder::SerializeScript(CExBaseObject *p, long &nScriptIndex)
{
	CScriptText *ppScript = (CScriptText*)p;

	if (ppScript->InitFuncName(nScriptIndex) == 0)
	{
		return;
	}

	g_oBinaryBuffer << ("func ");
	g_oBinaryBuffer << ppScript->m_pszFuncName;
	g_oBinaryBuffer << ("()\r\n{\r\n");

	g_oBinaryBuffer.Append_ASCII(ppScript->m_strScriptText);

	//if (ppScript->m_strScript.Find(_T("return ")) < 0)
	{
		g_oBinaryBuffer << ("\r\nreturn 1;");
	}

	g_oBinaryBuffer << ("\r\n}\r\n\r\n");
	nScriptIndex++;

	return;// g_oBinaryBuffer.GetBuffer();
}

void CGbXvmScriptBuilder::SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex)
{
	CScriptText *ppScript = (CScriptText*)p;

	if (ppScript->m_strScriptText.GetLength() < 6)
	{
		ppScript->m_pszFuncName[0] = 0;
		return;
	}

	sprintf(ppScript->m_pszFuncName, "func%d", nScriptIndex);

	nScriptIndex++;
}


void CGbXvmScriptBuilder::SerializeScript(CExBaseList *pList, long &nScriptIndex)
{
	if (! IsScriptParent(pList) )
	{
		return;
	}

	CXvmScriptBuilder::SerializeScript(pList, nScriptIndex);
}

void CGbXvmScriptBuilder::SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex)
{
	if (! IsScriptParent(pList) )
	{
		return;
	}

	CXvmScriptBuilder::SerializeScriptFunc(pList, nScriptIndex);
}

BOOL CGbXvmScriptBuilder::IsScriptParent(CExBaseList *pList)
{
	UINT nClassID = pList->GetClassID();

	if (GBCLASSID_CMD == nClassID
		|| RPTCLASSID_RPTREPORTMAP == nClassID
		|| DTMCLASSID_CSHORTDATAS == nClassID
		|| GBCLASSID_DLLCALL == nClassID)
	{
		return FALSE;
	}

	return TRUE;
}
