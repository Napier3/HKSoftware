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

//�����豸�Ƿ���Ҫ �·� ���ں� �����ʵȣ�����ֱ���ڱ��ش��������� 
long CVmGuBeiApp::TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pAppConfig)
{
	//������Ϣ�����в�����������������MQTT��������������һ��Socket���ᵼ��MQTT��Ϣ���ղ���
	m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_CONFIGDEVICE, 0, 0);

	//�Ӹ�whileѭ�����ж��Ƿ������ɹ����ܰѸú�������ֵ������
	CTickCount32 oTick;

	while (TRUE)
	{
		if (IsConnectSuccess())
		{
			break;
		}

		if (GetLastError().GetLength() > 0)
		{
			//������>0��˵���Ѿ�����ʧ�ܡ����õȳ�ʱ
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
	//������ֵ
	if (dwTimerID == STT_MACROTEST_TIMER_ID_READMEAS)
	{
		m_oGuBeiTest.Test(GUBEI_MACRO_ID_ReadMeas);
		SendRtData();
	}

	if (dwTimerID == STT_MACROTEST_TIMER_ID_JUDGEERR)
	{
		m_oGuBeiTest.m_fRunTime -= GUBEI_TIMER_NUMBER/1000;//����ʱ��ĵ�λ��s
		//��������ֵ�����ֵ������һ����Χ��˵������
		if (m_oGuBeiTest.IsTestFinished())
		{
			KillTimer(m_pVmImpMsgWnd->m_hWnd, dwTimerID);
			m_oGuBeiTest.setOneValue(ADDR_ZL, 0);// �ر�����
			m_oGuBeiTest.setOneValue(ADDR_SB, 0);// �ر�ˮ��
			m_oGuBeiTest.setOneValue(ADDR_YSJ_DELAY, 0); // �رյ�Դ
			m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);//�жϿ��Ƴɹ�����ʧ�ܣ����ͽ�����Ϣ
		}
	}
}

//ִ�в��Ե�Ԫ		�ȶԲ������н����������ò����ǵĿ���ģ�飨���磺CGuBeiTest�������������ݸ�������
long CVmGuBeiApp::TestExec(CDataGroup *pParas)
{
	//�õ��豸ID
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_Temperature, m_oGuBeiTest.m_fTemperature); //�¶��趨 float
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_JdgType, m_oGuBeiTest.m_strJdgType);// �����ж���ʽ string
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_AbsErr, m_oGuBeiTest.m_fAbsErr); // ��������� float
	stt_GetDataValueByID(pParas, GUBEI_PARA_ID_RunTime, m_oGuBeiTest.m_fRunTime); // �趨ʱ�� float


	//yzj 2021-10-13
	if (m_strCurrTestMacroID == GUBEI_MACRO_ID_ManualTest)
	{
		//������ʵʱ���ݵĶ�ʱ�����жϽ�����Ķ�ʱ���ֿ�����ȷ��ֻ����һ�ν�����Ϣ
		if (m_oGuBeiTest.m_bIsXTimerRunning == FALSE)
		{
			m_oGuBeiTest.m_bIsXTimerRunning = TRUE;
			m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_READMEAS, GUBEI_TIMER_NUMBER, NULL);  //��������ʵʱ���ݵĶ�ʱ��
		}

		m_pVmImpMsgWnd->SetTimer(STT_MACROTEST_TIMER_ID_JUDGEERR, GUBEI_TIMER_NUMBER, NULL);  //�����жϽ�����Ķ�ʱ��
	}
	
	long nRes = m_oGuBeiTest.Test(m_strCurrTestMacroID);

	//GUBEI_MACRO_ID_ManualTest���ܣ�����ݾ����жϽ��������������ؽ����¼������ڴ˴����ؽ����¼�
	if(nRes && m_strCurrTestMacroID != GUBEI_MACRO_ID_ManualTest)
	{
		m_pVmImpMsgWnd->PostMessage(STT_MACROTEST_MSG_FINISH, (WPARAM)this, 0);
	}

	return nRes;
}

long CVmGuBeiApp::StopTest()
{
	m_oGuBeiTest.StopTest();

	//�ظ��ɹ�Ӧ����IotVm������ڲ��Ա��
	CSttSysState oSysState;
	m_pSttMacroTestEventServerInterface->OnTestState_Reply(m_pCmmOptrInterface, &oSysState, STT_CMD_ExecStatus_SUCCESS, STT_CMD_TYPE_ATS_StopTest, STT_CMD_SYSSTATE_TEST);

	return 0;
}

long CVmGuBeiApp::TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas)
{
	KillTimer(m_pVmImpMsgWnd->m_hWnd, STT_MACROTEST_TIMER_ID_READMEAS);
	m_oGuBeiTest.m_bIsXTimerRunning = FALSE;
	//�ڴ���ӹر��豸�Ĵ���
	m_oGuBeiTest.Test(GUBEI_MACRO_ID_StopManualTest);
	m_oGuBeiTest.DisConnect();

	return 0;
}

BOOL CVmGuBeiApp::IsConnectSuccess()
{
	//�ڴ���Ӵ���
	return m_oGuBeiTest.IsConnectSuccess();
} 

BOOL CVmGuBeiApp::ConnectDeviceExec()
{
	//�ڴ����ConnectDevice�Ĵ���
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

//topic��������SN/RTDATA
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