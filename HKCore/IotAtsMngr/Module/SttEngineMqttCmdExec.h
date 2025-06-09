#pragma once

#include "../../SttStudio/Module/SttSocket/SttSocketDataBase.h"
#include "../../SttStudio/Module/SttCmd/SttTestCmd.h"
#include "MqttPpTemplate/MqttPpTemplate.h"

#define STT_MACRO_ID_MSGRCVSEND			_T("MsgSendRecv")
#define STT_MACRO_ID_MONITORPRASE		_T("MonitorPrase")
#define STT_MACRO_ID_WARNINGPRASEREPLY	_T("WarningPraseReply")

//���Ĺ��̣�group id
#define STT_PARA_ID_PKG			_T("Pkg")	
#define STT_PARA_ID_RSLTJUDGE	_T("RsltJdg")
#define STT_PARA_ID_RSLTDSC		_T("RsltDsc")

class CSttEngineMqttCmdExec : public CExBaseList
{
public:
	CSttEngineMqttCmdExec(CSttSocketDataBase *pRefSocket);
	virtual ~CSttEngineMqttCmdExec();

	//m_strID:��Ӧװ��ID
	CSttSocketDataBase *m_pRefSocket;
	CSttTestCmd m_oCurTestCmd;//��ǰ��������
	CMqttPpTemplate m_oMqttPpTemplate;	//��Լģ��
	
	BOOL OnMqttMsgRecieve(CSttSysState &oSysState);
public:
	long ReturnSysState(long nCmdExecStatus,CSttCmdData *pRetData=NULL,CSttSocketDataBase *pSocket=NULL,CSttTestCmd *pTestCmd=NULL);

	long Process_Cmd_Test(CSttTestCmd &oTestCmd);
	long Process_Cmd_Test_SetParameter(CSttTestCmd &oTestCmd);	
	long Process_Cmd_Test_StartTest(CSttTestCmd &oTestCmd);
	long Process_Cmd_Test_StopTest(CSttTestCmd &oTestCmd);

	BOOL PublicTestCmd(CSttTestCmd &oTestCmd);
	CString GetCurMacroID();
	void UpdateSysState(CSttSysState &oSysState);
	long UpdateSysState_MsgSendRecv(CSttSysState &oSysState);
	long UpdateSysState_MonitorPrase(CSttSysState &oSysState);
	long UpdateSysState_WarningPraseReply(CSttSysState &oSysState);
	long ProcessRecvPacket(char *pBuf,long nLen,CMqttPpProcedure *pProcedure,CMqttPpPrase **ppPrase);
public:
	DWORD m_dwStartTime;	//��ʱ��ʱʱ��
	long m_nTimeOut;		//��ʱ��-1���޳�ʱ
	BOOL IsCmdTimeOut();
	void ReplyCmdTimeOut();
	long UpdateTimerOut(const CString &strCurCmd){return 5000;}

protected:
	BOOL m_bExitThread;
	BOOL m_bSuspendThread;

	//��鵱ǰItem�Ƿ���ɻ�ʱ�߳�
	HANDLE m_pThread;
	static void *TestCmdExecThread(LPVOID lParam);
};

///////////////////////
void UpdateRsltJudge(long nRslt,CSttParas *pParas);