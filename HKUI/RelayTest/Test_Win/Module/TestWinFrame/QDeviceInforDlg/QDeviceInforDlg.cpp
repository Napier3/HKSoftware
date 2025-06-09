#include "QDeviceInforDlg.h"
#include <QPushButton>
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../Module/SttSystemConfig/SttSystemConfig.h"
#include <QDirIterator>
#include <QDesktopWidget>
#include <QApplication>
#include <QSplitter>
#include "..\ReportView\XLangResource_PowerTestWin.h"

QDeviceInforDlg::QDeviceInforDlg(QWidget *parent)
	: QDialog(parent)
{
	m_pVLayout = NULL;
	m_tabWidget = NULL;
	m_pDevcieAttrsGrid = NULL;

	setWindowIcon (QIcon(":/image/set.png"));
	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(/*tr("版本信息")*/g_sLangTxt_State_VersionInformation);
}

QDeviceInforDlg::~QDeviceInforDlg()
{
	ReleaseUI();
}

void QDeviceInforDlg::ReleaseUI()
{
	if (m_pDevcieAttrsGrid != NULL)
	{
		delete m_pDevcieAttrsGrid;
		m_pDevcieAttrsGrid = NULL;
	}

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

void QDeviceInforDlg::initUI(BOOL bEnableCmbSel)
{
	ReleaseUI();

	resize(600, 600);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pVLayout = new QVBoxLayout;
	m_tabWidget = new QTabWidget(this);
	m_pDevcieAttrsGrid = new CDeviceAttrsGrid(this);
	m_pDevcieAttrsGrid->InitGrid();
	//m_tabWidget->addTab(m_pDevcieAttrsGrid,tr("装置属性"));
	m_tabWidget->addTab(m_pDevcieAttrsGrid,g_sLangTxt_State_ApplianceProperties); // 装置属性 lcq 3.15
	m_pVLayout->addWidget(m_tabWidget);
	m_pHBoxLayout = new QHBoxLayout;

	CString strText = g_sLangTxt_Report_AppModel;
	strText += ":";

	m_pModelLabel = new QLabel(this);
	//m_pModelLabel->setText(tr("型号:"));
	m_pModelLabel->setText(strText); //型号: lcq 3.15
	m_pHBoxLayout->addWidget(m_pModelLabel);
	m_pModelSelCombobox = new QComboBox(this);

	sizePolicy.setHeightForWidth(m_pModelSelCombobox->sizePolicy().hasHeightForWidth());
	m_pModelSelCombobox->setSizePolicy(sizePolicy);

	m_pHBoxLayout->addWidget(m_pModelSelCombobox);
	m_pHBoxLayout->addSpacing(10);
	m_pSN_Label = new QLabel(this);
	//m_pSN_Label->setText(tr("编号:"));
	m_pSN_Label->setText(g_sLangTxt_State_AppNumber);// 编号: lcq 3.15
	m_pHBoxLayout->addWidget(m_pSN_Label);
	m_pSN_SelCombobox = new QComboBox(this);

	sizePolicy.setHeightForWidth(m_pSN_SelCombobox->sizePolicy().hasHeightForWidth());
	m_pSN_SelCombobox->setSizePolicy(sizePolicy);

	m_pHBoxLayout->addWidget(m_pSN_SelCombobox);

	m_pHBoxLayout->addStretch();
	m_pHBoxLayout->addSpacing(80);
	m_pOK_PushButton = new QPushButton(this);
	m_pOK_PushButton->setText(/*tr("关闭")*/g_sLangTxt_Close);
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
	m_pHBoxLayout->addWidget(m_pOK_PushButton);
//	m_pHBoxLayout->addSpacing(20);
//	m_pHBoxLayout->addStretch();
	m_pHBoxLayout->setContentsMargins(3,3,3,3);
	m_pHBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pVLayout->addLayout(m_pHBoxLayout);

	QSplitter *pDevInforSplitterV = new QSplitter(Qt::Vertical, this);
	m_tabWidget->addTab(pDevInforSplitterV,/*tr("模块管理")*/g_sLangTxt_State_ModuleManagement);
	m_pModulesGrid = new CSttModulesGrid(pDevInforSplitterV);
	m_pModulesGrid->InitGrid();
	pDevInforSplitterV->addWidget(m_pModulesGrid);
	m_pModuleAttrsGrid = new CSttModuleAttrsGrid(pDevInforSplitterV);
	m_pModuleAttrsGrid->InitGrid();
	pDevInforSplitterV->addWidget(m_pModuleAttrsGrid);

	pDevInforSplitterV->setStretchFactor(0,10);
	pDevInforSplitterV->setStretchFactor(1,20);
	pDevInforSplitterV->setAutoFillBackground(true);

	InitDatas();

//	m_pDevAttrsWiget->initUI(&m_oSysParas,&m_oSttChMaps);
	m_pVLayout->setContentsMargins(3,0,0,0);
	m_pVLayout->setSpacing(0);
	this->setLayout(m_pVLayout);

	m_pModelSelCombobox->setEnabled(bEnableCmbSel);
	m_pSN_SelCombobox->setEnabled(bEnableCmbSel);

	m_pOK_PushButton->setFocusPolicy(Qt::NoFocus);
	connect(m_pModelSelCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeModelSel(int)));
	connect(m_pSN_SelCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_changeSN_Sel(int)));
	connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));

	//2023-11-17 wuxinyi 2880X1800分辨率处理
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height() == 1800)
	{
		resize(1050, 700);
	}
}

