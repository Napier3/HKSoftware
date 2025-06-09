#include "QModuleSetDlg.h"
#include <QDirIterator>
#include "../../../SttCmd/SttParas.h"
#include "../../../SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../CommonMethod/commonMethod.h"
#include "../../Module/XLangResource_Native.h"

extern CFont *g_pSttGlobalFont;  

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
	InitDatas();
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
	m_pModuleSetWidget->initUI(&m_oSysParas);

}

void QModuleSetDlg::slot_OKClicked()
{
	m_pModuleSetWidget->SaveDatas();
	BOOL bMergeCurrHasChanged = m_oSysParas.m_oGearSetCurModules.MergeCurrHasChanged(&g_oSystemParas.m_oGearSetCurModules);
	m_oSysParas.m_oGearSetCurModules.CopyOwn(&g_oSystemParas.m_oGearSetCurModules);
	g_oSttTestResourceMngr.SaveSystemParasFile();

	if ((bMergeCurrHasChanged)&&(g_oSystemParas.m_nHasAnalog))
	{
		g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital);
		g_oSttTestResourceMngr.SaveCurChMapsFile();
	}
	emit sig_UpdateModulesGear(bMergeCurrHasChanged);
	close();
}

void QModuleSetDlg::slot_CancelClicked()
{
	close();
}
