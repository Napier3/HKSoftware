#pragma once

#include "SttSocketDataBase_File.h"
#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttSysState.h"


//2022-2-12  lijunqing 报文转发,例如：自动测试控制服务，收到的测试仪事件报文，通过自动测试控制通信通道转发给上位机软件
#include "../SttPkgDispatchInterface.h"

class CSttTestEngineBase;
class CSttTestClientUser;

class CSttSocketDataBase : public CSttSocketDataBase_File
{
public:
	CSttSocketDataBase();
	virtual ~CSttSocketDataBase();

/***************
对于远程：Bind命令云端生成测试端ID返回m_nID_Remote
对于本地：Login命令由脱机程序或测试服务程序生成测试端ID返回m_nID_Local
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

	//2022-10-22  lijunqing 命令数据的格式，根据接收的报文自动识别
	long m_nSttCmdDataFormat; 

public:
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);

	virtual long SendCmd(CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long SendCmdEx(CSttCmdBase *pCmd,long nSrcID=0);
	virtual long SendSysState(CSttSysState *pSysState);
	virtual long SendSysStateEx(CSttSysState *pSysState,long nDstID=0);
	virtual long SendHeartbeatCmd();
	virtual long RetFailureSysState(CSttCmdBase *pCmd);

	//用于超时处理逻辑
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
	//Socket关联的引擎，考虑到Local端，有可能同时控制多台测试仪
	//因此每一个Socket都关联自身的Engine对象
	CSttTestEngineBase *m_pTestEngine;
	CSttTestClientUser *m_pUser;

public:
	CSttTestEngineBase * GetTestEngine()	{	return m_pTestEngine;	}
	void SetTestEngine(CSttTestEngineBase *pTestEngine)	{	m_pTestEngine = pTestEngine;	}
	void SetUser(CSttTestClientUser *pUser)	{	m_pUser = pUser;	}

    bool Match_IdSoft(const CString &strIdSoft);
};



BOOL stt_pkg_get_cmd_id(char *pPkgBuf,long nPktLen,long &nCmdType,char *pszCmdID,char *pszTestor, char *pszRetCmdType);

//2022-10-22  lijunqing  函数增加格式，没有采用缺省值，编译的时候会导致语法错误，从强制修改，实现代码的统一
void stt_InitSendBuf_Cmd(BYTE **ppszSendBuf,long &nSendBufLen, CSttCmdBase *pCmd, BOOL bCompress, long nSttCmdDataFormat);
void stt_InitRetSendBuf(BYTE **ppszSendBuf,long &nSendBufLen,CSttSysState *pSysState, BOOL bCompress, long nSttCmdDataFormat);
