#include "SttMultiMacroParaEditViewLowFreq.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif
QSttMultiMacroParaEditViewLowFreq::QSttMultiMacroParaEditViewLowFreq(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
	m_pParas = NULL;
	m_strTabTitleList.clear();
    m_strTabTitleList << /*"动作值"*/g_sLangTxt_State_ActionValue << /*"动作时间"*/g_sLangTxt_Gradient_ActionTime
                      << /*"滑差闭锁值"*/g_sLangTxt_Native_sliptripValue << /*"低电压闭锁值"*/g_sLangTxt_LowFreq_ULock
                      << /*"低电流闭锁值"*/g_sLangTxt_LowFreq_ILock;


	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowFreqAct,&m_oMultiMacroItemsRef[LOWFREQ_ID_PsuLowFreqAct],m_pMultiRootItems[LOWFREQ_ID_PsuLowFreqAct]);
	m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqAct] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowFreqAct);
	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowFreqTime,&m_oMultiMacroItemsRef[LOWFREQ_ID_PsuLowFreqTime],m_pMultiRootItems[LOWFREQ_ID_PsuLowFreqTime]);
	m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqTime] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowFreqTime);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowFreqDfdt,&m_oMultiMacroItemsRef[LOWFREQ_ID_PsuLowFreqDfdt],m_pMultiRootItems[LOWFREQ_ID_PsuLowFreqDfdt]);
	m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqDfdt] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowFreqDfdt);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowFreqULock,&m_oMultiMacroItemsRef[LOWFREQ_ID_PsuLowFreqULock],m_pMultiRootItems[LOWFREQ_ID_PsuLowFreqULock]);
	m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqULock] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowFreqULock);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowFreqILock,&m_oMultiMacroItemsRef[LOWFREQ_ID_PsuLowFreqILock],m_pMultiRootItems[LOWFREQ_ID_PsuLowFreqILock]);
	m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqILock] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowFreqILock);

	m_pGridInst_ActValue = NULL;
	m_pGridInst_ActTime = NULL;
	m_pGridInst_SlipTrip = NULL;
	m_pGridInst_VBlock = NULL;
	m_pGridInst_IBlock = NULL;

}

QSttMultiMacroParaEditViewLowFreq::~QSttMultiMacroParaEditViewLowFreq()
{
}

void QSttMultiMacroParaEditViewLowFreq::InitUI_OneMacro()
{
    //m_pSingleItemParaEditWidget = new QLowFreqItemParaEditWidget();
    m_pMultiItemParaEditWidget[LOWFREQ_ID_PsuLowFreqAct] = new QLowFreqActItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWFREQ_ID_PsuLowFreqTime] = new QLowFreqTimeItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWFREQ_ID_PsuLowFreqDfdt] = new QLowFreqDfdtItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWFREQ_ID_PsuLowFreqULock] = new QLowFreqULockItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWFREQ_ID_PsuLowFreqILock] = new QLowFreqILockItemParaEditWidget();
	m_pMultiItemStackedWidget = new QStackedWidget();
    
	CString strText;
	strText = /*功能参数*/g_sLangTxt_Diff_FuncParas;
	m_pSingleItemEditTab->insertTab(0,m_pMultiItemStackedWidget,strText);

	//20240624 luozibing 测试使用传入GOOSE发布信息
// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
// 
// 	strText = "GOOSE发布";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
	strText = /*添加测试项*/g_sLangTxt_Button_AddOneItem;
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = /*添加系列*/g_sLangTxt_Button_AddMultiItem;
	m_pAddMultiItemBtn = new QPushButton(strText);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
}

