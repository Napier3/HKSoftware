#pragma once
#include "SttTestClientUser.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

class CSttTestClientUserMngr : public CExBaseList
{
public:
	CSttTestClientUserMngr();
	virtual ~CSttTestClientUserMngr();
	CAutoCriticSection m_oUserMngrSection;//用户管理互斥锁

public:
	CSttTestClientUser *FindUser(CSttSocketDataBase *pSocket,long nID_Test);
	BOOL FindByRefSocket(CSttSocketDataBase *pSocket,CExBaseList &oUseList);
	BOOL FindByIdSoft(const CString &strIdSoft,CExBaseList &oUseList);
	CSttTestClientUser *FindByIDTest(DWORD nID_Test);
	CSttTestClientUser *FindByIDTest(DWORD nID_Test, const CString &strSoftID);  //2020-11-29   lijunqing
	CSttTestClientUser *FindHasAuthority(const CString &strAuthorityID);
	BOOL DeleteUserByRefSocket(CSttSocketDataBase *pSocket);
	void DeleteUserByIDTest(DWORD nID_Test);
	void DeleteUserByIDTest(DWORD nID_Test, const CString &strSoftID);
	void DeleteUserByIDTerminal(const CString &strIdTerminal);
    void OnAuthority(const CString &strAuthorityID,long nOwnAuthority=0);

	//Login\Logout\Request命令应答，更新用户链表
	BOOL UpdateUserList(CSttSysState &oSysState);
	BOOL UpdateCurrUser(CSttTestClientUser &oCurrUser);
	//用户链表来生成Login\Logout\Request命令应答
	void GenerateSysState(CSttSysState &oSysState);

	void ClearOtherAuthoritys(CExBaseList *pParas, CSttTestClientUser *pCurrUser);
	CSttTestClientUser * FindHasAuthorityUser(const char*){return NULL;};

    void RestartRecvHeartbeatTickCount(DWORD nID_Test);

    //2020-11-29  lijunqing
    //根据软件ID返回报文
    void SendToAllUser(const CString &strSoftID, BYTE *pBuf,long nLen);
    void SendSysState(CSttSocketDataBase *pCurrSocket, CSttSysState *pSysState, BOOL bSpyAllCmd);
    void SendCmd(CSttSocketDataBase *pCurrSocket, CSttCmdBase *pSttCmd, BOOL bSpyAllCmd);
};
