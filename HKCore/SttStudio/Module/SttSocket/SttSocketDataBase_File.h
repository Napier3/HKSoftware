#pragma once

#include "../SttProtocolBufBase.h"
#include "../../../Module/BaseClass/SttFileTransferProgress.h"
#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/System/TickCount32.h"

#ifdef _PSX_QT_LINUX_
#include "../../../Module/Socket/WinTcpSocketClient.h"
#else
#include "../../../Module/Socket/WinTcpSocketClient.h"
#endif

class CSttCmdOverTimeMsgRcv;

extern long g_nSendHeartbeatTimeGap;
extern long g_nRecvHeartbeatTimeGap;

extern long g_nFileCmdTimeOut;
extern CString g_strFtpRootFile;
CString Stt_GetAbsolutePathFile(const CString &strFile);

class CSttSocketDataBase_File : public CExBaseList, public CWinTcpSocketClient,public CSttProtocolBufBase
{
public:
	CSttSocketDataBase_File();
	virtual ~CSttSocketDataBase_File();

public:
	virtual BOOL ConnectServer();
	virtual BOOL ConnectServer(const CString &strIPServer,long nPort);
	virtual long SendBuffer(BYTE *pBuf,long nLen);
	virtual long ReceiveBuffer(BYTE *pBuf,long nLen){	return 0;	}
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);
	virtual void OnSocketClose(int nErrorCode, BOOL bDeleteSocket = TRUE);
	virtual void CloseSocket();

	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnReceiveBuffer(int nErrorCode){}
	virtual void OnReceiveBuffer(BYTE *pBuf, long nLen);
	virtual DWORD GetIDTest();
	long HasComplatePkg();

#ifdef _PSX_QT_LINUX_
    virtual unsigned long GetLastError()    {   return 0;   }
#endif

//File
protected:
	UINT m_nCmdResult;
	CFile m_oFile;
	long  m_nFileTotalSize;
	long m_nFileSendSize;
	CString m_strLocalFile; //文件传输：本地文件
	CString m_strRemoteFile; //文件传输：远程文件
	DWORD m_dwSendBeginTime;
	CSttSocketFileTransferProgress *m_pFtpProgress;
	CSttCmdOverTimeMsgRcv *m_pCmdOverTimeMsgRcv;

	SYSTEMTIME m_tmFileModify;

	void ResetAfterTransmit();
	void CloseFile();
	int RenameRecvFile(const CString &strBkFileName);

public:
	void AttachFileTransferProgress(CSttSocketFileTransferProgress *pFtpProgress)		{	m_pFtpProgress = pFtpProgress;	}
	void DetachFileTransferProgress()		{	m_pFtpProgress = NULL;	}
	void AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv)		{	m_pCmdOverTimeMsgRcv = pCmdOverTimeMsgRcv;	}
	void DetachCmdOverTimeMsgRcv()		{	m_pCmdOverTimeMsgRcv = NULL;	}
	void SendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer=FALSE);
	void DownloadFile(const CString &strLocalFile, const CString &strReoteFile,long nTimeOut);
	
	long ProcessCmd_File(BYTE *pBuf,long nLen);
	virtual void ProcessCmd_End();

protected:	
	long ProcessCmd_File_ReadWrite(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);
	long ProcessCmd_File_Data(BYTE *pBuf,long nLen, long nMode, long nDataLen);
	long ProcessCmd_File_FileName(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);
	long ProcessCmd_File_FileName_Write(BYTE *pBuf,long nLen, long nMode, long nDataLen);
	long ProcessCmd_File_FileName_Read(BYTE *pBuf,long nLen, long nMode, long nDataLen);
	long ProcessCmd_File_Ret(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode);

	long ProcessCmd_File_Rename(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);
	long ProcessCmd_File_Delete(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);
	long ProcessCmd_File_GetDir(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);
	long ProcessCmd_File_Move(BYTE *pBuf,long nLen, UINT nFileCmd, UINT nMode, long nDataLen);

	virtual long SendFileCmd(BYTE *pBuf, UINT nFileCmd, UINT nMode, long nLen);
	virtual long SendRetFileCmd(UINT nFileCmd, UINT nMode);

private:
	BYTE m_chRecvBuf[STT_SOCKET_RECV_SIZE];//接收缓存4K
	BYTE m_chSendFileCmdBuf[STT_FILECMD_MAX_LEN];//文件命令发送缓存:4K+帧头长

public:
	//发送接收心跳计时器
	CTickCount32 m_oSendHeartbeatTick;

	//2021-8-20  lijunqing  use timer-count
	//CTickCount32 m_oRecvHeartbeatTick;
	long m_nRecvHeartbeatCounter;

	void RestartSendHeartbeatTickCount();
	void RestartRecvHeartbeatTickCount();

public:
	DWORD m_nDestID;
	void SetDestID(DWORD nDestID){	m_nDestID = nDestID;	}

	virtual BOOL SttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL SttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL SttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL SttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
};

//解析命令头节点
BOOL stt_cmd_get_key_value(char *pCmdBuf,long nCmdLen,const char *pszKey, char *pszValue);
BOOL stt_pkg_get_cmddata(char *pPkgBuf,long nPktLen,char *&pCmdData,long &nCmdLen);
void stt_LogPkgHeadError(BYTE *pBuf, long nLen);

