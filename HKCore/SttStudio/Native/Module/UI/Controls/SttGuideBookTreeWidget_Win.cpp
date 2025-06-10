#include "SttGuideBookTreeWidget_Win.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include <QMessageBox>
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "SttTestCntrFrameWin.h"
#include "ViewRpts/SttGbViewRpts.h"
#include "../SttTestCntrCmdDefine.h"
#include "../../SttTestCtrl/SttTestCtrlCntrWin.h"
#include "../ResultExpr/ResultExprCanvas.h"
#include "SttGbSafetyEdit.h"

#include "../../XLangResource_Native.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttGuideBookTreeWidget_Win::QSttGuideBookTreeWidget_Win(CExBaseObject *pSttGuideBook, CSttFrame_GbTree *pTreeParas, QWidget *parent)
    : QSttGuideBookTreeWidget(pSttGuideBook, pTreeParas, parent)
{

	//这个是将鼠标移动事件改为实时监测，默认的是按下才监测 sf 20220329
	m_pTreeCtrl->setMouseTracking(true);
	m_bTreeUpdateFinish = FALSE;
	m_bTreeCheckStateChanging = FALSE;
	m_pTreeCtrl->setIconSize(QSize(36,36));
	m_pTreeCtrl->InitAllIcons();
	m_pTreeCtrl->setStyleSheet("QTreeWidget::item{height:25px}"); 

	//树形节点鼠标移动事件 sf 20220329
    connect(m_pTreeCtrl,SIGNAL(sig_MouseMoveGbTree(QMouseEvent*)),this,SLOT(slot_SttMouseMoveEventGbTree(QMouseEvent*)));
	setContextMenuPolicy (Qt::CustomContextMenu);
 }

void QSttGuideBookTreeWidget_Win::InitButton()
{
    QSttGuideBookTreeWidget::InitButton();

    QString strPicPath = _P_GetResourcePath();
 
	m_pBtnDeleteCurr = NewButton(strPicPath + "TestDelete.png");
    m_pBtnEditCurr = NewButton(strPicPath + "TestEdit.png");
	m_pBtnNew = NewButton(strPicPath + "TesNew.png");
	m_pBtnSaveCurr = NewButton(strPicPath + "TesSave.png");

	connect(m_pBtnDeleteCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnDeleteCurr()));
	connect(m_pBtnEditCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnEditCurr()));
	connect(m_pBtnNew, SIGNAL(clicked()),this,SLOT(slot_OnBtnNew()));
	connect(m_pBtnSaveCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnSaveCurr()));
}

BOOL QSttGuideBookTreeWidget_Win::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	
{
	if (pSelObj->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		g_theTestCntrFrame->ViewCmdEditWidget(pSelObj);
		return TRUE;
	}

	if (pSelObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		g_theTestCntrFrame->ViewMacroEditWidget(pSelObj);
		return TRUE;
	}

	if (pSelObj->GetClassID() == STTGBXMLCLASSID_CSTTSAFETY)
	{
		slot_OnBtnEditSafety();
		return TRUE;
	}

	return FALSE;
}

void QSttGuideBookTreeWidget_Win::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(pSelObj, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (g_theTestCntrFrame->IsTestStarted())
	{
		return;
	}
	//先判断参数是否发生改变，若发生改变，则提示保存+

	g_theTestCntrFrame->PromptToSave(pSelObj);
	m_pCurrSelGbItem = pSelObj;
   
	//根据当前选中的节点，查找最近的m_strType == rootnode的节点，切换显示模板视图
	//最开始计划做在双击事件中，但双击事件响应成了两次单击事件，暂时先做在此处
	SwitchMacroViewByCurrSel(pSelObj);

	//CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(pSelObj, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems != NULL)
	{
		if (g_theTestCntrFrame->GetMacroEditView() != NULL)
		{
			g_theTestCntrFrame->GetMacroEditView()->m_pSttItems = pItems;
		}
	}

	if(pItems && pItems->m_strCharacteristicID.GetLength())
	{
		g_theTestCntrFrame->UpdateButtonsStateByID(STT_CNTR_CMD_CharDrawView, TRUE);
		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->EnableAction(STT_CNTR_CMD_CharDrawView, TRUE);
	}
	else
	{
		g_theTestCntrFrame->UpdateButtonsStateByID(STT_CNTR_CMD_CharDrawView, FALSE);
		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->EnableAction(STT_CNTR_CMD_CharDrawView, FALSE);
	}

	((QSttTestCntrFrameWin*)g_theTestCntrFrame)->UpdateCmdButtonsState_AddMacro();
}

void QSttGuideBookTreeWidget_Win::HideAllBtns()
{
	QSttGuideBookTreeWidget::HideAllBtns();

// 	m_pBtnDeleteCurr->hide();
// 	m_pBtnEditCurr->hide();
// 	m_pBtnNew->hide();
// 	m_pBtnSaveCurr->hide();
}

void QSttGuideBookTreeWidget_Win::UpdateButtons()
{
	m_bHasButtonsShow = FALSE;

	if (g_pTheSttTestApp->m_pTestCtrlCntr->IsTestStarted())
	{
		return;
	}

	if (m_pCurrSelGbItem == NULL)
	{
		HideAllBtns();
		return;
	}

	QSttGuideBookTreeItem *pGbTreeItem = (QSttGuideBookTreeItem*)m_pCurrSelGbItem->m_dwItemData;
	QList<QToolButton*> listShow;
	QRect rc;
	rc = m_pTreeCtrl->visualItemRect(pGbTreeItem);//获取当前点击节点位置
	m_rectClicked = rc;

	QRect rcTree;
	rcTree = m_pTreeCtrl->rect();
	int nSize = rc.height() + 4;

	//全部隐藏
	HideAllBtns();

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	if(nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{//Device根节点
		listShow.append(m_pBtnNew);
		listShow.append(m_pBtnTestThis);
		listShow.append(m_pBtnTestFrom);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{//项目分类节点
		CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;

		if (pItems->m_strType == GBITEMS_NODETYPE_ROOTNODE)
		{
			listShow.append(m_pBtnEditCurr);
			//shaolei注释 20220404  防止添加功能时选错功能模块，则需要整个删除
			listShow.append(m_pBtnDeleteCurr);
			listShow.append(m_pBtnSaveCurr);
		}

		if (pItems->m_strType == GBITEMS_NODETYPE_ITEMS)
		{//人工添加的项目分类节点
			listShow.append(m_pBtnNew);
			listShow.append(m_pBtnEditCurr);

			if (pItems->GetCount() == 0)
			{//没有子对象，可以删除当前节点
				listShow.append(m_pBtnDeleteCurr);
			}
		}

		if (pItems->GetCount() >= 0)
		{//有子对象，就可以测试，暂时不考虑当前新项目分类下没有可执行的项目，后续增加
			//可以测试
			listShow.append(m_pBtnTestThis);
			listShow.append(m_pBtnTestFrom);
		}
	}
	else
	{
		listShow.append(m_pBtnTestThis);
		listShow.append(m_pBtnTestFrom);
	}

	long nCount = listShow.size();
	long nLeft = rcTree.right() - nCount * nSize;
	QToolButton *pBtn = NULL;
	long nTop = rc.top() - 1;

	for (long k=0; k<nCount; k++)
	{
		pBtn = listShow.at(k);
		pBtn->setGeometry(nLeft + nSize * k, nTop, nSize, nSize);
		pBtn->show();
	}

	m_bHasButtonsShow = TRUE;
	listShow.clear();
}

void QSttGuideBookTreeWidget_Win::slot_ItemStateChanged( CExBaseObject *pCurTestItem )
{
	HideAllBtns();
	m_pTreeCtrl->UpdateItemColour();

	//对于Windows平台的单机软件，由于可能添加了多个测试功能，在项目状态改变时，需要相应地切换参数视图、矢量图、状态图、信息图、硬件资源等
	SwitchMacroViewByCurrSel(pCurTestItem);
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnTestFrom()
{
	if (!IsContinueTest_FromTree(1))
	{
		return;
	}

	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	QSttGuideBookTreeWidget::slot_OnBtnTestFrom();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnTestThis()
{
	if (!IsContinueTest_FromTree(0))
	{
		return;
	}

	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	QSttGuideBookTreeWidget::slot_OnBtnTestThis();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnNew()
{
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	QSttGbItemsEdit dlg(NULL, pParent, this);

	if (dlg.exec() == 0)
	{
		return;
	}

	CSttItems *pNewItems = (CSttItems *)dlg.m_pSttItems;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pNewItems);
	m_pTreeCtrl->AddObj(pNewItems, TRUE);
// 	slot_ShowItems(pParent);
// 
// 	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
// 
// 	if (hItem != NULL)
// 	{
// 		hItem->setExpanded(true);
// 	}

	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->NewItems(strParentItemPath, pNewItems);
	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pNewItems->m_strID, pNewItems->m_strName
		, pNewItems->m_nTestTimes, pNewItems->m_nRptTitle, pNewItems->m_nTitleLevel);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnEditCurr()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}
	
	CString strItemsID = m_pCurrSelGbItem->m_strID;
	CString strItemsName = m_pCurrSelGbItem->m_strName;  //编辑前的项目的名称、ID
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem->GetParent();
	QSttGbItemsEdit dlg((CSttItems*)m_pCurrSelGbItem, pParent, this);
	
	if (dlg.exec() == 0)
	{
		return;
	}

	long nRepeatTimes = 0;
	long nRptTitle = 0;
	long nTitleLevel = 1;

	if (m_pCurrSelGbItem->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems *)m_pCurrSelGbItem;
		nRepeatTimes = pItems->m_nTestTimes;
		nRptTitle = pItems->m_nRptTitle;
		nTitleLevel = pItems->m_nTitleLevel;

		QExBaseTreeWidgetItem* pSelItem = (QExBaseTreeWidgetItem*)m_pTreeCtrl->currentItem();
		m_pTreeCtrl->UpdateTestTimesIcon(pSelItem, pItems);
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_EditItems(pParent, m_pCurrSelGbItem, strItemsID);
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pTreeCtrl->UpdateObject(m_pCurrSelGbItem);
	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	g_theGbSmartGenWzd->EditItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), strItemsID, strItemsName, m_pCurrSelGbItem
		, nRepeatTimes, nRptTitle, nTitleLevel);
	g_theTestCntrFrame->FillRptTitle(m_pCurrSelGbItem);//2023.7.25 zhouhj 更新当前测试项标题
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnDeleteCurr()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CString strName = m_pCurrSelGbItem->m_strName;
	CString strMsg, strAdd;
	CString strID = m_pCurrSelGbItem->m_strID;
	strMsg = /*_T("确定要删除 [ ")*/g_sLangTxt_Native_DeletestrMsg;
	strMsg += strName;
	strAdd = /*_T(" ] 吗？删除后无法恢复！")*/g_sLangTxt_Native_DeletestrMsg3;
	strMsg += strAdd;
	CString strTitle;
	strTitle = /*_T("确认删除项目")*/g_sLangTxt_Native_ConfirmDelProj;
	int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem->GetParent();
	CExBaseObject *pCurr = m_pCurrSelGbItem;

	//先关闭相关的视图
	g_theTestCntrFrame->OnDeleteCurr(m_pCurrSelGbItem);

	CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrSelGbItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems == m_pCurrSelRootNode && pItems == pCurr)
	{
		//当被删除的项目是根节点时，将当前选中的根节点置NULL
		m_pCurrSelRootNode = NULL;
		m_strCurrSelRootNodePath = _T("");
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_DeleteItems(pParent, pCurr);
	m_pCurrSelGbItem = NULL;
	g_theGbSmartGenWzd->DeleteItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pCurr);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	m_pTreeCtrl->DeleteObject(pCurr);
	pParent->Delete(pCurr);

	CString strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->DeleteMacroTestReport(strParentPath, strID);
	QExBaseTreeWidgetItem* hSelItem = (QExBaseTreeWidgetItem*)m_pTreeCtrl->currentItem();

	if (hSelItem != NULL)
	{
		m_pCurrSelGbItem = hSelItem->m_pItemData;

		if (m_pCurrSelGbItem->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			//说明被删除的是最后一个测试项
			m_pCurrSelRootNode = NULL;
			m_strCurrSelRootNodePath = _T("");
		}

		m_pTreeCtrl->OnItemSelChanged(m_pCurrSelGbItem);
	}

	//Device节点不允许删除，因此此处若返回为0，则表示恢复到新建测试后的状态
	long nCount = g_theTestCntrFrame->GetGbItemCount();

	if (nCount == 0)
	{
		((QSttTestCntrFrameWin *)g_theTestCntrFrame)->UpdateToolButtons_AfterNew();
		((QSttTestCntrFrameWin *)g_theTestCntrFrame)->ReInitViews();
	}
	//g_theTestCntrFrame->UpdateStartStopButtonByItemCount();
