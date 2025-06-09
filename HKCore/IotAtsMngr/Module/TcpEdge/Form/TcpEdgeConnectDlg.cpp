#include "TcpEdgeConnectDlg.h"
#include "ui_TcpEdgeConnectDlg.h"
#include <QNetworkInterface>

CTcpEdgeConnectDlg::CTcpEdgeConnectDlg(QWidget *parent) :
	CTcpEdgeFormUI(parent),
	ui(new Ui::CTcpEdgeConnectDlg)
{
	ui->setupUi(this);

	ui->editMngrPort->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->editDataPort->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->titleName->setText("新建设备");
	setWindowTitle("新建设备");
	InitFormUI(this, ui->title);
}

CTcpEdgeConnectDlg::~CTcpEdgeConnectDlg()
{
	delete ui;
}

void CTcpEdgeConnectDlg::InitIP(QStringList strIPs)
{
	//初始化平台IP
	QList<QHostAddress> listAll = QNetworkInterface::allAddresses();
	QStringList temp;
	for (int i = 0; i < listAll.count(); i++)
	{
		if(listAll[i].protocol() == QAbstractSocket::IPv4Protocol)
		{
			temp.append(listAll[i].toString());
		}
	}
	temp.sort();
	ui->editLocalIP->addItem("");
	for (int i = 0; i < temp.count(); i++)
	{
		ui->editLocalIP->addItem(temp[i]);
	}

	//初始化客户端IP
	for (int i = 0; i < strIPs.count(); i++)
	{
		ui->editIP->addItem(strIPs[i]);
	}
}

QString CTcpEdgeConnectDlg::GetLocalIP()
{
	return ui->editLocalIP->currentText();
}

QString CTcpEdgeConnectDlg::GetIP()
{
	return ui->editIP->currentText();
}

long CTcpEdgeConnectDlg::GetMngrPort()
{
	return ui->editMngrPort->text().toLong();
}

long CTcpEdgeConnectDlg::GetDataPort()
{
	return ui->editDataPort->text().toLong();
}

bool CTcpEdgeConnectDlg::IsSign()
{
	return ui->cbSign->isChecked();
}

bool CTcpEdgeConnectDlg::IsZilb()
{
	return ui->cbZlib->isChecked();
}