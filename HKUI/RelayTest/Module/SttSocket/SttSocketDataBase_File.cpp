#include "stdafx.h"
#include "SttSocketDataBase_File.h"
#include "SttServerSocketDataBase.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "SttCmdOverTimeMngr.h"
#include "../../../Module/System/TickCount32.h"
#include "../SttFileToolMngr.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../../Module/XLanguage/XLanguageResource.h"
#endif

#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Engine/SttTestEngineBase.h"
#include "../SttCmdToolMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef CHECK_HEARTBEAT_TIMEOUT_MODE
long g_nSendHeartbeatTimeGap = 5000;
//long g_nRecvHeartbeatTimeGap = 30000;//2021-8-20  lijunqing  use timer-count
long g_nRecvHeartbeatTimeGap = 30;//2021-8-20  lijunqing  use timer-count
#else
long g_nSendHeartbeatTimeGap = 0;
long g_nRecvHeartbeatTimeGap = 0;
#endif

long g_nFileCmdTimeOut = 10000;
CString g_strFtpRootFile = _T("");

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CString CSttSocketDataBase_File::XGetLocalIP()
{
    char pszIP[24];
    XGetLocalIP(pszIP);
    CString strIP;
    strIP = pszIP;

    return strIP;
}

void CSttSocketDataBase_File::XGetLocalIP(char *pszIP)
{
    get_LocalIP(pszIP);
}

CString CSttSocketDataBase_File::XGetRemoteIP()
{
    return m_strIPRemote;
}

bool  CSttSocketDataBase_File::IsSttXcmdChValid()
{
	return m_hSocket != 0;
}

void CSttSocketDataBase_File::CloseSttXcmdCh()
{
	CloseSocket();
}

CString CSttSocketDataBase_File::SttXmdChAddr()
{
	return m_strIPLocal;
}

bool CSttSocketDataBase_File::XConnectServer(const CString &strIPServer, long nPort)
{
	return ConnectServer(strIPServer, nPort);
}

long CSttSocketDataBase_File::XRecvHeartbeatCounterAdd()
{
	m_nRecvHeartbeatCounter++;
	return m_nRecvHeartbeatCounter;
}

long CSttSocketDataBase_File::XRestartRecvHeartbeatTickCount()
{
	RestartRecvHeartbeatTickCount();
	return m_nRecvHeartbeatCounter;
}

void CSttSocketDataBase_File::SttXmdChAddr(const CString &strAddr)
{
	m_strIPLocal = strAddr;
}

BOOL CSttSocketDataBase_File::ProcessRecvPacket(BYTE *pBuf,long nLen)
{
	if (CSttSocketDataBase_File::ProcessRecvPacket_File(pBuf, nLen))
	{
		return TRUE;
	}

	if (m_pTestEngine == NULL)//20220621 zhouhj 防止未绑定engine导致崩溃,或者连接成功后到执行绑定函数之间出现问题
	{
		return FALSE;
	}

	return m_pTestEngine->OnTestMsg(this, pBuf, nLen);
}

long CSttSocketDataBase_File::XSendBuffer(BYTE *pBuf,long nLen)
{
	return SendBuffer(pBuf, nLen);
}

void CSttSocketDataBase_File::XAttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)
{
	AttachCmdOverTimeMsgRcv(pCmdOverTimeMsgRcv);
}

//发送命令之前先生成报文头
long CSttSocketDataBase_File::XSendCmd(CSttCmdBase *pCmd,BOOL bCompress,BOOL bReset)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	pCmd->m_nIDTester = GetIDTest();
	stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pCmd,bCompress, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase_File::XSendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents,BOOL bCompress,BOOL bReset)
{
	long nExecStatus = 0;

	//命令发送之前添加到超时链表
	STT_CMD_INFO *pCmdInfo = CSttCmdOverTimeTool::AddSttCmd(this,pCmd->m_nType_Cmd,pCmd->m_strID,0, 0, NULL,STT_CMD_Send_Sync);
	if (pCmdInfo == NULL)
	{
		return nExecStatus;
	}

	long nRet = XSendCmd(pCmd,bCompress,bReset);

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

long CSttSocketDataBase_File::XSendCmdAsync(CSttCmdBase *pCmd,long nTimeOut, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv,BOOL bCompress,BOOL bReset)
{
	CSttCmdOverTimeTool::AddSttCmd(this,pCmd->m_nType_Cmd,pCmd->m_strID
		,GetTickCount(), nTimeOut, pSttCmdOverTimeMsgRcv,STT_CMD_Send_Async);

	return XSendCmd(pCmd,bCompress,bReset);
}

long CSttSocketDataBase_File::XSendCmdEx(CSttCmdBase *pCmd,long nSrcID)
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
long CSttSocketDataBase_File::XSendSysState(CSttSysState *pSysState)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase_File::XSendSysStateEx(CSttSysState *pSysState,long nDstID)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	pSysState->m_nIDTester = nDstID;
	stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, m_nSttCmdDataFormat);

	long nRet = SendBuffer(pSendBuf,nSendBufLen);
	delete pSendBuf;

	return nRet;
}

