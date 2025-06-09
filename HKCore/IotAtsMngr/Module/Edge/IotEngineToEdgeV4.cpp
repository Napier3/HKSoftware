#include "stdafx.h"
#include "IotEngineToEdgeV4.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineToEdgeV4::CIotEngineToEdgeV4()
{

}

CIotEngineToEdgeV4::~CIotEngineToEdgeV4()
{

}

long CIotEngineToEdgeV4::RunProcedure(CSttIotCmd &oIotCmd)
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

	//调用CIotEdgeProtoServerV4|5的RunProcedure接口
	return m_pProtocolImpInterface->RunProcedure(strPrcdrID,pDataInterface,pDataset,strRecordMode);
}

long CIotEngineToEdgeV4::PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	return 0;
}

long CIotEngineToEdgeV4::PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	return 0;
}

long CIotEngineToEdgeV4::GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
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

long CIotEngineToEdgeV4::ConfigDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	//	m_pIotEdgeProtoSvr->ConfigDevice(const CString &strConfig);
	return 0;
}

long CIotEngineToEdgeV4::CloseDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	return m_pProtocolImpInterface->CloseDevice();
}

void CIotEngineToEdgeV4::OnPrcdrFinished(CPxPrcdrBase *pPrcdr)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pPrcdr->GetResultEvent(),pPrcdr->m_pRefDataset);
}

void CIotEngineToEdgeV4::OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pszEventID,pDatasetRef);
}

void CIotEngineToEdgeV4::OnDeviceClosed(long nDeviceIndex)
{
	m_pIotEngineProtoSvr->OnDeviceClosed(nDeviceIndex);
}

void CIotEngineToEdgeV4::OnPkgReceive(CPxPkgBase *pPkg)
{

}

void CIotEngineToEdgeV4::OnPkgSend(CPxPkgBase *pPkg)
{

}

void CIotEngineToEdgeV4::OnException(unsigned long nErrNo)
{

}

void CIotEngineToEdgeV4::OnClose(char *pszErr)
{

}