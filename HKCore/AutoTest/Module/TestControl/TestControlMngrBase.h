#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "TestControl.h"
#include "../TaskMngr\TestTask.h"

class CTestControlChildBase : public CTestControl
{
public:
	CTestControlChildBase();
	virtual ~CTestControlChildBase();

//2017-3-18  测试控制部分，全部设置为虚函数，便于多测试的控制
public:
	//单一项目
	virtual long TestSingle(CGbItemBase* pGbItem);
	virtual long TestSingle(long nItemIndex);

	//某个项目到结束
	virtual long TestFrom(CGbItemBase* pGbItem);
	virtual long TestFrom(long nItemIndex);

public:
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);
	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual void CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //外部停止测试：用户停止测试、由于异常停止测试
	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);

	virtual void ContinueExecutePpEngineCmd(CTestControl *pTestControl);
	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);

	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);
	//virtual void InitItemsRsltExprScript(CCommCmd* pItem);
	virtual BOOL ContinueTestByItemsRsltExprScript(CCommCmd* pItem);

	virtual void EditItemPara(CCommCmd *pCommCmd, CValue *pValue);
	virtual void EditItemPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual BOOL ItemsRsltExprScriptTimeIgnore();
	virtual void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);

	virtual void GBS_GotoItemEx_Go(CGbItemBase *pItem){};
	virtual BOOL GBS_CanBreakLoop(CGbItemBase *pItem);
	virtual void GBS_ClearBreakLoopState(CGbItemBase *pItem);
	virtual long GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);
	
	virtual long FinishTestItemMacroTest_Process(CMacroTest* pItem); //2019-4-27 MdvTestEach

};

class CTestControlMngrBase : public CTestControl
{
public:
	CTestControlMngrBase();
	virtual ~CTestControlMngrBase();

	void AddSysPara(const CString &strID, const CString &strValue);
	void AddSysPara(const CString &strID, long nValue);
//2017-3-18  测试控制部分，全部设置为虚函数，便于多测试的控制
public:
	virtual BOOL IsTestControlMngr()	{	return TRUE;		}

	//单一项目
	virtual long TestSingle(CGbItemBase* pGbItem);
	virtual long TestSingle(long nItemIndex);

	//某个项目到结束
	virtual long TestFrom(CGbItemBase* pGbItem);
	virtual long TestFrom(long nItemIndex);

public:
	virtual BOOL OpenTaskFile(const CString &strFile);
	virtual BOOL OpenTaskFile_XML(const CString &strFile);
	virtual void InitByTask(CTestTask *pTestTask, BOOL bCreate);
	virtual CTestTask* CloneTask(CTestTask *pTestTask);
	virtual void InitByOwnTask();
	virtual CTestControl* CreateChildTest(CTestProject *pProject, long nIndex, BOOL bUpdateTest);
	virtual CTestControl* CreateChildTest();
	virtual CTestTask* GetTestTask();
	virtual CString GetTestTaskFile();
	virtual void SaveTask();
	virtual void SaveTask_XML();

protected:
	//是否自动删除子对象：兼容老版本程序，子对象在框架中删除
	BOOL m_bAutoDeleteChild;
	CTestTask m_oTask;
	CString m_strBinaryTaskFile;

	void UpdateTest(CGuideBook *pGuideBook, CTestProject *pProject);
	void UpdateTest_ReportSN(CGuideBook *pGuideBook, CTestProject *pProject);
	void UpdateTest_DeviceIndex(CGuideBook *pGuideBook, CTestProject *pProject);
	void UpdateTest_TestApp(CGuideBook *pGuideBook, CTestProject *pProject);
	void UpdateTest_DeviceAttr(CGuideBook *pGuideBook, CTestProject *pProject);

public:
	virtual long TestItem(CGbItemBase* pItem);
	virtual long TestItemCommCmdEx(CCommCmd* pItem);
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //外部停止测试：用户停止测试、由于异常停止测试

	virtual BOOL NeedTestNextDevice();
	virtual CReport* UpdateMacroTestReport(CMacroTest* pItem);
	virtual CReport* UpdateMacroTestReport(CGuideBook *pGuideBook, CMacroTest* pItem, CReport *pSrcReport);
	virtual long ProcessFinishCommCmd(CCommCmd* pItem);

	virtual long FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);
	virtual long FinishTestItemSysParaEdit(CSysParaEdit* pItem);

	virtual long TestNextItem();
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);

	virtual void AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
	virtual void AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
