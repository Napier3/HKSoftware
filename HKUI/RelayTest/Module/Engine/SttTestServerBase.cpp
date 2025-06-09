#include "stdafx.h"
#include "SttTestServerBase.h"

#include "../SttSocket/TestServer/VC/SttTestServerSocket.h"

#include "../SttTestBase/SttTestFactory.h"
#include "../ReplayTest/SttComtradeRcvSocket.h"
#include "../RecordTest/SttRcdSendSocket.h"

#include"../SttTest/Common/Adjust/SttAdjustTool.h"
#include"../SttTest/Common/Meas/meas_define.h"

extern MEAS_DEVICE *g_MeasDevice;
#ifndef _STT_NOT_IN_TEST_SERVER_
#include "../SttDevice/SttDeviceStatus.h"

#ifdef _PSX_QT_LINUX_
#include "QMap"
#include "../SttDevice/SttDeviceBase.h"
#include "../SttTest/Common/SttSystemDefaultOutput.h"
#include "../SttTest/Common/SttSystemConfig.h"
#include "../SttTest/Common/SttAppRatesConfig.h"
#include "../SttTest/Common/SttUartConfig.h"
extern PTMT_ADJ_MODULE_OUTPUT g_theModuleOutPut;
extern CSttSystemDefaultOutput g_theSystemDefaultOutput;
extern CSttDevSystemParas *g_theSystemConfig;
BOOL g_bRtDataLock = FALSE;
#endif//_PSX_QT_LINUX_

#endif//_STT_NOT_IN_TEST_SERVER_

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


long CSttTestServerBase::m_nSttTestServerEngineRef = 0;
CSttTestServerBase* CSttTestServerBase::g_pSttTestServerEngine = NULL;

CSttXmlSerializeBase* stt_create_sys_state_paras_register(CSttXmlSerializeTool &oSttXmlRegister, CSttSysState &oSysState, CSttCmdBase *pSttCmd)
{
	oSysState.UpdateSysStateHead(pSttCmd);
	oSysState.GetSttParas();
	oSysState.Set_ExecStatus_Success();
	oSttXmlRegister.CreateXmlSerializeRegister(&oSysState);

	CSttXmlSerializeBase *pParasRegister = oSttXmlRegister.GetParas();

	return pParasRegister;
}

CSttXmlSerializeBase* stt_create_sys_state_paras_register(CSttXmlSerializeTool &oSttXmlRegister, CSttSysState &oSysState, CSttCmdBase *pSttCmd, char *pszRetType)
{
	oSysState.SetRetType(pszRetType);
	return stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, pSttCmd);
}

CSttXmlSerializeBase* stt_create_sys_state_paras_register(CSttXmlSerializeTool &oSttXmlRegister, CSttSysState &oSysState, CSttCmdBase *pSttCmd, const CString &strRetType)
{
	oSysState.SetRetType(strRetType);
	return stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, pSttCmd);
}

CSttTestServerBase::CSttTestServerBase()
{

}

CSttTestServerBase::~CSttTestServerBase()
{	

}

#define DeviceUTC      0
#define DeviceException 1
#define TestRtDatas    2
#define IecRtDatas     3
#define DevExceptClear 4

void CSttTestServerBase::ReturnSysStatesToChildren(int nDataType)
{
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister;
	CSttTestCmd oSttCmd;
	oSttCmd.m_strID = _T("");
	oSttCmd.m_nIDTester = m_oSttTestCmd.m_nIDTester;
	oSttCmd.m_nPkgSendIndex = m_oSttTestCmd.m_nPkgSendIndex;

	CSttXmlSerializeTool oSttXmlRegister;

#ifndef _STT_NOT_IN_TEST_SERVER_
	switch(nDataType)
	{
		case DeviceUTC:
		{
        pParasRegister=stt_create_sys_state_paras_register(oSttXmlRegister,
							 oSysState, &oSttCmd, SYS_STATE_RETTYPE_RTDATA);

#ifdef _PSX_QT_LINUX_
			if(pParasRegister != NULL)
			{
				stt_xml_serialize_device_utc(pParasRegister);
			}
#endif
		}
		break;
		case DeviceException:
		{
			//实验中电流开路异常应及时上报
			pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister,
							 oSysState, &oSttCmd, SYS_STATE_RETTYPE_EXCEPTION);
#ifdef _PSX_QT_LINUX_
			if(pParasRegister != NULL)
			{
				stt_xml_serialize_device_status(pParasRegister, FALSE);
			}
#endif
		}
		break;

		case DevExceptClear:
		{
			//实验中电流开路异常应及时上报
			pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister,
							 oSysState, &oSttCmd, SYS_STATE_RETTYPE_EXCEPTION);
#ifdef _PSX_QT_LINUX_
			long nValue = 0;

			if(pParasRegister != NULL)
			{
				pParasRegister->xml_serialize("模块过热", STT_SYS_STATE_ID_OverHeat, "", "long", nValue);
				pParasRegister->xml_serialize("电流开路", STT_SYS_STATE_ID_IBreak, "", "long", nValue);
				pParasRegister->xml_serialize("电压短路", STT_SYS_STATE_ID_UShort, "", "long", nValue);
				pParasRegister->xml_serialize("辅助电压", STT_SYS_STATE_ID_Udc, "", "long", g_theSttDeviceStatus->m_nUdc);
			}
#endif
		}
		break;
		case TestRtDatas:
		{
			oSysState.SetRetType(SYS_STATE_RETTYPE_RTDATA);
			oSysState.UpdateSysStateHead(&oSttCmd);
			oSysState.GetSttParas();
			oSysState.Set_ExecStatus_Success();
			oSttXmlRegister.CreateXmlSerializeWrite(&oSysState);//只有id value
			pParasRegister = oSttXmlRegister.GetParas();

#ifdef _PSX_QT_LINUX_
			if(pParasRegister != NULL)
			{
				stt_xml_serialize_rtdatas(pParasRegister);				
			}
#endif
		}
		break;
		case IecRtDatas:
#ifdef _PSX_QT_LINUX_
        pParasRegister=stt_create_sys_state_paras_register(oSttXmlRegister,
							 oSysState, &oSttCmd, SYS_STATE_RETTYPE_RTDATA);

			if(pParasRegister != NULL)
			{
				BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->stt_xml_serialize_iec_rtdatas(pParasRegister);
				if(!bRet)
				{
					return;
				}
			}
#endif
			break;
		default:
			return;
	}
#endif

	char *pszPkgBuffer = NULL;
	long nLen = oSttXmlRegister.Stt_GetXml(&pszPkgBuffer, STT_PKG_HEAD_LEN);
	oSysState.m_nDataLen = nLen - STT_PKG_HEAD_LEN;
    oSysState.ProducePkgHead((BYTE*)pszPkgBuffer);
    SendBufferToChildren(NULL,(BYTE*)pszPkgBuffer,nLen);
	delete pszPkgBuffer;
}

long bNeedStop = 0;
long bException = 0;
void CSttTestServerBase::OnTimer()
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    if(g_bUpdateFPGA)
		return;

	BOOL bGetDevSta = FALSE;
	if (g_bNeedReadDeviceStatatus)
	{
		bGetDevSta = CSttDeviceBase::g_pSttDeviceBase->OnTimer();
	}

	if(g_theSttDeviceStatus != NULL)
	{
		if(bGetDevSta)
		{
			if(g_theSttDeviceStatus->m_bNeedStop)
			{
				bNeedStop = 1;
			}
			else
			{
				bNeedStop = 0;
			}
		}

		if(g_theSttDeviceStatus->is_exception())
		{
			bException = 1;
		}
		else
		{
			bException = 0;
		}
	}

	//2020-10-23  lijunqing
	//只有在不实时上报时间的时候，才能定时上报事件，在一定程度上避免重复上报
	if (!stt_test_event_set_is_lock())
	{
		if(g_nNeedReportEvents)
		{
			ReturnTestEvents();
		}
	}

	if(g_pFpgaUart != NULL)
	{
		g_pFpgaUart->SendUartData();
	}
#endif
#endif

}


long g_nRtDataLockCnt = 0;
void CSttTestServerBase::OnTimer_RtDataEvent()
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    if(g_bUpdateFPGA)
		return;

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	if(pCurrTest != NULL && pCurrTest->GetTestStarting())
	{
		if(g_bRtDataLock)
			return;
	}

	if(CSttDeviceBase::g_pSttDeviceBase->GetIecPktList())
	{
		ReturnSysStatesToChildren(IecRtDatas);
	}

	if (g_nNeedReportRTDATA && stt_get_rtdatas_count() > 0)
	{
		ReturnSysStatesToChildren(TestRtDatas);
	}

	g_nRtDataLockCnt++;
	if(g_nRtDataLockCnt*50 > 1000)
	{
		g_nRtDataLockCnt = 0;
		if(g_theSttDeviceStatus != NULL)
		{
			if(g_nNeedReportDevExcept)
			{
				if(bException)
				{
					ReturnSysStatesToChildren(DeviceException);
				}
				else
				{
					ReturnSysStatesToChildren(DevExceptClear);
				}
			}

			if(g_nNeedReportUTC)
			{
				ReturnSysStatesToChildren(DeviceUTC);
			}
		}
	}
#endif
#endif

}

