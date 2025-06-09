#include "stdafx.h"
#include"SttSmartTestSvrFactory.h"

#include "SttSmartTestCom_Flow.h"
#include "SttSmartTestMqttBase.h"

CSttSmartTestSvrFactory* CSttSmartTestSvrFactory::g_pSttSmartTestSvrFactory = NULL;
long CSttSmartTestSvrFactory::g_nSttSmartTestSvrFactory = 0;

CSttSmartTestSvrFactory::CSttSmartTestSvrFactory()
{

}

CSttSmartTestSvrFactory::~CSttSmartTestSvrFactory(void)
{

}

CSttSmartTestSvrFactory* CSttSmartTestSvrFactory::Create()
{
	g_nSttSmartTestSvrFactory++;

	if (g_nSttSmartTestSvrFactory == 1)
	{
		g_pSttSmartTestSvrFactory = new CSttSmartTestSvrFactory();
	}

	return g_pSttSmartTestSvrFactory;
}

void CSttSmartTestSvrFactory::Release()
{
	g_nSttSmartTestSvrFactory--;

	if (g_nSttSmartTestSvrFactory == 0)
	{
		delete g_pSttSmartTestSvrFactory;
		g_pSttSmartTestSvrFactory = NULL;
	}
}

CXSttSmartTestXInterface* CSttSmartTestSvrFactory::CreateSttSmartTestSvr(const CString &strSmratTestSvr, const CString &strID)
{
	CXSttSmartTestXInterface* pInterface = (CXSttSmartTestXInterface *)CSttSmartTestSvrFactory::g_pSttSmartTestSvrFactory->FindByID(strID);

	if (pInterface != NULL)
	{
		return pInterface;
	}

	if (strSmratTestSvr == SmartTestSvr_Com)
	{
		CSttSmartTestCom *pNew = CSttSmartTestCom::CreateSmartTest();
		return pNew;
	}
	else if(strSmratTestSvr == SmartTestSvr_Com_Flow)
	{
		CSttSmartTestCom_Flow *pNew = CSttSmartTestCom_Flow::CreateSmartTest();
		return pNew;
	}
	else if (strSmratTestSvr == SmartTestSvr_Mqtt)
	{
		CSttSmartTestMqttBase *pNew = CSttSmartTestMqttBase::CreateSmartTest();
		return pNew;
	}
	else if (strSmratTestSvr == SmartTestSvr_Mqtt_Flow)
	{
		return NULL;//暂不支持这种模式
	}

	return NULL;
}

