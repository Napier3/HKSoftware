#pragma once
#include "SclCheckSettingDlgGrid.h"
#include "..\..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include "afxcmn.h"

#include "SclCheckCtrlDlg.h"

// CSclCheckSetDlg 对话框

class CSclCheckSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclCheckSetDlg)

public:
	CSclCheckSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSclCheckSetDlg();

	CString m_strTitle;
	long m_cxMIn, m_cyMin;
	CMFCTabCtrl m_tabPara;

	CSclCheckCtrlDlg m_schemaDlg;
	CSclCheckCtrlDlg m_DLT860ModelDlg;
	CSclCheckCtrlDlg m_ProjAppModelDlg;
	CSclCheckCtrlDlg m_virLoopDlg;

// 对话框数据
	enum { IDD = IDD_SCLCHECKSETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
