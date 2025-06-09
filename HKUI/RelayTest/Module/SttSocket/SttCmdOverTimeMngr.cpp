#include "stdafx.h"
#include "SttCmdOverTimeMngr.h"
#include "../SttGlobalDef.h"
#include "../../../Module/System/TickCount32.h"
#include "../Engine/SttTestEngineBase.h"
#ifdef _STT_NOT_IN_TEST_SERVER_
#include "../Engine/SttTestEngineClientData.h"
#endif

#include "SttSocketDataBase_File.h"

//2020-5-27
//调试的时候，是否需要判断超时，内存中将变量的值修改为0即可
long g_nSttCmdOverTimeEnable = 1;

long g_nSttCmdOverTimeViewLog = 0;

#ifdef _PSX_QT_LINUX_
         #include <pthread.h> //线程头文件
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////
void stt_cmd_info::OnSendCmdFinish(BOOL bSuccess)
{
	if (pSttCmdOverTimeMsgRcv != NULL)
	{
		if (bSuccess)
		{
			pSttCmdOverTimeMsgRcv->OnSendCmdFinish(pSocketRef, nCmdType, pszCmdID);
		}
		else
		{
			pSttCmdOverTimeMsgRcv->OnSendCmdFailFinish(pSocketRef, nCmdType, pszCmdID);
		}	
	}

	m_nUse = FALSE;
}

#if !defined(_OA_MNGR_CLIENT) && !defined(_STT_FTP_SVR_)
void stt_cmd_info::OnSendCmdStatusChanged(long nExecState,CExBaseList *pSysState2)
{
	if (pSysState != NULL)
	{
		delete pSysState;
	}

	pSysState = new CSttCmdData;
	pSysState->AppendEx(*pSysState2);
	pSysState2->RemoveAll();

/*
	if(nExecState == STT_CMD_ExecStatus_ACK)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s Cmd :  Ack"),pszCmdID);
	}
	else if(nExecState == STT_CMD_ExecStatus_FAILURE)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s Cmd :  Failure"),pszCmdID);
	}
	else if(nExecState == STT_CMD_ExecStatus_SUCCESS)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s Cmd :  Success"),pszCmdID);
	}
*/

	if (nMode == STT_CMD_Send_Async)
	{//只有异步发送命令，直接删除队列
		m_nCmdExecState = nExecState;

		if (IsCmdExecState_Success())
		{
			OnSendCmdFinish(TRUE);
		}
		else if (IsCmdExecState_Failure() )
		{
			OnSendCmdFinish(FALSE);
		}
	}
	else
	{//如果是同步命令发送，需在DoWait中删除队列
		//必须放到最后赋值

		m_nCmdExecState = nExecState;

		if (g_nSttCmdOverTimeViewLog == 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s ExecState = %d"), pszCmdID, nExecState);
		}
	}
}
#endif

BOOL stt_cmd_info::CheckTimeOut(DWORD dwCurTime)
{
	BOOL bRet = FALSE;

	if (!IsUsed())
	{
		return bRet;
	}

	//文件命令才在线程中判超时
	//其他命令在DoWait中判超时
	if (!stt_is_cmd_a_file_cmd(nCmdType))
	{
		return bRet;
	}

	if (g_nSttCmdOverTimeEnable)
	{
		bRet = IsTimeOut(dwCurTime);
	}

	if (bRet)
	{
//		long nVal = ((CSttXcmdChInterface *)pSocketRef)->m_oExpandRecvBuf.GetDataLength();
		
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("命令超时：【%d,%d】【%s】%d"),nCmdType,nMode,pszCmdID,nVal);
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Command[%d,%d][%s]"),nCmdType,nMode,pszCmdID);

		if (pSttCmdOverTimeMsgRcv != NULL)
		{
			pSttCmdOverTimeMsgRcv->OnSendCmdOverTime(pSocketRef, nCmdType, pszCmdID);
		}

		m_nUse = FALSE;
	}

	return bRet;	
}

