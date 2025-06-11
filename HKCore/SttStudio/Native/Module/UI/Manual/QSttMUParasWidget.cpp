#include "QSttMUParasWidget.h"
#include "../../../Module/XLangResource_Native.h"
#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/API/GlobalConfigApi.h"
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
	m_bHasInitFinished = false;
}

void QSttMUParasWidget::showEvent(QShowEvent *event)
{
	if (!m_bHasInitFinished)
	{
	InitUI();
		m_bHasInitFinished = true;
	}
	QWidget::showEvent(event);
}

QSttMUParasWidget::~QSttMUParasWidget()
{

}

void QSttMUParasWidget::InitUI()
{
	CString strTemp;
/////////////////////////////////////////��һ�У������߼���PPS����//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//strTemp = "��ֵ��";
	m_pInterPolMethodRadio = new QRadioButton(g_sLangTxt_State_Interpolation,this); // ��ֵ�� lcq 3.13
	//strTemp = "ͬ����";
	m_pSynchMethodRadio = new QRadioButton(g_sLangTxt_State_Synchronousmethod,this);// ͬ���� lcq 3.13

	m_pTestMethodHBoxLayout = new QHBoxLayout;
	m_pInterPolMethodRadio->setFont(*g_pSttGlobalFont);
	m_pSynchMethodRadio->setFont(*g_pSttGlobalFont);
	m_pTestMethodHBoxLayout->addWidget(m_pInterPolMethodRadio);
	m_pTestMethodHBoxLayout->addWidget(m_pSynchMethodRadio);
	//strTemp = "�����߼�";
	m_pTestMethodGroupBox = new QSttGroupBox(g_sLangTxt_State_TestLogic,this); // �����߼� lcq 3.13
	m_pTestMethodGroupBox->setLayout(m_pTestMethodHBoxLayout);

	//strTemp = "��������Ч";
	m_pRisingEdgeRadio = new QRadioButton(g_sLangTxt_State_Risingedgeeffective);// ��������Ч lcq 3.13
	//strTemp = "�½�����Ч";
	m_pFallingEdgeRadio = new QRadioButton(g_sLangTxt_State_Downedgeeffective);// �½�����Ч lcq 3.13
	//strTemp = "��PPS";
	m_pNoPPSEdgeRadio = new QRadioButton(g_sLangTxt_State_NOPPS);// ��PPS lcq 3.13

	m_pPPS_SetHBoxLayout = new QHBoxLayout;
	m_pPPS_SetHBoxLayout->addWidget(m_pRisingEdgeRadio);
	m_pPPS_SetHBoxLayout->addWidget(m_pFallingEdgeRadio);
	m_pPPS_SetHBoxLayout->addWidget(m_pNoPPSEdgeRadio);
	//strTemp = "PPS����";
	m_pPPS_SetGroupBox = new QSttGroupBox(g_sLangTxt_State_PPSsettings);// PPS���� lcq 3.13

	m_pPPS_SetGroupBox->setLayout(m_pPPS_SetHBoxLayout);
	m_pPPS_SetGroupBox->setVisible(false);

	m_pFirstHBoxLayout = new QHBoxLayout;
	m_pFirstHBoxLayout->addWidget(m_pTestMethodGroupBox);
	m_pFirstHBoxLayout->addWidget(m_pPPS_SetGroupBox);

	m_pTestMethodGroupBox->setFont(*g_pSttGlobalFont);
//  	m_pInterPolMethodRadio->setFont(*g_pSttGlobalFont);
//  	m_pSynchMethodRadio->setFont(*g_pSttGlobalFont);

/////////////////////////////////////////�ڶ��У���������//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	//strTemp = "��������";
	m_pOutSetGroupBox = new QSttGroupBox(g_sLangTxt_Manual_OutSetting );

	m_pOutSetGroupBox->setLayout(m_pOutSetHBoxLayout);
	m_pOutSetGroupBox->setFont(*g_pSttGlobalFont);

/////////////////////////////////////////�����У���������//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//strTemp = "���ѹ(V):";
	m_pUn_Label = new QLabel(g_sLangTxt_Report_Vnom);//���ѹ lcq 3.13
	m_pUn_FloatLineEdit = new QFloatLineEdit;
	//strTemp = "�����(A):";
	m_pIn_Label = new QLabel(g_sLangTxt_Native_EDCurrent);//����� lcq 3.13
	m_pIn_FloatLineEdit = new QFloatLineEdit;
	m_pOtherSetHBoxLayout = new QHBoxLayout;
	m_pOtherSetHBoxLayout->addWidget(m_pUn_Label);
	m_pOtherSetHBoxLayout->addWidget(m_pUn_FloatLineEdit);
	m_pOtherSetHBoxLayout->addWidget(m_pIn_Label);
	m_pOtherSetHBoxLayout->addWidget(m_pIn_FloatLineEdit);


	//strTemp = "��������";
	m_pOtherSetGroupBox = new QSttGroupBox(g_sLangTxt_State_Othersettings);//�������� lcq 3.13

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


