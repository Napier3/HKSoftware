#pragma once

#include "GbOptmItemGroup.h"
#include "..\..\Module\MfcCtrlEx\ThreadProgrssDlg.h"

class CGbOptimizeTool
{
public:
	CGbOptimizeTool();
	virtual ~CGbOptimizeTool();

	BOOL m_bOptmizeDeviceAll;
	BOOL m_bOptimizeCommCmd;
	BOOL m_bOptimizeSysParaEdit;
	BOOL m_bOptimizeIecConfig;

public:
	void SetParentWnd(CWnd *pWnd);
	void Optimize(CExBaseList *pItems);

//////////////////////////////////////////////////////////////////////////
//通讯命令的优化
protected:
	void GetAllLevel1Items(CExBaseList *pItems, CExBaseList &oListItems);
	BOOL IsItemsHasItems(CExBaseList *pItems);

	void Optimize_Level(CExBaseList *pItems, long nCount, long nIndex);
	void GetAllBftAftItems(CExBaseList *pItems);

	//对项目分类集合进行分组
	BOOL CanBuildGroup(CExBaseObject *pItem);
	void BuildGroup(CExBaseList &oListItems, CExBaseList &oListGroup);
	void BuildGroup(CExBaseList &oListItems, POS posItemsFrom, CExBaseList *pCurrItems, CExBaseList &oListGroup);
	void BuildGroup(CExBaseList &oListItems, POS posItemsFrom, CExBaseObject *pCurrCmd, CExBaseList &oListCmd);
	long BuildGroup(CExBaseList *pCurrItems, CExBaseObject *pCurrItem, CExBaseList &oListCmd);
	long BuildGroup(CCommCmd *pIemDest, CCommCmd *pCurrItem, CExBaseList &oListCmd);

	//优化
	CExBaseList* GetGroupAncestor(CGbOptmItemGroup *pGroup);
	CExBaseList* GetSecondAncestor(CExBaseObject *pItem, CExBaseObject *pFirstAncestor);
	CExBaseList* GetAncestorByDepth(CExBaseObject *pItem, long nIndex);

	void OptimizeCombine(CCommCmd *pDestIem, CCommCmd *pSrcItem);
	void OptimizeCombineRptMap(CExBaseList *pDestRptMap, CExBaseList *pSrcRptMap);
	void OptimizeCombine(CGbOptmItemGroup *Group, CExBaseList *pNewItems);

	//优化“试验前”准备项目
	void OptimizeBfT();
	void OptimizeBfT(CGbOptmItemGroup *pGroup);
	CExBaseList* CreateBfTItems(CExBaseList *pFirstAncestor, CExBaseList *pSecondAncestor);

	//优化“试验后”回复项目
	void OptimizeAfT();
	void OptimizeAfT(CGbOptmItemGroup *pGroup);
	CExBaseList* CreateAfTItems(CExBaseList *pFirstAncestor, CExBaseList *pSecondAncestor);

//////////////////////////////////////////////////////////////////////////
//IEC61850配置的优化
protected:
	void OptimizeIECConfig();
	void GetAllIecItems(CExBaseList *pItems);
	void BuildIecGroup();
	void BuildIecGroup(POS posItemsFrom, CExBaseObject *pCurrItem);
	long BuildIecGroup(CMacroTest *pIemDest, CMacroTest *pCurrItem, CExBaseList &oListMacroTest);
	void OptimizeItemByGroup(CGbOptmItemGroup *pGroup);

//////////////////////////////////////////////////////////////////////////
//测试参数优化
protected:
	void OptimizeSysParaEdit();
	void GetAllSysParaEditItems(CExBaseList *pItems);
	void BuildSysParaEditGroup();
	void BuildSysParaEditGroup(POS posItemsFrom, CExBaseObject *pCurrItem);
	long BuildSysParaEditGroup(CSysParaEdit *pIemDest, CSysParaEdit *pCurrItem, CExBaseList &oListMacroTest);
	void OptimizeSysParaEditConfig(CGbOptmItemGroup *pGroup);

private:
	//通讯命令的优化
	CExBaseList m_listBftItems;
	CExBaseList m_listAftItems;
	CExBaseList m_listBftGroup;
	CExBaseList m_listAftGroup;

	//IEC61850配置的优化
	CExBaseList m_listIecConfig;
	CExBaseList m_listIecCfgGroup;

	//测试参数优化
	CExBaseList m_listSysParaEdit;
	CExBaseList m_listSysParaEditGroup;

	//线程
	CWnd *m_pParentWnd;
	CThreadProgressInterface *m_pThreadProgress;
	CWinThread *m_pOptimizeThread;
	BOOL m_bExInsertState;

	static UINT ExecOptimizeThread(LPVOID pParam);

};

class CGbOptimizeThread : public CWinThread, public CThreadProgressInterface
{
DECLARE_DYNCREATE(CGbOptimizeThread)

public:
	virtual void SetMaxRange(long nMaxRange)
	{
		m_nStepIndex = 0;
		m_nMaxRange = nMaxRange;
		PostThreadMessage(WM_USER + 2355, nMaxRange, nMaxRange);
	}
	virtual void ResetProcess()
	{
		m_nStepIndex = 0;
		PostThreadMessage(WM_USER + 2356, 0, 0);
	}
	virtual void StepIt()
	{
		m_nStepIndex++;
		PostThreadMessage(WM_USER + 2357, 0, 0);
	}

	virtual void ShowMsg(const CString &strMsg)
	{
		CString_to_char(strMsg, m_pszMessage);
		PostThreadMessage(WM_USER + 2358, 0, 0);
	}

	virtual void Exit()
	{
		PostThreadMessage(WM_QUIT, 0, 0);
	}


	void StartTimer(long nTimerLong)
	{

	}

	BOOL IsThreadCreated()	{	return m_pProgressDlg != NULL;}

protected:
	CGbOptimizeThread();           // protected constructor used by dynamic creation

	CThreadProgrssDlg *m_pProgressDlg;
	char m_pszMessage[4096];
	long m_nMaxRange;
	CWnd *m_pParentWnd;
	long m_nStepIndex;

	void ShowProgressDlg();
public:
	static CGbOptimizeThread* CreateTestCtrlThread(CWnd *pWnd)
	{
		CGbOptimizeThread* pThread = (CGbOptimizeThread*)AfxBeginThread(RUNTIME_CLASS(CGbOptimizeThread));
		pThread->m_bAutoDelete = TRUE;
		pThread->ResumeThread();
		pThread->m_pParentWnd = pWnd;
		return pThread;
	}

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CGbOptimizeThread();


	// Generated message map functions
	//{{AFX_MSG(CTestWorkThread)
	afx_msg void On2355(WPARAM wParam, LPARAM lParam);
	afx_msg void On2356(WPARAM wParam, LPARAM lParam);
	afx_msg void On2357(WPARAM wParam, LPARAM lParam);
	afx_msg void On2358(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};