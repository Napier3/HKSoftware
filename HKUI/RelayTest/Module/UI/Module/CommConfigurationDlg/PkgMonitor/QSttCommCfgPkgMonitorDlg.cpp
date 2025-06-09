#include "QSttCommCfgPkgMonitorDlg.h"
#include "../../../SttTestCntrFrameBase.h"
extern CFont *g_pSttGlobalFont;

QSttCommCfgPkgMonitorDlg::QSttCommCfgPkgMonitorDlg(QSttCommCfgPkgMonitorWidget *pSttCommCfgPkgMonitorWidget,QWidget *parent)
	: QDialog(parent)
{

	m_pQSttCommCfgPkgMonitorWidget = pSttCommCfgPkgMonitorWidget;
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("报文监听"));
	resize(800, 630);
	InitUI();
}


QSttCommCfgPkgMonitorDlg::~QSttCommCfgPkgMonitorDlg()
{

}

void QSttCommCfgPkgMonitorDlg::InitUI()
{
	m_pMainLayout = new QVBoxLayout(this);

	if (m_pQSttCommCfgPkgMonitorWidget == NULL)
	{
		m_pQSttCommCfgPkgMonitorWidget = new QSttCommCfgPkgMonitorWidget;
	}
	else
	{
		m_pQSttCommCfgPkgMonitorWidget->show();
	}

	m_pMainLayout->addWidget(m_pQSttCommCfgPkgMonitorWidget);

	//verticalLayout_2
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);
	//strText = _T("取消");
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel);
	QHBoxLayout *m_pOkCancel_HBoxLayout = new QHBoxLayout(this);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pMainLayout->addLayout(m_pOkCancel_HBoxLayout);

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	SetDialogFont();
	setLayout(m_pMainLayout);
}

void QSttCommCfgPkgMonitorDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}

	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}

void QSttCommCfgPkgMonitorDlg::slot_OKClicked()
{
	m_pMainLayout->removeWidget(m_pQSttCommCfgPkgMonitorWidget);
	m_pQSttCommCfgPkgMonitorWidget->hide();
	m_pQSttCommCfgPkgMonitorWidget->setParent(g_theTestCntrFrame);
	close();
}

void QSttCommCfgPkgMonitorDlg::slot_CancelClicked()
{
	m_pMainLayout->removeWidget(m_pQSttCommCfgPkgMonitorWidget);
	m_pQSttCommCfgPkgMonitorWidget->hide();
	m_pQSttCommCfgPkgMonitorWidget->setParent(g_theTestCntrFrame);
	close();
}


