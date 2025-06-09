#pragma once
#include "afxcmn.h"
#include "AudioButton.h"
#include "../../../AudioTest/resource.h"
#include "../../../AudioTest/AudioTest.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"
// CMainDlg 对话框

class CMainDlg : public CDialog, CXUIAdjItem_Area
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAIN };
	virtual BOOL OnInitDialog();
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX); 


	DECLARE_MESSAGE_MAP()
	BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnBnClickedBtnNewtest();
	afx_msg void OnBnClickedBtnQuitsystem();
	afx_msg void OnBnClickedBtnSetSystem();
	//afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
public:
	CFont m_font;
	CStatic m_static;
	CAudioButton m_btnNewTest;
	CAudioButton m_btnTestRecord;
	CAudioButton m_btnSystem;
	CAudioButton m_btnQuit;
};