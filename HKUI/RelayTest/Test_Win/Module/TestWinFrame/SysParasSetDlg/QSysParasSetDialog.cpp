#include "QSysParasSetDialog.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../Module/Engine/SttPowerTestEngineBase.h"
#include "../testwinbase.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

QSysParasSetDialog::QSysParasSetDialog(QWidget *parent)
	: QDialog(parent)
{
	m_pVLayout = NULL;
	m_tabWidget = NULL;
//	m_pChMapsWiget = NULL;
	m_pWeakSetWiget = NULL;
	m_pSysParasWiget = NULL;
//	m_pModuleSetWiget = NULL;
	m_bOutputTypeHasChanged = FALSE;

	setWindowIcon (QPixmap( ":/images/setCommon.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("系统参数")*/g_sLangTxt_SystemPara);
}

QSysParasSetDialog::~QSysParasSetDialog()
{
	ReleaseUI();
}

void QSysParasSetDialog::ReleaseUI()
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

void QSysParasSetDialog::initUI()
{
	ReleaseUI();

	resize(600, 600);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	m_pVLayout = new QVBoxLayout;
	m_tabWidget = new QTabWidget(this);
//	m_pChMapsWiget = new QChMapsWidget(this);
	m_pSysParasWiget = new QSysParasWidget(this);
//	m_pModuleSetWiget = new QModuleSetWidget(this);

//	m_tabWidget->addTab(m_pChMapsWiget,tr("通道资源映射"));
	m_tabWidget->addTab(m_pSysParasWiget,/*tr("系统参数设置")*/g_sLangTxt_IEC_SysParasSet);

	if (g_oLocalSysPara.m_nSupportWeakOutput)
	{
		m_pWeakSetWiget = new QWeakSetWidget(this);
		m_tabWidget->addTab(m_pWeakSetWiget,/*tr("弱信号设置")*/g_sLangTxt_IEC_IEC_WeakSet);
	}

//	m_tabWidget->addTab(m_pModuleSetWiget,tr("模块设置"));
	m_pVLayout->addWidget(m_tabWidget);

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( "./images/Cancel.png"));

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

//	m_pChMapsWiget->initUI(&m_oSysParas,&m_oSttChMaps);

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

void QSysParasSetDialog::DisEnableDigitalUI()
{
	m_pSysParasWiget->DisEnableDigitalUI();
}

void QSysParasSetDialog::DisEnableWeekUI()
{
	m_pSysParasWiget->DisEnableWeekUI();
}

void QSysParasSetDialog::InitDatas()
{
	m_oSttChMaps.DeleteAll();
	g_oSttTestResourceMngr.m_oChMaps.Copy(&m_oSttChMaps);
	g_oSystemParas.CopyOwn(&m_oSysParas);
}

void QSysParasSetDialog::slot_OKClicked()
{
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

	g_oSttTestResourceMngr.m_oIecDatasMngr.UpdateFT3ChsType(g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nIecFormatMeas);//20230118 suyang 更新FT3通道类型
	g_TestWinBase->UpdateFreq();
//	emit sig_SysParasHasChanged(bOutputTypeHasChanged);
	accept();
}

void QSysParasSetDialog::slot_CancelClicked()
{
	close();
}

void QSysParasSetDialog::slot_TabChanged(QWidget *pCurWidget)
{
	if ((pCurWidget == m_pWeakSetWiget)&&(m_pWeakSetWiget != NULL))
	{
		m_pWeakSetWiget->ShowDatas();
	}
}