#include "QHardwareSetDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../CommonMethod/commonMethod.h"
#include "../Module/XLangResource_Native.h"

QHardwareSetDlg::QHardwareSetDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	//setWindowTitle(tr("Ӳ����Ϣ����"));
	setWindowTitle(g_sLangTxt_State_HardwareInformationSettings); //Ӳ����Ϣ���� lcq 3.15
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
	strTmp = _T("4G������������ʹ��");

	if (!xlang_IsCurrXLanguageChinese()/*g_oSttSystemConfig.GetDevModel() == "L336EXi"*/)
	{
		strTmp = _T("Communication");//20240622 suyang ӦҪ����Ӣ�����ΪCommunication
	}
	else
	{
	xlang_GetLangStrByFile(strTmp,"State_FGBlueNetworkcar");   //LCQ
		
	}

	m_p4GBlueTooth_GroupBox = new QGroupBox(strTmp);
	strTmp = _T("4G");
	m_p4G_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("����");
	xlang_GetLangStrByFile(strTmp,"State_Bluetooth");   //LCQ
	m_pBlueTooth_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("��������");
	xlang_GetLangStrByFile(strTmp,"State_Wirelesscard");   //LCQ
	m_pWirelessNet_CheckBox = new QSttCheckBox(strTmp);
	strTmp = _T("��������");
	xlang_GetLangStrByFile(strTmp,"State_NativeNetworkcard");   //LCQ
	m_pLocalNet_CheckBox = new QSttCheckBox(strTmp);
	m_p4GBlueTooth_HBoxLayout = new QHBoxLayout;
	m_p4GBlueTooth_HBoxLayout->addWidget(m_p4G_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pBlueTooth_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pWirelessNet_CheckBox);
	m_p4GBlueTooth_HBoxLayout->addWidget(m_pLocalNet_CheckBox);

	m_p4GBlueTooth_GroupBox->setLayout(m_p4GBlueTooth_HBoxLayout);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	strTmp = _T("��������");
	xlang_GetLangStrByFile(strTmp,"State_Othersettings");   //LCQ
	m_pOtherSet_GroupBox = new QGroupBox(strTmp);
	m_pOtherSet_VLayout = new QVBoxLayout;
// 	m_pBackLightTime_HBoxLayout = new QHBoxLayout;

	strTmp = _T("��Ļ����(1-5)");
	xlang_GetLangStrByFile(strTmp,"State_MinScreenBright");
	m_pScreenBright_Label = new QLabel(strTmp);
	m_pScreenBright_LineEdit = new QLongLineEdit;
	m_pScreenBright_LineEdit->InitCoverage(1,5);
	strTmp = _T("(��ע:5��������)");
	xlang_GetLangStrByFile(strTmp,"State_NoteFivemeansBrightest");
	m_pReMarksScreen_Label = new QLabel(strTmp);

	strTmp = _T("����ʱ��(����)");
	xlang_GetLangStrByFile(strTmp,"State_MinBacklighttime");   //LCQ
	m_pBackLightTime_Label = new QLabel(strTmp);
	m_pBackLightTime_LineEdit = new QLongLineEdit;
	m_pBackLightTime_LineEdit->InitCoverage(0,60);
	strTmp = _T("(��ע:0������)");
	xlang_GetLangStrByFile(strTmp,"State_NoteZeromeansAlwayson");   //LCQ
	m_pReMarks_Label = new QLabel(strTmp);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pBackLightTime_Label);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pBackLightTime_LineEdit);
// 	m_pBackLightTime_HBoxLayout->addWidget(m_pReMarks_Label);

	//20241128 suyang ӦҪ����ʾ
// 	strTmp = _T("����ɢ�ȷ���ģʽ");
// 	xlang_GetLangStrByFile(strTmp,"State_FanMode");
// 	m_pFanMode_Label = new QLabel(strTmp);
// 
// 	strTmp = _T("����");
// 	xlang_GetLangStrByFile(strTmp,"State_Normal");
// 	m_pNormal_RadioButton = new QRadioButton(strTmp);
// 	strTmp = _T("����");
// 	xlang_GetLangStrByFile(strTmp,"State_Mute");
// 	m_pMute_RadioButton = new QRadioButton(strTmp);
// 	m_pFanModeBtnGroup = new QButtonGroup(this);
// 	m_pFanModeBtnGroup->addButton(m_pMute_RadioButton,0);
// 	m_pFanModeBtnGroup->addButton(m_pNormal_RadioButton,1);
// 	m_pFanModeBtnGroup->setExclusive(true);


	m_pTimeZoneSet_HBoxLayout = new QHBoxLayout;
