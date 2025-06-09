#include "QScdFileRWDlg.h"

CScdFileRWDlg::CScdFileRWDlg(QWidget* pParent /*=NULL*/)
: QProgressDialog(pParent)
{
	resize(0,0);
	setFont(QFont(QObject::tr("Arial"),10,4));

	if (pParent != NULL)
	{
		QRect rc = pParent->topLevelWidget()->geometry();
		setGeometry(rc.left() + pParent->width()/2-150, rc.top() + pParent->height()/2 -50, 300, 100);
	} 
	else
	{
		resize(300,100);
	}
	
}

CScdFileRWDlg::~CScdFileRWDlg()
{

}


void CScdFileRWDlg::SetTitle(const CString &strTitle)
{
	setWindowTitle(strTitle);
}

void  CScdFileRWDlg::SetMaxRange(long nMaxRange)
{
	setRange(0,nMaxRange);
}

void  CScdFileRWDlg::ResetProcess()
{
//	m_prgsScdFileRead.SetPos(0);
}

void  CScdFileRWDlg::StepIt()
{
	m_nOneStepIndex++;
	long nValue = m_nOneStepIndex*m_nOneStepCount;

	if(nValue > m_nMaxRange)
	{
		m_nOneStepIndex = 0;
		nValue = m_nOneStepIndex*m_nOneStepCount;
	}

	setValue(nValue);
//	m_prgsScdFileRead.StepIt();
}

void  CScdFileRWDlg::ShowMsg(const CString &strMsg)
{
	setLabelText(strMsg);
}

void CScdFileRWDlg::StartTimer(long nTimerLong)
{
}

void CScdFileRWDlg::InitThreadProgress(long nMaxRange, long nOneStepCount)
{
	m_nOneStepIndex = 0;
	CThreadProgressInterface::InitThreadProgress(nMaxRange,nOneStepCount);
	setModal(true);
	show();
}

// BOOL CScdFileRWDlg::OnInitDialog()
//{
// 	CDynDialogEx::OnInitDialog();
// 	
// 
// 	CreateStatic(m_stcTime,  _T("0 s"), CRect(460,13,500,35), SCDFILE_RW_TIME, this);
// 	CreateProgressCtrl(m_prgsScdFileRead,CRect(13,13,450,35), SCDFILE_RW_PROGCTRL, this);	
// 
// 	CFont *pFont = g_pGlobalFont;
// 	m_stcTime.SetFont(pFont);
// 	m_prgsScdFileRead.SetFont(pFont);
// 	m_bHasInitDialog = TRUE;
// 
// 	CenterWindow();
// 	m_nTimeCout = 0;
// 	m_prgsScdFileRead.SetRange32(1,100);
// 	m_prgsScdFileRead.SetStep(1);
// 	SetTimer(1, 1000, NULL);
// 	SetWindowText(_T(""));
// 	return TRUE;  // return TRUE unless you set the focus to a control
// 	// 异常: OCX 属性页应返回 FALSE
// }

//void CScdFileRWDlg::OnCancel()
//{
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnCancel();
//}

// void CScdFileRWDlg::OnOK()
// {
	// TODO: 在此添加专用代码和/或调用基类

	//__super::OnOK();
//}