long CSttSocketDataBase_File::XSendHeartbeatCmd()
{
	if (m_oSendHeartbeatTick.GetTickCountLong(FALSE) >= g_nSendHeartbeatTimeGap)
	{
		//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("发送心跳报文"));
		BYTE pSendBuf[STT_PKG_HEAD_LEN];
		long nSendBufLen = 0;

		stt_InitPktBuffer_Head(pSendBuf, STT_CMD_TYPE_HEARTBEAT, 0, GetIDTest(), 0, 0);

		return SendBuffer(pSendBuf,STT_PKG_HEAD_LEN);
	}
	else
	{
		return 0;
	}
}

long CSttSocketDataBase_File::XRetFailureSysState(CSttCmdBase *pCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pCmd);
	oSysState.Set_ExecStatus_Failure();

	return XSendSysState(&oSysState);
}

BOOL CSttSocketDataBase_File::ProcessCmd_System_DownFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

BOOL CSttSocketDataBase_File::ProcessCmd_System_CreateFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

BOOL CSttSocketDataBase_File::ProcessCmd_System_DeleteFolder(CSttSystemCmd &oSysCmd)
{
	return TRUE;
}

long CSttSocketDataBase_File::ProcessCmd_System_DeleteFile(CSttSystemCmd &oSysCmd)
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

	return XSendSysState(&oSysState);
}

BOOL CSttSocketDataBase_File::XSttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	return SttSendFiles(oFilesList, nTestID, pProgress);
}

BOOL CSttSocketDataBase_File::XSttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	return XSttSendFile(strLocalFile, strRemoteFile, nTestID, pProgress);
}

BOOL CSttSocketDataBase_File::XSttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	return XSttDownloadFiles(oFilesList, nTestID, pProgress);
}

BOOL CSttSocketDataBase_File::XSttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	return XSttDownloadFile(strLocalFile, strRemoteFile, nTestID, pProgress);
}

void CSttSocketDataBase_File::XSendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer)
{
	SendFile(strLocalFile, strReoteFile, nTimeOut, bServer);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CSttSocketDataBase_File::CSttSocketDataBase_File()
{
	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;
	m_dwSendBeginTime = 0;
	m_pFtpProgress = NULL;
	m_pCmdOverTimeMsgRcv = NULL;

	m_nSendIndex = 0;
	m_nRecvIndex = 0;

	m_nPortLocal = 0;
	m_nPortRemote = 0;

	m_oExpandRecvBuf.AllocBuffer();

	//2021-8-20  lijunqing  use timer-count
	m_nRecvHeartbeatCounter = 0;
}

CSttSocketDataBase_File::~CSttSocketDataBase_File()
{
	CloseFile();
	ResetAfterTransmit();
}

BOOL CSttSocketDataBase_File::ConnectServer()
{
#ifndef _PSX_QT_LINUX_
	InitSocket();
#endif
	SetReceiveBuffLen( STT_FILECMD_MAX_LEN );
	Create(SOCK_STREAM);
	InitSocketClient(20);

	BOOL bRet = Connect(m_strIPRemote.GetString(), m_nPortRemote);
	#ifdef NOT_USE_XLANGUAGE
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接服务器[%s][%d]成功"), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#else
	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ConServerSucc.GetString(), m_strIPRemote.GetString(), m_nPortRemote);
	}
	#endif
	return bRet;
}

BOOL CSttSocketDataBase_File::ConnectServer(const CString &strIPServer,long nPort)
{//本地或远程测试端，连接成功后设置SttLocalTestEngine的RefSocket

	char pszIPServer[64] = {0};
	CString_to_char(strIPServer,pszIPServer);

	m_strIPRemote = strIPServer;
	m_nPortRemote = nPort;

	return ConnectServer();
}

