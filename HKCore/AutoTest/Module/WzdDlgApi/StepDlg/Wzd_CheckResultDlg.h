#pragma once
#include "WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"

#include "../../../Module/GuideBook/Items.h"
#include "afxwin.h"
#include "ListCtrlEx.h"
#include "../StepCtrl/UIDrawer.h"

// CWzd_CheckResultDlg 对话框

class CWzd_CheckResultDlg : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzd_CheckResultDlg)

public:
	CWzd_CheckResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzd_CheckResultDlg();

// 对话框数据
	enum { IDD = IDD_CHECK_RESULT_DIALOG };
	virtual void XUI_InitAdjust();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	

public:
	//初始化 列表的值
	void InitCheckResultInfo();
	//初始化 combox列表的值
	void InitCheckBoxInfo();
	//设置表格内容
	void SetCheckResultInfo(CReports* pReports);
	void SetCurrentCheckResultInfo(CReport* pReport);
	void ClearResult();

protected:
	//消息响应函数
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeCheckCountCombo();

private:
	// 项目检查结果信息
	//CListCtrl m_ctrlItemResutList;
	CListCtrlEx m_ctrlItemResutList;
	//CComboBox m_ctrlCBBChectCount;
	CUIComboBox	m_ctrlCBBChectCount;
	CImageList m_ImageList;

public:
	CStatic m_Static3;
};
