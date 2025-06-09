#include "SttCustomSetDlg.h"
#include "../../XLangResource_Native.h"
#include "../SttTestCntrFrameBase.h"
extern long g_nTreeVertScrollWidth;	//菜单栏自定义设置界面竖直滑块宽度
extern long g_nTreeHorizontalScrollHeight;	//菜单栏自定义设置界面水平滑块宽度

SttCustomSetDlg::SttCustomSetDlg(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	this->setWindowTitle(g_sLangTxt_Native_CustomSetup);

	m_pSttMenus = NULL;
	m_pToolBar = NULL;
    m_pSttFrameConfig = NULL;

	m_pFloatBarList = NULL;
	m_pMenutList = NULL;
	m_pCurrFloatBarData = NULL;
	m_pCurrMenuData = NULL;
	m_pCurrMenuItem =NULL;
	m_pCurrFloatBarItem = NULL;
	
	
	initData();
	OnSetItemClick();
	SetMenuItemState();
	SetCustomSetFont();
}
SttCustomSetDlg::~SttCustomSetDlg()
{

}
void SttCustomSetDlg::SetCustomSetFont()
{
	ui.m_pFloatBarTreeCtrl->setFont(*g_pSttGlobalFont);
	ui.m_pMenuTreeCtrl->setFont(*g_pSttGlobalFont);
	ui.BtnAddBar->setFont(*g_pSttGlobalFont);
	ui.BtnCancel->setFont(*g_pSttGlobalFont);
	ui.BtnInsertAfter->setFont(*g_pSttGlobalFont);
	ui.BtnInsertBefore->setFont(*g_pSttGlobalFont);
	ui.BtnRemove->setFont(*g_pSttGlobalFont);
}

void SttCustomSetDlg::initData()
{

	m_pSttFrameConfig = CSttFrameConfig::g_pSttFrameConfig;
// 	QFont font;
// 	font.setPointSize(10);

	m_pSttMenus = m_pSttFrameConfig->GetMenus();
	ui.m_pMenuTreeCtrl->ShowMenuBaseList(m_pSttMenus);
	ui.m_pMenuTreeCtrl->expandAll();
//	ui.m_pMenuTreeCtrl->setStyleSheet("QTreeWidget::item{height:25px}");
// 	ui.m_pMenuTreeCtrl->setFont(font);

	
	m_pToolBar = m_pSttFrameConfig->GetToolBar();
	CExBaseList *pList = (CExBaseList*)m_pToolBar->FindByID("float-buttons");
	ui.m_pFloatBarTreeCtrl->ShowCustomSetBarTree_ToolBar(pList);
	ui.m_pFloatBarTreeCtrl->expandAll();
//	ui.m_pFloatBarTreeCtrl->setStyleSheet("QTreeWidget::item{height:25px}");
	ui.m_pMenuTreeCtrl->SetCustomSetScrollWidth(g_nTreeVertScrollWidth,g_nTreeHorizontalScrollHeight);
	ui.m_pFloatBarTreeCtrl->SetCustomSetScrollWidth(g_nTreeVertScrollWidth,g_nTreeHorizontalScrollHeight);
//  	ui.m_pFloatBarTreeCtrl->setFont(font);

	ui.BtnAddBar->setText(g_sLangTxt_Native_BtnEndInsert);
	ui.BtnCancel->setText(g_sLangTxt_Close);
	ui.BtnInsertAfter->setText(g_sLangTxt_Native_BtnInsertAfter);
	ui.BtnInsertBefore->setText(g_sLangTxt_Native_BtnInsertBefore);
	ui.BtnRemove->setText(g_sLangTxt_Native_BtnRemove);

	connect(ui.BtnRemove,SIGNAL(clicked()),this,SLOT(slot_OnBtnRemove()));
	connect(ui.BtnAddBar,SIGNAL(clicked()),this,SLOT(slot_OnBtnAddBar()));
	connect(ui.BtnCancel,SIGNAL(clicked()),this,SLOT(slot_OnClose()));
	connect(ui.BtnInsertAfter,SIGNAL(clicked()),this,SLOT(slot_OnBtnInsertAfter()));
	connect(ui.BtnInsertBefore,SIGNAL(clicked()),this,SLOT(slot_OnBtnInsertBefore()));
	connect(ui.m_pMenuTreeCtrl,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_MeunTreeItemClicked(QTreeWidgetItem *, int)));
	connect(ui.m_pFloatBarTreeCtrl,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_FolatBarTreeItemClicked(QTreeWidgetItem *, int)));
	connect(ui.m_pFloatBarTreeCtrl,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(slot_FloatBarTreeItemDoubleClicked(QTreeWidgetItem *, int)));

}

