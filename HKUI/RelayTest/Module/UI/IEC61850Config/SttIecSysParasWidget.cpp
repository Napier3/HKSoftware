#include "SttIecSysParasWidget.h"
#include "SttIecSysParasOtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

QSttSysParasWidget::QSttSysParasWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pMain_HLayout = NULL;
	m_pMain_ScrollArea = NULL;
	m_pScrollArea_Widget = NULL;
	m_pScrollAreaWidget_GridLayout = NULL;
	m_pPkgSendType_HBoxLayout = NULL;
	m_pPkgSendTypeComboBox = NULL;
	m_pParasSetSelCombox = NULL;
	m_pPkgSendSelCombox = NULL;
//	m_pSecondSynComboBox = NULL;
	m_pOtherSetPushBtn = NULL;
	m_pPkgSendType_FormLayout = NULL;
	m_pParasSetSel_FormLayout = NULL;
	m_pPkgSendSel_FormLayout = NULL;
//	m_pSencondSyn_FormLayout = NULL;
	m_pPkgSendType_GroupBox = NULL;
	m_pTransRadios_GroupBox = NULL;
	m_pTransRadio_VBoxLayout = NULL;
	m_pIecCfgSysParas = NULL;
	m_pPrimRates = NULL;
	m_pPrimRatesIn = NULL;
	InitUI();
}

QSttSysParasWidget::~QSttSysParasWidget()
{
 
}

