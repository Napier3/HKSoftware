#pragma once

#include "../SttSocketDataBase.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../SttCmd/SttRemoteCmd.h"

class CSttCloudServerClientSocketBase : public CSttSocketDataBase
{
public:
	CSttCloudServerClientSocketBase();
	virtual ~CSttCloudServerClientSocketBase();

	CString m_strCode_Register;	//注册码
	CString m_strSN_TestApp;

	//注册socket
	CSttCloudServerClientSocketBase *m_pRefSttSckt;
public:
	virtual void OnSocketClose(int nErrorCode);
	virtual BOOL ProcessRecvPacket(BYTE *pBuf, long nLen);
	virtual BOOL SendCmdToChildren(CSttSocketDataBase *pExceptSocket,CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE,BOOL bRetOwn=FALSE);
	virtual BOOL SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen,BOOL bRetOwn=FALSE);
	virtual BOOL SendSysStateToChildren(CSttSocketDataBase *pExceptSocket,CSttSysState *pSysState,BOOL bRetOwn=FALSE);

	virtual CSttSocketDataBase *FindDestSocket(int nDestID);
	virtual CSttSocketDataBase *FindDestSocket(BYTE *pBuf,long nLen);
	long TransmitBufferToDest(BYTE *pBuf,long nLen);
public:
	long ProcessCmd_Register(BYTE *pBuf, long nLen);
	BOOL ProcessCmd_UnRegister(BYTE *pBuf, long nLen);
	BOOL ProcessCmd_Query(BYTE *pBuf, long nLen);
	long ProcessCmd_Bind(BYTE *pBuf, long nLen);
	BOOL ProcessCmd_File(BYTE *pBuf, long nLen);
	long ProcessCmd_HeartBeat(BYTE *pBuf, long nLen);

	BOOL ProcessCmd_SysState(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	BOOL ProcessCmd_XCmd_Ats(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	BOOL ProcessCmd_XCmd_System(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	BOOL ProcessCmd_XCmd_Test(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	BOOL ProcessCmd_XCmd_Assist(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	BOOL ProcessCmd_XCmd_Debug(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

public:
	CAutoCriticSection m_oClientChildSocketMngrLock;

	void AddBindSocket(CSttCloudServerClientSocketBase *p,DWORD nIDTester);
	void DeleteBindSocket(CSttCloudServerClientSocketBase *p);
	CSttCloudServerClientSocketBase* FindBindSocketByIDTest(DWORD nIDTester);
	void InitAfterUnRegister(BOOL bDisconnect);

	//2020-5-25  避免xml解析的时候，频繁分配内存，缺省为1M个wchar_t
protected:
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	void SetXmlBufferLen(long nLen);
};

////////////////////////////////
void Stt_GenerateSN_TestApp(CString &strSN_TestApp);
void Stt_GenerateCode_Register(const CString &strSN_TestApp,CString &strCode_Register);