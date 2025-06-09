#include "QHardwareSetDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../CommonMethod/commonMethod.h"
#include "../../../Module/XLangResource_Native.h"

QHardwareSetDlg::QHardwareSetDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	//setWindowTitle(tr("硬件信息设置"));
	setWindowTitle(g_sLangTxt_State_HardwareInformationSettings); //硬件信息设置 lcq 3.15
	m_pSysParas = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
	m_pSttFrameConfig = NULL;
}

QHardwareSetDlg::~QHardwareSetDlg()
{
}

void QHardwareSetDlg::initUI(STT_SystemParas *pSysParas)
{
	m_pSysParas = pSysParas;
	ReleaseUI();
	resize(300, 330);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pAllVLayout = new QVBoxLayout(this);
	CString strTmp;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	strTmp = _T("4G、蓝牙、网卡使能");
	xlang_GetLangStrByFile(strTmp,"State_FGBlueNetworkcar");   //LCQ
	m_p4GBlueTooth_GroupBox = new QGroupBox(strTmp);
	strTmp = _T("4G");
	m_p4G_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("蓝牙");
	xlang_GetLangStrByFile(strTmp,"State_Bluetooth");   //LCQ
	m_pBlueTooth_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("无线网卡");
	xlang_GetLangStrByFile(strTmp,"State_Wirelesscard");   //LCQ
	m_pWirelessNet_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("本机网卡");
	xlang_GetLangStrByFile(strTmp,"State_NativeNetworkcard");   //LCQ
	m_pLocalNet_CheckBox = new QSttCheckBox(strTmp);
	m_p4GBlueTooth_HBoxLayout = new QHBoxLayout;
	m_p4GBlueTooth_HBoxLayout->addWidget(m_p4G_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pBlueTooth_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pWirelessNet_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pLocalNet_CheckBox);

	m_p4GBlueTooth_GroupBox->setLayout(m_p4GBlueTooth_HBoxLayout);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	strTmp = _T("其它设置");
	xlang_GetLangStrByFile(strTmp,"State_Othersettings");   //LCQ
	m_pOtherSet_GroupBox = new QGroupBox(strTmp);
	m_pOtherSet_VLayout = new QVBoxLayout;
// 	m_pBackLightTime_HBoxLayout = new QHBoxLayout;

	strTmp = _T("屏幕亮度(1-5)");
	xlang_GetLangStrByFile(strTmp,"State_MinScreenBright");
	m_pScreenBright_Label = new QLabel(strTmp);
	m_pScreenBright_LineEdit = new QLongLineEdit;
	m_pScreenBright_LineEdit->InitCoverage(1,5);
	strTmp = _T("(备注:5代表最亮)");
	xlang_GetLangStrByFile(strTmp,"State_NoteFivemeansBrightest");
	m_pReMarksScreen_Label = new QLabel(strTmp);

	strTmp = _T("背光时间(分钟)");
	xlang_GetLangStrByFile(strTmp,"State_MinBacklighttime");   //LCQ
	m_pBackLightTime_Label = new QLabel(strTmp);
	m_pBackLightTime_LineEdit = new QLongLineEdit;
	m_pBackLightTime_LineEdit->InitCoverage(0,60);
	strTmp = _T("(备注:0代表常亮)");
	xlang_GetLangStrByFile(strTmp,"State_NoteZeromeansAlwayson");   //LCQ
	m_pReMarks_Label = new QLabel(strTmp);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pBackLightTime_Label);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pBackLightTime_LineEdit);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pReMarks_Label);

	strTmp = _T("机器散热风扇模式");
	xlang_GetLangStrByFile(strTmp,"State_FanMode");
	m_pFanMode_Label = new QLabel(strTmp);

	strTmp = _T("正常");
	xlang_GetLangStrByFile(strTmp,"State_Normal");
	m_pNormal_RadioButton = new QRadioButton(strTmp);
	strTmp = _T("静音");
	xlang_GetLangStrByFile(strTmp,"State_Mute");
	m_pMute_RadioButton = new QRadioButton(strTmp);
	m_pFanModeBtnGroup = new QButtonGroup(this);
	m_pFanModeBtnGroup->addButton(m_pMute_RadioButton,0);
	m_pFanModeBtnGroup->addButton(m_pNormal_RadioButton,1);
	m_pFanModeBtnGroup->setExclusive(true);


	m_pTimeZoneSet_HBoxLayout = new QHBoxLayout;
	m_pFanMode_HBoxLayout = new QHBoxLayout;
	strTmp = _T("时区设置");
	xlang_GetLangStrByFile(strTmp,"State_Timezonesetting");   //LCQ
	m_pTimeZoneSet_Label = new QLabel(strTmp);
	m_pTimeZoneSet_ComboBox = new QScrollComboBox;
	QStringList astrTimeZones;
	CString strTimeZones;

	//strTimeZones = _T("(UTC-12:00)国际日期变更线西");
	strTimeZones = g_sLangTxt_State_UTC_TwelveWIntDLine; //lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-11:00)协调世界时-11");
	strTimeZones = g_sLangTxt_State_UTC_ElevenCUTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-10:00)阿留申群岛");
	strTimeZones = g_sLangTxt_State_UTC_TenAleutianIslands;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-9:00)阿拉斯加");
	strTimeZones = g_sLangTxt_State_UTC_NineAlaska;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-8:00)太平洋时间(美国和加拿大)");//lcq 3.30
	strTimeZones = g_sLangTxt_State_UTC_EUCPacificTime;
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-7:00)奇瓦瓦,拉巴斯,马萨特兰");//lcq 3.30
	strTimeZones = g_sLangTxt_State_UTC_SevenCLM;
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-6:00)中美洲");
	strTimeZones = g_sLangTxt_State_UTC_SixCentralAmerica;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-5:00)东部时间(美国和加拿大)");
	strTimeZones = g_sLangTxt_State_UTC_FiveUCEasternTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-4:00)大西洋时间(加拿大)");
	strTimeZones = g_sLangTxt_State_UTC_FourCanadaAtlanticTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-3:00)格陵兰");
	strTimeZones = g_sLangTxt_State_UTC_ThreeGreenland;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-2:00)协调世界时-2");
	strTimeZones = g_sLangTxt_State_UTC_TwoCooUniversalTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-1:00)佛得角群岛,亚速尔群岛");
	strTimeZones = g_sLangTxt_State_UTC_OneCapIslandsAzores;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC)都柏林,爱丁堡,里斯本,伦敦");
	strTimeZones = g_sLangTxt_State_UTC_DubEdinhLisLon;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+1:00)布鲁塞尔,哥本哈根,马德里,巴黎,中非西部");
	strTimeZones = g_sLangTxt_State_UTC_POneBCMPWAfrica;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+2:00)开罗,雅典,耶路撒冷");
	strTimeZones = g_sLangTxt_State_UTC_PTwoCAJerusalem;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+3:00)巴格达,科威特,莫斯科,圣彼得比");
	strTimeZones = g_sLangTxt_State_UTC_PThreeBKMPeterby;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+4:00)阿布扎比,巴库");
	strTimeZones = g_sLangTxt_State_UTC_PFourAbuDhabiBaku;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+5:00)伊斯兰堡,卡拉奇");
	strTimeZones = g_sLangTxt_State_UTC_PFiveIslamabadKarachi;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+6:00)阿斯塔纳");
	strTimeZones = g_sLangTxt_State_UTC_PSixAstana;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+7:00)曼谷,河内,雅加达");
	strTimeZones = g_sLangTxt_State_UTC_PSevenBHJakarta;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+8:00)北京,重庆,香港,乌鲁木齐");
	strTimeZones = g_sLangTxt_State_UTC_PEightBCHUrumqi;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+9:00)东京,首尔,平壤");
	strTimeZones = g_sLangTxt_State_UTC_PNineTSPyongyang;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+10:00)堪培拉,墨尔本,悉尼");
	strTimeZones = g_sLangTxt_State_UTC_PTenCMSydney;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+11:00)所罗门群岛,新喀里多尼亚");
	strTimeZones = g_sLangTxt_State_UTC_PSINCaledonia;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+12:00)斐济");
	strTimeZones = g_sLangTxt_State_UTC_PTwelveFiji;//lcq 3.30
	astrTimeZones.append(strTimeZones);


	m_pTimeZoneSet_ComboBox->addItems(astrTimeZones);
	m_pTimeZoneSet_HBoxLayout->addWidget(m_pTimeZoneSet_Label);
	m_pTimeZoneSet_HBoxLayout->addWidget(m_pTimeZoneSet_ComboBox);

	m_pOtherSet_VLayout->addLayout(m_pTimeZoneSet_HBoxLayout);
	m_pOtherSet_GridLayout = new QGridLayout;//dingxy 20240415 改为栅格布局
	m_pOtherSet_GridLayout->addWidget(m_pScreenBright_Label, 0, 0);
	m_pOtherSet_GridLayout->addWidget(m_pScreenBright_LineEdit, 0, 1);
	m_pOtherSet_GridLayout->addWidget(m_pReMarksScreen_Label, 0, 2);

	m_pOtherSet_GridLayout->addWidget(m_pBackLightTime_Label, 1, 0);
	m_pOtherSet_GridLayout->addWidget(m_pBackLightTime_LineEdit, 1, 1);
	m_pOtherSet_GridLayout->addWidget(m_pReMarks_Label, 1, 2);
	m_pFanMode_HBoxLayout->addWidget(m_pFanMode_Label);
	m_pFanMode_HBoxLayout->addWidget(m_pMute_RadioButton);
	m_pFanMode_HBoxLayout->addWidget(m_pNormal_RadioButton);
