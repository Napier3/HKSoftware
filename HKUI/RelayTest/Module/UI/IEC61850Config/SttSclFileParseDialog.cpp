#include "SttSclFileParseDialog.h"
#include <QCloseEvent>
#include <QHeaderView>
#include <QToolButton>
#include <QFileDialog>
#ifdef _PSX_QT_LINUX_
#include "../SttTestCntrFrameApi.h"
#endif
#include "SttSclIedTreeItem.h"
#include "../../../../61850/Module/IecCfgSclTool/SclToIecCfgTool.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../SCL/QSttSelSclFileDlg.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../../Module/System/TickCount32.h"
#include "../../XLangResource_Native.h"

#include <QDesktopWidget>
#include <QApplication>

void GetRepeatSclCtrlsLogString(CExBaseList &oRepeatListRef,CString &strMsg,BOOL bSmvInOutMerge = TRUE)
{
	CString strSmvIn = _T(""),strSmvOut = _T(""),strGin = _T(""),strGout = _T("");
	POS pos = oRepeatListRef.GetHeadPosition();
	CSclCtrlBase *pSclCtrlBase = NULL;
	xlang_GetLangStrByFile(strMsg, "IEC_Msg_OverWriteCtrl");

	while(pos)
	{
		pSclCtrlBase = (CSclCtrlBase *)oRepeatListRef.GetNext(pos);

		if ((pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)||(pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN))
		{
			if ((pSclCtrlBase->m_dwItemData == 0)&&(!bSmvInOutMerge))//用于测试仪订阅
			{
				strSmvIn.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());
			}
			else//用于测试仪发布
			{
				strSmvOut.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());		 
			}
		}
		else if (pSclCtrlBase->m_dwItemData == 0)//用于测试仪Goose订阅
		{
			strGin.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());
		}
		else//用于测试仪Goose发布
		{
			strGout.AppendFormat(_T("0x%04X;"),pSclCtrlBase->GetAppID());		 
		}
	}

	CString strText;
	if (!strSmvOut.IsEmpty())
	{
		strText.Format(_T("(AppID=%s)"),strSmvOut.GetString());
		strText = g_sLangTxt_samplepublish + strText;
		//strMsg.AppendFormat(_T("采样值发布(AppID=%s)"),strSmvOut.GetString());
	}

	if (!strSmvIn.IsEmpty())
	{
		strText.Format(_T("(AppID=%s)"),strSmvIn.GetString());
		strText =g_sLangTxt_valuesubscrip + strText;
		//strMsg.AppendFormat(_T("采样值订阅(AppID=%s)"),strSmvIn.GetString());
	}

	if (!strGin.IsEmpty())
	{
		strText.Format(_T("(AppID=%s)"),strGin.GetString());
		strText = g_sLangTxt_IEC_Subscription + strText;
		//strMsg.AppendFormat(_T("GOOSE订阅(AppID=%s)"),strGin.GetString());
	}

	if (!strGout.IsEmpty())
	{
		strText.Format(_T("(AppID=%s)"),strGout.GetString());
		strText = g_sLangTxt_IEC_Publish + strText;
		//strMsg.AppendFormat(_T("GOOSE发布(AppID=%s)"),strGout.GetString());
	}

	strMsg = strMsg + strText;
}

QSttSclFileParseDialog::QSttSclFileParseDialog(CSclStation  *pSclStation,QFont oFont , QWidget *parent)
: QDialog(parent)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_oIecFont = oFont;
	setFont(m_oIecFont);

	m_pSclFileIED_MainLayout = NULL;
	m_pSplitterLeft_VBoxLayout = NULL;
	m_pSclFileIED_Splitter = NULL;
	m_pSclFileIED_TreeWidget = NULL;
	m_pSclFileIedCtrls_TabWidget = NULL;
	m_pSplitterLeftWidget = NULL;
	m_pSclStation = pSclStation;
	m_pCurrSelSclIed = NULL;
	m_pIecCfgDatasMngr = NULL;
	m_pSCLSelect_PushButton = NULL;

	m_pSplitterRight_VBoxLayout = NULL;
	m_pSplitterRightWidget = NULL;
	m_pLeftDownSplitter = NULL;
	m_pLeftDown_VBoxLayout = NULL;
	m_pLeftDownWidget = NULL;
// #ifdef USE_STT_SCLIED_VIEW
// 	m_pIedViewWidget = NULL;
// #endif
	m_pSttSclParseProgDlg = NULL;
	m_pSttSclViewDatasParseThread = NULL;
	m_pSttSclSkectMapWidget = NULL;

	InitUI();
	InitData();
	SetSclFileParseFont();
	installEventFilter(this);
	m_pSCLSelect_PushButton->setFocus();
}

QSttSclFileParseDialog::~QSttSclFileParseDialog()
{
	m_oSelectedSclCtrlsRef.RemoveAll();

	if (m_pSttSclParseProgDlg != NULL)
	{
		delete m_pSttSclParseProgDlg;
		m_pSttSclParseProgDlg = NULL;
	}
}

