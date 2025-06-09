#include "QModuleSetDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../CommonMethod/commonMethod.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"

extern QFont *g_pSttGlobalFont;  

QModuleSetDlg::QModuleSetDlg(QWidget *parent)
	: QDialog(parent)
{
	//CString strText;
	//strText = _T("输出功率设置";
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(g_sLangTxt_Outputpower);
	m_pModuleSetWidget = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
}

QModuleSetDlg::~QModuleSetDlg()
{

}

void QModuleSetDlg::initUI()
{
	ReleaseUI();
	resize(300, 230);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

//  	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//  	sizePolicy.setHorizontalStretch(30);
//  	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pModuleSetWidget = new QModuleSetWidget(this);
	m_pAllVLayout->addWidget(m_pModuleSetWidget);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CString strText;
	//strText = _T("确定");
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(g_sLangTxt_OK);
#ifdef _PSX_QT_WINDOWS_
	m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
#else
    m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
#endif

	//strText = _T("取消");
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Cancel);
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
	m_pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);
	this->setLayout(m_pAllVLayout);

	if (!g_oSttTestResourceMngr.HasLoadDevice())//如果没有加载通道映射文件,主动加载通道映射文件
	{
	if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
	{
		m_pOK_PushButton->setDisabled(true);
	}
	}

	m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);

	g_oSttTestResourceMngr.InitLocalSysPara();
	//InitDatas();
	m_pModuleSetWidget->initUI();
 	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
 	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QModuleSetDlg::ReleaseUI()
{

}

void QModuleSetDlg::InitDatas()
{
// 	m_pSysParas = pSysParas;
	g_oSystemParas.m_oGearSetCurModules.CopyOwn(&m_oSysParas.m_oGearSetCurModules);
	//m_pModuleSetWidget->initUI(&m_oSysParas);
	m_pModuleSetWidget->SetSysParas(&m_oSysParas);
	m_pModuleSetWidget->InitDatas();
	m_pModuleSetWidget->UpdateCurSelModuleUI();
}

void QModuleSetDlg::slot_OKClicked()
{
	m_pModuleSetWidget->SaveDatas();
	BOOL bMergeCurrHasChanged = m_oSysParas.m_oGearSetCurModules.MergeCurrHasChanged(&g_oSystemParas.m_oGearSetCurModules);
	m_oSysParas.m_oGearSetCurModules.CopyOwn(&g_oSystemParas.m_oGearSetCurModules);
	g_oSttTestResourceMngr.SaveSystemParasFile();
	BOOL bCurrModulePowerHigh = FALSE;
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	if ((pCurDevice->m_strModel == _T("PNS330-6")) || (pCurDevice->m_strModel == _T("PNS330-6A")) || (pCurDevice->m_strModel == _T("PNS330-6M")))
	{
		long nIPowerMode = g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear[0].m_nIPowerMode;
		if (nIPowerMode == STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A)
			bCurrModulePowerHigh = TRUE;
	}

	if ((bMergeCurrHasChanged)&&(g_oSystemParas.m_nHasAnalog))
	{
		g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital);
		g_oSttTestResourceMngr.SaveCurChMapsFile();
	}
	emit sig_UpdateModulesGear(bMergeCurrHasChanged, bCurrModulePowerHigh);
	close();
}

void QModuleSetDlg::slot_CancelClicked()
{
	close();
}

void QModuleSetDlg::slot_UpdateModulesGearSwitchInfo()
{
	InitDatas();
}