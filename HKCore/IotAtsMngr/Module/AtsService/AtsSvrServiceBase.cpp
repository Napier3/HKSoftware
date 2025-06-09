//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrServiceBase.cpp  CAtsSvrServiceBase


#include "stdafx.h"
#include "AtsSvrServiceBase.h"
#include "../SttMqttClientEngineConfig.h"
#include "../Iot_AtsMngrDB/Iot_Bench.h"

CAtsSvrServiceBase::CAtsSvrServiceBase()
{
	//初始化属性

	//初始化成员变量
	m_pBenchs = NULL;
	m_pTestResources = NULL;
	m_pAttrs = NULL;
	m_pTestFlows = NULL;

	m_strSvrMode = ATSSVR_SVERVICE_MODE_BENCH;
	m_nIsServiceMngr = 0;
	m_pIotBenchsRef = NULL;
	m_strSmartTestSvr = _T("com");  //通过COM方式调用自动测试
	m_pAtsSvr_TemplateService = NULL;
}

CAtsSvrServiceBase::~CAtsSvrServiceBase()
{
	if (m_pAtsSvr_TemplateService != NULL)
	{
		delete m_pAtsSvr_TemplateService;
		m_pAtsSvr_TemplateService = NULL;
	}
}


//测试服务端SN/AtsCmd/CreateTest
BOOL CAtsSvrServiceBase::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1], MQTT_CMD_ID_AtsCmd) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

void CAtsSvrServiceBase::MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
{
	CSttAtsSvrMqttImpBase::MqttMsgProcess(oSttMqttTopicParser);
}

BOOL CAtsSvrServiceBase::MqttSubscribeTopic()
{
	CString strTopic ;

	//测试服务端发送的指令，主要是创建测试指令
	//测试服务端SN/AtsCmd/CreateTest
	strTopic = _T("+/AtsCmd/#");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	//测试服务端发给Bench以及Flow的指令
	//测试服务端SN/BenchSN/AtsCmd/CreateTest
	strTopic = _T("+/+/AtsCmd/#");
	g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	//测试服务端SN/BenchSN/AtsCmd/CreateTest
	//strTopic = _T("+/+/AtsState/#");
	//g_theSttOutMqttClient->SubscribeTopic(strTopic, 0);

	return TRUE;
}

BOOL CAtsSvrServiceBase::MqttUnSubscribeTopic() 
{
	CString strTopic ;

	//测试服务端发送的指令，主要是创建测试指令
	//测试服务端SN/AtsCmd/CreateTest
	strTopic = _T("+/AtsCmd/#");
	g_theSttOutMqttClient->UnSubscribeTopic(strTopic);

	//测试服务端发给Bench以及Flow的指令
	//测试服务端SN/BenchSN/AtsCmd/CreateTest
	strTopic = _T("+/+/AtsCmd/#");
	g_theSttOutMqttClient->UnSubscribeTopic(strTopic);

	return TRUE;
}

long CAtsSvrServiceBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strAtsServiceSn);
	xml_GetAttibuteValue(pXmlKeys->m_strSvrModeKey, oNode, m_strSvrMode);
	xml_GetAttibuteValue(pXmlKeys->m_strIsServiceMngrKey, oNode, m_nIsServiceMngr);
	xml_GetAttibuteValue(pXmlKeys->m_strSmartTestSvrKey, oNode, m_strSmartTestSvr);

	CString strPath;
	xml_GetAttibuteValue(pXmlKeys->m_strWokspacePathKey, oNode, strPath);

	if (strPath.GetLength() > 0)
	{
		g_strReportFilePath = strPath;
	}

	return 0;
}

long CAtsSvrServiceBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strAtsServiceSn);
	xml_SetAttributeValue(pXmlKeys->m_strSvrModeKey, oElement, m_strSvrMode);
	xml_SetAttributeValue(pXmlKeys->m_strIsServiceMngrKey, oElement, m_nIsServiceMngr);
	xml_SetAttributeValue(pXmlKeys->m_strSmartTestSvrKey, oElement, m_strSmartTestSvr);
	xml_SetAttributeValue(pXmlKeys->m_strWokspacePathKey, oElement, g_strReportFilePath);

	return 0;
}

long CAtsSvrServiceBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAtsServiceSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strSvrMode);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeCalLen(oBinaryBuffer, m_strSmartTestSvr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAtsServiceSn);
		BinarySerializeRead(oBinaryBuffer, m_strSvrMode);
		BinarySerializeRead(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeRead(oBinaryBuffer, m_strSmartTestSvr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAtsServiceSn);
		BinarySerializeWrite(oBinaryBuffer, m_strSvrMode);
		BinarySerializeWrite(oBinaryBuffer, m_nIsServiceMngr);
		BinarySerializeWrite(oBinaryBuffer, m_strSmartTestSvr);
	}
	return 0;
}

