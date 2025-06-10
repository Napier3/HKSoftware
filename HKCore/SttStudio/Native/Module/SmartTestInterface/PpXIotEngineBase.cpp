#include "stdafx.h"
#include"PpXIotEngineBase.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//CPpSttIotParas
CPpSttIotParas::CPpSttIotParas()
{
	m_pDataInterface = NULL;
}

CPpSttIotParas::~CPpSttIotParas()
{ 
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->DeleteAll();
		m_pDataInterface = NULL;
	}
}

long CPpSttIotParas::Reset()
{
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->DeleteAll();
	}
	
	return 0;
}

long CPpSttIotParas::AddData(const CString &bstrID, const CString &bstrValue)
{
	if (m_pDataInterface != NULL)
	{
		CDvmValue *pVariable = new CDvmValue();
		pVariable->m_strID = bstrID;
		pVariable->m_strValue = bstrValue;
		m_pDataInterface->AddHead(pVariable);
	}

	return 0;
}

long CPpSttIotParas::AddData(const CString &bstrID, long nValue)
{
	if (m_pDataInterface == NULL)
	{
		return 0;
	}

	CDvmValue *pVariable = new CDvmValue();
	pVariable->m_strID = bstrID;
	pVariable->m_strValue.Format(_T("%d"), nValue);
	m_pDataInterface->AddHead(pVariable);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//CPpSttIotValue
CPpSttIotValue::CPpSttIotValue()
{
   // m_pValue = NULL;
}

CPpSttIotValue::~CPpSttIotValue()
{
    //delete m_pValue;
    //m_pValue = NULL;
}

CString CPpSttIotValue::GetName()
{
    return _T("");
}

void CPpSttIotValue::SetName(CString propVal)
{

}

CString CPpSttIotValue::GetID()
{
	return _T("");
}

void CPpSttIotValue::SetID(CString propVal)
{

}

CString CPpSttIotValue::GetDataType()
{
	return _T("");
}

void CPpSttIotValue::SetDataType(CString propVal)
{
	
}

CString CPpSttIotValue::GetValue()
{
	return _T("");
}

void CPpSttIotValue::SetValue(CString propVal)
{
    //m_pValue->SetValue(propVal);
}

CString CPpSttIotValue::GetUnit()
{
	return _T("");
    //return m_pValue->GetUnit();
}

void CPpSttIotValue::SetUnit(CString propVal)
{
    //m_pValue->SetUnit(propVal);
}

//////////////////////////////////////////////////////////////////////////
//CPpSttIotData
CPpSttIotData::CPpSttIotData()
{
    //m_pData = NULL;
}

CPpSttIotData::~CPpSttIotData()
{
    //delete m_pData;
   // m_pData = NULL;
}


long CPpSttIotData::GetCount()
{
    return GetCount();
}

CProtocolValueInterface* CPpSttIotData::GetItem(long nIndex)
{
    CPpSttIotValue *pValue = new CPpSttIotValue();
    //pValue->m_pValue = m_pData->GetItem(nIndex);

    return pValue;
}

long CPpSttIotData::RegisterDataChangedWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nWMsgID)
{
    //m_pData->RegisterDataChangedWndMsg(hWnd, nWMsgID);
	return 0;
}

long CPpSttIotData::UnRegisterDataChangedWndMsg()
{
    //m_pData->UnRegisterDataChangedWndMsg();
	return 0;
}

CString CPpSttIotData::GetName()
{
	return _T("");
    //return m_pData->GetName();
}

void CPpSttIotData::SetName(CString propVal)
{
    //m_pData->SetName(propVal);
}

CString CPpSttIotData::GetID()
{
	return _T("");
    //return m_pData->GetID();
}

void CPpSttIotData::SetID(CString propVal)
{
    //m_pData->SetID(propVal);
}

CString CPpSttIotData::GetDataType()
{
	return _T("");
    //return m_pData->GetDataType();
}

void CPpSttIotData::SetDataType(CString propVal)
{
    //m_pData->SetDataType(propVal);
}

CString CPpSttIotData::GetValue()
{
	return _T("");
    //return m_pData->GetValue();
}

void CPpSttIotData::SetValue(CString propVal)
{
    //m_pData->SetValue(propVal);
}

CString CPpSttIotData::GetUnit()
{
	return _T("");
    //return m_pData->GetUnit();
}

void CPpSttIotData::SetUnit(CString propVal)
{
    //m_pData->SetUnit(propVal);
}

CString CPpSttIotData::GetMinValue()
{
	return _T("");
    //return m_pData->GetMinValue();
}

void CPpSttIotData::SetMinValue(CString propVal)
{
    //m_pData->SetMinValue(propVal);
}

CString CPpSttIotData::GetMaxValue()
{
	return _T("");
    //return m_pData->GetMaxValue();
}

