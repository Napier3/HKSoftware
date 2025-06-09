#include "stdafx.h"
#include "IotPxEngineDeviceBase.h"

#ifdef _PSX_IDE_QT_
#include "IotPxEngineDeviceWnd_Linux.h"
#else
#include "IotPxEngineDeviceWnd_Win.h"
#endif

//#include "../../../Protocol/Module/PxiEngine/PxiDevice.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"

//extern CIotPxEngineDeviceWnd *g_pIotPxEngineDeviceWnd;
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

CIotPxEngineDeviceBase::CIotPxEngineDeviceBase()
{
	//m_pPxCommChannel = NULL;
	m_pDvmDevice = NULL;

#ifdef _PSX_IDE_QT_
	m_pIotPxEngineDeviceWnd = new CIotPxEngineDeviceWnd_Linux();
#else
	m_pIotPxEngineDeviceWnd = new CIotPxEngineDeviceWnd_Win();
#endif
	
	m_pIotPxEngineDeviceWnd->CreateIotPxEngineDeviceWnd();
	m_pIotPxEngineDeviceWnd->m_pIotPxEngineDevice = this;

	m_oArrCommCh.SetMaxCount(20);
	m_oArrSttIotCmdDriver.SetMaxCount(20);
}

CIotPxEngineDeviceBase::~CIotPxEngineDeviceBase()
{
	m_pIotPxEngineDeviceWnd->m_pIotPxEngineDevice = NULL;//zhouhj 2024.10.21
    m_pIotPxEngineDeviceWnd->DestroyWindow();

#ifdef _PSX_IDE_QT_
    m_pIotPxEngineDeviceWnd->deleteLater();
#else
	delete m_pIotPxEngineDeviceWnd;
#endif

    m_pIotPxEngineDeviceWnd = NULL;
}

unsigned long CIotPxEngineDeviceBase::GetMsgRcvWnd()
{
#ifdef _PSX_IDE_QT_
	return (unsigned long)m_pIotPxEngineDeviceWnd;
#else
	return (unsigned long)m_pIotPxEngineDeviceWnd->m_hWnd;
#endif
}


void CIotPxEngineDeviceBase::OnCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
	m_pIotPxEngineDeviceWnd->PostMessage(WM_PROCEDURE_END_MSG, wParam, lParam);
}

void CIotPxEngineDeviceBase::OnSysMessage(WPARAM wParam, LPARAM lParam)
{
    if (m_pIotPxEngineDeviceWnd != NULL)
    {
		m_pIotPxEngineDeviceWnd->PostMessage(WM_SYSTEM_MSG, wParam, lParam);
    }
}

void CIotPxEngineDeviceBase::OnEventMessage(WPARAM wParam, LPARAM lParam)
{
	m_pIotPxEngineDeviceWnd->PostMessage(WM_EVENT_MSG, wParam, lParam);
}

//2020-11-24  lijunqing LINUX  post msg to ats
void CIotPxEngineDeviceBase::OnEngineDataDeleted(const CString &strDeviceID)
{

}

void CIotPxEngineDeviceBase::OnReportMessage(WPARAM wParam, LPARAM lParam)
{
	m_pIotPxEngineDeviceWnd->PostMessage(WM_MMS_REPORT_MSG, wParam, lParam);
}

long CIotPxEngineDeviceBase::XOnEngineTimer_RTDATA()
{
	if (! IsConnectSuccessful())
	{//断开连接状态，关闭定时器
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("设备【%s】断开链接，关闭RTDATA定时器"), m_strID.GetString());
		m_pIotPxEngineDeviceWnd->KillPpEngineTimer(TIMER_PPENGINE_RTDATA);
		return 0;
	}

	//RTDATA，先读装置数据（ReadAin）。再返回RTDATA事件
	//shaolei ljq 先返回事件，再读。防止返回事件的时候，正在写数据集 2023-9-13
	XOnEngineTimer_RTDATA_ReturnEvent();
	//XOnEngineTimer_RTDATA_ReadAin();
	return 0;
}

long CIotPxEngineDeviceBase::XOnEngineTimer_RTDATA_ReadAin()
{
	ASSERT(FALSE);
	return -1;
}

long CIotPxEngineDeviceBase::XOnEngineTimer_RTDATA_ReturnEvent()
{
	ASSERT(FALSE);
	return -1;
}

