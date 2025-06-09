#include "SttGuideBookTreeWidget.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include <QMessageBox>
#include "../../../../Module/OSInterface/QT/XMessageBox.h"

#include "../../XLangResource_Native.h"

QSttGuideBookTreeWidget::QSttGuideBookTreeWidget(CExBaseObject *pSttGuideBook, CSttFrame_GbTree *pTreeParas, QWidget *parent)
    : QWidget(parent)
{
	m_bHasButtonsShow = FALSE;
	m_pCurrSelGbItem = NULL;
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

#ifndef _PSX_QT_LINUX_
	//����ǽ�����ƶ��¼���Ϊʵʱ��⣬Ĭ�ϵ��ǰ��²ż�� sf 20220329
	m_pTreeCtrl->setMouseTracking(true);
#endif

	m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTDEVICE);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTITEMS);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTCOMMCMD);
    m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTMACROTEST);
	m_pTreeCtrl->AddClassID(STTGBXMLCLASSID_CSTTMACROCHARITEMS);

    ShowBaseList((CExBaseList*)pSttGuideBook);
	connect(m_pTreeCtrl,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemDoubleClicked(QTreeWidgetItem *, int)));
    connect(m_pTreeCtrl,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	//���νڵ�����ƶ��¼� sf 20220329
#ifndef _PSX_QT_LINUX_
    connect(m_pTreeCtrl,SIGNAL(sig_MouseMoveGbTree(QMouseEvent*)),this,SLOT(slot_SttMouseMoveEventGbTree(QMouseEvent*)));
#endif
    connect(m_pTreeCtrl,SIGNAL(sig_focusOutEventGbTree(QFocusEvent*)),this,SLOT(slot_SttfocusOutEventGbTree(QFocusEvent*)));
    
	InitButton();
	m_pVLayout->addWidget(m_pTreeCtrl);
	m_pTreeCtrl->AttachOptrInterface(this);
	setContextMenuPolicy (Qt::CustomContextMenu);
}

void QSttGuideBookTreeWidget::ShowBaseList(CExBaseList *pGuideBook)
{
	m_pCurrSelGbItem = NULL;
	m_pTreeCtrl->clear();

	if (pGuideBook == NULL)
	{
		return;
	}

    m_pTreeCtrl->ShowBaseList(pGuideBook,false);
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
    QString strPicPath = _P_GetResourcePath();

    m_pBtnTestFrom = NewButton(strPicPath + "TestFrom.png");
    m_pBtnTestThis = NewButton(strPicPath + "TestThis.png");
 
#ifndef _PSX_QT_LINUX_
	m_pBtnDeleteCurr = NewButton(strPicPath + "TestDelete.png");
    m_pBtnEditCurr = NewButton(strPicPath + "TestEdit.png");
	m_pBtnNew = NewButton(strPicPath + "TesNew.png");
	m_pBtnSaveCurr = NewButton(strPicPath + "TesSave.png");
#endif

	connect(m_pBtnTestFrom, SIGNAL(clicked()),this,SLOT(slot_OnBtnTestFrom()));
	connect(m_pBtnTestThis, SIGNAL(clicked()),this,SLOT(slot_OnBtnTestThis()));

#ifndef _PSX_QT_LINUX_
	connect(m_pBtnDeleteCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnDeleteCurr()));
	connect(m_pBtnEditCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnEditCurr()));
	connect(m_pBtnNew, SIGNAL(clicked()),this,SLOT(slot_OnBtnNew()));
	connect(m_pBtnSaveCurr, SIGNAL(clicked()),this,SLOT(slot_OnBtnSaveCurr()));
#endif
}

BOOL QSttGuideBookTreeWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	
{
	return 0;
}

void QSttGuideBookTreeWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
#ifndef _PSX_QT_LINUX_
	if (g_theTestCntrFrame->IsTestStarted())
	{
		return;
	}
	//���жϲ����Ƿ����ı䣬�������ı䣬����ʾ����
	g_theTestCntrFrame->PromptToSave(pSelObj);
#endif
	m_pCurrSelGbItem = pSelObj;
   
