#pragma once
#include "../../../iSmartTestWzd/Resource.h"

// CWzdDlg_Advise 对话框

class CWzdDlg_Advise : public CDialog
{
	DECLARE_DYNAMIC(CWzdDlg_Advise)

public:
	CWzdDlg_Advise(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzdDlg_Advise();

// 对话框数据
	enum { IDD = IDD_ADVISE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
