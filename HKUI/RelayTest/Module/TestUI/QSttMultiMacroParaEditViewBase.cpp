#include "QSttMultiMacroParaEditViewBase.h"
#include "../SttGlobalDef.h"
#include "../SttTestCtrl/SttTestAppBase.h"
#include "../UI/SttTestCntrFrameBase.h"
#include "../UI/SttTestCntrFrameApi.h"
#include "./SttMultiMacroParasDefine.h"
#include "../HtmlReport/SttXHtmlRptGenFactoryBase.h"

#include <QDesktopWidget>
#include <QApplication>

BOOL Global_HasMacroItemModified(CSttItems *pParentItems)
{
	if (pParentItems == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pCurrObj = NULL;
	POS pos = pParentItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pParentItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			if (Global_HasMacroItemModified((CSttItems*)pCurrObj))
			{
				return TRUE;
			}
		} 
		else if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			if (((CSttMacroTest*)pCurrObj)->m_nModified)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void Global_GetAllMacroTest(CExBaseList *pSingleMacroItemsRef,CSttItems *pMulitMacroRootItems,CTestMacro *pSingleMacroRef)
{
	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest* pMacroTest = NULL;
	CSttMacroTestParaDatas *pSttMacroTestParaDatas = NULL;
	CString strTmp;

	//2024-10-16 wuxinyi 该提示与InitData中重复，故注释
// 	if (pMulitMacroRootItems->GetCount() <= 0)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("请添加测试项！"));//在初始化没有测试项时提示；
// 	}

	POS pos = pMulitMacroRootItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pMulitMacroRootItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pMacroTest = (CSttMacroTest*)pCurrObj;
			strTmp = pMacroTest->GetTestMacroID();

			if (strTmp == pSingleMacroRef->m_strID)
			{
				pSttMacroTestParaDatas = pMacroTest->GetSttMacroTestParaDatas(TRUE,pSingleMacroRef->m_strID);
				Global_CreateAllParaDatas(pSttMacroTestParaDatas, pSingleMacroRef);
				pSingleMacroItemsRef->AddTail(pCurrObj);
			}
		} 
		//2024.7.24 zhangyq 电流反时限节点为macro-char-items
		else if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS || pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			Global_GetAllMacroTest(pSingleMacroItemsRef,(CSttItems*)pCurrObj,pSingleMacroRef);
		}
	}
};

QSttMultiMacroParaEditViewBase::QSttMultiMacroParaEditViewBase(const CString &strGridFile,QWidget *parent)
	: CSttMacroParaEditViewOriginal(parent)
{
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase : 1"));

//	m_pAddMultItems_Paras = NULL;
	m_pCharactInterface = NULL;
	m_pAddMultiItemSelectDlg = NULL;
	m_bCharTestObjectHasChanged = FALSE;
	CString strPath;
	strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += strGridFile;
	m_pSingleMacroRef = NULL;
	m_pCurrMacroItemsRef = &m_oSingleMacroItemsRef;

	if (m_oSttTestGridDefine.OpenXmlFile(strPath,CSttTestGridDefineXmlRWKeys::g_pXmlKeys))
	{
		m_oSttTestGridDefine.InitGridInsts();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("打开测试功能表格配置文件(%s)失败."),strPath.GetString());
	}
	
	m_pSingleItemEditTab = NULL;
	m_pSingleItemParaEditWidget = NULL;
	m_pGoosePubsWidget = NULL;
	m_pCurrMacroParaEditGrid = NULL;
	m_pMultiMacroGridTab = NULL;
	m_pAddOneItemBtn = NULL;
	m_pAddMultiItemBtn = NULL;
	m_pCommonParasBtn = NULL;
	m_pBinarysBtn = NULL;
	m_pDeleteItemBtn = NULL;
	m_pClearResultBtn = NULL;
	m_pMulitMacroRootItems = NULL;
	m_pMainVboxLayout = NULL;
	m_pBottomHboxLayout = NULL;

	for (int i = 0;i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM;i++)
	{
		m_pMultiMacroParaEditGrid[i] = NULL;
		m_pMultiMacroRef[i] = NULL;
		m_pMultiItemParaEditWidget[i] = NULL;
	}

    m_menuTest = NULL;
    m_actSelectAll = NULL;
    m_actDeselectAll = NULL;
    m_actAddOneItem = NULL;
    m_actAddMultiItem = NULL;
    m_actDeleteSelItem = NULL;
    m_actDeleteAllItem = NULL;
    m_actClearResult = NULL;
    m_actClearAllResult = NULL;

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase : 2"));

    m_menuTest = new QMenu(this);
    InitTestMenu();
}

QSttMultiMacroParaEditViewBase::~QSttMultiMacroParaEditViewBase()
{
// 	if (m_pAddMultItems_Paras != NULL)
// 	{
// 		delete m_pAddMultItems_Paras;
// 		m_pAddMultItems_Paras = NULL;
// 	}

	m_oSingleMacroItemsRef.RemoveAll();
	for (int i = 0;i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM;i++)
	{
		m_oMultiMacroItemsRef[i].RemoveAll();
	}
}


//创建单功能多点界面
void QSttMultiMacroParaEditViewBase::InitUI_OneMacro()
{
	setFont(*g_pSttGlobalFont);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 1"));

	CString strText;
	m_pSingleItemEditTab = new QTabWidget();

	m_pCurrMacroParaEditGrid = new QSttMacroParaEditGrid(this);
	m_pCurrMacroParaEditGrid->m_pCharacteristics_Items = g_theTestCntrFrame->m_pCharacteristics;
	m_pCurrMacroParaEditGrid->AttachDataViewOptrInterface(this);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 2"));

	m_pBottomHboxLayout = new QHBoxLayout();
	strText = g_sLangTxt_Gradient_CommonParas/*"通用参数"*/;
	m_pCommonParasBtn = new QPushButton(strText);
	strText = g_sLangTxt_Native_SwitchVal /*"开关量"*/;
	m_pBinarysBtn = new QPushButton(strText);
	strText =  g_sLangTxt_Distance_DeleteItem/*"删除测试项"*/;
	m_pDeleteItemBtn = new QPushButton(strText);
	strText = g_sLangTxt_Distance_ClearResult/*"清除测试结果"*/;
	m_pClearResultBtn = new QPushButton(strText);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 3"));

	m_pBottomHboxLayout->addWidget(m_pCommonParasBtn);
	m_pBottomHboxLayout->addWidget(m_pBinarysBtn);
	m_pBottomHboxLayout->addWidget(m_pDeleteItemBtn);
	m_pBottomHboxLayout->addWidget(m_pClearResultBtn);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 4"));

	m_pMainVboxLayout = new QVBoxLayout();

    // 2024-7-19 wuxinyi 中间可拖动，创建 QSplitter
    QSplitter *pSplitter = new QSplitter(Qt::Vertical, this);
    pSplitter->addWidget(m_pSingleItemEditTab);
    pSplitter->addWidget(m_pCurrMacroParaEditGrid);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 5"));

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->screenGeometry();
    int nHeight = rect.height()/2;

    QList<int> HeightList;
    int nHeight1 = nHeight-15;
    int nHeight2 = nHeight+15;

    HeightList << nHeight1 << nHeight2;
    pSplitter->setSizes(HeightList);

    m_pMainVboxLayout->addWidget(pSplitter);
	m_pMainVboxLayout->addLayout(m_pBottomHboxLayout);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 6"));


	setLayout(m_pMainVboxLayout);

	stt_Frame_InitVectorWidget(NULL, NULL);
	stt_Frame_InitPowerWidget(NULL, NULL);
	stt_Frame_InitStateMonitor();
	stt_Frame_ClearInfoWidget();

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 7"));
}