#ifdef _PSX_QT_LINUX_
	UpdateButtons();
#endif

	//���ݵ�ǰѡ�еĽڵ㣬���������m_strType == rootnode�Ľڵ㣬�л���ʾģ����ͼ
	//�ʼ�ƻ�����˫���¼��У���˫���¼���Ӧ�������ε����¼�����ʱ�����ڴ˴�
#ifndef _PSX_QT_LINUX_
	SwitchMacroViewByCurrSel(pSelObj);
#endif
}

void QSttGuideBookTreeWidget::HideAllBtns()
{
	m_bHasButtonsShow = FALSE;
	m_pBtnTestFrom->hide();
	m_pBtnTestThis->hide();

#ifndef _PSX_QT_LINUX_
	m_pBtnDeleteCurr->hide();
	m_pBtnEditCurr->hide();
	m_pBtnNew->hide();
	m_pBtnSaveCurr->hide();
#endif
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
#ifndef _PSX_QT_LINUX_
	m_rectClicked = rc;
#endif

	QRect rcTree;
	rcTree = m_pTreeCtrl->rect();
	int nSize = rc.height() + 4;

	//ȫ������
	HideAllBtns();

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	if(nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{//Device���ڵ�
#ifndef _PSX_QT_LINUX_
		listShow.append(m_pBtnNew);
#endif
		listShow.append(m_pBtnTestThis);
		listShow.append(m_pBtnTestFrom);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{//��Ŀ����ڵ�
		CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;

#ifndef _PSX_QT_LINUX_
		if (pItems->m_strType == GBITEMS_NODETYPE_ROOTNODE)
		{
			listShow.append(m_pBtnEditCurr);
			//shaoleiע�� 20220404  ��ֹ��ӹ���ʱѡ����ģ�飬����Ҫ����ɾ��
			listShow.append(m_pBtnDeleteCurr);
			listShow.append(m_pBtnSaveCurr);
		}
#endif

		if (pItems->m_strType == GBITEMS_NODETYPE_ITEMS)
		{//�˹���ӵ���Ŀ����ڵ�
#ifndef _PSX_QT_LINUX_
			listShow.append(m_pBtnNew);
			listShow.append(m_pBtnEditCurr);

			if (pItems->GetCount() == 0)
			{//û���Ӷ��󣬿���ɾ����ǰ�ڵ�
				listShow.append(m_pBtnDeleteCurr);
			}
#endif
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

void QSttGuideBookTreeWidget::slot_ItemStateChanged( CExBaseObject *pCurTestItem )
{
	HideAllBtns();
	m_pTreeCtrl->UpdateItemColour();

	//����Windowsƽ̨�ĵ�����������ڿ�������˶�����Թ��ܣ�����Ŀ״̬�ı�ʱ����Ҫ��Ӧ���л�������ͼ��ʸ��ͼ��״̬ͼ����Ϣͼ��Ӳ����Դ��
#ifndef _PSX_QT_LINUX_
	SwitchMacroViewByCurrSel(pCurTestItem);
#endif
}

void QSttGuideBookTreeWidget::slot_ShowItems( CExBaseList *pCurTestItems )
{
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
			return;
		}

		if (pParent->m_dwItemData != 0)
		{
			QExBaseTreeWidgetItem* hItem = (QExBaseTreeWidgetItem *)pParent->m_dwItemData;
			hItem->setExpanded(true);
		}
	}
}

void QSttGuideBookTreeWidget::slot_OnBtnTestFrom()
{
	HideAllBtns();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->TestFrom(strItemPath);

	//3 == STT_CMD_ExecStatus_SUCCESS
	if(nRet != 3)
	{
		g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
	}
}

void QSttGuideBookTreeWidget::slot_OnBtnTestThis()
{
	HideAllBtns();
	CString strItemPath = m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->TestItem(strItemPath);

	//3 == STT_CMD_ExecStatus_SUCCESS
	if(nRet != 3)
	{
		g_theTestCntrFrame->on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
	}
}

void QSttGuideBookTreeWidget::slot_OnBtnNew()
{
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	QSttGbItemsEdit dlg(NULL, pParent, this);

	if (dlg.exec() == 0)
	{
		return;
	}

	CSttItems *pNewItems = dlg.m_pSttItems;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pNewItems);
	m_pTreeCtrl->AddObj(pNewItems, FALSE);
}

void QSttGuideBookTreeWidget::slot_OnBtnEditCurr()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}
	
	CString strItemsID = m_pCurrSelGbItem->m_strID;
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem->GetParent();
	QSttGbItemsEdit dlg((CSttItems*)m_pCurrSelGbItem, pParent, this);
	
	if (dlg.exec() == 0)
	{
		return;
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_EditItems(pParent, m_pCurrSelGbItem, strItemsID);
	m_pTreeCtrl->UpdateObject(m_pCurrSelGbItem);
}

void QSttGuideBookTreeWidget::slot_OnBtnDeleteCurr()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CString strName = m_pCurrSelGbItem->m_strName;
	CString strMsg;
	strMsg = /*"ȷ��Ҫɾ�� ["*/ g_sLangTxt_Native_DeletestrMsg + strName + /*"] ��"*/g_sLangTxt_Native_DeletestrMsg2;
	int result = CXMessageBox::information(this, "", strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem->GetParent();
	CExBaseObject *pCurr = m_pCurrSelGbItem;

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_DeleteItems(pParent, pCurr);
	m_pCurrSelGbItem = NULL;
	m_pTreeCtrl->DeleteObject(pCurr);
	pParent->Delete(pCurr);

	CString strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	g_theTestCntrFrame->DeleteMacroTestReport(strParentPath, strName);
	QExBaseTreeWidgetItem* hSelItem = (QExBaseTreeWidgetItem*)m_pTreeCtrl->currentItem();

	if (hSelItem != NULL)
	{
		m_pCurrSelGbItem = hSelItem->m_pItemData;
		m_pTreeCtrl->OnItemSelChanged(m_pCurrSelGbItem);
	}

//	UpdateButtons();
}

void QSttGuideBookTreeWidget::slot_OnBtnSaveCurr()
{
	if (! g_theTestCntrFrame->GetDatas())
	{
		return;
	}

	CString strItemParentPath;
	CExBaseObject *pParent = (CExBaseObject *)m_pCurrSelGbItem->GetParent();
	strItemParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, m_pCurrSelGbItem->m_strName, m_pCurrSelGbItem->m_strID);
}