void stt_cmd_info::Clear()
{
    m_nUse = 0;
    pSocketRef = NULL;
    pSttCmdOverTimeMsgRcv = NULL;
}

///////////////////////////////////////////////

CSttCmdOverTimeTool* CSttCmdOverTimeTool::g_pSttCmdOverTimeTool = NULL;
long CSttCmdOverTimeTool::g_nSttCmdOverTimeToolRef = 0;


CSttCmdOverTimeTool::CSttCmdOverTimeTool()
{
	m_pSttCmdOverTimeMsgRcv = NULL;
	memset(m_arrHasSendCmd,0,sizeof(STT_CMD_INFO)*STT_CMD_INFO_MAX_COUNT);
	m_nMaxIndex = 0;
}

CSttCmdOverTimeTool::~CSttCmdOverTimeTool()
{
	for (int nIndex=0; nIndex<STT_CMD_INFO_MAX_COUNT; nIndex++)
	{
		if (m_arrHasSendCmd[nIndex].pSysState != NULL)
		{
			delete m_arrHasSendCmd[nIndex].pSysState;
			m_arrHasSendCmd[nIndex].pSysState = NULL;
		}
	}
}

CSttCmdOverTimeTool *CSttCmdOverTimeTool::Create()
{
	g_nSttCmdOverTimeToolRef++;

	if (g_nSttCmdOverTimeToolRef == 1)
	{
		g_pSttCmdOverTimeTool = new CSttCmdOverTimeTool();

#ifdef _PSX_QT_LINUX_
        pthread_t id1;
        pthread_create(&id1,NULL,ProcessTimeOutProc,NULL ); //创建线程
#else
		HANDLE handle =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ProcessTimeOutProc,NULL,0,NULL);
		CloseHandle(handle);
 //       AfxBeginThread(ProcessTimeOutProc,NULL);
#endif
 			
	}

	return g_pSttCmdOverTimeTool;
}

void CSttCmdOverTimeTool::Release()
{
	g_nSttCmdOverTimeToolRef--;

	if (g_nSttCmdOverTimeToolRef == 0)
	{
		delete g_pSttCmdOverTimeTool;
		g_pSttCmdOverTimeTool = NULL;
	}
}

CSttCmdOverTimeTool *CSttCmdOverTimeTool::GetSttCmdOverTimeTool()
{
	return g_pSttCmdOverTimeTool;
}

void CSttCmdOverTimeTool::AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv)
{
	g_pSttCmdOverTimeTool->m_pSttCmdOverTimeMsgRcv = pSttCmdOverTimeMsgRcv;
}