void CSttSocketDataBase_File::CloseFile()
{
	//lijq 2020-03-22  Close函数中，已经对句本的有效性做了判断
#ifdef _PSX_IDE_QT_
	if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
//		CTickCount32 oTick;
		m_oFile.Close();
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("m_oFile.Close[%d]"),oTick.GetTickCountLong());
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oFile.Close"));
	}
}

void CSttSocketDataBase_File::ResetAfterTransmit()
{
	m_strLocalFile.Empty();
	m_strRemoteFile.Empty();
	m_pFtpProgress = NULL;
	m_pCmdOverTimeMsgRcv = NULL;
}

void CSttSocketDataBase_File::ProcessCmd_End()
{
	CloseFile();
	ResetAfterTransmit();
}

/*//2024-7-8  lijunqing
DWORD CSttSocketDataBase_File::GetIDTest()
{
	return 0;
}
*/

void CSttSocketDataBase_File::OnSocketClose(int nErrorCode, BOOL bDeleteSocket)
{
	CSttServerSocketDataBase *pServer = (CSttServerSocketDataBase*)GetParent();

	if (pServer == NULL)
	{
		return;
	}

	pServer->OnSttScktClose(this, bDeleteSocket);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("nErrorCode=%d[CSttSocketDataBase_File::OnSocketClose]"),nErrorCode);
}

void CSttSocketDataBase_File::CloseSocket()
{
	Close();
}

long CSttSocketDataBase_File::SendBuffer(BYTE *pBuf,long nLen)
{
	long nRet = Send((char*)pBuf, nLen);

	if(nRet <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG,_T("+++++++++++SendBuffer failed"));
	}

	//发送数据后重新计时
	RestartSendHeartbeatTickCount();

	return nRet;
}

long CSttSocketDataBase_File::ReceiveBuffer(BYTE *pBuf,long nLen)
{
    return 0;
}

long CSttSocketDataBase_File::SendRetFileCmd(UINT nFileCmd, UINT nMode)
{
	return SendFileCmd(m_chSendFileCmdBuf, nFileCmd, nMode, 0);
}

long CSttSocketDataBase_File::OnReceive(BYTE *pRcvBuf, int iLen)
{
	OnReceiveBuffer(pRcvBuf, iLen);
	return 0;
}

void CSttSocketDataBase_File::OnReceiveBuffer(int nErrorCode)
{

}

void CSttSocketDataBase_File::OnReceiveBuffer(BYTE *pBuf, long nLen)
{
	if (nLen <= 0)
	{
		return;
	}

	//收到数据时重新计时
	RestartRecvHeartbeatTickCount();

	CSttProtocolBufBase::OnReceiveBuffer(pBuf, nLen);
}

long CSttSocketDataBase_File::HasComplatePkg()
{
	BYTE *pTemp = (BYTE *)m_oExpandRecvBuf.GetDataBuffer();
	long nDataLen = m_oExpandRecvBuf.GetDataLength();

	if (nDataLen < STT_PKG_HEAD_LEN)
	{
		return STT_PKG_HEAD_LEN - nDataLen;
	}

	if(!stt_pkg_match_head(pTemp))
	{
		//暂时不处理非法报文
	}

	long nPkgDataLen = stt_pkg_get_data_len(pTemp);
	long nPkgNeedLen = nPkgDataLen + STT_PKG_HEAD_LEN;

	if (nPkgNeedLen > nDataLen)
	{//余下的报文长度不够一个完整的报文
		return nPkgNeedLen - nDataLen;
	}
	else
	{
		return 0;
	}
}

BOOL CSttSocketDataBase_File::ProcessRecvPacket_File(BYTE *pBuf,long nLen)
{
	long nCmdType = 0, nRetCmdType=0;
	nCmdType = stt_pkg_get_cmd_type(pBuf);

	if (stt_is_cmd_a_file_cmd(nCmdType))
	{
		ProcessCmd_File(pBuf, nLen);
		return TRUE;
	}

	return FALSE;
}

long CSttSocketDataBase_File::SendFileCmd(BYTE *pBuf, UINT nFileCmd, UINT nMode, long nLen)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("-----SendFileCmd:nFileCmd[%x],Mode[%x],SendLen[%d]"),nFileCmd,nMode,nLen);
	
	stt_InitPktBuffer_Head_File(pBuf, nFileCmd, nMode, nLen
								, m_nDestID, 0, FALSE);

	return SendBuffer(pBuf, STT_PKG_HEAD_LEN + nLen);
}