void CAtsSvrServiceBase::InitAfterRead()
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
		m_pTestFlows = (CAtsSvrTestFlows*)AddNewChild(NewAtsSvrTestFlows());
	}
}

BOOL CAtsSvrServiceBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrServiceBase *p = (CAtsSvrServiceBase*)pObj;

	if(m_strAtsServiceSn != p->m_strAtsServiceSn)
	{
		return FALSE;
	}

	if(m_strSvrMode != p->m_strSvrMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrServiceBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrServiceBase *p = (CAtsSvrServiceBase*)pDest;

	p->m_strAtsServiceSn = m_strAtsServiceSn;
	p->m_strSvrMode = m_strSvrMode;
	return TRUE;
}

CBaseObject* CAtsSvrServiceBase::Clone()
{
	CAtsSvrServiceBase *p = new CAtsSvrServiceBase();
	Copy(p);
	return p;
}

BOOL CAtsSvrServiceBase::CanPaste(UINT nClassID)
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

CExBaseObject* CAtsSvrServiceBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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
	else if (strClassID == pXmlKeys->m_strCAtsSvrTestFlowsKey)
	{
		pNew = NewAtsSvrTestFlows();
	}

	return pNew;
}

CExBaseObject* CAtsSvrServiceBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
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
	else if (nClassID == ATSVRCLASSID_CATSSVRTESTFLOWS)
	{
		pNew = NewAtsSvrTestFlows();
	}

	return pNew;
}

void CAtsSvrServiceBase::InitAtsSvrService()
{
	m_pAtsSvr_TemplateService = NewTemplateService();
	InitAtsSvrService(Ats_Svr_Service_Config_File);
}

void CAtsSvrServiceBase::InitAtsSvrService(const CString &strFile)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFile;

	OpenXmlFile(strPath, CAtsServiceXmlRWKeys::g_pXmlKeys);

	SyncBenchsFormDB();
	CreateAtsServiceMqttClient();
/*
	if (IsMode_Flow() || IsMode_BenchFlow())
	{//流程模式下才创建Service的MqTT客户端
		//[测试台SN/测试服务端SN]/AtsCmd/CreateTest
		if (!CreateAtsServiceMqttClient(STT_CMD_TYPE_ATS_CreateTest))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AtsSvrServiceBase  Create Failed"));
		}
	}

	if (IsMode_Bench() || IsMode_BenchFlow())
	{//工作台可以独立接受任务
		m_pBenchs->CreateAtsServiceMqttClient();
	}
*/
}

void CAtsSvrServiceBase::SaveAtsSvrService()
{
	SaveAtsSvrService(Ats_Svr_Service_Config_File);
}

void CAtsSvrServiceBase::SaveAtsSvrService(const CString &strFile)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFile;

	SaveXmlFile(strPath, CAtsServiceXmlRWKeys::g_pXmlKeys);
}

CAtsSvrTestFlows* CAtsSvrServiceBase::NewAtsSvrTestFlows()
{
	return new CAtsSvrTestFlows();
}

CAtsSvr_TemplateServiceBase* CAtsSvrServiceBase::NewTemplateService()
{
	return new CAtsSvr_TemplateServiceBase();
}

CAtsSvrTestBench* CAtsSvrServiceBase::FindBench(const CString &strBenchSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->FindByID(strBenchSN);
}

CAtsSvrTestBench* CAtsSvrServiceBase::FindBenchByDeviceSN(const CString &strDeviceSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->FindBenchByDeviceSN(strDeviceSN);
}

CAtsSvrTestBench* CAtsSvrServiceBase::AddNewBench(const CString &strBenchSN)
{
	return (CAtsSvrTestBench*)m_pBenchs->AddNewBench(strBenchSN);
}

void CAtsSvrServiceBase::SyncBenchsFormDB()
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

long CAtsSvrServiceBase::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv)
{
	if (IsMode_Flow() || IsMode_BenchFlow())
	{
		m_pTestFlows->Process_Cmd_Ats(oAtsCmdDrv, this);
		return 0;
	}

	return 0;
}

long CAtsSvrServiceBase::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv)
{
	if (IsMode_Flow() || IsMode_BenchFlow())
	{
		m_pTestFlows->Process_Cmd_SysState(oSysStateDrv, this);
		return 0;
	}

	return 0;
}

CXSttSmartTestXInterface* CAtsSvrServiceBase::FindSmartTestXInterface(const CString &strDeviceSN)
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

