#include "SttIecConfigDialogLinux.h"
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolButton>
#include <QFileDialog>
#include <QFile>
#include "../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Controls/SttTabWidget.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include"../../XLangResource_Native.h"

#define STT_IECCONFIG_TREE_LEVEL_TOP                                             0
#define STT_IECCONFIG_TREE_LEVEL_SECOND                                          1


QSttIecConfigDialogLinux::QSttIecConfigDialogLinux(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent)
: QSttIecConfigDialogBase(pIecCfgDatasMngr,parent)
{
//	InitUI();
	installEventFilter(this);
}

QSttIecConfigDialogLinux::~QSttIecConfigDialogLinux()
{
	if (m_pIecCfgDatasMngr_Inter != NULL)
	{
		delete m_pIecCfgDatasMngr_Inter;
		m_pIecCfgDatasMngr_Inter = NULL;
	}
}

void QSttIecConfigDialogLinux::InitUI()
{

#ifdef _PSX_QT_WINDOWS_
	CString strFilePath = _P_GetResourcePath();
	strFilePath += _T("tree.ico");
	m_oIconTree.addFile(strFilePath);
#else
	CString strFilePath = ":/ctrls/images/tree.ico";
	m_oIconTree.addFile(strFilePath);
#endif
	resize(g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth,g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight);
	this->setFixedWidth(g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth);
	this->setFixedHeight(g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight);
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	m_pSttIecConfigMainLayout = new QGridLayout(this);
	m_pIecConfigRightTabWidget = new QSttTabWidget(this);
	// 	m_pIecConfigRightTabWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget = new QStackedWidget(m_pIecConfigRightTabWidget);
	CreateToolBar();//创建工具栏
	CreateNavigationTree(g_oSttTestResourceMngr.m_nTotalFiberNum_LC,g_oSttTestResourceMngr.m_nTotalFiberNum_STSend);//创建导航栏

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_SysParasConfig");

	m_pIecConfigRightStackedWidget->setCurrentIndex(0);//默认显示第一个堆栈视图
	m_pIecConfigRightTabWidget->addTab(m_pIecConfigRightStackedWidget,m_oIconTree,strTemp);

	m_pSttIecConfigSplitter = new QSplitter(Qt::Horizontal);
	m_pSttIecConfigSplitter->addWidget(m_IecConfigNavigationTree);
	m_pSttIecConfigSplitter->addWidget(m_pIecConfigRightTabWidget);
	// 	m_pSttIecConfigSplitter->setStretchFactor(0,4);
	// 	m_pSttIecConfigSplitter->setStretchFactor(1,6);
	QList<int> oListSize;
	oListSize.append(154);
	oListSize.append(870);
	m_pSttIecConfigSplitter->setSizes(oListSize);

	m_pSttIecConfigMainLayout->addWidget(m_pSttIecConfigToolBar,0,0,1,1);
	m_pSttIecConfigMainLayout->addWidget(m_pSttIecConfigSplitter,1,0,1,1);
	//	setWindowState(Qt::WindowMaximized);
	setLayout(m_pSttIecConfigMainLayout);
	SetIecConfigFont();
	InitData();
}

