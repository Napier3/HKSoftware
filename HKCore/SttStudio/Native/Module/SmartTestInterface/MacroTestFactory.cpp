#include "stdafx.h"
#include"MacroTestFactory.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"

CString g_strActiveTestMacroProgID;

CMacroTestFactory* CMacroTestFactory::g_pMacroTestFactory = NULL;
long CMacroTestFactory::g_nMacroTestFactory = 0;

CMacroTestFactory::CMacroTestFactory()
{
#ifdef _USE_SMARTTEST_INTERFACE_COM_
	m_pVmMacroTestCreator = new CVmMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_STT_
	m_pSttMacroTestCreator  = new CSttMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	m_pMqttMacroTestCreator  = new CVmMqttMacroTestCreator;
#endif
}

CMacroTestFactory::~CMacroTestFactory(void)
{
#ifdef _USE_SMARTTEST_INTERFACE_COM_
	delete m_pVmMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_STT_
	delete m_pSttMacroTestCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	delete m_pMqttMacroTestCreator;
#endif

}

CMacroTestFactory* CMacroTestFactory::Create()
{
	g_nMacroTestFactory++;

	if (g_nMacroTestFactory == 1)
	{
		g_pMacroTestFactory = new CMacroTestFactory();
	}

	return g_pMacroTestFactory;
}

void CMacroTestFactory::Release()
{
	g_nMacroTestFactory--;

	if (g_nMacroTestFactory == 0)
	{
		delete g_pMacroTestFactory;
		g_pMacroTestFactory = NULL;
	}
}

void CMacroTestFactory::RemoveMacroTest(CMacroTestInterface *pMacroTestInterface)
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	g_pMacroTestFactory->m_pSttMacroTestCreator->Remove(pMacroTestInterface);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	g_pMacroTestFactory->m_pVmMacroTestCreator->Remove(pMacroTestInterface);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	g_pMacroTestFactory->m_pMqttMacroTestCreator->Remove(pMacroTestInterface);
#endif

}

CMacroTestEngineInterface* CMacroTestFactory::CreateMacroTestEngine(const CString &strMacroFile)
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	g_pMacroTestFactory->m_pSttMacroTestCreator->CreateMacroTestEngine(strMacroFile);
#endif
	
#ifdef _USE_SMARTTEST_INTERFACE_COM_
	g_pMacroTestFactory->m_pVmMacroTestCreator->CreateMacroTestEngine(strMacroFile);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	g_pMacroTestFactory->m_pMqttMacroTestCreator->CreateMacroTestEngine(strMacroFile);
#endif

	return NULL;
}

void CMacroTestFactory::ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara)
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	g_pMacroTestFactory->m_pSttMacroTestCreator->ExecuteMtCmd(strCmdID, strCmdPara);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	g_pMacroTestFactory->m_pVmMacroTestCreator->ExecuteMtCmd(strCmdID, strCmdPara);
#endif


#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	g_pMacroTestFactory->m_pMqttMacroTestCreator->ExecuteMtCmd(strCmdID, strCmdPara);
#endif

}


void CMacroTestFactory::ReleaseMacroTestEngine()
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	if (g_pMacroTestFactory != NULL)
	{
		g_pMacroTestFactory->m_pSttMacroTestCreator->ReleaseMacroTestEngine();
	}
#endif

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	if (g_pMacroTestFactory != NULL)
	{
		g_pMacroTestFactory->m_pVmMacroTestCreator->ReleaseMacroTestEngine();
	}
#endif


#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	if (g_pMacroTestFactory != NULL)
	{
		g_pMacroTestFactory->m_pMqttMacroTestCreator->ReleaseMacroTestEngine();
	}
#endif

}

void CMacroTestFactory::InitMacroTestEngineShowSpyWnd()
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	g_pMacroTestFactory->m_pSttMacroTestCreator->ShowSpyWnd();
#endif

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	g_pMacroTestFactory->m_pVmMacroTestCreator->ShowSpyWnd();
#endif


#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	g_pMacroTestFactory->m_pMqttMacroTestCreator->ShowSpyWnd();
#endif
}

CMacroTestInterface* CMacroTestFactory::GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	if (g_pMacroTestFactory == NULL)
	{
		return NULL;
	}

	return g_pMacroTestFactory->In_GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
}

void CMacroTestFactory::ConfigMacroTestEngine(const CString &strMacroFile, const CString &strIP)
{
	if (g_pMacroTestFactory == NULL)
	{
		return;
	}

	return g_pMacroTestFactory->In_ConfigMacroTestEngine(strMacroFile, strIP);
}

CMacroTestInterface* CMacroTestFactory::In_GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	//2023-8-19  lijunqing ���ݸ���ͨ��ģʽ
	//��ʽ1������EngineMode����
   	CMacroTestInterface *pMacroTest = In_GetMacroTest_EngineMode(strType, strProgID, strMacroFile, pTestApps);

	if (pMacroTest != NULL)
	{//����EngineMode�����ɹ����򷵻�
		return pMacroTest;
	}


	//��ʽ2��֮ǰ��ģʽ����
	CString strActiveMacroTestEngineProgID;

	//for debug   
	//�˴�����ʹ�õ�ǰActive��ProgID���ǲ�����ġ�
	//��ʹ��COM�ӿڵ���ʱ����������CreateTestָ��ָ������Ҫ���޸ĵ�ǰActive��ProgID
	//2022-6-26  lijunqing

	if (strType.GetLength() > 0)
	{
		strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, strType);
	}
	else
	{
		if (strProgID.GetLength() == 0)
		{
			strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, strType);
		}
		else
		{
			strActiveMacroTestEngineProgID = strProgID;
		}
	}
	
    //2020-10-19  lijunqing  LINUX ֻ����  "SttTestEngine"
