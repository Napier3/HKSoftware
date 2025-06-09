#include "SttReplayTriggerWidget.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttCheckBox.h"
#include"../../Module/XLangResource_Native.h"
#include "SttMacroParaEditViewTransPlay.h"

CSttReplayTriggerWidget::CSttReplayTriggerWidget(QWidget *pParent)
:QWidget(pParent)
{
	initUI(); 
	SetTriggerParaFont();
	initSignalSlots();

	UpdateWidget(COMTRADE_TRIGGRE_TYPE_No);
}

CSttReplayTriggerWidget::~CSttReplayTriggerWidget()
{

}

void CSttReplayTriggerWidget::SetTriggerParaFont()
{
	m_pCheck_Input1->setFont(*g_pSttGlobalFont);
	m_pCheck_Input2->setFont(*g_pSttGlobalFont);
	m_pCheck_Input3->setFont(*g_pSttGlobalFont);
	m_pCheck_Input4->setFont(*g_pSttGlobalFont);
	m_pCheck_Input5->setFont(*g_pSttGlobalFont);
	m_pCheck_Input6->setFont(*g_pSttGlobalFont);
	m_pCheck_Input7->setFont(*g_pSttGlobalFont);
	m_pCheck_Input8->setFont(*g_pSttGlobalFont);
	m_pCheck_Input9->setFont(*g_pSttGlobalFont);
	m_pCheck_Input10->setFont(*g_pSttGlobalFont);
	m_pLogicAnd->setFont(*g_pSttGlobalFont);
	m_pLogicOr->setFont(*g_pSttGlobalFont);
	m_pedtGpsTime_Hour->setFont(*g_pSttGlobalFont);
	m_pedtGpsTime_Minute->setFont(*g_pSttGlobalFont);
	m_pedtGpsTime_Second->setFont(*g_pSttGlobalFont);
	m_pedtCycleNum->setFont(*g_pSttGlobalFont);

}