void QSttSysParasWidget::InitUI()
{
	CString strTemp;

	m_pPkgSendTypeComboBox = new QScrollComboBox;
	xlang_GetLangStrByFile(strTemp,"IEC_KeepSendAfterStop");
	m_pPkgSendTypeComboBox->addItem(strTemp);
	xlang_GetLangStrByFile(strTemp,"IEC_StopSending");
	m_pPkgSendTypeComboBox->addItem(strTemp);

	//2022.5.26 zyq
	m_pParasSetSelCombox = new QScrollComboBox;
	xlang_GetLangStrByFile(strTemp,"IEC_OnceValue");
	m_pParasSetSelCombox->addItem(strTemp);
	xlang_GetLangStrByFile(strTemp,"IEC_TwiceValue");
	m_pParasSetSelCombox->addItem(strTemp);
	//m_pParasSetSelCombox->addItem(tr("一次值"));
	//m_pParasSetSelCombox->addItem(tr("二次值"));

	m_pPkgSendSelCombox = new QScrollComboBox;
	xlang_GetLangStrByFile(strTemp,"IEC_OnceValue");
	m_pPkgSendSelCombox->addItem(strTemp);
	xlang_GetLangStrByFile(strTemp,"IEC_TwiceValue");
	m_pPkgSendSelCombox->addItem(strTemp);
	//m_pPkgSendSelCombox->addItem(tr("一次值"));
	//m_pPkgSendSelCombox->addItem(tr("二次值"));
	
// 	m_pSecondSynComboBox = new QScrollComboBox;
// 	m_pSecondSynComboBox->addItem(tr("开启秒同步"));
// 	m_pSecondSynComboBox->addItem(tr("关闭秒同步"));

	xlang_GetLangStrByFile(strTemp,"State_Othersettings");
	m_pOtherSetPushBtn = new QPushButton(strTemp);

	m_pPkgSendType_HBoxLayout = new QHBoxLayout;
	m_pPkgSendType_FormLayout = new QFormLayout;
	m_pParasSetSel_FormLayout = new QFormLayout;
	m_pPkgSendSel_FormLayout = new QFormLayout;

	m_pPkgSendType_HBoxLayout->addLayout(m_pPkgSendType_FormLayout);
	m_pPkgSendType_HBoxLayout->addLayout(m_pParasSetSel_FormLayout);
	m_pPkgSendType_HBoxLayout->addLayout(m_pPkgSendSel_FormLayout);
//	m_pPkgSendType_HBoxLayout->addStretch();
//	m_pSencondSyn_FormLayout = new QFormLayout;

	xlang_GetLangStrByFile(strTemp,"IEC_PacketSendingMode");
 	m_pPkgSendType_FormLayout->addRow(strTemp, m_pPkgSendTypeComboBox);
	
	xlang_GetLangStrByFile(strTemp,"Gradient_ParaSet");
	m_pParasSetSel_FormLayout->addRow(strTemp, m_pParasSetSelCombox);
	//m_pParasSetSel_FormLayout->addRow(tr("参数设置:"), m_pParasSetSelCombox);
	
	xlang_GetLangStrByFile(strTemp,"IEC_PacketSending");
	m_pPkgSendSel_FormLayout->addRow(strTemp, m_pPkgSendSelCombox);
	//m_pPkgSendSel_FormLayout->addRow(tr("报文输出:"), m_pPkgSendSelCombox);

// 	m_pSencondSyn_FormLayout->addRow(tr("秒同步状态："),m_pSecondSynComboBox);
//	m_pPkgSendType_HBoxLayout->addLayout(m_pSencondSyn_FormLayout);
//	m_pPkgSendType_HBoxLayout->addStretch();
	m_pPkgSendType_HBoxLayout->addWidget(m_pOtherSetPushBtn);
	m_pPkgSendType_GroupBox = new QGroupBox;
	m_pPkgSendType_GroupBox->setLayout(m_pPkgSendType_HBoxLayout);

	//变比设置
	m_pTransRadio_VBoxLayout = new QVBoxLayout;
	m_pTransRadio_VBoxLayout->setContentsMargins(0,0,0,0);
	QString strGroupDesc;
	long nGroupIndex = 0;

	for (int nIndex=0; nIndex<STT_SYSPARAS_TRANS_RADIO_NUM; nIndex++)
	{
		nGroupIndex = nIndex+1;
		if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
		{
			strGroupDesc = QString("第%1组(Ua%2,Ub%3,Uc%4,Ia%5,Ib%6,Ic%7)").arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex);
		}
		else
		{
			strGroupDesc = QString("Group %1(Ua%2,Ub%3,Uc%4,Ia%5,Ib%6,Ic%7)").arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex).arg(nGroupIndex);
		}

		m_oTransRadioGroup[nIndex].pGroupBox = new QGroupBox(strGroupDesc);
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit = new QFloatLineEdit();
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->setMaximumWidth(120);
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit = new QFloatLineEdit();
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->setMaximumWidth(120);
		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit = new QFloatLineEdit();
		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->setMaximumWidth(120);
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit = new QFloatLineEdit();
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->setMaximumWidth(120);

		connect(m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_Clicked()));
		connect(m_oTransRadioGroup[nIndex].pSecondVolLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_Clicked()));
		connect(m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_Clicked()));
		connect(m_oTransRadioGroup[nIndex].pSecondCurrLineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_Clicked()));

		m_oTransRadioGroup[nIndex].pHBoxLayout = new QHBoxLayout;
		m_oTransRadioGroup[nIndex].pGroupBox->setLayout(m_oTransRadioGroup[nIndex].pHBoxLayout);
		xlang_GetLangStrByFile(strTemp,"IEC_PTRatio");
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(new QLabel(strTemp));
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit);
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(new QLabel("/"));
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(m_oTransRadioGroup[nIndex].pSecondVolLineEdit);
		m_oTransRadioGroup[nIndex].pHBoxLayout->addStretch();
		xlang_GetLangStrByFile(strTemp,"IEC_CTRatio");
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(new QLabel(strTemp));
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit);
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(new QLabel("/"));
		m_oTransRadioGroup[nIndex].pHBoxLayout->addWidget(m_oTransRadioGroup[nIndex].pSecondCurrLineEdit);
		m_oTransRadioGroup[nIndex].pHBoxLayout->addStretch();

		m_pTransRadio_VBoxLayout->addWidget(m_oTransRadioGroup[nIndex].pGroupBox);
	}

	m_pTransRadios_GroupBox = new QGroupBox;
	m_pTransRadios_GroupBox->setLayout(m_pTransRadio_VBoxLayout);

	//main
	m_pScrollAreaWidget_GridLayout = new QGridLayout;
	m_pScrollAreaWidget_GridLayout->setHorizontalSpacing(100);
	m_pScrollAreaWidget_GridLayout->addWidget(m_pPkgSendType_GroupBox, 0, 0, 1, 1);
	m_pScrollAreaWidget_GridLayout->addWidget(m_pTransRadios_GroupBox, 1, 0, 1, 2);

	m_pMain_ScrollArea = new QScrollArea(this);
	m_pScrollArea_Widget = new QWidget(m_pMain_ScrollArea);
	m_pScrollArea_Widget->setLayout(m_pScrollAreaWidget_GridLayout);

	m_pMain_ScrollArea->setWidget(m_pScrollArea_Widget);
	m_pMain_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pMain_HLayout = new QHBoxLayout(this);
	m_pMain_HLayout->addWidget(m_pMain_ScrollArea);
	connect(m_pPkgSendTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PkgSendTypeChanged(int)));

	connect(m_pParasSetSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ParasSetSelChanged(int)));
	connect(m_pPkgSendSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PkgSendSelChanged(int)));

	connect(m_pOtherSetPushBtn, SIGNAL(clicked()), SLOT(slot_OtherSetPushBtnClicked()));
