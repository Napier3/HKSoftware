#include "stateparawidget.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "SttMacroParaEditViewState.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameAPI.h"
#include "../Controls/SttCheckBox.h"

QStateParaWidget::QStateParaWidget(BOOL *pbTmtParaChanged,QWidget *parent)
	: QWidget(parent)
{
	m_pbTmtParaChanged = pbTmtParaChanged;
	m_pStatePara = NULL;
	m_pTrigerBox = NULL;
	m_pBinBox = NULL;
	m_pBoutBox = NULL;

	m_pTrigerCondition = NULL;
	m_pTrigerTime = NULL;
	m_pOutputTime = NULL;
	m_pTrigerHoldTime = NULL;
	m_pOutputHoldTime = NULL;
	m_pHour = NULL;
	m_pMinute = NULL;
	m_pSecond = NULL;

	m_pTrigerConditionCombox = NULL;
	m_pOutputTimeEdit = NULL;
	m_pTrigerHoldTimeEdit = NULL;
	m_pOutputHoldTimeEdit = NULL;
	m_pHourEdit = NULL;
	m_pMinuteEdit = NULL;
	m_pSecondEdit = NULL;

	m_pBin_A = NULL;
	m_pBin_B = NULL;
	m_pBin_C = NULL;
	m_pBin_D = NULL;
	m_pBin_E = NULL;
	m_pBin_F= NULL;
	m_pBin_G= NULL;
	m_pBin_H= NULL;
	m_pBin_I= NULL;
	m_pBin_J= NULL;

	m_pLogicOr= NULL;
	m_pLogicAnd= NULL;

	m_pBout_1= NULL;
	m_pBout_2= NULL;
	m_pBout_3= NULL;
	m_pBout_4= NULL;
	m_pBout_5= NULL;
	m_pBout_6= NULL;
	m_pBout_7= NULL;
	m_pBout_8= NULL;
	m_pBout_9= NULL;
	m_pBout_10= NULL;
	m_pChk_HoldTime = NULL;


	initUI();
	initBaseData();
	SetStateParaFont();
}

QStateParaWidget::~QStateParaWidget()
{
	
}

void QStateParaWidget::SetStateParaFont()
{
	m_pBin_A->setFont(*g_pSttGlobalFont);
	m_pBin_B->setFont(*g_pSttGlobalFont);
	m_pBin_C->setFont(*g_pSttGlobalFont);
	m_pBin_D->setFont(*g_pSttGlobalFont);
	m_pBin_E->setFont(*g_pSttGlobalFont);
	m_pBin_F->setFont(*g_pSttGlobalFont);
	m_pBin_G->setFont(*g_pSttGlobalFont);
	m_pBin_H->setFont(*g_pSttGlobalFont);
	m_pBin_I->setFont(*g_pSttGlobalFont);
	m_pBin_J->setFont(*g_pSttGlobalFont);
	m_pTrigerConditionCombox->setFont(*g_pSttGlobalFont);
	m_pBout_1->setFont(*g_pSttGlobalFont);
	m_pBout_2->setFont(*g_pSttGlobalFont);
	m_pBout_3->setFont(*g_pSttGlobalFont);
	m_pBout_4->setFont(*g_pSttGlobalFont);
	m_pBout_5->setFont(*g_pSttGlobalFont);
	m_pBout_6->setFont(*g_pSttGlobalFont);
	m_pBout_7->setFont(*g_pSttGlobalFont);
	m_pBout_8->setFont(*g_pSttGlobalFont);
	m_pBout_9->setFont(*g_pSttGlobalFont);
	m_pBout_10->setFont(*g_pSttGlobalFont);
	m_pChk_HoldTime->setFont(*g_pSttGlobalFont);

	m_pTrigerBox->setFont(*g_pSttGlobalFont);
	m_pBinBox->setFont(*g_pSttGlobalFont);
	m_pBoutBox->setFont(*g_pSttGlobalFont);
	m_pTrigerCondition->setFont(*g_pSttGlobalFont);
	m_pTrigerTime->setFont(*g_pSttGlobalFont);
	m_pOutputTime->setFont(*g_pSttGlobalFont);
	m_pTrigerHoldTime->setFont(*g_pSttGlobalFont);
	m_pOutputHoldTime->setFont(*g_pSttGlobalFont);
	m_pHour->setFont(*g_pSttGlobalFont);
	m_pMinute->setFont(*g_pSttGlobalFont);
	m_pSecond->setFont(*g_pSttGlobalFont);
	m_pOutputTimeEdit->setFont(*g_pSttGlobalFont);
	m_pTrigerHoldTimeEdit->setFont(*g_pSttGlobalFont);
	m_pOutputHoldTimeEdit->setFont(*g_pSttGlobalFont);
	m_pHourEdit->setFont(*g_pSttGlobalFont);
	m_pMinuteEdit->setFont(*g_pSttGlobalFont);
	m_pSecondEdit->setFont(*g_pSttGlobalFont);
	m_pLogicAnd->setFont(*g_pSttGlobalFont);
	m_pLogicOr->setFont(*g_pSttGlobalFont);
}


