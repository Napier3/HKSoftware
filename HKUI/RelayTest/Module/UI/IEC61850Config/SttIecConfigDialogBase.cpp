#include "SttIecConfigDialogBase.h"
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolButton>
#include <QFileDialog>
#include <QFile>
#include "../SttTestCntrFrameApi.h"
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
#include <QApplication>
#include "../Module/CommonMethod/commonMethod.h"


QSttIecConfigDialogBase::QSttIecConfigDialogBase(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pSttIecConfigMainLayout = NULL;
	m_pSttIecConfigSplitter = NULL;
	m_IecConfigNavigationTree = NULL;
	m_nIecConfigNavigationTreeIndex = 0;
	m_pIecConfigRightTabWidget = NULL;
	m_pIecConfigRightStackedWidget = NULL;
	m_pSttIecChsEditStackedWidget = NULL;
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
	m_pSttIecChsEdit92OutWidget = NULL;
	m_pSttIecChsEditFT3OutWidget = NULL;
	m_pSttIecChsEdit92InWidget = NULL;
	m_pSttIecChsEditFT3InWidget = NULL;
	m_pSttIecChsEditGinWidget = NULL;
	m_pSttIecChsEditGoutWidget = NULL;
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
}

QSttIecConfigDialogBase::~QSttIecConfigDialogBase()
{
	if (m_pIecCfgDatasMngr_Inter != NULL)
	{
		delete m_pIecCfgDatasMngr_Inter;
		m_pIecCfgDatasMngr_Inter = NULL;
	}
}

void QSttIecConfigDialogBase::SetIecConfigFont()
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
void QSttIecConfigDialogBase::closeEvent( QCloseEvent * event )
{
	event->accept();
}

void QSttIecConfigDialogBase::InitUI()
{

#ifdef _PSX_QT_WINDOWS_
	CString strFilePath = _P_GetResourcePath();
	strFilePath += _T("tree.ico");
	m_oIconTree.addFile(strFilePath);
#else
	CString strFilePath = ":/ctrls/images/tree.ico";
	m_oIconTree.addFile(strFilePath);
#endif
#ifndef _PSX_QT_LINUX_  //窗口大小区分
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
  	resize(nWidth, nHeight);//充满窗口

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
	strTitle = /*_T("IEC配置")*/g_sLangTxt_Gradient_IECConfiguration; //lcq
	setWindowTitle(strTitle);
#else
	resize(stt_FrameTestCntrFrameWidth(),stt_FrameTestCntrFrameHeight());
	this->setFixedWidth(stt_FrameTestCntrFrameWidth());
	this->setFixedHeight(stt_FrameTestCntrFrameHeight());
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif
 	

	m_pSttIecConfigMainLayout = new QGridLayout(this);
	m_pIecConfigRightTabWidget = new QSttTabWidget(this);
// 	m_pIecConfigRightTabWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget = new QStackedWidget(m_pIecConfigRightTabWidget);
	m_pSttIecChsEditStackedWidget = new QStackedWidget(this);
	m_pSttIecConfigSplitter = new QSplitter(Qt::Horizontal);
	CreateToolBar();//创建工具栏
	CreateNavigationTree();//创建导航栏

	CString strTemp;
	xlang_GetLangStrByFile(strTemp,"IEC_SysParasConfig");

	m_pIecConfigRightStackedWidget->setCurrentIndex(0);//默认显示第一个堆栈视图
	m_pIecConfigRightTabWidget->addTab(m_pIecConfigRightStackedWidget,m_oIconTree,strTemp);
	m_pSttIecConfigSplitter->addWidget(m_IecConfigNavigationTree);

#ifdef _PSX_QT_LINUX_
	m_pSttIecConfigSplitter->addWidget(m_pIecConfigRightTabWidget);
#else
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
#endif

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
}

void QSttIecConfigDialogBase::ReleaseUI()
{

}