//创建多功能多点界面
void QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(QStringList strTabTitleList)
{

	setFont(*g_pSttGlobalFont);

	CString strText;
	m_pMultiMacroGridTab = new QTabWidget();
	m_pSingleItemEditTab = new QTabWidget();

	m_pBottomHboxLayout = new QHBoxLayout();
    strText = g_sLangTxt_Gradient_CommonParas/*通用参数*/;
	m_pCommonParasBtn = new QPushButton(strText);
    strText = g_sLangTxt_Native_SwitchVal/*"开关量"*/;
	m_pBinarysBtn = new QPushButton(strText);
    strText = g_sLangTxt_Distance_DeleteItem/*"删除测试项"*/;
	m_pDeleteItemBtn = new QPushButton(strText);
    strText = g_sLangTxt_Distance_ClearResult/*"清除测试结果"*/;
	m_pClearResultBtn = new QPushButton(strText);

	m_pBottomHboxLayout->addWidget(m_pCommonParasBtn);
	m_pBottomHboxLayout->addWidget(m_pBinarysBtn);
	m_pBottomHboxLayout->addWidget(m_pDeleteItemBtn);
	m_pBottomHboxLayout->addWidget(m_pClearResultBtn);

	m_pMainVboxLayout = new QVBoxLayout();

	
	for (int i = 0; i < strTabTitleList.size(); ++i) 
	{
		QString tabTitle = strTabTitleList[i];
		m_pMultiMacroParaEditGrid[i] = new QSttMacroParaEditGrid(this); 
		m_pMultiMacroParaEditGrid[i]->m_pCharacteristics_Items = g_theTestCntrFrame->m_pCharacteristics;
		m_pMultiMacroParaEditGrid[i]->AttachDataViewOptrInterface(this);
		m_pMultiMacroGridTab->addTab(m_pMultiMacroParaEditGrid[i], tabTitle);
	}
    // 2024-7-19 wuxinyi 中间可拖动，创建 QSplitter
    QSplitter *pSplitter = new QSplitter(Qt::Vertical, this);

	m_pMultiMacroGridTab->setTabPosition(QTabWidget::South);
//	m_pMainVboxLayout->addWidget(m_pSingleItemEditTab);
//	m_pMainVboxLayout->addWidget(m_pMultiMacroGridTab);
//	m_pMainVboxLayout->addLayout(m_pBottomHboxLayout);

    pSplitter->addWidget(m_pSingleItemEditTab);
    pSplitter->addWidget(m_pMultiMacroGridTab);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->screenGeometry();
    int nHeight = rect.height()/2;

    QList<int> HeightList;
    int nHeight1 = nHeight-15;
    int nHeight2 = nHeight+15;

    HeightList << nHeight1 << nHeight2;
    pSplitter->setSizes(HeightList);

    m_pMainVboxLayout->addWidget(pSplitter);
	m_pMainVboxLayout->addLayout(m_pBottomHboxLayout);

	setLayout(m_pMainVboxLayout);

	m_pCurrMacroParaEditGrid = m_pMultiMacroParaEditGrid[0];

	stt_Frame_InitVectorWidget(NULL, NULL);
	stt_Frame_InitPowerWidget(NULL, NULL);
	stt_Frame_InitStateMonitor();
	stt_Frame_ClearInfoWidget();
}

void QSttMultiMacroParaEditViewBase::InitDatas(CSttItems *pCurrRootItems)
{
	m_pMulitMacroRootItems = pCurrRootItems;
	m_oSingleMacroItemsRef.RemoveAll();

	if (m_pCurrMacroParaEditGrid != NULL)
	{
		m_pCurrMacroParaEditGrid->InitGrid();

		if (m_pMulitMacroRootItems == NULL)
		{
			m_pCurrMacroParaEditGrid->ShowDatas(NULL);
		}

		UpdateBottomBtnsEnable();
	}

	//单功能多点
	if (m_pMulitMacroRootItems != NULL)
	{
		Global_GetAllMacroTest(&m_oSingleMacroItemsRef,m_pMulitMacroRootItems,m_pSingleMacroRef);
	}
	else
	{
		if (m_pSingleItemParaEditWidget != NULL)
		{
			m_pSingleItemParaEditWidget->m_pCurrMacroTest_External = NULL;
		}
	}

	//2024-10-16 wuxinyi 新增多功能多点表格刷新
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++)
	{
		if (m_pMultiMacroParaEditGrid[i] == NULL)
		{
			break;
		}
		m_oMultiMacroItemsRef[i].RemoveAll();
		Global_GetAllMacroTest(&m_oMultiMacroItemsRef[i], m_pMulitMacroRootItems, m_pMultiMacroRef[i]);
		m_pMultiMacroParaEditGrid[i]->ShowDatas(&m_oMultiMacroItemsRef[i]);

		//先移除再安装过滤器，避免重复安装
		m_pMultiMacroParaEditGrid[i]->viewport()->removeEventFilter(this);
		m_pMultiMacroParaEditGrid[i]->viewport()->installEventFilter(this);
	}


	//2024-10-16 wuxinyi 新增刷新测试项
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject *pData = (CExBaseObject *)m_pCurrMacroItemsRef->GetNext(pos);
		if (pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
		{
			continue;
		}
		CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pData;
		UpdateCharacteristicParas(pSttMacroTest);
		SetMacroTestNameByParas(pSttMacroTest);

	}

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	m_pCurrMacroParaEditGrid->viewport()->removeEventFilter(this);
    m_pCurrMacroParaEditGrid->viewport()->installEventFilter(this);  //20240813 wanmj

//	DisConnectAll_SigSlot();
}