void QStateParaWidget::initUI()
{
	m_pTrigerBox = new QGroupBox(tr("触发设置"));
	m_pBinBox = new QGroupBox(tr("开入量"));
	m_pBoutBox = new QGroupBox(tr("开出量"));

	m_pTrigerCondition = new QLabel(tr("触发条件"));
	m_pTrigerTime = new QLabel(tr("触发时刻"));
	m_pOutputTime = new QLabel(tr("输出时间"));
	m_pTrigerHoldTime = new QLabel(tr("触发后保持时间"));
	m_pOutputHoldTime = new QLabel(tr("保持时间"));

	m_pHour = new QLabel(tr("时 "));
	m_pMinute = new QLabel(tr("分 "));
	m_pSecond = new QLabel(tr("秒 "));

	xlang_SetLangStrToWidget(m_pTrigerBox, "State_TrigerSetup", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(m_pBinBox, "Native_Bin", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(m_pBoutBox, "Native_Bout", XLang_Ctrls_QGroupBox);

	xlang_SetLangStrToWidget(m_pTrigerCondition, "State_TrigerCondition", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pTrigerTime, "State_TrigerTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pOutputTime, "State_OutTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pTrigerHoldTime, "State_TrigerHoldTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pOutputHoldTime, "State_HoldTime", XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget(m_pHour, "State_Hour", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pMinute, "State_Minute", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pSecond, "State_Second", XLang_Ctrls_QLabel);

	m_pTrigerConditionCombox = new QScrollComboBox();
	m_pOutputTimeEdit = new QSttLineEdit(this);
	m_pTrigerHoldTimeEdit = new QSttLineEdit(this);
	m_pOutputHoldTimeEdit = new QSttLineEdit(this);
	m_pHourEdit = new QSttLineEdit(this);
	m_pMinuteEdit = new QSttLineEdit(this);
	m_pSecondEdit = new QSttLineEdit(this);

// 	QString strStyle = "QCheckBox::indicator:unchecked{width: 20px;height: 20px;}"
// 		"QCheckBox::indicator:checked{width: 20px;height: 20px;}";
// 	  /*"QCheckBox{font-size:18px;}";*/  //2022-10-22 sy 采用g_pSttGlobalFont

	m_pBin_A = new QSttCheckBox(tr("A"));
	m_pBin_B = new QSttCheckBox(tr("B"));
	m_pBin_C = new QSttCheckBox(tr("C"));
	m_pBin_D = new QSttCheckBox(tr("D"));
	m_pBin_E = new QSttCheckBox(tr("E"));
	m_pBin_F= new QSttCheckBox(tr("F"));
	m_pBin_G= new QSttCheckBox(tr("G"));
	m_pBin_H= new QSttCheckBox(tr("H"));
	m_pBin_I= new QSttCheckBox(tr("I"));
	m_pBin_J= new QSttCheckBox(tr("J"));

	//采用QSttCheckBox类，需要注销样式  2022-11-19 sy
// 	m_pBin_A->setStyleSheet(strStyle);
// 	m_pBin_B->setStyleSheet(strStyle);
// 	m_pBin_C->setStyleSheet(strStyle);
// 	m_pBin_D->setStyleSheet(strStyle);
// 	m_pBin_E->setStyleSheet(strStyle);
// 	m_pBin_F->setStyleSheet(strStyle);
// 	m_pBin_G->setStyleSheet(strStyle);
// 	m_pBin_H->setStyleSheet(strStyle);
// 	m_pBin_I->setStyleSheet(strStyle);
// 	m_pBin_J->setStyleSheet(strStyle);

	m_pLogicOr= new QRadioButton(tr("逻辑或"));
	m_pLogicAnd= new QRadioButton(tr("逻辑与"));

	xlang_SetLangStrToWidget(m_pLogicOr, "Native_LogicOr", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(m_pLogicAnd, "Native_LogicAnd", XLang_Ctrls_QRadioButton);

	m_pBout_1= new QSttCheckBox(tr("1"));
	m_pBout_2= new QSttCheckBox(tr("2"));
	m_pBout_3= new QSttCheckBox(tr("3"));
	m_pBout_4= new QSttCheckBox(tr("4"));
	m_pBout_5= new QSttCheckBox(tr("5"));
	m_pBout_6= new QSttCheckBox(tr("6"));
	m_pBout_7= new QSttCheckBox(tr("7"));
	m_pBout_8= new QSttCheckBox(tr("8"));
	m_pBout_9= new QSttCheckBox(tr("9"));
	m_pBout_10= new QSttCheckBox(tr("10"));
	m_pChk_HoldTime = new QSttCheckBox(tr(""));

// 	m_pBout_1->setStyleSheet(strStyle);
// 	m_pBout_2->setStyleSheet(strStyle);
// 	m_pBout_3->setStyleSheet(strStyle);
// 	m_pBout_4->setStyleSheet(strStyle);
// 	m_pBout_5->setStyleSheet(strStyle);
// 	m_pBout_6->setStyleSheet(strStyle);
// 	m_pBout_7->setStyleSheet(strStyle);
// 	m_pBout_8->setStyleSheet(strStyle);
// 	m_pBout_9->setStyleSheet(strStyle);
// 	m_pBout_10->setStyleSheet(strStyle);
// 	m_pChk_HoldTime->setStyleSheet(strStyle);

// 	if(g_nBoutCount == 8)
// 	{
// 		m_pBout_9->setChecked(false);
// 		m_pBout_10->setChecked(false);
// 		m_pBout_9->setEnabled(false);
// 		m_pBout_10->setEnabled(false);
// 	}
// 
// 	if (g_nBinCount == 8)
// 	{
// 		m_pBin_I->setChecked(false);
// 		m_pBin_J->setChecked(false);
// 		m_pBin_I->setEnabled(false);
// 		m_pBin_J->setEnabled(false);
// 	}

	//创建布局
	QGridLayout* m_pMainLayout = new QGridLayout(this);
	m_pMainLayout->setSpacing(2);
	m_pMainLayout->setContentsMargins(2, 2, 2, 2);
	m_pMainLayout->setObjectName(QString::fromUtf8("gridLayout"));
	m_pMainLayout->setHorizontalSpacing(2);
	m_pMainLayout->setVerticalSpacing(2);

	QGridLayout* pGridLayoutTop = new QGridLayout(m_pTrigerBox);
	pGridLayoutTop->addWidget(m_pTrigerCondition,0,0);
	pGridLayoutTop->addWidget(m_pTrigerConditionCombox,0,1);
	pGridLayoutTop->addWidget(m_pOutputTime,0,2);
	pGridLayoutTop->addWidget(m_pOutputTimeEdit,0,3);
	QHBoxLayout* pHTop = new QHBoxLayout(m_pTrigerBox);
	pHTop->addWidget(m_pHourEdit);
	pHTop->addWidget(m_pHour);
	pHTop->addWidget(m_pMinuteEdit);
	pHTop->addWidget(m_pMinute);
	pHTop->addWidget(m_pSecondEdit);
	pHTop->addWidget(m_pSecond);
	pGridLayoutTop->addWidget(m_pTrigerTime,1,0);
	pGridLayoutTop->addLayout(pHTop,1,1);
	pGridLayoutTop->addWidget(m_pTrigerHoldTime,1,2);
	pGridLayoutTop->addWidget(m_pTrigerHoldTimeEdit,1,3);
	pGridLayoutTop->setColumnStretch(0,1);
	pGridLayoutTop->setColumnStretch(1,2);
	pGridLayoutTop->setColumnStretch(2,1);
	pGridLayoutTop->setColumnStretch(3,2);
	m_pMainLayout->addWidget(m_pTrigerBox,0,0,1,2);

	QGridLayout* pGridLayoutLeft = new QGridLayout(m_pBinBox);
	pGridLayoutLeft->addWidget(m_pBin_A,0,0);
	pGridLayoutLeft->addWidget(m_pBin_B,0,1);
	pGridLayoutLeft->addWidget(m_pBin_C,0,2);
	pGridLayoutLeft->addWidget(m_pBin_D,0,3);
	pGridLayoutLeft->addWidget(m_pBin_E,0,4);
	pGridLayoutLeft->addWidget(m_pLogicOr,0,5);
	pGridLayoutLeft->addWidget(m_pBin_F,1,0);
	pGridLayoutLeft->addWidget(m_pBin_G,1,1);
	pGridLayoutLeft->addWidget(m_pBin_H,1,2);
	pGridLayoutLeft->addWidget(m_pBin_I,1,3);
	pGridLayoutLeft->addWidget(m_pBin_J,1,4);
	pGridLayoutLeft->addWidget(m_pLogicAnd,1,5);
	for (int i=0;i<6;i++)
	{
		pGridLayoutLeft->setColumnStretch(i,1);
	}

	m_pMainLayout->addWidget(m_pBinBox,1,0,1,1);

	QGridLayout* pGridLayoutRight = new QGridLayout(m_pBoutBox);
	pGridLayoutRight->addWidget(m_pBout_1,0,0);
	pGridLayoutRight->addWidget(m_pBout_2,0,1);
	pGridLayoutRight->addWidget(m_pBout_3,0,2);
	pGridLayoutRight->addWidget(m_pBout_4,0,3);
	pGridLayoutRight->addWidget(m_pBout_5,0,4);
	pGridLayoutRight->addWidget(m_pOutputHoldTime,0,5);
	pGridLayoutRight->addWidget(m_pBout_6,1,0);
	pGridLayoutRight->addWidget(m_pBout_7,1,1);
	pGridLayoutRight->addWidget(m_pBout_8,1,2);
	pGridLayoutRight->addWidget(m_pBout_9,1,3);
	pGridLayoutRight->addWidget(m_pBout_10,1,4);

	QHBoxLayout* pHoldTimeLayout = new QHBoxLayout();
	pHoldTimeLayout->addWidget(m_pChk_HoldTime);
	pHoldTimeLayout->addWidget(m_pOutputHoldTimeEdit);
	pGridLayoutRight->addLayout(pHoldTimeLayout,1,5);

	for (int i=0;i<6;i++)
	{
		pGridLayoutRight->setColumnStretch(i,1);
	}

	m_pMainLayout->addWidget(m_pBoutBox,1,1,1,1);

	setLayout(m_pMainLayout);	
}

void QStateParaWidget::initConnections()
{
	connect(m_pTrigerConditionCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TrigerConditionChanged(int)),Qt::UniqueConnection);

#ifdef _PSX_QT_LINUX_
	connect(m_pOutputTimeEdit, SIGNAL(clicked()), this, SLOT(slot_lne_OutputTimeChanged()),Qt::UniqueConnection);
	connect(m_pTrigerHoldTimeEdit, SIGNAL(clicked()), this, SLOT(slot_lne_TrigerHoldTimeChanged()),Qt::UniqueConnection);
	connect(m_pHourEdit, SIGNAL(clicked()), this, SLOT(slot_lneH_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pMinuteEdit, SIGNAL(clicked()), this, SLOT(slot_lneM_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pSecondEdit, SIGNAL(clicked()), this, SLOT(slot_lneS_GPSTimeChanged()),Qt::UniqueConnection);
	connect(m_pOutputHoldTimeEdit, SIGNAL(clicked ()), this, SLOT(slot_lne_OutPutHoldTimeChanged()),Qt::UniqueConnection);

#endif

	connect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChangedKeyBoard()));
	connect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChangedKeyBoard()));
	connect(m_pHourEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneH_GPSTimeChangedKeyBoard()));
	connect(m_pMinuteEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneM_GPSTimeChangedKeyBoard()));
	connect(m_pSecondEdit, SIGNAL(editingFinished()), this, SLOT(slot_lneS_GPSTimeChangedKeyBoard()));


	connect(m_pBin_A, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputAStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_B, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputBStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_C, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputCStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_D, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputDStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_E, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputEStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_F, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputFStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_G, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputGStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_H, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputHStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_I, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputIStateChanged(int)),Qt::UniqueConnection);
	connect(m_pBin_J, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InputJStateChanged(int)),Qt::UniqueConnection);

	connect(m_pLogicAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)),Qt::UniqueConnection);
	connect(m_pLogicOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)),Qt::UniqueConnection);

	connect(m_pBout_1, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut1StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_2, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut2StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_3, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut3StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_4, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut4StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_5, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut5StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_6, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut6StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_7, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut7StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_8, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut8StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_9, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut9StateChanged(int)),Qt::UniqueConnection);
	connect(m_pBout_10, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPut10StateChanged(int)),Qt::UniqueConnection);
	connect(m_pOutputHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutPutHoldTimeChangedKeyBoard()),Qt::UniqueConnection);
	connect(m_pChk_HoldTime, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_OutPutHoldTimeStateChanged(int)),Qt::UniqueConnection);
}

