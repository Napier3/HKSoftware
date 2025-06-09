#include "QPasswordDlg.h"
#include <QDirIterator>
#include "../../../../../Module/Log/LogPrint.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
QPasswordDlg::QPasswordDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon (QPixmap( ":/images/Sys.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("通道映射密码")*/g_sLangTxt_Native_MapPass);
	m_bIsCorrected = false;
}

QPasswordDlg::~QPasswordDlg()
{

}

void QPasswordDlg::initUI()
{
	ReleaseUI();
	resize(200, 100);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	m_pPasswordGroupBox = new QGroupBox(this);
	m_pPasswordGroupBox->setTitle(tr(""));
	m_pVBoxLayout1 = new QGridLayout(m_pPasswordGroupBox);
	m_pModelLabel = new QLabel(m_pPasswordGroupBox);
	m_pModelLabel->setText(/*tr("密码:")*/g_sLangTxt_Native_Pass);
	m_pVBoxLayout1->addWidget(m_pModelLabel,0,0,1,1);

	m_pPasswordLineEdit = new QLineEdit(m_pPasswordGroupBox);
	m_pPasswordLineEdit->setEchoMode(QLineEdit::Password);

	sizePolicy.setHeightForWidth(m_pPasswordLineEdit->sizePolicy().hasHeightForWidth());
	m_pPasswordLineEdit->setSizePolicy(sizePolicy);

	m_pVBoxLayout1->addWidget(m_pPasswordLineEdit,0,1,1,1);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));

	m_pHBoxLayout2 = new QHBoxLayout(this);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->addWidget(m_pOK_PushButton);
	m_pHBoxLayout2->addSpacing(5);
	m_pHBoxLayout2->addWidget(m_pCancel_PushButton);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addWidget(m_pPasswordGroupBox);
	m_pAllVLayout->addLayout(m_pHBoxLayout2);
	InitDatas();
	this->setLayout(m_pAllVLayout);

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QPasswordDlg::ReleaseUI()
{

}

void QPasswordDlg::InitDatas()
{
}

void QPasswordDlg::slot_OKClicked()
{
	QString strValue = m_pPasswordLineEdit->text();

	if (strValue == "ponovo")//密码
	{
		m_bIsCorrected = true;
		close();
	}
	else
	{
		m_bIsCorrected = false;

		if (strValue.isEmpty())
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("密码为空,请重新输入.")*/g_sLangTxt_Native_EmptyPass.GetString());
		} 
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("密码错误,请重新输入.")*/g_sLangTxt_Native_WrongPass.GetString());
		}

		m_pPasswordLineEdit->setText("");
		m_pPasswordLineEdit->setFocus(Qt::MouseFocusReason);
	}
}

void QPasswordDlg::slot_CancelClicked()
{
	close();
}