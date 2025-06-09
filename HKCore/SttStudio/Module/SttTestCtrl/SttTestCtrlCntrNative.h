#ifndef CSttTestCtrlCntrNative_H
#define CSttTestCtrlCntrNative_H

#include "SttTestCtrlCntrBase.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "../TestClient/SttAtsTestClient.h"
#include "../../../Module/TestMacro/TestMacros.h"

class CSttTestCtrlCntrNative : public CSttTestCtrlCntrBase, public CAtsEventInterface
{
public:
    CSttTestCtrlCntrNative();
    virtual ~CSttTestCtrlCntrNative();

	CSttGuideBook *m_pSttGuideBook;
	CTestMacros* m_pTestMacros;
	CSttAtsTestClient m_oSttAtsClient;
	CDataGroup m_oStateGroupParas;//dingxy 20240515 ���StateTestDataType����

	void SttOpen(const CString &strTestAppCfgFile);

//CAtsEventInterface
public:
// 	virtual long OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
// 		long nPowerAC, long nBatCap ,long nUSB);
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);
	virtual long OnUpdateException();//20220914 zhouhj �����쳣��Ϣ
	virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas);
	virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas);
	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs);
	virtual long OnExportRptEvent(CSttParas *pParas);
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup);//zhouhj 20220326 �������ڸ���Ӳ����Ϣ
	virtual void OnReport_ReadSystemState(const CString &strMacroID, CDataGroup *pParas);//dingxy 20260320 ���������������


	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);


	//2022-01-18  lijunqing
	virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas);
	virtual void On_Ats_Generate_cmd_add_grp(const CString &strParentItemPath, CSttItems *pItems);
	virtual void On_Ats_Generate_import_dvmfile(CSttItems *pItems);
	virtual void On_Ats_Generate_ain_data_map(CSttItems *pItems);
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml,const CString &strParentPath);
	//2022-4-13  lijunqing
	virtual void On_IecDetect(CDataGroup *pIecCb);
	//2022-04-18  shaolei
	virtual void On_Ats_SaveTest(CSttSysState *pSysState);
	virtual void On_Ats_SaveTemplate(CSttSysState *pSysState);
	virtual long OnConnectStateChanged(bool bState);

	//2022-06-25  shaolei
	virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState);

	//2022-9-13  lijunqing
	virtual void On_Ats_QueryItem(CSttSysState *pSysState);

	//2022-10-6  lijunqing
	virtual long On_RtData(CDataGroup *pRtData);

public:
	virtual CExBaseObject* GetGuideBook()		{	return m_pSttGuideBook;	}
	virtual long GetGbItemCount();   //����ģ���пɲ����Ŀ������
	virtual BOOL IsHasTestTask();   //�Ƿ����в����������Ƿ񴴽����ԣ�����CSttDevice��Ϊ�ж�����

	virtual BOOL StartTest(CDataGroup *pCurrentUIParas);
	virtual BOOL StopTest();
	virtual void FillReport(CSttReports *pSttReports);
	virtual CExBaseList *GetReports();
	virtual void GetEventInfo(CExBaseList& oInfoList);
	virtual bool IsTestStarted();
	virtual bool IsTestAppConnect();
	virtual void ConnectAtsServer();
	virtual void Test_GetSystemState();

	virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void GetMacroUI_GbItems(CString &strMacroUI_Items);
	virtual CExBaseList* GetTestGlobalParas();//zhouhj 20220913 �������ڻ�ȡ��·�����ء����ȵ�״̬

	//ģ��������صĽӿ�
	virtual long Ats_GenerateTemplate();//�������ܵ�ģ������
	virtual long Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd=NULL, const CString &strDvmFile=_T(""), const CString strTestClass=_T(""), long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1, long nSynMode=STT_CMD_Send_Sync);
	virtual long Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID);
	virtual long Ats_SetItemPara_RsltExpr(const CString &strItemPath, const CString& strRlstExpr);
	virtual long Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString &strMacroID, const CString &strItemParas);
	virtual long Ats_UpdateItem(const CString &strItemPath);
	virtual long Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType=_T(""));
	virtual long Ats_QueryItem(const CString &strItemPath);
	virtual long Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs);
	virtual long SendManuTrigger();
	virtual long Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas);//2023.7.7 zhouhj �������ڸ���ֱ������
	//add by shaolei 20220319
	virtual void GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList);//������ĿID���������е���Ŀ

	virtual long TestItem(const CString &strItemPath);
	virtual long TestFrom(const CString &strItemPath);

	//ģ�塢�������ݵ���صĽӿ�  2022-3-14  lijunqing
	virtual CString SaveTestFile(const CString &strRealPath, const CString &strTemplateFileName);
	virtual CString SaveSysTemplateFile(const CString &strTemplateFileName);
	virtual CString SaveTemplateFile(const CString &strTemplateFileName);
	virtual BOOL SaveTemplate(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = STT_CMD_Send_Sync);
	virtual BOOL SaveTest(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = STT_CMD_Send_Sync);
	virtual BOOL ExportWordRpt(const CString &strPath, const CString &strFileName, CDataGroup *pParas);
	virtual BOOL OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL OpenTest(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL ClearReportsRslts(CDataGroup *pParas);  //����������ݣ��β���Ԥ���Ĳ��������Բ����ݲ���
	virtual void On_Ats_CreateTest(CSttSysState *pSysState) {}
	virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState) {}

	//2023-8-29 shaolei  //����װ��
	virtual long Ats_ConfigDevice(CDataGroup *pCommCfg);

	virtual void CloseTest(long nSynMode = STT_CMD_Send_Sync);//�رղ���ǰҪ�ɵĻ� sf 20220318

	//2022-4-14 lijunqing
	virtual void Ats_IecDetect(long bEnable);
	virtual void Ats_IecRecord(CDataGroup *pIecRecordParas);
	virtual BOOL Ats_UartConfig(CDataGroup *pUartConfigParas);
	virtual void Ats_BinConfig(CDataGroup *pBinConfigParas);//20240922 zhouyangyong �������ڿ���������

	//2022-10-5  lijunqing
	virtual void InitMeasServer();
	virtual void ExitMeasServer();

	void UpdateReportValuesByMacroTestDataType(CSttItems *pItems);//��Ҫ����Reports�е��������͸�������ֵ
	void UpdateReportValuesByMacroTestDataType(CSttReport *pReport,const CString &strMacroID,CSttItems *pSttItem = NULL);
	void ModifyReport_ManualTest(CDvmValues *pValues);
	void ModifyReport_StateTest(CDvmValues *pValues,CSttItems *pSttItem = NULL);
	void ModifyReport_HarmTest(CDvmValues *pValues); 
	void ModifyReportUnGradienParas_StateTest(CDvmValues *pValues, int nStateCount, CDataGroup *pParasDataGroup);//dingxy 20240717 ����״̬���б����зǵݱ�ͨ����ֵ
	CExBaseObject* FindRootItemsByID(const CString &strObjID);
protected:
	CSttContents* NewCharactersContents();
	void InitGuideBookBySttParas(CSttParas *pParas);
	BOOL m_bCmdReplyProcessFinished;  //�����Ӧ���Ƿ������
public:
	BOOL IsCmdReplyProcessFinish()		{	return m_bCmdReplyProcessFinished;	}
	virtual void WaitCmdReplyProcess();		//�ȴ������Ӧ�������
	bool IsRemoteAutoTest(const CString &strMacroID);//chenling 2024.8.20 �ж��Ƿ����Զ�����ģ��ID,��Ҫ���ع�Լ
};


#endif // CSttTestCtrlCntrNative_H
