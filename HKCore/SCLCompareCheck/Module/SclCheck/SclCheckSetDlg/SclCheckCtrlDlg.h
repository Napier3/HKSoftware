#pragma once

#include "SclCheckSettingDlgGrid.h"

#define SCLCHECK_VIEW_CHOOSEALL           0X0891000
#define SCLCHECK_VIEW_CHOOSENULL          0X0891001
#define SCLCHECK_VIEW_CHOOSEINVERT        0X0891002



class CSclCheckCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclCheckCtrlDlg)

public:
	CSclCheckCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSclCheckCtrlDlg();

	long m_cxMIn, m_cyMin;
	void ShowGridDatas(CExBaseList *pDatas );

	CSclCheckSettingDlgGrid m_oSclCheckSettingDlgGrid;
	CExBaseList *m_pCheckObjectsData;

// 对话框数据
	enum { IDD = IDD_CTRLDLG_SCLCHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnChooseAllItems();
	afx_msg void OnChooseNullItems();
	afx_msg void OnChooseInvertItems();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