//20240910 wanmj 表格鼠标右键点击新增快捷功能
void QSttMultiMacroParaEditViewBase::InitTestMenu()
{
    if(m_menuTest == NULL)
        return;
    if(!m_menuTest->isEmpty())
        return;

    m_actSelectAll = new QAction(g_sLangTxt_SelAll, this);
    m_menuTest->addAction(m_actSelectAll);
    connect(m_actSelectAll, SIGNAL(triggered()), this, SLOT(slot_SelectAllItems()));

    m_actDeselectAll = new QAction(g_sLangTxt_SelNone, this);
    m_menuTest->addAction(m_actDeselectAll);
    connect(m_actDeselectAll, SIGNAL(triggered()), this, SLOT(slot_DeselectAllItems()));

    m_actAddOneItem = new QAction(g_sLangTxt_Action_AddOneItem, this);
    m_menuTest->addAction(m_actAddOneItem);
    connect(m_actAddOneItem, SIGNAL(triggered()), this, SLOT(slot_AddOneItemBtnClick()));

    m_actAddMultiItem = new QAction(g_sLangTxt_Button_AddMultiItem, this);
    m_menuTest->addAction(m_actAddMultiItem);
    connect(m_actAddMultiItem, SIGNAL(triggered()), this, SLOT(slot_AddMultiItemBtnClick()));

    m_actDeleteSelItem = new QAction(g_sLangTxt_Action_DeleteSelItem, this);
    m_menuTest->addAction(m_actDeleteSelItem);
    connect(m_actDeleteSelItem, SIGNAL(triggered()), this, SLOT(slot_DeleteSelItemBtnClick()));

    m_actDeleteAllItem = new QAction(g_sLangTxt_Action_DeleteAllItem, this);
    m_menuTest->addAction(m_actDeleteAllItem);
    connect(m_actDeleteAllItem, SIGNAL(triggered()), this, SLOT(slot_DeleteAllItemBtnClick()));

    m_actClearResult = new QAction(g_sLangTxt_Action_ClearSelResult, this);
    m_menuTest->addAction(m_actClearResult);
    connect(m_actClearResult, SIGNAL(triggered()), this, SLOT(slot_ClearSelResultBtnClick()));

    m_actClearAllResult = new QAction(g_sLangTxt_Action_ClearAllResult, this);
    m_menuTest->addAction(m_actClearAllResult);
    connect(m_actClearAllResult, SIGNAL(triggered()), this, SLOT(slot_ClearAllResultBtnClick()));

}

void QSttMultiMacroParaEditViewBase::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
//	return;

	if (m_pSingleItemParaEditWidget == NULL)
	{
		return;
	}

	//CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
	//20240627 luozibing 如果选择的单元格为空，切换行失败
	CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetData(nRow,0);
	if (pCurrObj == NULL)
	{
		return;
	}

	CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);

// 	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External != NULL)
// 	{
// //		CSttItemBase *pParentItems = (CSttItemBase*)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetParent();
// 		CDataGroup *pMacroParas = GetUpdateOneItem_DataGroup(m_pSingleItemParaEditWidget->m_pCurrMacroTest_External);
// 		CString strItemPath;
// 		strItemPath = m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// 
// 		long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateOneMacroItem(pMacroParas,m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->m_nSelect,
// 			strItemPath, m_pSingleMacroRef->m_strID);
// 
// 
// 		if (nRet!= STT_CMD_ExecStatus_SUCCESS)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("更新单个电气量测试功能执行命令失败(%ld)."),nRet);
// 			return;
// 		}
// 	}
	////更新当前选择项时间定值等参数
	//UpdateCharacteristicParas(pSttMacroTest);

	m_pSingleItemParaEditWidget->UpdateParas(pSttMacroTest);

	//2024-10-14 wuxinyi 先判断m_pCharactInterface
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}

	if (m_pCharactInterface)
	{
	//当前选择项改变，更新当前选择测试点
	AddUpdateTestPoint_To_Charact(pSttMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
		UpdateTestUI_To_Charact(pSttMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	}

	if (m_pZTViewInterface == NULL)
	{
		m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
	}
	if (m_pZTViewInterface)
	{
	UpdateTestPoint_To_ZTView(pSttMacroTest, true);
	UpdateParas_To_ZTView();//20240925 luozibing 设置故障类型后更新Z/T视图折线图
	}

}

void QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot()
{
	connect(m_pCommonParasBtn, SIGNAL(clicked()), this, SLOT(slot_CommonParasBtnClick()), Qt::UniqueConnection);
	connect(m_pBinarysBtn, SIGNAL(clicked()), this, SLOT(slot_BinarysBtnClick()), Qt::UniqueConnection);
	connect(m_pDeleteItemBtn, SIGNAL(clicked()), this, SLOT(slot_DeleteItemBtnClick()), Qt::UniqueConnection);
	connect(m_pClearResultBtn, SIGNAL(clicked()), this, SLOT(slot_ClearResultBtnClick()), Qt::UniqueConnection);
}

void QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot()
{
	disconnect(m_pCommonParasBtn,SIGNAL(clicked()),this,SLOT(slot_CommonParasBtnClick()));
	disconnect(m_pBinarysBtn,SIGNAL(clicked()),this,SLOT(slot_BinarysBtnClick()));
	disconnect(m_pDeleteItemBtn,SIGNAL(clicked()),this,SLOT(slot_DeleteItemBtnClick()));
	disconnect(m_pClearResultBtn,SIGNAL(clicked()),this,SLOT(slot_ClearResultBtnClick()));
}

CSttItems* QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return m_pMulitMacroRootItems;
}

void QSttMultiMacroParaEditViewBase::OnViewTestStart()
{
	if (m_pCurrMacroParaEditGrid)
	{
		m_pCurrMacroParaEditGrid->setDisabled(true);
	}
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++) //add wangtao20240801 多功能模块，开始测试时，让每个功能界面都不使能，停止测试同理
	{
		if (m_pMultiMacroParaEditGrid[i])
		{
			m_pMultiMacroParaEditGrid[i]->setDisabled(true);
		}
	}

	if (m_pSingleItemParaEditWidget != NULL)
	{
		m_pSingleItemParaEditWidget->setDisabled(true);
	}
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++)
	{
		if (m_pMultiItemParaEditWidget[i])
		{
			m_pMultiItemParaEditWidget[i]->setDisabled(true);
		}
	}

	if (m_pAddMultiItemBtn != NULL)
	{
		m_pAddMultiItemBtn->setDisabled(true);
	}

	//202408122 zhangyq 开始试验后表格下方的按钮不可编辑
	m_pAddOneItemBtn->setDisabled(true);
	//m_pAddMultiItemBtn->setDisabled(true);
	m_pCommonParasBtn->setDisabled(true);
	m_pBinarysBtn->setDisabled(true);
	m_pDeleteItemBtn->setDisabled(true);
	m_pClearResultBtn->setDisabled(true);

	if (m_pGoosePubsWidget != NULL)
	{
		m_pGoosePubsWidget->SetRunState(STT_UI_RUN_STATE_StateTested_NotEditable);
	}

	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	stt_Frame_ClearInfoWidget();
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();
}

