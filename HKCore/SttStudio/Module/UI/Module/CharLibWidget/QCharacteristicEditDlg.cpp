#include "QCharacteristicEditDlg.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"

QCharacteristicEditDlg::QCharacteristicEditDlg(CCharacteristic *pCharacteristic,QWidget *parent)
	: QDialog(parent)
{
	m_pSrcCharacteristic = pCharacteristic;
	m_pEditCharacteristic = (CCharacteristic*)m_pSrcCharacteristic->Clone();
}

QCharacteristicEditDlg::~QCharacteristicEditDlg()
{
	delete m_pEditCharacteristic;
}

void QCharacteristicEditDlg::InitUI()
{
	CString strText;
	m_pMain_VLayout = new QVBoxLayout(this);

	m_pOkCancelHLayout = new QHBoxLayout(this);


	strText = /*_T("确定")*/g_sLangTxt_OK; //lcq
	m_pOk_Button = new QPushButton(strText);
	strText = /*_T("取消")*/g_sLangTxt_Cancel; //lcq
	m_pCancel_Button = new QPushButton(strText);
	m_pOkCancelHLayout->addWidget(m_pOk_Button);
	m_pOkCancelHLayout->addWidget(m_pCancel_Button);

	m_pMain_VLayout->addLayout(m_pOkCancelHLayout);

	InitDatas();
	IntConnects();
}

void QCharacteristicEditDlg::IntConnects()
{
	connect(m_pOk_Button, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_Button, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QCharacteristicEditDlg::InitDatas()
{

}

void QCharacteristicEditDlg::slot_OKClicked()
{
	accept();
}

void QCharacteristicEditDlg::slot_CancelClicked()
{
	close();
}