void QSttSclFileParseDialog::SetSclFileParseFont()
{
	m_pSclFileIED_TreeWidget->setFont(*g_pSttGlobalFont);
	m_pSclFileIED_TreeWidget->header()->setFont(*g_pSttGlobalFont);
	m_pSclFileIedCtrls_TabWidget->setFont(*g_pSttGlobalFont);
	m_pIedSearch_LineEdit->setFont(*g_pSttGlobalFont);
	m_pSCLSelect_PushButton->setFont(*g_pSttGlobalFont);
	m_pOneKeyCfg_PushButton->setFont(*g_pSttGlobalFont);
	m_pImportIecCfg_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	m_pFind_Label->setFont(*g_pSttGlobalFont);
}

void QSttSclFileParseDialog::UpdateIedSearchEditFocus()
{
	m_pIedSearch_LineEdit->setFocusPolicy(Qt::NoFocus);

	m_pSCLSelect_PushButton->setFocus();
	CTickCount32 oTickCount;
	oTickCount.DoEvents(10);
	m_pIedSearch_LineEdit->setFocusPolicy(Qt::StrongFocus);
}

void QSttSclFileParseDialog::closeEvent( QCloseEvent * event )
{
	event->accept();
}

void QSttSclFileParseDialog::InitUI()
{
	CString strFind, strGOOSEPublish, strSMVPublish, 
		strGOOSESub, strSMVSub,strSclSelect ,strConfig, strImport, strCancle;
	
	strSclSelect = g_sLangTxt_Native_SCLPath;//_T("选择SCL文件");
	xlang_GetLangStrByFile(strFind, "IEC_Find");
	strFind += ":";
	xlang_GetLangStrByFile(strGOOSEPublish, "IEC_Publish");
	xlang_GetLangStrByFile(strSMVPublish, "IEC_SMVPublish");
	xlang_GetLangStrByFile(strGOOSESub, "IEC_Subscription");
	xlang_GetLangStrByFile(strSMVSub, "IEC_SMVSubscription");
	xlang_GetLangStrByFile(strConfig, "IEC_Configure");
	xlang_GetLangStrByFile(strImport, "sImport");
	xlang_GetLangStrByFile(strCancle, "sCancel");

#ifdef _PSX_QT_LINUX_
	resize(stt_FrameTestCntrFrameWidth(),stt_FrameTestCntrFrameHeight());
	this->setFixedWidth(stt_FrameTestCntrFrameWidth());
	this->setFixedHeight(stt_FrameTestCntrFrameHeight());
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#else
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
	//strTitle = _T("SCL解析界面");
	strTitle = g_sLangTxt_Gradient_SCLPars; //lcq
	setWindowTitle(strTitle);

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
#endif

 	m_pSclFileIED_MainLayout = new QVBoxLayout(this);
	m_pSclFileIED_Splitter = new QSplitter(Qt::Horizontal);
 	CreateSclFileIEDTree();//创建IED树
	m_pSplitterLeftWidget = new QWidget(m_pSclFileIED_Splitter);
	m_pSplitterLeft_VBoxLayout = new QVBoxLayout(m_pSplitterLeftWidget);

	m_pSplitterRightWidget = new QWidget(m_pSclFileIED_Splitter);
	m_pSplitterRight_VBoxLayout = new QVBoxLayout(m_pSplitterRightWidget);

	m_pIedSearch_HBoxLayout = new QHBoxLayout/*(m_pSplitterLeftWidget)*/;
	m_pFind_Label = new QLabel(strFind);
	m_pIedSearch_HBoxLayout->addWidget(m_pFind_Label/*new QLabel(strFind)*/);
	m_pIedSearch_LineEdit = new QSttLineEdit(this);
	m_pIedSearch_HBoxLayout->addWidget(m_pIedSearch_LineEdit);
	m_pSplitterLeft_VBoxLayout->addLayout(m_pIedSearch_HBoxLayout);
	//m_pSplitterLeft_VBoxLayout->addWidget(m_pSclFileIED_TreeWidget);
	m_pLeftDownWidget = new QWidget(m_pSplitterLeftWidget);
	m_pSplitterLeft_VBoxLayout->addWidget(m_pLeftDownWidget);

	//2023/9/19 wjs 加入左下角表格
	m_pLeftDown_VBoxLayout = new QVBoxLayout(m_pLeftDownWidget);
	m_pLeftDownSplitter = new QSplitter(Qt::Vertical);
	m_pSclFileIED_TreeWidget->setParent(m_pLeftDownSplitter);
	
 	m_pSclFileIedCtrls_TabWidget = new QTabWidget;
	m_pSplitterRight_VBoxLayout->addWidget(m_pSclFileIedCtrls_TabWidget);

	m_pGooseOutWidget = new QSttSclCtrlsWidget(STT_SCL_CTRLS_TYPE_GOOSEOUT,&m_oSelectedSclCtrlsRef ,m_oIecFont,m_pSclFileIedCtrls_TabWidget);
	m_pSmvOutWidget = new QSttSclCtrlsWidget(STT_SCL_CTRLS_TYPE_SMVOUT,&m_oSelectedSclCtrlsRef,m_oIecFont,m_pSclFileIedCtrls_TabWidget);
	m_pGooseInWidget = new QSttSclCtrlsWidget(STT_SCL_CTRLS_TYPE_GOOSEIN,&m_oSelectedSclCtrlsRef,m_oIecFont,m_pSclFileIedCtrls_TabWidget);
	m_pSmvInWidget = new QSttSclCtrlsWidget(STT_SCL_CTRLS_TYPE_SMVIN,&m_oSelectedSclCtrlsRef,m_oIecFont,m_pSclFileIedCtrls_TabWidget);
	m_pSclFileIedCtrls_TabWidget->addTab(m_pGooseOutWidget,strGOOSEPublish);
	m_pSclFileIedCtrls_TabWidget->addTab(m_pSmvOutWidget,strSMVPublish);
	m_pSclFileIedCtrls_TabWidget->addTab(m_pGooseInWidget,strGOOSESub);
	m_pSclFileIedCtrls_TabWidget->addTab(m_pSmvInWidget,strSMVSub);

// #ifdef USE_STT_SCLIED_VIEW
// 	CString strText;
// 	strText =/* "示意图"*/g_sLangTxt_Native_schematic;
// 	//lichao 添加图形界面
// 	m_pIedViewWidget = new QSttSclIedViewWidget(this);
// 	m_pSclFileIedCtrls_TabWidget->addTab(m_pIedViewWidget, strText);
// #endif

	m_pSttSclSkectMapWidget = new QSttSclIedSkectMapWidget(this);
	m_pSclFileIedCtrls_TabWidget->addTab(m_pSttSclSkectMapWidget,/* tr("示意图")*/g_sLangTxt_Native_schematic);
	m_pSttSclSkectMapWidget->InitUI();

	QSplitterHandle *handle = m_pSclFileIED_Splitter->handle(1); 
	handle->setToolTip(/* "已选中" */g_sLangTxt_Native_selected);
	handle->setAttribute(Qt::WA_Hover, true);
	m_pSclFileIED_Splitter->setStyleSheet(	"QSplitter::handle:hover{background-color: black}");

	m_pSclFileIED_Splitter->addWidget(m_pSplitterLeftWidget);
	m_pSclFileIED_Splitter->addWidget(m_pSplitterRightWidget);
	//m_pSclFileIED_Splitter->addWidget(m_pSclFileIedCtrls_TabWidget);
	m_pSclFileIED_Splitter->setStretchFactor(0,3);
	m_pSclFileIED_Splitter->setStretchFactor(1,7);

	//2023/9/12 wjs 添加SelectCtrlsGrid
	m_pSclSelectCtrlsGrid = new QSclSelectCtrlsGrid(m_pLeftDownSplitter);
	m_pSclSelectCtrlsGrid->InitGrid();
	m_pLeftDownSplitter->addWidget(m_pSclFileIED_TreeWidget);
	m_pLeftDownSplitter->addWidget(m_pSclSelectCtrlsGrid);
	QSplitterHandle *handle2 = m_pLeftDownSplitter->handle(1); 
	handle2->setToolTip(/* "已选中" */g_sLangTxt_Native_selected);
	handle2->setAttribute(Qt::WA_Hover, true);
	m_pLeftDownSplitter->setStyleSheet(	"QSplitter::handle:hover{background-color: black}");

	//m_pSclFileIED_Splitter->addWidget(m_pSclFileIedCtrls_TabWidget);
	m_pLeftDownSplitter->setStretchFactor(0,6);
	m_pLeftDownSplitter->setStretchFactor(1,4);
	m_pLeftDown_VBoxLayout->addWidget(m_pLeftDownSplitter);

	m_pSclFileBottom_HBoxLayout = new QHBoxLayout;
	m_pSCLSelect_PushButton = new QPushButton(strSclSelect);
	m_pOneKeyCfg_PushButton = new QPushButton(strConfig);
	m_pImportIecCfg_PushButton = new QPushButton(strImport);
	m_pCancel_PushButton = new QPushButton(strCancle);
	m_pOneKeyCfg_PushButton->setFixedWidth(130);
	m_pImportIecCfg_PushButton->setFixedWidth(80);
	m_pCancel_PushButton->setFixedWidth(80);
	m_pSclFileBottom_HBoxLayout->addWidget(m_pSCLSelect_PushButton);
	m_pSclFileBottom_HBoxLayout->addStretch();
	m_pSclFileBottom_HBoxLayout->addWidget(m_pOneKeyCfg_PushButton);
	m_pSclFileBottom_HBoxLayout->addWidget(m_pImportIecCfg_PushButton);
	m_pSclFileBottom_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pSclFileIED_MainLayout->addWidget(m_pSclFileIED_Splitter);
	m_pSclFileIED_MainLayout->addLayout(m_pSclFileBottom_HBoxLayout);
 	setLayout(m_pSclFileIED_MainLayout);
	connect(m_pSCLSelect_PushButton, SIGNAL(clicked()),SLOT(slot_SCLSelectBtnClicked()));
	connect(m_pOneKeyCfg_PushButton, SIGNAL(clicked()),SLOT(slot_OneKeyCfgBtnClicked()));
	connect(m_pImportIecCfg_PushButton, SIGNAL(clicked()), SLOT(slot_ImportIecCfgBtnClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), SLOT(slot_CancelBtnClicked()));
	connect(m_pSclFileIED_TreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)),SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	connect(m_pIedSearch_LineEdit,SIGNAL(editingFinished(/*const QString &*/)),this,SLOT(slot_IedSearchtextChanged(/*const QString &*/)));
	connect(m_pIedSearch_LineEdit,SIGNAL(clicked(/*const QString &*/)),this,SLOT(slot_IedSearchtextclicked(/*const QString &*/)));

	//2023/9/20 wjs 添加控制块选择按钮被点击事件
	connect(m_pGooseOutWidget->m_pSclCtrlsGrid,SIGNAL(sig_UpdateSelectCtrlsGrid()),this,SLOT(slot_UpdateSelectCtrlsGrid()));
	connect(m_pGooseInWidget->m_pSclCtrlsGrid,SIGNAL(sig_UpdateSelectCtrlsGrid()),this,SLOT(slot_UpdateSelectCtrlsGrid()));
	connect(m_pSmvOutWidget->m_pSclCtrlsGrid,SIGNAL(sig_UpdateSelectCtrlsGrid()),this,SLOT(slot_UpdateSelectCtrlsGrid()));
	connect(m_pSmvInWidget->m_pSclCtrlsGrid,SIGNAL(sig_UpdateSelectCtrlsGrid()),this,SLOT(slot_UpdateSelectCtrlsGrid()));

	// 20240408chenling 当分隔条拖动时，更新示意图的大小
	connect(m_pSclFileIED_Splitter, SIGNAL(splitterMoved(int , int )), this, SLOT(slot_UpdateSketchMapWidgetSize(int , int )));
	
	setFocusPolicy(Qt::StrongFocus);
