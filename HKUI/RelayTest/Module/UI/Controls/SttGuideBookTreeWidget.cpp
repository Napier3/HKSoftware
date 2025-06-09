#include "SttGuideBookTreeWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include <QMessageBox>
#include "../../../../Module/OSInterface/QT/XMessageBox.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
#include "../SttTestCntrCmdDefine.h" 


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

}

void QSttGuideBookTreeWidget::slot_ItemStateChanged( CExBaseObject *pCurTestItem )
{
	HideAllBtns();
	m_pTreeCtrl->UpdateItemColour();
	m_pCurrTestGbItem = pCurTestItem;
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