void QSttMultiMacroParaEditViewBase::OnViewTestStop()
{
	if (m_pCurrMacroParaEditGrid)
	{
		m_pCurrMacroParaEditGrid->setDisabled(false);
	}
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++)
	{
		if (m_pMultiMacroParaEditGrid[i])
		{
			m_pMultiMacroParaEditGrid[i]->setDisabled(false);
		}
	}

	if (m_pSingleItemParaEditWidget != NULL)
	{
		m_pSingleItemParaEditWidget->setDisabled(false);
	}
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++)
	{
		if (m_pMultiItemParaEditWidget[i])
		{
			m_pMultiItemParaEditWidget[i]->setDisabled(false);
		}
	}


	if (m_pAddMultiItemBtn != NULL)
	{
		m_pAddMultiItemBtn->setDisabled(false);
	}

	m_pAddOneItemBtn->setDisabled(false);
	//m_pAddMultiItemBtn->setDisabled(false);
	m_pCommonParasBtn->setDisabled(false);
	m_pBinarysBtn->setDisabled(false);
	m_pDeleteItemBtn->setDisabled(false);
	m_pClearResultBtn->setDisabled(false);

	if (m_pGoosePubsWidget != NULL)
	{
		m_pGoosePubsWidget->SetRunState(STT_UI_RUN_STATE_Stoped);
	}

	g_theTestCntrFrame->OnViewTestStop_Common();
}

void QSttMultiMacroParaEditViewBase::SyncCurrMacroItemParaEditWidget(CSttItemBase *pSttItem)
{

}

BOOL QSttMultiMacroParaEditViewBase::ItemStateChanged(CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}

	if (pSttItem->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return FALSE;
	}

	if (!m_pMulitMacroRootItems->IsChildItemExist(pSttItem))
	{
		return FALSE;
	}

	//多功能多点使用,用于切换当前tab显示界面
	SyncCurrMacroItemParaEditWidget(pSttItem);

	if (m_pCurrMacroItemsRef->Find(pSttItem) != NULL)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("测试状态改变[%s][%ld]"),pSttItem->m_strID.GetString(),pSttItem->m_nState);
		m_pSingleItemParaEditWidget->UpdateParas((CSttMacroTest*)pSttItem);
		m_pCurrMacroParaEditGrid->UpdateData(pSttItem);
		m_pCurrMacroParaEditGrid->SelectRow(pSttItem);//zhouhj 2024.9.2 设置选择行

		if (IsManualTriggerMode_MacroTestItem((CSttMacroTest*)pSttItem))
		{
			//手动触发按钮变亮
			g_theTestCntrFrame->EnableManualTriggerButton(true);
		}

		return TRUE;
	}

	return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::GetMacroIDAndFaultType(CSttItemBase *pSttItem, CString &strMacroID, long &nFaultType)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}

	if (pSttItem->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return FALSE;
	}

	CSttMacroTest *pSttMacroID = (CSttMacroTest*)pSttItem;
	strMacroID = pSttMacroID->GetTestMacroID();
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewBase::ShowRslt(CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}

	if (pSttItem->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	{
		return FALSE;
	}

	if (!m_pMulitMacroRootItems->IsChildItemExist(pSttItem))
	{
		return FALSE;
	}

	//多功能多点使用,用于切换当前tab显示界面
	SyncCurrMacroItemParaEditWidget(pSttItem);

	if (m_pCurrMacroItemsRef->Find(pSttItem) != NULL)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pSttItem;
		pSttMacroTest->UpdateItemState_ByLastRptRsltJdg();
		m_pCurrMacroParaEditGrid->UpdateData(pSttItem);
	}

	return TRUE;
}

void QSttMultiMacroParaEditViewBase::Update_MultiMacroParaEditView()
{
	m_pCurrMacroItemsRef->RemoveAll();
	Global_GetAllMacroTest(m_pCurrMacroItemsRef,m_pMulitMacroRootItems,m_pSingleMacroRef);
//	m_oSingleMacroItemsRef.AddTail(pNewTest);
	POS pos  = m_pCurrMacroItemsRef->GetHeadPosition();
	while(pos != NULL)
	{
		CExBaseObject *pData = (CExBaseObject *)m_pCurrMacroItemsRef->GetNext(pos);
		if (pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
		{
			continue;
		}
		CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pData;
		UpdateCharacteristicParas(pSttMacroTest);//20240813 luozibing 添加 添加系列生成的测试项时关联时间定值等参数
		SetMacroTestNameByParas(pSttMacroTest);//20240920 luozibing 根据参数设置测试项Name
		AddUpdateTestPoint_To_Charact(pSttMacroTest);
		//UpdateTestUI_To_Charact(pSttMacroTest);
		UpdateTestPoint_To_ZTView(pSttMacroTest);
		UpdateTestUI_To_Charact(pSttMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	}
	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());
	//CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetData(m_pCurrMacroItemsRef->GetCount(),0);
	//if (pCurrObj != NULL)
	//{
	//	CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pCurrObj;
	//	UpdateTestPoint_To_Charact(pSttMacroTest,XDRAW_TEST_STATE_SELECT);
	//	UpdateTestUI_To_Charact(pSttMacroTest, XDRAW_TEST_STATE_SELECT);
	//	UpdateTestPoint_To_ZTView(pSttMacroTest,true);
	//}
	UpdateBottomBtnsEnable();//20240902 luozibing添加系列后更新按键使能
}

BOOL QSttMultiMacroParaEditViewBase::IsManualTriggerMode_MacroTestItem(CSttMacroTest* pMacroTest)
{
	return FALSE;
}

//添加测试项时,在特性曲线界面添加对应测试点
//BOOL QSttMultiMacroParaEditViewBase::AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
//{
//	return FALSE;
//}

BOOL QSttMultiMacroParaEditViewBase::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
	return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::AddUpdateTestPoint_To_Charact()
{
	if (m_pCurrMacroItemsRef == NULL)
	{
		return FALSE;
	}

	CCharacteristics *pCharacteristics = g_theTestCntrFrame->m_pCharacteristics;
	pCharacteristics->ClearTestData();
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();

	while (pos != NULL)
	{
		CSttMacroTest* pMacroTestTemp = (CSttMacroTest*)m_pCurrMacroItemsRef->GetNext(pos);
		AddUpdateTestPoint_To_Charact(pMacroTestTemp);
	}
}

BOOL QSttMultiMacroParaEditViewBase::UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::AddItem_From_Charact(double dX, double dY)
{
	return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::AddItem_From_Charact(double dBegX, double dBegY, double dEndX, double dEndY)
{
    return FALSE;
}

BOOL QSttMultiMacroParaEditViewBase::UpdateCurrItem_From_Charact(double dX, double dY)
{
	return FALSE;
}

CDataGroup* QSttMultiMacroParaEditViewBase::GetAddOneItem_DataGroup(CSttMacroTest *pSttMacroTest)
{
	CDataGroup *pMacroParasGroup = new CDataGroup;
	pMacroParasGroup->m_strID = STT_CMD_PARA_TestMacroParas;
	CSttMacroTestParaDatas *pSttTestParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pSttMacroTestParaData = NULL;
	CShortData *pShortData = NULL;
	CShortDatas *pShortDatas = m_pSingleMacroRef->GetFaultParas();
	POS pos = pShortDatas->GetHeadPosition();

	while(pos)
	{
		pShortData = (CShortData *)pShortDatas->GetNext(pos);
		//zhouhj 2024.10.9 修改为发送全量数据的方式
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)//如果当前链表中没有,则添加缺省内容
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pShortData->m_strID, pShortData->m_strDataTypeID, pShortData->m_strValue);
		}
		else//否则以当前链表为准
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pSttMacroTestParaData->m_strID, pShortData->m_strDataTypeID, pSttMacroTestParaData->m_strValue);
		}

		//pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		//if (pSttMacroTestParaData == NULL)
		//{
		//	continue;
		//}

		//if (pSttMacroTestParaData->m_strValue != pShortData->m_strValue)
		//{
		//	//20240717 luozibing 修改传递参数
		//	pMacroParasGroup->AddNewData(pShortData->m_strName,pSttMacroTestParaData->m_strID,pShortData->m_strDataTypeID,pSttMacroTestParaData->m_strValue);
		//}
	}

	pShortDatas = m_pSingleMacroRef->GetSysParas();
	pos = pShortDatas->GetHeadPosition();

	while(pos)
	{
		pShortData = (CShortData *)pShortDatas->GetNext(pos);
		//zhouhj 2024.10.9 修改为发送全量数据的方式
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)//如果当前链表中没有,则添加缺省内容
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pShortData->m_strID, pShortData->m_strDataTypeID, pShortData->m_strValue);
		}
		else//否则以当前链表为准
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pSttMacroTestParaData->m_strID, pShortData->m_strDataTypeID, pSttMacroTestParaData->m_strValue);
		}