void QSttIecConfigDialogBase::CreateNavigationTree()
{
	m_IecConfigNavigationTree = new QTreeWidget;
	m_IecConfigNavigationTree->setStyleSheet("QTreeWidget::item{height:30px}");
	m_IecConfigNavigationTree->header()->setVisible(false);
	//m_IecConfigNavigationTree->setFont(m_oIecFont);
	
	//2022-11-22  sy checkbox换成图片
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QTreeView::indicator:checked {image: url(:/ctrls/images/checked.png);} QTreeView::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	m_IecConfigNavigationTree->setStyleSheet(strStyleSheet);

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
	pChildItem->setCheckState(0, Qt::Checked);
	pQTreeTopItem->addChild(pChildItem);
	m_pIecSMV92OutWidget = new QSttIecSMV92Widget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92OutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92OutWidget);

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEdit92OutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV92);
	m_pSttIecChsEdit92OutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEdit92OutWidget);
#endif

	//FT3报文
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
	pChildItem->setCheckState(0, Qt::Checked);
	pQTreeTopItem->addChild(pChildItem);
	m_pIecSMVFT3OutWidget = new QSttIecSMVFT3OutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3OutWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3OutWidget);

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEditFT3OutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV_FT3OUT);
	m_pSttIecChsEditFT3OutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditFT3OutWidget);
#endif

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
	pChildItem->setCheckState(0, Qt::Checked);
	pQTreeTopItem->addChild(pChildItem);
	m_pIecSMV92InWidget = new QSttIecSMV92InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
//	m_pIecSMV92InWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMV92InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMV92InWidget);  

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEdit92InWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV92IN);
	m_pSttIecChsEdit92InWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEdit92InWidget);
#endif

	//FT3报文
	astrItemDesc.clear();
	strTemp = tr("FT3");
	astrItemDesc<<strTemp;
	pChildItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_SECOND);
	pChildItem->setCheckState(0, Qt::Checked);
	pQTreeTopItem->addChild(pChildItem);
	m_pIecSMVFT3InWidget = new QSttIecSMVFT3InWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecSMVFT3InWidget);
	m_oTreeStackedWidgetHash.insert(pChildItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecSMVFT3InWidget);

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEditFT3InWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_SMV_FT3IN);
	m_pSttIecChsEditFT3InWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditFT3InWidget);
#endif

	//GOOSE 发布
	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Publish");
	astrItemDesc<<strTemp;
	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);
	m_pIecGoutWidget = new QSttIecGoutWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
// 	m_pIecGoutWidget->setFont(m_oIecFont);
	m_pIecConfigRightStackedWidget->addWidget(m_pIecGoutWidget);
	m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));
	m_oRightStackedWidgetList.append(m_pIecGoutWidget);

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEditGoutWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_GOUT);
	m_pSttIecChsEditGoutWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditGoutWidget);
#endif

 	//GOOSE 订阅
 	astrItemDesc.clear();
	xlang_GetLangStrByFile(strTemp,"IEC_Subscription");
 	astrItemDesc<<strTemp;
 	pQTreeTopItem = new QTreeWidgetItem(astrItemDesc,STT_IECCONFIG_TREE_LEVEL_TOP);
	pQTreeTopItem->setIcon(0,m_oIconTree);
 	m_IecConfigNavigationTree->addTopLevelItem(pQTreeTopItem);
 	m_pIecGinWidget = new QSttIecGinWidget(m_oIecFont,m_pIecConfigRightStackedWidget);
// 	m_pIecGinWidget->setFont(m_oIecFont);
 	m_pIecConfigRightStackedWidget->addWidget(m_pIecGinWidget);
 	m_oTreeStackedWidgetHash.insert(pQTreeTopItem ,(m_pIecConfigRightStackedWidget->count()-1));

#ifndef _PSX_QT_LINUX_
	m_pSttIecChsEditGinWidget = new QSttIecChsEditWidget(STT_IEC_CHS_TYPE_GIN);
	m_pSttIecChsEditGinWidget->setFont(m_oIecFont);
	m_pSttIecChsEditStackedWidget->addWidget(m_pSttIecChsEditGinWidget);