void CPpSttIotData::SetMaxValue(CString propVal)
{
    //m_pData->SetMaxValue(propVal);
}

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDataset
CPpSttIotDataset::CPpSttIotDataset()
{
	m_pDataset = NULL;
}

CPpSttIotDataset::~CPpSttIotDataset()
{
	
}

void CPpSttIotDataset::Release()
{
	//目前没有通过ClassID去判，因为父对象只可能是CPpSttIotDeviceBase
	CPpSttIotDeviceBase *pParent = (CPpSttIotDeviceBase*)GetParent();

	if (pParent != NULL)
	{
		//pParent->m_listDataset.Delete(m_pDataset);
		pParent->Delete(this);
	}
	else
	{
		delete this;
	}
}

long CPpSttIotDataset::GetCount()
{
    return GetCount();
}

CProtocolDataInterface* CPpSttIotDataset::GetItem(long nIndex)
{
    CPpSttIotData *pData = new CPpSttIotData();

    return pData;
}

CProtocolDataInterface* CPpSttIotDataset::FindDataByID(const CString &strDataID)
{
    CPpSttIotData *pData = new CPpSttIotData();
    //pData->m_pData = m_oDataset->FindDataByID(strDataID);

    return pData;
}

CProtocolDataInterface* CPpSttIotDataset::FindDataByName(const CString &strName)
{
    CPpSttIotData *pData = new CPpSttIotData();
    //pData->m_pData = m_oDataset->FindDataByName(strName);

    return pData;
}

CString CPpSttIotDataset::GetXmlData()
{
	CString strResult;
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();
	m_pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strResult);
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	return strResult;
}

long CPpSttIotDataset::SetXmlData(const CString &strXmlData)
{
	m_pDataset->DeleteAll();
    BSTR bstrText = strXmlData.AllocSysString();
    m_pDataset->SetXml(bstrText, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
#ifdef _PSX_IDE_QT_
    delete bstrText;
#else
    SysFreeString(bstrText);// 用完释放
#endif

	CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase*)GetParent();
	pDevice->m_pWriteDataset = m_pDataset;

	return 0;
}

long CPpSttIotDataset::DeleteAllDatas()
{
	return 0;
}

void CPpSttIotDataset::UpdateDataset(CDvmDataset *pDataset)
{
	if (pDataset != NULL && m_pDataset != NULL)
	{//简单处理，只发送需要设置的数据
		m_pDataset->DeleteAll();

		POS pos = pDataset->GetHeadPosition();
		CDvmData *p = NULL;

		while (pos != NULL)
		{
			p = (CDvmData *)pDataset->GetNext(pos);

			if (p->m_nChange == 1)
			{
				m_pDataset->AddNewChild((CExBaseObject*)p->Clone());
			}
		}
	
		//2022-11-20  lijunqing 设置当前修改的数据集
		CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase*)GetParent();
		pDevice->m_pWriteDataset = m_pDataset;
	}
}

BOOL CPpSttIotDataset::UpdateData_Single(CDvmData *pData)
{
	if (m_pDataset == NULL)
	{
		return FALSE;
	}

	m_pDataset->DeleteAll();
	m_pDataset->AddNewChild((CExBaseObject*)pData->Clone());
	//2022-11-20  lijunqing 设置当前修改的数据集
	CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase*)GetParent();
	pDevice->m_pWriteDataset = m_pDataset;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////
/// CPpSttIotLogicDevice
CPpSttIotLogicDevice::CPpSttIotLogicDevice()
{
    //m_pLogicDevice = NULL;
}

CPpSttIotLogicDevice::~CPpSttIotLogicDevice()
{
    //delete m_pLogicDevice;
   // m_pLogicDevice = NULL;
}

long CPpSttIotLogicDevice::GetCount()
{
	return 0;
    //return m_pLogicDevice->GetCount();
}

CProtocolDatasetInterface* CPpSttIotLogicDevice::GetItem(long nIndex)
{
    CPpSttIotDataset *pDataset = new CPpSttIotDataset();
    //pDataset->m_oDataset = m_pLogicDevice->GetItem(nIndex);

    return pDataset;
}

CProtocolDatasetInterface* CPpSttIotLogicDevice::FindDataSet(const CString &strDatasetPath)
{
    CPpSttIotDataset *pDataset = new CPpSttIotDataset();
    //pDataset->m_oDataset = m_pLogicDevice->FindDataSet(strDatasetPath);

    return pDataset;
}

CProtocolDataInterface* CPpSttIotLogicDevice::FindData(const CString &strPath)
{
    CPpSttIotData *pData = new CPpSttIotData();
    //pData->m_pData = m_pLogicDevice->FindData(strPath);

    return pData;
}

CString CPpSttIotLogicDevice::GetXmlData()
{
	return _T("");
    //return m_pLogicDevice->GetXmlData();
}