//	UpdateButtons();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnSaveCurr()
{
	QSttTestCntrFrameWin *pSttTestCntrFrameWin = (QSttTestCntrFrameWin*)g_theTestCntrFrame;
	pSttTestCntrFrameWin->CharactDatasToTestMacroParas();
	//获取最新的界面参数，并将界面参数刷新到CSttTestCtrlCntrBase :: m_oTestMacroUI_Paras，即QSttTestCntrFrameWin :: m_pTestMacroUI_Paras
	if (! g_theTestCntrFrame->GetDatas())
	{
		return;
	}

	CString strItemParentPath, strRootNodeID/*, strRootNodeName*/;
	CExBaseObject *pParent = NULL;

	if (m_pCurrSelRootNode != NULL)
	{
		pParent = (CExBaseObject *)m_pCurrSelRootNode->GetParent();
		/*strRootNodeName = m_pCurrSelRootNode->m_strName;*/
		strRootNodeID = m_pCurrSelRootNode->m_strID;
	}
	else
	{
		pParent = (CExBaseObject *)m_pCurrSelGbItem->GetParent();
	}
	
	strItemParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->OnSaveCurr(m_pCurrSelRootNode);   

	/*  以下代码，移动到FrameWin中   shaolei  2023-3-23
	CGbMacroGenWzd *pMacroGen = (CGbMacroGenWzd *)g_theGbSmartGenWzd->FindMacroGen(strRootNodeID
		, strRootNodeName, strItemParentPath);

	if (pMacroGen != NULL)
	{
		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, strRootNodeName
			, strRootNodeID, pMacroGen->m_pCmdGenParas, g_theGbSmartGenWzd->m_strDvmFile
			, pMacroGen->m_strTestClass, pMacroGen->m_nRepeatTimes);
	}
	else
	{
		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, strRootNodeName, strRootNodeID);
	}
	*/

	g_pTheSttTestApp->m_pTestCtrlCntr->WaitCmdReplyProcess();

	//保存后，还需要处理单独添加的电气量项目和通讯命令项目
	CString strRootNodePath;

	if (strItemParentPath.GetLength() > 0)
	{
		strRootNodePath = strItemParentPath + _T("$");
	}
	
	strRootNodePath += strRootNodeID;

	After_SaveCurr(strRootNodePath);
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnMoveUp()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CSttItemBase *pParent = (CSttItemBase*)m_pCurrSelGbItem->GetParent();
	CSttItemBase *pPrevItem = pParent->GetPrevItem((CSttItemBase*)m_pCurrSelGbItem);

	if (pPrevItem == NULL)
	{
		return;
	}

	CExBaseObject *pCurr = m_pCurrSelGbItem;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_MoveUpItem(pParent, pCurr);
	//g_theGbSmartGenWzd->DeleteItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pCurr);

	pParent->ChangePosition(pPrevItem, m_pCurrSelGbItem);
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pTreeCtrl->UpdateObject(pParent, TRUE);
	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	CString strParentItemPath;
	strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->MoveItem(strParentItemPath, pCurr, STT_CMD_PARA_generate_items_move_up);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnMoveDown()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CSttItemBase *pParent = (CSttItemBase*)m_pCurrSelGbItem->GetParent();
	CSttItemBase *pNextItem = pParent->GetNextItem((CSttItemBase*)m_pCurrSelGbItem);

	if (pNextItem == NULL)
	{
		return;
	}

	CExBaseObject *pCurr = m_pCurrSelGbItem;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_MoveDownItem(pParent, pCurr);
	//g_theGbSmartGenWzd->DeleteItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pCurr);

	pParent->ChangePosition(pNextItem, m_pCurrSelGbItem);
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pTreeCtrl->UpdateObject(pParent, TRUE);
	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	CString strParentItemPath;
	strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->MoveItem(strParentItemPath, pCurr, STT_CMD_PARA_generate_items_move_down);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnItemCopy()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CSttItemBase *pParent = (CSttItemBase*)m_pCurrSelGbItem->GetParent();
	CString strParentItemPath, strItemPath;
	strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	g_theGbSmartGenWzd->SetItemCopy(strParentItemPath, m_pCurrSelGbItem, strItemPath);
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnItemPaste()
{
	CString strItemCopyType = g_theGbSmartGenWzd->GetItemCopyType();
	if (strItemCopyType == _T("null"))
	{
		return;
	}

	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CSttItemBase *pParent = (CSttItemBase*)m_pCurrSelGbItem;//->GetParent();
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_ItemPaste(pParent
		, g_theGbSmartGenWzd->m_pCurrItemCopy->m_strItemPath);

	CSttGuideBook *pGuideBook = ((CSttTestCtrlCntrWin*)(g_pTheSttTestApp->m_pTestCtrlCntr))->m_pSttGuideBook;
	CSttItemBase *pSrcItemBase = stt_gb_find_itembase(pGuideBook, g_theGbSmartGenWzd->m_pCurrItemCopy->m_strItemPath);
	CExBaseObject *pDestItem = NULL;
	BOOL bRootNode = FALSE;

	if (strItemCopyType == _T("items"))
	{
		CSttItems *pSrcItem = (CSttItems *)pSrcItemBase;
		CSttItems *pNewItem = (CSttItems *)pSrcItem->CloneEx(TRUE, TRUE);
		pParent->InitNameAndIDForPaste(pNewItem);
		pParent->AddNewChild(pNewItem);
		pDestItem = pNewItem;

		if (pSrcItem->IsTypeRootNode())
		{
			bRootNode = TRUE;
		}
	}
	else if (strItemCopyType == _T("macrotest"))
	{
		CSttMacroTest *pSrcItem = (CSttMacroTest *)pSrcItemBase;
		CSttMacroTest *pNewItem = (CSttMacroTest *)pSrcItem->CloneEx(TRUE, TRUE);
		pParent->InitNameAndIDForPaste(pNewItem);
		pParent->AddNewChild(pNewItem);
		pDestItem = pNewItem;
	}
	else if (strItemCopyType == _T("commcmd"))
	{
		CSttCommCmd *pSrcItem = (CSttCommCmd *)pSrcItemBase;
		CSttCommCmd *pNewItem = (CSttCommCmd *)pSrcItem->CloneEx(TRUE, TRUE);
		pParent->InitNameAndIDForPaste(pNewItem);
		pParent->AddNewChild(pNewItem);
		pDestItem = pNewItem;
	}

	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pTreeCtrl->UpdateObject(pParent, TRUE);
	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	CString strParentItemPath;
	strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	g_theGbSmartGenWzd->ItemPaste(strParentItemPath, pDestItem);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();

	if (bRootNode)
	{
		//处理粘贴项目的报告
		CSttItems *pRootNode = (CSttItems *)pDestItem;
		g_theTestCntrFrame->ItemPaste_RootNode(pRootNode, pParent);
	}
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnNew_AFT()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	CSttItems *pAft = stt_gb_new_items(pParent, /*"测试后恢复"*/g_sLangTxt_Native_RestoreAfterTest, STT_ITEMS_ID_AFTERTEST);
	pAft->m_strType = GBITEMS_NODETYPE_NONE;  //测试后恢复，不允许再新建分类，设置成none
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pAft);
	m_pTreeCtrl->AddObj(pAft, TRUE);

// 	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
// 
// 	if (hItem != NULL)
// 	{
// 		hItem->setExpanded(true);
// 	}

	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->NewItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pAft);
	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pAft->m_strID, pAft->m_strName
		, pAft->m_nTestTimes, pAft->m_nRptTitle, pAft->m_nTitleLevel);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnNew_BFT()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	CSttItems *pBft = stt_gb_new_items(pParent, /*"测试前准备"*/g_sLangTxt_Native_PrepBeforeTest, STT_ITEMS_ID_BEFORETEST);
	pParent->BringToHead(pBft);
	pBft->m_strType = GBITEMS_NODETYPE_NONE;  //测试前准备，不允许再新建分类，设置成none
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pBft);
	//m_pTreeCtrl->AddObj(pBft, TRUE);
	slot_ShowItems(pParent);

