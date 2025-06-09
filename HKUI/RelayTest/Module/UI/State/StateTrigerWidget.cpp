#include "StateTrigerWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
//#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttCheckBox.h"
#include "SttMacroParaEditViewState.h"
#include "../../Module/XLangResource_Native.h"

#define  STT_MODULE_L336D          "L336D"

QStateTrigerWidget::QStateTrigerWidget(BOOL *pbTmtParaChanged,QWidget *parent)
	: QWidget(parent)
{	
	m_pbTmtParaChanged = pbTmtParaChanged;
	m_pTrigerWidgetStatePara = NULL;
	m_pBoutBox = NULL;
	m_pTrigerCondition = NULL;
	m_pTrigerTime = NULL;
	m_pOutputTime = NULL;
	m_pTrigerHoldTime = NULL;
	m_pHour = NULL;
	m_pMinute = NULL;
	m_pSecond = NULL;
	m_pBout_1= NULL;
	m_pBout_2= NULL;
	m_pBout_3= NULL;
	m_pBout_4= NULL;

	m_pGridLayoutLeft = NULL;
	m_pBinLayout = NULL;
	m_pBinLab = NULL;
	m_pBin_A = NULL;
	m_pBin_B = NULL;
	m_pBin_C = NULL;
	m_pBin_D = NULL;

	m_pTrigerConditionCombox = NULL;
	m_pTrigerHoldTimeEdit = NULL;
	m_pOutputTimeEdit = NULL;
	m_pHourEdit = NULL;
	m_pMinuteEdit = NULL;
	m_pSecondEdit = NULL;
	m_pEditUdc = NULL;

	InitUI();
 	InitBaseData();
	SetStateFont();
}

QStateTrigerWidget::~QStateTrigerWidget()
{
	
}

void QStateTrigerWidget::SetStateFont()
{
	m_pBoutBox->setFont(*g_pSttGlobalFont);
	m_pTrigerCondition->setFont(*g_pSttGlobalFont);
	m_pTrigerTime->setFont(*g_pSttGlobalFont);
	m_pOutputTime->setFont(*g_pSttGlobalFont);
	m_pTrigerHoldTime->setFont(*g_pSttGlobalFont);
	m_pTrigerHoldTimeEdit->setFont(*g_pSttGlobalFont);
	m_pHour->setFont(*g_pSttGlobalFont);
	m_pMinute->setFont(*g_pSttGlobalFont);
	m_pSecond->setFont(*g_pSttGlobalFont);
	m_pOutputTimeEdit->setFont(*g_pSttGlobalFont);
	m_pHourEdit->setFont(*g_pSttGlobalFont);
	m_pMinuteEdit->setFont(*g_pSttGlobalFont);
	m_pSecondEdit->setFont(*g_pSttGlobalFont);
	m_pBout_1->setFont(*g_pSttGlobalFont);
	m_pBout_2->setFont(*g_pSttGlobalFont);
	m_pBout_3->setFont(*g_pSttGlobalFont);
	m_pBout_4->setFont(*g_pSttGlobalFont);
	m_pBinLab->setFont(*g_pSttGlobalFont);
	m_pBin_A->setFont(*g_pSttGlobalFont);
	m_pBin_B->setFont(*g_pSttGlobalFont);
	m_pBin_C->setFont(*g_pSttGlobalFont);
	m_pBin_D->setFont(*g_pSttGlobalFont);

	m_pEditUdc->setFont(*g_pSttGlobalFont);
	m_pLabUdc->setFont(*g_pSttGlobalFont);

}

