#include "stdafx.h"
#include"PpEngine_COM.h"

//////////////////////////////////////////////////////////////////////////
//CPpeParas
CPpeParas::CPpeParas()
{
	m_oDataInterface = NULL;
}

CPpeParas::~CPpeParas()
{
	m_oDataInterface = NULL;
}

long CPpeParas::Reset()
{
	return m_oDataInterface.Reset();
}

long CPpeParas::AddData(const CString &bstrID, const CString &bstrValue)
{
	return m_oDataInterface.AddData(bstrID, bstrValue);
}

//////////////////////////////////////////////////////////////////////////
//CPpeValue
CPpeValue::CPpeValue()
{
}

CPpeValue::~CPpeValue()
{
}

CString CPpeValue::GetName()
{
	return 0;
}

void CPpeValue::SetName(CString propVal)
{

}

CString CPpeValue::GetID()
{
	return _T("");
}

void CPpeValue::SetID(CString propVal)
{

}

CString CPpeValue::GetDataType()
{
	return _T("");
}

void CPpeValue::SetDataType(CString propVal)
{
	
}

CString CPpeValue::GetValue()
{
	return _T("");
}

void CPpeValue::SetValue(CString propVal)
{

}

CString CPpeValue::GetUnit()
{
	return _T("");
}

void CPpeValue::SetUnit(CString propVal)
{
	
}

//////////////////////////////////////////////////////////////////////////
//CPpeData
CPpeData::CPpeData()
{
	m_oData = NULL;
}

CPpeData::~CPpeData()
{
	m_oData = NULL;
}


long CPpeData::GetCount()
{
	return m_oData.GetCount();
}

CProtocolValueInterface* CPpeData::GetItem(long nIndex)
{
	CPpeValue *pNew = new CPpeValue;
	pNew->m_oValue = m_oData.GetItem(nIndex);

	return pNew;
}

long CPpeData::RegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID)
{
	return m_oData.RegisterDataChangedWndMsg(hWnd, nWMsgID);
}

long CPpeData::UnRegisterDataChangedWndMsg()
{
	return m_oData.UnRegisterDataChangedWndMsg();
}

CString CPpeData::GetName()
{
	return m_oData.GetName();
}

void CPpeData::SetName(CString propVal)
{
	m_oData.SetName(propVal);
}

CString CPpeData::GetID()
{
	return m_oData.GetID();
}

void CPpeData::SetID(CString propVal)
{
	m_oData.SetID(propVal);
}

CString CPpeData::GetDataType()
{
	return m_oData.GetDataType();
}

void CPpeData::SetDataType(CString propVal)
{
	m_oData.SetDataType(propVal);
}

CString CPpeData::GetValue()
{
	return m_oData.GetValue();
}

void CPpeData::SetValue(CString propVal)
{
	m_oData.SetValue(propVal);
}

CString CPpeData::GetUnit()
{
	return m_oData.GetUnit();
}

void CPpeData::SetUnit(CString propVal)
{
	m_oData.SetUnit(propVal);
}

CString CPpeData::GetMinValue()
{
	return m_oData.GetMinValue();
}

void CPpeData::SetMinValue(CString propVal)
{
	m_oData.SetMinValue(propVal);
}

CString CPpeData::GetMaxValue()
{
	return m_oData.GetMaxValue();
}

void CPpeData::SetMaxValue(CString propVal)
{
	m_oData.SetMaxValue(propVal);
}

//////////////////////////////////////////////////////////////////////////
//CPpeDataset
CPpeDataset::CPpeDataset()
{
	
}

CPpeDataset::~CPpeDataset()
{
	
}

long CPpeDataset::GetCount()
{
	return m_oDataset.GetCount();
}

CProtocolDataInterface* CPpeDataset::GetItem(long nIndex)
{
	CPpeData *pNew = new CPpeData;
	pNew->m_oData = m_oDataset.GetItem(nIndex);

	return pNew;
}