long CSttSocketDataBase_File::ProcessCmd_File(BYTE *pBuf,long nLen)
{
	long nDataLen = stt_pkg_get_data_len_cmd_file(pBuf);
	UINT nCmd = stt_pkg_get_cmd_type(pBuf);
	UINT nMode = stt_pkg_get_cmd_file_mode(pBuf);

	//每收到文件命令更新目标连接ID
	m_nDestID = stt_pkg_get_idtester(pBuf);

	CSttCmdOverTimeTool::OnSocketReceive_FileCmd(this, nCmd, nMode, GetTickCount());

	switch (nCmd)
	{
	case STT_CMD_TYPE_FILE_WRITE:
	case STT_CMD_TYPE_FILE_READ:
		ProcessCmd_File_ReadWrite(pBuf, nLen, nCmd, nMode, nDataLen);
		break;
	}
	
	return 1;
}

long CSttSocketDataBase_File::ProcessCmd_File_ReadWrite(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	if (nDataLen > 0)
	{//标识收到文件命令
		//表示此帧传输的是文件名，创建文件
		if (nMode == STT_FILEMODE_FILENAME)
		{
			return ProcessCmd_File_FileName(pBuf, nLen, nFileCmd, nMode, nDataLen);
		}
		else
		{
			return ProcessCmd_File_Data(pBuf, nLen, nMode, nDataLen);
		}
	}
	else
	{//等于0：表示收到文件命令应答
		return ProcessCmd_File_Ret(pBuf, nLen, nFileCmd, nMode);
	}
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	//ReadFile、WriteFile，都是用SendFile来实现文件的发送，两者的区别：
	//1、发送文件（Write）：
	//                                  发起端：m_strLocalFile为发送的本地文件，m_strRemoteFile为接收端文件
	//                                  接收端：m_strLocalFile、m_strRemoteFile都为空，m_strLocalFile为收到文件名称的命令时，设置的值；m_strRemoteFile为空
	//2、下载文件（Read）：
	//                                  发起端：m_strLocalFile为本地目标文件名，m_strRemoteFile为接收端文件名
	//                                  接收端：m_strLocalFile为收到文件名称，之后调用SendFile发送文件
	//                                                 m_strLocalFile为收到文件名称，之后调用SendFile发送文件，LocalFile与RemoteFile相同
	//                                  发起端：m_strLocalFile、m_strRemoteFile已经有了值，此时创建文件
	if (nFileCmd == STT_CMD_TYPE_FILE_WRITE)
	{//1、发送文件（Write）：
		if (m_strLocalFile.GetLength() <= 3)
		{//直接发送文件：
			return ProcessCmd_File_FileName_Write(pBuf, nLen, nMode, nDataLen);
		}
		else
		{//发起端调用ReadFile，服务端（接收端）调用SendFile，发起端收到的文件名称
			char *pszFileName = NULL;
			stt_pkg_get_cmd_file_name(pBuf, &pszFileName);

			if ((pszFileName == NULL) || (m_strRemoteFile.CompareNoCase(pszFileName) != 0))
			{
				CString strRemoteFile;
				strRemoteFile = pszFileName;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DownFile[%s] != SendFile[%s]"), m_strRemoteFile.GetString(), strRemoteFile.GetString());
			}

			delete pszFileName;
			return ProcessCmd_File_FileName_Read(pBuf, nLen, nMode, nDataLen);
		}
	}
	else //if (nFileCmd == STT_CMD_TYPE_FILE_READ)
	{//2、下载文件（Read）
		char *pszFileName = NULL;
		stt_pkg_get_cmd_file_name(pBuf, &pszFileName);
		CString strFile,strLocalFile;
		strFile = pszFileName;
		delete pszFileName;

		//获取绝对路径
		strLocalFile = Stt_GetAbsolutePathFile(strFile);
		SendFile(strLocalFile, strFile, g_nFileCmdTimeOut,TRUE);
		return 0;
	}
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName_Write(BYTE *pBuf,long nLen, long nMode, long nDataLen)
{
	if (nLen == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("文件名称错误......"));
		return FALSE;
	}

	// 	long nLenFileName = stt_pkg_get_data_len_cmd_file(pBuf);
	// 	pBuf[nLen] = 0;
	char * pszFileName = NULL;
	stt_pkg_get_cmd_file_name(pBuf, &pszFileName);
	long nFileSize = stt_pkg_get_cmd_file_size(pBuf);
	m_tmFileModify = stt_pkg_get_cmd_file_time(pBuf);

	CString strFile = pszFileName;
	CString strLocalFile;
	//如果是相对路径，则获取绝对路径
	strLocalFile = Stt_GetAbsolutePathFile(strFile);
	strLocalFile = strLocalFile + _T("bk");

	CString strPath = GetPathFromFilePathName(strLocalFile);
	CreateAllDirectories(strPath);
	
	UINT nOpenMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
	nOpenMode |= CFile::modeTruncate;
#endif
	BOOL bRet = m_oFile.Open(strLocalFile, nOpenMode);

	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;
	m_strLocalFile = strLocalFile;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]创建写文件失败"),pszFileName);

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(m_strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError：%s【%d】"), m_strLocalFile.GetString(),nMode);

		m_strLocalFile.Empty();
		m_strRemoteFile.Empty();
	}
	else
	{
		//设置文件时间
		// #ifdef _PSX_IDE_QT_
		// 		file_set_time(m_strLocalFile,tmFile);
		// #else
		// 		file_set_time(m_oFile.m_hFile,tmFile);
		// #endif

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(pszFileName, stt_pkg_get_cmd_file_size(pBuf));
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:%s"), pszFileName);
	}

	delete pszFileName;

	if(!stt_is_ret_file_cmd_fail(nMode))
	{
		//添加已发送命令队列
		CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_WRITE, GetTickCount(), g_nFileCmdTimeOut, m_pCmdOverTimeMsgRcv);
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