void CSttReplayTriggerWidget::initUI()
{
    //QFont oFont,Font;
    //oFont.setPixelSize(19);
    //setFont(oFont);
	m_pRadioBtn_NoTrip = new QSttCheckBox(g_sLangTxt_notrigger);
	m_plbCycleNum = new QLabel(g_sLangTxt_Cyclicwave);
	m_pedtCycleNum = new QSttLineEdit(this);
	CString strText = _T("0");
	m_pedtCycleNum->setText(strText);
	m_pHLayout1 = new QHBoxLayout;
	m_pHLayout1->addWidget(m_pRadioBtn_NoTrip);
	m_pHLayout1->addWidget(m_plbCycleNum);
	m_pHLayout1->addWidget(m_pedtCycleNum);
	m_pHLayout1->addStretch();

	m_pRadioBtn_ManualTrip = new QSttCheckBox(g_sLangTxt_State_Trigger_Manu);
	m_pHLayout2 = new QHBoxLayout;
	m_pHLayout2->addWidget(m_pRadioBtn_ManualTrip);
	m_pHLayout2->addStretch();

	m_pRadioBtn_GpsTrip = new QSttCheckBox(g_sLangTxt_GPS);
	m_plbGpsTime = new QLabel(g_sLangTxt_Timere);
	m_pedtGpsTime_Hour = new QSttLineEdit(this);
	strText = _T(":");
	m_plbGpsTime_Hour_comma = new QLabel(strText);
	m_pedtGpsTime_Minute = new QSttLineEdit(this);
	m_plbGpsTime_Minute_comma = new QLabel(strText);
	m_pedtGpsTime_Second = new QSttLineEdit(this);

	strText = _T("8");
	m_pedtGpsTime_Hour->setText(strText);
	strText = _T("0");
	m_pedtGpsTime_Minute->setText(strText);
	m_pedtGpsTime_Second->setText(strText);

	initMaxPositiveEdit(m_pedtGpsTime_Hour);
	initMaxPositiveEdit(m_pedtGpsTime_Minute);
	initMaxPositiveEdit(m_pedtGpsTime_Second);

	m_pHLayout3 = new QHBoxLayout;
	m_pHLayout3->addWidget(m_pRadioBtn_GpsTrip);
	m_pHLayout3->addWidget(m_plbGpsTime);
	m_pHLayout3->addWidget(m_pedtGpsTime_Hour);
	m_pHLayout3->addWidget(m_plbGpsTime_Hour_comma);
	m_pHLayout3->addWidget(m_pedtGpsTime_Minute);
	m_pHLayout3->addWidget(m_plbGpsTime_Minute_comma);
	m_pHLayout3->addWidget(m_pedtGpsTime_Second);
	m_pHLayout3->addStretch();

	m_pRadioBtn_BinaryInTrip = new QSttCheckBox(g_sLangTxt_Switchtrigger);
	m_pHLayout4 = new QHBoxLayout;
	m_pHLayout4->addWidget(m_pRadioBtn_BinaryInTrip);
	m_pHLayout4->addStretch();

	m_plbTripAfterMode = new QLabel(g_sLangTxt_posttrigger);
	m_pcmbTripAfterMode = new QComboBox();
	m_pcmbTripAfterMode->addItem(g_sLangTxt_Switchimmed);
	m_pcmbTripAfterMode->addItem(g_sLangTxt_loopwaveform);
	m_pcmbTripAfterMode->setCurrentIndex(0);
	m_pHLayout5 = new QHBoxLayout;
	m_pHLayout5->addWidget(m_plbTripAfterMode);
	m_pHLayout5->addWidget(m_pcmbTripAfterMode);
	m_pHLayout5->addStretch();
	m_plbTripAfterMode->setVisible(false);
	m_pcmbTripAfterMode->setVisible(false);

	m_pGroupBox_PutInSet = new QGroupBox();
	m_pGroupBox_PutInSet->setTitle(g_sLangTxt_Native_Bin);
	m_pGridLayout_PutInSet = new QGridLayout;
	m_pGroupBox_PutInSet->setLayout(m_pGridLayout_PutInSet);

	m_pCheck_Input1 = new QSttCheckBox(g_sLangTxt_Manual_InA);
//	m_pCheck_Input1->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input1,0,0);

	m_pCheck_Input2 = new QSttCheckBox(g_sLangTxt_Manual_InB);
//	m_pCheck_Input2->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input2,0,1);

	m_pCheck_Input3 = new QSttCheckBox(g_sLangTxt_Manual_InC);
//	m_pCheck_Input3->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input3,0,2);

	m_pCheck_Input4 = new QSttCheckBox(g_sLangTxt_Manual_InD);
//	m_pCheck_Input4->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input4,0,3);

	m_pCheck_Input5 = new QSttCheckBox(g_sLangTxt_Manual_InE);
//	m_pCheck_Input5->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input5,0,4);

	m_pLogicAnd = new QRadioButton(g_sLangTxt_Native_LogicAnd);
//	m_pLogicAnd->setStyleSheet("QRadioButton::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pLogicAnd,0,5);

	m_pCheck_Input6 = new QSttCheckBox(g_sLangTxt_Manual_InF);
//	m_pCheck_Input6->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input6,1,0);

	m_pCheck_Input7 = new QSttCheckBox(g_sLangTxt_Manual_InG);
//	m_pCheck_Input7->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input7,1,1);

	m_pCheck_Input8 = new QSttCheckBox(g_sLangTxt_Manual_InH);
//	m_pCheck_Input8->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input8,1,2);
	
	m_pCheck_Input9 = new QSttCheckBox();
//	m_pCheck_Input9->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Input9->setText(g_sLangTxt_Native_BinX + "I");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input9,1,3);

	m_pCheck_Input10 = new QSttCheckBox();
//	m_pCheck_Input10->setStyleSheet("QCheckBox::indicator{width:18px; height:18px;}");
	m_pCheck_Input10->setText(g_sLangTxt_Native_BinX + "J");
	m_pGridLayout_PutInSet->addWidget(m_pCheck_Input10,1,4);

	m_pLogicOr = new QRadioButton(g_sLangTxt_Native_LogicOr);
//	m_pLogicOr->setStyleSheet("QRadioButton::indicator{width:18px; height:18px;}");
	m_pGridLayout_PutInSet->addWidget(m_pLogicOr,1,5);

	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->insertSpacing(0,25);
	m_pMainLayout->setSpacing(25);
	m_pMainLayout->addLayout(m_pHLayout1);
	m_pMainLayout->addLayout(m_pHLayout2);
	m_pMainLayout->addLayout(m_pHLayout3);
	m_pMainLayout->addLayout(m_pHLayout4);
	m_pMainLayout->addLayout(m_pHLayout5);
	m_pMainLayout->addWidget(m_pGroupBox_PutInSet);

	m_pMainLayout->addStretch();
	setLayout(m_pMainLayout); //设置为窗体的主布局
}

