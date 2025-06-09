#include "QModifyIPAddrDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "..\..\..\..\..\Module\Log\LogPrint.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"

QModifyIPAddrDlg::QModifyIPAddrDlg(QWidget *pParent)
	:QDialog(pParent)
{
	initUI(); 
	initSignalSlots();
}

QModifyIPAddrDlg::~QModifyIPAddrDlg()
{

}

void QModifyIPAddrDlg::initUI()
{
	QHBoxLayout *pHLayModel = new QHBoxLayout;
	m_plbTesterModel = new QLabel(/*tr("仪器型号:")*/g_sLangTxt_instrument);
	m_pedtTesterModel = new QLineEdit(tr("PN466"));
	m_pedtTesterModel->setEnabled(false);
	pHLayModel->addWidget(m_plbTesterModel);
	pHLayModel->addWidget(m_pedtTesterModel);

	QHBoxLayout *pHLaySN = new QHBoxLayout;
	m_plbTesterSN = new QLabel(/*tr("仪器编号:")*/g_sLangTxt_instrumentnumber);
	m_pedtTesterSN = new QLineEdit(tr(""));
	m_pedtTesterSN->setEnabled(false);
	pHLaySN->addWidget(m_plbTesterSN);
	pHLaySN->addWidget(m_pedtTesterSN);

	m_plbServerIP = new QLabel(/*tr("测试仪IP:")*/g_sLangTxt_testip);
	m_pedtIP = new QLineEdit(tr("127.0.0.1"));
	QHBoxLayout *pHLay1 = new QHBoxLayout;
	pHLay1->addWidget(m_plbServerIP);
	pHLay1->addWidget(m_pedtIP);

	m_plbSubNetMask = new QLabel(/*tr("子网掩码:")*/g_sLangTxt_Native_SubMask+":");
	m_pedtSubNetMask = new QLineEdit(tr("255.255.255.0"));
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addWidget(m_plbSubNetMask);
	pHLay2->addWidget(m_pedtSubNetMask);
//	m_pedtSubNetMask->setEnabled(false);

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
	pVLay->addLayout(pHLayModel);
	pVLay->addLayout(pHLaySN);
	pVLay->addLayout(pHLay1);
	pVLay->addLayout(pHLay2);
	pVLay->addLayout(pHLay3);
	setLayout(pVLay); //设置为窗体的主布局

	setWindowTitle(/*tr("修改当前测试仪IP地址")*/g_sLangTxt_IPaddress);

	//去除对话框中问号
	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void QModifyIPAddrDlg::initSignalSlots()
{
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QModifyIPAddrDlg::slot_OKClicked()
{
	QString strIP = m_pedtIP->text();
	QString strSubnetMask = m_pedtSubNetMask->text();

	if (strIP.isEmpty() || strSubnetMask.isEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("IP地址或者子网掩码格式错误.")*/g_sLangTxt_correctlyform.GetString());
		return;
	}

	emit sig_ModifyTesterIP_OK(strIP,strSubnetMask);
	close();
}

void QModifyIPAddrDlg::slot_CancelClicked()
{
	close();
}

void QModifyIPAddrDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{

	}
}

void QModifyIPAddrDlg::InitParas(const QString &strModel,const QString &strSN,const QString &strIP,const QString &strSubNetMask)
{
	m_pedtTesterModel->setText(strModel);
	m_pedtTesterSN->setText(strSN);
	m_pedtIP->setText(strIP);
	m_pedtSubNetMask->setText(strSubNetMask);
}