// 
// 		if (pSttMacroTestParaData == NULL)
// 		{
// 			continue;
// 		}
// 
// 		if (pSttMacroTestParaData->m_strValue != pShortData->m_strValue)
// 		{
// 			//pMacroParasGroup->AddNewData(pSttMacroTestParaData->m_strID,pSttMacroTestParaData->m_strValue);
// 			pMacroParasGroup->AddNewData(pShortData->m_strName,pSttMacroTestParaData->m_strID,pShortData->m_strDataTypeID,pSttMacroTestParaData->m_strValue);
// 		}
	}

	return pMacroParasGroup;
}

// CDataGroup* QSttMultiMacroParaEditViewBase::GetUpdateOneItem_DataGroup(CSttMacroTest *pSttMacroTest)
// {
// 	CDataGroup *pMacroParasGroup = new CDataGroup;
// 	pMacroParasGroup->m_strID = STT_CMD_PARA_TestMacroParas;
// 	CSttMacroTestParaDatas *pSttTestParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
// 	CSttMacroTestParaData *pSttMacroTestParaData = NULL;
// 	POS pos = pSttTestParaDatas->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->GetNext(pos);
// 		pMacroParasGroup->AddNewData(pSttMacroTestParaData->m_strID,pSttMacroTestParaData->m_strValue);
// 	}
// 
// 	return pMacroParasGroup;
// }

void QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick()//添加单个测试项
{
	if (m_pMulitMacroRootItems == NULL)
	{
		return;
	}

	CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	if (pParentItems == NULL)
	{
		return;
	}

	CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CString strItemPath/*,strItemName,strItemID*/;
	strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// 	strItemName = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.m_strName;
// 	strItemID = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.m_strID;

// 	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.Clone();
// 	CSttMacroTestParaDatas *pParaDatas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
// 	pParentItems->AddNewChild(pNewTest,TRUE);

	CString strMacroUI_ID,strItemName,strItemID;
	strItemName = m_pSingleMacroRef->m_strName;
	strItemID = m_pSingleMacroRef->m_strID;
	strMacroUI_ID = GetMacroID();
	pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

	g_nUpdateMultiMacroParaEditView = 0;
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName/*pNewTest->m_strName*/, strItemID/*pNewTest->m_strID*/, strItemPath, 0,
		m_pSingleMacroRef->m_strID, strMacroUI_ID);
	g_nUpdateMultiMacroParaEditView = 1;

	if (nRet!= STT_CMD_ExecStatus_SUCCESS)
	{
//		pParentItems->Delete(pNewTest);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
		return;
	}

	CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);

	if (pNewTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
		return;
	}

	m_pCurrMacroItemsRef->AddTail(pNewTest);
	m_pCurrMacroParaEditGrid->InsertData(pNewTest);

	//20240920 luozibing 根据参数设置测试项Name
	SetMacroTestNameByParas(pNewTest);
	//添加特性图测试点	在函数中判断接口是否为空
	AddUpdateTestPoint_To_Charact(pNewTest);
	//添加Z/T视图测试点
		AddTestPoint_To_ZTView(pNewTest);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	UpdateBottomBtnsEnable();
// 
// 	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
// 	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroParaEditGrid->rowCount());
}

void QSttMultiMacroParaEditViewBase::slot_AddMultiItemBtnClick()//添加系列
{
	UpdateBottomBtnsEnable();
}

void QSttMultiMacroParaEditViewBase::slot_CommonParasBtnClick()//通用参数
{

}

void QSttMultiMacroParaEditViewBase::slot_BinarysBtnClick()//开关量
{

}

void QSttMultiMacroParaEditViewBase::slot_DeleteItemBtnClick()//删除测试项
{

}

void QSttMultiMacroParaEditViewBase::slot_ClearResultBtnClick()//清除测试结果
{

}

BOOL QSttMultiMacroParaEditViewBase::MultiMacroParaEdit_DeleteOneMacroItem(CSttMacroTest *pSttMacroTest,CExBaseList *pMacroItemsRef)
{
	if (pSttMacroTest == NULL)
	{
		return FALSE;
	}

	CSttItemBase *pParentItems = (CSttItemBase*)pSttMacroTest->GetParent();
	CString strParentItemsPath;
	strParentItemsPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_DeleteOneItem(pSttMacroTest->m_strID, strParentItemsPath);


	if (nRet!= STT_CMD_ExecStatus_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("删除单个电气量测试功能执行命令失败(%ld)."),nRet);
		return FALSE;
	}

	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == pSttMacroTest)
	{
		m_pSingleItemParaEditWidget->m_pCurrMacroTest_External = NULL;
	}
	
	//删除特性曲线测试点 在函数中判断接口是否为空
		DeleteTestPoint_To_Charact(pSttMacroTest);
	//删除Z/T视图测试点
		DeleteTestPoint_To_ZTView(pSttMacroTest);
	m_pCurrMacroParaEditGrid->DeleteDataRow(pSttMacroTest,FALSE);
	pMacroItemsRef->Remove(pSttMacroTest);
	ASSERT(m_pMulitMacroRootItems);
	m_pMulitMacroRootItems->DeleteChildItem(pSttMacroTest);

	UpdateBottomBtnsEnable();
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewBase::HasMacroParasModified()
{
	if (m_bCharTestObjectHasChanged)
	{
		return TRUE;
	}

	return Global_HasMacroItemModified(m_pMulitMacroRootItems);
}

