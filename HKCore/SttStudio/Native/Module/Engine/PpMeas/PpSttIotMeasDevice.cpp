#include "stdafx.h"
#include "PpSttIotMeasDevice.h"

CPpSttIotMeasDevice::CPpSttIotMeasDevice()
{
	m_pX61850CapBase = NULL;
}

CPpSttIotMeasDevice::~CPpSttIotMeasDevice()
{
		
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);

	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strProcedureID;

	pParas->GetDataValue(STT_CMD_PARA_ProcedureID, strProcedureID);

	if (strProcedureID == _T("ReadAin"))
	{
		return Process_Cmd_IOT_RunProcedure_ReadAin(pPxCommChn, pIotCmd);
	}
	else if (strProcedureID == _T("SetDataset"))
	{
		return Process_Cmd_IOT_RunProcedure_SetDataset(pPxCommChn, pIotCmd);
	}
	else
	{
		return ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE,NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
	}

	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_RunProcedure_ReadAin(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);

// 	CString strText;
// 	strText = pParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strText);

	if (m_pX61850CapBase == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	}

	//直接用当前合并单元测试用的数据集,不需要再去查找,查找的dsSV1有可能不是当前选择的控制块
	CDvmDataset*pDataset = m_pX61850CapBase->m_pDataset_MUTestCB;

	if (!strDatasetPath.IsEmpty())
	{
        long nIndex = strDatasetPath.ReverseFind('$');

		if (nIndex != -1)
		{
			CString strTmp;
			strTmp = strDatasetPath.Mid(nIndex+1);
			strDatasetPath = strTmp;
		}

		pDataset = m_pX61850CapBase->FindDataset(strDatasetPath);

		if (pDataset == NULL)
		{
			pDataset = m_pX61850CapBase->m_pDataset_MUTestCB;
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadAin查找数据集(%s)失败."),strDatasetPath.GetString());
		}
		else if (strDatasetPath == "dsMUTimeRlt")
		{
			CString strTmp;
			strTmp = _P_GetBinPath();
			strTmp += _T("dsMUTimeDataset.xml");
			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("存储dsMUTimeRlt数据集(%s)完成."),strTmp.GetString());
// 			pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys,strTmp);
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("dsSVErr数据集(%s)."),strTmp.GetString());
		}
// 		else
// 		{
// 			SYSTEMTIME tm;
// 			::GetLocalTime(&tm);
// 
// 			CString strTmp;
// 			strTmp = _P_GetBinPath();
// 			strTmp.AppendFormat(_T("dsReadAinDataset%d-%d-%d_%d-%d-%d_%d.xml"),tm.wYear, tm.wMonth, tm.wDay
// 				,tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
// 			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("存储dsReadAinDataset数据集(%s)完成."),strTmp.GetString());
// 		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadAin当前传递的数据集ID为空."));
	}

// 	CString strDatasetID;
// 	long nIndex = strDatasetPath.ReverseFind('$');
// 	strDatasetID = strDatasetPath;
// 
// 	if (nIndex>=0)
// 	{
// 		strDatasetID = strDatasetPath.Mid(nIndex+1);
// 	} 
//
//	 pDataset = m_pDvmDevice->FindDataset(strDatasetID);


	if (pDataset == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	} 
	
	pIotCmd->Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
// 	CString strSavePath;
// 	strSavePath = _P_GetLibraryPath(); 
// 	strSavePath += _T("ReturnSysState.xml");
// 	pDataset->SaveXmlFile(strSavePath,CDataMngrXmlRWKeys::g_pXmlKeys);
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("Process_Cmd_IOT_RunProcedure_ReadAin[成功]."));
	return 1;	
}

long CPpSttIotMeasDevice::Process_Cmd_IOT_RunProcedure_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;
// 	CString strText;
// 	strText = pParas->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 	CLogPrint::LogString(XLOGLEVEL_INFOR,strText);

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);

	CString strDatasetID;
	long nIndex = strDatasetPath.ReverseFind('$');
	strDatasetID = strDatasetPath;

	if (nIndex>=0)
	{
		strDatasetID = strDatasetPath.Mid(nIndex+1);
	} 
	if (strDatasetID.IsEmpty())
	{
		strDatasetID = CAP_DATASET_MAP_ID_dsCurrErrorRange/*_T("dsCurrErrorRange")*/;
	}

	CDvmDataset* pCurrDataset = m_pDvmDevice->FindDataset(strDatasetID);
	CDvmDataset *pSetDataset = (CDvmDataset*)pParas->FindByClassID(DVMCLASSID_CDVMDATASET);

	if ((pCurrDataset == NULL)||(pSetDataset == NULL))
	{
		if (pCurrDataset == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("数据集(%s)未找到."),strDatasetID.GetString());
		}

		if (pSetDataset == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SetDataset命令中未找到数据集."));
		}

		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommError);
		return 0;	
	} 

//  	CString strTmp;
//  	pSetDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys,strTmp);
//  	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("SetDataset内容,%s"),strTmp.GetString());
	pCurrDataset->UpdateDataValue(pSetDataset);

	if (m_pX61850CapBase != NULL)
	{
		if (strDatasetID == CAP_DATASET_MAP_ID_RcdStep6U6I)
		{
			m_pX61850CapBase->InitIsFirstCWTestValueByDataset();
		} 
		else if (strDatasetID == CAP_DATASET_MAP_ID_TestFunSelect) //chenling 2024.5.30 功能选择
		{
			//m_pX61850CapBase->ClearMUTestResults();
			m_pX61850CapBase->InitIsFunSelectValueByDataset();
		}
		else
		{
			m_pX61850CapBase->InitMuErrorRangesBydsCurrErrorRange();
		}
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SetDataset(%s)成功."),strDatasetID.GetString());
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;	
}

BOOL CPpSttIotMeasDevice::IsConnectSuccessful()
{
	return TRUE;
}