#ifndef _PSX_QT_LINUX_
	showMaximized();
#endif
}

void QSttSclFileParseDialog::ReleaseUI()
{

}

void QSttSclFileParseDialog::CreateSclFileIEDTree()
{
	CString strList, strTitle;
	xlang_GetLangStrByFile(strList, "IEC_IEDList");
 	m_pSclFileIED_TreeWidget = new QTreeWidget;
// 	m_pSclFileIED_TreeWidget->setFont(m_oIecFont);
	m_pSclFileIED_TreeWidget->setColumnCount(1);
	//strTitle = _T("IED列表");
	m_pSclFileIED_TreeWidget->setHeaderLabel(g_sLangTxt_IEC_IEDList);
	m_pSclFileIED_TreeWidget->setStyleSheet("QTreeView::item{margin:2px;}");
}

//lichao初始化图形界面数据
void QSttSclFileParseDialog::InitIedInforDatas()
{
//#ifdef USE_STT_SCLIED_VIEW
	if (m_pSclStation == NULL)
	{
		return;
	}

	if (m_pSttSclParseProgDlg == NULL)
	{
		m_pSttSclParseProgDlg = new QSttProgDlg(NULL);
		m_pSttSclParseProgDlg->initUI(_T("SCL加载进度条"),_T("正在加载SCL文件,请稍侯..."));
	}

	m_pSttSclParseProgDlg->setModal(false);
	m_pSttSclParseProgDlg->Start(0,100,50);
	CTickCount32 oTickCount;

#ifdef _PSX_QT_LINUX_
	pthread_create((pthread_t*)&m_pSttSclViewDatasParseThread,NULL,SttSclViewDatasParseThread,(LPVOID)this );
#else
	m_pSttSclViewDatasParseThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttSclViewDatasParseThread,
		(LPVOID)this,0,NULL);
