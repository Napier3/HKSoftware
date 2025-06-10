#include "stdafx.h"
#include"PpEngine_Stt.h"
#include "PpSttIotEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//CPpsttParas
CPpsttParas::CPpsttParas()
{
	m_pDataInterface = NULL;
}

CPpsttParas::~CPpsttParas()
{
    delete m_pDataInterface;
	m_pDataInterface = NULL;
}

long CPpsttParas::Reset()
{
	return m_pDataInterface->Reset();
}

long CPpsttParas::AddData(const CString &bstrID, const CString &bstrValue)
{
	return m_pDataInterface->AddData(bstrID, bstrValue);
}

//////////////////////////////////////////////////////////////////////////
//CPpsttValue
CPpsttValue::CPpsttValue()
{
    m_pValue = NULL;
}

CPpsttValue::~CPpsttValue()
{
    delete m_pValue;
    m_pValue = NULL;
}

CString CPpsttValue::GetName()
{
    return _T("");
}

void CPpsttValue::SetName(CString propVal)
{

}

CString CPpsttValue::GetID()
{
	return _T("");
}

void CPpsttValue::SetID(CString propVal)
{

}

CString CPpsttValue::GetDataType()
{
	return _T("");
}

void CPpsttValue::SetDataType(CString propVal)
{
	
}

CString CPpsttValue::GetValue()
{
	return _T("");
}

void CPpsttValue::SetValue(CString propVal)
{
    m_pValue->SetValue(propVal);
}

CString CPpsttValue::GetUnit()
{
    return m_pValue->GetUnit();
}

void CPpsttValue::SetUnit(CString propVal)
{
    m_pValue->SetUnit(propVal);
}

//////////////////////////////////////////////////////////////////////////
//CPpsttData
CPpsttData::CPpsttData()
{
    m_pData = NULL;
}

CPpsttData::~CPpsttData()
{
    delete m_pData;
    m_pData = NULL;
}


long CPpsttData::GetCount()
{
    return m_pData->GetCount();
}

CProtocolValueInterface* CPpsttData::GetItem(long nIndex)
{
    CPpsttValue *pValue = new CPpsttValue();
    pValue->m_pValue = m_pData->GetItem(nIndex);

    return pValue;
}

long CPpsttData::RegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID)
{
    m_pData->RegisterDataChangedWndMsg(hWnd, nWMsgID);
	return 0;
}

long CPpsttData::UnRegisterDataChangedWndMsg()
{
    m_pData->UnRegisterDataChangedWndMsg();
	return 0;
}

CString CPpsttData::GetName()
{
    return m_pData->GetName();
}

void CPpsttData::SetName(CString propVal)
{
    m_pData->SetName(propVal);
}

CString CPpsttData::GetID()
{
    return m_pData->GetID();
}

void CPpsttData::SetID(CString propVal)
{
    m_pData->SetID(propVal);
}

CString CPpsttData::GetDataType()
{
    return m_pData->GetDataType();
}

void CPpsttData::SetDataType(CString propVal)
{
    m_pData->SetDataType(propVal);
}

CString CPpsttData::GetValue()
{
    return m_pData->GetValue();
}

void CPpsttData::SetValue(CString propVal)
{
    m_pData->SetValue(propVal);
}

CString CPpsttData::GetUnit()
{
    return m_pData->GetUnit();
}

void CPpsttData::SetUnit(CString propVal)
{
    m_pData->SetUnit(propVal);
}

CString CPpsttData::GetMinValue()
{
    return m_pData->GetMinValue();
}

void CPpsttData::SetMinValue(CString propVal)
{
    m_pData->SetMinValue(propVal);
}

CString CPpsttData::GetMaxValue()
{
    return m_pData->GetMaxValue();
}

void CPpsttData::SetMaxValue(CString propVal)
{
    m_pData->SetMaxValue(propVal);
}

//////////////////////////////////////////////////////////////////////////
//CPpsttDataset
CPpsttDataset::CPpsttDataset()
{
    m_pDataset = NULL;
}

