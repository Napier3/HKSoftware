#include "SttMultiMacroParaEditViewDiff.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "../../UI/SttTestCntrFrameBase.h"

#ifdef _PSX_QT_WINDOWS_
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;
#endif
QSttMultiMacroParaEditViewDiff::QSttMultiMacroParaEditViewDiff(const CString &strGridFile,QWidget *parent) :
    QSttMultiMacroParaEditViewBase(strGridFile,parent)
{
//	m_pAddMultiItemSelectDlg = NULL;//放入基类  zhouhj 2024.9.15
	m_pParas = NULL;

	m_strTabTitleList.clear();
	m_strTabTitleList << /*"差动曲线搜索"*/ g_sLangTxt_Diff_Rate
		<< /*"动作时间"*/g_sLangTxt_DistanceSearch_ActionTime 
		<< /*"谐波制动搜索"*/g_sLangTxt_Diff_Harm;

 
	m_pMultiMacroRef[DIFF_ID_PSUDIFFRATE] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuDiffRateTest);
	m_pMultiMacroRef[DIFF_ID_PSUDIFFTIME] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuDiffTimeTest);
	m_pMultiMacroRef[DIFF_ID_PSUDIFFHARM] = (CTestMacro*)((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros->FindByID(STT_MACRO_ID_PsuDiffHarmTest);

	m_pGridInst_DiffRate = NULL;
	m_pGridInst_DiffTime = NULL;
	m_pGridInst_DiffHarm = NULL;

	m_pDiffWiringWidget = NULL;
	m_pDiffWiringWidget = new QDiffWiringWidget(this);
}

QSttMultiMacroParaEditViewDiff::~QSttMultiMacroParaEditViewDiff()
{
}

void QSttMultiMacroParaEditViewDiff::InitUI_OneMacro()
{
    //m_pSingleItemParaEditWidget = new QDiffItemParaEditWidget();
    m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFRATE] = new QDiffRateItemParaEditWidget();
	m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFTIME] = new QDiffTimeItemParaEditWidget();
	m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFHARM] = new QDiffHarmItemParaEditWidget();

	m_pMultiItemStackedWidget = new QStackedWidget();
    
	CString strText;
	strText = /*功能参数*/g_sLangTxt_Diff_FuncParas;
	m_pSingleItemEditTab->insertTab(0,m_pMultiItemStackedWidget,strText);

	//20240624 luozibing 测试使用传入GOOSE发布信息
// 	m_pGoosePubsWidget = new QGooseParaWidget(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr());
// 	strText = "GOOSE发布";
// 	m_pSingleItemEditTab->insertTab(1,m_pGoosePubsWidget,strText);
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();

	strText = /*添加单项*/g_sLangTxt_Diff_AddOneItem;
	m_pAddOneItemBtn = new QPushButton(strText);
	strText = /*添加系列*/g_sLangTxt_Button_AddMultDlg;
	m_pAddMultiItemBtn = new QPushButton(strText);
	
	m_pBottomHboxLayout->insertWidget(0,m_pAddOneItemBtn);
	m_pBottomHboxLayout->insertWidget(1,m_pAddMultiItemBtn);
}

void QSttMultiMacroParaEditViewDiff::InitUI_MultiMacro()
{
	QSttMultiMacroParaEditViewBase::InitUI_MultiMacro(m_strTabTitleList);
	CString strText;
	strText = /*清除结果*/g_sLangTxt_Diff_ClearResult;
	m_pClearResultBtn->setText(strText);
	InitUI_OneMacro();
}
void QSttMultiMacroParaEditViewDiff::InitDatas(CSttItems *pCurrRootItems)
{
    DisConnectAll_SigSlot();
	m_pGridInst_DiffRate = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuDiffRateTest,STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE);
	m_pGridInst_DiffTime = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuDiffTimeTest,STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME);
	m_pGridInst_DiffHarm = m_oSttTestGridDefine.GetGridInst(STT_MACRO_ID_PsuDiffHarmTest,STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM);
	InitGridTitleLanguage();    //表格表头多语言处理
	//m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFRATE]->InitColDef(m_pGridInst_DiffRate,m_pMultiMacroRef[DIFF_ID_PSUDIFFRATE],g_theHtmlRptGenFactory->m_pDataTypes);
	//m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFTIME]->InitColDef(m_pGridInst_DiffTime,m_pMultiMacroRef[DIFF_ID_PSUDIFFTIME],g_theHtmlRptGenFactory->m_pDataTypes);
	//m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFHARM]->InitColDef(m_pGridInst_DiffHarm,m_pMultiMacroRef[DIFF_ID_PSUDIFFHARM],g_theHtmlRptGenFactory->m_pDataTypes);
	if (m_pSingleMacroRef == NULL)
	{
		m_pSingleMacroRef = m_pMultiMacroRef[DIFF_ID_PSUDIFFRATE];
	}
	QSttMultiMacroParaEditViewBase::InitDatas(pCurrRootItems);
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		if (m_pMultiMacroParaEditGrid[i] != NULL)
		{
			m_pMultiMacroParaEditGrid[i]->InitGrid();
			m_pMultiItemParaEditWidget[i]->InitDatas(m_pMultiMacroRef[i]);
			m_pMultiItemStackedWidget->addWidget((QWidget*)m_pMultiItemParaEditWidget[i]);
			GetParasDataToMacroTest(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, m_pMultiItemParaEditWidget[i]->GetMacroTestParaDatas_Inner());
		}
	}

	if (m_oSingleMacroItemsRef.FindByClassID(STTGBXMLCLASSID_CSTTMACROTEST) == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("请添加测试项！"));//在初始化没有测试项时提示；
	}
	ConnectAll_SigSlot();
	slot_CurrMacroParaEditGridChanged(DIFF_ID_PSUDIFFRATE);
	m_pSingleItemParaEditWidget->InitDatas(m_pSingleMacroRef);
	slot_UpdateDiffWiringWidget();
	
}

void QSttMultiMacroParaEditViewDiff::ConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::ConnectAll_SigSlot();

    connect(m_pMultiMacroGridTab,SIGNAL(currentChanged(int)),this,SLOT(slot_CurrMacroParaEditGridChanged(int)));
	connect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	connect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		connect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
		connect(m_pMultiItemParaEditWidget[i], SIGNAL(sig_UpdateDiffWiringWidget()), this, SLOT(slot_UpdateDiffWiringWidget()));
		connect(m_pMultiItemParaEditWidget[i], SIGNAL(sig_UpdateId(double)), this, SLOT(slot_CalculateId(double)));
	}
}

