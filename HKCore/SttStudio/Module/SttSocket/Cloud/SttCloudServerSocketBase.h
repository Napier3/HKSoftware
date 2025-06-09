#pragma once

#include "../SttServerSocketDataBase.h"
#include "SttCloudServerClientSocketBase.h"
#include "../../SttCmd/SttRemoteCmd.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

class CSttCloudServerSocketBase : public CSttServerSocketDataBase
{
public:
	CSttCloudServerSocketBase();
	virtual ~CSttCloudServerSocketBase();

public:
	BOOL Bind(CSttCloudServerClientSocketBase *pSocket, const CString &strCode_Register,DWORD nIDTester);
	CSttCloudServerClientSocketBase *FindByRegisterCode(const CString &strCode_Register);

	virtual void OnSttSktAccept(CSttSocketDataBase *pSttSkt);
	BOOL HasRegisteredByTestApp(const CString &strSN_TestApp);
	void OnSttScktClose(CSttSocketDataBase_File *pSttSckt);

public:
	CAutoCriticSection m_oClientSocketMngrLock;
};

extern CSttCloudServerSocketBase *g_pSttCloudSvrSocket;