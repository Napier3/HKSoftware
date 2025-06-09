#include "QDeviceInforDlg.h"
#include <QPushButton>
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#include "../../../SttGlobalDef.h"
#include <QDirIterator>
#include <QSplitter>
#include "../../../Module/XLangResource_Native.h"

QDeviceInforDlg::QDeviceInforDlg(QWidget *parent)
	: QDialog(parent)
{
	m_pVLayout = NULL;
	m_tabWidget = NULL;
	m_pDevcieAttrsGrid = NULL;
	m_pDeviceAttrGroup = NULL;
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	//setWindowTitle(tr("版本信息"));
	setWindowTitle(g_sLangTxt_State_VersionInformation); //版本信息 lcq 3.15

	//InitVersionViewCfg();
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
	if (m_pDeviceAttrGroup != NULL)
	{
		delete m_pDeviceAttrGroup;
		m_pDeviceAttrGroup = NULL;
	}
}

void QDeviceInforDlg::initUI(BOOL bEnableCmbSel)
{
	ReleaseUI();

	resize(800, 700);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(30);
	sizePolicy.setVerticalStretch(30);

	m_pVLayout = new QVBoxLayout;
	m_tabWidget = new QTabWidget(this);
	m_pDevcieAttrsGrid = new CDeviceAttrsGrid(this);
	m_pDevcieAttrsGrid->setFont(this->font());
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
	//m_pOK_PushButton->setText(tr("关闭"));
	m_pOK_PushButton->setText(g_sLangTxt_Close);  // 关闭 lcq 3.15
#ifdef _PSX_QT_WINDOWS_
	m_pOK_PushButton->setIcon (QPixmap( "./images/Check.png"));
#else
    m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/Check.png"));
#endif
	m_pHBoxLayout->addWidget(m_pOK_PushButton);
//	m_pHBoxLayout->addSpacing(20);
//	m_pHBoxLayout->addStretch();
	m_pHBoxLayout->setContentsMargins(3,3,3,3);
	m_pHBoxLayout->setDirection(QBoxLayout::LeftToRight);
	m_pVLayout->addLayout(m_pHBoxLayout);

	QSplitter *pDevInforSplitterV = new QSplitter(Qt::Vertical, this);
	//m_tabWidget->addTab(pDevInforSplitterV,tr("模块管理"));
    m_tabWidget->addTab(pDevInforSplitterV,g_sLangTxt_State_ModuleManagement); //模块管理 lcq 3.15
	m_pModulesGrid = new CSttModulesGrid(pDevInforSplitterV);
	m_pModulesGrid->setFont(this->font());
	m_pModulesGrid->InitGrid();
	pDevInforSplitterV->addWidget(m_pModulesGrid);
	m_pModuleAttrsGrid = new CSttModuleAttrsGrid(pDevInforSplitterV);
	m_pModuleAttrsGrid->setFont(this->font());
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

    CDataGroup* pAttrGroup  = NULL;

	if (bHasLoadDev)
	{
		InitVersionViewCfg();
		CDataGroup *pSttAdjRef = g_oSttTestResourceMngr.m_oCurrDevice.m_pSttAdjRef;

		if (pSttAdjRef != NULL)
		{
			CDataGroup *pDeviceAttrs = (CDataGroup*)pSttAdjRef->FindByID(STT_CMD_PARA_DeviceAttrs);

			if (pDeviceAttrs != NULL)
			{
				CString strExeDateTime;
				strExeDateTime += __DATE__;
				strExeDateTime += " ";
				strExeDateTime += __TIME__;
				CDvmData *pExeVertionData = (CDvmData*)pDeviceAttrs->FindByID("ExeVertionDate");

				if (pExeVertionData == NULL)
				{
					pExeVertionData = pDeviceAttrs->AddNewData("ExeVertionDate",strExeDateTime);
					//pExeVertionData->m_strName = "TestCtrlCntrLinux生成日期";
					pExeVertionData->m_strName = g_sLangTxt_State_TBuildDate;
				} 
				else
				{
					pExeVertionData->m_strValue = strExeDateTime;
				}

                CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/* _T("当前测试控制程序生成日期(%s).") */ g_sLangTxt_Native_TestCtrlProgDate.GetString(),strExeDateTime.GetString());
			}
		}

		m_pDeviceAttrGroup = g_oSttTestResourceMngr.m_oCurrDevice.AddNewDeviceModelByVersionViewCfg(&m_oVersionViewCfg);
       pAttrGroup = (CDataGroup*)m_pDeviceAttrGroup->FindByID(_T("DeviceAttrs"));

		m_pDevcieAttrsGrid->ShowDatas(pAttrGroup);
		m_pModuleAttrsGrid->ShowDatas(NULL);
		m_pModulesGrid->ShowDatas(m_pDeviceAttrGroup);

		CDataGroup *pModuleGroup = (CDataGroup*)m_pDeviceAttrGroup->FindByID(_T("Module"));

		if (pModuleGroup != NULL)
		{
			CDataGroup* pAttrGroupModule = (CDataGroup*)pModuleGroup->FindByID(_T("ModuleAttrs"));
			m_pModuleAttrsGrid->ShowDatas(pAttrGroupModule);
		}
	}

	QString strPath = g_oSttTestResourceMngr.GetRsDirPath_Device();
	m_astrModels.clear();
	m_astrSNs.clear();
	m_pModelSelCombobox->clear();
	m_pSN_SelCombobox->clear();
#ifdef _PSX_QT_LINUX_

    if(pAttrGroup != NULL)
    {
        CDvmData *pData =  (CDvmData*)pAttrGroup->FindByID(_T("Model"));

        if (pData != NULL)
        {
            m_astrModels.append(pData->m_strValue);
            m_pModelSelCombobox->insertItems(0,m_astrModels);
            m_pModelSelCombobox->setCurrentIndex(0);
        }

        pData =  (CDvmData*)pAttrGroup->FindByID(_T("SN"));

        if (pData != NULL)
        {
            m_astrSNs.append(pData->m_strValue);
            m_pSN_SelCombobox->insertItems(0,m_astrSNs);
            m_pSN_SelCombobox->setCurrentIndex(0);
        }
    }
#else
	GetAllChildFolder(strPath,m_astrModels);
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
#endif
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

void QDeviceInforDlg::slot_UpdateTestResource()
{
	m_pDevcieAttrsGrid->UpdateDatas();
	m_pModulesGrid->UpdateDatas();
	m_pModuleAttrsGrid->UpdateDatas();
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

void QDeviceInforDlg::InitVersionViewCfg()
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += _T("VersionViewConfig.xml");
	m_oVersionViewCfg.DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oVersionViewCfg.OpenXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

//2024.2.23 zyq 版本信息表格多语言处理，直接在文件中进行翻译转换
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oVersionViewCfg, _T("VersionViewConfig.xml"));
#endif
}
