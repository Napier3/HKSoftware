#pragma once

#include "../SttCmd/SttSystemCmd.h"
#include "../SttCmd/SttAssistCmd.h"
#include "../SttCmd/SttAtsCmd.h"
#include "../SttCmd/SttDebugCmd.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttCmd/SttAdjustCmd.h"
#include "../SttGlobalDef.h"

#include "../SttSocket/TestTerminal/SttClientSocketBase.h"
#include "../SttAuthority/SttTestClientUserMngr.h"
#include "../TestClient/SttMacroTestInterface.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
#include "../SttRegisterCode.h"
#include "../SttCmd/GuideBook/SttContents.h"

//��ǰ���Զ�ID
extern DWORD g_nIDTester;
extern CDataGroup *g_pDeviceAttrs;

extern long g_nTimeOut_System;
extern long g_nTimeOut_Test;
extern long g_nTimeOut_Ats;
extern long g_nTimeOut_Debug;
extern long g_nTimeOut_Remote;
extern long g_nTimeOut_Adjust;
extern long g_nTimeOut_Meas; //2021-9-30  lijunqing

extern long g_nAtsGenTemplateForDebug;  //2022-3-14  lijunqing

class CSttTestEngineClientData
{
public:
	CSttTestEngineClientData();
	virtual ~CSttTestEngineClientData();
	virtual void PrepareFreeClientEngine();

	virtual CSttCmdOverTimeMsgRcv *GetCmdOverTimeMsgRcv(){	return NULL;	};

	void SetSttSvrUserMngrRef(CSttTestClientUserMngr *pSttSvrUserMngrRef);//	{	m_pSttSvrUserMngrRef = pSttSvrUserMngrRef;	}
	void SetTestEventInterface(CTestEventBaseInterface *pTestEventRcv);//	{	m_pTestEventRcv  = pTestEventRcv;	}
	CExBaseList* GetTestGlobalParas(){return &m_oTestGlobalParas;}

	//2022-10-23  lijunqing
	void SetSttCmdDataFormat(long nSttCmdDataFormat);

public:
	//���Զ��û����ѻ�����û�
	CSttTestClientUser m_oCurrUser;
	CSttClientSocketBase *m_pSttClientSocket;
	CSttTestClientUserMngr *m_pSttSvrUserMngrRef;//������û���������

	BOOL m_bHasLogin;
	BOOL m_bTestStarted;

protected:
	CTestEventBaseInterface *m_pTestEventRcv; //�¼����ն���
	
	//���Ե�ȫ�����ݣ����磺ExecStatus��IOverLoad��TestState��IsSuccess��
	//�μ�����02-ģ�黯���������ϵͳ������������1.6 ϵͳ״̬ͨ�����ݱ�
	//TestEngineData�������������ݣ�ȫ���ɵײ�͵������ģ���Ӧ�ò�ȷ��
	//���������Ҳ�����˵��������ͨ��ȫ�����ݡ�1.6 ϵͳ״̬ͨ�����ݱ�
	CExBaseList m_oTestGlobalParas;  

public:
	//ϵͳ��״̬
	long GetSysStateVal(const CString &strID, long nDefaultValue);
	BOOL IOverLoad();    //��������
	BOOL UOverLoad();    //��ѹ����
	BOOL OverHeat();    //����
	BOOL IBreak();    //������·
	BOOL UShort();    //��ѹ��·
	long ExecStatus();    //����ִ��״̬   0=ִ��ʧ��   1=ִ�гɹ�
	BOOL ExecStatus_Faild();
	BOOL ExecStatus_Success();

	long ConnectState();    //ͨѶ״̬   0=������ 1=���ӳɹ�  ����=�Զ���
	BOOL ConnectState_Idle();
	BOOL ConnectState_Testingt();
	BOOL ConnectState_Finish();
	
	long OutputState();    //���״̬   0=����   1=�ѿ�ʼ  2=�����
	BOOL OutputState_Idle();
	BOOL OutputState_Testing();
	BOOL OutputState_Finish();

	long CurrStateIndex();    //����״̬   0=���� 1=״̬1�ѿ�ʼ  2=״̬2�ѿ�ʼ  ����
	BOOL ErrCmd();    //�����������������ID
	BOOL DataNotExist();    //���󲻴��ڲ����ڵ����ݣ������ļ�����ĿID��
	BOOL IsSuccess();    //�Ƿ�ɹ�   0=ʧ��    1=�ɹ�
	long TestTimeLong();    //����ʱ���ܳ�������ĿԤ�Ʋ���ʱ�䳤��

