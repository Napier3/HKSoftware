#pragma once
#include "afxwin.h"

// CWaitingTimeDlg �Ի���

class CWaitingTimeDlg : public CDialog// , public CThreadProgressInterface
{
	DECLARE_DYNAMIC(CWaitingTimeDlg)

public:
	CWaitingTimeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWaitingTimeDlg();

    static bool g_bOver;
	long nRecTime;

	CString m_strMsgDesc;

// �Ի�������
	enum { IDD = IDD_DIALOG_DATAPROG };
public:
	CString m_strText;
	CFont *m_Font;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_staText;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	void ChgStaticText(CStatic *cTxt, const CString sContect);

};
