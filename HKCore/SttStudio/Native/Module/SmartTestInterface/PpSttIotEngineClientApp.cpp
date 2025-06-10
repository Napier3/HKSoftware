#include "stdafx.h"
#include"PpSttIotEngineClientApp.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPpSttIotEngineClientApp *g_theIotEngineApp = NULL;

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClient
CPpSttIotDeviceClient::CPpSttIotDeviceClient()
{
	m_nSttCmdForat = _PUGI_XML_TYPE_;
	m_pPpDevice = NULL;
	m_hEngineMsgWnd = 0;
    m_strProtoType = STT_IOT_PP_TYPE_PpEngine;
    InitCmdFilePath();

	m_pDvmDevice = NULL;
	m_pDsReport = NULL;
}

CPpSttIotDeviceClient::~CPpSttIotDeviceClient()
{ 
	if (m_pPpDevice != NULL)
	{
		delete m_pPpDevice;
		m_pPpDevice = NULL;
	}
}

void CPpSttIotDeviceClient::InitDvmDevice(CDvmDevice *pDvmDevice)
{
	m_pDvmDevice = pDvmDevice;
}

void CPpSttIotDeviceClient::InitCommConfig(CPpSttCommConfig *pCommConfig)
{
	m_oCommConfig.DeleteAll();
    m_oCommConfig.AppendCloneEx(*pCommConfig);
	m_oCommConfig.InitAfterRead();
}

void CPpSttIotDeviceClient::InitCmdFilePath()
{
	m_strCmdFilePath = _P_GetConfigPath();
	m_strCmdFilePath += m_strProtoType;
	m_strCmdFilePath += _T("/");

	CString strFile;
	strFile = m_strCmdFilePath;
	strFile += _T("CommConfig.xml");
	m_oCommConfig.DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oCommConfig.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	m_oCommConfig.GetDataValue(STT_CMD_PARA_DeviceSN, m_strDeviceID);
}

void CPpSttIotDeviceClient::SendIotCmdFile(PSX_OBJ_ADDR hWnd, const CString &strCmdID)
{
	CString strFile;
	strFile = m_strCmdFilePath + strCmdID + _T(".xml");
	CSttIotCmd oIotCmd;

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oIotCmd.OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	CString strDatasetPath, strDeviceSN;
	CSttParas *pParas = oIotCmd.GetSttParas();
	CDvmDataset *pDataset = oIotCmd.GetDataset();
	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);

	if (pDataset != NULL)
	{
		CPpSttIotDataset *pSttDataset = (CPpSttIotDataset*)m_pPpDevice->FindDataSet(strDatasetPath);

		if (pSttDataset != NULL)
		{
			pSttDataset->UpdateDataset(pDataset);
		}
	}

	RunProcedure(hWnd, strCmdID, strDatasetPath);
}


BOOL CPpSttIotDeviceClient::RunProcedure(PSX_OBJ_ADDR hWnd, const CString &strProcedureID, const CString &strDataset)
{
	if (m_strProcedureID.GetLength() > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s 指令还没有执行完毕"), m_strProcedureID.GetString());
		return FALSE; 
	}

    m_strDatasetPath = strDataset;
	m_strProcedureID = strProcedureID;
	m_pPpDevice->RegisterProcedureWndMsg(strProcedureID,  hWnd, WM_COMM_COMMAND);
	long nRet = m_pPpDevice->RunProcedure(strProcedureID, strDataset);

	return (nRet >10);//zhouhj 2024.1.22 实际返回的是发送报文的长度,字节长度不会小于10
}

void CPpSttIotDeviceClient::CreateDevice(PSX_OBJ_ADDR hWnd)
{
    if (m_pPpDevice == NULL)
    {
        m_pPpDevice = new CPpSttIotDevice();
        m_pPpDevice->m_strDvmFile = m_strDeviceFile;
        m_pPpDevice->m_strTemplateFile = m_strTemplateFile;
        m_pPpDevice->SetDeviceSN(m_strDeviceID);
    }

    if (hWnd != NULL)
    {
        m_hEngineMsgWnd = hWnd;
    }

	m_strProcedureID.Empty();
    m_pPpDevice->AttachSystemWndMsg(m_hEngineMsgWnd, WM_ENGINE_SYSTEM_MSG);
    m_pPpDevice->InitCommConfig(&m_oCommConfig);

    if (m_pPpDevice != NULL)
    {
        m_pPpDevice->SetSttCmdDataFormat(m_nSttCmdForat);
    }
}