// 	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
// 
// 	if (hItem != NULL)
// 	{
// 		hItem->setExpanded(true);
// 	}

	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->NewItems(pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE), pBft);
	g_theGbSmartGenWzd->ItemsAdd(strParentItemPath, pBft->m_strID, pBft->m_strName
		, pBft->m_nTestTimes, pBft->m_nRptTitle, pBft->m_nTitleLevel);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

//新建单个通讯命令
void QSttGuideBookTreeWidget_Win::slot_OnBtnNewCommCmd()
{
	QObject *pSender = sender();
	QString strName = pSender->objectName();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	((QSttTestCntrFrameWin*)g_theTestCntrFrame)->OnNew_CommCmd(strItemPath, strName);
}

//添加测试前后通讯组合
void QSttGuideBookTreeWidget_Win::slot_OnBtnCmdAddGrp()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_CmdAddGrp(pParent);

	CString strItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theGbSmartGenWzd->CommCmdAddGrp(strItemPath, 1, 1);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

//新建配置类电气量项目：IEC61850配置、硬件通道映射、系统参数配置
void QSttGuideBookTreeWidget_Win::slot_OnBtnNewCfgMacro()
{
	QObject *pSender = sender();
	QString strName = pSender->objectName();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	//新建配置类电气量项目，还未完成
	if (strName == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->OnNew_ChMapsConfig(strItemPath);
	}
	else if (strName == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->OnNew_SystemConfig(strItemPath);
	}
	else if (strName == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->OnNew_IECConfig(strItemPath);
	}
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnNewWzd()
{
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	g_theTestCntrFrame->InitCommCmdWzdMain(pParent);
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnViewRpts()
{
	QSttGbViewRpts dlg((CSttItemBase *)m_pCurrSelGbItem, this);
	dlg.exec();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnRsltExpr()
{
	QDialog dlg(this);
	dlg.setWindowTitle("");
	dlg.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	dlg.resize(1440, 960);
	QGridLayout* pLayout = new QGridLayout(&dlg);
	dlg.setLayout(pLayout);
	QScrollArea* pArea = new QScrollArea(&dlg);
	pLayout->addWidget(pArea);
	QResultExprCanvas* pCanvas = new QResultExprCanvas(&dlg);
	pCanvas->setMinimumSize(1400, 910);
	pArea->setWidget(pCanvas);
	CSttItemRsltExpr *pRsltExpr = ((CSttItemBase *)m_pCurrSelGbItem)->GetRsltExpr();
	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pCurrSelGbItem->GetAncestor(STTGBXMLCLASSID_CSTTGUIDEBOOK);
	CTestMacros *pTestMacros = ((CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr)->m_pTestMacros;
	pCanvas->NewRoot(pRsltExpr, (CSttItemBase*)m_pCurrSelGbItem, ((CSttItemBase *)m_pCurrSelGbItem)->GetSttReports(), pGuideBook, pTestMacros);
	if(dlg.exec() == QDialog::Rejected)
	{
		pCanvas->SaveExprBase();

		//保存完，发送SetItemPara指令，同步数据
		//shaolei  2023-4-6 调试默认的结果判断生成，临时注释
		//g_theTestCntrFrame->Ats_SetItemPara_RsltExpr(m_pCurrSelGbItem);
	}
}

//2022-09-09  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttGuideBookTreeWidget_Win::CreateGuideBookMenu()
{
	CDataGroup *pCommCmdCfg = (CDataGroup *)g_theGbSmartGenWzd->m_pCommCmdCfg->FindByID(STT_CMD_PARA_CMDSINGLE);
	m_MenuGuideBook = new QMenu(this);

	CString strAction;
	strAction = /*_T("新建项目分类")*/g_sLangTxt_Native_CreateProjCat;
	m_ActItemsNew = new QAction(strAction,this);
	strAction = /*_T("新建测试前准备")*/g_sLangTxt_Native_CreatePrepBeforeTest;
	m_ActItemsNew_BFT = new QAction(strAction,this);
	strAction = /*_T("新建测试后恢复")*/g_sLangTxt_Native_CreateReplyAfterTest;
	m_ActItemsNew_AFT = new QAction(strAction,this);
	strAction = /*_T("删除当前选中项目")*/g_sLangTxt_Native_DeleteCurrSelectedProj;
	m_ActDeleteCurr = new QAction(strAction,this);
	strAction = /*_T("重命名当前选中项目")*/g_sLangTxt_Native_RenameCurrSelProj;
	m_ActEditCurr = new QAction(strAction,this);
	strAction = /*_T("保存当前选中项目")*/g_sLangTxt_Native_SaveCurrSelectedProj;
	m_ActSaveCurr = new QAction(strAction,this);
	strAction = /*_T("添加功能向导")*/g_sLangTxt_Native_AddFuncWizard;
	m_ActWzdNew = new QAction(strAction,this);
	strAction = /*_T("从当前选中项目开始测试")*/g_sLangTxt_Native_StartTestFromSelProj;
	m_ActTestFrom = new QAction(strAction,this);
	strAction =/* _T("测试当前选中项目")*/g_sLangTxt_Native_TestCurrSelProj;
	m_ActTestThis = new QAction(strAction,this);
	strAction = /*_T("查看报告")*/g_sLangTxt_ViewReport;
	m_ActViewRpts = new QAction(strAction, this);
	//yzj 2023.11.10 禁用结果判断
	//strAction = /*_T("结果判断")*/g_sLangTxt_Native_ResultJudge;
	//m_ActRsltExpr = new QAction(strAction, this);
	strAction = /*_T("上移")*/g_sLangTxt_UpMove;
	m_ActMoveUp = new QAction(strAction,this);
	strAction = /*_T("下移")*/g_sLangTxt_DownMove;
	m_ActMoveDown = new QAction(strAction, this);
	strAction = /*_T("拷贝")*/g_sLangTxt_Copy;
	m_ActItemCopy = new QAction(strAction,this);
	strAction = /*_T("粘贴")*/g_sLangTxt_Paste;
	m_ActItemPaste = new QAction(strAction, this);
	strAction = /*_T("新建接线提示")*/g_sLangTxt_Gradient_WirPrompt;
	m_ActAddSafety = new QAction(strAction, this);
	strAction = /*_T("修改接线提示")*/g_sLangTxt_Gradient_ModifyTip;
	m_ActEditSafety = new QAction(strAction, this);
	strAction = /*_T("删除接线提示")*/g_sLangTxt_Native_DeleteWiringInstr;
	m_ActDeleteSafety = new QAction(strAction, this);
	strAction = /*_T("添加测试前、后通讯组合")*/g_sLangTxt_Native_AddPrePostCommCombo;
	m_ActCmdAddGrp = new QAction(strAction, this);

	m_MenuGuideBook->addAction(m_ActWzdNew);
	strAction = /*_T("新建配置项目")*/g_sLangTxt_Native_CreateConfigProj;
	m_subMenuAddCfgMacro = m_MenuGuideBook->addMenu(strAction);

	if (pCommCmdCfg->GetCount() > 0)
	{
		strAction = /*_T("新建通讯命令")*/g_sLangTxt_Native_CreateCommCommand;
		m_subMenuCommCmdNew = m_MenuGuideBook->addMenu(strAction);
	}

	m_MenuGuideBook->addAction(m_ActAddSafety);
	m_MenuGuideBook->addAction(m_ActCmdAddGrp);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActItemsNew);
	m_MenuGuideBook->addAction(m_ActItemsNew_BFT);
	m_MenuGuideBook->addAction(m_ActItemsNew_AFT);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActDeleteCurr);
	m_MenuGuideBook->addAction(m_ActEditCurr);
	m_MenuGuideBook->addAction(m_ActSaveCurr);
	m_MenuGuideBook->addAction(m_ActEditSafety);
	m_MenuGuideBook->addAction(m_ActDeleteSafety);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActMoveUp);
	m_MenuGuideBook->addAction(m_ActMoveDown);
	m_MenuGuideBook->addAction(m_ActItemCopy);
	m_MenuGuideBook->addAction(m_ActItemPaste);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActTestFrom);
	m_MenuGuideBook->addAction(m_ActTestThis);
	m_MenuGuideBook->addSeparator();

	//m_MenuGuideBook->addAction(m_ActRsltExpr);
	m_MenuGuideBook->addAction(m_ActViewRpts);

	if (pCommCmdCfg->GetCount() > 0)
	{
		POS pos = pCommCmdCfg->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pCommCmdCfg->GetNext(pos);
			QAction *pAct = m_subMenuCommCmdNew->addAction(pData->m_strName);
			pAct->setObjectName(pData->m_strID);
			connect(pAct,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewCommCmd()));
		}
	}

	strAction = /*_T("硬件通道映射")*/g_sLangTxt_Native_HWChanMapping;
	QAction *pActNew = m_subMenuAddCfgMacro->addAction(strAction);
	pActNew->setObjectName(STT_CMD_TYPE_ADJUST_ChMapsConfig);
	connect(pActNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewCfgMacro()));

	strAction = /*_T("系统参数配置")*/g_sLangTxt_IEC_SysParasConfig;
	pActNew = m_subMenuAddCfgMacro->addAction(strAction);
	pActNew->setObjectName(STT_CMD_TYPE_SYSTEM_SystemConfig);
	connect(pActNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewCfgMacro()));

	strAction = /*_T("IEC61850配置")*/g_sLangTxt_Native_IEC61850Config;
	pActNew = m_subMenuAddCfgMacro->addAction(strAction);
	pActNew->setObjectName(STT_CMD_TYPE_SYSTEM_IECConfig);
	m_ActNewIecCfg = pActNew;
	connect(pActNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewCfgMacro()));

	connect(m_ActItemsNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew()));
	connect(m_ActItemsNew_BFT,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew_BFT()));
	connect(m_ActItemsNew_AFT,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew_AFT()));
	connect(m_ActDeleteCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnDeleteCurr()));
	connect(m_ActEditCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnEditCurr()));
	connect(m_ActSaveCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnSaveCurr()));
	connect(m_ActWzdNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewWzd()));
	connect(m_ActTestFrom,SIGNAL(triggered()),this,SLOT(slot_OnBtnTestFrom()));
	connect(m_ActTestThis,SIGNAL(triggered()),this,SLOT(slot_OnBtnTestThis()));
	connect(m_ActViewRpts,SIGNAL(triggered()),this,SLOT(slot_OnBtnViewRpts()));
	//connect(m_ActRsltExpr,SIGNAL(triggered()),this,SLOT(slot_OnBtnRsltExpr()));
	connect(m_ActMoveUp,SIGNAL(triggered()),this,SLOT(slot_OnBtnMoveUp()));
	connect(m_ActMoveDown,SIGNAL(triggered()),this,SLOT(slot_OnBtnMoveDown()));
	connect(m_ActItemCopy,SIGNAL(triggered()),this,SLOT(slot_OnBtnItemCopy()));
	connect(m_ActItemPaste,SIGNAL(triggered()),this,SLOT(slot_OnBtnItemPaste()));
	connect(m_ActAddSafety,SIGNAL(triggered()),this,SLOT(slot_OnBtnAddSafety()));
	connect(m_ActEditSafety,SIGNAL(triggered()),this,SLOT(slot_OnBtnEditSafety()));
	connect(m_ActDeleteSafety,SIGNAL(triggered()),this,SLOT(slot_OnBtnDeleteSafety()));
	connect(m_ActCmdAddGrp,SIGNAL(triggered()),this,SLOT(slot_OnBtnCmdAddGrp()));

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_TreeShowMenu(QPoint)));
}