void QStateParaWidget::setData(tmt_StatePara* pStatePara)
{
	ASSERT(pStatePara != NULL);
	m_pStatePara = pStatePara;

	UpdateData();
	initConnections();
}

void QStateParaWidget::initBaseData()
{
	listTrigerConditions.clear();

    CString strItem1,strItem2,strItem3,strItem4,strItem5;
	xlang_GetLangStrByFile(strItem1,"State_Trigger_Time");
	xlang_GetLangStrByFile(strItem2,"State_Trigger_TimeAndBin");
	xlang_GetLangStrByFile(strItem3,"State_Trigger_Bin");
	xlang_GetLangStrByFile(strItem4,"State_Trigger_Manu");
	xlang_GetLangStrByFile(strItem5,"State_Trigger_GPSB");

//	listTrigerConditions << tr("时间触发") << tr("时间+开入量触发") << tr("开入量触发") << tr("手动触发")
//		<< tr("GPS/B码触发");

	listTrigerConditions << strItem1 << strItem2 << strItem3 << strItem4 << strItem5;
		
	m_pTrigerConditionCombox->clear();
	m_pTrigerConditionCombox->addItems(listTrigerConditions);
}

void QStateParaWidget::UpdateData()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	int nindex = m_pStatePara->m_nTriggerCondition;
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

	if (m_pStatePara->m_fTimeState <= 0)
	{
		m_pOutputTimeEdit->setText("");
	}
	else{
		m_pOutputTimeEdit->setText(QString::number(m_pStatePara->m_fTimeState,'f',3));	//输出时间
	}

	int nhour = m_pStatePara->m_tGps.nHour;
	int nmin = m_pStatePara->m_tGps.nMinutes;
	int nsec = m_pStatePara->m_tGps.nSeconds;

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

	if (m_pStatePara->m_fTimeAfterTrigger <= 0)
	{
		m_pTrigerHoldTimeEdit->setText("");
	}
	else
	{
		m_pTrigerHoldTimeEdit->setText(QString::number(m_pStatePara->m_fTimeAfterTrigger,'f',3));
	}

	if (m_pStatePara->m_fOutputHoldTime <=0 )
	{
		m_pOutputHoldTimeEdit->setText("");
		m_pOutputHoldTimeEdit->setDisabled(true);
		m_pChk_HoldTime->setChecked(false);
	}
	else
	{
		m_pOutputHoldTimeEdit->setText(QString::number(m_pStatePara->m_fOutputHoldTime,'f',3));
		m_pOutputHoldTimeEdit->setDisabled(false);
		m_pChk_HoldTime->setChecked(true);
	}

	UpdateTriggerBtnState();

	UpdateInput();
	UpdateOutPut();
}