BOOL CPpSttIotDeviceClient::ConnectDevice()
{
	if (m_pPpDevice == NULL)
	{
		return FALSE;
	}

	if (m_pPpDevice->IsConnectSuccessful())
	{
		return TRUE;
	}

	m_strProcedureID.Empty();
    m_pPpDevice->InitCommConfig(&m_oCommConfig);
	long nRet = m_pPpDevice->CommConfig("");
	return (nRet>10);//zhouhj 2024.1.22 此处返回的是发送报文的长度,理论不会小于10
}

BOOL CPpSttIotDeviceClient::IsConnectSuccessful()
{
	if (m_pPpDevice == NULL)
	{
		return FALSE;
	}

	if (m_pPpDevice->IsConnectSuccessful())
	{
		return TRUE;
	}

	return FALSE;
}

void CPpSttIotDeviceClient::CloseDevice()
{
	if (m_pPpDevice == NULL)
	{
		return;
	}

	m_strProcedureID.Empty();
	m_pPpDevice->UnLoad();
}


void CPpSttIotDeviceClient::SetSttCmdFormat(long nSttCmdForat)
{
	m_nSttCmdForat = nSttCmdForat;

	if (m_pPpDevice != NULL)
	{
        m_pPpDevice->SetSttCmdDataFormat(m_nSttCmdForat);
	}
}

void CPpSttIotDeviceClient::DisConnectForClose(BOOL bDelete)
{
	m_strProcedureID.Empty();

    if (m_pPpDevice == NULL)
    {
        return;
    }

    m_pPpDevice->DisConnectForClose(bDelete);
}

CDvmDataset* CPpSttIotDeviceClient::GetCurrDataset()
{
    if (m_pPpDevice == NULL)
    {
        return NULL;
    }

    return m_pPpDevice->FindDataSet2(m_strDatasetPath);
}

BOOL CPpSttIotDeviceClient::GetRunProcedureRltValue(const CString &strID,long &nValue)
{
	if (m_pPpDevice == NULL)
	{
		return FALSE;
	}

	return m_pPpDevice->GetRunProcedureRltValue(strID,nValue);
}

void CPpSttIotDeviceClient::GetDvmDevice(CDvmDevice *pDestDvmDevice)
{
	if (m_pPpDevice != NULL)
	{
		m_pPpDevice->GetDvmDevice(pDestDvmDevice);
	}
}

void CPpSttIotDeviceClient::ClearDvmDevice()
{
	if (m_pPpDevice != NULL)
	{
		m_pPpDevice->ClearDvmDevice();
	}
}

void CPpSttIotDeviceClient::FinishRunProcedure()
{
	m_strProcedureID = _T("");
}

BOOL CPpSttIotDeviceClient::IsRunProcedureFinished()
{
	return (m_strProcedureID.IsEmpty());
}

CDvmDataset* CPpSttIotDeviceClient::InitDvmDsReport()
{
	if (m_pDvmDevice == NULL)
	{
		return NULL;
	}

    return m_pDvmDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport]);
}

CDvmDataset* CPpSttIotDeviceClient::GetDvmDsReport(BOOL bCreateNew)
{
    return m_pDvmDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport], bCreateNew);
}

void CPpSttIotDeviceClient::AddToReport(CExBaseList *pList)
{
    CDvmDataset *pDataset = m_pDvmDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport]);

	if (pDataset != NULL)
	{
		pDataset->Append(pList);
	}
}

void CPpSttIotDeviceClient::AddCurrSoeReports(CExBaseList *pList)
{
	if (m_pPpDevice == NULL)
	{
		return;
	}

	m_pPpDevice->GetCurrSoeReports(pList);
	AddToReport(pList);
}

