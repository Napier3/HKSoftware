#ifndef CSTTTESTCTRLCNTRBASE_H
#define CSTTTESTCTRLCNTRBASE_H

#include "../UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../SttTest/Common/tmt_result_def.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../61850/Module/SCL/SclIecCfgDatas.h"

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
#include "../SttCmd/GuideBook/SttReports.h"
#endif

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
#include "../../../AutoTest/Module/GuideBook/Reports.h"
#endif
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../SttCmd/GuideBook/SttContents.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

class CSttTestCtrlCntrMsgInterface
{
public:
// 	virtual long OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend,long n4G, long nWifi, long nBle,
// 		long nPowerAC, long nBatCap ,long nUSB){	return 0; };
	virtual long OnUpdateSyncTime(CDataGroup *pSyncTime){	return 0; };
	virtual long OnUpdateException(){return 0;}//20220914 zhouhj �����쳣��Ϣ
	virtual long OnItemStateChanged(CExBaseObject *pItem) = 0;
	virtual long OnTestFinished() = 0;
	virtual long OnTestStarted() = 0;
	virtual long OnTestStoped() = 0;
	virtual long OnTestCreated() = 0;
	virtual void OnReport(CExBaseObject *pItem) = 0;
	virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup){}
	virtual void OnReport_ReadSystemState(const CString &strMacroID, CDataGroup *pParas){}
	virtual void OnAtsGenerate() = 0;
	virtual void OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent=FALSE) = 0;
	virtual void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp) = 0;
	virtual void OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList) = 0;
	virtual void OnAtsQueryItem(CExBaseObject *pItemPara) = 0;  //2022-9-13  lijunqing
	virtual void OnInputData(CSttParas *pParas,CExBaseList *pMsgs) = 0;  //SHAOLEI  2023-7-21
	virtual void OnTestDisconnected() = 0; //shaolei 2023-9-19 ����
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){};

};

class CSttTestCtrlCntrBase
{
public:
    CSttTestCtrlCntrBase();
    virtual ~CSttTestCtrlCntrBase();

	virtual void SetSttTestCtrlCntrMsgInterface(CSttTestCtrlCntrMsgInterface *pTestCtrlCntrMsg)	{	m_pTestCtrlCntrMsg = pTestCtrlCntrMsg;	}
    virtual void SetCurrTestItem(CExBaseObject *pCurrTestItem);
    virtual CExBaseObject *GetCurrTestItem();
	virtual CExBaseObject* GetGuideBook()	;
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml,const CString &strParentPath)	{	return 0;	}

    virtual BOOL StartTest(CDataGroup *pCurrentUIParas);
    virtual BOOL StopTest();
	virtual long SendManuTrigger();
	//add by shaolei 20220319  //������ĿID���������е���Ŀ
	virtual void GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList); 

	//2022-3-29  lijunqing
	virtual long TestItem(const CString &strItemPath);
	virtual long TestFrom(const CString &strItemPath);
	virtual void Test_GetSystemState(){};//dingxy 20250321����GetSystemState����

#ifdef STT_MACRO_TEST_UI_USE_GUIDEBOOK
    virtual void FillReport(CReports *pReports){}
#endif

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
  virtual void FillReport(CSttReports *pSttReports){}
#endif

    virtual CExBaseList *GetReports(){ return NULL; }
	virtual void GetEventInfo(CExBaseList& oInfoList){};
	virtual CExBaseList* GetTestGlobalParas(){return NULL;}//zhouhj 20220913 �������ڻ�ȡ��·�����ء����ȵ�״̬

	virtual bool IsTestStarted(){ return false; };
	virtual bool IsTestAppConnect(){ return false; };

	virtual void NewTest(CDataGroup *pDevice, CDataGroup *pTestApp, CDataGroup *pCommConfig){};
protected:
    CExBaseObject *m_pCurrTestItem;   //��ǰִ�еĲ�����Ŀ
	CSttTestCtrlCntrMsgInterface *m_pTestCtrlCntrMsg;
	CSttMacroTestUI_TestMacroUI *m_pCurrTestMacroUI;  //2022-3-11  lijunqing  for debug

