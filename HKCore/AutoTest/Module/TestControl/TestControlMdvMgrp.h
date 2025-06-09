#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/
#include "TestControlManyReport.h"

/*
MdvMgrpSpo测试模式
1）电气量项目：有主TestControl控制执行，子TestControl设置与主TestControl一致
2）提示信息：同上
3）系统参数编辑：同上
4）通讯命令：各自独立处理，有主TestControl统一调度管理
*/

//////////////////////////////////////////////////////////////////////////
//
class CMdvMgrpSpoDeviceTestControl : public CTestControlManyReport
{
public:
	CMdvMgrpSpoDeviceTestControl();
	virtual ~CMdvMgrpSpoDeviceTestControl();

public:
	//单一项目
	virtual long TestSingle(CGbItemBase* pGbItem);
	virtual long TestSingle(long nItemIndex);

	//某个项目到结束
	virtual long TestFrom(CGbItemBase* pGbItem);
	virtual long TestFrom(long nItemIndex);


	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);
	virtual void InitItemsRsltExprScript(CCommCmd* pItem);

	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);
	virtual long FinishTestItemSysParaEdit(CSysParaEdit* pItem);

	virtual BOOL NeedTestNextDevice();
	virtual BOOL ContinueTestByItemsRsltExprScript(CCommCmd* pItem);

	virtual void AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
	virtual void AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes); //20170529

	virtual void EditItemPara(CCommCmd *pCommCmd, CValue *pValue);
	virtual void EditItemPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual CReport* AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex);
	virtual BOOL ItemsRsltExprScriptTimeIgnore();
	virtual void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);
	virtual BOOL GBS_CanBreakLoop(CGbItemBase *pItem);
	virtual void GBS_ClearBreakLoopState(CGbItemBase *pItem);
	virtual long GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);
	virtual long FinishTestItemMacroTest_Process(CMacroTest* pItem); //2019-4-27 MdvTestEach

	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //外部停止测试：用户停止测试、由于异常停止测试
public:
	virtual long CopyChildDeviceTestControlReport(CMacroTest* pItem, CReport *pReportSrc);
	void TestMainItem(CGbItemBase *pItem);
	void InitTestItem(CGbItemBase *pCurrItem, CGbItemBase *pSubItem);

};


//////////////////////////////////////////////////////////////////////////
//
class CMdvMgrpSpoDeviceMngrTestControl : public CTestControlManyReport
{
public:
	CMdvMgrpSpoDeviceMngrTestControl();
	virtual ~CMdvMgrpSpoDeviceMngrTestControl();
	
	CExBaseList m_listMdvMgrpTestControl;
	CTestTasks* GetTestTasks();

protected:
	CTestTasks m_oTestTasks;
	CString m_strStdDestFile;

public:
	virtual void SetTestItemState(CGbItemBase* pItem, UINT nState);

	virtual void InitGuideBook();
	virtual long FindTestControlIndex(CTestControl *pTestControl);
	virtual void AttachTestControlWnd(CTestControlWnd *pWndRef);
	virtual long CreatemUICommCmdViewDlg(LPVOID pUIViewDlg);
	virtual void InitItemsRsltExprScript(CCommCmd* pItem);

	virtual UINT GetTestControlMode()	{	return TESTCONTROLMODE_MDVMGRP;	}
	//virtual void TestNextDevice(CGbItemBase *pItem, CTestControlMngrBase *pTestControlMngr);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);
	virtual long StopTestExtern(const CString &strMsg = _T(""), BOOL bExtern=FALSE);  //外部停止测试：用户停止测试、由于异常停止测试

	virtual BOOL AfterFinishTestItemSafety(CSafety *pSafety);
	virtual BOOL AfterFinishTestItemSafety_OneTime(CSafety *pSafety);

	virtual long FinishTestItemSysParaEdit(CSysParaEdit* pItem);

	virtual long TestItemMacroTest(CMacroTest* pItem);
	virtual long TestItemMacroTest_MdvEach(CMacroTest* pItem);
	virtual void GetMacroTestParaDatas(CMacroTestPara* pTestPara, CString &strPataDatas); //2018-12-23开关量合并处理 lijq
	virtual CReport* UpdateMacroTestReport(CMacroTest* pItem);

	virtual void AfterUpdateMacroTestReport(CMacroTest* pItem, long nMacroTestTimes); //20170529
	virtual void AfterCreateMtFinalReport(CMacroTest* pItem, long nMacroTestTimes); //20170529

