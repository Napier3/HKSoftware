#ifndef _SttCmdOverTimeMngr_h_
#define _SttCmdOverTimeMngr_h_

#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "SttSocketDataBase_File.h"
#include "SttCmdOverTimeMsgRcv.h"

class  CSttTestEngineClientData;


#ifndef _OA_MNGR_CLIENT
class CSttSysState;
#endif

//已发送命令超时管理
class CSttCmdOverTimeTool
{
private:
	CSttCmdOverTimeTool();
	virtual ~CSttCmdOverTimeTool();

	static CSttCmdOverTimeTool *g_pSttCmdOverTimeTool;
	static long g_nSttCmdOverTimeToolRef;

	CSttCmdOverTimeMsgRcv *m_pSttCmdOverTimeMsgRcv;

public:
	static CSttCmdOverTimeTool *Create();
	static void Release();
	static CSttCmdOverTimeTool *GetSttCmdOverTimeTool();
	static void AttachCmdOverTimeMsgRcv(CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv);
   static void Clear(void *pSocket);
   static void Clear(CSttTestEngineClientData *pEngineClient);

   static void ProcessTimeOutProc_Attach();
	static long ProcessTimeOut(DWORD dwCurTime);
	static STT_CMD_INFO *AddSttFileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
		, DWORD dwCurrTime, long dwCmdTimeout, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv);

	static STT_CMD_INFO *AddSttCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
		, char *pszCmdID, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL, long nSendMode = STT_CMD_Send_Sync);
	static STT_CMD_INFO *AddSttCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
		, const CString &strCmdID, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL, long nSendMode = STT_CMD_Send_Sync);
	static long OnSocketReceive_FileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
				, DWORD nCmdPara, DWORD dwCurrTime); 
	static long OnSocketFailFinish_FileCmd(CSttXcmdChInterface *pSocket, DWORD nCmdType
		, DWORD nCmdPara, DWORD dwCurrTime);

	static long OnSocketClosed(void *pSocket);
	static BOOL HasCmdUsing();//zhouhj 2023.7.21 zhouhj 关闭软件时,判断是否所有命令都已执行完成

#if !defined(_OA_MNGR_CLIENT) && !defined(_STT_FTP_SVR_)
	static long OnSocketReceive_FixedCmd(CSttXcmdChInterface *pSocket, CSttSysState &oSysState,long nExecStatus); 
#endif

protected:
	STT_CMD_INFO* GetCmdEmptyInfo();
	BOOL In_HasCmdUsing();//zhouhj 2023.7.21 zhouhj 关闭软件时,判断是否所有命令都已执行完成

private:
	STT_CMD_INFO m_arrHasSendCmd[STT_CMD_INFO_MAX_COUNT];
	long m_nMaxIndex;

	//缓存赋值互斥锁
	CAutoCriticSection m_oCriticSection;
};

void *ProcessTimeOutProc(LPVOID lParam);

//2020-5-27
//调试的时候，是否需要判断超时，内存中将变量的值修改为0即可
extern long g_nSttCmdOverTimeEnable;

//2023-5-18  lijunqing 方便调试的时候显示命令的一些信息
extern long g_nSttCmdOverTimeViewLog;


BOOL Stt_Is_ExecStatus_NULL(long nExecStatus);
BOOL Stt_Is_ExecStatus_Ack(long nExecStatus);
BOOL Stt_Is_ExecStatus_Failure(long nExecStatus);
BOOL Stt_Is_ExecStatus_Success(long nExecStatus);
BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus);

#endif