long CPpSttIotLogicDevice::SetXmlData(const CString &strXmlData)
{
   // m_pLogicDevice->SetXmlData(strXmlData);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceBase
CPpSttIotDeviceBase::CPpSttIotDeviceBase()
{
	m_pWriteDataset = NULL;
	m_hSysMsgWnd = 0;
	m_hMsgWnd = 0;
	m_bIsSvrDeviceConnectSucc = FALSE;
    m_nSttCmdDataFormat = _JSON_TYPE_;//TDM：暂时写死为JSON/*_PUGI_XML_TYPE_;*/

	m_nZoneIndex = -1;
	m_oSoeReports.SetMaxCount(-1);
}

CPpSttIotDeviceBase::~CPpSttIotDeviceBase()
{
    //CloseDevice();
	DisConnect();
}

void CPpSttIotDeviceBase::NewSttIotClient()
{
   
}

void CPpSttIotDeviceBase::SetSttCmdDataFormat(long nSttCmdForat)
{
    m_nSttCmdDataFormat = nSttCmdForat;
}

BOOL CPpSttIotDeviceBase::ConnectSttServer()
{
	return TRUE;
}

/*
<iot-cmd name="" id="CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="EngineProgID" name="" value="IotEngine.PoEngine"/>
		<data id="ProtocolID" name="" value="WSD.iotxml$IotEngine.PoEngine"/>
		<data id="ppxml-file" name="规则文件" value="WSD.iotxml"/>
		<data id="ppxml-file_s" name="规则文件" value="/profile/upload/2021/07/31/4e42cc98113b4bfa8fe90ec5e13447ec.iotxml"/>
		<data id="dvm-file" name="" value="WSD.xml"/>
		<data id="dvm-file_s" name="" value="/profile/upload/2021/07/31/360770cc768a45fab98c0db2277a2780.xml"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
	</paras>
</iot-cmd>
*/
long CPpSttIotDeviceBase::CommConfig(const CString &strCmmConfig)
{
	if (strCmmConfig.GetLength() > 0)
	{
		//初始化m_oCommConfig
		CDataGroup oCommConfig;
		 BSTR bstrCmmConfig = strCmmConfig.AllocSysString();

		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		oCommConfig.SetXml(bstrCmmConfig, CDataMngrXmlRWKeys::CDataGroupKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

#ifdef _PSX_IDE_QT_
		delete bstrCmmConfig;
#else
		SysFreeString(bstrCmmConfig);
#endif

		//m_oCommConfig.AppendEx(oCommConfig, TRUE);
		m_oCommConfig.InitDataValues(&oCommConfig, TRUE);
		oCommConfig.RemoveAll();
	}

    NewSttIotClient();

	//连接服务器
    long nRet = ConnectSttServer();

	if (! nRet)
	{
		return FALSE;
	}

	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_CreateDevice;

	if (m_oCommConfig.GetCount() > 0)
	{
		oIotCmd.AppendParas2(m_oCommConfig, TRUE);
	}
	else
	{
		CSttParas *pParas = oIotCmd.GetSttParas();
		pParas->AddNewData(STT_CMD_PARA_DeviceSN, m_strID);
		pParas->AddNewData(STT_CMD_PARA_EngineProgID, g_strSttEngine_IOT);
	}
	
    nRet = X_SendIotCmd(oIotCmd);

    //for debug begin
    if(nRet > 0)
    {
        CString strFile;
        strFile = _P_GetLibraryPath();
        strFile += _T("oIotCmdFile_CommConfig.xml");
        oIotCmd.SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    }
    //for debug end

/*
	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		//PostDeviceSysMessage(0, engineConnectDeviceSuccessful);
	}
	else
	{
		PostDeviceSysMessage(0, engineConnectDeviceFailed);
	}
*/

	//shaolei 20230509  注释此处  这个是干啥的？
//     CSttTestEngineClientData *pEngineData = m_pSttIotClient->GetTestEngineClient();
//     pEngineData->m_pSttClientSocket->IsSocketValid();

	return nRet;
}

long CPpSttIotDeviceBase::IsConnectSuccessful()
{
	return m_bIsSvrDeviceConnectSucc;
}

long CPpSttIotDeviceBase::GetCount()
{
	return GetCount();
}

CProtocolLogicDeviceInterface* CPpSttIotDeviceBase::GetItem(long nIndex)
{
    CPpSttIotLogicDevice *pLogicDevice = new CPpSttIotLogicDevice();
    //pLogicDevice->m_pLogicDevice = m_pPxiDevice->GetItem(nIndex);

    return pLogicDevice;
}

CProtocolDatasetInterface* CPpSttIotDeviceBase::FindDataSet(const CString &strDataSetName)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("CPpSttIotDeviceBase::FindDataSet======%s"), strDataSetName.GetString());
	//strDataSetName，是由自动测试这边传过来的数据集路径，一般包含逻辑设备的路径，例如：IecRcd$dsSV1
	CString strID = strDataSetName;
	CDvmDataset *pFind = FindDataSet2(strID);

	if (pFind == NULL)
	{
		pFind = new CDvmDataset();
		pFind->m_strID = strID;
		pFind->m_strName = strID;
		m_listDataset.AddTail(pFind);
	}

// 	CString strFile = _P_GetLibraryPath();
// 	strFile += _T("00_00.XML");
// 	pFind->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	CPpSttIotDataset *pDataset = new CPpSttIotDataset;
	pDataset->m_strID = strID;
	AddNewChild(pDataset);
	pDataset->m_pDataset = pFind;

    return pDataset;
}