	//virtual long FinishTestItemMacroTest_Only(CMacroTest* pItem);
	virtual void ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_Repeat(CCommCmd* pItem);
	virtual BOOL ExcuteCommCmdOnDelayAfterFinish_RepeatEx(CCommCmd* pItem);
	virtual BOOL IsAllItemQualified(CCommCmd* pItem);
	virtual BOOL ContinueTestByItemsRsltExprScript(CCommCmd* pItem);

	virtual BOOL NeedTestNextDevice();
	virtual void ClearSysRptFill(CGbItemBase *pItem);
	virtual void ClearTestSubItem(BOOL bClearMain);
	virtual void EditItemPara(CCommCmd *pCommCmd, CValue *pValue);
	virtual void EditItemPara(CMacroTest *pMacroTest, CShortData  *pData);
	virtual long SelectAllTestControl(CExBaseList &listTestControl, BOOL bMainFirst);
	virtual void SetTestEndTime();
	virtual CReport* AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex);
	virtual BOOL ItemsRsltExprScriptTimeIgnore();
	virtual long FillParentItemsReport(CGbItemBase *pItems);
	virtual void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);
	virtual long UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg=TRUE);
	virtual long UpdateStateAfterFinishTestItem_MdvEach(CGbItemBase* pItem);

	virtual long CopyChildDeviceTestControlReport(CMacroTest* pItem, CReport *pReportSrc);
	BOOL IsMdvMgrpTailItem(CExBaseObject *pItem);
	CMdvMgrpSpoDeviceTestControl* GetNextDevice(CExBaseObject *pItem);
	CMdvMgrpSpoDeviceTestControl* GetCurrDevice(CExBaseObject *pItem);

	virtual void SetCommCmdRepeatTimes(long nTimes);
	virtual BOOL GBS_CanBreakLoop(CGbItemBase *pItem);
	virtual void GBS_ClearBreakLoopState(CGbItemBase *pItem);
	virtual long GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);
	virtual long FinishTestItemMacroTest_Process(CMacroTest* pItem); //2019-4-27 MdvTestEach

protected:
	BOOL TestOwn(CCommCmd* pItem);
	BOOL ContinueTestByItemsExpr(CCommCmd* pItem);
	BOOL TestOwn(CSafety* pItem);
	BOOL TestNextDeviceMainItem(CCommCmd* pItem);
	void CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas);
	void CombineTestParaDatas(CString &strDestParaDatas, const CString &strSrcDatas, const CString &strParaID);

public:
	void CreateAllFilesByTasks(CTestTasks *pSrcTasks);
	void CreateByTasks(CGuideBook *pGuideBook, const CString &strDocFile);
	void CreateByTasks(CTestTasks *pSrcTasks, CGuideBook *pGuideBook, const CString &strDocFile);
	void CreateEnginePoProject();
	void InitBinRng();

protected:
	void CreateByTask(CGuideBook *pGuideBook, const CString &strDocFile, CTestTask *pTestTask, long nTaskIndex);

public:
	void OpenTasksFile(const CString &strTasksFile);
	void CreateTestControls(BOOL bCreate);
	CTestTask* GetSelectTestTask(CExBaseList &listTask, POS &posCurr);
	
protected:
	void CreateMainTestControls(CTestTask *pTestTask, long nTaskIndex, BOOL bCreate);
	void CreateSubMgrpTestControls(CTestTask *pTestTask, long nTaskIndex, BOOL bCreate);

	BOOL ProcessGotoItemEx();
	BOOL ProcessBreakLoopByAllRpt();

public:
	CTestControl* GetTestControlByIndex(long nIndex);

public:
	virtual void ReleaseMacroTestInterface(BOOL bRelease=TRUE);

	virtual void SaveFinalXMLReport();
	virtual void UploadRptFiles(CString &strFiles);
	//调整报告，试验完成后归档调用
	virtual void AdjustReport(CThreadProgressInterface *pProgress=NULL);
	virtual BOOL SetItemState(CDataGroup *pParas);
	virtual void ResetTestControl();   //shaolei 2023-11-6

	//shaolei 2023-11-1
	virtual void AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *pInterface);
	virtual void OnTestItemCount_TCtrlMsg(long nItemCount);
	virtual void OnTestBegin_TCtrlMsg();
	virtual void OnStopTest_TCtrlMsg(long nType);
	virtual void OnException_TCtrlMsg(long nEvent, const CString &strError);
	virtual void OnConnectSuccess_TCtrlMsg();
};