void QSttMultiMacroParaEditViewLowFreq::InitUI_MultiMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(m_strTabTitleList);
	InitUI_OneMacro();
}
void QSttMultiMacroParaEditViewLowFreq::InitDatas(CSttItems *pCurrRootItems)
{
    DisConnectAll_SigSlot();
	m_pGridInst_ActValue = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowFreqAct,STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTVALUE);
	m_pGridInst_ActTime = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowFreqTime,STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTTIME);
	m_pGridInst_SlipTrip = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowFreqDfdt,STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_SLIPTRIP);
	m_pGridInst_VBlock = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowFreqULock,STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_VBLOCK);
	m_pGridInst_IBlock = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowFreqILock,STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_IBLOCK);
	InitGridTitleLanguage();    //表格表头多语言处理
	m_pMultiMacroParaEditGrid[LOWFREQ_ID_PsuLowFreqAct]->InitColDef(m_pGridInst_ActValue,m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqAct],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWFREQ_ID_PsuLowFreqTime]->InitColDef(m_pGridInst_ActTime,m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqTime],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWFREQ_ID_PsuLowFreqDfdt]->InitColDef(m_pGridInst_SlipTrip,m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqDfdt],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWFREQ_ID_PsuLowFreqULock]->InitColDef(m_pGridInst_VBlock,m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqULock],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWFREQ_ID_PsuLowFreqILock]->InitColDef(m_pGridInst_IBlock,m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqILock],g_theHtmlRptGenFactory->m_pDataTypes);
	if (m_pSingleMacroRef == NULL)
	{
		m_pSingleMacroRef = m_pMultiMacroRef[LOWFREQ_ID_PsuLowFreqAct];
	}
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);

	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		if (m_pMultiMacroParaEditGrid[i] != NULL)
		{
			m_pMultiMacroParaEditGrid[i]->InitGrid();
			m_pMultiItemParaEditWidget[i]->InitDatas(m_pMultiMacroRef[i]);
			m_pMultiItemStackedWidget->addWidget((QWidget*)m_pMultiItemParaEditWidget[i]);
		}
	}
	if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("请添加测试项！"));//在初始化没有测试项时提示；
	}
	ConnectAll_SigSlot();
	slot_CurrMacroParaEditGridChanged(LOWFREQ_ID_PsuLowFreqAct);
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);
	
}

void QSttMultiMacroParaEditViewLowFreq::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();

    connect(m_pMultiMacroGridTab,SIGNAL(currentChanged(int)),this,SLOT(slot_CurrMacroParaEditGridChanged(int)));
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		connect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	}
	
}

void QSttMultiMacroParaEditViewLowFreq::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		disconnect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	}
}
//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewLowFreq::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
	//return QSttMultiMacroParaEditViewBase::GetRootItems_CurrTestMacro(pSttMacroTest);

	if (pSttMacroTest == NULL)
	{
		return NULL;
	}

	if (m_pMulitMacroRootItems == NULL)
	{
		return NULL;
	}

	CString strItemID,strItemName;

	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case LOWFREQ_ID_PsuLowFreqAct:
		strItemID = STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTVALUE;
		strItemName = /*动作值*/g_sLangTxt_State_ActionValue;
		break;
	case LOWFREQ_ID_PsuLowFreqTime:
		strItemID = STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_ACTTIME;
		strItemName = /*动作时间*/g_sLangTxt_Gradient_ActionTime;
		break;
	case LOWFREQ_ID_PsuLowFreqDfdt:
		strItemID = STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_SLIPTRIP;
		strItemName = /*滑差闭锁值*/g_sLangTxt_Native_sliptripValue;
		break;
	case LOWFREQ_ID_PsuLowFreqULock:
		strItemID = STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_VBLOCK;
		strItemName = /*低电压闭锁值*/g_sLangTxt_LowFreq_ULock;
		break;
	case LOWFREQ_ID_PsuLowFreqILock:
		strItemID = STT_MULTI_MACRO_LOWFREQ_PARAS_GRID_ID_IBLOCK;
		strItemName = /*低电流闭锁值*/g_sLangTxt_LowFreq_ILock;
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

	g_theTestCntrFrame->m_pSttGbTreeView->m_pTreeCtrl->AddObj(pNewItems, TRUE);

	CString strParentItemPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// #ifdef _PSX_QT_WINDOWS_//zhouhj 2024.10.10 删除防止自动添加测试项
// 	g_theGbSmartGenWzd->NewItems(strParentItemPath, pNewItems);
// 	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pNewItems->m_strID, pNewItems->m_strName
// 		, pNewItems->m_nTestTimes, pNewItems->m_nRptTitle, pNewItems->m_nTitleLevel);
// #endif
	return pNewItems;
}

