#pragma once

#include "SttNativeClientTestEngine.h"
#include "SttNativeTestEngineInterface.h"
#include "../../../IotAtsMngr/Module/MqttCmmInterface.h"
//2020-10-17  lijunqing


class CSttNativeTestEngine_Mqtt : public CSttNativeTestEngineInterface
	, public CMqttMsgProcessInterface
{
//MQTT�¼�����ӿڣ���CMqttMsgInterface�������
//class CMqttMsgProcessInterface
public:
	//�����յ���MQTT�������ƥ�䣬���ƥ��ɹ����򷵻�TRUE�����򷵻�FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT��Ϣ����
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT���ⶩ�Ľӿں�����MQTT Client���ӳɹ��󣬱�����CMqttMsgProcessInterface
	//������ص�����
	virtual BOOL MqttSubscribeTopic();

	//MQTTȡ�����ⶩ�Ľӿں�����MQTT Client�Ͽ����Ӻ󣬱�����CMqttMsgProcessInterface
	//Tȡ��������ص�����
	virtual BOOL MqttUnSubscribeTopic();

	CString m_strBentchSN;  //����̨SN

public:
	void InitMqttTopicCmbn(const CString &strAtsServiceSN, const CString &strBentchSN);

protected:
	char* GetAtsCmdID(CSttMqttTopicParser &oSttMqttTopicParser);
	void InitMqttTopicCmbn(CSttMqttTopicParser &oSttMqttTopicParser);
	CSttMqttTopicCmbn *m_pMqttTopicCmbn;
	long m_nXmlRWType;

public:
	virtual long GetXmlRwType()	{	return m_nXmlRWType;	}
	virtual void SetXmlRwType(long nType)	{	m_nXmlRWType = nType;	}
    virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam);
    virtual void OnSysMessage(WPARAM wParam, LPARAM lParam);
    //2020-11-24  lijunqing LINUX  post msg to ats
    virtual void OnEngineDataDeleted(const CString &strDeviceID);

public:	//CSttPkgDispatchInterface
	//2022-2-12  lijunqing
	virtual void DispatchMsg(unsigned char *pBuf, long nLen);

public: //CSttNativeTestEngineInterface
	virtual long X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState) ;
	virtual long X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs) ;

private:
	CSttNativeTestEngine_Mqtt();
	virtual ~CSttNativeTestEngine_Mqtt();

	static CSttNativeTestEngine_Mqtt* g_pNativeTestEngine;
	static long g_nNativeTestEngineRef;

public:
	static CSttNativeTestEngine_Mqtt* Create(const CString &strBentchSN, CSttSmartTest *pSttSmartTest);
	static void Release();
	static CSttNativeTestEngine_Mqtt* GetNativeTestEngine();

