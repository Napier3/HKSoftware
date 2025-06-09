#pragma once
#include "sysparagrid.h"

#include "UITestGlobalDefine.h"


#include "..\GuideBook\SetsTools\StesFileToolsFactory.h"

// CSysParaEditDlg 对话框
#ifdef _UITEST_USE_DIALOGEX
#include "..\..\..\Module\DialogBase\DynDialogEx.h"
class CSysParaEditDlg : public CDynDialogEx
{
#else
class CSysParaEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysParaEditDlg)
#endif

public:
	CSysParaEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysParaEditDlg();

// 对话框数据
	//enum { IDD = IDD_DLG_SYSPARAS };

private:
	CSysParaEdit* m_pTestItemSysParaEdit;
	CTestControlWnd* m_pWndMsgRcv;
	CString m_strDatasetPathForEdit;

	//所有CPU的集合
	CExBaseList m_setCpu;

	//当前CPU及对应的CSet
	CCpu* m_pCurCpu;
	CExBaseList m_listSets;

// 	CSet* EditSelectSet(const CString &strType, CCpus *pCpus, const CString &strPath, CExBaseList *pList);

	//当前CSysParaEdit对应的CDevice
	CDevice* m_pCurDevice;

	//切换当前CPU
	void ChangeCurGroup(long nIndex);

	//用于区别系统参数、测试参数和定值、软压板、控制字的标识
	BOOL m_bSysPara;

	CStesFileToolsFactory *m_pStesFileToolsFactory;
	//CSysParaEditGroups *m_pSysParaEditGroups;;

	void InitListData();
public:
	void InitTestItem(CSysParaEdit* pTestItemSysParaEdit, CTestControlWnd *pWndMsgRcv);
	void InitTestItem(const CString &strSysParaID, CTestControlWnd *pWndMsgRcv, CDevice *pDevice);
	void FinishTestCmmCmdItem();
	void UIFinishTestItem();
	void InitTableItems();
	void ShowSysParaDatas();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSysParaGrid m_gridSysPara;
//	CTabCtrl	m_tabParaEditSel;
	CButton m_btnNext;
	CButton m_btnImport;
	CButton m_btnExport;

	CRect m_rectWin,m_rectTab,m_rectGrid,m_rectBtnNext,m_rectImport,m_rectExport;

	void InitMacroRect();

	CFont m_font;
	LOGFONT m_lfFont;
	CFont m_fontRsltCtrl;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
