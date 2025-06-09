//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//在CSttProtocolInterface类的FreePxCmmInterface中会释放MqttClient，此处注释
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
	//UploadReportFinished 主题的  需要特殊处理，是JSON报文
	if (strcmp(pszCmdID, STT_CMD_TYPE_ATS_UploadReportFinished) == 0)
	{
		char* strMsg = (char*)malloc(strlen(pBuf) + 1);
		strMsg[strlen(pBuf)] = '\0';
		strcpy_s(strMsg, strlen(pBuf) + 1, (char*)pBuf);//_s安全版本中len应该定义为被复制字符串长度+1,即是strlen + 1,否则缓冲区不足
		m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV_JSON, (WPARAM)this, (LPARAM)strMsg);
		return 0;
	}

	switch (nCmdType)
	{
	case STT_CMD_TYPE_ATS:
		{
			//创建时，pAtsCmd的引用计数器为1，oDriver销毁时-1
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

			//pAtsCmd的引用计数器+1，然后发送收到命令的消息，对命令进行处理
			//采用发消息的方式，可以避免处理在这里堵塞，亦可避免连环死锁调用
			//消息发送给CSttAtsSvrMqttImpBase对象关联的ServiceWnd，在ServiceWnd中调用CSttAtsSvrMqttImpBase的“Process_Cmd_Ats”
			//此处实际上可以理解为直接调用了CSttAtsSvrMqttImpBase的“Process_Cmd_Ats”
			//参见  LRESULT CAtsSvrServiceWnd::OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam)
			oDriver.AddRef();
			m_pServiceWnd->PostMessage(WM_ON_STT_ENGINE_CMD_RCV, (WPARAM)this, (LPARAM)pAtsCmd);
		}
		break;

	case STT_CMD_TYPE_IOT:
		{
			//创建时，pIotCmd的引用计数器为1，oDriver销毁时-1
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
			//创建时，pTestCmd的引用计数器为1，oDriver销毁时-1
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
			//此处不对pszRetType进行区分：EVENT、RTDATA
			//因为可以通过sys-state的ID区分。
			//创建时，pSysState的引用计数器为1，oDriver销毁时-1
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
