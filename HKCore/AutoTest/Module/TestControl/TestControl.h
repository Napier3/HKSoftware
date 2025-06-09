#pragma once

/*
	�������������Կ��ƶ��󣻹���һ�����Ե�ȫ������
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

	//����ͨѶ��Լ�������
	virtual void CreatePpEngineDevice(CProtocolEngineInterface *pEngine, CPpDeviceRef *pDevieceRef);
	virtual BOOL CreatePpEngineDevice(CCommCmd *pCmd);

	virtual long CreatemUICommCmdViewDlg(LPVOID pUIViewDlg);
	virtual void HideCommCmdAttrDlg();

	CTreeCtrl* GetGbTreeCtrl()	{	return m_pGbTreeCtrl;	}
public:
	CTestItemViewGrid *m_pInlegibleTestItemViewGrid;

	//��ȫ����û�����
	CUISafetyTest* m_pSafetyDlg;

	//ϵͳ����¼�����
#ifndef GUIDEBOOK_DEV_MODE
	CSysParaEditDlg* m_pSysParaEditDlg;
	CSysParaEditDlg* m_pSysParaViewDlg;
#endif

	//ͨѶ�����ֶ�¼�����
	//CUICommCmdDlg *m_pCommCmdDlg;

	//ͨѶ����������ʾ
	BOOL m_bUICommCmdViewDlgRef;
	CUICommCmdViewDlg *m_pUICommCmdViewDlg;

	//2020-02-03 lijq  �Զ����������ģ��༭����֮�������Ŀ�����Ľ���
	CTreeCtrl *m_pGbTreeCtrl;

	virtual BOOL OpenWordReportFile(BOOL bExportWord=FALSE, const CString &strDocFile=_T(""));
	virtual BOOL OpenWordReportFileOnly(CString &strWordFile);

public:
	//TCtrl�쳣
    virtual void IsMacroTCtrlException();

	//�Զ��ϴ����Ա���
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
	//�ⲿ�ӿ�
	virtual long CreateReportFill(const CString &strRptProgID, BOOL bExportWord=FALSE);
	virtual CWordRptExportBase* CreateRptExport(const CString &strRptProgID);

	//shaolei 20220611
	virtual void FinishInptuData(CDataGroup *pDataGroup);
protected:
	//����ȫ��������صĽ���
	virtual void HideAllTestItemUI();
	virtual void DestroyAllTestItemUI();

	void AddRecordReport(CGbItemBase* pItem);
	void AdjustSafetyComCmdDlgPos();

public:
	virtual void AttachItemViewGrid(void *pGrid, BOOL bUpdateGrid);

//////////////////////////////////////////////////////////////////////////
//ͨѶ����Ĵ���
public:
	//ִ��ͨѶ����
	virtual BOOL RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
		, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd);

private:
	virtual BOOL ExecuteTestItemCommCmd_ViewDlg(CCommCmd* pItem);
	virtual BOOL ExecuteTestItemCommCmd(CCommCmd* pItem);

//////////////////////////////////////////////////////////////////////////
//�ű��Ľӿ�
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