#endif

	while(m_pSttSclViewDatasParseThread != NULL)
	{
		oTickCount.DoEvents(2);
	}

	m_pSttSclParseProgDlg->Stop();
//#endif
// 	g_oGloalIEDNameList.clear();
// 	g_oIED_Hash.clear();
// 	g_oTotalIEDList.clear();
// 	CSclIed*pIedFirst=NULL;
// 	//------首先初始化ied名称数组和hash
// 	POS posFirst =m_pSclStation->GetHeadPosition();
// 	CExBaseObject *pObjFirst=NULL;
// 	long nIedIndex = 0;
// 	while (posFirst)
// 	{
// 		pObjFirst=m_pSclStation->GetNext(posFirst);
// 		if(pObjFirst->GetClassID()!=SCLIECCLASSID_IED)
// 		{
// 			continue;
// 		}
// 		pIedFirst= (CSclIed *)pObjFirst;
// 		g_oGloalIEDNameList.push_back(pIedFirst->m_strID);
// 
// 		if(!g_oIED_Hash.contains(pIedFirst->m_strID))
// 		{
// 			g_oIED_Hash.insert(pIedFirst->m_strID,nIedIndex);
// 		}
// 		nIedIndex++;
// 	}
// 	//--------------------
// 	POS pos =m_pSclStation->GetHeadPosition();
// 	CExBaseObject *pObj=NULL;
// 	
// 	CSclIed*pIed=NULL;
// 	while (pos)
// 	{
// 		pObj=m_pSclStation->GetNext(pos);
// 
// 		if(pObj->GetClassID()!=SCLIECCLASSID_IED)
// 		{
// 			continue;
// 		}
// 		pIed= (CSclIed *)pObj;
// 		_IED_INFO oIedInfo;
// 		oIedInfo.name=pIed->m_strID;
// 		oIedInfo.desc=pIed->m_strName;
// 		oIedInfo.type=pIed->m_strModel;
// 		//------以下要使用ied名称数组和hash
// 		Global_SclIed_To_IedInfor(pIed,&oIedInfo);
// 		g_oTotalIEDList.push_back(oIedInfo);	
// 	}
// 
// 	lastFillGseRecInexList();
// 	lastFillSmvRecInexList();
}

