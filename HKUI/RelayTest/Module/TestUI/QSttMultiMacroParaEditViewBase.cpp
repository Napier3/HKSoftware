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

	//2024-10-16 wuxinyi ����ʾ��InitData���ظ�����ע��
// 	if (pMulitMacroRootItems->GetCount() <= 0)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("����Ӳ����"));//�ڳ�ʼ��û�в�����ʱ��ʾ��
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
		//2024.7.24 zhangyq ������ʱ�޽ڵ�Ϊmacro-char-items
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�򿪲��Թ��ܱ�������ļ�(%s)ʧ��."),strPath.GetString());
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


//���������ܶ�����
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
	strText = g_sLangTxt_Gradient_CommonParas/*"ͨ�ò���"*/;
	m_pCommonParasBtn = new QPushButton(strText);
	strText = g_sLangTxt_Native_SwitchVal /*"������"*/;
	m_pBinarysBtn = new QPushButton(strText);
	strText =  g_sLangTxt_Distance_DeleteItem/*"ɾ��������"*/;
	m_pDeleteItemBtn = new QPushButton(strText);
	strText = g_sLangTxt_Distance_ClearResult/*"������Խ��"*/;
	m_pClearResultBtn = new QPushButton(strText);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 3"));

	m_pBottomHboxLayout->addWidget(m_pCommonParasBtn);
	m_pBottomHboxLayout->addWidget(m_pBinarysBtn);
	m_pBottomHboxLayout->addWidget(m_pDeleteItemBtn);
	m_pBottomHboxLayout->addWidget(m_pClearResultBtn);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewBase::InitUI_OneMacroce : 4"));

	m_pMainVboxLayout = new QVBoxLayout();

    // 2024-7-19 wuxinyi �м���϶������� QSplitter
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

//�����๦�ܶ�����
void QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(QStringList strTabTitleList)
{

	setFont(*g_pSttGlobalFont);

	CString strText;
	m_pMultiMacroGridTab = new QTabWidget();
	m_pSingleItemEditTab = new QTabWidget();

	m_pBottomHboxLayout = new QHBoxLayout();
    strText = g_sLangTxt_Gradient_CommonParas/*ͨ�ò���*/;
	m_pCommonParasBtn = new QPushButton(strText);
    strText = g_sLangTxt_Native_SwitchVal/*"������"*/;
	m_pBinarysBtn = new QPushButton(strText);
    strText = g_sLangTxt_Distance_DeleteItem/*"ɾ��������"*/;
	m_pDeleteItemBtn = new QPushButton(strText);
    strText = g_sLangTxt_Distance_ClearResult/*"������Խ��"*/;
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
    // 2024-7-19 wuxinyi �м���϶������� QSplitter
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

	//�����ܶ��
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

	//2024-10-16 wuxinyi �����๦�ܶ����ˢ��
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++)
	{
		if (m_pMultiMacroParaEditGrid[i] == NULL)
		{
			break;
		}
		m_oMultiMacroItemsRef[i].RemoveAll();
		Global_GetAllMacroTest(&m_oMultiMacroItemsRef[i], m_pMulitMacroRootItems, m_pMultiMacroRef[i]);
		m_pMultiMacroParaEditGrid[i]->ShowDatas(&m_oMultiMacroItemsRef[i]);

		//���Ƴ��ٰ�װ�������������ظ���װ
		m_pMultiMacroParaEditGrid[i]->viewport()->removeEventFilter(this);
		m_pMultiMacroParaEditGrid[i]->viewport()->installEventFilter(this);
	}


	//2024-10-16 wuxinyi ����ˢ�²�����
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

