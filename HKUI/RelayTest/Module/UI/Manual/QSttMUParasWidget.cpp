#include "QSttMUParasWidget.h"
#include "../../../Module/XLangResource_Native.h"
#include "../../../../Module/OSInterface/OSInterface.h"
#include "../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Controls/SttCheckBox.h"

QSttMUParasWidget::QSttMUParasWidget(BOOL *pbTmtParaChanged,QWidget *parent)
	: QWidget(parent)
{
	m_pbTmtParaChanged = pbTmtParaChanged;
	m_pMainVBoxLayout = NULL;
	m_pTestMethodGroupBox = NULL;
	m_pFirstHBoxLayout = NULL;
	m_pTestMethodHBoxLayout = NULL;
	m_pInterPolMethodRadio = NULL;
	m_pSynchMethodRadio = NULL;
	InitUI();
}

QSttMUParasWidget::~QSttMUParasWidget()
{

}

void QSttMUParasWidget::InitUI()
{
	CString strTemp;
/////////////////////////////////////////第一行：测试逻辑、PPS设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//strTemp = "插值法";
	m_pInterPolMethodRadio = new QRadioButton(g_sLangTxt_State_Interpolation,this); // 插值法 lcq 3.13
	//strTemp = "同步法";
	m_pSynchMethodRadio = new QRadioButton(g_sLangTxt_State_Synchronousmethod,this);// 同步法 lcq 3.13

	m_pTestMethodHBoxLayout = new QHBoxLayout;
	m_pInterPolMethodRadio->setFont(*g_pSttGlobalFont);
	m_pSynchMethodRadio->setFont(*g_pSttGlobalFont);
	m_pTestMethodHBoxLayout->addWidget(m_pInterPolMethodRadio);
	m_pTestMethodHBoxLayout->addWidget(m_pSynchMethodRadio);
	//strTemp = "测试逻辑";
	m_pTestMethodGroupBox = new QSttGroupBox(g_sLangTxt_State_TestLogic,this); // 测试逻辑 lcq 3.13
	m_pTestMethodGroupBox->setLayout(m_pTestMethodHBoxLayout);

	//strTemp = "上升沿有效";
	m_pRisingEdgeRadio = new QRadioButton(g_sLangTxt_State_Risingedgeeffective);// 上升沿有效 lcq 3.13
	//strTemp = "下降沿有效";
	m_pFallingEdgeRadio = new QRadioButton(g_sLangTxt_State_Downedgeeffective);// 下降沿有效 lcq 3.13
	//strTemp = "无PPS";
	m_pNoPPSEdgeRadio = new QRadioButton(g_sLangTxt_State_NOPPS);// 无PPS lcq 3.13

	m_pPPS_SetHBoxLayout = new QHBoxLayout;
	m_pPPS_SetHBoxLayout->addWidget(m_pRisingEdgeRadio);
	m_pPPS_SetHBoxLayout->addWidget(m_pFallingEdgeRadio);
	m_pPPS_SetHBoxLayout->addWidget(m_pNoPPSEdgeRadio);
	//strTemp = "PPS设置";
	m_pPPS_SetGroupBox = new QSttGroupBox(g_sLangTxt_State_PPSsettings);// PPS设置 lcq 3.13

	m_pPPS_SetGroupBox->setLayout(m_pPPS_SetHBoxLayout);
	m_pPPS_SetGroupBox->setVisible(false);

	m_pFirstHBoxLayout = new QHBoxLayout;
	m_pFirstHBoxLayout->addWidget(m_pTestMethodGroupBox);
	m_pFirstHBoxLayout->addWidget(m_pPPS_SetGroupBox);

	m_pTestMethodGroupBox->setFont(*g_pSttGlobalFont);
//  	m_pInterPolMethodRadio->setFont(*g_pSttGlobalFont);
//  	m_pSynchMethodRadio->setFont(*g_pSttGlobalFont);

/////////////////////////////////////////第二行：开出设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pOutSetHBoxLayout = new QHBoxLayout;
	CString strOutDesc;
	xlang_GetLangStrByFile(strOutDesc, "Native_BoutX");

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		strTemp = strOutDesc;
		strTemp.AppendFormat("%d",nIndex+1);
		m_pOutCheckBox[nIndex] = new QSttCheckBox(strTemp);
		m_pOutSetHBoxLayout->addWidget(m_pOutCheckBox[nIndex]);
	}

	//strTemp = "开出设置";
	m_pOutSetGroupBox = new QSttGroupBox(g_sLangTxt_Manual_OutSetting );

	m_pOutSetGroupBox->setLayout(m_pOutSetHBoxLayout);
	m_pOutSetGroupBox->setFont(*g_pSttGlobalFont);

