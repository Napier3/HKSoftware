#include "SttMultiMacroParaEditViewSyn.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif

QSttMultiMacroParaEditViewSyn::QSttMultiMacroParaEditViewSyn(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
	m_pParas = NULL;

	m_strTabTitleList.clear();
	m_strTabTitleList << g_sLangTxt_Syn_ActVoltageTest/*"电压边界值测试"*/ << g_sLangTxt_Syn_ActFreqTest/*"频率边界值测试"*/ << g_sLangTxt_Syn_LeadAngTest/*"导前角及导前时间"*/ << g_sLangTxt_Syn_AutoAdjTest/*"自动调整试验"*/ << g_sLangTxt_Syn_AdjVolTest/*"调压周期测试"*/ << g_sLangTxt_Syn_AdjFreqTest/*"调频周期测试"*/;

	//nOldMacroItemsRef = Syn_ID_SynActVoltageTest;

	m_pMultiMacroRef[Syn_ID_SynActVoltageTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynActVoltageTest);
	m_pMultiMacroRef[Syn_ID_SynActFreqTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynActFreqTest);
	m_pMultiMacroRef[Syn_ID_SynLeadAngTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynLeadAngTest);
	m_pMultiMacroRef[Syn_ID_SynAutoAdjTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynAutoAdjTest);
	m_pMultiMacroRef[Syn_ID_SynAdjVolTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynAdjVolTest);
	m_pMultiMacroRef[Syn_ID_SynAdjFreqTest] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_SynAdjFreqTest);

	m_pGridInst_VoltageTest = NULL;
	m_pGridInst_FreqTest = NULL;
	m_pGridInst_LeadAng = NULL;
	m_pGridInst_AutoAdj = NULL;
	m_pGridInst_AdjVol = NULL;
	m_pGridInst_AdjFreq = NULL;

	m_pSynWiringDiagramWidget = new QSynWiringDiagramWidget(this);
}

QSttMultiMacroParaEditViewSyn::~QSttMultiMacroParaEditViewSyn()
{

}

void QSttMultiMacroParaEditViewSyn::InitUI_OneMacro()
{
    //m_pSingleItemParaEditWidget = new QSynItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynActVoltageTest] = new QSynActVoltageItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynActFreqTest] = new QSynActFreqItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynLeadAngTest] = new QSynLeadAngItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynAutoAdjTest] = new QSynAutoAdjItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynAdjVolTest] = new QSynAdjVolItemParaEditWidget();
	m_pMultiItemParaEditWidget[Syn_ID_SynAdjFreqTest] = new QSynAdjFreqItemParaEditWidget();
	m_pMultiItemStackedWidget = new QStackedWidget();

	CString strText;
	strText = g_sLangTxt_Impedance_FunParas/*"功能参数"*/;
	m_pSingleItemEditTab->insertTab(0,m_pMultiItemStackedWidget,strText);

	//20240624 luozibing 测试使用传入GOOSE发布信息
// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
// 	strText = "GOOSE发布";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	//strText = "添加单项";
	m_pAddOneItemBtn = new QPushButton(/*strText*/g_sLangTxt_Button_AddOneItem);
	//strText = "添加系列";
	m_pAddMultiItemBtn = new QPushButton(/*strText*/g_sLangTxt_Button_AddMultiItem);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
}

void QSttMultiMacroParaEditViewSyn::InitUI_MultiMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(m_strTabTitleList);
	InitUI_OneMacro();
}

