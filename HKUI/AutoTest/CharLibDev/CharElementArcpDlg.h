#pragma once

#include "CharElmentBaseDlg.h"
#include "..\Module\Characteristic\CharElementArcp.h"
#include "..\..\Module\BaseClass\ExBaseListComboBox.h"

// CCharElementArcpDlg 对话框

class CCharElementArcpDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementArcpDlg)

public:
	CCharElementArcpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementArcpDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_ARCP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CString m_strZ;
	CString m_strPh;
	CString m_strRadius;
	CString m_strAngleBegin;
	CString m_strAngleEnd;
	CString m_strDir;
	CExBaseListComboBox m_cmbDir;
	CExBaseListComboBox m_cmbClockwise;
};