CPpsttDataset::~CPpsttDataset()
{
    delete m_pDataset;
    m_pDataset = NULL;
}

long CPpsttDataset::GetCount()
{
    return m_pDataset->GetCount();
}

CProtocolDataInterface* CPpsttDataset::GetItem(long nIndex)
{
    CPpsttData *pData = new CPpsttData();
    pData->m_pData = m_pDataset->GetItem(nIndex);

    return pData;
}

CProtocolDataInterface* CPpsttDataset::FindDataByID(const CString &strDataID)
{
    CPpsttData *pData = new CPpsttData();
    pData->m_pData = m_pDataset->FindDataByID(strDataID);

    return pData;
}

CProtocolDataInterface* CPpsttDataset::FindDataByName(const CString &strName)
{
    CPpsttData *pData = new CPpsttData();
    pData->m_pData = m_pDataset->FindDataByName(strName);

    return pData;
}

CString CPpsttDataset::GetXmlData()
{
    return m_pDataset->GetXmlData();
}

long CPpsttDataset::SetXmlData(const CString &strXmlData)
{
    m_pDataset->SetXmlData(strXmlData);

	return 0;
}

long CPpsttDataset::DeleteAllDatas()
{
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
/// CPpsttLogicDevice
CPpsttLogicDevice::CPpsttLogicDevice()
{
    m_pLogicDevice = NULL;
}

CPpsttLogicDevice::~CPpsttLogicDevice()
{
    delete m_pLogicDevice;
    m_pLogicDevice = NULL;
}

long CPpsttLogicDevice::GetCount()
{
    return m_pLogicDevice->GetCount();
}

CProtocolDatasetInterface* CPpsttLogicDevice::GetItem(long nIndex)
{
    CPpsttDataset *pDataset = new CPpsttDataset();
    pDataset->m_pDataset = m_pLogicDevice->GetItem(nIndex);

    return pDataset;
}

CProtocolDatasetInterface* CPpsttLogicDevice::FindDataSet(const CString &strDatasetPath)
{
    CPpsttDataset *pDataset = new CPpsttDataset();
    pDataset->m_pDataset = m_pLogicDevice->FindDataSet(strDatasetPath);

    return pDataset;
}

CProtocolDataInterface* CPpsttLogicDevice::FindData(const CString &strPath)
{
    CPpsttData *pData = new CPpsttData();
    pData->m_pData = m_pLogicDevice->FindData(strPath);

    return pData;
}

CString CPpsttLogicDevice::GetXmlData()
{
    return m_pLogicDevice->GetXmlData();
}

long CPpsttLogicDevice::SetXmlData(const CString &strXmlData)
{
    m_pLogicDevice->SetXmlData(strXmlData);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//CPpsttDevice
CPpsttDevice::CPpsttDevice()
{
    m_pPxiDevice = NULL;
}

CPpsttDevice::~CPpsttDevice()
{
    delete m_pPxiDevice;
    m_pPxiDevice = NULL;
}

void CPpsttDevice::InitCommConfig(CDataGroup *pCommConfig)
{
}

long CPpsttDevice::CommConfig(const CString &strCmmConfig)
{
    return m_pPxiDevice->CommConfig(strCmmConfig);
}

long CPpsttDevice::IsConnectSuccessful()
{
    return m_pPxiDevice->IsConnectSuccessful();
}

long CPpsttDevice::GetCount()
{
    return m_pPxiDevice->GetCount();
}

CProtocolLogicDeviceInterface* CPpsttDevice::GetItem(long nIndex)
{
    CPpsttLogicDevice *pLogicDevice = new CPpsttLogicDevice();
    pLogicDevice->m_pLogicDevice = m_pPxiDevice->GetItem(nIndex);

    return pLogicDevice;
}

CProtocolDatasetInterface* CPpsttDevice::FindDataSet(const CString &strDataSetName)
{
    CPpsttDataset *pDataset = new CPpsttDataset();
    pDataset->m_pDataset = m_pPxiDevice->FindDataSet(strDataSetName);

    return pDataset;
}

CProtocolDataInterface* CPpsttDevice::FindData(const CString &strPath)
{
    CPpsttData *pData = new CPpsttData();
    pData->m_pData = m_pPxiDevice->FindData(strPath);

    return pData;
}

long CPpsttDevice::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
    return m_pPxiDevice->RunProcedure(strProcedureID, strDatasetPath);
}

long CPpsttDevice::RunProcedureEx(const CString &strProcedureScript)
{
    return m_pPxiDevice->RunProcedureEx(strProcedureScript);
}

long CPpsttDevice::AttachSystemWndMsg(unsigned long hWnd, unsigned long nMsgID)
{
    return m_pPxiDevice->AttachSystemWndMsg(hWnd, nMsgID);
}

long CPpsttDevice::RegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID)
{
    return m_pPxiDevice->RegisterProcedureWndMsg(strProcedureID, hWnd, nMsgID);
}

