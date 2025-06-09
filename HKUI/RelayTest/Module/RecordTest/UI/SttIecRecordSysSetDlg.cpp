#include "SttIecRecordSysSetDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../XLangResource_Native.h"

QSttIecRecordSysSetDlg::QSttIecRecordSysSetDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pMain_VLayout = NULL;
	m_pRadioHLayout = NULL;
//	m_pOK_CancelHLayout = NULL;
	m_pOK_PushButton = NULL;
//	m_pCancel_PushButton = NULL;
	m_pPrimaryValueRadioBtn = NULL;
	m_pSecondValueRadioBtn = NULL;
	m_pSttCapAnalysisConfig = NULL;
	m_pLeft_PrimRateGrid = NULL;
	m_pRight_PrimRateGrid = NULL;
	m_pIecCfgPrimRatesIn = NULL;
	InitUI();
}

QSttIecRecordSysSetDlg::~QSttIecRecordSysSetDlg()
{
	m_oLeftList.RemoveAll();
	m_oRightList.RemoveAll();
}

void QSttIecRecordSysSetDlg::InitUI()
{
	resize(850,420);
	this->setFixedWidth(850);
	this->setFixedHeight(420);
	CString strTemp;
	strTemp = /*_T("变比设置")*/g_sLangTxt_Smv_Rates; //lcq
//	xlang_GetLangStrByFile(strTemp, "Smv_SysSet");
	setWindowTitle(strTemp/*tr("系统设置")*/);

	m_pPT_CT_RatesHLayout = new QHBoxLayout;

	m_pLeft_PrimRateGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_PT,this);
	m_pLeft_PrimRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont/*m_oIecFont*/); // 2022-10-22 sy m_oIecFont修改为*g_pSttGlobalFont
	m_pLeft_PrimRateGrid->setFont(*g_pSttGlobalFont);
	m_pRight_PrimRateGrid = new CIecCfgPrimRateGrid(IECCFG_PRIMRATE_GRIDTYPE_CT,this);
	m_pRight_PrimRateGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pRight_PrimRateGrid->setFont(*g_pSttGlobalFont);
	m_pLeft_PrimRateGrid->InitGrid();
	m_pRight_PrimRateGrid->InitGrid();
	m_pPT_CT_RatesHLayout->addWidget(m_pLeft_PrimRateGrid);
	m_pPT_CT_RatesHLayout->addWidget(m_pRight_PrimRateGrid);

	m_pPrimaryValueRadioBtn = new QRadioButton(tr("显示一次值"));
	xlang_SetLangStrToWidget(m_pPrimaryValueRadioBtn, "Smv_ShowOneValue", XLang_Ctrls_QRadioButton);
	m_pSecondValueRadioBtn = new QRadioButton(tr("显示二次值"));
	xlang_SetLangStrToWidget(m_pSecondValueRadioBtn, "Smv_ShowTwoValue", XLang_Ctrls_QRadioButton);

	m_pRadioHLayout = new QHBoxLayout;
	m_pRadioHLayout->addWidget(m_pPrimaryValueRadioBtn);
	m_pRadioHLayout->addWidget(m_pSecondValueRadioBtn);
	m_pRadioHLayout->addStretch();

	m_pOK_PushButton = new QPushButton(this);
	xlang_SetLangStrToWidget(m_pOK_PushButton, "sOK", XLang_Ctrls_QPushButton);
	m_pRadioHLayout->addWidget(m_pOK_PushButton);

// 	m_pCancel_PushButton = new QPushButton(this);
// 	xlang_SetLangStrToWidget(m_pCancel_PushButton, "Native_Cancel", XLang_Ctrls_QPushButton);
// 	m_pOK_CancelHLayout = new QHBoxLayout;
// 	m_pOK_CancelHLayout->addStretch();
// 	m_pOK_CancelHLayout->addWidget(m_pOK_PushButton);
// 	m_pOK_CancelHLayout->addSpacing(20);
// 	m_pOK_CancelHLayout->addWidget(m_pCancel_PushButton);
// 	m_pOK_CancelHLayout->addStretch();
// 	m_pOK_CancelHLayout->setContentsMargins(3,3,3,3);
// 	m_pOK_CancelHLayout->setDirection(QBoxLayout::LeftToRight);
	//main
	m_pMain_VLayout = new QVBoxLayout(this);
 	m_pMain_VLayout->addLayout(m_pPT_CT_RatesHLayout);
	m_pMain_VLayout->addLayout(m_pRadioHLayout);
