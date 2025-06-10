#include "stdafx.h"
#include "SttSocketDataBase.h"
#include "../../Module/API/FileApi.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../Engine/SttTestEngineBase.h"
#include "../SttCmdToolMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttSocketDataBase::CSttSocketDataBase()
{
	m_nIDTester = 0;
	m_nSocketType = 0;

	m_pTestEngine = NULL;
	m_pUser = NULL;
	m_nSttCmdDataFormat = _PUGI_XML_TYPE_;
}

CSttSocketDataBase::~CSttSocketDataBase()
{
}

DWORD CSttSocketDataBase::GetIDTest()
{
	return m_nIDTester;
}

BOOL CSttSocketDataBase::ProcessRecvPacket(BYTE *pBuf,long nLen)
{
	if (CSttSocketDataBase_File::ProcessRecvPacket(pBuf, nLen))
	{
		return TRUE;
	}

	if (m_pTestEngine == NULL)//20220621 zhouhj 防止未绑定engine导致崩溃,或者连接成功后到执行绑定函数之间出现问题
	{
		return FALSE;
	}

	return m_pTestEngine->OnTestMsg(this, pBuf, nLen);
}

//发送命令之前先生成报文头
long CSttSocketDataBase::SendCmd(CSttCmdBase *pCmd,BOOL bCompress,BOOL bReset)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	pCmd->m_nIDTester = GetIDTest();
	stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pCmd,bCompress, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase::SendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents,BOOL bCompress,BOOL bReset)
{
	long nExecStatus = 0;

	//命令发送之前添加到超时链表
	STT_CMD_INFO *pCmdInfo = CSttCmdOverTimeTool::AddSttCmd(this,pCmd->m_nType_Cmd,pCmd->m_strID,0, 0, NULL,STT_CMD_Send_Sync);
	if (pCmdInfo == NULL)
	{
		return nExecStatus;
	}

	long nRet = SendCmd(pCmd,bCompress,bReset);

	if (nRet > 0)
	{
		nExecStatus = pCmd->DoWait(this,pCmdInfo,nTimeOut,pRetData,bDoEvents);
	}
	else
	{
		pCmdInfo->SetUsed(0);//发送失败删除超时链表
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Send cmd %s  failed"), pCmd->m_strID.GetString());
	}

	return nExecStatus;
}

long CSttSocketDataBase::SendCmdAsync(CSttCmdBase *pCmd,long nTimeOut, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv,BOOL bCompress,BOOL bReset)
{
	CSttCmdOverTimeTool::AddSttCmd(this,pCmd->m_nType_Cmd,pCmd->m_strID
								   ,GetTickCount(), nTimeOut, pSttCmdOverTimeMsgRcv,STT_CMD_Send_Async);

	return SendCmd(pCmd,bCompress,bReset);
}

long CSttSocketDataBase::SendCmdEx(CSttCmdBase *pCmd,long nSrcID)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	if (nSrcID != 0)
	{
		pCmd->m_nIDTester = nSrcID;
	}
	else
	{
		pCmd->m_nIDTester = GetIDTest();
	}
	
	stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pCmd,0, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

//发送命令之前先生成报文头
long CSttSocketDataBase::SendSysState(CSttSysState *pSysState)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase::SendSysStateEx(CSttSysState *pSysState,long nDstID)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	pSysState->m_nIDTester = nDstID;
	stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase::SendHeartbeatCmd()
{
	//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("发送心跳报文"));
	BYTE pSendBuf[STT_PKG_HEAD_LEN];
	long nSendBufLen = 0;

	stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_HEARTBEAT, 0, GetIDTest(), 0, 0);

	return SendBuffer(pSendBuf,STT_PKG_HEAD_LEN);
}

long CSttSocketDataBase::RetFailureSysState(CSttCmdBase *pCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pCmd);
	oSysState.Set_ExecStatus_Failure();

	return SendSysState(&oSysState);
}

BOOL CSttSocketDataBase::ProcessCmd_System_DownFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

BOOL CSttSocketDataBase::ProcessCmd_System_CreateFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

BOOL CSttSocketDataBase::ProcessCmd_System_DeleteFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

long CSttSocketDataBase::ProcessCmd_System_DeleteFile(CSttSystemCmd &oSysCmd)
{
	CString strLocalFile;
	long nRet = -1;
	BOOL bRet = FALSE;

	oSysCmd.GetParasDataValueByID(STT_CMD_PARA_FILE_PATH, strLocalFile);
	ASSERT(!strLocalFile.IsEmpty());

	bRet = X_DeleteFile(strLocalFile);

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oSysCmd);

	oSysState.AddNewParasData(STT_CMD_PARA_FILE_PERMISSION, 1);

	if (bRet)
	{
		oSysState.AddNewParasData(STT_CMD_PARA_FILE_STATE, 0);
	}
	else
	{
		oSysState.AddNewParasData(STT_CMD_PARA_FILE_STATE, STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED);
	}
	
	return SendSysState(&oSysState);
}

