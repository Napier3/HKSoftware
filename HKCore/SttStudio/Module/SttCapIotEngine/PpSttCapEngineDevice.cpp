#include "stdafx.h"
#include "PpSttCapEngineDevice.h"
#include <tchar.h>
#include "QSttCapIotEngineFrameBase.h"

extern QSttCapIotEngineFrameBase *g_pSttCapIotEngineBase;

CPpSttCapEngineDevice::CPpSttCapEngineDevice()
{
	m_pX61850CapBase = NULL;
}

CPpSttCapEngineDevice::~CPpSttCapEngineDevice()
{

}

long CPpSttCapEngineDevice::Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
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
	else if (strProcedureID == _T("SetDataset"))//SetDataset
	{
		return Process_Cmd_IOT_RunProcedure_SetDataset(pPxCommChn, pIotCmd);
	}
	else if (strProcedureID == _T("ReadSV1"))
	{
		return Process_Cmd_IOT_RunProcedure_ReadSV1(pPxCommChn, pIotCmd);
	}
	else if (strProcedureID == _T("ReadSVErr"))
	{
		return Process_Cmd_IOT_RunProcedure_ReadSVErr(pPxCommChn, pIotCmd);
	}
	else if (strProcedureID == _T("ReadSVDelay"))
	{
		return Process_Cmd_IOT_RunProcedure_ReadSVDelay(pPxCommChn, pIotCmd);
	}
	else if (strProcedureID == _T("FunSelect"))
	{
		return Process_Cmd_IOT_RunProcedure_SetTestFun(pPxCommChn, pIotCmd);
	}
	else
	{
		return ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE,NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
	}

	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	return 0;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_ReadAin(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);


	if (m_pX61850CapBase == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	}

	//ֱ���õ�ǰ�ϲ���Ԫ�����õ����ݼ�,����Ҫ��ȥ����,���ҵ�dsSV1�п��ܲ��ǵ�ǰѡ��Ŀ��ƿ�
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadAin�������ݼ�(%s)ʧ��."),strDatasetPath.GetString());
		}
		else if (strDatasetPath == "dsMUTimeRlt")
		{
			CString strTmp;
			strTmp = _P_GetBinPath();
			strTmp += _T("dsMUTimeDataset.xml");
			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�洢dsMUTimeRlt���ݼ�(%s)���."),strTmp.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadAin��ǰ���ݵ����ݼ�IDΪ��."));
	}

	if (pDataset == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	} 

	pIotCmd->Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;	
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ݼ�(%s)δ�ҵ�."),strDatasetID.GetString());
		}

		if (pSetDataset == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SetDataset������δ�ҵ����ݼ�."));
		}

		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommError);
		return 0;	
	} 
	pCurrDataset->UpdateDataValue(pSetDataset);

	if (m_pX61850CapBase != NULL)
	{
		if (strDatasetID == CAP_DATASET_MAP_ID_RcdStep6U6I)
		{
			m_pX61850CapBase->InitIsFirstCWTestValueByDataset();
			m_pX61850CapBase->UpdateUI_Paras(TRUE);//���ж��Ƿ�����Ư���ٸ��²���
		} 
		else
		{
			m_pX61850CapBase->InitMuErrorRangesBydsCurrErrorRange();
		}
	}

	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;	
}


