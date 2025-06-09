#include "qcommconfigmmsdlg.h"
#include "ui_qcommconfigmmsdlg.h"

QCommConfigMmsDlg::QCommConfigMmsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommConfigMmsDlg)
{
    ui->setupUi(this);
    m_pMms = NULL;
    m_pCommConfig = NULL;
}

QCommConfigMmsDlg::~QCommConfigMmsDlg()
{
    delete ui;
}

//void QCommConfigMmsDlg::ShowData(CDvmData *pData)
//{
//    m_pMms = pData;
//    CDvmValue *pLocalIP = (CDvmValue*)m_pMms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey);
//    CDvmValue *pEncryptKey = (CDvmValue*)m_pMms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptKeyKey);
//    CDvmValue *pEncryptPsw = (CDvmValue*)m_pMms->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strEncryptPswKey);
//    ui->m_editLocalIP->setText(pLocalIP->m_strValue);
//    ui->m_editEncryptKey->setText(pEncryptKey->m_strValue);
//    ui->m_editEncryptPsw->setText(pEncryptPsw->m_strValue);
//}

void QCommConfigMmsDlg::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
    ui->m_editRemoteIP->setText(m_pCommConfig->MMS_Get_RemoteIP());
    ui->m_editEncryptKey->setText(m_pCommConfig->MMS_Get_EncryptKey());
    ui->m_editEncryptPsw->setText(m_pCommConfig->MMS_Get_EncryptPsw());
}

void QCommConfigMmsDlg::SaveData()
{
    m_pCommConfig->MMS_Set_RemoteIP(ui->m_editRemoteIP->text());
    m_pCommConfig->MMS_Set_EncryptKey(ui->m_editEncryptKey->text());
    m_pCommConfig->MMS_Set_EncryptPsw(ui->m_editEncryptPsw->text());
}