void QStateParaWidget::UpdateInput()
{
	if (m_pStatePara == NULL)
	{
		return;
	}


	Global_CheckBinSelect(m_pStatePara->m_binIn,g_nBinCount, m_pStatePara->m_nBinLogic);

	GlobalSetQcheckState_BinaryIn(m_pBin_A,m_pStatePara->m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_pBin_B,m_pStatePara->m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_pBin_C,m_pStatePara->m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_pBin_D,m_pStatePara->m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_pBin_E,m_pStatePara->m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_pBin_F,m_pStatePara->m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_pBin_G,m_pStatePara->m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_pBin_H,m_pStatePara->m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_pBin_I,m_pStatePara->m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_pBin_J,m_pStatePara->m_binIn,9);

// 	m_pBin_A->setChecked(m_pStatePara->m_binIn[0].nSelect == 1);
// 	m_pBin_B->setChecked(m_pStatePara->m_binIn[1].nSelect == 1);
// 	m_pBin_C->setChecked(m_pStatePara->m_binIn[2].nSelect == 1);
// 	m_pBin_D->setChecked(m_pStatePara->m_binIn[3].nSelect == 1);
// 	m_pBin_E->setChecked(m_pStatePara->m_binIn[4].nSelect == 1);
// 	m_pBin_F->setChecked(m_pStatePara->m_binIn[5].nSelect == 1);
// 	m_pBin_G->setChecked(m_pStatePara->m_binIn[6].nSelect == 1);
// 	m_pBin_H->setChecked(m_pStatePara->m_binIn[7].nSelect == 1);
// 	if(g_nBinCount == 10)
// 	{
// 		m_pBin_I->setChecked(m_pStatePara->m_binIn[8].nSelect == 1);
// 		m_pBin_J->setChecked(m_pStatePara->m_binIn[9].nSelect == 1);
// 	}

	if (m_pStatePara->m_nBinLogic)
	{
		m_pLogicAnd->setChecked(true);
	}
	else
	{
		m_pLogicOr->setChecked(true);
	}
}

void QStateParaWidget::UpdateOutPut()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	GlobalSetQcheckState_BinaryOut(m_pBout_1,m_pStatePara->m_binOut,0);
	GlobalSetQcheckState_BinaryOut(m_pBout_2,m_pStatePara->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(m_pBout_3,m_pStatePara->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(m_pBout_4,m_pStatePara->m_binOut,3);
	GlobalSetQcheckState_BinaryOut(m_pBout_5,m_pStatePara->m_binOut,4);
	GlobalSetQcheckState_BinaryOut(m_pBout_6,m_pStatePara->m_binOut,5);
	GlobalSetQcheckState_BinaryOut(m_pBout_7,m_pStatePara->m_binOut,6);
	GlobalSetQcheckState_BinaryOut(m_pBout_8,m_pStatePara->m_binOut,7);
	GlobalSetQcheckState_BinaryOut(m_pBout_9,m_pStatePara->m_binOut,8);
	GlobalSetQcheckState_BinaryOut(m_pBout_10,m_pStatePara->m_binOut,9);

// 	m_pBout_1->setChecked(m_pStatePara->m_binOut[0].nState == 1);
// 	m_pBout_2->setChecked(m_pStatePara->m_binOut[1].nState == 1);
// 	m_pBout_3->setChecked(m_pStatePara->m_binOut[2].nState == 1);
// 	m_pBout_4->setChecked(m_pStatePara->m_binOut[3].nState == 1);
// 	m_pBout_5->setChecked(m_pStatePara->m_binOut[4].nState == 1);
// 	m_pBout_6->setChecked(m_pStatePara->m_binOut[5].nState == 1);
// 	m_pBout_7->setChecked(m_pStatePara->m_binOut[6].nState == 1);
// 	m_pBout_8->setChecked(m_pStatePara->m_binOut[7].nState == 1);
// 	if(g_nBoutCount == 10)
// 	{
// 		m_pBout_9->setChecked(m_pStatePara->m_binOut[8].nState == 1);
// 		m_pBout_10->setChecked(m_pStatePara->m_binOut[9].nState == 1);
// 	}
}

void QStateParaWidget::MakeInPut(int nIndex,bool bSel)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (bSel)
	{
		m_pStatePara->m_binIn[nIndex].nSelect = 1;
	}
	else
	{
		m_pStatePara->m_binIn[nIndex].nSelect = 0;
	}

	stt_Frame_UpdateToolButtons();
	*m_pbTmtParaChanged= TRUE;

	if((m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER
		|| m_pStatePara->m_nTriggerCondition == TMT_MDSTATE_BINTRIGGER)
		&& !CalculateBin())
	{
		m_pBin_A->setCheckState(Qt::Checked);
	}

	emit sig_SwitchStateChanged();
}