public:
	//2020-4-6  lijq
	virtual void InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort=0);
	virtual void ExitSttServerEngine();

	virtual void OnSocketClose(void *pSocket);
	virtual long SendSysState(CSttSysState *pSysState);

	virtual BOOL SendBufferToChildren(void *pExceptSocket,BYTE *pBuf,long nLen);	
	virtual long Process_Cmd_System_Request(void *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Authority(void *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_SysState(void *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Register(CSttSysState &oSysState);
	virtual long Process_SysState_UnRegister(CSttSysState &oSysState);
	virtual long Process_SysState_InputData(void *pClientSocket,CSttSysState &oSysState);

	//�յ���������ȼ���Ƿ���Ȩ�ޣ���Ȩ���򷵻�ʧ��
	BOOL CheckBeforeProcessCmdTest(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	BOOL CheckBeforeProcessCmdAts(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

    // 2020-05-27  shaolei  add    �����Ʋ���
    virtual long ProcessCmd_CloudTest(void *pClientSocket, CSttSystemCmd &oSysCmd);
	//����Ats��Զ�̵�¼
	virtual long Process_Cmd_System_Login(void *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(void *pClientSocket, CSttSystemCmd &oSysCmd);
	//�˳���¼�����������Ƿ�ֹͣ����
	virtual void CheckStopTestAfterReleaseUser();
	//ֻ�����е�������Ȩ�޵Ĳ��Զ�������ʱ
	virtual void CheckHeartbeatOverTime();
	
public:
    //2020-5-18  lijunqing
	//virtual long Process_Cmd_Ats(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
    virtual long Process_Cmd_Ats(void *pClientSocket, CSttAtsCmd &oAtsCmd);

	//2022-4-20 shaolei lijunq 
	//virtual long Process_Cmd_Test(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	long ReturnExecReply(CSttAtsCmd *pAtsCmd, long nCmdExecStatus,CSttCmdData *pRetData=NULL);

protected:
    CDvmDataset* Ats_GetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_SetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_ConfigDevice(CSttAtsCmd &oAtsCmd);

    long Process_Cmd_Ats_CreateTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StartTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StopTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestItem(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestFrom(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestAllFailedItems(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetItemReport(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetReportFile(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetSystemState(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CreateDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConnectDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetDataset(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetDataset(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_RunProcedure(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigEngine(void *pClientSocket, CSttAtsCmd &oAtsCmd);

	long Process_Cmd_Ats_FinishInputData(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_QueryAtsFile(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetItemState(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GenerateTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateItems(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateMacroTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetItemPara(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Procss_Cmd_Ats_SetItemPara_SystemConfig(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ManualTrigger(void *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SaveTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SaveTest(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportWordRpt(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenGbrptFile(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustMainWnd(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportReport(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_QueryItem(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_UpdateItem(void *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustReport(void *pClientSocket, CSttAtsCmd &oAtsCmd);


    void Return_Ats_Success(void *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState=STT_CMD_ExecStatus_SUCCESS, CDvmDataset *pDatas=NULL, CExBaseObject *pGuideBook = NULL);
    void Return_NoDevice(void *pClientSocket, CSttSysState &oSysState);
    void Return_Ats_Event(void *pClientSocket, CSttSysState &oSysState);
    long ValidateSmartTest(void *pClientSocket, CSttSysState &oSysState);
	//shaolei 20220326 
	void Return_DeviceParameter_AfterLogin(void *pClientSocket, CSttSysState &oSysState);

public:
	//�������Զ�����
    CSttNativeClientTestEngine  *m_pNativeClientTestEngine;
	//long m_nSttCmdDataFormat;  �������m_nXmlRWType�ظ���ע�͵�
	long m_nRecvHeartbeatCounter;

    //SmartTest  Ŀǰֻ����װ�õĲ���
    CSttSmartTest *m_pSmartTest;
	void SetSttSmartTest(CSttSmartTest *pSmartTest)	{	m_pSmartTest = pSmartTest;	}
	
public:
	virtual long ConnectCloudServer(const CString &strIPServer,long nPort);
	void DisConnectCloudServer();
    BOOL IsConnectColudServerSuccess();
	virtual long Register(CSttCmdData *pRetData=NULL);
	virtual long UnRegister(CSttCmdData *pRetData=NULL);
	virtual long Ats_InputData(void *pClientSocket,CDataGroup *pDatas,CExBaseList *pMsgs);
	
	//���ڳ�ʱ�����߼�
	virtual long SendCmd(CSttCmdBase *pCmd,long nTimeOut=3000,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	//���ڳ�ʱ�����߼�
	virtual long SendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE);
	

public:
	void InitClientUserMngr();
	void AttachSttAtsInterface(CSttAtsInterface *pSttAtsInterface){	m_pSttAtsInterface = pSttAtsInterface;	}
	void AttachRefAtsUser(CSttTestClientUser *pRefAtsUser);

	BOOL AuthorityToAtsUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser);
	BOOL AuthorityToTestUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser);
	virtual long AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess=TRUE);
	virtual long AuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest);
	BOOL IsCanAuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest);

	CSttTestClientUser* User_Login(void *pClientSocket, CSttSystemCmd &oSysCmd);

	//���û��ClientEngineȨ�ޣ����ͷ�NativeClient��TestȨ��
	long CheckCancelNativeClientAuthority();

	//���û��AtsȨ�ޣ����ͷ�TestControl��ClientEngineȨ��
	long CheckUpdateTestControlAuthority();

private:
	//���Կ��ƹ���ӿڣ������н����TestMain���ɽ�������������û�н����TestMain,��TestMainCore����
	CSttAtsInterface *m_pSttAtsInterface;

/*
	//�Զ�����Ȩ���û�����Զ�̵������Ծ���ClientEngineȨ��
	CSttTestClientUser m_oTestControlUser;

	//TestMain��������û����޽���ʱΪNULL
	//ID_Terminal=STT_TERMINAL_TYPE_NATIVE_ATSΪ�Զ����Խ����û���
	//����ΪSTT_TERMINAL_TYPE_NATIVE_TESTΪ�������Խ����û�
	CSttTestClientUser *m_pRefAtsUser;
*/

//2020-11-25  lijunqing
public:
    virtual void OnTimer();

protected:
	long ReturnSysState(void *pComm, CSttSysState *pSysState, long nSpyAllCmd);
	long ReturnSysStateToChildren(void *pComm,CSttSysState *pSysState);
	long X_SendSysState(void *pComm, CSttSysState *pSysState, long nSpyAllCmd);
	long RetFailureSysState(CSttCmdBase *pCmd);
	long X_SendCmd(void *pComm, CSttCmdBase *pSttCmdBase, long nSpyAllCmd);

};

extern CSttNativeTestEngineInterfaces *g_theNativeTestEngine;
extern CSttTestAppCfg *g_pTheSttTestAppCfg ;
