#include "stdafx.h"
#include"VmSimpac.h"

#include "../../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../../../../Module/API/GlobalConfigApi.h"

#include "../../../../SttStudio/Module/SmartTestInterface/SttMacroTestMsgRcvInterface_Win.h"
#include "../../../../Module/System/StringTokenizer.h"


CVmSimpacApp::CVmSimpacApp()
{

}


CVmSimpacApp::~CVmSimpacApp(void)
{

}

long CVmSimpacApp::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pAppConfig)
{
	stt_GetDataValueByID(pAppConfig, XPARA_ID_Remote_ip, m_oSimpacTestAscii2.m_strIP);
	short nPort;
	stt_GetDataValueByID(pAppConfig, XPARA_ID_Remote_port, nPort);
	m_oSimpacTestAscii2.m_nPort = nPort;
	stt_GetDataValueByID(pAppConfig, XPARA_ID_Address, m_oSimpacTestAscii2.m_strAddress);
	//������Ϣ�����в�����������������MQTT��������������һ��Socket���ᵼ��MQTT��Ϣ���ղ���
	m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_CONFIGDEVICE, 0, 0);

	//������  
// 	CTickCount32 oTick32;
// 	oTick32.DoEvents(5000);
// 	return TRUE;

	//�Ӹ�whileѭ�����ж��Ƿ������ɹ����ܰѸú�������ֵ������
	CTickCount32 oTick;
	while (TRUE)
	{
		if (IsConnectSuccess())
		{
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

	//����������ֵ�У�����ݷ���ֵ����REPLYӦ�𣬹ʴ˴�ע��  shaolei  20210917
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

void CVmSimpacApp::OnXTimer(DWORD dwTimerID)
{
	//������ֵ
	if (dwTimerID == STT_MACROTEST_TIMER_ID_READMEAS)
	{
	//m_oSimpacTestAscii2.Test(SIMPAC_MACRO_ID_ReadMeas);
	m_oSimpacTestAscii2.Test(SIMPAC_MACRO_ID_ReadMeas);
	SendRtData();
	}

	if (dwTimerID == STT_MACROTEST_TIMER_ID_JUDGEERR)
	{
		m_oSimpacTestAscii2.m_fRunTime -= SIMPAC_TIMER_NUMBER;
		//��������ֵ�����ֵ������һ����Χ��˵������
		if (m_oSimpacTestAscii2.IsTestFinished())
		{
				KillTimer(m_pVmImpMsgWnd->m_hWnd, dwTimerID);
			m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
		}
	}
}

long CVmSimpacApp::TestExec(CDataGroup *pParas)
{
	stt_GetDataValueByID(pParas, SIMPAC_PARA_ID_Temperature, m_oSimpacTestAscii2.m_fTemperature);
	stt_GetDataValueByID(pParas, SIMPAC_PARA_ID_Humidity, m_oSimpacTestAscii2.m_fHumidity);
	stt_GetDataValueByID(pParas, SIMPAC_PARA_ID_JdgType, m_oSimpacTestAscii2.m_strJdgType);
	stt_GetDataValueByID(pParas, SIMPAC_PARA_ID_AbsErr, m_oSimpacTestAscii2.m_fAbsErr);
	stt_GetDataValueByID(pParas, SIMPAC_PARA_ID_RunTime, m_oSimpacTestAscii2.m_fRunTime);
	m_oSimpacTestAscii2.m_fRunTime *= 1000;

	//yzj 2021-10-13
	if (m_strCurrTestMacroID == SIMPAC_MACRO_ID_ManualTest)
	{
		//������ʵʱ���ݵĶ�ʱ�����жϽ�����Ķ�ʱ���ֿ�����ȷ��ֻ����һ�ν�����Ϣ
		if (m_oSimpacTestAscii2.m_bIsXTimerRunning == FALSE)
		{
			m_oSimpacTestAscii2.m_bIsXTimerRunning = TRUE;
			m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_READMEAS, SIMPAC_TIMER_NUMBER, NULL);  //��������ʵʱ���ݵĶ�ʱ��
		}

		m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_JUDGEERR, SIMPAC_TIMER_NUMBER, NULL);  //�����жϽ�����Ķ�ʱ��
	}
	
	long nRes = m_oSimpacTestAscii2.Test(m_strCurrTestMacroID);

	//SIMPAC_MACRO_ID_ManualTest���ܣ�����ݾ����жϽ��������������ؽ����¼������ڴ˴����ؽ����¼�
	if(nRes && m_strCurrTestMacroID != SIMPAC_MACRO_ID_ManualTest)
	{
		m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
// 		CSttResults *pSttRslts = pSttMacro->GetResults();
// 		pSttRslts->m_strID = pSttMacro->m_strID;
// 
// 		if (pSttMacro->m_strID == SIMPAC_MACRO_ID_ReadMeas)
// 		{
// 			GetRtDatas(pSttRslts);
// 		}
// 
// 		m_pSttMacroTestEventServerInterface->OnTestEvent_TestFinished(pSttCmmOptrInterface, pSttRslts);
	}

	return nRes;
}

