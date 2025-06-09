#include "stdafx.h"
#include "TcpEdgeInformationDlg.h"
#include "ui_TcpEdgeInformationDlg.h"

CTcpEdgeInformationDlg::CTcpEdgeInformationDlg(QWidget *parent) :
	CTcpEdgeFormUI(parent),
	ui(new Ui::CTcpEdgeInformationDlg)
{
	ui->setupUi(this);

	CString strFilePath = _P_GetResourcePath();
	m_imgInfo = QIcon(strFilePath + "Info.png");
	m_imgWarning = QIcon(strFilePath + "WarningInfo.png");
	m_imgError = QIcon(strFilePath + "ErrorInfo.png");
	m_imgAbout = QIcon(strFilePath + "Title.png");

	InitFormUI(this, ui->title);
}

CTcpEdgeInformationDlg::~CTcpEdgeInformationDlg()
{
	delete ui;
}

void CTcpEdgeInformationDlg::show(const QString& strText)
{
	ui->progressBar->hide();
	ui->btnCancel->hide();
	ui->btnOK->hide();
	ui->titleName->setText("提示");
	ui->icon->setPixmap(m_imgInfo.pixmap(QSize(40, 40)));
	ui->txtInformation->setText(strText);
	QDialog::show();
}

int CTcpEdgeInformationDlg::exec(long nModel, const QString& strText)
{
	ui->btnCancel->hide();
	ui->progressBar->hide();
	ui->txtInformation->setText(strText);
	switch(nModel)
	{
	case INFO:
		ui->titleName->setText("提示");
		ui->btnCancel->show();
		ui->icon->setPixmap(m_imgInfo.pixmap(QSize(40, 40)));
		break;
	case WARNING:
		ui->titleName->setText("警告");
		ui->icon->setPixmap(m_imgWarning.pixmap(QSize(40, 40)));
		break;
	case ERR:
		ui->titleName->setText("错误");
		ui->icon->setPixmap(m_imgError.pixmap(QSize(40, 40)));
		break;
	case ABOUT:
		ui->titleName->setText("关于");
		ui->icon->setPixmap(m_imgAbout.pixmap(QSize(40, 40)));
		break;
	case PERCENT:
		ui->btnOK->hide();
		ui->txtInformation->hide();
		ui->icon->hide();
		ui->progressBar->show();
		ui->titleName->setText(strText);
	default:
		break;
	}
	return QDialog::exec();
}