#include "SttIecSysCfgWidget.h"

#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
//#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"

QSttIecSysCfgWidget::QSttIecSysCfgWidget(QFont oIecFont,QWidget *parent)
	: QWidget(parent)
{
	m_pIecCfgTabWidget = NULL;
	m_pIecCfgSysParas = NULL;
	m_oIecFont = oIecFont;
	setFont(m_oIecFont);
	InitUI();
	SetIecSysCfgFont();

}

QSttIecSysCfgWidget::~QSttIecSysCfgWidget()
{

}

void QSttIecSysCfgWidget::SetIecSysCfgFont()
{
	m_pPkgSendSelCombox->setFont(*g_pSttGlobalFont);
	m_pParasSetSelCombox->setFont(*g_pSttGlobalFont);
	m_pPkgSendTypeComboBox->setFont(*g_pSttGlobalFont);
	m_pIecCfgTabWidget->setFont(*g_pSttGlobalFont);
	m_pPacketSending_Label->setFont(*g_pSttGlobalFont);
	m_pPacketSendingMode_Label->setFont(*g_pSttGlobalFont);
	m_pParasSet_Label->setFont(* g_pSttGlobalFont);
}

void QSttIecSysCfgWidget::InitData(CIecCfgSysParas* pIecCfgSysParas)
{
	m_pIecCfgSysParas = pIecCfgSysParas;
	m_pPkgSendTypeComboBox->setCurrentIndex(m_pIecCfgSysParas->m_nPkgSendType);
	m_pParasSetSelCombox->setCurrentIndex(!m_pIecCfgSysParas->m_nPrimParas);
	m_pPkgSendSelCombox->setCurrentIndex(!m_pIecCfgSysParas->m_nPrimOutput);

	m_pSmvOutPrimRateWidget->InitData(pIecCfgSysParas);
	m_pSmvInPrimRateWidget->InitData(pIecCfgSysParas);
	m_pFibersWidget->InitData(pIecCfgSysParas);
	m_pFibersInWidget->InitData(pIecCfgSysParas);

	UpdateRates_EditState();
}

void QSttIecSysCfgWidget::SaveData()
{
	m_pIecCfgSysParas->m_nPkgSendType = m_pPkgSendTypeComboBox->currentIndex();
	m_pIecCfgSysParas->m_nPrimParas = (!m_pParasSetSelCombox->currentIndex());
	m_pIecCfgSysParas->m_nPrimOutput = (!m_pPkgSendSelCombox->currentIndex());
	m_pSmvOutPrimRateWidget->SaveData();
	m_pSmvInPrimRateWidget->SaveData();
	m_pFibersWidget->SaveData();

	m_pFibersInWidget->SaveData();
}