void CSttTestServerBase::OnTimer_CheckHeartbeat()
{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    if(g_bUpdateFPGA)
		return;
#endif
#endif

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	//每秒定时任务
	if(pCurrTest !=NULL)
	{
		//2020-10-26  lijunqing  使用公共的接口来进行判断，不要使用具体的功能ID判断
		//这样通用性不好，后续如果出现一些功能不需要判断，例如模拟量录波，
		//就又要返回这里进行代码的修改
		// 		if((pCurrTest->m_strID != _T("SttReplayTest"))
		// 			&& (pCurrTest->m_strID != _T("SttRecord")))
		if(pCurrTest->NeedCheckHeartbeat())
		{
			//只检测具有单机测试权限的测试端心跳超时
			CheckHeartbeatOverTime();
		}

		BOOL bFinish=FALSE;
		pCurrTest->OnTimer(bFinish);

		if(bNeedStop)
		{
			Process_Cmd_Test_StopTest(FALSE);
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] Current MaxTemperature > 84,TestStop"));
		}
	}
	else
	{
		//只检测具有单机测试权限的测试端心跳超时
		CheckHeartbeatOverTime();
		if(bNeedStop)
		{
			Process_Cmd_Test_StopTest(FALSE);
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] Current MaxTemperature > 84,TestStop"));
		}
	}
}

void CSttTestServerBase::StopAutoTestEvent()
{
    CSttXcmdChInterface* pSocket=m_oSttTestCmd.GetRefSocketData();
    if(pSocket==NULL)
		return;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttSysState oSysState;
	oSysState.SetRetType(SYS_STATE_RETTYPE_STOP_AUTOTEST);
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSysState);
    Ret_SysState(oSysState,pSocket,oSttXmlSerializeTool);

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
    if(pCurrTest!=NULL)
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s %s Stop_AutoTest"),m_pServerSocket->m_strIPLocal.GetString(),pCurrTest->m_strID.GetString());
}

//只检测具有单机测试权限的测试端心跳超时
void CSttTestServerBase::CheckHeartbeatOverTime()
{
    CSttXcmdChInterface *pSocket;
	CString strIDSoft;
	QMap<unsigned long,long> oHeartTmOut;
    QList<CSttXcmdChInterface *> oSocketList;
	BOOL bStop = FALSE;

    if(!g_oUserMngrMutex.tryLock())//__FILE__,__FUNCTION__,__LINE__))
	{
		return;
	}

	POS pos = m_oClientUserMngr.GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{		
		pFind = (CSttTestClientUser *)m_oClientUserMngr.GetNext(pos);
		if (pFind == NULL)
		{
			continue;
		}

		pSocket = pFind->m_pRefSttSckt;
		if (pSocket == NULL)
		{
			continue;
		}

		strIDSoft = pFind->id_soft();

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
		if(strIDSoft == STT_SOFT_ID_DEBUG)
		{
            int nRet = pSocket->XSendHeartbeatCmd();
			if(nRet < 0)
			{				
				oSocketList.append(pSocket);
			}
		}
		else if(strIDSoft == STT_SOFT_ID_TEST)
		{
            int nRet = pSocket->XSendHeartbeatCmd();
			if(nRet < 0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("SendHeartbeatCmd, Retrun -1"));
				oSocketList.append(pSocket);
				if(pSocket == m_oSttTestCmd.GetRefSocketData())
				{
					bStop = TRUE;
				}
				continue;
			}

			if(pFind->HasAuthority(KEY_AUTHORITY_MODULE_Test) == FALSE)
			{
				//无测试权限不需判心跳
				continue;
			}

			if (g_nRecvHeartbeatTimeGap <= 0)
			{
				continue;
			}

			//根据配置条件选择是否检测心跳 2021-05-21 zhoulei
			if(!g_theSystemConfig->m_bCheckHeartOverTime)
			{
				continue;
			}

			//2021-8-20  lijunqing  use timer-count
            long nTimeGap = pSocket->XRecvHeartbeatCounterAdd();

			if (nTimeGap >= g_nRecvHeartbeatTimeGap)
			{//主动断链，断链后StopTest,CloseDevice
				if (CanSendLog())
				{
					oHeartTmOut.insert(pFind->GetIDTest(),nTimeGap);
				}
				oSocketList.append(pSocket);
				if(pSocket == m_oSttTestCmd.GetRefSocketData())
				{
					bStop = TRUE;
				}
			}
		}
#endif
#endif
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	if(pCurrTest != NULL && pCurrTest->GetTestStarting() && bStop)
	{
		pCurrTest->Stop();
	}

	CString strInfor;
	QMap<unsigned long,long>::const_iterator oiterator = oHeartTmOut.constBegin();

	while(oiterator != oHeartTmOut.constEnd())
	{
		strInfor.Format(_T("Heartbeat Timeout:%u[%d]"), oiterator.key(),oiterator.value());
		LogDebugInfor(strInfor);
		oiterator++;
	}

	for(int i = 0;i < oSocketList.count();i++)
	{
		pSocket = oSocketList.at(i);
        pSocket->CloseSttXcmdCh();
		Sleep(10);
	}
}

void CSttTestServerBase::ReturnTestStateEvent(long nEventType, PSTT_TIME pTime, bool bWithEvent)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&m_oSttTestCmd);
    CSttXcmdChInterface *pSocket = m_oSttTestCmd.GetRefSocketData();

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
    if (SttResult_Type_TestParaException == nEventType)
	{
        oSysState.m_strID=SYS_STATE_EXCEPTION;
		stt_test_event_set_lock(1);
        Ret_Test_SysState(oSysState, pSocket, FALSE, FALSE, TRUE,FALSE, SYS_STATE_RETTYPE_EVENT, pTime, bWithEvent);
		stt_test_event_set_lock(0);
		return;
	}

    if (SttResult_Type_TestFinish == nEventType)
	{
		stt_test_event_set_lock(1);
        if (!bWithEvent)
		{
			ReturnTestEvents();//缓存的Event需要单独上报时,必须在TestFinished前发送
		}
        oSysState.m_strID=SYS_STATE_EVENT_OnTestFinished;
        Ret_Test_SysState(oSysState, pSocket, FALSE, FALSE, TRUE,FALSE, SYS_STATE_RETTYPE_EVENT, pTime, bWithEvent);
		stt_test_event_set_lock(0);
        if(pCurrTest!=NULL)
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s %s TestFinished"),m_pServerSocket->m_strIPLocal.GetString(),pCurrTest->m_strID.GetString());
		return;
	}

    if (SttResult_Type_TestStart == nEventType)
	{
        oSysState.m_strID=SYS_STATE_EVENT_OnTestStarted;
		stt_test_event_set_lock(1);
        Ret_Test_SysState(oSysState, pSocket, FALSE, FALSE, TRUE,FALSE, SYS_STATE_RETTYPE_EVENT, pTime, bWithEvent);
		stt_test_event_set_lock(0);
        if(pCurrTest!=NULL)
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s %s TestStarted"),m_pServerSocket->m_strIPLocal.GetString(),pCurrTest->m_strID.GetString());
		return;
	}

    if (SttResult_Type_SearchPointReport == nEventType)
	{
		oSysState.m_strID = SYS_STATE_EVENT_OnSearchPointReport;
		stt_test_event_set_lock(1);
        Ret_Test_SysState(oSysState, pSocket, FALSE, FALSE, FALSE,TRUE, SYS_STATE_RETTYPE_EVENT, pTime, bWithEvent);
		stt_test_event_set_lock(0);
        if(pCurrTest!=NULL)
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s %s SearchPointReport"),m_pServerSocket->m_strIPLocal.GetString(),pCurrTest->m_strID.GetString());
		return;
	}

	//switch(pEvent->nType)
	{
		// 	case Result_Type_TestStart:
		// 		{
		// 			pXmlEvent->xml_serialize("Event","Event","","string", SYS_STATE_EVENT_OnTestStarted); //EventTime?
		// 			oSysState.SetEvent();
		// 			pParas->m_strID=pCurrTest->m_strID;
		// 			oSysState.m_strID=SYS_STATE_EVENT_OnTestStarted;
		// 		}
		// 		break;
		// 	case Result_Type_TestFinish:
		// 		{
		// 			oSysState.SetEvent();
		// 			pParas->m_strID=pCurrTest->m_strID;
		// 			oSysState.m_strID=SYS_STATE_EVENT_OnTestFinished;
		// 		}
		// 		break;
		// 	case Result_Type_UpdateParas:
		// 		{
		// 			oSysState.SetUpdate();
		// 		}
		// 		break;
	}
}

void CSttTestServerBase::ReturnTestEvents()
{
#ifndef _STT_NOT_IN_TEST_SERVER_
    if (stt_get_test_event_count() == 0)
    {//没有事件
		return;
	}
#endif

	//获取数据
	CSttXmlSerializeTool oSttXmlRegister;
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister = NULL;

	//2020-10-24 lijunqing 返回事件的时候，使用空的ID
    CSttTestCmd *pTempCmd = (CSttTestCmd*)m_oSttTestCmd.CloneEx();
	pTempCmd->m_strID = _T("");

	oSysState.SetRetType(SYS_STATE_RETTYPE_EVENT);
	oSysState.UpdateSysStateHead(pTempCmd);
	oSysState.GetSttParas();
	oSysState.Set_ExecStatus_Success();
	oSttXmlRegister.CreateXmlSerializeWrite(&oSysState);//只有id value
	pParasRegister = oSttXmlRegister.GetParas();

#ifndef _STT_NOT_IN_TEST_SERVER_	
	stt_xml_serialize_test_events(pParasRegister);
#endif

	//返回结果
	Ret_SysState(oSysState, NULL, oSttXmlRegister);
	delete pTempCmd;
}

