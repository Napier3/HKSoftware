#pragma once

/*
	�������������Կ��ƶ��󣻹���һ�����Ե�ȫ������
*/

#include "../../../Module/TestMacro/TestMacroInterface.h"
#include "../GuideBook/GuideBook.h"
#include "../GuideBook/GuideBookDefine.h"
#include "../TCtrlCntrDefine.h"
#include "../GuideBook/ReportMap/RptFillInterface.h"
#include "../TCtrlMsgRcvInterface.h"

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include"../../../SttStudio/Module/SmartTestInterface/MacroTestInterface.h"
#include "../PpDeviceRefs.h"
#include "../../../Module/DataMngr/DataMngrTrans.h"
#include "../../../SttStudio/Module/SmartTestInterface/ProtocolEngineInterface.h"

CString ats_GetBinaryTempFile(const CString strTempFilePath, CGbItemBase* pItem);
CString ats_GetBinaryTempFilePath(CGbItemBase* pItem);


#define ProcedureType_TestItem    0
#define ProcedureType_EngineCmd   1

class CRptFillInterface;
class CTestControlWnd;
class CWordRptExportBase;

extern long g_nLog_TestControl_Msg;//   = 0;
extern CString g_strReportFillProgID;
extern BOOL g_bInXTestDbGenReprtState;

//2021-2-23  lijunqing  CTestControlBaseInterface
class CTestControlBase : public CTestControlBaseInterface //CExBaseList  //CBaseObject
{
public:
	CTestControlBase();
	virtual ~CTestControlBase();

	virtual UINT GetClassID()                             {      return GBCLASSID_TESTCONTROL;                 }

	CString GetProjectName()
	{
			return m_strGbBinaryFile;
	}

	BOOL HasProject()
	{
		if (m_strGbBinaryFile.GetLength() > 0)
		{
			return TRUE;
		}

		return FALSE;
	}

	void SaveFinalXMLReportEx();
	virtual void SaveFinalXMLReport();
	void SaveBinaryFile();

    virtual void DeleteTempDirectorys();
	void InitGbBinaryFileName();
	CString GetGbBinaryFileName();
	CString GetGbBinaryFileNameShort()		{	return m_strGbBinaryFileName;	}
	CString GetGbBinaryFile()	{	return m_strGbBinaryFile;	}
	void ChangeGbBinaryFileName(const CString &strFileName);

	BOOL IsEncrypt();
	CExBaseObject* GetTestProjectRef()	{	return m_pTestProjectRef;	}
	void SetTestProjectRef(CExBaseObject *pTestProjectRef)	{	m_pTestProjectRef = pTestProjectRef;	}

	//2021-10-14  lijunqing
	CDvmDataset* CreateNewDvmDatasetForCommCmd(CCommCmd* pItem);

public:
	virtual void InitGuideBook();
	virtual long FindTestControlIndex(CTestControlBase *pTestControl)	{	return 0;	}
	virtual BOOL IsTestControlMngr()	{	return FALSE;		}
	virtual void CreateTestControlWnd(CTestControlWnd *pWndRef=NULL);
	virtual long TestItem(CGbItemBase* pItem);
	virtual void SetTestItemState(CGbItemBase* pItem, UINT nState);
	virtual long TestItemCommCmdEx(CCommCmd* pItem);

	virtual long StopTestCurrItem(); 
	virtual long StopTest(const CString &strMsg = _T("")); //�Զ���������ֹͣ����
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //�ⲿֹͣ���ԣ��û�ֹͣ���ԡ������쳣ֹͣ����
	virtual long StopTestByOptr();//������ԭStopTestExtern���л���������OnElectricMsg�е����ظ�����Ҫɾ��ԭ�����ĵ��˺��������ӻ�����
    virtual  long UpdateParameter(CDataGroup *pParas);    //�ֶ���г�����ܣ���Ҫ�ڲ��Թ����У�ʵʱ���²���
    virtual long ManualTrigger();  //�ֶ�����

	virtual UINT GetTestControlMode()	{	return TESTCONTROLMODE_NORMAL;	}
	virtual CReport* AddMacroTestReport(CMacroTest* pItem);
	virtual CReport* AddHdResReqestReport(CHdResReqest* pItem);
	virtual CReport* AddMacroTestReport(CMacroTest* pItem, const CString &strItemPara);
	virtual void AddMacroTestReport(CMacroTest* pItem, CReport *pSrcReport);
	virtual CReport* UpdateMacroTestReport(CMacroTest* pItem);
	virtual void AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
	virtual void AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
	virtual void UpdateMacroTestReport(CMacroTest* pItem, CReport *pSrcReport);
	virtual BOOL WriteDatasToEngine(CCommCmd* pItem); 
	virtual long SaveCmdDatasToLocal(CCommCmd* pItem);

	virtual long ProcessFinishCommCmd(CCommCmd* pItem);
	virtual long ProcessFinishCommCmdWrite(CCommCmd* pItem);
	virtual long ProcessFinishCommCmdRead(CCommCmd* pItem);
	virtual long ProcessFinishCommCmdReadLog(CCommCmd* pItem);
	virtual long ProcessFinishCommCmdReadSOE(CCommCmd* pItem,CDvmDataset *pDataset);
	virtual long ProcessFinishCommCmdReadOther(CCommCmd* pItem,CDvmDataset *pDataset);
	virtual long ProcessFinishCommCmdNone(CCommCmd* pItem);
	virtual long ProcessFinishCommCmdAfter(CCommCmd* pItem, CReport *pReport);
	virtual long ReadEngineDatas(CCommCmd* pItem, CDvmDataset *pShortDatas); 
	virtual long ReadEngineDatas(CProtocolDeviceInterface* &oPpDevice, const CString &strName, const CString &strDatasetPath, CDvmDataset *pShortDatas); 