long CSttSocketDataBase_File::ProcessCmd_File_FileName_Read(BYTE *pBuf,long nLen, long nMode, long nDataLen)
{
	if (nLen == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("文件名称错误......"));
		return FALSE;
	}

	//本地下载时，收到sendFile命令时，创建bk文件
	m_strLocalFile = m_strLocalFile + _T("bk");
	CString strPath = GetPathFromFilePathName(m_strLocalFile);
	CreateAllDirectories(strPath);

	UINT nOpenMode = CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;
#ifdef _PSX_IDE_QT_
	nOpenMode |= CFile::modeTruncate;
#endif
	BOOL bRet = m_oFile.Open(m_strLocalFile, nOpenMode);

	m_nFileTotalSize = 0;
	m_nFileSendSize = 0;

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]创建写文件失败"),m_strLocalFile.GetString());

		nMode = STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED;

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(m_strLocalFile.GetString(),nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError：%s【%d】"), m_strLocalFile.GetString(),nMode);

		m_strLocalFile.Empty();
		m_strRemoteFile.Empty();

		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, STT_CMD_TYPE_FILE_WRITE
														, nMode, GetTickCount());
	}
	else
	{
		m_tmFileModify = stt_pkg_get_cmd_file_time(pBuf);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(m_strLocalFile, stt_pkg_get_cmd_file_size(pBuf));
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Start:%s[%d]"), m_strLocalFile.GetString(),stt_pkg_get_cmd_file_size(pBuf));
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

int CSttSocketDataBase_File::RenameRecvFile(const CString &strBkFileName)
{//例如临时备份文件：d:/abk、d:/a.txtbk,目标文件：d:/a、d:/a.txt
	//去除临时文件中最后的bk,得到真正需要的文件名
	CString strNewFile = strBkFileName.Left(strBkFileName.GetLength()-2);

	if (IsFileExist(strNewFile))
	{
		if (!X_DeleteFile(strNewFile))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_DeleteFile fail[%s]"),strNewFile.GetString());
		}
	}
	BOOL bRet = X_CopyFile(strBkFileName,strNewFile);
	if(bRet)
	{
		file_set_time(strNewFile,m_tmFileModify);

#ifdef  _STT_NOT_IN_TEST_SERVER_
		//底层需将临时文件保存
		X_DeleteFile(strBkFileName);
#endif
	}
	return bRet;

	//	char chOldFileName[255] = {0};
	//	char chNewFileName[255] = {0};
	//	CString_to_char(strBkFileName,chOldFileName);
	//	CString_to_char(strNewFile,chNewFileName);

	//	if (IsFileExist(strNewFile))
	//	{
	//		if (!X_DeleteFile(strNewFile))
	//		{
	//			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_DeleteFile fail[%s]"),strNewFile.GetString());
	//		}
	//	}

	//	return rename(chOldFileName,chNewFileName);
}