void CPpSttIotDeviceClient::Reset()
{
	RunProcedure(m_hEngineMsgWnd, CMDID_reset, "");
	m_pPpDevice->m_oSoeReports.FreeBuffer();
    CDvmDataset *pDataset = m_pDvmDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport]);

	if (pDataset == NULL)
	{
		return;
	}

	pDataset->DeleteAll();
}

void CPpSttIotDeviceClient::EnumDevice(CDvmDevice *pDevice)
{
	CProtocolParasInterface *pDataInterface = m_pPpDevice->GetDataInterface();
	
	//pDataInterface->AddData(ParaID_FileName, _T("1"));
	pDataInterface->AddData(ParaID_EnumSetting,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayEna,  _T("1"));
	pDataInterface->AddData(ParaID_EnumParameter,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayAin,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayDin,  _T("1"));
	pDataInterface->AddData(ParaID_EnumTripInfo,  _T("1"));
	pDataInterface->AddData(ParaID_EnumAlarm_Warning,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayBlk,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayState,  _T("1"));
	pDataInterface->AddData(ParaID_EnumRelayFunEn,  _T("1"));
	pDataInterface->AddData(ParaID_EnumLog,  _T("1"));
	pDataInterface->AddData(ParaID_DevStdMsg,  _T("1"));

	RunProcedure(m_hEngineMsgWnd, CMDID_dvmenum, "");
}

void CPpSttIotDeviceClient::EnumLDevice(CDvmLogicDevice *pLdevice)
{

}

void CPpSttIotDeviceClient::EnumDataset(CDvmDataset *pDataset)
{

}

void CPpSttIotDeviceClient::ReadDataset(CDvmDataset *pDataset)
{
	if (pDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("当前选择数据集为空,请先选择需要读取的数据集."));
		return;
	}

	CString strDatasetPath;
	strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);;

    ReadDataset(strDatasetPath);
}

BOOL CPpSttIotDeviceClient::ReadSoe(const CString &strDatasetPath)
{
	ReadDataset(strDatasetPath, CMDID_readsoe);
	return TRUE;
}

void CPpSttIotDeviceClient::ReadDataset(const CString &strDatasetPath)
{
// 	if (strDatasetPath.Find("dsDin")>=0)
// 	{
// 		return ReadDataset(strDatasetPath, CMDID_readsoe);
// 	}

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsParameter))
    {
        return ReadDataset(strDatasetPath, CMDID_readparameter);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsAin))
    {
        return ReadDataset(strDatasetPath, CMDID_readain);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsSetting))
    {
        return ReadDataset(strDatasetPath, CMDID_readsetting);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsEna))
    {
        return ReadDataset(strDatasetPath, CMDID_readena);
    }

 	if (Px_JdgDataset(strDatasetPath, PX_DSID_dsDin))//zhouhj 2024.1.16开放此处,在PpEngine下需要单独处理
 	{
 		return ReadDataset(strDatasetPath, CMDID_readdin);
 	}

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsReport))
    {
        return ReadDataset(strDatasetPath, CMDID_readsoe);
    }

    return ReadDataset(strDatasetPath, CMDID_readdataset);
}

BOOL CPpSttIotDeviceClient::WriteDataset(CDvmDataset *pDataset)
{
	if (Px_JdgDataset(pDataset->m_strID, PX_DSID_dsParameter))
	{
		return WriteDataset(pDataset, CMDID_writeparameter);
	}

	if (Px_JdgDataset(pDataset->m_strID, PX_DSID_dsSetting))
	{
		return WriteDataset(pDataset, CMDID_writesetting);
	}

	if (Px_JdgDataset(pDataset->m_strID, PX_DSID_dsEna))
	{
		return WriteDataset(pDataset, CMDID_writeena);
	}

	if (Px_JdgDataset(pDataset->m_strID, PX_DSID_dsDout))
	{
		return WriteDataset(pDataset, CMDID_writedout);
	}

	CString strText = pDataset->m_strID;
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("WriteDataset Error [%s] "), strText.GetString());
	return FALSE;
}

