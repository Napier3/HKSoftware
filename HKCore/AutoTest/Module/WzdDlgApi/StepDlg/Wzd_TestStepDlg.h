#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../Module/GuideBook/Items.h"
#include "ListCtrlEx.h"
// CWzd_TestStepDlg 对话框
#define  WM_TEST_STEP_CHANG WM_USER+1000

class CWzd_TestStepDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_TestStepDlg)

public:
	CWzd_TestStepDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_TestStepDlg();

// 对话框数据
	enum { IDD = IDD_TEST_STEP_DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	
public:
	//初始化 列表的值
	void InitCheckStepInfo(CItems& stepItems);
	//检测过程中，更新测试值 测试的状态图标
	void UpdateCheckStepState(CGbItemBase* pStep);
	CGbItemBase* UpdateCheckStepState2();
protected:
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnLvnGetdispinfoCheckStepList(NMHDR *pNMHDR, LRESULT *pResult);
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickCheckStepList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	// 作业指导书
	//CListCtrl m_ctrlCheckStepList;
	CListCtrlEx m_ctrlCheckStepList;
	CImageList m_ImageList;
};