void QSttGuideBookTreeWidget::slot_OnBtnNew_AFT()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	CSttItems *pAft = stt_gb_new_items(pParent, /*"���Ժ�ָ�"*/g_sLangTxt_Native_RestoreAfterTest, STT_ITEMS_ID_AFTERTEST);
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pAft);
	m_pTreeCtrl->AddObj(pAft, FALSE);
}

void QSttGuideBookTreeWidget::slot_OnBtnNew_BFT()
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	CSttItems *pBft = stt_gb_new_items(pParent, /*"����ǰ׼��"*/g_sLangTxt_Native_PrepBeforeTest, STT_ITEMS_ID_BEFORETEST);
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_NewItems(pParent, pBft);
	m_pTreeCtrl->AddObj(pBft, FALSE);
}

void QSttGuideBookTreeWidget::slot_OnBtnNewCommCmd()
{
	QObject *pSender = sender();
	QString strName = pSender->objectName();
}

void QSttGuideBookTreeWidget::slot_OnBtnNewWzd()
{
	CExBaseList *pParent = (CExBaseList*)m_pCurrSelGbItem;
	g_theTestCntrFrame->InitCommCmdWzdMain(pParent);
}

/*
QAction *m_ActItemsNew_BFT;  //�½�����ǰ׼��
QAction *m_ActItemsNew_AFT;  //�½����Ժ�ظ�
QAction *m_ActDeleteCurr;    //ɾ����ǰѡ����Ŀ
QAction *m_ActEditCurr;      //�༭��ǰѡ����Ŀ
QAction *m_ActSaveCurr;      //���浱ǰѡ����Ŀ
QAction *m_ActCommCmdNew;    //�½�ͨѶ����
QAction *m_ActWzdNew;        //��ӹ�����
QAction *m_ActTestFrom;      //�ӵ�ǰѡ����Ŀ��ʼ����
QAction *m_ActTestThis;      //���Ե�ǰѡ����Ŀ
*/
#ifndef _PSX_QT_LINUX_