void CPpSttIotDeviceClient::WriteDataset2(CDvmDataset *pDataset, const CString &strDatasetPath)
{
    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsParameter))
    {
        return WriteDataset(pDataset, strDatasetPath, CMDID_writeparameter);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsSetting))
    {
        return WriteDataset(pDataset, strDatasetPath, CMDID_writesetting);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsEna))
    {
        return WriteDataset(pDataset, strDatasetPath, CMDID_writeena);
    }

    if (Px_JdgDataset(strDatasetPath, PX_DSID_dsDout))
    {
        return WriteDataset(pDataset, strDatasetPath, CMDID_writedout);
    }

    CString strText = pDataset->m_strID;
    CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("WriteDataset Error [%s] "), strText.GetString());
}

void CPpSttIotDeviceClient::ReadZone()
{
	RunProcedure(m_hEngineMsgWnd, CMDID_readzone, "");
}

void CPpSttIotDeviceClient::WriteZone(long nZoneIndex)
{
	m_pPpDevice->m_nZoneIndex = nZoneIndex;
	CProtocolParasInterface *pDataInterface = m_pPpDevice->GetDataInterface();
	pDataInterface->AddData(ParaID_setzone, nZoneIndex);
	RunProcedure(m_hEngineMsgWnd, CMDID_changesetzone, "");
	pDataInterface->Release();
}

void CPpSttIotDeviceClient::StartRpt(CDvmDataset *pDataset, PMMS_BRCB_CTRL_CONFIG pBrcbCfg)
{
	CProtocolParasInterface *pDataInterface = m_pPpDevice->GetDataInterface();

	pDataInterface->AddData(ParaID_TrgOps_1, pBrcbCfg->TrgOps_UI[0]);
	pDataInterface->AddData(ParaID_TrgOps_4, pBrcbCfg->TrgOps_UI[3]);
	pDataInterface->AddData(ParaID_IntgPd, pBrcbCfg->nIntgPd);

	CString strDatasetPath;
	strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);;

	RunProcedure(m_hEngineMsgWnd, CMDID_registerreport, strDatasetPath);
	pDataInterface->Release();
}

void CPpSttIotDeviceClient::StopReport(CDvmDataset *pDataset)
{
	CString strDatasetPath;
	strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);;
	RunProcedure(m_hEngineMsgWnd, CMDID_unregisterreport, strDatasetPath);
}

void CPpSttIotDeviceClient::OpenDvmFile(CDvmDevice *pDevice)
{

}

void CPpSttIotDeviceClient::SaveDvmFile(CDvmDevice *pDevice)
{

}

void CPpSttIotDeviceClient::ReadDataset(CDvmDataset *pDataset, const CString &strCmdID)
{
	CString strDatasetPath;
	strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);;
	RunProcedure(m_hEngineMsgWnd, strCmdID, strDatasetPath);
}

void CPpSttIotDeviceClient::ReadDataset(const CString &strDatasetPath, const CString &strCmdID)
{
    RunProcedure(m_hEngineMsgWnd, strCmdID, strDatasetPath);
}

void CPpSttIotDeviceClient::ReadAin(const CString &strDatasetPath)
{
	RunProcedure(m_hEngineMsgWnd, CMDID_readain, strDatasetPath);
}

BOOL CPpSttIotDeviceClient::Initialize_Cmd()
{
	if (m_strProcedureID.GetLength() > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s 指令还没有执行完毕"), m_strProcedureID.GetString());
		return FALSE; 
	}

	m_strDatasetPath = "";
	m_strProcedureID = CMDID_Initialize;
	m_pPpDevice->RegisterProcedureWndMsg(m_strProcedureID,  m_hEngineMsgWnd, WM_COMM_COMMAND);
	long nRet = m_pPpDevice->RunProcedure(m_strProcedureID, "");

	return (nRet >10);//zhouhj 2024.1.22 实际返回的是发送报文的长度,字节长度不会小于10
}

BOOL CPpSttIotDeviceClient::RegisterReport_Cmd(const CString &strDatasetPath)
{
	if (m_strProcedureID.GetLength() > 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s 指令还没有执行完毕"), m_strProcedureID.GetString());
		return FALSE; 
	}
 
    m_pPpDevice->RegisterProcedureWndMsg(CMDID_RegisterReport,  m_hEngineMsgWnd, WM_COMM_COMMAND);
    long nRet = m_pPpDevice->RunProcedure(CMDID_RegisterReport, strDatasetPath);

    return (nRet >10);
}

