#ifndef _SttCmdOverTimeMngr_h_
#define _SttCmdOverTimeMngr_h_

#include "../../../Module/CriticalSection/SynCriticalSection.h"

#include "SttSocketDataBase_File.h"
class  CSttTestEngineClientData;

//////////////���ʱ����/////////////////
#define STT_CMD_INFO_MAX_COUNT  100
#define STT_CMD_INFO_EXPAND_COUNT  100

//����ִ��״̬	ExecStatus	0=δ����  1=ACK 2=ִ��ʧ�ܣ�3=ִ�гɹ�
#define STT_CMD_ExecStatus_NULL		0
#define STT_CMD_ExecStatus_ACK		1
#define STT_CMD_ExecStatus_FAILURE	2
#define STT_CMD_ExecStatus_SUCCESS	3
#define STT_CMD_ExecStatus_TIMEOUT	4
#define STT_CMD_ExecStatus_SocketClose	5

#define STT_CMD_Send_Sync	0
#define STT_CMD_Send_Async	1

#ifndef _OA_MNGR_CLIENT
class CSttSysState;
#endif

//�ѷ������������ʱ�ӿڣ�
class CSttCmdOverTimeMsgRcv
{
public:
	virtual void OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){};
	virtual void OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){};
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID) = 0;
};

//�ѷ���������Ϣ��
typedef struct stt_cmd_info
{
	DWORD m_nUse;//��ǰ�ṹ���Ƿ�ʹ��
	DWORD nCmdType;//�������ͣ��ļ������������
	DWORD dwBeginCmdTime;//�����ʱ��
	DWORD dwCmdSendTime;//���ʱ
	DWORD dwCmdTimeout;//���ʱʱ��
	char pszCmdID[32];   //�����id
	long nMode;			//��������ļ����0��ʾͬ�����ͣ�1��ʾ�첽����
	LPVOID pSocketRef;
	CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv;
	volatile long m_nCmdExecState;//����״̬0,1��ack,2:fail,3:success,4;timeout
	CExBaseList *pSysState;//Ӧ����ָ��

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
	void OnSendCmdStatusChanged(long nExecState,CSttSysState &oSysState);
#endif

	BOOL CheckTimeOut(DWORD dwCurTime);
	BOOL IsCmdExecState_Failure(){return m_nCmdExecState == STT_CMD_ExecStatus_FAILURE;}
	BOOL IsCmdExecState_Success(){return m_nCmdExecState == STT_CMD_ExecStatus_SUCCESS;}
    void Clear();
}STT_CMD_INFO;

//�ѷ������ʱ����
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
   static void Clear(CSttSocketDataBase_File *pSocket);
   static void Clear(CSttTestEngineClientData *pEngineClient);

	static long ProcessTimeOut(DWORD dwCurTime);
	static STT_CMD_INFO *AddSttFileCmd(CSttSocketDataBase_File *pSocket, DWORD nCmdType
		, DWORD dwCurrTime, long dwCmdTimeout, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv);

	static STT_CMD_INFO *AddSttCmd(CSttSocketDataBase_File *pSocket, DWORD nCmdType
		, char *pszCmdID, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL, long nSendMode = STT_CMD_Send_Sync);
	static STT_CMD_INFO *AddSttCmd(CSttSocketDataBase_File *pSocket, DWORD nCmdType
		, const CString &strCmdID, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL, long nSendMode = STT_CMD_Send_Sync);
	static long OnSocketReceive_FileCmd(CSttSocketDataBase_File *pSocket, DWORD nCmdType
				, DWORD nCmdPara, DWORD dwCurrTime); 
	static long OnSocketFailFinish_FileCmd(CSttSocketDataBase_File *pSocket, DWORD nCmdType
		, DWORD nCmdPara, DWORD dwCurrTime);

	static long OnSocketClosed(CSttSocketDataBase_File *pSocket);
	static BOOL HasCmdUsing();//zhouhj 2023.7.21 zhouhj �ر����ʱ,�ж��Ƿ����������ִ�����

#if !defined(_OA_MNGR_CLIENT) && !defined(_STT_FTP_SVR_)
	static long OnSocketReceive_FixedCmd(CSttSocketDataBase_File *pSocket, CSttSysState &oSysState,long nExecStatus); 
#endif

protected:
	STT_CMD_INFO* GetCmdEmptyInfo();
	BOOL In_HasCmdUsing();//zhouhj 2023.7.21 zhouhj �ر����ʱ,�ж��Ƿ����������ִ�����

private:
	STT_CMD_INFO m_arrHasSendCmd[STT_CMD_INFO_MAX_COUNT];
	long m_nMaxIndex;

	//���渳ֵ������
	CAutoCriticSection m_oCriticSection;
};

void *ProcessTimeOutProc(LPVOID lParam);

//2020-5-27
//���Ե�ʱ���Ƿ���Ҫ�жϳ�ʱ���ڴ��н�������ֵ�޸�Ϊ0����
extern long g_nSttCmdOverTimeEnable;

//2023-5-18  lijunqing ������Ե�ʱ����ʾ�����һЩ��Ϣ
extern long g_nSttCmdOverTimeViewLog;


BOOL Stt_Is_ExecStatus_NULL(long nExecStatus);
BOOL Stt_Is_ExecStatus_Ack(long nExecStatus);
BOOL Stt_Is_ExecStatus_Failure(long nExecStatus);
BOOL Stt_Is_ExecStatus_Success(long nExecStatus);
BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus);

#endif