#endif

	m_IecConfigNavigationTree->expandAll();

	connect(m_IecConfigNavigationTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)),SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	connect(m_IecConfigNavigationTree, SIGNAL(itemChanged ( QTreeWidgetItem *, int )), SLOT(slot_TreeItemChanged( QTreeWidgetItem *, int )));

#ifndef _PSX_QT_LINUX_
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
#endif
}

void QSttIecConfigDialogBase::CreateToolBar()
{
	CString strTemp;
	m_pSttIecConfigToolBar = new QToolBar(tr(""),this);
// 	m_pSttIecConfigToolBar->setFont(m_oIecFont);
	m_pOpenCfgToolBtn = new QToolButton(m_pSttIecConfigToolBar);
	//m_pOpenCfgToolBtn->setText(tr("打开配置"));
	xlang_SetLangStrToWidget(m_pOpenCfgToolBtn, "IEC_OpenConfig", XLang_Ctrls_QToolButton);
	//m_pOpenCfgToolBtn->setIcon(QIcon(":/res/images/open.png"));
	xlang_GetLangStrByFile(strTemp,"IEC_OpenConfigFile");
	m_pOpenCfgToolBtn->setToolTip(strTemp);
	m_pOpenCfgToolBtn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	m_pSttIecConfigToolBar->addWidget( m_pOpenCfgToolBtn );

	m_pSaveAsCfgToolBtn = new QToolButton(m_pSttIecConfigToolBar);
	xlang_SetLangStrToWidget(m_pSaveAsCfgToolBtn, "IEC_ConfigSaveAs", XLang_Ctrls_QToolButton);
// 	m_pSaveAsCfgToolBtn->setText(tr("配置另存"));
// 	m_pSaveAsCfgToolBtn->setIcon(QIcon(":/res/images/save as.png"));
	xlang_GetLangStrByFile(strTemp,"IEC_ConfigFileSaveAs");
	m_pSaveAsCfgToolBtn->setToolTip(strTemp);
	m_pSaveAsCfgToolBtn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	m_pSttIecConfigToolBar->addWidget( m_pSaveAsCfgToolBtn );

	m_pImportSCLToolBtn = new QToolButton(m_pSttIecConfigToolBar);
// 	m_pImportSCLToolBtn->setText(tr("导入SCL"));
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
// 	m_pSaveToolBtn->setText(tr(" 确定 "));
// 	m_pSaveToolBtn->setIcon(QIcon(":/pic/images/set.png"));
	xlang_SetLangStrToWidget(m_pSaveToolBtn, "sOK", XLang_Ctrls_QToolButton);
	xlang_GetLangStrByFile(strTemp,"IEC_Message");
	m_pSaveToolBtn->setToolTip(strTemp);
	m_pSaveToolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_pSaveToolBtn->setFocusPolicy(Qt::StrongFocus);
	m_pSttIecConfigToolBar->addWidget(m_pSaveToolBtn);


	m_pCancelToolBtn = new QToolButton(m_pSttIecConfigToolBar);
// 	m_pCancelToolBtn->setText(tr(" 退出 "));
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

void QSttIecConfigDialogBase::InitData()
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

// void QSttIecConfigDialogBase::slot_UpdateData()
// {
// 	if (m_pIecSMV92OutWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEdit92OutWidget->InitData(m_pIecSMV92OutWidget->GetCfgChs());
// 		m_pIecSMV92OutWidget->m_bDataSelChanged = false;
// 	}
// 	if (m_pIecSMVFT3OutWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEditFT3OutWidget->InitData(m_pIecSMVFT3OutWidget->GetCfgChs());
// 		m_pIecSMVFT3OutWidget->m_bDataSelChanged = false;
// 	}
// 	if (m_pIecSMV92InWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEdit92InWidget->InitData(m_pIecSMV92InWidget->GetCfgChs());
// 		m_pIecSMV92InWidget->m_bDataSelChanged = false;
// 	}
// 	if (m_pIecSMVFT3InWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEditFT3InWidget->InitData(m_pIecSMVFT3InWidget->GetCfgChs());
// 		m_pIecSMVFT3InWidget->m_bDataSelChanged = false;
// 	}
// 	if (m_pIecGinWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEditGinWidget->InitData(m_pIecGinWidget->GetCfgChs());
// 		m_pIecGinWidget->m_bDataSelChanged = false;
// 	}
// 	if (m_pIecGoutWidget->m_bDataSelChanged)
// 	{
// 		m_pSttIecChsEditGoutWidget->InitData(m_pIecGoutWidget->GetCfgChs());
// 		m_pIecGoutWidget->m_bDataSelChanged = false;
// 	}
// }

QString QSttIecConfigDialogBase::GetTreetItemAllString(QTreeWidgetItem *pCurSelItem)
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

void QSttIecConfigDialogBase::slot_TreeItemClicked(QTreeWidgetItem * pItem, int nColumn )
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
	m_nIecCIecChsEditStackedIndex = m_nIecConfigNavigationTreeIndex-1;

	QString strText;
	strText = GetTreetItemAllString(pCurSelItem);
	m_pIecConfigRightTabWidget->setTabText(0, strText/*pCurSelItem->text(0)*/);
	m_pIecConfigRightStackedWidget->setCurrentIndex(m_nIecConfigNavigationTreeIndex);

#ifndef _PSX_QT_LINUX_
	if (m_nIecConfigNavigationTreeIndex==0)
	{
		m_pSttIecChsEditStackedWidget->hide();
	}
	else
	{
		m_pSttIecChsEditStackedWidget->show();
	}
	m_pSttIecChsEditStackedWidget->setCurrentIndex(m_nIecCIecChsEditStackedIndex);
#endif

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

void QSttIecConfigDialogBase::slot_OpenCfgBtnClicked()
{
	CString strFilePath,strFolderPath;

	strFolderPath = g_oFileMngrTool.GetFolderPath_STD(STT_FILE_MNGR_IEC61850Config) ;

#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;
// 	CString strFolderPath;
// 	strFolderPath = _P_GetLibraryPath();
	astrPostfix<<"*.ixml";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
// 	oOpenDlg.setFont(m_oIecFont);// 2022-10-22 sy 采用g_pSttGlobalFont
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

//  	CString strFilePath = QFileDialog::getOpenFileName(this, tr("打开IEC配置文件"), "." ,"ixml(*.ixml)");
// 
//  	if(strFilePath.IsEmpty())
//  		return;
 
	if(strFilePath.IsEmpty())//20241025 wuxinyi 应判断路径是否为空
	{
		return;
	}
	if (!IsFileExist(strFilePath))
	{
		return;
	}

	if (!m_pIecCfgDatasMngr_Inter->OpenIecCfgFile(strFilePath))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("打开配置文件(%s)失败."),strFilePath.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_configurationfile.GetString(),strFilePath.GetString());
		return;
	}

	InitData();
}

