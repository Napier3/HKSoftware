#include "PpSttIotEngineDeviceBase.h"

CPpSttIotEngineDeviceBase::CPpSttIotEngineDeviceBase()
{
	m_pDvmDeviceRef = NULL;
}

CPpSttIotEngineDeviceBase::~CPpSttIotEngineDeviceBase()
{

}

void CPpSttIotEngineDeviceBase::SetDeviceRef(CDvmDevice* pDeviceRef)
{
	m_pDvmDeviceRef = pDeviceRef;
}

CDvmDevice* CPpSttIotEngineDeviceBase::GetDeviceRef()
{
	return m_pDvmDeviceRef;
}

CSttSysState* CPpSttIotEngineDeviceBase::GetDataset(const CString& strDeviceSN, const CString& strIDPath)
{
	//CDvmDataset* pDataset = (CDvmDataset*)m_pDvmDeviceRef->FindByPathChildren(strDatasetID, *pDatasetRef, '$');
	//测试从AT02D.xml文件中取数据集
	CDvmDevice oDevice;
	CString strFile = _P_GetBinPath();
	strFile += "AT02D.xml";
	oDevice.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	CExBaseList* pDataset = new CExBaseList;
	CString strDatasetID = strIDPath;
	long nRes = oDevice.FindByPathChildren(strDatasetID, *pDataset, '$');
	strDatasetID = strIDPath.Mid(strIDPath.ReverseFind('$') + 1);
	//
	CSttSysState* pSysState = new CSttSysState;
	pSysState->AddNewParasData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	if(nRes == 1)
	{
		pSysState->AddNewParas((CExBaseList*)pDataset->FindByID(strDatasetID));
		pSysState->Set_ExecStatus_Success();
		
	}
	else
	{
		pSysState->Set_ExecStatus_Failure();
	}

	pDataset->RemoveAll();
	delete pDataset;

	return pSysState;
}

CSttSysState* CPpSttIotEngineDeviceBase::SetDataset(CDvmDataset* pDataset, const CString& strDeviceSN, const CString& strIDPath)
{
	//CDvmDataset* pDatasetRef = (CDvmDataset*)m_pDvmDeviceRef->FindByPathChildren(strDatasetID, *pDatasetRef, '$');
	//测试从AT02D.xml文件中取数据集
	CDvmDevice oDevice;
	CString strFile = _P_GetBinPath();
	strFile += "AT02D.xml";
	oDevice.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	CExBaseList* pDatasetRef = new CExBaseList;
	CString strDatasetID = strIDPath;
	long nRes = oDevice.FindByPathChildren(strDatasetID, *pDatasetRef, '$');
	strDatasetID = strIDPath.Mid(strIDPath.ReverseFind('$') + 1);
	//
	CSttSysState* pSysState = new CSttSysState;
	pSysState->AddNewParasData(STT_CMD_PARA_DeviceSN, strDeviceSN);
	if(nRes == 1)
	{
		CDvmDataset* p = (CDvmDataset*)pDatasetRef->FindByID(strDatasetID);
		p->UpdateDataValue(pDataset);
		pSysState->Set_ExecStatus_Success();
	}
	else
	{
		pSysState->Set_ExecStatus_Failure();
	}

	pDatasetRef->RemoveAll();
	delete pDatasetRef;

	return pSysState;
}