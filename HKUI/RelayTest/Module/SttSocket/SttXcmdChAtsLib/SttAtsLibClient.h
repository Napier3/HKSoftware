#pragma once

#include "../SttXcmdChInterface.h"
#include "../../AtsLib/atslib.h"

class CSttAtsLibClient : public CSttXcmdChInterface, public CSttAtsLibEvent
{
public:
	CSttAtsLibClient();
    virtual ~CSttAtsLibClient();

public://CSttAtsLibEvent
     virtual void XProcess_SysState(CSttSysState &oSysState);
    virtual void XProcess_XCmd(CSttCmdBase *pSttCmd);

public:
    virtual CString XGetLocalIP();
    virtual void XGetLocalIP(char *pszIP);
    virtual CString XGetRemoteIP();

    virtual bool IsSttXcmdChValid();
	virtual void CloseSttXcmdCh();
	virtual CString SttXmdChAddr();
	virtual void SttXmdChAddr(const CString &strAddr);
	virtual bool XConnectServer(const CString &strIPServer, long nPort);
	virtual long XRecvHeartbeatCounterAdd();
	virtual long XRestartRecvHeartbeatTickCount();

	virtual long XSendBuffer(BYTE *pBuf,long nLen);
	virtual void XAttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pCmdOverTimeMsgRcv);


	virtual long XSendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long XSendCmdEx(CSttCmdBase *pCmd,long nSrcID=0);
	virtual long XSendSysState(CSttSysState *pSysState);
	virtual long XSendSysStateEx(CSttSysState *pSysState,long nDstID=0);
	virtual long XSendHeartbeatCmd();
	virtual long XRetFailureSysState(CSttCmdBase *pCmd);

	//用于超时处理逻辑
	virtual long XSendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long XSendCmdAsync(CSttCmdBase *pCmd,long nTimeOut=-1, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	
	virtual BOOL XSttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL XSttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL XSttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
	virtual BOOL XSttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);

	virtual void XSendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer=FALSE);

protected:
    AtsLib m_oAtsLib;

public:
    AtsLib* GetAtsLib() {   return &m_oAtsLib;  }

};