CProtocolDataInterface* CPpSttIotDeviceBase::FindData(const CString &strPath)
{
	return NULL;
    //CPpSttIotData *pData = new CPpSttIotData();
    //pData->m_pData = m_pPxiDevice->FindData(strPath);

   // return pData;
}

/*
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
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
*/
long CPpSttIotDeviceBase::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
    if (! IsConnectSuccessful())
    {
        PostDeviceCommCmdMessage(0, engineCommError);
        return 0;
    }

	m_strCurrProcedureID = strProcedureID;
	long nRet = 0;
	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_RunProcedure;
	CSttParas *pParas = oIotCmd.GetSttParas();

	//<data id="id-procedure" value="WriteSetting">【执行的通信过程】
	CDvmData *pPara = pParas->AddNewData(STT_CMD_PARA_ProcedureID, strProcedureID);
	if (m_listDataInterface.GetCount() > 0)
	{
		pPara->AppendCloneEx(m_listDataInterface);
		m_listDataInterface.DeleteAll();  //用完立即释放
	}

	//<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
	pParas->AddNewData(STT_CMD_PARA_DatasetPath, strDatasetPath);

	//<dataset id="LLN0$dsSetting1" name="">
	if (m_pWriteDataset != NULL)
	{
		pParas->AddTail(m_pWriteDataset);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SendIotCmd %s begin"), m_strCurrProcedureID.GetString());
    nRet = X_SendIotCmd(oIotCmd);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SendIotCmd %s finish"), m_strCurrProcedureID.GetString());

	if (m_pWriteDataset != NULL)
	{
		pParas->Remove(m_pWriteDataset);
		m_pWriteDataset = NULL;
	}
	
/*
	if (nRet != STT_CMD_ExecStatus_SUCCESS)
	{
		PostDeviceCommCmdMessage(0, engineCommError);
	}
*/

	return nRet;
}

long CPpSttIotDeviceBase::RunProcedureEx(const CString &strProcedureScript)
{
	return 0;
    //return m_pPxiDevice->RunProcedureEx(strProcedureScript);
}

long CPpSttIotDeviceBase::AttachSystemWndMsg(PSX_OBJ_ADDR hWnd, unsigned long nMsgID)
{
	m_hSysMsgWnd = hWnd;
	m_nSysMsgID = nMsgID;

	return 0;
}

long CPpSttIotDeviceBase::RegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID)
{
	m_hMsgWnd = hWnd;
	m_nMsgID = nMsgID;

	return 0;
}

long CPpSttIotDeviceBase::UnRegisterProcedureWndMsg(const CString &strProcedureID, PSX_OBJ_ADDR hWnd, unsigned long nMsgID)
{
	m_hMsgWnd = NULL;
	m_nMsgID = 0;

	return 0;
}

long CPpSttIotDeviceBase::RegisterDataChangedWndMsg(const CString &strDataPath, PSX_OBJ_ADDR hWnd, unsigned long nWMsgID)
{
	return 0;
}

long CPpSttIotDeviceBase::UnRegisterDataChangedWndMsg(const CString &strDataPath)
{
	return 0;
}

long CPpSttIotDeviceBase::UnLoad()
{
	CloseDevice();

	return 0;
}

CString CPpSttIotDeviceBase::GetXmlData()
{
	return _T("");
    //return m_pPxiDevice->GetXmlData();
}

long CPpSttIotDeviceBase::SetXmlData(const CString &bstrXmlData)
{
    //m_pPxiDevice->SetXmlData(bstrXmlData);
	return 0;
}

CString CPpSttIotDeviceBase::GetXmlDataEx(const CString &strDatasetPath)
{
	return _T("");
    //return m_pPxiDevice->GetXmlDataEx(strDatasetPath);
}

CString CPpSttIotDeviceBase::SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData)
{
    //m_pPxiDevice->SetXmlDataEx(strDatasetPath, strXmlData);
	return _T("");
}