/*
//物联规约命令  20210619  xxy
#define STT_CMD_TYPE_IOT_PkgParse			_T("PkgParse")
#define STT_CMD_TYPE_IOT_PkgProduce			_T("PkgProduce")
#define STT_CMD_TYPE_IOT_RunProcedure		_T("RunProcedure")
#define STT_CMD_TYPE_IOT_GetDataset			_T("GetDataset")
#define STT_CMD_TYPE_IOT_SetDataset			_T("SetDataset")
#define STT_CMD_TYPE_IOT_CreateDevice		_T("CreateDevice")
#define STT_CMD_TYPE_IOT_ConfigDevice		_T("ConfigDevice")
#define STT_CMD_TYPE_IOT_CloseDevice		_T("CloseDevice")
#define STT_CMD_TYPE_IOT_UpdateDataset      _T("UpdateDataset")

*/
long CIotPxEngineDeviceBase::Process_Cmd_IOT(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();

	if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_PkgParse)
	{
		return Process_Cmd_IOT_PkgParse(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_PkgProduce)
	{
		return Process_Cmd_IOT_PkgProduce(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_RunProcedure)
	{
		return Process_Cmd_IOT_RunProcedure(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_GetDataset)
	{
		return Process_Cmd_IOT_GetDataset(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_SetDataset)
	{
		return Process_Cmd_IOT_SetDataset(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_ConfigDevice)
	{
		return Process_Cmd_IOT_ConfigDevice(pPxCommChn, oDrvIotCmd);
	}
	else if (pIotCmd->m_strID == STT_CMD_TYPE_IOT_UpdateDataset)
	{
		return Process_Cmd_IOT_UpdateDataset(pPxCommChn, oDrvIotCmd);
	}
	else
	{
		return -1;
	}
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	m_oSttIotCmdDriver = oDrvIotCmd;
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	m_oArrCommCh.FreeObject(pPxCommChn);
	long nCount = m_oArrCommCh.GetObjectCount();

	if (nCount == 0)
	{
		OnSysMessage(0, 0);
	}
	else
	{
	}

	return nCount;
}

BOOL CIotPxEngineDeviceBase::CloseByPxCommChannel(CIotPxCommChannelInterface *pPxCommChn)
{
	if (m_oArrCommCh.HasObject(pPxCommChn))
	{
		m_oArrCommCh.FreeObject(pPxCommChn);
		return TRUE;
	}

	return FALSE;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_PkgParse(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_PkgProduce(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	if (! IsConnectSuccessful())
	{//断开连接状态，返回执行失败，返回断开连接
		CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_FAILURE);
		ReturnConnectFailed(pIotCmd, pPxCommChn);

		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Process_Cmd_IOT_RunProcedure: IsConnectSuccessful == false"));
		return 0;
	}

	if (m_oSttIotCmdDriver.SttIotCmd() != NULL)
	{
		//当前命令还没有执行完毕，就收到下一个通信命令
		//此处暂时缓存通信命令，并且返回应到以及执行成功消息
		//立即返回执行成功消息的目的是避免客户端超时
		CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_ACK);

		m_oArrSttIotCmdDriver.AddObject((CSttIotCmdDriver*)oDrvIotCmd.Clone());

		ReturnSysState(pPxCommChn, pIotCmd, STT_CMD_ExecStatus_SUCCESS);

		return 0;
	}
	else
	{
		return IOT_RunProcedure(pPxCommChn, oDrvIotCmd);
	}

	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_GetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_SetDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_ConfigDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

long CIotPxEngineDeviceBase::Process_Cmd_IOT_UpdateDataset(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

//lijunqing 2022-10-9
// long CIotPxEngineDeviceBase::ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus, CSttCmdData *pRetData)
// {
// 	if (m_pPxCommChannel == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttCmd->m_pRefSocketDataBase == NULL"));
// 		return 0;
// 	}
// 
// 	CSttSysState oSysState;
// 	oSysState.UpdateSysStateHead(pSttCmd);
// 
// 	if (pRetData != NULL)
// 	{//返回结果数据
// 		oSysState.AppendParas(*pRetData);
// 	}
// 
// 	oSysState.Set_ExecStatus(nCmdExecStatus);
// 
// 	return m_pPxCommChannel->PxSendSysState(&oSysState);
// }

//lijunqing 2022-10-9
long CIotPxEngineDeviceBase::ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttCmdBase *pSttCmd, long nCmdExecStatus,
											CDvmDataset *pDataset,const CString &strAddDataID,const CString &strAddDataValue)
{
	if (pPxCommChn == NULL)
	{
		CIotPxCommChannelInterface *p = NULL;
		long nCount = m_oArrCommCh.GetMaxCount();

		for (long k=0; k<nCount; k++)
		{
			p = m_oArrCommCh.GetObject(k);

			if (p != NULL)
			{
				iotpx_ReturnSysState(p, pSttCmd, nCmdExecStatus, pDataset,strAddDataID,strAddDataValue);
			}
		}
	}
	else
	{
		iotpx_ReturnSysState(pPxCommChn, pSttCmd, nCmdExecStatus, pDataset,strAddDataID,strAddDataValue);
	}

	return 0;
}

long CIotPxEngineDeviceBase::ReturnSysState(CIotPxCommChannelInterface *pPxCommChn, CSttSysState &oSysState)
{
	if (pPxCommChn == NULL)
	{
		CIotPxCommChannelInterface *p = NULL;
		long nCount = m_oArrCommCh.GetMaxCount();

		for (long k=0; k<nCount; k++)
		{//2022-10-27  lijunqing  不考虑效率，每次发送都序列化一次数据
			p = m_oArrCommCh.GetObject(k);

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

void CIotPxEngineDeviceBase::InitSysStateByCurrCmd(CSttSysState &oSysState)
{
	CSttIotCmd *pIotCmd = m_oSttIotCmdDriver.SttIotCmd();

	if (pIotCmd != NULL)
	{
		CSttParas *pSttParas = oSysState.GetSttParas();
		oSysState.UpdateSysStateHead(pIotCmd);
	}
	else
	{
		oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();
	}
}


void CIotPxEngineDeviceBase::ReturnSysState2(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pIotCmd);
	CSttParas *pSttParas = oSysState.GetSttParas();
	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);

	iotpx_ReturnSysState(pPxCommChn, oSysState);
}

void CIotPxEngineDeviceBase::ReturnConnectFailed(CSttIotCmd *pIotCmd, CIotPxCommChannelInterface *pPxCommChn)
{
	CSttSysState oSysState;
	CSttParas *pSttParas = oSysState.GetSttParas();

	oSysState.m_strRetSttCmd = STT_CMD_TYPE_IOT_CreateDevice;
	oSysState.Set_ExecStatus_Failure();
	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);
	pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);

	if (pPxCommChn != NULL)
	{
		iotpx_ReturnSysState(pPxCommChn, oSysState);
	}
	else
	{
		ReturnSysState(NULL, oSysState);
	}

	m_oSttIotCmdDriver.Release();
	CSttIotCmdDriver *pDrvIotCmd = NULL;

	while (m_oArrSttIotCmdDriver.GetCurrReadCount() > 0)
	{
		pDrvIotCmd = m_oArrSttIotCmdDriver.ReadCurr();
		m_oArrSttIotCmdDriver.FreeCurr();
		delete pDrvIotCmd;
	}
}

CDvmDataset* CIotPxEngineDeviceBase::FindDvmDataset()
{
	return NULL;
}

long CIotPxEngineDeviceBase::IOT_RunProcedure(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver oDrvIotCmd)
{
	return 0;
}

unsigned long CIotPxEngineDeviceBase::OnProcedureEndMsg(unsigned long wParam, unsigned long lParam)
{
	CSttSysState oSysState;
	CSttIotCmd *pIotCmd = m_oSttIotCmdDriver.SttIotCmd();
	CSttParas *pSttParas = oSysState.GetSttParas();

	if (pIotCmd != NULL)
	{
		oSysState.UpdateSysStateHead(pIotCmd);
	}
	else
	{
		oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();
		oSysState.m_strID = STT_CMD_TYPE_IOT_RunProcedure;
	}

	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);
	pSttParas->SetDataValue(STT_CMD_PARA_ProcedureID, m_strProcedureID, TRUE);
	pSttParas->SetDataValue(STT_CMD_PARA_DatasetPath, m_strDatasetID, TRUE);
	CString strSysState;
	strSysState = pxi_get_engine_sys_state(lParam);
	pSttParas->SetDataValue(PXI_DATA_ID_EngineSysState, strSysState, TRUE);

	if (oSysState.m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{//关闭指令出发过来的调用：多连接模式下，直接返回连接失败
		pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);
	}

	if (oSysState.m_strID == STT_CMD_TYPE_IOT_CreateDevice)
	{
		if (lParam == engineCommError)
		{
			pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);
		}
	}

	//处理返回指令写到的数据对象
	//1、返回数据集：为通用操作，放在基类
	CDvmDataset *pDataset = FindDvmDataset();
	if (pDataset != NULL)
	{
		pSttParas->AddTail(pDataset);
	}

	//2、返回其他数据：根据不同的协议，做不同处理
	AddRetDatasToParas(pSttParas);

	oSysState.Set_Xml_Pkg_With_Name(TRUE);
	if (pIotCmd != NULL)
	{
		iotpx_ReturnSysState((CIotPxCommChannelInterface*)pIotCmd->GetSttCmmOptrInterface(), oSysState);
	}
	else
	{
		ReturnSysState(NULL, oSysState);
	}
	oSysState.Set_Xml_Pkg_With_Name(FALSE);

	if (pDataset != NULL)
	{
		pSttParas->Remove(pDataset);
	}

	//命令执行完毕，清空
	m_strProcedureID.Empty();
	m_strDatasetID.Empty();
	m_oSttIotCmdDriver.Release();

	//如果处理多连接端实现不同通信命令操作，需要记录通信命令链表
	//此处添加执行下一个通信命令的代码
	if (m_oArrSttIotCmdDriver.GetCurrReadCount() > 0)
	{
		m_oSttIotCmdDriver.Release();
		CSttIotCmdDriver *pDrvIotCmd = m_oArrSttIotCmdDriver.ReadCurr();
		m_oArrSttIotCmdDriver.FreeCurr();
		CSttIotCmdDriver oDrvIotCmd = *pDrvIotCmd;
		delete pDrvIotCmd;
		CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
		Process_Cmd_IOT_RunProcedure((CIotPxCommChannelInterface*)pIotCmd->GetSttCmmOptrInterface(), oDrvIotCmd);
	}

	return 0;
}

/*   2023-9-11 针对南瑞传感器项目，对事件的参数，重新进行了整理
<sys-state name="" id="EngineEvent" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data id="EventID" data-type="string" value="CommFinish" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>
*/
unsigned long CIotPxEngineDeviceBase::OnEngineSystemMessage(unsigned long wPara,unsigned long lPara)
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
		}
		else
		{
			pSttParas->SetDataValue(STT_SYS_STATE_ID_ConnectState, EngineSysState_ConnectFailed, TRUE);
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
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"【CIotPxEngineDeviceBase】【m_strID=%s】【oSysState.m_strID=%s】【nConnectState=%ld】",m_strID.GetString(),oSysState.m_strID.GetString(),strConnectState.GetString());
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

	return 0;
}