void SttCustomSetDlg::slot_OnClose()
{
	CString strFile;
	strFile = _P_GetConfigPath();

	if (!CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID.IsEmpty())
	{
		strFile += CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID;
		strFile += _T("/TestCntrlFrameConfig.xml");	
	}
	else
	{
		strFile += _T("TestCntrlFrameConfig.xml");	
	}

	m_pSttFrameConfig->SaveXmlFile(strFile, CSttTestCtrlFrameCfgMngrXmlRWKeys:: g_pXmlKeys);
	m_pToolBar = m_pSttFrameConfig->GetToolBar();
 	QSttTestCntrFrameBase* pSttTestCntrFrameBase = (QSttTestCntrFrameBase*)g_theTestCntrFrame;
 	
 	QSttBarBase *oToolBar = (QSttBarBase*)m_pToolBar->m_dwItemData;
	QSttFloatPanel *pQSttFloatPanel = (QSttFloatPanel*)oToolBar->FindFloatPanel();

	if (pQSttFloatPanel == NULL)
	{
		return;
	}

 	for (int nIndex  =0;nIndex<pQSttFloatPanel->m_listCtrls.size(); nIndex++)
 	{
		pSttTestCntrFrameBase->m_oDataBtnsMngr.removeOne(pQSttFloatPanel->m_listCtrls[nIndex]);
		delete pQSttFloatPanel->m_listCtrls[nIndex]; 
 	}
 
  	pQSttFloatPanel->m_listCtrls.clear();
  	pQSttFloatPanel->CreateByData(pSttTestCntrFrameBase->m_oDataBtnsMngr);
//  pSttFloatPanelBase->AdjustCtrls();
//	QSttFloatPanel *pQSttFloatPanel = (QSttFloatPanel *)pSttFloatPanelBase;
	pQSttFloatPanel->m_nBtnIndex = 0;
	oToolBar->AdjustPanels();
  	pSttTestCntrFrameBase->InitIcon();
}


void SttCustomSetDlg::slot_OnBtnRemove()
{
	GetCurrItemData();

	if (m_pCurrFloatBarItem->parent() == 0)
	{
		return;
	}

	SetCurrSelMenuItemUpdateState();
	ui.m_pFloatBarTreeCtrl->DeleteObject(m_pCurrFloatBarData);
	m_pFloatBarList->Delete(m_pCurrFloatBarData);
	EnableBtns();

	
	
}

void SttCustomSetDlg::slot_OnBtnInsertBefore()
{

	GetCurrItemData();
	if (IsCurrFloatBarRoot())
	{
		return;
	}
	if (IsCurrSelMenuItemInBar())
	{
		return;
	}
	CSttFrame_Button *pNewFloatBarData = NewBtnByCurrSelMenuItem();
	m_pFloatBarList->InsertBefore(m_pFloatBarList->Find(m_pCurrFloatBarData),pNewFloatBarData);
//	ui.m_pFloatBarTreeCtrl->UpdateObject(m_pFloatBarList,TRUE);
//	ui.m_pFloatBarTreeCtrl->SetCurrSelObj(pNewFloatBarData);
	
	ui.m_pFloatBarTreeCtrl->clear();
	ui.m_pFloatBarTreeCtrl->ShowBaseList(m_pFloatBarList);
	ui.m_pFloatBarTreeCtrl->setCurrentItem((QTreeWidgetItem*)pNewFloatBarData->m_dwItemData);
	EnableBtns();

	SetMenuItemState();

}


