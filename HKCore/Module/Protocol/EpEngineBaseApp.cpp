// D:\WorkPM\Source\Protocol\Module\Engine\EpEngineBaseApp.cpp : 实现文件
//

#include "stdafx.h"
#include "EpEngineBaseApp.h"

// CEpEngineBaseApp

CEpNode *g_pPpEndNode = NULL;


CEpEngineBaseApp::CEpEngineBaseApp()
{
	m_pPpEngineDataMngrCntr = NULL;
	m_bProtocolSpy = TRUE;

	m_bExitEngineThread = FALSE;
}

CEpEngineBaseApp::~CEpEngineBaseApp()
{

}

//新建设备
CEpEngineData* CEpEngineBaseApp::Create(CEpProtocolBase *pProtocol, CEpDevice *pDevice)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	//新建设备、新建模板，添加到建立设备管理对象中
	CEpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Create(pProtocol, pDevice);

	//引擎数据有效，启动线程
	if (pEngineData->IsEngineDataValid())
	{
		CEpEngineThread *pThread = CEpEngineThread::CreateEngineThread(pEngineData);
	}
	else
	{

	}

	return pEngineData;
}

BOOL CEpEngineBaseApp::LoadEngineData(CEpEngineData*pEngineData, const CString &strPpTemplateFile, const CString &strDeviceFile)
{
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return FALSE;
	}

//	pEngineData->LoadEngineFile(strPpTemplateFile, strDeviceFile);

	//引擎数据有效，启动线程
	if (pEngineData->IsEngineDataValid())
	{
		CEpEngineThread *pThread = CEpEngineThread::CreateEngineThread(pEngineData);
		pEngineData->m_pEngineThread = pThread;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CEpEngineBaseApp::ReleaseEngineData(CEpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	CEpEngineData *p = m_pPpEngineDataMngrCntr->Find(pData->m_pDevice);
	ASSERT (p != NULL);
	pData->ExitEngineThread();
}

BOOL CEpEngineBaseApp::HasEngineDataDeleted(CEpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = ((CExBaseList*)m_pPpEngineDataMngrCntr)->Find((CExBaseObject*)pData);

	return (pos == NULL);
}

void CEpEngineBaseApp::DeleteEngineData(CEpEngineData *pData)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = ((CExBaseList*)m_pPpEngineDataMngrCntr)->Find((CExBaseObject*)pData);

	if (pos != NULL)
	{
		m_pPpEngineDataMngrCntr->RemoveAt(pos);
		delete pData;
	}
}

void CEpEngineBaseApp::ReleaseEngineDataMngrCntr()
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = NULL;
	CEpEngineData *pData = NULL;
	pos = m_pPpEngineDataMngrCntr->GetHeadPosition();
	
	while (pos != NULL)
	{
		pData = (CEpEngineData*)m_pPpEngineDataMngrCntr->GetNext(pos);
		ReleaseEngineData(pData);
	}

}

//初始化
long CEpEngineBaseApp::InitPpBaseApp()
{
	CEpCmmChannelCreateMngr::Create();

	g_pPpEndNode = new CEpNode(EPNODE_TYPE_PRODUCE);
	g_pPpEndNode->m_strID = g_strProcedureEndNodeID;
	g_pPpEndNode->m_strName = g_pPpEndNode->m_strID;

	m_pPpEngineDataMngrCntr = new CEpEngineDataMngrCntr();

	return 0;
}

long CEpEngineBaseApp::ExitPpBaseApp()
{
#ifdef _debug_spy
	CString strDebugSpyFile;
	strDebugSpyFile = _P_GetBinPath();
	strDebugSpyFile += L"PpEngineThreadSpy.txt";
	m_pDebugSpy->WriteDebugSpy(strDebugSpyFile);

	strDebugSpyFile = _P_GetBinPath();
	strDebugSpyFile += L"PpEngineRunSpy.txt";
	m_pRunDebugSpy->WriteDebugSpy(strDebugSpyFile);
#endif

	CEpCmmChannelCreateMngr::Release();

	if (m_pPpEngineDataMngrCntr != NULL)
	{
		m_pPpEngineDataMngrCntr->RemoveAll();
		delete m_pPpEngineDataMngrCntr;
		m_pPpEngineDataMngrCntr = NULL;
	}

	return 0;
}

long CEpEngineBaseApp::ExitEngineThread()
{
	m_bExitEngineThread = TRUE;
	ReleaseEngineDataMngrCntr();
	return 0;
}

BOOL CEpEngineBaseApp::IsAllEngineThreadExit()
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	POS pos = NULL;
	CEpEngineData *pData = NULL;
	pos = m_pPpEngineDataMngrCntr->GetHeadPosition();
	BOOL bHasAllExit = TRUE;

	while (pos != NULL)
	{
		pData = (CEpEngineData*)m_pPpEngineDataMngrCntr->GetNext(pos);
		
		if (!pData->IsThreadExit())
		{
			bHasAllExit = FALSE;
			break;
		}
	}

// 	if (!bHasAllExit)
// 	{
// 		return bHasAllExit;
// 	}
//
//	bHasAllExit = CEpCmmChannelCreateMngr::HasAllServerExit();

	return bHasAllExit;
}



CEpEngineThread* CEpEngineBaseApp::FindEngineThread(CEpProtocolBase *pTemplate)
{
	CEpEngineThread *pThread = NULL;
	CEpEngineData *pEngineData = m_pPpEngineDataMngrCntr->Find(pTemplate);
	ASSERT (pEngineData != NULL);

	if (pEngineData != NULL)
	{
		pThread = (CEpEngineThread*)pEngineData->m_pEngineThread;
	}

	return pThread;
}

