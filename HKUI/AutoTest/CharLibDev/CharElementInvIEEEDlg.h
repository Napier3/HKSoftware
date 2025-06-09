#pragma once

#include "CharElmentBaseDlg.h"

// CCharElementInvIEEEDlg 对话框

class CCharElementInvIEEEDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementInvIEEEDlg)

public:
	CCharElementInvIEEEDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementInvIEEEDlg();

	virtual BOOL OnInitDialog();
	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_INV_IEEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	 afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTP;
	CString m_strA;
	CString m_strB;
	CString m_strP;
	CString m_strQ;
	CString m_strK1;
	CString m_strK2;

	 CBitmap  m_bmp;
};
