#include "SttIecChsEditDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../SttTestCntrFrameBase.h"


QSttIecChsEditDialog::QSttIecChsEditDialog(int nChsType,QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_nChsType = nChsType;
	InitUI();
}

QSttIecChsEditDialog::~QSttIecChsEditDialog()
{
}

void QSttIecChsEditDialog::InitUI()
{
#ifndef _PSX_QT_LINUX_
	QRect rcScreen = QApplication::desktop()->availableGeometry();
	resize(rcScreen.width(), rcScreen.height());
	this->setFixedWidth(rcScreen.width());
	this->setFixedHeight(rcScreen.height());
#else
	resize(g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth,g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight);
	this->setFixedWidth(g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth);
	this->setFixedHeight(g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight);
#endif
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
// 	resize(650,500);
// 	this->setFixedWidth(650);
// 	this->setFixedHeight(500);

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_ChEdit");
	setWindowTitle(strTemp);
//	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	m_pIecChsEditWidget = new QSttIecChsEditWidget(m_nChsType,this);
	m_pIecChsEditWidget->m_pOK_PushButton->setVisible(true);
	QVBoxLayout *pMain_VLayout = new QVBoxLayout(this);
	pMain_VLayout->addWidget(m_pIecChsEditWidget);
	setLayout(pMain_VLayout);
	connect(m_pIecChsEditWidget->m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
//	m_pIecChsEditWidget->resize(this->width(), this->height());

}

void QSttIecChsEditDialog::InitData(CIecCfgChsBase *pIecCfgChs)
{
	m_pIecChsEditWidget->InitData(pIecCfgChs);
}

void QSttIecChsEditDialog::slot_OKClicked()
{
	close();
}
