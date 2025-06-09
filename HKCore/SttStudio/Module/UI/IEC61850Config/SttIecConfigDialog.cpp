#include "SttIecConfigDialog.h"
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolButton>
#include <QFileDialog>
#include <QFile>
#include "../SttTestCntrFrameBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttSclFileParseDialog.h"
#include "../../../../61850/Module/SCL_Qt/QScdFileRWDlg.h"
#include "../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../Controls/SttFileSaveAsDlg.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "../Controls/SttTabWidget.h"
#include "../SCL/QSttSelSclFileDlg.h"
#include "../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../Module/PopupDialog/SttPopupSaveAsDialog.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../Module/PopupDialog/SttFileMngrTool.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../AutoTest/Module/XLanguageResourceAts.h"
#include "../../XLangResource_Native.h"
#ifdef _PSX_QT_LINUX_
#include <sys/sysinfo.h>
#include <stdint.h>
#endif
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

QSttIecConfigDialog::QSttIecConfigDialog(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pSttIecConfigMainLayout = NULL;
	m_pSttIecConfigSplitter = NULL;
	m_IecConfigNavigationTree = NULL;
	m_nIecConfigNavigationTreeIndex = 0;
	m_pIecConfigRightTabWidget = NULL;
	m_pIecConfigRightStackedWidget = NULL;
	m_pSttIecConfigToolBar = NULL;
	m_pOpenCfgToolBtn = NULL;
	m_pSaveAsCfgToolBtn = NULL;
	m_pImportSCLToolBtn = NULL;
	m_pSaveToolBtn = NULL;
	m_pCancelToolBtn = NULL;
	m_pSysParasWidget = NULL;
	m_pIecSMV92OutWidget = NULL;
	m_pIecSMV92InWidget = NULL;
	m_pIecSMVFT3OutWidget= NULL;
	m_pIecSMVFT3InWidget= NULL;
	m_pIecGinWidget = NULL;
	m_pIecGoutWidget = NULL;
	m_pSclStation = NULL;
	ASSERT(pIecCfgDatasMngr);
	m_pIecCfgDatasMngr_Extern = pIecCfgDatasMngr;
	m_pIecCfgDatasMngr_Inter = (CIecCfgDatasMngr*)pIecCfgDatasMngr->Clone();
	m_pIecCfgDatasMngr_Inter->InitCommon();

	m_oIecFont.setFamily("Tahoma");
	m_oIecFont.setPixelSize(18);
	m_oIecFont.setBold(0);

	m_bTotalFiberNum_LC = TRUE;
	m_bTotalFiberNum_STSend = TRUE;
	
//	InitUI();

	installEventFilter(this);
}

QSttIecConfigDialog::~QSttIecConfigDialog()
{
	if (m_pIecCfgDatasMngr_Inter != NULL)
	{
		delete m_pIecCfgDatasMngr_Inter;
		m_pIecCfgDatasMngr_Inter = NULL;
	}
}

void QSttIecConfigDialog::SetIecConfigFont()
{
	m_pCancelToolBtn->setFont(*g_pSttGlobalFont);
	m_pSaveToolBtn->setFont(*g_pSttGlobalFont);
	m_pImportSCLToolBtn->setFont(*g_pSttGlobalFont);
	m_pSaveAsCfgToolBtn->setFont(*g_pSttGlobalFont);
	m_pOpenCfgToolBtn->setFont(*g_pSttGlobalFont);
	m_pSttIecConfigToolBar->setFont(*g_pSttGlobalFont);
	m_pIecConfigRightStackedWidget->setFont(*g_pSttGlobalFont);
	m_pIecConfigRightTabWidget->setFont(*g_pSttGlobalFont);
	m_IecConfigNavigationTree->setFont(*g_pSttGlobalFont);

	m_pSysParasWidget->setFont(*g_pSttGlobalFont);
	m_pIecSMV92OutWidget->setFont(*g_pSttGlobalFont);
	m_pIecSMV92InWidget->setFont(*g_pSttGlobalFont);
	m_pIecSMVFT3OutWidget->setFont(*g_pSttGlobalFont);
	m_pIecSMVFT3InWidget->setFont(*g_pSttGlobalFont);
	m_pIecGinWidget->setFont(*g_pSttGlobalFont);
 	m_pIecGoutWidget->setFont(*g_pSttGlobalFont);
	
}
void QSttIecConfigDialog::closeEvent( QCloseEvent * event )
{
	event->accept();
}