void QStateParaWidget::MakeOutPut(int nIndex,bool bSel)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (bSel)
	{
		m_pStatePara->m_binOut[nIndex].nState = 1;
	}
	else
	{
		m_pStatePara->m_binOut[nIndex].nState = 0;
	}

	*m_pbTmtParaChanged = TRUE;
}

long QStateParaWidget::CalculateBin()
{
	long nValue = 0;

	for (int nIndex = 0;nIndex<g_nBinCount;nIndex++)
	{
		nValue += m_pStatePara->m_binIn[nIndex].nSelect;
	}

// 	nValue += m_pStatePara->m_binIn[0].nSelect;
// 	nValue += m_pStatePara->m_binIn[1].nSelect;
// 	nValue += m_pStatePara->m_binIn[2].nSelect;
// 	nValue += m_pStatePara->m_binIn[3].nSelect;
// 	nValue += m_pStatePara->m_binIn[4].nSelect;
// 	nValue += m_pStatePara->m_binIn[5].nSelect;
// 	nValue += m_pStatePara->m_binIn[6].nSelect;
// 	nValue += m_pStatePara->m_binIn[7].nSelect;
// 
// 	if(g_nBinCount == 10)
// 	{
// 		nValue += m_pStatePara->m_binIn[8].nSelect;
// 		nValue += m_pStatePara->m_binIn[9].nSelect;
// 	}
	return nValue;
}

void QStateParaWidget::startInit()
{
	m_pTrigerBox->setDisabled(true);
	m_pBinBox->setDisabled(true);
	m_pBoutBox->setDisabled(true);
}

void QStateParaWidget::stopInit()
{
	m_pTrigerBox->setDisabled(false);
	m_pBinBox->setDisabled(false);
	m_pBoutBox->setDisabled(false);
}

void QStateParaWidget::slot_cmb_TrigerConditionChanged(int index)
{
	if(m_pTrigerConditionCombox->IsScrolling())
	{
		return;
	}

	ASSERT(m_pStatePara != NULL);
	switch (index)
	{
	case 0:
		if(m_pStatePara->m_nTriggerCondition != TMT_MDSTATE_TIMETRIGGER)
		{
			*m_pbTmtParaChanged= TRUE;
			m_pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;	//时间触发
		}
		break;  
	case 1:
		if(m_pStatePara->m_nTriggerCondition != TMT_MDSTATE_TIMEBINTRIGGER)
		{
			*m_pbTmtParaChanged= TRUE;
			m_pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;	//时间+开入量

			if(!CalculateBin())
			{
				m_pBin_A->setCheckState(Qt::Checked);
			}
		}
		break;
	case 2:
		if(m_pStatePara->m_nTriggerCondition != TMT_MDSTATE_BINTRIGGER)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER;		//开入量触发

			if(!CalculateBin())
			{
				m_pBin_A->setCheckState(Qt::Checked);
			}
		}
		break;
	case 3:
		if(m_pStatePara->m_nTriggerCondition != TMT_MDSTATE_MEARSURETRIGGER)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER;//手动触发
		}
		break;
	case 4:
		if(m_pStatePara->m_nTriggerCondition != TMT_MDSTATE_GPSBTRIGGER)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER;	//GPS/B码触发
		}
		break;
	}

	UpdateTriggerBtnState();
}


void QStateParaWidget::SetBinaryInEnable(bool bFlag)
{
	GlobalSetQcheckEnable_Binary(m_pBin_A,0,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_B,1,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_C,2,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_D,3,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_E,4,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_F,5,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_G,6,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_H,7,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_I,8,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pBin_J,9,g_nBinCount,bFlag);

	m_pLogicAnd->setEnabled(bFlag);
	m_pLogicOr->setEnabled(bFlag);
}