void CSttReplayTriggerWidget::ConnectAllBinaryIn(BOOL bCoonect)
{
	if (bCoonect)
	{
		connect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)),Qt::UniqueConnection);
		connect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)),Qt::UniqueConnection);
	} 
	else
	{
		disconnect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)));
		disconnect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)));
		disconnect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)));
		disconnect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)));
		disconnect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)));
		disconnect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)));
		disconnect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)));
		disconnect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)));
		disconnect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)));
		disconnect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)));
	}
}

void CSttReplayTriggerWidget::initSignalSlots()
{
	connect(m_pRadioBtn_NoTrip,SIGNAL(clicked()),this,SLOT(slot_NoTripClicked()));
	connect(m_pRadioBtn_ManualTrip,SIGNAL(clicked()),this,SLOT(slot_ManualTripClicked()));
	connect(m_pRadioBtn_GpsTrip,SIGNAL(clicked()),this,SLOT(slot_GpsTripClicked()));
	connect(m_pRadioBtn_BinaryInTrip,SIGNAL(clicked()),this,SLOT(slot_BinaryInTripClicked()));

	connect(m_pcmbTripAfterMode,SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TripAfterModeChanged(int)));
	connect(m_pedtGpsTime_Hour, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	connect(m_pedtGpsTime_Minute, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	connect(m_pedtGpsTime_Second, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	connect(m_pedtCycleNum, SIGNAL(editingFinished()), this, SLOT(slot_CycleNumChanged()));

#ifdef _PSX_QT_LINUX_
	connect(m_pedtGpsTime_Hour,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	connect(m_pedtGpsTime_Minute,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	connect(m_pedtGpsTime_Second,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	connect(m_pedtCycleNum,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
#endif

	ConnectAllBinaryIn(TRUE);

	connect(m_pLogicAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)));
	connect(m_pLogicOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)));
}

void CSttReplayTriggerWidget::uninitSignalSlots()
{
	disconnect(m_pRadioBtn_NoTrip,SIGNAL(clicked()),this,SLOT(slot_NoTripClicked()));
	disconnect(m_pRadioBtn_ManualTrip,SIGNAL(clicked()),this,SLOT(slot_ManualTripClicked()));
	disconnect(m_pRadioBtn_GpsTrip,SIGNAL(clicked()),this,SLOT(slot_GpsTripClicked()));
	disconnect(m_pRadioBtn_BinaryInTrip,SIGNAL(clicked()),this,SLOT(slot_BinaryInTripClicked()));

	disconnect(m_pcmbTripAfterMode,SIGNAL(currentIndexChanged(int)), this, SLOT(slot_TripAfterModeChanged(int)));
	disconnect(m_pedtGpsTime_Hour, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	disconnect(m_pedtGpsTime_Minute, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	disconnect(m_pedtGpsTime_Second, SIGNAL(editingFinished()), this, SLOT(slot_GpsTimeChanged()));
	disconnect(m_pedtCycleNum, SIGNAL(editingFinished()), this, SLOT(slot_CycleNumChanged()));

#ifdef _PSX_QT_LINUX_
	disconnect(m_pedtGpsTime_Hour,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	disconnect(m_pedtGpsTime_Minute,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	disconnect(m_pedtGpsTime_Second,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
	disconnect(m_pedtCycleNum,SIGNAL(clicked()),this,SLOT(slot_SttLineEditChanged()));
#endif

	ConnectAllBinaryIn(FALSE);
// 	disconnect(m_pCheck_Input1, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In1StateChanged(int)));
// 	disconnect(m_pCheck_Input2, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In2StateChanged(int)));
// 	disconnect(m_pCheck_Input3, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In3StateChanged(int)));
// 	disconnect(m_pCheck_Input4, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In4StateChanged(int)));
// 	disconnect(m_pCheck_Input5, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In5StateChanged(int)));
// 	disconnect(m_pCheck_Input6, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In6StateChanged(int)));
// 	disconnect(m_pCheck_Input7, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In7StateChanged(int)));
// 	disconnect(m_pCheck_Input8, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In8StateChanged(int)));
// 	disconnect(m_pCheck_Input9, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In9StateChanged(int)));
// 	disconnect(m_pCheck_Input10, SIGNAL(stateChanged (int)), this, SLOT(slot_ck_In10StateChanged(int)));

	disconnect(m_pLogicAnd, SIGNAL(toggled(bool )), this, SLOT(slot_radio_AndStateChanged(bool)));
	disconnect(m_pLogicOr, SIGNAL(toggled(bool )), this, SLOT(slot_radio_OrStateChanged(bool)));
}

void CSttReplayTriggerWidget::slot_SttLineEditChanged()
{
	QSttLineEdit* pEditLine = qobject_cast<QSttLineEdit*>(sender());

	if (pEditLine->text().isEmpty())
	{
		pEditLine->setText("0.0");
	}

	QString str = pEditLine->text();

	GetWidgetBoard_DigitData(4,str,pEditLine,this);

	if (str.right(1).contains("."))
	{
		str.append("000");
	}

// 	pEditLine->setText(str);
// 	pEditLine->SetEditFinished();
}

void CSttReplayTriggerWidget::slot_NoTripClicked()
{
	UpdateWidget(COMTRADE_TRIGGRE_TYPE_No);
}

void CSttReplayTriggerWidget::slot_ManualTripClicked()
{
	UpdateWidget(COMTRADE_TRIGGRE_TYPE_Manual);
}

void CSttReplayTriggerWidget::slot_GpsTripClicked()
{
	UpdateWidget(COMTRADE_TRIGGRE_TYPE_GPS);
}

void CSttReplayTriggerWidget::slot_BinaryInTripClicked()
{
	UpdateWidget(COMTRADE_TRIGGRE_TYPE_Binary);
}

void CSttReplayTriggerWidget::slot_TripAfterModeChanged(int nIndex)
{
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nTrigAfterMode = nIndex;
}

void CSttReplayTriggerWidget::slot_GpsTimeChanged()
{
	int nHour = m_pedtGpsTime_Hour->text().toInt();
	if (nHour<0)
	{
		nHour = 0;
	}
	if (nHour>23)
	{
		nHour = 23;	
	}
	m_pedtGpsTime_Hour->setText(QString::number(nHour,10));

	int nMin = m_pedtGpsTime_Minute->text().toInt();
	if (nMin <0)
	{
		nMin = 0;
	}
	if (nMin>59)
	{
		nMin = 59;	
	}
	m_pedtGpsTime_Minute->setText(QString::number(nMin,10));

	int nSec = m_pedtGpsTime_Second->text().toInt();
	if (nSec <0)
	{
		nSec = 0;
	}
	if (nSec>59)
	{
		nSec = 59;	
	}
	m_pedtGpsTime_Second->setText(QString::number(nSec,10));

	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nHour = nHour;
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nMinutes = nMin;
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nSeconds = nSec;
}

void CSttReplayTriggerWidget::slot_CycleNumChanged()
{
	int nCnt = m_pedtCycleNum->text().toInt();
	if (nCnt<0)
	{
		nCnt = 0;
	}
	if (nCnt>10)
	{
		nCnt = 10;
	}
	m_pedtCycleNum->setText(QString::number(nCnt,10));

	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nStartCycleNum = nCnt;
}

void CSttReplayTriggerWidget::slot_ck_In1StateChanged(int)
{	
	if (m_pCheck_Input1->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();
	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In2StateChanged(int)
{	
	if (m_pCheck_Input2->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In3StateChanged(int)
{	
	if (m_pCheck_Input3->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[2].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[2].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In4StateChanged(int)
{	
	if (m_pCheck_Input4->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[3].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[3].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In5StateChanged(int)
{	
	if (m_pCheck_Input5->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[4].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[4].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In6StateChanged(int)
{	
	if (m_pCheck_Input6->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[5].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[5].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In7StateChanged(int)
{	
	if (m_pCheck_Input7->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[6].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[6].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In8StateChanged(int)
{	
	if (m_pCheck_Input8->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[7].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[7].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In9StateChanged(int)
{	
	if (m_pCheck_Input9->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[8].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[8].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_ck_In10StateChanged(int)
{	
	if (m_pCheck_Input10->checkState() == Qt::Checked)
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[9].nSelect = 1;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[9].nSelect = 0;
	}

	if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
	{
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
		{
			m_pCheck_Input1->setCheckState(Qt::Checked);
		}
		if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
		{
			m_pCheck_Input2->setCheckState(Qt::Checked);
		}	
	}

	g_pReplayTestMain->SwitchStateChanged();

	//emit sig_InPutStateChanged();
}

void CSttReplayTriggerWidget::slot_radio_AndStateChanged( bool )
{
	if(m_pLogicAnd->isChecked())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = 1;
		if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
		{
			if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
			{
				m_pCheck_Input1->setCheckState(Qt::Checked);
			}
			if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
			{
				m_pCheck_Input2->setCheckState(Qt::Checked);
			}	
		}
	}
	else if (m_pLogicOr->isChecked())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = 0;
	}
}

void CSttReplayTriggerWidget::slot_radio_OrStateChanged( bool )
{
	if(m_pLogicAnd->isChecked())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = 1;
		if (!Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic))
		{
			if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[0].nSelect == 1)
			{
				m_pCheck_Input1->setCheckState(Qt::Checked);
			}
			if(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn[1].nSelect == 1)
			{
				m_pCheck_Input2->setCheckState(Qt::Checked);
			}	
		}
	}
	else if (m_pLogicOr->isChecked())
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic = 0;
	}
}

void CSttReplayTriggerWidget::UpdateWidget(int nMode)
{
	bool bNoTrip = (nMode == COMTRADE_TRIGGRE_TYPE_No);
	m_pedtCycleNum->setDisabled(!bNoTrip);
	m_pcmbTripAfterMode->setDisabled(bNoTrip);

	bool bGpsTrip = (nMode == COMTRADE_TRIGGRE_TYPE_GPS);
	m_pedtGpsTime_Hour->setDisabled(!bGpsTrip);
	m_pedtGpsTime_Minute->setDisabled(!bGpsTrip);
	m_pedtGpsTime_Second->setDisabled(!bGpsTrip);

	uninitSignalSlots();

	m_pRadioBtn_NoTrip->setChecked(false);
	m_pRadioBtn_ManualTrip->setChecked(false);
	m_pRadioBtn_GpsTrip->setChecked(false);
	m_pRadioBtn_BinaryInTrip->setChecked(false);

	switch(nMode)
	{
	case COMTRADE_TRIGGRE_TYPE_No:
		m_pRadioBtn_NoTrip->setChecked(true);
		SetBinaryInEnable(false);
		break;
	case COMTRADE_TRIGGRE_TYPE_Manual:
		m_pRadioBtn_ManualTrip->setChecked(true);
		SetBinaryInEnable(false);
		break;
	case COMTRADE_TRIGGRE_TYPE_GPS:
		m_pRadioBtn_GpsTrip->setChecked(true);
		SetBinaryInEnable(false);
		break;
	case COMTRADE_TRIGGRE_TYPE_Binary:
		m_pRadioBtn_BinaryInTrip->setChecked(true);
		SetBinaryInEnable(true);
		break;
	default:
		break;
	}
	
	initSignalSlots();

	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nTriggerType = nMode;
}

void CSttReplayTriggerWidget::SetBinaryInEnable(bool bFlag)
{
	GlobalSetQcheckEnable_Binary(m_pCheck_Input1,0,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input2,1,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input3,2,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input4,3,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input5,4,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input6,5,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input7,6,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input8,7,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input9,8,g_nBinCount,bFlag);
	GlobalSetQcheckEnable_Binary(m_pCheck_Input10,9,g_nBinCount,bFlag);

	m_pLogicAnd->setEnabled(bFlag);
	m_pLogicOr->setEnabled(bFlag);
}

void CSttReplayTriggerWidget::UpdateEditData()
{
	slot_GpsTimeChanged();
	slot_CycleNumChanged();
}

void CSttReplayTriggerWidget::InitSttReplayTriggerWidget()
{
	UpdateWidget(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nTriggerType);

	m_pedtCycleNum->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nStartCycleNum,10));

	int nHour = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nHour;
	int nMinute = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nMinutes;
	int nSecond = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_tGps.nSeconds;
	m_pedtGpsTime_Hour->setText(QString::number(nHour,10));
	m_pedtGpsTime_Minute->setText(QString::number(nMinute,10));
	m_pedtGpsTime_Second->setText(QString::number(nSecond,10));

	m_pcmbTripAfterMode->setCurrentIndex(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_nTrigAfterMode);
	UpdateBinaryInEnable();
}


void CSttReplayTriggerWidget::UpdateBinaryInEnable()
{
	ConnectAllBinaryIn(FALSE);
	Global_CheckBinSelect(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,g_nBinCount, g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic);

	GlobalSetQcheckState_BinaryIn(m_pCheck_Input1,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,0);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input2,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,1);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input3,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,2);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input4,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,3);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input5,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,4);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input6,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,5);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input7,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,6);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input8,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,7);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input9,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,8);
	GlobalSetQcheckState_BinaryIn(m_pCheck_Input10,g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_binIn,9);

	ConnectAllBinaryIn(TRUE);

	if (g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oBinaryConfig.m_nBinLogic)
	{
		m_pLogicAnd->setChecked(true);
	}
	else
	{
		m_pLogicOr->setChecked(true);
	}

}