void QStateTrigerWidget::InitUI()
{
	CString strText;
    strText = _T("触发条件");
    m_pTrigerCondition=new QLabel(strText);
	strText = _T("触发后保持时间");
	m_pTrigerHoldTime=new QLabel(strText);
	strText = _T("触发时刻");
	m_pTrigerTime=new QLabel(strText);
	strText = _T("输出时间");
	m_pOutputTime=new QLabel(strText);
    strText = _T("时");
	m_pHour=new QLabel(strText);
	strText = _T("分");
	m_pMinute=new QLabel(strText);
	strText = _T("秒 ");
	m_pSecond=new QLabel(strText);
	

    m_pTrigerConditionCombox=new QScrollComboBox();
	m_pTrigerHoldTimeEdit = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang
	//m_pTrigerHoldTimeEdit->setFixedSize(100,30);
	m_pOutputTimeEdit = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang
	//m_pOutputTimeEdit->setFixedSize(100,30);
	m_pHourEdit = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang
	m_pMinuteEdit = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang
	m_pSecondEdit = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang

	m_pLabUdc = new QLabel("Udc(V):");
	m_pEditUdc = new QSettingLineEdit(this);//new QSttLineEdit(this);	//20270712 huangliang
	//m_pEditUdc->setFixedSize(100,30);

 	//2024-8-7 wuxy 修改控件高度统一
#ifdef _PSX_QT_WINDOWS_
	m_pTrigerHoldTimeEdit->setFixedWidth(100);
	m_pOutputTimeEdit->setFixedWidth(100);
	m_pEditUdc->setFixedWidth(100);
#else
	m_pTrigerConditionCombox->setFixedHeight(30);
	m_pTrigerHoldTimeEdit->setFixedSize(100,30);
	m_pOutputTimeEdit->setFixedSize(100,30);
	m_pEditUdc->setFixedSize(100,30);
#endif // _PSX_QT_WINDOWS_

	//strText = _T("开出量");
	
	m_pBoutBox = new QGroupBox(g_sLangTxt_Native_Bin);
    strText = _T("1");
	m_pBout_1= new QSttCheckBox(strText);
    strText = _T("2");
	m_pBout_2= new QSttCheckBox(strText);
	strText = _T("3");
	m_pBout_3= new QSttCheckBox(strText);
	strText = _T("4");
	m_pBout_4= new QSttCheckBox(strText);

	//strText = _T("开入量");
	
	m_pBinLab = new QLabel(g_sLangTxt_Native_Bout);
	strText = _T("A");
	m_pBin_A = new QSttCheckBox(strText);
	strText = _T("B");
	m_pBin_B = new QSttCheckBox(strText);
	strText = _T("C");
	m_pBin_C = new QSttCheckBox(strText);
	strText = _T("D");
	m_pBin_D = new QSttCheckBox(strText);
    xlang_SetLangStrToWidget_Txt(m_pBoutBox, g_sLangTxt_Native_Bout , XLang_Ctrls_QGroupBox);//开入量-LCQ
    xlang_SetLangStrToWidget_Txt(m_pBinLab, g_sLangTxt_Native_Bin , XLang_Ctrls_QLabel);//开出量-LCQ

	xlang_SetLangStrToWidget(m_pTrigerCondition, "State_TrigerCondition", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pTrigerHoldTime, "State_TrigerHoldTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pTrigerTime, "State_TrigerTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pOutputTime, "State_OutTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pHour, "State_Hour", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pMinute, "State_Minute", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSecond, "State_Second", XLang_Ctrls_QLabel);


	m_pGridLayoutLeft = new QGridLayout();
	m_pGridLayoutLeft->addWidget(m_pTrigerCondition,0,0);
	m_pGridLayoutLeft->addWidget(m_pTrigerConditionCombox,0,1);
// 	m_pGridLayoutLeft->addWidget(m_pTrigerHoldTime,0,2);
// 	m_pGridLayoutLeft->addWidget(m_pTrigerHoldTimeEdit,0,3);
	m_pGridLayoutLeft->addWidget(m_pLabUdc,0,4);
	m_pGridLayoutLeft->addWidget(m_pEditUdc,0,5);
 	QHBoxLayout* pHTrigerTime = new QHBoxLayout();//触发时刻
 	pHTrigerTime->addWidget(m_pHourEdit);
 	pHTrigerTime->addWidget(m_pHour);
 	pHTrigerTime->addWidget(m_pMinuteEdit);
 	pHTrigerTime->addWidget(m_pMinute);
 	pHTrigerTime->addWidget(m_pSecondEdit);
 	pHTrigerTime->addWidget(m_pSecond);

	m_pBinLayout = new QGridLayout();
	//m_pBinLayout->addWidget(m_pBinLab,0,0);
	m_pBinLayout->addWidget(m_pBin_A,0,0);
	m_pBinLayout->addWidget(m_pBin_B,0,1);
	m_pBinLayout->addWidget(m_pBin_C,0,2);
	m_pBinLayout->addWidget(m_pBin_D,0,3);//开入量设置
	for (int i=0;i<4;i++)
	{
		m_pBinLayout->setColumnStretch(i,1);
	}

// 	QWidget* pTrigerTimeWidget = new QWidget();
// 	pTrigerTimeWidget->setLayout(pHTrigerTime);
// 	QWidget* pBinWidget = new QWidget();
// 	pBinWidget->setLayout(m_pBinLayout);
// 	QStackedLayout* pStackedLayout = new QStackedLayout();
// 	pStackedLayout->addWidget(pTrigerTimeWidget);
// 	pStackedLayout->addWidget(pBinWidget);
// 	pStackedLayout->widget(1)->show();

	m_pGridLayoutLeft->addWidget(m_pBinLab,1,0);
	m_pGridLayoutLeft->addLayout(m_pBinLayout,1,1);//开入量
    m_pGridLayoutLeft->addWidget(m_pTrigerTime,1,0);
	m_pGridLayoutLeft->addLayout(pHTrigerTime,1,1);
// 	m_pGridLayoutLeft->addWidget(m_pOutputTime,1,2);//输出时间
// 	m_pGridLayoutLeft->addWidget(m_pOutputTimeEdit,1,3);

	//按需求调换触发后保持时间与输出时间位置
	m_pGridLayoutLeft->addWidget(m_pOutputTime, 0, 2);
	m_pGridLayoutLeft->addWidget(m_pOutputTimeEdit, 0, 3);
	m_pGridLayoutLeft->addWidget(m_pTrigerHoldTime, 1, 2);
	m_pGridLayoutLeft->addWidget(m_pTrigerHoldTimeEdit, 1, 3);



	QGridLayout* pGridBoutBoxLayout = new QGridLayout(m_pBoutBox);
	pGridBoutBoxLayout->addWidget(m_pBout_1,0,0);
	pGridBoutBoxLayout->addWidget(m_pBout_2,0,1);
	pGridBoutBoxLayout->addWidget(m_pBout_3,0,2);
	pGridBoutBoxLayout->addWidget(m_pBout_4,0,3);
	for (int i=0;i<4;i++)
	{
		pGridBoutBoxLayout->setColumnStretch(i,1);
	}

	QHBoxLayout* pHMainLayout=new QHBoxLayout(this);
	pHMainLayout->addLayout(m_pGridLayoutLeft, 7);
	pHMainLayout->addSpacing(30);
	pHMainLayout->addWidget(m_pBoutBox, 3);
	pHMainLayout->addSpacing(10);

	CString strModel,strL336DName;
	strModel = g_oSttSystemConfig.GetDevModel();
	strL336DName = strModel.Left(5);

	if (strL336DName != STT_MODULE_L336D)
	{
		m_pEditUdc->hide();
		m_pLabUdc->hide();
	}

	setLayout(pHMainLayout);	
}


void QStateTrigerWidget::InitConnections()
{
	connect(m_pTrigerConditionCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TrigerConditionChanged(int)),Qt::UniqueConnection);
#ifdef _PSX_QT_LINUX_
	connect(m_pTrigerHoldTimeEdit, SIGNAL(clicked()), this, SLOT(slot_lne_TrigerHoldTimeChanged()),Qt::UniqueConnection);
	connect(m_pOutputTimeEdit, SIGNAL(clicked()), this, SLOT(slot_lne_OutputTimeChanged()),Qt::UniqueConnection);
	connect(m_pHourEdit, SIGNAL(clicked()), this, SLOT(slot_lneH_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pMinuteEdit, SIGNAL(clicked()), this, SLOT(slot_lneM_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pSecondEdit, SIGNAL(clicked()), this, SLOT(slot_lneS_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pEditUdc, SIGNAL(clicked()), this, SLOT(slot_lne_EditUdcChanged()),Qt::UniqueConnection);

#endif
	connect(m_pBout_1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_3, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_4, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4StateChanged(int)),Qt::UniqueConnection);

	connect(m_pBin_A, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutA_StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_B, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutB_StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_C, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutC_StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_D, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutD_StateChanged(int)),Qt::UniqueConnection);

	connect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChangedKeyBoard()));
	connect(m_pHourEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneH_GPSTimeChangedKeyBoard()));
	connect(m_pMinuteEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneM_GPSTimeChangedKeyBoard()));
	connect(m_pSecondEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneS_GPSTimeChangedKeyBoard()));
	connect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChangedKeyBoard()));
	connect(m_pEditUdc, SIGNAL(editingFinished()), this, SLOT(slot_lne_EditUdcChangedKeyBoard()));
	
}

