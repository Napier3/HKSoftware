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

	//�½��豸���½�ģ�壬��ӵ������豸���������
	CIotEdgeEngineData *pEngineData = m_oIotEdgeEngineMngr.Create(strPpTemplateFile, strDeviceFile,strDeviceID);

	if (pEngineData != NULL)
	{
		//����������Ч�������߳�
//  		CIotEdgeEngineThread *pThread = CIotEdgeEngineThread::CreateEngineThread(pEngineData);
//  		pEngineData->m_pEngineThread = pThread;
	}

	return pEngineData;
}