// 	m_pOtherSet_VLayout->addLayout(m_pBackLightTime_HBoxLayout);
	m_pOtherSet_VLayout->addLayout(m_pOtherSet_GridLayout);
	m_pOtherSet_VLayout->addLayout(m_pFanMode_HBoxLayout);
	m_pOtherSet_GroupBox->setLayout(m_pOtherSet_VLayout);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);//lcq 3.15
#ifdef _PSX_QT_WINDOWS_
	m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
#else
    m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
#endif

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel);//lcq 3.15
#ifdef _PSX_QT_WINDOWS_
	m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));
#else
	m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif
	m_pOkCancel_HBoxLayout = new QHBoxLayout(this);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	m_pAllVLayout->addWidget(m_p4GBlueTooth_GroupBox);
	m_pAllVLayout->addWidget(m_pOtherSet_GroupBox);
	m_pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);
	this->setLayout(m_pAllVLayout);
	InitDatas();
	connect(m_p4G_CheckBox, SIGNAL(clicked()), this, SLOT(slot_On4GBlueToothSetCheckChanged()));
	connect(m_pBlueTooth_CheckBox, SIGNAL(clicked()), this, SLOT(slot_On4GBlueToothSetCheckChanged()));
	connect(m_pWirelessNet_CheckBox, SIGNAL(clicked()), this, SLOT(slot_On4GBlueToothSetCheckChanged()));
	connect(m_pLocalNet_CheckBox, SIGNAL(clicked()), this, SLOT(slot_On4GBlueToothSetCheckChanged()));
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));

	connect(m_pNormal_RadioButton, SIGNAL(toggled(bool )), this, SLOT(slot_radio_NormalLogicChanged(bool)));
	connect(m_pMute_RadioButton, SIGNAL(toggled(bool )), this, SLOT(slot_radio_MuteLogicChanged(bool)));
}

