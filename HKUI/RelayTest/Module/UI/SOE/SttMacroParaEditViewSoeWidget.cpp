#include "SttMacroParaEditViewSoeWidget.h"
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"

#include "SttMacroParaEditViewSoe.h"

QSttMacroParaEditViewSoeWidget::QSttMacroParaEditViewSoeWidget(QWidget *parent) :QWidget(parent)   
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint); 
	
	m_pMain_VLayout = NULL;
	m_pBtn_HLayout = NULL;
	m_pHLayout = NULL;
	m_pSoe_VLayout = NULL;
	m_pSoe_Widget = NULL;

	m_pPulseWidth_Edit = NULL;
	m_pPulseWidth_Label= NULL;

	m_pSOE_Edit= NULL;
	m_pSOE_Label= NULL;

	m_pDeflectio_Edit= NULL;
	m_pDeflection_Label = NULL;

	m_pSelectAll_PushButton = NULL;
	m_pCancelAll_PushButton = NULL;
	
	m_pInitialAll_PushButton = NULL;
	m_pInitialDivideAll_PushButton = NULL;

	m_pTrigerConditionCombox = NULL;
	m_pTrigger_Label = NULL;

	m_pGPSTime_Label = NULL;
	m_pHourEdit = NULL;
	m_pMinuteEdit = NULL;
	m_pSecondEdit = NULL;
	m_pHourLabel = NULL;
	m_pSecondLabel = NULL;
	m_pMinuteLabel = NULL;

// 	InitUI();
// 	initConnections();

}

void QSttMacroParaEditViewSoeWidget::InitUI()
{
	CString strTemp;

//顶部button
	//strTemp = _T("脉冲宽度(ms)");
	m_pPulseWidth_Edit = new QSttLineEdit();
	m_pPulseWidth_Edit->setFixedWidth(70);
	m_pPulseWidth_Label= new QLabel(g_sLangTxt_SOE_PulseWidth);

	//strTemp = _T("SOE分辨率(ms)");
	m_pSOE_Edit= new QSttLineEdit();
	m_pSOE_Edit->setFixedWidth(60);
	m_pSOE_Label=  new QLabel(g_sLangTxt_SOE_Resolution);

	//strTemp = _T("变位次数(次)");
	m_pDeflectio_Edit= new QSttLineEdit();
	m_pDeflectio_Edit->setFixedWidth(70);
	m_pDeflection_Label =  new QLabel(g_sLangTxt_SOE_Count);

	//strTemp = _T("全部选择");
	m_pSelectAll_PushButton = new QPushButton(g_sLangTxt_SOE_SelectAll);
	//strTemp = _T("全部取消");
	m_pCancelAll_PushButton = new QPushButton(g_sLangTxt_SOE_CancelAll);

	//strTemp = _T("初始全合");
	m_pInitialAll_PushButton = new QPushButton(g_sLangTxt_SOE_InitialAll);
	//strTemp = _T("初始全分");
	m_pInitialDivideAll_PushButton = new QPushButton(g_sLangTxt_SOE_InitialDivideAll);

	//strTemp = _T("触发方式");
	m_pTrigerConditionCombox = new QScrollComboBox();
	m_pTrigger_Label =  new QLabel(g_sLangTxt_State_TrigerCondition);

	//strTemp = _T("触发时刻");
	m_pGPSTime_Label =  new QLabel(g_sLangTxt_State_TrigerTime);
	//strTemp = _T("时");
	m_pHourLabel = new QLabel(g_sLangTxt_State_Hour);
	//strTemp = _T("分");
	m_pMinuteLabel = new QLabel(g_sLangTxt_State_Minute);
	//strTemp = _T("秒");
	m_pSecondLabel = new QLabel(g_sLangTxt_State_Second);

	m_pHourEdit = new QSttLineEdit(this);
	m_pMinuteEdit = new QSttLineEdit(this);
	m_pSecondEdit = new QSttLineEdit(this);


	m_pBtn_HLayout = new QHBoxLayout();
	m_pBtn_HLayout->addWidget(m_pPulseWidth_Label);
	m_pBtn_HLayout->addWidget(m_pPulseWidth_Edit);
	m_pBtn_HLayout->addWidget(m_pSOE_Label);
	m_pBtn_HLayout->addWidget(m_pSOE_Edit);
	m_pBtn_HLayout->addWidget(m_pDeflection_Label);
	m_pBtn_HLayout->addWidget(m_pDeflectio_Edit);
	m_pBtn_HLayout->addWidget(m_pSelectAll_PushButton);
	m_pBtn_HLayout->addWidget(m_pCancelAll_PushButton);
	m_pBtn_HLayout->addWidget(m_pInitialAll_PushButton);
	m_pBtn_HLayout->addWidget(m_pInitialDivideAll_PushButton);
 	m_pBtn_HLayout->addStretch();

	m_pHLayout = new QHBoxLayout();
	m_pHLayout->addWidget(m_pTrigger_Label);
	m_pHLayout->addWidget(m_pTrigerConditionCombox);
	m_pHLayout->addWidget(m_pGPSTime_Label);
	m_pHLayout->addWidget(m_pHourEdit);
	m_pHLayout->addWidget(m_pHourLabel);
	m_pHLayout->addWidget(m_pMinuteEdit);
	m_pHLayout->addWidget(m_pMinuteLabel);
	m_pHLayout->addWidget(m_pSecondEdit);
	m_pHLayout->addWidget(m_pSecondLabel);
	m_pHLayout->addStretch();

	
	m_pSoe_VLayout = new QVBoxLayout();
	m_pSoeGrid = new QSttMacroParaEditViewSoeTable();
	m_pSoe_VLayout->addLayout(m_pBtn_HLayout);
	m_pSoe_VLayout->addLayout(m_pHLayout);
	m_pSoe_VLayout->addWidget(m_pSoeGrid);

	m_pSoe_Widget = new QWidget();
	m_pSoe_Widget->setLayout(m_pSoe_VLayout);

	m_pSoeTab = new QSttTabWidget(this);
	strTemp = _T("SOE");
	m_pSoeTab->addTab(m_pSoe_Widget,strTemp);



	m_pMain_VLayout = new QVBoxLayout(this);
	m_pMain_VLayout->addWidget(m_pSoeTab);

	InitComboxData();

	//combobox默认是立即触发，不需要时间，初始化时隐藏
	m_pGPSTime_Label->hide();
	m_pHourEdit->hide();
	m_pMinuteEdit->hide();
	m_pSecondEdit->hide();
	m_pHourLabel->hide();
	m_pMinuteLabel->hide();
	m_pSecondLabel->hide();

}

