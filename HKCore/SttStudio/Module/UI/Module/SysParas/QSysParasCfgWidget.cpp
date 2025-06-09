#include "QSysParasCfgWidget.h"

QSysParasCfgWidget::QSysParasCfgWidget(CIecCfgSysParas* pIecCfgSysParas, QWidget *parent)
: QWidget(parent)
{
	m_pCfgSysParas = pIecCfgSysParas;
	m_pSmvOutPrimRateWidget = NULL;
	m_pParasSetSelCombox = NULL;
	m_pParasSet_Label = NULL;
	m_pPkgSendType_HBoxLayout = NULL;
	m_pMainVLayout = NULL;
	m_pIecCfgTabWidget = NULL;
	InitUI();
	InitConnection();
	InitData();
}

QSysParasCfgWidget::~QSysParasCfgWidget()
{

}

void QSysParasCfgWidget::InitUI()
{
	m_pSmvOutPrimRateWidget = new QSttIecSysCfgChildWidget(font(),STT_IECSYS_WIDGET_TYPE_SmvOutRate);
	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"Gradient_ParaSet");
	m_pParasSet_Label = new QLabel(strTemp);		//参数设置
	m_pParasSetSelCombox = new QComboBox;
	xlang_GetLangStrByFile(strTemp,"IEC_OnceValue");//一次值
	m_pParasSetSelCombox->addItem(strTemp);
	xlang_GetLangStrByFile(strTemp,"IEC_TwiceValue");//二次值
	m_pParasSetSelCombox->addItem(strTemp);

	m_pPkgSendType_HBoxLayout = new QHBoxLayout;
	m_pPkgSendType_HBoxLayout->addWidget(m_pParasSet_Label);
	m_pPkgSendType_HBoxLayout->addWidget(m_pParasSetSelCombox);
	m_pPkgSendType_HBoxLayout->addStretch();

	m_pIecCfgTabWidget = new QTabWidget(this);
	m_pIecCfgTabWidget->addTab(m_pSmvOutPrimRateWidget, /*_T("发送变比设置")*/g_sLangTxt_IEC_Sendratio);
	m_pMainVLayout = new QVBoxLayout(this);
	m_pMainVLayout->addWidget(m_pIecCfgTabWidget);
	m_pMainVLayout->addLayout(m_pPkgSendType_HBoxLayout);
	UpdateRates_EditState();
}

void QSysParasCfgWidget::InitConnection()
{
	connect(m_pParasSetSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ParasSetSelChanged(int)));
}

void QSysParasCfgWidget::InitData()
{
	m_pParasSetSelCombox->setCurrentIndex(!m_pCfgSysParas->m_nPrimParas);
	m_pSmvOutPrimRateWidget->InitData(m_pCfgSysParas);
}

void QSysParasCfgWidget::UpdateRates_EditState()
{
	BOOL bShow = TRUE;
	if (m_pCfgSysParas->m_nPrimOutput == m_pCfgSysParas->m_nPrimParas)//如果参数设置与实际输出一致,则不需要设置变比
	{
		bShow = FALSE;
	}

	m_pSmvOutPrimRateWidget->SetEnableState(bShow);
}

void QSysParasCfgWidget::slot_ParasSetSelChanged(int nIndex)
{
	ASSERT(m_pCfgSysParas);
	m_pCfgSysParas->m_nPrimParas = (nIndex == 0);
	UpdateRates_EditState();
}

void QSysParasCfgWidget::SaveDatas()
{
	CIecCfgPrimRates* pPrimRates = m_pCfgSysParas->GetPrimRates();
	m_pCfgSysParas->m_nPrimParas = (!m_pParasSetSelCombox->currentIndex());
	m_pSmvOutPrimRateWidget->SaveData();
}
