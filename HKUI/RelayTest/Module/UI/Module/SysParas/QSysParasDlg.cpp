#include "QSysParasDlg.h"
#include "../../../Module/Engine/SttPowerTestEngineBase.h"
//#include "testwinbase.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_	
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

QSysParasDlg::QSysParasDlg(QWidget *parent)
	: QDialog(parent)
{
	m_pVLayout = NULL;
	m_tabWidget = NULL;
//	m_pChMapsWiget = NULL;
	m_pWeakSetWiget = NULL;
	m_pSysParasWiget = NULL;
//	m_pModuleSetWiget = NULL;
	m_bOutputTypeHasChanged = FALSE;
	m_nSysConfig_Mode = STT_HTML_SYSCONFIG_MODE_UPDATE;

}

QSysParasDlg::~QSysParasDlg()
{
	ReleaseUI();
}

void QSysParasDlg::ReleaseUI()
{
// 	if (m_pChMapsWiget != NULL)
// 	{
// 		delete m_pChMapsWiget;
// 		m_pChMapsWiget = NULL;
// 	}

	if (m_pWeakSetWiget != NULL)
	{
		delete m_pWeakSetWiget;
		m_pWeakSetWiget = NULL;
	}

	if (m_pSysParasWiget != NULL)
	{
		delete m_pSysParasWiget;
		m_pSysParasWiget = NULL;
	}

// 	if (m_pModuleSetWiget != NULL)
// 	{
// 		delete m_pModuleSetWiget;
// 		m_pModuleSetWiget = NULL;
// 	}

	if (m_tabWidget != NULL)
	{
		delete m_tabWidget;
		m_tabWidget = NULL;
	}
	if (m_pVLayout != NULL)
	{
		delete m_pVLayout;
		m_pVLayout = NULL;
	}
}

void QSysParasDlg::initUI()
{
	ReleaseUI();
	CString strTemp;
	QString strPixPath = _P_GetResourcePath();
#ifdef _PSX_QT_WINDOWS_
	strTemp = strPixPath + "setCommon.png";
#else
    strTemp = ":/ctrls/images/setCommon.png";
#endif
	setWindowIcon(QPixmap(strTemp));
// 	setWindowFlags(Qt::WindowCloseButtonHint);
	xlang_GetLangStrByFile(strTemp,"sSystemPara");//系统参数
	setWindowTitle(strTemp);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::NonModal);

    resize(600, 400);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pVLayout = new QVBoxLayout;
	m_tabWidget = new QTabWidget(this);
//	m_pChMapsWiget = new QChMapsWidget(this);
	m_pSysParasWiget = new QSysParasWidget(this);
//	m_pModuleSetWiget = new QModuleSetWidget(this);

//	m_tabWidget->addTab(m_pChMapsWiget,tr("通道资源映射"));
	xlang_GetLangStrByFile(strTemp,"IEC_SysParasSet");//系统参数设置
	m_tabWidget->addTab(m_pSysParasWiget,strTemp);
	m_tabWidget->setFont(*g_pSttGlobalFont);

	if (g_oLocalSysPara.m_nSupportWeakOutput)
	{
		m_pWeakSetWiget = new QWeakSetWidget(this);
		m_tabWidget->addTab(m_pWeakSetWiget,/*tr("弱信号设置")*/g_sLangTxt_IEC_IEC_WeakSet); //lcq
	}

//	m_tabWidget->addTab(m_pModuleSetWiget,tr("模块设置"));
	m_pVLayout->addWidget(m_tabWidget);

	m_pOK_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sOK");//确定
	m_pOK_PushButton->setText(strTemp);
	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
#ifdef _PSX_QT_WINDOWS_
	strTemp = strPixPath + "check.png";
#else
    strTemp = ":/ctrls/images/check.png";
#endif
	m_pOK_PushButton->setIcon (QPixmap(strTemp));

	m_pCancel_PushButton = new QPushButton(this);
	xlang_GetLangStrByFile(strTemp,"sCancel");//取消
	m_pCancel_PushButton->setText(strTemp);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
#ifdef _PSX_QT_WINDOWS_
	strTemp = strPixPath + "Cancel.png";
#else
	strTemp = ":/ctrls/images/Cancel.png";