// 	m_pFanMode_HBoxLayout = new QHBoxLayout;
	strTmp = _T("ʱ������");
	xlang_GetLangStrByFile(strTmp,"State_Timezonesetting");   //LCQ
	m_pTimeZoneSet_Label = new QLabel(strTmp);
	m_pTimeZoneSet_ComboBox = new QScrollComboBox;
	QStringList astrTimeZones;
	CString strTimeZones;

	//strTimeZones = _T("(UTC-12:00)�������ڱ������");
	strTimeZones = g_sLangTxt_State_UTC_TwelveWIntDLine; //lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-11:00)Э������ʱ-11");
	strTimeZones = g_sLangTxt_State_UTC_ElevenCUTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-10:00)������Ⱥ��");
	strTimeZones = g_sLangTxt_State_UTC_TenAleutianIslands;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-9:00)����˹��");
	strTimeZones = g_sLangTxt_State_UTC_NineAlaska;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-8:00)̫ƽ��ʱ��(�����ͼ��ô�)");//lcq 3.30
	strTimeZones = g_sLangTxt_State_UTC_EUCPacificTime;
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-7:00)������,����˹,��������");//lcq 3.30
	strTimeZones = g_sLangTxt_State_UTC_SevenCLM;
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-6:00)������");
	strTimeZones = g_sLangTxt_State_UTC_SixCentralAmerica;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-5:00)����ʱ��(�����ͼ��ô�)");
	strTimeZones = g_sLangTxt_State_UTC_FiveUCEasternTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-4:00)������ʱ��(���ô�)");
	strTimeZones = g_sLangTxt_State_UTC_FourCanadaAtlanticTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-3:00)������");
	strTimeZones = g_sLangTxt_State_UTC_ThreeGreenland;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-2:00)Э������ʱ-2");
	strTimeZones = g_sLangTxt_State_UTC_TwoCooUniversalTime;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC-1:00)��ý�Ⱥ��,���ٶ�Ⱥ��");
	strTimeZones = g_sLangTxt_State_UTC_OneCapIslandsAzores;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC)������,������,��˹��,�׶�");
	strTimeZones = g_sLangTxt_State_UTC_DubEdinhLisLon;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+1:00)��³����,�籾����,�����,����,�з�����");
	strTimeZones = g_sLangTxt_State_UTC_POneBCMPWAfrica;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+2:00)����,�ŵ�,Ү·����");
	strTimeZones = g_sLangTxt_State_UTC_PTwoCAJerusalem;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+3:00)�͸��,������,Ī˹��,ʥ�˵ñ�");
	strTimeZones = g_sLangTxt_State_UTC_PThreeBKMPeterby;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+4:00)��������,�Ϳ�");
	strTimeZones = g_sLangTxt_State_UTC_PFourAbuDhabiBaku;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+5:00)��˹����,������");
	strTimeZones = g_sLangTxt_State_UTC_PFiveIslamabadKarachi;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+6:00)��˹����");
	strTimeZones = g_sLangTxt_State_UTC_PSixAstana;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+7:00)����,����,�żӴ�");
	strTimeZones = g_sLangTxt_State_UTC_PSevenBHJakarta;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+8:00)����,����,���,��³ľ��");
	strTimeZones = g_sLangTxt_State_UTC_PEightBCHUrumqi;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+9:00)����,�׶�,ƽ��");
	strTimeZones = g_sLangTxt_State_UTC_PNineTSPyongyang;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+10:00)������,ī����,Ϥ��");
	strTimeZones = g_sLangTxt_State_UTC_PTenCMSydney;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+11:00)������Ⱥ��,�¿��������");
	strTimeZones = g_sLangTxt_State_UTC_PSINCaledonia;//lcq 3.30
	astrTimeZones.append(strTimeZones);
	//strTimeZones = _T("(UTC+12:00)쳼�");
	strTimeZones = g_sLangTxt_State_UTC_PTwelveFiji;//lcq 3.30
	astrTimeZones.append(strTimeZones);


	m_pTimeZoneSet_ComboBox->addItems(astrTimeZones);
	m_pTimeZoneSet_HBoxLayout->addWidget(m_pTimeZoneSet_Label);
	m_pTimeZoneSet_HBoxLayout->addWidget(m_pTimeZoneSet_ComboBox);

	m_pOtherSet_VLayout->addLayout(m_pTimeZoneSet_HBoxLayout);
	m_pOtherSet_GridLayout = new QGridLayout;//dingxy 20240415 ��Ϊդ�񲼾�
	m_pOtherSet_GridLayout->addWidget(m_pScreenBright_Label, 0, 0);
	m_pOtherSet_GridLayout->addWidget(m_pScreenBright_LineEdit, 0, 1);
	m_pOtherSet_GridLayout->addWidget(m_pReMarksScreen_Label, 0, 2);

	m_pOtherSet_GridLayout->addWidget(m_pBackLightTime_Label, 1, 0);
	m_pOtherSet_GridLayout->addWidget(m_pBackLightTime_LineEdit, 1, 1);
	m_pOtherSet_GridLayout->addWidget(m_pReMarks_Label, 1, 2);