//20240910 wanmj �������Ҽ����������ݹ���
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
	//20240627 luozibing ���ѡ��ĵ�Ԫ��Ϊ�գ��л���ʧ��
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
// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���µ������������Թ���ִ������ʧ��(%ld)."),nRet);
// 			return;
// 		}
// 	}
	////���µ�ǰѡ����ʱ�䶨ֵ�Ȳ���
	//UpdateCharacteristicParas(pSttMacroTest);

	m_pSingleItemParaEditWidget->UpdateParas(pSttMacroTest);

	//2024-10-14 wuxinyi ���ж�m_pCharactInterface
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}

	if (m_pCharactInterface)
	{
	//��ǰѡ����ı䣬���µ�ǰѡ����Ե�
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
	UpdateParas_To_ZTView();//20240925 luozibing ���ù������ͺ����Z/T��ͼ����ͼ
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
	for (int i = 0; i < STT_MULTI_MACRO_PARAS_EDIT_GRID_MAXNUM; i++) //add wangtao20240801 �๦��ģ�飬��ʼ����ʱ����ÿ�����ܽ��涼��ʹ�ܣ�ֹͣ����ͬ��
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

	//202408122 zhangyq ��ʼ��������·��İ�ť���ɱ༭
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

	//�๦�ܶ��ʹ��,�����л���ǰtab��ʾ����
	SyncCurrMacroItemParaEditWidget(pSttItem);

	if (m_pCurrMacroItemsRef->Find(pSttItem) != NULL)
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����״̬�ı�[%s][%ld]"),pSttItem->m_strID.GetString(),pSttItem->m_nState);
		m_pSingleItemParaEditWidget->UpdateParas((CSttMacroTest*)pSttItem);
		m_pCurrMacroParaEditGrid->UpdateData(pSttItem);
		m_pCurrMacroParaEditGrid->SelectRow(pSttItem);//zhouhj 2024.9.2 ����ѡ����

		if (IsManualTriggerMode_MacroTestItem((CSttMacroTest*)pSttItem))
		{
			//�ֶ�������ť����
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

	//�๦�ܶ��ʹ��,�����л���ǰtab��ʾ����
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
		UpdateCharacteristicParas(pSttMacroTest);//20240813 luozibing ��� ���ϵ�����ɵĲ�����ʱ����ʱ�䶨ֵ�Ȳ���
		SetMacroTestNameByParas(pSttMacroTest);//20240920 luozibing ���ݲ������ò�����Name
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
	UpdateBottomBtnsEnable();//20240902 luozibing���ϵ�к���°���ʹ��
}

BOOL QSttMultiMacroParaEditViewBase::IsManualTriggerMode_MacroTestItem(CSttMacroTest* pMacroTest)
{
	return FALSE;
}

//��Ӳ�����ʱ,���������߽�����Ӷ�Ӧ���Ե�
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
		//zhouhj 2024.10.9 �޸�Ϊ����ȫ�����ݵķ�ʽ
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)//�����ǰ������û��,�����ȱʡ����
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pShortData->m_strID, pShortData->m_strDataTypeID, pShortData->m_strValue);
		}
		else//�����Ե�ǰ����Ϊ׼
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
		//	//20240717 luozibing �޸Ĵ��ݲ���
		//	pMacroParasGroup->AddNewData(pShortData->m_strName,pSttMacroTestParaData->m_strID,pShortData->m_strDataTypeID,pSttMacroTestParaData->m_strValue);
		//}
	}

	pShortDatas = m_pSingleMacroRef->GetSysParas();
	pos = pShortDatas->GetHeadPosition();

	while(pos)
	{
		pShortData = (CShortData *)pShortDatas->GetNext(pos);
		//zhouhj 2024.10.9 �޸�Ϊ����ȫ�����ݵķ�ʽ
		pSttMacroTestParaData = (CSttMacroTestParaData*)pSttTestParaDatas->FindByID(pShortData->m_strID);

		if (pSttMacroTestParaData == NULL)//�����ǰ������û��,�����ȱʡ����
		{
			pMacroParasGroup->AddNewData(pShortData->m_strName, pShortData->m_strID, pShortData->m_strDataTypeID, pShortData->m_strValue);
		}
		else//�����Ե�ǰ����Ϊ׼
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

void QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick()//��ӵ���������
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ӵ������������Թ���ִ������ʧ��(%ld)."),nRet);
		return;
	}

	CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);

	if (pNewTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ӵ������������Թ���ʧ��."));
		return;
	}

	m_pCurrMacroItemsRef->AddTail(pNewTest);
	m_pCurrMacroParaEditGrid->InsertData(pNewTest);

	//20240920 luozibing ���ݲ������ò�����Name
	SetMacroTestNameByParas(pNewTest);
	//�������ͼ���Ե�	�ں������жϽӿ��Ƿ�Ϊ��
	AddUpdateTestPoint_To_Charact(pNewTest);
	//���Z/T��ͼ���Ե�
		AddTestPoint_To_ZTView(pNewTest);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	UpdateBottomBtnsEnable();
