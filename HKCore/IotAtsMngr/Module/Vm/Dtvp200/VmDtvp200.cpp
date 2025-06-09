#include "stdafx.h"
#include "VmDtvp200.h"

#include "../../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "../../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface_Win.h"
#include "../../../../Module/System/StringTokenizer.h"


CVmDtvp200::CVmDtvp200()
{

}


CVmDtvp200::~CVmDtvp200(void)
{

}

long CVmDtvp200::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pAppConfig)
{
	//发送消息，进行测试仪联机。
	m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_CONFIGDEVICE, 0, 0);

	//加个while循环，判断是否联机成功，能把该函数返回值用起来
	CTickCount32 oTick;

	while (TRUE)
	{
		if (IsConnectSuccess())
		{
			break;
		}

		if (GetLastError().GetLength() > 0)
		{
			//错误码>0，说明已经联机失败。不用等超时
			break;
		}

		oTick.DoEvents(50);

		if (oTick.GetTickCountLong() >= 30000)
		{
			break;
		}
	}

	return IsConnectSuccess();
	//BOOL bIsConnect = m_oSimpacTestAscii2.Connect();

	//在联机返回值中，会根据返回值进行REPLY应答，故此处注释  shaolei  20210917
// 	if (IsConnectSuccess())
// 	{
// 		m_pSttMacroTestEventServerInterface->OnTestEvent_ConnectSuccess(pSttCmmOptrInterface, pAppConfig);
// 	}
// 	else
// 	{
// 		m_pSttMacroTestEventServerInterface->OnTestEvent_ConnectFailed(pSttCmmOptrInterface, pAppConfig);
// 	}

	//return bIsConnect;
}

void CVmDtvp200::OnXTimer(DWORD dwTimerID)
{
	m_oDtvp200.receive_answer();
	//读测量值，即返回实时值
	if (dwTimerID == STT_MACROTEST_TIMER_ID_READMEAS)
	{
		SendRtData();
		return;
	}

	if (dwTimerID == STT_MACROTEST_TIMER_ID_JUDGEERR)
	{
		m_oDtvp200.m_nRunTime += DTVP_TIMER_NUMBER_JUDGERSLT;
		if (m_oDtvp200.IsTestFinish())//机器达到指定位置
		{
			KillTimer(m_pVmImpMsgWnd->m_hWnd, dwTimerID);
			m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
		}
	}
}

long CVmDtvp200::TestExec(CDataGroup *pParas)
{
	double fAngle;
	
	if (m_strCurrTestMacroID == DTVP_MACRO_ID_AngleSet)
	{
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PitchWrokModel, (long &)m_oDtvp200.m_nWrokModel[0]);
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PitchAngleControl, fAngle);
		m_oDtvp200.m_nAngleControl[0] = fAngle * 1000;
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PitchSpeedControl, fAngle);
		m_oDtvp200.m_nSpeedControl[0] = fAngle * 1000;

		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PositionWrokModel, (long &)m_oDtvp200.m_nWrokModel[1]);
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PositionAngleControl, fAngle);
		m_oDtvp200.m_nAngleControl[1] = fAngle * 1000;
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PositionSpeedControl, fAngle);
		m_oDtvp200.m_nSpeedControl[1] = fAngle * 1000;

		if (m_oDtvp200.m_bIsXTimerRunning == FALSE)
		{
			m_oDtvp200.m_bIsXTimerRunning = TRUE;
			m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_READMEAS, DTVP_TIMER_NUMBER_READMEAS, NULL);
		}
	}
	else if (m_strCurrTestMacroID == DTVP_MACRO_ID_SetEnable)
	{
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PitchEnable, (long &)m_oDtvp200.m_nEnable[0]);
		stt_GetDataValueByID(pParas, DTVP_PARA_ID_PositionEnable, (long &)m_oDtvp200.m_nEnable[1]);
	}

	long nRet = m_oDtvp200.Test(m_strCurrTestMacroID);

	//延迟两百ms,起定时器。在定时器中去收实时数据，确保收到的实时数据是最新的
	CTickCount32 oTick;
	oTick.DoEvents(200);
	m_oDtvp200.m_nRunTime = 0;
	m_oDtvp200.m_nJudgeCount = 0;
	m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_JUDGEERR, DTVP_TIMER_NUMBER_JUDGERSLT, NULL);  //启动判断结果误差的定时器

	return nRet;
}