#ifdef _PSX_QT_LINUX_
    return m_pSttMacroTestCreator->GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	CMacroTestInterface *pRet = m_pMqttMacroTestCreator->GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
	
	if (pRet != NULL)
	{
		return pRet;
	}
#endif


	//shaolei 20210515 
	//���е�ѹ����̣���Ҫͬʱ����4̨PIϵ�е�װ�ý������飬�޸Ĵ˴�
	if (strActiveMacroTestEngineProgID.Find(g_strSttTestClientEngine) >= 0)
	{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
		return m_pSttMacroTestCreator->GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
#endif
	}
	else
	{
#ifdef _USE_SMARTTEST_INTERFACE_COM_
		return m_pVmMacroTestCreator->GetMacroTest(strType, strProgID, strMacroFile, pTestApps);
#endif
	}

	return NULL;
}

CMacroTestInterface* CMacroTestFactory::In_GetMacroTest_EngineMode(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps)
{
	if (pTestApps == NULL)
	{//û�ж�������ǹ������
		return NULL;
	}

	if (pTestApps->GetCount() == 0)
	{//û�ж�������ǹ������
		return NULL;
	}

	CDataGroup *pTestApp = NULL;
	
	if (pTestApps->GetCount() == 1)
	{//ֻ��һ̨������
		pTestApp = (CDataGroup *)pTestApps->GetHead();
	}
	else
	{//���Ҳ����ǵ�����
		pTestApp = pTestApps->FindByDataType(strType);
	}

	if (pTestApp == NULL)
	{//û���ҵ���ǰ���͵Ĳ�����
		return NULL;
	}

	CString strEngineMode, strEngineProgID;
	pTestApp->GetDataValue(STT_CMD_PARA_EngineMode  , strEngineMode);
	pTestApp->GetDataValue(STT_CMD_PARA_EngineProgID, strEngineProgID);

	if (strEngineMode == STT_CMD_PARA_EngineMode_STT || strEngineProgID == STT_CMD_PARA_EngineMode_STT)
	{//STTģʽ
#ifdef _USE_SMARTTEST_INTERFACE_STT_
		return m_pSttMacroTestCreator->GetMacroTest(strType, strEngineProgID, strMacroFile, pTestApps);
#else
		return NULL;
#endif
	}

	if (strEngineMode == STT_CMD_PARA_EngineMode_MQTT || strEngineProgID == STT_CMD_PARA_EngineMode_MQTT)
	{//MQTTģʽ
#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
		return m_pMqttMacroTestCreator->GetMacroTest(strType, strEngineProgID, strMacroFile, pTestApps);
#else
		return NULL;
#endif
	}

	return NULL;
}

void CMacroTestFactory::In_ConfigMacroTestEngine(const CString &strMacroFile, const CString &strIP)
{
	CString strActiveMacroTestEngineProgID;
	strActiveMacroTestEngineProgID = CTestMacrosFileMngr::GetActiveMacroTestProgID(strMacroFile, _T(""));

	//2020-10-19  lijunqing  LINUX ֻ����  "SttTestEngine"
#ifdef _PSX_QT_LINUX_
    m_pSttMacroTestCreator->ConfigEngine(strActiveMacroTestEngineProgID, strIP);
    return;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	long nRet = m_pMqttMacroTestCreator->ConfigEngine(strActiveMacroTestEngineProgID, strIP);

	if (nRet)
	{
		return;
	}
#endif


	//shaolei 20210515 
	//���е�ѹ����̣���Ҫͬʱ����4̨PIϵ�е�װ�ý������飬�޸Ĵ˴�
	if (strActiveMacroTestEngineProgID.Find(g_strSttTestClientEngine) >= 0)
	{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
		m_pSttMacroTestCreator->ConfigEngine(strActiveMacroTestEngineProgID, strIP);
#endif
	}
	else
	{
#ifdef _USE_SMARTTEST_INTERFACE_COM_
		m_pVmMacroTestCreator->ConfigEngine(strActiveMacroTestEngineProgID, strIP);
#endif
	}
}


long CMacroTestFactory::AttatchLogWnd(unsigned long hWnd)
{
#ifdef _USE_SMARTTEST_INTERFACE_STT_
	g_pMacroTestFactory->m_pSttMacroTestCreator->AttatchLogWnd(hWnd);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_COM_
	g_pMacroTestFactory->m_pVmMacroTestCreator->AttatchLogWnd(hWnd);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_MQTT_
	g_pMacroTestFactory->m_pMqttMacroTestCreator->AttatchLogWnd(hWnd);
#endif

	return 0;
}


// 
// void mt_GetIP_ConfigString(CDvmDataset *pDataset, const CString &strIP)
// {
// 	pDataset->m_strID = _T("cmm-config");
// 	pDataset->m_strName = pDataset->m_strID;
// 	CDvmData *pData = pDataset->AddNewData();
// 	pData->m_strID = _T("ip-addr");
// 	pData->m_strName = pData->m_strID;
// 	pData->m_strValue = strIP;
// }
// 
// //2021-1-8
// void mt_GetIP_ConfigString(const CString &strIP, CString &strXml)
// {
// 	CDvmDataset oDataset;
// 	mt_GetIP_ConfigString(&oDataset, strIP);
// 	oDataset.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXml);
// }
// 