void QStateTrigerWidget::SetData(tmt_StatePara* pStatePara)
{
	ASSERT(pStatePara != NULL);
	m_pTrigerWidgetStatePara = pStatePara;
	UpdateData();
	InitConnections();
	UpdateOutPut();
	UpdateInPut();
}

void QStateTrigerWidget::InitBaseData()
 {
 	listTrigerConditions.clear();
 	CString strItem1,strItem2,strItem3,strItem4,strItem5;
 	xlang_GetLangStrByFile(strItem1,"State_Trigger_Time");
 	xlang_GetLangStrByFile(strItem2,"State_Trigger_TimeAndBin");
 	xlang_GetLangStrByFile(strItem3,"State_Trigger_Bin");
 	xlang_GetLangStrByFile(strItem4,"State_Trigger_Manu");
 	xlang_GetLangStrByFile(strItem5,"State_Trigger_GPSB");
 	listTrigerConditions << strItem1 << strItem2 << strItem3 << strItem4 << strItem5;
 	m_pTrigerConditionCombox->clear();
 	m_pTrigerConditionCombox->addItems(listTrigerConditions);
}

void QStateTrigerWidget::UpdateData()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	int nindex = m_pTrigerWidgetStatePara->m_nTriggerCondition;
	switch (nindex)
	{
	case TMT_MDSTATE_TIMETRIGGER:
		m_pTrigerConditionCombox->setCurrentIndex(0);
		break;
	case TMT_MDSTATE_TIMEBINTRIGGER:
		m_pTrigerConditionCombox->setCurrentIndex(1);
		break;
	case TMT_MDSTATE_BINTRIGGER:
		m_pTrigerConditionCombox->setCurrentIndex(2);
		break;
	case TMT_MDSTATE_MEARSURETRIGGER:
		m_pTrigerConditionCombox->setCurrentIndex(3);
		break;
	case TMT_MDSTATE_GPSBTRIGGER:
		m_pTrigerConditionCombox->setCurrentIndex(4);
		break;
	}

	if (m_pTrigerWidgetStatePara->m_fTimeState <= 0)
	{
		//m_pOutputTimeEdit->setText("");
		m_pTrigerWidgetStatePara->m_fTimeState = 0;	//20240705 huangliang
	}
	else{
		//m_pOutputTimeEdit->setText(QString::number(m_pTrigerWidgetStatePara->m_fTimeState,'f',3));	//输出时间
	}
	m_pOutputTimeEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_fTimeState), 3);

	int nhour = m_pTrigerWidgetStatePara->m_tGps.nHour;
	int nmin = m_pTrigerWidgetStatePara->m_tGps.nMinutes;
	int nsec = m_pTrigerWidgetStatePara->m_tGps.nSeconds;

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
	if (m_pTrigerWidgetStatePara->m_fTimeAfterTrigger <= 0)
	{
		//m_pTrigerHoldTimeEdit->setText("");
		m_pTrigerWidgetStatePara->m_fTimeAfterTrigger = 0;	//20240705 huangliang
	}
	else
	{
		//m_pTrigerHoldTimeEdit->setText(QString::number(m_pTrigerWidgetStatePara->m_fTimeAfterTrigger,'f',3));
	}
	m_pTrigerHoldTimeEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_fTimeAfterTrigger), 3);

	//20240625 huangliang 
	//m_pEditUdc->setText(QString::number(g_oSystemParas.m_fAuxDC_Vol,'f',3));
	m_pEditUdc->UpdateStructText(CVariantDataAddress(&g_oSystemParas.m_fAuxDC_Vol), 3);
	UpdateAuxDcEnabled();

	UpdateTriggerBtnState();
	UpdateOutPut();
	UpdateInPut();
}

