#include "qcommcfgtcpclientdlg.h"
#include "ui_qcommcfgtcpclientdlg.h"

QCommCfgTcpClientDlg::QCommCfgTcpClientDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommCfgTcpClientDlg)
{
    ui->setupUi(this);
    m_pTcpClient = NULL;
}

QCommCfgTcpClientDlg::~QCommCfgTcpClientDlg()
{
    delete ui;
}

#include "../../../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"

//void QCommCfgTcpClientDlg::ShowData(CDvmData *pData)
//{
//    m_pTcpClient = pData;
//    CDvmValue *pRemotePort = (CDvmValue*)m_pTcpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey);
//    CDvmValue *pRemoteIP = (CDvmValue*)m_pTcpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey);
//    CDvmValue *pLocalPort = (CDvmValue*)m_pTcpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
//    CDvmValue *pLocalIP = (CDvmValue*)m_pTcpClient->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    ui->m_editRemotePort->setText(pRemotePort->m_strValue);
//    ui->m_editRemoteIP->setText(pRemoteIP->m_strValue);
//    ui->m_editLocalPort->setText(pLocalPort->m_strValue);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//}

void QCommCfgTcpClientDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editRemotePort->setText(m_pCommConfig->TcpClient_Get_RemotePort());
    ui->m_editRemoteIP->setText(m_pCommConfig->TcpClient_Get_RemoteIP());
    ui->m_editLocalIP->setText(m_pCommConfig->TcpClient_Get_LocalIP());
    ui->m_editLocalPort->setText(m_pCommConfig->TcpClient_Get_LocalPort());

}

void QCommCfgTcpClientDlg::SaveData()
{

    m_pCommConfig->TcpClient_Set_RemotePort(ui->m_editRemotePort->text().toInt());
    m_pCommConfig->TcpClient_Set_RemoteIP(ui->m_editRemoteIP->text());
    m_pCommConfig->TcpClient_Set_LocalIP(ui->m_editLocalIP->text());
    m_pCommConfig->TcpClient_Set_LocalPort(ui->m_editLocalPort->text().toInt());
}