void QStateParaWidget::UpdateTriggerBtnState()
{
	int nTrigerMode = m_pStatePara->m_nTriggerCondition;

	if (nTrigerMode == TMT_MDSTATE_TIMETRIGGER)	//时间触发
	{
		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(false);
		m_pTrigerHoldTimeEdit->setDisabled(true);

		SetBinaryInEnable(false);
// 		m_pBin_A->setDisabled(true);
// 		m_pBin_B->setDisabled(true);
// 		m_pBin_C->setDisabled(true);
// 		m_pBin_D->setDisabled(true);
// 		m_pBin_E->setDisabled(true);
// 		m_pBin_F->setDisabled(true);
// 		m_pBin_G->setDisabled(true);
// 		m_pBin_H->setDisabled(true);
// 		if(g_nBinCount == 10)
// 		{
// 			m_pBin_I->setDisabled(true);
// 			m_pBin_J->setDisabled(true);
// 		}

// 		m_pLogicAnd->setDisabled(true);
// 		m_pLogicOr->setDisabled(true);

		//yzj 2022-4-11 注释该函数内所有的保持时间编辑框的disable，因为该代码与6.3软件表现不符
		//m_pOutputHoldTimeEdit->setDisabled(false);
	}
	else if (nTrigerMode == TMT_MDSTATE_TIMEBINTRIGGER)
	{
		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(false);
		m_pTrigerHoldTimeEdit->setDisabled(false);

		SetBinaryInEnable(true);
// 		m_pBin_A->setDisabled(false);
// 		m_pBin_B->setDisabled(false);
// 		m_pBin_C->setDisabled(false);
// 		m_pBin_D->setDisabled(false);
// 		m_pBin_E->setDisabled(false);
// 		m_pBin_F->setDisabled(false);
// 		m_pBin_G->setDisabled(false);
// 		m_pBin_H->setDisabled(false);
// 		if(g_nBinCount == 10)
// 		{
// 			m_pBin_I->setDisabled(false);
// 			m_pBin_J->setDisabled(false);
// 		}
// 
// 		m_pLogicAnd->setDisabled(false);
// 		m_pLogicOr->setDisabled(false);

		//m_pOutputHoldTimeEdit->setDisabled(false);

		if (m_pTrigerHoldTimeEdit->text().isEmpty())
		{
			m_pTrigerHoldTimeEdit->setText("0.000");
		}
	}
	else if (nTrigerMode == TMT_MDSTATE_BINTRIGGER)
	{
		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(false);

		SetBinaryInEnable(true);
// 		m_pBin_A->setDisabled(false);
// 		m_pBin_B->setDisabled(false);
// 		m_pBin_C->setDisabled(false);
// 		m_pBin_D->setDisabled(false);
// 		m_pBin_E->setDisabled(false);
// 		m_pBin_F->setDisabled(false);
// 		m_pBin_G->setDisabled(false);
// 		m_pBin_H->setDisabled(false);
// 		if(g_nBinCount == 10)
// 		{
// 			m_pBin_I->setDisabled(false);
// 			m_pBin_J->setDisabled(false);
// 		}
// 
// 		m_pLogicAnd->setDisabled(false);
// 		m_pLogicOr->setDisabled(false);

		//m_pOutputHoldTimeEdit->setDisabled(true);

		if (m_pTrigerHoldTimeEdit->text().isEmpty())
		{
			m_pTrigerHoldTimeEdit->setText("0.000");
		}
	}
	else if (nTrigerMode == TMT_MDSTATE_MEARSURETRIGGER)  //手动触发
	{
		m_pHourEdit->setDisabled(true);
		m_pMinuteEdit->setDisabled(true);
		m_pSecondEdit->setDisabled(true);
		m_pHour->setDisabled(true);
		m_pMinute->setDisabled(true);
		m_pSecond->setDisabled(true);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(true);

		SetBinaryInEnable(false);
// 		m_pBin_A->setDisabled(true);
// 		m_pBin_B->setDisabled(true);
// 		m_pBin_C->setDisabled(true);
// 		m_pBin_D->setDisabled(true);
// 		m_pBin_E->setDisabled(true);
// 		m_pBin_F->setDisabled(true);
// 		m_pBin_G->setDisabled(true);
// 		m_pBin_H->setDisabled(true);
// 		if(g_nBinCount == 10)
// 		{
// 			m_pBin_I->setDisabled(true);
// 			m_pBin_J->setDisabled(true);
// 		}
// 
// 		m_pLogicAnd->setDisabled(true);
// 		m_pLogicOr->setDisabled(true);

		//m_pOutputHoldTimeEdit->setDisabled(true);
	}
	else if (nTrigerMode == TMT_MDSTATE_GPSBTRIGGER)
	{
		m_pHourEdit->setDisabled(false);
		m_pMinuteEdit->setDisabled(false);
		m_pSecondEdit->setDisabled(false);
		m_pHour->setDisabled(false);
		m_pMinute->setDisabled(false);
		m_pSecond->setDisabled(false);

		m_pOutputTimeEdit->setDisabled(true);
		m_pTrigerHoldTimeEdit->setDisabled(true);

		SetBinaryInEnable(false);
// 		m_pBin_A->setDisabled(true);
// 		m_pBin_B->setDisabled(true);
// 		m_pBin_C->setDisabled(true);
// 		m_pBin_D->setDisabled(true);
// 		m_pBin_E->setDisabled(true);
// 		m_pBin_F->setDisabled(true);
// 		m_pBin_G->setDisabled(true);
// 		m_pBin_H->setDisabled(true);
// 		if(g_nBinCount == 10)
// 		{
// 			m_pBin_I->setDisabled(true);
// 			m_pBin_J->setDisabled(true);
// 		}
// 
// 		m_pLogicAnd->setDisabled(true);
// 		m_pLogicOr->setDisabled(true);

		//m_pOutputHoldTimeEdit->setDisabled(true);
	}
}

void QStateParaWidget::slot_lne_OutputTimeChanged()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pOutputTimeEdit->text().isEmpty())
	{
		m_pOutputTimeEdit->setText("0.000");
	}

	QString str = m_pOutputTimeEdit->text();
	GetWidgetBoard_DigitData(4,str,m_pOutputTimeEdit,this);
// 
// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 	float fv= str.toFloat();
// 	fv = setLimit(0,999.999,fv);
// 
// //	disconnect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChanged()));
// 
// 	m_pOutputTimeEdit->setText(QString::number(fv,'f',3));
// 
// 	if (fv != m_pStatePara->m_fTimeState)
// 	{
// 		m_pStatePara->m_fTimeState = fv;
// 		*m_pbTmtParaChanged = TRUE;
// 	}

//	connect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChanged()));
}


void QStateParaWidget::slot_lne_OutputTimeChangedKeyBoard()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pOutputTimeEdit->text().isEmpty())
	{
		m_pOutputTimeEdit->setText("0.000");
	}

	QString str = m_pOutputTimeEdit->text();
// 	GetWidgetBoard_DigitData(4,str,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);

	//	disconnect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChanged()));

	m_pOutputTimeEdit->setText(QString::number(fv,'f',3));

	if (fv != m_pStatePara->m_fTimeState)
	{
		m_pStatePara->m_fTimeState = fv;
		*m_pbTmtParaChanged = TRUE;
	}

	//	connect(m_pOutputTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_OutputTimeChanged()));
}

void QStateParaWidget::slot_lneH_GPSTimeChanged()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pHourEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pHourEdit,this);
	
// 	float h = strValue.toFloat();
// 	if (h>23)
// 	{
// 		h = m_pStatePara->m_tGps.nHour;
// 	}
// 
// 	if (m_pStatePara->m_tGps.nHour != h)
// 	{
// 		m_pStatePara->m_tGps.nHour = h;
// 		*m_pbTmtParaChanged = TRUE;
// 	}
// 
// 	if (m_pStatePara->m_tGps.nHour<10)
// 	{
// 		m_pHourEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nHour,10));
// 	}
// 	else
// 	{
// 		m_pHourEdit->setText(QString::number(m_pStatePara->m_tGps.nHour,10));
// 	}
}

void QStateParaWidget::slot_lneH_GPSTimeChangedKeyBoard()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pHourEdit->text();

