#include "StdAfx.h"
#include "GbScript_GlobalDefine.h"

#include "../GbItemBase.h"
#include "../Device.h"

#include "../../XLanguageResourceAts.h"
extern long g_nLog_TestControl_Msg;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//_CGbScriptGlobalDefine


long _CGbScriptGlobalDefine::g_nGbScriptGlobalDefineRef = 0;
_CGbScriptGlobalDefine* _CGbScriptGlobalDefine::g_pGbScriptGlobalDefine = NULL;

void _CGbScriptGlobalDefine::SetScriptText(CScriptText *pScript)
{
	m_pScriptText = pScript;
	m_pDevice = (CDevice*)pScript->GetAncestor(GBCLASSID_DEVICE);
}

long _CGbScriptGlobalDefine::SelectGbItems(const char* pszPath, CGbItemBaseList &oListDest)
{
	oListDest.RemoveAll();
	CGbItemBase *pItem = (CGbItemBase*)m_pScriptText->GetParentGbItem();

	ASSERT ( pItem != NULL );

	if (pItem == NULL)
	{
		return -1;
	}

	//路径分隔字符替换
    //2020-12-21  lijunqing
    //CString strPath(pszPath);
    //TCHAR *p = (TCHAR*)strPath.GetString();
    char *p = (char*)pszPath;

	while (*p != 0)
	{
		if (*p == '/')
		{
            *p = '\\';
        }

		p++;
	}

    CString strPath(pszPath);

	//路径
	pItem->SelectItems(strPath, oListDest);

	return oListDest.GetCount();
}

CExBaseObject* _CGbScriptGlobalDefine::SelectGbItem()
{
	CGbItemBase *pItem = (CGbItemBase*)m_pScriptText->GetParentGbItem();
	return pItem;
}

CExBaseObject* _CGbScriptGlobalDefine::SelectGbItem_CommCmd()
{
	CGbItemBase *pItem = (CGbItemBase*)m_pScriptText->GetParentGbItem();
	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return NULL;
	}

	if (pItem->GetClassID() != GBCLASSID_COMMCMD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_FtcnCmdUse/*_T("CalSoeTime函数只能在通讯命令中使用")*/);
		return NULL;
	}
	else
	{
		return pItem;
	}
}

CExBaseObject* _CGbScriptGlobalDefine::SelectGbItem(const char* pszPath)
{
	m_pCurrSelectGbItem = NULL;
	m_pCurrSelectReport = NULL;

	CGbItemBase *pItem = (CGbItemBase*)m_pScriptText->GetParentGbItem();
	ASSERT ( pItem != NULL );

	if (pItem == NULL)
	{
		return NULL;
	}

	if (pszPath == NULL)
	{
		return pItem;
	}

	CGbItemBaseList oListDest;
	CString strPath(pszPath);
	pItem->SelectItems(strPath, oListDest);
	long nCount = oListDest.GetCount();

	if (nCount == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_PathNoItem.GetString() /*L"路径[%s]没有选择的项目"*/, strPath.GetString());
	}
	else if (nCount > 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  g_sLangTxt_PathSelItem.GetString()/*L"路径[%s]选择的项目不唯一"*/, strPath.GetString());
	}
	else
	{
		m_pCurrSelectGbItem = oListDest.GetHead();
	}

	oListDest.RemoveAll();
	return m_pCurrSelectGbItem;
}

CExBaseObject* _CGbScriptGlobalDefine::SelectGbItemReport(long nReportIndex)
{
	if (m_pCurrSelectGbItem == NULL)
	{
		return NULL;
	}

	CGbItemBase *pCurrItem = (CGbItemBase*)m_pCurrSelectGbItem;
	m_pCurrSelectReport = pCurrItem->GetReport(nReportIndex);

	return m_pCurrSelectReport;
}


//////////////////////////////////////////////////////////////////////////
//_CGbScriptGlobalDefineCreator

class _CGbScriptGlobalDefineCreator
{
public:
	_CGbScriptGlobalDefine *m_pGbScriptGlobalDefine;

	_CGbScriptGlobalDefineCreator()
	{
		m_pGbScriptGlobalDefine = _CGbScriptGlobalDefine::Create();
	}

	virtual ~_CGbScriptGlobalDefineCreator()
	{
		m_pGbScriptGlobalDefine->Release();
		m_pGbScriptGlobalDefine = NULL;
	}
};

_CGbScriptGlobalDefineCreator g_oGbScriptGlobalDefineCreator;



void GBS_LogTime_PcTime(PPCTIME pTm)
{
	if (g_nLog_TestControl_Msg == 0)
	{
		return;
	}

	CString strLog;
	strLog.Format(_T("%d-%d-%d %d:%d:%d.%d"), pTm->nYear, pTm->nMonth, pTm->nDay
		, pTm->nHour, pTm->nMinute, pTm->nSecond, pTm->nMilliseconds);
	CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
}

void GBS_LogTime_GpsTime(PGPSTIME pTm)
{
	if (g_nLog_TestControl_Msg == 0)
	{
		return;
	}

	CString strLog;
	strLog.Format(_T("%d-%d-%d %d:%d:%d.%d.%d"), pTm->nYear, pTm->nMonth, pTm->nDay
		, pTm->nHour, pTm->nMinute, pTm->nSecond, pTm->nMilliseconds, pTm->nMicroseconds);
	CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
}