void QHardwareSetDlg::ReleaseUI()
{

}

void QHardwareSetDlg::InitDatas()
{
	if (m_pSysParas == NULL)
	{
		return;
	}
	
// 	m_p4G_CheckBox->setChecked(m_pSysParas->m_oPeripheral.m_b4G);
// 	m_pBlueTooth_CheckBox->setChecked(m_pSysParas->m_oPeripheral.m_bBle);
// 	m_pWirelessNet_CheckBox->setChecked(m_pSysParas->m_oPeripheral.m_bNetWifi);
// 	m_pLocalNet_CheckBox->setChecked(m_pSysParas->m_oPeripheral.m_bNetRj45);
// 	m_pBackLightTime_LineEdit->SetValue(m_pSysParas->m_oPeripheral.m_nLcdTimes);
// 	m_pTimeZoneSet_ComboBox->setCurrentIndex(m_pSysParas->m_nTimeZone+12);

	if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
	{
		m_pOK_PushButton->setDisabled(true);
	}
	
	//2024-7-9 wuxinyi m_p4G_CheckBox����������
	//m_p4G_CheckBox->setVisible(false);
	Update4GEnable();
	g_oSttTestResourceMngr.InitLocalSysPara();
	m_pBlueTooth_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bBle);
	m_pWirelessNet_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bNetWifi);
	m_pLocalNet_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bNetRj45);
	m_pScreenBright_LineEdit->SetValue(g_oSystemParas.m_oPeripheral.m_nLcdLight);
	m_pBackLightTime_LineEdit->SetValue(g_oSystemParas.m_oPeripheral.m_nLcdTimes);
	m_pTimeZoneSet_ComboBox->setCurrentIndex(g_oSystemParas.m_nTimeZone+12);
	if (g_oSystemParas.m_nWindSpeed == 0)
	{
		m_pMute_RadioButton->setChecked(true);
		m_pNormal_RadioButton->setChecked(false);
	} 
	else
	{
		m_pNormal_RadioButton->setChecked(true);
		m_pMute_RadioButton->setChecked(false);
	}
}

