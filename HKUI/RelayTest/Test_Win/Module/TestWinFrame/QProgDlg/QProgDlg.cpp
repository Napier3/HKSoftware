#include "QProgDlg.h"

QProgDlg::QProgDlg(QWidget *parent)
	: QDialog(parent)
{
//	setWindowIcon (QPixmap( ":/images/Sys.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(tr(""));
	m_pCurrProgressBar = NULL;
	m_nCurrProgValue = 0;
	m_nProgDlgType = 0;
}

QProgDlg::~QProgDlg()
{

}

void QProgDlg::initUI()
{
	ReleaseUI();
	resize(400, 60);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pAllVLayout = new QVBoxLayout(this);
	m_pVBoxLayout1 = new QGridLayout(this);
	m_pCurrProgressBar = new QProgressBar(this);
	m_pVBoxLayout1->addWidget(m_pCurrProgressBar);
	m_pAllVLayout->addLayout(m_pVBoxLayout1);

	InitDatas();
	this->setLayout(m_pAllVLayout);
	connect(&m_oTimer,SIGNAL(timeout()),this,SLOT(slot_Timer()));
}

void QProgDlg::ReleaseUI()
{

}

void QProgDlg::InitDatas()
{
}

void QProgDlg::Start()
{

	if(m_nProgDlgType == REPLAYTESTDOWNLOADDATA)
	{
		m_pCurrProgressBar->setMinimum(0);
		m_pCurrProgressBar->setMaximum(0);

		this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);

	}
	else if(m_nProgDlgType == REPLAYTESTOPENFILE)
	{
		m_pCurrProgressBar->setMinimum(0);
		m_pCurrProgressBar->setMaximum(100);
		m_nCurrProgValue = 0;
		m_pCurrProgressBar->setValue(m_nCurrProgValue);
		m_oTimer.start(200);

	}

	else
	{
	m_pCurrProgressBar->setMinimum(0);
	m_pCurrProgressBar->setMaximum(20);
	m_nCurrProgValue = 0;
	m_pCurrProgressBar->setValue(m_nCurrProgValue);
	m_oTimer.start(200);
	 
	}
	
}

void QProgDlg::Stop()
{
	m_oTimer.stop();
	hide();
}

void QProgDlg::slot_Timer()
{
	if (!isHidden())
	{
		m_nCurrProgValue++;

		if(m_nProgDlgType == REPLAYTESTOPENFILE)
		{
			if (m_nCurrProgValue>100)
			{
				m_nCurrProgValue = 0;
			}
		}
		else if(m_nProgDlgType == TYPICALMODULE)
		{
		if (m_nCurrProgValue>20)
		{
			m_nCurrProgValue = 0;
		}
		}


		m_pCurrProgressBar->setValue(m_nCurrProgValue);
		m_pCurrProgressBar->update();
	}
	}

void QProgDlg::SetProgDlgType( int nType /*= TYPICALMODULE*/ )
{
	m_nProgDlgType = nType;
}