void QSttIecConfigDialogLinux::CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend)
{
	m_IecConfigNavigationTree = new QTreeWidget;
	m_IecConfigNavigationTree->setStyleSheet("QTreeWidget::item{height:30px}");
	m_IecConfigNavigationTree->header()->setVisible(false);
	//m_IecConfigNavigationTree->setFont(m_oIecFont);

	
	//2023-12-28 suyang 取消树形控件勾选框
	//2022-11-22  sy checkbox换成图片
// 	CString strStyleSheet;
// #ifndef _PSX_QT_WINDOWS_
// 	strStyleSheet.Format("QTreeView::indicator:checked {image: url(:/ctrls/images/checked.png);} QTreeView::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
// #endif
// 	m_IecConfigNavigationTree->setStyleSheet(strStyleSheet);

	CString strTemp;
	//	strTemp = _T("系统参数");
	//	xlang_GetLangStrByFile(strTemp,"IEC_SysParasSet");

	QStringList astrItemDesc;

	astrItemDesc<<g_sLangTxt_SystemPara;
	QTreeWidgetItem *pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

#ifdef IecCfgSysParas_USE_Grid
	m_pSysParasWidget = new QSttIecSysCfgWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
#else
	m_pSysParasWidget = new QSttSysParasWidget(m_pIecConfigRightStackedWidget);
	m_pSysParasWidget->setFont(m_oIecFont);
#endif
	m_pIecConfigRightStackedWidget->addWidget(m_pSysParasWidget);
	m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pSysParasWidget);

	//SMV发布
	astrItemDesc.clear();
	//strTemp = _T("SMV发布");
	xlang_GetLangStrByFile(strTemp,"IEC_SMVPublish");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	//9-2报文
	astrItemDesc.clear();
	strTemp = tr("9-2");
	//	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	astrItemDesc<<strTemp;
	QTreeWidgetItem *pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
	//pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang 取消树形控件勾选框
	if (nTotalFiberNum_LC > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}
	
	m_pIecSMV92OutWidget = new QSttIecSMV92Widget(m_oIecFont,m_pIecConfigRightStackedWidget);
	//	m_pIecSMV92OutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92OutWidget);

	//FT3报文
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
	//pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang 取消树形控件勾选框
	if (nTotalFiberNum_STSend > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}

	m_pIecSMVFT3OutWidget = new QSttIecSMVFT3OutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3OutWidget);

	//SMV订阅
	astrItemDesc.clear();    //20220728 暂时删除该显示,本月底发布,不修改该功能
	//strTemp = _T("SMV订阅");
	xlang_GetLangStrByFile(strTemp,"IEC_SMVSubscription");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	//92报文
	astrItemDesc.clear();
	strTemp = tr("9-2");
	//	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang 取消树形控件勾选框
	if (nTotalFiberNum_LC > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMV92InWidget = new QSttIecSMV92InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	//	m_pIecSMV92InWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92InWidget);  

	//FT3报文
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang 取消树形控件勾选框
	if (nTotalFiberNum_STSend > 0)
	{
	pQTreeTopItem->addChild(pChildItem);

	}
	m_pIecSMVFT3InWidget = new QSttIecSMVFT3InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3InWidget);

	// 	pQTreeTopItem->setDisabled(true);
	// 	pChildItem->setDisabled(true);
	// 	m_pIecSMV92InWidget->setDisabled(false);

	//GOOSE 发布
	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Publish");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	if (nTotalFiberNum_LC > 0)
	{
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	}

	m_pIecGoutWidget = new QSttIecGoutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	// 	m_pIecGoutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecGoutWidget);
	m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecGoutWidget);

	//GOOSE 订阅
	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Subscription");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	if (nTotalFiberNum_LC > 0)
	{
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	}
	m_pIecGinWidget = new QSttIecGinWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	// 	m_pIecGinWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecGinWidget);
	m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecGinWidget);

	m_IecConfigNavigationTree->expandAll();

	if (nTotalFiberNum_LC == 0)
	{
		m_bTotalFiberNum_LC = FALSE;
	}
	else if (nTotalFiberNum_STSend == 0)
	{
		m_bTotalFiberNum_STSend = FALSE;
	}
	connect(m_IecConfigNavigationTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)),SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	connect(m_IecConfigNavigationTree, SIGNAL(itemChanged ( QTreeWidgetItem *, int )), SLOT(slot_TreeItemChanged( QTreeWidgetItem *, int )));
}

void QSttIecConfigDialogLinux::slot_TreeItemClicked(QTreeWidgetItem * pItem, int nColumn )
{
	if(pItem == NULL) 
		return;

	QTreeWidgetItem *pCurSelItem = pItem;

	while(!m_oTreeStackedWidgetHash.contains(pCurSelItem))//判断当前节点是否映射了Hash表如果未映射,则获取其第一个子节点
	{
		pCurSelItem = pCurSelItem->child(0);//如果

		if(pCurSelItem == NULL) 
		{
			return;
		}
	}

	m_nIecConfigNavigationTreeIndex = m_oTreeStackedWidgetHash.value(pCurSelItem);

	QString strText;
	strText = GetTreetItemAllString(pCurSelItem);
	m_pIecConfigRightTabWidget->setTabText(0, strText/*pCurSelItem->text(0)*/);
	m_pIecConfigRightStackedWidget->setCurrentIndex(m_nIecConfigNavigationTreeIndex);
	QWidget *pCurrWidget = m_pIecConfigRightStackedWidget->currentWidget();
	CIecCfgDatasSMV* pIecCfgDatasSMV = m_pIecCfgDatasMngr_Inter->GetSmvMngr();
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = m_pIecCfgDatasMngr_Inter->GetSmvInMngr();

	if (pIecCfgDatasSMV != NULL)
	{
		if (pCurrWidget == m_pIecSMV92OutWidget)
		{
			pIecCfgDatasSMV->SetSmvType(SMVTYPE_92);
		}
		else if (pCurrWidget == m_pIecSMVFT3OutWidget)
		{
			pIecCfgDatasSMV->SetSmvType(SMVTYPE_6044_COMMON);
		}
	}

	if (pIecCfgDatasSmvIn != NULL)
	{
		if (pCurrWidget == m_pIecSMV92InWidget)
		{
			pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_92);
		}
		else if (pCurrWidget == m_pIecSMVFT3InWidget)
		{
			pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_6044_COMMON);
		}
	}
}
