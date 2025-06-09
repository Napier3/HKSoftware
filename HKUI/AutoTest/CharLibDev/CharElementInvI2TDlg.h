#pragma once

#include "CharElmentBaseDlg.h"

// CCharElementInvI2TDlg 对话框

class CCharElementInvI2TDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementInvI2TDlg)

public:
	CCharElementInvI2TDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementInvI2TDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_INV_I2T };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTp;
	CString m_strA;
};