/////////////////////////////////////////第三行：其它设置//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//strTemp = "额定电压(V):";
	m_pUn_Label = new QLabel(g_sLangTxt_Report_Vnom);//额定电压 lcq 3.13
	m_pUn_FloatLineEdit = new QFloatLineEdit;
	//strTemp = "额定电流(A):";
	m_pIn_Label = new QLabel(g_sLangTxt_Native_EDCurrent);//额定电流 lcq 3.13
	m_pIn_FloatLineEdit = new QFloatLineEdit;
	m_pOtherSetHBoxLayout = new QHBoxLayout;
	m_pOtherSetHBoxLayout->addWidget(m_pUn_Label);
	m_pOtherSetHBoxLayout->addWidget(m_pUn_FloatLineEdit);
	m_pOtherSetHBoxLayout->addWidget(m_pIn_Label);
	m_pOtherSetHBoxLayout->addWidget(m_pIn_FloatLineEdit);


	//strTemp = "其它设置";
	m_pOtherSetGroupBox = new QSttGroupBox(g_sLangTxt_State_Othersettings);//其它设置 lcq 3.13

	m_pOtherSetGroupBox->setLayout(m_pOtherSetHBoxLayout);

	m_pMainVBoxLayout = new QVBoxLayout(this);
	m_pMainVBoxLayout->addLayout(m_pFirstHBoxLayout);
	m_pMainVBoxLayout->addWidget(m_pOutSetGroupBox);
	m_pMainVBoxLayout->addWidget(m_pOtherSetGroupBox);
	m_pMainVBoxLayout->addStretch();
	setLayout(m_pMainVBoxLayout);
}

void QSttMUParasWidget::UpdateUI()
{
	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setVisible(g_nBoutCount>nIndex);
	}
}

void QSttMUParasWidget::InitData(tmt_ManualParas *pManualParas)
{
	DisConnectAllSigSlot();
	m_pManualParas = pManualParas;
	m_pInterPolMethodRadio->setChecked(pManualParas->m_oMuParas.nAlgorithmType == 0);
	m_pSynchMethodRadio->setChecked(pManualParas->m_oMuParas.nAlgorithmType == 1);

	m_pRisingEdgeRadio->setChecked(pManualParas->m_oMuParas.nPPS_SetType == 0);
	m_pFallingEdgeRadio->setChecked(pManualParas->m_oMuParas.nPPS_SetType == 1);
	m_pNoPPSEdgeRadio->setChecked(pManualParas->m_oMuParas.nPPS_SetType == 2);

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		m_pOutCheckBox[nIndex]->setChecked(pManualParas->m_binOut[nIndex].nState);
		m_pOutCheckBox[nIndex]->setVisible(g_nBoutCount>nIndex);
	}

	m_pUn_FloatLineEdit->InitCoverage(0,130,3);
	m_pUn_FloatLineEdit->SetValue(&pManualParas->m_oMuParas.fUn);
	m_pIn_FloatLineEdit->InitCoverage(0,20,3);
	m_pIn_FloatLineEdit->SetValue(&pManualParas->m_oMuParas.fIn);
	m_pOtherSetGroupBox->setVisible(pManualParas->m_nFuncType == TMT_MANU_FUNC_TYPE_MUFirstCycleWave);
	ConnectAllSigSlot();
}

