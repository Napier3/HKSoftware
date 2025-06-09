#pragma once
#include "../../../iSmartTestWzd/Resource.h"

// CWndDlg_CheckDetail 对话框

class CWndDlg_CheckDetail : public CDialog
{
	DECLARE_DYNAMIC(CWndDlg_CheckDetail)

public:
	CWndDlg_CheckDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWndDlg_CheckDetail();

// 对话框数据
	enum { IDD = IDD_CHECK_DETAIL_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