void QSttMultiMacroParaEditViewDiff::DisConnectAll_SigSlot()
{
	QSttMultiMacroParaEditViewBase::DisConnectAll_SigSlot();
	disconnect(m_pAddOneItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddOneItemBtnClick()));
	disconnect(m_pAddMultiItemBtn,SIGNAL(clicked()),this,SLOT(slot_AddMultiItemBtnClick()));
	for (int i = 0;i < m_strTabTitleList.size();i++)
	{
		disconnect(m_pMultiItemParaEditWidget[i],SIGNAL(sig_UpdateCurrSelGridData(CSttMacroTest*)),this,SLOT(slot_ParaEditWidget_To_Grid(CSttMacroTest*)));
		disconnect(m_pMultiItemParaEditWidget[i], SIGNAL(sig_UpdateDiffWiringWidget()), this, SLOT(slot_UpdateDiffWiringWidget()));
		disconnect(m_pMultiItemParaEditWidget[i], SIGNAL(sig_UpdateId(double)), this, SLOT(slot_CalculateId(double)));
	}
}
//添加单个测试项时,获取当前项目需要添加的父节点,如距离保护,需要按故障类型进行分类,如当前父节点Items不存在需要单独创建
CSttItems* QSttMultiMacroParaEditViewDiff::GetRootItems_CurrTestMacro(CSttMacroTest *pSttMacroTest)
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
	case DIFF_ID_PSUDIFFRATE:
		strItemID = STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE;
		strItemName = /*差动曲线搜索*/g_sLangTxt_Diff_Rate;
		break;
	case DIFF_ID_PSUDIFFTIME:
		strItemID = STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME;
		strItemName = /*动作时间*/g_sLangTxt_Gradient_ActionTime;
		break;
	case DIFF_ID_PSUDIFFHARM:
		strItemID = STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM;
		strItemName = /*谐波制动搜索*/g_sLangTxt_Diff_Harm;
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
void QSttMultiMacroParaEditViewDiff::slot_CommonParasBtnClick()
{
	//20240620 luozibing 通用参数页面
	QDiffCommonParasDlg oDiffCommonParasDlg;
    oDiffCommonParasDlg.SetDatas(m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());
    if(oDiffCommonParasDlg.exec() == QDialog::Accepted)
	{
		CExBaseList *pItem = NULL;
		if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External !=NULL)
        {
			pItem = m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
		}
            if (pItem == NULL)
            {
            pItem = m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner();
            }
            if (oDiffCommonParasDlg.CheckItemsModify(pItem))
            {
                //oDiffCommonParasDlg.GetDatas(((QDiffRateItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
                //通用参数修改后，修改表格中所有项数据通用参数
                //oDiffCommonParasDlg.UpdataAllCommonParas(m_pCurrMacroItemsRef);
				//通用参数修改后，修改所有tab表格的通用参数数据

				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
						oDiffCommonParasDlg.GetDatas(((QItemParaEditWidgetBase*)m_pMultiItemParaEditWidget[i])->GetMacroTestParaDatas_Inner());
						oDiffCommonParasDlg.UpdataAllCommonParas(&m_oMultiMacroItemsRef[i]);
					}
				}

				// 通用参数更新后，记录是否已经被抬高
				long nClock, nFaultType, nComBineFeature, nZeroSeqElimiType;
				CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
				pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE, nFaultType);
				pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE, nClock);
				pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, nComBineFeature);
				pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, nZeroSeqElimiType);

			m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType);
			GetParasDataToMacroTest(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());
                Ats_UpdateMacroTestItems();
                //m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);
				slot_UpdateDiffWiringWidget();   //更新右侧接线图	
            }
        }
}

void QSttMultiMacroParaEditViewDiff::slot_BinarysBtnClick()
{
	//20240620 luozibing 开入量、开出量页面
	QDiffBinarysDlg oDiffBinarysDlg;
	oDiffBinarysDlg.SetDatas(m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());
    if(oDiffBinarysDlg.exec() == QDialog::Accepted)
	{
		CExBaseList *pItem = NULL;
		if (m_pSingleItemParaEditWidget->m_pCurrMacroTest_External != NULL)
        {
			pItem = m_pSingleItemParaEditWidget->m_pCurrMacroTest_External->GetSttMacroTestParaDatas(FALSE, "");
		}
            if (pItem == NULL)
            {
			pItem = m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner();
            }
            if (oDiffBinarysDlg.CheckItemsModify(pItem))
            {
				/* oDiffBinarysDlg.GetDatas(((QDiffRateItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
				 oDiffBinarysDlg.UpdataAllBinarys(m_pCurrMacroItemsRef);*/
				//通用参数修改后，修改所有tab表格的通用参数数据
				for (int i = 0; i < m_strTabTitleList.size(); i++)
				{
					if (m_pMultiMacroParaEditGrid[i] != NULL)
					{
					oDiffBinarysDlg.GetDatas(m_pMultiItemParaEditWidget[i]->GetMacroTestParaDatas_Inner());
						oDiffBinarysDlg.UpdataAllBinarys(&m_oMultiMacroItemsRef[i]);
					}
				}
			GetParasDataToMacroTest(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, m_pSingleItemParaEditWidget->GetMacroTestParaDatas_Inner());
                Ats_UpdateMacroTestItems();
            }
        }
}

void QSttMultiMacroParaEditViewDiff::slot_AddMultiItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pAddMultiItemBtn->pos(),ADDMULTIITEM_DLG);
}

void QSttMultiMacroParaEditViewDiff::slot_DeleteItemBtnClick()
{
	InitAddMultiItemSelectDlg(m_pDeleteItemBtn->pos(),DELETEITEM_DLG);
}

void QSttMultiMacroParaEditViewDiff::slot_ClearResultBtnClick()
{
	InitAddMultiItemSelectDlg(m_pClearResultBtn->pos(),CLEARSELRESULT);
}

