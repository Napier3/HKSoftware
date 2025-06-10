#include "qcommconfigtcpserverdlg.h"
#include "ui_qcommconfigtcpserverdlg.h"

QCommConfigServerDlg::QCommConfigServerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommConfigServerDlg)
{
    ui->setupUi(this);
    m_pTcpServer = NULL;
    m_pCommConfig = NULL;
}

QCommConfigServerDlg::~QCommConfigServerDlg()
{
    delete ui;
}

//void QCommConfigServerDlg::ShowData(CDvmData *pData)
//{
//    m_pTcpServer = pData;
//    CDvmValue *pLocalPort = (CDvmValue*)m_pTcpServer->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalPortKey);
//    CDvmValue *pLocalIP = (CDvmValue*)m_pTcpServer->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    ui->m_editLocalPort->setText(pLocalPort->m_strValue);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//}

void QCommConfigServerDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editLocalIP->setText(m_pCommConfig->TcpServer_Get_LocalIP());
    ui->m_editLocalPort->setText(m_pCommConfig->TcpServer_Get_LocalPort());

}

void QCommConfigServerDlg::SaveData()
{
    m_pCommConfig->TcpServer_Set_LocalIP(ui->m_editLocalIP->text());
    m_pCommConfig->TcpServer_Set_LocalPort(ui->m_editLocalPort->text().toInt());
}


