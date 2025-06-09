#include "SttMultiMacroParaEditViewLowVol.h"
//#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"
#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../UI/SttTestCntrFrameApi.h"
QSttMultiMacroParaEditViewLowVol::QSttMultiMacroParaEditViewLowVol(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
	m_pParas = NULL;

	m_strTabTitleList.clear();
    m_strTabTitleList << /*"低压减载动作值"*/g_sLangTxt_Native_LVLRActionVal
                      << /*"动作时间"*/ g_sLangTxt_DistanceSearch_ActionTime
                      << /*"电压滑差动作值"*/g_sLangTxt_Native_VoltSlipAct
                      << /*"低电流闭锁值"*/g_sLangTxt_LowFreq_ILock;

	m_pMultiMacroRef[LOWVOL_ID_PsuLowVolAct] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowVolAct);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowVolTime,&m_oMultiMacroItemsRef[LOWVOL_ID_PsuLowVolTime],m_pMultiRootItems[LOWVOL_ID_PsuLowVolTime]);
	m_pMultiMacroRef[LOWVOL_ID_PsuLowVolTime] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowVolTime);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowVolDvdt,&m_oMultiMacroItemsRef[LOWVOL_ID_PsuLowVolDfdt],m_pMultiRootItems[LOWVOL_ID_PsuLowVolDfdt]);
	m_pMultiMacroRef[LOWVOL_ID_PsuLowVolDfdt] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowVolDvdt);

	//stt_gb_get_all_macro_items(STT_MACRO_ID_PsuLowVolILock,&m_oMultiMacroItemsRef[LOWVOL_ID_PsuLowVolILock],m_pMultiRootItems[LOWVOL_ID_PsuLowVolILock]);
	m_pMultiMacroRef[LOWVOL_ID_PsuLowVolILock] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuLowVolILock);

    m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();

	m_pGridInst_ActValue = NULL;
	m_pGridInst_ActTime = NULL;
	m_pGridInst_SlipTrip = NULL;
	m_pGridInst_IBlock = NULL;
}

QSttMultiMacroParaEditViewLowVol::~QSttMultiMacroParaEditViewLowVol()
{
}

void QSttMultiMacroParaEditViewLowVol::InitUI_OneMacro()
{

	m_pMultiItemParaEditWidget[LOWVOL_ID_PsuLowVolAct] = new QLowVolActItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWVOL_ID_PsuLowVolTime] = new QLowVolTimeItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWVOL_ID_PsuLowVolDfdt] = new QLowVolDvdtItemParaEditWidget();
	m_pMultiItemParaEditWidget[LOWVOL_ID_PsuLowVolILock] = new QLowVolILockItemParaEditWidget();
	m_pMultiItemStackedWidget = new QStackedWidget();

	CString strText;
	strText = /*功能参数*/g_sLangTxt_Diff_FuncParas;
	m_pSingleItemEditTab->insertTab(0,m_pMultiItemStackedWidget,strText);

	//20240624 luozibing 测试使用传入GOOSE发布信息
// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
// 	strText = "GOOSE发布";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);
	strText = /*添加测试项*/g_sLangTxt_Button_AddOneItem;
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = /*添加系列*/g_sLangTxt_Button_AddMultiItem;
	m_pAddMultiItemBtn = new QPushButton(strText);

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
}

void QSttMultiMacroParaEditViewLowVol::InitUI_MultiMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(m_strTabTitleList);
	InitUI_OneMacro();
}
void QSttMultiMacroParaEditViewLowVol::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();

	m_pGridInst_ActValue = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowVolAct,STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTVALUE);
	m_pGridInst_ActTime = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowVolTime,STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTTIME);
	m_pGridInst_SlipTrip = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowVolDvdt,STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_SLIPTRIP);
	m_pGridInst_IBlock = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuLowVolILock,STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_IBLOCK);
	InitGridTitleLanguage();    //表格表头多语言处理

	m_pMultiMacroParaEditGrid[LOWVOL_ID_PsuLowVolAct]->InitColDef(m_pGridInst_ActValue,m_pMultiMacroRef[LOWVOL_ID_PsuLowVolAct],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWVOL_ID_PsuLowVolTime]->InitColDef(m_pGridInst_ActTime,m_pMultiMacroRef[LOWVOL_ID_PsuLowVolTime],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWVOL_ID_PsuLowVolDfdt]->InitColDef(m_pGridInst_SlipTrip,m_pMultiMacroRef[LOWVOL_ID_PsuLowVolDfdt],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[LOWVOL_ID_PsuLowVolILock]->InitColDef(m_pGridInst_IBlock,m_pMultiMacroRef[LOWVOL_ID_PsuLowVolILock],g_theHtmlRptGenFactory->m_pDataTypes);
	if (m_pSingleMacroRef == NULL)
	{
		m_pSingleMacroRef = m_pMultiMacroRef[LOWVOL_ID_PsuLowVolAct];
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
	slot_CurrMacroParaEditGridChanged(LOWVOL_ID_PsuLowVolAct);
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);
	
}

