#include "SttGuideBookTreeWidget.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include <QMessageBox>
#include "../../../Module/OSInterface/QT/XMessageBox.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../SttTestCntrCmdDefine.h" 
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdItemSetState.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttGuideBookTreeWidget::QSttGuideBookTreeWidget(CExBaseObject *pSttGuideBook, CSttFrame_GbTree *pTreeParas, QWidget *parent)
    : QWidget(parent)
{
	m_bHasButtonsShow = FALSE;
	m_pCurrSelGbItem = NULL;
	m_pCurrTestGbItem = NULL;
	m_pCurrSelRootNode = NULL;
    m_pVLayout = new QVBoxLayout(this);
    this->setLayout(m_pVLayout);
    m_pVLayout->setMargin(0);

    CSttFrame_Font *pFont = pTreeParas->GetFont();
	QFont oFont;
    oFont.setFamily(pFont->m_strName);
    oFont.setPixelSize(pFont->m_nHeigth);
    oFont.setBold(pFont->m_nBold);

    m_pTreeCtrl = new QSttGuideBookTreeCtrl(oFont,this);
	m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTDEVICE);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTITEMS);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTCOMMCMD);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTMACROTEST);
	m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTMACROCHARITEMS);
	m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTSAFETY);

    ShowBaseList((CExBaseList*)pSttGuideBook);
	connect(m_pTreeCtrl,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemDoubleClicked(QTreeWidgetItem *, int)));
    connect(m_pTreeCtrl,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
    connect(m_pTreeCtrl,SIGNAL(sig_focusOutEventGbTree(QFocusEvent*)),this,SLOT(slot_SttfocusOutEventGbTree(QFocusEvent*)));
    
	InitButton();
	m_pVLayout->addWidget(m_pTreeCtrl);
	m_pTreeCtrl->AttachOptrInterface(this);
	m_pTreeCtrl->setFont(*g_pSttGlobalFont);
	m_pTreeCtrl->setSelectionBehavior(QAbstractItemView::SelectItems);

	m_bTreeCheckStateChanging = FALSE;
}

void QSttGuideBookTreeWidget::ShowBaseList(CExBaseList *pGuideBook)
{
	m_pCurrSelGbItem = NULL;
	m_pTreeCtrl->clear();

	if (pGuideBook == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
	m_pTreeCtrl->ShowBaseListEx(pGuideBook,false,true);
#else
    m_pTreeCtrl->ShowBaseList(pGuideBook,false);
#endif
}

QToolButton* QSttGuideBookTreeWidget::NewButton(const CString &strPicPath)
{
	QToolButton *pBtn = new QToolButton(this);
	pBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
	pBtn->setIcon(QIcon(strPicPath));
	pBtn->hide();
	return pBtn;
}

void QSttGuideBookTreeWidget::InitButton()
{
#ifdef _PSX_QT_WINDOWS_
    QString strPicPath = _P_GetResourcePath();
    m_pBtnTestFrom = NewButton(strPicPath + "TestFrom.png");
    m_pBtnTestThis = NewButton(strPicPath + "TestThis.png");
#else
    QString strPicPath;
    strPicPath = ":/ctrls/images/TestFrom.png";
	m_pBtnTestFrom = NewButton(strPicPath);
	strPicPath = ":/ctrls/images/TestThis.png";
	m_pBtnTestThis = NewButton(strPicPath);
#endif
	connect(m_pBtnTestFrom, SIGNAL(clicked()),this,SLOT(slot_OnBtnTestFrom()));
	connect(m_pBtnTestThis, SIGNAL(clicked()),this,SLOT(slot_OnBtnTestThis()));
}

BOOL QSttGuideBookTreeWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	
{
	return 0;
}

void QSttGuideBookTreeWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	m_pCurrSelGbItem = pSelObj;
   
//#ifdef _PSX_QT_LINUX_
	UpdateButtons();
//#endif

}

void QSttGuideBookTreeWidget::HideAllBtns()
{
	m_bHasButtonsShow = FALSE;
	m_pBtnTestFrom->hide();
	m_pBtnTestThis->hide();
}

void QSttGuideBookTreeWidget::UpdateButtons()
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

	QRect rcTree;
	rcTree = m_pTreeCtrl->rect();
	int nSize = rc.height() + 4;

	//全部隐藏
	HideAllBtns();

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	if(nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{//Device根节点
		listShow.append(m_pBtnTestThis);
		listShow.append(m_pBtnTestFrom);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{//项目分类节点
		CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;

		if (pItems->m_strType == GBITEMS_NODETYPE_ITEMS)
		{//人工添加的项目分类节点
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

void QSttGuideBookTreeWidget::SetCurTestItem( CExBaseObject *pCurTestItem )
{
	m_pTreeCtrl->UpdateItemColour();
}

CExBaseObject* QSttGuideBookTreeWidget::GetCurTestItem()
{
	return m_pCurrTestGbItem;
}

void QSttGuideBookTreeWidget::After_SaveCurr(const CString &strRootNodePath)
{

}

void QSttGuideBookTreeWidget::ExpandRootNode()
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
			QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pItems->m_dwItemData;
			if (hItem)
			{
				QSttGuideBookTreeCtrl *pTree = (QSttGuideBookTreeCtrl *)hItem->treeWidget();
				pTree->setItemExpanded(hItem, true);
			}
		}

		ExpandRootNode(pItems);
	}
}

void QSttGuideBookTreeWidget::ExpandRootNode(CSttItems *pItems)
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
		}

		ExpandRootNode(pChildItems);
	}
}