CProtocolParasInterface* CPpSttIotDeviceBase::GetDataInterface()
{
	CProtocolParasInterface *pParas = CPpSttIotParas::_New_ParasInterface(&m_listDataInterface);

    return  pParas;
}

long CPpSttIotDeviceBase::ConnectDevice()
{
	return CommConfig(_T(""));
}

CString CPpSttIotDeviceBase::GetAttrByID(const CString &strAttrID)
{
    return _T("");
    //return  m_pPxiDevice->GetAttrByID(strAttrID);
}

long CPpSttIotDeviceBase::SetAttrByID(const CString &strAttrID, const CString &strValue)
{
    //m_pPxiDevice->SetAttrByID(strAttrID, strValue);
	return 0;
}

long CPpSttIotDeviceBase::SaveDvmFile(const CString &strDvmFile)
{
    //m_pPxiDevice->SaveDvmFile(strDvmFile);
	return 0;
}

long CPpSttIotDeviceBase::SetCommConfig(const CString &strCommConfig)
{
    //m_pPxiDevice->SetCommConfig(strCommConfig);
	return 0;
}

CString CPpSttIotDeviceBase::GetCommConfig(const CString &strCommConfig)
{
	return _T("");
    //return  m_pPxiDevice->GetCommConfig();
}

CString CPpSttIotDeviceBase::GetXmlDataLD()
{
	return _T("");
}

CString CPpSttIotDeviceBase::GetLogsXml()
{
    return _T("");
}

CString CPpSttIotDeviceBase::QueryRecord(const CString &strBeginTime, const CString &strEndTime, const CString &strRcdFileName)
{
    return _T("");
}

long CPpSttIotDeviceBase::SetRecordPath(const CString &strRcdPath)
{
    return 0;
}

BOOL CPpSttIotDeviceBase::IsConnectIotServerSucc()
{
   return FALSE;
}

void CPpSttIotDeviceBase::On_SysState_IOT(CSttSysState *pSysState)
{
	long nCmdExecState = pSysState->Get_ExecStatus();

	if (Stt_Is_ExecStatus_Ack(nCmdExecState))
	{
		return;
	}

	if (Stt_Is_ExecStatus_Failure(nCmdExecState)
		|| Stt_Is_ExecStatus_Timeout(nCmdExecState))
	{
		if (pSysState->m_strID == STT_CMD_TYPE_IOT_CreateDevice)
		{
			PostDeviceSysMessage(0, engineConnectDeviceFailed);
		}
		else
		{
			PostDeviceCommCmdMessage(0, engineCommError);
		}

		return;
	}

	if (pSysState->m_strID == STT_CMD_TYPE_IOT_RunProcedure)
	{
		On_SysState_IOT_RunProcedure(pSysState);
	}
	else if (pSysState->m_strID == STT_CMD_TYPE_IOT_GetDataset)
	{
		On_SysState_Test_GetDataset(pSysState);
	}
	else if (pSysState->m_strID == STT_CMD_TYPE_IOT_CreateDevice)
	{
		On_SysState_IOT_CreateDevice(pSysState);
	}
	else if (pSysState->m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{
		On_SysState_IOT_CloseDevice(pSysState);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnEngineEvent)
	{
		On_SysState_IOT_OnEngineEvent(pSysState);
	}

}

BOOL CPpSttIotDeviceBase::On_SysState_Test_GetDataset(CSttSysState *pSysState)
{
	BOOL bRet = GetDatasetFromParas(pSysState);

	if (bRet)
	{	
		PostDeviceCommCmdMessage(0, engineCommFinish);
	}
	else
	{
		PostDeviceCommCmdMessage(0, engineCommError);
	}

	return TRUE;
}

BOOL CPpSttIotDeviceBase::On_SysState_IOT_CreateDevice(CSttSysState *pSysState)
{
	CSttParas *pSttParas = pSysState->GetSttParas();
	CString strState;

	if (pSttParas->GetDataValue(STT_SYS_STATE_ID_ConnectState, strState))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("+++debug+++ConnectState = %s"), strState.GetString());
		if (strState == EngineSysState_ConnectSuccessful)
		{
			m_bIsSvrDeviceConnectSucc = TRUE;
			PostDeviceSysMessage(0, engineConnectDeviceSuccessful);
		}
		else
		{
			m_bIsSvrDeviceConnectSucc = FALSE;
			PostDeviceSysMessage(0, engineConnectDeviceFailed);
		}
	}
	
	return TRUE;
}