	virtual void InitGbCommConfig();   //2023-4-3 lijunqing ͨ�Ų��ָ�ΪSttIot
	virtual BOOL CreateTest(CDataGroup *pTestApps);
	//shaolei �����βΣ��Ƿ��Ƕ������ļ�
	virtual BOOL CreateTest(const CString &strGbBinaryFile, BOOL bFullPath=FALSE, BOOL bBinaryFile=TRUE);  
	virtual long OpenBinaryFile(const CString &strFile, long nRWReportFileMode, BOOL bOnlyReadAttr = FALSE);
	virtual long OpenGbxmlFile(const CString &strFile, BOOL bOnlyReadAttr = FALSE,const long &nXmlRWType = _PUGI_XML_TYPE_);

	virtual void InitAfterOpenBinaryFile();
	virtual long FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);

    virtual long FinishCurrTestItem(CDataGroup *pDataGroup);

	//2021-8-10  lijunqing
	virtual void SetItemReport(CGbItemBase *pCurrItem, CGbItemBase *pSrcItem);
	virtual void SetItemsReport(CItems *pCurrItems, CItems *pSrcItems);
	virtual long FinishTestItemSafety(CSafety* pItem);
	virtual long FinishTestItemSafety(CSafety* pItem, CSafety *pSrcItem); //2021-8-10  lijunqing
	virtual long FinishTestItemSafety_Process(CSafety* pItem, CReport *pReport);//2021-8-10  lijunqing
	virtual long FinishTestItemSysParaEdit(CSysParaEdit* pItem);
	virtual long FinishTestItemSysParaEdit(CSysParaEdit* pItem, CSysParaEdit* pSrcItem);
	virtual long FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem);
	virtual long FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem, CReport *pReport);

	virtual long TestNextItem();
	virtual void GotoItem(CGbItemBase *pGotoItem);
	virtual void SetTestEndTime();
	virtual void SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime);
	virtual void SetTestError(const CString &strTestError);
	virtual BOOL ContinueTestByHdResReq();

	virtual void SetBinaryFile(const CString &strFile);
	virtual void InitEngineDataInterface(CCommCmd* pItem);
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);

	virtual long FinishTestItemMacroTest_Only(CMacroTest* pItem);
	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);
	virtual void SaveReport();
	virtual void ExportRptDataFile(); //2023-9-26  lijunqing �������������ļ�
	virtual void SaveReportOwn();

	virtual CGbItemBase* GetTestItem(CGbItemBase *pGbItem, long nIndex);
	virtual CReport* AddCommCmdReportDataEx(CCommCmd* pItem, CDvmDataset *pDatas);
	virtual CReport* AddCommCmdReportDataEx_OverWrite(CCommCmd* pItem, CDvmDataset *pDatas);
	virtual long SaveEngineDatasToLocal(CCommCmd* pItem, CDvmDataset *pShortDatas); 

	virtual double GBS_GetDsDataValueEx(CGbItemBase *pItem, long nDeviceIndex, const char* pszID);
	virtual CDataObj* GBS_GetDsDataObj(CGbItemBase *pItem, long nDeviceIndex, const char* pszID);
	virtual BOOL CanRunCommCmdFinalResultScript(CCommCmd* pItem);
	virtual void InitAfterMacroTestItemsChanged(){};
	//virtual void AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *pInterface);  //2023-8-29 lijunqing
	virtual void AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *pInterface);

	virtual long LocateReport(CGbItemBase* pItem, long nIndex);
	virtual long LocateReport(CGbItemBase* pItem);

	virtual LRESULT OnElectricTestAppMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnElectricTestMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnElectricTestMsg_MacroTest(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnElectricTestMsg_ResReq(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnCommCommandMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnSafetyTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnSysParaEditTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnCommCmdMamualTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnManualTestMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnEngineSystemMessage(WPARAM wParam, LPARAM lParam);

	virtual void CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);

	virtual long UpdateGbItem(const CString &strGbxmlFile, CGbItemBase* pGbItemSrc);

	//ִ�й������е�ͨѶ����
	virtual void ContinueExecutePpEngineCmd(CTestControlBase *pTestControl);

	virtual long FinishTestItemMacroTest_IsError(CMacroTest* pItem);
	virtual long FinishTestItemMacroTest_Report(CMacroTest* pItem);
	virtual long FinishTestItemMacroTest_Process(CMacroTest* pItem);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

	virtual long TestItemMacroTest(CMacroTest* pItem);
	virtual void GetMacroTestParaDatas(CMacroTestPara* pTestPara, CString &strPataDatas); //2018-12-23�������ϲ����� lijq
	virtual long TestFirstSubItems();
	virtual BOOL IsVirtualVm();
	virtual long TestFirstSubItems_MacroTest(BOOL bFromMtMsg);
	virtual CGbItemBase* GetNextTestSubItem();
	virtual BOOL CanTestFirstSubItems();

	virtual long TestItemHdResReqest(CHdResReqest *pItem);

	virtual long CreatemUICommCmdViewDlg(LPVOID pUIViewDlg);
	virtual void HideCommCmdAttrDlg();
	virtual CProtocolDeviceInterface* GetDevicePtr(CCommCmd* pItem);
	virtual CProtocolDeviceInterface* GetDevicePtr();
	virtual CProtocolDeviceInterface* GetDevicePtr_0();

	//����ͨѶ��Լ�������
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);
	virtual void InitItemsRsltExprScript(CCommCmd* pItem);
	virtual void DeviceCmmConfig(CPpDeviceRef *pPpDeviceRef);
	virtual BOOL ContinueTestByItemsRsltExprScript(CCommCmd* pItem);
	virtual BOOL CanContinueTestByItemsRsltExprScript(CCommCmd* pItem);
	virtual void ClearSysRptFill(CGbItemBase *pItem);

	virtual void EditItemPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual void EditItemPara(CCommCmd *pCommCmd, CValue *pValue);

	virtual void EditMacroTestPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual void EditCommCmdPara(CCommCmd *pCommCmd, CValue *pValue);
	virtual long SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst);
	virtual CReport* AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex);
	virtual void DeleteReport(CGbItemBase *pItem, CReport *pReport);
	virtual BOOL ItemsRsltExprScriptTimeIgnore();
	virtual CReport* GetReport(CGbItemBase* pItem, long nIndex);
	virtual long FillParentItemsReport(CGbItemBase *pItems);
	virtual void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);
	virtual void UpdateDvmLdeviceID();

	//��װ�á�������Թ�����ת  2017-11-22
	virtual BOOL GBS_CanBreakLoop(CGbItemBase *pItem);
	virtual void GBS_ClearBreakLoopState(CGbItemBase *pItem);
	virtual void GBS_GotoItemEx(CGbItemBase *pCurrItem, CGbItemBase *pGotoItem, const CString &strGotoItemPath, long nRslt, long nAndOr);
	virtual void GBS_GotoItemEx_Go(CGbItemBase *pItem);
	virtual long GetBreakLoopState();
	virtual void RcdCmp(const CString &strStdFile, const CString &strTestFile);
	virtual long GBS_RcdCmp_CopyStdFile(CTestControlBase *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);
	virtual void RcdAnalyse(const CString &strTestFile);

	virtual void FillGlobalDatasRpt();

	 //2021-2-23  lijunqing : 
	virtual CString GetItemTempPath(); 
	//shaolei 20210807
	virtual void GetReportFiles(CDataGroup *pDataGroup);
	//shaolei 20211101
	void GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);
	virtual void UploadRptFiles(CString &strFiles);
	void UploadRptFiles(CDataGroup *pGroup);
	virtual void SetDeviceSN_AfterTestCreated(const CString &strDeviceSN);

    void SetGuideBook(CGuideBook *pGuideBook);
    void FreeItemsContainer();
	virtual void ResetTestControl();

	virtual void AttachItemViewGrid(void *pGrid, BOOL bUpdateGrid);
	virtual void EmptyReportDatas(BOOL bUseCfgFlag=TRUE);
	virtual void FinishInptuData(CDataGroup *pDataGroup);
	void AutoSaveReportFileName(CWnd *pParentWnd, BOOL bJudgeState=FALSE);