void QSttMultiMacroParaEditViewLowVol::ConnectAll_SigSlot()
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

void QSttMultiMacroParaEditViewLowVol::DisConnectAll_SigSlot()
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
CSttItems* QSttMultiMacroParaEditViewLowVol::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
{
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
	case LOWVOL_ID_PsuLowVolAct:
		strItemID = STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTVALUE;
		strItemName = /*_T("低压减载动作值")*/g_sLangTxt_Native_LowVoltUnderloadTripSet;
		break;
	case LOWVOL_ID_PsuLowVolTime:
		strItemID = STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_ACTTIME;
		strItemName = /*动作时间*/g_sLangTxt_Gradient_ActionTime;
		break;
	case LOWVOL_ID_PsuLowVolDfdt:
		strItemID = STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_SLIPTRIP;
		strItemName = /*_T("电压滑差动作值")*/g_sLangTxt_Native_VoltSlipAct;
		break;
	case LOWVOL_ID_PsuLowVolILock:
		strItemID = STT_MULTI_MACRO_LOWVOL_PARAS_GRID_ID_IBLOCK;
		strItemName = /*_T("低电流闭锁值")*/g_sLangID_LowFreq_LowVol;
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

    //g_theTestCntrFrame->m_pSttGbTreeView->m_pTreeCtrl->AddObj(pNewItems, TRUE);
    stt_Frame_GbTreeCtrl()->AddObj(pNewItems, TRUE);

	CString strParentItemPath = m_pMulitMacroRootItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
// #ifdef _PSX_QT_WINDOWS_//zhouhj 2024.10.10 删除防止自动添加测试项
// 	g_theGbSmartGenWzd->NewItems(strParentItemPath, pNewItems);
// 	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pNewItems->m_strID, pNewItems->m_strName
// 		, pNewItems->m_nTestTimes, pNewItems->m_nRptTitle, pNewItems->m_nTitleLevel);
// #endif
	return pNewItems;
}

