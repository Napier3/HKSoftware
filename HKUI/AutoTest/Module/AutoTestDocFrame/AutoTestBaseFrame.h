#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "AutoTestBaseDoc.h"
#include "AutoTestBaseTreeView.h"
#include "AutoTestBaseReportView.h"
#include "AutoTestBaseLogicView.h"

// 带有拆分器的 CSclFileFrame 框架

class CAutoTestBaseFrame : public CMDIChildWndEx, public CTCtrlMsgRcvInterface
{
	DECLARE_DYNCREATE(CAutoTestBaseFrame)
protected:
	CAutoTestBaseFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CAutoTestBaseFrame();

	CSplitterWnd *m_wndSplitter;
	BOOL m_bTestControlRef;

public:
	virtual long OnException(long nError, const CString &strError, CExBaseObject *pTestControl);
	virtual long OnConnectSuccess(CExBaseObject *pTestControl);
	virtual long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop=TRUE);
	virtual long OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj);
	virtual long OnStopTest(long nType, CExBaseObject *pTestControl);
	virtual long OnUpdateMeasure(long nData, CExBaseObject *pTestControl);
	virtual BOOL IsRunning(long nType, CExBaseObject *pTestControl);
	virtual long HideAllTestItemUI(long nData, CExBaseObject *pTestControl); 
	virtual HWND GetFrameHwnd();
	virtual void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE, BOOL bShow=TRUE);
	virtual void ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow=TRUE);
	virtual void EditItemPara(CExBaseObject *pGbItem);
	virtual void LocateItemReport(CExBaseObject *pGbItem);
	virtual long OnTestBegin(CExBaseObject *pTestControl);

	//shaolei 20220622 SV接收压板一致性测试，需要动态生成项目，需要删除或插入
	virtual void InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	virtual void DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	//shaolei 2023-6-14：插入项目时，递归插入子项目
	virtual void InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem);

protected:
	void ShowMacroCharTestPane(CGbItemBase *pGbItem);

public:
	CTestControlBase* m_pTestControl;
	CAutoTestBaseTreeView *m_pTreeView;
	CAutoTestBaseReportView *m_pReportView;
	CAutoTestBaseLogicView *m_pLogicView;
	CMacroCharTestInterface *m_pMacroCharTestPaneRef;

	virtual BOOL CanCloseAtsFrame();
	virtual BOOL OnCloseAtsFrame();
	virtual BOOL CloseAtsFrame();
	virtual BOOL CloseAtsFrameEx();

	virtual void SelectTestItem(CExBaseObject *pItem);
	void CreateView_Logic(CCreateContext* pContext, CRect rect, long nRight);

	void CreateClient(CTestControlBase *pTestControl, CDocTemplate* pNewDocTemplate, CDocument* pCurrentDoc, CRuntimeClass* pNewViewClass=NULL);
	void CreateClient(CCreateContext* pContext);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};