void QStateTrigerWidget::UpdateOutPut()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	disconnect(m_pBout_1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1StateChanged(int)));
	disconnect(m_pBout_2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2StateChanged(int)));
	disconnect(m_pBout_3, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3StateChanged(int)));
	disconnect(m_pBout_4, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4StateChanged(int)));
	GlobalSetQcheckState_BinaryOut(m_pBout_1,m_pTrigerWidgetStatePara->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pBout_2,m_pTrigerWidgetStatePara->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pBout_3,m_pTrigerWidgetStatePara->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pBout_4,m_pTrigerWidgetStatePara->m_binOut,3);

	connect(m_pBout_1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1StateChanged(int)));
	connect(m_pBout_2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2StateChanged(int)));
	connect(m_pBout_3, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3StateChanged(int)));
	connect(m_pBout_4, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4StateChanged(int)));
}

void QStateTrigerWidget::UpdateInPut()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	disconnect(m_pBin_A, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutA_StateChanged(int)));
	disconnect(m_pBin_B, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutB_StateChanged(int)));
	disconnect(m_pBin_C, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutC_StateChanged(int)));
	disconnect(m_pBin_D, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutD_StateChanged(int)));
	GlobalSetQcheckState_BinaryIn(m_pBin_A,m_pTrigerWidgetStatePara->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_pBin_B,m_pTrigerWidgetStatePara->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_pBin_C,m_pTrigerWidgetStatePara->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_pBin_D,m_pTrigerWidgetStatePara->m_binIn,3);

	connect(m_pBin_A, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutA_StateChanged(int)));
	connect(m_pBin_B, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutB_StateChanged(int)));
	connect(m_pBin_C, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutC_StateChanged(int)));
	connect(m_pBin_D, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InPutD_StateChanged(int)));
}

