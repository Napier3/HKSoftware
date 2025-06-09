#pragma once
#include "SclCheckSettingDlgGrid.h"
#include "..\..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include "afxcmn.h"

#include "SclCheckCtrlDlg.h"

// CSclCheckSetDlg �Ի���

class CSclCheckSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclCheckSetDlg)

public:
	CSclCheckSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSclCheckSetDlg();

	CString m_strTitle;
	long m_cxMIn, m_cyMin;
	CMFCTabCtrl m_tabPara;

	CSclCheckCtrlDlg m_schemaDlg;
	CSclCheckCtrlDlg m_DLT860ModelDlg;
	CSclCheckCtrlDlg m_ProjAppModelDlg;
	CSclCheckCtrlDlg m_virLoopDlg;

// �Ի�������
	enum { IDD = IDD_SCLCHECKSETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
