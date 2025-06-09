#include "QSttBinRecordMainDlg.h"
#include "SttBinRecordDefine.h"
QSttBinRecordMainDlg *g_theSttBinRecordMainWidget = NULL;
QSttBinRecordMainDlg::QSttBinRecordMainDlg(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	g_theSttBinRecordMainWidget = this;
	m_pBinRecordCbWdiget = new QSttBinRecordCbWidget(this);
	m_pBinRecordConfigWidget = new QSttBinRecordDlg(this);
	m_pBinRecordConfigWidget->hide();
	m_pBinRecordCbWdiget->hide();
	ui.m_VLayOut_Center->insertWidget(STT_BINRECORD_ID_NZERO, m_pBinRecordConfigWidget);
	ui.m_VLayOut_Center->insertWidget(STT_BINRECORD_ID_NZERO, m_pBinRecordCbWdiget);

	connect(this, SIGNAL(sig_ShowBinConfigWindow()), this, SLOT(on_ShowBinConfigWindow()));
	connect(this, SIGNAL(sig_ShowBinRecordCbWindow()), this, SLOT(on_ShowBinRecordCbWindow()));
}

QSttBinRecordMainDlg::~QSttBinRecordMainDlg()
{

}

void QSttBinRecordMainDlg::closeEvent(QCloseEvent *event)
{
	m_pBinRecordConfigWidget->ExistBinRecord();
	QDialog::closeEvent(event);
}

void QSttBinRecordMainDlg::ShowBinConfigWindow()
{
	emit sig_ShowBinConfigWindow();
}

void QSttBinRecordMainDlg::ShowBinRecordCbWindow()
{
	emit sig_ShowBinRecordCbWindow();
}

void QSttBinRecordMainDlg::on_ShowBinConfigWindow()
{
	m_pBinRecordCbWdiget->hide();
	m_pBinRecordConfigWidget->show();
}

void QSttBinRecordMainDlg::on_ShowBinRecordCbWindow()
{
	if (m_pBinRecordCbWdiget == NULL)
	{
		m_pBinRecordCbWdiget = new QSttBinRecordCbWidget(this);
		ui.m_VLayOut_Center->insertWidget(STT_BINRECORD_ID_NZERO, m_pBinRecordCbWdiget);
	}
	m_pBinRecordCbWdiget->show();
	m_pBinRecordCbWdiget->SetCapDevice(m_pBinRecordCbWdiget->m_pCurrCapDevice);
	m_pBinRecordCbWdiget->UpDataShowPrimState();
	m_pBinRecordConfigWidget->hide();
}