long CSttSocketDataBase_File::ProcessCmd_File_Data(BYTE *pBuf, long nLen, long nMode, long nDataLen)
{
	CString strLocalFile = m_strLocalFile;

	//表示传输的是文件数据，写文件
	if (nDataLen > 0)
	{//处理：最后一帧没有数据，即文件长度是4096的整数倍
		//不确定写入0长度是否会出错，所以，处理下
#ifdef _PSX_IDE_QT_
		if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
		if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
		{
			m_oFile.Write(pBuf + STT_PKG_INDEX_DATA, nDataLen);
			m_nFileSendSize += nDataLen;

			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferStep(m_nFileSendSize);
			}
		}
		else
		{//文件已关闭
			//			DeleteFile(m_strLocalFile);
			nMode = STT_FILEMODE_ERRNO_READFILE_FAILED;

			CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, STT_CMD_TYPE_FILE_WRITE, nMode, GetTickCount());
		}
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//表示最后一帧
	{
		m_oFile.Flush();
		CloseFile();
#ifdef _PSX_QT_LINUX_
        system("sync");
#endif
		//设置文件时间
		file_set_time(strLocalFile,m_tmFileModify);

		if (RenameRecvFile(strLocalFile) < 0)
		{//重命名失败
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("X_Copy fail[%s]"),strLocalFile.GetString());
		}

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);
#ifdef _PSX_QT_LINUX_
		system("sync");
#endif
		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		ResetAfterTransmit();
	}

	return SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, nMode);
}

long CSttSocketDataBase_File::ProcessCmd_File_Ret(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode)
{
	//文件传输失败或结束，一定要先关闭文件，后调用后续接口，防止多线程时序乱
	CString strLocalFile = m_strLocalFile;

	if (stt_is_ret_file_cmd_fail(nMode))
	{//文件传输错误，关闭文件
		CloseFile();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferError(strLocalFile,nMode);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError：%s【%d】"), strLocalFile.GetString(),nMode);
		
		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, nFileCmd, nMode, GetTickCount());

		ResetAfterTransmit();
		return -1;
	}

	if (nMode == STT_FILEMODE_LASTFRAME)//表示最后一帧
	{//此为文件接收端的处理
		CloseFile();

		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish---:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferFinish(strLocalFile);
		}

		ResetAfterTransmit();
		return 0;
	}

	long nReadLen = 0;
#ifdef _PSX_IDE_QT_
	if (m_oFile.handle() != (int)INVALID_HANDLE_VALUE)
#else
	if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
#endif
	{
		nReadLen = m_oFile.Read(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN, STT_PKG_SEND_FILEDATA_MAXLEN);
		m_nFileSendSize += nReadLen;

		//生成报文头
		//if (nReadLen < STT_PKG_SEND_FILEDATA_MAXLEN)
		if (nReadLen == 0 || m_nFileSendSize >= m_nFileTotalSize)
		{//最后一帧
			nMode = STT_FILEMODE_LASTFRAME;

			if(nReadLen == 0)
			{//DataLen为0，接收端判为应答命令，所以特例处理
				CloseFile();
				
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("TransferFinish===:%s[%d]"), strLocalFile.GetString(),m_nFileSendSize);

				if (m_pFtpProgress != NULL)
				{
					m_pFtpProgress->TransferFinish(strLocalFile);
				}

				ResetAfterTransmit();
			}
		}
		else
		{
			//最后一帧没有数据，此处不考虑：文件长度是4096的整数倍，如果是，最后一证为空，多发一帧报文
			nMode++ ;

			if (nMode >= STT_FILEMODE_ERRNO_TRANSMITERROR )
			{
				nMode = 0x01;
			}
		}
	}
	else
	{
		nMode = STT_FILEMODE_ERRNO_READFILE_FAILED;
		CSttCmdOverTimeTool::OnSocketFailFinish_FileCmd(this, nFileCmd, nMode, GetTickCount());
	}

	long nRet = SendFileCmd(m_chSendFileCmdBuf, nFileCmd, nMode, nReadLen);

	if ((m_pFtpProgress != NULL) && (nReadLen > 0))
	{
		m_pFtpProgress->TransferStep(m_nFileSendSize);
	}

	return nRet;
}