long CVmDtvp200::StopTest()
{
	m_strCurrTestMacroID = DTVP_MACRO_ID_StopTest;
	m_oDtvp200.StopTest();

	//回复成功应答，让IotVm清除正在测试标记
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(m_pCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);

	return 0;
}

long CVmDtvp200::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	//在此添加关闭设备的代码
	KillTimer(m_pVmImpMsgWnd->m_hWnd, STT_MACROTEST_TIMER_ID_READMEAS);
	m_oDtvp200.m_bIsXTimerRunning = FALSE;
	m_oDtvp200.StopTest();
	m_oDtvp200.DisConnect();

	return 0;
}

BOOL CVmDtvp200::IsConnectSuccess()
{
	//在此添加代码
	return m_oDtvp200.IsConnectSuccess();
}

BOOL CVmDtvp200::ConnectDeviceExec()
{
	//在此添加ConnectDevice的代码
	return m_oDtvp200.Connect();
}

long CVmDtvp200::GetRtDatas(CDataGroup *pSttParas)
{
	//m_oSimpacTestAscii2.Test(SIMPAC_MACRO_ID_ReadMeas);
 	pSttParas->AddNewData(DTVP_RESULT_ID_PitchAngle, m_oDtvp200.m_fPitchRtAngle);
 	pSttParas->AddNewData(DTVP_RESULT_ID_PositionAngle, m_oDtvp200.m_fPositionRtAngle);

	return 0;
}

void CVmDtvp200::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CVmDtvpApp::OnConfigDevice"));
	m_oDtvp200.Connect();
}

void CVmDtvp200::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{
	if(m_pCmmOptrInterface)
	{
		CDataGroup oGroup;
		oGroup.m_strID = m_strCurrTestMacroID;

		if (m_strCurrTestMacroID == DTVP_MACRO_ID_AngleSet)
		{
			oGroup.AddNewData(DTVP_RESULT_ID_PitchAngle, m_oDtvp200.m_fPitchRtAngle);
			oGroup.AddNewData(DTVP_RESULT_ID_PositionAngle, m_oDtvp200.m_fPositionRtAngle);
		}

		m_pSttMacroTestEventServerInterface->OnTestEvent_TestFinished(m_pCmmOptrInterface, &oGroup);
	}
	else
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pCmmOptrInterface == NULL"));
}

void CVmDtvp200::SendRtData()
{
	CString strTm;
	GetCurrSystemtimeString(strTm);

	CString strSetPitchRtAngle, strRealPitchAngle;
	strRealPitchAngle.Format(_T("%.3f"), m_oDtvp200.m_fPitchRtAngle);
	float fAngleControl = m_oDtvp200.m_nAngleControl[0]/1000.0;
	strSetPitchRtAngle.Format(_T("%.3f"), fAngleControl);
	//strPitchRtSpeed.Format(_T("%.2f"), m_oDtvp200.m_nPitchRtSpeed);
	//strSetPositionRtAngle.Format(_T("%.3f"), m_oDtvp200.m_fPositionRtAngle);
	//strPositionRtSpeed.Format(_T("%.2f"), m_oDtvp200.m_nPositionRtSpeed);

	CString strXML;
	CDataGroup oGroup;
	oGroup.AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	CDataGroup *pParas = oGroup.AddNewGroup(_T(""), _T("RTDATA"), _T(""));
	pParas->AddNewData(_T("SetPitchAngle"), strSetPitchRtAngle);
	pParas->AddNewData(_T("RealPitchAngle"), strRealPitchAngle);
	//pParas->AddNewData(_T("PitchSpeed"), strPitchRtSpeed);
	//pParas->AddNewData(_T("SetPositionAngle"), strSetPositionRtAngle);
	//pParas->AddNewData(_T("PositionSpeed"), strPositionRtSpeed);
	oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXML);

	CString strTopic = m_strDeviceSN + _T("/RTDATA");
	m_pCmmOptrInterface->Send(const_cast<char*>(strXML.GetString()), 
		strXML.GetLength(), strTopic);
}