void QSttIecConfigDialogBase::slot_SaveAsCfgBtnClicked()
{

	//20241025 wuxinyi 另存为时需要先保存数据一下，否则存储是上一次的数据，修改后数据没保存
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

void QSttIecConfigDialogBase::slot_ImportSCLBtnClicked()
{
	disconnect(m_pImportSCLToolBtn, SIGNAL(clicked()),this,SLOT(slot_ImportSCLBtnClicked()));
	m_pImportSCLToolBtn->setEnabled(false);

	if (m_pSclStation == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("QSttIecConfigDialogBase中(m_pSclStation==NULL)."));
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


	//如果当前Scl链表中内容为空,则选择SCL文件
	if (m_pSclStation->GetCount() == 0)
	{
		bool bIsOpen = false;
//		if (g_oXSclFileMngr.GetCount() == 0)//如果当前SCL历史记录为空,则直接弹出选择SCL界面
		{
			CString strSclFilePath;
			long nSize = 0;
#ifdef _PSX_QT_LINUX_
			QStringList astrPostfix;
			CString strFolderPath;
			strFolderPath = _P_GetLibraryPath();
            astrPostfix<<"*.scd"<<"*.cid"<<"*.icd"<<"*.tscd";
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
				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,/* _T("获取SCL文件路径失败(%s).") */g_sLangTxt_Native_FailtoGetsclPath.GetString(),strSclFilePath.GetString());
				
				m_pImportSCLToolBtn->setEnabled(true);
				connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));

				return;
			}

			bIsOpen = true;
			nSize = oOpenDlg.GetFileSize();
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
			//strText = _T("SCD文件(*.scd);;ICD文件(*.icd);;CID文件(*.cid);;TSCD文件(*.tscd)");
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
			//选择了一个SCL文件
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
// 		else//否则弹出SCL历史记录选择界面,选择需要的SCL
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
	m_pIecCfgDatasMngr_Inter->SetSmvInType(SMVTYPE_92);//zhouhj 202321 导入SCL之前,确保当前为9-2类型
	m_pIecCfgDatasMngr_Inter->SetSmvType(SMVTYPE_92);

	connect(&oSttSclFileDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),SLOT(slot_IecCfgDataMngrUpdate()));
