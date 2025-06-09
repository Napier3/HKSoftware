#include "qcommconfigudpclientdlg.h"
#include "ui_qcommconfigudpclientdlg.h"

QCommConfigUdpClientDlg::QCommConfigUdpClientDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommConfigUdpClientDlg)
{
    ui->setupUi(this);
    m_pUdpClient = NULL;
    m_pCommConfig = NULL;
}

QCommConfigUdpClientDlg::~QCommConfigUdpClientDlg()
{
    delete ui;
}

//void QCommConfigUdpClientDlg::ShowData(CDvmData *pData)
//{
//    m_pUdpClient = pData;
//    CDvmValue *pLocalPort = (CDvmValue*)m_pUdpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
//    CDvmValue *pLocalIP = (CDvmValue*)m_pUdpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    CDvmValue *pRemotePort = (CDvmValue*)m_pUdpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey);
//    CDvmValue *pRemoteIP = (CDvmValue*)m_pUdpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
//    CDvmValue *pMulticastIP = (CDvmValue*)m_pUdpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMulticastIPKey);

//    ui->m_editLocalPort->setText(pLocalPort->m_strValue);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//    ui->m_editRemotePort->setText(pRemotePort->m_strValue);
//    ui->m_editRemoteIP->setText(pRemoteIP->m_strValue);
//    ui->m_editMulticastIP->setText(pMulticastIP->m_strValue);
//}

void QCommConfigUdpClientDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editLocalIP->setText(m_pCommConfig->UdpClient_Get_LocalIP());
    ui->m_editLocalPort->setText(m_pCommConfig->UdpClient_Get_LocalPort());
    ui->m_editRemoteIP->setText(m_pCommConfig->UdpClient_Get_RemoteIP());
    ui->m_editRemotePort->setText(m_pCommConfig->UdpClient_Get_RemotePort());
    ui->m_editMulticastIP->setText(m_pCommConfig->UdpClient_Get_MuticastIP());
}

void QCommConfigUdpClientDlg::SaveData()
{
    m_pCommConfig->UdpClient_Set_LocalIP(ui->m_editLocalIP->text());
    m_pCommConfig->UdpClient_Set_LocalPort(ui->m_editLocalPort->text().toInt());
    m_pCommConfig->UdpClient_Set_RemoteIP(ui->m_editRemoteIP->text());
    m_pCommConfig->UdpClient_Set_RemotePort(ui->m_editRemotePort->text().toInt());
    m_pCommConfig->UdpClient_Set_MuticastIP(ui->m_editMulticastIP->text());
}

void QCommConfigUdpClientDlg::on_m_chkIsBroadcast_stateChanged(int arg1)
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
