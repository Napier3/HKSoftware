#include <QComboBox>

#include "qcommconfigserialmode.h"
#include "ui_qcommconfigserialmode.h"


QCommConfigSerialMode::QCommConfigSerialMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCommConfigSerialMode)
{
    ui->setupUi(this);
    m_pSerial = NULL;
	//m_pCommConfig = pCommConfg;

	QStringList strList;
	for (int i=0; i<ui->m_cmbPortNum->count(); i++)
	{
		strList << ui->m_cmbPortNum->itemText(i);
	}
	ui->m_cmbPortNum->clear();
	ui->m_cmbPortNum-> addItem("COM0");
	ui->m_cmbPortNum->addItems(strList);

	ui->m_cmbStopBits->removeItem(1);
}

QCommConfigSerialMode::~QCommConfigSerialMode()
{
    delete ui;
}

//void  QCommConfigSerialMode::ShowData(CDvmData *pData)
//{
//    m_pSerial = pData;
//    CDvmValue *pPortNum = (CDvmValue*)m_pSerial->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strPortNumKey);
//    CDvmValue *pBaudRate = (CDvmValue*)m_pSerial->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strBaudRateKey);
//    CDvmValue *ByteSize = (CDvmValue*)m_pSerial->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strByteSizeKey);
//    CDvmValue *pStopBits = (CDvmValue*)m_pSerial->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strStopBitsKey);
//    CDvmValue *pParity = (CDvmValue*)m_pSerial->FindByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strParityKey);
//    ui->m_cmbPortNum->setCurrentText(pPortNum->m_strValue);
//    ui->m_cmbBaudRate->setCurrentText(pBaudRate->m_strValue);
//    ui->m_cmbByteSize->setCurrentText(ByteSize->m_strValue);
//    ui->m_cmbStopBits->setCurrentText(pStopBits->m_strValue);
//    ui->m_cmbParity->setCurrentText(pParity->m_strValue);

//}
void QCommConfigSerialMode::SetComboSelIndex(QComboBox* pCombo, CString strNameFind)
{
	for (int i=0; i<pCombo->count(); i++)
	{
		if (pCombo->itemText(i) == strNameFind)
		{
			pCombo->setCurrentIndex(i);
			break;
		}
	}

}
void  QCommConfigSerialMode::ShowData(CPpSttCommConfig *pCommConfig)
{
    m_pCommConfig = pCommConfig;
	//InsertPolicy poly;
	//ui->m_cmbPortNum->setInsertPolicy(poly);


    //ui->m_cmbPortNum->setEditText(m_pCommConfig->Serial_Get_port_number());
	ui->m_cmbPortNum->setCurrentIndex(m_pCommConfig->Serial_Get_port_number().toInt());

    //ui->m_cmbBaudRate->setEditText(m_pCommConfig->Serial_Get_baud_rate());
	SetComboSelIndex(ui->m_cmbBaudRate,m_pCommConfig->Serial_Get_baud_rate());

    //ui->m_cmbByteSize->setEditText(m_pCommConfig->Serial_Get_byte_size());
	SetComboSelIndex(ui->m_cmbByteSize,m_pCommConfig->Serial_Get_byte_size());

   // ui->m_cmbStopBits->setEditText(m_pCommConfig->Serial_Get_stop_bit());
	SetComboSelIndex(ui->m_cmbStopBits,m_pCommConfig->Serial_Get_stop_bit());


   // ui->m_cmbParity->setEditText(m_pCommConfig->Serial_Get_parity());
	ui->m_cmbParity->setCurrentIndex(m_pCommConfig->Serial_Get_parity().toInt());

}
void  QCommConfigSerialMode::SaveData()
{
    //m_pCommConfig->Serial_Set_port_number(ui->m_cmbPortNum->currentText().toInt());
	m_pCommConfig->Serial_Set_port_number(ui->m_cmbPortNum->currentIndex());

    m_pCommConfig->Serial_Set_baud_rate(ui->m_cmbBaudRate->currentText().toInt());
    m_pCommConfig->Serial_Set_byte_size(ui->m_cmbByteSize->currentText().toInt());
    m_pCommConfig->Serial_Set_stop_bit(ui->m_cmbStopBits->currentText().toInt());

    //m_pCommConfig->Serial_Set_parity(ui->m_cmbParity->currentText().toInt());
	m_pCommConfig->Serial_Set_parity(ui->m_cmbParity->currentIndex());

}