BOOL CPpSttIotDeviceBase::On_SysState_IOT_CloseDevice(CSttSysState *pSysState)
{
	CSttParas *pSttParas = pSysState->GetSttParas();
	CString strState;

	if (! pSttParas->GetDataValue(STT_SYS_STATE_ID_ConnectState, strState))
	{//收到连接状态
		return TRUE;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s %s"), pSysState->m_strID.GetString(), strState.GetString());
	m_bIsSvrDeviceConnectSucc = FALSE;

	PostDeviceSysMessage(0, engineConnectDeviceFailed);

	return TRUE;
}

BOOL CPpSttIotDeviceBase::On_SysState_IOT_OnEngineEvent(CSttSysState *pSysState)
{
	//EngineEvent_DvmEnum
	CSttParas *pSttParas = pSysState->GetSttParas();
	CString strEventID;
	
	if (!pSttParas->GetDataValue(SYS_STATE_XEVENT_EVENTID, strEventID))
	{
		return FALSE;
	}

	if (strEventID == EngineEvent_DvmEnumFinish)
	{
		InitDvmDevice(pSttParas);  //2023-2-1 装置枚举完成事件，获取装置模型
		PostDeviceEventMessage(EngineEvent_ID_DvmEnumFinish, EngineEvent_ID_DvmEnumFinish);
	}
	else if (strEventID == EngineEvent_Report)
	{
		CDvmDataset *pReports = pSysState->GetDataset();
		m_oSoeReports.AddExBaseObjects(pReports, TRUE);
		pReports->RemoveAll();
		PostDeviceEventMessage(EngineEvent_ID_Report, EngineEvent_ID_Report);
	}
	else if (strEventID == EngineEvent_ID_ex_ConnectDeviceSuccessful
		|| strEventID == EngineEvent_ID_ex_ConnectDeviceFailed)
	{
		return On_SysState_IOT_CreateDevice(pSysState);
	}

	return TRUE;
}

BOOL CPpSttIotDeviceBase::GetDatasetFromParas(CSttSysState *pSysState)
{
// 	if (IsCurrProcedure_Write())
// 	{
// 		return TRUE;
// 	}

	CSttParas *pParas = pSysState->GetSttParas();
	CDvmDataset *pDataset = (CDvmDataset*)pParas->FindByClassID(DVMCLASSID_CDVMDATASET)/*pParas->GetDvmDataset(FALSE)*//*,*pAttrDataset = NULL*/;
    CString strDatasetID;

// 	CExBaseObject *pCurrObj = NULL;
// 	POS pos = pParas->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pCurrObj = pParas->GetNext(pos);
// 
// 		if (pCurrObj->GetClassID() != DVMCLASSID_CDVMDATASET)
// 		{
// 			continue;
// 		}
// 
// 		if (pCurrObj->m_strID == XPARA_ID_DEVICE_ATTR/*"device-attr"*/)
// 		{
// 			pAttrDataset = (CDvmDataset*)pCurrObj;
// 		}
// 		else
// 		{
// 			pDataset = (CDvmDataset*)pCurrObj;
// 		}
// 	}

	//19821服务端，返回的数据集的ID，一般包含逻辑设备的路径，例如：IecRcd$dsSV1
	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetID);
	CString strErrorInfor;

	if (pParas->GetDataValue(ATTRID_ERRINFO, strErrorInfor))
	{
		m_listRunProcedureRlt.SetDataValue(ATTRID_ERRINFO,strErrorInfor,TRUE);
	}


	if ((pDataset == NULL)/*&&(pAttrDataset == NULL)*/)
	{
		//PostDeviceCommCmdMessage(0, engineCommError);
		return FALSE;
	}

//	if (pDataset != NULL)
	{
		CDvmDataset *pClone = NULL;

		if (strDatasetID == "report$soe")//zhouhj 2024.3.16 增加对PpEngine的SOE数据的特殊处理,后期需要改为Event时间方式实时传递过来
		{
			pClone = (CDvmDataset *)pDataset->CloneEx(TRUE, TRUE);
			//m_oSoeReports.AddExBaseObjects(pDataset, TRUE);
			//pDataset->RemoveAll();
		}
		//else
		{
			pDataset->m_strID = strDatasetID;  //赋值为全路径，方便查找
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Return Dataset %s"), pDataset->m_strID.GetString());
			CDvmDataset *pFind = FindDataSet2(pDataset->m_strID);

			if (pFind == NULL)
			{
				m_listDataset.AddTail(pDataset);
				pParas->Remove(pDataset);
			}
			else
			{
				pFind->DeleteAll();
				pFind->AppendEx(*pDataset);
				pDataset->RemoveAll();
			}
		}

		if (pClone != NULL)
		{
			//SOE数据，克隆一份，存两份
			m_oSoeReports.AddExBaseObjects(pClone, TRUE);
			pClone->RemoveAll();
			delete pClone;
			pClone = NULL;
		}
	}

// 	if (pAttrDataset != NULL)
// 	{
// 		CDvmDataset *pFind = FindDataSet2(pAttrDataset->m_strID);
// 
// 		if (pFind == NULL)
// 		{
// 			m_listDataset.AddTail(pAttrDataset);
// 			pParas->Remove(pAttrDataset);
// 		}
// 		else
// 		{
// 			pFind->DeleteAll();
// 			pFind->AppendEx(*pAttrDataset);
// 			pAttrDataset->RemoveAll();
// 		}
// 	}
   
	return TRUE;
}