protected:
	CString GetLdKey(const CString &strLdevice);
	CDvmLogicDevice* FindByLdKey(CDvmDevice *pDevice, const CString &strKey);

protected:
	//�Ƿ�ִ��ͨѶ�������ʱ�����ڶ��豸��ͨѶ���ִ��һ����ʱ���㹻��
	BOOL m_bExecCommCmdTdelayBefore;
	BOOL m_bExecCommCmdTdelayAfter;
	//CTestProject* m_pTestProject;
	CExBaseObject *m_pTestProjectRef;
	CString m_strGbBinaryFile;
	CString m_strGbBinaryFileName;

	CTickCount32 m_oTickCount32;
	BOOL     m_bSafetyScriptStopByRecord;
	CReport *m_pCurrReport;

	//2023-6-13  lijunqing
	CExBaseList m_listHdResReqFaildItem;

public:
	CAutoCriticSection m_oCriticSectionGridTest;
	//�������
	CItemContainer* m_pItemContainer;
	long m_nCurrProjectIndex;
	long m_nCurrTestItemIndex;
	long m_nTestItemIndexBkForAllInlegible;  //2022-11-7  lijunqing  ���Թ����г��ֲ��ϸ���Ŀ�������ز⣬�����ټ������ԣ���Ҫ�ָ��ֳ�
	CGuideBook* m_pGuideBook;
	BOOL m_bSingleTestControl;

	CGbItemBase* m_pCurrTestItem;
	CGbItemBase* m_pCurrSubTestItem;
	long m_nCommCmdTestTimes;   //ͨѶ����ִ�в��ԵĴ���
	long m_nCommCmdReCommTimes;  //ͨѶ�������ԵĴ���
	long m_nCommCmdErrorState;  //ͨѶ�����쳣״̬
	long m_nCommCmdCurrDeviceIndex;
	long m_nMacroTestTimes;       //MacroTest�ظ�����ʱ�ĵ�ǰ����
	long m_nMacroTestReTestTimes;
	long m_nBreakItemsLevel;    //�Ƿ�������Ŀ���࣬ȱʡֵΪ-1,0��ʾ������ǰ���࣬1��ʾ������һ�����࣬��������

	//��Ŀ����ͳһ����жϹ�ʽ
	CItemsRsltExprScript *m_pItemsRsltExprScript;
	long m_nItemsRsltExprScriptIndex;
	long m_nItemsRsltExprScriptTimerLong;
	long m_nItemsRsltExprScriptMaxRead;
	long m_nItemsRsltExprScriptTimeIgnore;
	CTickCount32 m_oItemsRsltExprScriptTimeTick;

	//���������� �Ƿ���ȷ�����ʶ
	BOOL m_bElectricTesting;

	//����
	CRptFillInterface* m_pReportFill;

	//Safety������
	CWnd* m_pParentWnd;

	//����
	//��Ŀԭ����״̬������ֹͣ����ʱ�ָ�������Ŀ��״̬��
	//ֹͣʱ���������Normal״̬����ָ���ԭ����״̬
	long m_nItemOldTestState;

	//��ǰ������Ŀ������Ŀ����ҪָMacroTest��Ŀ��������ͨѶ���Safety��Ŀ������ͨѶ���SysParaEdit������ͨѶ����
	long m_nCurrChildItemIndex;

	//���潻��
	//2023-8-29  lijunqing ��Ϊ�Զ����Է������Ҫ���Զ������¼�������Ҫ���͸�������
	//Ҳ��Ҫ���͸��Զ����Է��������޸Ķ���Ϊ�ӿڹ������
	CTCtrlMsgRcvInterfaceMngr m_oTCtrlMsgRcv;  //CTCtrlMsgRcvInterface* m_pTCtrlMsgRcv;

	//��Ϣ����
	CTestControlWnd* m_pTCtrlWnd;
	BOOL m_bTestControlWndRef;

	//ͨѶ�ӿ�
	//MacroTest::IMacroTest m_oMacroTest;  //2020-06-5  lijunqing
	CMacroTestInterface *m_pMacroTestInterface;
	BOOL m_bMacroTestFinished;

	long m_nHasTestItemCount;
	long m_nStopTestByError;

	//2018-12-23  lijq���ڴ����Ƿ���Ҫ������ƫ�ƣ���װ�ò���
	BOOL m_bUseBinaryOffset;
	long m_nBinRngBegin, m_nBinRngEnd;

	static CAutoCriticSection m_oTestCriticSection;	//����ִ�еĻ�����

public:
	//���л�
	virtual long BinarySerialize(CBinarySerialBuffer &oBinaryBuff);

#ifdef GUIDEBOOK_DEV_MODE
	BOOL CreateTest(CGuideBook *pGuideBook, BOOL bCreatePpDeviceRefs);
#endif
	//����
	//��ʼ��
	void SetSafetyParentWnd(CWnd* pParentWnd)			{		m_pParentWnd = pParentWnd;		}

	void Test_OpenTempBinaryFile(CGbItemBase *pItem);
	void OpenAllBinaryTempFiles();
	CString GetReportFilePath(const CString &strExtend=_T(""));
	void OpenReportFile(CWnd *pParentWnd, BOOL bFirst);
	virtual BOOL OpenWordReportFile(BOOL bExportWord=FALSE, const CString &strDocFile=_T(""));
	virtual BOOL OpenWordReportFileOnly(CString &strWordFile);
	CString GetDeviceReportFile();
	void GenerateWordReport(CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd);

	void CloseReportFill();
	void AdjustReport_FillEmpty();

private:
	void TraceItems();
	void InitAllCpus();

protected:
	long AfterOnUpdateGbItem(CGbItemBase* pGbItem);
	long AfterOnUpdateGbItem_CommCmd(CGbItemBase* pGbItem);

//2017-3-18  ���Կ��Ʋ��֣�ȫ������Ϊ�麯�������ڶ���ԵĿ���
public:
	//��һ��Ŀ
	virtual long TestSingle(CGbItemBase* pGbItem);
	virtual long TestSingle(long nItemIndex);
	virtual long OnTestAllInlegibleItems();

	//ĳ����Ŀ������
	virtual long TestFrom(CGbItemBase* pGbItem);
	virtual long TestFrom(long nItemIndex);
	virtual long QueryFrom(long nItemIndex);
	virtual long QueryFrom_Ex(long nItemIndex);   //���ݲ���ģʽ��������Ŀ��ѯ

	CGbItemBase* GetItemByIndex(long nItemIndex);
	void ProcessCurrentItemLast();
public:
	//��һ��Ŀ
	long TestSingle_MdOne(CGbItemBase* pGbItem);

	//������Ŀ֮��
	long TestBetween(CGbItemBase* pGbItemBegin, CGbItemBase* pItemEnd);
	long TestBetween(long nBeginItemIndex, long EndItemIndex);

	//��ʱ�ز�
	void TestOverTimerItem();

	//TCtrl�쳣
    virtual void IsMacroTCtrlException();

	//״̬
	long TestByState(long nTestState);
	long TestAllIneligible();
	long TestAllNormal();

	//���Կ���
	long FinishTest();
	long StopMacroTestOutput(BOOL bStopDevice=FALSE);
	BOOL IsNowTesting();
	void EditItemPara(CExBaseObject *pItem);

	//���洦�� 2010-07-14
	void SetReportFill(CRptFillInterface* pRptFillInterface);

	//������д����
	void ReFillReport();

	//�������棬������ɺ�鵵����
	virtual void AdjustReport(CThreadProgressInterface *pProgress=NULL);

	//������Ŀ״̬
	virtual BOOL SetItemState(CDataGroup *pParas);

	//shaolei 2023-11-1
	virtual void OnTestItemCount_TCtrlMsg(long nItemCount);
	virtual void OnTestBegin_TCtrlMsg();
	virtual void OnStopTest_TCtrlMsg(long nType);
	virtual void OnException_TCtrlMsg(long nEvent, const CString &strError);
	virtual void OnConnectSuccess_TCtrlMsg();

	//������д
	long InitFillReport(CGbItemBase* pItem);
	long InitFillReport(CReport* pReport);
	long GenerateWordReport(CGbItemBase* pItem, CBinarySerialBuffer *pBuffer);
	long FillReportRepeatCommCmd(CMacroTest *pMacroTest, CCommCmd* pCommCmd);
	long FillReport(CReport* pReport, long nRepeatIndex);
	void ClearItemInDbState();  //2021-1-27  lijunqing

	//��ӡ����
	virtual void PrintReport();
	virtual void ExportPdf();
	virtual void ZoomReport(long nPercentage);
	virtual long GetZoomReport();

	CString GetReportFile();
	CString GetSysReportFile();

	//��Ϣ����
	virtual void OnPpEngineExceptionTimer();
	void AddBeforeTestItems(CExBaseObject *pCurrTestItem);

