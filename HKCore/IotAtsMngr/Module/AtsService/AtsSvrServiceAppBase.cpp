//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "AtsSvrServiceAppBase.h"
#include "../SttMqttClientEngineConfig.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"
#include "../../../Module/BaseClass/XDbBaseLib.h"
#include "../Iot_AtsMngrDB/Iot_AtsMngrGlobal.h"
#include "../../../Module/TestMacro/TestMacrosFileMngr.h"

CAtsSvrServiceAppBase::CAtsSvrServiceAppBase()
{
	m_pIotBenchs = NULL;
}

CAtsSvrServiceAppBase::~CAtsSvrServiceAppBase()
{
	if (m_pIotBenchs != NULL)
	{
		delete m_pIotBenchs;
		m_pIotBenchs = NULL;
	}
}

void CAtsSvrServiceAppBase::InitAtsSvrServiceApp()
{
	CAtsServiceXmlRWKeys::Create();
	CIot_AtsMngrXmlRWKeys::Create();

	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CSttMqttClientEngineConfig::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CXFileHttpClient::InitXFileHttpClient();

	CTestMacroXmlRWKeys::Create();
	CTestMacrosFileMngr::Create(TRUE);
	CGbXMLKeys::CreatetGbXMLkeys();
	CGbDataTypeMngr::Create(FALSE);
	CScriptTextMngrGlobalPool::Create();
	CGbParaTypeMngr::Create();

	CSttOutInterfaceMqttClient::Create();

	g_strReportFilePath = _P_GetInstallPath();
	g_strReportFilePath += _T("WorkSpace/");
}

void CAtsSvrServiceAppBase::ExitAtsSvrServiceApp()
{
	CCfgDataMngrXmlRWKeys::Release();
	CSttMqttClientEngineConfig::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();
	CAtsServiceXmlRWKeys::Release();
	CGbDataTypeMngr::Release();
	CGbXMLKeys::Release();
	CTestMacroXmlRWKeys::Release();
	CTestMacrosFileMngr::Release();
	CScriptTextMngrGlobalPool::Release();
	CGbParaTypeMngr::Release();

	CSttOutInterfaceMqttClient::Release();
}

CAtsSvrServiceBase* CAtsSvrServiceAppBase::XGetAtsSvrService()
{
	return (CAtsSvrServiceBase*)GetHead();
}

CAtsSvrServiceBase* CAtsSvrServiceAppBase::XGetAtsSvrService(const CString &strSN)
{
	return (CAtsSvrServiceBase*)FindByID(strSN);
}

CAtsSvrServiceBase* CAtsSvrServiceAppBase::XGetAtsSvrService(long nIndex)
{
	return (CAtsSvrServiceBase*)GetAtIndex(nIndex);
}

CAtsSvrServiceBase* CAtsSvrServiceAppBase::NewAtsSvrService()
{
	return new CAtsSvrServiceBase();
}

//////////////////////////////////////////////////////////////////////////
//
void CAtsSvrServiceAppBase::InitAtsSvrService()
{
	CAtsSvrServiceBase *pNew = NewAtsSvrService();
	pNew->SetBenchsRef(m_pIotBenchs);
	pNew->InitAtsSvrService();
	AddNewChild(pNew);
}

void CAtsSvrServiceAppBase::InitAtsSvrService(const CString &strFile)
{
	CAtsSvrServiceBase *pNew = NewAtsSvrService();
	pNew->SetBenchsRef(m_pIotBenchs);
	AddNewChild(pNew);
	pNew->InitAtsSvrService(strFile);
}

void CAtsSvrServiceAppBase::SaveAtsSvrService()
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CAtsSvrServiceBase *pService = (CAtsSvrServiceBase *)GetNext(pos);
		pService->SaveAtsSvrService();
	}
}

CXSttSmartTestXInterface* CAtsSvrServiceAppBase::XFindSmartTestXInterface(const CString &strDeviceSN)
{
	POS pos = GetHeadPosition();
	CAtsSvrServiceBase *p = NULL;
	CXSttSmartTestXInterface *pFind = NULL;

	while (pos != NULL)
	{
		p = (CAtsSvrServiceBase *)GetNext(pos);
		pFind = p->FindSmartTestXInterface(strDeviceSN);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