void QSttIecConfigDialog::InitUI()
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
	CreateToolBar();//����������
	CreateNavigationTree(g_oSttTestResourceMngr.m_nTotalFiberNum_LC,g_oSttTestResourceMngr.m_nTotalFiberNum_STSend);//����������

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_SysParasConfig");

	m_pIecConfigRightStackedWidget->setCurrentIndex(0);//Ĭ����ʾ��һ����ջ��ͼ
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

void QSttIecConfigDialog::ReleaseUI()
{

}

void QSttIecConfigDialog::CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend)
{
	m_IecConfigNavigationTree = new QTreeWidget;
	m_IecConfigNavigationTree->setStyleSheet("QTreeWidget::item{height:30px}");
	m_IecConfigNavigationTree->header()->setVisible(false);
	//m_IecConfigNavigationTree->setFont(m_oIecFont);
	
	bool bIsEnabled = FALSE;
	if (g_oSystemParas.m_nIecFormat == 0)
	{
		bIsEnabled = TRUE;
	}

	//2022-11-22  sy checkbox����ͼƬ
	CString strStyleSheet;
//#ifndef _PSX_QT_WINDOWS_
//	strStyleSheet.Format("QTreeView::indicator:checked {image: url(:/ctrls/images/checked.png);} QTreeView::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
//#endif
//	m_IecConfigNavigationTree->setStyleSheet(strStyleSheet);

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
	//pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��
	
	if(bIsEnabled)
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);//2023-12-28 suyang ȡ�����οؼ���ѡ��
	}
	else
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled);
	}


	if (nTotalFiberNum_LC > 0)
	{
		pQTreeTopItem->addChild(pChildItem);
	}

	m_pIecSMV92OutWidget = new QSttIecSMV92Widget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92OutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92OutWidget);
	if (bIsEnabled)
	{
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	}
	m_oRightStackedWidgetList.append(m_pIecSMV92OutWidget);
	
	//FT3����
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	//pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	if(bIsEnabled)
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled);//2023-12-28 suyang ȡ�����οؼ���ѡ��
	}
	else
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
	}

	if (nTotalFiberNum_STSend > 0)
	{
		pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMVFT3OutWidget = new QSttIecSMVFT3OutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3OutWidget);
	if (!bIsEnabled)
	{
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	}
	m_oRightStackedWidgetList.append(m_pIecSMVFT3OutWidget);

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
	//pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��
	if(bIsEnabled)
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable| Qt::ItemIsEnabled);//2023-12-28 suyang ȡ�����οؼ���ѡ��
	}
	else
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled);
	}

	if (nTotalFiberNum_LC > 0)
	{
		pQTreeTopItem->addChild(pChildItem);
	}
	m_pIecSMV92InWidget = new QSttIecSMV92InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92InWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92InWidget);
	if (bIsEnabled)
	{
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	}
	m_oRightStackedWidgetList.append(m_pIecSMV92InWidget);  

	//FT3����
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
// 	pChildItem->setCheckState(0, Qt::Checked);
	//pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	if(bIsEnabled)
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled);//2023-12-28 suyang ȡ�����οؼ���ѡ��

	}
	else
	{
		pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
	}

	if (nTotalFiberNum_STSend > 0)
	{
		pQTreeTopItem->addChild(pChildItem);

	}
	m_pIecSMVFT3InWidget = new QSttIecSMVFT3InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3InWidget);
	if (!bIsEnabled)
	{
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	}
	m_oRightStackedWidgetList.append(m_pIecSMVFT3InWidget);

// 	pQTreeTopItem->setDisabled(true);
// 	pChildItem->setDisabled(true);
// 	m_pIecSMV92InWidget->setDisabled(false);

	//GOOSE ����
	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Publish");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