//	m_pMain_VLayout->addLayout(m_pOK_CancelHLayout);
}

void QSttIecRecordSysSetDlg::InitData(CCapAnalysisConfig *pCapAnalysisConfig,CIecCfgPrimRatesIn *pIecCfgPrimRatesIn)
{
	m_pSttCapAnalysisConfig = pCapAnalysisConfig;
	m_pIecCfgPrimRatesIn = pIecCfgPrimRatesIn;
	m_oLeftList.RemoveAll();
	m_oRightList.RemoveAll();

	POS pos = pIecCfgPrimRatesIn->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;

	while(pos)
	{
		pCurrObj = pIecCfgPrimRatesIn->GetNext(pos);

		if (pCurrObj->m_strID.Find("U") != -1)
		{
			m_oLeftList.AddTail(pCurrObj);
		} 
		else
		{
			m_oRightList.AddTail(pCurrObj);

		}
	}

	m_pLeft_PrimRateGrid->ShowDatas(&m_oLeftList);
	m_pRight_PrimRateGrid->ShowDatas(&m_oRightList);

// 	m_pPrimaryVolLineEdit->InitUnit("kV");
// 	m_pPrimaryVolLineEdit->InitCoverage(1.0,10000,3);
// 	m_pSecondVolLineEdit->InitUnit("V");
// 	m_pSecondVolLineEdit->InitCoverage(1.0,10000,3);
// 
// 	m_pPrimaryCurrLineEdit->InitUnit("A");
// 	m_pPrimaryCurrLineEdit->InitCoverage(1.0,10000,3);
// 	m_pSecondCurrLineEdit->InitUnit("A");
// 	m_pSecondCurrLineEdit->InitCoverage(1.0,10000,3);

// 	m_pPrimaryVolLineEdit->SetValue(m_pSttCapAnalysisConfig->m_dPT_PrimaryValue);
// 	m_pSecondVolLineEdit->SetValue(m_pSttCapAnalysisConfig->m_dPT_SecondValue);
// 	m_pPrimaryCurrLineEdit->SetValue(m_pSttCapAnalysisConfig->m_dCT_PrimaryValue);
// 	m_pSecondCurrLineEdit->SetValue(m_pSttCapAnalysisConfig->m_dCT_SecondValue);

	if (m_pSttCapAnalysisConfig->m_nShowPrimaryValue)
	{
		m_pPrimaryValueRadioBtn->setChecked(1);
	} 
	else
	{
		m_pSecondValueRadioBtn->setChecked(1);
	}

	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
//	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QSttIecRecordSysSetDlg::SaveData()
{
	m_pSttCapAnalysisConfig->m_nShowPrimaryValue = m_pPrimaryValueRadioBtn->isChecked();
}

void QSttIecRecordSysSetDlg::slot_OKClicked()
{
//	ExitHideKeyboardWidget();
	SaveData();
	accept();
}

void QSttIecRecordSysSetDlg::slot_CancelClicked()
{
//	ExitHideKeyboardWidget();
	close();
}

// void QSttIecRecordSysSetDlg::slot_lne_Clicked()
// {
// 	QFloatLineEdit* f_sender = qobject_cast<QFloatLineEdit*>(sender());
// 
// 	CString strValue;
// 	strValue.Format("%.3f",f_sender->GetValue());
// 	GetWidgetBoard_DigitData(4, strValue,f_sender, (QWidget*)this->parent());
// // 	f_sender->setText(strValue);
// // 	f_sender->SetEditFinished();
// }



