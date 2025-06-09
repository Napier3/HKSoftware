#include "QScdFileRWDlg.h"

CScdFileRWDlg::CScdFileRWDlg(QWidget* pParent /*=NULL*/)
: QProgressDialog(pParent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

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
	
	connect(this, SIGNAL(sig_SetTitle(const CString&)), this, SLOT(slot_SetTitle(const CString&)), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_SetMaxRange(long)), this, SLOT(slot_SetMaxRange(long)), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_ResetProcess()), this, SLOT(slot_ResetProcess()), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_StepIt()), this, SLOT(slot_StepIt()), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_ShowMsg(const CString&)), this, SLOT(slot_ShowMsg(const CString&)), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_StartTimer(long)), this, SLOT(slot_StartTimer(long)), Qt::QueuedConnection);
	connect(this, SIGNAL(sig_InitThreadProgress(long, long)), this, SLOT(slot_InitThreadProgress(long, long)), Qt::QueuedConnection);
}

CScdFileRWDlg::~CScdFileRWDlg()
{

}


void CScdFileRWDlg::SetTitle(const CString &strTitle)
{
	emit sig_SetTitle(strTitle);
	//setWindowTitle(strTitle);
}

void  CScdFileRWDlg::SetMaxRange(long nMaxRange)
{
	emit sig_SetMaxRange(nMaxRange);
	//setRange(0,nMaxRange);
}

void  CScdFileRWDlg::ResetProcess()
{
//	m_prgsScdFileRead.SetPos(0);
}

void  CScdFileRWDlg::StepIt()
{
	emit sig_StepIt();
/*
 	m_nOneStepIndex++;
 	long nValue = m_nOneStepIndex*m_nOneStepCount;
 
 	if(nValue > m_nMaxRange)
 	{
 		m_nOneStepIndex = 0;
 		nValue = m_nOneStepIndex*m_nOneStepCount;
 	}
 
 	setValue(nValue);
*/


//	m_prgsScdFileRead.StepIt();
}

void  CScdFileRWDlg::ShowMsg(const CString &strMsg)
{
	emit sig_ShowMsg(strMsg);
	//setLabelText(strMsg);
}

void CScdFileRWDlg::StartTimer(long nTimerLong)
{
}

void CScdFileRWDlg::InitThreadProgress(long nMaxRange, long nOneStepCount)
{
	emit sig_InitThreadProgress(nMaxRange, nOneStepCount);
/*
	m_nOneStepIndex = 0;
	CThreadProgressInterface::InitThreadProgress(nMaxRange,nOneStepCount);
	setModal(true);
	show();
*/
}
///////////////////slots///////////////////////////////
void CScdFileRWDlg::slot_SetTitle(const CString &strTitle)
{
	setWindowTitle(strTitle);
}

void CScdFileRWDlg::slot_SetMaxRange(long nMaxRange)
{
	setRange(0,nMaxRange);
}

void CScdFileRWDlg::slot_ResetProcess()
{

}

void CScdFileRWDlg::slot_StepIt()
{
	m_nOneStepIndex++;
	long nValue = m_nOneStepIndex*m_nOneStepCount;

	if(nValue > m_nMaxRange)
	{
		m_nOneStepIndex = 0;
		nValue = m_nOneStepIndex*m_nOneStepCount;
	}

	setValue(nValue);
}

void CScdFileRWDlg::slot_ShowMsg(const CString &strMsg)
{
	setLabelText(strMsg);
}

void CScdFileRWDlg::slot_StartTimer(long nTimerLong)
{

}

void CScdFileRWDlg::slot_InitThreadProgress(long nMaxRange, long nOneStepCount)
{
	m_nOneStepIndex = 0;
	m_nMaxRange = nMaxRange;
	m_nOneStepCount = nOneStepCount;
	setRange(0,nMaxRange);
	setModal(true);
	show();
}