public:
	//��֯����
	long AddEnableFilter(long nEnable=1);
	long AddShowFilter(long nShow=1);
	long AddIndexFilter(long nIndex);
	long AddIndexFilter2(long nBeginIndex, long nEndIndex=-1);
	long AddStateFilter(long nState);
	long AddTKidFilter(long nTKid);
	long AddEnableShowFilter(long nEnable, long nShow);
	long AddEnableShowStateFilter(long nEnable, long nShow, long nState);

	//����
	//������Ŀ
	long TestFirstItem();
// 	long TestNextItem();
	BOOL HasNextItemNeedTest();//		{		return !(m_pItemContainer->ReachTailPos());	}

	virtual void BackRptsBeforeTest(CGbItemBase *pItem); //����ǰ�����ݱ���
	virtual void ChangeReportFileName(const CString &strFileName);

	virtual long TestItemSafety(CSafety* pItem);
	virtual long TestItemSysParaEdit(CSysParaEdit* pItem);
	virtual long TestItemSysParaEdit_Test(CSysParaEdit* pItem);
	virtual long ViewSysPara(const CString &strSysParaID, CGbItemBase *pCurrSelItem);
	virtual void ShowItemReportDsv(CExBaseObject *pGbItem, CReport *pReport);

	//long TestItemMacroTest(CMacroTest* pItem);
	long TestItemMacroCharTest(CMacroCharItems* pMacroCharItems);

	long TestItemMacroTestChildItem(CMacroTest* pItem);
	long TestItemCommCmd(CCommCmd* pItem);
//	long TestItemCommCmdMamual(CCommCmd* pItem);
	void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE);
	void ShowCharDraw(CExBaseObject *pGbItem);
	void ShowItemRecord(CExBaseObject *pGbItem);

	BOOL IsItemMacroTest(CGbItemBase* pItem);

	//��ɲ���
	long FinishTestItem(CGbItemBase* pItem);
	long FinishTestItemMacroTest(CMacroTest* pItem);
	long FinishTestItemHdResReqest(CHdResReqest* pItem);
	long FinishTestItemMacroCharTest(CMacroCharItems* pMacroCharItems);
	long FinishTestItemCommCmd(CCommCmd* pItem);

	virtual void AddSysParasToTask(CSysParaEdit* pItem);

	virtual long UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg=TRUE);
	virtual long TestNextSubItem(CGbItemBase* pCurrSubItem);
	BOOL HasNextSubItem(CGbItemBase* pCurrSubItem);
	void FinishTestSubItem_MacroTest(BOOL &bCallMacroStopTestError);
	virtual BOOL WriteItemTempFile(CGbItemBase* pItem);
	//CString GetItemTempPath();  //2021-2-23  lijunqing : 

	//ͨѶ
	BOOL HasCommCmdEngine(CCommCmd* pItem);

	//�ⲿ�ӿ�
	virtual long CreateReportFill(const CString &strRptProgID, BOOL bExportWord=FALSE);
	virtual CWordRptExportBase* CreateRptExport(const CString &strRptProgID);

protected:
	//����ȫ��������صĽ���
	virtual void HideAllTestItemUI();
	virtual void DestroyAllTestItemUI();

	void InitFinalReportState(CGbItemBase *pItem, long nRepeatTimes);

	//���Խ���������ɺ�Ĵ���
	void OnProjectTestEnded(BOOL bFinish);

	//����PMTest���
    virtual void CreateMacroTestInterface(CTestMacros* pTestMacros, const CString &strMacroID);
	virtual void CreateMacroTestInterface_HdRes();
	virtual void CreateMacroTestInterface(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	virtual void CreateMacroTestInterface();

	void InitEquation();
	void AddRecordReport(CGbItemBase* pItem);
	void AdjustSafetyComCmdDlgPos();

public:
	CMacroTestInterface* CreateMacroTestInterface(const CString &strType, const CString &strProgID);
	void CreatePpDeviceRefs();
	void ReleasePpDeviceRefs(BOOL bPpDeviceHasDelete=TRUE);
	void InitPpDeviceRefsCommConfig();

public:
	virtual void ReleaseMacroTestInterface(BOOL bRelease=TRUE);

public:
	void QueryRecord(CGbItemBase* pItem);

protected:
	void GetAllInlegibleTestItems(CExBaseList *pList, CExBaseList *pGbList);

//////////////////////////////////////////////////////////////////////////
//ͨѶ����Ĵ���
public:
	BOOL m_bCanRunCommCmdFinalResultScript;

	BOOL Out_RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
		, WPARAM wParam, LPARAM lParam, UINT nProcedureType);
	
	//ִ��ͨѶ����
	virtual BOOL RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
		, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd);
	BOOL UnRegisterProcedureMsg(WPARAM wParam, LPARAM lParam, HWND hMsgRcvWnd);

