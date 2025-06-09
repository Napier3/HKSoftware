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

 //2022-2-12  lijunqing  测试仪报文转发，通过SocketServer转发给所有链接自动测试控制服务的客户端
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
    CSttTestClientUser *User_Login(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
public:
    virtual void OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket = TRUE);
    virtual long ReturnSysStateToChildren(CSttXcmdChInterface *pExceptSocket,CSttSysState *pSysState);
    virtual BOOL SendBufferToChildren(CSttXcmdChInterface *pExceptSocket,BYTE *pBuf,long nLen);
	long ReturnBroadcastUserMngr(CSttSysState &oSysState);
	long ReturnGetSocketConnect(CSttSysState &oSysState);

    CSttXcmdChInterface *FindSocketByAuthority(const CString &strAuthorityID);

    virtual long Process_Cmd_System_Login(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_Logout(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_Request(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_Authority(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_LiveUpdate(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    //2020-12-05  lijunqing add
    BOOL Cmd_System_GetFilePath(CSttSystemCmd &oSysCmd,  CString &strFullPath, CString &strRelPath);
    virtual long Process_Cmd_System_DownFile(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long ProcessCmd_SetSysConfig(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long ProcessCmd_GetSysConfig(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
    virtual long Process_Cmd_System_GetDirs(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);

    //2021-0527  shaolei   add
    virtual long ProcessCmd_CloudTest(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd) {return  0;}

	//退出登录或断链，检查是否停止测试
    virtual void CheckStopTestAfterRelease(CSttXcmdChInterface *pClientSocket){}

	//只检测具有单机测试权限的测试端心跳超时
	virtual void CheckHeartbeatOverTime()=0;

//2020-07-12  lijunqing
public:
    BOOL CanSendLog()	{	return g_nSttLogServerDebugInfor;	};
	virtual void LogDebugInfor(const CString &strInfor);

    virtual long Process_Debug_ConfigDebug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);

};

//2020-10-19  lijunqing  Server只有一个，所以定义一个全局变量，方便访问
extern CSttTestEngineServerData *g_theSttTestEngineServer;
extern CSttXcmdChInterface *g_pReplayTestSocket;
extern long g_nCheckAuthority;
