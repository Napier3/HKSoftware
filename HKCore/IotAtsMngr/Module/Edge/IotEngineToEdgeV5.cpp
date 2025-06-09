#include "stdafx.h"
#include "IotEngineToEdgeV5.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineToEdgeV5::CIotEngineToEdgeV5()
{

}

CIotEngineToEdgeV5::~CIotEngineToEdgeV5()
{

}

long CIotEngineToEdgeV5::RunProcedure(CSttIotCmd &oIotCmd)
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
	if(pDataset == NULL)
		pDataset = oIotCmd.GetDatasetGroup();
	strPrcdrID = pDataInterface->m_strValue;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_RecordMode,strRecordMode);

	return m_pProtocolImpInterface->RunProcedure(strPrcdrID,pDataInterface,pDataset,strRecordMode);
}

long CIotEngineToEdgeV5::PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	return 0;
}

long CIotEngineToEdgeV5::PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	return 0;
}

long CIotEngineToEdgeV5::GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
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

long CIotEngineToEdgeV5::ConfigDevice(CSttIotCmd &oIotCmd)
{
	return 0;
}

long CIotEngineToEdgeV5::CloseDevice(CSttIotCmd &oIotCmd)
{
	if (m_pProtocolImpInterface == NULL)
	{
		return 0;
	}

	return m_pProtocolImpInterface->CloseDevice();
}

void CIotEngineToEdgeV5::OnPrcdrFinished(CPxPrcdrBase *pPrcdr)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pPrcdr->GetResultEvent(),pPrcdr->m_pRefDataset);
}

void CIotEngineToEdgeV5::OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef)
{
	m_pIotEngineProtoSvr->OnPrcdrFinished(pszEventID,pDatasetRef);
}

void CIotEngineToEdgeV5::OnDeviceClosed(long nDeviceIndex)
{
	m_pIotEngineProtoSvr->OnDeviceClosed(nDeviceIndex);
}

void CIotEngineToEdgeV5::OnPkgReceive(CPxPkgBase *pPkg)
{

}

void CIotEngineToEdgeV5::OnPkgSend(CPxPkgBase *pPkg)
{

}

void CIotEngineToEdgeV5::OnException(unsigned long nErrNo)
{

}

void CIotEngineToEdgeV5::OnClose(char *pszErr)
{

}