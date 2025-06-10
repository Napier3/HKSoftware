#pragma once

#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttAssistCmd.h"
#include "../SttCmd/SttAtsCmd.h"
#include "../SttCmd/SttDebugCmd.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttCmd/SttAdjustCmd.h"
#include "../SttGlobalDef.h"

#include "../SttSocket/SttServerSocketDataBase.h"
#include "../SttAuthority/SttTestClientUserMngr.h"
#include "../SttTestBase/SttXmlSerialize.h"

#include "SttServerNativeConfig.h"

 //2022-2-12  lijunqing  �����Ǳ���ת����ͨ��SocketServerת�������������Զ����Կ��Ʒ���Ŀͻ���
class CSttTestEngineServerData : public CSttPkgDispatchInterface
{
public:
	CSttTestEngineServerData();
	virtual ~CSttTestEngineServerData();

    //2022-2-12  lijunqing
    virtual void DispatchMsg(unsigned char *pBuf, long nLen);

protected:
	CSttServerSocketDataBase *m_pServerSocket;
    CSttServerSocketDataBase *m_pReplaySocket;
	CSttTestClientUserMngr *m_pSttTestClientUserMngr;

public:
    void SetServerSocketDataBase(CSttServerSocketDataBase *pCSttServerSocketDataBase) {m_pServerSocket=pCSttServerSocketDataBase;}
	void SetTestClientUserMngr(CSttTestClientUserMngr *pSttTestClientUserMngr){	m_pSttTestClientUserMngr = pSttTestClientUserMngr;	}
    CSttTestClientUserMngr* GetTestClientUserMngr(){return	m_pSttTestClientUserMngr;}
	CSttServerSocketDataBase * GetServerSocketDataBase(){ return m_pServerSocket; }
	virtual long SendSysState(CSttSysState *pSysState){return 0;}

    virtual long IsCanAuthorityToUser(CSttSystemCmd &oSysCmd, BOOL bRequest = TRUE);
    virtual long IsCanAuthorityToUser(CSttTestClientUser *pUser, CDvmData *pData, BOOL bRequest = TRUE);
    virtual long AuthorityToUser(CSttSystemCmd &oSysCmd, BOOL bRequest, BOOL bBroadcastWhenSuccess = TRUE);
    CSttTestClientUser *User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
public:
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);
	virtual long ReturnSysStateToChildren(CSttSocketDataBase *pExceptSocket,CSttSysState *pSysState);
	virtual BOOL SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen);	
	long ReturnBroadcastUserMngr(CSttSysState &oSysState);
	long ReturnGetSocketConnect(CSttSysState &oSysState);

	CSttSocketDataBase *FindSocketByAuthority(const CString &strAuthorityID);

	virtual long Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Request(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Authority(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_LiveUpdate(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
    //2020-12-05  lijunqing add
    BOOL Cmd_System_GetFilePath(CSttSystemCmd &oSysCmd,  CString &strFullPath, CString &strRelPath);
    virtual long Process_Cmd_System_DownFile(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long ProcessCmd_SetSysConfig(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long ProcessCmd_GetSysConfig(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_GetDirs(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);

    //2021-0527  shaolei   add
    virtual long ProcessCmd_CloudTest(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd) {return  0;}

	//�˳���¼�����������Ƿ�ֹͣ����
	virtual void CheckStopTestAfterRelease(CSttSocketDataBase *pClientSocket){}

	//ֻ�����е�������Ȩ�޵Ĳ��Զ�������ʱ
	virtual void CheckHeartbeatOverTime()=0;

//2020-07-12  lijunqing
public:
    BOOL CanSendLog()	{	return g_nSttLogServerDebugInfor;	};
	virtual void LogDebugInfor(const CString &strInfor);

	virtual long Process_Debug_ConfigDebug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);

};

//2020-10-19  lijunqing  Serverֻ��һ�������Զ���һ��ȫ�ֱ������������
extern CSttTestEngineServerData *g_theSttTestEngineServer;
extern CSttSocketDataBase *g_pReplayTestSocket;
extern long g_nCheckAuthority;
