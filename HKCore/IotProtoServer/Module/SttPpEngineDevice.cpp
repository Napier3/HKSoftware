#include "stdafx.h"
#include "SttPpEngineDevice.h"
#include "../../IotAtsMngr/Module/PxEngineServer/IotPxEngineServer.h"

//CIotPxEngineDeviceWnd *g_pIotPxEngineDeviceWnd = NULL;

CSttPpEngineDevice::CSttPpEngineDevice()
{
	m_pPxiDevice = NULL;
    m_pPxiDeviceForDel = NULL;
}

CSttPpEngineDevice::~CSttPpEngineDevice()
{
	
}

void stt_pp_engine_add_device_attrs(CPxiDevice *pPxiDevice, CDataGroup *pParas)
{
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("update device attr paras ...."));

	if (pPxiDevice->m_pACSI_NODE == NULL)
	{
		return;
	}

	CDvmDataset *pDataset = pPxiDevice->m_pACSI_NODE->GetDeviceAttrs();

	if (pDataset == NULL)
	{
		return;
	}

	POS pos = pParas->GetHeadPosition();
	CDvmData *pAttr = NULL;
    CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pAttr = (CDvmData*)pParas->GetNext(pos);

		if (pAttr->GetClassID() == DVMCLASSID_CDVMDATA)
		{
            pData = pDataset->AddNewDataEx(pAttr);
            CString strID, strValue;
            strID = pData->m_strID;
            strValue = pData->m_strValue;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s = %s"), strID.GetString(), strValue.GetString());
		}
	}
}

/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="ppxml-file" data-type="" value="SZNR-TTU.ppxml"/>
		<data name="" id="dvm-file" data-type="" value="SZNR-TTU.xml"/>
		<data name="" id="cmm-cfg-file" data-type="" value="SZNR-TTU202012131700"/>
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
long CSttPpEngineDevice::Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	m_oSttIotCmdDriver = oDrvIotCmd;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CIotPxEngineDeviceBase::Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);

	//关联绑定消息以及窗口
	m_pPxiDevice->Attatch(this);

	//获取参数
	CSttParas *pSttParas = pIotCmd->GetSttParas();
	CDataGroup *pCommConfig = (CDataGroup*)pSttParas->FindByID(STT_CMD_PARA_CommConfig);

	//2023-2-19  保存创建Device指令传递过来的参数，例如DNP协议的masterAddr、slaveAddr
	stt_pp_engine_add_device_attrs(m_pPxiDevice, pSttParas);  

	if (! m_pPxiDevice->IsConnectSuccessful())
	{//如果连接成功，表示多次连接或者是重复连接
		if (pCommConfig != NULL)
		{//初始化连接，通信连接
			m_pPxiDevice->InitCmmConfig(pCommConfig, TRUE);
		}
		else
		{
			m_pPxiDevice->CommConfig(_T(""));
		}

		//shaolei 2023-9-11 注释此处
		//ReturnSysState2(pIotCmd, pPxCommChn);
	}
	else
	{
		//shaolei 2023-9-11 注释此处
		//ReturnSysState2(pIotCmd, pPxCommChn);
		OnSysMessage(0, 0);
	}

	return 0;
}

long CSttPpEngineDevice::Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	long nCount = CIotPxEngineDeviceBase::Process_Cmd_IOT_CloseDevice(pPxCommChn, oDrvIotCmd);

	if (nCount == 0)
	{
		//表示没有引用，释放设备
		m_pPxiDevice->UnLoad();

        //当前实际设备对象赋值为空
        m_pPxiDeviceForDel = m_pPxiDevice;
		m_pPxiDevice = NULL;

        CIotPxEngineDeviceBase::OnEngineSystemMessage(0, 0);
	}

	return nCount;
}

BOOL CSttPpEngineDevice::IsConnectSuccessful()
{
	if (m_pPxiDevice == NULL)
	{
		return FALSE;
	}

	return m_pPxiDevice->IsConnectSuccessful();
}

long CSttPpEngineDevice::Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttPpEngineDevice::Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
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
long CSttPpEngineDevice::Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return CIotPxEngineDeviceBase::Process_Cmd_IOT_RunProcedure(pPxCommChn, oDrvIotCmd);
}