void QSttMultiMacroParaEditViewLowVol::slot_AddMultiItemBtnClick()
{
	QLowVolAddMultDlg oLowVolAddMultDlg;

	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras = (CDataGroup*)pTestMacroUI_Paras->Clone();
	pCurrTestMacroUI_Paras->Copy(&oLowVolAddMultDlg.m_oLowVolDataGroup);
	oLowVolAddMultDlg.InitDatas();

	if(oLowVolAddMultDlg.exec() == QDialog::Accepted)
	{
		//??????zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas

		//CDataGroup *pTestMacroUI_Paras = &g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras;
		//pTestMacroUI_Paras = (CDataGroup *)oLowVolAddMultDlg.m_oLowVolDataGroup.Clone();

		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.RemoveAll();
		oLowVolAddMultDlg.GetBinarysParas(m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());//统一开关量
		oLowVolAddMultDlg.m_oLowVolDataGroup.Copy(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

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
void QSttMultiMacroParaEditViewLowVol::slot_CommonParasBtnClick()
{
	
	//20240620 luozibing 通用参数页面
	QLowVolCommonParasDlg oLowVolCommonParasDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case LOWVOL_ID_PsuLowVolAct:
        oLowVolCommonParasDlg.SetDatas(((QLowVolActItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowVolCommonParasDlg.GetDatas(((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowVolCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				//切换界面相电压和线电压
				QLowVolActItemParaEditWidget *m_pActItemParaEditWidget = (QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget;
				m_pActItemParaEditWidget->USetModeChange(oLowVolCommonParasDlg.m_nVType);
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolTime:
        oLowVolCommonParasDlg.SetDatas(((QLowVolTimeItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowVolCommonParasDlg.GetDatas(((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowVolCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				//切换界面相电压和线电压
				QLowVolTimeItemParaEditWidget *m_pTimeItemParaEditWidget = (QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget;
				m_pTimeItemParaEditWidget->USetModeChange(oLowVolCommonParasDlg.m_nVType);
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolDfdt:
        oLowVolCommonParasDlg.SetDatas(((QLowVolDvdtItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowVolCommonParasDlg.GetDatas(((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowVolCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				//切换界面相电压和线电压
				QLowVolDvdtItemParaEditWidget *m_pDvdtItemParaEditWidget = (QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget;
				m_pDvdtItemParaEditWidget->USetModeChange(oLowVolCommonParasDlg.m_nVType);
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolILock:
        oLowVolCommonParasDlg.SetDatas(((QLowVolILockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolCommonParasDlg.CheckItemsModify(pItem))
            {
                //oLowVolCommonParasDlg.GetDatas(((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oLowVolCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				//切换界面相电压和线电压
				QLowVolILockItemParaEditWidget *m_pILockItemParaEditWidget = (QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget;
				m_pILockItemParaEditWidget->USetModeChange(oLowVolCommonParasDlg.m_nVType);
            }
        }
        break;
	}
}

void QSttMultiMacroParaEditViewLowVol::slot_BinarysBtnClick()
{
	//20240620 luozibing 开入量、开出量页面
	QLowVolBinarysDlg oLowVolBinarysDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case LOWVOL_ID_PsuLowVolAct:
        oLowVolBinarysDlg.SetDatas(((QLowVolActItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowVolBinarysDlg.GetDatas(((QLowVolActItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowVolBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolTime:
        oLowVolBinarysDlg.SetDatas(((QLowVolTimeItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowVolBinarysDlg.GetDatas(((QLowVolTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowVolBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolDfdt:
        oLowVolBinarysDlg.SetDatas(((QLowVolDvdtItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowVolBinarysDlg.GetDatas(((QLowVolDvdtItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowVolBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case LOWVOL_ID_PsuLowVolILock:
        oLowVolBinarysDlg.SetDatas(((QLowVolILockItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oLowVolBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oLowVolBinarysDlg.CheckItemsModify(pItem))
            {
                //oLowVolBinarysDlg.GetDatas(((QLowVolILockItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //oLowVolBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
				//开关量修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oLowVolBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oLowVolBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	}
}

void QSttMultiMacroParaEditViewLowVol::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewLowVol::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewLowVol::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
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

		pLayout->addWidget(pBtnDeleteSelItem,0,0);
		pLayout->addWidget(pBtnDeleteAllItem,1,0);

		pLayout->addWidget(pBtnClearSelResult,2,0);
		pLayout->addWidget(pBtnClearAllResult,3,0);

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

void QSttMultiMacroParaEditViewLowVol::slot_CurrMacroParaEditGridChanged(int index)//当前显示测试项表格改变
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
void QSttMultiMacroParaEditViewLowVol::Update_MultiMacroParaEditView()
{
	/*CSttGuideBook *pSttGuideBook = (CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();

	CSttItemBase *pParent = pSttGuideBook->GetDevice();
	if (pParent == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("找不到模板文件项目节点"));
		return;
	}
	m_pMulitMacroRootItems = (CSttItems*)pParent->FindByID(STT_ORG_MACRO_LowVolTest_I);*/

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
void QSttMultiMacroParaEditViewLowVol::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewLowVol::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewLowVol::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewLowVol::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewLowVol::InitGridTitleLanguage()
{
	if (m_pGridInst_ActValue == NULL)
		return;

	CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_ActValue->GetInst_Cols();
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();
	while (pos != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		SetValueToInstColName(pSttGdInst_Col, LOWVOL_ID_PsuLowVolAct);
	}

	if (m_pGridInst_ActTime == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_ActTime->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos2 = pSttGdInst_Cols->GetHeadPosition();
	while (pos2 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos2);
		SetValueToInstColName(pSttGdInst_Col, LOWVOL_ID_PsuLowVolTime);
	}

	if (m_pGridInst_SlipTrip == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_SlipTrip->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos3 = pSttGdInst_Cols->GetHeadPosition();
	while (pos3 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos3);
		SetValueToInstColName(pSttGdInst_Col, LOWVOL_ID_PsuLowVolDfdt);
	}

	if (m_pGridInst_IBlock == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_IBlock->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos4 = pSttGdInst_Cols->GetHeadPosition();
	while (pos4 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos4);
		SetValueToInstColName(pSttGdInst_Col, LOWVOL_ID_PsuLowVolILock);
	}
}
void QSttMultiMacroParaEditViewLowVol::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col, int nLowFreqType)
{
	if (pSttGdInst_Col == NULL)
		return;
	if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		return;

	if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_SELECT)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*选择*/g_sLangTxt_Diff_Select;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_STATE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*状态*/g_sLangTxt_Syn_State;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_GRID_PARAS_ID_TESTRSLT)
	{
		if (nLowFreqType == LOWVOL_ID_PsuLowVolAct)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(V)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolTime)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(s)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(V/s)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*结果评估*/g_sLangTxt_StateEstimate_ResultEstimate;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ACTVALUE)/*UAct*/
	{
		if (nLowFreqType == LOWVOL_ID_PsuLowVolAct)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(V)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolTime)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*电压动作值(V)*/g_sLangTxt_Gradient_VActionValue;
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_TSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(s)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(V/s)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_IBLOCKSETTING)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(I)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTART)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(V)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTSTART)/*BeginVal*/
	{
		if (nLowFreqType == LOWVOL_ID_PsuLowVolDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(V/s)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化始值*/g_sLangTxt_LowFreq_BeginVal + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VEND)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(V)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_DFDTEND)/*EndVal*/
	{
		if (nLowFreqType == LOWVOL_ID_PsuLowVolDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(V/s)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化终值*/g_sLangTxt_LowFreq_EndVal + "(A)";
		}
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_VSTEP)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(V)";
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_VSTEP)/*Step*/
	{
		if (nLowFreqType == LOWVOL_ID_PsuLowVolDfdt)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(V/s)";
		}
		else if (nLowFreqType == LOWVOL_ID_PsuLowVolILock)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*变化步长*/g_sLangTxt_Diff_Step + "(A)";
		}
	}
}