//	connect(m_oTransRadioGroup[0].pPrimaryCurrLineEdit, SIGNAL(editingFinished()), SLOT(slot_PrimaryCurr1_EditFinished()));
}

void QSttSysParasWidget::InitData(CIecCfgSysParas* pIecCfgSysParas)
{
	m_pIecCfgSysParas = pIecCfgSysParas;
	m_pPrimRates = m_pIecCfgSysParas->GetPrimRates();
	m_pPrimRatesIn = m_pIecCfgSysParas->GetPrimRatesIn();
	m_pPkgSendTypeComboBox->setCurrentIndex(m_pIecCfgSysParas->m_nPkgSendType);

	m_pParasSetSelCombox->setCurrentIndex(!m_pIecCfgSysParas->m_nPrimParas);
	m_pPkgSendSelCombox->setCurrentIndex(!m_pIecCfgSysParas->m_nPrimOutput);
	CString strID;
	CIecCfgPrimRate *pPrimRate = NULL;

	for (int nIndex = 0;nIndex<IECCFG_MAX_PT_CT_NUM;nIndex++)
	{
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->InitUnit("kV");
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->InitCoverage(1.0,10000,3);
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->InitUnit("V");
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->InitCoverage(1.0,10000,3);

		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->InitUnit("A");
		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->InitCoverage(1.0,10000,3);
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->InitUnit("A");
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->InitCoverage(1.0,10000,3);

		strID.Format(_T("U%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strName = strID;
			pPrimRate->m_strID = strID;
			m_pPrimRates->AddNewChild(pPrimRate);
		}

		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->SetValue(pPrimRate->m_fPrimValue);
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->SetValue(pPrimRate->m_fSecondValue);

		strID.Format(_T("I%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strName = strID;
			pPrimRate->m_strID = strID;
			m_pPrimRates->AddNewChild(pPrimRate);
		}

		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->SetValue(pPrimRate->m_fPrimValue);
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->SetValue(pPrimRate->m_fSecondValue);
	}

	UpdateRates_EditState();
}

void QSttSysParasWidget::SaveData()
{
	m_pPrimRates = m_pIecCfgSysParas->GetPrimRates();
	m_pIecCfgSysParas->m_nPkgSendType = m_pPkgSendTypeComboBox->currentIndex();

	m_pIecCfgSysParas->m_nPrimParas = (!m_pParasSetSelCombox->currentIndex());
	m_pIecCfgSysParas->m_nPrimOutput = (!m_pPkgSendSelCombox->currentIndex());

	CString strID;
	CIecCfgPrimRate *pPrimRate = NULL;

	for (int nIndex = 0;nIndex<IECCFG_MAX_PT_CT_NUM;nIndex++)
	{
		strID.Format(_T("U%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strName = strID;
			pPrimRate->m_strID = strID;
			m_pPrimRates->AddNewChild(pPrimRate);
		}

		pPrimRate->m_fPrimValue = m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->GetValue();
		pPrimRate->m_fSecondValue = m_oTransRadioGroup[nIndex].pSecondVolLineEdit->GetValue();

		strID.Format(_T("I%d-abc"),nIndex+1);
		pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strName = strID;
			pPrimRate->m_strID = strID;
			m_pPrimRates->AddNewChild(pPrimRate);
		}

		pPrimRate->m_fPrimValue = m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->GetValue();
		pPrimRate->m_fSecondValue = m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->GetValue();
	}
}

void QSttSysParasWidget::SetScaleEnable(bool _bEnable)
{
	m_pTransRadios_GroupBox->setEnabled(_bEnable);
}


void QSttSysParasWidget::slot_PkgSendTypeChanged(int index)
{
}

void QSttSysParasWidget::slot_ParasSetSelChanged(int index)
{
	ASSERT(m_pIecCfgSysParas);
	m_pIecCfgSysParas->m_nPrimParas = (index == 0);
	UpdateRates_EditState();
}

void QSttSysParasWidget::slot_PkgSendSelChanged(int index)
{
	ASSERT(m_pIecCfgSysParas);
	m_pIecCfgSysParas->m_nPrimOutput = (index == 0);
	UpdateRates_EditState();
}

void QSttSysParasWidget::slot_OtherSetPushBtnClicked()
{
	QSttIecSysParasOtherSetDialog oSttOtherSetDlg;

// 	m_oIecFont.setFamily("Tahoma");
// 	m_oIecFont.setPixelSize(18);
// 	m_oIecFont.setBold(0);

	oSttOtherSetDlg.setFont(font());
	oSttOtherSetDlg.InitData(m_pIecCfgSysParas->GetFiberParas());
	oSttOtherSetDlg.exec();
}

void QSttSysParasWidget::slot_lne_Clicked()
{
	QFloatLineEdit* f_sender = qobject_cast<QFloatLineEdit*>(sender());
	
	/*
	int n = 0;
	if (f_sender->text().contains("V"))
	{
		n = 0;
	}
	else
	{	
		n = 1;
	}
	*/

	CString strValue;
	strValue.Format("%.3f",f_sender->GetValue());
	GetWidgetBoard_DigitData(4, strValue,f_sender, this);
// 	f_sender->setText(strValue);
// 	f_sender->SetEditFinished();

	/*
	WidgetKeyboardV_Digit dlg(n,this);
	CString strTemp;
	strTemp.Format("%.3f",f_sender->GetValue());
	dlg.m_strEditInfo = strTemp;
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		f_sender->setText(dlg.m_strEditInfo);
	}

	f_sender->SetEditFinished();
	*/
}

void QSttSysParasWidget::UpdateRates_EditState()
{
	BOOL bShow = TRUE;

	if (m_pIecCfgSysParas->m_nPrimOutput == m_pIecCfgSysParas->m_nPrimParas)//如果参数设置与实际输出一致,则不需要设置变比
	{
		bShow = FALSE;
	}

	for (int nIndex = 0;nIndex<IECCFG_MAX_PT_CT_NUM;nIndex++)
	{
		m_oTransRadioGroup[nIndex].pPrimaryVolLineEdit->setEnabled(bShow);
		m_oTransRadioGroup[nIndex].pSecondVolLineEdit->setEnabled(bShow);

		m_oTransRadioGroup[nIndex].pPrimaryCurrLineEdit->setEnabled(bShow);
		m_oTransRadioGroup[nIndex].pSecondCurrLineEdit->setEnabled(bShow);
	}
}