long CSttTestServerBase::XSendSysState(CSttSysState *pSysState)
{
	if(pSysState == NULL)
	{
		return 0;
	}

	CSttTestClientUser *pFind = m_oClientUserMngr.FindByIDTest(pSysState->m_nIDTester);
	if((pFind == NULL)  || (pFind->m_pRefSttSckt == NULL))
	{
		return 0;
	}

    return pFind->m_pRefSttSckt->XSendSysState(pSysState);
}


void CSttTestServerBase::Ret_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	char *pszPkgBuffer = NULL;
	long nLen = oSttXmlSerializeTool.Stt_GetXml(&pszPkgBuffer, STT_PKG_HEAD_LEN);
	oSysState.m_nDataLen = nLen - STT_PKG_HEAD_LEN;
    oSysState.ProducePkgHead((BYTE*)pszPkgBuffer);
	//	pSttSocketDataBase->SendBuffer((BYTE*)pszPkgBuffer, nLen);

    SendBufferToChildren(NULL,(BYTE*)pszPkgBuffer,nLen);//20210902 返回底层的事件消息给所有连接的测试端

	delete pszPkgBuffer;
}

void CSttTestServerBase::Ret_Cmd_SysState(CSttCmdBase &oCmd, CSttXcmdChInterface *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oCmd);
	Ret_SysState(oSysState, pSttSocketDataBase, oSttXmlSerializeTool);
}


long CSttTestServerBase::Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	long nRet = 0;

    if (oAdjustCmd.m_strID == STT_CMD_TYPE_ADJUST_Adjust)
	{
        nRet = Process_Cmd_Adjust_Adjust(pClientSocket,oAdjustCmd,oSttXmlSerializeTool);
	}
    else if (oAdjustCmd.m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
        nRet = Process_Cmd_Ajust_ReadDeviceParameter(pClientSocket,oAdjustCmd, oSttXmlSerializeTool);
	}
    else if(oAdjustCmd.m_strID ==STT_CMD_TYPE_ADJUST_WriteFile)
    {//其他测试命令
        nRet = Process_Cmd_Ajust_WriteFile(pClientSocket,oAdjustCmd);
	}

	//2020-3-28 xxy
    if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->On_Process_Cmd_Adjust(pClientSocket, oAdjustCmd);
	}

	return nRet;
}

long CSttTestServerBase::Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	long nRet = 0;

    if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Login)
	{
        nRet = Process_Cmd_System_Login(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
	{
        nRet = Process_Cmd_System_Logout(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Request)
	{
        nRet = Process_Cmd_System_Request(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
	{
        nRet = Process_Cmd_System_Authority(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_SetSysConfig)
	{
        nRet = ProcessCmd_SetSysConfig(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_GetSysConfig)
	{
        nRet = ProcessCmd_GetSysConfig(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_LiveUpdate)
	{
        nRet = Process_Cmd_System_LiveUpdate(pClientSocket,oSysCmd);
	}
	else if(oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_ReadMeas)
	{
        nRet = Process_Cmd_System_ReadMeas(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_GetSystemState)
	{
        nRet =  Process_Cmd_System_GetSystemState(pClientSocket,oSysCmd,oSttXmlSerializeTool);
	}
	else
    {//其他测试命令

	}

	//2020-3-28 xxy
    if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->On_Process_Cmd_System(pClientSocket, oSysCmd);
	}

	return nRet;
}

//收到测试命令，先检查是否有权限，无权限则返回失败
BOOL CSttTestServerBase::CheckBeforeProcessCmdTest(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttSystemCmd oSysCmd;
	oSysCmd.m_strTestor = STT_SOFT_ID_TEST;
	oSysCmd.AddNewParasData(KEY_AUTHORITY_MODULE_Test, 1);
    if (GetNativeClientSocket() == pClientSocket)
    {//NativeClient命令
		oSysCmd.m_nIDTester = pClientSocket->GetIDTest();

        if (CanSendLog())
        {//2020-07-12 lijq
			CString strInfor;
			strInfor.Format(_T(">>> CheckBeforeProcessCmdTest[Native] : %u,%u"), oSysCmd.m_nIDTester, pClientSocket->GetIDTest());
			LogDebugInfor(strInfor);
		}
	}
	else
	{
		oSysCmd.m_nIDTester = stt_pkg_get_idtester(pBuf);

        if (CanSendLog())
        {//2020-07-12 lijq
			CString strInfor;
			strInfor.Format(_T(">>> CheckBeforeProcessCmdTest [not native]: %u,%u"), oSysCmd.m_nIDTester, pClientSocket->GetIDTest());
			LogDebugInfor(strInfor);
		}
	}

	CSttTestCmd oTestCmd;
	oTestCmd.ParsePkgHead(pBuf);

	CSttTestClientUser *pUser = NULL;
	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	pUser = m_pSttTestClientUserMngr->FindByIDTest(oSysCmd.m_nIDTester,oSysCmd.m_strTestor);
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(pUser == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] User no Login"));
		CSttSysState oSysState;

		oSysState.Free();
		oSysState.UpdateSysStateHead(&oTestCmd);
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_ACK);
        pClientSocket->XSendSysState(&oSysState);
		oSysState.Free();
		oSysState.UpdateSysStateHead(&oTestCmd);
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
        pClientSocket->XSendSysState(&oSysState);

		return FALSE;
	}

	BOOL bRet = TRUE;

	if(g_nCheckAuthority)
	{
		//判断是否具有Test权限（或可以申请Test权限）
		bRet = (AuthorityToUser(oSysCmd,TRUE,TRUE) != 0);

		if (!bRet)
		{
			CSttSysState oSysState;

			oSysState.Free();
			oSysState.UpdateSysStateHead(&oTestCmd);
			oSysState.Set_ExecStatus(STT_CMD_ExecStatus_ACK);
            pClientSocket->XSendSysState(&oSysState);
			oSysState.Free();
			oSysState.UpdateSysStateHead(&oTestCmd);
			oSysState.Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
            pClientSocket->XSendSysState(&oSysState);

			if (CanSendLog())
			{
				//2020-07-12 lijq
				// CString strInfor;
				// strInfor.Format(_T(">>> Process_Cmd_Test : %s,%u   has no [test] authority"), pszCmdID, pClientSocket->GetIDTest());
				// LogDebugInfor(strInfor);

				//2024.115 zhoulei
				oSysState.Free();
				oSysState.m_strRetType = SYS_STATE_RETTYPE_LOG;
				CSttMsgs *pMsgs = oSysState.GetSttMsgs();
				pMsgs->AddMsg(SYS_STATE_RETTYPE_LOG, _T("[error] 设备被占用，你没有测试权限，请不要多台电脑控制"));
                pClientSocket->XSendSysState(&oSysState);
			}
		}
	}

	return bRet;
}

void CSttTestServerBase::CheckStopTestAfterRelease(CSttXcmdChInterface *pClientSocket)
{
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("【TestServer:CheckStopTestAfterRelease】IDTest:%u"),pClientSocket->GetIDTest());

	if(m_oSttTestCmd.GetRefSocketData() == pClientSocket)
	{
		m_oSttTestCmd.SetRefSocketData(NULL);
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
		if(g_theSystemDefaultOutput.m_bUseSysOutput)
		{
            g_theSystemDefaultOutput.m_bUseSysOutput=FALSE;
			g_theSystemDefaultOutput.StopTest();
		}
#endif
#endif
		CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
		if (pCurrTest != NULL && pCurrTest->GetTestStarting())
		{
			pCurrTest->Stop();//手动实验老化模式断链不停输出
		}
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
		if(CSttDeviceBase::g_pSttDeviceBase != NULL)
		{
			CSttDeviceBase::g_pSttDeviceBase->CloseDevice();
		}
#endif
#endif
	}
}

long CSttTestServerBase::ReturnSysState(long nCmdExecStatus,CSttCmdData *pRetData)
{
	//2020-10-20  lijunqing
	return CSttTestEngineBase::ReturnSysState(&m_oSttTestCmd, nCmdExecStatus, pRetData);

	/*
	//xxy测试命令应答
    CSttXcmdChInterface *pSocket = m_oSttTestCmd.GetRefSocketData();
	if (pSocket == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttTestCmd.m_pRefSocketDataBase == NULL"));
		return 0;
	}

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&m_oSttTestCmd);
	if (pRetData != NULL)
	{//返回结果数据
		oSysState.AppendEx(*pRetData);
		pRetData->RemoveAll();
	}
	oSysState.Set_ExecStatus(nCmdExecStatus);

    return pSocket->XSendSysState(&oSysState);
*/
}

long CSttTestServerBase::Process_Cmd_Test(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    if(!CheckBeforeProcessCmdTest(pClientSocket,pBuf,nLen,pszCmdID,pszTestor))
	{
		return 0;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	m_oSttTestCmd.SetRefSocketData(pClientSocket);
	char *pszPkgXml = m_oSttTestCmd.ParsePkgOnly(pBuf);
    CSttTestCmd *pSttTestCmd=new CSttTestCmd;
	oSttXmlSerializeTool.CreateXmlSerializeRead(pSttTestCmd, pszPkgXml, nLen - STT_PKG_HEAD_LEN);
    m_oSttTestCmd.m_strID=pSttTestCmd->m_strID;
	delete pSttTestCmd;
    pSttTestCmd=NULL;

    if (CanSendLog())
    {//2020-07-12 lijq
		CString strInfor;
		strInfor.Format(_T(">>> Process_Cmd_Test : %s"), pszCmdID);
		LogDebugInfor(strInfor);
	}

	long nRet = 0;
    if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_SetParameter) == 0)
	{
		nRet =  Process_Cmd_Test_SetParameter(oSttXmlSerializeTool);
	}
	else if(strcmp(pszCmdID, STT_CMD_TYPE_TEST_UpdateParameter) == 0)
	{
		nRet =  Process_Cmd_Test_UpdateParameter(oSttXmlSerializeTool);
	}
    else if (strcmp(pszCmdID, STT_CMD_TYPE_TEST_StartTest) == 0)
	{
		nRet =  Process_Cmd_Test_StartTest(oSttXmlSerializeTool);
	}
    else if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_StopTest) == 0)
	{
		nRet =  Process_Cmd_Test_StopTest();
	}
    else if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_GetReport) == 0)
	{
		nRet =  Process_Cmd_Test_GetReport();
	}
    else if (strcmp(pszCmdID ,STT_CMD_TYPE_TEST_CloseDevice) == 0)
	{
		nRet =  Process_Cmd_Test_CloseDevice();
	}

    if (CanSendLog())
    {//2020-07-12 lijq
		LogDebugInfor(_T("Process_Cmd_Test >>>>"));
	}

	return nRet;
}