// 	if(g_oSystemParas.m_nIecFormat == 0)
// 	{
// 		pQTreeTopItem->setFlags(pQTreeTopItem->flags() | Qt::ItemIsEnabled);
// 	}
// 	else
// 	{
// 		pQTreeTopItem->setFlags(pQTreeTopItem->flags() & ~Qt::ItemIsEnabled);
// 	}

	if (nTotalFiberNum_LC > 0)
	{
		m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	}
	m_pIecGoutWidget = new QSttIecGoutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
// 	m_pIecGoutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecGoutWidget);
// 	if (bIsEnabled)
// 	{
// 		m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
// 	}
	m_oRightStackedWidgetList.append(m_pIecGoutWidget);

 	//GOOSE ����
 	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Subscription");
 	astrItemDesc<<strTemp;
 	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
// 	if(bIsEnabled)
// 	{
// 		pQTreeTopItem->setFlags(pQTreeTopItem->flags() | Qt::ItemIsEnabled);
// 	}
// 	else
// 	{
// 		pQTreeTopItem->setFlags(pQTreeTopItem->flags() & ~Qt::ItemIsEnabled);
// 	}
	if (nTotalFiberNum_LC > 0)
	{
 	    m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);

	}
 	m_pIecGinWidget = new QSttIecGinWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
// 	m_pIecGinWidget->setFont(m_oIecFont);
 	m_pIecConfigRightStackedWidget->addWidget(m_pIecGinWidget);
// 	if (bIsEnabled)
// 	{
// 		m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
// 	}
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

void QSttIecConfigDialog::CreateToolBar()
{
	CString strTemp;
	m_pSttIecConfigToolBar = new QToolBar(tr(""),this);
// 	m_pSttIecConfigToolBar->setFont(m_oIecFont);
	m_pOpenCfgToolBtn = new QToolButton(m_pSttIecConfigToolBar);
	//m_pOpenCfgToolBtn->setText(tr("������"));
	xlang_SetLangStrToWidget(m_pOpenCfgToolBtn, "IEC_OpenConfig", XLang_Ctrls_QToolButton);
	//m_pOpenCfgToolBtn->setIcon(QIcon(":/res/images/open.png"));
	xlang_GetLangStrByFile(strTemp,"IEC_OpenConfigFile");
	m_pOpenCfgToolBtn->setToolTip(strTemp);
	m_pOpenCfgToolBtn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	m_pSttIecConfigToolBar->addWidget( m_pOpenCfgToolBtn );

	m_pSaveAsCfgToolBtn = new QToolButton(m_pSttIecConfigToolBar);
	xlang_SetLangStrToWidget(m_pSaveAsCfgToolBtn, "IEC_ConfigSaveAs", XLang_Ctrls_QToolButton);
// 	m_pSaveAsCfgToolBtn->setText(tr("�������"));
// 	m_pSaveAsCfgToolBtn->setIcon(QIcon(":/res/images/save as.png"));
	xlang_GetLangStrByFile(strTemp,"IEC_ConfigFileSaveAs");
	m_pSaveAsCfgToolBtn->setToolTip(strTemp);
	m_pSaveAsCfgToolBtn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	m_pSttIecConfigToolBar->addWidget( m_pSaveAsCfgToolBtn );

	m_pImportSCLToolBtn = new QToolButton(m_pSttIecConfigToolBar);
// 	m_pImportSCLToolBtn->setText(tr("����SCL"));
// 	m_pImportSCLToolBtn->setIcon(QIcon(":/res/images/import.png"));
	xlang_SetLangStrToWidget(m_pImportSCLToolBtn, "IEC_ImportSCL", XLang_Ctrls_QToolButton);
	xlang_GetLangStrByFile(strTemp,"IEC_ImportSCLFile");
	m_pImportSCLToolBtn->setToolTip(strTemp);
	m_pImportSCLToolBtn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	m_pSttIecConfigToolBar->addWidget( m_pImportSCLToolBtn );

	m_pSttIecConfigToolBar->addSeparator();

	QWidget *widget = new QWidget;
	QHBoxLayout *hBoxLayout = new QHBoxLayout;
	hBoxLayout->addStretch();
	widget->setLayout(hBoxLayout);
	m_pSttIecConfigToolBar->addWidget(widget);

	m_pSaveToolBtn = new QToolButton(m_pSttIecConfigToolBar);
// 	m_pSaveToolBtn->setText(tr(" ȷ�� "));
// 	m_pSaveToolBtn->setIcon(QIcon(":/pic/images/set.png"));
	xlang_SetLangStrToWidget(m_pSaveToolBtn, "sOK", XLang_Ctrls_QToolButton);
	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	m_pSaveToolBtn->setToolTip(strTemp);
	m_pSaveToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_pSaveToolBtn->setFocusPolicy(Qt::StrongFocus);
	m_pSttIecConfigToolBar->addWidget(m_pSaveToolBtn);


	m_pCancelToolBtn = new QToolButton(m_pSttIecConfigToolBar);
// 	m_pCancelToolBtn->setText(tr(" �˳� "));
// 	m_pCancelToolBtn->setIcon(QIcon(":/pic/images/set.png"));
	xlang_SetLangStrToWidget(m_pCancelToolBtn, "sAppExit", XLang_Ctrls_QToolButton);
	xlang_GetLangStrByFile(strTemp,"sAppExit");
	m_pCancelToolBtn->setToolTip(strTemp);
	m_pCancelToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_pSttIecConfigToolBar->addWidget(m_pCancelToolBtn);

	connect(m_pOpenCfgToolBtn, SIGNAL(clicked()),SLOT(slot_OpenCfgBtnClicked()));
	connect(m_pSaveAsCfgToolBtn, SIGNAL(clicked()),SLOT(slot_SaveAsCfgBtnClicked()));
	connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
	connect(m_pSaveToolBtn, SIGNAL(clicked()),SLOT(slot_SaveBtnClicked()));
	connect(m_pCancelToolBtn, SIGNAL(clicked()), SLOT(slot_CancelBtnClicked()));
}