// 	GetWidgetBoard_DigitData(4,strValue,this);

	float h = strValue.toFloat();
	if (h>23)
	{
		h = m_pStatePara->m_tGps.nHour;
	}

	if (m_pStatePara->m_tGps.nHour != h)
	{
		m_pStatePara->m_tGps.nHour = h;
		*m_pbTmtParaChanged = TRUE;
	}

	if (m_pStatePara->m_tGps.nHour<10)
	{
		m_pHourEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nHour,10));
	}
	else
	{
		m_pHourEdit->setText(QString::number(m_pStatePara->m_tGps.nHour,10));
	}
}

void QStateParaWidget::slot_lneM_GPSTimeChanged()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pMinuteEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pMinuteEdit,this);

// 	float m = strValue.toFloat();
// 	
// 	if (m>59)
// 	{
// 		m = m_pStatePara->m_tGps.nMinutes;
// 	}
// 	
// 	if (m_pStatePara->m_tGps.nMinutes != m)
// 	{
// 		m_pStatePara->m_tGps.nMinutes = m;
// 		*m_pbTmtParaChanged = TRUE;
// 	}
// 
// 	if (m_pStatePara->m_tGps.nMinutes<10)
// 	{
// 		m_pMinuteEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nMinutes,10));
// 	}
// 	else
// 	{
// 		m_pMinuteEdit->setText(QString::number(m_pStatePara->m_tGps.nMinutes,10));
// 	}
}

void QStateParaWidget::slot_lneM_GPSTimeChangedKeyBoard()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pMinuteEdit->text();

// 	GetWidgetBoard_DigitData(4,strValue,this);

	float m = strValue.toFloat();

	if (m>59)
	{
		m = m_pStatePara->m_tGps.nMinutes;
	}

	if (m_pStatePara->m_tGps.nMinutes != m)
	{
		m_pStatePara->m_tGps.nMinutes = m;
		*m_pbTmtParaChanged = TRUE;
	}

	if (m_pStatePara->m_tGps.nMinutes<10)
	{
		m_pMinuteEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nMinutes,10));
	}
	else
	{
		m_pMinuteEdit->setText(QString::number(m_pStatePara->m_tGps.nMinutes,10));
	}
}


void QStateParaWidget::slot_lneS_GPSTimeChanged()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pSecondEdit->text();

	GetWidgetBoard_DigitData(4,strValue,m_pSecondEdit,this);

// 	float s = strValue.toFloat();
// 	
// 	if (s>59)
// 	{
// 		s = m_pStatePara->m_tGps.nSeconds;
// 	}
// 
// 	if (m_pStatePara->m_tGps.nSeconds != s)
// 	{
// 		m_pStatePara->m_tGps.nSeconds = s;
// 		*m_pbTmtParaChanged = TRUE;
// 	}
// 
// 	if (m_pStatePara->m_tGps.nSeconds<10)
// 	{
// 		m_pSecondEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nSeconds,10));
// 	}
// 	else
// 	{
// 		m_pSecondEdit->setText(QString::number(m_pStatePara->m_tGps.nSeconds,10));
// 	}
}

void QStateParaWidget::slot_lneS_GPSTimeChangedKeyBoard()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	QString strValue = m_pSecondEdit->text();

// 	GetWidgetBoard_DigitData(4,strValue,this);

	float s = strValue.toFloat();

	if (s>59)
	{
		s = m_pStatePara->m_tGps.nSeconds;
	}

	if (m_pStatePara->m_tGps.nSeconds != s)
	{
		m_pStatePara->m_tGps.nSeconds = s;
		*m_pbTmtParaChanged = TRUE;
	}

	if (m_pStatePara->m_tGps.nSeconds<10)
	{
		m_pSecondEdit->setText("0"+QString::number(m_pStatePara->m_tGps.nSeconds,10));
	}
	else
	{
		m_pSecondEdit->setText(QString::number(m_pStatePara->m_tGps.nSeconds,10));
	}
}

void QStateParaWidget::slot_lne_TrigerHoldTimeChanged()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

//	disconnect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChanged()));

	if (m_pTrigerHoldTimeEdit->text().isEmpty())
	{
		m_pTrigerHoldTimeEdit->setText("0.000");
	}

	QString str = m_pTrigerHoldTimeEdit->text();
	GetWidgetBoard_DigitData(4,str,m_pTrigerHoldTimeEdit,this);

// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 
// 	float fv= str.toFloat();
// 	fv = setLimit(0,999.999,fv);
// 
// 	m_pTrigerHoldTimeEdit->setText(QString::number(fv,'f',3));
// 
// 	if (fv != m_pStatePara->m_fTimeAfterTrigger)
// 	{
// 		m_pStatePara->m_fTimeAfterTrigger = fv;
// 		*m_pbTmtParaChanged = TRUE;
// 	}

//	connect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChanged()));
}

void QStateParaWidget::slot_lne_TrigerHoldTimeChangedKeyBoard()
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	//	disconnect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChanged()));

	if (m_pTrigerHoldTimeEdit->text().isEmpty())
	{
		m_pTrigerHoldTimeEdit->setText("0.000");
	}

	QString str = m_pTrigerHoldTimeEdit->text();
// 	GetWidgetBoard_DigitData(4,str,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

	float fv= str.toFloat();
	fv = setLimit(0,999.999,fv);

	m_pTrigerHoldTimeEdit->setText(QString::number(fv,'f',3));

	if (fv != m_pStatePara->m_fTimeAfterTrigger)
	{
		m_pStatePara->m_fTimeAfterTrigger = fv;
		*m_pbTmtParaChanged = TRUE;
	}

	//	connect(m_pTrigerHoldTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_TrigerHoldTimeChanged()));
}

void QStateParaWidget::slot_chb_InputAStateChanged(int)
{
	if (m_pBin_A->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[0].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[0].nSelect = 0;
	}

	MakeInPut(0,m_pBin_A->isChecked());
}

void QStateParaWidget::slot_chb_InputBStateChanged(int)
{
	if (m_pBin_B->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[1].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[1].nSelect = 0;
	}

	MakeInPut(1,m_pBin_B->isChecked());
}

void QStateParaWidget::slot_chb_InputCStateChanged(int)
{
	if (m_pBin_C->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[2].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[2].nSelect = 0;
	}

	MakeInPut(2,m_pBin_C->isChecked());
}