void QSttMUParasWidget::ConnectAllSigSlot()
{
	connect(m_pInterPolMethodRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnTestMethodRadioChanged(bool)));
	connect(m_pSynchMethodRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnTestMethodRadioChanged(bool)));

	connect(m_pRisingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	connect(m_pFallingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	connect(m_pNoPPSEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));

	connect(m_pUn_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnUnEditChanged()));
	connect(m_pIn_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnInEditChanged()));

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		connect(m_pOutCheckBox[nIndex], SIGNAL(clicked()), this, SLOT(slot_OnOutCheckChanged()));
	}
}

void QSttMUParasWidget::DisConnectAllSigSlot()
{
	disconnect(m_pInterPolMethodRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnTestMethodRadioChanged(bool)));
	disconnect(m_pSynchMethodRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnTestMethodRadioChanged(bool)));

	disconnect(m_pRisingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	disconnect(m_pFallingEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));
	disconnect(m_pNoPPSEdgeRadio, SIGNAL(toggled(bool)), this, SLOT(slot_OnPPSSetRadioChanged(bool)));

	disconnect(m_pUn_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnUnEditChanged()));
	disconnect(m_pIn_FloatLineEdit, SIGNAL(clicked()), this, SLOT(slot_OnInEditChanged()));

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		disconnect(m_pOutCheckBox[nIndex], SIGNAL(clicked()), this, SLOT(slot_OnOutCheckChanged()));
	}
}

void QSttMUParasWidget::slot_OnTestMethodRadioChanged(bool bValue)
{
	if (!bValue)
	{
		return;
	}

	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());

	if (pRadioBtn == m_pInterPolMethodRadio)
	{
		m_pManualParas->m_oMuParas.nAlgorithmType = 0;
	}
	else if (pRadioBtn == m_pSynchMethodRadio)
	{
		m_pManualParas->m_oMuParas.nAlgorithmType = 1;
	}

	*m_pbTmtParaChanged = TRUE;
}

void QSttMUParasWidget::slot_OnPPSSetRadioChanged(bool bValue)
{
	if (!bValue)
	{
		return;
	}

	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());

	if (pRadioBtn == m_pRisingEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 0;
	}
	else if (pRadioBtn == m_pFallingEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 1;
	}
	else if (pRadioBtn == m_pNoPPSEdgeRadio)
	{
		m_pManualParas->m_oMuParas.nPPS_SetType = 2;
	}

	*m_pbTmtParaChanged = TRUE;
	emit sig_updataParas();
}

void QSttMUParasWidget::slot_OnOutCheckChanged()
{
	QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(sender());

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		if (pCheckBox == m_pOutCheckBox[nIndex])
		{
			m_pManualParas->m_binOut[nIndex].nState = pCheckBox->isChecked();
			*m_pbTmtParaChanged = TRUE;
			emit sig_updataParas();
			break;
		}
	}
}

void QSttMUParasWidget::slot_OnUnEditChanged()
{
	CString strValue;
	float fValue = m_pUn_FloatLineEdit->GetValue();
	strValue.Format("%.03f",fValue);

	GetWidgetBoard_DigitData(4,strValue,m_pUn_FloatLineEdit,this);
	fValue = CString_To_double(strValue);
// 	m_pUn_FloatLineEdit->SetValue(fValue);
// 	m_pUn_FloatLineEdit->SetEditFinished();
	*m_pbTmtParaChanged = TRUE;
}

void QSttMUParasWidget::slot_OnInEditChanged()
{
	CString strValue;
	float fValue = m_pIn_FloatLineEdit->GetValue();
	strValue.Format("%.03f",fValue);

	GetWidgetBoard_DigitData(4,strValue,m_pIn_FloatLineEdit,this);
	fValue = CString_To_double(strValue);
// 	m_pIn_FloatLineEdit->SetValue(fValue);
// 	m_pIn_FloatLineEdit->SetEditFinished();
	*m_pbTmtParaChanged = TRUE;
}


