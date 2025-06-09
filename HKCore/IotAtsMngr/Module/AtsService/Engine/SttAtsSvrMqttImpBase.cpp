//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAtsSvrMqttImpBase.cpp  CSttAtsSvrMqttImpBase


#include "stdafx.h"
#include "SttAtsSvrMqttImpBase.h"
#include "AtsSvrMsgWnd.h"

#include "../../SttMqttClientEngineConfig.h"

CSttAtsSvrMqttImpBase::CSttAtsSvrMqttImpBase()
{
	m_pMqttClient = NULL;

	m_pServiceWnd = new CAtsSvrMsgWnd();
	m_pServiceWnd->CreateAtsSvrMsgWnd(this);
	m_pServiceWnd->ShowWindow(SW_HIDE);
}

CSttAtsSvrMqttImpBase::~CSttAtsSvrMqttImpBase()
{
	//��CSttProtocolInterface���FreePxCmmInterface�л��ͷ�MqttClient���˴�ע��
// 	if (m_pMqttClient != NULL)
// 	{
// 		delete m_pMqttClient;
// 		m_pMqttClient = NULL;
// 	}

	m_pServiceWnd->DestroyWindow();
	delete m_pServiceWnd;
	m_pServiceWnd = NULL;

}

BOOL CSttAtsSvrMqttImpBase::CreateAtsServiceMqttClient(const CString &strMqttTopic)
{
	if (m_pMqttClient != NULL)
	{
		if (m_pMqttClient->IsConnectSuccessful())
		{
			return TRUE;
		}
	}
	else
	{
		m_pMqttClient = new CSttProtoAtsServiceMqttClient(strMqttTopic);
		m_pMqttClient->m_strSN = m_strID;
		m_pMqttClient->SetMqttEngineRef(this);
	}

	return m_pMqttClient->Connect(CSttMqttClientEngineConfig::GetMqttServerIP(), CSttMqttClientEngineConfig::GetMqttServerPort(), _T("AtsService"));
}

long CSttAtsSvrMqttImpBase::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	//UploadReportFinished �����  ��Ҫ���⴦����JSON����
	if (strcmp(pszCmdID, STT_CMD_TYPE_ATS_UploadReportFinished) == 0)
	{
		char* strMsg = (char*)malloc(strlen(pBuf) + 1);
		strMsg[strlen(pBuf)] = '\0';
		strcpy_s(strMsg, strlen(pBuf) + 1, (char*)pBuf);//_s��ȫ�汾��lenӦ�ö���Ϊ�������ַ�������+1,����strlen + 1,���򻺳�������
		m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV_JSON, (WPARAM)this, (LPARAM)strMsg);
		return 0;
	}

	switch (nCmdType)
	{
	case STT_CMD_TYPE_ATS:
		{
			//����ʱ��pAtsCmd�����ü�����Ϊ1��oDriver����ʱ-1
			CXObjectRefDriver oDriver(CSttAtsCmd::New);
			CSttAtsCmd  *pAtsCmd = (CSttAtsCmd*)oDriver.New();
			pAtsCmd->SetSttCmmOptrInterface(pCmmOptrInterface);
			pAtsCmd->m_strFromSN = strFromSN;

			if (pBuf[0] == '<')
			{
				BufToCmd(pAtsCmd, pBuf, nLen, MQTT_DATA_FORMAT_XML);
			}
			else
			{
				BufToCmd(pAtsCmd, pBuf, nLen, MQTT_DATA_FORMAT_JSON);
			}

			//pAtsCmd�����ü�����+1��Ȼ�����յ��������Ϣ����������д���
			//���÷���Ϣ�ķ�ʽ�����Ա��⴦���������������ɱ���������������
			//��Ϣ���͸�CSttAtsSvrMqttImpBase���������ServiceWnd����ServiceWnd�е���CSttAtsSvrMqttImpBase�ġ�Process_Cmd_Ats��
			//�˴�ʵ���Ͽ������Ϊֱ�ӵ�����CSttAtsSvrMqttImpBase�ġ�Process_Cmd_Ats��
			//�μ�  LRESULT CAtsSvrServiceWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
			oDriver.AddRef();
			m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV, (WPARAM)this, (LPARAM)pAtsCmd);
		}
		break;

	case STT_CMD_TYPE_IOT:
		{
			//����ʱ��pIotCmd�����ü�����Ϊ1��oDriver����ʱ-1
			CXObjectRefDriver oDriver(CSttIotCmd::New);
			CSttIotCmd  *pIotCmd = (CSttIotCmd*)oDriver.New();
			pIotCmd->SetSttCmmOptrInterface(pCmmOptrInterface);
			pIotCmd->m_strFromSN = strFromSN;

			if (pBuf[0] == '<')
			{
				BufToCmd(pIotCmd, pBuf, nLen, MQTT_DATA_FORMAT_XML);
			}
			else
			{
				BufToCmd(pIotCmd, pBuf, nLen, MQTT_DATA_FORMAT_JSON);
			}

			oDriver.AddRef();
			m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV_IOTCMD, (WPARAM)this, (LPARAM)pIotCmd);
		}
		break;

	case STT_CMD_TYPE_TEST:
		{
			//����ʱ��pTestCmd�����ü�����Ϊ1��oDriver����ʱ-1
			CXObjectRefDriver oDriver(CSttTestCmd::New);
			CSttTestCmd  *pTestCmd = (CSttTestCmd*)oDriver.New();
			pTestCmd->SetSttCmmOptrInterface(pCmmOptrInterface);
			pTestCmd->m_strFromSN = strFromSN;

			if (pBuf[0] == '<')
			{
				BufToCmd(pTestCmd, pBuf, nLen, MQTT_DATA_FORMAT_XML);
			}
			else
			{
				BufToCmd(pTestCmd, pBuf, nLen, MQTT_DATA_FORMAT_JSON);
			}

			oDriver.AddRef();
			m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV_TESTCMD, (WPARAM)this, (LPARAM)pTestCmd);
		}
		break;

	case STT_CMD_TYPE_SYSSTATE:
		{
			//�˴�����pszRetType�������֣�EVENT��RTDATA
			//��Ϊ����ͨ��sys-state��ID���֡�
			//����ʱ��pSysState�����ü�����Ϊ1��oDriver����ʱ-1
			CXObjectRefDriver oDriver(CSttSysState::New);
			CSttSysState  *pSysState = (CSttSysState*)oDriver.New();
			pSysState->SetSttCmmOptrInterface(pCmmOptrInterface);
			pSysState->m_strFromSN = strFromSN;

			if (pBuf[0] == '<')
			{
				BufToCmd(pSysState, pBuf, nLen, MQTT_DATA_FORMAT_XML);
			}
			else
			{
				BufToCmd(pSysState, pBuf, nLen, MQTT_DATA_FORMAT_JSON);
			}

			oDriver.AddRef();
			m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV_SYSSTATE, (WPARAM)this, (LPARAM)pSysState);
		}
		break;
	}
	
	return 0;
}
