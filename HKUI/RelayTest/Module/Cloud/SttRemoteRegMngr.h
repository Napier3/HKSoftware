#pragma once

#include "DB/Stt_RemoteRegRTs.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../SttSocket/Cloud/SttCloudServerClientSocketBase.h"

#define WM_UPDATE_REGMNGR   (WM_USER + 200)
#define WM_UPDATE_REG_ADD		0x0
#define WM_UPDATE_REG_UPDATE	0x1
#define WM_UPDATE_REG_DELETE	0x2

class CSttRemoteRegMngr : public CExBaseList
{
public:
	CSttRemoteRegMngr();
	virtual ~CSttRemoteRegMngr();

public:
	CWnd *m_pMsgWnd;
	virtual void SetMsgWnd(CWnd *pWnd)	{m_pMsgWnd = pWnd;}

public:
	CStt_RemoteRegRT *FindByRefSocket(CSttCloudServerClientSocketBase *pRef_Socket);
	CStt_RemoteRegRT *FindByCode_Register(const CString &strCode_Register);

	void AddRegisterChild(CSttRemoteCmd &oRemoteCmd,CSttCloudServerClientSocketBase *pRef_Socket);
	void DeleteRegisterChild(CSttCloudServerClientSocketBase *pRef_Socket);

	//远程协助用户数据更新
	void AnalysisUserList(CSttSysState *pSysState,CStt_RemoteRegRT &oUserList);
	void Update_UserList(CSttSysState *pSysState,CSttCloudServerClientSocketBase *pRef_Socket);
	void UpdateAssist_UserList(CSttSysState *pSysState,CStt_RemoteRegRT *pFind);
	//远程控制测试仪用户数据更新
	void UpdateTest_UserList(CSttSysState *pSysState);

	BOOL QueryRegisterList(const CString &strCode_Register,CStt_RemoteRegRTs &oRemoteRegRTs);

//	void Update_UserList_Request(CSttSysState *pSysState,CSttCloudServerClientSocketBase *pRef_Socket);
};

extern CSttRemoteRegMngr g_oSttRemoteRegMngr;
