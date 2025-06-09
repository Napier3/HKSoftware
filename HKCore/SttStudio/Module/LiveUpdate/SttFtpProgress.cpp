// SttFtpProgress.cpp : 实现文件
//

#include "stdafx.h"
#include "SttFtpProgress.h"

// CSttFtpProgress 对话框

//IMPLEMENT_DYNAMIC(CSttFtpProgress, CDialog)

CSttFtpProgress::CSttFtpProgress(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_bHasInitDialog = FALSE;
}

CSttFtpProgress::~CSttFtpProgress()
{
}

void CSttFtpProgress::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
	if (!m_bHasInitDialog)
	{
		return;
	}

	DDX_Control(pDX, XFIDC_CTRL_PROGRESS, m_prgsSttXftp);
}

BEGIN_MESSAGE_MAP(CSttFtpProgress, CDynDialogEx)
END_MESSAGE_MAP()

// CSttFtpProgress 消息处理程序

BOOL CSttFtpProgress::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	SetWindowText(_T("正在执行文件传输......"));
	CreateProgressCtrl(m_prgsSttXftp, CRect(10,10,450,40), XFIDC_CTRL_PROGRESS, this);

    MoveWindow(CRect( 0, 0, 470, 100), TRUE);
	CenterWindow();

	m_bHasInitDialog = TRUE;

	return TRUE;
}

void CSttFtpProgress::TransferStart(const CString &strFile, long nTotalSize)
{
	long nMax = CalStep(nTotalSize);
	m_prgsSttXftp.SetRange32(1, nMax);
	m_prgsSttXftp.SetPos(1);
	m_prgsSttXftp.SetStep(1);
}

void CSttFtpProgress::TransferStep(long nCurrSendSize)
{
	long nStep = CalStep(nCurrSendSize);
	m_prgsSttXftp.SetPos(nStep);
}

void CSttFtpProgress::TransferFinish(const CString &strFile)
{
	
}

void CSttFtpProgress::TransferError(const CString &strFile,long nErrNo)
{
	
}