long CSttTestServerBase::Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttAdjustCmd oAdjustCmd;
	CSttXmlSerializeTool oSttXmlSerializeTool;
	char *pszPkgXml = oAdjustCmd.ParsePkgOnly(pBuf);
	oSttXmlSerializeTool.CreateXmlSerializeRead(&oAdjustCmd, pszPkgXml, nLen - STT_PKG_HEAD_LEN);
    return Process_Cmd_Adjust(pClientSocket,oAdjustCmd,oSttXmlSerializeTool);
}

long CSttTestServerBase::Process_Cmd_System(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttSystemCmd oSysCmd;
	CSttXmlSerializeTool oSttXmlSerializeTool;
	//  oSysCmd.SetRefSocketData(pClientSocket);
	char *pszPkgXml = oSysCmd.ParsePkgOnly(pBuf);
	oSysCmd.SetRefSocketData(pClientSocket);
	oSttXmlSerializeTool.CreateXmlSerializeRead(&oSysCmd, pszPkgXml, nLen - STT_PKG_HEAD_LEN);
    return Process_Cmd_System(pClientSocket,oSysCmd,oSttXmlSerializeTool);
}

long CSttTestServerBase::Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//TestSever debug命令处理
    if(strcmp(pszCmdID,STT_CMD_TYPE_DEBUG_GetSocketConnect) == 0)
	{
		m_pSocketDataBase = GetNativeClientSocket();
		if((m_pSocketDataBase != NULL) && (pClientSocket != m_pSocketDataBase))
        {//本地Debug端，转发给NativeClient
            return m_pSocketDataBase->XSendBuffer(pBuf,nLen);
		}
	}

    return CSttTestEngineBase::Process_Cmd_Debug(pClientSocket, pBuf,nLen,pszCmdID,pszTestor);
}

long CSttTestServerBase::Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{//TestServer 收到Debug应答
	if(oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetSocketConnect)
    {//merge own userlist and oSysState(Native userlist)
		return ReturnGetSocketConnect(oSysState);
	}

	return 0;
}