void CSttCmdOverTimeTool::Clear(void *pSocket)
{
#ifndef _SttCmdOverTimeTool_No_Critical_
    CAutoSimpleLock oLock(g_pSttCmdOverTimeTool->m_oCriticSection);
#endif
   STT_CMD_INFO *p = NULL;
    int i = 0;
   // p = g_pSttCmdOverTimeTool->m_arrHasSendCmd;

    for (i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
    {
        p = &g_pSttCmdOverTimeTool->m_arrHasSendCmd[i];

        if(p->pSocketRef == pSocket)
            p->Clear();
//        p->Clear();
//        p++;
    }
}

void CSttCmdOverTimeTool::Clear(CSttTestEngineClientData *pEngineClient)
{
	if (pEngineClient == NULL)
	{
		return;
	}
#ifdef _STT_NOT_IN_TEST_SERVER_
	Clear(pEngineClient->m_pSttClientSocket);
#endif
}

STT_CMD_INFO* CSttCmdOverTimeTool::GetCmdEmptyInfo()
{
	STT_CMD_INFO *pFind = NULL;
	STT_CMD_INFO *p = NULL;
	int i = 0;

	for (i=0; i<STT_CMD_INFO_MAX_COUNT; i++)
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
// 		long nSize = sizeof(STT_CMD_INFO);
// 		long nNewLen = m_nMaxIndex + STT_CMD_INFO_EXPAND_COUNT;
// 		STT_CMD_INFO *Temp = new STT_CMD_INFO[nNewLen];
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

BOOL CSttCmdOverTimeTool::In_HasCmdUsing()
{
	STT_CMD_INFO *p = NULL;
	int i = 0;
	BOOL bIsUsing = FALSE;

	for (i=0; i<STT_CMD_INFO_MAX_COUNT; i++)
	{
		p = &m_arrHasSendCmd[i];

		if (p->IsUsed())
		{
			bIsUsing = TRUE;
			break;
		}
	}

	return bIsUsing;
}

long CSttCmdOverTimeTool::ProcessTimeOut(DWORD dwCurTime)
{
	long nTimeOutCnt = 0;

	for (int i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
	{
		if (g_pSttCmdOverTimeTool->m_arrHasSendCmd[i].CheckTimeOut(dwCurTime))
		{
			nTimeOutCnt++;
		}
	}

	return nTimeOutCnt;
}

STT_CMD_INFO *CSttCmdOverTimeTool::AddSttFileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
							, DWORD dwCurrTime, long dwCmdTimeout, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv)
{
	ASSERT(pSocket != NULL);

#ifndef _SttCmdOverTimeTool_No_Critical_
	CAutoSimpleLock oLock(g_pSttCmdOverTimeTool->m_oCriticSection);
#endif

	//找到未用缓存，并设置已用标记
	STT_CMD_INFO *pFind = g_pSttCmdOverTimeTool->GetCmdEmptyInfo();
	ASSERT(pFind != NULL);

	pFind->pSocketRef = (LPVOID)pSocket;
	pFind->nCmdType = nCmdType;

#ifndef _PSX_QT_LINUX_
	pFind->dwBeginCmdTime = dwCurrTime;
	pFind->dwCmdSendTime = dwCurrTime;
#else
	pFind->dwBeginCmdTime = 0;
	pFind->dwCmdSendTime = 0;
#endif

	pFind->dwCmdTimeout = dwCmdTimeout;

	if (pSttCmdOverTimeMsgRcv == NULL)
	{
		pFind->pSttCmdOverTimeMsgRcv = g_pSttCmdOverTimeTool->m_pSttCmdOverTimeMsgRcv;
	}
	else
	{
		pFind->pSttCmdOverTimeMsgRcv = pSttCmdOverTimeMsgRcv;
	}

	pFind->m_nCmdExecState = STT_CMD_ExecStatus_NULL;
	//pSysState统一在收到应答后，更新前删除，和最后析构删除
//	pFind->pSysState = NULL;
	memset(pFind->pszCmdID,0,32);

	return pFind;
}

STT_CMD_INFO *CSttCmdOverTimeTool::AddSttCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
					, char *pszCmdID, DWORD dwCurrTime, long dwCmdTimeout, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv, long nSendMode)
{
	ASSERT(pSocket != NULL);


#ifndef _SttCmdOverTimeTool_No_Critical_
	CAutoSimpleLock oLock(g_pSttCmdOverTimeTool->m_oCriticSection);
#endif

	//找到未用缓存，并设置已用标记
	STT_CMD_INFO *pFind = g_pSttCmdOverTimeTool->GetCmdEmptyInfo();
	ASSERT(pFind != NULL);

	if (pFind == NULL)
	{
		return NULL;
	}

	pFind->pSocketRef = (LPVOID)pSocket;
	pFind->nCmdType = nCmdType;

#ifndef _PSX_QT_LINUX_
	pFind->dwBeginCmdTime = dwCurrTime;
	pFind->dwCmdSendTime = dwCurrTime;
#else
	pFind->dwBeginCmdTime = 0;
	pFind->dwCmdSendTime = 0;
#endif

	pFind->dwCmdTimeout = dwCmdTimeout;
	pFind->nMode = nSendMode;

	if (pSttCmdOverTimeMsgRcv == NULL)
	{
		pFind->pSttCmdOverTimeMsgRcv = g_pSttCmdOverTimeTool->m_pSttCmdOverTimeMsgRcv;
	}
	else
	{
		pFind->pSttCmdOverTimeMsgRcv = pSttCmdOverTimeMsgRcv;
	}

	pFind->m_nCmdExecState = STT_CMD_ExecStatus_NULL;
	//pSysState统一在收到应答后，更新前删除，和最后析构删除
//	pFind->pSysState = NULL;

	memset(pFind->pszCmdID,0,32);
	if (pszCmdID != NULL)
	{
		strcpy(pFind->pszCmdID,pszCmdID);
	}

	return pFind;
}

STT_CMD_INFO *CSttCmdOverTimeTool::AddSttCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
			   , const CString &strCmdID, DWORD dwCurrTime, long dwCmdTimeout, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv, long nSendMode)
{
	char pszCmdID[64] = {0};
	CString_to_char(strCmdID,pszCmdID);

	return AddSttCmd(pSocket, nCmdType, pszCmdID, dwCurrTime, dwCmdTimeout, pSttCmdOverTimeMsgRcv,nSendMode);
}