void QSttIecSysCfgWidget::InitUI()
{
	m_pMainVLayout = new QVBoxLayout(this);
	m_pIecCfgTabWidget = new QTabWidget(this);
	m_pSmvOutPrimRateWidget = new QSttIecSysCfgChildWidget(m_oIecFont,STT_IECSYS_WIDGET_TYPE_SmvOutRate);
	m_pSmvInPrimRateWidget = new QSttIecSysCfgChildWidget(m_oIecFont,STT_IECSYS_WIDGET_TYPE_SmvInRate);
	m_pFibersWidget = new QSttIecSysCfgChildWidget(m_oIecFont,STT_IECSYS_WIDGET_TYPE_FiberSet);
	m_pFibersInWidget = new QSttIecSysCfgChildWidget(m_oIecFont,STT_IECSYS_WIDGET_TYPE_FiberInSet);

	CString strTemp;
	//strTemp = _T("发送变比设置");
	m_pIecCfgTabWidget->addTab(m_pSmvOutPrimRateWidget,g_sLangTxt_IEC_Sendratio);
	//strTemp = _T("接收变比设置");
	m_pIecCfgTabWidget->addTab(m_pSmvInPrimRateWidget,g_sLangTxt_IEC_Receiveratio);
	//strTemp = _T("光口设置");
	m_pIecCfgTabWidget->addTab(m_pFibersWidget,g_sLangTxt_IEC_FiberOutSet);
	
	if (g_oLocalSysPara.m_nTotalSTRecv_Num > 0)
	{
	m_pIecCfgTabWidget->addTab(m_pFibersInWidget,g_sLangTxt_IEC_FiberInSet);
	}

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

	m_pPkgSendType_HBoxLayout = new QHBoxLayout;
// 	m_pPkgSendType_FormLayout = new QFormLayout;
// 	m_pParasSetSel_FormLayout = new QFormLayout;
// 	m_pPkgSendSel_FormLayout = new QFormLayout;

	

// 	m_pPkgSendType_HBoxLayout->addLayout(m_pPkgSendType_FormLayout);
// 	m_pPkgSendType_HBoxLayout->addLayout(m_pParasSetSel_FormLayout);
// 	m_pPkgSendType_HBoxLayout->addLayout(m_pPkgSendSel_FormLayout);
	//	m_pPkgSendType_HBoxLayout->addStretch();
	//	m_pSencondSyn_FormLayout = new QFormLayout;

	xlang_GetLangStrByFile(strTemp,"IEC_PacketSendingMode");
	m_pPacketSendingMode_Label = new QLabel(strTemp);
	m_pPkgSendType_HBoxLayout->addWidget(m_pPacketSendingMode_Label);
	m_pPkgSendType_HBoxLayout->addWidget(m_pPkgSendTypeComboBox);
// 	m_pPkgSendType_FormLayout->addRow(m_pPacketSendingMode_Label, m_pPkgSendTypeComboBox);

	xlang_GetLangStrByFile(strTemp,"Gradient_ParaSet");
	m_pParasSet_Label = new QLabel(strTemp);
	m_pPkgSendType_HBoxLayout->addWidget(m_pParasSet_Label);
	m_pPkgSendType_HBoxLayout->addWidget(m_pParasSetSelCombox);
// 	m_pParasSetSel_FormLayout->addRow(m_pParasSet_Label, m_pParasSetSelCombox);
	//m_pParasSetSel_FormLayout->addRow(tr("参数设置:"), m_pParasSetSelCombox);

	xlang_GetLangStrByFile(strTemp,"IEC_PacketSending");
	m_pPacketSending_Label = new QLabel(strTemp);
	m_pPkgSendType_HBoxLayout->addWidget(m_pPacketSending_Label);
	m_pPkgSendType_HBoxLayout->addWidget(m_pPkgSendSelCombox);
// 	m_pPkgSendSel_FormLayout->addRow(m_pPacketSending_Label, m_pPkgSendSelCombox);
	m_pPkgSendType_HBoxLayout->addStretch();


	m_pMainVLayout->addWidget(m_pIecCfgTabWidget);
	m_pMainVLayout->addLayout(m_pPkgSendType_HBoxLayout);
	setLayout(m_pMainVLayout);

	connect(m_pParasSetSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ParasSetSelChanged(int)));
	connect(m_pPkgSendSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PkgSendSelChanged(int)));
}

void QSttIecSysCfgWidget::UpdateRates_EditState()
{
	BOOL bShow = TRUE;

	if (m_pIecCfgSysParas->m_nPrimOutput == m_pIecCfgSysParas->m_nPrimParas)//如果参数设置与实际输出一致,则不需要设置变比
	{
		bShow = FALSE;
	}

	m_pSmvOutPrimRateWidget->SetEnableState(bShow);
//	m_pSmvInPrimRateWidget->setEnabled(bShow);
}

void QSttIecSysCfgWidget::slot_ParasSetSelChanged(int index)
{
	ASSERT(m_pIecCfgSysParas);
	m_pIecCfgSysParas->m_nPrimParas = (index == 0);
	UpdateRates_EditState();
}

void QSttIecSysCfgWidget::slot_PkgSendSelChanged(int index)
{
	ASSERT(m_pIecCfgSysParas);
	m_pIecCfgSysParas->m_nPrimOutput = (index == 0);
	UpdateRates_EditState();
}