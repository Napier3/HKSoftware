#include "QSttProgDlg.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/XLangResource_Native.h"

QSttProgDlg::QSttProgDlg(QWidget *parent)
	: QDialog(parent)
{
//	setWindowIcon (QPixmap( ":/images/Sys.png"));
//	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(tr(""));
	m_pCurrProgressBar = NULL;
	m_pMsgLabel = NULL;
	m_nCurrProgValue = 0;
}

QSttProgDlg::~QSttProgDlg()
{

}

void QSttProgDlg::initUI(const CString &strTitle,const CString &strText)
{
	ReleaseUI();
	resize(400, 60);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

	setWindowTitle(strTitle);
//	m_pAllVLayout = new QVBoxLayout(this);
	m_pVBoxLayout1 = new QGridLayout(this);
	m_pMsgLabel = new QLabel(this);
	m_pMsgLabel->setText(strText);
	m_pCurrProgressBar = new QProgressBar(this);
	m_pVBoxLayout1->addWidget(m_pCurrProgressBar);
	m_pVBoxLayout1->addWidget(m_pMsgLabel);
//	m_pAllVLayout->addLayout(m_pVBoxLayout1);

	InitDatas();
	setLayout(m_pVBoxLayout1);
	connect(&m_oTimer,SIGNAL(timeout()),this,SLOT(slot_Timer()));
}

void QSttProgDlg::SetText(const CString &strMsgText,const CString &strTitle)
{
	m_pMsgLabel->setText(strMsgText);

	if (!strTitle.IsEmpty())
	{
		setWindowTitle(strTitle);
	}
}

void QSttProgDlg::ReleaseUI()
{

}

void QSttProgDlg::InitDatas()
{
}

void QSttProgDlg::Start(int nMinValue,int nMaxValue,int nCurrValue)
{
	m_pCurrProgressBar->setMinimum(nMinValue);
	m_pCurrProgressBar->setMaximum(nMaxValue);
	m_nCurrProgValue = nCurrValue;
	m_pCurrProgressBar->setValue(m_nCurrProgValue);
	m_oTimer.start(500);
	show();
}

void QSttProgDlg::Stop()
{
	m_oTimer.stop();
	hide();
}

void QSttProgDlg::slot_Timer()
{
	if (!isHidden())
	{
		m_nCurrProgValue++;
		m_pCurrProgressBar->setValue(m_nCurrProgValue%100);
		CString strMsg;
		float fTime = m_nCurrProgValue;
		fTime /= 2;
		//strMsg = _T("请稍后,已开始");
		strMsg = g_sLangTxt_Gradient_Pleaselaterithasstarted;
		strMsg.AppendFormat(_T("%.01fs..."),fTime);
//		strMsg += _T("请稍后....");
		m_pMsgLabel->setText(strMsg);
	}
}