#pragma once
#include "sysparagrid.h"

#include "UITestGlobalDefine.h"
#include "CommCmdGrid.h"
// CUICommCmdDlg 对话框


class CUICommCmdDlg : public CDialog
{
	DECLARE_DYNAMIC(CUICommCmdDlg)

public:
	CUICommCmdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUICommCmdDlg();

// 对话框数据
	//enum { IDD = IDD_DLG_SYSPARAS };

private:
	CCommCmd* m_pTestItemCommCmd;
	CTestControlWnd* m_pWndMsgRcv;
	CString m_strType;

	//所有CPU的集合
	CExBaseList m_setCpu;

	//当前CPU及对应的CSet
	CCpu* m_pCurCpu;
	CExBaseList m_listNodeDatas;

	//当前CCommCmd对应的CDevice
	CDevice* m_pCurDevice;

	//初始化Tab页
	void InitTabandCpu();
	
	//切换当前CPU
	void ChangeCurCpu(CCpu* pChangeCpu);
	void CreateCommCmdGrid();

public:
	CExBaseList* GetDatas()	{	return &m_listNodeDatas;	}
	void InitTestItem(CCommCmd* pTestItemCommCmd, CTestControlWnd *pWndMsgRcv);
	void FinishTestCmmCmdItem();
	void FinishTestItem();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CCommCmdGrid *m_pGridCmdDatas;
	CTabCtrl	m_tabParaSel;
	CButton m_btnNext;

	CRect rectWin,rectTab,rectGrid,rectBtnNext;

	void InitMacroRect();

	CFont m_font;
	LOGFONT m_lfFont;
	CFont m_fontRsltCtrl;

	afx_msg void OnBnClickedOk();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEndEdit(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
