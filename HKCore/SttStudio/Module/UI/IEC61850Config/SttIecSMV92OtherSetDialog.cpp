#include "SttIecSMV92OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../SttTestCntrFrameBase.h"

QSttIecSMV92OtherSetDialog::QSttIecSMV92OtherSetDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	m_pMain_VLayout = NULL;
	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pSmvRates_Inner = NULL;
	m_pSmvRates_Extern = NULL;
	m_pSmvRateGrid = NULL;
	InitUI();
}

QSttIecSMV92OtherSetDialog::~QSttIecSMV92OtherSetDialog()
{
	if (m_pSmvRates_Inner != NULL)
	{
		delete m_pSmvRates_Inner;
		m_pSmvRates_Inner = NULL;
	}
}

void QSttIecSMV92OtherSetDialog::InitUI()
{
	resize(550,500);
	this->setFixedWidth(550);
	this->setFixedHeight(500);

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_SetScaleFactor");
	setWindowTitle(strTemp);

	m_pSmvRateGrid = new CIecCfgSmvRateGrid(this);
	m_pSmvRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pSmvRateGrid->setFont(*g_pSttGlobalFont);
	m_pSmvRateGrid->InitGrid();


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
	m_pMain_VLayout->addWidget(m_pSmvRateGrid);
	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttIecSMV92OtherSetDialog::InitData(CIecCfgSmvRates *pSmvRates)
{
	m_pSmvRates_Extern = pSmvRates;
	m_pSmvRates_Inner = (CIecCfgSmvRates*)m_pSmvRates_Extern->Clone();
	m_pSmvRateGrid->ShowDatas(m_pSmvRates_Inner);
}

void QSttIecSMV92OtherSetDialog::SaveData()
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
		}
	}
}

void QSttIecSMV92OtherSetDialog::slot_OKClicked()
{
	ExitHideKeyboardWidget();
	SaveData();
	close();
}

void QSttIecSMV92OtherSetDialog::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}