// 	m_pFanMode_HBoxLayout->addWidget(m_pFanMode_Label);
// 	m_pFanMode_HBoxLayout->addWidget(m_pMute_RadioButton);
// 	m_pFanMode_HBoxLayout->addWidget(m_pNormal_RadioButton);
	// 	m_pOtherSet_VLayout->addLayout(m_pBackLightTime_HBoxLayout);
#ifndef _PSX_OS_CENTOS_
	m_pOtherSet_VLayout->addLayout(m_pOtherSet_GridLayout);
// 	m_pOtherSet_VLayout->addLayout(m_pFanMode_HBoxLayout);
#endif
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

#ifndef _PSX_OS_CENTOS_
	m_pAllVLayout->addWidget(m_p4GBlueTooth_GroupBox);
#endif
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

// 	connect(m_pNormal_RadioButton, SIGNAL(toggled(bool )), this, SLOT(slot_radio_NormalLogicChanged(bool)));
// 	connect(m_pMute_RadioButton, SIGNAL(toggled(bool )), this, SLOT(slot_radio_MuteLogicChanged(bool)));
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

	if (!g_oSttTestResourceMngr.HasLoadDevice())//���û�м���ͨ��ӳ���ļ�,��������ͨ��ӳ���ļ�
	{
	if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
	{
		m_pOK_PushButton->setDisabled(true);
	}
	}

	m_p4G_CheckBox->setVisible(false);
	Update4GEnable();
	g_oSttTestResourceMngr.InitLocalSysPara();
	m_pBlueTooth_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bBle);
	m_pWirelessNet_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bNetWifi);
	m_pLocalNet_CheckBox->setChecked(g_oSystemParas.m_oPeripheral.m_bNetRj45);
	m_pScreenBright_LineEdit->SetValue(g_oSystemParas.m_oPeripheral.m_nLcdLight);
	m_pBackLightTime_LineEdit->SetValue(g_oSystemParas.m_oPeripheral.m_nLcdTimes);
	m_pTimeZoneSet_ComboBox->setCurrentIndex(g_oSystemParas.m_nTimeZone+12);
// 	if (g_oSystemParas.m_nWindSpeed == 0)
// 	{
// 		m_pMute_RadioButton->setChecked(true);
// 		m_pNormal_RadioButton->setChecked(false);
// 	} 
// 	else
// 	{
// 		m_pNormal_RadioButton->setChecked(true);
// 		m_pMute_RadioButton->setChecked(false);
// 	}
}

void QHardwareSetDlg::Update4GEnable()
{
	m_pSttFrameConfig = CSttFrameConfig::g_pSttFrameConfig;
	CSttFrame_BarBase* pToolBar = m_pSttFrameConfig->GetToolBar();
	CExBaseList *pList = (CExBaseList*)pToolBar->FindByID("state-pic");
	if (pList == NULL)
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
