#include "stdafx.h"
#include"SttSmartTestSvrInterface.h"


CSttSmartTestSvrInterface::CSttSmartTestSvrInterface()
{
	m_pSttProtocol = NULL;
}

CSttSmartTestSvrInterface::~CSttSmartTestSvrInterface()
{

}

long CSttSmartTestSvrInterface::Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol)
{		
	CSttAtsCmd *pCmd = (CSttAtsCmd *)oAtsCmdDrv.GetXObjectRef();

	if (pCmd->m_strID == STT_CMD_TYPE_ATS_CreateTest)
	{
		if (m_pSttProtocol == NULL)
		{
			m_pSttProtocol = pSttProtocol;
		}

		return Ats_CreateTest(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_StartTest)
	{
		return Ats_StartTest(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_StopTest)
	{
		return Ats_StopTest(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_CloseTest)
	{
		return Ats_CloseTest(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_SetItemState)
	{
		return Ats_SetItemState(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_TestItem)
	{
		return Ats_TestItem(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_TestFrom)
	{
		return Ats_TestFrom(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_TestAllFailedItems)
	{
		return Ats_TestAllFailedItems(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_GetItemReport)
	{
		return Ats_GetItemReport(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_GetReportFile)
	{
		return Ats_GetReportFile(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_GetSystemState)
	{
		return Ats_GetSystemState(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_CreateDevice)
	{
		//return Ats_CreateDevice(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_ConnectDevice)
	{
		//return Ats_ConnectDevice(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_ConfigDevice)
	{
		//return Ats_ConfigDevice(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_GetDataset)
	{
		//return Ats_GetDataset(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_SetDataset)
	{
		//return Ats_SetDataset(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_RunProcedure)
	{
		//return Ats_RunProcedure(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_CloseDevice)
	{
		//return Ats_CloseDevice(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_ConfigEngine)
	{
		//return Ats_ConfigEngine(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_InputData)
	{
		return Ats_InputData(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_FinishInputData)
	{
		return Ats_FinishInputData(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_QueryAtsFile)
	{
		//return Ats_QueryAtsFile(oAtsCmdDrv, pSttProtocol);
		return -1;
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_ExportReport)
	{
		return Ats_ExportReport(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_SetItemsReport)
	{
		return Ats_SetItemsReport(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_QueryItems)
	{
		return Ats_QueryItems(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_ConfigTest)
	{
		return Ats_ConfigTest(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_QueryTestPara)
	{
		return Ats_QueryTestParas(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_SetTestPara)
	{
		return Ats_SetTestParas(oAtsCmdDrv, pSttProtocol);
	}
	else if (pCmd->m_strID == STT_CMD_TYPE_ATS_FlowSetBench)
	{
		return Ats_ConfigTest(oAtsCmdDrv, pSttProtocol);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Cmd_Ats [%s] not implemented"), pCmd->m_strID.GetString());
	}

	return 0;
}

long CSttSmartTestSvrInterface::Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)
{
	CSttSysState *pSysState = (CSttSysState *)oSysStateDrv.GetXObjectRef();

	if (pSysState->m_strID == SYS_STATE_EVENT_OnItemStateChanged)
	{
		return Process_Cmd_SysState_ItemStateChanged(oSysStateDrv, pSttProtocol);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnTestFinished)
	{
		return Process_Cmd_SysState_TestFinished(oSysStateDrv, pSttProtocol);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnTestStarted)
	{
		return Process_Cmd_SysState_TestStarted(oSysStateDrv, pSttProtocol);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnTestStoped)
	{
		return Process_Cmd_SysState_TestStoped(oSysStateDrv, pSttProtocol);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_OnReprot)
	{
		return Process_Cmd_SysState_OnReport(oSysStateDrv, pSttProtocol);
	}
	else if (pSysState->m_strID == SYS_STATE_EVENT_ExportReport)
	{
		return Process_Cmd_SysState_ExportReport(oSysStateDrv, pSttProtocol);
	}

	return 0;
}