//文件为相对路径
void CSttSocketDataBase_File::SendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer)
{
	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;
	long nRet = -1;
	long nMode = 1;

	BOOL bRet = m_oFile.Open(strLocalFile, CFile::modeRead | CFile::shareDenyWrite);

	if (bRet)
	{//
		m_nFileTotalSize = m_oFile.GetLength();
		m_nFileSendSize = 0;
		m_dwSendBeginTime = GetTickCount();

		if (m_pFtpProgress != NULL)
		{
			m_pFtpProgress->TransferStart(strLocalFile, m_nFileTotalSize);
		}
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Start:%s[%d]"), strLocalFile.GetString(),m_nFileTotalSize);

		//首先发送文件名，与主动发送文件的流程保持一致
		//		long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_HEAD_LEN));

		memcpy((char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILESIZE),&m_nFileTotalSize,STT_PKG_FILEMODE_FILESIZE_LEN);

#ifdef _PSX_IDE_QT_
		stt_pkg_set_cmd_file_time(m_chSendFileCmdBuf,strLocalFile.toStdString().c_str());
#else
		stt_pkg_set_cmd_file_time(m_chSendFileCmdBuf,strLocalFile);
#endif

		long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
		nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

		nRet = SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_FILENAME, nLen);

		//添加已发送命令队列
		CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_WRITE, GetTickCount(), nTimeOut, m_pCmdOverTimeMsgRcv);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s]创建读文件失败"),strLocalFile.GetString());
		//文件名为空，表示文件不存在，与主动发送文件的流程保持一致
		if (bServer)
		{//如果是下载文件的模式，返回错误信息

			SendRetFileCmd(STT_CMD_TYPE_FILE_WRITE, STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
		else
		{
			if (m_pFtpProgress != NULL)
			{
				m_pFtpProgress->TransferError(strLocalFile,STT_FILEMODE_ERRNO_READFILE_FAILED);
			}
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError：%s【%d】"), m_strLocalFile.GetString()
									   ,STT_FILEMODE_ERRNO_READFILE_FAILED);
		}
	}
}

void CSttSocketDataBase_File::DownloadFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut)
{
	m_strLocalFile = strLocalFile;
	m_strRemoteFile = strReoteFile;

	//首先发送文件名，与主动发送文件的流程保持一致
	long nLen = CString_to_char(strReoteFile, (char*)(m_chSendFileCmdBuf+STT_PKG_INDEX_FILENAME));
	nLen += STT_PKG_FILEMODE_FILESIZE_LEN + STT_PKG_FILEMODE_FILETIME_LEN;

	SendFileCmd(m_chSendFileCmdBuf, STT_CMD_TYPE_FILE_READ, STT_FILEMODE_FILENAME, nLen);

	//添加已发送命令队列
	CSttCmdOverTimeTool::AddSttFileCmd(this, STT_CMD_TYPE_FILE_READ, GetTickCount(), nTimeOut, m_pCmdOverTimeMsgRcv);
}