void QSttIecConfigDialog::InitData()
{
	ASSERT(m_pIecCfgDatasMngr_Inter);
	CIecCfgGinDatas* pIecCfgGinDatas = m_pIecCfgDatasMngr_Inter->GetGinMngr();
	CIecCfgDatasSMV* pIecCfgDatasSMV = m_pIecCfgDatasMngr_Inter->GetSmvMngr();
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = m_pIecCfgDatasMngr_Inter->GetSmvInMngr();
	CIecCfgGoutDatas* pIecCfgGoutDatas = m_pIecCfgDatasMngr_Inter->GetGoutMngr();
	CIecCfgSysParas* pIecCfgSysParas = m_pIecCfgDatasMngr_Inter->GetSysParasMngr();
	m_pSysParasWidget->InitData(pIecCfgSysParas);
	m_pIecSMV92OutWidget->InitData(pIecCfgDatasSMV);
	m_pIecSMVFT3OutWidget->InitData(pIecCfgDatasSMV);

	if (m_pIecSMV92InWidget != NULL)
	{
		m_pIecSMV92InWidget->InitData(pIecCfgDatasSmvIn);
	}
	if (m_pIecSMVFT3InWidget != NULL)
	{
		m_pIecSMVFT3InWidget->InitData(pIecCfgDatasSmvIn);
	}
	m_pIecGinWidget->InitData(pIecCfgGinDatas);
	m_pIecGoutWidget->InitData(pIecCfgGoutDatas);
}

QString GetTreetItemAllString(QTreeWidgetItem *pCurSelItem)
{
	QString strAllString;

	if (pCurSelItem->type() == STT_IECCONFIG_TREE_LEVEL_SECOND)
	{
		QTreeWidgetItem *pParent = pCurSelItem->parent();

		if (pParent != NULL)
		{
			strAllString = pParent->text(0);
			strAllString += "-";
		}

		strAllString += pCurSelItem->text(0);

	}
	else
	{
		strAllString = pCurSelItem->text(0);
	}

	return strAllString;
}