// 
// 	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
// 	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroParaEditGrid->rowCount());
}

void QSttMultiMacroParaEditViewBase::slot_AddMultiItemBtnClick()//���ϵ��
{
	UpdateBottomBtnsEnable();
}

void QSttMultiMacroParaEditViewBase::slot_CommonParasBtnClick()//ͨ�ò���
{

}

void QSttMultiMacroParaEditViewBase::slot_BinarysBtnClick()//������
{

}

void QSttMultiMacroParaEditViewBase::slot_DeleteItemBtnClick()//ɾ��������
{

}

void QSttMultiMacroParaEditViewBase::slot_ClearResultBtnClick()//������Խ��
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ɾ���������������Թ���ִ������ʧ��(%ld)."),nRet);
		return FALSE;
	}

	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == pSttMacroTest)
	{
		m_pSingleItemParaEditWidget->m_pCurrMacroTest_External = NULL;
	}
	
	//ɾ���������߲��Ե� �ں������жϽӿ��Ƿ�Ϊ��
		DeleteTestPoint_To_Charact(pSttMacroTest);
	//ɾ��Z/T��ͼ���Ե�
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
			CLogPrint::LogString(XLOGLEVEL_ERROR, "m_oTestMacroUI_Paras����Ϊ��,������������ļ���");
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
	if ((m_pGoosePubsWidget == NULL) && (g_oSystemParas.m_nHasDigital) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC > 0))//����ǰ��GOOSE����,���º���ҪGOOSE����
	{
		AddGooseParaWidget(m_pGoosePubsWidget);

		connect(m_pGoosePubsWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()), Qt::DirectConnection);
		connect(m_pGoosePubsWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGoosePubsWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGoosePubsWidget != NULL) && (!g_oSystemParas.m_nHasDigital))//����ǰ��GOOSE����,���º���Ҫ
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
	else if ((m_pGoosePubsWidget != NULL) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//����ǰ��GOOSE����,���º�LC��Ϊ0����Ҫ
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

//20240813 wanmj �Ӿ���ģ���Ƶ�����
bool QSttMultiMacroParaEditViewBase::eventFilter(QObject *target, QEvent *event)
{
    //20240729 luozibing ������հ״���ȡ��ѡ��
//     QMouseEvent *e = static_cast<QMouseEvent *>(event);
//     if(target == m_pCurrMacroParaEditGrid->viewport() &&(e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease))
//     {
//        QPoint point = e->pos();
//         // ����������꣬��ȡ��ʱ��갴��ʱ���ڵ��С���
//        QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
//        m_pCurrMacroParaEditGrid->item(index.row(), index.column());
//        if (m_pCurrMacroParaEditGrid->item(index.row(), index.column()) == nullptr)
//        {
//            //20240910 wanmj �һ�������ȫѡ/ȫ��ѡ/���/ɾ����ݹ���
//            if(e->button() == Qt::RightButton)
//            {
//                m_menuTest->exec(QCursor::pos());
//            }
//            else
//            {
//             //ȡ��ѡ��
//             m_pCurrMacroParaEditGrid->setCurrentItem(NULL);
//             m_pSingleItemParaEditWidget->UpdateParas(NULL);
// 		   }
// 	   }
//     }

	//2024-10-16 wuxinyi �����Ӧ�����������ſɳ��ֲ˵���
	if (event->type() == QEvent::MouseButtonPress)
	{
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
		if (e->button() == Qt::RightButton)
    {
       QPoint point = e->pos();
        // ����������꣬��ȡ��ʱ��갴��ʱ���ڵ��С���
       QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
			if (index.isValid())  // ȷ��������Ч�ĸ�����
       {
				qDebug() << m_pCurrMacroParaEditGrid->currentRow();
				m_pCurrMacroParaEditGrid->SelectRow(index.row() + 1);

				if (m_pCurrMacroParaEditGrid->item(index.row(), index.column()) != NULL)
           {
					// ��ʾ�Ҽ��˵�
               m_menuTest->exec(QCursor::pos());

					// �¼��Ѵ�����ֹ�ظ�����
					return true;
           }
        }
    }
		else if (e->button() == Qt::LeftButton)
		{
			QPoint point = e->pos();
			// ����������꣬��ȡ��ʱ��갴��ʱ���ڵ��С���
			QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
			if (!index.isValid())  // ȷ����δ����Ч�ĸ�����
			{
				 //20241025 luozibing ���������հ״� ȡ��ѡ��
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

	BOOL bEnable = ((m_pCurrMacroItemsRef->GetCount()) > 0 && (!stt_Frame_IsTestStarted()));//add wangtao 20241014 ���ڲ��Թ����У��๦��ģ���л�����ť��ʹ��
	UpdateBtnEnable(m_pDeleteItemBtn, bEnable);
	UpdateBtnEnable(m_pClearResultBtn, bEnable);
}

bool QSttMultiMacroParaEditViewBase::PrepStartTest()
{
	if (m_pCurrMacroItemsRef->GetCount() <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("��ǰ������Ϊ�գ�����Ӳ�����֮���ٴο�ʼ���ԣ�"));
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
	//20240809 luozibing ��MultiMacroParaEdit_DeleteOneMacroItem����ɾ����ӦpCurrSelectData�Ĳ��Ե�
	MultiMacroParaEdit_DeleteOneMacroItem(pCurrSelectData, m_pCurrMacroItemsRef);
    //stt_Frame_AddUpdateReport_QT(m_pMulitMacroRootItems);//zhouhj 2024.10.16 ���±�����ͼ

    //ftt 2024.10.16 ʹ����Ŀ·�����±���
    QString strItemsPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    stt_Frame_AddUpdateReport_QT(strItemsPath);


// 	//20240625 luozibing ɾ����ǰ�����ѡ�е�һ��
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
    //stt_Frame_AddUpdateReport_QT(m_pMulitMacroRootItems);//zhouhj 2024.10.16 ���±�����ͼ

    //ftt 2024.10.16 ʹ����Ŀ·�����±���
    QString strItemsPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    stt_Frame_AddUpdateReport_QT(strItemsPath);

// 	m_pSingleItemParaEditWidget->m_pCurrMacroTest_External = NULL;
// 	m_oSingleMacroItemsRef.RemoveAll();
// 	m_pCurrMacroParaEditGrid->ShowDatas(NULL);
// 	ASSERT(m_pMulitMacroRootItems);
// 	m_pMulitMacroRootItems->DeleteAll();
// 	//20240625 luozibing ɾ�����в�����
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

//�������޸ĺ�,���µ���ǰ�����༭����
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
	UpdateParas_To_ZTView();//20240925 luozibing ���ù������ͺ����Z/T��ͼ����ͼ
	UpdateTestUI_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
}

//������ȫѡ
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

//������ȫ��ѡ
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

//�����༭�����޸ĺ�,���µ���ǰѡ����
void QSttMultiMacroParaEditViewBase::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{

	pMacroTest->m_nModified = 1;
	UpdateCharacteristicParas(pMacroTest);
	SetMacroTestNameByParas(pMacroTest);//20240920 luozibing ���ݲ������ò�����Name
	m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);
	AddUpdateTestPoint_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	UpdateTestPoint_To_ZTView(pMacroTest, true);
	UpdateParas_To_ZTView();//20240925 luozibing ���ù������ͺ����Z/T��ͼ����ͼ
	UpdateTestUI_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
}
//��ȡ�����������߲��������µ����� 20240724 luozibing
void QSttMultiMacroParaEditViewBase::UpdateParasByCharEdit()
{
	//������������ʱ�䶨ֵ�Ȳ������������
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
	while(pos != NULL)
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
		UpdateCharacteristicParas(pMacroTest);
	}
	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	//������������ʱ�䶨ֵ���༭����
	UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	UpdateParas_To_ZTView();//20240925 luozibing �������߲����ı�ʱ����Z/T��ͼ����ͼ
}
void QSttMultiMacroParaEditViewBase::UpdateCharacteristicParas(CSttMacroTest *pMacroTest)
{//���½�����ʾ��Ӧ�������߲���
	
}

void QSttMultiMacroParaEditViewBase::UpdateZoneSelDataTypes()
{
	//��ȡ�������߹������Ͷ�ӦCDataType������ӽڵ�
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
		//��ȡ��ѡʹ�õ�����
		if (pChar->m_nUse != 1)
		{
			continue;
		}

		CString strDataTypeId_Char;
		CDataType *pDataType = NULL;
		CDataTypeValue *pDataTypeValue = NULL;
		CString strCharIndex = pChar->m_strIndex;
		CString strCharIndexName;//��Ӧ���ν�����ʾ����
		//�������ߵ�����ֵ �������������������ʾ����
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
		{//���������߹������Ͷ�ӦCDataType�ж��������ֵ��ӦCDataTypeValue
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
		{//���߹������Ͳ�ΪALL ������ֵ��ӦCDataTypeValue��ӵ���ӦDateType
			strDataTypeId_Char = strDataTypeId + pChar->m_strID;
			pDataType = g_theHtmlRptGenFactory->m_pDataTypes->FindAddDataTypeById(strDataTypeId_Char, pChar->m_strID);
			pDataTypeValue = (CDataTypeValue *)pDataType->FindByID(strCharIndex);
			if (pDataTypeValue == NULL)
			{
				pDataType->AddNewValue(strCharIndexName, strCharIndex, strCharIndex);
			}
		}
	}

	//������index��С��������
	pDataType_LL->Sort(true);
	pDataType_LN->Sort(true);
	pDataType_LLL->Sort(true);
	pDataType_LLN->Sort(true);

	//������CDataType�����·���� �������� ����
	CString strValueID_Line, strValueID_ALL;
	strValueID_Line.setNum(STT_MULTI_MACRO_ZONELine);
	strValueID_ALL.setNum(STT_MULTI_MACRO_ZONEAll);

	pDataType_LL->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"��·����"*/, strValueID_Line, strValueID_Line);
	pDataType_LL->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"��������"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LN->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"��·����"*/, strValueID_Line, strValueID_Line);
	pDataType_LN->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"��������"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LLL->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"��·����"*/, strValueID_Line, strValueID_Line);
	pDataType_LLL->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"��������"*/, strValueID_ALL, strValueID_ALL);
	pDataType_LLN->AddNewValue(g_sLangTxt_Distance_ZoneLine/*"��·����"*/, strValueID_Line, strValueID_Line);
	pDataType_LLN->AddNewValue(g_sLangTxt_Distance_ZoneAllarea/*"��������"*/, strValueID_ALL, strValueID_ALL);
}
void QSttMultiMacroParaEditViewBase::UpdateParas_To_ZTView()
{//����ZT��ͼ������ʾ

}
BOOL QSttMultiMacroParaEditViewBase::AddTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)
{//��Ӳ�����ʱ,��ZT��ͼ������Ӷ�Ӧ���Ե�
	return false;
}
BOOL QSttMultiMacroParaEditViewBase::DeleteTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)
{//����·��ɾ��ZT��ͼ��Ӧ���Ե�
	return false;
}
BOOL QSttMultiMacroParaEditViewBase::UpdateTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest, bool bSelPoint)
{//����·������ZT��ͼ��Ӧ���Ե�
	return false;
}void QSttMultiMacroParaEditViewBase::SetMacroTestNameByParas(CSttMacroTest *pMacroTest)
{//20240920 luozibing ���ݲ������ò�����Name

}
