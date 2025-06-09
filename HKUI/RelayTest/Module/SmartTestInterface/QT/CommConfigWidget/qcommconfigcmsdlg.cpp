#include "qcommconfigcmsdlg.h"
#include "ui_qcommconfigcmsdlg.h"

QCOmmConfigCmsDlg::QCOmmConfigCmsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCOmmConfigCmsDlg)
{
    ui->setupUi(this);
    m_pCms = NULL;
    m_pCommConfig = NULL;
    ui->m_editClientIP->setDisabled(true);
}

QCOmmConfigCmsDlg::~QCOmmConfigCmsDlg()
{
    delete ui;
}

//void QCOmmConfigCmsDlg::ShowData(CDvmData *pData)
//{
//    m_pCms = pData;
//    CDvmValue *pLocalIP = (CDvmValue*)m_pCms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    CDvmValue *pEncryptKey = (CDvmValue*)m_pCms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey);
//    CDvmValue *pEncryptPsw = (CDvmValue*)m_pCms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//    ui->m_editEncryptKey->setText(pEncryptKey->m_strValue);
//    ui->m_editEncryptPsw->setText(pEncryptPsw->m_strValue);
//}

void QCOmmConfigCmsDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editLocalIP->setText(m_pCommConfig->CMS_Get_LocalIP());
    ui->m_editEncryptKey->setText(m_pCommConfig->CMS_Get_EncryptKey());
    ui->m_editEncryptPsw->setText(m_pCommConfig->CMS_Get_EncryptPsw());
    ui->m_editClientIP->setText(m_pCommConfig->CMS_Get_RemoteIP());

}

void QCOmmConfigCmsDlg::SaveData()
{
    m_pCommConfig->CMS_Set_LocalIP(ui->m_editLocalIP->text());
    m_pCommConfig->CMS_Set_EncryptKey(ui->m_editEncryptKey->text());
    m_pCommConfig->CMS_Set_EncryptPsw(ui->m_editEncryptPsw->text());
    m_pCommConfig->CMS_Set_RemoteIP(ui->m_editClientIP->text());
}


void QCOmmConfigCmsDlg::on_isClientIP_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->m_editClientIP->setDisabled(false);
    }
    else
    {
        ui->m_editClientIP->setDisabled(true);
    }
}
