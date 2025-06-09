#pragma once

#include "../SttSocket/SttSocketDataBase.h"
#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttAssistCmd.h"
#include "../SttCmd/SttAtsCmd.h"
#include "../SttCmd/SttDebugCmd.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttCmd/SttAdjustCmd.h"
#include "../SttGlobalDef.h"
#include "../SttAuthority/SttTestClientUserMngr.h"

//view test msg interface. for debug or other
class CSttTestMsgViewInterface
{
public:
    virtual void OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
    virtual void On_Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual void On_Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd);
    virtual void On_Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual void On_Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket, CSttRemoteCmd &oRemoteCmd);
    virtual void On_Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd);
    virtual void On_Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket, CSttAssistCmd &oAssistCmd);
    virtual void On_Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd);
    virtual void On_Process_SysState(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
};

class CSttTestEngineBase : public CSttCmdOverTimeMsgRcv
{
public:
	CSttTestEngineBase();
	virtual ~CSttTestEngineBase();
public:
    virtual void OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
    virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);
    virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);


	void AttatchSttTestMsgViewInterface(CSttTestMsgViewInterface *pSttTestMsgViewInterface)	{	m_pSttTestMsgViewInterface = pSttTestMsgViewInterface;	}

protected:
	CSttTestMsgViewInterface *m_pSttTestMsgViewInterface;

	void LogPkgHeadError(BYTE *pBuf, long nLen);
public:
	virtual void CloseSocket(CSttXcmdChInterface *pSocket);
	virtual void OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket = TRUE);
	virtual long SendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE, long nSrcID_Test=0, long nTimeOut=0);
	virtual long ReturnSysState(CSttXcmdChInterface *pSocket, int nCmdType, char *pszCmdID, BOOL bIsSuccess);
    virtual long ReturnSysState(CSttXcmdChInterface *pSocket,CSttSysState *pSysState, BOOL bSpyAllCmd);
    virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData);  //lijunqing 2020-10-20
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttXcmdChInterface *pSocket, CSttCmdData *pRetData);  //lijunqing 2020-10-21

	virtual long OnTestMsg(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen);
	virtual BOOL OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet);

	virtual long Process_Cmd_System(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Test(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_SysState(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
	virtual long Process_Heartbeat(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
    virtual long Process_Trigger(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Comtrade(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);


    virtual long Process_Cmd(CSttXcmdChInterface *pClientSocket, CSttCmdBase *pCmd);

	virtual long Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket, CSttRemoteCmd &oRemoteCmd);
	virtual long Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd);
	virtual long Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket, CSttAssistCmd &oAssistCmd);
	virtual long Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd);
	virtual long Process_SysState(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

public:
	CSttXcmdChInterface *m_pSocketDataBase;
	CSttTestClientUserMngr m_oClientUserMngr;
	
	void SetRefSocket(CSttXcmdChInterface *pSocket)	{	m_pSocketDataBase = pSocket;	}
	CSttXcmdChInterface *GetTestAuthoritySocket();
	CSttXcmdChInterface *GetAtsAuthoritySocket();

    //2020-11-29  lijunqing
    //根据软件ID返回报文
    void SendToAllUser(const CString &strSoftID, BYTE *pBuf,long nLen);

    //2022-2-12  lijunqing
    CSttPkgDispatchInterfaces m_oSttPkgDispatch;
    void Add(CSttPkgDispatchInterface *p)           {   m_oSttPkgDispatch.Add(p);   }
    void Remove(CSttPkgDispatchInterface *p)    {   m_oSttPkgDispatch.Remove(p);    }

public:
	virtual long Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Remote(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Assist(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Adjust(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_IOT(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_State(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_SearchPointReport(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Log(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Event(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Packet(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Update(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Reply(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_RtData(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Meas(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats_Stop(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

//2020-5-25  避免xml解析的时候，频繁分配内存，缺省为1M个wchar_t
protected:
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	void SetXmlBufferLen(long nLen);
};

#ifdef _PSX_QT_LINUX_ 
extern long g_nSttLogServerSpyAllCmd;
#endif