void SttCustomSetDlg::slot_OnBtnInsertAfter()
{
	GetCurrItemData();
	if (IsCurrFloatBarRoot())
	{
		return;
	}
	if (IsCurrSelMenuItemInBar())
	{
		return;
	}

	CSttFrame_Button *pNewFloatBarData = NewBtnByCurrSelMenuItem();
 	m_pFloatBarList->InsertAfter(m_pFloatBarList->Find(m_pCurrFloatBarData),pNewFloatBarData);

//	ui.m_pFloatBarTreeCtrl->UpdateObject(m_pFloatBarList,TRUE);
// 	ui.m_pFloatBarTreeCtrl->SetCurrSelObj(pNewFloatBarData);

	ui.m_pFloatBarTreeCtrl->clear();
	ui.m_pFloatBarTreeCtrl->ShowBaseList(m_pFloatBarList);
	ui.m_pFloatBarTreeCtrl->setCurrentItem((QTreeWidgetItem*)pNewFloatBarData->m_dwItemData);
	EnableBtns();
	SetMenuItemState();
 
}

void SttCustomSetDlg::slot_OnBtnAddBar()
{
	GetCurrItemData();

	if (IsCurrFloatBarRoot())
	{
		return;
	}
	if (IsCurrSelMenuItemInBar())
	{
		return;
	}

	CSttFrame_Button *pNewFloatBarData = NewBtnByCurrSelMenuItem();

 	m_pFloatBarList->AddNewChild(pNewFloatBarData);
//	ui.m_pFloatBarTreeCtrl->UpdateObject(m_pFloatBarList,TRUE);
//	ui.m_pFloatBarTreeCtrl->SetCurrSelObj(pNewFloatBarData);
	
	ui.m_pFloatBarTreeCtrl->clear();
	ui.m_pFloatBarTreeCtrl->ShowBaseList(m_pFloatBarList);
	ui.m_pFloatBarTreeCtrl->setCurrentItem((QTreeWidgetItem*)pNewFloatBarData->m_dwItemData);
	EnableBtns();
	SetMenuItemState();
}


void SttCustomSetDlg::slot_MeunTreeItemClicked(QTreeWidgetItem * pSetItem, int nColumn )
{
	EnableBtns();

}
void SttCustomSetDlg::slot_FolatBarTreeItemClicked(QTreeWidgetItem * pSetItem, int nColumn )
{
	EnableBtns();	
}

void SttCustomSetDlg::OnSetItemClick()
{
	//设置默认的树形控件节点
 	QTreeWidgetItem *pMenuItem = ui.m_pMenuTreeCtrl->topLevelItem(0)->child(0)->child(0);
	ui.m_pMenuTreeCtrl->setCurrentItem(pMenuItem);
	
	QTreeWidgetItem *pBarItem = ui.m_pFloatBarTreeCtrl->topLevelItem(0)->child(0);
	ui.m_pFloatBarTreeCtrl->setCurrentItem(pBarItem);

	if (pBarItem == NULL)
	{
		ui.BtnRemove->setEnabled(false);
		ui.BtnAddBar->setEnabled(false);
		ui.BtnInsertAfter->setEnabled(false);
		ui.BtnInsertBefore->setEnabled(false);	
	}
}

void SttCustomSetDlg::slot_FloatBarTreeItemDoubleClicked(QTreeWidgetItem *pTreeItem, int nCol)
{
	slot_OnBtnRemove();

}

