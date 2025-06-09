#include "SttMacroParaEditViewFreqOutput.h"

#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewFreqOutput* g_pFreqOutputTest = NULL;
QSttMacroParaEditViewFreqOutput::QSttMacroParaEditViewFreqOutput( QWidget *parent /*= 0*/ )
{
	g_pFreqOutputTest = this;
	m_pFreqOutPutTable = NULL;
	m_pTabWidget = NULL;
	m_pFreqFileWidget = NULL;

	InitUI();
	InitConnect();

	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	g_theTestCntrFrame->InitTestResource();
	m_pFreqOutputParas = &m_oTmtFreqOutputTest.m_oFreqOutputParas;

	OpenTestTestMngrFile(m_strDefaultParaFile);
	SetDatas(NULL);
}

QSttMacroParaEditViewFreqOutput::~QSttMacroParaEditViewFreqOutput()
{
	if (m_pFreqOutPutTable != NULL)
	{
		delete m_pFreqOutPutTable;
		m_pFreqOutPutTable = NULL;
	}

	if (m_pFreqFileWidget != NULL)
	{
		delete m_pFreqFileWidget;
		m_pFreqFileWidget = NULL;
	}

	for (int i = 0; i < 3; ++i)
	{
		delete m_OutPutTypeBtn[i];
		m_OutPutTypeBtn[i] = NULL;
	}
}

