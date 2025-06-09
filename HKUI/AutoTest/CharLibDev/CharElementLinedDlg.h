#pragma once
#include "afxwin.h"
#include "CharElmentBaseDlg.h"

#include "..\Module\Characteristic\CharElementLined.h"
#include "..\..\Module\BaseClass\ExBaseListComboBox.h"

// CCharElementLinedDlg 对话框

class CCharElementLinedDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementLinedDlg)

public:
	CCharElementLinedDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementLinedDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_LINED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strXb;
	CString m_strYb;
	CString m_strXe;
	CString m_strYe;
	CExBaseListComboBox m_cmbDir;
};
