#include "RemoteCtrlDlg.h"
#include "../SttTestCntrFrameBase.h"
extern QFont *g_pSttGlobalFont;

QRemoteCtrlDlg::QRemoteCtrlDlg(QSttMacroParaEditViewRemoteCtrl *pSttMacroParaEditViewRemoteCtrl,QWidget *parent)
	: QDialog(parent)
{

	m_pSttMacroParaEditViewRemoteCtrl = pSttMacroParaEditViewRemoteCtrl;
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	setWindowTitle(_T("Ò£¿Ø"));
	resize(1000, 800);
	setFixedSize(1000, 800);
	
	InitUI();
}


QRemoteCtrlDlg::~QRemoteCtrlDlg()
{

}

void QRemoteCtrlDlg::InitUI()
{
	m_pMainLayout = new QVBoxLayout(this);

	if (m_pSttMacroParaEditViewRemoteCtrl == NULL)
	{
		m_pSttMacroParaEditViewRemoteCtrl = new QSttMacroParaEditViewRemoteCtrl;
	}
	else
	{
		m_pSttMacroParaEditViewRemoteCtrl->show();
	}

	m_pMainLayout->addWidget(m_pSttMacroParaEditViewRemoteCtrl);

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);
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

void QRemoteCtrlDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}

	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
}

void QRemoteCtrlDlg::slot_OKClicked()
{
	m_pMainLayout->removeWidget(m_pSttMacroParaEditViewRemoteCtrl);
	m_pSttMacroParaEditViewRemoteCtrl->hide();
	m_pSttMacroParaEditViewRemoteCtrl->setParent(g_theTestCntrFrame);
	close();
}

void QRemoteCtrlDlg::slot_CancelClicked()
{
	m_pMainLayout->removeWidget(m_pSttMacroParaEditViewRemoteCtrl);
	m_pSttMacroParaEditViewRemoteCtrl->hide();
	m_pSttMacroParaEditViewRemoteCtrl->setParent(g_theTestCntrFrame);
	close();
}