public:
	//���Թ��ܲ����༭
	CDataGroup m_oTestMacroUI_Paras;  //��ǰ���Թ���ҳ��Ĳ���
	CExBaseObject *m_pCurrEditMacroItems;   //��ǰ���Թ��ܶ�Ӧ�Ĳ�����Ŀ�����ǲ�����Ŀ����
	CDataGroup m_oTestReportHead;//��ǰ����ͷ���� sf 20220217
	CEventResult m_oCurrEventResult; //��ǰ�¼�����
	tmt_BinaryConfig m_oBinaryConfig;//������
	CSttTestResourceBase *m_pSttTestResouce;//zhouhj �ܵ������Դ,ֻ��һ��
	CSclStation m_oSclStation;//�������ڴ洢��ǰSCD�ļ��е�ȫ�����ƿ�����,����IEC���ú�IEC̽�� zhouhj 20221206

	virtual void ConnectAtsServer();
	virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void GetMacroUI_GbItems(CString &strMacroUI_Items);
	void GetReportHeadFile(CString &strFile);
	void OpenReportHead();
	void SaveReportHead();
	void stt_OpenHdRsFile(const CString &strHdRsFile);

	void InitDefaultHdRs();//zhouhj 20220402 ��ʼ��һ��ͬ��ģʽ����󻯵������Դ

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
	virtual long Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas);//2023.7.7 zhouhj �������ڸ���ֱ������

	//2022-3-29  lijunqing
	virtual long Ats_NewItems(CExBaseList *pParent, CExBaseObject *pItems);
	virtual long Ats_EditItems(CExBaseList *pParent, CExBaseObject *pItems, const CString &strItemsID);
	virtual long Ats_DeleteItems(CExBaseList *pParent, CExBaseObject *pItems);
	//2022-10-20  shaolei
	virtual long Ats_MoveUpItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	virtual long Ats_MoveDownItem(CExBaseList *pParent, CExBaseObject *pItems, long nMoveTimes = 1);
	//2023-2-1  shaolei
	virtual long Ats_ItemPaste(CExBaseList *pParent, const CString& strSrcItemPath);
	//2023-8-11 shaolei //��Ӳ���ǰ����ͨѶ���
	virtual long Ats_CmdAddGrp(CExBaseList *pParent, long nAftUseReset = 1, long nAddCommCmd = 1);
	//2023-8-14 shaolei  //����ģ���ļ�(ģ��ӳ��)
	virtual long Ats_ImportDvmFile(const CString &strDvmFile, long nIsDvmMap = 0);
	//2023-8-28 shaolei  //ң�����ӳ��
	virtual long Ats_AinDataMap(CDataGroup *pMapParas, CDataGroup *pAinDevRatios);
	//2023-8-29 shaolei  //����װ��
	virtual long Ats_ConfigDevice(CDataGroup *pCommCfg);

	//2022-08-31 shaolei
	virtual long Ats_GenrateItems_CmdWzd(CExBaseList *pParent, CDataGroup *pCommCmd, const CString &strMacroName, const CString &strTestClass, long nSynMode = 0);
	virtual long Ats_GenrateItems_CmdAdd(const CString &strParentItemPath, CDataGroup *pCommCmd, CSttContents *pContents);
	virtual long Ats_GenerateItems_AddSafety(CDataGroup *pParas, CExBaseList *pListDatas, CExBaseList *pMsgs);

	//ģ�塢�������ݵ���صĽӿ�  2022-3-14  lijunqing
	virtual CString SaveTestFile(const CString &strRealPath, const CString &strTemplateFileName);
	virtual CString SaveSysTemplateFile(const CString &strTemplateFileName);
	virtual CString SaveTemplateFile(const CString &strTemplateFileName);
	virtual BOOL SaveTemplate(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = 0);  //0��ʾͬ����STT_CMD_Send_Sync
	virtual BOOL SaveTest(const CString &strPath, const CString &strFileName, CDataGroup *pCurrentUIParas, long nSynMode = 0);
	virtual BOOL ExportWordRpt(const CString &strPath, const CString &strFileName, CDataGroup *pParas);   //pParasΪ��������Ҫ���ݵ���������
	virtual BOOL OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL OpenTest(const CString &strFileWithPath, const CString &strDvmFile);
	virtual BOOL ClearReportsRslts(CDataGroup *pParas);  //����������ݣ��β���Ԥ���Ĳ��������Բ����ݲ���

	virtual void CloseTest(long nSynMode = STT_CMD_Send_Sync){	};//�رղ���ǰҪ�ɵĻ� sf 20220318

	//2022-4-14 lijunqing
	virtual void Ats_IecDetect(long bEnable);
	virtual void Ats_IecRecord(CDataGroup *pIecRecordParas);
	virtual void Ats_BinConfig(CDataGroup *pBinConfigParas);//20240922 zhouyangyong �������ڿ���������

public:
	//2022-3-11 lijunqing
	void OpenMacroTestUI_ParaFile(long nFileIndex);
	void SaveMacroTestUI_ParaFile(const CString &strTitleAdd);

	void SaveCurrTestMacroUITemplateFile();
	CSttMacroTestUI_TestMacroUI* GetCurrTestMacroUI()	{	return 	m_pCurrTestMacroUI;	}
	void SetCurrTestMacroUI(CSttMacroTestUI_TestMacroUI *pSttMacroTestUI_TestMacroUI){m_pCurrTestMacroUI = pSttMacroTestUI_TestMacroUI;}

	virtual long GetGbItemCount();   //����ģ���пɲ����Ŀ������
	virtual BOOL IsHasTestTask();   //�Ƿ����в����������Ƿ񴴽����ԣ�����CSttDevice��Ϊ�ж�����
	virtual void WaitCmdReplyProcess()	{	}
};

#endif // CSTTTESTCTRLCNTRBASE_H