void QStateTrigerWidget::slot_cmb_TrigerConditionChanged(int index)
{
	if(m_pTrigerConditionCombox->IsScrolling())
	{
		return;
	}
	ASSERT(m_pTrigerWidgetStatePara != NULL);
	switch (index)
	{
	case 0:
		if(m_pTrigerWidgetStatePara->m_nTriggerCondition != TMT_MDSTATE_TIMETRIGGER)
		{
			*m_pbTmtParaChanged= TRUE;
			m_pTrigerWidgetStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;	//时间触发
		}
		break; 
	case 1:
 		if(m_pTrigerWidgetStatePara->m_nTriggerCondition != TMT_MDSTATE_TIMEBINTRIGGER)
 		{
 			*m_pbTmtParaChanged= TRUE;
 			m_pTrigerWidgetStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;	//时间+开入量
		}
		break;
	case 2:
 		if(m_pTrigerWidgetStatePara->m_nTriggerCondition != TMT_MDSTATE_BINTRIGGER)
 		{
 			*m_pbTmtParaChanged = TRUE;
			m_pTrigerWidgetStatePara->m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER;		//开入量触发
		}
		break;

	case 3:
		if(m_pTrigerWidgetStatePara->m_nTriggerCondition != TMT_MDSTATE_MEARSURETRIGGER)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pTrigerWidgetStatePara->m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER;//手动触发
		}
		break;
	case 4:
		if(m_pTrigerWidgetStatePara->m_nTriggerCondition != TMT_MDSTATE_GPSBTRIGGER)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pTrigerWidgetStatePara->m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER;	//GPS/B码触发
		}
		break;
	}
	UpdateTriggerBtnState();
}

