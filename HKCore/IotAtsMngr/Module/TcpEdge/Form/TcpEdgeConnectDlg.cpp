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
	ui->titleName->setText("�½��豸");
	setWindowTitle("�½��豸");
	InitFormUI(this, ui->title);
}

CTcpEdgeConnectDlg::~CTcpEdgeConnectDlg()
{
	delete ui;
}

void CTcpEdgeConnectDlg::InitIP(QStringList strIPs)
{
	//��ʼ��ƽ̨IP
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

	//��ʼ���ͻ���IP
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