#include "QSysParasCfgWidget_NoGrid.h"

QSysParasCfgWidget_NoGrid::QSysParasCfgWidget_NoGrid(CIecCfgSysParas* pIecCfgSysParas, QWidget *parent)
: QWidget(parent)
{
	m_pCfgSysParas = pIecCfgSysParas;
	m_pPrimRates = NULL;
	m_pTransRadio_VBoxLayout = NULL;
	m_pMainVLayout = NULL;
	m_pPkgSendType_HBoxLayout = NULL;
	m_pParasSetSelCombox = NULL;
	m_pParasSet_Label = NULL;
	InitUI();
	InitConnection();
	InitData();
}

QSysParasCfgWidget_NoGrid::~QSysParasCfgWidget_NoGrid()
{

}

void QSysParasCfgWidget_NoGrid::InitUI()
{
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
	m_pMainVLayout = new QVBoxLayout(this);
	m_pMainVLayout->addLayout(m_pTransRadio_VBoxLayout);
	m_pMainVLayout->addLayout(m_pPkgSendType_HBoxLayout);
	UpdateRates_EditState();
}

void QSysParasCfgWidget_NoGrid::InitConnection()
{
	connect(m_pParasSetSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_ParasSetSelChanged(int)));
}

void QSysParasCfgWidget_NoGrid::InitData()
{
	m_pPrimRates = m_pCfgSysParas->GetPrimRates();
	m_pParasSetSelCombox->setCurrentIndex(!m_pCfgSysParas->m_nPrimParas);
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

void QSysParasCfgWidget_NoGrid::UpdateRates_EditState()
{
	BOOL bShow = TRUE;
	if (m_pCfgSysParas->m_nPrimOutput == m_pCfgSysParas->m_nPrimParas)//如果参数设置与实际输出一致,则不需要设置变比
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

void QSysParasCfgWidget_NoGrid::slot_ParasSetSelChanged(int nIndex)
{
	ASSERT(m_pCfgSysParas);
	m_pCfgSysParas->m_nPrimParas = (nIndex == 0);
	UpdateRates_EditState();
}

void QSysParasCfgWidget_NoGrid::SaveDatas()
{
	CIecCfgPrimRates* pPrimRates = m_pCfgSysParas->GetPrimRates();
	m_pCfgSysParas->m_nPrimParas = (!m_pParasSetSelCombox->currentIndex());
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