BOOL CPpSttIotDeviceClient::WriteDataset(CDvmDataset *pDataset, const CString &strCmdID)
{
	CString strDatasetPath;
	strDatasetPath = pDataset->GetIDPathEx(DVMCLASSID_CDVMLOGICDEVICE);
	CPpSttIotDataset *pSttDataset = (CPpSttIotDataset*)m_pPpDevice->FindDataSet(strDatasetPath);

	if (pSttDataset != NULL)
	{
		pSttDataset->UpdateDataset(pDataset);
		pSttDataset->Release();
	}

	return RunProcedure(m_hEngineMsgWnd, strCmdID, strDatasetPath);
}


void CPpSttIotDeviceClient::WriteDataset(CDvmDataset *pDataset, const CString &strDatasetPath, const CString &strCmdID)
{
    CPpSttIotDataset *pSttDataset = (CPpSttIotDataset*)m_pPpDevice->FindDataSet(strDatasetPath);

    if (pSttDataset != NULL)
    {
        pSttDataset->UpdateDataset(pDataset);
        pSttDataset->Release();
    }

    RunProcedure(m_hEngineMsgWnd, strCmdID, strDatasetPath);
}

BOOL CPpSttIotDeviceClient::WriteSingleData(CDvmData *pData,const CString &strDatasetPath,const CString &strCmdID)
{
	CPpSttIotDataset *pSttDataset = (CPpSttIotDataset*)m_pPpDevice->FindDataSet(strDatasetPath);

	if (pSttDataset == NULL)
	{
		return FALSE;
	}

	if (!pSttDataset->UpdateData_Single(pData))
	{
		return FALSE;
	}

	pSttDataset->Release();
	return RunProcedure(m_hEngineMsgWnd, strCmdID, strDatasetPath);
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
///
//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClient
CPpSttIotEngineClientApp::CPpSttIotEngineClientApp()
{

}

CPpSttIotEngineClientApp::~CPpSttIotEngineClientApp()
{
	//CreateDevice时，是在外部界面new，通过AddTail添加到链表，故释放的时候仍放在外部界面
	//故此处RemoveAll();   shaolei   20230518
	RemoveAll();
}

long CPpSttIotEngineClientApp::InitPpSttIotEngineClientApp()
{
    CDataMngrXmlRWKeys::Create();
    CSttCmdDefineXmlRWKeys::Create();
    CSttCmdOverTimeTool::Create();
    CMacroXmlKeys::Create();
    CDeviceModelXmlKeys::Create();

    return 0;
}

long CPpSttIotEngineClientApp::ExitPpSttIotEngineClientApp()
{
    CDataMngrXmlRWKeys::Release();
    CSttCmdDefineXmlRWKeys::Release();
    CSttCmdOverTimeTool::Release();
    CMacroXmlKeys::Release();
    CDeviceModelXmlKeys::Release();

    return 0;
}

void CPpSttIotEngineClientApp::CreateDevice(CPpSttIotDeviceClient *pDevice, PSX_OBJ_ADDR hWnd)
{
    pDevice->CreateDevice(hWnd);
    AddTail(pDevice);
}

void CPpSttIotEngineClientApp::CloseDevice(CPpSttIotDeviceClient *pDevice)
{
    pDevice->CloseDevice();
    //Delete(pDevice);  //必须完全断开之后，才能删除Device，在外部界面中增加定时器来删除
}

CPpSttIotDeviceClient* CPpSttIotEngineClientApp::FindDeviceClient(const CString &strDeviceSN)
{
    CPpSttIotDeviceClient *p = NULL;
    CPpSttIotDeviceClient *pFind = NULL;
    POS pos = GetHeadPosition();

    while (pos != NULL)
    {
        p = (CPpSttIotDeviceClient*)GetNext(pos);

        if (p->m_strDeviceID == strDeviceSN)
        {
            pFind = p;
            break;
        }
    }

    return pFind;
}
