// D:/WorkPM/Source/Protocol/Module/Engine/PpEngineBaseApp.cpp : 实现文件
//

#include "stdafx.h"
#include "PpEngineBaseApp.h"

#include "PpScriptGlobal.h"
#include "../XLanguageResourcePp.h"
#include "../../../Module/System/TickCount32.h"
// CPpEngineBaseApp

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _PSX_IDE_QT_
#include "QT/PpEngineThread.h"
#else
#include "VC/PpEngineThread.h"
#endif


CPpEngineBaseApp *g_pTheEngineApp;

CPpEngineBaseApp::CPpEngineBaseApp()
{
	CXPpPkgLogTool::Create();
	m_pPpEngineDataMngrCntr = NULL;
	SetProtocolSpy(TRUE);

#ifdef _debug_spy
	m_pDebugSpy = new CDebugSpy();
	m_pRunDebugSpy = new CDebugSpy();
#endif

	m_bExitEngineThread = FALSE;
	m_bDebugMode = FALSE;
	g_pTheEngineApp = this;
	m_pPpEngineConfig = NULL;
}

CPpEngineBaseApp::~CPpEngineBaseApp()
{
	CXPpPkgLogTool::Release();
#ifdef _debug_spy
	delete m_pDebugSpy;
	delete m_pRunDebugSpy;
#endif

	delete m_pPpEngineConfig;
	m_pPpEngineConfig = NULL;
}

CPpEngineData* CPpEngineBaseApp::FindEngineData(const CString &strID)
{
	CPpEngineData *pFind = (CPpEngineData*)m_pPpEngineDataMngrCntr->FindByID(strID);

	return pFind;
}

//新建设备
CPpEngineData* CPpEngineBaseApp::Create(const CString &strPpTemplateFile, const CString &strDeviceFile, BOOL bRunEngine)
{
	CTickCount32 oTickCount32;

	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create Engine:[%s] [%s]"), strPpTemplateFile.GetString(), strDeviceFile.GetString());

	//新建设备、新建模板，添加到建立设备管理对象中
	CPpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Create(strPpTemplateFile, strDeviceFile);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PpEngineDataMngrCntr->Create=%d"), oTickCount32.GetTickCountLong(TRUE));

	if (pEngineData != NULL && pEngineData->IsEngineDataValid() && bRunEngine)
	{
	//引擎数据有效，启动线程
		CPpEngineThreadBase *pThread = CPpEngineThread::CreateEngineThread(pEngineData);
		pEngineData->m_pEngineThread = pThread;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreateEngineThread-=%d"), oTickCount32.GetTickCountLong(TRUE));

	return pEngineData;
}

BOOL CPpEngineBaseApp::BeginThreadEngine(CPpEngineData *pEngineData)
{
	if (pEngineData->m_pEngineThread == NULL)
	{
		if (pEngineData->IsEngineDataValid())
		{
			CPpEngineThreadBase *pThread = CPpEngineThread::CreateEngineThread(pEngineData);
			pEngineData->m_pEngineThread = pThread;
			return TRUE;
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                      , g_sLangTxt_EditDevDataModel.GetString() /*_T("[%s] 引擎数据无效，请编辑设备数据模型")*/
                      , pEngineData->m_pTemplate->m_strName.GetString());
			return FALSE;
		}
	}

	return TRUE;
}

//退出线程，不关闭数据
BOOL CPpEngineBaseApp::ExitThreadEngine(CPpEngineData *pEngineData)
{
	if (pEngineData->m_pEngineThread != NULL)
	{
		CPpEngineThreadBase *pThread = (CPpEngineThreadBase *)pEngineData->m_pEngineThread;
		pThread->SetDeleteEngineDataInExit(FALSE);
		pEngineData->ExitEngineThread();
		return TRUE;
	}

	return TRUE;
}