#endif
	m_pCancel_PushButton->setIcon (QPixmap(strTemp));

	m_pHBoxLayout = new QHBoxLayout;
	m_pHBoxLayout->addStretch();
	m_pHBoxLayout->addWidget(m_pOK_PushButton);
	m_pHBoxLayout->addSpacing(20);
	m_pHBoxLayout->addWidget(m_pCancel_PushButton);
	m_pHBoxLayout->addStretch();
	m_pHBoxLayout->setContentsMargins(3,3,3,3);
	m_pHBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pVLayout->addLayout(m_pHBoxLayout);

	InitDatas();

	//m_pChMapsWiget->initUI(&m_oSysParas,&m_oSttChMaps);

	if (g_oLocalSysPara.m_nSupportWeakOutput)
	{
		m_pWeakSetWiget->initUI(&m_oSttChMaps);
	}

	m_pSysParasWiget->initUI(&m_oSysParas);
//	m_pModuleSetWiget->initUI(&m_oSysParas);

	m_pVLayout->setContentsMargins(3,0,0,0);
	m_pVLayout->setSpacing(0);
	this->setLayout(m_pVLayout);

	m_pOK_PushButton->setFocusPolicy(Qt::NoFocus);
	m_pCancel_PushButton->setFocusPolicy(Qt::NoFocus);
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_tabWidget, SIGNAL(currentChanged(QWidget *)), this, SLOT(slot_TabChanged(QWidget *)));
}

void QSysParasDlg::DisEnableDigitalUI()
{
	m_pSysParasWiget->DisEnableDigitalUI();
}

void QSysParasDlg::DisEnableWeekUI()
{
	m_pSysParasWiget->DisEnableWeekUI();
}

void QSysParasDlg::InitDatas()
{
	m_oSttChMaps.DeleteAll();
	g_oSttTestResourceMngr.m_oChMaps.Copy(&m_oSttChMaps);
	g_oSystemParas.CopyOwn(&m_oSysParas);
}

void QSysParasDlg::slot_OKClicked()
{
	ExitHideKeyboardWidget();
	m_pOK_PushButton->setEnabled(false);
	CTickCount32 oTickCount;
	oTickCount.DoEvents(10);
//	m_pChMapsWiget->SaveDatas();

	if (g_oLocalSysPara.m_nSupportWeakOutput)
	{
		m_pWeakSetWiget->SaveDatas();
	}

	m_pSysParasWiget->SaveDatas();
//	m_pModuleSetWiget->SaveDatas();
	m_bOutputTypeHasChanged = m_oSysParas.OutputTypeHasChanged(&g_oSystemParas);
	m_oSysParas.CopyOwn(&g_oSystemParas);

	if (/*(!bOutputTypeHasChanged)&&*/(g_oLocalSysPara.m_nSupportWeakOutput)&&(g_oSystemParas.m_nHasWeek))//如果输出支持弱信号输出,并且当前输出弱信号
	{
		g_oSttTestResourceMngr.m_oChMaps.DeleteAll();
		m_oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);

		m_bOutputTypeHasChanged = TRUE;
	}
	else if (m_bOutputTypeHasChanged)//如果不支持弱信号输出,并且勾选了弱信号,输出类型发生了改变,则重新进行缺省映射
	{
		g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital);
		g_oSttTestResourceMngr.SaveCurChMapsFile();
	}

	if ((g_oLocalSysPara.m_nSupportWeakOutput)&&(g_oSystemParas.m_nHasWeek))//20220507 如果支持弱信号输出,则保存弱信号配置
	{
		g_oSttTestResourceMngr.SaveCurChMapsFile();
	}
//	emit sig_SysParasHasChanged(bOutputTypeHasChanged);
	accept();

	double dStabTimeMs = m_oSysParas.m_fStabTime;
	double dStabTimeS = dStabTimeMs/1000;
	m_oSysParas.m_fStabTime = dStabTimeS;

	g_oSttTestResourceMngr.SaveSystemParasFile();

	if (m_nSysConfig_Mode == STT_HTML_SYSCONFIG_MODE_UPDATE)
	{
		g_theTestCntrFrame->UpdateSysConfig();
	}
	else
	{
		g_theTestCntrFrame->New_SysConfig();
	}
}

void QSysParasDlg::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
}
void QSysParasDlg::slot_TabChanged(QWidget *pCurWidget)
{
	if ((pCurWidget == m_pWeakSetWiget)&&(m_pWeakSetWiget != NULL))
	{
		m_pWeakSetWiget->ShowDatas();
	}
}