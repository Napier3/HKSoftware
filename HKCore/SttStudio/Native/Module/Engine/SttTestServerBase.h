#pragma once

#include "SttTestEngineServerBase.h"
#include "../SttSocket/SttServerSocketDataBase.h"
#include "../SttTestBase/SttXmlSerialize.h"
#include "SttServerTestCtrlCntr.h"

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_IDE_QT_
#include "QT/SttMqttEngine.h"
#else
#endif
#endif

class CSttTestServerBase : public  CSttTestEngineServerBase
{
public:
	static CSttTestServerBase* GetServerEngine()  {   return g_pSttTestServerEngine;  }

protected:
	static long m_nSttTestServerEngineRef;
	static CSttTestServerBase *g_pSttTestServerEngine;

protected:
	CSttTestServerBase();
	virtual ~CSttTestServerBase();

	void Ret_SysState(CSttSysState &oSysState, CSttSocketDataBase *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool);
	void Ret_Cmd_SysState(CSttCmdBase &oCmd, CSttSocketDataBase *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool);

public:
	virtual long SendSysState(CSttSysState *pSysState);

	virtual long Process_Heartbeat(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Trigger(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Adjust(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_System(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual long Process_Cmd_Comtrade(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataFinish(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataStart(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual long Process_Cmd_Adjust(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_System(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	//�յ���������ȼ���Ƿ���Ȩ�ޣ���Ȩ���򷵻�ʧ��
	BOOL CheckBeforeProcessCmdTest(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	//�˳���¼�����������Ƿ�ֹͣ����
	virtual void CheckStopTestAfterRelease(CSttSocketDataBase *pClientSocket);
public:
	CSttTestCmd m_oSttTestCmd;

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_IDE_QT_
	CSttMqttEngine m_oMqttEngine;
#else
#endif
#endif

public:
	CSttTestClientUser *GetNativeClientUser();
	CSttSocketDataBase *GetNativeClientSocket();
    virtual void InitSttServerEngine(const char *pszIP, int nTestPort,int nReplayPort = 0);
	virtual void ExitSttServerEngine();
	virtual void OnTimer();
	virtual void OnCallBackTimer(){}
	//ֻ�����е�������Ȩ�޵Ĳ��Զ�������ʱ
	virtual void CheckHeartbeatOverTime();

	void ReturnTestStateEvent(long nEventType, PSTT_TIME pTime, bool bWithEvent);
	void ReturnTestEvents();
	void ReturnSysStatesToChildren(int nDataType);

protected:
	//2020-04-6  lijq
	void Ret_Test_SysState(CSttSysState &oSysState, CSttSocketDataBase *pSttSocketDataBase
						   , BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
						   , PSTT_TIME pTime, bool bWithEvent);//zhouhj 20210925 ����������
	void Ret_Test_SysState(CSttSysState &oSysState, CSttSocketDataBase *pSttSocketDataBase
						   , BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
						   , char *strRetType, PSTT_TIME pTime, bool bWithEvent);
	void Ret_Test_SysState(CSttSysState &oSysState, CSttSocketDataBase *pSttSocketDataBase
						   , BOOL bBasic, BOOL bParas, BOOL bReport , BOOL bSearchResult
						   , const CString &strRetType, PSTT_TIME pTime, bool bWithEvent);
	long ReturnSysState(long nCmdExecStatus,CSttCmdData *pRetData=NULL);

	//2021-03-12 zhoulei
	void ReturnTestParaCheckFail();
protected:
	virtual long Process_Cmd_Test_SetParameter(CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_UpdateParameter(CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_StartTest(CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_StopTest(BOOL bReturnAsk=TRUE);
	virtual long Process_Cmd_Test_CloseDevice();

public:
	virtual long Process_Cmd_Test_GetReport(BOOL bParas=TRUE);
	virtual long Process_Debug_GetProcessState(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetMemState(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetTestParas(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetTestReports(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetBasicTestParas(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetBasicReportData(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetDrvTestData(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetDrvReportData(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetFpgaData(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_GetSocketConnect(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_Debug_ConfigDebug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd);

	virtual long Process_Cmd_System_ReadMeas(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_GetSystemState(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	//У׼�����
	virtual long Process_Cmd_Adjust_Adjust(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Ajust_ReadDeviceParameter(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Ajust_WriteFile(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd);
	//����������������ϻط�����
	long Comtrade_SendRequestData(long nIndex);

	//������Ӧ�������ݿ�ʼ
	long Comtrade_SendDataStartAck(long nIndex);
	//�����߳̽��������ݺ������������ݺ�SttReplayTest�����߼�
	void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen);

	void StopAutoTestEvent();  //����ֹͣ�Զ������¼�
};


//extern CSttServerTestCtrlCntr  *g_pTestCtrlEngine;
