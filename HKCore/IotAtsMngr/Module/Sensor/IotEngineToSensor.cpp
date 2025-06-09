#include "stdafx.h"
#include "IotEngineToSensor.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineToSensor::CIotEngineToSensor()
{

}

/******************************
Э��ʵ�ֽӿ�ָ��ָ��RTDeviceCtrl,Э��ת��ģ������ʱ�����ͷ�RTDeviceCtrl��
����������������m_pProtocolImpInterface=NULL��
*******************************/
CIotEngineToSensor::~CIotEngineToSensor()
{
	m_pProtocolImpInterface = NULL;	//��ֹ����ʱɾ��RTDeviceCtrl
}

/*************************************
���⣺�����SN/DeviceID/IotCmd/RunProcedure
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="id-procedure" value="WriteSetting">��ִ�е�ͨ�Ź��̡�
			<value data-type="FLOAT" id="" name="" value=""/>��ͨ�Ź��̵Ĳ�����
		</data>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
RecordMode��none=��¼����own=ֻ¼���������ݡ�all=¼�������ڼ��ȫ������
**************************************/
long CIotEngineToSensor::RunProcedure(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	CString strPrcdrID,strRecordMode;
	CDvmData *pDataInterface = NULL;
	CDvmDataset *pDataset = NULL;

	CSttParas *pParas = oIotCmd.GetSttParas();
	pDataInterface = (CDvmData *)pParas->FindByID(STT_CMD_PARA_ProcedureID);
	if (pDataInterface == NULL)
	{
		return 0;
	}

	pDataset = oIotCmd.GetDataset();
	strPrcdrID = pDataInterface->m_strValue;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_RecordMode,strRecordMode);

	//����CRTDeviceCtrl��RunProcedure�ӿ�
	return m_pProtocolImpInterface->RunProcedure(strPrcdrID,pDataInterface,pDataset,strRecordMode);
}

long CIotEngineToSensor::PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

// 	CString strPkg,strDatasetPath;
// 	oIotCmd.GetParasDataValueByID(_T("Pkg"),strPkg);
// 	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DatasetPath,strDatasetPath);
// 
// 	CDvmDataset *pRetDataset = new CDvmDataset;
// 	pRetDataset->m_strID = strDatasetPath;
// 
// 	m_pIotEdgeProtoSvr->PkgPrase((char *)strPkg.GetString(),strPkg.GetLength(),*pRetDataset);
// 	oRetParas.AddNewChild(pRetDataset);

	return 0;
}

long CIotEngineToSensor::PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	//	m_pIotEdgeProtoSvr->PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen);
	return 0;
}

long CIotEngineToSensor::GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	CString strDatasetPath;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DatasetPath,strDatasetPath);

	CDvmDataset *pRetDataset = new CDvmDataset;
	m_pProtocolImpInterface->GetDataset(strDatasetPath,*pRetDataset);

	oRetParas.AddNewChild(pRetDataset);
	return 0;
}

long CIotEngineToSensor::ConfigDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	//	m_pIotEdgeProtoSvr->ConfigDevice(const CString &strConfig);
	return 0;
}

/*************************************
���⣺�����SN/DeviceID/IotCmd/CloseDevice
<iot-cmd name="" id=" CloseDevice " testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
	</paras>
</iot-cmd>
******************************************/
long CIotEngineToSensor::CloseDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	//����CRTDeviceCtrl��CloseDevice�ӿ�
	return m_pProtocolImpInterface->CloseDevice();
}


void CIotEngineToSensor::OnPrcdrFinished(CPxPrcdrBase *pPrcdr)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pPrcdr->GetResultEvent(),pPrcdr->m_pRefDataset);
}

void CIotEngineToSensor::OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pszEventID,pDatasetRef);
}

void CIotEngineToSensor::OnDeviceClosed(long nDeviceIndex)
{
	m_pIotEngineProtoSvr->OnDeviceClosed(nDeviceIndex);
}

void CIotEngineToSensor::OnPkgReceive(CPxPkgBase *pPkg)
{

}

void CIotEngineToSensor::OnPkgSend(CPxPkgBase *pPkg)
{

}

void CIotEngineToSensor::OnException(unsigned long nErrNo)
{

}

void CIotEngineToSensor::OnClose(char *pszErr)
{

}