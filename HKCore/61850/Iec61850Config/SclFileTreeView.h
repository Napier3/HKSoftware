#pragma once
#include "..\module\scl\sclieccfgtreectrl.h"

#include "DlgSclReadProgress.h"
#include "SclFileCtrlView.h"
#include "..\..\module\filtertext\filtertextcombobox.h"
#include "afxwin.h"
#include "..\..\Module\WndGroupMngr\XUIAutoAdjTool.h"

#include "..\module\SCL\SclFileRead.h"
#include "../Module/SCL/SclIecCfgCtrlsGrid.h"
#include "..\..\Module\XLanguage\XLanguageButton.h" //2016.10.13

// CSclFileTreeView 窗体视图

class CSclFileTreeView : public CFormView , public CXUIAdjItem_Area
{
	DECLARE_DYNCREATE(CSclFileTreeView)

public:
	CSclFileCtrlView *m_pSclFileCtrlView;
	void ShowSelectIED(const CString &strIedId);
	void UpdateSclCtrl(CSclCtrlBase *pSclCtrlBase);//更新m_oIecCfgCtrlsGrid表格
	void ShowGridDatas();
	void AddGridCtrls(CSclCtrls *pSclCtrls);
	virtual void XUI_InitAdjust();

	void xlang_InitAndAdjust();//2016.10.14
	CExBaseList m_oSelectedSclCtrls;

protected:
	CSclFileTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSclFileTreeView();

// 	CDlgSclReadProgress *m_pDlgSclReadProgress;
	CSclFile *m_pSclFile;
	long m_nBtnHeight;
	CFilterTextMngr m_oFilterTextMngr;
	CSclIecCfgCtrlsGrid m_oIecCfgCtrlsGrid;

	CSclFileRead *m_pSclFileRead;

	CSclFileRead* GetSclFileRead();
	void FreeSclFileRead();

public:
	enum { IDD = IDD_SCLFILE_TREE_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSclIecCfgTreeCtrl m_treeSclIecCfg;
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnSclReadFinish(WPARAM, LPARAM);

	CFilterTextComboBox m_cmbFilter;
	CXLanguageButton m_btnFilter; //20131014
	afx_msg void OnBnClickedBtnFilter();
};