void QSttGuideBookTreeWidget_Win::mouseMoveEvent( QMouseEvent *e )
{
	if (m_bHasButtonsShow)
	{
		slot_SttMouseMoveEventGbTree(e);
	}
}

void QSttGuideBookTreeWidget_Win::slot_SttMouseMoveEventGbTree( QMouseEvent *e )
{
	if (!m_bHasButtonsShow)
	{
		return;
	}

	QPoint point = e->pos();

	if (!m_rectClicked.contains(point))
	{
		HideAllBtns();
	}
	else
	{
		//考虑鼠标移回去之后要不要重新显示
		//sf 20220328
	}
}

void QSttGuideBookTreeWidget_Win::slot_TreeShowMenu(QPoint pos)
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	if (g_pTheSttTestApp->m_pTestCtrlCntr->IsTestStarted())
	{
		return;
	}

	QSttTestCntrFrameWin* pFrameWin = (QSttTestCntrFrameWin *)g_theTestCntrFrame;

	m_ActItemsNew->setVisible(true);
	m_ActItemsNew_BFT->setVisible(true);
	m_ActItemsNew_AFT->setVisible(true);
	m_ActDeleteCurr->setVisible(true);
	m_ActEditCurr->setVisible(true);
	m_ActSaveCurr->setVisible(true);
	m_ActWzdNew->setVisible(true);
	m_ActTestFrom->setVisible(true);
	m_ActTestThis->setVisible(true);
	m_subMenuCommCmdNew->menuAction()->setVisible(true);
	m_subMenuAddCfgMacro->menuAction()->setVisible(true);
	m_ActNewIecCfg->setVisible(true);
	m_ActViewRpts->setVisible(true);
	m_ActMoveDown->setVisible(true);
	m_ActMoveUp->setVisible(true);
	m_ActItemCopy->setVisible(false);
	m_ActItemPaste->setVisible(false);
	//m_ActRsltExpr->setVisible(true);
	m_ActAddSafety->setVisible(false);
	m_ActEditSafety->setVisible(false);
	m_ActDeleteSafety->setVisible(false);
	m_ActCmdAddGrp->setVisible(false);

	//获得鼠标点击的x，y坐标点 
	int x = pos.x(); 
	int y = pos.y(); 

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	switch (nClassID)
	{
	case STTGBXMLCLASSID_CSTTDEVICE:
		{
			m_ActDeleteCurr->setVisible(false);
			m_ActSaveCurr->setVisible(false);
			m_ActEditCurr->setVisible(false);
			m_ActMoveDown->setVisible(false);
			m_ActMoveUp->setVisible(false);
			//m_ActRsltExpr->setVisible(false);

			CSttDevice *pDevice = (CSttDevice*)m_pCurrSelGbItem;

			if (pDevice->GetGbItemCount() <= 0)
			{
				m_ActTestFrom->setVisible(false);
				m_ActTestThis->setVisible(false);
			}

			if (g_theGbSmartGenWzd->GetItemCopyType() != _T("null"))
			{
				m_ActItemPaste->setVisible(true);
			}
		}
		break;
	case STTGBXMLCLASSID_CSTTITEMS:
		{
			CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;
			//m_ActRsltExpr->setVisible(false);

			if (pItems->IsTypeItems())
			{//人工添加的项目分类节点
				if (pItems->GetGbItemCount() > 0)
				{//有子对象，不可以删除当前节点
					//m_ActDeleteCurr->setVisible(false);
				}

				if (g_theGbSmartGenWzd->GetItemCopyType() != _T("null"))
				{
					m_ActItemPaste->setVisible(true);
				}

				if (pItems->FindByID(STT_ITEMS_ID_AFTERTEST) == NULL
					&& pItems->FindByID(STT_ITEMS_ID_BEFORETEST) == NULL)
				{
					m_ActCmdAddGrp->setVisible(true);
				}
			}
			else if (pItems->IsTypeRootNode()
				/*|| pItems->IsTypeNone()*/)
			{
				m_ActItemsNew->setVisible(false);   //rootnode表示一个完整的测试模块，不再支持添加新的测试分类
				m_ActWzdNew->setVisible(false);

				m_ActItemCopy->setVisible(true);

				if (pItems->FindByID(STT_ITEMS_ID_AFTERTEST) == NULL
					&& pItems->FindByID(STT_ITEMS_ID_BEFORETEST) == NULL)
				{
					m_ActCmdAddGrp->setVisible(true);
				}
			}
			else 
			{
				//m_strType == none || m_strType == ""
				m_ActDeleteCurr->setVisible(false);
				m_ActWzdNew->setVisible(false);
				m_ActItemsNew->setVisible(false);

				if (pItems->m_strID == STT_ITEMS_ID_AFTERTEST
					|| pItems->m_strID == STT_ITEMS_ID_BEFORETEST)
				{
					//测试前准备、测试后恢复，不再支持添加准备、恢复的项目分类
					m_ActItemsNew_AFT->setVisible(false);
					m_ActItemsNew_BFT->setVisible(false);
				}

				if (pItems->m_strID == STT_ITEMS_ID_BEFORETEST)
				{
					m_ActAddSafety->setVisible(true);  //目前仅在测试前准备，才开放添加接线提示
				}
			}

			if (pItems->FindByID(STT_ITEMS_ID_AFTERTEST) != NULL)
			{
				m_ActItemsNew_AFT->setVisible(false);
			}

			if (pItems->FindByID(STT_ITEMS_ID_BEFORETEST) != NULL)
			{
				m_ActItemsNew_BFT->setVisible(false);
			}

			if (pItems->GetGbItemCount() <= 0)
			{//没有子对象，就不可以测试
				m_ActTestFrom->setVisible(false);
				m_ActTestThis->setVisible(false);
			}

			if (pItems->m_strID == STT_ITEMS_ID_DEVRESET)
			{
				m_ActItemsNew_BFT->setVisible(false);
				m_ActItemsNew_AFT->setVisible(false);
			}
			
			if (pItems->m_strID == STT_ITEMS_ID_AFTERTEST
				|| pItems->m_strID == STT_ITEMS_ID_BEFORETEST)
			{
				//测试前准备、测试后恢复：支持单独删除
				m_ActDeleteCurr->setVisible(true);
			}
		}
		break;
	case STTGBXMLCLASSID_CSTTMACROTEST:
		{
			m_ActItemsNew->setVisible(false);
			m_ActItemsNew_BFT->setVisible(false);
			m_ActItemsNew_AFT->setVisible(false);
			m_ActWzdNew->setVisible(false);
			//m_ActEditCurr->setVisible(false);
			m_subMenuAddCfgMacro->menuAction()->setVisible(false);

			if (m_pCurrSelGbItem->m_strID != STT_ORG_MACRO_Iec61850Config
				&& m_pCurrSelGbItem->m_strID != STT_ORG_MACRO_SystemConfig
				&& m_pCurrSelGbItem->m_strID != STT_ORG_MACRO_ChMapsConfig)
			{
				CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(m_pCurrSelGbItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

				//智能生成的电气量项目，不允许单独删除
				if (pItems != NULL)
				{
					m_ActDeleteCurr->setVisible(false);
				}
			}
		}
		break;
	case STTGBXMLCLASSID_CSTTCOMMCMD:
		{
			m_ActItemsNew->setVisible(false);
			m_ActItemsNew_BFT->setVisible(false);
			m_ActItemsNew_AFT->setVisible(false);
			m_ActWzdNew->setVisible(false);
			//m_ActEditCurr->setVisible(false);
			m_ActSaveCurr->setVisible(false);
			m_subMenuAddCfgMacro->menuAction()->setVisible(false);
			m_subMenuCommCmdNew->menuAction()->setVisible(false);
		}
		break;
	case STTGBXMLCLASSID_CSTTMACROCHARITEMS:
		{
			m_ActItemsNew->setVisible(false);
			m_ActItemsNew_BFT->setVisible(false);
			m_ActItemsNew_AFT->setVisible(false);
			m_ActDeleteCurr->setVisible(false);
			m_ActWzdNew->setVisible(false);
			m_subMenuCommCmdNew->menuAction()->setVisible(false);
			m_subMenuAddCfgMacro->menuAction()->setVisible(false);
			m_ActNewIecCfg->setVisible(false);
			m_ActViewRpts->setVisible(false);
			//m_ActRsltExpr->setVisible(false);
		}
		break;
	case STTGBXMLCLASSID_CSTTSAFETY:
		{
			m_ActItemsNew->setVisible(false);
			m_ActItemsNew_BFT->setVisible(false);
			m_ActItemsNew_AFT->setVisible(false);
			m_ActDeleteCurr->setVisible(false);
			m_ActWzdNew->setVisible(false);
			m_subMenuCommCmdNew->menuAction()->setVisible(false);
			m_subMenuAddCfgMacro->menuAction()->setVisible(false);
			m_ActNewIecCfg->setVisible(false);
			m_ActViewRpts->setVisible(false);
			//m_ActRsltExpr->setVisible(false);
			m_ActEditSafety->setVisible(true);
			m_ActSaveCurr->setVisible(false);
			m_ActEditCurr->setVisible(false);
			m_ActDeleteSafety->setVisible(true);

		}
		break;
	default:
		m_ActItemsNew->setVisible(false);
		m_ActItemsNew_AFT->setVisible(false);
		m_ActItemsNew_BFT->setVisible(false);
		break;
	}

	if (g_oSystemParas.m_nHasDigital == 0)
	{
		m_ActNewIecCfg->setVisible(false);
	}

	CSttItemBase *pItem = (CSttItemBase *)m_pCurrSelGbItem;
	
	if (pItem->GetReportsCount() == 0)
	{
		m_ActViewRpts->setVisible(false);
	}

	CSttItemBase *pParent = (CSttItemBase *)pItem->GetParent();
	CSttItemBase *pItem2 = pParent->GetPrevItem((CSttItemBase*)m_pCurrSelGbItem);

	if (pItem2 == NULL)
	{
		m_ActMoveUp->setVisible(false);
	}

	pItem2 = pParent->GetNextItem((CSttItemBase*)m_pCurrSelGbItem);

	if (pItem2 == NULL)
	{
		m_ActMoveDown->setVisible(false);
	}

	if (pItem->m_strID == STT_ITEMS_ID_AFTERTEST)
	{
		m_ActMoveUp->setVisible(false);
	}

	if (pItem->m_strID == STT_ITEMS_ID_BEFORETEST)
	{
		m_ActMoveDown->setVisible(false);
	}

	if ( !pFrameWin->IsAutoTest())
	{
		m_subMenuAddCfgMacro->menuAction()->setVisible(false);
		m_subMenuCommCmdNew->menuAction()->setVisible(false);
		m_ActItemsNew->setVisible(false);
		m_ActItemsNew_BFT->setVisible(false);
		m_ActItemsNew_AFT->setVisible(false);
		m_ActDeleteCurr->setVisible(false);
		m_ActWzdNew->setVisible(false);
		m_ActMoveUp->setVisible(false);
		m_ActMoveDown->setVisible(false);
		m_ActSaveCurr->setVisible(false);
		m_ActItemCopy->setVisible(false);
		m_ActItemPaste->setVisible(false);
		m_ActAddSafety->setVisible(false);
		m_ActEditSafety->setVisible(false);
		m_ActDeleteSafety->setVisible(false);
		m_ActCmdAddGrp->setVisible(false);
	}

	m_MenuGuideBook->move(cursor().pos()); 
	m_MenuGuideBook->show(); 
}

