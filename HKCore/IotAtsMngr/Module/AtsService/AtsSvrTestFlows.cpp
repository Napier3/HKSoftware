//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrTestFlows.cpp  CAtsSvrTestFlows


#include "stdafx.h"
#include "AtsSvrTestFlows.h"

CAtsSvrTestFlows::CAtsSvrTestFlows()
{
	//��ʼ������

	//��ʼ����Ա����
}

CAtsSvrTestFlows::~CAtsSvrTestFlows()
{
}

long CAtsSvrTestFlows::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestFlows::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestFlows::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CAtsSvrTestFlows::InitAfterRead()
{
}

BOOL CAtsSvrTestFlows::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrTestFlows *p = (CAtsSvrTestFlows*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestFlows::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrTestFlows *p = (CAtsSvrTestFlows*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestFlows::Clone()
{
	CAtsSvrTestFlows *p = new CAtsSvrTestFlows();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestFlows::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRTESTFLOW)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestFlows::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestFlowKey)
	{
		pNew = new CAtsSvrTestFlow();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestFlows::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTFLOW)
	{
		pNew = new CAtsSvrTestFlow();
	}

	return pNew;
}

long CAtsSvrTestFlows::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttAtsCmd *pAtsCmd = (CSttAtsCmd*)oAtsCmdDrv.GetXObjectRef();

	//�ж��Ƿ�ΪCreateTest�������ǣ�
	//��ȡDevieSN������DeviceSN����TestFlow��Ȼ�����TestFlow��Process_Cmd_Ats
	CString strDeviceSN;
	pAtsCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	CSttParas *pParas = pAtsCmd->GetSttParas();
	CDataGroup *pDevices = (CDataGroup *)pParas->FindByID(XPARA_ID_devices);

	if (pDevices != NULL)
	{
		if (strDeviceSN.IsEmpty() && pDevices != NULL)
		{
			CDataGroup *pFirstDevice = (CDataGroup *)pDevices->GetHead();
			pFirstDevice->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);
		}
	}

	CAtsSvrTestFlow *pFlow = (CAtsSvrTestFlow*)FindByID(strDeviceSN);
	CSttSysState oSysState;
	CSttParas *pParasReturn = oSysState.GetSttParas();
	pParasReturn->AddNewData(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);

	if (pFlow == NULL)
	{
		pFlow = new CAtsSvrTestFlow();
		pFlow->m_strID = strDeviceSN;
		pFlow->CreateAtsServiceMqttClient(_T("#"));
		AddNewChild(pFlow);
		pFlow->Process_Cmd_Ats(oAtsCmdDrv);
		//pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_SUCCESS, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
	}
	else
	{//�Ѿ����ڣ�ִ��ʧ��
		if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest)
		{
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_ACK, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
			pSttProtocol->ReturnSysState_REPLY((CSttCmmOptrInterface *)pAtsCmd->GetSttCmmOptrInterface(), STT_CMD_ExecStatus_FAILURE, &oSysState, STT_CMD_TYPE_ATS_CreateTest, STT_CMD_SYSSTATE_ATS);
		}
		else
		{
			//����CreateTest֮���ָ����磺STT_CMD_TYPE_ATS_FlowSetBench����Ҫ������
			pFlow->Process_Cmd_Ats(oAtsCmdDrv);
		}
	}

	return 0;
}