//#ifdef USE_STT_SCLIED_VIEW
#ifdef _PSX_QT_LINUX_
void* QSttSclFileParseDialog::SttSclViewDatasParseThread(LPVOID pParam)
#else
UINT QSttSclFileParseDialog::SttSclViewDatasParseThread(LPVOID pParam)
#endif
{
	QSttSclFileParseDialog *pSttSclFileParseDialog = (QSttSclFileParseDialog*)pParam;
	CSclStation  *pSclStation = pSttSclFileParseDialog->m_pSclStation;
	pSttSclFileParseDialog->m_pSttSclSkectMapWidget->m_pSttSclViewWidget->ReleaseList();


// #ifdef USE_STT_SCLIED_VIEW
// 	g_oGloalIEDNameList.clear();
// 	g_oIED_Hash.clear();
// 	_IED_INFO *pIED_INFO = NULL;
// 	long nIedCount = g_oTotalIEDList.size();
// 
// 	for (int nIndex = 0; nIndex<nIedCount;nIndex++)
// 	{
// 		pIED_INFO = g_oTotalIEDList.at(nIndex);
// 		delete pIED_INFO;
// 	}
// 
// 	g_oTotalIEDList.clear();
// #endif

	
	CSclIed*pIedFirst = NULL;
	//------首先初始化ied名称数组和hash
	POS posFirst = pSclStation->GetHeadPosition();
	CExBaseObject *pObjFirst=NULL;
	long nIedIndex = 0;
	while (posFirst)
	{
		pObjFirst=pSclStation->GetNext(posFirst);
		if(pObjFirst->GetClassID()!=SCLIECCLASSID_IED)
		{
			continue;
		}

		pIedFirst= (CSclIed *)pObjFirst;
        //chenling20231228
        CString strName = pIedFirst->m_strID + "\n" + pIedFirst->m_strName;
		pSttSclFileParseDialog->m_pSttSclSkectMapWidget->m_pSttSclViewWidget->m_strNameList.push_back(strName);

// #ifdef USE_STT_SCLIED_VIEW
// 		g_oGloalIEDNameList.push_back(pIedFirst->m_strID);
// 
// 		if(!g_oIED_Hash.contains(pIedFirst->m_strID))
// 		{
// 			g_oIED_Hash.insert(pIedFirst->m_strID,nIedIndex);
// 		}
// 		nIedIndex++;
// #endif
	}
	//--------------------
	POS pos =pSclStation->GetHeadPosition();
	CExBaseObject *pObj=NULL;

	CSclIed*pIed=NULL;
	while (pos)
	{
		pObj=pSclStation->GetNext(pos);

		if(pObj->GetClassID()!=SCLIECCLASSID_IED)
		{
			continue;
		}
		pIed= (CSclIed *)pObj;
		//chenling
		pSttSclFileParseDialog->m_pSttSclSkectMapWidget->m_pSttSclViewWidget->IedDataInfo(pIed);
	}
    pSttSclFileParseDialog->m_pSttSclViewDatasParseThread = NULL;

// #ifdef USE_STT_SCLIED_VIEW
// 		_IED_INFO *oIedInfo = new _IED_INFO;
// 		oIedInfo->name=pIed->m_strID;
// 		oIedInfo->desc=pIed->m_strName;
// 		oIedInfo->type=pIed->m_strModel;
// 		//------以下要使用ied名称数组和hash
// 		Global_SclIed_To_IedInfor(pIed,oIedInfo);
// 		g_oTotalIEDList.push_back(oIedInfo);
// 
// 	}
// 
// 	lastFillGseRecInexList();
// 	lastFillSmvRecInexList();
// 	pSttSclFileParseDialog->m_pSttSclViewDatasParseThread = NULL;
// #endif

#ifndef _PSX_QT_LINUX_
	return 1;
#endif
}
//#endif

