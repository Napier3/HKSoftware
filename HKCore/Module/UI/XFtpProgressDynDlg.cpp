#include "stdafx.h"
#include "XFtpProgressDynDlg.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

#define XFTP_PROGRESS_MAX 100

// CXFtpProgressDynDlg 对话框

//IMPLEMENT_DYNAMIC(CXFtpProgressDynDlg, CDialog)

CXFtpProgressDynDlg::CXFtpProgressDynDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CXFtpProgressDynDlg::IDD, pParent)
: CDynDialogEx(pParent)
{

}

CXFtpProgressDynDlg::~CXFtpProgressDynDlg()
{
}

void CXFtpProgressDynDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CXFtpProgressDynDlg, CDynDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CXFtpProgressDynDlg 消息处理程序

BOOL CXFtpProgressDynDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateProgressCtrl(m_prgsSttXftp, CRect(10,10,500,35), X_PROGRESS_FTP, this);
	CreateEdit(m_edtProgress, CRect(505,10,580,35), X_EDIT_PROGRESS, this,EXSTYLE_EDIT, (WS_VISIBLE | WS_CHILD | WS_TABSTOP | SS_CENTER | ES_AUTOHSCROLL));
	CreateEdit(m_edtFileList, CRect(10,40,580,200), X_EDIT_FILELIST, this,EXSTYLE_EDIT, STYLE_MULTIEDIT);

	m_edtProgress.SetFont(g_pGlobalFont11);
	m_edtProgress.SetFont(g_pGlobalFont11);

	MoveWindow(CRect( 0, 0, 590, 250), TRUE);

	return TRUE;
}

void CXFtpProgressDynDlg::OnClose()
{//配置未完成结束
	ShowWindow(FALSE);
//	CDynDialogEx::OnClose();
}

void CXFtpProgressDynDlg::TransferStart(const CString &strFile, long nTotalSize)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Start:%s"), strFile);
	long nMax = CalStep(nTotalSize);
	m_prgsSttXftp.SetRange32(1, nMax);
	m_prgsSttXftp.SetPos(1);
	m_prgsSttXftp.SetStep(1);

	CenterWindow();
	SetWindowTopMost(TRUE);
}

void CXFtpProgressDynDlg::TransferStep(long nCurrSendSize)
{
	long nStep = CalStep(nCurrSendSize);
	m_prgsSttXftp.SetPos(nStep);
}

void CXFtpProgressDynDlg::TransferFinish(const CString &strFile)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferFinish:%s"), strFile);

	m_nPos++;
	UpdateEditProgress();

	if (m_nPos == m_nMaxRange)
	{
		SetWindowText(_T("文件传输完成"));
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("文件传输完成"));
		ShowWindow(SW_HIDE);
	}
}

void CXFtpProgressDynDlg::TransferError(const CString &strFile,long nErrNo)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TransferError：%s"), strFile);
	SetWindowText(_T("文件传输失败"));
}

void CXFtpProgressDynDlg::Init(CStringArray &strArray)
{
	CString tmpStr = _T("传输文件列表：\r\n");
	m_nPos = 0;
	m_nMaxRange = strArray.GetSize();

	for (int i=0; i < m_nMaxRange; i++)
	{
		tmpStr.AppendFormat(_T("%s"),strArray[i]);

		if (i < m_nMaxRange-1)
		{
			tmpStr.Append(_T("\r\n"));
		}
	}

	SetWindowText(_T("文件正在传输中……"));
	m_edtFileList.SetWindowText(tmpStr);
	UpdateEditProgress();

	CenterWindow();
	SetWindowTopMost(TRUE);
}

void CXFtpProgressDynDlg::UpdateEditProgress()
{
	CString tmpStr = _T("");

	tmpStr.Format(_T("%d/%d"),m_nPos,m_nMaxRange);
	m_edtProgress.SetWindowText(tmpStr);
}

void CXFtpProgressDynDlg::SetWindowTopMost(BOOL bTopMost)
{
	CRect rtClient;
	GetWindowRect(rtClient); 

	if (bTopMost)
	{
		::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW); 
	}
	else
	{
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW); 
	}
}