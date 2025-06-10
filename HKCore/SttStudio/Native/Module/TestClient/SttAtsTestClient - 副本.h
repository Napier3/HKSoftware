#pragma once
#include "SttMacroTestInterface.h"
#include "../Engine/SttTestEngineClientData.h"
#include "../Engine/SttTestEngineBase.h"
#include "../SttTest/Common/tmt_result_def.h"
#include "../SttTestAppConfig/SttTestAppConfigTool.h"
#include "../SttCmd/GuideBook/SttContents.h"

class CSttAtsTestClient : public CSttTestMsgViewInterface, public CTestEventInterface
{
public:
	CSttAtsTestClient(void);
	virtual ~CSttAtsTestClient(void);

	void SttOpen(const CString &strTestAppCfgFile);
	CSttTestAppCfg* GetSttTestAppCfg();

public:
	CSttTestEngineClientData *m_pXClientEngine;//�����ɹ���ö����Tool�л�ȡ
	BOOL m_bTestAppConnect;
	//֪ͨӦ�ý���ˢ��
	CEventResult m_oCurrEventResult;	//����ˢ��
	CEventResult *m_pLastEventResult;	//�¼����һ��

	CAtsEventInterface *m_pAtsEventRcv;

public:
	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oFlushEventList;
	void AppenEventInfo(CEventResult *pEventInfo);
	void GetEventInfo(CExBaseList &oEventInfoList);
	BOOL m_bLockFlag; //1:ͨ�����顢г����0:����

	virtual BOOL IsAtsRetCmd(CSttParas *pParas);