void QSttGuideBookTreeWidget_Win::slot_ShowItems(CExBaseList *pCurTestItems)
{
	QSttGuideBookTreeWidget::slot_ShowItems(pCurTestItems);

	m_bTreeUpdateFinish = TRUE;
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnAddSafety()
{
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	QSttGbSafetyEdit dlg(pParent, this);
	dlg.SetDlgRunMode(DLG_SAFETY_RUNMODE_NEW);
	dlg.Init(NULL);

	if (dlg.exec() == 0)
	{
		return;
	}

	CSttSafety *pNewSafety = (CSttSafety *)dlg.m_pSttSafety;
	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CDataGroup oParas;
	oParas.AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
	oParas.AddNewData(STT_CMD_PARA_ItemName, pNewSafety->m_strName);
	oParas.AddNewData(STT_CMD_PARA_ItemID, pNewSafety->m_strID);
	CExBaseList oListMsgs;
	pNewSafety->GetMsgs(&oListMsgs);

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems_AddSafety(&oParas, NULL, &oListMsgs);
	m_pTreeCtrl->AddObj(pNewSafety, TRUE);
	//slot_ShowItems(pParent);

// 	QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
// 
// 	if (hItem != NULL)
// 	{
// 		hItem->setExpanded(true);
// 	}

	CString strMsgs;
	pNewSafety->GetMsgs(strMsgs);
	g_theGbSmartGenWzd->SafetyAdd_Add(strParentItemPath, pNewSafety->m_strID, pNewSafety->m_strName
		, strMsgs);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	oListMsgs.RemoveAll();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnEditSafety()
{
	CSttSafety *pSafety = (CSttSafety*)m_pCurrSelGbItem;
	CExBaseList *pParent = (CExBaseList *)pSafety->GetParent();
	QSttGbSafetyEdit dlg(pParent, this);
	dlg.SetDlgRunMode(DLG_SAFETY_RUNMODE_EDIT);
	dlg.Init(pSafety);

	if (dlg.exec() == 0)
	{
		return;
	}

	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CDataGroup oParas;
	oParas.AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
	oParas.AddNewData(STT_CMD_PARA_ItemName, pSafety->m_strName);
	oParas.AddNewData(STT_CMD_PARA_ItemID, pSafety->m_strID);
	CExBaseList oListMsgs;
	pSafety->GetMsgs(&oListMsgs);

	//编辑采用和新建同一个指令。会根据项目是否存在，进行区分处理
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems_AddSafety(&oParas, NULL, &oListMsgs);

	CString strMsgs;
	pSafety->GetMsgs(strMsgs);
	g_theGbSmartGenWzd->SafetyAdd_Edit(strParentItemPath, pSafety->m_strID, pSafety->m_strName
		, strMsgs);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();

	oListMsgs.RemoveAll();
}

void QSttGuideBookTreeWidget_Win::slot_OnBtnDeleteSafety()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CString strName = m_pCurrSelGbItem->m_strName;
	CString strMsg, strAdd;
	CString strID = m_pCurrSelGbItem->m_strID;
	strMsg = /*_T("确定要删除 [ ")*/g_sLangTxt_Native_DeletestrMsg;
	strMsg += strName;
	strAdd = /*_T(" ] 吗？删除后无法恢复！")*/g_sLangTxt_Native_DeletestrMsg3;
	strMsg += strAdd;
	CString strTitle;
	strTitle = /*_T("确认删除接线提示")*/g_sLangTxt_Native_ConfirmDelWiringInstr;
	int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem->GetParent();
	CExBaseObject *pCurr = m_pCurrSelGbItem;
	CString strItemsID, strParentItemPath;
	strItemsID = pCurr->m_strID;
	strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_DeleteItems(pParent, pCurr);
	m_pCurrSelGbItem = NULL;
	m_pTreeCtrl->DeleteObject(pCurr);
	pParent->Delete(pCurr);

	QExBaseTreeWidgetItem* hSelItem = (QExBaseTreeWidgetItem*)m_pTreeCtrl->currentItem();

	if (hSelItem != NULL)
	{
		m_pCurrSelGbItem = hSelItem->m_pItemData;

		if (m_pCurrSelGbItem->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			//说明被删除的是最后一个测试项
			m_pCurrSelRootNode = NULL;
			m_strCurrSelRootNodePath = _T("");
		}

		m_pTreeCtrl->OnItemSelChanged(m_pCurrSelGbItem);
	}

	g_theGbSmartGenWzd->SafetyAdd_Delete(strParentItemPath, strItemsID);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttGuideBookTreeWidget_Win::After_SaveCurr(const CString &strRootNodePath)
{
	if (g_theGbSmartGenWzd == NULL)
	{
		return;
	}

	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	//保存后，还需要处理单独添加的电气量项目和通讯命令项目
	POS pos = g_theGbSmartGenWzd->GetHeadPosition();
	CExBaseObject *pChild = NULL;
	UINT nClassID = 0;
	BOOL bUpdateCheckState = FALSE;

	while (pos != NULL)
	{
		pChild = g_theGbSmartGenWzd->GetNext(pos);
		nClassID = pChild->GetClassID();

		if (nClassID == DVMCLASSID_GBWZDCOMMCMDADD)
		{
			CGbWzdCommCmdAdd *pCommCmdAdd = (CGbWzdCommCmdAdd *)pChild;
			After_OnBtnSaveCurr_CommCmdAdd(pCommCmdAdd, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDMACROTESTADD)
		{
			CGbWzdMacroTestAdd *pMacroTestAdd = (CGbWzdMacroTestAdd *)pChild;
			After_OnBtnSaveCurr_MacroTestAdd(pMacroTestAdd, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSADD)
		{
			CGbWzdItemsAdd *pItemsAdd = (CGbWzdItemsAdd *)pChild;
			After_OnBtnSaveCurr_ItemsAdd(pItemsAdd, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMEDIT)
		{
			CGbWzdItemEdit *pItemEdit = (CGbWzdItemEdit *)pChild;
			After_OnBtnSaveCurr_ItemEdit(pItemEdit, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMMOVE)
		{
			CGbWzdItemMove *pItemMove = (CGbWzdItemMove *)pChild;
			After_OnBtnSaveCurr_ItemMove(pItemMove, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMRSLTEXPREDIT)
		{
			CGbWzdItemRsltExprEdit *pRsltExprEdit = (CGbWzdItemRsltExprEdit *)pChild;
			After_OnBtnSaveCurr_ItemRsltExprEdit(pRsltExprEdit, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSETSTATE)
		{
			CGbWzdItemSetState *pSetState = (CGbWzdItemSetState *)pChild;
			After_OnBtnSaveCurr_ItemSetState(pSetState, strRootNodePath);
			bUpdateCheckState = TRUE;
		}
		else if (nClassID == DVMCLASSID_GBWZDSAFETYADD)
		{
			CGbWzdSafetyAdd *pSafetyAdd = (CGbWzdSafetyAdd *)pChild;
			After_OnBtnSaveCurr_SafetyAdd(pSafetyAdd, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDUPDATE)
		{
			CGbWzdCommCmdUpdate *pCommCmdUpdate = (CGbWzdCommCmdUpdate *)pChild;
			After_OnBtnSaveCurr_CommCmdUpdate(pCommCmdUpdate, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDCOMMCMDADDGRP)
		{
			CGbWzdCommCmdAddGrp *pCommCmdAddGrp = (CGbWzdCommCmdAddGrp *)pChild;
			After_OnBtnSaveCurr_CommCmdAddGrp(pCommCmdAddGrp, strRootNodePath);
		}
		else if (nClassID == DVMCLASSID_GBWZDITEMSDELETE)
		{
			CGbWzdItemsDelete *pItemsDelete = (CGbWzdItemsDelete *)pChild;
			After_OnBtnSaveCurr_ItemsDelete(pItemsDelete, strRootNodePath);
		}
	}

// 	if (bUpdateCheckState == TRUE)
// 	{
// 		if (m_pCurrSelRootNode != NULL)
// 		{
// 			m_bTreeCheckStateChanging = TRUE;
// 			QSttGuideBookTreeItem* pItem = (QSttGuideBookTreeItem*)m_pCurrSelRootNode->m_dwItemData;
// 			UpdateChildCheckState(pItem);
// 			UpdateParentCheckState((QSttGuideBookTreeItem*)pItem->parent());
// 			m_bTreeCheckStateChanging = FALSE;
// 		}
// 	}

	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_CommCmdAdd(CGbWzdCommCmdAdd *pCommCmdAdd, const CString &strRootNodePath)
{
	long nPos = pCommCmdAdd->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pCommCmd的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CDataGroup *pCommCmdCfg = (CDataGroup *)g_theGbSmartGenWzd->m_pCommCmdCfg->FindByID(STT_CMD_PARA_CMDSINGLE);
	CDvmData *pData = (CDvmData *)pCommCmdCfg->FindByID(pCommCmdAdd->m_strCommCmdID);
	ASSERT(pData != NULL);

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, /*_T("保存项目指令，创建通讯命令失败！")*/g_sLangTxt_Native_SaveProjInstrFailCommCmd.GetString());
		return;
	}

	CDataGroup oCommCmd;
	CSttContents *pContents = (CSttContents *)pCommCmdAdd->FindByID(STT_CMD_PARA_ItemParas);
	oCommCmd.AddNewGroup(pData->m_strName, pData->m_strID, pData->m_strValue);
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pCommCmdAdd->m_strParentItemsID);

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenrateItems_CmdAdd(pCommCmdAdd->m_strParentItemsID, &oCommCmd, pContents);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttCommCmd *pCommCmd = new CSttCommCmd;
		pCommCmd->m_strName = pData->m_strName;
		pCommCmd->m_strID = pData->m_strID;
		//pCommCmd->m_nFillRptDataset = 1;
		pCommCmd->m_strCommCmdID = pCommCmdAdd->m_strCommCmdID;
		pCommCmd->m_strRwOptr = pData->m_strValue;  //read、write、register
		pCommCmd->GetCommCmdData(TRUE);
		pParentItem->AddNewChild(pCommCmd, TRUE);
		slot_ShowItems(pParentItem);
	}
}

//这个部分，主要针对：系统参数配置、IEC61850配置、硬件通道映射
void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_MacroTestAdd(CGbWzdMacroTestAdd *pMacroTestAdd, const CString &strRootNodePath)
{
	long nPos = pMacroTestAdd->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pMacroTestAdd的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CString strItemParas;
	CSttContents *pContents = (CSttContents *)pMacroTestAdd->FindByID(STT_CMD_PARA_ItemParas);

	if (pContents != NULL)
	{
		strItemParas = pContents->m_strText;
	}

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddMacro(pMacroTestAdd->m_strParentItemsID, pMacroTestAdd->m_strItemsName, 
		pMacroTestAdd->m_strItemsID, pMacroTestAdd->m_strTestMacroUI, strItemParas);

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pMacroTestAdd->m_strParentItemsID);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttMacroTest *pMacro = new CSttMacroTest;
		pMacro->m_strName = pMacroTestAdd->m_strItemsName;
		pMacro->m_strID = pMacroTestAdd->m_strItemsID;
		pMacro->m_strMacroID = pMacroTestAdd->m_strTestMacroUI;
		pParentItem->AddNewChild(pMacro);
		slot_ShowItems(pParentItem);
	}
}

//这个部分，针对单独添加的分类项目
void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemsAdd(CGbWzdItemsAdd *pItemsAdd, const CString &strRootNodePath)
{
	long nPos = pItemsAdd->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pItemsAdd的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CSttItems *pNewItems = new CSttItems();
	pNewItems->m_strName = pItemsAdd->m_strItemsName;
	pNewItems->m_strID = pItemsAdd->m_strItemsID;
	pNewItems->m_nTestTimes = pItemsAdd->m_nRepeatTimes;
	pNewItems->m_nRptTitle = pItemsAdd->m_nRptTitle;
	pNewItems->m_nTitleLevel = pItemsAdd->m_nTitleLevel;

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pItemsAdd->m_strParentItemsID);

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParentItem, pNewItems);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		pParentItem->AddNewChild(pNewItems);
		
		if (pNewItems->m_strID == STT_ITEMS_ID_BEFORETEST)
		{
			pParentItem->BringToHead(pNewItems);
		}

		slot_ShowItems(pParentItem);
	}
	else
	{
		delete pNewItems;
	}
}

//这个部分，针对修改过名称、ID的项目
void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemEdit(CGbWzdItemEdit *pItemEdit, const CString &strRootNodePath)
{
	long nPos = pItemEdit->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pItemEdit的父项目路径的第一级，必然是RootNode的Path
		return;
		
		//陈伟这边出现问题了：当前编辑的项目就是rootnode本身时，找不到wzdxml文件中没有macro-gen节点
		nPos = strRootNodePath.Find(pItemEdit->m_strParentItemsID);

		if (nPos != 0)
		{
			return;
		}
		else
		{
			//确保当前编辑的。就是rootnode本身
			if (pItemEdit->m_strItemsID != m_pCurrSelRootNode->m_strID)
			{
				return;
			}
		}
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pItemEdit->m_strParentItemsID);
	CSttItemBase *pItem = (CSttItemBase *)pParentItem->FindByID(pItemEdit->m_strItemsID_Old);   //编辑前的项目
	CSttItemBase *pItemNew = (CSttItemBase *)pItem->Clone();
	pItemNew->m_strID = pItemEdit->m_strItemsID;
	pItemNew->m_strName = pItemEdit->m_strItemsName;
	
	if (pItemNew->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pSttItems = (CSttItems *)pItemNew;
		pSttItems->m_nTestTimes = pItemEdit->m_nRepeatTimes;
		pSttItems->m_nRptTitle = pItemEdit->m_nRptTitle;
		pSttItems->m_nTitleLevel = pItemEdit->m_nTitleLevel;
	}

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_EditItems(pParentItem, pItemNew, pItemEdit->m_strItemsID_Old);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		pItem->m_strID = pItemEdit->m_strItemsID;
		pItem->m_strName = pItemEdit->m_strItemsName;

		if (pItemNew->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pSttItems = (CSttItems *)pItem;
			pSttItems->m_nTestTimes = pItemEdit->m_nRepeatTimes;
			pSttItems->m_nRptTitle = pItemEdit->m_nRptTitle;
			pSttItems->m_nTitleLevel = pItemEdit->m_nTitleLevel;
		}

		slot_ShowItems(pParentItem);
	}
	
	delete pItemNew;
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemMove(CGbWzdItemMove *pItemMove, const CString &strRootNodePath)
{
	long nPos = pItemMove->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pItemMove的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pItemMove->m_strParentItemsID);

	if(pParentItem == NULL)
	{
		return;
	}

	CSttItemBase *pCurrItem = (CSttItemBase *)pParentItem->FindByID(pItemMove->m_strItemsID);

	if (pCurrItem == NULL)
	{
		return;
	}

	if (pItemMove->m_strMoveType == STT_CMD_PARA_generate_items_move_up)
	{
		//move-up
		CSttItemBase *pPrevItem = pParentItem->GetPrevItem(pCurrItem);

		if (pPrevItem == NULL)
		{
			return;
		}

		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_MoveUpItem(pParentItem, pCurrItem, pItemMove->m_nMoveTimes);
		long nMoveTimes = pItemMove->m_nMoveTimes;

		while (nMoveTimes > 0)
		{
			if (pPrevItem == NULL)
			{
				break;
			}

			pParentItem->ChangePosition(pPrevItem, pCurrItem);
			pPrevItem = pParentItem->GetPrevItem(pCurrItem);
			nMoveTimes--;
		}
	}
	else
	{
		//move-down
		CSttItemBase *pNextItem = pParentItem->GetNextItem((CSttItemBase*)m_pCurrSelGbItem);

		if (pNextItem == NULL)
		{
			return;
		}

		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_MoveDownItem(pParentItem, pCurrItem, pItemMove->m_nMoveTimes);
		long nMoveTimes = pItemMove->m_nMoveTimes;

		while (nMoveTimes > 0)
		{
			if (pNextItem == NULL)
			{
				break;
			}

			pParentItem->ChangePosition(pNextItem, pCurrItem);
			pNextItem = pParentItem->GetNextItem(pCurrItem);
			nMoveTimes--;
		}
	}

	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pTreeCtrl->UpdateObject(pParentItem, TRUE);
	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemRsltExprEdit(CGbWzdItemRsltExprEdit *pItemRsltExprEdit, const CString &strRootNodePath)
{
	long nPos = pItemRsltExprEdit->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pItemRsltExprEdit的父项目路径的第一级，必然是RootNode的Path
		return;
	}
	
	CString strItemPath;
	
	if (pItemRsltExprEdit->m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = pItemRsltExprEdit->m_strParentItemsID + _T("$");
	}
	
	strItemPath += pItemRsltExprEdit->m_strItemsID;

	CSttDevice* pDevice = (CSttDevice *)m_pCurrSelRootNode->GetAncestor(STTGBXMLCLASSID_CSTTDEVICE);
	CSttItemBase* pItem = (CSttItemBase*)pDevice->SelectData(strItemPath);

	if (pItem == NULL)
	{
		//说明，当前结果判断对应的测试项，重新生成后，并不存在。
		return;
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_SetItemPara_RsltExpr(strItemPath, pItemRsltExprEdit->m_pRsltExpr->m_strText);

	CSttItemRsltExpr* pRsltExpr = new CSttItemRsltExpr;
	pRsltExpr->SetXml(pItemRsltExprEdit->m_pRsltExpr->m_strText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	pItem->m_pRsltExpr = pRsltExpr;
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemSetState(CGbWzdItemSetState *pItemSetState, const CString &strRootNodePath)
{
	BOOL bNeedSet = FALSE;
	CSttDevice* pDevice = (CSttDevice *)m_pCurrSelRootNode->GetAncestor(STTGBXMLCLASSID_CSTTDEVICE);

	if (pItemSetState->m_strParentItemsID == _T("")
		&& pItemSetState->m_strItemsID == pDevice->m_strID)
	{
		//说明就是CSttDevice节点
		bNeedSet = TRUE;
	}
	else
	{
		long nPos = pItemSetState->m_strParentItemsID.Find(strRootNodePath);

		if (nPos != 0)
		{
			//如果是当前RootNode下的子项目。则pItemSetState的父项目路径的第一级，必然是RootNode的Path
			bNeedSet = FALSE;
		}
		else
		{
			bNeedSet = TRUE;
		}
	}

	if (!bNeedSet)
	{
		return;
	}

	CString strItemPath;

	if (pItemSetState->m_strParentItemsID.GetLength() > 0)
	{
		strItemPath = pItemSetState->m_strParentItemsID + _T("$");
	}

	strItemPath += pItemSetState->m_strItemsID;

	CSttItemBase* pItem = NULL;
	
	if (strItemPath == pDevice->m_strID)
	{
		pItem = pDevice;
	}
	else
	{
		pItem = (CSttItemBase*)pDevice->SelectData(strItemPath);
	}

	if (pItem == NULL)
	{
		//说明，当前设置勾选的测试项，重新生成后，并不存在。
		return;
	}

	pItem->m_nSelect = pItemSetState->m_nSelect;

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	CSttParas paras;
	paras.AddNewData("ItemPath", strItemPath);
	paras.AddNewData("Select", pItem->m_nSelect);
	pNative->m_oSttAtsClient.Ats_SetItemState(&paras);

	//刷新树显示
	QSttGuideBookTreeItem* pTreeItem = (QSttGuideBookTreeItem*)pItem->m_dwItemData;
	if(pTreeItem)
	{
		if (pItem->m_nSelect)
		{
			pTreeItem->setCheckState(0, Qt::Checked);
		}
		else
		{
			pTreeItem->setCheckState(0, Qt::Unchecked);
		}

		m_bTreeCheckStateChanging = TRUE;
		UpdateChildCheckState(pTreeItem);
		UpdateParentCheckState((QSttGuideBookTreeItem*)pTreeItem->parent());
		m_bTreeCheckStateChanging = FALSE;

		//OnItemCheckChanged(NULL, pItem);
	}
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_SafetyAdd(CGbWzdSafetyAdd *pSafetyAdd, const CString &strRootNodePath)
{
	long nPos = pSafetyAdd->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pSafetyAdd的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CDataGroup oParas;
	oParas.AddNewData(STT_CMD_PARA_ParentItemsPath, pSafetyAdd->m_strParentItemsID);
	oParas.AddNewData(STT_CMD_PARA_ItemName, pSafetyAdd->m_strItemsName);
	oParas.AddNewData(STT_CMD_PARA_ItemID, pSafetyAdd->m_strItemsID);
	CExBaseList oListMsgs;
	CSttMsg *pNewMsg = new CSttMsg();
	pNewMsg->m_strMsg = pSafetyAdd->m_strMsg;
	oListMsgs.AddTail(pNewMsg);

	CSttSafety *pNewSafety = new CSttSafety();
	pNewSafety->m_strName = pSafetyAdd->m_strItemsName;
	pNewSafety->m_strID = pSafetyAdd->m_strItemsID;
	pNewSafety->AddNewChild(pNewMsg);
	
	if (pSafetyAdd->GetCount() > 0)
	{
		CShortDatas *pDatas = pNewSafety->GetDatas();
		POS pos = pSafetyAdd->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmData *pData = (CDvmData *)pSafetyAdd->GetNext(pos);
			CShortData *pNewData = new CShortData();
			pDatas->AddNewChild(pNewData);

			pNewData->m_strName = pData->m_strName;
			pNewData->m_strID = pData->m_strID;
			pNewData->m_dwReserved = 1;
			pNewData->m_strDataTypeID = pData->m_strDataType;
			pNewData->m_strFormat = pData->m_strFormat;
			pNewData->m_strUnit = pData->m_strUnit;
		}
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pSafetyAdd->m_strParentItemsID);
	pParentItem->AddNewChild(pNewSafety);

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems_AddSafety(&oParas, NULL, &oListMsgs);
	m_pTreeCtrl->AddObj(pNewSafety, TRUE);

	oListMsgs.RemoveAll();
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_CommCmdUpdate(CGbWzdCommCmdUpdate *pCommCmdUpdate, const CString &strRootNodePath)
{
	long nPos = pCommCmdUpdate->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pCommCmdUpdate的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CString strPath, strItemParas;
	pCommCmdUpdate->GetCommCmd_String(strItemParas);

	if (pCommCmdUpdate->m_strParentItemsID.IsEmpty())
	{
		strPath = pCommCmdUpdate->m_strItemsID;
	}
	else
	{
		strPath = pCommCmdUpdate->m_strParentItemsID + _T("$");
		strPath += pCommCmdUpdate->m_strItemsID;
	}

	CSttCommCmd oCommCmd;  //从pCommCmdUpdate中解析的对象
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttCommCmd *pCurrentItem = (CSttCommCmd *)stt_gb_find_itembase(pGuideBook, strPath);//当前模板中的通讯命令项目
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strPath, strItemParas, _T("commcmd"));

	BSTR bstrItemParas = strItemParas.AllocSysString();
	oCommCmd.SetXml(bstrItemParas, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

#ifdef _PSX_IDE_QT_
	delete bstrItemParas;
#else
	SysFreeString(bstrItemParas);
#endif

	if (pCurrentItem == NULL)
	{
		//表示是导入模型后，重新添加的通讯命令。每一个指令都会下发commcmd-update
		//但是原来的commcmd-add、cmd-add-grp等都被删掉了。因此上位机模板中没有对应的项目
		pCurrentItem = new CSttCommCmd();
		pCurrentItem->m_strName = pCommCmdUpdate->m_strItemsName;
		pCurrentItem->m_strID = pCommCmdUpdate->m_strItemsID;
		CSttItemBase *pParentItem = stt_gb_find_itembase(pGuideBook, pCommCmdUpdate->m_strParentItemsID);

		if (pParentItem == NULL)
		{
			delete pCurrentItem;
			pCurrentItem = NULL;
			return;
		}

		pParentItem->AddNewChild(pCurrentItem);
		m_pTreeCtrl->AddObj(pCurrentItem, TRUE);
	}

	oCommCmd.UpdateEx(pCurrentItem);  //更新参数到当前模板中的项目

	//stt_cmd_wzd_UpdateTestMacroUiParas(pCurrentItem);
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_CommCmdAddGrp(CGbWzdCommCmdAddGrp *pCommCmdAddGrp, const CString &strRootNodePath)
{
	long nPos = pCommCmdAddGrp->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pCommCmdAddGrp的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CExBaseList *pParent = (CExBaseList*)stt_gb_find_itembase(pGuideBook, pCommCmdAddGrp->m_strParentItemsID);
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_CmdAddGrp(pParent, pCommCmdAddGrp->m_nAftUseReset, pCommCmdAddGrp->m_nAddCommCmd);
}

void QSttGuideBookTreeWidget_Win::After_OnBtnSaveCurr_ItemsDelete(CGbWzdItemsDelete *pItemsDelete, const CString &strRootNodePath)
{
	long nPos = pItemsDelete->m_strParentItemsID.Find(strRootNodePath);

	if (nPos != 0)
	{
		//如果是当前RootNode下的子项目。则pCommCmdAddGrp的父项目路径的第一级，必然是RootNode的Path
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CExBaseList *pParent = (CExBaseList*)stt_gb_find_itembase(pGuideBook, pItemsDelete->m_strParentItemsID);
	CString strItemPath;
	pItemsDelete->GetItemPath(strItemPath);
	CExBaseObject *pCurr = stt_gb_find_itembase(pGuideBook, strItemPath);

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_DeleteItems(pParent, pCurr);
	m_pTreeCtrl->DeleteObject(pCurr);
	pParent->Delete(pCurr);
}

void QSttGuideBookTreeWidget_Win::WaitForGuideBookTreeUpdate()
{
	CTickCount32 oTick;

	while ( !m_bTreeUpdateFinish )
	{
		oTick.DoEvents(10);
	}
}

//当从树上操作，判断是否继续测试
//nType：TestThis = 0; TestFrom = 1;
BOOL QSttGuideBookTreeWidget_Win::IsContinueTest_FromTree(int nType)
{
	QSttTestCntrFrameWin *pFrameWin = (QSttTestCntrFrameWin *)g_theTestCntrFrame;

	//先记录选中的项目
	CExBaseObject *pCurrentSel = GetCurrSelectGbItem();
	CString strItemPath = pCurrentSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	m_bTreeUpdateFinish = TRUE;
	pFrameWin->PromptToSave(m_pCurrSelRootNode, TRUE);
	WaitForGuideBookTreeUpdate();  //重新生成项目后，等待项目树刷新显示
	pFrameWin->ClearItemStateList();

	//保存参数后，由于模板重新生成，还原之前选中的项目。
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	m_pCurrSelGbItem = stt_gb_find_itembase(pGuideBook, strItemPath);

	//pCurrentSel = GetCurrSelectGbItem();  //对于高级试验，当前选中的电气量，可能因为参数的改变而被删除，需要重新选择一下当前选中的项目

	if (m_pCurrSelGbItem == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, /*_T("当前选中的项目，不存在！请重新选择项目后进行测试")*/g_sLangTxt_Native_SelProjNotExistRetryTest.GetString());
		return FALSE;
	}
	
	if (nType == 0)
	{
		if (stt_IsItemHasAin((CSttItemBase *)m_pCurrSelRootNode))
		{
			if (! pFrameWin->IsAinDataMapValid())
			{
				if (! pFrameWin->Warning_AinDataMapInvalid((CSttItemBase *)m_pCurrSelRootNode))
				{
					return FALSE;
				}
			}
		}
	}
	else
	{
		//当前项开始测试，简单处理未：判断整个模板
		if (stt_IsItemHasAin(pGuideBook))
		{
			if (! pFrameWin->IsAinDataMapValid())
			{
				if (! pFrameWin->Warning_AinDataMapInvalid(NULL))
				{
					return FALSE;
				}
			}
		}
	}
	
	return TRUE;
}

long QSttGuideBookTreeWidget_Win::SendSetItemState(CSttItemBase *pItemBase)
{
	//发送自动测试改变测试项
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	CString strParentItemPath, strItemPath;

	if (pItemBase->GetClassID() != STTGBXMLCLASSID_CSTTDEVICE)
	{
		CExBaseObject *pParent = (CExBaseObject *)pItemBase->GetParent();
		strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (strParentItemPath.GetLength() > 0)
		{
			strItemPath = strParentItemPath + _T("$");
			strItemPath += pItemBase->m_strID;
		}
		else
		{
			strItemPath = pItemBase->m_strID;
		}
	}
	else
	{
		strItemPath = pItemBase->m_strID;
	}

	CSttParas paras;
	paras.AddNewData("ItemPath", strItemPath);
	paras.AddNewData("Select", pItemBase->m_nSelect);  //确保此处要么是1  要么是0
	long nRet = pNative->m_oSttAtsClient.Ats_SetItemState(&paras);

	if (nRet == 3)
	{
		CGbWzdItemSetState* pSetState = g_theGbSmartGenWzd->ItemsSetState(strParentItemPath, pItemBase->m_strID, pItemBase->m_strName
			, pItemBase->m_nSelect, pItemBase->m_nEnable, pItemBase->m_nShow);
		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	}

	return nRet;
}

void QSttGuideBookTreeWidget_Win::SwitchMacroViewByCurrSel(CExBaseObject *pSel)
{
	if (pSel == NULL)
	{
		return;
	}

	CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(pSel, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems == NULL)
	{
		if(!m_pCurrSelRootNode)
		{
			g_theTestCntrFrame->HideCharLib();
		}
		return;
	}

	if (m_pCurrSelRootNode == pItems)
	{
		return;
	}

	m_pCurrSelRootNode = pItems;
	m_strCurrSelRootNodePath = m_pCurrSelRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	g_theTestCntrFrame->SwitchMacroViewByCurrSel(pItems);

	//2023-3-21 zhouhj 放入SwitchMacroViewByCurrSel函数中实现
// 	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pItems->m_strstxmlFile);
// 
// 	if (pTestMacroUI == NULL)
// 	{
// 		return;
// 	}
// 
// 	CSttTestMacroUiParas *pUIParas = ((QSttTestCntrFrameWin*)g_theTestCntrFrame)->GetTestMacroUiParas(m_pCurrSelRootNode);
// 
// 	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
// 	g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
// 	g_theTestCntrFrame->OpenMacroTestUI(pUIParas, pTestMacroUI);
// 
// 	if (!g_theTestCntrFrame->HasManuTrigerBtn())
// 	{
// 		g_theTestCntrFrame->EnableManualTriggerButton(false);
// 	}
// 
// 	//特性曲线
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && g_theTestCntrFrame->m_pCharacteristics != NULL)
// 	{
// 		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->ShowCharLib();
// 	}
// 	else
// 	{
// 		((QSttTestCntrFrameWin*)g_theTestCntrFrame)->HideCharLib();
// 	}


//	CString strFile = pTestMacroUI->m_strReportFile;
//	CString strTemp;
//	stt_ui_OpenHtmlFile(strFile, strTemp);
//	strTemp.Replace("$XID$", m_pCurrSelRootNode->m_strID);
//	g_theTestCntrFrame->GetReportViewHtml()->SetRptFileData(const_cast<char*>(strTemp.GetString()));
}

void QSttGuideBookTreeWidget_Win::UpdateParentCheckState(QSttGuideBookTreeItem* pParent)
{
	if(g_theTestCntrFrame->m_tagAppState == QSttTestCntrFrameBase::APPSTATE_OPENTEMPLATE)
	{
		return;
	}

	if(pParent)
	{
		CSttItemBase *pParentItem = (CSttItemBase *)pParent->m_pItemData;
		long nCount = 0;
		long nPartCount = 0;
		long nChildCount = pParent->childCount();
		for (int i = 0; i < nChildCount; i++)
		{
			QTreeWidgetItem *pChildItem = pParent->child(i);
			if (pChildItem->checkState(0) == Qt::Checked)
			{
				nCount++;
			}
			else if (pChildItem->checkState(0) == Qt::PartiallyChecked)
			{
				nPartCount++;
			}
		}

		if (nCount == nChildCount)
		{
			//选中状态
			pParent->setCheckState(0, Qt::Checked);
			pParentItem->m_nSelect = 1;
		}
		else if (nCount > 0 || nPartCount > 0)
		{
			//部分选中状态
			pParent->setCheckState(0, Qt::PartiallyChecked);
			pParentItem->m_nSelect = 1;
		}
		else
		{
			//未选中状态
			pParent->setCheckState(0, Qt::Unchecked);
			pParentItem->m_nSelect = 0;
		}

		UpdateParentCheckState((QSttGuideBookTreeItem*)pParent->parent());
	}
}

void QSttGuideBookTreeWidget_Win::UpdateChildCheckState(QSttGuideBookTreeItem* pItem)
{
	if(g_theTestCntrFrame->m_tagAppState == QSttTestCntrFrameBase::APPSTATE_OPENTEMPLATE)
	{
		return;
	}

	CSttItemBase *pItemBase = NULL;

	if(pItem->checkState(0) == Qt::Checked)
	{
		for (int i = 0; i < pItem->childCount(); i++)
		{
			pItem->child(i)->setCheckState(0, Qt::Checked);
			pItemBase = (CSttItemBase *)((QSttGuideBookTreeItem*)pItem->child(i))->m_pItemData;
			pItemBase->m_nSelect = 1;
			UpdateChildCheckState((QSttGuideBookTreeItem*)pItem->child(i));
		}
	}
	else if(pItem->checkState(0) == Qt::Unchecked)
	{
		for (int i = 0; i < pItem->childCount(); i++)
		{
			pItem->child(i)->setCheckState(0, Qt::Unchecked);
			pItemBase = (CSttItemBase *)((QSttGuideBookTreeItem*)pItem->child(i))->m_pItemData;
			pItemBase->m_nSelect = 0;
			UpdateChildCheckState((QSttGuideBookTreeItem*)pItem->child(i));
		}
	}

}

void QSttGuideBookTreeWidget_Win::SetCheckBoxEnable(BOOL bEnable)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return;
	}

	CSttDevice* pDevice = (CSttDevice *)pGuideBook->GetDevice(FALSE);

	if (pDevice == NULL)
	{
		return;
	}

	QSttGuideBookTreeItem* pItem = (QSttGuideBookTreeItem*)pDevice->m_dwItemData;

	if (pItem == NULL)
	{
		return;
	}

	if (!bEnable)
	{
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsUserCheckable);
	}
	else
	{
		pItem->setFlags(pItem->flags() | Qt::ItemIsUserCheckable);
	}

	SetChildCheckBoxEnable(pItem, bEnable);
}

void QSttGuideBookTreeWidget_Win::SetChildCheckBoxEnable(QSttGuideBookTreeItem* pItem, BOOL bEnable)
{
	for (int i = 0; i < pItem->childCount(); i++)
	{
		QSttGuideBookTreeItem *pChildItem = (QSttGuideBookTreeItem *)pItem->child(i);

		if (!bEnable)
		{
			pChildItem->setFlags(pChildItem->flags() & ~Qt::ItemIsUserCheckable);
		}
		else
		{
			pChildItem->setFlags(pChildItem->flags() | Qt::ItemIsUserCheckable);
		}

		SetChildCheckBoxEnable(pChildItem, bEnable);
	}
}

void QSttGuideBookTreeWidget_Win::OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if(m_bTreeCheckStateChanging)
	{
		return;
	}

	m_bTreeCheckStateChanging = TRUE;

	QSttGuideBookTreeItem* pItem = (QSttGuideBookTreeItem*)pSelObj->m_dwItemData;
	bool bSelect = pItem->checkState(0);
	long nSelect = pItem->checkState(0);
	CSttItemBase* pItemBase = (CSttItemBase*)pSelObj;

	if (pItemBase->m_nSelect == nSelect)
	{
		UpdateChildCheckState(pItem);
		UpdateParentCheckState((QSttGuideBookTreeItem*)pItem->parent());

// 		if (nSelect == 2)
// 		{
// 			pItemBase->m_nSelect = 1;
// 			SendSetItemState(pItemBase);
// 		}

		m_bTreeCheckStateChanging = FALSE;
		return;
	}

	pItemBase->m_nSelect = bSelect;
	SendSetItemState(pItemBase);	

	UpdateChildCheckState(pItem);
	UpdateParentCheckState((QSttGuideBookTreeItem*)pItem->parent());
	m_bTreeCheckStateChanging = FALSE;
}