long CSttCmdOverTimeTool::OnSocketReceive_FileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
					, DWORD nCmdPara, DWORD dwCurrTime)
{
	STT_CMD_INFO *p = NULL;
	for (int i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
	{
		p = &g_pSttCmdOverTimeTool->m_arrHasSendCmd[i];

		if (!p->IsUsed())
		{
			continue;
		}

		if (p->pSocketRef != pSocket)
		{
			continue;
		}

		if (!stt_is_cmd_a_file_cmd(p->nCmdType))
		{
			continue;
		}

		switch (p->nCmdType)
		{
		case STT_CMD_TYPE_FILE_WRITE:
		case STT_CMD_TYPE_FILE_READ:
			{
				ASSERT(nCmdType == STT_CMD_TYPE_FILE_WRITE);

				p->nMode = nCmdPara;

#ifndef _PSX_QT_LINUX_
				p->dwCmdSendTime = dwCurrTime;
#else
				p->dwCmdSendTime = 0;
#endif
				if (nCmdPara == STT_FILEMODE_LASTFRAME)
				{
					p->OnSendCmdFinish(TRUE);
				}
				return 1;
			}
		case STT_CMD_TYPE_FILE_DELETE:
		case STT_CMD_TYPE_FILE_RENAME:
		case STT_CMD_TYPE_FILE_GETDIR:
		case STT_CMD_TYPE_FILE_MOVE:
			{
				if (nCmdType == p->nCmdType)
				{
					p->OnSendCmdFinish(TRUE);
					return 1;
				}
				break;
			}
		default:	
			break;
		}	
	}

	return 0;
}

long CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
								, DWORD nCmdPara, DWORD dwCurrTime)
{
	STT_CMD_INFO *p = NULL;
	for (int i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
	{
		p = &g_pSttCmdOverTimeTool->m_arrHasSendCmd[i];

		if (!p->IsUsed())
		{
			continue;
		}

		if (p->pSocketRef != pSocket)
		{
			continue;
		}

		if (!stt_is_cmd_a_file_cmd(p->nCmdType))
		{
			continue;
		}

		switch (p->nCmdType)
		{
		case STT_CMD_TYPE_FILE_WRITE:
		case STT_CMD_TYPE_FILE_READ:
			{
				ASSERT(nCmdType == STT_CMD_TYPE_FILE_WRITE);

				p->nMode = nCmdPara;

#ifndef _PSX_QT_LINUX_
				p->dwCmdSendTime = dwCurrTime;
#else
				p->dwCmdSendTime = 0;
#endif
				if (stt_is_ret_file_cmd_fail(nCmdPara))
				{
					p->OnSendCmdFinish(FALSE);
				}
				return 1;
			}
		case STT_CMD_TYPE_FILE_DELETE:
		case STT_CMD_TYPE_FILE_RENAME:
		case STT_CMD_TYPE_FILE_GETDIR:
		case STT_CMD_TYPE_FILE_MOVE:
			{
				if (nCmdType == p->nCmdType)
				{
					p->OnSendCmdFinish(FALSE);
					return 1;
				}
				break;
			}
		default:	
			break;
		}	
	}

	return 0;
}

long CSttCmdOverTimeTool::OnSocketClosed(void *pSocket)
{
	if (g_pSttCmdOverTimeTool == NULL)
	{
		return 0;
	}

	STT_CMD_INFO *p = NULL;
	for (int i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
	{
		p = &g_pSttCmdOverTimeTool->m_arrHasSendCmd[i];

		if (p->pSocketRef == pSocket)
		{
			p->pSocketRef = NULL;
			continue;
		}
	}

	return 0;
}

BOOL CSttCmdOverTimeTool::HasCmdUsing()
{
	if (g_pSttCmdOverTimeTool == NULL)
	{
		return FALSE;
	}

	return g_pSttCmdOverTimeTool->In_HasCmdUsing();
}

#if !defined(_OA_MNGR_CLIENT) && !defined(_STT_FTP_SVR_)
long CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(CSttXcmdChInterface *pSocket, CSttSysState &oSysState,long nExecStatus)
{
	STT_CMD_INFO *p = NULL;
	char pszCmdID[64] = {0};
	CString_to_char(oSysState.m_strID,pszCmdID);

	for (int i=0; i<=g_pSttCmdOverTimeTool->m_nMaxIndex; i++)
	{
		p = &g_pSttCmdOverTimeTool->m_arrHasSendCmd[i];

		if (!p->IsUsed())
		{
			continue;
		}

		if (p->pSocketRef != pSocket)
		{
			continue;
		}

		if (stt_is_cmd_a_file_cmd(p->nCmdType))
		{
			continue;
		}

		if (strcmp(pszCmdID,p->pszCmdID) == 0)
		{//命令一致
			if ((strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Register) == 0)
				|| (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_UnRegister) == 0)
				|| (strcmp(pszCmdID,STT_CMD_TYPE_SYSTEM_Login) == 0)
				|| (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Bind) == 0)
				|| (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Query) == 0))
			{
				p->OnSendCmdStatusChanged(nExecStatus,&oSysState);
				return 1;
			}

			if ((oSysState.m_nIDTester != 0) && (oSysState.m_nIDTester == ((CSttXcmdChInterface*)pSocket)->GetIDTest()))
			{
				p->OnSendCmdStatusChanged(nExecStatus,&oSysState);
				return 1;
			}	
			else
			{
				if (g_nSttCmdOverTimeViewLog == 1)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error: (%s) oSysState.m_nIDTester(%d) != SocketID(%d)")
						, pszCmdID,oSysState.m_nIDTester, ((CSttXcmdChInterface*)pSocket)->GetIDTest());
				}
			}
		}
	}

	return 0;
}
#endif

void *ProcessTimeOutProc(LPVOID lParam)
{
	long g_nTickCountLong = 0;

	while(TRUE)
	{
		if (CSttCmdOverTimeTool::GetSttCmdOverTimeTool() == NULL)
		{
			break;
		}

		CSttCmdOverTimeTool::ProcessTimeOut(g_nTickCountLong);

        Sleep(10);
		g_nTickCountLong += 10;

		if (g_nTickCountLong < 0)
		{
			g_nTickCountLong = 0;
		}
	}

	return (void *)0;
}

unsigned int g_nTimeOutTickCount = 0;
void CSttCmdOverTimeTool::ProcessTimeOutProc_Attach()
{
	if (CSttCmdOverTimeTool::GetSttCmdOverTimeTool() == NULL)
	{
		return;
	}

	CSttCmdOverTimeTool::ProcessTimeOut(g_nTimeOutTickCount);
	g_nTimeOutTickCount += 50;
}
