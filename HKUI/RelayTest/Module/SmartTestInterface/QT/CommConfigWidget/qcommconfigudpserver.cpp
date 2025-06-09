#include "qcommconfigudpserver.h"
#include "ui_qcommconfigudpserver.h"

QCommConfigUdpServer::QCommConfigUdpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommConfigUdpServer)
{
    ui->setupUi(this);
    m_pUdpServer = NULL;
    m_pCommConfig = NULL;
}

QCommConfigUdpServer::~QCommConfigUdpServer()
{
    delete ui;
}

//void QCommConfigUdpServer::ShowData(CDvmData *pData)
//{
//    m_pUdpServer = pData;
//    CDvmValue *pLocalPort = (CDvmValue*)m_pUdpServer->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
//    CDvmValue *pLocalIP = (CDvmValue*)m_pUdpServer->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    CDvmValue *pMulticastIP = (CDvmValue*)m_pUdpServer->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey);
//    ui->m_editLocalPort->setText(pLocalPort->m_strValue);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//    ui->m_editMulticastIP->setText(pMulticastIP->m_strValue);
//}

void QCommConfigUdpServer::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editLocalIP->setText(m_pCommConfig->UdpServer_Get_LocalIP());
    ui->m_editLocalPort->setText(m_pCommConfig->UdpServer_Get_LocalPort());
    ui->m_editMulticastIP->setText(m_pCommConfig->UdpServer_Get_MuticastIP());

}

void QCommConfigUdpServer::SaveData()
{
    m_pCommConfig->UdpServer_Set_LocalIP(ui->m_editLocalIP->text());
//    m_pCommConfig->UdpServer_Set_LocalIP(ui->m_editMulticastIP->text());
    m_pCommConfig->UdpServer_Set_LocalPort(ui->m_editLocalPort->text().toInt());
	m_pCommConfig->UdpServer_Set_MuticastIP(ui->m_editMulticastIP->text());
}


void QCommConfigUdpServer::on_isBroadcast_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->m_editMulticastIP->setDisabled(true);
        ui->label_5->setDisabled(true);
        ui->m_editMulticastIP->setText("0.0.0.0");
    }
    else
    {
        ui->m_editMulticastIP->setDisabled(false);
        ui->label_5->setDisabled(false);
    }
}
