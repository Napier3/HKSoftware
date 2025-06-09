#include "stdafx.h"
#include "SttMqttOverTimeMngr.h"
#include "../../../Module/System/TickCount32.h"

//2020-5-27
//调试的时候，是否需要判断超时，内存中将变量的值修改为0即可
long g_nSttMqttOverTimeEnable = 1;

#ifdef _PSX_QT_LINUX_
         #include <pthread.h> //线程头文件
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////
void stt_mqtt_cmd_info::OnSendCmdFinish(BOOL bSuccess)
{
	if (m_pSttMqttOverTimeMsgRcv != NULL)
	{
		if (bSuccess)
		{
			m_pSttMqttOverTimeMsgRcv->OnSendCmdFinish(m_pMqttClient, m_nCmdType, m_pszMqttTopic);
		}
		else
		{
			m_pSttMqttOverTimeMsgRcv->OnSendCmdFailFinish(m_pMqttClient, m_nCmdType, m_pszMqttTopic);
		}	
	}

	m_nUse = FALSE;
}

BOOL stt_mqtt_cmd_info::CheckTimeOut(DWORD dwCurTime)
{
	BOOL bRet = FALSE;

	if (!IsUsed())
	{
		return bRet;
	}

	if (g_nSttMqttOverTimeEnable)
	{
		bRet = IsTimeOut(dwCurTime);
	}

	if (bRet)
	{
//		long nVal = ((void *)pMqttClient)->m_oExpandRecvBuf.GetDataLength();
		
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("命令超时：【%d,%d】【%s】%d"),nCmdType,nMode,pszMqttTopic,nVal);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("命令超时：【%d,%d】【%s】"), m_nCmdType,m_nMode,m_pszMqttTopic);

		if (m_pSttMqttOverTimeMsgRcv != NULL)
		{
			m_pSttMqttOverTimeMsgRcv->OnSendCmdOverTime(m_pMqttClient, m_nCmdType, m_pszMqttTopic);
		}

		m_nUse = FALSE;
	}

	return bRet;	
}

void stt_mqtt_cmd_info::Clear()
{
    m_nUse = 0;
    m_pMqttClient = NULL;
    m_pSttMqttOverTimeMsgRcv = NULL;
}

///////////////////////////////////////////////

CSttMqttOverTimeTool* CSttMqttOverTimeTool::g_pSttMqttOverTimeTool = NULL;
long CSttMqttOverTimeTool::g_nSttMqttOverTimeToolRef = 0;


CSttMqttOverTimeTool::CSttMqttOverTimeTool()
{
	m_pSttMqttOverTimeMsgRcv = NULL;
	memset(m_arrHasSendCmd,0,sizeof(STT_MQTT_CMD_INFO)*STT_MQTT_CMD_INFO_MAX_COUNT);
	m_nMaxIndex = 0;
}

CSttMqttOverTimeTool::~CSttMqttOverTimeTool()
{
	
}

CSttMqttOverTimeTool *CSttMqttOverTimeTool::Create()
{
	g_nSttMqttOverTimeToolRef++;

	if (g_nSttMqttOverTimeToolRef == 1)
	{
		g_pSttMqttOverTimeTool = new CSttMqttOverTimeTool();

#ifdef _PSX_QT_LINUX_
        pthread_t id1;
        pthread_create(&id1,NULL,ProcessTimeOutProc,NULL ); //创建线程
#else
		HANDLE handle =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ProcessTimeOutProc,NULL,0,NULL);
		CloseHandle(handle);
 //       AfxBeginThread(ProcessTimeOutProc,NULL);
#endif
 			
	}

	return g_pSttMqttOverTimeTool;
}

void CSttMqttOverTimeTool::Release()
{
	g_nSttMqttOverTimeToolRef--;

	if (g_nSttMqttOverTimeToolRef == 0)
	{
		delete g_pSttMqttOverTimeTool;
		g_pSttMqttOverTimeTool = NULL;
	}
}

CSttMqttOverTimeTool *CSttMqttOverTimeTool::GetSttMqttOverTimeTool()
{
	return g_pSttMqttOverTimeTool;
}

void CSttMqttOverTimeTool::AttachCmdOverTimeMsgRcv(CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv)
{
	g_pSttMqttOverTimeTool->m_pSttMqttOverTimeMsgRcv = pSttMqttOverTimeMsgRcv;
}

void CSttMqttOverTimeTool::Clear(LPVOID pMqttClient)
{
   STT_MQTT_CMD_INFO *p = NULL;
    int i = 0;

    for (i=0; i<=g_pSttMqttOverTimeTool->m_nMaxIndex; i++)
    {
        p = &g_pSttMqttOverTimeTool->m_arrHasSendCmd[i];

        if(p->m_pMqttClient == pMqttClient)
            p->Clear();
    }
}

STT_MQTT_CMD_INFO* CSttMqttOverTimeTool::GetCmdEmptyInfo()
{
	STT_MQTT_CMD_INFO *pFind = NULL;
	STT_MQTT_CMD_INFO *p = NULL;
	int i = 0;

	for (i=0; i<STT_MQTT_CMD_INFO_MAX_COUNT; i++)
	{
		p = &m_arrHasSendCmd[i];

		if (!p->IsUsed())
		{
			pFind = p;
			break;
		}
	}

	if (m_nMaxIndex < i)
	{
		m_nMaxIndex = i;
	}

// 	if (pFind == NULL)
// 	{
// 		long nSize = sizeof(STT_MQTT_CMD_INFO);
// 		long nNewLen = m_nMaxIndex + STT_MQTT_CMD_INFO_EXPAND_COUNT;
// 		STT_MQTT_CMD_INFO *Temp = new STT_MQTT_CMD_INFO[nNewLen];
// 		memset(Temp,0,nNewLen * nSize);
// 
// 		memcpy(Temp,m_pArrHasSendCmd,m_nMaxIndex * nSize);
// 		delete m_pArrHasSendCmd;
// 		m_pArrHasSendCmd = Temp;
// 
// 		pFind = &m_pArrHasSendCmd[m_nMaxIndex];
// 		m_nMaxIndex = nNewLen;
// 	}

	if (pFind != NULL)
	{
		pFind->m_nUse = TRUE;
	}
	
	return pFind;
}