QSttMacroParaEditViewSoeWidget::~QSttMacroParaEditViewSoeWidget()
{
   
}

void QSttMacroParaEditViewSoeWidget::initConnections()
{
	connect(m_pSoeTab, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));

}

void QSttMacroParaEditViewSoeWidget::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (g_pSoeTest == NULL)
	{
		return;
	}

	BOOL bVisibleBottomCtrls = (g_pSoeTest->m_pGooseParaWidget != m_pSoeTab->currentWidget());
	

	if (bVisibleBottomCtrls == 1)
	{
		m_pGPSTime_Label->hide();
		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHourLabel->hide();
		m_pMinuteLabel->hide();
		m_pSecondLabel->hide();

	}
}


void QSttMacroParaEditViewSoeWidget::SetData(tmt_SoeParas* pSoeParas)
{

	m_pSoeParas = pSoeParas;
	
	CString strPulse,strDeflectio;
	strPulse.Format(_T("%0.0f"),pSoeParas->m_binOut[0].otmt_SoeState[1].time);
	m_pPulseWidth_Edit->setText(strPulse);

	m_pSOE_Edit->setText("1");

	strDeflectio.Format(_T("%d"),pSoeParas->m_binOut[0].cnt);
	m_pDeflectio_Edit->setText(strDeflectio);

	UpdateData();
	initConnections();
	UpdateTriggerBtnState();
}

void QSttMacroParaEditViewSoeWidget::InitComboxData()
{
	
	listTrigerConditions.clear();

	CString strItem1,strItem2;
/*	strItem1 = _T("立即实验");*/
	xlang_GetLangStrByFile(strItem1,"Soe_ImmediateExperiment");
	xlang_GetLangStrByFile(strItem2,"State_Trigger_GPSB");

	//	listTrigerConditions << tr("立即实验")<< tr("GPS/B码触发");	

	listTrigerConditions << strItem1 << strItem2 ;

	m_pTrigerConditionCombox->clear();
	m_pTrigerConditionCombox->addItems(listTrigerConditions);
}