void QSttIecConfigDialog::slot_TreeItemClicked(QTreeWidgetItem * pItem, int nColumn )
{
	if(pItem == NULL) 
		return;

	if ((pItem->flags() & Qt::ItemIsEnabled) == 0)
	{
		return;
	}

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

void QSttIecConfigDialog::slot_OpenCfgBtnClicked()
{
	CString strFilePath,strFolderPath;

	strFolderPath = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_IEC61850Config) ;

#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
// 	CString strFolderPath;
// 	strFolderPath = _P_GetLibraryPath();
	astrPostfix<<"*.ixml";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
// 	oOpenDlg.setFont(m_oIecFont);// 2022-10-22 sy ����g_pSttGlobalFont
	//oOpenDlg.setFont(*g_pSttGlobalFont);

	oOpenDlg.InitUI();

	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		oOpenDlg.resize(850,500);
		oOpenDlg.setFixedHeight(500);
	}

	if (oOpenDlg.exec() != QDialog::Accepted)
		return;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return;
	}
#else
	strFilePath = OpenixmlFileDlg(TRUE);
#endif

//  	CString strFilePath = QFileDialog::getOpenFileName(this, tr("��IEC�����ļ�"), "." ,"ixml(*.ixml)");
// 
//  	if(strFilePath.IsEmpty())
//  		return;
	if(strFilePath.IsEmpty())//20240626 suyang Ӧ�ж�·���Ƿ�Ϊ��
	{
		return;
	}
	if (!IsFileExist(strFilePath))
	{
		return;
	}
 
	if (!m_pIecCfgDatasMngr_Inter->OpenIecCfgFile(strFilePath))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�������ļ�(%s)ʧ��."),strFilePath.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_configurationfile.GetString(),strFilePath.GetString());
		return;
	}

	InitData();
}

void QSttIecConfigDialog::slot_SaveAsCfgBtnClicked()
{
	CString strFilePath,strFolderPath;

	strFolderPath = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_IEC61850Config) ;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
// 	CString strFolderPath;
// 	strFolderPath = _P_GetLibraryPath();
	astrPostfix<<"*.ixml";	
	QSttPopupSaveAsDialog dlg(strFolderPath,astrPostfix,"",this);
	dlg.InitUI();

	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}

	//QSttFileSaveAsDlg dlg("", "", this);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
#endif

	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
	strFilePath = dlg.GetFilePath();
#else
	strFilePath = OpenixmlFileDlg(FALSE);

	if (strFilePath.IsEmpty())
	{
		return;
	}

	if (strFilePath.Find(_T(".ixml")) < 0)
	{
		strFilePath = ChangeFilePostfix(strFilePath, "ixml");
	}
	
#endif
	m_pIecCfgDatasMngr_Inter->SaveAsIecCfgFile(strFilePath,FALSE);
}

