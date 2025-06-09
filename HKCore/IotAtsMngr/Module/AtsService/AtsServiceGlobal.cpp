//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsServiceGlobal.cpp

#include "stdafx.h"
#include "AtsServiceGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CAtsServiceXmlRWKeys

CAtsServiceXmlRWKeys* CAtsServiceXmlRWKeys::g_pXmlKeys = NULL;
long CAtsServiceXmlRWKeys::g_nATSVRRef = 0;


CAtsServiceXmlRWKeys::CAtsServiceXmlRWKeys()
{
	m_strCAtsSvrTestFlowsKey = L"TestFlows";
	m_strCAtsSvrTestFlowKey = L"TestFlow";
	m_strCAtsSvrDevicesKey = L"Devices";
	m_strCAtsSvrDeviceKey = L"Device";
	m_strCAtsSvrServiceKey = L"AtsService";
	m_strCAtsSvrTestBenchsKey = L"Benchs";
	m_strCAtsSvrTestBenchKey = L"Bench";
	m_strCAtsSvrTestAppsKey = L"TestApps";
	m_strCAtsSvrTestAppExKey = L"TestAppEx";
	m_strCAtsSvrRsTestAppRefKey = L"TestAppRef";
	m_strCAtsSvrTestResourcesKey = L"TestResources";
	m_strCAtsSvrTestResourceKey = L"TestResource";
	m_strCAtsSvrRsTestAppKey = L"TestApp";
	m_strCAtsSvrRsAllocDefMngrKey = L"RsAllocDefMngr";
	m_strCAtsSvrRsAllocDefKey = L"RsAllocDef";
	m_strCAtsSvrRsAllocParasKey = L"RsAllocParas";
	m_strDeviceTypeKey = L"DeviceType";
	m_strDeviceSNKey = L"DeviceSN";
	m_strMacroIDKey = L"MacroID";
	m_strBenchSNKey = L"BenchSN";
	m_strTypeKey = L"type";
	m_strSelfStartKey = L"SelfStart";
	m_strSnKey = L"sn";
	m_strAttrsKey = L"Attrs";
	m_strSvrModeKey = L"SvrMode";
	m_strIsServiceMngrKey = L"service-mngr";
	m_strUseTemplateSvrKey = L"use-template-svr";
	m_strSmartTestSvrKey = L"SmartTestSvr";
}

CAtsServiceXmlRWKeys::~CAtsServiceXmlRWKeys()
{
}

CAtsServiceXmlRWKeys* CAtsServiceXmlRWKeys::Create()
{
	g_nATSVRRef++;

	if (g_nATSVRRef == 1)
	{
		g_pXmlKeys = new CAtsServiceXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CAtsServiceXmlRWKeys::Release()
{
	g_nATSVRRef--;

	if (g_nATSVRRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CAtsServiceConstGlobal

long CAtsServiceConstGlobal::g_nGlobalRef = 0;
CAtsServiceConstGlobal* CAtsServiceConstGlobal::g_pGlobal = NULL;


CAtsServiceConstGlobal::CAtsServiceConstGlobal()
{

//����ȫ�ֳ�����������ʼ������������  InitVariableDataTypes()

}

CAtsServiceConstGlobal::~CAtsServiceConstGlobal()
{
}

CAtsServiceConstGlobal* CAtsServiceConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CAtsServiceConstGlobal();
	}

	return g_pGlobal;
}

void CAtsServiceConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;
