#include "QChMapsDlg.h"
#include <QDirIterator>
#include "../../../../Module/SttCmd/SttParas.h"
#include "../../../../Module/SttGlobalDef.h"
#include "../../../../../Module/System/TickCount32.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../CommonMethod/commonMethod.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
#include "../../../..//Module/SttSystemConfig/SttSystemConfig.h"

bool SpaceKeyFilter::eventFilter( QObject *obj, QEvent *event )
{
	if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Space)
		{
			// 忽略空格键事件
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

/////////////////////////////////////////////////////////////////////////

QChMapsDlg::QChMapsDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon (QIcon(":/image/set.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("通道映射设置")*/g_sLangTxt_ChMaps_Title);
	m_pChMapsWidget = NULL;
	m_pOK_PushButton = NULL;
	m_pCancel_PushButton = NULL;
}

QChMapsDlg::~QChMapsDlg()
{

}

void QChMapsDlg::initUI()
{
	ReleaseUI();
	long nType = g_oSttTestResourceMngr.m_pTestResouce->GetTestRsType();
	if ((nType == STT_TEST_RESOURCE_TYPE_4U3I) || (nType == STT_TEST_RESOURCE_TYPE_6U6I))
	{
		resize(950, 820);
	}
	else
	{
		resize(600, 600);
	}
 	
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

//  	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//  	sizePolicy.setHorizontalStretch(30);
//  	sizePolicy.setVerticalStretch(30);

	m_pAllVLayout = new QVBoxLayout(this);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pChMapsWidget = new QChMapsWidget(this);
	m_pAllVLayout->addWidget(m_pChMapsWidget);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_pLockMaps_CheckBox = new QCheckBox/*(m_pOutputSel_GroupBox)*/;
	m_pLockMaps_CheckBox->setText("锁定映射");
	m_pLockMaps_CheckBox->setChecked(false);

	m_pDefautMaps_PButton = new QPushButton(this);
	m_pDefautMaps_PButton->setText(/*tr("设置缺省映射")*/g_sLangTxt_ChMaps_DefautMaps);
	m_pDefautMaps_PButton->setEnabled(true);

	m_pImportChMaps_PButton = new QPushButton(this);
	m_pImportChMaps_PButton->setText(/*tr("导入通道映射")*/g_sLangTxt_ChMaps_ImportChMaps);
	m_pImportChMaps_PButton->setEnabled(true);

	m_pExportChMaps_PButton = new QPushButton(this);
	m_pExportChMaps_PButton->setText(/*tr("导出通道映射")*/g_sLangTxt_ChMaps_ExportChMaps);
	m_pExportChMaps_PButton->setEnabled(true);

	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("确定")*/g_sLangTxt_OK);
	m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));

	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);
	m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));

	m_pHBoxLayout2 = new QHBoxLayout(this);
	//m_pHBoxLayout2->addStretch();
	m_pHBoxLayout2->addSpacing(10);
	m_pHBoxLayout2->addWidget(m_pLockMaps_CheckBox);
	m_pHBoxLayout2->addSpacing(20);
	m_pHBoxLayout2->addWidget(m_pDefautMaps_PButton);
	m_pHBoxLayout2->addSpacing(10);
	m_pHBoxLayout2->addWidget(m_pImportChMaps_PButton);
	m_pHBoxLayout2->addSpacing(10);
	m_pHBoxLayout2->addWidget(m_pExportChMaps_PButton);
	m_pHBoxLayout2->addSpacing(200);
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
	connect(m_pDefautMaps_PButton, SIGNAL(clicked()), m_pChMapsWidget, SLOT(slot_DefautMapsClicked()));
 	connect(m_pImportChMaps_PButton, SIGNAL(clicked()), m_pChMapsWidget, SLOT(slot_ImportChMapsClicked()));
 	connect(m_pExportChMaps_PButton, SIGNAL(clicked()), m_pChMapsWidget, SLOT(slot_ExportChMapsClicked()));
// 	connect(m_pExportChMaps_PButton, SIGNAL(clicked()), m_pChMapsWidget, SLOT(slot_ExportChMapsClicked()));//2024-5-22 wuxinyi 多连接一次信号，导出通道映射按钮会按下两次

	if (g_oSttSystemConfig.GetLockMaps() != 0)
	{
		m_pLockMaps_CheckBox->setChecked(true);
	}
	connect(m_pLockMaps_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_LockMapsChecked(int)));

	SpaceKeyFilter *pFilter = new SpaceKeyFilter();
	m_pImportChMaps_PButton->installEventFilter(pFilter);
	m_pLockMaps_CheckBox->installEventFilter(pFilter);
	m_pDefautMaps_PButton->installEventFilter(pFilter);
	m_pExportChMaps_PButton->installEventFilter(pFilter);
	m_pOK_PushButton->installEventFilter(pFilter);
	m_pCancel_PushButton->installEventFilter(pFilter);

}

void QChMapsDlg::ReleaseUI()
{

}

void QChMapsDlg::InitDatas()
{
	m_oSttChMaps.DeleteAll();
	g_oSttTestResourceMngr.m_oChMaps.Copy(&m_oSttChMaps);
	g_oSystemParas.CopyOwn(&m_oSysParas);
	m_pChMapsWidget->initUI(&m_oSysParas,&m_oSttChMaps);
}

void QChMapsDlg::slot_OKClicked()
{
	close();
	m_pChMapsWidget->SaveDatas();
	BOOL bSysParasHasChanged = FALSE;

	if ((m_oSysParas.m_nHasAnalog != g_oSystemParas.m_nHasAnalog)||(m_oSysParas.m_nHasDigital != g_oSystemParas.m_nHasDigital)
		||(m_oSysParas.m_nHasWeek != g_oSystemParas.m_nHasWeek)||(m_oSysParas.m_nIecFormat != g_oSystemParas.m_nIecFormat))
	{
		g_oSystemParas.m_nHasAnalog = m_oSysParas.m_nHasAnalog;
		g_oSystemParas.m_nHasDigital = m_oSysParas.m_nHasDigital;
		g_oSystemParas.m_nHasWeek = m_oSysParas.m_nHasWeek;
		g_oSystemParas.m_nIecFormat = m_oSysParas.m_nIecFormat;
		bSysParasHasChanged = TRUE;
		g_oSttTestResourceMngr.SaveSystemParasFile();
	}

	g_oSttTestResourceMngr.m_oChMaps.DeleteAll();
    //wangtao 20240504 更新别名，使其与Name保持一致
	m_oSttChMaps.UpdateAliasByName();
	m_oSttChMaps.Copy(&g_oSttTestResourceMngr.m_oChMaps);
	emit sig_UpdateChRsMaps(bSysParasHasChanged);
	g_oSttTestResourceMngr.SaveCurChMapsFile();
	g_oSttSystemConfig.SaveSystemConfig();
}

void QChMapsDlg::slot_CancelClicked()
{
	close();
}
void QChMapsDlg::slot_LockMapsChecked(int nState)
{
	//g_oSttSystemConfig.SetLockMaps(nState);
	if (m_pLockMaps_CheckBox->checkState() == Qt::Checked)
	{
		g_oSttSystemConfig.SetLockMaps(1);
	}
	else
	{
		g_oSttSystemConfig.SetLockMaps(0);
	}

}