BOOL CPpSttIotDeviceBase::IsCurrProcedure_Write()
{
	if (m_strCurrProcedureID == STT_CMD_TYPE_IOT_SetDataset)
	{
		return TRUE;
	}

	return FALSE;
}

void CPpSttIotDeviceBase::InitDvmDevice(CSttParas *pSttParas)
{
	CDvmDevice *pDevice = pSttParas->GetDvmDevice();

	if (pDevice == NULL)
	{
		return;
	}

	m_oDvmDeviceForEnum.DeleteAll();
	m_oDvmDeviceForEnum.Append(*pDevice);
	pDevice->RemoveAll();
}

/*
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
*/
//目前没有区分是读、写指令。写指令应当不返回dataset
BOOL CPpSttIotDeviceBase::On_SysState_IOT_RunProcedure(CSttSysState *pSysState)
{
	GetDatasetFromParas(pSysState);

    CString strEngineSysState;
    CSttParas *pSttParas = pSysState->GetSttParas();

    BOOL bRet = pSttParas->GetDataValue(PXI_DATA_ID_EngineSysState, strEngineSysState);
	InitDvmDevice(pSttParas);  //2023-1-29  lijunqing  处理枚举

	On_SysState_IOT_RunProcedure_Cmd(pSysState);

    if (!bRet)
    {
        return TRUE;
    }

    if (strEngineSysState == EngineSysState_CommFinish)
    {
		PostDeviceCommCmdMessage(0, engineCommFinish);
	}
	else if (strEngineSysState == EngineSysState_Exception
		|| strEngineSysState == EngineSysState_CommOverTime
		|| strEngineSysState == EngineSysState_CmdError
		|| strEngineSysState == EngineSysState_CommError)
	{
		PostDeviceCommCmdMessage(0, engineCommError);
	}

	return TRUE;
}

void CPpSttIotDeviceBase::On_SysState_IOT_RunProcedure_Cmd(CSttSysState *pSysState)
{
	CSttParas *pSttParas = pSysState->GetSttParas();
	CString strIdProcedure;
	
	if ( ! pSttParas->GetDataValue(STT_CMD_PARA_ProcedureID, strIdProcedure) )
	{
		return;
	}

	if (strIdProcedure == CMDID_readzone)
	{
		On_SysState_IOT_RunProcedure_ReadZone(pSttParas);
	}
	else
	{

	}

}

void CPpSttIotDeviceBase::On_SysState_IOT_RunProcedure_ReadZone(CSttParas *pSttParas)
{
	if (pSttParas->GetDataValue(ParaID_setzone, m_nZoneIndex))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Zone Index = %d"), m_nZoneIndex);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Read Zone Index error......"));
	}
}


void CPpSttIotDeviceBase::SetDeviceSN(const CString &strDeviceSN)
{
	if (strDeviceSN.GetLength() > 0)
	{
		m_strID = strDeviceSN;
	}
	else
	{
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		m_strID.Format(_T("%u_%02d%02d%03d"), stt_GetMachineCode_U32()
			,tm.wMinute, tm.wSecond, tm.wMilliseconds);
	}
}

void CPpSttIotDeviceBase::DisConnect()
{
   
}

void CPpSttIotDeviceBase::DisConnectForClose(BOOL bDelete)
{
    
}

long CPpSttIotDeviceBase::CloseDevice()
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++ for debug ++++CPpSttIotDeviceBase::CloseDevice()   %s +++++    1"), m_strID.GetString());

	//for debug
	if (!IsConnectSuccessful())
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++ for debug ++++CPpSttIotDeviceBase::CloseDevice()   %s +++++    2"), m_strID.GetString());
		return -1;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++ for debug ++++CPpSttIotDeviceBase::CloseDevice()   %s +++++    3"), m_strID.GetString());
	CSttIotCmd oIotCmd;
	oIotCmd.m_strID = STT_CMD_TYPE_IOT_CloseDevice;
	oIotCmd.AppendParas2(m_oCommConfig, TRUE);

	long nRet = X_SendIotCmd(oIotCmd);

	return nRet;
}

void stt_PostMessage(PSX_OBJ_ADDR hWnd, unsigned long nMsgID, WPARAM wParam, LPARAM lParam)
{
	CWnd *pWnd = NULL;
#ifdef _PSX_IDE_QT_
	pWnd = (CWnd *)hWnd;
#else
	pWnd = CWnd::FromHandle((HWND)hWnd);
#endif

	if (pWnd != NULL)
	{
		pWnd->PostMessage(nMsgID, wParam, lParam);
	}
}

