#pragma once

#include "SttSocketDataBase_File.h"
#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttSysState.h"


//2022-2-12  lijunqing ����ת��,���磺�Զ����Կ��Ʒ����յ��Ĳ������¼����ģ�ͨ���Զ����Կ���ͨ��ͨ��ת������λ�����
#include "../SttPkgDispatchInterface.h"

class CSttTestEngineBase;
class CSttTestClientUser;

class CSttSocketDataBase : public CSttSocketDataBase_File
{
public:
	CSttSocketDataBase();
	virtual ~CSttSocketDataBase();

/***************
����Զ�̣�Bind�����ƶ����ɲ��Զ�ID����m_nID_Remote
���ڱ��أ�Login�������ѻ��������Է���������ɲ��Զ�ID����m_nID_Local
***************/
// 	int m_nID_Local;
// 	int m_nID_Remote;
	DWORD m_nIDTester;
/***************
#define STT_SOCKET_TYPE_OWN				1
#define STT_SOCKET_TYPE_LOCAL			2
#define STT_SOCKET_TYPE_REMOTE			3
***************/
	int m_nSocketType;

	//2022-10-22  lijunqing �������ݵĸ�ʽ�����ݽ��յı����Զ�ʶ��
	long m_nSttCmdDataFormat; 

public:
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);

	virtual long SendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long SendCmdEx(CSttCmdBase *pCmd,long nSrcID=0);
	virtual long SendSysState(CSttSysState *pSysState);
	virtual long SendSysStateEx(CSttSysState *pSysState,long nDstID=0);
	virtual long SendHeartbeatCmd();
	virtual long RetFailureSysState(CSttCmdBase *pCmd);

	//���ڳ�ʱ�����߼�
	virtual long SendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long SendCmdAsync(CSttCmdBase *pCmd,long nTimeOut=-1, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL,BOOL bCompress=FALSE,BOOL bReset=TRUE);

	DWORD GetIDTest();

	BOOL IsSocketType_Own()	{	return (m_nSocketType == STT_SOCKET_TYPE_OWN);}
	BOOL IsSocketType_Local()	{	return (m_nSocketType == STT_SOCKET_TYPE_LOCAL);}
	BOOL IsSocketType_Remote()	{	return (m_nSocketType == STT_SOCKET_TYPE_REMOTE);}
	void SetSocketType(int nType){	m_nSocketType = nType;	}

public:
	BOOL ProcessCmd_System_DownFolder(CSttSystemCmd &oSysCmd);
	BOOL ProcessCmd_System_CreateFolder(CSttSystemCmd &oSysCmd);
	BOOL ProcessCmd_System_DeleteFolder(CSttSystemCmd &oSysCmd);
	long ProcessCmd_System_DeleteFile(CSttSystemCmd &oSysCmd);


protected:
	//2020-1-10  lijunqing
	//Socket���������棬���ǵ�Local�ˣ��п���ͬʱ���ƶ�̨������
	//���ÿһ��Socket�����������Engine����
	CSttTestEngineBase *m_pTestEngine;
	CSttTestClientUser *m_pUser;

public:
	CSttTestEngineBase * GetTestEngine()	{	return m_pTestEngine;	}
	void SetTestEngine(CSttTestEngineBase *pTestEngine)	{	m_pTestEngine = pTestEngine;	}
	void SetUser(CSttTestClientUser *pUser)	{	m_pUser = pUser;	}

    bool Match_IdSoft(const CString &strIdSoft);
};



BOOL stt_pkg_get_cmd_id(char *pPkgBuf,long nPktLen,long &nCmdType,char *pszCmdID,char *pszTestor, char *pszRetCmdType);

//2022-10-22  lijunqing  �������Ӹ�ʽ��û�в���ȱʡֵ�������ʱ��ᵼ���﷨���󣬴�ǿ���޸ģ�ʵ�ִ����ͳһ
void stt_InitSendBuf_Cmd(BYTE **ppszSendBuf,long &nSendBufLen, CSttCmdBase *pCmd, BOOL bCompress, long nSttCmdDataFormat);
void stt_InitRetSendBuf(BYTE **ppszSendBuf,long &nSendBufLen,CSttSysState *pSysState, BOOL bCompress, long nSttCmdDataFormat);
