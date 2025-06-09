#pragma once

#include "..\TaskMngr\TestTask.h"
#include "../TestControl\TctrlCntrBaseApp.h"
#include "..\GuideBook\GuideBook.h"

#include "..\..\..\Module\XLanguage\XLangToolBar.h" 
#include "..\..\..\Module\MfcCtrlEx\BmpImageList.h"

#define ID_GBTASK_DOCPANE   4122
#define ID_GBTASK_TREECTRL  4123
#define ID_GBTASK_TOOLBAR  4124

#define ID_TASK_EXPORT_REPORT           38775
#define ID_TASK_ADD_PROJECT             38776
#define ID_TASK_DELETE_PROJECT          38777
#define ID_TASK_MOVEUP_PROJECT          38778
#define ID_TASK_MOVEDOWN_PROJECT        38779
#define ID_TASK_OPEN_REPORT             38781
#define ID_TASK_EXIT                    38782
#define ID_TASK_CLEAR_FINISH_STATE      38783
#define ID_TASK_VIEW_PROJECT_TEMPLATE   38784
// #define ID_TASK_ADD_MDTASK              38786
// #define ID_TASK_ADD_SDVMPPTASK          38788
#define ID_TASK_STITCH_REPORT           38789

class CGbTaskOptrInerface
{
public:
	CGbTaskOptrInerface(){}
	virtual ~CGbTaskOptrInerface()	{}

public:
	virtual BOOL IsTesting() = 0;
	virtual BOOL OpenReport(CTestProject *pProject, CXFolder *pXFolder) = 0;
	virtual CString AddProject() = 0;
	virtual BOOL DeleteProject(CXFile *pFile) = 0;
	virtual void ExitTask() = 0;
};

class CGbTaskToolBar : public CXLangToolBar 
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }

	CMFCToolBarImages m_oImgToolBar;

	BOOL CreateToolBar(CWnd *pParentWnd);
};

class CGBTaskTreeCtrl : public CTreeCtrl
{
public:
	CGBTaskTreeCtrl();
	virtual ~CGBTaskTreeCtrl();

	//属性
private:
	CTestTask *m_pTestTask;

	//公共接口
public:
	void ShowTask(CTestTask* pTestTask);
	void UpdateProject(CTestProject *pProject);
	CTestProject* GetCurrSelProject();
	BOOL ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2);
	void AddErrTestItem(CExBaseObject *pItem);
	void RemoveErrTestItem(DWORD dwItem);
	virtual void AddProject(CTestProject *pProject);

protected:
	virtual void InsertToTreeCtrl(CTestTask *pTask,HTREEITEM htiParent);
	virtual void InsertToTreeCtrl(CTestProject *pProject,HTREEITEM htiParent, HTREEITEM hAfter=TVI_LAST);
	UINT GetProjectBmpID(CTestProject *pProject);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnExpandAllChildren();
	afx_msg void OnTestPoint();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

class CGbTaskDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CGbTaskDockablePane)

public:
	void CreateToolBar();

public:
	CGbTaskDockablePane();
	virtual ~CGbTaskDockablePane();

	void AdjustLayout();//自适应调整尺寸
	CGBTaskTreeCtrl* GetGBTaskTree()							{		return &m_GBTaskTree;		}

	void AttachGbTaskOptrInerface(CGbTaskOptrInerface *pGbTaskOptrInerface)		{	m_pGbTaskOptrInerface = pGbTaskOptrInerface;	}
	void ShowTask(CTestTask *pTestTask, CXFolder *pFolder);
	void UpdateProject(CTestProject *pProject);

	void AddErrTestItem(CExBaseObject *pItem)	{	m_GBTaskTree.AddErrTestItem(pItem);	}
	void RemoveErrTestItem(DWORD dwItem)		{	m_GBTaskTree.RemoveErrTestItem(dwItem);	}
	CXFolder* GetXFolder()						{	return m_pXFolder;	}

private:
	CGbTaskToolBar m_wndToolBar;
	CTestTask *m_pTestTask;
	CGBTaskTreeCtrl m_GBTaskTree;
	CXFolder  *m_pXFolder;
	CGbTaskOptrInerface *m_pGbTaskOptrInerface;

	CBmpImageList m_oImageList;

// 属性
public:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnExportReport();
	afx_msg void OnUpdateExportReport(CCmdUI* pCmdUI);
	afx_msg void OnOpenReport();
	afx_msg void OnUpdateOpenReport(CCmdUI* pCmdUI);
	afx_msg void OnAddProject();
	afx_msg void OnUpdateAddProject(CCmdUI* pCmdUI);
	afx_msg void OnDeleteProject();
	afx_msg void OnUpdateDeleteProject(CCmdUI* pCmdUI);
	afx_msg void OnMoveDownProject();
	afx_msg void OnUpdateMoveDownProject(CCmdUI* pCmdUI);
	afx_msg void OnMoveUpProject();
	afx_msg void OnUpdateMoveUpProject(CCmdUI* pCmdUI);
	afx_msg void OnExitTask();
	afx_msg void OnUpdateExitTask(CCmdUI* pCmdUI);
	afx_msg void OnClearFinishState();
	afx_msg void OnUpdateClearFinishState(CCmdUI* pCmdUI);
	afx_msg void OnViewProjectTemplate();
	afx_msg void OnUpdateViewProjectTemplate(CCmdUI* pCmdUI);
	afx_msg void OnStitchReport();
	afx_msg void OnUpdateStitchReport(CCmdUI* pCmdUI);
};