	CEventResult *InitEvent(const CString &strEventID,double fTime,double fRealTime
		,const CString &strTimeStr/*,BOOL bUpdateLastResult=TRUE*/); //yyj modify 20210902
	void SetLockFlag(BOOL bFlag){ m_bLockFlag = bFlag; }
	void OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas);

	virtual void OnUpdateSyncTime(CDataGroup *pRtSyncTime);
	//GpsTime(long nSyn, long nSecond,long nNSecend, long n4G, long nWifi, long nBle,
	//	long nPowerAC, long nBatCap,long nUSB);//zhouhj 20210827����Gpsʱ��    //���ӵ����Լ�USB״̬ sf 20220228

	virtual BOOL ConnectAtsTestServer(const CString &strIP,long nPort,const CString &strSoftID = STT_SOFT_ID_ATS);
	virtual BOOL ConnectAtsTestServer(const CString &strTestAppIP = _T(""));
	virtual void FreeXClientEngine();
	virtual BOOL IsConnectSuccess();

	//ats cmd
	virtual long Ats_CreateTest(CExBaseList *pSttParas);
	virtual long Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);

	virtual long Ats_StartTest(CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup *pCommCmd=NULL, CSttContents *pCharacteristic=NULL, BOOL bDoEvents=TRUE, 
		CSttCmdData *pRetData = NULL,const CString &strDvmFile = _T(""), long nTestMode = TEST_MODE_SINGLETEST);//20230227 zhouhj ����strDvmFile
	virtual long Ats_StopTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_CloseTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_SetItemState(CExBaseList *pSttParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_TestItem (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_TestAllFailedItems(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath=_T(""),BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_GetSystemState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
		,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs);
	virtual long Ats_QueryAtsFile(long nGetGbxmlFile=1,long nGetPpxmlFile=1,long nGetDvmFile=1,long nGetGbrptFile=1,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Process_Cmd_Ats_InputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	virtual long Ats_SetTestParas(const CString &strDeviceID, CExBaseList *pTestParas, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);  //2024-2-28 ���ò��Բ��� shaolei

	//20230227 zhouhj ����strDvmFile
	virtual long Ats_GenerateTemplate(CDataGroup *pTestMacroUI, CDataGroup *pUIParas,CDataGroup *pCommCmd
		, CSttContents *pCharacteristic, const CString &strRetMode, long nHasDigital,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL,const CString &strDvmFile = _T(""));//�������ܵ�ģ������
	virtual long Ats_GenerateTemplate(CDataGroup *pGenParas,const CString &strRetMode, long nHasDigital,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);//�๦�ܵ�ģ������
	virtual long Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID, CDataGroup *pTestMacroUI, CDataGroup *pUIParas
		, CDataGroup *pCommCmd, CSttContents *pCharacteristic, const CString &strDvmFile, const CString strTestClass, const CString &strRetMode, long nHasDigital
		, long nRepeatTimes, long nRptTitle, long nTitleLevel, long nSynMode, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID, CDataGroup *pItemParas,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL, const CString &strContents=_T(""), const CString &strRsltExpr=_T(""));
	virtual long Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString& strMacroID, const CString &strItemParas,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ManuTrigger(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL); //yyj �ֶ������ź� 20220224
	virtual long Ats_SaveTemplate(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI=NULL, CDataGroup *pUIParas=NULL, bool bDoEvents=TRUE, CSttCmdData *pRetData = NULL,long nSynMode = STT_CMD_Send_Sync);
	virtual long Ats_SaveTest(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI=NULL, CDataGroup *pUIParas=NULL, bool bDoEvents=TRUE, CSttCmdData *pRetData = NULL,long nSynMode = STT_CMD_Send_Sync);
	virtual long Ats_ExportWordRpt(const CString &strPath, const CString& strFileName, CDataGroup *pParas=NULL, bool bDoEvents=TRUE, CSttCmdData *pRetData = NULL);
	virtual long Ats_OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile, bool bDoEvents=TRUE, CSttCmdData *pRetData = NULL);
	virtual long Ats_GenerateItems_Items(CDataGroup *pGenItemsParas, CSttContents *pContents=NULL, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL,long nSynMode = STT_CMD_Send_Sync);
	virtual long Ats_OpenGbrptFile(const CString &strGbrptFile, const CString &strDvmFile, const CString &strSmartTestRunMode=SmartTest_Run_Mode_Server,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_AdjustMainWnd(LONG hMainParent, LONG hLogParent, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ExportRpt(const CString &strDeviceID, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_UpdateItem(const CString &strItemPath, CDataGroup *pItemParas,bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType=_T(""), bool bDoEvents=TRUE, CSttCmdData *pRetData = NULL);
	virtual long Ats_QueryItem(const CString &strItemPath, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_AdjustReport(const CString &strDeviceSN, long nShowWnd, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_ClearReportsRslts(CDataGroup *pParas, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	virtual long Ats_AddSafety(CDataGroup *pParas, CExBaseList *pDatas, CExBaseList *pMsgs, bool bDoEvents=TRUE,CSttCmdData *pRetData = NULL, long nSynMode = STT_CMD_Send_Sync);//pParas�����Ŀ���ơ�ID��·������Ϣ
	//�¼��ӿ�
	virtual void OnException(CDataGroup *pParas);
	virtual long OnDisConnect();
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual long OnRtData(CSttParas *pParas);
	virtual long OnMeas(CDataGroup *pParas);

	//2022-1-14  lijunqing  AtsReport
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);


	//�Զ������¼��ӿ�
	virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas);
	virtual long OnTestProcess(CSttParas *pParas);
	virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas);
	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs);
	virtual long OnExportRptEvent(CSttParas *pParas);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);

	virtual long OnReTestFinished(CSttParas *pParas)
	{
		if (m_pAtsEventRcv != NULL)
		{
			m_pAtsEventRcv->OnReTestFinished(pParas);
		}

		return 0;
	}
	//2022-01-18  lijunqing
	virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas);
	//2022-04-18  shaolei
	virtual void On_Ats_SaveTest(CSttSysState *pSysState);
	virtual void On_Ats_SaveTemplate(CSttSysState *pSysState);
	virtual void On_Ats_CreateTest(CSttSysState *pSysState);
	virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState);

	//2022-06-25  shaolei
	virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState);
	
	//2022-9-13  lijunqing
	virtual void On_Ats_QueryItem(CSttSysState *pSysState);

//2022-4-14 lijunqing
public:
	virtual void Ats_IecDetect(long bEnable);
	virtual void Ats_IecRecord(CDataGroup *pIecRecordParas);
	virtual long Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas);

protected:
	void ValidExceptionTimeOut();

	CTickCount32 m_oExceptionTick;//20220915 zhouhj ���Ӵ����쳣�¼�����
};
