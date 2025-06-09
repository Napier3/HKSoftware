#pragma once
#include "MqttEngineBase.h"
#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"
#include "../../../SttStudio/Module/SttCmd/SttSysState.h"


class CSttMqttEngineBase:public CMqttEngineBase
{
public:
	CSttMqttEngineBase();
	virtual ~CSttMqttEngineBase();

public:
	virtual void BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat);

	//��ǰ�����Ӧ��
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData);
	virtual long ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,const CString &strDeviceID=_T(""));

	//2021-7-22  lijunqing  ���ӷ���ϵͳ״̬�ĸ��ֺ�������
	//ǰ����Ϊ���ݺ�����û���Ϣ���أ�����������������ֱ��������Ϊ�˼������д��벻Ҫ��������
	//���º�����shaolei���������޸ģ����������βεȣ�  20210727
	virtual long ReturnSysState_REPLY(CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType);
	virtual long ReturnSysState_EVENT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID, char *pszRetCmdType);

	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszRetCmdType);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdBase *pSttCmd, long nCmdExecStatus, const CString &strDeviceID);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, int nCmdType, char *pszCmdID, BOOL bIsSuccess);
	virtual long ReturnSysState(CSttCmmOptrInterface *pCmmOptrInterface, CSttSysState *pSysState, BOOL bSpyAllCmd);

};