void QSttIecConfigDialog::slot_ImportSCLBtnClicked()
{
	disconnect(m_pImportSCLToolBtn, SIGNAL(clicked()),this,SLOT(slot_ImportSCLBtnClicked()));
	m_pImportSCLToolBtn->setEnabled(false);

	if (m_pSclStation == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("QSttIecConfigDialog��(m_pSclStation==NULL)."));
		m_pImportSCLToolBtn->setEnabled(true);
		connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
		return;
	}

	if (!g_oXSclFileMngr.m_bHasOpenCfgFile)
	{
		g_oXSclFileMngr.OpenSclFileMngrCfg();
		CString strCurrTscdFilePath;
		strCurrTscdFilePath = g_oXSclFileMngr.GetCurrSelTscdFilePah();
		m_pSclStation->OpenSclStationFile(strCurrTscdFilePath);
	}


	//�����ǰScl����������Ϊ��,��ѡ��SCL�ļ�
	if (m_pSclStation->GetCount() == 0)
	{
		bool bIsOpen = false;
//		if (g_oXSclFileMngr.GetCount() == 0)//�����ǰSCL��ʷ��¼Ϊ��,��ֱ�ӵ���ѡ��SCL����
		{
			CString strSclFilePath;
			long nSize = 0;
#ifdef _PSX_QT_LINUX_
			QStringList astrPostfix;
			CString strFolderPath;
			strFolderPath = _P_GetLibraryPath();
            astrPostfix<<"*.scd"<<"*.cid"<<"*.icd"<<"*.tscd"<<"*.ccd";
			QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this,FALSE);
			oOpenDlg.InitUI();

			QDesktopWidget* desktopWidget = QApplication::desktop(); 
			QRect rect = desktopWidget->screenGeometry();
			if(rect.height()<650)
			{
				oOpenDlg.resize(850,500);
				oOpenDlg.setFixedHeight(500);
			}

			if (oOpenDlg.exec() != QDialog::Accepted)
			{
				m_pImportSCLToolBtn->setEnabled(true);
				connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
				return;
			}

			if (!oOpenDlg.GetFilePath(strSclFilePath))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,/* _T("��ȡSCL�ļ�·��ʧ��(%s).") */g_sLangTxt_Native_FailtoGetsclPath.GetString(),strSclFilePath.GetString());
				m_pImportSCLToolBtn->setEnabled(true);
				connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
				return;
			}

			bIsOpen = true;
			nSize = oOpenDlg.GetFileSize();

			struct sysinfo s_info;
			sysinfo(&s_info);
			uint32_t ufreeram ;
            ufreeram = s_info.freeram ;
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰϵͳʣ���ڴ��С%lu B"), ufreeram);

             if (nSize * STT_IECCONFIG_FILE_SCALE >= ufreeram)
             {
                 CString strTip = _T("��ʾ");
                 CString strText = _T("��ǰϵͳʣ���ڴ治��");
                 int result =  CXMessageBox::information(this,strTip,strText, QMessageBox::Ok);
                 if (result == QMessageBox::Ok)
                 {
					m_pImportSCLToolBtn->setEnabled(true);
					connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
                     return;
                 }
             }
 #else
 			CString strSCLPath, strSCLFilter, strFilePath, 
 				strFileName, strFileType, strOpen, strCancel;
 			xlang_GetLangStrByFile(strSCLPath, "Native_SCLPath");
 			xlang_GetLangStrByFile(strSCLFilter, "Native_SCLFilter");
			xlang_GetLangStrByFile(strFilePath, "FilePath");
			xlang_GetLangStrByFile(strFileName, "sFileName");
 			xlang_GetLangStrByFile(strFileType, "Native_FileType");
			xlang_GetLangStrByFile(strOpen, "sOpen");
			xlang_GetLangStrByFile(strCancel, "sCancel");
 
 			QFileDialog dlg(this, strSCLPath);
 			dlg.setFileMode(QFileDialog::AnyFile);
			//CString strText;
 			//strText = _T("SCD�ļ�(*.scd);;ICD�ļ�(*.icd);;CID�ļ�(*.cid);;TSCD�ļ�(*.tscd)");
 			dlg.setNameFilter(/*strText*/strSCLFilter);
 
 			dlg.setViewMode(QFileDialog::Detail);
 			dlg.setAcceptMode(QFileDialog::AcceptOpen);
 			CString strPath = _P_GetLibraryPath();
 			dlg.setDirectory(strPath);
 			dlg.setLabelText(QFileDialog::LookIn, strFilePath);
 			dlg.setLabelText(QFileDialog::FileName, strFileName);
 			dlg.setLabelText(QFileDialog::FileType, strFileType);
 			dlg.setAcceptMode(QFileDialog::AcceptOpen);
 			dlg.setLabelText(QFileDialog::Accept, strOpen);
 			dlg.setLabelText(QFileDialog::Reject, strCancel);
 
 			QStringList fileNames;
 			
 			if (dlg.exec() == QFileDialog::Accepted)
 			{
 				fileNames = dlg.selectedFiles();
 				strSclFilePath = fileNames.at(0);
 
 				QFile oFile(strSclFilePath);
 
 				if (oFile.open(QFile::ReadOnly | QIODevice::Text))
 				{
 					bIsOpen = true;
 					nSize = oFile.size();
 					oFile.close();
 				}
 			}
 #endif
			//ѡ����һ��SCL�ļ�
			if(bIsOpen)
			{
				CXSclFileObj *pXSclFileObj = new CXSclFileObj;
				g_oXSclFileMngr.AddNewChild(pXSclFileObj);
				pXSclFileObj->m_nSize = nSize;
				pXSclFileObj->m_strName = GetFileNameFromFilePath(strSclFilePath);
				pXSclFileObj->m_strID = g_oXSclFileMngr.GenerateSclFileObjID();
				pXSclFileObj->m_strSclPath = strSclFilePath;
				pXSclFileObj->m_nUse = 1;
//#ifdef _PSX_QT_LINUX_
				pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs(strSclFilePath,m_pSclStation,this,pXSclFileObj->m_strID);
// #else 
// 				pXSclFileObj->m_strSsclPath = Global_ParseSclFileSaveSclCfgs_EX(strSclFilePath,m_pSclStation,this);
// #endif
				g_oXSclFileMngr.SaveSclFileMngrCfg();
			}
		}