void QStateTrigerWidget::UpdateTriggerBtnState()
{
	int nTrigerMode = m_pTrigerWidgetStatePara->m_nTriggerCondition;

	if (nTrigerMode == TMT_MDSTATE_TIMETRIGGER)	//时间触发
	{

		m_pBinLab->hide();
		m_pBin_A->hide();
		m_pBin_B->hide();
		m_pBin_C->hide();
		m_pBin_D->hide();

		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHour->hide();
		m_pMinute->hide();
		m_pSecond->hide();
		m_pTrigerTime->hide();

		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(false);
		m_pTrigerHoldTimeEdit->setDisabled(true);

	}
	else if (nTrigerMode == TMT_MDSTATE_TIMEBINTRIGGER)
	{
		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHour->hide();
		m_pMinute->hide();
		m_pSecond->hide();
		m_pTrigerTime->hide();

		m_pBinLab->show();
		m_pBin_A->show();
		m_pBin_B->show();
		m_pBin_C->show();
		m_pBin_D->show();

		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(false);
		m_pTrigerHoldTimeEdit->setDisabled(false);

		if (m_pTrigerHoldTimeEdit->text().isEmpty())
		{
			//20240705 huangliang 
			if (m_pTrigerHoldTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
			{
				if (((QSettingLineEdit*)m_pTrigerHoldTimeEdit)->IsSetting())
				{
					return ;
				}		
			}
			m_pTrigerHoldTimeEdit->setText("0.000");
		}
	}
	else if (nTrigerMode == TMT_MDSTATE_BINTRIGGER)
	{
		
		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHour->hide();
		m_pMinute->hide();
		m_pSecond->hide();
		m_pTrigerTime->hide();

		m_pBinLab->show();
		m_pBin_A->show();
		m_pBin_B->show();
		m_pBin_C->show();
		m_pBin_D->show();

		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(false);

		if (m_pTrigerHoldTimeEdit->text().isEmpty())
		{
			//20240705 huangliang 
			if (m_pTrigerHoldTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
			{
				if (((QSettingLineEdit*)m_pTrigerHoldTimeEdit)->IsSetting())
				{
					return ;
				}		
			}
			m_pTrigerHoldTimeEdit->setText("0.000");
		}
	}
	else if (nTrigerMode == TMT_MDSTATE_MEARSURETRIGGER)  //手动触发
	{
		m_pBinLab->hide();
		m_pBin_A->hide();
		m_pBin_B->hide();
		m_pBin_C->hide();
		m_pBin_D->hide();

		m_pHourEdit->hide();
		m_pMinuteEdit->hide();
		m_pSecondEdit->hide();
		m_pHour->hide();
		m_pMinute->hide();
		m_pSecond->hide();
		m_pTrigerTime->hide();

		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(true);

	}
	else if (nTrigerMode == TMT_MDSTATE_GPSBTRIGGER)
	{

		m_pBinLab->hide();
		m_pBin_A->hide();
		m_pBin_B->hide();
		m_pBin_C->hide();
		m_pBin_D->hide();

		m_pHourEdit->show();
		m_pMinuteEdit->show();
		m_pSecondEdit->show();
		m_pHour->show();
		m_pMinute->show();
		m_pSecond->show();
		m_pTrigerTime->show();
		
		m_pHourEdit->setDisabled(false);
		m_pMinuteEdit->setDisabled(false);
		m_pSecondEdit->setDisabled(false);
		m_pHour->setDisabled(false);
		m_pMinute->setDisabled(false);
		m_pSecond->setDisabled(false);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(true);
	}
}

void QStateTrigerWidget::slot_lneH_GPSTimeChanged()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pHourEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pHourEdit,this);

}
void QStateTrigerWidget::slot_lneH_GPSTimeChangedKeyBoard()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	QString strValue = m_pHourEdit->text();
	float h = strValue.toFloat();
	if (h>23)
	{
		h = m_pTrigerWidgetStatePara->m_tGps.nHour;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nHour != h)
	{
		m_pTrigerWidgetStatePara->m_tGps.nHour = h;
		*m_pbTmtParaChanged = TRUE;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nHour<10)
	{
		//2024-8-14 wuxinyi 触发时刻无需保留小数
		//m_pHourEdit->setText("0"+QString::number(m_pTrigerWidgetStatePara->m_tGps.nHour,10));
		//m_pHourEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nHour), 10);
		m_pHourEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nHour), 0);
	}
	else
	{
		//m_pHourEdit->setText(QString::number(m_pTrigerWidgetStatePara->m_tGps.nHour,10));
// 		m_pHourEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nHour), 10);
		m_pHourEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nHour), 0);

	}
}
void QStateTrigerWidget::slot_lneM_GPSTimeChanged()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	QString strValue = m_pMinuteEdit->text();
	GetWidgetBoard_DigitData(4,strValue,m_pMinuteEdit,this);
}

void QStateTrigerWidget::slot_lneM_GPSTimeChangedKeyBoard()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	QString strValue = m_pMinuteEdit->text();
	float m = strValue.toFloat();

	if (m>59)
	{
		m = m_pTrigerWidgetStatePara->m_tGps.nMinutes;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nMinutes != m)
	{
		m_pTrigerWidgetStatePara->m_tGps.nMinutes = m;
		*m_pbTmtParaChanged = TRUE;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nMinutes<10)
	{
		//m_pMinuteEdit->setText("0"+QString::number(m_pTrigerWidgetStatePara->m_tGps.nMinutes,10));
		m_pMinuteEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nMinutes), 0);
	}
	else
	{
		//m_pMinuteEdit->setText(QString::number(m_pTrigerWidgetStatePara->m_tGps.nMinutes,10));
		m_pMinuteEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nMinutes), 0);
	}
}

void QStateTrigerWidget::slot_lneS_GPSTimeChanged()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pSecondEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSecondEdit,this);
}