long CSttMqttOverTimeTool::ProcessTimeOut(DWORD dwCurTime)
{
	long nTimeOutCnt = 0;

	for (int i=0; i<=g_pSttMqttOverTimeTool->m_nMaxIndex; i++)
	{
		if (g_pSttMqttOverTimeTool->m_arrHasSendCmd[i].CheckTimeOut(dwCurTime))
		{
			nTimeOutCnt++;
		}
	}

	return nTimeOutCnt;
}

STT_MQTT_CMD_INFO *CSttMqttOverTimeTool::AddSttMqtt(void *pMqttClient, DWORD nCmdType
					, char *pszMqttTopic, DWORD dwCurrTime, long dwCmdTimeout, CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv, long nSendMode)
{
	ASSERT(pMqttClient != NULL);

	//找到未用缓存，并设置已用标记
	STT_MQTT_CMD_INFO *pFind = g_pSttMqttOverTimeTool->GetCmdEmptyInfo();
	ASSERT(pFind != NULL);

	pFind->m_pMqttClient = (LPVOID)pMqttClient;
	pFind->m_nCmdType = nCmdType;

#ifndef _PSX_QT_LINUX_
	pFind->m_dwBeginCmdTime = dwCurrTime;
	pFind->m_dwCmdSendTime = dwCurrTime;
#else
	pFind->m_dwBeginCmdTime = 0;
	pFind->m_dwCmdSendTime = 0;
#endif

	pFind->m_dwCmdTimeout = dwCmdTimeout;
	pFind->m_nMode = nSendMode;

	if (pSttMqttOverTimeMsgRcv == NULL)
	{
		pFind->m_pSttMqttOverTimeMsgRcv = g_pSttMqttOverTimeTool->m_pSttMqttOverTimeMsgRcv;
	}
	else
	{
		pFind->m_pSttMqttOverTimeMsgRcv = pSttMqttOverTimeMsgRcv;
	}

	pFind->m_nCmdExecState = STT_MQTT_CMD_ExecStatus_NULL;
	//pSysState统一在收到应答后，更新前删除，和最后析构删除
//	pFind->pSysState = NULL;

	memset(pFind->m_pszMqttTopic,0,32);
	if (pszMqttTopic != NULL)
	{
		strcpy(pFind->m_pszMqttTopic,pszMqttTopic);
	}

	return pFind;
}

STT_MQTT_CMD_INFO *CSttMqttOverTimeTool::AddSttMqtt(void *pMqttClient, DWORD nCmdType
			   , const CString &strCmdID, DWORD dwCurrTime, long dwCmdTimeout, CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv, long nSendMode)
{
	char pszMqttTopic[64] = {0};
	CString_to_char(strCmdID,pszMqttTopic);

	return AddSttMqtt(pMqttClient, nCmdType, pszMqttTopic, dwCurrTime, dwCmdTimeout, pSttMqttOverTimeMsgRcv,nSendMode);
}

long CSttMqttOverTimeTool::OnSocketClosed(void *pMqttClient)
{
	if (g_pSttMqttOverTimeTool == NULL)
	{
		return 0;
	}

	STT_MQTT_CMD_INFO *p = NULL;
	for (int i=0; i<=g_pSttMqttOverTimeTool->m_nMaxIndex; i++)
	{
		p = &g_pSttMqttOverTimeTool->m_arrHasSendCmd[i];

		if (p->m_pMqttClient == pMqttClient)
		{
			p->m_pMqttClient = NULL;
			continue;
		}
	}

	return 0;
}

BOOL Stt_Is_ExecStatus_NULL(long nExecStatus)
{
	return (nExecStatus == STT_MQTT_CMD_ExecStatus_NULL);
}

BOOL Stt_Is_ExecStatus_Ack(long nExecStatus)
{
	return (nExecStatus == STT_MQTT_CMD_ExecStatus_ACK);
}

BOOL Stt_Is_ExecStatus_Failure(long nExecStatus)
{
	return (nExecStatus == STT_MQTT_CMD_ExecStatus_FAILURE);
}

BOOL Stt_Is_ExecStatus_Success(long nExecStatus)
{
	return (nExecStatus == STT_MQTT_CMD_ExecStatus_SUCCESS);
}

BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus)
{
	return (nExecStatus == STT_MQTT_CMD_ExecStatus_TIMEOUT);
}

void *ProcessTimeOutProc(LPVOID lParam)
{
	long g_nTickCountLong = 0;

	while(TRUE)
	{
		if (CSttMqttOverTimeTool::GetSttMqttOverTimeTool() == NULL)
		{
			break;
		}

		CSttMqttOverTimeTool::ProcessTimeOut(g_nTickCountLong);

		Sleep(10);
		g_nTickCountLong += 10;

		if (g_nTickCountLong < 0)
		{
			g_nTickCountLong = 0;
		}
	}

	return (void *)0;
}
