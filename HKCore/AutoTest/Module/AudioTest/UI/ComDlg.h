#pragma once
#include "afxwin.h"
#include "ListBoxLog.h"
#include "AudioButton.h"
#include "../../../AudioTest/resource.h"
#include "../../../Module/WndGroupMngr/XUIAutoAdjTool.h"

// CComDlg �Ի���

class CComDlg : public CDialog, CXUIAdjItem_Area
{
	DECLARE_DYNAMIC(CComDlg)

public:
	CListBoxLog		m_ctrlLogListBox;
	CAudioButton	m_btnServer;
	CAudioButton	m_btnListener;
	CAudioButton	m_btnListen;
	CStatic			m_txtListener;
	CStatic			m_txtServer;

	bool m_bListen;
	bool m_bTestFlag;

	CComDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CComDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMM };
	virtual BOOL OnInitDialog();
	virtual void XUI_InitAdjust();
	BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void UpdateState(int nFlag = false);
	void InitLogListBox(int nFlag,CString strPath);

	void SetBtnSize(bool bFlag);
	void SetBtnState(int nTestState);
	 


protected:
	BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnStart();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonReturn();
	afx_msg void OnBnClickedButtonTestStop();
	afx_msg void OnBnClickedButtonTestGo();
	afx_msg void OnBnClickedButtonTestClose();
};