void QSttSclFileParseDialog::InitData()
{
	InitIedInforDatas();
	UpdateIedTreeBySearchText("");
// 	CExBaseObject *pCurIed = NULL;
// 	QSttSclIedTreeItem *pSclIedTreeItem = NULL; 
// 	POS pos = m_pSclStation->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pCurIed = m_pSclStation->GetNext(pos);
// 
// 		if (pCurIed->GetClassID() != SCLIECCLASSID_IED)
// 		{
// 			continue;
// 		}
// 
// 		pSclIedTreeItem = new QSttSclIedTreeItem(m_pSclFileIED_TreeWidget);
// 		pSclIedTreeItem->SetTreeItemObject(pCurIed);
// 		pSclIedTreeItem->ShowItemData();
// 		m_pSclFileIED_TreeWidget->addTopLevelItem(pSclIedTreeItem);
// 	}
// 
// 	m_pCurrSelSclIed = (CSclIed*)m_pSclStation->FindByClassID(SCLIECCLASSID_IED);
// 	ShowSclIedDetail(m_pCurrSelSclIed);
//	connect(m_pSclFileIED_TreeWidget, SIGNAL(itemChanged ( QTreeWidgetItem *, int )), SLOT(slot_TreeItemChanged( QTreeWidgetItem *, int )));
//	m_pSclFileIED_TreeWidget->setCurrentItem(m_pSclFileIED_TreeWidget->topLevelItem(0));
}

