#pragma once

#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../../../Module/BaseClass/SttFileTransferProgress.h"

class CSttSysState;
class CSttSystemCmd;
class CSttTestEngineBase;
class CSttTestClientUser;

class CSttXcmdChInterface
{
public:
	CSttXcmdChInterface();
	virtual ~CSttXcmdChInterface();

/***************
对于远程：Bind命令云端生成测试端ID返回m_nID_Remote
对于本地：Login命令由脱机程序或测试服务程序生成测试端ID返回m_nID_Local
***************/
// 	int m_nID_Local;
// 	int m_nID_Remote;
	DWORD m_nIDTester;
/***************
#define STT_SOCKET_TYPE_OWN				1
#define STT_SOCKET_TYPE_LOCAL			2
#define STT_SOCKET_TYPE_REMOTE			3
***************/
	int m_nSocketType;

	//2022-10-22  lijunqing 命令数据的格式，根据接收的报文自动识别
	long m_nSttCmdDataFormat; 

public:
        virtual CString XGetLocalIP() = 0;
        virtual void XGetLocalIP(char *pszIP) = 0;
        virtual CString XGetRemoteIP() = 0;

	virtual bool IsSttXcmdChValid() = 0;
	virtual void CloseSttXcmdCh() = 0;
	virtual CString SttXmdChAddr() = 0;
	virtual void SttXmdChAddr(const CString &strAddr) = 0;
	virtual bool XConnectServer(const CString &strIPServer, long nPort) = 0;
	virtual long XRecvHeartbeatCounterAdd() = 0;
	virtual long XRestartRecvHeartbeatTickCount() = 0;

	virtual long XSendBuffer(BYTE *pBuf,long nLen) = 0;
	virtual void XAttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv) = 0;


	virtual long XSendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE) = 0;
	virtual long XSendCmdEx(CSttCmdBase *pCmd,long nSrcID=0) = 0;
	virtual long XSendSysState(CSttSysState *pSysState) = 0;
	virtual long XSendSysStateEx(CSttSysState *pSysState,long nDstID=0) = 0;
	virtual long XSendHeartbeatCmd() = 0;
	virtual long XRetFailureSysState(CSttCmdBase *pCmd) = 0;

	//用于超时处理逻辑
	virtual long XSendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE,BOOL bCompress=FALSE,BOOL bReset=TRUE) = 0;
	virtual long XSendCmdAsync(CSttCmdBase *pCmd,long nTimeOut=-1, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL,BOOL bCompress=FALSE,BOOL bReset=TRUE) = 0;

	virtual DWORD GetIDTest();

	BOOL IsSocketType_Own()	{	return (m_nSocketType == STT_SOCKET_TYPE_OWN);}
	BOOL IsSocketType_Local()	{	return (m_nSocketType == STT_SOCKET_TYPE_LOCAL);}
	BOOL IsSocketType_Remote()	{	return (m_nSocketType == STT_SOCKET_TYPE_REMOTE);}
	void SetSocketType(int nType){	m_nSocketType = nType;	}

public:
	virtual BOOL ProcessCmd_System_DownFolder(CSttSystemCmd &oSysCmd);
	virtual BOOL ProcessCmd_System_CreateFolder(CSttSystemCmd &oSysCmd);
	virtual BOOL ProcessCmd_System_DeleteFolder(CSttSystemCmd &oSysCmd);
	virtual long ProcessCmd_System_DeleteFile(CSttSystemCmd &oSysCmd);

	virtual BOOL XSttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress) = 0;
	virtual BOOL XSttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress) = 0;
	virtual BOOL XSttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress) = 0;
	virtual BOOL XSttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress) = 0;

	virtual void XSendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer=FALSE) = 0;

protected:
	//2020-1-10  lijunqing
	//Socket关联的引擎，考虑到Local端，有可能同时控制多台测试仪
	//因此每一个Socket都关联自身的Engine对象
	CSttTestEngineBase *m_pTestEngine;
	CSttTestClientUser *m_pUser;

public:
	CSttTestEngineBase * GetTestEngine()	{	return m_pTestEngine;	}
	void SetTestEngine(CSttTestEngineBase *pTestEngine)	{	m_pTestEngine = pTestEngine;	}
	void SetUser(CSttTestClientUser *pUser)	{	m_pUser = pUser;	}

  virtual bool Match_IdSoft(const CString &strIdSoft);
};