void QSttMacroParaEditViewSoeWidget::UpdateData()
{
	if(m_pSoeParas == NULL )
	{
		return;
	}
	

	int nIndex = m_pSoeParas->m_nMode;
	switch(nIndex)
	{
		case  SOETYPE_NULL:
			m_pTrigerConditionCombox->setCurrentIndex(0);
			break;
		case SOETYPE_GPS:
			m_pTrigerConditionCombox->setCurrentIndex(1);
			break;
	}

	int nhour = m_pSoeParas->m_tGps.nHour;
	int nmin = m_pSoeParas->m_tGps.nMinutes;
	int nsec = m_pSoeParas->m_tGps.nSeconds;

	QString str_hour;
	QString str_min;
	QString str_sec;
	if (nhour<10)
	{
		str_hour = tr("0")+QString::number(nhour,10);
	}
	else
	{
		str_hour = QString::number(nhour,10);
	}
	if (nmin<10)
	{
		str_min = tr("0")+QString::number(nmin,10);
	}
	else
	{
		str_min = QString::number(nmin,10);
	}
	if (nsec<10)
	{
		str_sec = tr("0")+QString::number(nsec,10);
	}
	else
	{
		str_sec = QString::number(nsec,10);
	}

	m_pHourEdit->setText(str_hour);
	m_pMinuteEdit->setText(str_min);
	m_pSecondEdit->setText(str_sec);
	
}

void QSttMacroParaEditViewSoeWidget::slot_cmb_TrigerConditionChanged(int index)
{
	if(m_pTrigerConditionCombox->IsScrolling())
	{
		return;
	}

	ASSERT(m_pSoeParas != NULL);
	switch (index)
	{
	case 0:
		if( m_pSoeParas->m_nMode != SOETYPE_NULL)
		{
			
			m_pSoeParas->m_nMode = SOETYPE_NULL;	//立即实验


		}
		break;  
	case 1:
		if(m_pSoeParas->m_nMode != SOETYPE_GPS)
		{
			
			m_pSoeParas->m_nMode  = SOETYPE_GPS;	//GPS/B码触发


		}
		break;
	
	}

	UpdateTriggerBtnState();
}

void QSttMacroParaEditViewSoeWidget::UpdateTriggerBtnState()
{
	int nTrigerMode = m_pSoeParas->m_nMode;
	if (nTrigerMode == SOETYPE_NULL)//立即实验
	{

		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHourLabel->setDisabled(true);
		m_pMinuteLabel->setDisabled(true);
		m_pSecondLabel->setDisabled(true);
		m_pGPSTime_Label->setDisabled(true);
		m_pGPSTime_Label->hide();

		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHourLabel->hide();
		m_pMinuteLabel->hide();
		m_pSecondLabel->hide();

	}
	else if (nTrigerMode == SOETYPE_GPS)
	{
		m_pHourEdit->setDisabled(false);
		m_pMinuteEdit->setDisabled(false);
		m_pSecondEdit->setDisabled(false);
		m_pHourLabel->setDisabled(false);
		m_pMinuteLabel->setDisabled(false);
		m_pSecondLabel->setDisabled(false);
		m_pGPSTime_Label->setDisabled(false);

		m_pHourEdit->show();
		m_pMinuteEdit->show();
		m_pSecondEdit->show();
		m_pHourLabel->show();
		m_pMinuteLabel->show();
		m_pSecondLabel->show();
		m_pGPSTime_Label->show();
  
	}

}

void QSttMacroParaEditViewSoeWidget::StartInit()
{

	m_pSoeGrid->setDisabled(true);
	m_pHourEdit->setDisabled(true);
	m_pMinuteEdit->setDisabled(true);
	m_pSecondEdit->setDisabled(true);
	m_pHourLabel->setDisabled(true);
	m_pMinuteLabel->setDisabled(true);
	m_pSecondLabel->setDisabled(true);
	m_pTrigerConditionCombox->setDisabled(true);

	m_pSelectAll_PushButton->setDisabled(true);
	m_pCancelAll_PushButton->setDisabled(true);
	m_pInitialAll_PushButton->setDisabled(true);
	m_pInitialDivideAll_PushButton->setDisabled(true);

	m_pDeflectio_Edit->setDisabled(true);
	m_pSOE_Edit->setDisabled(true);
	m_pPulseWidth_Edit->setDisabled(true);


}

void QSttMacroParaEditViewSoeWidget::StopInit()
{
	m_pSoeGrid->setDisabled(false);

	m_pHourEdit->setDisabled(false);
	m_pMinuteEdit->setDisabled(false);
	m_pSecondEdit->setDisabled(false);
	m_pHourLabel->setDisabled(false);
	m_pMinuteLabel->setDisabled(false);
	m_pSecondLabel->setDisabled(false);
	
	m_pTrigerConditionCombox->setDisabled(false);

	m_pSelectAll_PushButton->setDisabled(false);
	m_pCancelAll_PushButton->setDisabled(false);
	m_pInitialAll_PushButton->setDisabled(false);
	m_pInitialDivideAll_PushButton->setDisabled(false);

	m_pDeflectio_Edit->setDisabled(false);
	m_pSOE_Edit->setDisabled(false);
	m_pPulseWidth_Edit->setDisabled(false);
}