void QSttMultiMacroParaEditViewSyn::InitDatas(CSttItems *pCurrRootItems)
{
	DisConnectAll_SigSlot();
	m_pGridInst_VoltageTest = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynActVoltageTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_VOLTAGETEST);
	m_pGridInst_FreqTest = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynActFreqTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_FREQTEST);
	m_pGridInst_LeadAng = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynLeadAngTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_LEADANG);
	m_pGridInst_AutoAdj = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynAutoAdjTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_AUTOADJ);
	m_pGridInst_AdjVol = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynAdjVolTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJVOL);
	m_pGridInst_AdjFreq = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_SynAdjFreqTest,STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJFREQ);

	m_pMultiMacroParaEditGrid[Syn_ID_SynActVoltageTest]->InitColDef(m_pGridInst_VoltageTest,m_pMultiMacroRef[Syn_ID_SynActVoltageTest],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[Syn_ID_SynActFreqTest]->InitColDef(m_pGridInst_FreqTest,m_pMultiMacroRef[Syn_ID_SynActFreqTest],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[Syn_ID_SynLeadAngTest]->InitColDef(m_pGridInst_LeadAng,m_pMultiMacroRef[Syn_ID_SynLeadAngTest],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[Syn_ID_SynAutoAdjTest]->InitColDef(m_pGridInst_AutoAdj,m_pMultiMacroRef[Syn_ID_SynAutoAdjTest],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[Syn_ID_SynAdjVolTest]->InitColDef(m_pGridInst_AdjVol,m_pMultiMacroRef[Syn_ID_SynAdjVolTest],g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[Syn_ID_SynAdjFreqTest]->InitColDef(m_pGridInst_AdjFreq,m_pMultiMacroRef[Syn_ID_SynAdjFreqTest],g_theHtmlRptGenFactory->m_pDataTypes);
	if (m_pSingleMacroRef == NULL)
	{
		m_pSingleMacroRef = m_pMultiMacroRef[Syn_ID_SynActVoltageTest];
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
	//20240926 gongyiping 初始化数据时 CSttMacroTest为空显示提示信息
	if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, g_sLangID_Distance_AddTestItemTips /*_T("请添加测试项！")*/);//在初始化没有测试项时提示；
	}
	ConnectAll_SigSlot();
	slot_CurrMacroParaEditGridChanged(Syn_ID_SynActVoltageTest);
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);
}

void QSttMultiMacroParaEditViewSyn::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();

    //connect(m_pMultiMacroGridTab,SIGNAL(currentChanged(int)),m_pSingleItemParaEditWidget,SLOT(slot_MultiTab_clicked(int)));
    connect(m_pMultiMacroGridTab,SIGNAL(currentChanged(int)),this,SLOT(slot_CurrMacroParaEditGridChanged(int)));
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	//connect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		connect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	}
}

void QSttMultiMacroParaEditViewSyn::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	//disconnect(m_pMultiMacroGridTab,SIGNAL(currentChanged(int)),m_pSingleItemParaEditWidget,SLOT(slot_MultiTab_clicked(int)));
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	//disconnect(m_pSingleItemParaEditWidget,SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		disconnect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
	}
}

//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewSyn::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
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
	case Syn_ID_SynActVoltageTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_VOLTAGETEST;
		strItemName = "电压边界值测试";
		break;
	case Syn_ID_SynActFreqTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_FREQTEST;
		strItemName = "频率边界值测试";
		break;
	case Syn_ID_SynLeadAngTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_LEADANG;
		strItemName = "导前角及导前时间";
		break;
	case Syn_ID_SynAutoAdjTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_AUTOADJ;
		strItemName = "自动调整试验";
		break;
	case Syn_ID_SynAdjVolTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJVOL;
		strItemName = "调压周期测试";
		break;
	case Syn_ID_SynAdjFreqTest:
		strItemID = STT_MULTI_MACRO_SYN_PARAS_GRID_ID_ADJFREQ;
		strItemName = "调频周期测试";
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

void QSttMultiMacroParaEditViewSyn::slot_AddOneItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_AddOneItemBtnClick();
}