long CPpsttDevice::UnRegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID)
{
    return m_pPxiDevice->UnRegisterProcedureWndMsg(strProcedureID, hWnd, nMsgID);
}

long CPpsttDevice::RegisterDataChangedWndMsg(const CString &strDataPath, unsigned long hWnd, unsigned long nWMsgID)
{
    return m_pPxiDevice->RegisterDataChangedWndMsg(strDataPath, hWnd, nWMsgID);
}

long CPpsttDevice::UnRegisterDataChangedWndMsg(const CString &strDataPath)
{
    return m_pPxiDevice->UnRegisterDataChangedWndMsg(strDataPath);
}

long CPpsttDevice::UnLoad()
{
    return m_pPxiDevice->UnLoad();
}

CString CPpsttDevice::GetXmlData()
{
    return m_pPxiDevice->GetXmlData();
}

long CPpsttDevice::SetXmlData(const CString &bstrXmlData)
{
    m_pPxiDevice->SetXmlData(bstrXmlData);
	return 0;
}

CString CPpsttDevice::GetXmlDataEx(const CString &strDatasetPath)
{
    return m_pPxiDevice->GetXmlDataEx(strDatasetPath);
}

CString CPpsttDevice::SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData)
{
    m_pPxiDevice->SetXmlDataEx(strDatasetPath, strXmlData);
	return _T("");
}

CProtocolParasInterface* CPpsttDevice::GetDataInterface()
{
    CPpsttParas *pParas = new CPpsttParas();
    pParas->m_pDataInterface = m_pPxiDevice->GetDataInterface();

    return  pParas;
}

long CPpsttDevice::ConnectDevice()
{
    return  m_pPxiDevice->ConnectDevice();
}

CString CPpsttDevice::GetAttrByID(const CString &strAttrID)
{
    return  m_pPxiDevice->GetAttrByID(strAttrID);
}

long CPpsttDevice::SetAttrByID(const CString &strAttrID, const CString &strValue)
{
     m_pPxiDevice->SetAttrByID(strAttrID, strValue);
	return 0;
}

long CPpsttDevice::SaveDvmFile(const CString &strDvmFile)
{
     m_pPxiDevice->SaveDvmFile(strDvmFile);
	return 0;
}

long CPpsttDevice::SetCommConfig(const CString &strCommConfig)
{
     m_pPxiDevice->SetCommConfig(strCommConfig);
	return 0;
}

CString CPpsttDevice::GetCommConfig(const CString &strCommConfig)
{
    return  m_pPxiDevice->GetCommConfig();
}

CString CPpsttDevice::GetXmlDataLD()
{
	return _T("");
}

CString CPpsttDevice::GetLogsXml()
{
    return _T("");
}

CString CPpsttDevice::QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName)
{
    return _T("");
}

long CPpsttDevice::SetRecordPath(const CString &strRcdPath)
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//CPpsttEngine
CPpsttEngine::CPpsttEngine()
{
	
}

CPpsttEngine::~CPpsttEngine(void)
{
	
}


