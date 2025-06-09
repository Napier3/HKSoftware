#include "SttAuxModifyIPDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../../Module/Log/LogPrint.h"
#include "../../Module/XLangResource_Native.h"
#include "../../SttTestCntrFrameBase.h"

QAuxModifyIPDlg::QAuxModifyIPDlg(QWidget *pParent)
	:QDialog(pParent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); 
	setWindowTitle(g_sLangTxt_IPaddress);
	initUI(); 
	initSignalSlots();
}

QAuxModifyIPDlg::~QAuxModifyIPDlg()
{

}

void QAuxModifyIPDlg::initUI()
{	
	CString strTemp;
	QLabel *pIpLabel = new QLabel(this);
	strTemp = _T("IPµØÖ·:");
	pIpLabel->setText(strTemp);
	m_pedtIP = new QLineEdit(this);
	strTemp = _T("×ÓÍøÑÚÂë:");
	QLabel *plbSubNetMask = new QLabel(this);
	plbSubNetMask->setText(strTemp);
	m_pedtSubNetMask = new QLineEdit(this);
	pIpLabel->setFont(*g_pSttGlobalFont);
	m_pedtIP->setFont(*g_pSttGlobalFont);
	plbSubNetMask->setFont(*g_pSttGlobalFont);
	m_pedtSubNetMask->setFont(*g_pSttGlobalFont);

	QGridLayout *pGridLayout = new QGridLayout;
	pGridLayout->addWidget(pIpLabel,0,0,1,1);
	pGridLayout->addWidget(m_pedtIP,0,1,1,1);
	pGridLayout->addWidget(plbSubNetMask,1,0,1,1);
	pGridLayout->addWidget(m_pedtSubNetMask,1,1,1,1);

	m_pbtnOK = new QPushButton(g_sLangTxt_OK);
	m_pbtnCancel = new QPushButton(g_sLangTxt_Cancel);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
 	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(m_pbtnOK);
	pOkCancel_HBoxLayout->addWidget(m_pbtnCancel);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addLayout(pGridLayout);
	pMainLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainLayout); 
}

void QAuxModifyIPDlg::initSignalSlots()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QAuxModifyIPDlg::slot_OKClicked()
{
	QString strIP = m_pedtIP->text();
	QString strSubnetMask = m_pedtSubNetMask->text();

	if (strIP.isEmpty() || strSubnetMask.isEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_correctlyform.GetString());
		return;
	}

	emit sig_ModifyTesterIP_OK(strIP,strSubnetMask);
	close();
}

void QAuxModifyIPDlg::slot_CancelClicked()
{
	close();
}


void QAuxModifyIPDlg::InitParas(const QString &strIP,const QString &strSubNetMask)
{
	m_pedtIP->setText(strIP);
	m_pedtSubNetMask->setText(strSubNetMask);
}
