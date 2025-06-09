#pragma once

#include "CharElmentBaseDlg.h"
#include "..\Module\Characteristic\CharElementArc.h"
#include "afxwin.h"

#include "..\..\Module\BaseClass\ExBaseListComboBox.h"

// CCharElementArcDlg 对话框

class CCharElementArcDlg : public CDialog , public CCharElmentBaseDlg
{
	DECLARE_DYNAMIC(CCharElementArcDlg)

public:
	CCharElementArcDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharElementArcDlg();

	virtual void CreateDlg(CWnd *pParent) ; 
	virtual void GetData(); 
	virtual void ShowData(); 	
	virtual BOOL IsEnable();

// 对话框数据
	enum { IDD = IDD_DIALOG_ARC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strXCenter;
	CString m_strYCenter;
	CString m_strRadius;
	CString m_strAngleBegin;
	CString m_strAngleEnd;
	CString m_strClockwise;
	CExBaseListComboBox m_cmbDir;
	CExBaseListComboBox m_cmbClockwise;
};