CString CPpsttEngine::GetVersion()
{
	return _T("");
}

CProtocolDeviceInterface* CPpsttEngine::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
    CPpsttDevice *pDevice = new CPpsttDevice();
    pDevice->m_pPxiDevice = g_thePxiEngine->CreateDevice(strTemplateFile, strDeviceFile, strDeviceID, NULL);
    AddNewChild(pDevice);

    return pDevice;
}

long CPpsttEngine::GetCount()
{
    return g_thePxiEngine->GetCount();
}

CProtocolDeviceInterface* CPpsttEngine::GetItem(long nIndex)
{
    CPpsttDevice *pDevice = new CPpsttDevice();
    pDevice->m_pPxiDevice = g_thePxiEngine->GetItem(nIndex);
    return pDevice;
}

long CPpsttEngine::ShowSpyWnd(long nShow)
{
    return g_thePxiEngine->ShowSpyWnd(nShow);
}

long CPpsttEngine::ReleaseDevice(const CString &strDeviceID)
{
    return g_thePxiEngine->ReleaseDevice(strDeviceID);
}

long CPpsttEngine::ReleaseAllDevice()
{
    return g_thePxiEngine->ReleaseAllDevice();
}

long CPpsttEngine::CreateProject(const CString &strProjectFile)
{
    return g_thePxiEngine->CreateProject(strProjectFile);
}

long CPpsttEngine::SetProtocolParse(long nStopFlag)
{
    return 0;
}

long CPpsttEngine::ConfigEngine(const CString &strDvmFile)
{
    return 0;
}

long CPpsttEngine::AttatchLogWnd(unsigned long hWnd)
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////
/*  shaolei 移动到PpsttEngineCreator.h中  20220813
//CPpsttEngineCreator
CPpsttEngineCreator::CPpsttEngineCreator()
{
	
}

CPpsttEngineCreator::~CPpsttEngineCreator()
{
	
}

CProtocolEngineInterface* CPpsttEngineCreator::GetProtocolEngine(const CString &strPpEngineProgID)
{
	CProtocolEngineInterface *pEngine = (CProtocolEngineInterface *)FindByID(strPpEngineProgID);

	if (pEngine == NULL)
	{
		if (strPpEngineProgID == g_strSttEngine_PXI)
		{
#ifndef NOT_USE_PPSTTENGINE
			pEngine = new CPpsttEngine;
#endif
		}
		else if(strPpEngineProgID == g_strSttEngine_IOT)
		{
			pEngine = new CPpSttIotEngine;
		}
		else if (strPpEngineProgID == g_strSttEngine_MQTT)
		{
			//pEngine = new CPpSttMqttEngine;
		}

		pEngine->m_strID = strPpEngineProgID;
		AddNewChild(pEngine);
	}

	return pEngine;
}

void CPpsttEngineCreator::ReleasePpEngine(const CString &strProgID)
{
	CProtocolEngineInterface *pEngine = (CProtocolEngineInterface *)FindByID(strProgID);

	if (pEngine != NULL)
	{
		//需增加断开连接等；
		Delete(pEngine);
	}
}

void CPpsttEngineCreator::ReleasePpEngine()
{
	POS pos = GetHeadPosition();
	CProtocolEngineInterface *pEngine = NULL;

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		//需增加断开连接等；
	}

	DeleteAll();
}


void CPpsttEngineCreator::StopProtocolParseForReadSoe(BOOL bStop)
{
	CProtocolEngineInterface *pEngine = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		pEngine->SetProtocolParse(bStop);
	}
}

BOOL CPpsttEngineCreator::HasPpEngine()
{
	return GetCount() > 0;
}

void CPpsttEngineCreator::InitPpEngineShowSpyWnd()
{
	CProtocolEngineInterface *pEngine = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pEngine = (CProtocolEngineInterface *)GetNext(pos);
		pEngine->ShowSpyWnd(g_bShowTestWndTop);
	}
}

 long CPpsttEngineCreator::ConfigEngine()
 {
    return 0;
 }

 */

