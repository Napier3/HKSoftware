#include "QSttCommCfgDeviceDlg.h"
#include <QMessageBox>
//d:\WorkLiJQ\Source\Module\OSInterface\QT\CString_QT.h
#include "../../../../../../Module/OSInterface/QT/CString_QT.h"
#include "../CommCfg/QSttCommCfgMainDlg.h"
#include "QSttCommCfgDeviceWidget.h"
#include "../../../SttTestCntrFrameBase.h"

extern CFont *g_pSttGlobalFont;

QSttCommCfgDeviceDlg::QSttCommCfgDeviceDlg(QPpSttIotEngineClientWidget *pSttCommCfgDeviceWidget,QWidget *parent) :
    QDialog(parent)
{
	m_pSttCommCfgDeviceWidget = pSttCommCfgDeviceWidget;
	setWindowTitle(CString("装置通讯"));
	resize(900, 630);
//	this->pParentDlg = (QSttCommCfgDeviceWidget*)parent;
	InitUI();
}

QSttCommCfgDeviceDlg::~QSttCommCfgDeviceDlg()
{

}


void QSttCommCfgDeviceDlg::InitUI()
{
	m_pMainLayout = new QVBoxLayout(this);

	if (m_pSttCommCfgDeviceWidget == NULL)
	{
		m_pSttCommCfgDeviceWidget = new QSttCommCfgDeviceWidget;
	}
	else
	{
		m_pSttCommCfgDeviceWidget->show();
	}

	m_pMainLayout->addWidget(m_pSttCommCfgDeviceWidget);

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

void QSttCommCfgDeviceDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}

	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);

}



void QSttCommCfgDeviceDlg::slot_OKClicked()
{
	m_pMainLayout->removeWidget(m_pSttCommCfgDeviceWidget);
	m_pSttCommCfgDeviceWidget->hide();
	m_pSttCommCfgDeviceWidget->setParent(g_theTestCntrFrame);
	close();
}

void QSttCommCfgDeviceDlg::slot_CancelClicked()
{
	m_pMainLayout->removeWidget(m_pSttCommCfgDeviceWidget);
	m_pSttCommCfgDeviceWidget->hide();
	m_pSttCommCfgDeviceWidget->setParent(g_theTestCntrFrame);
	close();
}