void CPpSttIotDeviceBase::PostDeviceSysMessage(WPARAM wParam, LPARAM lParam)
{
    stt_PostMessage((PSX_OBJ_ADDR)m_hSysMsgWnd, m_nSysMsgID, wParam, lParam);
// 	HWND hWnd = (HWND)m_hSysMsgWnd;
// 
// 	if (!::IsWindow((hWnd)))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【Sys】"), m_hSysMsgWnd);
// 		return;
// 	}
// 
// 	::PostMessage(hWnd, m_nSysMsgID, wParam, lParam);
}

void CPpSttIotDeviceBase::PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
    stt_PostMessage((PSX_OBJ_ADDR)m_hMsgWnd, m_nMsgID, wParam, lParam);
// 	HWND hWnd = (HWND)m_hMsgWnd;
// 
// 	if (!::IsWindow((hWnd)))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口【CommCmd】"), m_hMsgWnd);
// 		return;
// 	}
// 
// 	::PostMessage(hWnd, m_nMsgID, wParam, lParam);
}

void CPpSttIotDeviceBase::PostDeviceEventMessage(WPARAM wParam, LPARAM lParam)
{
    stt_PostMessage((PSX_OBJ_ADDR)m_hSysMsgWnd, WM_ENGINE_EVENT_MSG, wParam, lParam);
}

void CPpSttIotDeviceBase::InitCommConfig(CDataGroup *pCommConfig)
{
	m_oCommConfig.DeleteAll();
	m_oCommConfig.AppendCloneEx(*pCommConfig);
}

CDvmDataset* CPpSttIotDeviceBase::FindDataSet2(const CString &strDataSetName)
{
	CDvmDataset *pFind = (CDvmDataset*)m_listDataset.FindByID(strDataSetName);

	return pFind;
}

void CPpSttIotDeviceBase::GetDvmDevice(CDvmDevice *pDestDvmDevice)
{
	pDestDvmDevice->DeleteAll();
	pDestDvmDevice->AppendCloneEx(m_oDvmDeviceForEnum);
}

void CPpSttIotDeviceBase::ClearDvmDevice()
{
	m_oDvmDeviceForEnum.DeleteAll();
}

void CPpSttIotDeviceBase::GetCurrSoeReports(CExBaseList *pList)
{
	m_oSoeReports.ReadAll(pList, -1, TRUE);
}


//////////////////////////////////////////////////////////////////////////
//CPpXIotEngineBase
CPpXIotEngineBase::CPpXIotEngineBase()
{

}

CPpXIotEngineBase::~CPpXIotEngineBase(void)
{

}


CString CPpXIotEngineBase::GetVersion()
{
	return _T("");
}

CProtocolDeviceInterface* CPpXIotEngineBase::CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	CPpSttIotDeviceBase *pDevice = CreateNewDevice();
	pDevice->m_strDvmFile = strDeviceFile;
	pDevice->m_strTemplateFile = strTemplateFile;
	pDevice->SetDeviceSN(strDeviceID);
	AddNewChild(pDevice);

	return pDevice;
}

//2023-3-16 lijunqing
CProtocolDeviceInterface* CPpXIotEngineBase::CreateDevice(CPpSttCommConfig *pCommConfig)
{
	CPpSttIotDeviceBase *pDevice = CreateNewDevice();
	pDevice->InitCommConfig(pCommConfig);
	AddNewChild(pDevice);
	return pDevice;
}

long CPpXIotEngineBase::GetCount()
{
	return GetCount();
}

CProtocolDeviceInterface* CPpXIotEngineBase::GetItem(long nIndex)
{
	CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase *)GetAtIndex(nIndex);
	return pDevice;
}

long CPpXIotEngineBase::ShowSpyWnd(long nShow)
{
	return 0;
}

long CPpXIotEngineBase::ReleaseDevice(const CString &strDeviceID)
{
	CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase*)FindByID(strDeviceID);

	if (pDevice == NULL)
	{
		return -1;
	}

	pDevice->CloseDevice();
	pDevice->DisConnect();
	delete pDevice;

	return 0;
}

long CPpXIotEngineBase::ReleaseAllDevice()
{
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CPpSttIotDeviceBase *pDevice = (CPpSttIotDeviceBase*)GetNext(pos);
		pDevice->CloseDevice();
		pDevice->DisConnect();
	}

	DeleteAll();

	return 0;
}

long CPpXIotEngineBase::CreateProject(const CString &strProjectFile)
{
	return 0;
}

long CPpXIotEngineBase::SetProtocolParse(long nStopFlag)
{
	return 0;
}

long CPpXIotEngineBase::ConfigEngine(const CString &strDvmFile)
{
	return 0;
}

long CPpXIotEngineBase::AttatchLogWnd(PSX_OBJ_ADDR hWnd)
{
	return 0;
}