void QSttMultiMacroParaEditViewDiff::InitAddMultiItemSelectDlg(QPoint pos,int nDlgState)
{
	//20240621 luozibing 初次初始化创建选择界面时，创建所有按键，根据按键名称与传入状态显示不同按键
	if (m_pAddMultiItemSelectDlg == NULL)
	{
		m_pAddMultiItemSelectDlg = new QDialog(this);
		//m_pAddMultiItemSelectDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
		m_pAddMultiItemSelectDlg->setWindowFlags(Qt::Popup);
		m_pAddMultiItemSelectDlg->setFont(*g_pSttGlobalFont);

		QGridLayout *pLayout = new QGridLayout(m_pAddMultiItemSelectDlg);

        QPushButton *pBtnAddSearchLine = new QPushButton(g_sLangTxt_Diff_AddSearchLine);
        QPushButton *pBtnAddBatchItem = new QPushButton(g_sLangTxt_Button_AddMultBatch);

        QPushButton *pBtnDeleteSelItem= new QPushButton(g_sLangTxt_Button_DeleteSelItem);
        QPushButton *pBtnDeleteAllItem= new QPushButton(g_sLangTxt_Button_DeleteAllItem);

        QPushButton *pBtnClearSelResult= new QPushButton(g_sLangTxt_Button_ClearSelResult);
        QPushButton *pBtnClearAllResult= new QPushButton(g_sLangTxt_Button_ClearAllResult);

		pBtnDeleteSelItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnDeleteAllItem->setMinimumSize(m_pDeleteItemBtn->size());
		pBtnClearSelResult->setMinimumSize(m_pClearResultBtn->size());
		pBtnClearAllResult->setMinimumSize(m_pClearResultBtn->size());

		pLayout->addWidget(pBtnAddSearchLine,0,0);
		pLayout->addWidget(pBtnAddBatchItem,1,0);

		pLayout->addWidget(pBtnDeleteSelItem,2,0);
		pLayout->addWidget(pBtnDeleteAllItem,3,0);

		pLayout->addWidget(pBtnClearSelResult,4,0);
		pLayout->addWidget(pBtnClearAllResult,5,0);

		connect(pBtnAddSearchLine,SIGNAL(clicked()),this,SLOT(slot_AddSearchLineBtnClick()));
		connect(pBtnAddBatchItem,SIGNAL(clicked()),this,SLOT(slot_AddBatchItemBtnClick()));

		connect(pBtnDeleteSelItem,SIGNAL(clicked()),this,SLOT(slot_DeleteSelItemBtnClick()));
		connect(pBtnDeleteAllItem,SIGNAL(clicked()),this,SLOT(slot_DeleteAllItemBtnClick()));

		connect(pBtnClearSelResult,SIGNAL(clicked()),this,SLOT(slot_ClearSelResultBtnClick()));
		connect(pBtnClearAllResult,SIGNAL(clicked()),this,SLOT(slot_ClearAllResultBtnClick()));
	}
	QStringList listTmp;
	switch(nDlgState)
	{
	case ADDMULTIITEM_DLG:
        listTmp.append(g_sLangTxt_Diff_AddSearchLine);
        listTmp.append(g_sLangTxt_Button_AddMultBatch);
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

void QSttMultiMacroParaEditViewDiff::slot_AddSearchLineBtnClick()//添加搜索线
{
	m_pAddMultiItemSelectDlg->hide();

	QDiffAddSearchLineDlg oDiffAddSearchLineDlg;
	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras = (CDataGroup*)pTestMacroUI_Paras->Clone();
	oDiffAddSearchLineDlg.SetDatas(pCurrTestMacroUI_Paras);
	if (oDiffAddSearchLineDlg.exec() == QDialog::Accepted)
	{
		m_pMultiMacroGridTab->setCurrentIndex(DIFF_ID_PSUDIFFRATE);
		for (int i = 0; i < m_pMultiMacroGridTab->count(); ++i) 
		{
			m_pMultiMacroGridTab->setTabEnabled(i, false);
		}
		double dCurrVal = oDiffAddSearchLineDlg.m_dBeginVal;
		for (int i = 0; i < oDiffAddSearchLineDlg.m_nPoints; i++)
		{
			for (int i = 0; i < 7;i++)
			{
				if (oDiffAddSearchLineDlg.m_Isbcheck_FaultType[i] == true)
				{
					AddItem_From_SearchLine(i, dCurrVal, oDiffAddSearchLineDlg.m_dTime, oDiffAddSearchLineDlg.m_nErrorLogic, oDiffAddSearchLineDlg.m_dAbsErr, oDiffAddSearchLineDlg.m_dRelErr);
				}
			}

			dCurrVal += oDiffAddSearchLineDlg.m_dStep;
			if (dCurrVal>oDiffAddSearchLineDlg.m_dEndVal)
			{
				dCurrVal = oDiffAddSearchLineDlg.m_dEndVal;
				break;
			}
		}
		for (int i = 0; i < m_pMultiMacroGridTab->count(); ++i)
	{
			m_pMultiMacroGridTab->setTabEnabled(i, true);
		}
	}
	
}
void QSttMultiMacroParaEditViewDiff::slot_AddBatchItemBtnClick()//批量添加
{
	m_pAddMultiItemSelectDlg->hide();

	QDiffAddBatchDlg oDiffAddBatchDlg;

	CDataGroup *pTestMacroUI_Paras = GetAddMultItems_Paras();
	CDataGroup *pCurrTestMacroUI_Paras  = (CDataGroup*)pTestMacroUI_Paras->Clone();
	oDiffAddBatchDlg.SetDatas(pCurrTestMacroUI_Paras);

	if(oDiffAddBatchDlg.exec() == QDialog::Accepted)
	{
		oDiffAddBatchDlg.GetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);

		double dIr, dId;
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_IR, dIr);
		m_oDiffCharCal.CalculateId_Custom(dIr, dId);
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_SL_ID, dId,TRUE);
		
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

void QSttMultiMacroParaEditViewDiff::slot_CurrMacroParaEditGridChanged(int index)//当前显示测试项表格改变
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

	m_pCurrMacroParaEditGrid->ShowDatas(m_pCurrMacroItemsRef);

	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	UpdateBottomBtnsEnable();//添加系列后更新按键使能

	CCharacteristic* pChar = NULL;
	switch (m_pMultiMacroGridTab->currentIndex())
	{
	case DIFF_ID_PSUDIFFRATE:
		pChar = stt_Frame_Characteristics()->FindByID_Char(STT_MACRO_ID_PsuDiffRateTest);

		if (!pChar)
		{
			break;
		}
		((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_LINE);//比率制动
		break;
	case DIFF_ID_PSUDIFFTIME:
		pChar = stt_Frame_Characteristics()->FindByID_Char(STT_MACRO_ID_PsuDiffRateTest);

		if (!pChar)
		{
			break;
		}
		((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_POINT);//动作时间
		break;
	case DIFF_ID_PSUDIFFHARM:
		pChar = stt_Frame_Characteristics()->FindByID_Char(STT_MACRO_ID_PsuDiffHarmTest);

		if (!pChar)
		{
			break;
		}
		((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffHarmTest, CHAR_TEST_OBJECT_DRAW_LINE);//谐波制动
		break;
	}
	
}

void QSttMultiMacroParaEditViewDiff::Update_MultiMacroParaEditView()
{
    for (int i = 0;i<m_strTabTitleList.size();i++)
    {
		m_oMultiMacroItemsRef[i].RemoveAll();
		Global_GetAllMacroTest(&m_oMultiMacroItemsRef[i],m_pMulitMacroRootItems,m_pMultiMacroRef[i]);
		m_pCurrMacroItemsRef = &m_oMultiMacroItemsRef[i];

		if (i == DIFF_ID_PSUDIFFHARM)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffHarmTest, CHAR_TEST_OBJECT_DRAW_LINE);//谐波制动
		}
		else if (i == DIFF_ID_PSUDIFFTIME)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_POINT);//动作时间
		}
		else if (i == DIFF_ID_PSUDIFFRATE)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_LINE);//比率制动
		}

		POS pos = m_oMultiMacroItemsRef[i].GetHeadPosition();
		while (pos != NULL)
		{
			CExBaseObject *pData = (CExBaseObject *)m_pCurrMacroItemsRef->GetNext(pos);
			if (pData->GetClassID() != STTGBXMLCLASSID_CSTTMACROTEST)
			{
				continue;
			}
			
			CSttMacroTest *pSttMacroTest = (CSttMacroTest *)pData;
			AddUpdateTestPoint_To_Charact(pSttMacroTest);
		}
    }
	slot_CurrMacroParaEditGridChanged(m_pMultiMacroGridTab->currentIndex());
	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());
}
void QSttMultiMacroParaEditViewDiff::slot_DeleteSelItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteSelItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiff::slot_DeleteAllItemBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_DeleteAllItemBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewDiff::slot_ClearSelResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearSelResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}