long CSttTestServerBase::Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//TODO：处理调试命令
	long bRet = 0;

	CString strDebugCmd = oDebugCmd.m_strID; //获取Debug命令类型

	if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetProcessState)
	{
        bRet = Process_Debug_GetProcessState(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetMemState)
	{
        bRet = Process_Debug_GetMemState(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetTestParas)
	{
        bRet = Process_Debug_GetTestParas(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetTestReports)
	{
        bRet = Process_Debug_GetTestReports(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetBasicTestParas)
	{
        bRet = Process_Debug_GetBasicTestParas(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetBasicReportData)
	{
        bRet = Process_Debug_GetBasicReportData(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetDrvTestData)
	{
        bRet = Process_Debug_GetDrvTestData(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetDrvReportData)
	{
        bRet = Process_Debug_GetDrvReportData(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetFpgaData)
	{
        bRet = Process_Debug_GetFpgaData(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetSocketConnect)
    {//远程Debug端透传过来的命令
        bRet = Process_Debug_GetSocketConnect(pClientSocket,oDebugCmd);
	}
	else if(strDebugCmd == STT_CMD_TYPE_DEBUG_ConfigDebug)
	{
        bRet = Process_Debug_ConfigDebug(pClientSocket,oDebugCmd);
	}
	else
	{
	}

	CSttTestEngineBase::ReturnSysState(&oDebugCmd, STT_CMD_ExecStatus_SUCCESS, NULL);

	return bRet;
}

void CSttTestServerBase::InitSttServerEngine(const char *pszIP, int nTestPort,int nReplayPort)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
	stt_test_new_drvparas_buff();
	stt_test_new_drvresult_buff();
	stt_create_test_event_cycle_array();
	stt_create_rtdatas_cycle_array();
#endif

    m_pServerSocket=new CSttTestServerSocket;
    m_pServerSocket->m_nMaxClientCount=5;
    m_pServerSocket->CreateServer(pszIP,nTestPort);
	m_pServerSocket->AttachCmdOverTimeMsgRcv(this);
	m_pServerSocket->SetTestEngine(this);

	if(nReplayPort > 0)
	{
        m_pReplaySocket=new CSttTestServerSocket;
		m_pReplaySocket->m_nMaxClientCount = 5;
        m_pReplaySocket->CreateServer(pszIP,nReplayPort);
		m_pReplaySocket->SetTestEngine(this);
	}

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
	g_oTheOwnIotDevice.SetSN(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strSN);
	g_oTheOwnIotDevice.SetModel(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDeviceName);
#endif
	// m_oMqttEngine.ConnectMqttSvr("192.168.2.160",1883,"","");
#endif
}

//2020-4-6  lijq
//如果没有这部分，Server的Accept线程无法退出
void CSttTestServerBase::ExitSttServerEngine()
{
    if (m_pServerSocket != NULL)
	{
		m_pServerSocket->CloseSttServer();
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}

    if (m_pReplaySocket != NULL)
	{
#ifndef _STT_NOT_IN_TEST_SERVER_
		g_oSttComtradeRcvSocket.Close();
#endif
		m_pReplaySocket->CloseSttServer();
		delete m_pReplaySocket;
		m_pReplaySocket = NULL;
	}

	if(g_pReplayTestSocket != NULL)
	{
        g_pReplayTestSocket->CloseSttXcmdCh();
	}

#ifndef _STT_NOT_IN_TEST_SERVER_
	stt_test_free_drvparas_buff();
	stt_test_free_drvresult_buff();
	stt_free_rtdatas_cycle_array();
	stt_free_test_event_cycle_array();
#endif	
}

CSttTestClientUser *CSttTestServerBase::GetNativeClientUser()
{
	POS pos = m_oClientUserMngr.GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CSttTestClientUser *)m_oClientUserMngr.GetNext(pos);

        if (pFind->IsTerminalType_Native())
		{
			return pFind;
		}
	}

	m_pSocketDataBase = NULL;
	return NULL;
}

CSttXcmdChInterface *CSttTestServerBase::GetNativeClientSocket()
{
	if(m_pSocketDataBase != NULL)
	{
		return m_pSocketDataBase;
	}

	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);

	POS pos = m_oClientUserMngr.GetHeadPosition();
	CSttTestClientUser *pFind = NULL;

	while(pos != NULL)
	{		
		pFind = (CSttTestClientUser *)m_oClientUserMngr.GetNext(pos);

		if (pFind != NULL && pFind->IsTerminalType_Native())
		{
			m_pSocketDataBase = pFind->m_pRefSttSckt;
			g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
			return m_pSocketDataBase;
		}		
	}

	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	return NULL;
}

///////////////////////////////
long CSttTestServerBase::Process_Cmd_Test_SetParameter(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = oSttXmlSerializeTool.GetMacroID(CSttCmdDefineXmlRWKeys::CSttTestCmdKey());

#ifndef _STT_NOT_IN_TEST_SERVER_
    g_nTmtParaMode = 1;

#ifdef _SttTestServer_For_Debug_//20220905 zhouhj 调试模式下,兼容系统参数下发
    if (strMacroID == STT_MACRO_ID_SystemConfig)
	{
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		return 0;
	}
#endif

#ifdef _PSX_QT_LINUX_

	if(strMacroID == g_theSystemConfig->m_strMacroID)
	{
		CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

		if(pCurrTest != NULL)
		{
			pCurrTest->Stop();//修改系统参数需要停止输出
		}

		g_theSystemConfig->Para_XmlSerialize(pMacroParas);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		return 0;
	}

	/***
	if(strMacroID == STT_MACRO_ID_AuxDCOutput)
	{
		//20220217 zhoulei开放单机软件实验运行过程中辅助直流修改
		CSttTestBase *pTest = stt_CreateTestMacroByMacroID(strMacroID);
		pTest->Para_XmlSerialize(pMacroParas);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		delete pTest;
		return 0;
	}

    if (strMacroID == STT_MACRO_ID_IecDetect)
	{
		CSttTestBase *pTest = stt_CreateTestMacroByMacroID(strMacroID);
		pTest->Para_XmlSerialize(pMacroParas);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		delete pTest;
		return 0;
	}

    if (strMacroID == STT_MACRO_ID_IecRecord)
	{
		CSttTestBase *pTest = stt_CreateTestMacroByMacroID(strMacroID);
		pTest->Para_XmlSerialize(pMacroParas);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		delete pTest;
		return 0;
	}
	****/

	if(g_pSttTestFactory->FindMacroID_NoChgCurrTest(strMacroID))
	{
		CSttTestBase *pTest = stt_CreateTestMacroByMacroID(strMacroID);

		if(pTest == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
			ReturnSysState(STT_CMD_ExecStatus_FAILURE);
		}
		else
		{
			pTest->Para_XmlSerialize(pMacroParas);
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
			delete pTest;
		}

		return 0;
	}

#endif
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	CSttTestBase *pNewTest = NULL;
    if (pCurrTest == NULL)
	{
		pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
		//ASSERT (pNewTest != NULL);
		if(pNewTest == NULL)
		{
#ifdef _SttTestServer_For_Debug_
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
#else
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
			ReturnSysState(STT_CMD_ExecStatus_FAILURE);
#endif
			return 0;
		}

		pNewTest->Init();
		pNewTest->Para_XmlSerialize(pMacroParas);
		CSttServerTestCtrlCntr::SetParameter(pNewTest);
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		//20231020  zhoulei  以注册类里面的strMacroID为唯一判断依据
		if(pCurrTest->m_strID == strMacroID)
		{
			pCurrTest->Init();
			pCurrTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::SetParameter();
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
		else
		{
			pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
			//ASSERT (pNewTest != NULL);
			if(pNewTest == NULL)
			{
#ifdef _SttTestServer_For_Debug_
				ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
#else
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
				ReturnSysState(STT_CMD_ExecStatus_FAILURE);
#endif
				return 0;
			}

			pNewTest->Init();
			pNewTest->Para_XmlSerialize(pMacroParas);
			CSttServerTestCtrlCntr::SetParameter(pNewTest);
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		}
	}
	//CSttServerTestCtrlCntr::UpdateParameter如果同步模式，直接调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	//如果CSttServerTestCtrlCntr::UpdateParameter异步过程，则需在收到CSttServerTestCtrlCntr::UpdateParameter消息的地方调用
	//如果成功则调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS)
	//否则调用ReturnSysState(STT_CMD_ExecStatus_Failure)

#endif
	return 0;
}

long CSttTestServerBase::Process_Cmd_Test_UpdateParameter(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = oSttXmlSerializeTool.GetMacroID(CSttCmdDefineXmlRWKeys::CSttTestCmdKey());

#ifndef _STT_NOT_IN_TEST_SERVER_
    g_nTmtParaMode = 1;
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

	if(pCurrTest != NULL)
	{
		//20231020  zhoulei  以注册类里面的strMacroID为唯一判断依据
		if(pCurrTest->m_strID == strMacroID)
		{
			pCurrTest->UpdatePara_XmlSerialize(pMacroParas);
			if(pCurrTest->TestPara_CheckOK())
			{
				CSttServerTestCtrlCntr::UpdateParameter();
			}
			else
				ReturnTestParaCheckFail();
		}
	}

	//CSttServerTestCtrlCntr::UpdateParameter如果同步模式，直接调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	//如果CSttServerTestCtrlCntr::UpdateParameter异步过程，则需在收到CSttServerTestCtrlCntr::UpdateParameter消息的地方调用
	//如果成功则调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS)
	//否则调用ReturnSysState(STT_CMD_ExecStatus_Failure)
#endif
	ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	return 0;
}

long CSttTestServerBase::Process_Cmd_Test_StartTest(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	ReturnSysState(STT_CMD_ExecStatus_ACK);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = oSttXmlSerializeTool.GetMacroID(CSttCmdDefineXmlRWKeys::CSttTestCmdKey());

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    g_nTmtParaMode = 1;
	long nIndex = strMacroID.indexOf('$');
	if(nIndex > -1)
        strMacroID = strMacroID.split('$')[1];//20221009 zhoulei支持自动测试多型号设备调用同一种功能

	if(strMacroID == g_theSystemDefaultOutput.m_strMacroID)
	{
		if(pMacroParas == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
		}
		else
		{
			g_theSystemDefaultOutput.Para_XmlSerialize(pMacroParas);
		}

		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		return 0;
	}

	if(strMacroID == g_theAppRatesConfig.m_strMacroID)
	{
		if(pMacroParas == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
		}
		else
		{
			g_theAppRatesConfig.Para_XmlSerialize(pMacroParas);
		}

		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);

		//获取数据
		CSttXmlSerializeTool oSttXmlRegister;
		CSttSysState oSysState;
		CSttXmlSerializeBase *pParasRegister = NULL;
        CSttTestCmd *pTempCmd = (CSttTestCmd*)m_oSttTestCmd.CloneEx();
		pTempCmd->m_strID = SYS_STATE_EVENT_OnTestFinished;
		pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, pTempCmd, SYS_STATE_RETTYPE_EVENT);

		//返回结果
		Ret_SysState(oSysState, m_oSttTestCmd.GetRefSocketData(), oSttXmlRegister);
		delete pTempCmd;
		return 0;
	}

    if (strMacroID == g_theSystemConfig->m_strMacroID
			|| strMacroID == "SttSystemConfig")//20220311 zhoulei PTU200L
	{
		CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

		if(pCurrTest != NULL)
		{
			pCurrTest->Stop();//修改系统参数需要停止输出
		}

		if(pMacroParas == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
		}
		else
		{
			g_theSystemConfig->Para_XmlSerialize(pMacroParas);
		}

		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);

		//获取数据
		CSttXmlSerializeTool oSttXmlRegister;
		CSttSysState oSysState;
		CSttXmlSerializeBase *pParasRegister = NULL;
        CSttTestCmd *pTempCmd = (CSttTestCmd*)m_oSttTestCmd.CloneEx();
		pTempCmd->m_strID = SYS_STATE_EVENT_OnTestStarted;
		CSttMacro* pSttMacro= oSysState.GetSttMacro();
		pSttMacro->m_strID = strMacroID;
		pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, pTempCmd, SYS_STATE_RETTYPE_EVENT);		
		Ret_SysState(oSysState, m_oSttTestCmd.GetRefSocketData(), oSttXmlRegister);
		Sleep(50);		
		oSysState.Free();
		((CExBaseList*)&oSttXmlRegister)->DeleteChildren();
		pTempCmd->m_strID = SYS_STATE_EVENT_OnTestFinished;
		pSttMacro= oSysState.GetSttMacro();
		pSttMacro->m_strID = strMacroID;
		pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, pTempCmd, SYS_STATE_RETTYPE_EVENT);
        stt_xml_serialize(g_theSystemConfig,pParasRegister);		
		Ret_SysState(oSysState, m_oSttTestCmd.GetRefSocketData(), oSttXmlRegister);
		delete pTempCmd;
		return 0;
	}
#endif

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	CSttTestBase *pNewTest = NULL;

    if (pCurrTest == NULL)
	{
		pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
		//ASSERT (pNewTest != NULL);
		if(pNewTest == NULL)
		{
#ifdef _SttTestServer_For_Debug_
			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
#else
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
			ReturnSysState(STT_CMD_ExecStatus_FAILURE);
#endif	
			return 0;
		}

		pNewTest->Init();
		if(pMacroParas == NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
		}
		else
		{
			pNewTest->Para_XmlSerialize(pMacroParas);
		}

		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
		CSttServerTestCtrlCntr::Test(pNewTest);		
		if(!pNewTest->TestPara_CheckOK())
		{
			//实验参数异常,直接返回TestFinish
			ReturnTestParaCheckFail();
			STT_TIME pTime;
            pTime.dRealTime=0;
            pTime.dTime=0;
            pTime.dBinActTime=-1;
            ReturnTestStateEvent(SttResult_Type_TestFinish,&pTime,FALSE);
		}
	}
	else
	{
		//20231020  zhoulei  以注册类里面的strMacroID为唯一判断依据
		if(pCurrTest->m_strID == strMacroID)
		{
			pCurrTest->Init();
			if(pMacroParas == NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
			}
			else
			{
				pCurrTest->Para_XmlSerialize(pMacroParas);
			}

			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
			CSttServerTestCtrlCntr::Test();			
			if(!pCurrTest->TestPara_CheckOK())
			{
				//实验参数异常,直接返回TestFinish
				ReturnTestParaCheckFail();
				STT_TIME pTime;
                pTime.dRealTime=0;
                pTime.dTime=0;
                pTime.dBinActTime=-1;
                ReturnTestStateEvent(SttResult_Type_TestFinish,&pTime,FALSE);
			}
		}
		else
		{
			pNewTest = stt_CreateTestMacroByMacroID(strMacroID);
			//ASSERT (pNewTest != NULL);
			if(pNewTest == NULL)
			{
#ifdef _SttTestServer_For_Debug_
				ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
#else
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] CreateTestMacroByMacroID Fail %s"), strMacroID.GetString());
				ReturnSysState(STT_CMD_ExecStatus_FAILURE);
#endif	
				return 0;
			}

#ifdef _PSX_QT_LINUX_
			pCurrTest->Stop();
#endif
			pNewTest->Init();
			if(pMacroParas == NULL)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] pMacroParas == NULL"));
			}
			else
			{
				pNewTest->Para_XmlSerialize(pMacroParas);
			}

			ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
			CSttServerTestCtrlCntr::Test(pNewTest);			
			if(!pNewTest->TestPara_CheckOK())
			{
				//实验参数异常,直接返回TestFinish
				ReturnTestParaCheckFail();
				STT_TIME pTime;
                pTime.dRealTime=0;
                pTime.dTime=0;
                pTime.dBinActTime=-1;
                ReturnTestStateEvent(SttResult_Type_TestFinish,&pTime,FALSE);
			}
		}
	}

