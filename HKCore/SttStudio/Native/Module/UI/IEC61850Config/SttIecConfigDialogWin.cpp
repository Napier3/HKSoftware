#include "SttIecConfigDialogWin.h"
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolButton>
#include <QFileDialog>
#include <QFile>
#include "../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Controls/SttTabWidget.h"
#include "../../XLangResource_Native.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

QSttIecConfigDialogWin::QSttIecConfigDialogWin(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent)
: QSttIecConfigDialogBase(pIecCfgDatasMngr,parent)
{
//	InitUI();
	installEventFilter(this);
}

QSttIecConfigDialogWin::~QSttIecConfigDialogWin()
{
	if (m_pIecCfgDatasMngr_Inter != NULL)
	{
		delete m_pIecCfgDatasMngr_Inter;
		m_pIecCfgDatasMngr_Inter = NULL;
	}
}

void QSttIecConfigDialogWin::InitUI()
{
#ifdef _PSX_QT_WINDOWS_
	CString strFilePath = _P_GetResourcePath();
	strFilePath += _T("tree.ico");
	m_oIconTree.addFile(strFilePath);
#else
	CString strFilePath = ":/ctrls/images/tree.ico";
	m_oIconTree.addFile(strFilePath);
#endif
	//���ڴ�С����
 	QRect rcScreen = QApplication::desktop()->availableGeometry();
	long nWidth = rcScreen.width();
	long nHeight = rcScreen.height() - 30;
	long nTmp = nWidth*0.8;

	if (nHeight<nTmp)
	{
		nWidth = (nHeight/0.8);
	} 
	else
	{
		nHeight = nTmp;
	}
  	resize(nWidth, nHeight);//��������

	Qt::WindowFlags flags=Qt::Dialog;  
	flags |=Qt::WindowMinMaxButtonsHint;  
	flags |=Qt::WindowCloseButtonHint;  
	setWindowFlags(flags); 
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath += _T("images/Iec61850Config.png");
#else
	strPngPath = ":/ctrls/images/Iec61850Config.png";
#endif
	setWindowIcon(QIcon(strPngPath));
	CString strTitle;
	//strTitle = _T("IEC����");
	strTitle = g_sLangTxt_Gradient_IECConfiguration;//lcq
	setWindowTitle(strTitle);


	m_pSttIecConfigMainLayout = new QGridLayout(this);
	m_pIecConfigRightTabWidget = new QSttTabWidget(this);
// 	m_pIecConfigRightTabWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget = new QStackedWidget(m_pIecConfigRightTabWidget);
	m_pSttIecChsEditStackedWidget = new QStackedWidget(this);
	m_pSttIecConfigSplitter = new QSplitter(Qt::Horizontal);
	CreateToolBar();//����������
	CreateNavigationTree(g_oSttTestResourceMngr.m_nTotalFiberNum_LC,g_oSttTestResourceMngr.m_nTotalFiberNum_STSend);//����������

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_SysParasConfig");

	m_pIecConfigRightStackedWidget->setCurrentIndex(0);//Ĭ����ʾ��һ����ջ��ͼ
	m_pIecConfigRightTabWidget->addTab(m_pIecConfigRightStackedWidget,m_oIconTree,strTemp);
	m_pSttIecConfigSplitter->addWidget(m_IecConfigNavigationTree);

	m_pSttIecConfigRightSplitter= new QSplitter(Qt::Vertical);
	m_pSttIecConfigRightSplitter->addWidget(m_pIecConfigRightTabWidget);
	m_pSttIecChsEditStackedWidget->hide();
	m_pSttIecConfigRightSplitter->addWidget(m_pSttIecChsEditStackedWidget);
	QList<int> oRightListSize;
	oRightListSize.append(300);
	oRightListSize.append(600);
// 	m_pSttIecConfigSplitter->setStretchFactor(0,4);
// 	m_pSttIecConfigSplitter->setStretchFactor(1,4);
	m_pSttIecConfigRightSplitter->setSizes(oRightListSize);
	m_pSttIecConfigSplitter->addWidget(m_pSttIecConfigRightSplitter);

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
	showMaximized();
	SetIecConfigFont();
	InitData();
}