long CVmSimpacApp::StopTest()
{
	m_oSimpacTestAscii2.StopTest();

	//�ظ��ɹ�Ӧ����IotVm������ڲ��Ա��
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(m_pCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);

	return 0;
}

long CVmSimpacApp::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	KillTimer(m_pVmImpMsgWnd->m_hWnd, STT_MACROTEST_TIMER_ID_READMEAS);
	m_oSimpacTestAscii2.m_bIsXTimerRunning = FALSE;
	//�ڴ���ӹر��豸�Ĵ���
	m_oSimpacTestAscii2.Test(SIMPAC_MACRO_ID_StopManualTest);
	m_oSimpacTestAscii2.DisConnect();

	return 0;
}

BOOL CVmSimpacApp::IsConnectSuccess()
{
	//�ڴ���Ӵ���
	return m_oSimpacTestAscii2.IsConnectSuccess();
}

BOOL CVmSimpacApp::ConnectDeviceExec()
{
	//�ڴ����ConnectDevice�Ĵ���
    return m_oSimpacTestAscii2.Connect();
}

long CVmSimpacApp::GetRtDatas(CDataGroup *pSttParas)
{
	//m_oSimpacTestAscii2.Test(SIMPAC_MACRO_ID_ReadMeas);
	pSttParas->AddNewData(SIMPAC_PARA_ID_Temperature, m_oSimpacTestAscii2.m_fTemperature_Read);
	pSttParas->AddNewData(SIMPAC_PARA_ID_Humidity, m_oSimpacTestAscii2.m_fHumidity_Read);

	return 0;
}

void CVmSimpacApp::OnConfigDevice(WPARAM wParam, LPARAM lParam)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CVmSimpacApp::OnConfigDevice"));
	m_oSimpacTestAscii2.Connect();
}

void CVmSimpacApp::OnMacroTestMsgFinish(WPARAM wParam, LPARAM lParam)
{
	if(m_pCmmOptrInterface)
	{
		CDataGroup oGroup;
		oGroup.m_strID = m_strCurrTestMacroID;

		if (m_strCurrTestMacroID == SIMPAC_MACRO_ID_ReadMeas)
		{
			oGroup.AddNewData(SIMPAC_PARA_ID_Temperature, m_oSimpacTestAscii2.m_fTemperature_Read);
			oGroup.AddNewData(SIMPAC_PARA_ID_Humidity, m_oSimpacTestAscii2.m_fHumidity_Read);
		}

		m_pSttMacroTestEventServerInterface->OnTestEvent_TestFinished(m_pCmmOptrInterface, &oGroup);
	}
	else
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pCmmOptrInterface == NULL"));
}

//topic��������SN/RTDATA
void CVmSimpacApp::SendRtData()
{
	//m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_RTDATA, (WPARAM)this, (LPARAM)this);

	//yzj 2021-10-11 ƴRTDATA����
// 	CString strTm;
// 	GetCurrSystemtimeString(strTm);

// 	CStringTokenizer oTokens;
// 	oTokens.Init(m_oSimpacTestAscii2.m_strIP, '.');
// 	//�˴�DeviceSNȡ���豸IP����Ҫ���ݿ���������ȷ
// 	CString strDeviceSN;
// 	for (int i =0; i < oTokens.GetStringsCount(); i++)
// 	{
// 		strDeviceSN += oTokens.GetToken(i);
// 	}

	//������
// 	m_oSimpacTestAscii2.m_fHumidity_Read = 0.15;
// 	m_oSimpacTestAscii2.m_fTemperature_Read = 25.89;

	CString strHumidity, strHumidity_Read, strTemperature, strTemperature_Read;
	strHumidity.Format(_T("%.2f"), m_oSimpacTestAscii2.m_fHumidity);
	strHumidity_Read.Format(_T("%.2f"), m_oSimpacTestAscii2.m_fHumidity_Read);
	strTemperature.Format(_T("%.2f"), m_oSimpacTestAscii2.m_fTemperature);
	strTemperature_Read.Format(_T("%.2f"), m_oSimpacTestAscii2.m_fTemperature_Read);
	//������λС��
// 	strHumidity = strHumidity.Mid(0, strHumidity.Find('.') + 3);
// 	strHumidity_Read = strHumidity_Read.Mid(0, strHumidity_Read.Find('.') + 3);
// 	strTemperature = strTemperature.Mid(0, strTemperature.Find('.') + 3);
// 	strTemperature_Read = strTemperature_Read.Mid(0, strTemperature_Read.Find('.') + 3);

// 	CString strXML;
// 	strXML.Format(_T("<iot_rt_device_data>"
// 		"<sn>%s</sn>"
// 		"<data_format>string</data_format>"
// 		"<data>RealTemp=%s;SetTemp=%s;RealHumi=%s;SetHumi=%s;</data>"
// 		"<tm_update>%s</tm_update>"
// 		"<is_warning>%d</is_warning>"
// 		"</iot_rt_device_data>"), strDeviceSN,
// 		strTemperature_Read, strTemperature, 
// 		strHumidity_Read, strHumidity, 	
// 		strTm, 0);
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