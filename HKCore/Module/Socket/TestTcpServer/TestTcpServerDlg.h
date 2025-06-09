
// TestTcpServerDlg.h : 头文件
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

// CTestTcpServerDlg 对话框
class CTestTcpServerDlg : public CDialog
{
// 构造
public:
	CTestTcpServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTTCPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CXTestTcpSocketServer m_oWinTcpSocketServer;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreateServer();
	afx_msg void OnBnClickedBtnCloseServer();
};
