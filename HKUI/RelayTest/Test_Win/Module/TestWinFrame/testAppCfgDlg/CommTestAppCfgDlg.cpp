#include "CommTestAppCfgDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "..\..\..\..\..\Module\Log\LogPrint.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

CCommTestAppCfgDlg::CCommTestAppCfgDlg(QWidget *pParent)
	:QDialog(pParent)
{
	initUI(); 
	initSignalSlots();
}

CCommTestAppCfgDlg::~CCommTestAppCfgDlg()
{

}

void CCommTestAppCfgDlg::initUI()
{
	m_plb1 = new QLabel(tr("IP:"));
	m_pedtIP = new QLineEdit(tr("127.0.0.1"));
	QHBoxLayout *pHLay1 = new QHBoxLayout;
	pHLay1->addWidget(m_plb1);
	pHLay1->addWidget(m_pedtIP);

	m_plb2 = new QLabel(/*tr("端口号:")*/g_sLangTxt_Native_PortNum);
	m_pedtPort = new QLineEdit(tr("19814"));
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addWidget(m_plb2);
	pHLay2->addWidget(m_pedtPort);
	m_pedtPort->setEnabled(false);

	QHBoxLayout *pHLay3 = new QHBoxLayout;
	pHLay3->addStretch();
	m_pbtnOK = new QPushButton(/*tr("确定")*/g_sLangTxt_OK);
	m_pbtnOK->setIcon (QPixmap( "./images/Check.png"));
	m_pbtnCancel = new QPushButton(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pbtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
	pHLay3->addWidget(m_pbtnOK);
	pHLay3->addWidget(m_pbtnCancel);
	pHLay3->addStretch();

	QVBoxLayout *pVLay=new QVBoxLayout;
	pVLay->addLayout(pHLay1);
	pVLay->addLayout(pHLay2);
	pVLay->addLayout(pHLay3);
	setLayout(pVLay); //设置为窗体的主布局

	setWindowTitle(/*"网络配置"*/g_sLangTxt_Native_NetConfig);

	//去除对话框中问号
	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void CCommTestAppCfgDlg::initSignalSlots()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void CCommTestAppCfgDlg::slot_OKClicked()
{
	QString strIP = m_pedtIP->text();
	long nPort = m_pedtPort->text().toInt();

	if (strIP.isEmpty() || nPort < 1000)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("IP和端口号输入不合法")*/g_sLangTxt_Native_InvalidIPPort.GetString());
		return;
	}

	emit sig_CommCfgOK(strIP,nPort);
}

void CCommTestAppCfgDlg::slot_CancelClicked()
{
	close();
}

void CCommTestAppCfgDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{

	}
}

void CCommTestAppCfgDlg::InitParas(const QString &strIP,long nPort)
{
	m_pedtIP->setText(strIP);
	m_pedtPort->setText(QString::number(nPort));
}