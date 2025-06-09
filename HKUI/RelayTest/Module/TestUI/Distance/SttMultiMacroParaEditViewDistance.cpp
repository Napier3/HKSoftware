#include "SttMultiMacroParaEditViewDistance.h"
//#include "ui_SttMultiMacroParaEditViewDistance.h"
//#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

#include "../../UI/SttTestCntrFrameBase.h"
QSttMultiMacroParaEditViewDistance::QSttMultiMacroParaEditViewDistance(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15

// 	CString strGbXmlPath;
// 	strGbXmlPath = _P_GetLibraryPath();
// 	strGbXmlPath += "Distance.gbxml";
// 	CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
// 	CExBaseList oTempList;
// 	oTempList.Append(pSttGuideBook);
// 	pSttGuideBook->RemoveAll();
// 	
// 	pSttGuideBook->OpenXmlFile(strGbXmlPath, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 	pSttGuideBook->AppendEx(oTempList);
// 	oTempList.RemoveAll();
// 	m_pMulitMacroRootItems = pSttGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);
// 	stt_gb_get_all_macro_items(STT_MACRO_ID_Distance,&m_oSingleMacroItemsRef,m_pMulitMacroRootItems);
	m_pSingleMacroRef = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_Distance_I);
	m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
    m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();

	m_pZPhiGridInst = NULL;
	m_pRXGridInst = NULL;
    m_bDefault = TRUE;
		
	m_pAddSinglePhase_Paras = NULL;
	m_pAddInterPhase_Paras = NULL;
	m_pAddMult_Paras = NULL;
    //installEventFilter(this);

}

QSttMultiMacroParaEditViewDistance::~QSttMultiMacroParaEditViewDistance()
{
}

void QSttMultiMacroParaEditViewDistance::InitUI_OneMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_OneMacro();

   CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 1"));

    m_pSingleItemParaEditWidget = new QDistanceItemParaEditWidget();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 1-2"));

    m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 2"));

	CString strText;
	strText = g_sLangTxt_Impedance_FunParas/*"功能参数"*/;
	m_pSingleItemEditTab->insertTab(0,m_pSingleItemParaEditWidget,strText);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 3"));


	UpdateBinBoutExTab();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 4"));

    UpdateGoutTab();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 5"));

    UpdateFT3Tab();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 6"));


	strText = g_sLangTxt_Action_AddOneItem/*添加测试项*/;
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = g_sLangTxt_Button_AddMultiItem/*"添加系列"*/;
	m_pAddMultiItemBtn = new QPushButton(strText);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QSttMultiMacroParaEditViewDistance : 7"));
}
//使用基类
//void QSttMultiMacroParaEditViewDistance::UpdateGoutTab(BOOL bUpdateList)
//{
//	m_pGoosePubsWidget->initGoosePubTable(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
//}
void QSttMultiMacroParaEditViewDistance::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();

	UpdateZoneSelDataTypes();//20240911 luozibing 初始化区段下拉框显示

	m_pRXGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_Distance_I, STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_RX);
	m_pZPhiGridInst = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_Distance_I, STT_MULTI_MACRO_DISTANCE_PARAS_GRID_ID_ZPhi);
	m_pCurrMacroParaEditGrid->InitColDef(m_pZPhiGridInst,m_pSingleMacroRef,g_theHtmlRptGenFactory->m_pDataTypes/*((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->GetDataTypes()*/);
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	CheckAllPresence(&m_oSingleMacroItemsRef);
	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
	//20241016 luozibing 初始化数据时判断按键使能
	UpdateBottomBtnsEnable();

    //20240813 wanmj 移到基类
    //m_pCurrMacroParaEditGrid->viewport()->installEventFilter(this);
	//20240912 luozibing 初始化数据时 CSttMacroTest为空显示提示信息
	if (m_pMulitMacroRootItems != NULL)
	{
		if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL&&m_pMulitMacroRootItems->GetCount() > 0)
	{
			CLogPrint::LogString(XLOGLEVEL_INFOR, g_sLangID_Distance_AddTestItemTips /*_T("请添加测试项！")*/);//在初始化没有测试项时提示；
	}
	}
	

	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	if (m_pAddSinglePhase_Paras == NULL)//20240820 luozibing 初始化所有添加系列界面对应数据
	{
		m_pAddSinglePhase_Paras = (CDataGroup *)pTestMacroUI_Paras->Clone();
	}
	if (m_pAddInterPhase_Paras == NULL)
	{
		m_pAddInterPhase_Paras = (CDataGroup *)pTestMacroUI_Paras->Clone();
	}
	if (m_pAddMult_Paras == NULL)
	{
		m_pAddMult_Paras = (CDataGroup *)pTestMacroUI_Paras->Clone();
	}

	UpdateParas_To_ZTView();
	//初始化时获取特性曲线参数
	UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	//初始化特性曲线显示
	UpdateCharacterisByFaultType();

	ConnectAll_SigSlot();
	//20240924 luozibing 设置线路长度阻抗定值缺省值
	CShortDatas* pPars = m_pSingleMacroRef->GetFaultParas();
	CShortData *pZl = (CShortData *)pPars->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
	if (pZl != NULL)
	{
		CDvmData *pData_LN = (CDvmData*)m_pAddSinglePhase_Paras->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6);
		CDvmData *pData_LL = (CDvmData*)m_pAddInterPhase_Paras->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6);

		if (pData_LN != NULL)
		{
			pData_LN->m_strValue = pZl->m_strValue;
		}

		if (pData_LL != NULL)
		{
			pData_LL->m_strValue = pZl->m_strValue;
		}
	}
}

void QSttMultiMacroParaEditViewDistance::CheckAllPresence(CExBaseList *pListItems)
{
	POS pos = pListItems->GetHeadPosition();
	while(pos != NULL)
	{
		CExBaseObject *pData = (CExBaseObject *)pListItems->GetNext(pos);
		if(pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
		{
			continue;
		}
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pData;
		CSttMacroTestParaDatas *pParaDatas = pMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		CheckForPresence(pParaDatas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
	}
}
void QSttMultiMacroParaEditViewDistance::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

void QSttMultiMacroParaEditViewDistance::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
}

//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewDistance::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);

	if (pSttMacroTest == NULL)
	{
		return NULL;
	}

	if (m_pMulitMacroRootItems == NULL)
	{
		return NULL;
	}

	CSttMacroTestParaData *pSttMacroTestParaData = Global_FindAddMacroTestParaData(pSttMacroTest,m_pSingleMacroRef,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);

	if (pSttMacroTestParaData == NULL)
	{
		return NULL;
	}

	CString strItemID,strItemName;
	long nFaultType = CString_To_long(pSttMacroTestParaData->m_strValue);

	switch(nFaultType)
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_AN;
		strItemName = "A相接地";
		break;
	case IMPEDANCE_FAULT_TYPE_BN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BN;
		strItemName = "B相接地";
		break;
	case IMPEDANCE_FAULT_TYPE_CN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CN;
		strItemName = "C相接地";
		break;
	case IMPEDANCE_FAULT_TYPE_AB:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_AB;
		strItemName = "AB相间";
		break;
	case IMPEDANCE_FAULT_TYPE_BC:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BC;
		strItemName = "BC相间";
		break;
	case IMPEDANCE_FAULT_TYPE_CA:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CA;
		strItemName = "CA相间";
		break;
	case IMPEDANCE_FAULT_TYPE_ABN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ABN;
		strItemName = "AB相间接地";
		break;
	case IMPEDANCE_FAULT_TYPE_BCN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_BCN;
		strItemName = "BC相间接地";
		break;
	case IMPEDANCE_FAULT_TYPE_CAN:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_CAN;
		strItemName = "CA相间接地";
		break;
	case IMPEDANCE_FAULT_TYPE_ABC:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ABC;
		strItemName = "三相故障";
		break;
	case IMPEDANCE_FAULT_TYPE_ONE:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_ONE;
		strItemName = "单相故障";
		break;
	default:
		strItemID = STT_MULTI_MACRO_DISTANCE_FaultType_Items_ID_AN;
		strItemName = "A相接地";
		break;
	}

	CSttItems *pCSttItems = (CSttItems*)m_pMulitMacroRootItems->FindByID(strItemID);

	if (pCSttItems != NULL)
	{
		return pCSttItems;
	}

	CSttItems *pNewItems = new CSttItems;
	pNewItems->m_strID = strItemID;
	pNewItems->m_strName = strItemName;
	m_pMulitMacroRootItems->AddNewChild(pNewItems);
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(m_pMulitMacroRootItems, pNewItems);

    stt_Frame_GbTreeCtrl()->AddObj(pNewItems, TRUE);

	CString strParentItemPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// #ifdef _PSX_QT_WINDOWS_//zhouhj 2024.10.10 删除防止自动添加测试项
// 	g_theGbSmartGenWzd->NewItems(strParentItemPath, pNewItems);
// 	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pNewItems->m_strID, pNewItems->m_strName
// 		, pNewItems->m_nTestTimes, pNewItems->m_nRptTitle, pNewItems->m_nTitleLevel);
// #endif
	return pNewItems;
}