void QSttSclFileParseDialog::UpdateIedTreeBySearchText(const CString &strSearchText)
{
	m_pSclFileIED_TreeWidget->clear();

	CExBaseObject *pCurIed = NULL;
	QSttSclIedTreeItem *pSclIedTreeItem = NULL; 
	QSttSclIedTreeItem *pSclIedTreeItemFirst = NULL; 
	CString strSearchTextUpper,strNameUpper,strIDUpper;
	strSearchTextUpper = m_strSearchText;
	strSearchTextUpper.MakeUpper();
	POS pos = m_pSclStation->GetHeadPosition();

	while(pos)
	{
		pCurIed = m_pSclStation->GetNext(pos);

		if (pCurIed->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		strNameUpper = pCurIed->m_strName;
		strIDUpper = pCurIed->m_strID;
		strNameUpper.MakeUpper();
		strIDUpper.MakeUpper();

		if ((strIDUpper.Find(strSearchTextUpper.GetString()) == -1)&&(strNameUpper.Find(strSearchTextUpper.GetString()) == -1))
		{
			continue;
		}

		pSclIedTreeItem = new QSttSclIedTreeItem(m_pSclFileIED_TreeWidget);
		pSclIedTreeItem->SetTreeItemObject(pCurIed);
		pSclIedTreeItem->ShowItemData();
		m_pSclFileIED_TreeWidget->addTopLevelItem(pSclIedTreeItem);

		if (pSclIedTreeItemFirst == NULL)
		{
			pSclIedTreeItemFirst = pSclIedTreeItem;
		}
	}

	if (pSclIedTreeItemFirst != NULL)
	{
		m_pCurrSelSclIed = (CSclIed*)pSclIedTreeItemFirst->GetTreeItemObject();
		ShowSclIedDetail(m_pCurrSelSclIed);
	}
	
}

void QSttSclFileParseDialog::ShowSclIedDetail(CSclIed *pSclIed)
{
	CSclCtrls *pSmvOutCtrls = pSclIed->GetSmvOuts();
	CSclCtrls *pSmvInCtrls = pSclIed->GetSmvIns();
	CSclCtrls *pGsOutCtrls = pSclIed->GetGsOuts();
	CSclCtrls *pGsInCtrls = pSclIed->GetGsIns();

	m_pSmvOutWidget->ShowDatas(pSmvOutCtrls);
	m_pSmvInWidget->ShowDatas(pSmvInCtrls);
	m_pGooseOutWidget->ShowDatas(pGsOutCtrls);
	m_pGooseInWidget->ShowDatas(pGsInCtrls);

	m_pSclFileIedCtrls_TabWidget->setTabEnabled(0,pGsOutCtrls->GetCount()>0);
	m_pSclFileIedCtrls_TabWidget->setTabEnabled(1,pSmvOutCtrls->GetCount()>0);
	m_pSclFileIedCtrls_TabWidget->setTabEnabled(2,pGsInCtrls->GetCount()>0);
	m_pSclFileIedCtrls_TabWidget->setTabEnabled(3,pSmvInCtrls->GetCount()>0);

// #ifdef USE_STT_SCLIED_VIEW
// 	//lichao 添加图形界面
// 	m_pIedViewWidget->ShowIED(pSclIed);
// #endif

    if (m_pSttSclSkectMapWidget)
	{
	    m_pSttSclSkectMapWidget->ShowIED(pSclIed);//chenling20231229
	}
}


// void QSttSclFileParseDialog::slot_UpdateCurrentChsGrid()
// {
// 	if(m_pSclFileIedCtrls_TabWidget->currentIndex() == 3)
// 	{
// 		m_pSmvInChWidget->show();
// 	}
// }

void QSttSclFileParseDialog::slot_TreeItemClicked(QTreeWidgetItem * pItem, int nColumn )
{
 	if(pItem == NULL) 
 		return;

	QSttSclIedTreeItem *pSclIedTreeItem = (QSttSclIedTreeItem*)pItem; 
	m_pCurrSelSclIed = (CSclIed*)pSclIedTreeItem->GetTreeItemObject();
	ShowSclIedDetail(m_pCurrSelSclIed);
// #ifdef USE_STT_SCLIED_VIEW
// 	//lichao 调整画布区域
// 	m_pIedViewWidget->resizeEvent(NULL);
// #endif
}

void QSttSclFileParseDialog::slot_OneKeyCfgBtnClicked()
{
	if (m_pCurrSelSclIed == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_emptyIed.GetString());
		return;
	}

	CSclCtrlsSmvOut *pSmvOutCtrls = m_pCurrSelSclIed->GetSmvOuts();
	CSclCtrlsSmvIn *pSmvInCtrls = m_pCurrSelSclIed->GetSmvIns();
	CSclCtrlsGsIn *pGsInCtrls = m_pCurrSelSclIed->GetGsIns();
	CSclCtrlsGsOut *pGsOutCtrls = m_pCurrSelSclIed->GetGsOuts();
	BOOL bIsAllSelected = FALSE;

	if (m_pCurrSelSclIed->IsAllCtrlsSelected())
	{
		bIsAllSelected = TRUE;
	}

	if (pSmvOutCtrls != NULL)
	{
		pSmvOutCtrls->SetSelectAll(!bIsAllSelected);
		pSmvOutCtrls->SetAllItemData(0);//用于测试仪订阅
		AddGridCtrls(pSmvOutCtrls);
	}

	if (pSmvInCtrls != NULL)
	{
		pSmvInCtrls->SetSelectAll(!bIsAllSelected);
		pSmvInCtrls->SetAllItemData(1);//用于测试仪发布
		AddGridCtrls(pSmvInCtrls);


	}

	if (pGsInCtrls != NULL)
	{
		pGsInCtrls->SetSelectAll(!bIsAllSelected);
		pGsInCtrls->SetAllItemData(1);//用于测试仪Goose发布
		AddGridCtrls(pGsInCtrls);
	}

	if (pGsOutCtrls != NULL)
	{
		pGsOutCtrls->SetSelectAll(!bIsAllSelected);
		pGsOutCtrls->SetAllItemData(0);//用于测试仪Goose订阅
		AddGridCtrls(pGsOutCtrls);
	}

	m_pSmvOutWidget->UpdateSelectedState();
	m_pSmvInWidget->UpdateSelectedState();
	m_pGooseOutWidget->UpdateSelectedState();
	m_pGooseInWidget->UpdateSelectedState();

	//2023/10/20 wjs 一键配置后也要更新左下角表格
	m_pSclSelectCtrlsGrid->ShowDatas(&m_oSelectedSclCtrlsRef);

	CString strText = m_pOneKeyCfg_PushButton->text();

	if (strText == g_sLangTxt_IEC_Configure)
	{
		strText = g_sLangTxt_Cancel/*g_sLangTxt_Native_Cancel*/;
		strText += g_sLangTxt_IEC_Configure;
		m_pOneKeyCfg_PushButton->setText(strText);
	}
	else
	{
		m_pOneKeyCfg_PushButton->setText(g_sLangTxt_IEC_Configure);
	}

}

void QSttSclFileParseDialog::slot_SCLSelectBtnClicked()
{
	QSttSelSclFileDlg oSttSelSclFileDlg(this);
	oSttSelSclFileDlg.InitUI();
	oSttSelSclFileDlg.exec();
	CString strCurrTscdFilePath;
	strCurrTscdFilePath = g_oXSclFileMngr.GetCurrSelTscdFilePah();

	if (!IsFileExist(strCurrTscdFilePath))
	{
		CString strMsg;
		strMsg = /*_T("解析文件(")*/g_sLangTxt_Gradient_ParseLFile; //lcq
		strMsg += strCurrTscdFilePath;
		strMsg += /*_T(")不存在,无法进行SCL选择切换.")*/g_sLangTxt_Gradient_SCLNoSel; //lcq
		CXMessageBox::information(this,g_sLangTxt_Message,strMsg);
		return;
	}

	m_pSclStation->OpenSclStationFile(strCurrTscdFilePath);
	//--------------
	InitIedInforDatas();
	//---------------
	UpdateIedTreeBySearchText("");
	
// #ifdef USE_STT_SCLIED_VIEW
// 	//lichao 调整画布区域
// 	m_pIedViewWidget->resizeEvent(NULL);
// #endif
}