void QHardwareSetDlg::Update4GEnable()
{
	m_pSttFrameConfig = CSttFrameConfig::g_pSttFrameConfig;
	CSttFrame_BarBase* pToolBar = m_pSttFrameConfig->GetToolBar();
	CExBaseList *pList = (CExBaseList*)pToolBar->FindByID("state-pic");

	//2024-7-9 wuxinyi ���Ӳ�����ô򿪴����ж�
	if(!pList)
	{
		return;
	}

	POS pos = pList->GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	while (pos != NULL)
	{
		pCurObj = pList->GetNext(pos);
		if (pCurObj->m_strID == HARDWARESET_4G)
		{
			m_p4G_CheckBox->setVisible(true);
			m_p4G_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_b4G);
		}
	}
}

void QHardwareSetDlg::slot_On4GBlueToothSetCheckChanged()
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender());

	if (m_p4G_CheckBox->isChecked() && m_pBlueTooth_CheckBox->isChecked())
	{
		if (pCheckBox == m_p4G_CheckBox)
		{
			m_pBlueTooth_CheckBox->setChecked(false);
		} 
		else
		{
			m_p4G_CheckBox->setChecked(false);
		}
	}
	else if ((!m_p4G_CheckBox->isChecked()) && (!m_pBlueTooth_CheckBox->isChecked()))
	{
		if (pCheckBox == m_p4G_CheckBox)
		{
			m_pBlueTooth_CheckBox->setChecked(true);
		} 
		else
		{
			m_p4G_CheckBox->setChecked(true);
		}
	}
	else if (m_pWirelessNet_CheckBox->isChecked() && m_pLocalNet_CheckBox->isChecked())
	{
		if (pCheckBox == m_pWirelessNet_CheckBox)
		{
			m_pLocalNet_CheckBox->setChecked(false);
		} 
		else
		{
			m_pWirelessNet_CheckBox->setChecked(false);
		}
	}
	else if ((!m_pWirelessNet_CheckBox->isChecked()) && (!m_pLocalNet_CheckBox->isChecked()))
	{
		if (pCheckBox == m_pWirelessNet_CheckBox)
		{
			m_pLocalNet_CheckBox->setChecked(true);
		} 
		else
		{
			m_pWirelessNet_CheckBox->setChecked(true);
		}
	}
}

void QHardwareSetDlg::slot_OKClicked()
{
	m_pSysParas->m_oPeripheral.m_b4G = m_p4G_CheckBox->isChecked();
	m_pSysParas->m_oPeripheral.m_bBle = m_pBlueTooth_CheckBox->isChecked();
	m_pSysParas->m_oPeripheral.m_bNetWifi = m_pWirelessNet_CheckBox->isChecked();
	m_pSysParas->m_oPeripheral.m_bNetRj45 = m_pLocalNet_CheckBox->isChecked();
	m_pSysParas->m_nTimeZone = m_pTimeZoneSet_ComboBox->currentIndex() - 12;
	m_pSysParas->m_oPeripheral.m_nLcdTimes = m_pBackLightTime_LineEdit->GetValue();
	m_pSysParas->m_oPeripheral.m_nLcdLight = m_pScreenBright_LineEdit->GetValue();

	this->accept();
}

void QHardwareSetDlg::slot_CancelClicked()
{
	close();
}
void QHardwareSetDlg::slot_radio_NormalLogicChanged(bool ret)
{
	if (ret)
	{
		m_pSysParas->m_nWindSpeed = 1;
	} 
	else
	{
		m_pSysParas->m_nWindSpeed = 0;
	}
}
void QHardwareSetDlg::slot_radio_MuteLogicChanged(bool ret)
{
	if (ret)
	{
		m_pSysParas->m_nWindSpeed = 0;
	} 
	else
	{
		m_pSysParas->m_nWindSpeed = 1;
	}
}