long CSttSocketDataBase_File::ProcessCmd_File_Rename(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_Delete(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_GetDir(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

long CSttSocketDataBase_File::ProcessCmd_File_Move(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen)
{
	return 0;
}

void CSttSocketDataBase_File::RestartSendHeartbeatTickCount()
{
	m_oSendHeartbeatTick.Enter();
}

void CSttSocketDataBase_File::RestartRecvHeartbeatTickCount()
{
	//m_oRecvHeartbeatTick.Enter();
	//2021-8-20  lijunqing  use timer-count
	m_nRecvHeartbeatCounter = 0;
}

BOOL CSttSocketDataBase_File::SttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.AddFile(strLocalFile,strRemoteFile);
	return oFileTool.SendFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.Append(oFilesList);
	oFilesList.RemoveAll();
	return oFileTool.SendFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.AddFile(strLocalFile,strRemoteFile);
	return oFileTool.DownloadFiles(TRUE);
}

BOOL CSttSocketDataBase_File::SttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
	CSttFileTool oFileTool;
	oFileTool.m_pSocket = this;
	oFileTool.AttachSttSocketFileTransferProgress(pProgress);
	SetDestID(nTestID);
	oFileTool.m_bIsSocketRef = TRUE;
	oFileTool.Append(oFilesList);
	oFilesList.RemoveAll();
	return oFileTool.DownloadFiles(TRUE);
}

//////////////////////////////////////////
//迁移至"SttGlobalDef_File.h"内联函数
//void stt_InitPktBuffer_Head_File(BYTE *pPkgBuffer,long nTypeCmd, long nMode, long nDataLen, DWORD nIDTester, long nSendIndex, BYTE bCompress)
//{
//	stt_pkg_set_head(pPkgBuffer);
//	stt_pkg_set_cmd_type(pPkgBuffer, (BYTE)nTypeCmd);
//	stt_pkg_set_idtester(pPkgBuffer, nIDTester);
//	stt_pkg_set_send_index(pPkgBuffer, nSendIndex);
//	//	stt_pkg_set_compress(pPkgBuffer, bCompress);

//	stt_pkg_set_data_len_cmd_file(pPkgBuffer, nMode, nDataLen);
//}


void stt_pkg_offset(char* &pPos)
{
	while (*pPos == ' ' || *pPos == '\t')
	{
		pPos++;
	}
}

char* stt_pkg_find_attr(char *pPkgBuf, const char *pszKey, long nKeyLen)
{
	char *pPos = pPkgBuf;
	char *pTemp = NULL;

	while (*pPos != '>')
	{
		if (strncmp(pPos, pszKey,nKeyLen) == 0)
		{
			pTemp = pPos;
			pTemp += nKeyLen;
			stt_pkg_offset(pTemp);

			if (*pTemp == '=')
			{
				if((pPos-pPkgBuf) > 0)
				{
					if(*(pPos-1) == ' '||*(pPos-1) == '<'||*(pPos-1) == '\"')
						return pTemp+1;
				}
				else
					return pTemp+1;

				//return pTemp+1;zhoulei 20211014
			}

			pPos++;
		}
		else
		{
			pPos++;
		}
	}

	return NULL;
}

BOOL stt_cmd_get_key_value(char *pCmdBuf,long nCmdLen, const char *pszKey, char *pszValue)
{
	ASSERT(pCmdBuf[0] == '<');

	char *pPos = pCmdBuf;
	long nKeyLen = strlen(pszKey);

	pPos = stt_pkg_find_attr(pPos, pszKey, nKeyLen);

	if (pPos == NULL)
	{
		return FALSE;
	}

	stt_pkg_offset(pPos);
	ASSERT (*pPos == '\"' || *pPos == '\'');
	char *pBegin = ++pPos;
	char *pEnd = pPos;

	while (*pPos != '>')
	{
		if (*pPos == '\"' || *pPos == '\'')
		{
			pEnd = pPos;
			break;
		}

		pPos++;
	}

	if (pEnd == pBegin)
	{
		*pszValue = 0;
	}
	else
	{
		memcpy(pszValue, pBegin, pEnd - pBegin);
	}
	
	return TRUE;
}

BOOL stt_pkg_get_cmddata(char *pPkgBuf,long nPktLen,char *&pCmdData,long &nCmdLen)
{
	ASSERT(pPkgBuf[STT_PKG_HEAD_LEN] == '<');

	pCmdData = pPkgBuf + STT_PKG_INDEX_DATA;
	if (strncmp(pCmdData,"<?xml",5) != 0)
	{
		nCmdLen = nPktLen - STT_PKG_INDEX_DATA;
		return TRUE;
	}

	//去除“<?xml ……\>”
	int nCnt = STT_PKG_INDEX_DATA;
	while(*pCmdData != '>' && nCnt < nPktLen)
	{
		pCmdData++;
		nCnt++;
	}

	if (*pCmdData != '>' || nCnt >= nPktLen)
	{
		return FALSE;
	}

	pCmdData++;
	stt_pkg_offset(pCmdData);

	if (*pCmdData != '<')
	{
		return FALSE;
	}

	nCmdLen = nPktLen - (pCmdData - pPkgBuf);
	return TRUE;
}

CString Stt_GetAbsolutePathFile(const CString &strFile)
{
	CString strTemp = strFile;

#ifdef _PSX_QT_LINUX_
	if (strFile.GetAt(0) != '/')
#else
	if (strFile.Find(_T(":")) < 0)
#endif
	{//相对路径
		if (g_strFtpRootFile.GetLength() == 0)
		{
			CString strPath;
			strPath = _P_GetSystemPath();
			strTemp = strPath + strTemp;
		}
		else
		{
			strTemp = g_strFtpRootFile + strTemp;
		}
	}

	return strTemp;
}


void stt_LogPkgHeadError(BYTE *pBuf, long nLen)
{
	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("解析报文命令头错误!!!!!"));
	long i = 0;
	CString strMsg;

	long nBeginPos = STT_PKG_HEAD_LEN * 2;
	char *pHexPkg = new char[nLen + STT_PKG_HEAD_LEN * 2 + 2];

	for (i=0; i<STT_PKG_HEAD_LEN; i++)
	{
		ValueToHex(pBuf[i], pHexPkg[i*2], pHexPkg[i*2+1]);
	}

	memcpy(pHexPkg + STT_PKG_HEAD_LEN * 2, pBuf+STT_PKG_HEAD_LEN, nLen - STT_PKG_HEAD_LEN);

	pHexPkg[nLen + STT_PKG_HEAD_LEN ] = 0;
	pHexPkg[nLen + STT_PKG_HEAD_LEN +1] = 0;
	strMsg = pHexPkg;
	CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);

	delete pHexPkg;
}


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
