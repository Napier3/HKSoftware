// D:\WorkOld\Source\AutoTest\Module\WzdDlgApi\StepDlg\ThreadPrgsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "ThreadPrgsDlg.h"


// CThreadPrgsDlg �Ի���

IMPLEMENT_DYNAMIC(CThreadPrgsDlg, CDialog)

CThreadPrgsDlg::CThreadPrgsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadPrgsDlg::IDD, pParent)
{

}

CThreadPrgsDlg::~CThreadPrgsDlg()
{
}

void CThreadPrgsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_wndPrgs);
	DDX_Control(pDX, IDC_EDIT_INFOR, m_wndInfor);
}


BEGIN_MESSAGE_MAP(CThreadPrgsDlg, CDialog)
END_MESSAGE_MAP()


// CThreadPrgsDlg ��Ϣ�������

void CThreadPrgsDlg::OnOK()
{

}

void CThreadPrgsDlg::OnCancel()
{

}

void CThreadPrgsDlg::SetTitle(const CString &strTitle)
{
	SetWindowText(strTitle);
	CRect rc;
	GetWindowRect(&rc);
	SetWindowPos(&wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW   );
}

void CThreadPrgsDlg::SetMaxRange(long nMaxRange)
{
	m_wndPrgs.SetRange32(0, nMaxRange);
	m_wndPrgs.SetStep(1);
}

void CThreadPrgsDlg::ResetProcess()
{
	m_wndPrgs.SetPos(0);
}

void CThreadPrgsDlg::StepIt()
{
	m_wndPrgs.StepIt();
}

void CThreadPrgsDlg::ShowMsg(const CString &strMsg) 
{
	m_wndInfor.SetWindowText(strMsg);

	//���߳�����ʱһ��㣬����Ϣ��ʾ�����ʾ���
	Sleep(1);
}

void CThreadPrgsDlg::StartTimer(long nTimerLong)
{

}


void CThreadPrgsDlg::Finish(DWORD dwParam)
{
	ShowWindow(SW_HIDE);
}

void CThreadPrgsDlg::StepPos(long nPos)
{

}

void CThreadPrgsDlg::Exit()
{

}