void QSttGuideBookTreeWidget::slot_ItemStateChanged( CExBaseObject *pCurTestItem )
{
	HideAllBtns();
	m_pTreeCtrl->UpdateItemColour();
	m_pCurrTestGbItem = pCurTestItem;

	SwitchMacroViewByCurrSel(pCurTestItem);


  	if (g_pTheSttTestApp->m_pTestCtrlCntr->IsTestStarted())
  	{
 		QSttGuideBookTreeItem *pGbTreeItem = (QSttGuideBookTreeItem*)pCurTestItem->m_dwItemData;
		// 确保目标项滚动到可见区域
 		m_pTreeCtrl->scrollToItem(pGbTreeItem, QAbstractItemView::PositionAtTop);
	}
}


void QSttGuideBookTreeWidget::SwitchMacroViewByCurrSel(CExBaseObject *pSel) 
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
 
 	//g_theTestCntrFrame->SwitchMacroViewByCurrSel(pItems);
}

void QSttGuideBookTreeWidget::slot_ShowItems( CExBaseList *pCurTestItems )
{
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	if (pCurTestItems == NULL)
	{
		ShowBaseList(pCurTestItems);
	}
	else
	{
		if (pCurTestItems->GetClassID() == STTGBXMLCLASSID_CSTTGUIDEBOOK)
		{
			ShowBaseList(pCurTestItems);
		}
		else
		{
			if (pCurTestItems->m_dwItemData == 0)
			{
				m_pTreeCtrl->AddObj(pCurTestItems, TRUE);;
			}
			else
			{
				m_pTreeCtrl->UpdateObject(pCurTestItems, TRUE, TRUE);
			}
		}

		CExBaseObject *pParent = (CExBaseObject *)pCurTestItems->GetParent();

		if (pParent == NULL)
		{
			connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
			return;
		}

		if (pParent->m_dwItemData != 0)
		{
			QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
			hItem->setExpanded(true);
		}
	}

	connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
}

void QSttGuideBookTreeWidget::slot_OnBtnTestFrom()
{
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	HideAllBtns();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TESTTING);

	//2023.9.18 zhouhj 在开始测试前更新特性图,防止第一个测试点更新慢了
	//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
	CSttItemBase* pItem = stt_gb_find_itembase((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook(), strItemPath);
	long nIndex = ((CExBaseList*)pItem->GetParent())->FindIndex(pItem);
	g_theTestCntrFrame->UpdateCharactWidgetForTest(nIndex - 1);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->TestFrom(strItemPath);

	//3 == STT_CMD_ExecStatus_SUCCESS
	if(nRet != 3)
	{
		g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
		connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}
// 	else//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
// 	{
// 		g_theTestCntrFrame->UpdateCharactWidgetForTest();
// 	}
}

void QSttGuideBookTreeWidget::slot_OnBtnTestThis()
{
	disconnect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	HideAllBtns();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	//2023.9.18 zhouhj 在开始测试前更新特性图,防止第一个测试点更新慢了
	CSttItemBase* pItem = stt_gb_find_itembase((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook(), strItemPath);
	long nIndex = ((CExBaseList*)pItem->GetParent())->FindIndex(pItem);
	g_theTestCntrFrame->UpdateCharactWidgetForCurTest(nIndex - 1);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->TestItem(strItemPath);

	//3 == STT_CMD_ExecStatus_SUCCESS
	if(nRet != 3)
	{
		g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
		connect(m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}
// 	else//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
// 	{
// 		g_theTestCntrFrame->UpdateCharactWidgetForTest();
// 	}
}

void QSttGuideBookTreeWidget::slot_SttfocusOutEventGbTree( QFocusEvent *e )
{
	if (m_bHasButtonsShow)
	{
		HideAllBtns();
	}
}


CExBaseObject* QSttGuideBookTreeWidget::GetCurrSelectGbItem()
{
	m_pCurrSelGbItem = m_pTreeCtrl->GetCurrSelObject();
	return m_pCurrSelGbItem;
}
void QSttGuideBookTreeWidget::OnItemCheckChanged( CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj )
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
		m_bTreeCheckStateChanging = FALSE;
		return;
	}
	pItemBase->m_nSelect = bSelect;
	SendSetItemState(pItemBase);	

	UpdateChildCheckState(pItem);
	UpdateParentCheckState((QSttGuideBookTreeItem*)pItem->parent());
	m_bTreeCheckStateChanging = FALSE;
}

long QSttGuideBookTreeWidget::SendSetItemState(CSttItemBase *pItemBase)
{
	if (g_pTheSttTestApp->m_pTestCtrlCntr->IsTestStarted())
	{
		return FALSE;
	}

		
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
	}

	return nRet;
}

void QSttGuideBookTreeWidget::SetCheckBoxEnable(BOOL bEnable)
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

void QSttGuideBookTreeWidget::SetChildCheckBoxEnable(QSttGuideBookTreeItem* pItem, BOOL bEnable)
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


void QSttGuideBookTreeWidget::UpdateParentCheckState( QSttGuideBookTreeItem* pParent )
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

void QSttGuideBookTreeWidget::UpdateChildCheckState( QSttGuideBookTreeItem* pItem )
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
