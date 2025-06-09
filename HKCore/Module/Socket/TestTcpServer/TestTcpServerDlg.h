
// TestTcpServerDlg.h : ͷ�ļ�
//

#pragma once

#include "..\WinTcpSocketServer.h"

class CXTestTcpSocketServer : public CWinTcpSocketServer
{
public:
	CXTestTcpSocketServer();
	virtual ~CXTestTcpSocketServer();

	CWinTcpSocketClient *m_pCurrTcpSocket;

public:
	virtual CWinTcpSocketClient* CreateNewSocketClient();

};

// CTestTcpServerDlg �Ի���
class CTestTcpServerDlg : public CDialog
{
// ����
public:
	CTestTcpServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTTCPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CXTestTcpSocketServer m_oWinTcpSocketServer;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreateServer();
	afx_msg void OnBnClickedBtnCloseServer();
};
