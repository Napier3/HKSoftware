//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.cpp  CAtsSvrService


#include "stdafx.h"
#include "AtsSvrService.h"
#include "../SttMqttClientEngineConfig.h"
#include "../Iot_AtsMngrDB/Iot_Bench.h"

CAtsSvrService::CAtsSvrService()
{
	//初始化属性

	//初始化成员变量
	m_pBenchs = NULL;
	m_pTestResources = NULL;
	m_pAttrs = NULL;
	m_pTestFlows = NULL;

	m_pMqttClient = NULL;

	m_strSvrMode = ATSSVR_SVERVICE_MODE_BENCH;
	//m_pTestFlows = new CAtsSvrTestFlows();
	m_nIsServiceMngr = 0;
	m_pIotBenchsRef = NULL;
	m_nUseTemplateSvr = 0;
	m_pAtsSvr_TemplateService = NULL;
	m_strSmartTestSvr = _T("com");  //通过COM方式调用自动测试
}

CAtsSvrService::~CAtsSvrService()
{
	//delete m_pTestFlows;

	if (m_pAtsSvr_TemplateService != NULL)
	{
		delete m_pAtsSvr_TemplateService;
	}
}

long CAtsSvrService::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetAttibuteValue(pXmlKeys->m_strSvrModeKey, oNode, m_strSvrMode);
	xml_GetAttibuteValue(pXmlKeys->m_strIsServiceMngrKey, oNode, m_nIsServiceMngr);
	xml_GetAttibuteValue(pXmlKeys->m_strUseTemplateSvrKey, oNode, m_nUseTemplateSvr);
	xml_GetAttibuteValue(pXmlKeys->m_strSmartTestSvrKey, oNode, m_strSmartTestSvr);
	return 0;
}

long CAtsSvrService::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strSn);
	xml_SetAttributeValue(pXmlKeys->m_strSvrModeKey, oElement, m_strSvrMode);
	xml_SetAttributeValue(pXmlKeys->m_strIsServiceMngrKey, oElement, m_nIsServiceMngr);
	xml_SetAttributeValue(pXmlKeys->m_strUseTemplateSvrKey, oElement, m_nUseTemplateSvr);
	xml_SetAttributeValue(pXmlKeys->m_strSmartTestSvrKey, oElement, m_strSmartTestSvr);
	return 0;
}

long CAtsSvrService::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strSvrMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseTemplateSvr);
		BinarySerializeCalLen(oBinaryBuffer, m_strSmartTestSvr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_strSvrMode);
		BinarySerializeRead(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeRead(oBinaryBuffer, m_nUseTemplateSvr);
		BinarySerializeRead(oBinaryBuffer, m_strSmartTestSvr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_strSvrMode);
		BinarySerializeWrite(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeWrite(oBinaryBuffer, m_nUseTemplateSvr);
		BinarySerializeWrite(oBinaryBuffer, m_strSmartTestSvr);
	}
	return 0;
}

void CAtsSvrService::InitAfterRead()
{
	m_strSmartTestSvr.MakeLower();

	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ATSVRCLASSID_CATSSVRTESTBENCHS)
		{
			m_pBenchs = (CAtsSvrTestBenchs*)p;
		}
		else if (nClassID == ATSVRCLASSID_CATSSVRTESTRESOURCES)
		{
			m_pTestResources = (CAtsSvrTestResources*)p;
		}
		else if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			m_pAttrs = (CDvmDataset*)p;
		}
	}

	if (m_pBenchs == NULL)
	{
		m_pBenchs = (CAtsSvrTestBenchs*)AddNewChild(new CAtsSvrTestBenchs());
	}

	if (m_pTestResources == NULL)
	{
		m_pTestResources = (CAtsSvrTestResources*)AddNewChild(new CAtsSvrTestResources());
	}

	if (m_pAttrs == NULL)
	{
		m_pAttrs = (CDvmDataset*)AddNewChild(new CDvmDataset());
	}

	if (m_pTestFlows == NULL)
	{
		m_pTestFlows = (CAtsSvrTestFlows*)AddNewChild(new CAtsSvrTestFlows());
	}

	if (m_nUseTemplateSvr == 1)
	{
		m_pAtsSvr_TemplateService = new CAtsSvr_TemplateService();
	}
}

BOOL CAtsSvrService::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrService *p = (CAtsSvrService*)pObj;

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_strSvrMode != p->m_strSvrMode)
	{
		return FALSE;
	}

	if(m_nUseTemplateSvr != p->m_nUseTemplateSvr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrService::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrService *p = (CAtsSvrService*)pDest;

	p->m_strSn = m_strSn;
	p->m_strSvrMode = m_strSvrMode;
	p->m_nUseTemplateSvr = m_nUseTemplateSvr;
	return TRUE;
}

CBaseObject* CAtsSvrService::Clone()
{
	CAtsSvrService *p = new CAtsSvrService();
	Copy(p);
	return p;
}

BOOL CAtsSvrService::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRTESTBENCHS)
	{
		return TRUE;
	}

	if (nClassID == ATSVRCLASSID_CATSSVRTESTRESOURCES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrService::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestBenchsKey)
	{
		pNew = new CAtsSvrTestBenchs();
	}
	else if (strClassID == pXmlKeys->m_strCAtsSvrTestResourcesKey)
	{
		pNew = new CAtsSvrTestResources();
	}
	else if (strClassID == pXmlKeys->m_strAttrsKey)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}