protected:
	//��������Ŀ����ҪΪ����������Ŀ��ͨѶ���SysParaEdit
	//long TestFirstSubItems();
	//CGbItemBase* GetNextTestSubItem();

	static const BSTR g_strDataInterfaceID_CPU;
	static const BSTR g_strDataInterfaceID_Group;
	static const BSTR g_strDataInterfaceID_Index;
	static const BSTR g_strDataInterfaceID_Value;

	long GetCurrCpuIndex(CCommCmd *pItem);
	CString GetCurrCpuIndexString(CCommCmd *pItem);

	virtual BOOL ExecuteTestItemCommCmd_ViewDlg(CCommCmd* pItem);
	virtual BOOL ExecuteTestItemCommCmd(CCommCmd* pItem);

	long TestItemCmdRunProcedure(CCommCmd* pItem);
	void Update_dsSetting_TimeData_s(CDataSet *pDataset);
	void Update_dsSetting_TimeData_ms(CDvmDataset *pDataset);
	void AddAnalogErrorDatas(CCommCmd* pItem, CValues * oValues);
	CReport* AddCommCmdReportData(CCommCmd* pItem, CDvmDataset *pDatas);
	CReport* AddCommCmdReportData(CCommCmd* pItem, CDataSet *pDatas);
	CReport* GetReport_AddCommCmdReportData(CCommCmd* pItem);
	long ContinueTestCommCmd(CCommCmd* pItem, BOOL &bFinish);
	long ProcessFinishCommCmdNormal(CCommCmd* pItem);
	long GbDeleteAllNodeData(const CString &strID);
	long ProcessFinishCommCmdMamual(CCommCmd* pItem);
	long GetCommCmdItemReportFillIndex(CCommCmd* pItem);
	long GetCommCmdItemMaxRepeatTimes(CCommCmd* pItem);
	void FillCommCmdItemReport(CCommCmd* pItem, CReport *pReport);  //��дͨѶ������Ŀ�ı�������
	
	//ִ�й���
	CString m_strProcedureID;
	CString m_strDatasetPath;
	
	//ִ�й��̵����ͣ�ͨѶ�������ͺͲ�����Ŀ����
	//�Զ�������ף��������ִ��ͨѶ����İ�ť������˰�ť�����������ͣ���Out_RunProcedure��
	UINT   m_nRunProcedureType;  

	void AddSoeDatasToReportEx(CReport *pReport);

	CValues m_listMacroTestResults;
	void BackMacroTestResults(CReport *pReport);
	void BackMacroTestResult(CReport *pReport, const CString &strValID);
	void UpdateMacroTestResults(CReport *pReport);

	CReport* CreateCmmFinalReport(CCommCmd* pItem, long nRepeatTimes);
	CReport* CreateMtFinalReport(CMacroTest* pItem);
	CReport* CreateMtFinalReport(CCommCmd* pItem, long nCalMode, long nRepeatTimes);
	void CreateCalRpt_SubItems(CMacroTest *pMacroTest);
	void GetCmmReportsForCal(CCommCmd* pItem, CExBaseList &oReports);
	void GetMtReportsForCal(CGbItemBase* pItem, CExBaseList &oReports);
	void CmmCalReports_Average(CReport *pReportFinal, CExBaseList &oReports);
	void CmmCalReports_Max(CReport *pReportFinal, CExBaseList &oReports);
	void CmmCalReports_Min(CReport *pReportFinal, CExBaseList &oReports);
	void CmmCalReports_ErrorMax(CReport *pReportFinal, CExBaseList &oReports);
	void CmmCalReports_StdError(CReport *pReportFinal, CExBaseList &oReports);
	void CmmCalReports_OverWrite(CReport *pReportFinal, CExBaseList &oReports);
	BOOL CanCal(CValue *oValue, CString &bstrID, CString &bstrValue);

	void AddCpuInterface(CProtocolDeviceInterface* &oPpDevice, CCpu *pCpu, BSTR bstrCpuVal);
	long GetMaxRepeatTimes(long nRepeatTimes);
	long GetCmmMaxRetryTimes();
	long GetCmmRetryDelay();
	BOOL SkipStxmlWhenWSetsError(long nSkipStxmlWhenWSetsError, CCommCmd *pCommCmd);
	BOOL SkipStxml(CCommCmd *pCommCmd);
	BOOL SkipItems(CCommCmd *pCommCmd);
	BOOL SkipItem(CCommCmd *pCommCmd);
	CItems* GetStxmlItemsRoot(CExBaseList *pItem);

	BOOL BreakItems();
	void SkipItemsAndTest(CItems *pItems);
	void SkipTestNext(CGbItemBase *pNextFind);

	void UpdateMacroCharTest_Finished(CMacroTest *pMacroTest, CReport *pReport, long &nCurrIndex);  //��Ŀ����ʱ

public:
	void UpdateMacroCharTest_Testing(CMacroTest *pMacroTest);   //�����м��
	BOOL IsRepeatTimesFinished(CMacroTest *pMacroTest);  //shaolei 20211119 �ظ������Ƿ��Ѿ�ȫ������

//////////////////////////////////////////////////////////////////////////
//�ű��Ľӿ�
public:
	// ��Լ֡¼������
	void GBS_RecordPackage(const  char* pszPkgID);
	void GBS_UnRecordPackage(const  char* pszPkgID);
	void GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);

	// ��ȡ��׼Դװ��GPSʱ����PCʱ���֮���Ӧ��ϵ
	void GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPcTime);

	//��ȡ�����ʼʱ�̵ı�׼Դװ��GPSʱ��
	void GBS_GetOutGpsTime(const char *pszGpsTimeID);
	long GBS_ReadMacroTestResult();
	void GBS_DownloadMacroTestPara();

	long GBS_PpGetDeviceAttr(const char *pszAttrID, CString &strAttr);
	void GBS_PpSetDeviceAttr(const char *pszAttrID, CString &strAttr);
	long GBS_PpRptGetDevieNodeDatas(const char *pszNodePath);
	long GBS_PpRptGetDeviceAttrs(void);
	long GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, CString &strAttr);
	long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue);
	long GBS_PpDeleteAllNodeData(const char *pszNodePath);

	long GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);
	long GBS_PpReleaseDevice(const char *pszDeviceID);
	long GBS_PpReleaseAllDevice();
	long GBS_PpCreateDeviceEx(const char *pszPpFile, const char *pszDeviceFile);
	long GBS_PpReleaseDeviceEx();

	void GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara);
	void GBS_MtRegistPpDataMsg(const char *pszDvmDataPath);
	void GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax);
	void GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath);
	void GBS_MtUnRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax);

	void GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);
	void GBS_MtUnRegistCmdMsg(const char *pszCmdID);

	long GBS_GetTestIndex(CGbItemBase *pItem);

	virtual long GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara);
	virtual long GBS_RcdSetProgID(const char* pszRcdProgID);
	virtual long GBS_RcdExit();
	virtual long GBS_RcdConfig(const char* pszPara);
	virtual long GBS_RcdSelect(const char* pszPara);
	virtual long GBS_RcdValidate(const char* pszRsltID);
	virtual long GBS_RcdCmpClear();
	virtual long GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile);
	virtual long GB_GetFullPath(CGbItemBase *pCurrItem, CString &strFile);
	virtual long GBS_RcdCmp_GetFiles(const char* pszStdFile, const char* pszTestFile, CString &strStdFile, CString &strTestFile, CGbItemBase **ppRcdCmpItem);
	virtual long GBS_RcdAnalyse(const char* pszRcdFile);
	virtual long GBS_RcdAnalyse_GetFile(const char* pszRcdFile, CString &strRcdFile, CGbItemBase **ppRcdCmpItem);
	virtual CCommCmd* GBS_RcdCmp_GetCommCmd();
	virtual long GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);
	virtual CString GBS_RcdGetRcdDestPath(BOOL bIsFullPath);
	virtual long GBS_RcdSetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir);
	virtual CString GBS_RcdGetPath(CGbItemBase *pItem, long nAppendItemPath, const CString &strRcdFilePathRoot, long nAppendTestTimeDir);

	virtual BOOL Parse_Item_File_Path(CGbItemBase *pCurrItem, const CString &strEpxr, CString &strRet);
	virtual BOOL Parse_Report_File_Path(CGbItemBase *pCurrItem, const CString &strEpxr, CString &strRet);
	
	BOOL Parse_Report_File_Path(CGbItemBase *pCurrItem, CString &strPath);
	void SetPpEngineRecordFilePath(CProtocolDeviceInterface *oPpDevice);

	virtual void Gbs_SetTmTriggerSecond(long nSecond, long nOptr);
	virtual void Gbs_SetTmTriggerCountMinute(long nMinute);
	virtual void Gbs_EnterTmTrigger();
	virtual void Gbs_StartTimerTigger();
	virtual void Gbs_StopTimerTrigger();

	CDataSet* GetDataset(CCommCmd *pCommCmd, CString *pStrDatasetPath=NULL);
	long JudgeItemGotoItemEx(CGbItemBase **ppItemGotoItemEx_Curr, CString &strGotoItemExPath, long &nGotoItemLogic);

	//��װ�á�������Թ�����ת  2017-11-22
	CString m_strGotoItemExPath;
	CGbItemBase *m_pItemGotoItemEx;
	CGbItemBase *m_pItemGotoItemEx_Curr;
	long m_nGotoItemExAndOr;
	long m_nGotoItemExRsltState;

	long GBS_BinRslt(CGbItemBase *pItem, const char *pszParaID, const char *pszRsltID);
	long GBS_BinStateRslt(CGbItemBase *pItem, const char *pszParaID, const char *pszRsltID);
	long GBS_BinChngCntRslt(CGbItemBase *pItem, const char *pszBinChngData, const char *pszRsltID);

	void 	GBS_AddDataErrorToRpt(CGbItemBase *pItem, const char* pszDataID, long nValue);
	double GBS_GetItemParaValueEx(CGbItemBase *pItem, const char* pszValID);
	virtual CReport* GBS_GetReport(CGbItemBase* pItem, long nIndex);
	void GBS_OffsetTestDataByGbrptIndex(CGbItemBase *pItem, const CString &strRsltDataID);

protected:
		void ClearGotoItemEx()
		{
			m_pItemGotoItemEx = NULL;
			m_pItemGotoItemEx_Curr = NULL;
			m_strGotoItemExPath.Empty();
			m_nGotoItemExRsltState = 0;
			m_nGotoItemExAndOr = 0;
		}


