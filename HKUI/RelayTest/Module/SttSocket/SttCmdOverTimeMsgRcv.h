#ifndef _SttCmdOverTimeMsgRcv_h_
#define _SttCmdOverTimeMsgRcv_h_

#include "../../../Module/BaseClass/ExBaseList.h"

//////////////命令超时机制/////////////////
#define STT_CMD_INFO_MAX_COUNT  100
#define STT_CMD_INFO_EXPAND_COUNT  100

//命令执行状态	ExecStatus	0=未处理  1=ACK 2=执行失败，3=执行成功
#define STT_CMD_ExecStatus_NULL		0
#define STT_CMD_ExecStatus_ACK		1
#define STT_CMD_ExecStatus_FAILURE	2
#define STT_CMD_ExecStatus_SUCCESS	3
#define STT_CMD_ExecStatus_TIMEOUT	4
#define STT_CMD_ExecStatus_SocketClose	5

#define STT_CMD_Send_Sync	0
#define STT_CMD_Send_Async	1

//已发送命令结束或超时接口：
class CSttCmdOverTimeMsgRcv
{
public:
    virtual void OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
    {
#ifdef _PSX_IDE_QT_
        (void)pSocketRef;
        (void)nCmdType;
        (void)pszCmdID;
#endif
    };
    virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
    {
#ifdef _PSX_IDE_QT_
        (void)pSocketRef;
        (void)nCmdType;
        (void)pszCmdID;
#endif
    };
    virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID) = 0;
};


//已发送命令信息类
typedef struct stt_cmd_info
{
	DWORD m_nUse;//当前结构体是否被使用
	DWORD nCmdType;//命令类型：文件命令，其他命令
	DWORD dwBeginCmdTime;//命令发送时间
	DWORD dwCmdSendTime;//命令超时
	DWORD dwCmdTimeout;//命令超时时间
	char pszCmdID[32];   //命令的id
	long nMode;			//如果不是文件命令，0表示同步发送，1表示异步发送
	LPVOID pSocketRef;
	CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv;
	volatile long m_nCmdExecState;//运行状态0,1：ack,2:fail,3:success,4;timeout
	CExBaseList *pSysState;//应答结果指针

	void SetUsed(DWORD nUsed){m_nUse = nUsed;}
	BOOL IsUsed()									{	return m_nUse;	}
	BOOL IsTimeOut(DWORD dwCurTime)
	{
		if (dwCmdSendTime == 0)
		{// call first time
			dwCmdSendTime = dwCurTime;
		}

		if (dwCmdSendTime > dwCurTime)
		{//2021-8-20  lijunqing long==>> overflow
			dwCmdSendTime = dwCurTime;
		}

		return (dwCurTime - dwCmdSendTime >= dwCmdTimeout);
	}
	void OnSendCmdFinish(BOOL bSuccess=TRUE);

#if !defined(_OA_MNGR_CLIENT) && !defined(_STT_FTP_SVR_)
	void OnSendCmdStatusChanged(long nExecState,CExBaseList *pSysState2);
#endif

	BOOL CheckTimeOut(DWORD dwCurTime);
	BOOL IsCmdExecState_Failure(){return m_nCmdExecState == STT_CMD_ExecStatus_FAILURE;}
	BOOL IsCmdExecState_Success(){return m_nCmdExecState == STT_CMD_ExecStatus_SUCCESS;}
	void Clear();
}STT_CMD_INFO;


inline BOOL Stt_Is_ExecStatus_NULL(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_NULL);
}

inline BOOL Stt_Is_ExecStatus_Ack(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_ACK);
}

inline BOOL Stt_Is_ExecStatus_Failure(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_FAILURE);
}

inline BOOL Stt_Is_ExecStatus_Success(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_SUCCESS);
}

inline BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus)
{
	return (nExecStatus == STT_CMD_ExecStatus_TIMEOUT);
}

#endif //_SttCmdOverTimeMsgRcv_h_