void QSttMultiMacroParaEditViewDiff::slot_ClearAllResultBtnClick()
{
	QSttMultiMacroParaEditViewBase::slot_ClearAllResultBtnClick();
//     if(m_pAddMultiItemSelectDlg != NULL)    //使用右键快捷方式时m_pAddMultiItemSelectDlg为空指针
//     {
// 	m_pAddMultiItemSelectDlg->hide();//放入基类  zhouhj 2024.9.15
//     }
}
void QSttMultiMacroParaEditViewDiff::slot_UpdateDiffWiringWidget()
{
	switch (m_pMultiMacroGridTab->currentIndex())
	{
	case DIFF_ID_PSUDIFFRATE:
		m_pDiffWiringWidget->setCommonData(((QDiffRateItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		m_pDiffWiringWidget->updateTable(STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_RATE);
		break;
	case DIFF_ID_PSUDIFFTIME:
		m_pDiffWiringWidget->setCommonData(((QDiffTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		m_pDiffWiringWidget->updateTable(STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_TIME);
		break;
	case DIFF_ID_PSUDIFFHARM:
		m_pDiffWiringWidget->setCommonData(((QDiffHarmItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetMacroTestParaDatas_Inner());
		m_pDiffWiringWidget->updateTable(STT_MULTI_MACRO_DIFF_PARAS_GRID_ID_HARM);
		break;
	}
}
BOOL QSttMultiMacroParaEditViewDiff::DeleteTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	if (pCurrMacroTest == NULL)
	{
		return FALSE;
	}
	m_pCharactInterface->DeleteTestData(pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE));
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}

BOOL QSttMultiMacroParaEditViewDiff::AddUpdateTestPoint_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}

		//判断测试项是否已添加
		BOOL bCurrMacroTestExist = FALSE;
		POS pos = m_pCurrMacroItemsRef->GetHeadPosition();
		while (pos != NULL)
		{
			CSttMacroTest* pMacroTestTemp = (CSttMacroTest*)m_pCurrMacroItemsRef->GetNext(pos);
			if (pMacroTestTemp == pCurrMacroTest)
			{
				bCurrMacroTestExist = TRUE;
				break;
			}
		}
		if (!bCurrMacroTestExist)
			return FALSE;
	
	CSttMacroTestParaDatas *pDataParas = pCurrMacroTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pDataParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[UpdateTestLine_To_Charact]参数为空"));
		return FALSE;
	}
	CSttMacroTestParaData *pData_Ir = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);//Ir
	if (pData_Ir == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
		pData_Ir = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
	}
	CSttMacroTestParaData *pData_Id = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);//Id
	if (pData_Id == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);
		pData_Id = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);
	}
	CSttMacroTestParaData *pData_BeginVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);//搜索上限
	if (pData_BeginVal == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
		pData_BeginVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
	}
	CSttMacroTestParaData *pData_EndVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);//搜索下限
	if (pData_EndVal == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
		pData_EndVal = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
	}
	CSttMacroTestParaData *pData_FaultType = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);//故障类型
	if (pData_FaultType == NULL)
	{
		CheckForPresence(pDataParas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
		pData_FaultType = (CSttMacroTestParaData *)pDataParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	}

	double dBegX, dBegY, dEndX, dEndY, dX, dY;
	CString strTmpVString;
	strTmpVString = pCurrMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);


	if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffRateTest)
	{
		dBegX = pData_Ir->m_strValue.toDouble();
		dBegY = pData_BeginVal->m_strValue.toDouble();
		dEndX = dBegX;
		dEndY = pData_EndVal->m_strValue.toDouble();
		m_pCharactInterface->AddUpdateTestLine(strTmpVString, dBegX, dBegY, dEndX, dEndY, pData_FaultType->m_strValue.toInt(), nState);
	}
	else if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffTimeTest)
	{
		dX = pData_Ir->m_strValue.toDouble();
		dY = pData_Id->m_strValue.toDouble();
		m_pCharactInterface->AddUpdateTestPoint(strTmpVString, dX, dY, pData_FaultType->m_strValue.toInt(), nState);
	}
	else if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffHarmTest)
	{
		dBegX = pData_BeginVal->m_strValue.toDouble();
		dBegY = pData_Id->m_strValue.toDouble();
		dEndX = pData_EndVal->m_strValue.toDouble();
		dEndY = dBegY;
		m_pCharactInterface->AddUpdateTestLine(strTmpVString, dBegX, dBegY, dEndX, dEndY, pData_FaultType->m_strValue.toInt(), nState);
	}
	
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}
BOOL QSttMultiMacroParaEditViewDiff::AddItem_From_Charact(double dX, double dY)
{
	if (m_pMulitMacroRootItems == NULL)
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

	//根据坐标生成Id,Ir
	CString strIr, strId;
	strIr.setNum(dX);
	strId.setNum(dY);
	double dIr, dId, dBeginVal, dEndVal, dBeginValRate, dEndValRate, nFaultType;

	CDvmData *pData_FaultType = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	nFaultType = pData_FaultType->m_strValue.toInt();

	if (m_pMultiMacroGridTab->currentIndex() == DIFF_ID_PSUDIFFRATE)
	{
		CDvmData *pData_BeginVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
		CDvmData *pData_EndVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
		CDvmData *pData_IdSetting = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
		CDvmData *pData_Ir = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
		if (pData_Ir != NULL)
		{
			pData_Ir->m_strValue = strIr;
			if (!InitDiffCharCal())
			{
				return FALSE;
			}
			m_oDiffCharCal.CalculateId_Custom(pData_Ir->m_strValue.toDouble(), dId);
			
			dBeginValRate = pData_BeginVal->m_strValue.toDouble() / pData_IdSetting->m_strValue.toDouble();
			dEndValRate = pData_EndVal->m_strValue.toDouble() / pData_IdSetting->m_strValue.toDouble();
			pData_IdSetting->m_strValue = QString::number(dId, 'f', 3);

			dBeginVal = dId *dBeginValRate;
			double dMaxdId = dBeginVal;
			m_pDiffWiringWidget->GetCurrentCal(&dMaxdId, pData_Ir->m_strValue.toDouble());

			if (dBeginVal > dMaxdId)
			{
				dBeginVal = dMaxdId;
			}
			pData_BeginVal->m_strValue = QString::number(dBeginVal, 'f', 3);
			pData_EndVal->m_strValue = QString::number(dId *dEndValRate, 'f', 3);
			dIr = pData_Ir->m_strValue.toDouble();
			dEndVal = pData_EndVal->m_strValue.toDouble();
		}
	}
	else if (m_pMultiMacroGridTab->currentIndex() == DIFF_ID_PSUDIFFTIME)
	{
		CDvmData *pData_Id = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
		CDvmData *pData_Ir = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR);
		if (pData_Ir != NULL)
		{
			pData_Ir->m_strValue = strIr;
			double dId;
			if (!InitDiffCharCal())
			{
				return FALSE;
			}
			m_oDiffCharCal.CalculateId_Custom(pData_Ir->m_strValue.toDouble(), dId);
			pData_Id->m_strValue = QString::number(dId, 'f', 3);
			dIr = pData_Ir->m_strValue.toDouble();
			dId = pData_Id->m_strValue.toDouble();
		}
	}
	else if (m_pMultiMacroGridTab->currentIndex() == DIFF_ID_PSUDIFFHARM)
	{
		CDvmData *pData_BeginVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL);
		CDvmData *pData_EndVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL);
		CDvmData *pData_Id = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);
		pData_Id->m_strValue = strId;

		dBeginVal = pData_BeginVal->m_strValue.toDouble();
		dEndVal = pData_EndVal->m_strValue.toDouble();
		dId = pData_Id->m_strValue.toDouble();
	}

	CString strItemPath;
	strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	CString strMacroUI_ID, strItemName, strItemID;
	strItemName = m_pSingleMacroRef->m_strName;
	strItemID = m_pSingleMacroRef->m_strID;
	strMacroUI_ID = GetMacroID();
	pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

	g_nUpdateMultiMacroParaEditView = 0;
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName/*pNewTest->m_strName*/, strItemID/*pNewTest->m_strID*/, strItemPath, 0,
		m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DiffTest_I);
	g_nUpdateMultiMacroParaEditView = 1;

	if (nRet != STT_CMD_ExecStatus_SUCCESS)
	{
		//		pParentItems->Delete(pNewTest);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能执行命令失败(%ld)."), nRet);
		return FALSE;
	}

	CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);

	if (pNewTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
		return FALSE;
	}
	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pNewDataParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[AddItem_From_Charact]参数为空"));
		return FALSE;
	}

	m_pCurrMacroItemsRef->AddTail(pNewTest);
	m_pCurrMacroParaEditGrid->InsertData(pNewTest);
	//添加测试线
	double dBegX, dBegY, dEndX, dEndY;
	CString strTmpString;
	strTmpString = pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	switch (m_pMultiMacroGridTab->currentIndex())
	{
	case DIFF_ID_PSUDIFFRATE:
		dBegX = dIr;
		dBegY = dBeginVal;
		dEndX = dBegX;
		dEndY = dEndVal;
		m_pCharactInterface->AddUpdateTestLine(strTmpString, dBegX, dBegY, dEndX, dEndY, nFaultType);
		break;
	case DIFF_ID_PSUDIFFTIME:
		dX = dIr;
		dY = dId;
		m_pCharactInterface->AddUpdateTestPoint(strTmpString, dX, dY, nFaultType);
		break;
	case DIFF_ID_PSUDIFFHARM:
		dBegX = dBeginVal;
		dBegY =	dId;
		dEndX = dEndVal;
		dEndY = dBegY;
		m_pCharactInterface->AddUpdateTestLine(strTmpString, dBegX, dBegY, dEndX, dEndY, nFaultType);
		break;
	}
	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	//通过特性图添加测试项后更新按键使能
	UpdateBottomBtnsEnable();
	m_bCharTestObjectHasChanged = TRUE;
	return TRUE;
}
BOOL QSttMultiMacroParaEditViewDiff::InitDiffCharCal()
{
	if (m_oDiffCharCal.m_oPoints.GetCount() != 0)
	{
		return TRUE;
	}

	CCharacteristic* pChar = stt_Frame_Characteristics()->FindByID_Char(STT_MACRO_ID_PsuDiffRateTest);

	if (!pChar)
	{
		return FALSE;
	}
	else
	{
		
		CCharacterArea* pArea = pChar->GetCharacterArea();

		long nIsCustomChar = 0;
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR, nIsCustomChar); //自定义曲线ID
		
		if (!nIsCustomChar)
		{
			CCharElementLined* pLine = (CCharElementLined*)pArea->GetHead();
			m_oDiffCharCal.m_fIcdqd = CString_To_double(pLine->m_strYb);
			m_oDiffCharCal.m_fKid0 = CalLineK(pLine);
			g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IDOOR, m_oDiffCharCal.m_fIcdqd, TRUE);
			//设置拐点
			switch (pArea->GetCount())
			{
			case 5:
				pLine = (CCharElementLined*)pArea->GetAt((long)3);
				m_oDiffCharCal.m_fKid3 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp3 = CString_To_double(pLine->m_strXb);
				g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP3, m_oDiffCharCal.m_fIp3, TRUE);
			case 4:
				pLine = (CCharElementLined*)pArea->GetAt((long)2);
				m_oDiffCharCal.m_fKid2 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp2 = CString_To_double(pLine->m_strXb);
				g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP2, m_oDiffCharCal.m_fIp2, TRUE);
			case 3:
				pLine = (CCharElementLined*)pArea->GetAt((long)1);
				m_oDiffCharCal.m_fKid1 = CalLineK(pLine);
				m_oDiffCharCal.m_fIp1 = CString_To_double(pLine->m_strXb);
				g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP1, m_oDiffCharCal.m_fIp1, TRUE);
				break;
			default:
				break;
			}
			m_oDiffCharCal.m_nKneePoints = pArea->GetCount() - 2;

			//设置速断
			pLine = (CCharElementLined*)pArea->GetTail();
			m_oDiffCharCal.m_fIsd = CString_To_double(pLine->m_strYb);
		}
		
		//设置拐点
		POS pos = pArea->GetHeadPosition();
		while (pos != NULL)
		{
			CExBaseList* pLine = (CExBaseList*)pArea->GetNext(pos);
			if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTEXPR)
			{
				m_oDiffCharCal.m_oPoints.AddTail(new CXDrawData_Point(((CCharElementExpr*)pLine)->m_strXb.toDouble(), ((CCharElementExpr*)pLine)->m_strYb.toDouble()));
			}
			else if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
			{
				m_oDiffCharCal.m_oPoints.AddTail(new CXDrawData_Point(((CCharElementLined*)pLine)->m_strXb.toDouble(), ((CCharElementLined*)pLine)->m_strYb.toDouble()));
			}
		}
		//设置速断
		CExBaseList* pLine = (CExBaseList*)pArea->GetTail();
		if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTEXPR)
		{
			m_oDiffCharCal.m_oPoints.AddTail(new CXDrawData_Point(((CCharElementExpr*)pLine)->m_strXe.toDouble(), ((CCharElementExpr*)pLine)->m_strYe.toDouble()));
		}
		else if (pLine->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
			m_oDiffCharCal.m_oPoints.AddTail(new CXDrawData_Point(((CCharElementLined*)pLine)->m_strXe.toDouble(), ((CCharElementLined*)pLine)->m_strYe.toDouble()));
		}
	}
	return TRUE;
}

