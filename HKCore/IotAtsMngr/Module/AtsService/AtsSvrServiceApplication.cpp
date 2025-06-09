//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "AtsSvrServiceApplication.h"
#include "../SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"
#include "../../../Module/BaseClass/XDbBaseLib.h"
#include "../Iot_AtsMngrDB/Iot_AtsMngrGlobal.h"

long CAtsSvrServiceApplication::g_nAtsSvrServiceApplicationRef = 0;
CAtsSvrServiceApplication* CAtsSvrServiceApplication::g_pAtsSvrServiceApplication = NULL;

CAtsSvrServiceApplication::CAtsSvrServiceApplication()
{
	m_pIotBenchs = NULL;
	CAtsServiceXmlRWKeys::Create();
	CIot_AtsMngrXmlRWKeys::Create();

	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CSttMqttClientEngineConfig::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CXFileHttpClient::InitXFileHttpClient();
	InitMySqlDB();
	SyncBenchs();
}

CAtsSvrServiceApplication::~CAtsSvrServiceApplication()
{
	if (m_pIotBenchs != NULL)
	{
		delete m_pIotBenchs;
		m_pIotBenchs = NULL;
	}

	CCfgDataMngrXmlRWKeys::Release();
	CSttMqttClientEngineConfig::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();
	CAtsServiceXmlRWKeys::Release();
}

CAtsSvrServiceApplication* CAtsSvrServiceApplication::Create()
{
	g_nAtsSvrServiceApplicationRef++;

	if (g_nAtsSvrServiceApplicationRef == 1)
	{
		g_pAtsSvrServiceApplication = new CAtsSvrServiceApplication();
		g_pAtsSvrServiceApplication->InitAtsSvrService();
	}

	return g_pAtsSvrServiceApplication;
}

void CAtsSvrServiceApplication::Release()
{
	g_nAtsSvrServiceApplicationRef--;

	if (g_nAtsSvrServiceApplicationRef == 0)
	{
		delete g_pAtsSvrServiceApplication;
		g_pAtsSvrServiceApplication = NULL;
	}
}

CAtsSvrServiceApplication* CAtsSvrServiceApplication::GetApplication()
{
	return g_pAtsSvrServiceApplication;
}

CAtsSvrService* CAtsSvrServiceApplication::GetAtsSvrService()
{
	return (CAtsSvrService*)g_pAtsSvrServiceApplication->GetHead();
}

CAtsSvrService* CAtsSvrServiceApplication::GetAtsSvrService(const CString &strSN)
{
	return (CAtsSvrService*)g_pAtsSvrServiceApplication->FindByID(strSN);
}

CAtsSvrService* CAtsSvrServiceApplication::GetAtsSvrService(long nIndex)
{
	return (CAtsSvrService*)g_pAtsSvrServiceApplication->GetAtIndex(nIndex);
}

CXSttSmartTestXInterface* CAtsSvrServiceApplication::FindSmartTestXInterface(const CString &strDeviceSN)
{
	return g_pAtsSvrServiceApplication->In_FindSmartTestXInterface(strDeviceSN);
}


//////////////////////////////////////////////////////////////////////////
//
BOOL CAtsSvrServiceApplication::SyncBenchs()
{
	if (m_pIotBenchs == NULL)
	{
		m_pIotBenchs = new CIot_Benchs();
	}

	m_pIotBenchs->DeleteAll();
	BOOL bRet = m_pIotBenchs->QueryAllBenchs(g_pTheMySqlApp);

	if (bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("同步测试台信息---成功！"));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("同步测试台信息---失败！"));
		delete m_pIotBenchs;
		m_pIotBenchs = NULL;
	}

	return bRet;
}

BOOL CAtsSvrServiceApplication::InitMySqlDB()
{
	CDBServerInfoBase oDBServerInfo;
	CSttMqttClientEngineConfig::GetMysqlServerDBName(oDBServerInfo.m_strDbName);//_T("tyh");//数据库名称
	oDBServerInfo.m_strUserName = _T("root");
	CSttMqttClientEngineConfig::GetMysqlServerPassword(oDBServerInfo.m_strPasswd);//_T("123456");
	CSttMqttClientEngineConfig::GetMysqlServerIP(oDBServerInfo.m_strHostIp);
	long nPort = 0;
	CSttMqttClientEngineConfig::GetMysqlServerPort(nPort);
	oDBServerInfo.m_iPort = nPort;
	CSttMqttClientEngineConfig::GetMysqlServerDBEncoding(oDBServerInfo.m_strEncoding);
	return g_pTheMySqlApp->InitMySqlDB(oDBServerInfo);
}

void CAtsSvrServiceApplication::InitAtsSvrService()
{
	CAtsSvrService *pNew = new CAtsSvrService();
	pNew->SetBenchsRef(m_pIotBenchs);
	pNew->InitAtsSvrService();
	AddNewChild(pNew);
}

void CAtsSvrServiceApplication::InitAtsSvrService(const CString &strFile)
{
	CAtsSvrService *pNew = new CAtsSvrService();
	pNew->SetBenchsRef(m_pIotBenchs);
	AddNewChild(pNew);
	pNew->InitAtsSvrService(strFile);
}

void CAtsSvrServiceApplication::SaveAtsSvrService()
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CAtsSvrService *pService = (CAtsSvrService *)GetNext(pos);
		pService->SaveAtsSvrService();
	}
}

CXSttSmartTestXInterface* CAtsSvrServiceApplication::In_FindSmartTestXInterface(const CString &strDeviceSN)
{
	POS pos = GetHeadPosition();
	CAtsSvrService *p = NULL;
	CXSttSmartTestXInterface *pFind = NULL;

	while (pos != NULL)
	{
		p = (CAtsSvrService *)GetNext(pos);
		pFind = p->FindSmartTestXInterface(strDeviceSN);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

