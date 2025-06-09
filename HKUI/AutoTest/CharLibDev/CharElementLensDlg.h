#pragma once
#include "afxwin.h"
#include "CharElmentBaseDlg.h"

#include "..\Module\Characteristic\CharElementLens.h"

// CCharElementLensDlg 对话框

class CCharElementLensDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementLensDlg)

public:
	CCharElementLensDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementLensDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_LENS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strForwardReach;
	CString m_strAngle;
	CString m_strOffset;
	CString m_strWidth;
};
