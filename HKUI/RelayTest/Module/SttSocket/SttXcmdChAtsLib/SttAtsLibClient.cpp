#include "stdafx.h"
#include "SttAtsLibClient.h"
#include "../../Engine/SttTestEngineBase.h"

CSttAtsLibClient* g_theSttAtsLibClient = 0;//new CSttAtsLibClient();

CSttAtsLibClient::CSttAtsLibClient()
{
    //m_oAtsLib.
    m_oAtsLib.InitAtsLib(NULL, _P_GetSystemPath(), this);
}

CSttAtsLibClient::~CSttAtsLibClient()
{
    m_oAtsLib.ExitAtsLib();
}

void CSttAtsLibClient::XProcess_SysState(CSttSysState &oSysState)
{
//	return;
    m_pTestEngine->Process_SysState(this, oSysState);
}

void CSttAtsLibClient::XProcess_XCmd(CSttCmdBase *pSttCmd)
{

}

CString CSttAtsLibClient::XGetLocalIP()
{
    return "";
}

void CSttAtsLibClient::XGetLocalIP(char *pszIP)
{

}

CString CSttAtsLibClient::XGetRemoteIP()
{
     return "";
}

bool CSttAtsLibClient::IsSttXcmdChValid()
{
    return 1;
}

void CSttAtsLibClient::CloseSttXcmdCh()
{

}

CString CSttAtsLibClient::SttXmdChAddr()
{
	return "";
}

void CSttAtsLibClient::SttXmdChAddr(const CString &strAddr)
{

}

bool CSttAtsLibClient::XConnectServer(const CString &strIPServer, long nPort)
{
    return 1;
}

long CSttAtsLibClient::XRecvHeartbeatCounterAdd()
{
	return 0;
}

long CSttAtsLibClient::XRestartRecvHeartbeatTickCount()
{
	return 0;
}


long CSttAtsLibClient::XSendBuffer(BYTE *pBuf,long nLen)
{
    m_oAtsLib.XSendBuffer(pBuf, nLen);
	return 0;
}

void CSttAtsLibClient::XAttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)
{

}



long CSttAtsLibClient::XSendCmd(CSttCmdBase *pCmd,BOOL bCompress,BOOL bReset)
{
    m_oAtsLib.XSendCmd(pCmd, bCompress, bReset);
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}

long CSttAtsLibClient::XSendCmdEx(CSttCmdBase *pCmd,long nSrcID)
{
    m_oAtsLib.XSendCmdEx(pCmd, nSrcID);
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}

long CSttAtsLibClient::XSendSysState(CSttSysState *pSysState)
{
    m_oAtsLib.XSendSysState(pSysState);
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}

long CSttAtsLibClient::XSendSysStateEx(CSttSysState *pSysState,long nDstID)
{
    m_oAtsLib.XSendSysStateEx(pSysState, nDstID);
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}

long CSttAtsLibClient::XSendHeartbeatCmd()
{
    m_oAtsLib.XSendHeartbeatCmd();
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}

long CSttAtsLibClient::XRetFailureSysState(CSttCmdBase *pCmd)
{
    m_oAtsLib.XRetFailureSysState(pCmd);
	return STT_CMD_ExecStatus_SUCCESS;  // return len 1
}


//用于超时处理逻辑
long CSttAtsLibClient::XSendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents,BOOL bCompress,BOOL bReset)
{
    return XSendCmd(pCmd, bCompress, bReset);
}

long CSttAtsLibClient::XSendCmdAsync(CSttCmdBase *pCmd,long nTimeOut, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv,BOOL bCompress,BOOL bReset)
{
    return XSendCmd(pCmd, bCompress, bReset);
}


BOOL CSttAtsLibClient::XSttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
    return m_oAtsLib.XSttSendFiles(oFilesList, nTestID,pProgress );
}

BOOL CSttAtsLibClient::XSttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
    return m_oAtsLib.XSttSendFile(strLocalFile, strRemoteFile, nTestID,pProgress );
}

BOOL CSttAtsLibClient::XSttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
    return m_oAtsLib.XSttDownloadFiles(oFilesList, nTestID,pProgress );
}

BOOL CSttAtsLibClient::XSttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress)
{
    return m_oAtsLib.XSttDownloadFile(strLocalFile, strRemoteFile, nTestID,pProgress );
}


void CSttAtsLibClient::XSendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer)
{
    m_oAtsLib.XSendFile(strLocalFile, strReoteFile, nTimeOut, bServer );
}