void QSttGuideBookTreeWidget_Win::ExpandRootNode()
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice->m_dwItemData != 0)
	{
		QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pDevice->m_dwItemData;
		hItem->setExpanded(true);
	}

	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pItems = (CSttItems *)pObj;

		if (pItems->IsTypeRootNode() || pItems->IsTypeItems())
		{
			//rootnode或者人工创建的分类
			QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pItems->m_dwItemData;
			QSttGuideBookTreeCtrl *pTree = (QSttGuideBookTreeCtrl *)hItem->treeWidget();
			pTree->setItemExpanded(hItem, true);
			//hItem->setExpanded(true);
		}

		ExpandRootNode(pItems);
	}
}

void QSttGuideBookTreeWidget_Win::ExpandRootNode(CSttItems *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pChildItems = (CSttItems *)pObj;

		if (pChildItems->IsTypeRootNode() || pChildItems->IsTypeItems())
		{
			//rootnode或者人工创建的分类
			QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pChildItems->m_dwItemData;
			QSttGuideBookTreeCtrl *pTree = (QSttGuideBookTreeCtrl *)hItem->treeWidget();
			pTree->setItemExpanded(hItem, true);
			//hItem->setExpanded(true);
		}

		ExpandRootNode(pChildItems);
	}
}