CProtocolDataInterface* CPpeDataset::FindDataByID(const CString &strDataID)
{
	CPpeData *pNew = new CPpeData;
	pNew->m_oData = m_oDataset.FindDataByID(strDataID);

	return pNew;
}

CProtocolDataInterface* CPpeDataset::FindDataByName(const CString &strName)
{
	CPpeData *pNew = new CPpeData;
	pNew->m_oData = m_oDataset.FindDataByName(strName);

	return pNew;
}

CString CPpeDataset::GetXmlData()
{
	return m_oDataset.GetXmlData();
}

long CPpeDataset::SetXmlData(const CString &strXmlData)
{
	return m_oDataset.SetXmlData(strXmlData);
}

long CPpeDataset::DeleteAllDatas()
{
	return m_oDataset.DeleteAllDatas();
}



CPpeLogicDevice::CPpeLogicDevice()
{
	
}

CPpeLogicDevice::~CPpeLogicDevice()
{
	
}

long CPpeLogicDevice::GetCount()
{
	return 0;
}

CProtocolDatasetInterface* CPpeLogicDevice::GetItem(long nIndex)
{
	return 0;
}

CProtocolDatasetInterface* CPpeLogicDevice::FindDataSet(const CString &strDatasetPath)
{
	return 0;
}

CProtocolDataInterface* CPpeLogicDevice::FindData(const CString &strPath)
{
	return 0;
}

CString CPpeLogicDevice::GetXmlData()
{
	return 0;
}

long CPpeLogicDevice::SetXmlData(const CString &strXmlData)
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//CPpeDevice
CPpeDevice::CPpeDevice()
{
	m_oPpDevice = NULL;
}

CPpeDevice::~CPpeDevice()
{
	try
	{
		m_oPpDevice = NULL;
	}
	catch (...)
	{
		
	}
}

void CPpeDevice::InitCommConfig(CDataGroup *pCommConfig)
{

}

long CPpeDevice::CommConfig(const CString &strCmmConfig)
{
	return m_oPpDevice.CommConfig(strCmmConfig);
}

long CPpeDevice::IsConnectSuccessful()
{
	return m_oPpDevice.IsConnectSuccessful();
}

long CPpeDevice::GetCount()
{
	return 0;
}

CProtocolLogicDeviceInterface* CPpeDevice::GetItem(long nIndex)
{
	return NULL;
}

CProtocolDatasetInterface* CPpeDevice::FindDataSet(const CString &strDataSetName)
{
	CPpeDataset *pNew = new CPpeDataset();
	pNew->m_oDataset = m_oPpDevice.FindDataSet(strDataSetName);
	//AddNewChild(pNew);
	return pNew;
}

CProtocolDataInterface* CPpeDevice::FindData(const CString &strPath)
{
	CPpeData *pNew = new CPpeData();
	pNew->m_oData = m_oPpDevice.FindData(strPath);
	//AddNewChild(pNew);
	return pNew;
}

long CPpeDevice::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
	return m_oPpDevice.RunProcedure(strProcedureID, strDatasetPath);
}

long CPpeDevice::RunProcedureEx(const CString &strProcedureScript)
{
	return m_oPpDevice.RunProcedureEx(strProcedureScript);
}

long CPpeDevice::AttachSystemWndMsg(unsigned long hWnd, unsigned long nMsgID)
{
	return m_oPpDevice.AttachSystemWndMsg(hWnd, nMsgID);
}

long CPpeDevice::RegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID)
{
	return m_oPpDevice.RegisterProcedureWndMsg(strProcedureID, hWnd, nMsgID);
}

long CPpeDevice::UnRegisterProcedureWndMsg(const CString &strProcedureID, unsigned long hWnd, unsigned long nMsgID)
{
	return m_oPpDevice.UnRegisterProcedureWndMsg(strProcedureID, hWnd, nMsgID);
}

