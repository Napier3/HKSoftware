#include "QModuleSetDlg.h"
#include <QDirIterator>
#include "../../../../Module/SttCmd/SttParas.h"
#include "../../../../Module/SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../CommonMethod/commonMethod.h"
#include "../ReportView/XLangResource_PowerTestWin.h"


QModuleSetDlg::QModuleSetDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon (QIcon(":/image/set.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("输出功率设置")*/g_sLangTxt_Outputpower);
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


	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));

	m_pHBoxLayout2 = new QHBoxLayout(this);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->addWidget(m_pOK_PushButton);
	m_pHBoxLayout2->addSpacing(10);
	m_pHBoxLayout2->addWidget(m_pCancel_PushButton);
	m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->setDirection(QBoxLayout::LeftToRight);
	m_pAllVLayout->addLayout(m_pHBoxLayout2);
	this->setLayout(m_pAllVLayout);

	if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
	{
		m_pOK_PushButton->setDisabled(true);
	}

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