void SttCustomSetDlg::EnableBtns()
{
	m_pCurrMenuItem  = (QExBaseTreeWidgetItem*)ui.m_pMenuTreeCtrl->currentItem();//item

	m_pCurrFloatBarItem  = (QExBaseTreeWidgetItem*)ui.m_pFloatBarTreeCtrl->currentItem();//button

	if((m_pCurrFloatBarItem == NULL)||(m_pCurrMenuItem == NULL))
	{
		return;
	}

	if ((m_pCurrFloatBarItem->m_pItemData->GetClassID() != MNGRCLASSID_CSTTFRAME_BUTTON)||
		(m_pCurrMenuItem->m_pItemData->GetClassID() != MNGRCLASSID_CSTTFRAME_ITEM))
	{

		ui.BtnRemove->setEnabled(false);
		ui.BtnAddBar->setEnabled(false);
		ui.BtnInsertAfter->setEnabled(false);
		ui.BtnInsertBefore->setEnabled(false);

		if (m_pCurrFloatBarItem->childCount() == 0)
		{
			if (m_pCurrFloatBarItem->parent() == 0)
			{
				if (m_pCurrMenuItem->childCount() == 0)
				{
					ui.BtnAddBar->setEnabled(true);
					ui.BtnInsertAfter->setEnabled(true);
					ui.BtnInsertBefore->setEnabled(true);
				}
			}
		}
		
	}
	else
	{
		ui.BtnRemove->setEnabled(true);
		ui.BtnAddBar->setEnabled(true);
		ui.BtnInsertAfter->setEnabled(true);
		ui.BtnInsertBefore->setEnabled(true);
 
	}

}


void SttCustomSetDlg::GetCurrItemData()
{
	m_pCurrMenuItem  = (QExBaseTreeWidgetItem*)ui.m_pMenuTreeCtrl->currentItem();//item

	m_pCurrFloatBarItem  = (QExBaseTreeWidgetItem*)ui.m_pFloatBarTreeCtrl->currentItem();//button

	if(m_pCurrMenuItem != NULL)
	{
		if (m_pCurrMenuItem->m_pItemData->GetClassID() == MNGRCLASSID_CSTTFRAME_ITEM)
		{
			m_pCurrMenuData = (CSttFrame_Item*)m_pCurrMenuItem->m_pItemData;
			m_pMenutList = (CExBaseList*)m_pCurrMenuData->GetParent();
		}
	}


	if (m_pCurrFloatBarItem != NULL)
	{
		if (m_pCurrFloatBarItem->m_pItemData->GetClassID() == MNGRCLASSID_CSTTFRAME_BUTTON)	
		{
			m_pCurrFloatBarData = (CSttFrame_Button*)m_pCurrFloatBarItem->m_pItemData;
			m_pFloatBarList = (CExBaseList*)m_pCurrFloatBarData->GetParent();
		}
	}
		
}

BOOL SttCustomSetDlg::IsCurrFloatBarRoot()
{
	if(m_pCurrFloatBarItem->childCount() == 0)
	{
		if (m_pCurrFloatBarItem->parent() == 0)
		{
			CSttFrame_Button *pNewFloatBarData = NewBtnByCurrSelMenuItem();
			CExBaseList* pData = (CExBaseList*)m_pCurrFloatBarItem->m_pItemData;
			
			pData->AddNewChild(pNewFloatBarData);
 			ui.m_pFloatBarTreeCtrl->clear();
// 			ui.m_pFloatBarTreeCtrl->AddObj(pData);
			ui.m_pFloatBarTreeCtrl->ShowBaseList(pData);
			ui.m_pFloatBarTreeCtrl->setCurrentItem((QTreeWidgetItem*)pNewFloatBarData->m_dwItemData);
			EnableBtns();
			return true;
		}
	}
	return false;
}