CExBaseObject* CAtsSvrService::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTBENCHS)
	{
		pNew = new CAtsSvrTestBenchs();
	}
	else if (nClassID == ATSVRCLASSID_CATSSVRTESTRESOURCES)
	{
		pNew = new CAtsSvrTestResources();
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}

void CAtsSvrService::InitAtsSvrService()
{
	InitAtsSvrService(Ats_Svr_Service_Config_File);
}

void CAtsSvrService::InitAtsSvrService(const CString &strFile)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFile;

	OpenXmlFile(strPath, CAtsServiceXmlRWKeys::g_pXmlKeys);

	SyncBenchsFormDB();

	if (IsMode_Flow() || IsMode_BenchFlow())
	{//流程模式下才创建Service的MqTT客户端
		//[测试台SN/测试服务端SN]/AtsCmd/CreateTest
		if (!CreateAtsServiceMqttClient(STT_CMD_TYPE_ATS_CreateTest))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AtsSvrService  Create Failed"));
		}
	}

	if (IsMode_Bench() || IsMode_BenchFlow())
	{//工作台可以独立接受任务
		m_pBenchs->CreateAtsServiceMqttClient();
	}

	if (m_nUseTemplateSvr == 1)
	{
		//对于不是测试台订阅的主题，在该Client中订阅
		CreateAtsServiceMqttClient_Ex(_T("#"));
	}
}

void CAtsSvrService::SaveAtsSvrService()
{
	SaveAtsSvrService(Ats_Svr_Service_Config_File);
}

void CAtsSvrService::SaveAtsSvrService(const CString &strFile)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFile;

	SaveXmlFile(strPath, CAtsServiceXmlRWKeys::g_pXmlKeys);
}

CAtsSvrTestBench* CAtsSvrService::FindBench(const CString &strBenchSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->FindByID(strBenchSN);
}

CAtsSvrTestBench* CAtsSvrService::FindBenchByDeviceSN(const CString &strDeviceSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->FindBenchByDeviceSN(strDeviceSN);
}

CAtsSvrTestBench* CAtsSvrService::AddNewBench(const CString &strBenchSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->AddNewBench(strBenchSN);
}

//对于配置为模板服务时，同时又配置为流程模式，此处会有问题。
//按照目前的逻辑，配置为流程模式时，再配置为模板服务，则不起作用了。
BOOL CAtsSvrService::CreateAtsServiceMqttClient_Ex(const CString &strMqttTopic)
{
	if (m_pMqttClient != NULL)
	{
		if (m_pMqttClient->IsConnectSuccessful())
		{
			return TRUE;
		}
	}
	else
	{
		m_pMqttClient = new CSttProtoAtsService_Template_MqttClient(strMqttTopic);
		m_pMqttClient->m_strSN = m_strID;
		m_pMqttClient->SetMqttEngineRef(this);
	}

	return m_pMqttClient->Connect(CSttMqttClientEngineConfig::GetMqttServerIP(), CSttMqttClientEngineConfig::GetMqttServerPort(), _T("AtsService_TemplateSvr"));
}

void CAtsSvrService::SyncBenchsFormDB()
{
	if (m_pIotBenchsRef == NULL)
	{
		return;
	}

	if (m_pBenchs == NULL)
	{
		m_pBenchs = (CAtsSvrTestBenchs*)AddNewChild(new CAtsSvrTestBenchs());
	}

	POS pos = m_pIotBenchsRef->GetHeadPosition();

	while (pos != NULL)
	{
		CIot_Bench *pIotBench = (CIot_Bench *)m_pIotBenchsRef->GetNext(pos);

		if (m_pBenchs->FindByID(pIotBench->m_strCode) == NULL)
		{
			CAtsSvrTestBench *p = new CAtsSvrTestBench();
			p->m_strID = pIotBench->m_strCode;
			p->InitAfterRead();
			m_pBenchs->AddNewChild(p);
		}
	}
}

long CAtsSvrService::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv)
{
	if (IsMode_Flow() || IsMode_BenchFlow())
	{
		m_pTestFlows->Process_Cmd_Ats(oAtsCmdDrv, this);
		return 0;
	}

	if (m_nUseTemplateSvr == 1)
	{
		m_pAtsSvr_TemplateService->Process_Cmd_Ats(oAtsCmdDrv, this);
		return 0;
	}

	return 0;
}

long CAtsSvrService::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv)
{
	if (IsMode_Flow() || IsMode_BenchFlow())
	{
		m_pTestFlows->Process_Cmd_SysState(oSysStateDrv, this);
		return 0;
	}

	if (m_nUseTemplateSvr == 1)
	{
		m_pAtsSvr_TemplateService->Process_Cmd_SysState(oSysStateDrv, this);
		return 0;
	}

	return 0;
}

CXSttSmartTestXInterface* CAtsSvrService::FindSmartTestXInterface(const CString &strDeviceSN)
{
	CAtsSvrTestBench *pBench = FindBenchByDeviceSN(strDeviceSN);

	if (pBench != NULL)
	{
		return pBench->GetSmartTestSvrInterface();
	}

	CAtsSvrTestFlow *pFlow = (CAtsSvrTestFlow*)m_pTestFlows->FindByID(strDeviceSN);

	if (pFlow != NULL)
	{
		return pFlow->GetSmartTestSvrInterface();
	}

	return NULL;
}