//2022-09-09  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttGuideBookTreeWidget::CreateGuideBookMenu()
{
	CDataGroup *pCommCmdCfg = (CDataGroup *)g_theGbSmartGenWzd->m_oCommCmdCfg.FindByID(_T("cmd-single"));
	m_MenuGuideBook = new QMenu(this);

	m_ActItemsNew = new QAction(/*tr("�½���Ŀ����")*/g_sLangTxt_Native_CreateProjCat,this);
	m_ActItemsNew_BFT = new QAction(/*tr("�½�����ǰ׼��")*/g_sLangTxt_Native_CreatePrepBeforeTest,this);
	m_ActItemsNew_AFT = new QAction(/*tr("�½����Ժ�ָ�")*/g_sLangTxt_Native_CreateReplyAfterTest,this);
	m_ActDeleteCurr = new QAction(/*tr("ɾ����ǰѡ����Ŀ")*/g_sLangTxt_Native_DeleteCurrSelectedProj,this);
	m_ActEditCurr = new QAction(/*tr("�༭��ǰѡ����Ŀ")*/g_sLangTxt_Native_EditCurrSelectedProj,this);
	m_ActSaveCurr = new QAction(/*tr("���浱ǰѡ����Ŀ")*/g_sLangTxt_Native_SaveCurrSelectedProj,this);
	m_ActWzdNew = new QAction(/*tr("��ӹ�����")*/g_sLangTxt_Native_AddFuncWizard,this);
	m_ActTestFrom = new QAction(/*tr("�ӵ�ǰѡ����Ŀ��ʼ����")*/g_sLangTxt_Native_StartTestFromSelProj,this);
	m_ActTestThis = new QAction(/*tr("���Ե�ǰѡ����Ŀ")*/g_sLangTxt_Native_TestCurrSelProj,this);

	if (pCommCmdCfg->GetCount() > 0)
	{
		m_subMenuCommCmdNew = m_MenuGuideBook->addMenu(/*"�½�ͨѶ����"*/g_sLangTxt_Native_CreateCommCommand);
	}

	m_MenuGuideBook->addAction(m_ActWzdNew);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActItemsNew);
	m_MenuGuideBook->addAction(m_ActItemsNew_BFT);
	m_MenuGuideBook->addAction(m_ActItemsNew_AFT);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActDeleteCurr);
	m_MenuGuideBook->addAction(m_ActEditCurr);
	m_MenuGuideBook->addAction(m_ActSaveCurr);
	m_MenuGuideBook->addSeparator();

	m_MenuGuideBook->addAction(m_ActTestFrom);
	m_MenuGuideBook->addAction(m_ActTestThis);

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

	connect(m_ActItemsNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew()));
	connect(m_ActItemsNew_BFT,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew_BFT()));
	connect(m_ActItemsNew_AFT,SIGNAL(triggered()),this,SLOT(slot_OnBtnNew_AFT()));
	connect(m_ActDeleteCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnDeleteCurr()));
	connect(m_ActEditCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnEditCurr()));
	connect(m_ActSaveCurr,SIGNAL(triggered()),this,SLOT(slot_OnBtnSaveCurr()));
	connect(m_ActWzdNew,SIGNAL(triggered()),this,SLOT(slot_OnBtnNewWzd()));
	connect(m_ActTestFrom,SIGNAL(triggered()),this,SLOT(slot_OnBtnTestFrom()));
	connect(m_ActTestThis,SIGNAL(triggered()),this,SLOT(slot_OnBtnTestThis()));

	connect(this, SIGNAL(customContextMenuRequested ( const QPoint & )), this, SLOT(slot_TreeShowMenu(QPoint)));
}

void QSttGuideBookTreeWidget::mouseMoveEvent( QMouseEvent *e )
{
	if (m_bHasButtonsShow)
	{
		slot_SttMouseMoveEventGbTree(e);
	}
}

