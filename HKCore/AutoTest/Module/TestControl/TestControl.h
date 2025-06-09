#pragma once

/*
	功能描述：测试控制对象；管理一个测试的全部过程
*/

#include "TestControlBase.h"


#include "../TaskMngr/TestProject.h"
#include "../GuideBookFileMngr/GuideBookFileMngr.h"

#include "../UITestItem/UISafetyTest.h"
#include "../GuideBook/ReportMap/WordReport/WordRptFill.h"
#include "../GuideBook/ReportMap/WPSReport/WPSRptFill.h"

#include "../GuideBook/ReportMap/SystemReport/SystemRptFill.h"
#include "../UITestItem/SysParaEditDlg.h"
#include "../UITestItem/UICommCmdDlg.h"
#include "../UITestItem/UICommCmdViewDlg.h"
#include "../UITestItem/TestItemViewGrid.h"


class CTestControl : public CTestControlBase
{
public:
	CTestControl();
	virtual ~CTestControl();

	virtual void SetTestError(const CString &strTestError);
	virtual BOOL ProcessAfterCommCmdFinish(CCommCmd *pCommCmd);

	//创建通讯规约引擎对象
	virtual void CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef);
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);

	virtual long CreatemUICommCmdViewDlg(LPVOID pUIViewDlg);
	virtual void HideCommCmdAttrDlg();

	CTreeCtrl* GetGbTreeCtrl()	{	return m_pGbTreeCtrl;	}
public:
	CTestItemViewGrid *m_pInlegibleTestItemViewGrid;

	//安全检查用户界面
	CUISafetyTest* m_pSafetyDlg;

	//系统参数录入界面
#ifndef GUIDEBOOK_DEV_MODE
	CSysParaEditDlg* m_pSysParaEditDlg;
	CSysParaEditDlg* m_pSysParaViewDlg;
#endif

	//通讯命令手动录入界面
	//CUICommCmdDlg *m_pCommCmdDlg;

	//通讯命令属性显示
	BOOL m_bUICommCmdViewDlgRef;
	CUICommCmdViewDlg *m_pUICommCmdViewDlg;

	//2020-02-03 lijq  自动测试与测试模板编辑程序之间进行项目参数的交互
	CTreeCtrl *m_pGbTreeCtrl;

	virtual BOOL OpenWordReportFile(BOOL bExportWord=FALSE, const CString &strDocFile=_T(""));
	virtual BOOL OpenWordReportFileOnly(CString &strWordFile);

public:
	//TCtrl异常
    virtual void IsMacroTCtrlException();

	//自动上传测试报告
	void AutoSaveReportFileName(CWnd *pParentWnd, BOOL bJudgeState=FALSE);
	virtual void EmptyReportDatas(BOOL bUseCfgFlag=TRUE);
	virtual void ChangeReportFileName(const CString &strFileName);

public:
	virtual long TestItemSafety(CSafety* pItem);
	virtual long TestItemSysParaEdit(CSysParaEdit* pItem);
	virtual long TestItemSysParaEdit_Test(CSysParaEdit* pItem);
	virtual long ViewSysPara(const CString &strSysParaID, CGbItemBase *pCurrSelItem);
	virtual void ShowItemReportDsv(CExBaseObject *pGbItem, CReport *pReport);

	long FinishTestItemCommCmd(CCommCmd* pItem);
	virtual void AddSysParasToTask(CSysParaEdit* pItem);
	virtual long UpdateStateAfterFinishTestItem(CGbItemBase* pItem, BOOL bNeedFireMsg=TRUE);
	virtual long TestNextSubItem(CGbItemBase* pCurrSubItem);

	virtual long FinishCurrTestItem(CDataGroup *pDataGroup);
	//外部接口
	virtual long CreateReportFill(const CString &strRptProgID, BOOL bExportWord=FALSE);
	virtual CWordRptExportBase* CreateRptExport(const CString &strRptProgID);

	//shaolei 20220611
	virtual void FinishInptuData(CDataGroup *pDataGroup);
protected:
	//隐藏全部测试相关的界面
	virtual void HideAllTestItemUI();
	virtual void DestroyAllTestItemUI();

	void AddRecordReport(CGbItemBase* pItem);
	void AdjustSafetyComCmdDlgPos();

public:
	virtual void AttachItemViewGrid(void *pGrid, BOOL bUpdateGrid);

//////////////////////////////////////////////////////////////////////////
//通讯命令的处理
public:
	//执行通讯过程
	virtual BOOL RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
		, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd);

private:
	virtual BOOL ExecuteTestItemCommCmd_ViewDlg(CCommCmd* pItem);
	virtual BOOL ExecuteTestItemCommCmd(CCommCmd* pItem);

//////////////////////////////////////////////////////////////////////////
//脚本的接口
public:
	long GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara);
	long GBS_RcdSetProgID(const char* pszRcdProgID);
	long GBS_RcdExit();
	long GBS_RcdConfig(const char* pszPara);

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
	virtual long GBS_RcdCmp_CopyStdFile(CTestControl *pTestControl, CString &strStdSrcFile, CString &strStdDestFile);
	virtual void RcdAnalyse(const CString &strTestFile);

	virtual void Gbs_SetTmTriggerSecond(long nSecond, long nOptr);
	virtual void Gbs_SetTmTriggerCountMinute(long nMinute);
	virtual void Gbs_EnterTmTrigger();
	virtual void Gbs_StartTimerTigger();
	virtual void Gbs_StopTimerTrigger();

//2020-12-21  lijunqing
public:
	void ConfigVmEngine();
	void ConfigPpEngine();
};
