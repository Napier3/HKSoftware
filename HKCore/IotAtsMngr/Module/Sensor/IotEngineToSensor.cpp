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
协议实现接口指针指向RTDeviceCtrl,协议转换模块析构时不能释放RTDeviceCtrl，
所以在析构函数中m_pProtocolImpInterface=NULL；
*******************************/
CIotEngineToSensor::~CIotEngineToSensor()
{
	m_pProtocolImpInterface = NULL;	//防止析构时删除RTDeviceCtrl
}

/*************************************
主题：请求端SN/DeviceID/IotCmd/RunProcedure
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="id-procedure" value="WriteSetting">【执行的通信过程】
			<value data-type="FLOAT" id="" name="" value=""/>【通信过程的参数】
		</data>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
RecordMode：none=不录波、own=只录波自身数据、all=录波过程期间的全部数据
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

	//调用CRTDeviceCtrl的RunProcedure接口
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
主题：请求端SN/DeviceID/IotCmd/CloseDevice
<iot-cmd name="" id=" CloseDevice " testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
	</paras>
</iot-cmd>
******************************************/
long CIotEngineToSensor::CloseDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	//调用CRTDeviceCtrl的CloseDevice接口
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