void QSttMultiMacroParaEditViewLowFreq::slot_AddMultiItemBtnClick()
{
	QLowFrepAddMultDlg oLowFrepAddMultDlg;

	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras = (CDataGroup*)pTestMacroUI_Paras->Clone();
	pCurrTestMacroUI_Paras->Copy(&oLowFrepAddMultDlg.m_oLowFrepDataGroup);
	oLowFrepAddMultDlg.InitDatas();

	if(oLowFrepAddMultDlg.exec() == QDialog::Accepted)
	{
		//??????zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas
		//CDataGroup *pTestMacroUI_Paras = &g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras;
        //pTestMacroUI_Paras = (CDataGroup *)oLowFrepAddMultDlg.m_oLowFrepDataGroup.Clone();
        g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.RemoveAll();
		oLowFrepAddMultDlg.GetBinarysParas(m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());//统一开关量
        oLowFrepAddMultDlg.m_oLowFrepDataGroup.Copy(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

		//oLowFrepAddMultDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
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
}
void QSttMultiMacroParaEditViewLowFreq::slot_CommonParasBtnClick()
{
	//20240620 luozibing 通用参数页面
	QLowFreqCommonParasDlg oLowFreqCommonParasDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case LOWFREQ_ID_PsuLowFreqAct:
        oLowFreqCommonParasDlg.SetDatas(((QLowFreqActItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowFreqCommonParasDlg.GetDatas(((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
				//oLowFreqCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqTime:
        oLowFreqCommonParasDlg.SetDatas(((QLowFreqTimeItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowFreqCommonParasDlg.GetDatas(((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowFreqCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqDfdt:
        oLowFreqCommonParasDlg.SetDatas(((QLowFreqDfdtItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowFreqCommonParasDlg.GetDatas(((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowFreqCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqULock:
        oLowFreqCommonParasDlg.SetDatas(((QLowFreqULockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowFreqCommonParasDlg.GetDatas(((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowFreqCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				//切换界面相电压和线电压
				QLowFreqULockItemParaEditWidget *m_pULockItemParaEditWidget = (QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget;
				m_pULockItemParaEditWidget->USetModeChange(oLowFreqCommonParasDlg.m_nVType);
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqILock:
        oLowFreqCommonParasDlg.SetDatas(((QLowFreqILockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
			}
            if (oLowFreqCommonParasDlg.CheckItemsModify(pItem))
			{
                //oLowFreqCommonParasDlg.GetDatas(((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
				//oLowFreqCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
				Ats_UpdateMacroTestItems();
            }
		}
		break;
	}
}

void QSttMultiMacroParaEditViewLowFreq::slot_BinarysBtnClick()
{
	//20240620 luozibing 开入量、开出量页面
	QLowFreqBinarysDlg oLowFreqBinarysDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case LOWFREQ_ID_PsuLowFreqAct:
        oLowFreqBinarysDlg.SetDatas(((QLowFreqActItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowFreqBinarysDlg.GetDatas(((QLowFreqActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowFreqBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqTime:
        oLowFreqBinarysDlg.SetDatas(((QLowFreqTimeItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowFreqBinarysDlg.GetDatas(((QLowFreqTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowFreqBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqDfdt:
        oLowFreqBinarysDlg.SetDatas(((QLowFreqDfdtItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowFreqBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowFreqBinarysDlg.GetDatas(((QLowFreqDfdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowFreqBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
		break;
	case LOWFREQ_ID_PsuLowFreqULock:
        oLowFreqBinarysDlg.SetDatas(((QLowFreqULockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
			if (oLowFreqBinarysDlg.CheckItemsModify(pItem))
			{
				//oLowFreqBinarysDlg.GetDatas(((QLowFreqULockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oLowFreqBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
				Ats_UpdateMacroTestItems();
			}
        }
		break;
	case LOWFREQ_ID_PsuLowFreqILock:
        oLowFreqBinarysDlg.SetDatas(((QLowFreqILockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowFreqBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
			}
            if (oLowFreqBinarysDlg.CheckItemsModify(pItem))
			{
                //oLowFreqBinarysDlg.GetDatas(((QLowFreqILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowFreqBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowFreqBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowFreqBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				
            }
        }
		break;
	}
}

void QSttMultiMacroParaEditViewLowFreq::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewLowFreq::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewLowFreq::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240621 luozibing 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		//m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);

        QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem);
        QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem);

        QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult);
        QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult);

		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());


		pLayout->addWidget(pBtnDeleteSelItem,3,0);
		pLayout->addWidget(pBtnDeleteAllItem,4,0);

		pLayout->addWidget(pBtnClearSelResult,5,0);
		pLayout->addWidget(pBtnClearAllResult,6,0);

		connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
		connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

		connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
		connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
	}
	QStringList listTmp;
	switch(nDlgState)
	{
	case DELETEITEM_DLG:
        listTmp.append(g_sLangTxt_Button_DeleteSelItem);
        listTmp.append(g_sLangTxt_Button_DeleteAllItem);
		break;
	case CLEARSELRESULT:
        listTmp.append(g_sLangTxt_Button_ClearSelResult);
        listTmp.append(g_sLangTxt_Button_ClearAllResult);
		break;
	}

    foreach(QPushButton* button, m_pAddMultiItemSelectDlg->findChildren<QPushButton*>())
	{
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

void QSttMultiMacroParaEditViewLowFreq::slot_CurrMacroParaEditGridChanged(int index)//当前显示测试项表格改变
{

	if (m_pMultiMacroParaEditGrid[index]  == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("切换测试功能失败，功能参数配置文件缺失"));
		return ;
	}

	if (m_pMultiMacroRef[index]  == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("切换项目功能失败，TestMacro.xml未包含该测试功能"));
		return ;
	}

	m_pSingleItemParaEditWidget = m_pMultiItemParaEditWidget[index];

	m_pMultiItemStackedWidget->setCurrentIndex(index);
	m_pCurrMacroItemsRef = &m_oMultiMacroItemsRef[index];
    m_pCurrMacroParaEditGrid = m_pMultiMacroParaEditGrid[index];
	m_pSingleMacroRef = m_pMultiMacroRef[index];
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());
	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
	UpdateBottomBtnsEnable();//添加系列后更新按键使能
}

void QSttMultiMacroParaEditViewLowFreq::Update_MultiMacroParaEditView()
{
	/*CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();

	CSttItemBase *pParent = pSttGuideBook->GetDevice();
	if (pParent == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("找不到模板文件项目节点"));
		return;
	}
	m_pMulitMacroRootItems = (CSttItems*)pParent->FindByID(STT_ORG_MACRO_LowFreqTest_I);*/

    for (int i = 0;i<m_strTabTitleList.size();i++)
    {
		m_oMultiMacroItemsRef[i].RemoveAll();
		Global_GetAllMacroTest(&m_oMultiMacroItemsRef[i],m_pMulitMacroRootItems,m_pMultiMacroRef[i]);
     	m_pMultiMacroParaEditGrid[i]->ShowDatas(&m_oMultiMacroItemsRef[i]);
    }
	slot_CurrMacroParaEditGridChanged(m_pMultiMacroGridTab->currentIndex());
	m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());
	UpdateBottomBtnsEnable();//添加系列后更新按键使能
}
void QSttMultiMacroParaEditViewLowFreq::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewLowFreq::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewLowFreq::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewLowFreq::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewLowFreq::InitGridTitleLanguage()
{

	if (m_pGridInst_ActValue == NULL)
		return;

	CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_ActValue->GetInst_Cols();
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();
	while (pos != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		SetValueToInstColName(pSttGdInst_Col, LOWFREQ_ID_PsuLowFreqAct);
	}

	if (m_pGridInst_ActTime == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_ActTime->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos2 = pSttGdInst_Cols->GetHeadPosition();
	while (pos2 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos2);
		SetValueToInstColName(pSttGdInst_Col, LOWFREQ_ID_PsuLowFreqTime);
	}

	if (m_pGridInst_SlipTrip == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_SlipTrip->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos3 = pSttGdInst_Cols->GetHeadPosition();
	while (pos3 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos3);
		SetValueToInstColName(pSttGdInst_Col, LOWFREQ_ID_PsuLowFreqDfdt);
	}

	if (m_pGridInst_VBlock == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_VBlock->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos4 = pSttGdInst_Cols->GetHeadPosition();
	while (pos4 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos4);
		SetValueToInstColName(pSttGdInst_Col, LOWFREQ_ID_PsuLowFreqULock);
	}

	if (m_pGridInst_IBlock == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_IBlock->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos5 = pSttGdInst_Cols->GetHeadPosition();
	while (pos5 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos5);
		SetValueToInstColName(pSttGdInst_Col, LOWFREQ_ID_PsuLowFreqILock);
	}
}
void QSttMultiMacroParaEditViewLowFreq::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col, int nLowFreqType)
{
	if (pSttGdInst_Col == NULL)
		return;
	if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		return;

	if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_SELECT)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*选择*/g_sLangTxt_Diff_Select;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_STATE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*状态*/g_sLangTxt_Syn_State;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_GRID_PARAS_ID_TESTRSLT)
	{
		if (nLowFreqType == LOWFREQ_ID_PsuLowFreqAct)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(Hz)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqTime)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(s)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(Hz/s)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqULock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(V)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_ACTVALUE)/*FAct*/
	{
		if (nLowFreqType == LOWFREQ_ID_PsuLowFreqAct)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(Hz)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqTime)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*频率动作值*/g_sLangTxt_Native_FreActValue + "(Hz)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTTIME_TSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(s)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(Hz/s)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_VBLOCK_VBLOCKSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(V)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_IBLOCK_IBLOCKSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(I)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTART)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(Hz)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTART)/*BeginVal*/
	{
		if (nLowFreqType == LOWFREQ_ID_PsuLowFreqDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(Hz/s)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqULock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(V)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQEND)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(Hz)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTEND)/*EndVal*/
	{
		if (nLowFreqType == LOWFREQ_ID_PsuLowFreqDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(Hz/s)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqULock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(V)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_ACTVALUE_FREQSTEP)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(Hz)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWFREQ_PARAS_ID_SLIPTRIP_DFDTSTEP)/*Step*/
	{
		if (nLowFreqType == LOWFREQ_ID_PsuLowFreqDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(Hz/s)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqULock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(V)";
		}
		else if (nLowFreqType == LOWFREQ_ID_PsuLowFreqILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(A)";
		}
	}
}