//	Global_SoftKeyBoardAttachObj(&oSttSclFileDlg,STT_DefaultKeyboardType_English);
	oSttSclFileDlg.exec();
#ifdef _USE_SoftKeyBoard_ 
	QSoftKeyBoard::ReAttachObj();
#endif
	disconnect(&oSttSclFileDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),this,SLOT(slot_IecCfgDataMngrUpdate()));
	
	m_pImportSCLToolBtn->setEnabled(true);
	connect(m_pImportSCLToolBtn, SIGNAL(clicked()),SLOT(slot_ImportSCLBtnClicked()));

}

void QSttIecConfigDialogBase::slot_IecCfgDataMngrUpdate()
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

void QSttIecConfigDialogBase::slot_TreeItemChanged( QTreeWidgetItem * item, int /*column*/ )
{
}

void QSttIecConfigDialogBase::slot_CancelBtnClicked()
{
#ifdef _USE_SoftKeyBoard_
    ExitHideKeyboardWidget();
#endif
	close();
}

void QSttIecConfigDialogBase::slot_SaveBtnClicked()
{
#ifdef _USE_SoftKeyBoard_
    ExitHideKeyboardWidget();
#endif
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

	if (!m_pIecCfgDatasMngr_Inter->HasContrlBlock_Selected(m_bTotalFiberNum_LC,m_bTotalFiberNum_STSend))//zhouhj 20220404 数字量输出,并且当前IEC配置为空的情况下，不能开始测试
	{
		CString strTitle, strText;
		//strTitle = _T("警告");
		//strText = _T("当前IEC配置为空.");
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

	//同步发送两个信号。实际上该对话框打开时，只绑定了一个信号与槽。
	//因为：打开对话框仅用于两种场景：更新配置参数、新建IEC61850Config项目
	emit sig_IecCfgDataMngrUpdate();
	emit sig_IecCfg_New();
	QDialog::accept();
}

bool QSttIecConfigDialogBase::eventFilter(QObject *obj, QEvent *event)
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

CString QSttIecConfigDialogBase::OpenixmlFileDlg(BOOL bIsOpen)
{
	//CString strText = _T("IEC配置文件路径");
	QFileDialog dlg(this,g_sLangTxt_IECpath);
	dlg.setFileMode(QFileDialog::AnyFile);
	//strText = _T("IEC文件(*.ixml)");
	dlg.setNameFilter(g_sLangTxt_IECdocument);

	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetLibraryPath();
	dlg.setDirectory(strPath);
	//strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn,g_sLangTxt_FilePath);
	//strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName,g_sLangTxt_FileName);
	//strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType,g_sLangTxt_Native_FileType);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		//strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept,g_sLangTxt_Open);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		//strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept,g_sLangTxt_Save);	
	}
	//strText = _T("取消");
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
