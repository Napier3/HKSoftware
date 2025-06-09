#include "SttAuxIPSetDlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../../../Module/Log/LogPrint.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../XLangResource_Native.h"

QSttAuxIPSetDlg::QSttAuxIPSetDlg(QWidget *pParent)
	:QDialog(pParent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	initUI(); 
	initSignalSlots();
}

QSttAuxIPSetDlg::~QSttAuxIPSetDlg()
{

}

void QSttAuxIPSetDlg::initUI()
{
	m_pIP_QLabel = new QLabel(tr("IP:"));
	m_pIP_QLineEdit = new QSttLineEdit(this);
	m_pIP_QLineEdit->setText(tr("127.0.0.1"));
	QHBoxLayout *pHLay1 = new QHBoxLayout;
	pHLay1->addWidget(m_pIP_QLabel);
	pHLay1->addWidget(m_pIP_QLineEdit);

	m_pbtnOK = new QPushButton(/*tr("确定")*/g_sLangTxt_OK); //lcq
	m_pbtnCancel = new QPushButton(/*tr("取消")*/g_sLangTxt_Cancel); //lcq
	QHBoxLayout *pHLay2 = new QHBoxLayout;
	pHLay2->addStretch();
	pHLay2->addWidget(m_pbtnOK);
	pHLay2->addWidget(m_pbtnCancel);

	QVBoxLayout *pVLay=new QVBoxLayout;
	pVLay->addLayout(pHLay1);
	pVLay->addLayout(pHLay2);
	setLayout(pVLay); //设置为窗体的主布局

	setWindowTitle(/*tr("辅助IP设置")*/g_sLangTxt_Gradient_SecondaryIPSet);

	//去除对话框中问号
	Qt::WindowFlags flags= this->windowFlags();
	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void QSttAuxIPSetDlg::initSignalSlots()
{
	connect(m_pIP_QLineEdit, SIGNAL(clicked()), this, SLOT(slot_IP_Changed()));
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttAuxIPSetDlg::slot_OKClicked()
{
	QString strIP = m_pIP_QLineEdit->text();

	if (strIP.isEmpty())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,/*_T("IP输入不合法")*/g_sLangTxt_Gradient_IPInputInvalid.GetString()); //lcq
		return;
	}

	accept();
}

void QSttAuxIPSetDlg::slot_CancelClicked()
{
	close();
}

void QSttAuxIPSetDlg::slot_IP_Changed()
{
	QString strValue = m_pIP_QLineEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pIP_QLineEdit,this);
// 	m_pIP_QLineEdit->setText(strValue);
// 	m_pIP_QLineEdit->SetEditFinished();
}

QString QSttAuxIPSetDlg::GetCurrIP()
{
	if (m_pIP_QLineEdit == NULL)
	{
		return "";
	}

	QString strIP;
	strIP = m_pIP_QLineEdit->text();
	return strIP;
}

void QSttAuxIPSetDlg::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter||key == Qt::Key_Return)
	{
	}
}

void QSttAuxIPSetDlg::InitParas(const QString &strIP)
{
	m_pIP_QLineEdit->setText(strIP);
}