float QSttMultiMacroParaEditViewDiff::CalLineK(CCharElementLined* pLine)
{
	float fXb, fXe, fYb, fYe;
	fXb = CString_To_double(pLine->m_strXb);
	fXe = CString_To_double(pLine->m_strXe);
	fYb = CString_To_double(pLine->m_strYb);
	fYe = CString_To_double(pLine->m_strYe);
	return (fYe - fYb) / (fXe - fXb);
}

void QSttMultiMacroParaEditViewDiff::slot_CalculateId(double dIr)
{
	if (!InitDiffCharCal())
	{
		return;
	}

	double dId;
	m_oDiffCharCal.CalculateId_Custom(dIr, dId);
	if (m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.m_strMacroID == STT_MACRO_ID_PsuDiffRateTest)
	{
		double dMaxdId = dId * ((QDiffRateItemParaEditWidget*)m_pSingleItemParaEditWidget)->GetBeginValText()/100;
		m_pDiffWiringWidget->GetCurrentCal(&dMaxdId, dIr);
		((QDiffRateItemParaEditWidget*)m_pSingleItemParaEditWidget)->UpdateId(dId, dMaxdId);
	}
	else if (m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner.m_strMacroID == STT_MACRO_ID_PsuDiffTimeTest)
	{
		((QDiffTimeItemParaEditWidget*)m_pSingleItemParaEditWidget)->UpdateId(dId);
	}
}
//获取最新特性曲线参数并更新到界面
void QSttMultiMacroParaEditViewDiff::UpdateParasByCharEdit()
{
	//曲线更新后，记录是否已经被抬高
	long nClock, nFaultType, nComBineFeature, nZeroSeqElimiType;
	g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE, nFaultType);
	g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE, nClock);
	g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, nComBineFeature);
	g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, nZeroSeqElimiType);
	m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType);

	m_oDiffCharCal.m_oPoints.DeleteAll();
	InitDiffCharCal();//更新算法
	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	//更新特性曲线时间定值到编辑界面
	/*UpdateCharacteristicParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	m_pSingleItemParaEditWidget->UpdateParas(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);*/

	//bIsUpdateTestPointByCharEdit = TRUE;
	CCharacteristics *pCharacteristics = g_theTestCntrFrame->m_pCharacteristics;
	pCharacteristics->ClearTestData();

	for (int i = 2; i > -1;i--)
	{
		m_pCurrMacroItemsRef = &m_oMultiMacroItemsRef[i];
		if (i == DIFF_ID_PSUDIFFHARM)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffHarmTest, CHAR_TEST_OBJECT_DRAW_LINE);//谐波制动
		}
		else if (i == DIFF_ID_PSUDIFFTIME)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_POINT);//动作时间
		}
		else if (i == DIFF_ID_PSUDIFFRATE)
		{
			((QCharactWidgetForTest *)m_pCharactInterface)->UpdateCharacteristic(STT_MACRO_ID_PsuDiffRateTest, CHAR_TEST_OBJECT_DRAW_LINE);//比率制动
		}

		POS pos = m_oMultiMacroItemsRef[i].GetHeadPosition();
		while (pos != NULL)
		{
			CSttMacroTest *pMacroTest = (CSttMacroTest *)m_oMultiMacroItemsRef[i].GetNext(pos);
			UpdateCharacteristicParas(pMacroTest);
			AddUpdateTestPoint_To_Charact(pMacroTest);
		}
		m_pMultiMacroParaEditGrid[i]->ShowDatas(&m_oMultiMacroItemsRef[i]);
	}

	//bIsUpdateTestPointByCharEdit = FALSE;
	slot_CurrMacroParaEditGridChanged(m_pMultiMacroGridTab->currentIndex());
}
void QSttMultiMacroParaEditViewDiff::UpdateCharacteristicParas(CSttMacroTest *pCurrMacroTest)
{
	if (pCurrMacroTest == NULL)
	{
		return;
	}

	CSttMacroTestParaDatas *pDstDatas = pCurrMacroTest->GetSttMacroTestParaDatas(FALSE, "");
	if (pDstDatas == NULL)
	{
		return;
	}
	GetParasDataToMacroTest(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras, pDstDatas);

	CSttMacroTestParaData *pDataFaultType = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	if (pDataFaultType == NULL)
	{
		CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
		pDataFaultType = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	}

	if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffRateTest)
	{
		CSttMacroTestParaData *pDataBeginVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
		if (pDataBeginVal == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
			pDataBeginVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
		}

		CSttMacroTestParaData *pDataEndVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
		if (pDataEndVal == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
			pDataEndVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
		}

		CSttMacroTestParaData *pDataIdSetting = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
		if (pDataIdSetting == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
			pDataIdSetting = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
		}

		CSttMacroTestParaData *pDataIr = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
		if (pDataIr != NULL)
		{
			double dId, dBeginValRate, dEndValRate, dMaxdId;
			int nFaultType = pDataFaultType->m_strValue.toInt();
			CSttMacroTestParaData *pData_ComBineFeature = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE);
			CSttMacroTestParaData *pData_ZeroSeqElimiType = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE);
			CSttMacroTestParaData *pData_Clock = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE);
			CSttMacroTestParaData *pData_CustomChar = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR);
			long nClock, nComBineFeature, nZeroSeqElimiType, nCustomChar;
			nComBineFeature = pData_ComBineFeature->m_strValue.toInt();
			nZeroSeqElimiType = pData_ZeroSeqElimiType->m_strValue.toInt();
			nClock = pData_Clock->m_strValue.toInt();
			nCustomChar = pData_CustomChar->m_strValue.toInt();

			if (!InitDiffCharCal())
			{
				return;
			}
			if ((nCustomChar == 0)&&(m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType, FALSE)))
			{
				dId = m_oDiffCharCal.CalculateId(pDataIr->m_strValue.toDouble());
			}
			else
			{
				m_oDiffCharCal.CalculateId_Custom(pDataIr->m_strValue.toDouble(), dId);
			}
			

			pCurrMacroTest->m_nModified = 1;

			dEndValRate = pDataEndVal->m_strValue.toDouble() / pDataIdSetting->m_strValue.toDouble();
			dBeginValRate = pDataBeginVal->m_strValue.toDouble() / pDataIdSetting->m_strValue.toDouble();
			double dBeginVal = dId *dBeginValRate;
			dMaxdId = dBeginVal;
 			m_pDiffWiringWidget->GetCurrentCal(&dMaxdId, pDataIr->m_strValue.toDouble());
			if (dBeginVal > dMaxdId)
			{
				dBeginVal = dMaxdId;
			}

			pDataIdSetting->m_strValue = QString::number(dId, 'f', 3);
			pDataBeginVal->m_strValue = QString::number(dBeginVal, 'f', 3);
			pDataEndVal->m_strValue = QString::number(dId *dEndValRate, 'f', 3);
		}
		
	}
	else if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffTimeTest)
	{
		CSttMacroTestParaData *pDataId = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
		if (pDataId == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
			pDataId = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
		}
		CSttMacroTestParaData *pDataIr = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR);
		if (pDataIr != NULL)
		{
			int nFaultType = pDataFaultType->m_strValue.toInt();
			CSttMacroTestParaData *pData_ComBineFeature = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE);
			CSttMacroTestParaData *pData_ZeroSeqElimiType = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE);
			CSttMacroTestParaData *pData_Clock = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE);
			CSttMacroTestParaData *pData_CustomChar = (CSttMacroTestParaData*)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR);
			long nClock, nComBineFeature, nZeroSeqElimiType, nCustomChar;
			nComBineFeature = pData_ComBineFeature->m_strValue.toInt();
			nZeroSeqElimiType = pData_ZeroSeqElimiType->m_strValue.toInt();
			nClock = pData_Clock->m_strValue.toInt();
			nCustomChar = pData_CustomChar->m_strValue.toInt();

			double dId;
			if (!InitDiffCharCal())
			{
				return;
			}
			
			if ((nCustomChar == 0) && (m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType, FALSE)))
			{
				dId = m_oDiffCharCal.CalculateId(pDataIr->m_strValue.toDouble());
			}
			else
			{
				m_oDiffCharCal.CalculateId_Custom(pDataIr->m_strValue.toDouble(), dId);
			}
			pCurrMacroTest->m_nModified = 1;
			pDataId->m_strValue = QString::number(dId, 'f', 3);
		}
	}
	else if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffHarmTest)
	{
		CSttMacroTestParaData *pDataBeginVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL);
		if (pDataBeginVal == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL);
			pDataBeginVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_BEGINVAL);
		}

		CSttMacroTestParaData *pDataEndVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL);
		if (pDataEndVal == NULL)
		{
			CheckForPresence(pDstDatas, STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL);
			pDataEndVal = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ENDVAL);
		}

		CSttMacroTestParaData *pDataRateHarmSetOld = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET);
		if (pDataRateHarmSetOld != NULL)
		{
			double dRateHarmSetOld, dRateHarmSetNew, dBeginValRate, dEndValRate;
			pCurrMacroTest->m_nModified = 1;

			dBeginValRate = pDataBeginVal->m_strValue.toDouble() / pDataRateHarmSetOld->m_strValue.toDouble();
			dEndValRate = pDataEndVal->m_strValue.toDouble() / pDataRateHarmSetOld->m_strValue.toDouble();

			CDvmData *pDataRateHarmSetNew = (CDvmData *)g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_RATEHARM);

			pDataBeginVal->m_strValue = QString::number(pDataRateHarmSetNew->m_strValue.toDouble() *dBeginValRate, 'f', 3);
			pDataEndVal->m_strValue = QString::number(pDataRateHarmSetNew->m_strValue.toDouble() *dEndValRate, 'f', 3);
		}
	}
	
}