void QStateTrigerWidget::slot_lneS_GPSTimeChangedKeyBoard()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	QString strValue = m_pSecondEdit->text();
	float s = strValue.toFloat();
	if (s>59)
	{
		s = m_pTrigerWidgetStatePara->m_tGps.nSeconds;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nSeconds != s)
	{
		m_pTrigerWidgetStatePara->m_tGps.nSeconds = s;
		*m_pbTmtParaChanged = TRUE;
	}
	if (m_pTrigerWidgetStatePara->m_tGps.nSeconds<10)
	{
		//m_pSecondEdit->setText("0"+QString::number(m_pTrigerWidgetStatePara->m_tGps.nSeconds,10));
		m_pSecondEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nSeconds), 0);
	}
	else
	{
		//m_pSecondEdit->setText(QString::number(m_pTrigerWidgetStatePara->m_tGps.nSeconds,10));
		m_pSecondEdit->UpdateStructText(CVariantDataAddress(&m_pTrigerWidgetStatePara->m_tGps.nSeconds), 0);
	}
}
void QStateTrigerWidget::slot_lne_OutputTimeChanged()
{
	//20240705 huangliang 
	if (m_pOutputTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pOutputTimeEdit)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (m_pOutputTimeEdit->text().isEmpty())
	{
		m_pOutputTimeEdit->setText("0.000");
	}

	QString str = m_pOutputTimeEdit->text();
}

void QStateTrigerWidget::slot_lne_OutputTimeChangedKeyBoard()
{
	//20240705 huangliang 
	if (m_pOutputTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pOutputTimeEdit)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}
	if (m_pOutputTimeEdit->text().isEmpty())
	{
		m_pOutputTimeEdit->setText("0.000");
	}
	QString str = m_pOutputTimeEdit->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);
	m_pOutputTimeEdit->setText(QString::number(fv,'f',3));

	if (fv != m_pTrigerWidgetStatePara->m_fTimeState)
	{
		m_pTrigerWidgetStatePara->m_fTimeState = fv;
		*m_pbTmtParaChanged = TRUE;
	}
}

void QStateTrigerWidget::MakeOutPut(int nIndex,bool bSel)
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (bSel)
	{
		m_pTrigerWidgetStatePara->m_binOut[nIndex].nState = 1;
	}
	else
	{
		m_pTrigerWidgetStatePara->m_binOut[nIndex].nState = 0;
	}

	*m_pbTmtParaChanged = TRUE;
}
void QStateTrigerWidget::MakeInPut(int nIndex,bool bSel)
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (bSel)
	{
		m_pTrigerWidgetStatePara->m_binIn[nIndex].nSelect = 1;
	}
	else
	{
		m_pTrigerWidgetStatePara->m_binIn[nIndex].nSelect = 0;
	}

	*m_pbTmtParaChanged = TRUE;

	//2024-8-1 wuxinyi 新增更新开入量状态灯
	emit sig_UpdateToolButtons();

}
void QStateTrigerWidget::slot_chb_OutPut1StateChanged(int)
{
	MakeOutPut(0,m_pBout_1->isChecked());
}

void QStateTrigerWidget::slot_chb_OutPut2StateChanged(int)
{
	MakeOutPut(1,m_pBout_2->isChecked());
}

void QStateTrigerWidget::slot_chb_OutPut3StateChanged(int)
{
	MakeOutPut(2,m_pBout_3->isChecked());
}

void QStateTrigerWidget::slot_chb_OutPut4StateChanged(int)
{
	MakeOutPut(3,m_pBout_4->isChecked());
}

void QStateTrigerWidget::slot_chb_InPutA_StateChanged(int)
{
	MakeInPut(0,m_pBin_A->isChecked());
}
void QStateTrigerWidget::slot_chb_InPutB_StateChanged(int)
{
	MakeInPut(1,m_pBin_B->isChecked());
}

void QStateTrigerWidget::slot_chb_InPutC_StateChanged(int)
{
	MakeInPut(2,m_pBin_C->isChecked());
}

void QStateTrigerWidget::slot_chb_InPutD_StateChanged(int)
{
	MakeInPut(3,m_pBin_D->isChecked());
}

void QStateTrigerWidget::slot_lne_TrigerHoldTimeChanged()
{
	//20240705 huangliang 
	if (m_pTrigerHoldTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pTrigerHoldTimeEdit)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}


	if (m_pTrigerHoldTimeEdit->text().isEmpty())
	{
		m_pTrigerHoldTimeEdit->setText("0.000");
	}

	QString str = m_pTrigerHoldTimeEdit->text();
	GetWidgetBoard_DigitData(4,str,m_pTrigerHoldTimeEdit,this);
}