//////////////////////////////////////////////////////////////////////////
//ͨѶ����
protected:
	CPpDeviceRefs m_oDeviceRefs;
	long GetCommCmdCurrDeviceIndex(CCommCmd *pCommCmd);
	BOOL IsDeviceConnectSucc(CCommCmd *pCommCmd);

    //Cmm-Config  lijunqing 2020-09-08
    CDataGroup m_oCmmConfig;

public:
     //Cmm-Config  lijunqing 2020-09-08
    void InitCmmConfig(CDataGroup *pCmmConfig);
    CDataGroup* GetCmmConfig();
	long GetDeviceRefsCount();

	virtual void ReleasePpEngine();

protected:
	class CGbItemBaseMapForDB
	{
	public:
		CGbItemBaseMapForDB(CGbItemBase *pRefItem)
		{
			m_pRefItem = pRefItem;
			CString strTempFileName = ats_GetBinaryTempFile(pRefItem);
			m_pTempItemForDB = pRefItem->OpenBinaryTempFileForRpt(strTempFileName);
		}
		virtual ~CGbItemBaseMapForDB()
		{
			delete m_pTempItemForDB;
		}
		
		double GetItemParaValueEx(const char* pszValID)
		{
			if (m_pTempItemForDB != NULL)
			{
				return m_pTempItemForDB->GetItemParaValue(pszValID);
			}
			else
			{
				return m_pRefItem->GetItemParaValue(pszValID);
			}
		}

		CReport* GetReport(long nIndex)
		{
			if (m_pTempItemForDB != NULL)
			{
				return m_pTempItemForDB->GetReport(nIndex);
			}
			else
			{
				return m_pRefItem->GetReport(nIndex);
			}
		}

		CGbItemBase *m_pRefItem;
		CGbItemBase *m_pTempItemForDB;
	};

	class CGbItemBaseMapForDB_Mngr : public CTLinkList<CGbItemBaseMapForDB>
	{
	public:
		CGbItemBaseMapForDB_Mngr(){};
		virtual ~CGbItemBaseMapForDB_Mngr(){};

		double GetItemParaValueEx(CGbItemBase *pItem, const char* pszValID)
		{
			CGbItemBaseMapForDB *p = AddMapForDB(pItem);
			return p->GetItemParaValueEx(pszValID);
		}
		CReport* GetReport(CGbItemBase *pItem, long nIndex)
		{
			CGbItemBaseMapForDB *p = AddMapForDB(pItem);
			return p->GetReport(nIndex);
		}

	private:
		CGbItemBaseMapForDB* FindMapForDB(CGbItemBase *pRefItem)
		{
			POS pos = GetHeadPosition();
			CGbItemBaseMapForDB *p = NULL;
			CGbItemBaseMapForDB *pFind = NULL;

			while (pos != NULL)
			{
				p = (CGbItemBaseMapForDB *)GetNext(pos);

				if (p->m_pRefItem == pRefItem)
				{
					pFind = p;
					break;
				}
			}

			return pFind;
		}

		CGbItemBaseMapForDB* AddMapForDB(CGbItemBase *pRefItem)
		{
			CGbItemBaseMapForDB *pFind = FindMapForDB(pRefItem);

			if (pFind == NULL)
			{
				pFind = new CGbItemBaseMapForDB(pRefItem);
				AddTail(pFind);
			}

			return pFind;
		}
	};

	CGbItemBaseMapForDB_Mngr m_oGbItemBaseMapForDB_Mngr;
};

BOOL ats_IsTestControlManyReport(CTestControlBase *pTestControl);
BOOL ats_IsTestControlManyDevice(CTestControlBase *pTestControl);
BOOL ats_IsTestControlSdvMpp(CTestControlBase *pTestControl);

BOOL ats_IsTestControlMode_NORMAL(CTestControlBase *pTestControl);
BOOL ats_IsTestControlMode_MGBRPT(CTestControlBase *pTestControl);
BOOL ats_IsTestControlMode_MDGBRPT(CTestControlBase *pTestControl);
BOOL ats_IsTestControlMode_MDVMGBRP(CTestControlBase *pTestControl);
BOOL ats_IsTestControlMode_SDVMPP(CTestControlBase *pTestControl);

CGbItemBase* ats_CloneGbItemFromDB(CGbItemBase *pGbItem);

//2021-1-2  lijunqing add: BOOL bClone
CGbItemBase* ats_CloneGbItemFromDB(CGbItemBase *pGbItem, CBinarySerialBuffer &oBuffer, BOOL bClone);

//2021-2-23  lijunqing : 
//CTestControlBase*  tctrl_GetTestControl(CExBaseObject *pItem);
long tctrl_GetTestControlIndex(CTestControlBase *pTestControl);

extern CString g_strRcdFilePathRoot;
extern BOOL g_bCreateTestTimesDir;

//2021-8-5  lijunqing
CGuideBook* ats_FindGuideBookByDeviceSN(CTestControlBase *pMainTestControl, const CString &strDeviceSN);
BOOL ats_IsGuideBook_DeviceSN(CGuideBook *pGuideBook, const CString &strDeviceSN);

//shaolei 2023-9-1
//���±������ݵ�����
void ats_InitReportValuesName(CReport *pReport, CMacroTest *pMacroTest);
void ats_InitReportValuesName(CValue *pValue, CXExprNode *pNode);