void QSttGuideBookTreeWidget::slot_SttMouseMoveEventGbTree( QMouseEvent *e )
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
		//��������ƻ�ȥ֮��Ҫ��Ҫ������ʾ
		//sf 20220328
	}
}

void QSttGuideBookTreeWidget::slot_TreeShowMenu(QPoint pos)
{
	if (m_pCurrSelGbItem == NULL)
	{
		return;
	}

	if (g_pTheSttTestApp->m_pTestCtrlCntr->IsTestStarted())
	{
		return;
	}

	m_ActItemsNew->setVisible(true);
	m_ActItemsNew_BFT->setVisible(true);
	m_ActItemsNew_AFT->setVisible(true);
	m_ActDeleteCurr->setVisible(true);
	m_ActEditCurr->setVisible(true);
	m_ActSaveCurr->setVisible(true);
	//m_ActCommCmdNew->setVisible(true);
	m_ActWzdNew->setVisible(true);
	m_ActTestFrom->setVisible(true);
	m_ActTestThis->setVisible(true);

	//����������x��y����� 
	int x = pos.x(); 
	int y = pos.y(); 

	UINT nClassID = m_pCurrSelGbItem->GetClassID();

	switch (nClassID)
	{
	case STTGBXMLCLASSID_CSTTDEVICE:
		{
			m_ActDeleteCurr->setVisible(false);
			m_ActSaveCurr->setVisible(false);

			CSttDevice *pDevice = (CSttDevice*)m_pCurrSelGbItem;

			if (pDevice->GetCount() <= 0)
			{
				m_ActTestFrom->setVisible(false);
				m_ActTestThis->setVisible(false);
			}
		}
		break;
	case STTGBXMLCLASSID_CSTTITEMS:
		{
			CSttItems *pItems = (CSttItems*)m_pCurrSelGbItem;

			if (pItems->m_strType == GBITEMS_NODETYPE_ITEMS)
			{//�˹���ӵ���Ŀ����ڵ�
				if (pItems->GetCount() > 0)
				{//���Ӷ��󣬲�����ɾ����ǰ�ڵ�
					m_ActDeleteCurr->setVisible(false);
				}
			}

			if (pItems->GetCount() <= 0)
			{//û���Ӷ��󣬾Ͳ����Բ���
				m_ActTestFrom->setVisible(false);
				m_ActTestThis->setVisible(false);
			}
		}
		break;
	default:
		m_ActItemsNew->setVisible(false);
		m_ActItemsNew_AFT->setVisible(false);
		m_ActItemsNew_BFT->setVisible(false);
		break;
	}

	m_MenuGuideBook->move(cursor().pos()); 
	m_MenuGuideBook->show(); 
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
		return;
	}

	if (m_pCurrSelRootNode == pItems)
	{
		return;
	}

	m_pCurrSelRootNode = pItems;

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pItems->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		return;
	}

	CSttTestMacroUiParas *pUIParas = NULL;

	if (pTestMacroUI->IsUIOriginal())
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pItems->FindByID(pTestMacroUI->m_strID);

		if (pMacroTest == NULL)
		{
			return;
		}

		g_theTestCntrFrame->SetMacroTest_Original(pMacroTest);
		pUIParas = (CSttTestMacroUiParas *)pMacroTest->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);
	}
	else if (pTestMacroUI->IsUIWeb())
	{
		g_theTestCntrFrame->SetMacroTest_Original(NULL);
		pUIParas = (CSttTestMacroUiParas *)pItems->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);
	}

	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
	g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
	g_theTestCntrFrame->OpenMacroTestUI(pUIParas, pTestMacroUI);

	CString strFile = pTestMacroUI->m_strReportFile;
	CString strTemp;
	stt_ui_OpenHtmlFile(strFile, strTemp);
	strTemp.Replace("$XID$", m_pCurrSelRootNode->m_strID);
	g_theTestCntrFrame->GetReportViewHtml()->SetRptFileData(const_cast<char*>(strTemp.GetString()));
}
#endif


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