CDataGroup* QSttMultiMacroParaEditViewBase::GetAddMultItems_Paras()
{
	CDataGroup *pAddMultItems_Paras = &g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras;
//	if (m_pAddMultItems_Paras == NULL)
	{
//		m_pAddMultItems_Paras = (CDataGroup*)g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.Clone();
//		m_pAddMultItems_Paras = new CDataGroup;

		if (pAddMultItems_Paras->GetCount() <= 0)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, "m_oTestMacroUI_Paras链表为空,查找相关配置文件。");
			CString strPath;
			strPath = g_pTheSttTestApp->m_pTestCtrlCntr->GetCurrMacroUIParasFilePath();
			CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
			pAddMultItems_Paras->OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
			CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
		}
	}

	return pAddMultItems_Paras;
}

CExBaseList* QSttMultiMacroParaEditViewBase::GetCurrentMacroDatas()
{
    CExBaseList* pTemp = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
    CExBaseList* pDatas = (CExBaseList*)pTemp->Clone();
    return pDatas;
}

BOOL QSttMultiMacroParaEditViewBase::Ats_UpdateMacroTestItems()
{
	if (m_pMulitMacroRootItems == NULL)
	{
		return FALSE;
	}

	return g_theTestCntrFrame->Ats_UpdateAllMacroItem_InternationalMode(m_pMulitMacroRootItems);
}

BOOL QSttMultiMacroParaEditViewBase::Ats_ClearReportRslts(CSttItemBase *pCurrItem)
{
	if (pCurrItem == NULL)
	{
		return FALSE;
	}

	CString strPath;
	CDataGroup oParas;
	strPath = pCurrItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	oParas.AddNewData(STT_CMD_PARA_OnlySelect, _T("1"));
	oParas.AddNewData(STT_CMD_PARA_ItemsID, strPath);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->ClearReportsRslts(&oParas);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		pCurrItem->ClearReport();
		pCurrItem->SetState(TEST_STATE_NORMAL);
		CSttItems oList;
		oList.AddTail(pCurrItem);
		Stt_EmptyReportDatas(&oList, TRUE);
		oList.RemoveAll();
		return TRUE;
	}

	return FALSE;
}

CSttItems* QSttMultiMacroParaEditViewBase::Get_MulitMacroRootItems()
{
	return m_pMulitMacroRootItems;
}

void QSttMultiMacroParaEditViewBase::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMultiMacroParaEditViewBase::UpdateGoutTab(BOOL bUpdateList /*= FALSE*/)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMultiMacroParaEditViewBase::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGoosePubsWidget == NULL) && (g_oSystemParas.m_nHasDigital) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC > 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		AddGooseParaWidget(m_pGoosePubsWidget);

		connect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()), Qt::DirectConnection);
		connect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGoosePubsWidget != NULL) && (!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
	else if ((m_pGoosePubsWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		m_pGoosePubsWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()), Qt::DirectConnection);
		connect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGoosePubsWidget != NULL) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
}

void QSttMultiMacroParaEditViewBase::RemoveGooseParaWidget()
{
	if (m_pGoosePubsWidget == NULL)
	{
		return;
	}

	int nIndex = m_pSingleItemEditTab->indexOf(m_pGoosePubsWidget);

	if (nIndex >= 0)
	{
		m_pSingleItemEditTab->removeTab(nIndex);
	}

	delete m_pGoosePubsWidget;
	m_pGoosePubsWidget = NULL;

}

void QSttMultiMacroParaEditViewBase::AddGooseParaWidget(QWidget *pWidget)
{
	if (m_pGoosePubsWidget || !m_pSingleItemEditTab)
	{
		return;
	}

	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());

	CString strTitle;
	xlang_GetLangStrByFile(strTitle, "Native_GooseDataSet");
	m_pSingleItemEditTab->addTab(m_pGoosePubsWidget, strTitle);

}

//20240813 wanmj 从距离模块移到基类
bool QSttMultiMacroParaEditViewBase::eventFilter(QObject *target, QEvent *event)
{
    //20240729 luozibing 点击表格空白处，取消选中
//     QMouseEvent *e = static_cast<QMouseEvent *>(event);
//     if(target == m_pCurrMacroParaEditGrid->viewport() &&(e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease))
//     {
//        QPoint point = e->pos();
//         // 根据鼠标坐标，获取此时鼠标按下时所在的行、列
//        QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
//        m_pCurrMacroParaEditGrid->item(index.row(), index.column());
//        if (m_pCurrMacroParaEditGrid->item(index.row(), index.column()) == nullptr)
//        {
//            //20240910 wanmj 右击表格添加全选/全不选/添加/删除快捷功能
//            if(e->button() == Qt::RightButton)
//            {
//                m_menuTest->exec(QCursor::pos());
//            }
//            else
//            {
//             //取消选中
//             m_pCurrMacroParaEditGrid->setCurrentItem(NULL);
//             m_pSingleItemParaEditWidget->UpdateParas(NULL);
// 		   }
// 	   }
//     }

	//2024-10-16 wuxinyi 点击对应测试项行数才可出现菜单栏
	if (event->type() == QEvent::MouseButtonPress)
	{
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
		if (e->button() == Qt::RightButton)
    {
       QPoint point = e->pos();
        // 根据鼠标坐标，获取此时鼠标按下时所在的行、列
       QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
			if (index.isValid())  // 确保点在有效的格子里
       {
				qDebug() << m_pCurrMacroParaEditGrid->currentRow();
				m_pCurrMacroParaEditGrid->SelectRow(index.row() + 1);

				if (m_pCurrMacroParaEditGrid->item(index.row(), index.column()) != NULL)
           {
					// 显示右键菜单
               m_menuTest->exec(QCursor::pos());

					// 事件已处理，防止重复触发
					return true;
           }
        }
    }
		else if (e->button() == Qt::LeftButton)
		{
			QPoint point = e->pos();
			// 根据鼠标坐标，获取此时鼠标按下时所在的行、列
			QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
			if (!index.isValid())  // 确保点未在有效的格子里
			{
				 //20241025 luozibing 鼠标左击表格空白处 取消选中
				 m_pCurrMacroParaEditGrid->setCurrentItem(NULL);
				 m_pSingleItemParaEditWidget->UpdateParas(NULL);
			}
		}
    }
    return QWidget::eventFilter(target, event);
}

