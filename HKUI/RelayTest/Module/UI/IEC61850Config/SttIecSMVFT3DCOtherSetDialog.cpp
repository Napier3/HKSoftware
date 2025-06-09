#include "SttIecSMVFT3DCOtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"

QSttIecSMVFT3DCOtherSetDialog::QSttIecSMVFT3DCOtherSetDialog(QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pSmvRates_Inner = NULL;
	m_pSmvRates_Extern = NULL;

	m_pDcAcTabWidget = NULL;
	m_pDcVBoxLayout = NULL;
	m_pAcVBoxLayout = NULL;
	m_pDcWidget = NULL;
	m_pAcWidget = NULL;

	
	m_pIecCfgSMVFT3DCVolGrid = NULL;
	m_pIecCfgSMVFT3DCCurGrid = NULL;
	m_pIecCfgSMVFT3ACVolGrid = NULL;
	m_pIecCfgSMVFT3AcCurGrid = NULL;
	
	InitUI();
}

QSttIecSMVFT3DCOtherSetDialog::~QSttIecSMVFT3DCOtherSetDialog()
{
	if (m_pSmvRates_Inner != NULL)
	{
		delete m_pSmvRates_Inner;
		m_pSmvRates_Inner = NULL;
	}
}


void QSttIecSMVFT3DCOtherSetDialog::InitUI()
{
	resize(550,500);
	this->setFixedWidth(550);
	this->setFixedHeight(500);

	CString strTemp;

	setWindowTitle(/* _T("码值设置") */g_sLangTxt_Native_codesSetting);

	m_pIecCfgSMVFT3DCVolGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_DCFT3_DCVOL_GRID);
	m_pIecCfgSMVFT3DCCurGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_DCFT3_DCCUR_GRID);
	m_pIecCfgSMVFT3ACVolGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_DCFT3_ACVOL_GRID);
	m_pIecCfgSMVFT3AcCurGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_DCFT3_ACCUR_GRID);
	m_pIecCfgSMVFT3DCVolGrid->InitGrid();
	m_pIecCfgSMVFT3DCCurGrid->InitGrid();
	m_pIecCfgSMVFT3ACVolGrid->InitGrid();
	m_pIecCfgSMVFT3AcCurGrid->InitGrid();
	

	m_pOK_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	m_pCancel_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);
	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->addSpacing(20);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);

	m_pDcAcTabWidget = new QTabWidget;
	m_pDcVBoxLayout = new QVBoxLayout(m_pDcWidget);
	m_pAcVBoxLayout = new QVBoxLayout(m_pAcWidget);
	m_pDcWidget = new QWidget(m_pDcAcTabWidget);
	m_pAcWidget = new QWidget(m_pDcAcTabWidget);
	m_pDcVBoxLayout->addWidget(m_pIecCfgSMVFT3DCVolGrid);
	m_pDcVBoxLayout->addWidget(m_pIecCfgSMVFT3DCCurGrid);
	m_pAcVBoxLayout->addWidget(m_pIecCfgSMVFT3ACVolGrid);
	m_pAcVBoxLayout->addWidget(m_pIecCfgSMVFT3AcCurGrid);

	m_pDcAcTabWidget->addTab(m_pDcWidget, /* "?直流部分" */g_sLangTxt_Native_DCPart);
	m_pDcAcTabWidget->addTab(m_pAcWidget, /* "交流部分" */g_sLangTxt_Native_ACPart);
	
	m_pDcWidget->setLayout(m_pDcVBoxLayout);
	m_pAcWidget->setLayout(m_pAcVBoxLayout);

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pDcAcTabWidget);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));

}

void QSttIecSMVFT3DCOtherSetDialog::InitData(CIecCfgSmvRates *pSmvRates)
{
	m_pSmvRates_Extern = pSmvRates;
	m_pSmvRates_Inner = (CIecCfgSmvRates*)m_pSmvRates_Extern->Clone();
	m_pIecCfgSMVFT3DCVolGrid->ShowDatas(m_pSmvRates_Inner);
	m_pIecCfgSMVFT3DCCurGrid->ShowDatas(m_pSmvRates_Inner);
	m_pIecCfgSMVFT3ACVolGrid->ShowDatas(m_pSmvRates_Inner);
	m_pIecCfgSMVFT3AcCurGrid->ShowDatas(m_pSmvRates_Inner);

}

void QSttIecSMVFT3DCOtherSetDialog::SaveData()
{
	CIecCfgSmvRate *pSmvRateExtern = NULL;
	CIecCfgSmvRate *pSmvRateInner = NULL;
	POS pos = m_pSmvRates_Extern->GetHeadPosition();

	while(pos)
	{
		pSmvRateExtern = (CIecCfgSmvRate *)m_pSmvRates_Extern->GetNext(pos);
		pSmvRateInner = (CIecCfgSmvRate *)m_pSmvRates_Inner->FindByID(pSmvRateExtern->m_strID);

		if (pSmvRateInner != NULL)
		{
			pSmvRateExtern->m_fRate = pSmvRateInner->m_fRate;
			pSmvRateExtern->m_nCodeValue = pSmvRateInner->m_nCodeValue;
			pSmvRateExtern->m_nMeasCurrCodeValue = pSmvRateInner->m_nMeasCurrCodeValue;
			pSmvRateExtern->m_fPrimValue = pSmvRateInner->m_fPrimValue;
			pSmvRateExtern->m_strAliasName = pSmvRateInner->m_strAliasName;
		}
	}
}

void QSttIecSMVFT3DCOtherSetDialog::slot_OKClicked()
{
	ExitHideKeyboardWidget();
	SaveData();
	accept();
}

void QSttIecSMVFT3DCOtherSetDialog::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}