//新建设备
CPpEngineData* CPpEngineBaseApp::Create()
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	//新建设备、新建模板，添加到建立设备管理对象中
	CPpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Create(_T(""), _T(""));

// 	if (pEngineData == NULL||!pEngineData->IsEngineDataValid())
// 	{
// 		return NULL;
// 	}
// 
// 	//引擎数据有效，启动线程
// 	if (pEngineData->IsEngineDataValid())
// 	{
// 		CPpEngineThread *pThread = CPpEngineThread::CreateEngineThread(pEngineData);
// 		pEngineData->m_pEngineThread = pThread;
// 	}
// 	else
// 	{
// 
// 	}

	return pEngineData;
}

BOOL CPpEngineBaseApp::LoadEngineData(CPpEngineData*pEngineData, const CString &strPpTemplateFile, const CString &strDeviceFile)
{
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return FALSE;
	}

	pEngineData->LoadEngineFile(strPpTemplateFile, strDeviceFile);

	//引擎数据有效，启动线程
	if (pEngineData->IsEngineDataValid())
	{
		CPpEngineThreadBase *pThread = CPpEngineThread::CreateEngineThread(pEngineData);
		pEngineData->m_pEngineThread = pThread;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPpEngineBaseApp::ReleaseEngineData(CPpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	CPpEngineData *p = m_pPpEngineDataMngrCntr->Find(pData->m_pPpDeviceRef);
	ASSERT (p != NULL);
	
	return pData->ExitEngineThread();
}

BOOL CPpEngineBaseApp::HasEngineDataDeleted(CPpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = ((CExBaseList*)m_pPpEngineDataMngrCntr)->Find((CExBaseObject*)pData);

	return (pos == NULL);
}

void CPpEngineBaseApp::DeleteEngineData(CPpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

    CString strDeviceID = pData->m_strDeviceID;
	POS pos = m_pPpEngineDataMngrCntr->CExBaseList::Find((CExBaseObject*)pData);

	if (pos != NULL)
	{
		m_pPpEngineDataMngrCntr->RemoveAt(pos);
		
#ifndef _PSX_IDE_QT_
        if (pData->m_pRefTreeCtrl != NULL)
		{
			pData->m_pRefTreeCtrl->DeleteItem((HTREEITEM)pData->m_dwItemData);
		}
#endif

		if (pData->m_pEngineThread != NULL)
		{
			((CPpEngineThreadBase*)pData->m_pEngineThread)->m_pEngineData = NULL;
		}

		delete pData;
		pData = NULL;

        OnEngineDataDeleted(strDeviceID);
	}
}

//2020-11-24  lijunqing
void CPpEngineBaseApp::OnEngineDataDeleted(const CString &strDeviceID)
{

}

long CPpEngineBaseApp::FindDeviceIndex(CPpEngineData *pData)
{
	return m_pPpEngineDataMngrCntr->FindIndex(pData);
}

void CPpEngineBaseApp::ReleaseEngineDataMngrCntr()
{
// 	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);
	if (m_pPpEngineDataMngrCntr == NULL)
	{
		return;
	}

	POS pos = NULL;
	CPpEngineData *pData = NULL;
	pos = m_pPpEngineDataMngrCntr->GetHeadPosition();
	
	while (pos != NULL)
	{
		pData = (CPpEngineData*)m_pPpEngineDataMngrCntr->GetNext(pos);
		ReleaseEngineData(pData);
	}
}

//初始化
long CPpEngineBaseApp::InitPpBaseApp()
{
	m_pPpEngineConfig = new CPpEngineConfig();
	CCmmChannelCreateMngr::Create();

	CPpDevBaseApp::InitPpBaseApp();

	m_pPpEngineDataMngrCntr = new CPpEngineDataMngrCntr();

#ifndef _PSX_QT_LINUX_  //zhouhj 2025.3.6 调试使用
	CXPpPkgLogTool::CreateLogWriteFile();
#endif

	return 0;
}

long CPpEngineBaseApp::ExitPpBaseApp()
{
	ExitAllEngineThread();
	WaitExitAllEngineThread();

#ifdef _debug_spy
	CString strDebugSpyFile;
	strDebugSpyFile = _P_GetBinPath();
	strDebugSpyFile += L"PpEngineThreadSpy.txt";
	m_pDebugSpy->WriteDebugSpy(strDebugSpyFile);

	strDebugSpyFile = _P_GetBinPath();
	strDebugSpyFile += L"PpEngineRunSpy.txt";
	m_pRunDebugSpy->WriteDebugSpy(strDebugSpyFile);
#endif

	CPpDevBaseApp::ExitPpBaseApp();

	CCmmChannelCreateMngr::Release();

	if (m_pPpEngineDataMngrCntr != NULL)
	{
		m_pPpEngineDataMngrCntr->RemoveAll();
		delete m_pPpEngineDataMngrCntr;
		m_pPpEngineDataMngrCntr = NULL;
	}

	return 0;
}

long CPpEngineBaseApp::ExitEngineThread()
{
	m_bExitEngineThread = TRUE;
	ReleaseEngineDataMngrCntr();
	return 0;
}

BOOL CPpEngineBaseApp::IsAllEngineThreadExit()
{
	if (m_pPpEngineDataMngrCntr == NULL)
	{
		return TRUE;
	}

	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = NULL;
	CPpEngineData *pData = NULL;
	pos = m_pPpEngineDataMngrCntr->GetHeadPosition();
	BOOL bHasAllExit = TRUE;

	while (pos != NULL)
	{
		pData = (CPpEngineData*)m_pPpEngineDataMngrCntr->GetNext(pos);
		
		if (!pData->IsThreadExit())
		{
			bHasAllExit = FALSE;
			break;
		}
	}

	if (bHasAllExit)
	{
		m_pPpEngineDataMngrCntr->DeleteAll();
	}

	return bHasAllExit;
}

void CPpEngineBaseApp::ScriptSetPkgLen(long nLen)
{
	ASSERT (FALSE);
#if 0
	CPpTemplate *pTmpl = (CPpTemplate*)m_pPpScript->GetAncestor(PPCLASSID_PPTEMPLATE);
	ASSERT (pTmpl != NULL);

	if (pTmpl == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ScriptCallError/*L"脚本函数SetPkgLen调用错误:对应的模板不存在"*/);
		return;
	}

	CPpEngineThread *pEngineThread = FindEngineThread(pTmpl);

	ASSERT (pEngineThread != NULL);

	if (pEngineThread != NULL)
	{
		pEngineThread->SetCurrPkgLen(nLen);
	}
#endif
}

CPpEngineThreadBase* CPpEngineBaseApp::FindEngineThread(CPpTemplate *pTemplate)
{
	CPpEngineThreadBase *pThread = NULL;
	CPpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Find(pTemplate);
	ASSERT (pEngineData != NULL);

	if (pEngineData != NULL)
	{
		pThread = (CPpEngineThreadBase*)pEngineData->m_pEngineThread;
	}

	return pThread;
}


void CPpEngineBaseApp::GetNomVarScript(CString &strNomVarScript)
{
	ASSERT (FALSE);
// 	CPpTemplate *pTemplate = (CPpTemplate*)m_pPpScript->GetAncestor(PPCLASSID_PPTEMPLATE);
// 	ASSERT (pTemplate != NULL);
// 
// 	if (pTemplate == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_ScriptCallError/*L"脚本函数SetPkgLen调用错误:对应的模板不存在"*/);
// 		return;
// 	}
// 
// 	CPpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Find(pTemplate);
// 	ASSERT (pEngineData != NULL);
// 
// 	if (pEngineData != NULL)
// 	{
// 		strNomVarScript = pEngineData->m_strNomVarsScript;
// 	}
}

void CPpEngineBaseApp::SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID)
{
	ASSERT (FALSE);
}