void QSttMultiMacroParaEditViewBase::UpdateBtnEnable(QPushButton *pPushButton, bool bEnable)
{
	if (pPushButton != NULL)
	{
		pPushButton->setEnabled(bEnable);
	}
}

void QSttMultiMacroParaEditViewBase::UpdateBottomBtnsEnable()
{
	if (m_pCurrMacroItemsRef == NULL)
	{
		return;
	}

	BOOL bEnable = ((m_pCurrMacroItemsRef->GetCount()) > 0 && (!stt_Frame_IsTestStarted()));//add wangtao 20241014 正在测试过程中，多功能模块切换，按钮不使能
	UpdateBtnEnable(m_pDeleteItemBtn, bEnable);
	UpdateBtnEnable(m_pClearResultBtn, bEnable);
}

bool QSttMultiMacroParaEditViewBase::PrepStartTest()
{
	if (m_pCurrMacroItemsRef->GetCount() <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("当前测试项为空，请添加测试项之后再次开始测试！"));
		return FALSE;
	}
	return TRUE;
}

void QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick()
{
	if (m_pAddMultiItemSelectDlg != NULL)   
	{
		m_pAddMultiItemSelectDlg->hide();
	}

	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttMacroTest *pCurrSelectData = m_pCurrMacroParaEditGrid->GetCurrSelSttMacroTest();

	if (pCurrSelectData == NULL)
	{
		return;
	}
	//20240809 luozibing 在MultiMacroParaEdit_DeleteOneMacroItem函数删除对应pCurrSelectData的测试点
	MultiMacroParaEdit_DeleteOneMacroItem(pCurrSelectData, m_pCurrMacroItemsRef);
    //stt_Frame_AddUpdateReport_QT(m_pMulitMacroRootItems);//zhouhj 2024.10.16 更新报告视图

    //ftt 2024.10.16 使用项目路径更新报告
    QString strItemsPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    stt_Frame_AddUpdateReport_QT(strItemsPath);


// 	//20240625 luozibing 删除当前测试项并选中第一行
// 	CExBaseObject *pCurrObj  = m_pCurrMacroParaEditGrid->GetCurrSelData();
// 	CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
// 	if(pSttMacroTest == m_pSingleItemParaEditWidget->m_pCurrMacroTest)
// 	{
// 		m_oSingleMacroItemsRef.Delete(pSttMacroTest);
// 		((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->DelMacroTestParaDatas();
// 		m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
// 		m_pCurrMacroParaEditGrid->SelectRow(1);
// 	}
}
void QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick()
{
	if (m_pAddMultiItemSelectDlg != NULL)  
	{
		m_pAddMultiItemSelectDlg->hide();
	}

	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttItems *pRootItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest *pCurrMacroTest = NULL;
	POS pos = pRootItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pRootItems->GetNext(pos);

		if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
		{
			continue;
		}

		pCurrMacroTest = (CSttMacroTest *)pCurrObj;
		MultiMacroParaEdit_DeleteOneMacroItem(pCurrMacroTest, m_pCurrMacroItemsRef);
	}

	UpdateBottomBtnsEnable();
    //stt_Frame_AddUpdateReport_QT(m_pMulitMacroRootItems);//zhouhj 2024.10.16 更新报告视图

    //ftt 2024.10.16 使用项目路径更新报告
    QString strItemsPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    stt_Frame_AddUpdateReport_QT(strItemsPath);

// 	m_pSingleItemParaEditWidget->m_pCurrMacroTest_External = NULL;
// 	m_oSingleMacroItemsRef.RemoveAll();
// 	m_pCurrMacroParaEditGrid->ShowDatas(NULL);
// 	ASSERT(m_pMulitMacroRootItems);
// 	m_pMulitMacroRootItems->DeleteAll();
// 	//20240625 luozibing 删除所有测试项
// 	((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->DelMacroTestParaDatas();
// 	POS pos = m_oSingleMacroItemsRef.GetHeadPosition();
// 	while (pos!= NULL)
// 	{
// 		CExBaseList *pItem = (CExBaseList*)m_oSingleMacroItemsRef.GetNext(pos);
// 		if(pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
// 		{
// 			m_oSingleMacroItemsRef.Delete(pItem);
// 		}
// 	}
// 	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
}

void QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick()
{
	if (m_pAddMultiItemSelectDlg != NULL)   
	{
		m_pAddMultiItemSelectDlg->hide();
	}

	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttMacroTest *pCurrSelectData = m_pCurrMacroParaEditGrid->GetCurrSelSttMacroTest();

	if (Ats_ClearReportRslts(pCurrSelectData))
	{
		m_pCurrMacroParaEditGrid->UpdateData(pCurrSelectData);
	}
}

void QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick()
{
	if (m_pAddMultiItemSelectDlg != NULL)
	{
		m_pAddMultiItemSelectDlg->hide();
	}

	if (m_pCurrMacroParaEditGrid == NULL)
	{
		return;
	}

	CSttItems *pRootItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CExBaseObject *pCurrObj = NULL;
	CSttMacroTest *pCurrMacroTest = NULL;
	POS pos = pRootItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pRootItems->GetNext(pos);

		if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
		{
			continue;
		}

		pCurrMacroTest = (CSttMacroTest *)pCurrObj;

		if (Ats_ClearReportRslts(pCurrMacroTest))
		{
			m_pCurrMacroParaEditGrid->UpdateData(pCurrMacroTest);
		}
// 		pCurrMacroTest->m_nState = TEST_STATE_NORMAL;
// 		m_pCurrMacroParaEditGrid->UpdateData(pCurrMacroTest);
// 		Ats_ClearReportRslts(pCurrMacroTest);
	}
}

//表格参数修改后,更新到当前参数编辑界面
void QSttMultiMacroParaEditViewBase::slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest)
{
	if (m_pSingleItemParaEditWidget == NULL)
	{
		return;
	}

	pMacroTest->m_nModified = 1;
	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External != pMacroTest)
	{
		return;
	}
	UpdateCharacteristicParas(pMacroTest);
	m_pSingleItemParaEditWidget->UpdateParas(pMacroTest);
	AddUpdateTestPoint_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	UpdateTestPoint_To_ZTView(pMacroTest,true);
	UpdateParas_To_ZTView();//20240925 luozibing 设置故障类型后更新Z/T视图折线图
	UpdateTestUI_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
}

//测试项全选
void QSttMultiMacroParaEditViewBase::slot_SelectAllItems()
{
    if(m_pCurrMacroParaEditGrid == NULL)
        return;

    POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTest* pMacroTestTemp = (CSttMacroTest*)m_pCurrMacroItemsRef->GetNext(pos);
        pMacroTestTemp->m_nSelect = 1;
        slot_ParaEditWidget_To_Grid(pMacroTestTemp);
    }

    Ats_UpdateMacroTestItems();
}