void QDeviceInforDlg::InitDatas()
{
	BOOL bHasLoadDev = TRUE;

	if (!g_oSttTestResourceMngr.HasLoadDevice())//如果没有加载通道映射文件,主动加载通道映射文件
	{
		if (!g_oSttTestResourceMngr.SelectDeviceFromLocalDB())
		{
			bHasLoadDev = FALSE;
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("测试仪硬件信息文件加载失败."))
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_TheTesterfileFailedtoload.GetString());//测试仪硬件信息文件加载失败 lcq 3.15
		}
	}

	if (bHasLoadDev)
	{
		CDataGroup* pAttrGroup = g_oSttTestResourceMngr.m_oCurrDevice.GetDeviceAttrs();
		m_pDevcieAttrsGrid->ShowDatas(pAttrGroup);
		m_pModuleAttrsGrid->ShowDatas(NULL);
		m_pModulesGrid->ShowDatas(g_oSttTestResourceMngr.m_oCurrDevice.m_pSttAdjRef);
		CDataGroup *pModuleGroup = (CDataGroup*)g_oSttTestResourceMngr.m_oCurrDevice.m_pSttAdjRef->FindByID(_T("Module"));

		if (pModuleGroup != NULL)
		{
			CDataGroup* pAttrGroupModule = (CDataGroup*)pModuleGroup->FindByID(_T("ModuleAttrs"));
			m_pModuleAttrsGrid->ShowDatas(pAttrGroupModule);
		}
	}

	QString strPath = g_oSttTestResourceMngr.GetRsDirPath_Device();
	m_astrModels.clear();
	m_astrSNs.clear();
	GetAllChildFolder(strPath,m_astrModels);
	m_pModelSelCombobox->clear();
	m_pSN_SelCombobox->clear();
	m_pModelSelCombobox->insertItems(0,m_astrModels);
	long nModelIndex = m_astrModels.indexOf(g_oSttSystemConfig.GetDevModel());

	if (nModelIndex>=0)
	{
		m_pModelSelCombobox->setCurrentIndex(nModelIndex);
		QString strCurDevPath;
		strCurDevPath = QString(tr("%1/%2/")).arg(strPath).arg(m_astrModels.at(nModelIndex));
		GetAllChildFolder(strCurDevPath,m_astrSNs);
		m_pSN_SelCombobox->insertItems(0,m_astrSNs);

		long nSnIndex = m_astrSNs.indexOf(g_oSttTestResourceMngr.GetCurrSelSN());

		if (nSnIndex>=0)
		{
			m_pSN_SelCombobox->setCurrentIndex(nSnIndex);
		}
	}

	m_pModulesGrid->AttachDataViewOptrInterface(this);