unsigned long CIotPxEngineDeviceBase::OnEngineEventMessage(unsigned long wPara,unsigned long lPara)
{
	CSttSysState oSysState;
	CSttParas *pSttParas = oSysState.GetSttParas();

	oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();
	oSysState.m_strID =  SYS_STATE_EVENT_OnEngineEvent;

	if (lPara == engineDvmEnumFinish)
	{
		pSttParas->AddNewData(SYS_STATE_XEVENT_EVENTID, EngineSysState_DvmEnumFinish);
		AddDvmEnumToParas(pSttParas);
	}

 	oSysState.Set_ExecStatus_Success();
 	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);
	ReturnSysState(NULL, oSysState);

	return 0;
}

unsigned long CIotPxEngineDeviceBase::OnMmsReportMessage(unsigned long wPara,unsigned long lPara)
{
	CSttSysState oSysState;
	CSttParas *pSttParas = oSysState.GetSttParas();

	oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();
	oSysState.m_strID =  SYS_STATE_EVENT_OnEngineEvent;
	pSttParas->AddNewData(SYS_STATE_XEVENT_EVENTID, EngineEvent_Report);
	AddSoeReportToParas(pSttParas, wPara, lPara);
	oSysState.Set_ExecStatus_Success();
	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);

	oSysState.Set_Xml_Pkg_With_Name(TRUE);
	ReturnSysState(NULL, oSysState);

	return 0;
}