//测试项全不选
void QSttMultiMacroParaEditViewBase::slot_DeselectAllItems()
{
    if(m_pCurrMacroParaEditGrid == NULL)
        return;

    POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
    while(pos != NULL)
    {
        CSttMacroTest* pMacroTestTemp = (CSttMacroTest*)m_pCurrMacroItemsRef->GetNext(pos);
        pMacroTestTemp->m_nSelect = 0;
        slot_ParaEditWidget_To_Grid(pMacroTestTemp);
    }

    Ats_UpdateMacroTestItems();
}

//参数编辑界面修改后,更新到当前选择表格
void QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{

	pMacroTest->m_nModified = 1;
	UpdateCharacteristicParas(pMacroTest);
	SetMacroTestNameByParas(pMacroTest);//20240920 luozibing 根据参数设置测试项Name
	m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);
	AddUpdateTestPoint_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	UpdateTestPoint_To_ZTView(pMacroTest, true);
	UpdateParas_To_ZTView();//20240925 luozibing 设置故障类型后更新Z/T视图折线图
	UpdateTestUI_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
}
//获取最新特性曲线参数并更新到界面 20240724 luozibing
void QSttMultiMacroParaEditViewBase::UpdateParasByCharEdit()
{
	//更新特性曲线时间定值等参数到表格数据
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
	while(pos != NULL)
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
		UpdateCharacteristicParas(pMacroTest);
	}
	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	//更新特性曲线时间定值到编辑界面
	UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	UpdateParas_To_ZTView();//20240925 luozibing 特性曲线参数改变时更新Z/T视图折线图
}
void QSttMultiMacroParaEditViewBase::UpdateCharacteristicParas(CSttMacroTest *pMacroTest)
{//更新界面显示对应特性曲线参数
	
}

void QSttMultiMacroParaEditViewBase::UpdateZoneSelDataTypes()
{
	//获取所有曲线故障类型对应CDataType并清空子节点
	CString strDataTypeId = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
	strDataTypeId += "_";
	CString strDataTypeId_LL = strDataTypeId + CHAR_DISTANCE_FAULT_TYPE_LL;
	CDataType *pDataType_LL = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_LL, CHAR_DISTANCE_FAULT_TYPE_LL);
	pDataType_LL->DeleteAll();

	CString strDataTypeId_LN = strDataTypeId + CHAR_DISTANCE_FAULT_TYPE_LN;
	CDataType *pDataType_LN = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_LN, CHAR_DISTANCE_FAULT_TYPE_LN);
	pDataType_LN->DeleteAll();

	CString strDataTypeId_LLL = strDataTypeId + CHAR_DISTANCE_FAULT_TYPE_LLL;
	CDataType *pDataType_LLL = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_LLL, CHAR_DISTANCE_FAULT_TYPE_LLL);
	pDataType_LLL->DeleteAll();

	CString strDataTypeId_LLN = strDataTypeId + CHAR_DISTANCE_FAULT_TYPE_LLN;
	CDataType *pDataType_LLN = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_LLN, CHAR_DISTANCE_FAULT_TYPE_LLN);
	pDataType_LLN->DeleteAll();

	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	POS pos = pCharacteristics->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject *pObj = pCharacteristics->GetNext(pos);
		if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharacteristic *pChar = (CCharacteristic *)pObj;
		//获取勾选使用的曲线
		if (pChar->m_nUse != 1)
		{
			continue;
		}

		CString strDataTypeId_Char;
		CDataType *pDataType = NULL;
		CDataTypeValue *pDataTypeValue = NULL;
		CString strCharIndex = pChar->m_strIndex;
		CString strCharIndexName;//对应区段界面显示数据
		//根据曲线的区段值 查找区段下拉框界面显示数据
		pDataType = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone);
		if (pDataType != NULL)
		{
			pDataTypeValue = pDataType->FindByIndex(strCharIndex);
			strCharIndexName = pDataTypeValue->m_strName;
		}
		if (strCharIndexName == g_sLangTxt_Distance_ZoneLine || strCharIndexName == g_sLangTxt_Distance_ZoneAllarea)
		{
			continue;
		}
		if (pChar->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
		{//在所有曲线故障类型对应CDataType中都添加区段值对应CDataTypeValue
			pDataTypeValue = (CDataTypeValue *)pDataType_LL->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType_LL->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
			pDataTypeValue = (CDataTypeValue *)pDataType_LN->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType_LN->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
			pDataTypeValue = (CDataTypeValue *)pDataType_LLL->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType_LLL->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
			pDataTypeValue = (CDataTypeValue *)pDataType_LLN->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType_LLN->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
		}
		else
		{//曲线故障类型不为ALL 将区段值对应CDataTypeValue添加到对应DateType
			strDataTypeId_Char = strDataTypeId + pChar->m_strID;
			pDataType = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_Char, pChar->m_strID);
			pDataTypeValue = (CDataTypeValue *)pDataType->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
		}
	}

	//将根据index从小到大排序
	pDataType_LL->Sort(true);
	pDataType_LN->Sort(true);
	pDataType_LLL->Sort(true);
	pDataType_LLN->Sort(true);

	//给所有CDataType添加线路长度 所有区段 区段
	CString strValueID_Line, strValueID_ALL;
	strValueID_Line.setNum(STT_MULTI_MACRO_ZONELine);
	strValueID_ALL.setNum(STT_MULTI_MACRO_ZONEAll);

	pDataType_LL->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"线路长度"*/, strValueID_Line, strValueID_Line);
	pDataType_LL->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"所有区域"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LN->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"线路长度"*/, strValueID_Line, strValueID_Line);
	pDataType_LN->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"所有区域"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LLL->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"线路长度"*/, strValueID_Line, strValueID_Line);
	pDataType_LLL->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"所有区域"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LLN->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"线路长度"*/, strValueID_Line, strValueID_Line);
	pDataType_LLN->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"所有区域"*/, strValueID_ALL, strValueID_ALL);
}
void QSttMultiMacroParaEditViewBase::UpdateParas_To_ZTView()
{//更新ZT视图折线显示

}
BOOL QSttMultiMacroParaEditViewBase::AddTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)
{//添加测试项时,在ZT视图界面添加对应测试点
	return false;
}
BOOL QSttMultiMacroParaEditViewBase::DeleteTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)
{//根据路径删除ZT视图对应测试点
	return false;
}
BOOL QSttMultiMacroParaEditViewBase::UpdateTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest, bool bSelPoint)
{//根据路径更新ZT视图对应测试点
	return false;
}void QSttMultiMacroParaEditViewBase::SetMacroTestNameByParas(CSttMacroTest *pMacroTest)
{//20240920 luozibing 根据参数设置测试项Name

}