bool CSttSocketDataBase::Match_IdSoft(const CString &strIdSoft)
{
	if (m_pUser == NULL)
	{
		return false;
	}

	return strIdSoft == m_pUser->id_soft() ;
}

//////////////////////////////////////////////////////////////////////////

long Stt_ToRetCmdType(char *pszRetCmdID)
{
	long nRet = 0;

	if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_SYSTEM) == 0)
	{
		nRet = STT_CMD_TYPE_SYSTEM;
	}
	else if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_TEST) == 0)
	{
		nRet = STT_CMD_TYPE_TEST;
	}
	else if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_DEBUG) == 0)
	{
		nRet = STT_CMD_TYPE_DEBUG;
	}
	else if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_REMOTE) == 0)
	{
		nRet = STT_CMD_TYPE_REMOTE;
	}
	else if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_ATS) == 0)
	{
		nRet = STT_CMD_TYPE_ATS;
	}
	else if (strcmp(pszRetCmdID,STT_CMD_SYSSTATE_ASSIST) == 0)
	{
		nRet = STT_CMD_TYPE_ASSIST;
	}

	return nRet;
}

BOOL stt_pkg_get_cmd_id(char *pPkgBuf,long nPktLen,long &nCmdType,char *pszCmdID,char *pszTestor, char *pszRetCmdType)
{
	ASSERT(pszCmdID != NULL);
	ASSERT(pszTestor != NULL);

	nCmdType = stt_pkg_get_cmd_type((BYTE *)pPkgBuf);
	if ((nCmdType == STT_CMD_TYPE_HEARTBEAT)
			|| (nCmdType == STT_CMD_TYPE_COMTRADE)
			|| (nCmdType == STT_CMD_TYPE_TRIGGER)
			|| (stt_is_cmd_a_file_cmd(nCmdType))
			|| ((nCmdType > STT_CMD_TYPE_BINARY) && (nCmdType <= STT_CMD_TYPE_BINARY + STT_CMD_TYPE_SYSSTATE)))
	{
		return TRUE;
	}

	char *pCmdData = NULL;
	long nCmdLen = 0;

	BOOL bRet = stt_pkg_get_cmddata(pPkgBuf,nPktLen,pCmdData,nCmdLen);
	if (!bRet)
	{
		return FALSE;
	}

	if (!stt_cmd_get_key_value(pCmdData,nCmdLen,"id",pszCmdID))
	{
		return FALSE;
	}

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{//应答命令

		BOOL b1 = stt_cmd_get_key_value(pCmdData,nCmdLen, STT_SYSSTATE_TESTOR, pszTestor);
		BOOL b2 = stt_cmd_get_key_value(pCmdData,nCmdLen, STT_SYSSTATE_RET_CMDTYPE, pszRetCmdType);

		return b1 && b2;
	}

	return stt_cmd_get_key_value(pCmdData,nCmdLen,STT_CMD_TESTOR,pszTestor);
}

void stt_InitSendBuf_Cmd(BYTE **ppszSendBuf,long &nSendBufLen, CSttCmdBase *pCmd, BOOL bCompress, long nSttCmdDataFormat)
{//发送序列号暂不考虑
	pCmd->GetXml_Pkg((char**)ppszSendBuf, nSendBufLen, nSttCmdDataFormat);

	if (bCompress)
	{//如果压缩，更新缓存和长度

	}

	stt_InitPktBuffer_Head((BYTE*)*ppszSendBuf,
						   pCmd->GetCmdType(), nSendBufLen - STT_PKG_HEAD_LEN,
						   pCmd->m_nIDTester, pCmd->m_nPkgSendIndex, bCompress);
}

void stt_InitRetSendBuf(BYTE **ppszSendBuf,long &nSendBufLen,CSttSysState *pSysState, BOOL bCompress, long nSttCmdDataFormat)
{
	pSysState->GetXml_Pkg((char**)ppszSendBuf, nSendBufLen, nSttCmdDataFormat);

	if(*ppszSendBuf!=NULL)
		stt_InitPktBuffer_Head((BYTE*)*ppszSendBuf,
							   STT_CMD_TYPE_SYSSTATE, nSendBufLen - STT_PKG_HEAD_LEN
							   , pSysState->m_nIDTester, pSysState->m_nPkgSendIndex, bCompress);
}