void QStateTrigerWidget::slot_lne_TrigerHoldTimeChangedKeyBoard()
{
	//20240705 huangliang 
	if (m_pTrigerHoldTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pTrigerHoldTimeEdit)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (m_pTrigerHoldTimeEdit->text().isEmpty())
	{
		m_pTrigerHoldTimeEdit->setText("0.000");
	}

	QString str = m_pTrigerHoldTimeEdit->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);

	m_pTrigerHoldTimeEdit->setText(QString::number(fv,'f',3));

	if (fv != m_pTrigerWidgetStatePara->m_fTimeAfterTrigger)
	{
		m_pTrigerWidgetStatePara->m_fTimeAfterTrigger = fv;
		*m_pbTmtParaChanged = TRUE;
	}
}

void QStateTrigerWidget::UpdateAuxDcEnabled()
{
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (g_oSystemParas.m_fAuxDC_Vol == 0)
	{
		m_pEditUdc->setDisabled(false);
	}
	else
	{
		m_pEditUdc->setDisabled(true);
	}

	//20240625 huangliang
	//m_pEditUdc->setText(QString::number(g_oSystemParas.m_fAuxDC_Vol,'f',3));
	m_pEditUdc->UpdateStructText(CVariantDataAddress(&g_oSystemParas.m_fAuxDC_Vol), 3);

}

void QStateTrigerWidget::slot_lne_EditUdcChanged()
{
	//20240705 huangliang 
	if (m_pEditUdc->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pEditUdc)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}


	if (m_pEditUdc->text().isEmpty())
	{
		m_pEditUdc->setText("0.000");
	}

	QString str = m_pEditUdc->text();
	GetWidgetBoard_DigitData(4,str,m_pEditUdc,this);
}

void QStateTrigerWidget::slot_lne_EditUdcChangedKeyBoard()
{
	//20240705 huangliang 
	if (m_pEditUdc->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)m_pEditUdc)->IsSetting())
		{
			return ;
		}		
	}
	if (m_pTrigerWidgetStatePara == NULL)
	{
		return;
	}

	if (m_pEditUdc->text().isEmpty())
	{
		m_pEditUdc->setText("0.000");
	}

	QString str = m_pEditUdc->text();
	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	float fv= str.toFloat();
	//fv = setLimit(0,999.999,fv);
	if (fv < 110)
	{

		CLogPrint::LogString(XLOGLEVEL_RESULT,_T("辅助直流输出最小值110V。"));
			fv = m_pTrigerWidgetStatePara->m_fVolAux;
	}

	if (fv > 300)
	{

		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("输入值(%.3f)超出辅助直流输出最大值300V。"),fv);
		fv = m_pTrigerWidgetStatePara->m_fVolAux;
	}

	m_pEditUdc->setText(QString::number(fv,'f',3));

	if (fv != m_pTrigerWidgetStatePara->m_fVolAux)
	{
		m_pTrigerWidgetStatePara->m_fVolAux = fv;
		*m_pbTmtParaChanged = TRUE;
	}
}

void QStateTrigerWidget::startInit()
{
	setEnabled(false);
	m_pTrigerConditionCombox->setEnabled(false);
	m_pTrigerHoldTimeEdit->setEnabled(false);
	m_pOutputTimeEdit->setEnabled(false);
	m_pHourEdit->setEnabled(false);
	m_pMinuteEdit->setEnabled(false);
	m_pSecondEdit->setEnabled(false);
	UpdateOutPut();
	UpdateInPut();
// 	m_pBout_1->setEnabled(false);
// 	m_pBout_2->setEnabled(false);
// 	m_pBout_3->setEnabled(false);
// 	m_pBout_4->setEnabled(false);
}
void QStateTrigerWidget::stopInit()
{
	setEnabled(true);
	m_pTrigerConditionCombox->setEnabled(true);
	UpdateTriggerBtnState();
	UpdateOutPut();
	UpdateInPut();
// 	m_pBout_1->setEnabled(true);
// 	m_pBout_2->setEnabled(true);
// 	m_pBout_3->setEnabled(true);
// 	m_pBout_4->setEnabled(true);
}