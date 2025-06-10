#include "SttGuideBookTreeWidget.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include <QMessageBox>
#include "../../Module/OSInterface/QT/XMessageBox.h"

//2022-12-02 �޸Ĺ���ID���������еĶ�Ҫ���룬Ч�ʵ��£����Դ�ͷ�ļ���ȥ�������κ���Ҫ�����ĵط����а���
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
	rc = m_pTreeCtrl->visualItemRect(pGbTreeItem);//��ȡ��ǰ����ڵ�λ��

	QRect rcTree;
	rcTree = m_pTreeCtrl->rect();
	int nSize = rc.height() + 4;

	//ȫ������
	HideAllBtns();

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	if(nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{//Device���ڵ�
		listShow.append(m_pBtnTestThis);
		listShow.append(m_pBtnTestFrom);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{//��Ŀ����ڵ�
		CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;

		if (pItems->m_strType == GBITEMS_NODETYPE_ITEMS)
		{//�˹���ӵ���Ŀ����ڵ�
		}

		if (pItems->GetCount() >= 0)
		{//���Ӷ��󣬾Ϳ��Բ��ԣ���ʱ�����ǵ�ǰ����Ŀ������û�п�ִ�е���Ŀ����������
			//���Բ���
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

	//2023.9.18 zhouhj �ڿ�ʼ����ǰ��������ͼ,��ֹ��һ�����Ե��������
	//zhouhj 2023.9.8�ڿ�ʼ����ǰ�����´�ͼ,��ֹ��ֹͣ���Ժ�,��ǰ����ͼ�����ѱ��޸�
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
// 	else//zhouhj 2023.9.8�ڿ�ʼ����ǰ�����´�ͼ,��ֹ��ֹͣ���Ժ�,��ǰ����ͼ�����ѱ��޸�
// 	{
// 		g_theTestCntrFrame->UpdateCharactWidgetForTest();
// 	}
}

void QSttGuideBookTreeWidget::slot_OnBtnTestThis()
{
	HideAllBtns();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	//2023.9.18 zhouhj �ڿ�ʼ����ǰ��������ͼ,��ֹ��һ�����Ե��������
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
// 	else//zhouhj 2023.9.8�ڿ�ʼ����ǰ�����´�ͼ,��ֹ��ֹͣ���Ժ�,��ǰ����ͼ�����ѱ��޸�
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