#endif

	//CSttServerTestCtrlCntr::Test如果同步模式，直接调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	//如果CSttServerTestCtrlCntr::Test异步过程，则需在收到CSttServerTestCtrlCntr::Test消息的地方调用
	//如果成功则调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS)
	//否则调用ReturnSysState(STT_CMD_ExecStatus_Failure)
	return 0;
}

void CSttTestServerBase::ReturnTestParaCheckFail()
{
	STT_TIME pTime;
    pTime.dRealTime=0;
    pTime.dTime=0;
    pTime.dBinActTime=-1;
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    if(g_theSttDeviceStatus!=NULL)
        pTime.dTime=g_theSttDeviceStatus->m_nUser_s;
#endif
#endif
    ReturnTestStateEvent(SttResult_Type_TestParaException,&pTime,TRUE);

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
#endif
}

long CSttTestServerBase::Process_Cmd_Test_StopTest(BOOL bReturnAsk)
{
	if(bReturnAsk)
		ReturnSysState(STT_CMD_ExecStatus_ACK);


	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
    if (pCurrTest != NULL)
	{
		pCurrTest->Stop();
	}
	else
	{
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
#endif
	}	

	if(bReturnAsk)
		ReturnSysState(STT_CMD_ExecStatus_SUCCESS);

	CSttSysState oEventSysState;
	oEventSysState.UpdateSysStateHead(&m_oSttTestCmd);
	oEventSysState.SetEvent();
    oEventSysState.m_strID=SYS_STATE_EVENT_OnTestStoped;
	CSttParas *pParas = oEventSysState.GetSttParas();
    pParas->m_strID=m_oSttTestCmd.m_strID;
    CSttXcmdChInterface *pSocket = m_oSttTestCmd.GetRefSocketData();
    if (pSocket == NULL)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttTestCmd.m_pRefSocketDataBase == NULL"));
		return 0;
	}

    pSocket->XSendSysState(&oEventSysState);
	//CSttServerTestCtrlCntr::Stop如果同步模式，直接调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
	//如果CSttServerTestCtrlCntr::Stop异步过程，则需在收到CSttServerTestCtrlCntr::Stop消息的地方调用
	//如果成功则调用ReturnSysState(STT_CMD_ExecStatus_SUCCESS)
	//否则调用ReturnSysState(STT_CMD_ExecStatus_Failure)

	return 0;
}

void CSttTestServerBase::Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
		, BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
		, PSTT_TIME pTime, bool bWithEvent)
{
	CSttXmlSerializeTool oSttXmlSerializeTool;

	oSysState.Set_ExecStatus_Success();
    CSttMacro* pSttMacro= oSysState.GetSttMacro(bParas, bReport,bSearchResult);
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	if(pCurrTest != NULL)
		pSttMacro->m_strID = pCurrTest->m_strID;
    CSttParas *pParas = oSysState.GetSttParas();

	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSysState);
	CSttXmlSerializeBase *pXmlMacroParas = NULL;
	CSttXmlSerializeBase *pXmlReport = NULL;
	CSttXmlSerializeBase *pXmlSearchReport = NULL;

	CSttXmlSerializeBase *pXmlParas = oSttXmlSerializeTool.GetParas();

#ifndef _STT_NOT_IN_TEST_SERVER_
	stt_xml_serialize_test_events_time(pXmlParas, pTime);
#endif

    if (bBasic || bParas)
	{
		pXmlMacroParas = oSttXmlSerializeTool.GetMacroParas();
	}

    if (bReport)
	{
		pXmlReport = oSttXmlSerializeTool.GetMacroResults();
	}

    ASSERT (pCurrTest != NULL);

    if (pCurrTest != NULL)
	{
        pParas->m_strID=pCurrTest->m_strID;

        if (bBasic)
		{
            if (bParas)
			{
                ASSERT (pXmlMacroParas != NULL);
				pCurrTest->Para_XmlSerialize_Basic(pXmlMacroParas);
			}

            if (bReport)
			{
                ASSERT (pXmlReport != NULL);
				pCurrTest->Report_XmlSerialize_Basic(pXmlReport);
			}
		}
		else
		{
            if (bParas)
			{
                ASSERT (pXmlMacroParas != NULL);
				pCurrTest->Para_XmlSerialize(pXmlMacroParas);
			}

            if (bReport)
			{
                ASSERT (pXmlReport != NULL);
				pCurrTest->Report_XmlSerialize(pXmlReport);
			}
		}

        if (bSearchResult)//zhouhj 20210925  增加搜索测试点的上送消息处理
		{
			pXmlSearchReport = oSttXmlSerializeTool.GetMacroSearchResults();
            ASSERT (pXmlSearchReport != NULL);
			pCurrTest->SearchReport_XmlSerialize(pXmlSearchReport);
		}
	}
#ifndef _STT_NOT_IN_TEST_SERVER_
    if (bWithEvent)
	{		
		stt_xml_serialize_test_events(pXmlParas);
	}
#endif

	Ret_SysState(oSysState, pSttSocketDataBase, oSttXmlSerializeTool);
}

//2020-10-22  lijunqing
void CSttTestServerBase::Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
		, BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
		, char *strRetType, PSTT_TIME pTime, bool bWithEvent)
{
	oSysState.SetRetType(strRetType);
    Ret_Test_SysState(oSysState, pSttSocketDataBase, bBasic, bParas, bReport,bSearchResult, pTime, bWithEvent);
}

void CSttTestServerBase::Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
		, BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
		, const CString &strRetType, PSTT_TIME pTime, bool bWithEvent)
{
	oSysState.SetRetType(strRetType);
    Ret_Test_SysState(oSysState, pSttSocketDataBase, bBasic, bParas, bReport,bSearchResult, pTime, bWithEvent);
}

long CSttTestServerBase::Process_Cmd_Test_GetReport(BOOL bParas)
{
	stt_test_event_set_lock(1);
	ReturnTestEvents();//缓存的Event需要单独上报时
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&m_oSttTestCmd);
	Ret_Test_SysState(oSysState, m_oSttTestCmd.GetRefSocketData()
                      , FALSE, bParas, TRUE,FALSE, SYS_STATE_RETTYPE_REPORT, NULL, FALSE);
	stt_test_event_set_lock(0);

	return 0;
}

long CSttTestServerBase::Process_Cmd_Test_CloseDevice()
{
    CSttXcmdChInterface *pClientSocket = m_oSttTestCmd.GetRefSocketData();
	DWORD nID_Test = 0;
	if (pClientSocket != NULL)
	{
		nID_Test = pClientSocket->GetIDTest();
	}

	g_oUserMngrMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	CSttTestClientUser *pUser = m_oClientUserMngr.FindByIDTest(nID_Test,STT_SOFT_ID_TEST);

	if(pUser != NULL && pUser->HasAuthority(KEY_AUTHORITY_MODULE_Test))
	{
		pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test, 0);
	}
	g_oUserMngrMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
	if(g_theSystemDefaultOutput.m_bUseSysOutput)
	{
		g_theSystemDefaultOutput.m_bUseSysOutput=FALSE;
		g_theSystemDefaultOutput.StopTest();
	}
#endif
#endif

	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
	if (pCurrTest != NULL && pCurrTest->GetTestStarting())
	{
		pCurrTest->Stop();//手动实验老化模式断链不停输出
	}

	ReturnSysState(STT_CMD_ExecStatus_ACK);
	ReturnSysState(STT_CMD_ExecStatus_SUCCESS);

	return 0;
}

long CSttTestServerBase::Process_Heartbeat(CSttXcmdChInterface *pClientSocket, unsigned char *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	return 0;
}

long CSttTestServerBase::Process_Trigger(CSttXcmdChInterface *pClientSocket
		, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//手动触发命令
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T("收到手动触发命令"));
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();
    if (pCurrTest != NULL)
	{
		pCurrTest->Triger();
	}
	return 0;
}

long CSttTestServerBase::Process_Comtrade_SendDataFinish(CSttXcmdChInterface *pClientSocket
		, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//Comtrade数据发送完成命令
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T("收到Comtrade数据块发送完成命令"));
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

    int *pTemp = (int *)(&pBuf[STT_PKG_HEAD_LEN+1]);
	int nSendIndex = pTemp[0];
	int nSendNum = pTemp[1];

    if (pCurrTest != NULL)
	{
        pCurrTest->OnSendDataFinish(nSendIndex,nSendNum);
	}
	return 0;
}