void QSttMultiMacroParaEditViewDiff::GetParasDataToMacroTest(CDataGroup *pParas, CExBaseList* pTestmacro)
{
	if (pParas == NULL || pTestmacro == NULL)
	{
		return;
	}
		
	POS pos = pTestmacro->GetHeadPosition();
	while (pos != NULL)
	{
		CSttMacroTestParaData *pData = (CSttMacroTestParaData*)pTestmacro->GetNext(pos);
		SetValueToMacroTest(pParas, pData);
	}
}
void QSttMultiMacroParaEditViewDiff::SetValueToMacroTest(CDataGroup *pParas, CSttMacroTestParaData *pData)
{
	if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_MINAXIS)//定值整定方式
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_MINAXIS, pData->m_strValue);
		UpdateMinaxis(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSEL)//基准电流选择
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSEL, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSET)//基准电流设定值
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_INSET, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IQUICK)//差动速断电流
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IQUICK, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IDOOR)//差动门槛电流
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_IDOOR, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KNEEPOINTS)//比率制动拐点数
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KNEEPOINTS, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP1)//比率制动拐点1电流
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP1, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP2)//比率制动拐点2电流
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP2, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP3)//比率制动拐点3电流
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_LIMP3, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID0)//启动段斜率
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID0, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID1)//基波比率制动特性斜率1
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID1, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID2)//基波比率制动特性斜率2
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID2, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID3)//基波比率制动特性斜率3
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_KID3, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR)//是否自定义曲线
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET )//谐波制动系数
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_RATEHARM, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX)//谐波次数
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE)//组合特性
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, pData->m_strValue);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE)//零序消除方式
	{
		pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, pData->m_strValue);
	}
	//以下是MacroTest通用参数更新至paras参数
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME)       //准备时间(s)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_PREPARETIME, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME)		//故障前时间(s)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_PREFAULTTIME, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIMEAFTER)         //动作后持续时间(s)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_TIMEAFTER, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE)			//各侧平衡系数
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_KPSETMODE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SN)				//变压器额定容量(MVA)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_SN, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HUN)				//高压侧额定电压(kV)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_HUN, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_MUN)				//中压侧额定电压(kV)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_MUN, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_LUN)				//低压侧额定电压(kV)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_LUN, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH)				//高压侧CT一次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTPH, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM)				//中压侧CT一次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTPM, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL)				//低压侧CT一次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTPL, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH)				//高压侧CT二次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTSH, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM)				//中压侧CT二次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTSM, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL)				//低压侧CT二次值(A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTSL, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET)			//高压侧差动平衡系数
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_KPHSET, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET)			//中压侧差动平衡系数
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_KPMSET, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET)			//低压侧差动平衡系数
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_KPLSET, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH)				//高压侧绕组接线型式
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_WINDH, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM)				//中压侧绕组接线型式
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_WINDM, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL)				//低压侧绕组接线型式
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_WINDL, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE)		//校正选择
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_PHCORRECTMODE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND)			//测试绕组
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ADOPTWIND, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE)	//测试绕组之间角差(钟点数)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR)			//平衡系数计算
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_JXFACTOR, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE)		//搜索方法
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_SEARCHMODE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT)			//CT极性
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CTPOINT, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION)		//制动方程
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_IREQUATION, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K)					//K1
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_K, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_K2)				//K2
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_K2, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE)	//组合特性
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE)  //零序消除方式
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING)			//接地
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_EARTHING, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_STEP)				//测试精度
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_STEP, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG1)				//Ua、Ub、Uc(V)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_VG1, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_VG2)				//Ua2、Ub2、Uc2(V)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_VG2, pData->m_strValue, TRUE);
	}
	else if(pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_A)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_A, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_B)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_B, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_C)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_C, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_D)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_D, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_E)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_E, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_F)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_F, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_G)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_G, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_H)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_H, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_AndOr)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_AndOr, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B01)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B01, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B02)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B02, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B03)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B03, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B04)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B04, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B05)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B05, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B06)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B06, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B07)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B07, pData->m_strValue, TRUE);
	}
	else if (pData->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID__B08)
	{
		pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID__B08, pData->m_strValue, TRUE);
	}
}