void QSttMultiMacroParaEditViewDistance::slot_AddOneItemBtnClick()
{
// 	int nItemNum = 0;
// 	nItemNum = m_pCurrMacroItemsRef->GetCount();
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
// 
// 	//20240626 luozibing 克隆当前编辑页面显示节点 
// 	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->CloneEx(TRUE,TRUE);
// 	CSttItems *pParent = (CSttItems *)m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->GetParent();
// 	//在其父节点后添加有不重复ID的新节点
// 	CExBaseObject *pFindID = pParent->FindByID(pNewTest->m_strID);
// 	CString strTmp,strID;
// 	int num = 0;
// 	while(pFindID != NULL)
// 	{
// 		strTmp.setNum(++num);
// 		strID = pNewTest->m_strID;
// 		strID +=strTmp;
// 		pFindID = pParent->FindByID(strID);
// 	}
// 	pNewTest->m_strID = strID;
// 
// 	//20240626 luozibing 克隆时未克隆CSttMacroTestParaData类信息
// 	if(pNewTest->GetSttMacroTestPara() == NULL)
// 	{
// 		CSttMacroTestPara *pTestPara = m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->GetSttMacroTestPara();
// 		CSttMacroTestPara *pTestPara_null = (CSttMacroTestPara *)pNewTest->FindByClassID(STTGBXMLCLASSID_CSTTMACROPARA);
// 		POS pos = pNewTest->Find(pTestPara_null);
// 		CSttMacroTestPara *pNewTestPara = (CSttMacroTestPara *)pNewTest->CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARA);
// 		pNewTest->InsertAfter(pos,pNewTestPara);
// 		pNewTestPara->SetParent(pNewTest);
// 		pNewTest->Delete(pTestPara_null);
// 		CSttMacroTestParaDatas *pNewParas = (CSttMacroTestParaDatas *)pNewTestPara->CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARADATAS);
// 		pNewTestPara->AddNewChild(pNewParas);
// 		pNewParas->AppendCloneEx((CExBaseList &)*pTestPara->GetHead());
// 	}
// 
// 	pParent->AddNewChild(pNewTest);
// 	m_oSingleMacroItemsRef.AddTail(pNewTest);
// 	
// 	m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
// 	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroParaEditGrid->rowCount());
}