long CSttTestServerBase::Process_Comtrade_SendDataStart(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T("收到Comtrade数据块开始发送命令"));
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

    int *pTemp = (int *)(&pBuf[STT_PKG_HEAD_LEN+1]);
	int nSendIndex = pTemp[0];
	int nSendNum = pTemp[1];

    if (pCurrTest != NULL)
	{
        pCurrTest->OnSendDataStart(nSendIndex,nSendNum);
	}

	return 1;
}

void CSttTestServerBase::OnAfterMoveToComtradeBuf(int nIndex,int nDataLen)
{
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnAfterMoveToComtradeBuf:nIndex[%d],nDataLen[%d]"),nIndex,nDataLen);
	CSttTestBase *pCurrTest = CSttServerTestCtrlCntr::GetCurrTest();

    if (pCurrTest != NULL)
	{
        pCurrTest->OnAfterMoveToComtradeBuf(nIndex,nDataLen);
	}
}

//Debug命令执行
long CSttTestServerBase::Process_Debug_GetProcessState(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	// 	if(pClientSocket!=NULL)
	// 	{
	// 		CSttSysState oSystateCmd;
	// 		oSystateCmd.m_nRetSttCmd = STT_CMD_TYPE_DEBUG;
	// 		oSystateCmd.m_strID = STT_CMD_TYPE_DEBUG_GetProcessState;
	//
	// 		CDvmData *pObj1 = oSystateCmd.AddNewParasData(_T("CDvmData1"), _T("1"));
	// 		pObj1->m_strName = _T("process1");
	// 		CString strMem1 = _T("0.1");
	// 		pObj1->AddValue(_T("mem"),strMem1);
	// 		CString strCpu1 = _T("0.2");
	// 		pObj1->AddValue(_T("cpu"),strCpu1);
	//
	// 		CDvmData *pObj2 = oSystateCmd.AddNewParasData(_T("CDvmData2"), _T("2"));
	// 		pObj2->m_strName = _T("process2");
	// 		CString strMem2 = _T("0.11");
	// 		pObj2->AddValue(_T("mem"),strMem2);
	// 		CString strCpu2 = _T("0.22");
	// 		pObj2->AddValue(_T("cpu"),strCpu2);
	//
    // 		pClientSocket->XSendSysState(&oSystateCmd); //test
	// 	}

	return 0;
}

long CSttTestServerBase::Process_Debug_GetMemState(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	// 	if(pClientSocket!=NULL)
	// 	{
	// 		CSttSysState oSystateCmd;
	// 		oSystateCmd.m_nRetSttCmd = STT_CMD_TYPE_DEBUG;
	// 		oSystateCmd.m_strID = STT_CMD_TYPE_DEBUG_GetMemState;
	//
	// 		oSystateCmd.AddNewParasData(_T("mem"), _T("500"));
	//
    // 		pClientSocket->XSendSysState(&oSystateCmd); //test
	// 	}

	return 0;
}

long CSttTestServerBase::Process_Debug_GetTestParas(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//2020-4-6  lijq
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

    Ret_Test_SysState(oSysState, pClientSocket, FALSE, TRUE, FALSE,FALSE, SYS_STATE_RETTYPE_REPORT, NULL, FALSE);

	return 0;
}

long CSttTestServerBase::Process_Debug_GetTestReports(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//2020-4-6  lijq
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

    Ret_Test_SysState(oSysState, pClientSocket, FALSE, TRUE, TRUE,FALSE, SYS_STATE_RETTYPE_REPORT, NULL, FALSE);

	return 0;
}

long CSttTestServerBase::Process_Debug_GetBasicTestParas(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//2020-4-6  lijq
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

    Ret_Test_SysState(oSysState, pClientSocket, TRUE, TRUE, FALSE,FALSE, SYS_STATE_RETTYPE_REPORT, NULL, FALSE);

	return 0;
}

long CSttTestServerBase::Process_Debug_GetBasicReportData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//2020-4-6  lijq
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

    Ret_Test_SysState(oSysState, pClientSocket, TRUE, TRUE, TRUE,FALSE, SYS_STATE_RETTYPE_REPORT, NULL, FALSE);

	return 0;
}

long CSttTestServerBase::Process_Debug_GetDrvTestData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	// 	if(pClientSocket!=NULL)
	// 	{
	// 		CSttSysState oSystateCmd;
	// 		oSystateCmd.m_nRetSttCmd = STT_CMD_TYPE_DEBUG;
	// 		oSystateCmd.m_strID = STT_CMD_TYPE_DEBUG_GetTestParas;
	//
	// 		BYTE pPkgBuffer[] = {0xEB,0x90,0xEB,0x90,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0xd0,0x07,0x00};
	// 		BYTE pXml[] =
	// 				"<sys-state name=\"NAME\" id=\"GetDrvTestData\" mater-host=\"HOST\" testor=\"\" id-cmd=\"0x3\" ret-type=\"\">\
	// 					<macro type=\"\" id=\"\" state=\"\">\
	// 						<results name=\"\" id=\"\">	\
	// 							<data id=\"\" value=\"\" />\
	// 						</results >\
	// 						<paras name=\"\" id=\"\">	\
	// 							<data id=\"\" value=\"\" />\
	// 						</paras>\
	// 					</macro>\
	// 					<paras name=\"\" id=\"\">	\
	// 						<data id=\"\" value=\"GetDrvTestData-Test\" />\
	// 					</paras>\
	// 				</sys-state>";
	// 		BYTE *pSend = (BYTE*)malloc(STT_PKG_HEAD_LEN + sizeof(pXml));
	// 		memcpy(pSend, pPkgBuffer, STT_PKG_HEAD_LEN);
	// 		memcpy(pSend + STT_PKG_HEAD_LEN , pXml, sizeof(pXml));
	//
	// 		oSystateCmd.ParsePkgXml(pSend);
	//
    // 		pClientSocket->XSendSysState(&oSystateCmd); //test
	// 		free(pSend);
	// 	}

	return 0;
}

long CSttTestServerBase::Process_Debug_GetDrvReportData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	// 	if(pClientSocket!=NULL)
	// 	{
	// 		CSttSysState oSystateCmd;
	// 		oSystateCmd.m_nRetSttCmd = STT_CMD_TYPE_DEBUG;
	// 		oSystateCmd.m_strID = STT_CMD_TYPE_DEBUG_GetTestParas;
	//
	// 		BYTE pPkgBuffer[] = {0xEB,0x90,0xEB,0x90,0x03,0x00,0x00,0x01,0x00,0x00,0x00,0xd0,0x07,0x00};
	// 		BYTE pXml[] =
	// 				"<sys-state name=\"NAME\" id=\"GetDrvReportData\" mater-host=\"HOST\" testor=\"\" id-cmd=\"0x3\" ret-type=\"\">\
	// 					<macro type=\"\" id=\"\" state=\"\">\
	// 						<results name=\"\" id=\"\">	\
	// 							<data id=\"\" value=\"\" />\
	// 						</results >\
	// 						<paras name=\"\" id=\"\">	\
	// 							<data id=\"\" value=\"\" />\
	// 						</paras>\
	// 					</macro>\
	// 					<paras name=\"\" id=\"\">	\
	// 						<data id=\"\" value=\"GetDrvReportData-Test\" />\
	// 					</paras>\
	// 				</sys-state>";
	// 		BYTE *pSend = (BYTE*)malloc(STT_PKG_HEAD_LEN + sizeof(pXml));
	// 		memcpy(pSend, pPkgBuffer, STT_PKG_HEAD_LEN);
	// 		memcpy(pSend + STT_PKG_HEAD_LEN , pXml, sizeof(pXml));
	//
	// 		oSystateCmd.ParsePkgXml(pSend);
	//
    // 		pClientSocket->XSendSysState(&oSystateCmd); //test
	// 		free(pSend);
	// 	}

	return 0;
}

long CSttTestServerBase::Process_Debug_GetFpgaData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	// 	if(pClientSocket!=NULL)
	// 	{
	// 		CSttSysState oSystateCmd;
	// 		oSystateCmd.UpdateSysStateHead(&oDebugCmd);
	// 		oSystateCmd.m_nType_Cmd = STT_CMD_TYPE_DEBUG;
	// 		oSystateCmd.m_strID = STT_CMD_TYPE_DEBUG_GetFpgaData;
	//
	// 		oSystateCmd.AddNewParasData(_T("addr-begin"), _T("0x111"));
	// 		oSystateCmd.AddNewParasData(_T("len"), 3);
	// 		oSystateCmd.AddNewParasData(_T("mem-data"), _T("123"));
	//
    // 		pClientSocket->XSendSysState(&oSystateCmd); //test
	// 	}

	return 0;
}

long CSttTestServerBase::Process_Debug_GetSocketConnect(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);
	oSysState.Set_ExecStatus_Success();

	m_oClientUserMngr.GenerateSysState(oSysState);

    return pClientSocket->XSendSysState(&oSysState);
}

long CSttTestServerBase::Process_Debug_ConfigDebug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	CSttTestEngineServerData::Process_Debug_ConfigDebug(pClientSocket, oDebugCmd);
	return 0;
}