CSttTestResourceBase* QSttMacroParaEditViewFreqOutput::CreateTestResource()
{
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewFreqOutput::SerializeTestParas( CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas, long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub )
{
	tmt_FreqOutputTest *pFreqOutputTest = (tmt_FreqOutputTest*)pParas;
	stt_xml_serialize(&pFreqOutputTest->m_oFreqOutputParas, pMacroParas,nVolRsNum,nCurRsNum);

}

void QSttMacroParaEditViewFreqOutput::InitUI()
{
	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_pFreqOutPutTable = new QFreqOutPutWidget(this);
	m_pFreqFileWidget = new QFreqFileWidget(this);

	CString strText;
	QStringList oRadioBtnList;
	oRadioBtnList << _T("电压电流") << _T("直流信号源")<< _T("转速脉冲信号");
	QHBoxLayout *pRadioBtnLayout = new QHBoxLayout();
	for (int i = 0; i < 3; ++i)
	{
		m_OutPutTypeBtn[i] = new QRadioButton(oRadioBtnList[i], this);
		m_OutPutTypeBtn[i]->setFont(*g_pSttGlobalFont);
		pRadioBtnLayout->addWidget(m_OutPutTypeBtn[i]); 
	}

	// 转速脉冲信号 
	m_pSpeedPulseGroup = new QGroupBox(this);
	m_pSpeedPulseGroup->setFont(*g_pSttGlobalFont);
	strText = _T("转速脉冲信号");
	m_pSpeedPulseGroup->setTitle(strText);
	QHBoxLayout *pSpeedPulseLayout = new QHBoxLayout();
	QLabel *pPulseSignalLabel = new QLabel(this);
	pPulseSignalLabel->setFont(*g_pSttGlobalFont);
	strText = _T("脉冲信号");
	pPulseSignalLabel->setText(strText);
	m_pPulseSignalCombox = new QComboBox(this);
	m_pPulseSignalCombox->setFont(*g_pSttGlobalFont);
	m_pPulseSignalCombox->setMaximumWidth(150);
	m_pPulseSignalCombox->setMinimumWidth(100);
	m_pPulseSignalCombox->addItems(QStringList()<<_T("正弦波")<<_T("矩形波"));
	QLabel *pPulseWidthLabel = new QLabel(this);
	strText = _T("脉冲宽度(ms)");
	pPulseWidthLabel->setText(strText);
	pPulseWidthLabel->setFont(*g_pSttGlobalFont);
	m_pPulseWidthEdit = new QSttLineEdit(this);
	m_pPulseWidthEdit->setFont(*g_pSttGlobalFont);
	m_pPulseWidthEdit->setMaximumWidth(120);
	QLabel *pPeakValueLabel = new QLabel(this);
	pPeakValueLabel->setFont(*g_pSttGlobalFont);
	strText = _T("峰峰值(V)");
	pPeakValueLabel->setText(strText);
	m_pPeakValueCombox = new QComboBox(this);
	m_pPeakValueCombox->setFont(*g_pSttGlobalFont);
	m_pPeakValueCombox->addItems(QStringList()<<_T("6")<<_T("12")<<_T("16")<<_T("24"));
	m_pPeakValueCombox->setMaximumWidth(120);
	m_pPeakValueCombox->setMinimumWidth(80);
	pSpeedPulseLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pSpeedPulseLayout->addWidget(pPulseSignalLabel);
	pSpeedPulseLayout->addWidget(m_pPulseSignalCombox);
	pSpeedPulseLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pSpeedPulseLayout->addWidget(pPulseWidthLabel);
	pSpeedPulseLayout->addWidget(m_pPulseWidthEdit);
	pSpeedPulseLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pSpeedPulseLayout->addWidget(pPeakValueLabel);
	pSpeedPulseLayout->addWidget(m_pPeakValueCombox);
	pSpeedPulseLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	m_pSpeedPulseGroup->setLayout(pSpeedPulseLayout);


	// 直流电流源 
	m_pDCSourceGroup = new QGroupBox(this);
	m_pDCSourceGroup->setFont(*g_pSttGlobalFont);
	strText = _T("直流电流源");
	m_pDCSourceGroup->setTitle(strText);
	QHBoxLayout *pDCSourceLayout = new QHBoxLayout();
	m_pIdc1CheckBox = new QSttCheckBox(this);
	m_pIdc1CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("Idc1");
	m_pIdc1CheckBox->setText(strText);
	m_pIdc2CheckBox= new QSttCheckBox(this);
	m_pIdc2CheckBox->setFont(*g_pSttGlobalFont);
	strText = _T("Idc2");
	m_pIdc2CheckBox->setText(strText);
	pDCSourceLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pDCSourceLayout->addWidget(m_pIdc1CheckBox);
	pDCSourceLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pDCSourceLayout->addWidget(m_pIdc2CheckBox);
	pDCSourceLayout->addItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pDCSourceLayout->addStretch();
	m_pDCSourceGroup->setLayout(pDCSourceLayout);
	
	QHBoxLayout *pBtnLayout = new QHBoxLayout();
	pBtnLayout->addWidget(m_pSpeedPulseGroup);
	pBtnLayout->addItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	pBtnLayout->addWidget(m_pDCSourceGroup);

	QWidget *pChannelTabWidget = new QWidget();
	QVBoxLayout *pMainTabLayout = new QVBoxLayout();
	pMainTabLayout->addLayout(pRadioBtnLayout); 
	pMainTabLayout->addWidget(m_pFreqOutPutTable); 
	pMainTabLayout->addLayout(pBtnLayout);   
	pChannelTabWidget->setLayout(pMainTabLayout);

	m_pTabWidget->addTab(pChannelTabWidget, _T("通道选择"));
	m_pTabWidget->addTab(m_pFreqFileWidget, _T("频率文件"));

	QVBoxLayout *pMainLayout = new QVBoxLayout(this);
	pMainLayout->addWidget(m_pTabWidget);
	this->setLayout(pMainLayout);

	setFocusPolicy(Qt::StrongFocus);
}


void QSttMacroParaEditViewFreqOutput::InitData()
{
	m_pFreqOutPutTable->setMacroType(MACROTYPE_Manual);
	m_pFreqOutPutTable->setPropertyOfParaSet(P_Common,g_oSttTestResourceMngr.m_pTestResouce,m_pFreqOutputParas->m_uiVOL,m_pFreqOutputParas->m_uiCUR,FALSE);
	m_pFreqOutPutTable->setMaxMinAndEDVal();

	int nOutPutType = m_pFreqOutputParas->m_nOutPutType;
	if (nOutPutType == 0)
	{
		m_OutPutTypeBtn[0]->setChecked(true);
	}
	else if (nOutPutType == 1)
	{
		m_OutPutTypeBtn[1]->setChecked(true);
	}
	else
	{
		m_OutPutTypeBtn[2]->setChecked(true);
	}

	m_pFreqOutPutTable->setEnabled(false);
	m_pSpeedPulseGroup->setEnabled(false);
	m_pDCSourceGroup->setEnabled(false);

	switch (nOutPutType)
	{
	case 0:
		m_pFreqOutPutTable->setEnabled(true);
		break;
	case 1:
		m_pDCSourceGroup->setEnabled(true);
		break;
	case 2:
		m_pSpeedPulseGroup->setEnabled(true);
		break;
	}

	m_pPulseSignalCombox->setCurrentIndex(m_pFreqOutputParas->m_nPulseType);
	m_pPeakValueCombox->setCurrentIndex(m_pFreqOutputParas->m_nPeakValueType);
	m_pPulseWidthEdit->setText(QString::number(m_pFreqOutputParas->m_fPulseWidth,'f',0));
	m_pIdc1CheckBox->setChecked(m_pFreqOutputParas->m_nIdc[0]);
	m_pIdc2CheckBox->setChecked(m_pFreqOutputParas->m_nIdc[1]);
	
	m_pFreqFileWidget->SetData(m_pFreqOutputParas);
}

void QSttMacroParaEditViewFreqOutput::InitConnect()
{
	connect(m_pFreqOutPutTable,SIGNAL(sig_updataParas()),this,SLOT(slot_updateParas()), Qt::UniqueConnection);

	for (int i = 0; i < 3; ++i)
	{
		connect(m_OutPutTypeBtn[i], SIGNAL(toggled(bool)), this, SLOT(slot_OutPutTypeRadioChanged(bool)));
	}

	connect(m_pIdc1CheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_Idc1CheckStateChanged(bool)));
	connect(m_pIdc2CheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_Idc2CheckStateChanged(bool)));
	connect(m_pPulseWidthEdit,SIGNAL(editingFinished()),this,SLOT(slot_PulseWidthEditChanged()));
	connect(m_pPulseSignalCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PulseSignalCombCurrentIndexChanged(int)));
	connect(m_pPeakValueCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_PeakValueCombCurrentIndexChanged(int)));
	connect(m_pTabWidget, SIGNAL(currentChanged(int)), this, SLOT(slot_TabWidgetChangedTabWidget(int)));
}