void QSttMultiMacroParaEditViewDistance::slot_AddMultiItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pAddMultiItemBtn->pos(),ADDMULTIITEM_DLG);
}
void QSttMultiMacroParaEditViewDistance::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240621 luozibing 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		//m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);
		//m_pAddMultiItemSelectDlg->setFont(m_oModuleFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);
		QPushButton *pBtnAddOne_LN= new QPushButton(g_sLangTxt_Distance_AddOneLN/*添加单个区段-接地故障*/);
		QPushButton *pBtnAddOne_LL= new QPushButton(g_sLangTxt_Distance_AddOneLL/*添加单个区段-相间故障*/);
		QPushButton *pBtnAddMult= new QPushButton(g_sLangTxt_Distance_AddMult/*添加多个区段*/);

		QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem/*删除当前*/);
		QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem/*删除全部*/);

		QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult/*清除当前*/);
		QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult/*清除全部*/);

		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());

		pLayout->addWidget(pBtnAddOne_LN,0,0);
		pLayout->addWidget(pBtnAddOne_LL,1,0);
		pLayout->addWidget(pBtnAddMult,2,0);

		pLayout->addWidget(pBtnDeleteSelItem,3,0);
		pLayout->addWidget(pBtnDeleteAllItem,4,0);

		pLayout->addWidget(pBtnClearSelResult,5,0);
		pLayout->addWidget(pBtnClearAllResult,6,0);

		connect(pBtnAddOne_LN,SIGNAL(clicked()),this,SLOT(slot_AddOneLNBtnClick()));
		connect(pBtnAddOne_LL,SIGNAL(clicked()),this,SLOT(slot_AddOneLLBtnClick()));
		connect(pBtnAddMult,SIGNAL(clicked()),this,SLOT(slot_AddMultBtnClick()));

		connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
		connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

		connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
		connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
	}
	QStringList listTmp;
	switch(nDlgState)
	{
	case ADDMULTIITEM_DLG:
		listTmp.append(g_sLangTxt_Distance_AddOneLN/*添加单个区段-接地故障*/);
		listTmp.append(g_sLangTxt_Distance_AddOneLL/*添加单个区段-相间故障*/);
		listTmp.append(g_sLangTxt_Distance_AddMult/*添加多个区段*/);
		break;
	case DELETEITEM_DLG:
		listTmp.append(g_sLangTxt_Button_DeleteSelItem/*删除当前*/);
		listTmp.append(g_sLangTxt_Button_DeleteAllItem/*删除全部*/);
		break;
	case CLEARSELRESULT:
		listTmp.append(g_sLangTxt_Button_ClearSelResult/*清除当前*/);
		listTmp.append(g_sLangTxt_Button_ClearAllResult/*清除全部*/);
		break;
	}

	foreach(QPushButton* button, m_pAddMultiItemSelectDlg->findChildren<QPushButton*>()) 
	{
		//button->setFont(m_oModuleFont);
		CString strBtnText = button->text();
		if (listTmp.indexOf(strBtnText)!= -1)
		{
			button->setVisible(true);
		}
		else
		{
			button->setVisible(false);
		}
	}

	QPoint ParentPos = this->mapToGlobal(QPoint(0, 0));
	QSize DlgSize = m_pAddMultiItemSelectDlg->sizeHint();
	m_pAddMultiItemSelectDlg->move(ParentPos.x()+pos.x()-10,ParentPos.y()+pos.y()-DlgSize.height());
	m_pAddMultiItemSelectDlg->show();
}
void QSttMultiMacroParaEditViewDistance::slot_AddOneLNBtnClick()
{//20240620 luozibing 添加单项接地故障页面
	m_pAddMultiItemSelectDlg->hide();

	QDistanceAddSinglePhaseDlg oDistanceAddSinglePhaseDlg;
	//oDistanceAddSinglePhaseDlg.setFont(m_oModuleFont);
	oDistanceAddSinglePhaseDlg.SetDatas(m_pAddSinglePhase_Paras);
	/*CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras = (CDataGroup *)pTestMacroUI_Paras->Clone();
	oDistanceAddSinglePhaseDlg.SetDatas(pCurrTestMacroUI_Paras);*/

	if(oDistanceAddSinglePhaseDlg.exec() == QDialog::Accepted)
	{
		//20240722 luozibing 测试发现右边树切换后m_pTestMacroUI未改变且m_oTestMacroUI_Paras被清空
		oDistanceAddSinglePhaseDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		//UpdateCharacteristicParasToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		GetLastBinarysAndCommonToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

		CString strItemsName,strItemsID;
		long nRepeatTimes = 1,nRptTitle = 2,nTitleLevel = 3;
#ifndef SttTestCntrThread_H
		bool bGenSucc = g_theTestCntrFrame->GenerateTemplate(m_pMulitMacroRootItems, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
#else
		g_theSttTestCntrThread->m_pParentItems = m_pMulitMacroRootItems;
		g_theSttTestCntrThread->m_strItemsName = strItemsName;
		g_theSttTestCntrThread->m_strItemsID = strItemsID;
		g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
	}
	else
	{//点击取消不保存界面设置参数
		oDistanceAddSinglePhaseDlg.GetDatas(NULL);
	}
	/*pCurrTestMacroUI_Paras->DeleteAll();
	delete pCurrTestMacroUI_Paras;
	pCurrTestMacroUI_Paras = NULL;*/
}
void QSttMultiMacroParaEditViewDistance::slot_AddOneLLBtnClick()
{//20240620 luozibing 添加相间接地故障
	m_pAddMultiItemSelectDlg->hide();

	QDistanceAddInterPhaseDlg oDistanceAddInterPhaseDlg;
	//oDistanceAddInterPhaseDlg.setFont(m_oModuleFont);
	oDistanceAddInterPhaseDlg.SetDatas(m_pAddInterPhase_Paras);
	/*CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras = (CDataGroup *)pTestMacroUI_Paras->Clone();
	oDistanceAddInterPhaseDlg.SetDatas(pCurrTestMacroUI_Paras);*/

	if(oDistanceAddInterPhaseDlg.exec() == QDialog::Accepted)
	{
		oDistanceAddInterPhaseDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		//UpdateCharacteristicParasToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		GetLastBinarysAndCommonToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		CString strItemsName,strItemsID;
		long nRepeatTimes = 1,nRptTitle = 2,nTitleLevel = 3;
#ifndef SttTestCntrThread_H
		bool bGenSucc = g_theTestCntrFrame->GenerateTemplate(m_pMulitMacroRootItems, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
#else
		g_theSttTestCntrThread->m_pParentItems = m_pMulitMacroRootItems;
		g_theSttTestCntrThread->m_strItemsName = strItemsName;
		g_theSttTestCntrThread->m_strItemsID = strItemsID;
		g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
	}
	else
	{//点击取消不保存界面设置参数
		oDistanceAddInterPhaseDlg.GetDatas(NULL);
	}
	/*pCurrTestMacroUI_Paras->DeleteAll();
	delete pCurrTestMacroUI_Paras;
	pCurrTestMacroUI_Paras = NULL;*/
}
void QSttMultiMacroParaEditViewDistance::slot_AddMultBtnClick()
{
	m_pAddMultiItemSelectDlg->hide();
	//20240620 luozibing 添加多个区段页面
	QDistanceAddMultDlg oDistanceAddMultDlg;
	//oDistanceAddMultDlg.SetPageFont(m_oModuleFont);
	oDistanceAddMultDlg.SetDatas(m_pAddMult_Paras);

	//CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	//CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
 //	oDistanceAddMultDlg.SetDatas(pCurrTestMacroUI_Paras);

	if(oDistanceAddMultDlg.exec() == QDialog::Accepted)
	{
		//??????zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas
		oDistanceAddMultDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		//UpdateCharacteristicParasToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		GetLastBinarysAndCommonToAddMult(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
		CString strItemsName,strItemsID;
		long nRepeatTimes = 1,nRptTitle = 2,nTitleLevel = 3;
#ifndef SttTestCntrThread_H
		bool bGenSucc = g_theTestCntrFrame->GenerateTemplate(m_pMulitMacroRootItems, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
#else
		g_theSttTestCntrThread->m_pParentItems = m_pMulitMacroRootItems;
		g_theSttTestCntrThread->m_strItemsName = strItemsName;
		g_theSttTestCntrThread->m_strItemsID = strItemsID;
		g_theSttTestCntrThread->PostThreadMessage(10, 0, 0);
#endif
	}
	/*pCurrTestMacroUI_Paras->DeleteAll();
	delete pCurrTestMacroUI_Paras;
	pCurrTestMacroUI_Paras = NULL;*/
}
void QSttMultiMacroParaEditViewDistance::slot_CommonParasBtnClick()
{
	//20240620 luozibing 通用参数页面
	QDistanceCommonParasDlg oDistanceCommonParasDlg;
	//oDistanceCommonParasDlg.setFont(m_oModuleFont);

	oDistanceCommonParasDlg.SetDatas(((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());

	if(oDistanceCommonParasDlg.exec() == QDialog::Accepted)
	{
		CExBaseList *pItem = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
		if (pItem == NULL)
		{
			pItem = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
		}
		if (oDistanceCommonParasDlg.CheckItemsModify(&m_oSingleMacroItemsRef,pItem))
		{
			oDistanceCommonParasDlg.GetDatas(((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
			CString strZSet_Line;
			if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
			{
				CExBaseList *pItems = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
				//20240924 luozibing 更新当前编辑页面显示
				CSttMacroTestParaData *pLine = (CSttMacroTestParaData *)pItems->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
				if (pLine != NULL)
				{
					strZSet_Line = pLine->m_strValue;
				}
				CSttMacroTestParaData *pZoneType = (CSttMacroTestParaData *)pItems->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
				int nType = CString_To_long(pZoneType->m_strValue);
				if (nType == STT_MULTI_MACRO_ZONELine)//20240814 luozibing 当前选中测试项区段为线路长度 更新编辑页面
				{
					CSttMacroTestParaData *pZSeting = (CSttMacroTestParaData *)pItems->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
					if (pZSeting != NULL)
					{
						pZSeting->m_strValue = strZSet_Line;
					}
					m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
					//当前选择项改变，更新当前选择测试点
					/*AddUpdateTestPoint_To_Charact(pCurrMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
					UpdateTestPoint_To_ZTView(pCurrMacroTest, true);*/
				}
			}
			else
			{
				//通用参数修改后，修改表格中所有项数据通用参数
				oDistanceCommonParasDlg.UpdataAllCommonParas(&m_oSingleMacroItemsRef);
				POS pos = m_oSingleMacroItemsRef.GetHeadPosition();
				while (pos)
				{
					pItem = (CExBaseList*)m_oSingleMacroItemsRef.GetNext(pos);

					if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
					{
						CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pItem;
						CSttMacroTestParaDatas *pParaDatas = pSttMacroTest->GetSttMacroTestParaDatas(FALSE, "");
						if (pParaDatas != NULL)
						{
							CSttMacroTestParaData *pZSettingLine = (CSttMacroTestParaData *)pParaDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
							CSttMacroTestParaData *pZSetting = (CSttMacroTestParaData *)pParaDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
							CSttMacroTestParaData *pZoneType = (CSttMacroTestParaData *)pParaDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
							int nType = CString_To_long(pZoneType->m_strValue);
							if (nType == STT_MULTI_MACRO_ZONELine)//20240814 luozibing 测试项为线路长度时，将线路阻抗值设置给阻抗定值 更新表格 特性图 Z/T视图显示
							{
								if (fabs(CString_To_double(pZSettingLine->m_strValue) - CString_To_double(pZSetting->m_strValue)) < 0.001)
								{//线路阻抗未被修改 跳出循环
									break;
								}
								pZSetting->m_strValue = pZSettingLine->m_strValue;
								strZSet_Line = pZSetting->m_strValue;

								if (pSttMacroTest == m_pSingleItemParaEditWidget->m_pCurrMacroTest_External)
								{//20240924 luozibing 测试项为选中项时更新编辑页面 并设置对应测试点状态为选择
									m_pSingleItemParaEditWidget->UpdateParas(pSttMacroTest);
									AddUpdateTestPoint_To_Charact(pSttMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
								}
								else
								{
									m_pCurrMacroParaEditGrid->UpdateData(pSttMacroTest);
									//设置对应测试点状态为 初始状态
									AddUpdateTestPoint_To_Charact(pSttMacroTest, CHAR_TEST_OBJECT_STATE_NORMAL);
								}
								UpdateTestPoint_To_ZTView(pSttMacroTest, true);
							}
						}
					}
				}
			}
			SetAddMultiItemByZSetLine(m_pAddInterPhase_Paras, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE6, strZSet_Line);
			SetAddMultiItemByZSetLine(m_pAddSinglePhase_Paras, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE6, strZSet_Line);

			Ats_UpdateMacroTestItems();
			//m_pCurrMacroParaEditGrid->ShowDatas(&m_oSingleMacroItemsRef);
		}
	}
}
void QSttMultiMacroParaEditViewDistance::SetAddMultiItemByZSetLine(CDataGroup *pGroup, CString strID, CString strZSet_Line)
{
	if (strZSet_Line == "" || pGroup == NULL)
	{
		return;
	}
	//20241017 luozibing 设置添加系列 线路长度阻抗值参数
	CDvmData *pData = (CDvmData*)pGroup->FindByID(strID);
	if (pData == NULL)
	{
		pData = pGroup->AddNewData(strID, strZSet_Line);
	}
	else
			{
				pData->m_strValue = strZSet_Line;
			}

	CDvmData *pData_ZLine = (CDvmData*)pGroup->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
	if (pData_ZLine == NULL)
	{
		pData_ZLine = pGroup->AddNewData(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE, strZSet_Line);
		}
	else
	{
		pData_ZLine->m_strValue = strZSet_Line;
	}
}
void QSttMultiMacroParaEditViewDistance::slot_BinarysBtnClick()
{
	//20240620 luozibing 开入量、开出量页面
	QDistanceBinarysDlg oDistanceBinarysDlg;
	//oDistanceBinarysDlg.SetPageFont(m_oModuleFont);
    if(m_bDefault)
    {
        oDistanceBinarysDlg.SetDisplayedByDefault(m_bDefault);
        m_bDefault = FALSE;
    }
	oDistanceBinarysDlg.SetDatas(((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	if(oDistanceBinarysDlg.exec() == QDialog::Accepted)
	{
		CExBaseList *pItem = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
		if (pItem == NULL)
		{
			pItem = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
		}
		if (oDistanceBinarysDlg.CheckItemsModify(pItem))
		{
			oDistanceBinarysDlg.GetDatas(((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
			oDistanceBinarysDlg.UpdataAllBinarys(&m_oSingleMacroItemsRef);
			Ats_UpdateMacroTestItems();
		}
	}
}

void QSttMultiMacroParaEditViewDistance::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewDistance::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
	//20240920 luozibing 删除当前选中项后更新表格选中项显示
	CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
	if (pCurrObj == NULL)
	{
		return;
	}

	CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
	m_pCurrMacroParaEditGrid->SelectRow(pSttMacroTest);
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
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

void QSttMultiMacroParaEditViewDistance::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
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

void QSttMultiMacroParaEditViewDistance::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewDistance::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
	CSttMacroTest *pCurrSelectData = m_pCurrMacroParaEditGrid->GetCurrSelSttMacroTest();
	if (pCurrSelectData != NULL)
	{
		if (pCurrSelectData->m_nState == TEST_STATE_NORMAL)
		{
			//20241028 luozibing 清除测试结果后 更新测试点状态
			AddUpdateTestPoint_To_Charact(pCurrSelectData, CHAR_TEST_OBJECT_STATE_NORMAL);
		}
	}
	
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDistance::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
	POS pos = m_oSingleMacroItemsRef.GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTest *pData = (CSttMacroTest *)m_oSingleMacroItemsRef.GetNext(pos);
		if (pData->m_nState == TEST_STATE_NORMAL)
		{
			//20241028 luozibing 清除测试结果后 更新测试点状态 清除时当前选择测试项改变
			AddUpdateTestPoint_To_Charact(pData, CHAR_TEST_OBJECT_STATE_NORMAL);
		}
	}
	
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}


//添加测试项时,在特性曲线界面添加对应测试点
//BOOL QSttMultiMacroParaEditViewDistance::AddTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
//{
//	if (m_pCharactInterface == NULL)
//	{
//		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
//	}
//	if (m_pCharactInterface == NULL)
//	{
//		return FALSE;
//	}
//	//添加测试点
//	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetTail();
//	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
//	if(pNewDataParas == NULL)
//	{
//		return FALSE;
//	}
//	CSttMacroTestParaData *pData_ZSetting = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
//	if (pData_ZSetting == NULL)
//	{
//		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
//		pData_ZSetting = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
//	}
//	CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
//	if (pData_ZAng == NULL)
//	{
//		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
//		pData_ZAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
//	}
//	CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//系数
//	if (pData_Rate == NULL)
//	{
//		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
//		pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
//	}
//	//20240809 luozibing 通过阻抗定值和系数计算阻抗值->从阻抗角和阻抗值计算R、X
//	CString strImp;
//	double dDataZ = pData_Rate->m_strValue.toDouble()*pData_ZSetting->m_strValue.toDouble();//阻抗值
//	strImp.Format("%lf", dDataZ);
//	CString strNewR, strNewX;
//	CheckRxValue(strNewR, strNewX, strImp, pData_ZAng->m_strValue);
//	strNewR = CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, 3);//R
//	strNewX = CheckDataMinMax(strNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, 3);//X
//
//	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
//	if (pData_Fault == NULL)
//	{
//		CheckForPresence(pNewDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
//		pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
//
//	}
//	CSttMacroTestParaData *pData_Zone = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);//区段
//	if (pData_Zone == NULL)
//	{
//		CheckForPresence(pNewDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
//		pData_Zone = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);//R
//
//	}
//	m_pCharactInterface->AddUpdateTestPoint_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), strNewR.toDouble(), strNewX.toDouble(), pData_Fault->m_strValue.toInt(), pData_Zone->m_strValue.toInt());
//	return TRUE;
//}

BOOL QSttMultiMacroParaEditViewDistance::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	if (m_pCharactInterface == NULL)
	{
		return FALSE;
	}
    if(pCurrMacroTest == NULL)
    {
        return FALSE;
    }
	m_pCharactInterface->DeleteTestData(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewDistance::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	if(pDataParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[UpdateTestPoint_To_Charact]参数为空"));
		return FALSE;
	}
	CSttMacroTestParaData *pData_ZSetting = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
	if (pData_ZSetting == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		pData_ZSetting = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	}
	CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
	if (pData_ZAng == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		pData_ZAng = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
	}
	CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//系数
	if (pData_Rate == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		pData_Rate = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	}
	//20240809 luozibing 通过阻抗定值和系数计算阻抗值->从阻抗角和阻抗值计算R、X
	CString strImp;
	double dDataZ = CString_To_double(pData_Rate->m_strValue)*CString_To_double(pData_ZSetting->m_strValue);//阻抗值
	strImp.Format("%lf", dDataZ);
	CString strNewR, strNewX;
	CheckRxValue(strNewR, strNewX, strImp, pData_ZAng->m_strValue);
	strNewR = CheckDataMinMax(strNewR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3);//R
	strNewX = CheckDataMinMax(strNewX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3);//X

	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
	if (pData_Fault == NULL)
	{
		CheckForPresence(pDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	}
	CSttMacroTestParaData *pData_Zone = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);//区段
	if (pData_Zone == NULL)
	{
		CheckForPresence(pDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
		pData_Zone = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	}

	m_pCharactInterface->AddUpdateTestPoint_Imp(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), 
		CString_To_double(strNewR), CString_To_double(strNewX), CString_To_long(pData_Fault->m_strValue), CString_To_long(pData_Zone->m_strValue), nState);
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewDistance::AddItem_From_Charact(double dX, double dY)
{
	
	/*if (m_pMulitMacroRootItems == NULL)
	{
		return FALSE;
	}

	CSttItems *pParentItems = GetRootItems_CurrTestMacro(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);

	if (pParentItems == NULL)
	{
		return FALSE;
	}

	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}

	CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CString strItemPath;
	strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);*/

	//根据坐标生成新建测试项阻抗定值、时间定值、R、X
	//CSttMacroTest *pNewTest = (CSttMacroTest *)m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.Clone();
	//CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//if(pNewDataParas == NULL)
	//{
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("[AddItem_From_Charact]参数为空"));
	//	return FALSE;
	//}
	////20240809 luozibing 根据传入坐标计算阻抗值和阻抗角 通过阻抗值和阻抗定值得出系数
	//CString strR, strX;
	//strR.setNum(dX);
	//strX.setNum(dY);

	//CString strNewZ,StrNewZAng;
	//CheckZSettingAndZAng(strR, strX, strNewZ, StrNewZAng);
	//strNewZ = CheckDataMinMax(strNewZ, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, 0.001, 3);
	//CSttMacroTestParaData *pData_ZSeting = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
	//if (pData_ZSeting == NULL)
	//{
	//	CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	//	pData_ZSeting = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	//}
	//CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
	//if(pData_ZAng == NULL)
	//{
	//	CheckForPresence(pNewDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
 //       pData_ZAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
	//}
	//pData_ZAng->m_strValue = CheckDataMinMax(StrNewZAng,360,-360,1);
	//CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//阻抗角
	//if (pData_Rate == NULL)
	//{
	//	CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	//	pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	//}
	//double dRate = CString_To_double(strNewZ) / CString_To_double(pData_ZSeting->m_strValue);
	//pData_Rate->m_strValue.setNum(dRate);

	//CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
	//if(pData_Fault == NULL)
	//{
	//	CheckForPresence(pNewDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
 //       pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	//}
	//CSttMacroTestParaData *pData_Zone = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);//区段
	//if(pData_Zone == NULL)
	//{
	//	CheckForPresence(pNewDataParas,STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
 //       pData_Zone = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	//}
	//CSttMacroTestParaDatas *pParaDatas = pNewTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	//pParentItems->AddNewChild(pNewTest,TRUE);

	//long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas,pNewTest->m_strName,pNewTest->m_strID,strItemPath,0,
	//	m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DistanceTest_I);

	//if (nRet!= STT_CMD_ExecStatus_SUCCESS)
	//{
	//	pParentItems->Delete(pNewTest);
	//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("添加单个电气量测试功能执行命令失败(%ld)."),nRet);
	//	return FALSE;
	//}

	//m_pCurrMacroItemsRef->AddTail(pNewTest);
	//m_pCurrMacroParaEditGrid->InsertData(pNewTest);
	////添加测试点
	//m_pCharactInterface->AddUpdateTestPoint_Imp(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), CString_To_double(strR), CString_To_double(strX), CString_To_long(pData_Fault->m_strValue), CString_To_long(pData_Zone->m_strValue));
	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	//20241011 luozibing 修改编辑页面数据并根据编辑页面数据添加单个测试项
	CSttMacroTest *pNewTest = &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner;
	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	//根据坐标设置R X值
	CString strR, strX;
	strR.setNum(dX);
	strX.setNum(dY);
	CSttMacroTestParaData *pData_R = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RSETTING);//R
	CSttMacroTestParaData *pData_X = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_XSETTING);//X
	pData_R->m_strValue = CheckDataMinMax(strR, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3);
	pData_X->m_strValue = CheckDataMinMax(strX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MAX, STT_MULTI_MACRO_DISTANCE_PARAS_IMPVALUE_MIN, STT_MULTI_MACRO_PLACES_3);

	//根据R X值 计算阻抗角和界面显示阻抗值
	CString strNewZ,StrNewZAng;
	CheckZSettingAndZAng(strR, strX, strNewZ, StrNewZAng);
	strNewZ = CheckDataMinMax(strNewZ, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
	CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
	pData_ZAng->m_strValue = CheckDataMinMax(StrNewZAng, STT_MULTI_MACRO_ANGMAX, STT_MULTI_MACRO_ANGMIN, STT_MULTI_MACRO_ANGPLACES);

	//根据阻抗角计算出阻抗定值 20241017 luozibing
	CSttMacroTestParaData *pData_ZSeting = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
	CSttMacroTestParaData *pData_Zone = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);//区段
	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型

	if (CString_To_long(pData_Zone->m_strValue) != STT_MULTI_MACRO_ZONELine)
	{
		CSttMacroTestParaData *pData_ZSetByAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
		if (pData_ZSetByAng == NULL)
		{
			CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
			pData_ZSetByAng = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
		}
		if (abs(CString_To_double(pData_ZSetByAng->m_strValue) - CString_To_double(pData_ZAng->m_strValue)) > 0.001 )
		{//阻抗角改变 更新对应阻抗定值
			double dZSetPara = -1;
			Global_GetZSettingValueFromCharacteristics(stt_Frame_Characteristics(), CString_To_long(pData_Zone->m_strValue), CString_To_long(pData_Fault->m_strValue), \
				CString_To_double(pData_ZAng->m_strValue), dZSetPara);
			if (dZSetPara == -1 || dZSetPara == 0)
			{
				dZSetPara = 0.001;
			}
			pData_ZSeting->m_strValue.setNum(dZSetPara);
		}
		
	}

	//根据界面显示阻抗值和阻抗定值计算倍数
	CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//倍数
	double dRate = CString_To_double(strNewZ) / CString_To_double(pData_ZSeting->m_strValue);
	pData_Rate->m_strValue.setNum(dRate);

	//根据编辑页面添加测试项
	slot_AddOneItemBtnClick();
	
	//20240913 luozibing 通过特性图添加测试项后更新按键使能
	UpdateBottomBtnsEnable();
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewDistance::UpdateCurrItem_From_Charact(double dX, double dY)
{
	return FALSE;
}
void QSttMultiMacroParaEditViewDistance::UpdateCharacteristicParasToAddMult(CDataGroup *pMaroTest_UI_Paras)
{//20240813 luozibing将特性曲线编辑中设置的时间定值等参数值添加到新增测试项中
	if (pMaroTest_UI_Paras->GetCount() == 0)
	{
		return;
	}
	long nZone;
	//20240820 luozibing 当前添加系列添加区段类型为线路长度时不处理 时间定值等参数
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE6_CHECK, nZone);
	if (nZone == 1)
	{
		return;
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE6_CHECK, nZone);
	if (nZone == 1)
	{
		return;
	}

	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5, pMaroTest_UI_Paras);
	}

	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4, pMaroTest_UI_Paras);
	}
	pMaroTest_UI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK, nZone);
	if (nZone == 1)
	{
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5, pMaroTest_UI_Paras);
		CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5, pMaroTest_UI_Paras);
	}
}
//获取最新特性曲线参数并更新到界面 20240724 luozibing
void QSttMultiMacroParaEditViewDistance::UpdateParasByCharEdit()
{
	//20240927 luozibing 进入特性曲线编辑前已经选中测试项 编辑完成后仍选择进入特性曲线编辑前的测试项
	CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
	//更新特性曲线时间定值等参数到表格数据
	POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetNext(pos);
		UpdateCharacteristicParas(pMacroTest);
	}
	UpdateZoneSelDataTypes();//20240911 luozibing 初始化区段下拉框显示

	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
	if (pCurrObj != NULL)
	{
		m_pCurrMacroParaEditGrid->SelectRow((CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST));
	}
	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	UpdateParas_To_ZTView();

	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == NULL ||\
		m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner)
	{
		//表格未选中测试项 更新特性曲线时间定值到编辑界面
		UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
		m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	}
}
// 20240724 luozibing 距离保护页面更新显示对应特性曲线参数
void QSttMultiMacroParaEditViewDistance::UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest)
{
	if (pCurrMacroTest == NULL)
	{
		return;
	}

	CSttMacroTestParaDatas *pDstDatas = pCurrMacroTest->GetSttMacroTestParaDatas(FALSE,"");
	if (pDstDatas == NULL)
	{
		return;
	}
	//20240819 luozibing 曲线编辑页面点击确定后更新特性曲线图时清空了测试点 在此更新测试点
	//if (bCharChange)
	//{
	//	CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
	//	CSttMacroTest *pSttGridSel = NULL;
	//	if (pCurrObj != NULL)
	//	{
	//		pSttGridSel = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
	//	}
	//	if (pSttGridSel == pCurrMacroTest)
	//	{
	//		AddUpdateTestPoint_To_Charact(pCurrMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	//	}
	//	else
	//	{//不属于选中状态且不与内部数据相同更新测试点状态
	//		if (pCurrMacroTest != &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner)
	//		{
	//			AddUpdateTestPoint_To_Charact(pCurrMacroTest);
	//		}

	//	}
	//}

    CSttMacroTestParaData *pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	if (pDataZonePara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
		pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	}
	CSttMacroTestParaData *pDataZSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	if (pDataZSetPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		pDataZSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
	}

	//20241017 luozibing 添加系列获取线路长度值时 阻抗值为最新值但线路长度阻抗值不为最新
	CExBaseList *pDatas_Inner = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
	CSttMacroTestParaData *pDataZSetPara_Line = (CSttMacroTestParaData *)pDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
	if (pDataZSetPara_Line == NULL)
	{
		CheckForPresence(pDatas_Inner, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
		pDataZSetPara_Line = (CSttMacroTestParaData *)pDatas_Inner->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
		pDataZSetPara_Line->m_strValue.setNum(6);
	}
	CSttMacroTestParaData *pDataZPara_Line = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
	if (pDataZPara_Line == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
		pDataZPara_Line = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTINGLINE);
		pDataZPara_Line->m_strValue = pDataZSetPara_Line->m_strValue;
	}
	pDataZPara_Line->m_strValue = pDataZSetPara_Line->m_strValue;
	//没有对应的特性曲线参数显示为0
	CSttMacroTestParaData *pDataTSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
	if (pDataTSetPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
		pDataTSetPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
	}
	CSttMacroTestParaData *pDataPlusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
	if (pDataPlusPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
		pDataPlusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);
	}
	CSttMacroTestParaData *pDataMinusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
	if (pDataMinusPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
		pDataMinusPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);
	}
	CSttMacroTestParaData *pDataRelPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
	if (pDataRelPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
		pDataRelPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR);
	}

	//CSttMacroTestParaData *pDataLogicPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
	//if (pDataLogicPara == NULL)
	//{
	//	CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
	//	pDataLogicPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ERRORLOGIC);
	//}
	CSttMacroTestParaData *pDataFaultPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	if (pDataFaultPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		pDataFaultPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	}
	CSttMacroTestParaData *pData_ZSetByAng = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
	if (pData_ZSetByAng == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
		pData_ZSetByAng = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng);
	}
	if (CString_To_long(pDataZonePara->m_strValue) == STT_MULTI_MACRO_ZONELine)
	{//当前区段为线路长度时 设置线路阻抗为测试项阻抗值
		pDataZSetPara->m_strValue = CheckDataMinMax(pDataZSetPara_Line->m_strValue, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
		pData_ZSetByAng->m_strName.clear();
//		if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == pCurrMacroTest)
//		{//20241008 luozibing 阻抗定值改变 当前测试项为选中测试项时更新编辑界面
//			m_pSingleItemParaEditWidget->UpdateParas(pCurrMacroTest);
//		}
		//pDataTSetPara->m_strValue = "0.000";
		//pDataPlusPara->m_strValue = "0.000";
		//pDataMinusPara->m_strValue = "0.000";
		//pDataRelPara->m_strValue = "0.000";
		//pDataLogicPara->m_strValue = "0";
		return;
	}
	//CString strFaultType;
	//CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	//strFaultType = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pData->m_strValue));//20240906 luozibing 使用新增全局函数

	//根据故障类型和区段值查找对应曲线 并将曲线参数设置到MacroTest
	CCharacteristic *pChar = NULL;
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	POS pos = pCharacteristics->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject *pObj = pCharacteristics->GetNext(pos);
		if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharacteristic *pCharTemp = (CCharacteristic *)pObj;
		//获取勾选使用的曲线
		if (pCharTemp->m_nUse != 1)
		{
			continue;
		}
		if (pCharTemp->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL)
		{
			if (pCharTemp->m_strIndex != pDataZonePara->m_strValue)
			{
				continue;
			}
		}
		else
		{
			CString strCharID = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pDataFaultPara->m_strValue));
			if (pCharTemp->m_strID != strCharID || pCharTemp->m_strIndex != pDataZonePara->m_strValue)
			{
				continue;
			}
		}
		
		pChar = pCharTemp;

		CExBaseList* pParas = (CExBaseList*)pChar->GetCharInterface();
		//CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(strTSetingID);
		CCharInterfaceVariable *pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataTSetPara->m_strID);
		if (pPara != NULL)
		{
			pCurrMacroTest->m_nModified = 1;//20240813 luozibing 修改时间定值标记修改
			pDataTSetPara->m_strValue = CheckDataMinMax(pPara->m_strValue, 999.999, 0, 3);
		}

		pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataPlusPara->m_strID);
		if (pPara != NULL)
		{
			pCurrMacroTest->m_nModified = 1;
			pDataPlusPara->m_strValue = CheckDataMinMax(pPara->m_strValue, 999.999, 0, 3);
		}
		
		pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataMinusPara->m_strID);
		if (pPara != NULL)
		{
			pCurrMacroTest->m_nModified = 1;
			pDataMinusPara->m_strValue = CheckDataMinMax(pPara->m_strValue, 999.999, 0, 3);
		}
		
		pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataRelPara->m_strID);
		if (pPara != NULL)
		{
			pCurrMacroTest->m_nModified = 1;
			pDataRelPara->m_strValue = CheckDataMinMax(pPara->m_strValue, 999.999, 0, 3);
		}

		//20240903 luozibing 存在对应曲线参数，测试项误差类型为曲线参数值
		//pPara = (CCharInterfaceVariable*)pParas->FindByID(pDataLogicPara->m_strID);
		//if (pPara != NULL)
		//{
		//	pCurrMacroTest->m_nModified = 1;
		//	pDataLogicPara->m_strValue = pPara->m_strValue;
		//}
		break;
	}

	if (pChar == NULL&&CString_To_long(pDataZonePara->m_strValue) != 1)//未找到对应曲线且不为全部区域
	{ 
		//将测试项区段设为线路长度并设置阻抗定值为线路阻抗
		pDataZonePara->m_strValue.setNum(0);
		pDataZSetPara->m_strValue = CheckDataMinMax(pDataZSetPara_Line->m_strValue, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
		pData_ZSetByAng->m_strName.clear();
		pCurrMacroTest->m_nModified = 1;
		//设置时间定值等参数为缺省值
		//pDataTSetPara->m_strValue = "0.000";
		//pDataPlusPara->m_strValue = "0.000";
		//pDataMinusPara->m_strValue = "0.000";
		//pDataRelPara->m_strValue = "0.000";
		//pDataLogicPara->m_strValue = "0";
	}
	else if (pChar != NULL)
	{
		double dTSetPara, dZSePara, dPlusPara, dMinusPara, dRelPara, dLogicPara;
		dZSePara = -1;
		//20230906 luozibing 特性曲线修改根据区段值 故障值 角阻抗值 计算阻抗定值
		CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		
		CString strTempName = pChar->m_strID;
		strTempName += pChar->m_strIndex;
		if (pData_ZSetByAng->m_strValue != pData_ZAng->m_strValue || pData_ZSetByAng->m_strName != strTempName)
		{//阻抗角对应阻抗定值参数保存 曲线对应故障类型 曲线区段 交点角度参数，任一参数改变则重新计算交点 20241009 luozibing
			if (Global_GetZSettingValueFromCharacteristic(pChar, CString_To_double(pData_ZAng->m_strValue), dZSePara))
			{
				//保存当前交点对应数据到ZsetByZAng参数
				pData_ZSetByAng->m_strValue = pData_ZAng->m_strValue;
				pData_ZSetByAng->m_strName = pChar->m_strID;
				pData_ZSetByAng->m_strName += pChar->m_strIndex;
				if (fabs(CString_To_double(pDataZSetPara->m_strValue) - dZSePara) > 0.001&&dZSePara != -1)
				{
					pCurrMacroTest->m_nModified = 1;
					CString strTemp;
					if (dZSePara == 0)
					{
						dZSePara = STT_MULTI_MACRO_ZSet_MIN;
					}
					strTemp.setNum(dZSePara);
					pDataZSetPara->m_strValue = CheckDataMinMax(strTemp, STT_MULTI_MACRO_ZSet_MAX, STT_MULTI_MACRO_ZSet_MIN, STT_MULTI_MACRO_PLACES_3);
				}
			}
		}
	}
}
void QSttMultiMacroParaEditViewDistance::CompareTestMacroUI_Paras(CString strID, CExBaseList *pTestMacro_Paras)
{
	CString strItemId;
	if (STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2 == strID ||\
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5 == strID)
	{
		strItemId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING;
	}
	else if (STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5 == strID )
	{
		strItemId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS;
	}
	else if (STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5 == strID)
	{
		strItemId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS;
	}
	else if (STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR1 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR2 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR3 == strID || STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR4 == strID || \
		STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR5 == strID)
	{
		strItemId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_RELERR;
	}
	else
	{
		strItemId = strID;
	}
	CShortDatas *pShortDatas = m_pSingleMacroRef->GetFaultParas();
	CExBaseList *pItem = ((QDistanceItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();

	CSttMacroTestParaData *pSttMacroTestParaData = (CSttMacroTestParaData*)pItem->FindByID(strItemId);
	if (pSttMacroTestParaData == NULL)
	{
		return;
	}
	if (pTestMacro_Paras->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}
	CDataGroup *pParas = (CDataGroup*)pTestMacro_Paras;
	CDvmData *pData_Paras = (CDvmData *)pParas->FindByID(strID);
	if (pData_Paras == NULL)
	{
		CShortData *pShortData = (CShortData *)pShortDatas->FindByID(strID);
		if (pShortData != NULL)
		{
			pParas->AddNewData(pShortData->m_strName, pSttMacroTestParaData->m_strID, pShortData->m_strDataTypeID, pSttMacroTestParaData->m_strValue);
		}
	}
	else
	{
		pData_Paras->m_strValue = pSttMacroTestParaData->m_strValue;
	}
}
void QSttMultiMacroParaEditViewDistance::GetLastBinarysAndCommonToAddMult(CExBaseList *pTestMacro)
{//20240813 luozibing 将开关量与通用参数相关参数设置添加到新测试项中

	//开关量
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_BINSELECT, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_A, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_B, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_C, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_D, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_E, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_F, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_G, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_H, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B01, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B02, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B03, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B04, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B05, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B06, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B07, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__B08, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTSWITCHMODE, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTKEEPTIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID__OUTPUTDELAYTIME, pTestMacro);

	//通用参数
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_PREFAULTTIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_MINTRIPTIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TIMEAFTERTRIGGER, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_PTPOS, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_CTPOS, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOAD, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ILOADPH, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_SIMULATEBREAKERDELAY, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKBREAKTIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_BRKCLOSETIME, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZDEFINE, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPHDEFINE, pTestMacro);
	CompareTestMacroUI_Paras(STT_MULTI_MACRO_DISTANCE_PARAS_ID_VZPH, pTestMacro);
}
//20240813 wanmj 移到基类
//bool QSttMultiMacroParaEditViewDistance::eventFilter(QObject *target, QEvent *event)
//{
//    //20240729 luozibing 点击表格空白处，取消选中
//    QMouseEvent *e = static_cast<QMouseEvent *>(event);
//    if(target == m_pCurrMacroParaEditGrid->viewport() &&(e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease))
//    {
//       QPoint point = e->pos();
//        // 根据鼠标坐标，获取此时鼠标按下时所在的行、列
//       QModelIndex index = m_pCurrMacroParaEditGrid->indexAt(point);
//       m_pCurrMacroParaEditGrid->item(index.row(), index.column());
//       if (m_pCurrMacroParaEditGrid->item(index.row(), index.column()) == nullptr)
//       {
//            //取消选中
//            m_pCurrMacroParaEditGrid->setCurrentItem(NULL);
//            m_pSingleItemParaEditWidget->UpdateParas(NULL);
//        }
//    }
//    return QWidget::eventFilter(target, event);
//}
void QSttMultiMacroParaEditViewDistance::UpdateParas_To_ZTView()
{//20240809 luozibing 从m_oTestMacroUI_Paras更新ZT视图折线显示
	if (m_pZTViewInterface == NULL)
	{
		m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
	}
	//20240925 luozibing 根据当前选中测试项故障类型判断
	CString strFaultType;
	CSttMacroTest *pSttMacroTest = NULL;
	pSttMacroTest = &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner;
	//CExBaseObject *pCurrObj = m_pCurrMacroParaEditGrid->GetCurrSelData();
	//if (pCurrObj != NULL)
	//{
	//	pSttMacroTest = (CSttMacroTest*)pCurrObj->GetAncestor(STTGBXMLCLASSID_CSTTMACROTEST);
	//}
	//else
	//{//未选中测试项 显示编辑页面选择故障类型
	//	
	//}

	CSttMacroTestParaDatas *pDstDatas = pSttMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pData_ZAng = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
	if (pData_ZAng == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		pData_ZAng = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);

	}

	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
	if (pData_Fault == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		pData_Fault = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);

	}
	strFaultType = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pData_Fault->m_strValue));

	CString arrName[10];
	double arrZSet[10] = { 0 };
	double arrTSet[10] = { 0 };
	double arrPlus[10] = { 0 };
	double arrMinus[10] = { 0 };
	Update_FaultTypeParas_To_ZTView(pDstDatas,strFaultType, pData_ZAng->m_strValue, arrName, arrZSet, arrTSet, arrPlus, arrMinus);
	m_pZTViewInterface->UpdateZTViewDraw(arrName, arrZSet, arrTSet, arrPlus, arrMinus);

	CString strFault = GetFaultNameByID(pDstDatas);
	m_pZTViewInterface->SetAngleAndFaultype(pData_ZAng->m_strValue, strFault);
}
void QSttMultiMacroParaEditViewDistance::Update_FaultTypeParas_To_ZTView(CSttMacroTestParaDatas *pDstDatas,CString strFaultType, CString strZAng, CString arrName[], double arrZSet[], double arrTSet[], double arrPlus[], double arrMinus[])
{
	//CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	//if (strFaultType == CHAR_DISTANCE_FAULT_TYPE_LN)
	//{
	//	arrName[0] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE1_CHECK;//接地故障-I段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE1, arrZSet[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE1, arrTSet[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1, arrPlus[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1, arrMinus[0]);
	//	arrName[1] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE2_CHECK;//接地故障-II段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE2, arrZSet[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE2, arrTSet[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2, arrPlus[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2, arrMinus[1]);
	//	arrName[2] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE3_CHECK;//接地故障-III段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE3, arrZSet[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE3, arrTSet[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3, arrPlus[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3, arrMinus[2]);
	//	arrName[3] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE4_CHECK; // 接地故障 - IV段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE4, arrZSet[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE4, arrTSet[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4, arrPlus[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4, arrMinus[3]);
	//	arrName[4] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LNZONE5_CHECK;//接地故障-V段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLN_ZONE5, arrZSet[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLN_ZONE5, arrTSet[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5, arrPlus[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5, arrMinus[4]);
	//}
	//else if (strFaultType == CHAR_DISTANCE_FAULT_TYPE_LL)
	//{
	//	arrName[0] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE1_CHECK;//相间故障-I段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE1, arrZSet[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE1, arrTSet[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS1, arrPlus[0]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS1, arrMinus[0]);
	//	arrName[1] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE2_CHECK;//相间故障-II段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE2, arrZSet[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE2, arrTSet[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS2, arrPlus[1]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS2, arrMinus[1]);
	//	arrName[2] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE3_CHECK;//相间故障-III段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE3, arrZSet[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE3, arrTSet[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS3, arrPlus[2]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS3, arrMinus[2]);
	//	arrName[3] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE4_CHECK; // 相间故障 - IV段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE4, arrZSet[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE4, arrTSet[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS4, arrPlus[3]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS4, arrMinus[3]);
	//	arrName[4] = STT_MULTI_MACRO_DISTANCE_PARAS_ID_LLZONE5_CHECK;//相间故障-V段
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETINGLL_ZONE5, arrZSet[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETINGLL_ZONE5, arrTSet[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS5, arrPlus[4]);
	//	pTestMacroUI_Paras->GetDataValue(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS5, arrMinus[4]);
	//}
	//20240924 luozibing 根据特性曲线编辑参数设置Z/T视图折线
	//获取对应曲线中阻抗定值 1.获取阻抗角 2.计算阻抗角对应线段之间的交点 3.根据交点得出阻抗定值
	double dZAng = CString_To_double(strZAng);
	double dZSet = -1;
	CCharacteristics* pCharacteristics = stt_Frame_Characteristics();
	POS pos = pCharacteristics->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseObject *pObj = pCharacteristics->GetNext(pos);
		if (pObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharacteristic *pCharTemp = (CCharacteristic *)pObj;
		//获取勾选使用的曲线
		if (pCharTemp->m_nUse != 1)
		{
			continue;
		}
		//获取故障类型相同的曲线
		if (pCharTemp->m_strID != CHAR_DISTANCE_FAULT_TYPE_ALL&&pCharTemp->m_strID != strFaultType)
		{
			continue;
		}
		int nZone = CString_To_long(pCharTemp->m_strIndex);
		CString strNodeId;
		strNodeId = STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZsetByZAng;
		strNodeId += "_";
		strNodeId += strFaultType;
		strNodeId += pCharTemp->m_strIndex;

		if (m_pAddMult_Paras == NULL)
		{
			return;
		}
		CDvmData *pPara_ZSetByAng = (CDvmData *)m_pAddMult_Paras->FindByID(strNodeId);
		if (pPara_ZSetByAng == NULL)
		{
			pPara_ZSetByAng = new CDvmData();
			pPara_ZSetByAng->m_strID = strNodeId;
			m_pAddMult_Paras->AddNewChild(pPara_ZSetByAng);
		}
		CString strTemp;
		if (pPara_ZSetByAng->m_strValue != strZAng)
		{//角度改变重新计算交点
			Global_GetZSettingValueFromCharacteristic(pCharTemp, dZAng, dZSet);
			pPara_ZSetByAng->m_strValue = strZAng;
			pPara_ZSetByAng->m_strFormat.setNum(dZSet);
		}
		else
		{
			dZSet = CString_To_double(pPara_ZSetByAng->m_strFormat);
		}
		
		//判断阻抗定值是否有效
		if (dZSet == 0)
		{//有效但为0 设置为最小值
			dZSet = 0.001;
		}
		else if (dZSet == -1)
		{//无效设置为0
			dZSet = 0;
		}

		CExBaseList* pParas = (CExBaseList*)pCharTemp->GetCharInterface();
		CCharInterfaceVariable *pPara_T = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);//时间定值
		CCharInterfaceVariable *pPara_P = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_PLUS);//正误差
		CCharInterfaceVariable *pPara_N = (CCharInterfaceVariable*)pParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ABSERR_MINUS);//负误差

		//2024-10-12 wuxinyi 该参数为null中断问题
		if (!(pPara_T && pPara_P && pPara_N))
		{
			return;
		}

		CString strZoneName = strFaultType;
		strZoneName += "_";
		strZoneName += pCharTemp->m_strIndex;//区段标识
		switch (nZone)
		{
		case STT_MULTI_MACRO_ZONE1://I段
			arrName[0] = strZoneName;//区段标识
			arrZSet[0] = dZSet;//阻抗定值 X轴坐标
			arrTSet[0] = CString_To_double(pPara_T->m_strValue);//时间定值 Y轴坐标
			arrPlus[0] = CString_To_double(pPara_P->m_strValue);//正误差	左侧误差虚线
			arrMinus[0] = CString_To_double(pPara_N->m_strValue);//负误差	右侧误差虚线
			break;
		case STT_MULTI_MACRO_ZONE2://II段
			arrName[1] = strZoneName;//区段标识
			arrZSet[1] = dZSet;//阻抗定值 X轴坐标
			arrTSet[1] = CString_To_double(pPara_T->m_strValue);//时间定值 Y轴坐标
			arrPlus[1] = CString_To_double(pPara_P->m_strValue);//正误差	左侧误差虚线
			arrMinus[1] = CString_To_double(pPara_N->m_strValue);//负误差	右侧误差虚线
			break;
		case STT_MULTI_MACRO_ZONE3://III段
			arrName[2] = strZoneName;//区段标识
			arrZSet[2] = dZSet;//阻抗定值 X轴坐标
			arrTSet[2] = CString_To_double(pPara_T->m_strValue);//时间定值 Y轴坐标
			arrPlus[2] = CString_To_double(pPara_P->m_strValue);//正误差	左侧误差虚线
			arrMinus[2] = CString_To_double(pPara_N->m_strValue);//负误差	右侧误差虚线
			break;
		case STT_MULTI_MACRO_ZONE4://IV段
			arrName[3] = strZoneName;//区段标识
			arrZSet[3] = dZSet;//阻抗定值 X轴坐标
			arrTSet[3] = CString_To_double(pPara_T->m_strValue);//时间定值 Y轴坐标
			arrPlus[3] = CString_To_double(pPara_P->m_strValue);//正误差	左侧误差虚线
			arrMinus[3] = CString_To_double(pPara_N->m_strValue);//负误差	右侧误差虚线
			break;
		case STT_MULTI_MACRO_ZONE5://V段
			arrName[4] = strZoneName;//区段标识
			arrZSet[4] = dZSet;//阻抗定值 X轴坐标
			arrTSet[4] = CString_To_double(pPara_T->m_strValue);//时间定值 Y轴坐标
			arrPlus[4] = CString_To_double(pPara_P->m_strValue);//正误差	左侧误差虚线
			arrMinus[4] = CString_To_double(pPara_N->m_strValue);//负误差	右侧误差虚线
			break;
		}
	}
}
BOOL QSttMultiMacroParaEditViewDistance::AddTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)//添加测试项时,在ZT视图界面添加对应测试点
{
	if (m_pZTViewInterface == NULL)
	{
		m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
	}
	//添加测试点
	CSttMacroTest *pNewTest = (CSttMacroTest *)m_pCurrMacroItemsRef->GetTail();
	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pNewDataParas == NULL)
	{
		return FALSE;
	}
	
	CSttMacroTestParaData *pData_Z = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
	if (pData_Z == NULL)
	{
		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		pData_Z = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值

	}
	CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//系数
	if (pData_Rate == NULL)
	{
		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		pData_Rate = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);

	}
	double dDataZ = CString_To_double(pData_Rate->m_strValue)*CString_To_double(pData_Z->m_strValue);
	CSttMacroTestParaData *pData_T = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);//时间定值
	if (pData_T == NULL)
	{
		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
		pData_T = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);

	}
	CSttMacroTestParaData *pData_Zang = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
	if (pData_Zang == NULL)
	{
		CheckForPresence(pNewDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
		pData_Zang = (CSttMacroTestParaData *)pNewDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);

	}
	m_pZTViewInterface->AddOneTestPoint(pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), GetFaultNameByID(pNewDataParas), dDataZ, CString_To_double(pData_T->m_strValue));
	return TRUE;
}
BOOL QSttMultiMacroParaEditViewDistance::DeleteTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest)
{
	if (m_pZTViewInterface == NULL)
	{
		m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
	}
	if (pCurrMacroTest == NULL)
	{
		return FALSE;
	}
	m_pZTViewInterface->DeleteTestPoint(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	return TRUE;
}
CString QSttMultiMacroParaEditViewDistance::GetFaultNameByID(CSttMacroTestParaDatas *pDataParas)
{
	if (pDataParas == NULL)
	{
		return "";
	}
	CSttMacroTestParaData *pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);//故障类型
	if (pData_Fault == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		pData_Fault = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);

	}
	CString strFault;
	CDataType *pFaultType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemFault);
	if (pFaultType != NULL)
	{
		CExBaseObject *pType = pFaultType->GetAt(CString_To_long(pData_Fault->m_strValue));
		if (pType != NULL)
		{
			strFault = pType->m_strName;
			return strFault;
		}
	}
	return "";
}
BOOL QSttMultiMacroParaEditViewDistance::UpdateTestPoint_To_ZTView(CSttMacroTest *pCurrMacroTest, bool bSelPoint)
{
	if (m_pZTViewInterface == NULL)
	{
		m_pZTViewInterface = g_theTestCntrFrame->GetInternationalZTViewInterface();
	}
	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pDataParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[UpdateTestPoint_To_ZTView]参数为空"));
		return FALSE;
	}
	CSttMacroTestParaData *pData_Z = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值
	if (pData_Z == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);
		pData_Z = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZSETTING);//阻抗定值

	}
	CSttMacroTestParaData *pData_Rate = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);//系数
	if (pData_Rate == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		pData_Rate = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);

	}
	double dDataZ = CString_To_double(pData_Rate->m_strValue)* CString_To_double(pData_Z->m_strValue);
	CSttMacroTestParaData *pData_T = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);//时间定值
	if (pData_T == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);
		pData_T = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_TSETTING);

	}
	CString strFault = GetFaultNameByID(pDataParas);
	if (bSelPoint)
	{
		CSttMacroTestParaData *pData_Zang = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);//阻抗角
		if (pData_Zang == NULL)
		{
			CheckForPresence(pDataParas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);
			pData_Zang = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZANG);

		}
		m_pZTViewInterface->SetAngleAndFaultype(pData_Zang->m_strValue, strFault);
	}
	m_pZTViewInterface->UpdateTestPoint(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), strFault, dDataZ, CString_To_double(pData_T->m_strValue), bSelPoint);
	return TRUE;
}
void QSttMultiMacroParaEditViewDistance::slot_Grid_To_ParaEditWidget(CSttMacroTest* pMacroTest)
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
	SetMacroTestNameByParas(pMacroTest);
	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == pMacroTest&&pMacroTest->m_nModified == 1)
	{//20241010 luozibing 当前测试项为选中测试项 且 测试项值改变更新编辑界面
		m_pSingleItemParaEditWidget->UpdateParas(pMacroTest);
	}
	else
	{
	m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);
	}
	//m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);
	
	AddUpdateTestPoint_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	UpdateTestPoint_To_ZTView(pMacroTest, true);
	//UpdateTestUI_To_Charact(pMacroTest, XDRAW_TEST_STATE_SELECT);
}
//参数编辑界面修改后,更新到当前选择表格
void QSttMultiMacroParaEditViewDistance::slot_ParaEditWidget_To_Grid(CSttMacroTest* pMacroTest)
{
	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == &m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner || pMacroTest == NULL)
	{//20241012 luozibing 未选中测试项或选中测试为编辑界面数据时 获取曲线相关数据并更新
		UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
		UpdateCharacterisByFaultType();
		UpdateParas_To_ZTView();
		m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
		return;
	}
	pMacroTest->m_nModified = 1;
	UpdateCharacteristicParas(pMacroTest);
	if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External == pMacroTest&&pMacroTest->m_nModified == 1)
	{
		m_pSingleItemParaEditWidget->UpdateParas(pMacroTest);
	}
	SetMacroTestNameByParas(pMacroTest);//20240920 luozibing 根据参数设置测试项Name
	m_pCurrMacroParaEditGrid->UpdateData(pMacroTest);
	AddUpdateTestPoint_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
	UpdateTestPoint_To_ZTView(pMacroTest, true);
	UpdateParas_To_ZTView();//20240925 luozibing 设置故障类型后更新Z/T视图折线图
	UpdateTestUI_To_Charact(pMacroTest, CHAR_TEST_OBJECT_STATE_SELECT);
}
void QSttMultiMacroParaEditViewDistance::SetMacroTestNameByParas(CSttMacroTest *pMacroTest)
{
	//根据测试项参数拼接Name,规则为【[方向][故障类型][倍数][区段]】
	//在添加单个测试项 添加系列生成测试项 表格数据修改 编辑界面修改 时调用
	CSttMacroTestParaDatas *pDstDatas = pMacroTest->GetSttMacroTestParaDatas(FALSE, "");
	if (pDstDatas == NULL)
	{
		return;
	}

	CString strDirection, strPermanent, strRate, strZone, strNewID;
	CDataType *pDataType = NULL;
	CDataTypeValue *pValue = NULL;
	CSttMacroTestParaData *pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	if (pDataZonePara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
		pDataZonePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_ZONETYPE);
	}
	CSttMacroTestParaData *pDataFaultTypePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	if (pDataFaultTypePara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
		pDataFaultTypePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	}
	CString strFaultType;
	strFaultType = Global_GetCharFaultTypeStringByFaultType(CString_To_long(pDataFaultTypePara->m_strValue));//20240906 luozibing 使用新增全局函数

	CString strTypeId = STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemZone;
	strTypeId += "_";
	strTypeId += strFaultType;
	pDataType = (CDataType *)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(strTypeId);
	if (pDataType == NULL)
	{
		return;
	}
	pValue = pDataType->FindByIndex(pDataZonePara->m_strValue);
	if (pValue == NULL)
	{
		return;
	}
	strZone = pValue->m_strName;

	CSttMacroTestParaData *pDataDirectionPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION);
	if (pDataDirectionPara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION);
		pDataDirectionPara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTDIRECTION);
	}

	CSttMacroTestParaData *pDataRatePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	if (pDataRatePara == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
		pDataRatePara = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_RATE);
	}

	pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(pDataDirectionPara->m_strID);
	pValue = pDataType->FindByIndex(pDataDirectionPara->m_strValue);
	strDirection = pValue->m_strName;

	pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_PARAS_DATATYPE_ID_SystemFault);
	pValue = pDataType->FindByIndex(pDataFaultTypePara->m_strValue);
	strPermanent = pValue->m_strName;

	strRate = CheckDataMinMax(pDataRatePara->m_strValue, 999.999, 0, 2);
	strRate += g_sLangTxt_Native_Multiple.left(1);

	
	strNewID = strDirection;
	strNewID += strPermanent;
	strNewID += strRate;
	strNewID += strZone;
	pMacroTest->m_strName = strNewID;
}
void QSttMultiMacroParaEditViewDistance::UpdateCharacterisByFaultType()
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	if (m_pCharactInterface == NULL)
	{
		return;
	}
	CSttMacroTestParaDatas *pSttMacroTestParaDatas = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pSttMacroTestParaDatas == NULL)
	{
		return;
	}
	CSttMacroTestParaData *pDataInner_Fault = (CSttMacroTestParaData *)pSttMacroTestParaDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTYPE);
	if (pDataInner_Fault != NULL)
	{
		m_pCharactInterface->UpdateCharacterisByFaultType(CString_To_long(pDataInner_Fault->m_strValue));
	}
}
void QSttMultiMacroParaEditViewDistance::OnViewTestStart()
{
	//20241012 luozibing 当前故障触发方式为手动触发时 使能状态栏手动触发按键
	CSttMacroTestParaDatas *pSttMacroTestParaDatas = m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pSttMacroTestParaDatas == NULL)
	{
		return;
	}
	CSttMacroTestParaData *pDataInner_FaultTrigMode = (CSttMacroTestParaData *)pSttMacroTestParaDatas->FindByID(STT_MULTI_MACRO_DISTANCE_PARAS_ID_FAULTTRIGMODE);
	if (CString_To_long(pDataInner_FaultTrigMode->m_strValue) == 1)
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger, true, true);
	}
	else
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger, false, true);
	}
	QSttMultiMacroParaEditViewBase::OnViewTestStart();
}
