#include "stdafx.h"
#include "VmGuBei.h"

#include "../../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "../../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface_Win.h"
#include "../../../../Module/System/StringTokenizer.h"


CVmGuBeiApp::CVmGuBeiApp()
{
	
}


CVmGuBeiApp::~CVmGuBeiApp(void)
{

}

//串口设备是否不需要 下发 串口号 波特率等，而是直接在本地代码中配置 
long CVmGuBeiApp::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pAppConfig)
{
	//发送消息，进行测试仪联机。否则在MQTT的连接里面连另一个Socket，会导致MQTT消息接收不到
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
}

void CVmGuBeiApp::OnXTimer(DWORD dwTimerID)
{
	//读测量值
	if (dwTimerID == STT_MACROTEST_TIMER_ID_READMEAS)
	{
		m_oGuBeiTest.Test(GUBEI_MACRO_ID_ReadMeas);
		SendRtData();
	}

	if (dwTimerID == STT_MACROTEST_TIMER_ID_JUDGEERR)
	{
		m_oGuBeiTest.m_fRunTime -= GUBEI_TIMER_NUMBER/1000;//运行时间的单位是s
		//计算设置值与测量值误差，满足一定误差范围，说明结束
		if (m_oGuBeiTest.IsTestFinished())
		{
			KillTimer(m_pVmImpMsgWnd->m_hWnd, dwTimerID);
			m_oGuBeiTest.setOneValue(ADDR_ZL, 0);// 关闭制冷
			m_oGuBeiTest.setOneValue(ADDR_SB, 0);// 关闭水泵
			m_oGuBeiTest.setOneValue(ADDR_YSJ_DELAY, 0); // 关闭电源
			m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);//判断控制成功或者失败，发送结束消息
		}
	}
}

//执行测试单元		先对参数进行解析，并调用测试仪的控制模块（例如：CGuBeiTest），将参数传递给测试仪
long CVmGuBeiApp::TestExec(CDataGroup *pParas)
{
	//得到设备ID
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_Temperature, m_oGuBeiTest.m_fTemperature); //温度设定 float
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_JdgType, m_oGuBeiTest.m_strJdgType);// 结束判定方式 string
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_AbsErr, m_oGuBeiTest.m_fAbsErr); // 绝对误差限 float
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_RunTime, m_oGuBeiTest.m_fRunTime); // 设定时间 float


	//yzj 2021-10-13
	if (m_strCurrTestMacroID == GUBEI_MACRO_ID_ManualTest)
	{
		//将发送实时数据的定时器和判断结果误差的定时器分开，以确保只发送一次结束消息
		if (m_oGuBeiTest.m_bIsXTimerRunning == FALSE)
		{
			m_oGuBeiTest.m_bIsXTimerRunning = TRUE;
			m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_READMEAS, GUBEI_TIMER_NUMBER, NULL);  //启动发送实时数据的定时器
		}

		m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_JUDGEERR, GUBEI_TIMER_NUMBER, NULL);  //启动判断结果误差的定时器
	}
	
	long nRes = m_oGuBeiTest.Test(m_strCurrTestMacroID);

	//GUBEI_MACRO_ID_ManualTest功能，会根据精度判断结束条件，并返回结束事件，不在此处返回结束事件
	if(nRes && m_strCurrTestMacroID != GUBEI_MACRO_ID_ManualTest)
	{
		m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
	}

	return nRes;
}

long CVmGuBeiApp::StopTest()
{
	m_oGuBeiTest.StopTest();

	//回复成功应答，让IotVm清除正在测试标记
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(m_pCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);

	return 0;
}

long CVmGuBeiApp::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	KillTimer(m_pVmImpMsgWnd->m_hWnd, STT_MACROTEST_TIMER_ID_READMEAS);
	m_oGuBeiTest.m_bIsXTimerRunning = FALSE;
	//在此添加关闭设备的代码
	m_oGuBeiTest.Test(GUBEI_MACRO_ID_StopManualTest);
	m_oGuBeiTest.DisConnect();

	return 0;
}

BOOL CVmGuBeiApp::IsConnectSuccess()
{
	//在此添加代码
	return m_oGuBeiTest.IsConnectSuccess();
} 

BOOL CVmGuBeiApp::ConnectDeviceExec()
{
	//在此添加ConnectDevice的代码
    return m_oGuBeiTest.Connect();
}

long CVmGuBeiApp::GetRtDatas(CDataGroup *pSttParas)
{
	//m_oGuBeiTest.Test(SIMPAC_MACRO_ID_ReadMeas);
	pSttParas->AddNewData(GUBEI_PARA_ID_Temperature, m_oGuBeiTest.m_fTemperature_Read);
	pSttParas->AddNewData(GUBEI_PARA_ID_Humidity, m_oGuBeiTest.m_fHumidity_Read);

	return 0;
}

void CVmGuBeiApp::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CVmGuBeiApp::OnConfigDevice"));
	m_oGuBeiTest.Connect();
}

void CVmGuBeiApp::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{
	if(m_pCmmOptrInterface)
	{
		CDataGroup oGroup;
		oGroup.m_strID = m_strCurrTestMacroID;

		if (m_strCurrTestMacroID == GUBEI_MACRO_ID_ReadMeas)
		{
			oGroup.AddNewData(GUBEI_PARA_ID_Temperature, m_oGuBeiTest.m_fTemperature_Read);
			//oGroup.AddNewData(GUBEI_PARA_ID_Humidity, m_oGuBeiTest.m_fHumidity_Read);
		}

		m_pSttMacroTestEventServerInterface->OnTestEvent_TestFinished(m_pCmmOptrInterface, &oGroup);
	}
	else
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pCmmOptrInterface == NULL"));
}

//topic：测试仪SN/RTDATA
void CVmGuBeiApp::SendRtData()
{
	CString strHumidity, strHumidity_Read, strTemperature, strTemperature_Read;
	strHumidity.Format(_T("%.2f"), m_oGuBeiTest.m_fHumidity);
	strHumidity_Read.Format(_T("%.2f"), m_oGuBeiTest.m_fHumidity_Read);
	strTemperature.Format(_T("%.2f"), m_oGuBeiTest.m_fTemperature);
	strTemperature_Read.Format(_T("%.2f"), m_oGuBeiTest.m_fTemperature_Read);

	CString strXML;
	CDataGroup oGroup;
	oGroup.AddNewData(STT_CMD_PARA_DeviceSN, m_strDeviceSN);
	CDataGroup *pParas = oGroup.AddNewGroup(_T(""), _T("RTDATA"), _T(""));
	pParas->AddNewData(_T("RealTemp"), strTemperature_Read);
	pParas->AddNewData(_T("SetTemp"), strTemperature);
	oGroup.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXML);

	CString strTopic = m_strDeviceSN + _T("/RTDATA");
	m_pCmmOptrInterface->Send(const_cast<char*>(strXML.GetString()), 
		strXML.GetLength(), strTopic);
}