long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_ReadSV1(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);


	if (m_pX61850CapBase == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	}

	//ֱ���õ�ǰ�ϲ���Ԫ�����õ����ݼ�,����Ҫ��ȥ����,���ҵ�dsSV1�п��ܲ��ǵ�ǰѡ��Ŀ��ƿ�
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSV1�������ݼ�(%s)ʧ��."),strDatasetPath.GetString());
		}
		else if (strDatasetPath == "dsMUTimeRlt")
		{
			CString strTmp;
			strTmp = _P_GetBinPath();
			strTmp += _T("dsMUTimeDataset.xml");
			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�洢dsMUTimeRlt���ݼ�(%s)���."),strTmp.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSV1��ǰ���ݵ����ݼ�IDΪ��."));
	}

	if (pDataset == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	} 

	pIotCmd->Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_ReadSVErr(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);


	if (m_pX61850CapBase == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	}

	//ֱ���õ�ǰ�ϲ���Ԫ�����õ����ݼ�,����Ҫ��ȥ����,���ҵ�dsSV1�п��ܲ��ǵ�ǰѡ��Ŀ��ƿ�
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSVErr�������ݼ�(%s)ʧ��."),strDatasetPath.GetString());
		}
		else if (strDatasetPath == "dsMUTimeRlt")
		{
			CString strTmp;
			strTmp = _P_GetBinPath();
			strTmp += _T("dsMUTimeDataset.xml");
			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�洢dsMUTimeRlt���ݼ�(%s)���."),strTmp.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSVErr��ǰ���ݵ����ݼ�IDΪ��."));
	}

	if (pDataset == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	} 

	pIotCmd->Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_ReadSVDelay(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

	pParas->GetDataValue(STT_CMD_PARA_DatasetPath, strDatasetPath);
	pParas->GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);


	if (m_pX61850CapBase == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	}

	//ֱ���õ�ǰ�ϲ���Ԫ�����õ����ݼ�,����Ҫ��ȥ����,���ҵ�dsSV1�п��ܲ��ǵ�ǰѡ��Ŀ��ƿ�
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSVDelay�������ݼ�(%s)ʧ��."),strDatasetPath.GetString());
		}
		else if (strDatasetPath == "dsMUTimeRlt")
		{
			CString strTmp;
			strTmp = _P_GetBinPath();
			strTmp += _T("dsMUTimeDataset.xml");
			pDataset->SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�洢dsMUTimeRlt���ݼ�(%s)���."),strTmp.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ReadSVDelay��ǰ���ݵ����ݼ�IDΪ��."));
	}

	if (pDataset == NULL)
	{
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CmdError);
		return 0;
	} 

	pIotCmd->Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, pDataset,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;
}

long CPpSttCapEngineDevice::Process_Cmd_IOT_RunProcedure_SetTestFun(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmd *pIotCmd)
{
	CSttParas* pParas = pIotCmd->GetSttParas();
	CString strDatasetPath, strDeviceSN;

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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ݼ�(%s)δ�ҵ�."),strDatasetID.GetString());
		}

		if (pSetDataset == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SetTestFun������δ�ҵ����ݼ�."));
		}

		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommError);
		return 0;	
	} 
	pCurrDataset->UpdateDataValue(pSetDataset);
	POS pos = pSetDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	while(pos)
	{
		pDvmData = (CDvmData *)pSetDataset->GetNext(pos);
		int nValue = _ttoi(pDvmData->m_strValue.GetString());
		if (pDvmData->m_strID == "TestFunction")
		{
			if (nValue == 0)
			{
				g_oCapAnalysisConfig.m_bSvAnalysis = false;
			}
			else if (nValue == 1)
			{
				g_oCapAnalysisConfig.m_bSvAnalysis = true;
			}
		}
		else if (pDvmData->m_strID == "PkgStcClearDelay")
		{
			g_pSttCapIotEngineBase->StartClearPkgStc(nValue);
		}	
	}
	if (m_pX61850CapBase != NULL)
	{
		if (strDatasetID == CAP_DATASET_MAP_ID_RcdStep6U6I)
		{
			m_pX61850CapBase->InitIsFirstCWTestValueByDataset();
		} 
		else
		{
			m_pX61850CapBase->InitMuErrorRangesBydsCurrErrorRange();
		}
	}

	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS, NULL,PXI_DATA_ID_EngineSysState, EngineSysState_CommFinish);
	return 1;
}

BOOL CPpSttCapEngineDevice::IsConnectSuccessful()
{
	return TRUE;
}
