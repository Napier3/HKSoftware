#include "stdafx.h"
#include "IotEdgeEngineBaseApp.h"
#include "IotEdgeEngineThread.h"

CIotEdgeEngineBaseApp::CIotEdgeEngineBaseApp()
{

}

CIotEdgeEngineBaseApp::~CIotEdgeEngineBaseApp()
{

}

void CIotEdgeEngineBaseApp::InitIotEdgeEngineBaseApp()
{

}

void CIotEdgeEngineBaseApp::ExitIotEdgeEngineBaseApp()
{

}

CIotEdgeEngineData* CIotEdgeEngineBaseApp::FindEngineData(const CString &strID)
{
	CIotEdgeEngineData *pFind = (CIotEdgeEngineData*)m_oIotEdgeEngineMngr.FindByID(strID);

	return pFind;
}

CIotEdgeEngineData* CIotEdgeEngineBaseApp::Create(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	CAutoSimpleLock oLock(&m_oEngineDataCriticSection);

	//新建设备、新建模板，添加到建立设备管理对象中
	CIotEdgeEngineData *pEngineData = m_oIotEdgeEngineMngr.Create(strPpTemplateFile, strDeviceFile,strDeviceID);

	if (pEngineData != NULL)
	{
		//引擎数据有效，启动线程
//  		CIotEdgeEngineThread *pThread = CIotEdgeEngineThread::CreateEngineThread(pEngineData);
//  		pEngineData->m_pEngineThread = pThread;
	}

	return pEngineData;
}