void QStateParaWidget::slot_chb_InputDStateChanged(int)
{
	if (m_pBin_D->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[3].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[3].nSelect = 0;
	}

	MakeInPut(3,m_pBin_D->isChecked());
}

void QStateParaWidget::slot_chb_InputEStateChanged(int)
{
	if (m_pBin_E->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[4].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[4].nSelect = 0;
	}

	MakeInPut(4,m_pBin_E->isChecked());
}

void QStateParaWidget::slot_chb_InputFStateChanged(int)
{
	if (m_pBin_F->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[5].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[5].nSelect = 0;
	}

	MakeInPut(5,m_pBin_F->isChecked());
}

void QStateParaWidget::slot_chb_InputGStateChanged(int)
{
	if (m_pBin_G->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[6].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[6].nSelect = 0;
	}

	MakeInPut(6,m_pBin_G->isChecked());
}

void QStateParaWidget::slot_chb_InputHStateChanged(int)
{
	if (m_pBin_H->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[7].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[7].nSelect = 0;
	}

	MakeInPut(7,m_pBin_H->isChecked());
}

void QStateParaWidget::slot_chb_InputIStateChanged(int)
{
	if (m_pBin_I->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[8].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[8].nSelect = 0;
	}

	MakeInPut(8,m_pBin_I->isChecked());
}

void QStateParaWidget::slot_chb_InputJStateChanged(int)
{
	if (m_pBin_J->checkState() == Qt::Checked)
	{
		stt_GetBinaryConfig()->m_binIn[9].nSelect = 1;
	}
	else
	{
		stt_GetBinaryConfig()->m_binIn[9].nSelect = 0;
	}

	MakeInPut(9,m_pBin_J->isChecked());
}

void QStateParaWidget::slot_radio_AndStateChanged(bool)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pLogicAnd->isChecked())
	{
		if (m_pStatePara->m_nBinLogic != 1)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nBinLogic = 1;
		}
		
		m_pLogicOr->setChecked(false);
	}
	else
	{
		if (m_pStatePara->m_nBinLogic != 0)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nBinLogic = 0;
		}
		
		m_pLogicOr->setChecked(true);
	}
}

void QStateParaWidget::slot_radio_OrStateChanged(bool)
{
	if (m_pStatePara == NULL)
	{
		return;
	}

	if (m_pLogicOr->isChecked())
	{
		if (m_pStatePara->m_nBinLogic != 0)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nBinLogic = 0;
		}
		m_pLogicAnd->setChecked(false);
	}
	else
	{
		if (m_pStatePara->m_nBinLogic != 1)
		{
			*m_pbTmtParaChanged = TRUE;
			m_pStatePara->m_nBinLogic = 1;
		}
		m_pLogicAnd->setChecked(true);
	}
}

void QStateParaWidget::slot_chb_OutPut1StateChanged(int)
{
	MakeOutPut(0,m_pBout_1->isChecked());
}

void QStateParaWidget::slot_chb_OutPut2StateChanged(int)
{
	MakeOutPut(1,m_pBout_2->isChecked());
}

void QStateParaWidget::slot_chb_OutPut3StateChanged(int)
{
	MakeOutPut(2,m_pBout_3->isChecked());
}

void QStateParaWidget::slot_chb_OutPut4StateChanged(int)
{
	MakeOutPut(3,m_pBout_4->isChecked());
}

void QStateParaWidget::slot_chb_OutPut5StateChanged(int)
{
	MakeOutPut(4,m_pBout_5->isChecked());
}

void QStateParaWidget::slot_chb_OutPut6StateChanged(int)
{
	MakeOutPut(5,m_pBout_6->isChecked());
}

void QStateParaWidget::slot_chb_OutPut7StateChanged(int)
{
	MakeOutPut(6,m_pBout_7->isChecked());
}

void QStateParaWidget::slot_chb_OutPut8StateChanged(int)
{
	MakeOutPut(7,m_pBout_8->isChecked());
}

void QStateParaWidget::slot_chb_OutPut9StateChanged(int)
{
	MakeOutPut(8,m_pBout_9->isChecked());
}

void QStateParaWidget::slot_chb_OutPut10StateChanged(int)
{
	MakeOutPut(9,m_pBout_10->isChecked());
}

void QStateParaWidget::slot_lne_OutPutHoldTimeChanged()
{
	if (m_pOutputHoldTimeEdit->text().isEmpty())
	{
		m_pOutputHoldTimeEdit->setText("0.000");
	}

	QString str = m_pOutputHoldTimeEdit->text();
	GetWidgetBoard_DigitData(4,str,m_pOutputHoldTimeEdit,this);

// 	if (str.right(1).contains("."))
// 	{
// 		str.append("000");
// 	}
// 	float fv = str.toFloat();
// 	fv = setLimit(0,999.999,fv);
// 
// 	m_pOutputHoldTimeEdit->setText(QString::number(fv,'f',3));
// 
// 	if (m_pStatePara != NULL)
// 	{
// 		m_pStatePara->m_fOutputHoldTime = fv;
// 		*m_pbTmtParaChanged = TRUE;
// 	}
}

void QStateParaWidget::slot_lne_OutPutHoldTimeChangedKeyBoard()
{
	if (m_pOutputHoldTimeEdit->text().isEmpty())
	{
		m_pOutputHoldTimeEdit->setText("0.000");
	}

	QString str = m_pOutputHoldTimeEdit->text();
// 	GetWidgetBoard_DigitData(4,str,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}
	float fv = str.toFloat();
	fv = setLimit(0,999.999,fv);

	m_pOutputHoldTimeEdit->setText(QString::number(fv,'f',3));

	if (m_pStatePara != NULL)
	{
		m_pStatePara->m_fOutputHoldTime = fv;
		*m_pbTmtParaChanged = TRUE;
	}
}


void QStateParaWidget::slot_chb_OutPutHoldTimeStateChanged(int )
{
	if (m_pChk_HoldTime->isChecked())
	{
		m_pOutputHoldTimeEdit->setDisabled(false);
	}
	else
	{
		m_pOutputHoldTimeEdit->setDisabled(true);
		if (m_pStatePara != NULL)
		{
			m_pStatePara->m_fOutputHoldTime = 0;
			m_pOutputHoldTimeEdit->setText("0");
			*m_pbTmtParaChanged = TRUE;
		}
	}
}