void QSttIecConfigDialogWin::CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend)
{
	m_IecConfigNavigationTree = new QTreeWidget;
	m_IecConfigNavigationTree->setStyleSheet("QTreeWidget::item{height:30px}");
	m_IecConfigNavigationTree->header()->setVisible(false);
	//m_IecConfigNavigationTree->setFont(m_oIecFont);
	
	//2022-11-22  sy checkbox����ͼƬ
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QTreeView::indicator:checked {image: url(:/ctrls/images/checked.png);} QTreeView::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	m_IecConfigNavigationTree->setStyleSheet(strStyleSheet);

	CString strTemp;
//	strTemp = _T("ϵͳ����");
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

	//SMV����
	astrItemDesc.clear();
	//strTemp = _T("SMV����");
	xlang_GetLangStrByFile(strTemp,"IEC_SMVPublish");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	//9-2����
	astrItemDesc.clear();
	strTemp = tr("9-2");
//	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	astrItemDesc<<strTemp;
	QTreeWidgetItem *pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	if (nTotalFiberNum_LC > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMV92OutWidget = new QSttIecSMV92Widget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92OutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92OutWidget);

	m_pSttIecChsEdit92OutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV92);
	m_pSttIecChsEdit92OutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEdit92OutWidget);

	//FT3����
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	if (nTotalFiberNum_STSend > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMVFT3OutWidget = new QSttIecSMVFT3OutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3OutWidget);

	m_pSttIecChsEditFT3OutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV_FT3OUT);
	m_pSttIecChsEditFT3OutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditFT3OutWidget);

	//SMV����
	astrItemDesc.clear();    //20220728 ��ʱɾ������ʾ,���µ׷���,���޸ĸù���
	//strTemp = _T("SMV����");
	xlang_GetLangStrByFile(strTemp,"IEC_SMVSubscription");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	//92����
	astrItemDesc.clear();
	strTemp = tr("9-2");
	//	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	if (nTotalFiberNum_LC > 0)
	{
	pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMV92InWidget = new QSttIecSMV92InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92InWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92InWidget);  

	m_pSttIecChsEdit92InWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV92IN);
	m_pSttIecChsEdit92InWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEdit92InWidget);

	//FT3����
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
	pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

// 	pChildItem->setCheckState(0, Qt::Checked);
	if (nTotalFiberNum_STSend > 0)
	{
	pQTreeTopItem->addChild(pChildItem);

	}
	m_pIecSMVFT3InWidget = new QSttIecSMVFT3InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3InWidget);

	m_pSttIecChsEditFT3InWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV_FT3IN);
	m_pSttIecChsEditFT3InWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditFT3InWidget);

	//GOOSE ����
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

	m_pSttIecChsEditGoutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_GOUT);
	m_pSttIecChsEditGoutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditGoutWidget);

 	//GOOSE ����
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
	
	m_pSttIecChsEditGinWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_GIN);
	m_pSttIecChsEditGinWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditGinWidget);

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

	m_pIecSMV92OutWidget->AttachRefChsGrid(m_pSttIecChsEdit92OutWidget->m_pIecCfgChsGrid);
	m_pIecSMVFT3OutWidget->AttachRefChsGrid(m_pSttIecChsEditFT3OutWidget->m_pIecCfgChsGrid);
	m_pIecSMV92InWidget->AttachRefChsGrid(m_pSttIecChsEdit92InWidget->m_pIecCfgChsGrid);
	m_pIecSMVFT3InWidget->AttachRefChsGrid(m_pSttIecChsEditFT3InWidget->m_pIecCfgChsGrid);
	m_pIecGinWidget->AttachRefChsGrid(m_pSttIecChsEditGinWidget->m_pIecCfgChsGrid);
	m_pIecGoutWidget->AttachRefChsGrid(m_pSttIecChsEditGoutWidget->m_pIecCfgChsGrid);
 
	connect(m_pIecSMV92OutWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEdit92OutWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
	connect(m_pIecSMVFT3OutWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEditFT3OutWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
	connect(m_pIecSMV92InWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEdit92InWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
	connect(m_pIecSMVFT3InWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEditFT3InWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
//	connect(m_pIecSMV92OutWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),SLOT(slot_UpdateData()));
	connect(m_pIecGinWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEditGinWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
	connect(m_pIecGoutWidget,SIGNAL(sig_UpdateCB_ChDatas(CExBaseList *)),
		m_pSttIecChsEditGoutWidget,SLOT(slot_UpdateCB_ChDatas(CExBaseList *)));
}

void QSttIecConfigDialogWin::slot_TreeItemClicked(QTreeWidgetItem * pItem, int nColumn )
{
	if(pItem == NULL) 
		return;

	QTreeWidgetItem *pCurSelItem = pItem;

	while(!m_oTreeStackedWidgetHash.contains(pCurSelItem))//�жϵ�ǰ�ڵ��Ƿ�ӳ����Hash�����δӳ��,���ȡ���һ���ӽڵ�
	{
		pCurSelItem = pCurSelItem->child(0);//���

		if(pCurSelItem == NULL) 
		{
			return;
		}
	}

	m_nIecConfigNavigationTreeIndex = m_oTreeStackedWidgetHash.value(pCurSelItem);
	m_nIecCIecChsEditStackedIndex = m_nIecConfigNavigationTreeIndex-1;

	QString strText;
	strText = GetTreetItemAllString(pCurSelItem);
	m_pIecConfigRightTabWidget->setTabText(0, strText/*pCurSelItem->text(0)*/);
	m_pIecConfigRightStackedWidget->setCurrentIndex(m_nIecConfigNavigationTreeIndex);

	if (m_nIecConfigNavigationTreeIndex==0)
	{
		m_pSttIecChsEditStackedWidget->hide();
	}
	else
	{
		m_pSttIecChsEditStackedWidget->show();
	}
	m_pSttIecChsEditStackedWidget->setCurrentIndex(m_nIecCIecChsEditStackedIndex);
 
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