void CIotPxEngineDeviceBase::AddDvmEnumToParas(CSttParas *pSttParas)
{
	
}

//2023-3-4  lijunqing  初始化通信过程结束返回的参数数据
void CIotPxEngineDeviceBase::AddRetDatasToParas(CSttParas *pSttParas)
{


}

//2023-3-5  lijunqing  添加报告数据到
void CIotPxEngineDeviceBase::AddSoeReportToParas(CSttParas *pSttParas, unsigned long wPara,unsigned long lPara)
{


}

//////////////////////////////////////////////////////////////////////////
//CThreadProgressInterface
void CIotPxEngineDeviceBase::SetTitle(const CString &strTitle)
{
	CSttSysState oSysState;
	CSttParas *pSttParas = oSysState.GetSttParas();

	oSysState.m_strRetSttCmd = CSttCmdDefineXmlRWKeys::CSttIotCmdKey();
	oSysState.m_strID =  SYS_STATE_RETTYPE_LOG;
	oSysState.SetRetType(SYS_STATE_RETTYPE_LOG);
	pSttParas->SetDataValue(STT_CMD_PARA_DeviceSN, m_strID, TRUE);
	oSysState.AddMsg(SYS_STATE_RETTYPE_LOG, strTitle);

	ReturnSysState(NULL, oSysState);
}

void CIotPxEngineDeviceBase::SetMaxRange(long nMaxRange)
{

}

void CIotPxEngineDeviceBase::ResetProcess()
{

}

void CIotPxEngineDeviceBase::StepIt()
{

}

void CIotPxEngineDeviceBase::ShowMsg(const CString &strMsg)
{

}

void CIotPxEngineDeviceBase::StartTimer(long nTimerLong)
{
	
}

void CIotPxEngineDeviceBase::Finish(DWORD dwParam)
{

}

void CIotPxEngineDeviceBase::StepPos(long nPos)
{

}

void CIotPxEngineDeviceBase::Exit()
{
	
}

