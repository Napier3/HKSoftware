#ifndef _SttMqttOverTimeMngr_h_
#define _SttMqttOverTimeMngr_h_

#ifdef _PSX_QT_LINUX_
#include "SttMqttClient_QT.h"
#else
#include "SttMqttClient.h"
#endif


//////////////命令超时机制/////////////////
#define STT_MQTT_CMD_INFO_MAX_COUNT  100
#define STT_MQTT_CMD_INFO_EXPAND_COUNT  100

//命令执行状态	ExecStatus	0=未处理  1=ACK 2=执行失败，3=执行成功
#define STT_MQTT_CMD_ExecStatus_NULL		0
#define STT_MQTT_CMD_ExecStatus_ACK		1
#define STT_MQTT_CMD_ExecStatus_FAILURE	2
#define STT_MQTT_CMD_ExecStatus_SUCCESS	3
#define STT_MQTT_CMD_ExecStatus_TIMEOUT	4
#define STT_MQTT_CMD_ExecStatus_SocketClose	5

#define STT_MQTT_CMD_Send_Sync	0
#define STT_MQTT_CMD_Send_Async	1


//已发送命令结束或超时接口：
class CSttMqttOverTimeMsgRcv
{
public:
	virtual void OnSendCmdFailFinish(LPVOID pMqttClient, DWORD nCmdType, char *pszMqttTopic){};
	virtual void OnSendCmdFinish(LPVOID pMqttClient, DWORD nCmdType, char *pszMqttTopic){};
	virtual void OnSendCmdOverTime(LPVOID pMqttClient, DWORD nCmdType, char *pszMqttTopic) = 0;
};

//已发送命令信息类
typedef struct stt_mqtt_cmd_info
{
	DWORD m_nUse;//当前结构体是否被使用
	DWORD m_nCmdType;//命令类型：文件命令，其他命令
	DWORD m_dwBeginCmdTime;//命令发送时间
	DWORD m_dwCmdSendTime;//命令超时
	DWORD m_dwCmdTimeout;//命令超时时间
	char m_pszMqttTopic[256];   //命令的id
	long m_nMode;			//如果不是文件命令，0表示同步发送，1表示异步发送
	LPVOID m_pMqttClient;
	CSttMqttOverTimeMsgRcv *m_pSttMqttOverTimeMsgRcv;
	long m_nCmdExecState;//运行状态0,1：ack,2:fail,3:success,4;timeout

	void SetUsed(DWORD nUsed){m_nUse = nUsed;}
	BOOL IsUsed()									{	return m_nUse;	}
	BOOL IsTimeOut(DWORD dwCurTime)
	{
		if (m_dwCmdSendTime == 0)
		{// call first time
			m_dwCmdSendTime = dwCurTime;
		}

		if (m_dwCmdSendTime > dwCurTime)
		{//2021-8-20  lijunqing long==>> overflow
			m_dwCmdSendTime = dwCurTime;
		}

		return (dwCurTime - m_dwCmdSendTime >= m_dwCmdTimeout);
	}
	void OnSendCmdFinish(BOOL bSuccess=TRUE);


	BOOL CheckTimeOut(DWORD dwCurTime);
	BOOL IsCmdExecState_Failure(){return m_nCmdExecState == STT_MQTT_CMD_ExecStatus_FAILURE;}
	BOOL IsCmdExecState_Success(){return m_nCmdExecState == STT_MQTT_CMD_ExecStatus_SUCCESS;}
    void Clear();
}STT_MQTT_CMD_INFO;

//已发送命令超时管理
class CSttMqttOverTimeTool
{
private:
	CSttMqttOverTimeTool();
	virtual ~CSttMqttOverTimeTool();

	static CSttMqttOverTimeTool *g_pSttMqttOverTimeTool;
	static long g_nSttMqttOverTimeToolRef;

	CSttMqttOverTimeMsgRcv *m_pSttMqttOverTimeMsgRcv;

public:
	static CSttMqttOverTimeTool *Create();
	static void Release();
	static CSttMqttOverTimeTool *GetSttMqttOverTimeTool();
	static void AttachCmdOverTimeMsgRcv(CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv);
   static void Clear(LPVOID pMqttClient);

	static long ProcessTimeOut(DWORD dwCurTime);

	static STT_MQTT_CMD_INFO *AddSttMqtt(void *pMqttClient, DWORD nCmdType
		, char *pszMqttTopic, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv=NULL, long nSendMode = STT_MQTT_CMD_Send_Sync);
	static STT_MQTT_CMD_INFO *AddSttMqtt(void *pMqttClient, DWORD nCmdType
		, const CString &strCmdID, DWORD dwCurrTime=0, long dwCmdTimeout=0, CSttMqttOverTimeMsgRcv *pSttMqttOverTimeMsgRcv=NULL, long nSendMode = STT_MQTT_CMD_Send_Sync);
	static long OnSocketReceive_FileCmd(void *pMqttClient, DWORD nCmdType
				, DWORD nCmdPara, DWORD dwCurrTime); 
	static long OnSocketFailFinish_FileCmd(void *pMqttClient, DWORD nCmdType
		, DWORD nCmdPara, DWORD dwCurrTime);

	static long OnSocketClosed(void *pMqttClient);


protected:
	STT_MQTT_CMD_INFO* GetCmdEmptyInfo();

private:
	STT_MQTT_CMD_INFO m_arrHasSendCmd[STT_MQTT_CMD_INFO_MAX_COUNT];
	long m_nMaxIndex;
};

void *ProcessTimeOutProc(LPVOID lParam);

//2020-5-27
//调试的时候，是否需要判断超时，内存中将变量的值修改为0即可
extern long g_nSttMqttOverTimeEnable;


BOOL Stt_Is_ExecStatus_NULL(long nExecStatus);
BOOL Stt_Is_ExecStatus_Ack(long nExecStatus);
BOOL Stt_Is_ExecStatus_Failure(long nExecStatus);
BOOL Stt_Is_ExecStatus_Success(long nExecStatus);
BOOL Stt_Is_ExecStatus_Timeout(long nExecStatus);

#endif