// 		else//���򵯳�SCL��ʷ��¼ѡ�����,ѡ����Ҫ��SCL
// 		{
// 			if (!IsFileExist(strCurrTscdFilePath))
// 			{
// 				QSttSelSclFileDlg oSttSelSclFileDlg(this);
// 				oSttSelSclFileDlg.InitUI();
// 				oSttSelSclFileDlg.exec();
// 				CString strCurrTscdFilePath;
// 				strCurrTscdFilePath = g_oXSclFileMngr.GetCurrSelTscdFilePah();
// 
// 				if (!IsFileExist(strCurrTscdFilePath))
// 					return;
// 			}
// 
// 			m_pSclStation->OpenSclStationFile(strCurrTscdFilePath);
// 		}
//		
//		g_oXSclFileMngr.SaveSclFileMngrCfg();
	}
	
	QSttSclFileParseDialog oSttSclFileDlg(m_pSclStation,m_oIecFont,this);
	oSttSclFileDlg.InitIecCfgDatasMngr(m_pIecCfgDatasMngr_Inter);
	m_pIecCfgDatasMngr_Inter->SetSmvInType(SMVTYPE_92);//zhouhj 202321 ����SCL֮ǰ,ȷ����ǰΪ9-2����
	m_pIecCfgDatasMngr_Inter->SetSmvType(SMVTYPE_92);

	connect(&oSttSclFileDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),SLOT(slot_IecCfgDataMngrUpdate()));
	Global_SoftKeyBoardAttachObj(&oSttSclFileDlg,STT_DefaultKeyboardType_English);
	oSttSclFileDlg.exec();
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
	disconnect(&oSttSclFileDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),this,SLOT(slot_IecCfgDataMngrUpdate()));

	m_pImportSCLToolBtn->setEnabled(true);
	connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));
}

void QSttIecConfigDialog::slot_IecCfgDataMngrUpdate()
{
	CIecCfgDatasSMV* pIecCfgDatasSMV = m_pIecCfgDatasMngr_Inter->GetSmvMngr();

	int nSelDataset = 0;
	int nSelSecurity = 0;
	int nSelSmpRate = 0;
	int nSelRefrTm = 0;

	m_pIecSMV92OutWidget->GetOptSelectState(nSelDataset,nSelSecurity,nSelSmpRate,nSelRefrTm);
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
		{
			pIecCfg92Data = (CIecCfg92Data *)pCurObj;
			pIecCfg92Data->m_nUseDataSet = nSelDataset;
			pIecCfg92Data->m_nUseEncrupt = nSelSecurity;
			pIecCfg92Data->m_nUseSampRate = nSelSmpRate;
			pIecCfg92Data->m_nUseRefreshTime = nSelRefrTm;
		}
	}

	InitData();
}

void QSttIecConfigDialog::slot_TreeItemChanged( QTreeWidgetItem * item, int /*column*/ )
{
}

void QSttIecConfigDialog::slot_CancelBtnClicked()
{
	ExitHideKeyboardWidget();
	close();
}