void QSttSclFileParseDialog::slot_ImportIecCfgBtnClicked()
{
	if (m_pIecCfgDatasMngr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_emptyIEC.GetString());
		return;
	}

	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(m_pSclStation);
	CExBaseList oRepeatListRef;
	BOOL bHasRepeatCtrls = oSclToIecCfgTool.HasRepeatCtrls(&m_oSelectedSclCtrlsRef,m_pIecCfgDatasMngr,oRepeatListRef,FALSE);//最后一个参数标识订阅发布不合并处理,即分开处理

	if (bHasRepeatCtrls)
	{
		CString strMsg, strTitle;
		GetRepeatSclCtrlsLogString(oRepeatListRef,strMsg,FALSE);

		strTitle = /*_T("提示")*/g_sLangTxt_Message;
		int nRet = CXMessageBox::question(this, strTitle, strMsg.GetString(), QMessageBox::Yes,QMessageBox::No);

		if (nRet == QMessageBox::Yes)
		{
			oSclToIecCfgTool.DeleteAllRepeatCtrls(m_pIecCfgDatasMngr,oRepeatListRef,FALSE);
		}
	}

	oRepeatListRef.RemoveAll();
	oSclToIecCfgTool.AddToIecCfg_Mix(&m_oSelectedSclCtrlsRef, m_pIecCfgDatasMngr,FALSE);
	m_oSelectedSclCtrlsRef.SetSelectAll(FALSE);
	emit sig_IecCfgDataMngrUpdate();
	close();
}

void QSttSclFileParseDialog::slot_CancelBtnClicked()
{
	close();
}

bool QSttSclFileParseDialog::eventFilter(QObject *obj, QEvent *event)
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

void QSttSclFileParseDialog::AddGridCtrls(CSclCtrls *pSclCtrls)
{
	CSclCtrlBase *pObj = NULL;
	POS pos = pSclCtrls->GetHeadPosition();
	CString strTmp;

	while(pos)
	{
		pObj = (CSclCtrlBase*)pSclCtrls->GetNext(pos);

		if (m_oSelectedSclCtrlsRef.Find(pObj) == NULL)
		{
			m_oSelectedSclCtrlsRef.AddTail(pObj);
		} 
		else if (pObj->m_nSelect == 1)
		{
			strTmp.Format(_T("0x%04X"),pObj->GetAppID());
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_addedblock.GetString(),strTmp.GetString());
		}
		else if (pObj->m_nSelect == 0)
		{
			m_oSelectedSclCtrlsRef.Remove(pObj);
		}
	}
}

void QSttSclFileParseDialog::slot_IedSearchtextChanged(/*const QString &text*/)
{
	CString strSearchIedText = m_pIedSearch_LineEdit->text();

	if (m_strSearchText != strSearchIedText)
	{
		m_strSearchText = strSearchIedText;
		UpdateIedTreeBySearchText(strSearchIedText);
	}
}

void QSttSclFileParseDialog::slot_IedSearchtextclicked(/*const QString &text*/)
{
	QString strValue = m_pIedSearch_LineEdit->text();
	GetEngWidgetBoard_DigitData(strValue, this);
	m_pIedSearch_LineEdit->setText(strValue);

	/*
	CString strSearchIedText = m_pIedSearch_LineEdit->text();

	WidgetKeyboard dlg(this);
	dlg.m_InputString = strSearchIedText;
	dlg.showToEdit();
	if (dlg.exec() == QDialog::Accepted)
	{
		m_pIedSearch_LineEdit->setText(dlg.m_InputString);
	}
	*/

	m_pIedSearch_LineEdit->SetEditFinished();
	
}

void QSttSclFileParseDialog::slot_UpdateSelectCtrlsGrid()
{
	m_pSclSelectCtrlsGrid->ShowDatas(&m_oSelectedSclCtrlsRef);
}

void QSttSclFileParseDialog::slot_UpdateSketchMapWidgetSize(int pos, int index)
{
	// 获取分隔条的位置
	Q_UNUSED(pos);//未使用参数pos防止编译器警告
	qreal totalSize = m_pSclFileIED_Splitter->sizes().at(0) + m_pSclFileIED_Splitter->sizes().at(1);
	qreal scale = (qreal)m_pSclFileIED_Splitter->sizes().at(1) / totalSize;
	
	qreal scaleFactor = 1.5; //缩放因子调整比例
	scale *= scaleFactor;

   if (m_pSttSclSkectMapWidget)
   {
	   m_pSttSclSkectMapWidget->UpdateViewScale(scale);
   }
}
