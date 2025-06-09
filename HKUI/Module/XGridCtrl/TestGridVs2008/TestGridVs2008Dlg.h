﻿
// TestGridVs2008Dlg.h : 头文件
//

#pragma once

#include "MyGridctrl.h"

// CTestGridVs2008Dlg 对话框
class CTestGridVs2008Dlg : public CDialog
{
// 构造
public:
	CTestGridVs2008Dlg(CWnd* pParent = NULL);	// 标准构造函数
	CMyGridCtrl m_gridex;
	void CreateGrid();

// 对话框数据
	enum { IDD = IDD_TESTGRIDVS2008_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