void QSttIecConfigDialog::slot_SaveBtnClicked()
{
	ExitHideKeyboardWidget();
	m_pSaveToolBtn->setDisabled(true);
	m_pSysParasWidget->SaveData();
	m_pIecSMV92OutWidget->SaveData();
	m_pIecSMVFT3OutWidget->SaveData();

	if (m_pIecSMV92InWidget != NULL)
	{
		m_pIecSMV92InWidget->SaveData();
	}
	if (m_pIecSMVFT3InWidget != NULL)
	{
		m_pIecSMVFT3InWidget->SaveData();
	}

	m_pIecGinWidget->SaveData();
	m_pIecGoutWidget->SaveData();

	if (!m_pIecCfgDatasMngr_Inter->HasContrlBlock_Selected(m_bTotalFiberNum_LC,m_bTotalFiberNum_STSend))//zhouhj 20220404 ���������,���ҵ�ǰIEC����Ϊ�յ�����£����ܿ�ʼ����
	{
		CString strTitle, strText;
		//strTitle = _T("����");
		//strText = _T("��ǰIEC����Ϊ��.");
		CXMessageBox::information(this,g_sLangTxt_warning ,g_sLangTxt_NullIEC);
		m_pSaveToolBtn->setDisabled(false);
		return;
	}

	m_pIecCfgDatasMngr_Extern->DeleteAll();
	m_pIecCfgDatasMngr_Extern->InitDatasMngr();
	m_pIecCfgDatasMngr_Extern->AppendEx(*m_pIecCfgDatasMngr_Inter);
	m_pIecCfgDatasMngr_Inter->RemoveAll();
	m_pIecCfgDatasMngr_Extern->InitAfterRead();
	m_pIecCfgDatasMngr_Extern->UpdateFiberIdex2();
	CIecCfgDatasSMV *pSmvMngr = m_pIecCfgDatasMngr_Extern->GetSmvMngr();
	pSmvMngr->InitCommonFromCfgDatas();
	pSmvMngr->InitCfgDatasByCommon();

	CIecCfgDatasSmvIn *pSmvInMngr = m_pIecCfgDatasMngr_Extern->GetSmvInMngr();
	pSmvInMngr->InitCommonFromCfgDatas();
	pSmvInMngr->InitCfgDatasByCommon();

	//ͬ�����������źš�ʵ���ϸöԻ����ʱ��ֻ����һ���ź���ۡ�
	//��Ϊ���򿪶Ի�����������ֳ������������ò������½�IEC61850Config��Ŀ
	emit sig_IecCfgDataMngrUpdate();
	emit sig_IecCfg_New();
	QDialog::accept();
}

bool QSttIecConfigDialog::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Escape)
		{
			return true;
		}
	}
	return false;
}

CString QSttIecConfigDialog::OpenixmlFileDlg(BOOL bIsOpen)
{
	//CString strText = _T("IEC�����ļ�·��");
	QFileDialog dlg(this,g_sLangTxt_IECpath);
	dlg.setFileMode(QFileDialog::AnyFile);
	//strText = _T("IEC�ļ�(*.ixml)");
	dlg.setNameFilter(g_sLangTxt_IECdocument);

	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetLibraryPath();
	dlg.setDirectory(strPath);
	//strText = _T("�ļ�·��");
	dlg.setLabelText(QFileDialog::LookIn,g_sLangTxt_FilePath);
	//strText = _T("�ļ���");
	dlg.setLabelText(QFileDialog::FileName,g_sLangTxt_FileName);
	//strText = _T("�ļ�����");
	dlg.setLabelText(QFileDialog::FileType,g_sLangTxt_Native_FileType);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		//strText = _T("��");
		dlg.setLabelText(QFileDialog::Accept,g_sLangTxt_Open);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		//strText = _T("����");
		dlg.setLabelText(QFileDialog::Accept,g_sLangTxt_Save);	
	}
	//strText = _T("ȡ��");
	dlg.setLabelText(QFileDialog::Reject,g_sLangTxt_Cancel);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
	}

	return strFileName;
}