//	m_pModulesGrid->SelectRow(1);
}

void QDeviceInforDlg::GetAllChildFolder(const QString &strParentFolderPath,QStringList &astrChildFolders)
{
	QDir dir(strParentFolderPath);

	//将过滤后的文件名称存入到files列表中
	QStringList nameFilters;
	astrChildFolders = dir.entryList(nameFilters, QDir::Dirs| QDir::NoDotAndDotDot);
}

void QDeviceInforDlg::slot_OKClicked()
{
	close();
}

void QDeviceInforDlg::slot_changeModelSel(int nCurComboxIndex)
{
	if (nCurComboxIndex<0)
	{
		return;
	}

	if (m_astrModels.count()<=nCurComboxIndex)
	{
		return;
	}

	QString strPath = g_oSttTestResourceMngr.GetRsDirPath_Device();
	QString strCurDevPath;
	strCurDevPath = QString(tr("%1/%2/")).arg(strPath).arg(m_astrModels.at(nCurComboxIndex));
	GetAllChildFolder(strCurDevPath,m_astrSNs);
	m_pSN_SelCombobox->clear();
	m_pSN_SelCombobox->insertItems(0,m_astrSNs);

	QString strOldModel = g_oSttSystemConfig.GetDevModel();
	QString strOldSN = g_oSttTestResourceMngr.GetCurrSelSN();
	QString strCurModel = m_astrModels.at(nCurComboxIndex);
	QString strCurSN = m_astrSNs.at(0);

	if ((strOldModel != strCurModel)||(strOldSN != strCurSN))
	{
		g_oSttTestResourceMngr.SetCurSelDevice(strCurModel,strCurSN,FALSE);
		CDataGroup* pAttrGroup = g_oSttTestResourceMngr.m_oCurrDevice.GetDeviceAttrs();
		m_pDevcieAttrsGrid->ShowDatas(pAttrGroup);
		m_pModuleAttrsGrid->ShowDatas(NULL);
		m_pModulesGrid->ShowDatas(g_oSttTestResourceMngr.m_oCurrDevice.m_pSttAdjRef);
	}
}

void QDeviceInforDlg::slot_changeSN_Sel(int nCurComboxIndex)
{
	long nCurModelIndex = m_pModelSelCombobox->currentIndex();

	if ((nCurComboxIndex<0)||(nCurModelIndex<0))
	{
		return;
	}

	if (m_astrSNs.count()<=nCurComboxIndex)
	{
		return;
	}

	QString strOldModel = g_oSttSystemConfig.GetDevModel();
	QString strOldSN = g_oSttTestResourceMngr.GetCurrSelSN();
	QString strCurModel = m_astrModels.at(nCurModelIndex);
	QString strCurSN = m_astrSNs.at(nCurComboxIndex);

	if ((strOldModel != strCurModel)||(strOldSN != strCurSN))
	{
		g_oSttTestResourceMngr.SetCurSelDevice(strCurModel,strCurSN,FALSE);
		CDataGroup* pAttrGroup = g_oSttTestResourceMngr.m_oCurrDevice.GetDeviceAttrs();
		m_pDevcieAttrsGrid->ShowDatas(pAttrGroup);
		m_pModuleAttrsGrid->ShowDatas(NULL);
		m_pModulesGrid->ShowDatas(g_oSttTestResourceMngr.m_oCurrDevice.m_pSttAdjRef);
	}
}


void QDeviceInforDlg::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	CDataGroup *pCurrSelModule = (CDataGroup*)m_pModulesGrid->GetCurrSelData();

	if (pCurrSelModule == NULL)
	{
		return;
	}

	m_pModuleAttrsGrid->ShowDatas(pCurrSelModule);
}

