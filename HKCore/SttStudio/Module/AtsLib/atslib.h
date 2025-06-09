#ifndef ATSLIB_H
#define ATSLIB_H

#include "atslib_global.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttAtsCmd.h"
#include "../../../Module/BaseClass/SttFileTransferProgress.h"

class CSttAtsLibEvent
{
public:
#ifdef ATSLIB_USE_PROTOCOL
    virtual void XProcess_SysState_Message(char *pBuffer, long nLen) = 0;
    virtual void XProcess_XCmd_Message(char *pBuffer, long nLen) = 0;
#else
    virtual void XProcess_SysState(CSttSysState &oSysState) = 0;
    virtual void XProcess_XCmd(CSttCmdBase *pSttCmd) = 0;
#endif
};

class ATSLIBSHARED_EXPORT AtsLib
{
public:
    AtsLib();
    ~AtsLib();

    void InitAtsLib(const char *pszCmdLine, const char *pszSysPath, CSttAtsLibEvent *pEventRcv);
    void ExitAtsLib();
    void SetLogBase(CLogBase *pLog);

public:
    long XSendBuffer(long nClassID, BYTE *pBuf,long nLen);

#ifndef ATSLIB_USE_PROTOCOL
    long XSendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE);
    long XSendCmdEx(CSttCmdBase *pCmd,long nSrcID=0);
    long XSendSysState(CSttSysState *pSysState);
    long XSendSysStateEx(CSttSysState *pSysState,long nDstID=0);
    long XSendHeartbeatCmd();
    long XRetFailureSysState(CSttCmdBase *pCmd);

    //用于超时处理逻辑
    long XSendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE,BOOL bCompress=FALSE,BOOL bReset=TRUE);
    long XSendCmdAsync(CSttCmdBase *pCmd,long nTimeOut=-1, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL,BOOL bCompress=FALSE,BOOL bReset=TRUE);

    BOOL XSttSendFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
    BOOL XSttSendFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
    BOOL XSttDownloadFiles(CExBaseList &oFilesList,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);
    BOOL XSttDownloadFile(const CString &strLocalFile,const CString &strRemoteFile,DWORD nTestID,CSttSocketFileTransferProgress *pProgress);

    virtual void XSendFile(const CString &strLocalFile, const CString &strReoteFile, long nTimeOut,BOOL bServer=FALSE);

    CExBaseList* NewCCharacteristics();
#endif
};

#endif // ATSLIB_H