//校准命令处理
long CSttTestServerBase::Process_Cmd_Adjust_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
    CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);

	//校准逻辑处理
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	CString strMacroID = oSttXmlSerializeTool.GetMacroID(CSttCmdDefineXmlRWKeys::CSttAdjustCmdKey());

	CSttSysState oEventSysState;
	oEventSysState.UpdateSysStateHead(&oAdjustCmd);

	//回复reply success
	oEventSysState.SetReply();
	oEventSysState.Set_ExecStatus_Success();
    pClientSocket->XSendSysState(&oEventSysState);

	//回复事件
	oEventSysState.SetEvent();

	//返回测试开始事件
	//两个事件不能用同一个CSttXmlSerializeTool  lijunqing 2020-10-24
	CSttXmlSerializeTool *pXmlRptStart = new CSttXmlSerializeTool();
	oEventSysState.GetSttMacro(FALSE, FALSE);
    oEventSysState.m_strID=SYS_STATE_EVENT_OnTestStarted;
	pXmlRptStart->CreateXmlSerializeWrite(&oEventSysState);
	Ret_SysState(oEventSysState, pClientSocket, *pXmlRptStart);
	delete pXmlRptStart;

	CSttXmlSerializeTool oXmlRptFinish;
	oEventSysState.GetSttMacro(FALSE, TRUE);
    oEventSysState.m_strID=SYS_STATE_EVENT_OnTestFinished;
	oXmlRptFinish.CreateXmlSerializeWrite(&oEventSysState);
	//获取校准系数结果
	CSttXmlSerializeBase *pXmlSerializeReport = oXmlRptFinish.GetMacroResults();

	//CSttSysState oSysState;
	//oSysState.UpdateSysStateHead(&oAdjustCmd);
    BOOL bRet=TRUE;

#ifndef _STT_NOT_IN_TEST_SERVER_
	// #ifdef _PSX_QT_LINUX_
    bRet=g_theSttAdjustTool.Adjust(strMacroID, pMacroParas , pXmlSerializeReport);
	//#endif
#endif

	if(bRet)
	{
		oEventSysState.Set_ExecStatus_Success();
	}
	else
	{
		oEventSysState.Set_ExecStatus_Failure();
	}

	//返回测试结束消息
	Ret_SysState(oEventSysState, pClientSocket, oXmlRptFinish);

	return 1;
}

long CSttTestServerBase::Process_Cmd_Ajust_ReadDeviceParameter(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
#ifndef _STT_NOT_IN_TEST_SERVER_
	//ReturnSysState(STT_CMD_ExecStatus_ACK);
    CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);
	//获取配置参数
	CSttXmlSerializeBase *pXmlSerializeParas = oSttXmlSerializeTool.GetParas();
	stt_xml_serialize_adj_para_config(pXmlSerializeParas);

	//获取数据
	CSttXmlSerializeTool oSttXmlRegister;
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister = NULL;
	pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, &oAdjustCmd, SYS_STATE_RETTYPE_REPORT);

    g_bWriteHdInfor=FALSE;
#ifdef _MainBoard_PI_
	CSttDeviceBase::g_pSttDeviceBase->GetPI1000ModulesFPGAInfo();
#endif
	stt_xml_serialize_register_adjust(pParasRegister);

	//恢复配置
	stt_init_adj_para_config();

	//返回结果
	Ret_SysState(oSysState, pClientSocket, oSttXmlRegister);

	//返回成功
	CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_SUCCESS, pClientSocket, NULL);
#endif
	return 1;
}

long CSttTestServerBase::Process_Cmd_Ajust_WriteFile(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd)
{
	//ReturnSysState(STT_CMD_ExecStatus_ACK);
    CSttTestEngineBase::ReturnSysState(&oAdjustCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAdjustCmd);
	oSysState.Set_ExecStatus_Success();
    pClientSocket->XSendSysState(&oSysState);
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    g_theSttAdjustTool.Adjust(oAdjustCmd.m_strID, NULL , NULL);
#endif
#endif
	CSttSysState oEventSysState;
	oEventSysState.UpdateSysStateHead(&oAdjustCmd);
	oEventSysState.SetEvent();

    oEventSysState.m_strID=SYS_STATE_EVENT_OnTestStarted;
    pClientSocket->XSendSysState(&oEventSysState);

    oEventSysState.m_strID=SYS_STATE_EVENT_OnTestFinished;
    pClientSocket->XSendSysState(&oEventSysState);

	return 1;
}

long CSttTestServerBase::Process_Cmd_System_ReadMeas(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd)
{
	//ReturnSysState(STT_CMD_ExecStatus_ACK);
    CSttTestEngineBase::ReturnSysState(&oSysCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);

	//获取数据
	CSttXmlSerializeTool oSttXmlRegister;
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister = NULL;
	pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, &oSysCmd, SYS_STATE_RETTYPE_MEAS);

#ifndef _STT_NOT_IN_TEST_SERVER_
	stt_xml_serialize_register_meas(pParasRegister);
#endif

	//返回结果
	Ret_SysState(oSysState, pClientSocket, oSttXmlRegister);

	//返回成功
	CSttTestEngineBase::ReturnSysState(&oSysCmd, STT_CMD_ExecStatus_SUCCESS, pClientSocket, NULL);

	return 1;
}


long CSttTestServerBase::Process_Cmd_System_GetSystemState(CSttXcmdChInterface *pClientSocket,CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool)
{
    CSttTestEngineBase::ReturnSysState(&oSysCmd, STT_CMD_ExecStatus_ACK,pClientSocket, NULL);

#ifndef _STT_NOT_IN_TEST_SERVER_

	//配置参数读取
	CSttXmlSerializeBase *pParasRead = oSttXmlSerializeTool.GetParas();
	STT_TEST_SYSTEM_STATUS_CONFIG oConfig;
	stt_xml_serialize_test_system_status_config(&oConfig, pParasRead);

	//获取数据
	CSttXmlSerializeTool oSttXmlRegister;
	CSttSysState oSysState;
	CSttXmlSerializeBase *pParasRegister = NULL;
	pParasRegister = stt_create_sys_state_paras_register(oSttXmlRegister, oSysState, &oSysCmd, SYS_STATE_RETTYPE_REPORT);

    if (oConfig.m_nDeviceStatus != 0)
	{
		//        stt_init_stt_device_status();
		BOOL bReturnUtc = FALSE;
#ifdef _PSX_QT_LINUX_
		g_nGetSystemStateTickCnt++;
		bReturnUtc = CSttDeviceBase::g_pSttDeviceBase->OnTimer(TRUE);
#endif
        stt_xml_serialize_device_status(pParasRegister,bReturnUtc);
	}

	//返回结果
	Ret_SysState(oSysState, pClientSocket, oSttXmlRegister);

#endif
	//返回成功
	CSttTestEngineBase::ReturnSysState(&oSysCmd, STT_CMD_ExecStatus_SUCCESS, pClientSocket, NULL);

	return 1;
}

//测试仪主动请求故障回放数据
long CSttTestServerBase::Comtrade_SendRequestData(long nIndex)
{
    //    CSttXcmdChInterface *pSocket = m_oSttTestCmd.GetRefSocketData();
    if (g_pReplayTestSocket == NULL)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttTestCmd.m_pRefSocketDataBase == NULL"));
		return 0;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Comtrade_SendRequestData:nIndex=%d"),nIndex);

    BYTE pSendBuf[STT_PKG_HEAD_LEN+10];
	long nDataLen = 5;
	pSendBuf[STT_PKG_HEAD_LEN] = STT_CMD_TYPE_COMTRADE_REQUESTDATA;
    memcpy(pSendBuf+STT_PKG_HEAD_LEN+1,&nIndex,4);

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_COMTRADE, nDataLen,
						   m_oSttTestCmd.m_nIDTester, 0, 0);

    return g_pReplayTestSocket->XSendBuffer(pSendBuf,STT_PKG_HEAD_LEN+nDataLen);
}

//测试仪应答发送数据开始
long CSttTestServerBase::Comtrade_SendDataStartAck(long nIndex)
{
    //    CSttXcmdChInterface *pSocket = m_oSttTestCmd.GetRefSocketData();
    if (g_pReplayTestSocket == NULL)
	{
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttTestCmd.m_pRefSocketDataBase == NULL"));
		return 0;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Comtrade_SendDataStartAck:nIndex=%d"),nIndex);

    BYTE pSendBuf[STT_PKG_HEAD_LEN+10];
	long nDataLen = 5;
	pSendBuf[STT_PKG_HEAD_LEN] = STT_CMD_TYPE_COMTRADE_SENDDATASTART_ACK;
    memcpy(pSendBuf+STT_PKG_HEAD_LEN+1,&nIndex,4);

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_COMTRADE, nDataLen,
						   m_oSttTestCmd.m_nIDTester, 0, 0);

    return g_pReplayTestSocket->XSendBuffer(pSendBuf,STT_PKG_HEAD_LEN+nDataLen);
}

long CSttTestServerBase::Process_Cmd_Comtrade(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	int nType = pBuf[STT_PKG_HEAD_LEN];

    switch (nType)
	{
		case STT_CMD_TYPE_COMTRADE_SENDDATAFINISH:
        return Process_Comtrade_SendDataFinish(pClientSocket,pBuf,nLen,pszCmdID,pszTestor);
		case STT_CMD_TYPE_COMTRADE_SENDDATASTART:
        return Process_Comtrade_SendDataStart(pClientSocket,pBuf,nLen,pszCmdID,pszTestor);
	}

	return 0;
}