//	virtual long FinishTestItemMacroTest_Only(CMacroTest* pItem);
	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);
	virtual void SaveReport();

	virtual long LocateReport(CGbItemBase* pItem, long nIndex);

	virtual BOOL CanRunCommCmdFinalResultScript(CCommCmd* pItem);


	virtual LRESULT OnElectricTestAppMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnElectricTestMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnCommCommandMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnSafetyTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnSysParaEditTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnCommCmdMamualTestFinished(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnManualTestMsg(WPARAM wPara,LPARAM lPara);
	virtual LRESULT OnEngineSystemMessage(WPARAM wParam, LPARAM lParam);

	virtual void ExcuteCommCmdOnDelayBeforeFinish(CCommCmd* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual void CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef);
	virtual CPpDeviceRef* FindPpDeviceRef(WPARAM wParam);
	virtual CProtocolDeviceInterface* FindPpDevice(WPARAM wParam);
	virtual long OnUpdateGbItem(CGbItemBase* pGbItem);

	virtual void ContinueExecutePpEngineCmd(CTestControl *pTestControl);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

	virtual long TestItemMacroTest(CMacroTest* pItem);
	virtual long TestFirstSubItems();
	virtual CGbItemBase* GetNextTestSubItem();
	virtual BOOL CanTestFirstSubItems();
	virtual long CreatemUICommCmdViewDlg(LPVOID pUIViewDlg);
	virtual void InitItemsRsltExprScript(CCommCmd* pItem);

	virtual void AttachTestControlWnd(CTestControlWnd *pWndRef);
	virtual BOOL ContinueTestByItemsRsltExprScript(CCommCmd* pItem);

	BOOL IsTailItem(CExBaseObject *pItem);
	void SetItemsRsltExprScriptIndex(long nIndex, DWORD dwIndex);

	virtual BOOL AfterFinishTestItemSafety_OneTimeEx(CSafety *pSafety);
	virtual long FinishTestItemMacroTest_OnlyEx(CTestControl *pTestControl, CMacroTest* pItem);
	virtual void ClearSysRptFill(CGbItemBase *pItem);
	virtual void ClearTestSubItem(BOOL bClearMain);
	virtual void EditItemPara(CCommCmd *pCommCmd, CValue *pValue);
	virtual void EditItemPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual long SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst);
	virtual void SetTestEndTime();
	virtual void SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime);
	virtual CReport* AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex);
	virtual BOOL ItemsRsltExprScriptTimeIgnore();
	virtual void CopyChildrenTestControlReport(CMacroTest *pMacroTestSrc, CReport *pReportSrc);
	virtual void CopyReportToTestControl(CTestControl *pTestControlDest, CMacroTest *pMacroTestSrc, CReport *pReportSrc, BOOL bIsFinisTest);
	virtual long FillParentItemsReport(CGbItemBase *pItems);
	virtual void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);

	virtual void SetCommCmdRepeatTimes(long nTimes);

	virtual void GBS_GotoItemEx_Go(CGbItemBase *pItem){};
	virtual BOOL GBS_CanBreakLoop(CGbItemBase *pItem);
	virtual void GBS_ClearBreakLoopState(CGbItemBase *pItem);
	virtual long GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);

protected:
	CTestControl *m_pCurrTestControl;

	CExBaseObject* GetItem(CGuideBook *pGuideBook, CExBaseObject *pItem);
	CTestControl* GetTestControl(CExBaseObject *pItem);
	long FindIndexByGuideBook(CGuideBook *pGuideBook);
	CGuideBook* FindGuideBookByIndex(long nIndex);

	virtual BOOL AfterFinishTestItemSafety_OneTime(CTestControl *pTestControl, CSafety *pSafety);
	virtual BOOL AfterFinishTestItemSafety_OneTime(CSafety *pSafety);
	virtual BOOL AfterFinishTestItemSafety_ManyTime(CSafety *pSafety);

	virtual long FinishTestControlSysParaEdit(CTestControl *pDestTestControl, CSysParaEdit* pItem);
	virtual long FinishTestControlSysParaEdit(CSysParaEdit* pItem);

protected:
	virtual CReport* UpdateMacroTestReport(CGuideBook *pGuideBook, CMacroTest* pItem);
	virtual long ProcessFinishCommCmd(CGuideBook *pGuideBook, CCommCmd* pItem);

public:
	virtual long FinishTestItemMacroTest_Process(CMacroTest* pItem); //2019-4-27 MdvTestEach

public:
	virtual void ReleaseMacroTestInterface(BOOL bRelease=TRUE);

};

CTestControlMngrBase* tctrl_GetTestControlMngr(CExBaseObject *pItem);
BOOL tctrl_IsTailTestControlItem(CExBaseObject *pItem);