long CSttPpEngineDevice::IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	m_oSttIotCmdDriver = oDrvIotCmd;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CIotPxEngineDeviceBase::ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);

	CSttParas* pParas = pIotCmd->GetSttParas();
	pParas->GetDataValue(STT_CMD_PARA_ProcedureID, m_strProcedureID);

	//ParaInterface
	CDvmData *pProcedure = (CDvmData*)pParas->FindByID(STT_CMD_PARA_ProcedureID);
	CPxiDataInterface *pDataInterface = m_pPxiDevice->GetDataInterface();
	pDataInterface->InitDataInterface(pProcedure);

	//Init Dataset
	CDvmDataset *pDataset = pParas->GetDvmDataset(FALSE);

	if (pParas->GetDataValue(STT_CMD_PARA_DatasetPath, m_strDatasetID))
	{
		if (pDataset != NULL)
		{//如果通信命令带了数据集参数，表示为写命令，在此更新数据集
			CPxiDataSet *pPxiDataset = m_pPxiDevice->FindDataSet(m_strDatasetID);

			if (pPxiDataset != NULL)
			{
				pPxiDataset->InitByDataset(pDataset);
			}
		}
	}

	//关联绑定消息以及窗口
	//m_pPxiDevice->RegisterProcedureWndMsg(m_strProcedureID, GetMsgRcvWnd(), WM_PROCEDURE_END_MSG);

	//Run Procedure
	long nRet = m_pPxiDevice->RunProcedure(m_strProcedureID, m_strDatasetID);

	if (m_pPxiDevice->IsWriteProcedure())//zhouhj 2024.9.12 在写数据命令执行时，增加执行成功/失败的返回结果
	{
		if (nRet == 0)
		{
			pParas->SetDataValue(ATTRID_ERRINFO, (long)0,TRUE);
		}
		else
		{
			pParas->SetDataValue(ATTRID_ERRINFO, (long)1,TRUE);
		}
	}

	CIotPxEngineDeviceBase::ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS);

	return 0;
}

long CSttPpEngineDevice::Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return CIotPxEngineDeviceBase::Process_Cmd_IOT_GetDataset(pPxCommChn, oDrvIotCmd);
}

long CSttPpEngineDevice::Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttPpEngineDevice::Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttPpEngineDevice::Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

CDvmDataset* CSttPpEngineDevice::FindDvmDataset()
{
	CDvmDataset *pDataset = m_pPxiDevice->FindDvmDataset(m_strDatasetID);
	return pDataset;
}

//shaolei 2023-9-11
long CSttPpEngineDevice::XOnEngineTimer_RTDATA_ReadAin()
{
	if (m_pPxiDevice == NULL)
	{
		return -1;
	}

	return m_pPxiDevice->RunProcedure_Timer_ReadAin();
}

long CSttPpEngineDevice::XOnEngineTimer_RTDATA_ReturnEvent()
{
	if (m_pPxiDevice == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("返回RTDATA失败，m_pPxiDevice == NULL"));
		return -1;
	}

	CString strDatasetPath;
	strDatasetPath = _T("dsAin");  
	CDvmDataset *pDataset = m_pPxiDevice->FindDvmDataset(strDatasetPath);

	if (pDataset == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("返回RTDATA失败，未找到数据集【%s】"), strDatasetPath.GetString());
		return -1;
	}

	CSttSysState oSysState;
	oSysState.m_strID = SYS_STATE_EVENT_OnRTDATA;
	oSysState.m_strRetType = SYS_STATE_RETTYPE_RTDATA;
	CSttParas *pParas = oSysState.GetSttParas();
	pParas->AddNewData(STT_CMD_PARA_DeviceSN, m_strID, TRUE);
	CDataGroup *pParasGrp = pParas->AddNewGroup(_T("rtdata"), _T("rtdata"), _T(""));

	POS pos = pDataset->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pDataset->GetNext(pos);
		CDvmData *pNewData = pParasGrp->AddNewData(pData->m_strID, pData->m_strValue);
		pNewData->m_strName = pData->m_strName;
		pNewData->m_strUnit = pData->m_strUnit;
	}

	oSysState.Set_Xml_Pkg_With_Name(TRUE);
	iotpx_ReturnSysState(oSysState, _T("ats"), m_strID);
	oSysState.Set_Xml_Pkg_With_Name(FALSE);

	return 0;
}

unsigned long CSttPpEngineDevice::OnProcedureEndMsg(unsigned long wParam, unsigned long lParam)
{
	return CIotPxEngineDeviceBase::OnProcedureEndMsg(wParam, lParam);
}

