#pragma once
#include "afxwin.h"
#include "resource.h"
#include "../Module/Characteristic/CharElementPoint.h"

// CDlgAddPoint 对话框

class CDlgAddPoint : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddPoint)

public:
	CDlgAddPoint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddPoint();

// 对话框数据
	enum { IDD = IDD_IOWNDEF_ADDPOINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CString m_strX;
	CString m_strY;
	CCharElementPoint *m_pPoint;
};