BOOL SttCustomSetDlg::IsCurrSelMenuItemInBar()
{
	POS pos = NULL;
	pos = m_pFloatBarList->GetHeadPosition();
	CSttFrame_BarBase *pTooBar =NULL;

	while(pos != NULL)
	{
		pTooBar = (CSttFrame_BarBase *)m_pFloatBarList->GetNext(pos);

		if (pTooBar->m_strID == m_pCurrMenuData->m_strID)
		{
			CString strTmp;
			CString strTips;
// 			strTmp = _T("已存在");
// 			strTips = _T("提示");
			CXMessageBox::information(this,g_sLangTxt_Message,g_sLangTxt_exist);
			//QMessageBox::information(this, strTips, strTmp);
			return  true;
		}

	}

	return false;
}

CSttFrame_Button* SttCustomSetDlg::NewBtnByCurrSelMenuItem()
{
	CSttFrame_Button *pNewFloatBarData = new CSttFrame_Button;
	pNewFloatBarData->SetParent(m_pFloatBarList);
	pNewFloatBarData->m_strName = m_pCurrMenuData->m_strName;
	pNewFloatBarData->m_strID = m_pCurrMenuData->m_strID;
	pNewFloatBarData->m_strIcon = m_pCurrMenuData->m_strIcon;
	pNewFloatBarData->m_nWidth =m_pCurrMenuData->m_nWidth;
	pNewFloatBarData->m_strEnableState = m_pCurrMenuData->m_strEnableState;

	return pNewFloatBarData;
}

void SttCustomSetDlg::SetMenuItemState()
{
	CSttFrame_BarBase * pToolBar = m_pSttFrameConfig->GetToolBar();

	CExBaseList *pList = (CExBaseList*)pToolBar->FindByID("float-buttons");
	
	CSttFrame_Menus * pSttMenus  = m_pSttFrameConfig->GetMenus();

	POS pos = NULL;
	pos = pList->GetHeadPosition();
	CSttFrame_BarBase *pTooBar =NULL;
	while(pos != NULL)
	{
		pTooBar = (CSttFrame_BarBase *)pList->GetNext(pos);

		POS pos2 = NULL;
		pos2 = pSttMenus->GetHeadPosition();
		CSttFrame_Menu *pMenu = NULL;

		while(pos2 != NULL)
		{
			pMenu = (CSttFrame_Menu *)pSttMenus->GetNext(pos2);

			POS pos3  = NULL;
			pos3 = pMenu->GetHeadPosition();
			CSttFrame_Item *pItem = NULL;

			while(pos3 != NULL)
			{
				pItem = (CSttFrame_Item *)pMenu->GetNext(pos3);
				QTreeWidgetItem *pItemColour = (QTreeWidgetItem *)pItem->m_dwItemData;

				if (pTooBar->m_strID == pItem->m_strID)
				{	
					pItemColour->setForeground(0,QBrush(QColor("#a3a3a2")));

				}
			}
		}
	}
}

void SttCustomSetDlg::SetCurrSelMenuItemUpdateState()
{
	CSttFrame_Menus * pSttMenus  = m_pSttFrameConfig->GetMenus();
	POS pos = NULL;
	pos = pSttMenus->GetHeadPosition();
	CSttFrame_Menu *pMenu = NULL;

	while(pos != NULL)
	{
		pMenu = (CSttFrame_Menu *)pSttMenus->GetNext(pos);

		POS pos2  = NULL;
		pos2 = pMenu->GetHeadPosition();
		CSttFrame_Item *pItem = NULL;

		while(pos2 != NULL)
		{
			pItem = (CSttFrame_Item *)pMenu->GetNext(pos2);
			QTreeWidgetItem *pItemColour = (QTreeWidgetItem *)pItem->m_dwItemData;

			if (m_pCurrFloatBarData->m_strID == pItem->m_strID)
			{
				pItemColour->setForeground(0,QBrush(QColor("#16160e")));

			}

		}
	}
}