void QSttMultiMacroParaEditViewSyn::slot_AddMultQuickClick()
{
	m_pAddMultiItemSelectDlg->hide();
	QSynAddMultQuickDlg oSynFastAddDlg;

	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
	oSynFastAddDlg.SetDatas(pCurrTestMacroUI_Paras);

	if(oSynFastAddDlg.exec() == QDialog::Accepted)
	{
		oSynFastAddDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
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
	pCurrTestMacroUI_Paras->DeleteAll();
	delete pCurrTestMacroUI_Paras;
}

void QSttMultiMacroParaEditViewSyn::slot_AddMultBtnClick()
{
	m_pAddMultiItemSelectDlg->hide();
	QSynAddMultDlg oSynAddMultDlg;
	/*CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
	oSynAddMultDlg.SetDatas(pCurrTestMacroUI_Paras);*/

	GetMacroTestDataToParas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, ((QItemParaEditWidgetBase *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	oSynAddMultDlg.SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
	
	if(oSynAddMultDlg.exec() == QDialog::Accepted)
	{
		//??????zhouhj备注,此处逻辑是有问题的,在点击确认时，就应该把对应的数据存入链表，此处不需要再调用GetDatas
		//CDataGroup *pTestMacroUI_Paras = &g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras;
		//pTestMacroUI_Paras = (CDataGroup *)oLowFrepAddMultDlg.m_oLowFrepDataGroup.Clone();
		//g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.RemoveAll();
		//oSynAddMultDlg.m_pDataGroup->Copy(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

		//oSynAddMultDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
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
		//UpdateBottomBtnsEnable();
	}
	return;
	//delete pCurrTestMacroUI_Paras;
}

void QSttMultiMacroParaEditViewSyn::slot_CommonParasBtnClick()
{
	//通用参数页面
	QSynCommonParasDlg oSynCommonParasDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case Syn_ID_SynActVoltageTest:
        oSynCommonParasDlg.SetDatas(((QSynActVoltageItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
				//oSynCommonParasDlg.GetDatas(((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	case Syn_ID_SynActFreqTest:
        oSynCommonParasDlg.SetDatas(((QSynActFreqItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
                //oSynCommonParasDlg.GetDatas(((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	case Syn_ID_SynLeadAngTest:
        oSynCommonParasDlg.SetDatas(((QSynLeadAngItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
                //oSynCommonParasDlg.GetDatas(((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	case Syn_ID_SynAutoAdjTest:
        oSynCommonParasDlg.SetDatas(((QSynAutoAdjItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
    //            oSynCommonParasDlg.GetDatas(((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
    //            //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	case Syn_ID_SynAdjVolTest:
        oSynCommonParasDlg.SetDatas(((QSynAdjVolItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
    //            oSynCommonParasDlg.GetDatas(((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
    //            //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	case Syn_ID_SynAdjFreqTest:
        oSynCommonParasDlg.SetDatas(((QSynAdjFreqItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynCommonParasDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynCommonParasDlg.CheckItemsModify(pItem))
            {
    //            oSynCommonParasDlg.GetDatas(((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
    //            //通用参数修改后，修改表格中所有项数据通用参数
				//oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);

				//202408122 zhangyq 通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
				UpdateTestUI_To_Wiring();
            }
        }
        break;
	}
	//oSynCommonParasDlg.SetDatas(((QSynItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas());

//	if(oSynCommonParasDlg.exec() == QDialog::Accepted)
//	{
//		//通用参数修改后，修改表格中所有项数据通用参数
//		oSynCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
//		Ats_UpdateMacroTestItems();
//	}
}

void QSttMultiMacroParaEditViewSyn::slot_BinarysBtnClick()
{
	//20240620 luozibing 开入量、开出量页面
	QSynBinarysDlg oSynBinarysDlg;
	switch(m_pMultiMacroGridTab->currentIndex())
	{
	case Syn_ID_SynActVoltageTest:
        oSynBinarysDlg.SetDatas(((QSynActVoltageItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynActVoltageItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case Syn_ID_SynActFreqTest:
        oSynBinarysDlg.SetDatas(((QSynActFreqItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynActFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case Syn_ID_SynLeadAngTest:
        oSynBinarysDlg.SetDatas(((QSynLeadAngItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynLeadAngItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case Syn_ID_SynAutoAdjTest:
        oSynBinarysDlg.SetDatas(((QSynAutoAdjItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynAutoAdjItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case Syn_ID_SynAdjVolTest:
        oSynBinarysDlg.SetDatas(((QSynAdjVolItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynAdjVolItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	case Syn_ID_SynAdjFreqTest:
        oSynBinarysDlg.SetDatas(((QSynAdjFreqItemParaEditWidget *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
        if(oSynBinarysDlg.exec() == QDialog::Accepted)
        {
            CExBaseList *pItem = ((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas();
            if (pItem == NULL)
            {
                pItem = ((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner();
            }
            if (oSynBinarysDlg.CheckItemsModify(pItem))
            {
    //            oSynBinarysDlg.GetDatas(((QSynAdjFreqItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				//oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oSynBinarysDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oSynBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
                Ats_UpdateMacroTestItems();
            }
        }
        break;
	}
//	if(oSynBinarysDlg.exec() == QDialog::Accepted)
//	{
//		oSynBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);
//	}
}

void QSttMultiMacroParaEditViewSyn::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewSyn::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewSyn::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
	//if (m_pCurrMacroParaEditGrid == NULL)
	//{
	//	return;
	//}

	//CSttItems *pRootItems = GetItems_AddOneItem(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	//CExBaseObject *pCurrObj = NULL;
	//CSttMacroTest *pCurrMacroTest = NULL;
	//POS pos = pRootItems->GetHeadPosition();

	//while(pos)
	//{
	//	pCurrObj = pRootItems->GetNext(pos);

	//	if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	//	{
	//		continue;
	//	}

	//	pCurrMacroTest = (CSttMacroTest *)pCurrObj;
	//	MultiMacroParaEdit_DeleteOneMacroItem(pCurrMacroTest,&m_oSingleMacroItemsRef);
	//}

//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewSyn::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewSyn::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewSyn::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();

	//if (m_pCurrMacroParaEditGrid == NULL)
	//{
	//	return;
	//}

	//CSttItems *pRootItems = GetItems_AddOneItem(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	//CExBaseObject *pCurrObj = NULL;
	//CSttMacroTest *pCurrMacroTest = NULL;
	//POS pos = pRootItems->GetHeadPosition();

	//while(pos)
	//{
	//	pCurrObj = pRootItems->GetNext(pos);

	//	if (pCurrObj->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
	//	{
	//		continue;
	//	}

	//	pCurrMacroTest = (CSttMacroTest *)pCurrObj;
	//	pCurrMacroTest->m_nState = TEST_STATE_NORMAL;
	//	m_pCurrMacroParaEditGrid->UpdateData(pCurrMacroTest);
	//}

//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewSyn::slot_AddMultiItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pAddMultiItemBtn->pos(),ADDMULTIITEM_DLG);
}

void QSttMultiMacroParaEditViewSyn::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240621 luozibing 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		//m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);
		QPushButton *pBtnAddMultQuick= new QPushButton(g_sLangTxt_Button_AddMultQuick);
		QPushButton *pBtnAddMult= new QPushButton(g_sLangTxt_Button_AddMultDlg);
		//QPushButton *pBtnAddMult= new QPushButton(STT_MULTI_MACRO_DISTANCE_PARAEDIT_BTN_ADDMULT);

		QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem);
		QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem);

		QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult);
		QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult);

		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());

		pLayout->addWidget(pBtnAddMultQuick,0,0);
		pLayout->addWidget(pBtnAddMult,1,0);
		//pLayout->addWidget(pBtnAddMult,2,0);

		pLayout->addWidget(pBtnDeleteSelItem,0,0);
		pLayout->addWidget(pBtnDeleteAllItem,1,0);

		pLayout->addWidget(pBtnClearSelResult,2,0);
		pLayout->addWidget(pBtnClearAllResult,3,0);

		connect(pBtnAddMultQuick,SIGNAL(clicked()),this,SLOT(slot_AddMultQuickClick()));
		//connect(pBtnAddOne_LL,SIGNAL(clicked()),this,SLOT(slot_AddOneLLBtnClick()));
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
		listTmp.append(g_sLangTxt_Button_AddMultQuick);
		listTmp.append(g_sLangTxt_Button_AddMultDlg);
		//listTmp.append(STT_MULTI_MACRO_DISTANCE_PARAEDIT_BTN_ADDMULT);
		break;
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

void QSttMultiMacroParaEditViewSyn::slot_CurrMacroParaEditGridChanged(int index)//当前显示测试项表格改变
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
	//nOldMacroItemsRef = index;

	UpdateBottomBtnsEnable();//添加系列后更新按键使能
}

void QSttMultiMacroParaEditViewSyn::Update_MultiMacroParaEditView()
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
}

//20240805 gongyiping 更新特性曲线图
BOOL QSttMultiMacroParaEditViewSyn::UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
	CSttMacroTestParaData *pData_X=NULL;
	CSttMacroTestParaData *pData_Y=NULL;

	pData_X = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_DFzd);
	pData_Y = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_DVzd);
	
	m_pCharactInterface->UpdateTestCharParas_Syn(pData_X->m_strValue.toDouble(), pData_Y->m_strValue.toDouble());
	return TRUE;
}
//20240905 gongyiping 更新接线图
void QSttMultiMacroParaEditViewSyn::UpdateTestUI_To_Wiring()
{
	CExBaseList*m_pParas = (((QItemParaEditWidgetBase *)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)m_pParas->FindByID(STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef);
	m_pSynWiringDiagramWidget->UpdateWiringUI(pData->m_strValue.toInt());

}
void QSttMultiMacroParaEditViewSyn::SetValueToParas(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
	//自动准同期模块添加系列界面未配置参数para.xml的id与testmacro.xml的id都相同
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Us)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Us, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Fs)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Fs, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_UgConnectDef, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Vref)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Vref, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_PointNum)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_PointNum, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Angle)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Angle, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Tmax)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Tmax, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_KStart)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_KStart, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_CloseTime, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout1)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout1, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout2)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout2, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_Bout3)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_Bout3, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinSyn, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinIncV, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinDecV, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinIncF, pData->m_strValue, true);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_SYN_PARAS_ADDMULT_ID_BinDecF, pData->m_strValue, true);
	}

	return;
}

void QSttMultiMacroParaEditViewSyn::CheckAllPresence(CExBaseList *pParas)
{
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Us);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Fs);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Ug);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_UgConnectDef);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Vref);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_PointNum);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Angle);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Tmax);

	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_KStart);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_CloseTime);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Bout1);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Bout2);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_Bout3);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_BinSyn);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_BinIncV);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_BinDecV);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_BinIncF);
	SynCheckParaExist(pParas, STT_MULTI_MACRO_SYN_PARAS_ID_BinDecF);


	return;
}
CString QSttMultiMacroParaEditViewSyn::SynValueCheck(CString strValue, float nMax, float nMin, int nAfterPoint)
{
	bool bOk = false;
	float fValue = strValue.toFloat(&bOk);

	if (!bOk)
	{
		fValue = 0;
		strValue.setNum(fValue);
	}

	if (fValue < nMin)
	{
		strValue.setNum(nMin);
	}
	if (fValue > nMax)
	{
		strValue.setNum(nMax);
	}

	int num = 0;
	int nPoint = strValue.indexOf(".");
	if (nPoint == -1)
	{
		if (strValue == "")
		{
			strValue = "0";
		}
		if (nAfterPoint>0)
			strValue += ".";
	}
	else
	{
		num = strValue.length() - nPoint - 1;
		if (num > nAfterPoint)
		{
			if (nAfterPoint >0)
				strValue = strValue.left(nPoint + 1 + nAfterPoint);
			else
				strValue = strValue.left(nPoint + nAfterPoint);

			num = nAfterPoint;
		}
	}

	for (int i = num; i<nAfterPoint; i++)
	{
		strValue += "0";
	}

	return strValue;
}

void QSttMultiMacroParaEditViewSyn::SynCheckParaExist(CExBaseList *pParas, CString strID)
{
	if (pParas == NULL)
		return;

	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if (pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}
//20240926 gongyiping 从测试项获取公共参数给m_oTestMacroUI_Paras
void QSttMultiMacroParaEditViewSyn::GetMacroTestDataToParas(CDataGroup *pParas, CExBaseList* pInnerTestmacro)
{
	if (pParas == NULL || pInnerTestmacro == NULL)
		return;

	CheckAllPresence(pInnerTestmacro);

	POS pos = pInnerTestmacro->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pInnerTestmacro->GetNext(pos);
		SetValueToParas(pParas, pData);
	}

	return;
}