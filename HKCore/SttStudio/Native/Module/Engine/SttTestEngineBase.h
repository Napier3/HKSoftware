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
#include "../SttSocket/SttCmdOverTimeMngr.h"

//view test msg interface. for debug or other
class CSttTestMsgViewInterface
{
public:
	virtual void OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType){}
	virtual void On_Process_Cmd_System(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd){}
	virtual void On_Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd){}
	virtual void On_Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd){}
	virtual void On_Process_Cmd_Remote(CSttSocketDataBase *pClientSocket, CSttRemoteCmd &oRemoteCmd){}
	virtual void On_Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd){}
	virtual void On_Process_Cmd_Assist(CSttSocketDataBase *pClientSocket, CSttAssistCmd &oAssistCmd){}
	virtual void On_Process_Cmd_Adjust(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd){}
	virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState){}
};

class CSttTestEngineBase : public CSttCmdOverTimeMsgRcv
{
public:
	CSttTestEngineBase();
	virtual ~CSttTestEngineBase();
public:
	virtual void OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}
	virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}


	void AttatchSttTestMsgViewInterface(CSttTestMsgViewInterface *pSttTestMsgViewInterface)	{	m_pSttTestMsgViewInterface = pSttTestMsgViewInterface;	}

protected:
	CSttTestMsgViewInterface *m_pSttTestMsgViewInterface;

	void LogPkgHeadError(BYTE *pBuf, long nLen);
public:
	virtual void CloseSocket(CSttSocketDataBase *pSocket);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);
	virtual long SendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE, long nSrcID_Test=0, long nTimeOut=0);
	virtual long ReturnSysState(CSttSocketDataBase *pSocket, int nCmdType, char *pszCmdID, BOOL bIsSuccess);
    virtual long ReturnSysState(CSttSocketDataBase *pSocket,CSttSysState *pSysState, BOOL bSpyAllCmd);
    virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData);  //lijunqing 2020-10-20
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttSocketDataBase *pSocket, CSttCmdData *pRetData);  //lijunqing 2020-10-21

	virtual long OnTestMsg(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen);
	virtual BOOL OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet);

	virtual long Process_Cmd_System(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Remote(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Assist(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Adjust(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
	virtual long Process_Heartbeat(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
    virtual long Process_Trigger(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Comtrade(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual long Process_Cmd_System(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket,  CSttTestCmd &oTestCmd);
	virtual long Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Cmd_Remote(CSttSocketDataBase *pClientSocket, CSttRemoteCmd &oRemoteCmd);
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	virtual long Process_Cmd_Assist(CSttSocketDataBase *pClientSocket, CSttAssistCmd &oAssistCmd);
	virtual long Process_Cmd_Adjust(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd);
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

public:
	CSttSocketDataBase *m_pSocketDataBase;
	CSttTestClientUserMngr m_oClientUserMngr;
	
	void SetRefSocket(CSttSocketDataBase *pSocket)	{	m_pSocketDataBase = pSocket;	}
	CSttSocketDataBase *GetTestAuthoritySocket();
	CSttSocketDataBase *GetAtsAuthoritySocket();

    //2020-11-29  lijunqing
    //根据软件ID返回报文
    void SendToAllUser(const CString &strSoftID, BYTE *pBuf,long nLen);

    //2022-2-12  lijunqing
    CSttPkgDispatchInterfaces m_oSttPkgDispatch;
    void Add(CSttPkgDispatchInterface *p)           {   m_oSttPkgDispatch.Add(p);   }
    void Remove(CSttPkgDispatchInterface *p)    {   m_oSttPkgDispatch.Remove(p);    }

public:
	virtual long Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Remote(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Ats(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Assist(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Adjust(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_IOT(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_State(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_SearchPointReport(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Reply(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState){	return 0;}
    virtual long Process_SysState_Meas(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState){	return 0;}
	virtual long Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)	{	return 0;	}

//2020-5-25  避免xml解析的时候，频繁分配内存，缺省为1M个wchar_t
protected:
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	void SetXmlBufferLen(long nLen);
};

#ifdef _PSX_QT_LINUX_ 
extern long g_nSttLogServerSpyAllCmd;
#endif