long CPpeDevice::RegisterDataChangedWndMsg(const CString &strDataPath, unsigned long hWnd, unsigned long nWMsgID)
{
	return m_oPpDevice.RegisterDataChangedWndMsg(strDataPath, hWnd, nWMsgID);
}

long CPpeDevice::UnRegisterDataChangedWndMsg(const CString &strDataPath)
{
	return m_oPpDevice.UnRegisterDataChangedWndMsg(strDataPath);
}

long CPpeDevice::UnLoad()
{
	return m_oPpDevice.UnLoad();
}

CString CPpeDevice::GetXmlData()
{
	return m_oPpDevice.GetXmlData();
}

long CPpeDevice::SetXmlData(const CString &bstrXmlData)
{
	return m_oPpDevice.SetXmlData(bstrXmlData);
}

CString CPpeDevice::GetXmlDataEx(const CString &strDatasetPath)
{
	return m_oPpDevice.GetXmlDataEx(strDatasetPath);
}

CString CPpeDevice::SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData)
{
	return m_oPpDevice.SetXmlDataEx(strDatasetPath, strXmlData);
}

CProtocolParasInterface* CPpeDevice::GetDataInterface()
{
	CPpeParas *pParas = new CPpeParas;
	pParas->m_oDataInterface = m_oPpDevice.GetDataInterface();
	AddNewChild(pParas);
	return pParas;
}

long CPpeDevice::ConnectDevice()
{
	return m_oPpDevice.ConnectDevice();
}

CString CPpeDevice::GetAttrByID(const CString &strAttrID)
{
	return m_oPpDevice.GetAttrByID(strAttrID);
}

long CPpeDevice::SetAttrByID(const CString &strAttrID, const CString &strValue)
{
	return m_oPpDevice.SetAttrByID(strAttrID, strValue);
}

long CPpeDevice::SaveDvmFile(const CString &strDvmFile)
{
	return m_oPpDevice.SaveDvmFile(strDvmFile);
}

long CPpeDevice::SetCommConfig(const CString &strCommConfig)
{
	return m_oPpDevice.SetCommConfig(strCommConfig);
}

CString CPpeDevice::GetCommConfig(const CString &strCommConfig)
{
	return m_oPpDevice.GetCommConfig(strCommConfig);
}

CString CPpeDevice::GetXmlDataLD()
{
	return m_oPpDevice.GetXmlDataLD();
}

CString CPpeDevice::GetLogsXml()
{
	return m_oPpDevice.GetLogsXml();
}

CString CPpeDevice::QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName)
{
	return m_oPpDevice.QueryRecord(strBeginTime, strEndTime, strRcdFileName);
}

long CPpeDevice::SetRecordPath(const CString &strRcdPath)
{
	return m_oPpDevice.SetRecordPath(strRcdPath);
}

//////////////////////////////////////////////////////////////////////////
//CPpeEngine
CPpeEngine::CPpeEngine()
{
	m_oEngine = NULL;
}

CPpeEngine::~CPpeEngine(void)
{
	try
	{
		m_oEngine = NULL;
	}
	catch (...)
	{		
	}
}

CString CPpeEngine::GetVersion()
{
	return m_oEngine.GetVersion();
}

CProtocolDeviceInterface* CPpeEngine::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	if (m_oEngine == NULL)
	{
		return NULL;
	}

	CPpeDevice *pDevice = new CPpeDevice();
	pDevice->m_oPpDevice = m_oEngine.CreateDevice(strTemplateFile, strDeviceFile, strDeviceID);
	AddNewChild(pDevice);

	return pDevice;
}

//2023-3-16 lijunqing
CProtocolDeviceInterface* CPpeEngine::CreateDevice(CPpSttCommConfig *pCommConfig)
{
	return NULL;
}


long CPpeEngine::GetCount()
{
	return m_oEngine.GetCount();
}

