#pragma once

#include "CharElmentBaseDlg.h"

// CCharElementInvIECDlg 对话框

class CCharElementInvIECDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementInvIECDlg)

public:
	CCharElementInvIECDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementInvIECDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_INV_IEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTp;
	CString m_strK;
	CString m_strAlpha;
};