	long TestState();    //����״̬   0=����  1=�ѿ�ʼ 2=����ɣ�������
	BOOL TestState_Idle();
	BOOL TestState_Testingt();
	BOOL TestState_Finish();

public:
	//connect device
	virtual BOOL IsConnectServerSucc();
	virtual BOOL ConnectServer(const CString &strIPServer, long nPort){return FALSE;}
	virtual void OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket = TRUE);
	virtual void DisConnect();
	BOOL IsMatchIDTest(long nIDTest){	return m_oCurrUser.IsMatchIDTest(nIDTest);	}

public:
    virtual long SendBuffer(BYTE *pBuf,long nLen);
	//���ڳ�ʱ�����߼�
	virtual long SendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long SendCmdAsync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdOverTimeMsgRcv *pSttCmdOverTimeMsgRcv=NULL, BOOL bCompress=FALSE,BOOL bReset=TRUE);
	virtual long SendCmdOnly(CSttCmdBase *pCmd, BOOL bCompress=FALSE,BOOL bReset=TRUE);

	//system command
	long System_SetSysConfig(CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_GetSysConfig(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local_Test(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local_ATS(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local(const CString &strTestID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Logout(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Request(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Authority(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	//2022-3-23  lijunqing
	long System_GetDirs(CDataGroup *pParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_DownFile(CDataGroup *pParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	
	//Remote cmd
	long Remote_Bind(CSttTestRemoteRegister *pRegister,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_Query(const CString &strCode_Register=_T(""),BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_Register(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_UnRegister(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	
	//Smart Test Terminal : Test Command
	long Test_SetParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Preset test parameters
	long Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Test_StartTest(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL, BOOL bSendCmdAsync=FALSE);	//start testing
	long Test_StopTest(const CString &strMacroID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);	//Stop testing
	long Test_GetReport(const CString &strMacroID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Get report data
	long Test_CloseDevice(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Turn off the device
	long Test_GetSystemState(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Query system status
	long Test_SendHeartbeat();

	//У׼���adj-cmd
	long Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_WriteFile(BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);

	//2021-9-30  lijunqing
	long Meas_Read(BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);

	//2020-10-09 �ļ�����  lijunqing
	//���ļ� strRealFilePath��Ŀ���ļ����·�������磺"Config/DeviceSystemParas.xml"  strDestFilePath,���ؾ���·��
	long ReadFile(const CString &strSrcFileRealPath, const CString &strDestFilePath,CSttSocketFileTransferProgress *pProgress);
	//д�ļ���strSrcFilePath�����ؾ���·����strSrcFileRealPathĿ���ļ����·��
	long Write(const CString &strSrcFilePath, const CString &strDestFileRealPath,CSttSocketFileTransferProgress *pProgress);
	
	//���ϻط�����
	//��λ���������ǣ��ֶ�����������ݷ����������
	long Test_SendTrigger();
	long Comtrade_SendDataFinish(long nIndex,long nSendLen,BOOL bLast);
	long Comtrade_SendDataStart(long nIndex,long nSendLen);

	//ats cmd
	long Ats_CreateTest(CExBaseList *pSttParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData=NULL);
	long Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);

	long Ats_StartTest(CDataGroup *pTestMacroUI=NULL, CDataGroup *pUIParas=NULL, CDataGroup *pCommCmd=NULL, CSttContents *pCharacteristic=NULL, 
		BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,const CString &strDvmFile = _T(""),const CString &strPpXmlFile = _T(""), long nTestMode = TEST_MODE_SINGLETEST);//20230227 zhouhj ����strDvmFile
	long Ats_StopTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CloseTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_SetItemState(CExBaseList *pSttParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestItem (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestAllFailedItems(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath=_T(""),BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long GetSystemState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
		,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs);
	long Ats_QueryAtsFile(long nGetGbxmlFile=1,long nGetPpxmlFile=1,long nGetDvmFile=1,long nGetGbrptFile=1,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Process_Cmd_Ats_InputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Ats_ManuTrigger(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);//yyj �ֶ����� 20220224
	long Ats_SetTestParas(const CString &strDeviceID, CExBaseList *pTestParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);  //2024-2-28 ���ò��Բ��� shaolei

	//2022-1-8 LINUX�ѻ��Լ��ƶ���Ӧ�ýӿ�ָ��
	//strRetMode: gbxml=ȫģ��   dscxml=ģ��ṹ

	//20230227 zhouhj ����strDvmFile   2024.7.1 chenling ����ppxml-file
    long Ats_GenerateTemplate(CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup*pCommcmd
		, CSttContents *pCharacteristic, const CString &strRetMode, long nHasDigital,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL,const CString &strDvmFile = _T(""),const CString &strPpXmlFile = _T(""));//�������ܵ�ģ������
    long Ats_GenerateTemplate(CDataGroup *pGenParas,const CString &strRetMode, long nHasDigital,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL,const CString &strDvmFile = _T(""),const CString &strPpXmlFile = _T(""));//�๦�ܵ�ģ������
    long Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID, CDataGroup *pTestMacroUI, CDataGroup *pUIParas
		, CDataGroup *pCommCmd, CSttContents *pCharacteristic, const CString &strDvmFile, const CString strTestClass, const CString &strRetMode, long nHasDigital
		, long nRepeatTimes, long nRptTitle, long nTitleLevel, long nSynMode, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
    long Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID, CDataGroup *pItemParas,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL, const CString &strContents=_T(""), const CString &strRsltExpr=_T(""));
	long Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString& strMacroID, const CString &strItemParas,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	//2022-3-23  lijunqing
	long Ats_SaveTemplate(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI, CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData, long nSynMode = STT_CMD_Send_Sync);
	long Ats_SaveTest(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI, CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData, long nSynMode = STT_CMD_Send_Sync);
	long Ats_ExportWordRpt(const CString &strPath, const CString& strFileName, CDataGroup *pParas, bool bDoEvents, CSttCmdData *pRetData);
	long Ats_OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile, bool bDoEvents, CSttCmdData *pRetData);
	long Ats_GenerateItems_Items(CDataGroup *pGenItemsParas, CSttContents *pContents=NULL, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL, long nSynMode = STT_CMD_Send_Sync);//�๦�ܵ�ģ������
	long Ats_OpenGbrptFile(const CString &strGbrptFile, const CString &strDvmFile, const CString &strSmartTestRunMode=SmartTest_Run_Mode_Server,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);//�򿪲��Լ�¼
	long Ats_AdjustMainWnd(LONG hMainParent, LONG hLogParent, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);//��������������
	long Ats_ExportRpt(const CString &strDeviceID, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_UpdateItem(const CString &strItemPath, CDataGroup *pItemParas, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType=_T(""), bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_QueryItem(const CString &strItemPath, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_AdjustReport(const CString &strDeviceSN, long nShowWnd, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ClearReportsRslts(CDataGroup *pParas, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_AddSafety(CDataGroup *pParas, CExBaseList *pDatas, CExBaseList *pMsgs, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL, long nSynMode = STT_CMD_Send_Sync);//pParas�����Ŀ���ơ�ID��·������Ϣ

	//debug command
	long Debug_Command(const CString &strCmdID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetProcessState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetMemState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetTestParas(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetTestReports(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetBasicTestParas(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetBasicReportData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetDrvTestData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetDrvReportData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetFpgaData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetSocketConnect(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_ConfigDebug(CDataGroup *pGroup,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_ConfigDebug(CSttDebugCmd *pCmd,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_ConfigDebug(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
		,long nLogDebugInfor,long nNoChangeWhenSame, long nSpyCmd);
	long Debug_ConfigDebug(const CString &strDebugParaID, long nValue); //2020-12-04  lijunqing add spy-cmd

	//////////////////////////////////////////////////////////////////////////
	//�������Ϣ����
	long On_SysState_Test(CSttSysState &oSysState);
	long On_SysState_Ats(CSttSysState &oSysState);
	long On_SysState_Adjust(CSttSysState &oSysState);
	long On_SysState_IOT(CSttSysState &oSysState);


public:
	virtual long Process_SysState_System_Login(CSttSysState &oSysState);
	virtual long Process_SysState_System_Logout(CSttSysState &oSysState);
	virtual long Process_SysState_System_Request(CSttSysState &oSysState);
	virtual long Process_SysState_System_Authority(CSttSysState &oSysState);
	virtual long Process_SysState_System_GetSysConfig(CSttSysState &oSysState);
	virtual long Process_SysState_System_SetSysConfig(CSttSysState &oSysState);
	virtual long Process_SysState_BroadcastUserMngr(CSttSysState &oSysState);
	virtual long Process_SysState_System_ReadMeas(CSttSysState &oSysState); //2021-10-2  lijunqing
	virtual long Process_SysState_System_LiveUpdate(CSttSysState &oSysState);
	void OnLogout();

	void On_SysState_Debug(CSttSysState &oSysState);

	//////////////////////////////////////////////////////////////////////////
	//���Բ���
	void On_SysState_Test_UpdateTestGlobalParas(CSttSysState &oSysState);

	virtual long Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	virtual long Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);	
	virtual long Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Meas(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
    virtual long Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);
	
public:
	//ֻ�о��е�������Ȩ�޵Ĳ��Զ˶�ʱ��������
	virtual void OnSendHeartbeatTimer();
	virtual void OnSendHeartbeatTimer_NotCheakAuthority();//20220713 zhouhj ��������������������testȨ��

    //2022-2-12  lijunqing
    virtual void AddPkgDispatch(CSttPkgDispatchInterface *pPkgDispatch){};
	virtual void RemovePkgDispatch(CSttPkgDispatchInterface *pPkgDispatch){};
};
