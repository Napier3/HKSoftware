#include "stdafx.h"
#include "SttCmsEngineDevice.h"

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS

//CIotPxEngineDeviceWnd *g_pIotPxEngineDeviceWnd = NULL;

CSttCmsEngineDevice::CSttCmsEngineDevice()
{
	m_pCmsDevice = NULL;
}

CSttCmsEngineDevice::~CSttCmsEngineDevice()
{
	
}

/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
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
long CSttCmsEngineDevice::Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	m_oSttIotCmdDriver = oDrvIotCmd;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CIotPxEngineDeviceBase::Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);

	//��������Ϣ�Լ�����
	m_pCmsDevice->Attatch(this);

	//��ȡ����
	CSttParas *pSttParas = pIotCmd->GetSttParas();
	CDataGroup *pCommConfig = (CDataGroup*)pSttParas->FindByID(STT_CMD_PARA_CommConfig);

	if (! m_pCmsDevice->IsConnectSuccessful())
	{//������ӳɹ�����ʾ������ӻ������ظ�����
		if (pCommConfig != NULL)
		{//��ʼ�����ӣ�ͨ������
			m_pCmsDevice->InitCmmConfig(pCommConfig, TRUE);
		}
		else
		{
			m_pCmsDevice->CommConfig(_T(""));
		}

		ReturnSysState2(pIotCmd, pPxCommChn);
	}
	else
	{
		ReturnSysState2(pIotCmd, pPxCommChn);
		OnSysMessage(0, 0);
	}

	return 0;
}

long CSttCmsEngineDevice::Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	long nCount = CIotPxEngineDeviceBase::Process_Cmd_IOT_CloseDevice(pPxCommChn, oDrvIotCmd);

	if (nCount == 0)
	{
		//��ʾû�����ã��ͷ��豸
		m_pCmsDevice->UnLoad();

		//��ǰʵ���豸����ֵΪ��
		m_pCmsDevice = NULL;
	}

	return nCount;
}

BOOL CSttCmsEngineDevice::IsConnectSuccessful()
{
	if (m_pCmsDevice == NULL)
	{
		return FALSE;
	}

	return m_pCmsDevice->IsConnectSuccessful();
}

long CSttCmsEngineDevice::Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttCmsEngineDevice::Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

/*
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="id-procedure" value="WriteSetting">��ִ�е�ͨ�Ź��̡�
			<value data-type="FLOAT" id="" name="" value=""/>��ͨ�Ź��̵Ĳ�����
		</data>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
*/
long CSttCmsEngineDevice::Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return CIotPxEngineDeviceBase::Process_Cmd_IOT_RunProcedure(pPxCommChn, oDrvIotCmd);
}

long CSttCmsEngineDevice::IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	m_oSttIotCmdDriver = oDrvIotCmd;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);

	CSttParas* pParas = pIotCmd->GetSttParas();
	pParas->GetDataValue(STT_CMD_PARA_ProcedureID, m_strProcedureID);

	//ParaInterface
	CDvmData *pProcedure = (CDvmData*)pParas->FindByID(STT_CMD_PARA_ProcedureID);
	CPoMmsDataInterface *pDataInterface = m_pCmsDevice->GetDataInterface();
	pDataInterface->InitDataInterface(pProcedure);

	//Init Dataset
	CDvmDataset *pDataset = pParas->GetDvmDataset(FALSE);

	if ( pParas->GetDataValue(STT_CMD_PARA_DatasetPath, m_strDatasetID) )
	{
		if (pDataset != NULL)
		{//���ͨ������������ݼ���������ʾΪд����ڴ˸������ݼ�
			CPoMmsDataSet *pPxiDataset = m_pCmsDevice->FindDataSet(m_strDatasetID);

			if (pPxiDataset != NULL)
			{
				pPxiDataset->InitByDataset(pDataset);
			}
		}
	}

	//��������Ϣ�Լ�����
	//m_pPxiDevice->RegisterProcedureWndMsg(m_strProcedureID, GetMsgRcvWnd(), WM_PROCEDURE_END_MSG);

	//Run Procedure
	m_pCmsDevice->RunProcedure(m_strProcedureID, m_strDatasetID);

	ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS);

	return 0;
}

long CSttCmsEngineDevice::Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return CIotPxEngineDeviceBase::Process_Cmd_IOT_GetDataset(pPxCommChn, oDrvIotCmd);
}

long CSttCmsEngineDevice::Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttCmsEngineDevice::Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CSttCmsEngineDevice::Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

CDvmDataset* CSttCmsEngineDevice::FindDvmDataset()
{
	if (m_pCmsDevice == NULL)
	{
		return NULL;
	}

	CPoMmsDataSet *pPoDataset = m_pCmsDevice->FindDataSet(m_strDatasetID);
	CDvmDataset *pDataset = NULL;

	if (pPoDataset != NULL)
	{
		pPoDataset->GetXmlData();
		pDataset = pPoDataset->m_pTempNewDataset;
	}
	return pDataset;
}

unsigned long CSttCmsEngineDevice::OnProcedureEndMsg(unsigned long wParam, unsigned long lParam)
{
	return CIotPxEngineDeviceBase::OnProcedureEndMsg(wParam, lParam);
}

unsigned long CSttCmsEngineDevice::OnEngineSystemMessage(unsigned long wPara,unsigned long lPara)
{
	CIotPxEngineDeviceBase::OnEngineSystemMessage(wPara, lPara);

	if (m_pCmsDevice == NULL)
	{
		delete this;
	}

	return 0;
}
#endif //#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
