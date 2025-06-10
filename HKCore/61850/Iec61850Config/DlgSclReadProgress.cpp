// DlgSclReadProgress.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "DlgSclReadProgress.h"


// CDlgSclReadProgress �Ի���

void CDlgSclReadProgress::SetTitle(const CString &strTitle)
{

}

void CDlgSclReadProgress::SetMaxRange(long nMaxRange)
{
	m_prgsSclRead.SetRange32(0, nMaxRange);
}

void CDlgSclReadProgress::ResetProcess()
{
	m_prgsSclRead.SetPos(0);
}

void CDlgSclReadProgress::StepIt()
{
	m_prgsSclRead.StepIt();
}

void CDlgSclReadProgress::ShowMsg(const CString &strMsg)
{
	SetWindowText(strMsg);
}

void CDlgSclReadProgress::StartTimer(long nTimerLong)
{

}

IMPLEMENT_DYNAMIC(CDlgSclReadProgress, CDialog)

CDlgSclReadProgress::CDlgSclReadProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSclReadProgress::IDD, pParent)
{

}

CDlgSclReadProgress::~CDlgSclReadProgress()
{
}

void CDlgSclReadProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_READ, m_prgsSclRead);
	DDX_Control(pDX, IDC_STATIC_TIME, m_stcTime);
}


BEGIN_MESSAGE_MAP(CDlgSclReadProgress, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgSclReadProgress ��Ϣ�������

void CDlgSclReadProgress::OnTimer(UINT_PTR nIDEvent)
{
	//m_prgsSclRead.StepIt();
	m_nTimeCout += 1000;
	CString strTitle;
	strTitle.Format(_T("%d ms"), m_nTimeCout);
	m_stcTime.SetWindowText(strTitle);

	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgSclReadProgress::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();
	m_nTimeCout = 0;
	m_prgsSclRead.SetRange32(1, 20);
	m_prgsSclRead.SetStep(1);
	SetTimer(1, 1000, NULL);
	xlang_InitAndAdjust(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSclReadProgress::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//__super::OnCancel();
}

void CDlgSclReadProgress::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//__super::OnOK();
}
void CDlgSclReadProgress::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}
	xlang_InitByLgugStr(CXLanguageResourceIec_61850Cfg::g_sLangID_SclReading, this);
}

