//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestBench.cpp  CAtsSvrTestBench


#include "stdafx.h"
#include "AtsSvrTestBench.h"
#include "../SttMqttClientEngineConfig.h"

#include "../../../SttStudio/Module/SmartTestInterface/SttSmartTestSvrFactory.h"
#include "AtsSvrService.h"

CAtsSvrTestBench::CAtsSvrTestBench()
{
	//初始化属性
	m_nSelfStart = 0;

	//初始化成员变量
	m_pTestApps = NULL;
	m_pAttrs = NULL;
	m_pDevices = NULL;

	m_pSmartTestSvr = NULL;
}

CAtsSvrTestBench::~CAtsSvrTestBench()
{
	if (m_pSmartTestSvr != NULL)
	{
		delete m_pSmartTestSvr;
		m_pSmartTestSvr = NULL;
	}
}

long CAtsSvrTestBench::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSelfStartKey, oNode, m_nSelfStart);
	return 0;
}

long CAtsSvrTestBench::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSelfStartKey, oElement, m_nSelfStart);
	return 0;
}

long CAtsSvrTestBench::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSelfStart);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSelfStart);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSelfStart);
	}
	return 0;
}

void CAtsSvrTestBench::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ATSVRCLASSID_CATSSVRTESTAPPS)
		{
			m_pTestApps = (CAtsSvrTestApps*)p;
		}
		else if (nClassID == DVMCLASSID_CDVMDATASET)
		{
			m_pAttrs = (CDvmDataset*)p;
		}
		else if (nClassID == ATSVRCLASSID_CATSSVRDEVICES)
		{
			m_pDevices = (CAtsSvrDevices*)p;
		}
	}

	if (m_pTestApps == NULL)
	{
		m_pTestApps = (CAtsSvrTestApps*)AddNewChild(new CAtsSvrTestApps());
	}

	if (m_pAttrs == NULL)
	{
		m_pAttrs = (CDvmDataset*)AddNewChild(new CDvmDataset());
	}

	if (m_pDevices == NULL)
	{
		m_pDevices = (CAtsSvrDevices*)AddNewChild(new CAtsSvrDevices());
	}
}

BOOL CAtsSvrTestBench::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrTestBench *p = (CAtsSvrTestBench*)pObj;

	if(m_nSelfStart != p->m_nSelfStart)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrTestBench::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrTestBench *p = (CAtsSvrTestBench*)pDest;

	p->m_nSelfStart = m_nSelfStart;
	return TRUE;
}

CBaseObject* CAtsSvrTestBench::Clone()
{
	CAtsSvrTestBench *p = new CAtsSvrTestBench();
	Copy(p);
	return p;
}

CExBaseObject* CAtsSvrTestBench::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestAppsKey)
	{
		pNew = new CAtsSvrTestApps();
	}
	else if (strClassID == pXmlKeys->m_strAttrsKey)
	{
		pNew = new CDvmDataset();
	}
	else if (strClassID == pXmlKeys->m_strCAtsSvrDevicesKey)
	{
		pNew = new CAtsSvrDevices();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestBench::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTAPPS)
	{
		pNew = new CAtsSvrTestApps();
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}
	else if (nClassID == ATSVRCLASSID_CATSSVRDEVICES)
	{
		pNew = new CAtsSvrDevices();
	}

	return pNew;
}

CDataGroup* CAtsSvrTestBench::FindDvmDevice(const CString &strDeviceSN)
{
	CExBaseList *p = NULL;
	CDataGroup *pFind = NULL;
	POS pos = m_oDvmDevices.GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList*)m_oDvmDevices.GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP || p->m_strID != XPARA_ID_device)
		{
			continue;
		}

		pData = (CDvmData*)p->FindByID( STT_CMD_PARA_DeviceSN);

		if (pData == NULL)
		{
			continue;
		}

		if (pData->m_strValue == strDeviceSN)
		{
			pFind = (CDataGroup *)p;
			break;
		}
	}

	return pFind;
}

void CAtsSvrTestBench::GetTestApps(CDataGroup &oTestApps)
{
	if (m_pTestApps == NULL)
	{
		return;
	}

	oTestApps.AppendEx(*m_pTestApps, FALSE);
}

void CAtsSvrTestBench::InitBinForStart(CDataGroup *pBinForStart)
{
	if (pBinForStart != NULL)
	{
		m_oBinForStart.AppendCloneEx(*pBinForStart);
	}
}

BOOL CAtsSvrTestBench::IsSmartTestSvr_Com()
{
	CAtsSvrService *pService = (CAtsSvrService *)GetAncestor(ATSVRCLASSID_CATSSVRSERVICE);

	return pService->m_strSmartTestSvr == _T("com");
}

//mqtt模式下，支持SmartTest多开
BOOL CAtsSvrTestBench::IsSmartTestSvr_Mqtt()
{
	CAtsSvrService *pService = (CAtsSvrService *)GetAncestor(ATSVRCLASSID_CATSSVRSERVICE);

	return pService->m_strSmartTestSvr == _T("mqtt");
}

long CAtsSvrTestBench::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>>>Bentch[%s]: receive ats cmd [%s]"), m_strID, pAtsCmd->m_strID);

	if (m_pSmartTestSvr == NULL)
	{
		if (IsSmartTestSvr_Com())
		{
			m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Com, m_strID);
			
		}
		else if (IsSmartTestSvr_Mqtt())
		{
			m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Mqtt, m_strID);
		}
		else
		{
			m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Com, m_strID);
		}

		m_pSmartTestSvr->m_strBenchSN = m_strID;
		m_pSmartTestSvr->m_strID = m_strID;
	}

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest)
	{//判断是否已经创建，已经创建则返回，否则创建
		//2021-8-4  lijunqing  记录Devices
		CExBaseObject *pDevices = pAtsCmd->FindInParasByID(XPARA_ID_devices);

		if (pDevices != NULL)
		{
			if (pDevices->GetClassID() == DTMCLASSID_CDATAGROUP)
			{
				m_oDvmDevices.DeleteAll();
				pDevices->Copy(&m_oDvmDevices);
			}
		}
	}
	
	m_pSmartTestSvr->Process_Cmd_Ats(oAtsCmdDrv, this);

	return 0;
}

long CAtsSvrTestBench::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv)
{
	if (m_pSmartTestSvr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("应用程序错误：CAtsSvrTestBench::Process_Cmd_SysState，m_pSmartTestSvr == NULL"));
		return -1;
	}

	return m_pSmartTestSvr->Process_Cmd_SysState(oSysStateDrv, this);
}

long CAtsSvrTestBench::Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase)
{
	if (m_pSmartTestSvr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("应用程序错误：CAtsSvrTestBench::Process_Cmd_Ats_Event_UploadFinish，m_pSmartTestSvr == NULL"));
		return -1;
	}

	return m_pSmartTestSvr->Process_Cmd_Ats_Event_UploadFinish(pSttCmdBase);
}