extern CIotPxEngineServer* g_theIotPxEngineServer;
unsigned long CSttPpEngineDevice::OnEngineSystemMessage(unsigned long wPara,unsigned long lPara)
{
	CSttIotCmd *pIotCmd = m_oSttIotCmdDriver.SttIotCmd();
	CIotPxCommChannelInterface *pCommCh = NULL;

	if (pIotCmd != NULL)
	{
		pCommCh = (CIotPxCommChannelInterface *)pIotCmd->GetSttCmmOptrInterface();
	}

	CSttSysState oSysState;
	CSttParas *pSttParas = oSysState.GetSttParas();

	oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();

	if (pIotCmd != NULL)
	{
		oSysState.m_strID = pIotCmd->m_strID;
	}
	else
	{
		oSysState.m_strID = STT_CMD_TYPE_IOT_CloseDevice;
	}

	//shaolei 2023-9-11 添加类型判断
	if (pCommCh != NULL)
	{
		if (pCommCh->GetClassID() != _PxCommChannelInterface_CLASSID_MQTT_)
		{
			oSysState.Set_ExecStatus_Success();
		}
	}
	
	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);

	if (oSysState.m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{//关闭指令出发过来的调用：多连接模式下，直接返回连接失败
		pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);
	}
	else
	{

		if (IsConnectSuccessful())
		{
			pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectSuccessful, TRUE);
			pSttParas->SetDataValue(ATTRID_ERRINFO, (long)0,TRUE);
		}
		else
		{
			pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);
			pSttParas->SetDataValue(ATTRID_ERRINFO, (long)1,TRUE);
		}
	}

	//shaolei 2023-9-11
	if (pCommCh != NULL)
	{
		if (pCommCh->GetClassID() == _PxCommChannelInterface_CLASSID_MQTT_)
		{
			oSysState.SetEvent();
			oSysState.m_strID = SYS_STATE_EVENT_OnEngineEvent;

			if (IsConnectSuccessful())
			{
				m_pIotPxEngineDeviceWnd->SetPpEngineTimer(TIMER_PPENGINE_RTDATA, TIMER_PPENGINE_RTDATA_LONG);
				pSttParas->SetDataValue(SYS_STATE_XEVENT_EVENTID, SYS_STATE_XEVENT_EVENTID_ConnectDeviceSuccessful, TRUE);
			}
			else
			{
				pSttParas->SetDataValue(SYS_STATE_XEVENT_EVENTID, SYS_STATE_XEVENT_EVENTID_ConnectDeviceFailed, TRUE);
			}
		}
	}

	CString strConnectState;
	pSttParas->GetDataValue(STT_SYS_STATE_ID_ConnectState, strConnectState);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"【CSttPpEngineDevice】【m_strID=%s】【oSysState.m_strID=%s】【nConnectState=%s】",m_strID.GetString(),oSysState.m_strID.GetString(),strConnectState.GetString());

	//shaolei 2023-9-11 end

	if (pCommCh != NULL)
	{
		iotpx_ReturnSysState(pCommCh, oSysState);
	}
	else
	{
		ReturnSysState(NULL, oSysState);
	}

	m_oSttIotCmdDriver.Release();
//	CIotPxEngineDeviceBase::OnEngineSystemMessage(wPara, lPara);

    if (m_pPxiDeviceForDel != NULL)
    {
        m_pPxiDeviceForDel->m_pPxiDeviceCommCmdMessage = NULL;
        m_pPxiDeviceForDel->m_pEngineData->m_pPxiDeviceCommCmdMessage = NULL;

		if (g_theIotPxEngineServer != NULL)
		{
			g_theIotPxEngineServer->RemoveDeviceFromFolDel(this);
		}
		
        delete this;
    }

	return 0;
}

long CSttPpEngineDevice::ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttSysState &oSysState)
{
	if (pPxCommChn == NULL)
	{
		CIotPxCommChannelInterface *p = NULL;
		long nCount = m_oArrCommCh.GetMaxCount();

		for (long k=0; k<nCount; k++)
		{//2022-10-27  lijunqing  不考虑效率，每次发送都序列化一次数据
			p = m_oArrCommCh.GetObject(k);

			if(p == NULL)
			{
				break;
			}

			if (p != NULL)
			{
				iotpx_ReturnSysState(p, oSysState);
			}
		}
	}
	else
	{
		iotpx_ReturnSysState(pPxCommChn, oSysState);
	}

	return 0;
}

void CSttPpEngineDevice::AddRetDatasToParas(CSttParas *pSttParas)
{
	if ((m_strProcedureID == CMDID_writeena)||
		(m_strProcedureID == CMDID_SingleDoutSelect)||(m_strProcedureID == CMDID_DoubleDoutSelect)||
		(m_strProcedureID == CMDID_SingleDoutExecute)||(m_strProcedureID == CMDID_DoubleDoutExecute)||
		(m_strProcedureID == CMDID_DoubleDoutQuash)||(m_strProcedureID == CMDID_DoubleDoutQuash))
	{
		long nErrorValue = 0;

		if (m_pPxiDevice != NULL)
		{
			if (m_pPxiDevice->m_pCurrDataset != NULL)
			{
				CDvmDevice *pCurDvmDevice = (CDvmDevice*)m_pPxiDevice->m_pCurrDataset->GetAncestor(DVMCLASSID_CDVMDEVICE);

				if (pCurDvmDevice != NULL)
				{
					nErrorValue = pCurDvmDevice->m_pDeviceAttr->GetValueLong(ATTRID_ERRINFO);
				}
			}
		}
		
		pSttParas->SetDataValue(ATTRID_ERRINFO, nErrorValue,TRUE);
// 		pSttParas->AddNewData(ParaID_setzone, m_pMmsDevice->m_pACSI_NODE->nRunSGIndex);
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Return ZoneIndex=%d"), m_pMmsDevice->m_pACSI_NODE->nRunSGIndex);
	}

}