void QSttMacroParaEditViewFreqOutput::slot_OutPutTypeRadioChanged( bool bValue )
{
	if (!bValue)
	{
		return;
	}

	QRadioButton* pRadioBtn = qobject_cast<QRadioButton*>(sender());
	if (!pRadioBtn) 
	{
		return;
	}

	m_pFreqOutPutTable->setEnabled(false);
	m_pSpeedPulseGroup->setEnabled(false);
	m_pDCSourceGroup->setEnabled(false);

	if (pRadioBtn == m_OutPutTypeBtn[0])
	{
		m_pFreqOutputParas->m_nOutPutType = 0;
		m_pFreqOutPutTable->setEnabled(true);
	}
	else if (pRadioBtn == m_OutPutTypeBtn[1])
	{
		m_pFreqOutputParas->m_nOutPutType = 1;
		m_pSpeedPulseGroup->setEnabled(true);
	}
	else
	{
		m_pFreqOutputParas->m_nOutPutType = 2;
		m_pDCSourceGroup->setEnabled(true);
	}
}

void QSttMacroParaEditViewFreqOutput::slot_PulseWidthEditChanged()
{
	float fv = m_pPulseWidthEdit->text().toFloat();
	fv = setLimit(0,20,fv);

	if (m_pFreqOutputParas->m_fPulseWidth != fv)
	{
		m_pFreqOutputParas->m_fPulseWidth = fv;
	}

	m_pPulseWidthEdit->setText(QString::number(fv,'f',0));
}

void QSttMacroParaEditViewFreqOutput::slot_TabWidgetChangedTabWidget( int nIndex )
{
	if (nIndex < 0)
	{
		return;
	}

	if (nIndex == 1 && m_pFreqFileWidget) //频率文件
	{
		m_pFreqFileWidget->SetData(m_pFreqOutputParas);
	}
}

void QSttMacroParaEditViewFreqOutput::slot_Idc1CheckStateChanged( int nState )
{
	m_pFreqOutputParas->m_nIdc[0] = nState;
}

void QSttMacroParaEditViewFreqOutput::slot_Idc2CheckStateChanged( int nState )
{
	m_pFreqOutputParas->m_nIdc[1] = nState;
}

void QSttMacroParaEditViewFreqOutput::slot_PulseSignalCombCurrentIndexChanged( int index )
{
	if(index < 0)
	{
		return;
	}
	m_pFreqOutputParas->m_nPulseType = index;

}

void QSttMacroParaEditViewFreqOutput::slot_PeakValueCombCurrentIndexChanged( int index )
{
	if(index < 0)
	{
		return;
	}
	m_pFreqOutputParas->m_nPeakValueType = index;
}

void QSttMacroParaEditViewFreqOutput::slot_updateParas()
{

}

void QSttMacroParaEditViewFreqOutput::UpdateTestResource( BOOL bCreateChMaps )
{
	m_pFreqOutPutTable->initUI(g_theTestCntrFrame->GetSttTestResource());	
	m_pFreqOutPutTable->setMaxMinAndEDVal();
	m_pFreqOutPutTable->initData();
}

void QSttMacroParaEditViewFreqOutput::GetDatas( CDataGroup *pParas )
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewFreqOutput::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(m_pFreqOutputParas, &oRead);
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();

	InitData();
}

void QSttMacroParaEditViewFreqOutput::OnViewTestStart()
{
	m_pTabWidget->setEnabled(false);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	
}

void QSttMacroParaEditViewFreqOutput::OnViewTestStop()
{
	m_pTabWidget->setEnabled(true);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}