CProtocolDeviceInterface* CPpeEngine::GetItem(long nIndex)
{
	//return m_oEngine.GetItem(nIndex);
	return NULL;
}

long CPpeEngine::ShowSpyWnd(long nShow)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	return m_oEngine.ShowSpyWnd(nShow);
}

long CPpeEngine::ReleaseDevice(const CString &strDeviceID)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	return m_oEngine.ReleaseDevice(strDeviceID);
}

long CPpeEngine::ReleaseAllDevice()
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	return m_oEngine.ReleaseAllDevice();
}

long CPpeEngine::CreateProject(const CString &strProjectFile)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	return m_oEngine.CreateProject(strProjectFile);
}

long CPpeEngine::SetProtocolParse(long nStopFlag)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	return m_oEngine.SetProtocolParse(nStopFlag);
}

long CPpeEngine::ConfigEngine(const CString &strDvmFile)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	long nRet = 0;

	try
	{
		nRet = m_oEngine.ConfigEngine(strDvmFile);
	}
	catch (...)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("被测装置通信配置失败"));
	}
	
	return nRet;
}

long CPpeEngine::AttatchLogWnd(unsigned long hWnd)
{
	if (m_oEngine == NULL)
	{
		return 0;
	}

	long nRet = 0;

	try
	{
		nRet = m_oEngine.AttatchLogWnd(hWnd);
	}
	catch (...)
	{
	}

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//CPpeEngineCreator
CPpeEngineCreator::CPpeEngineCreator()
{
	
}

CPpeEngineCreator::~CPpeEngineCreator()
{
	
}

CProtocolEngineInterface* CPpeEngineCreator::GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID)
{
	m_oPpEngineCreateMngr.m_hLogWnd = m_hLogWnd;

	CPpeEngine *pFind = (CPpeEngine*)FindByID(strPpEngineProgID);

	if (pFind != NULL)
	{
		if (pFind->m_oEngine != NULL)
		{
			return pFind;
		}
	}

	if (pFind == NULL)
	{
		pFind = new CPpeEngine();
		AddNewChild(pFind);
	}

	pFind->m_oEngine = m_oPpEngineCreateMngr.GetPpEngine(strPpEngineProgID);

	if (pFind->m_oEngine == NULL)
	{
		Delete(pFind);
		return NULL;
	}

	pFind->m_strID = strPpEngineProgID;

	return pFind;
}

void CPpeEngineCreator::ReleasePpEngine(const CString &strProgID)
{
	try
	{
		m_oPpEngineCreateMngr.ReleasePpEngine(strProgID);
	}
	catch (...)
	{

	}
}

void CPpeEngineCreator::ReleasePpEngine()
{
	try
	{
		m_oPpEngineCreateMngr.ReleasePpEngine();
		DeleteAll();
	}
	catch (...)
	{
		
	}
}

void CPpeEngineCreator::StopProtocolParseForReadSoe(BOOL bStop)
{
	m_oPpEngineCreateMngr.StopProtocolParseForReadSoe(bStop);
}

BOOL CPpeEngineCreator::HasPpEngine()
{
	return m_oPpEngineCreateMngr.HasPpEngine();
}

void CPpeEngineCreator::InitPpEngineShowSpyWnd()
{
	POS pos = m_oPpEngineCreateMngr.GetHeadPosition();
	CPpEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)m_oPpEngineCreateMngr.GetNext(pos);
		p->ShowSpyWnd();
	}
}

long CPpeEngineCreator::ConfigEngine()
{
	m_oPpEngineCreateMngr.ConfigEngine();
	return 0;
}

long CPpeEngineCreator::AttatchLogWnd(unsigned long hWnd)
{
	POS pos = m_oPpEngineCreateMngr.GetHeadPosition();
	CPpEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)m_oPpEngineCreateMngr.GetNext(pos);
		p->AttatchLogWnd(hWnd);
	}

	return 0;
}