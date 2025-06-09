#include "QModifyIPAddrDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../../Module/Log/LogPrint.h"
#include "../../Module/XLangResource_Native.h"
#include"../../../../61850/Module/XLanguageResourcePp_Mms.h"
QModifyIPAddrDlg::QModifyIPAddrDlg(QWidget *pParent)
	:QDialog(pParent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); 
	initUI(); 
	initSignalSlots();
}

QModifyIPAddrDlg::~QModifyIPAddrDlg()
{

}

void QModifyIPAddrDlg::initUI()
{
	QHBoxLayout *pHLayModel = new QHBoxLayout;
	CString strTemp;
	//strTemp = _T("仪器型号:");
	m_plbTesterModel = new QLabel(g_sLangTxt_instrument);
	strTemp = _T("PN466");
	m_pedtTesterModel = new QLineEdit(strTemp);
	m_pedtTesterModel->setEnabled(false);
	pHLayModel->addWidget(m_plbTesterModel);
	pHLayModel->addWidget(m_pedtTesterModel);

	QHBoxLayout *pHLaySN = new QHBoxLayout;
	//strTemp = _T("仪器编号:");
	m_plbTesterSN = new QLabel(g_sLangTxt_instrumentnumber);
	m_pedtTesterSN = new QLineEdit(tr(""));
	m_pedtTesterSN->setEnabled(false);
	pHLaySN->addWidget(m_plbTesterSN);
	pHLaySN->addWidget(m_pedtTesterSN);

	//strTemp = _T("测试仪IP:");
	m_plbServerIP = new QLabel(g_sLangTxt_testip);
	strTemp = _T("127.0.0.1");
	m_pedtIP = new QLineEdit(strTemp);
	QHBoxLayout *pHLay1 = new QHBoxLayout;
	pHLay1->addWidget(m_plbServerIP);
	pHLay1->addWidget(m_pedtIP);

	//strTemp = _T("子网掩码:");
	m_plbSubNetMask = new QLabel(g_sLangTxt_SubNetwMask );
	strTemp = _T("255.255.255.0");
	m_pedtSubNetMask = new QLineEdit(strTemp);
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addWidget(m_plbSubNetMask);
	pHLay2->addWidget(m_pedtSubNetMask);

	QHBoxLayout *pHLay3 = new QHBoxLayout;
	pHLay3->addStretch();
	//strTemp = _T("确定");
	m_pbtnOK = new QPushButton(g_sLangTxt_OK);
	//strTemp = _T("取消");
	m_pbtnCancel = new QPushButton(g_sLangTxt_Cancel);
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
	
	//strTemp = _T("修改当前测试仪IP地址");
	setWindowTitle(g_sLangTxt_IPaddress);

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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_correctlyform.GetString());
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
