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
	//2023-8-19  lijunqing 兼容各种通信模式
	//方式1：根据EngineMode创建
   	CMacroTestInterface *pMacroTest = In_GetMacroTest_EngineMode(strType, strProgID, strMacroFile, pTestApps);

	if (pMacroTest != NULL)
	{//根据EngineMode创建成功，则返回
		return pMacroTest;
	}


	//方式2：之前的模式创建
	CString strActiveMacroTestEngineProgID;

	//for debug   
	//此处总是使用当前Active的ProgID，是不合理的。
	//当使用COM接口调用时，测试仪由CreateTest指令指定，需要先修改当前Active的ProgID
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
	
    //2020-10-19  lijunqing  LINUX 只能是  "SttTestEngine"
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
	//因中低压配电盘，需要同时控制4台PI系列的装置进行试验，修改此处
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
	{//没有定义测试仪管理对象
		return NULL;
	}

	if (pTestApps->GetCount() == 0)
	{//没有定义测试仪管理对象
		return NULL;
	}

	CDataGroup *pTestApp = NULL;
	
	if (pTestApps->GetCount() == 1)
	{//只有一台测试仪
		pTestApp = (CDataGroup *)pTestApps->GetHead();
	}
	else
	{//查找测试仪的类型
		pTestApp = pTestApps->FindByDataType(strType);
	}

	if (pTestApp == NULL)
	{//没有找到当前类型的测试仪
		return NULL;
	}

	CString strEngineMode, strEngineProgID;
	pTestApp->GetDataValue(STT_CMD_PARA_EngineMode  , strEngineMode);
	pTestApp->GetDataValue(STT_CMD_PARA_EngineProgID, strEngineProgID);

	if (strEngineMode == STT_CMD_PARA_EngineMode_STT || strEngineProgID == STT_CMD_PARA_EngineMode_STT)
	{//STT模式
#ifdef _USE_SMARTTEST_INTERFACE_STT_
		return m_pSttMacroTestCreator->GetMacroTest(strType, strEngineProgID, strMacroFile, pTestApps);
#else
		return NULL;
#endif
	}

	if (strEngineMode == STT_CMD_PARA_EngineMode_MQTT || strEngineProgID == STT_CMD_PARA_EngineMode_MQTT)
	{//MQTT模式
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

	//2020-10-19  lijunqing  LINUX 只能是  "SttTestEngine"
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
	//因中低压配电盘，需要同时控制4台PI系列的装置进行试验，修改此处
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