void QSttMultiMacroParaEditViewDiff::UpdateMinaxis(int nMinaxis)//0:有名值(A) 1:标幺值(In)
{
	((QDiffRateItemParaEditWidget *)m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFRATE])->UpdateMinaxis(nMinaxis);
	((QDiffTimeItemParaEditWidget *)m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFTIME])->UpdateMinaxis(nMinaxis);
	((QDiffHarmItemParaEditWidget *)m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFHARM])->UpdateMinaxis(nMinaxis);

	if (m_pGridInst_DiffRate != NULL)
	{
		CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_DiffRate->GetInst_Cols();
		CSttGdInst_Col *pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_TESTRSLT);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(A)";
			}
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = "Ir(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = "Ir(A)";
			}
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*理论值Id*/g_sLangTxt_Diff_IdTheory + "(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*理论值Id*/g_sLangTxt_Diff_IdTheory + "(A)";
			}
		}
	}

	if (m_pGridInst_DiffTime != NULL)
	{
		CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_DiffTime->GetInst_Cols();
		CSttGdInst_Col *pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_TESTRSLT);
		if (pSttGdInst_Col)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result + "(s)";
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_ID);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*差动电流*/g_sLangTxt_State_DifferentCur + "(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*差动电流*/g_sLangTxt_State_DifferentCur + "(A)";
			}
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_IR);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*制动电流*/g_sLangTxt_State_BrakingCur + "(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*制动电流*/g_sLangTxt_State_BrakingCur + "(A)";
			}
		}
	}
	
	if (m_pGridInst_DiffHarm != NULL)
	{
		CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_DiffHarm->GetInst_Cols();
		CSttGdInst_Col *pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_TESTRSLT);
		if (pSttGdInst_Col)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*测试结果*/g_sLangTxt_Diff_Result;
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RATEHARMSET);
		if (pSttGdInst_Col)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*谐波制动系数*/g_sLangTxt_State_HarmonicBrakingcoefficient;
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_HARMINDEX);
		if (pSttGdInst_Col)
		{
			pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*谐波次数*/g_sLangTxt_Native_harmonicOrder;
		}
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_ID);
		if (pSttGdInst_Col)
		{
			if (nMinaxis)
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(Ie)";
			}
			else
			{
				pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*整定值*/g_sLangTxt_State_SettingValue + "(A)";
			}
		}
	}
	m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFRATE]->InitColDef(m_pGridInst_DiffRate, m_pMultiMacroRef[DIFF_ID_PSUDIFFRATE], g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFTIME]->InitColDef(m_pGridInst_DiffTime, m_pMultiMacroRef[DIFF_ID_PSUDIFFTIME], g_theHtmlRptGenFactory->m_pDataTypes);
	m_pMultiMacroParaEditGrid[DIFF_ID_PSUDIFFHARM]->InitColDef(m_pGridInst_DiffHarm, m_pMultiMacroRef[DIFF_ID_PSUDIFFHARM], g_theHtmlRptGenFactory->m_pDataTypes);
}
BOOL QSttMultiMacroParaEditViewDiff::AddUpdateTestPoint_To_Charact()
{
	return TRUE;
}
BOOL QSttMultiMacroParaEditViewDiff::AddItem_From_SearchLine(int nFaultType, double dIr, double dFaultTime, int nErrorLogic, double dAbsErr,double dRelErr)
{
	if (m_pMulitMacroRootItems == NULL)
	{
		return FALSE;
	}
	
	CSttItems *pParentItems = GetRootItems_CurrTestMacro(&((QDiffRateItemParaEditWidget*)m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFRATE])->m_oSttMacroTest_Inner);

	if (pParentItems == NULL)
	{
		return FALSE;
	}

	if (m_pCharactInterface == NULL)
	{
		m_pCharactInterface = g_theTestCntrFrame->GetInternationalCharactInterface();
	}
	CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&((QDiffRateItemParaEditWidget*)m_pMultiItemParaEditWidget[DIFF_ID_PSUDIFFRATE])->m_oSttMacroTest_Inner);


	double dId, dBeginVal, dEndVal, dBeginValRate, dEndValRate,dMaxdId;

	CDvmData *pData_FaultType = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
	pData_FaultType->m_strValue = QString::number(nFaultType);

	CDvmData *pData_FaultTime = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_FAULTTIME);
	pData_FaultTime->m_strValue = QString::number(dFaultTime);

	CDvmData *pData_ErrorLogic = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RSLTEVAL);
	pData_ErrorLogic->m_strValue = QString::number(nErrorLogic);

	CDvmData *pData_AbsErr = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ABSERR);
	pData_AbsErr->m_strValue = QString::number(dAbsErr);

	CDvmData *pData_RelErr = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RELERR);
	pData_RelErr->m_strValue = QString::number(dRelErr);

	CDvmData *pData_BeginVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_BEGINVAL);
	CDvmData *pData_EndVal = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_ENDVAL);
	CDvmData *pData_IdSetting = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IDSETTING);
	CDvmData *pData_Ir = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_IR);
	if (pData_Ir != NULL)
	{
		pData_Ir->m_strValue = QString::number(dIr);
		if (!InitDiffCharCal())
		{
			return FALSE;
		}

		long nClock, nComBineFeature, nZeroSeqElimiType, nCustomChar;
		pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, nComBineFeature);
		pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, nZeroSeqElimiType);
		pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE, nClock);
		pMacroParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_CUSTOMCHAR, nCustomChar);
		if ((nCustomChar == 0) && (m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType, FALSE)))
		{
			dId = m_oDiffCharCal.CalculateId(pData_Ir->m_strValue.toDouble());
		}
		else
		{
			m_oDiffCharCal.CalculateId_Custom(pData_Ir->m_strValue.toDouble(), dId);
		}


		dBeginValRate = pData_BeginVal->m_strValue.toDouble() / pData_IdSetting->m_strValue.toDouble();
		dEndValRate = pData_EndVal->m_strValue.toDouble() / pData_IdSetting->m_strValue.toDouble();
		pData_IdSetting->m_strValue = QString::number(dId, 'f', 3);
		dBeginVal = dId *dBeginValRate;
		dMaxdId = dBeginVal;
		m_pDiffWiringWidget->GetCurrentCal(&dMaxdId, pData_Ir->m_strValue.toDouble());
		if (dBeginVal > dMaxdId)
		{
			dBeginVal = dMaxdId;
		}

		pData_BeginVal->m_strValue = QString::number(dBeginVal, 'f', 3);
		pData_EndVal->m_strValue = QString::number(dId *dEndValRate, 'f', 3);
		dEndVal = pData_EndVal->m_strValue.toDouble();
	}

	CString strItemPath;
	strItemPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	CString strMacroUI_ID, strItemName, strItemID;
	strItemName = m_pSingleMacroRef->m_strName;
	strItemID = m_pSingleMacroRef->m_strID;
	strMacroUI_ID = GetMacroID();
	pParentItems->InitNameAndIDForPaste(strItemName, strItemID);

	g_nUpdateMultiMacroParaEditView = 0;
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddOneMacroItem(pMacroParas, strItemName/*pNewTest->m_strName*/, strItemID/*pNewTest->m_strID*/, strItemPath, 0,
		m_pSingleMacroRef->m_strID, STT_ORG_MACRO_DiffTest_I);
	g_nUpdateMultiMacroParaEditView = 1;

	if (nRet != STT_CMD_ExecStatus_SUCCESS)
	{
		//		pParentItems->Delete(pNewTest);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能执行命令失败(%ld)."), nRet);
		return FALSE;
	}

	CSttMacroTest *pNewTest = (CSttMacroTest*)pParentItems->FindByID(strItemID);

	if (pNewTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("添加单个电气量测试功能失败."));
		return FALSE;
	}
	CSttMacroTestParaDatas *pNewDataParas = pNewTest->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	if (pNewDataParas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[AddItem_From_Charact]参数为空"));
		return FALSE;
	}

	m_pCurrMacroItemsRef->AddTail(pNewTest);
	m_pCurrMacroParaEditGrid->InsertData(pNewTest);
	//添加测试线
	double dBegX, dBegY, dEndX, dEndY;
	CString strTmpString;
	strTmpString = pNewTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	dBegX = dIr;
	dBegY = dBeginVal;
	dEndX = dBegX;
	dEndY = dEndVal;
	m_pCharactInterface->AddUpdateTestLine(strTmpString, dBegX, dBegY, dEndX, dEndY, nFaultType);

	//m_pCurrMacroParaEditGrid->SelectRow(m_pCurrMacroItemsRef->GetCount());

	//通过特性图添加测试项后更新按键使能
	UpdateBottomBtnsEnable();
	return TRUE;
}
BOOL QSttMultiMacroParaEditViewDiff::UpdateTestUI_To_Charact(CSttMacroTest *pCurrMacroTest, int nState)
{
	if (pCurrMacroTest == NULL)
	{
		return FALSE;
	}

	CSttMacroTestParaDatas *pDstDatas = pCurrMacroTest->GetSttMacroTestParaDatas(FALSE, "");
	if (pDstDatas == NULL)
	{
		return FALSE;
	}
	long nClock, nFaultType, nComBineFeature, nZeroSeqElimiType;

	if (pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffRateTest || pCurrMacroTest->m_strMacroID == STT_MACRO_ID_PsuDiffTimeTest)
	{
		CSttMacroTestParaData *pDataFaultType = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);
		nFaultType = pDataFaultType->m_strValue.toInt();
		CSttMacroTestParaData *pDataClock = (CSttMacroTestParaData *)pDstDatas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_TRANSGROUPMODE);
		nClock = pDataClock->m_strValue.toInt();
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE, nFaultType);
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_COMBINEDFEATURE, nComBineFeature);
		g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras.GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_ZEROSEQELIMITYPE, nZeroSeqElimiType);

		if (m_oDiffCharCal.CalCombinedFeature(nComBineFeature, nZeroSeqElimiType, nClock, nFaultType)) 
		{
			m_oDiffCharCal.Cal();
			CCharacteristic* pChar = stt_Frame_Characteristics()->FindByID_Char(STT_MACRO_ID_PsuDiffRateTest);
			CCharacterArea* pArea = pChar->GetCharacterArea();

			POS pos = m_oDiffCharCal.m_oPoints.GetHeadPosition();
			CXDrawData_Point* pLast = NULL;
			CString strFX, strFY;
			long nIndex = 0;
			while (pos)
			{
				CXDrawData_Point* pt = (CXDrawData_Point*)m_oDiffCharCal.m_oPoints.GetNext(pos);
				if (pLast)
				{
					CCharElementLined* pLine = (CCharElementLined*)pArea->GetAt((long)nIndex);
					strFX.Format("%.3f", pLast->m_fX);
					strFY.Format("%.3f", pLast->m_fY);
					pLine->SetBeginPoint(strFX, strFY);
					strFX.Format("%.3f", pt->m_fX);
					strFY.Format("%.3f", pt->m_fY);
					pLine->SetEndPoint(strFX, strFY);
					nIndex++;
				}
				pLast = pt;
			}
			UpdateParasByCharEdit();
			m_pCurrMacroParaEditGrid->SelectRow(pCurrMacroTest);
		}
	}
	return FALSE;
}
void QSttMultiMacroParaEditViewDiff::GetDatas(CDataGroup *pParas)
{
	if (m_pMulitMacroRootItems == NULL)
	{
		return ;
	}
	CDataGroup *pMacroParas = GetAddOneItem_DataGroup(&m_pSingleItemParaEditWidget->m_oSttMacroTest_Inner);
	CDvmData *pData_FaultType = (CDvmData*)pMacroParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE);

	pParas->SetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE, pData_FaultType->m_strValue, TRUE);
}
void QSttMultiMacroParaEditViewDiff::InitGridTitleLanguage()
{
	if (m_pGridInst_DiffRate == NULL)
		return;

	CSttGdInst_Cols *pSttGdInst_Cols = m_pGridInst_DiffRate->GetInst_Cols();
	CSttGdInst_Col *pSttGdInst_Col = NULL;
	POS pos = pSttGdInst_Cols->GetHeadPosition();
	while (pos != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos);
		SetValueToInstColName(pSttGdInst_Col);
	}

	if (m_pGridInst_DiffTime == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_DiffTime->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos2 = pSttGdInst_Cols->GetHeadPosition();
	while (pos2 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos2);
		SetValueToInstColName(pSttGdInst_Col);
	}

	if (m_pGridInst_DiffHarm == NULL)
		return;

	pSttGdInst_Cols = m_pGridInst_DiffHarm->GetInst_Cols();
	pSttGdInst_Col = NULL;
	POS pos3 = pSttGdInst_Cols->GetHeadPosition();
	while (pos3 != NULL)
	{
		pSttGdInst_Col = (CSttGdInst_Col *)pSttGdInst_Cols->GetNext(pos3);
		SetValueToInstColName(pSttGdInst_Col);
	}
}
void QSttMultiMacroParaEditViewDiff::SetValueToInstColName(CSttGdInst_Col *pSttGdInst_Col)
{
	if (pSttGdInst_Col == NULL)
		return;
	if (pSttGdInst_Col->m_pSttGdColDef_Ref == NULL)
		return;

	if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_SELECT)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*选择*/g_sLangTxt_Diff_Select;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_GRID_PARAS_ID_STATE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*状态*/g_sLangTxt_Syn_State;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_FAULTTYPE)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*故障相*/g_sLangTxt_Diff_FaultType2;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_RATE_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*误差类型*/g_sLangTxt_StateEstimate_ErrorType;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_TIME_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*误差类型*/g_sLangTxt_StateEstimate_ErrorType;
	}
	else if (pSttGdInst_Col->m_pSttGdColDef_Ref->m_strID == STT_MULTI_MACRO_DIFF_PARAS_ID_HARM_RSLTEVAL)
	{
		pSttGdInst_Col->m_pSttGdColDef_Ref->m_strName = /*误差类型*/g_sLangTxt_StateEstimate_ErrorType;
	}
}