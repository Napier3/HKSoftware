//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlow.cpp  CAtsSvrTestFlow


#include "stdafx.h"
#include "AtsSvrTestFlow.h"

#include "AtsSvrService.h"
#include "../../../SttStudio/Module/SmartTestInterface/SttSmartTestSvrFactory.h"

CAtsSvrTestFlow::CAtsSvrTestFlow()
{
	//初始化属性

	//初始化成员变量
	m_pDevices = NULL;
	m_pSmartTestSvr  =NULL;
}

CAtsSvrTestFlow::~CAtsSvrTestFlow()
{
	if (m_pSmartTestSvr != NULL)
	{
		delete m_pSmartTestSvr;
		m_pSmartTestSvr  =NULL;
	}
}

long CAtsSvrTestFlow::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strSN);
	return 0;
}

long CAtsSvrTestFlow::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strSN);
	return 0;
}

long CAtsSvrTestFlow::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strSN);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strSN);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strSN);
	}
	return 0;
}

void CAtsSvrTestFlow::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == ATSVRCLASSID_CATSSVRDEVICES)
		{
			m_pDevices = (CAtsSvrDevices*)p;
		}
	}

	if (m_pDevices == NULL)
	{
		m_pDevices = (CAtsSvrDevices*)AddNewChild(new CAtsSvrDevices());
	}

}

BOOL CAtsSvrTestFlow::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrTestFlow *p = (CAtsSvrTestFlow*)pObj;

	if(m_strSN != p->m_strSN)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrTestFlow::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrTestFlow *p = (CAtsSvrTestFlow*)pDest;

	p->m_strSN = m_strSN;
	return TRUE;
}

CBaseObject* CAtsSvrTestFlow::Clone()
{
	CAtsSvrTestFlow *p = new CAtsSvrTestFlow();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestFlow::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRDEVICES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestFlow::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrDevicesKey)
	{
		pNew = new CAtsSvrDevices();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestFlow::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRDEVICES)
	{
		pNew = new CAtsSvrDevices();
	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
long CAtsSvrTestFlow::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	CString strBenchSN;

	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN);

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest
		|| pAtsCmd->m_strID == STT_CMD_TYPE_ATS_StartTest)
	{//判断是否已经创建，已经创建则返回，否则创建
		if (m_pSmartTestSvr == NULL)
		{
			m_pSmartTestSvr = CSttSmartTestSvrFactory::CreateSttSmartTestSvr(SmartTestSvr_Com_Flow, strBenchSN);
		}
	}

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_FlowSetBench)
	{
		m_pSmartTestSvr->m_strBenchSN = strBenchSN;
		FlowSetBench_InitPara_Apps(oAtsCmdDrv);
	}

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_StartTest)
	{//2021-11-3  lijunqing 如果是开始测试指令，给自动测试分配测试仪
		CAtsSvrTestBench *pBench = FindBench(strBenchSN);

		if (pBench != NULL)
		{
			CDataGroup oTestApps;  //使用Group节点传输
			pBench->GetTestApps(oTestApps);
			//shaolei 20220505
			//m_pSmartTestSvr->Ats_ConfigTest(strBenchSN, &oTestApps);
			m_pSmartTestSvr->Ats_ConfigTest(oAtsCmdDrv, NULL);
		}
	}

	m_pSmartTestSvr->Process_Cmd_Ats(oAtsCmdDrv, this);

	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CloseTest)
	{
		Disconnect();
		OnClose(NULL);
		((CAtsSvrTestFlows *)m_pParent)->Delete(this);
	}
	return 0;
}

/*
<ats-cmd name="" id="FlowSetBench" testor="ATS">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN"/>
		<group id="test-apps">  【测试仪，参考iot_testapp，除了测试状态，其他的字段都作为参数发送。】
	<group id="test-app">
				<data id="DeviceSN" value="123456789"/>
		<data id="EngineProgID" value="IotVm"/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
				<data id="factory" value="北京博电"/>
				。。。。。。。。。。
	</group>
	……
		</group>
		<group id="bin-for-start">  【测试开始的开关量输入条件】
	<data id="bin001" value="1"/>
	<data id="bin002" value="1"/>
	……
		</group>
	</paras>
</ats-cmd>
*/

long CAtsSvrTestFlow::FlowSetBench_InitPara_Apps(CXObjectRefDriver &oAtsCmdDrv)
{
	CString strBenchSN;
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();
	CSttParas *pSttParas = pAtsCmd->GetSttParas();

	if (! pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_BenchSN, strBenchSN))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TestFlow[%s] : %s cmd has no para [BenchID]"), m_strID, pAtsCmd->m_strID);
		return -1;
	}

	CAtsSvrTestBench *pBench = FindBench(strBenchSN);

	if (pBench == NULL)
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("TestFlow[%s] : %s cmd para BenchID=[%s] not exist")
// 			, m_strID, pAtsCmd->m_strID, strBenchSN);
// 		return -1;
		pBench = AddNewBench(strBenchSN);
	}

	//测试仪定义
	CAtsSvrTestApps *pApps = pBench->GetTestApps();
	pApps->InitSttParas(pSttParas);

	//开关量条件
	CDataGroup *pBinForStart = (CDataGroup*)pSttParas->FindByID(XPARA_ID_bin_for_start);
	pBench->InitBinForStart(pBinForStart);
	
	return 0;
}

CAtsSvrTestBench* CAtsSvrTestFlow::FindBench(const CString &strBenchSN)
{
	CAtsSvrService *pService = (CAtsSvrService*)GetAncestor(ATSVRCLASSID_CATSSVRSERVICE);
	ASSERT (pService != NULL);
	return pService->FindBench(strBenchSN);
}

CAtsSvrTestBench* CAtsSvrTestFlow::AddNewBench(const CString &strBenchSN)
{
	CAtsSvrService *pService = (CAtsSvrService*)GetAncestor(ATSVRCLASSID_CATSSVRSERVICE);
	ASSERT (pService != NULL);
	return pService->AddNewBench(strBenchSN);
}