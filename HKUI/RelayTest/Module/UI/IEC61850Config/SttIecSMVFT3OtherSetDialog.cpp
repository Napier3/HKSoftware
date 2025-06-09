#include "SttIecSMVFT3OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../SttTestCntrFrameBase.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../XLangResource_Native.h"
#include "../../SttSystemConfig/SttSystemConfig.h"

QSttIecSMVFT3OtherSetDialog::QSttIecSMVFT3OtherSetDialog(BOOL bIsFT3In,QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pSmvRates_Inner = NULL;
	m_pSmvRates_Extern = NULL;
	m_pIecCfgSMVFT3VolGrid = NULL;
	m_pIecCfgSMVFT3CurGrid = NULL;
	m_bIsFT3In = bIsFT3In;
	InitUI();
}

QSttIecSMVFT3OtherSetDialog::~QSttIecSMVFT3OtherSetDialog()
{
	if (m_pSmvRates_Inner != NULL)
	{
		delete m_pSmvRates_Inner;
		m_pSmvRates_Inner = NULL;
	}
}

void QSttIecSMVFT3OtherSetDialog::InitUI()
{
	resize(550,500);
	this->setFixedWidth(550);
	this->setFixedHeight(500);

	CString strTemp;

	setWindowTitle(/* _T("码值设置") */g_sLangTxt_Native_codesSetting);

	m_pIecCfgSMVFT3VolGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_FT3_VOL_GRID);

	//2024-5-30 wuxinyi 修改订阅发布都需要测量码值设置
// 	if (m_bIsFT3In)
// 	{
		m_pIecCfgSMVFT3CurGrid = new CIecCfgProtMaesCurrCodeSetGrid(this);
// 	} 
// 	else
// 	{
// 		m_pIecCfgSMVFT3CurGrid = new CIecCfgSMVFT3DCOtherSetGrid(this, IECCFGSMV_FT3_CUR_GRID);
// 	}

	m_pIecCfgSMVFT3VolGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgSMVFT3VolGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgSMVFT3VolGrid->InitGrid();
	m_pIecCfgSMVFT3CurGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgSMVFT3CurGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgSMVFT3CurGrid->InitGrid();

	m_pOK_PushButton = new QPushButton(this);
	//m_pOK_PushButton->setText(tr("确定"));
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	//m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
	
	m_pCancel_PushButton = new QPushButton(this);
	//m_pCancel_PushButton->setText(tr("取消"));
	xlang_SetLangStrToWidget(m_pCancel_PushButton, "sCancel", XLang_Ctrls_QPushButton);
	//m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));
	m_pOK_CancelHLayout = new QHBoxLayout;
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
	m_pOK_CancelHLayout->addSpacing(20);
	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
	m_pOK_CancelHLayout->addStretch();
	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main

	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pIecCfgSMVFT3VolGrid);
	m_pMain_VLayout->addWidget(m_pIecCfgSMVFT3CurGrid);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}



void QSttIecSMVFT3OtherSetDialog::InitData(CIecCfgSmvRates *pSmvRates)
	{
	m_pSmvRates_Extern = pSmvRates;
	m_pSmvRates_Inner = (CIecCfgSmvRates*)m_pSmvRates_Extern->Clone();
	m_pIecCfgSMVFT3VolGrid->ShowDatas(m_pSmvRates_Inner);
	m_pIecCfgSMVFT3CurGrid->ShowDatas(m_pSmvRates_Inner);
	}


void QSttIecSMVFT3OtherSetDialog::SaveData()
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

			if ((g_oSttSystemConfig.GetFt3PrimCodeValue()) && (pSmvRateInner->m_strID.Find("U")!= -1))
			{
				pSmvRateInner->m_fPrimValue = pSmvRateInner->m_fPrimValue / 1000;
			}
			
			pSmvRateExtern->m_fPrimValue = pSmvRateInner->m_fPrimValue;
			pSmvRateExtern->m_strAliasName = pSmvRateInner->m_strAliasName;
		}
	}
}

void QSttIecSMVFT3OtherSetDialog::slot_OKClicked()
{
	ExitHideKeyboardWidget();
	SaveData();
	accept();
}

void QSttIecSMVFT3OtherSetDialog::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}

