#include "QTerminalTreeWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "SttMacroParaEditViewTerminalAutoTest.h"
#include "../SttTestCntrFrameBase.h"

QTerminalTreeWidget::QTerminalTreeWidget(QWidget *parent):QWidget(parent)
{	
	m_pTreeWidget = NULL;
	m_pRootItem = NULL;
	m_pBtn_SelectAll = NULL;
	m_pBtn_Clear = NULL;
	m_pBtn_Setting = NULL;
	m_pGooseBinItem = NULL;
	m_pGooseBoutItem = NULL;
	m_pGooseBinItem1 = NULL;
	m_pGooseBoutItem1 = NULL;
	m_pMuSettingTabWidget = NULL;
	m_pSOEItem = NULL;
	m_pSOEItem1 = NULL;
	m_pSOEItem2 = NULL;
	InitUI();
	InitConnection();
	SetFont();
}

QTerminalTreeWidget::~QTerminalTreeWidget()
{

}

QExBaseTreeWidgetItem* QTerminalTreeWidget::NewMUItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pObj)
{
	if (parent == NULL)
	{
		return new QExBaseTreeWidgetItem(m_pTreeWidget, pObj);
	}
	else
	{
		return new QExBaseTreeWidgetItem(parent, pObj);
	}
}

void QTerminalTreeWidget::InitConnection()
{
	connect(m_pBtn_SelectAll,SIGNAL(clicked()), this, SLOT(slot_AllSelected()));
	connect(m_pBtn_Clear,SIGNAL(clicked()), this, SLOT(slot_Clear()));
	connect(m_pBtn_Setting,SIGNAL(clicked()), this, SLOT(slot_Setting()));
	connect(m_pTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), SLOT(handleItemChanged(QTreeWidgetItem*, int)));
}

void QTerminalTreeWidget::UpdateTreeItem()
{
// 	while(m_pGooseBinItem->childCount() > 0) 
// 	{
// 		for (int i = 0; i<m_pGooseBinItem->childCount();i++)
// 		{
// 			strID.Format(_T("Gout_Check%d"),i+1);
// 			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID,_T("0"));
// 		}
// 		QTreeWidgetItem *child = m_pGooseBinItem->takeChild(0); 
// 		delete child; 
// 	}
// 
// 	while(m_pGooseBoutItem->childCount() > 0) 
// 	{
// 		for (int i = 0; i<m_pGooseBoutItem->childCount();i++)
// 		{
// 			strID.Format(_T("Gin_Check%d"),i+1);
// 			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID,_T("0"));
// 		}
// 		QTreeWidgetItem *child = m_pGooseBoutItem->takeChild(0); 
// 		delete child; 
// 	}
	ClearChildItems(m_pGooseBinItem, "Gout_Check%1");
	ClearChildItems(m_pGooseBoutItem, "Gin_Check%1");

// 	CString strText,strID;
// 	for (long nIndex = 0; nIndex < g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex ; nIndex ++)
// 	{
// 		m_pGooseBinItem1 = NewMUItem(m_pGooseBinItem,NULL);
// 		strText.Format(_T("测试点%d"),nIndex+1);
// 		strID.Format(_T("Gout_Check%d"),nIndex+1);
// 		m_pGooseBinItem1->setText(0,strText);
// 		m_pGooseBinItem1->setCheckState(0,Qt::Checked); 
// 		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID,_T("1"));
// 		m_pGoutTestItems.append(m_pGooseBinItem1);
// 	}
// 
// 	for (long nIndex = 0; nIndex < g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex ; nIndex ++)
// 	{
// 		m_pGooseBoutItem1 = NewMUItem(m_pGooseBoutItem,NULL);
// 		strText.Format(_T("测试点%d"),nIndex+1);
// 		strID.Format(_T("Gin_Check%d"),nIndex+1);
// 		m_pGooseBoutItem1->setText(0,strText);
// 		m_pGooseBoutItem1->setCheckState(0,Qt::Checked); 
// 		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID,_T("1"));
// 		m_pGinTestItems.append(m_pGooseBoutItem1);
// 	}

	AddNewItems(m_pGooseBinItem, g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex, "Gout_Check%1", m_pGoutTestItems);
	AddNewItems(m_pGooseBoutItem, g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex, "Gin_Check%1", m_pGinTestItems);


	if (m_pSOEItem1)
	{
		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex < 3)
		{
			m_pSOEItem1->setCheckState(0, Qt::Unchecked);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue("SOEGout_Check","0");
			//CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的GOOSE转开入测试点%d个小于3个."),g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex);
		}
		else
		{
			m_pSOEItem1->setCheckState(0, Qt::Checked);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue("SOEGout_Check","1");
		}
	}
	

	if (m_pSOEItem2)
	{
		if (g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex < 3)
		{
			m_pSOEItem2->setCheckState(0, Qt::Unchecked);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue("SOEGin_Check","0");
			//CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的开出转GOOSE测试点%d个小于3个."),g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex);
		}
		else
		{
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue("SOEGin_Check","1");
			m_pSOEItem2->setCheckState(0, Qt::Checked);
		}
	}


	g_TerminalAutoTest->SaveXmlParas();
}

void QTerminalTreeWidget::AddNewItems(QExBaseTreeWidgetItem* parentItem, int nItemCount, const QString& idFormat, QList<QExBaseTreeWidgetItem *>& itemList)
{
	for (int nIndex = 0; nIndex < nItemCount; ++nIndex)
	{
		QExBaseTreeWidgetItem* newItem = NewMUItem(parentItem, NULL);
		QString strText = QString("测试点%1").arg(nIndex + 1);
		QString strID = idFormat.arg(nIndex + 1);
		newItem->setText(0, strText);
		newItem->setCheckState(0, Qt::Checked);
		g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID,"1");
		CDvmData* pCurData = (CDvmData*)g_TerminalAutoTest->m_pMUAutoTestDataGroup.FindByID(strID);
		newItem->m_pItemData = (CExBaseObject *)pCurData;
		itemList.append(newItem);
	}
}


void QTerminalTreeWidget::ClearChildItems(QTreeWidgetItem* parentItem, const QString& idFormat)
{

	while (parentItem->childCount() > 0)
	{
		for (int i = 0; i < parentItem->childCount(); ++i)
	{
			QString strID = idFormat.arg(i + 1);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strID, "0");
	}

		QTreeWidgetItem* child = parentItem->takeChild(0);
		delete child;
	}
}

void QTerminalTreeWidget::SetFont()
{
	m_pBtn_SelectAll->setFont(*g_pSttGlobalFont);
	m_pBtn_Clear->setFont(*g_pSttGlobalFont);
	m_pBtn_Setting->setFont(*g_pSttGlobalFont);
	m_pTreeWidget->setFont(*g_pSttGlobalFont);
}

void QTerminalTreeWidget::InitUI()
{
	QVBoxLayout *pTreelayout = new QVBoxLayout();
	m_pTreeWidget = new QScrollTreeWidget();
	m_pTreeWidget->setHeaderHidden(true);

	m_pTreeWidget->setStyle(QStyleFactory::create("windows"));
	m_pTreeWidget->setColumnCount(1);
	m_pTreeWidget->setStyleSheet("QTreeWidget::item{height: 30px;}");

	m_pRootItem = NewMUItem(NULL,NULL);
	CString strText;
	strText = _T("智能终端自动测试");
	m_pRootItem->setText(0,strText);
	m_pRootItem->setCheckState(0,Qt::Checked);  
	m_pTreeWidget->addTopLevelItem(m_pRootItem); 

	m_pGooseBinItem = NewMUItem(m_pRootItem,NULL);
	strText = _T("GOOSE转开入");
	m_pGooseBinItem->setText(0,strText);
	m_pGooseBinItem->setCheckState(0,Qt::Checked);  

	m_pGooseBoutItem = NewMUItem(m_pRootItem,NULL);
	strText = _T("开出转GOOSE");
	m_pGooseBoutItem->setText(0,strText);
	m_pGooseBoutItem->setCheckState(0,Qt::Checked);  

	UpdateTreeItem();

	m_pSOEItem = NewMUItem(m_pRootItem,NULL);
	strText = _T("SOE测试");
	m_pSOEItem->setText(0,strText);
	m_pSOEItem->setCheckState(0,Qt::Checked);  
	m_pSOEItem1 = NewMUItem(m_pSOEItem,NULL);
	strText = _T("GOOSE转开入");
	m_pSOEItem1->setText(0,strText);
	m_pSOEItem1->setCheckState(0,Qt::Checked);  
	m_pSOEItem2 = NewMUItem(m_pSOEItem,NULL);
	strText = _T("开出转GOOSE");
	m_pSOEItem2->setText(0,strText);
	m_pSOEItem2->setCheckState(0,Qt::Checked);  

	m_pTreeWidget->expandAll();
	m_pTreeWidget->setSelectionMode(QTreeWidget::ExtendedSelection);
	pTreelayout->addWidget(m_pTreeWidget);


	QHBoxLayout *pBtnLayout = new QHBoxLayout;
	m_pBtn_SelectAll = new QPushButton(this);
	strText = _T("全选");
	m_pBtn_SelectAll->setText(strText);
	m_pBtn_SelectAll->setFixedWidth(80);
	m_pBtn_Clear = new QPushButton(this);
	strText = _T("清除");
	m_pBtn_Clear->setText(strText);
	m_pBtn_Clear->setFixedWidth(80);
	pBtnLayout->addWidget(m_pBtn_SelectAll);
	pBtnLayout->addSpacing(20);
	pBtnLayout->addWidget(m_pBtn_Clear);


	QHBoxLayout *pSetLayout = new QHBoxLayout;
	m_pBtn_Setting = new QPushButton(this);
	strText = _T("设置");
	m_pBtn_Setting->setText(strText);
	m_pBtn_Setting->setFixedWidth(80);
	pSetLayout->addWidget(m_pBtn_Setting);
	pSetLayout->setAlignment(Qt::AlignLeft);


	QVBoxLayout *pMianLayout = new QVBoxLayout;
	pMianLayout->addLayout(pBtnLayout);
	pMianLayout->addLayout(pTreelayout);
	pMianLayout->addLayout(pSetLayout);

	this->setLayout(pMianLayout);
}

void QTerminalTreeWidget::StartInit()
{
	m_pTreeWidget->setDisabled(true);
	m_pBtn_Setting->setDisabled(true);
}

void QTerminalTreeWidget::StopInit()
{
	m_pTreeWidget->setDisabled(false);
	m_pBtn_Setting->setDisabled(false);
}

void QTerminalTreeWidget::slot_AllSelected()
{
	QTreeWidgetItemIterator pIterator(m_pTreeWidget);
	int nCount = 0;
	while(*pIterator)
	{
		QExBaseTreeWidgetItem *pExBaseTreeWidgetItem = dynamic_cast<QExBaseTreeWidgetItem*>(*pIterator);

		CString strText = pExBaseTreeWidgetItem->text(0);
		if (strText == _T("智能终端自动测试")/*  || strText == _T("GOOSE转开入") || strText == _T("开出转GOOSE") || strText == _T("SOE测试")*/)
		{
			(*pIterator)->setCheckState(0,Qt::Checked); 
		}

		if (pExBaseTreeWidgetItem && pExBaseTreeWidgetItem->m_pItemData)
		{ 	
			(*pIterator)->setCheckState(0,Qt::Checked); 
			CString strItemID = pExBaseTreeWidgetItem->m_pItemData->m_strID;
			
			if (strItemID == _T("SOEGout_Check"))
			{
				nCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex;
				if (nCount >= 3)
 				{
 					(*pIterator)->setCheckState(0,Qt::Checked); 
					(*pIterator)->parent()->setCheckState(0,Qt::Checked);
 					g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strItemID,"1");
 				}
				else
				{
					(*pIterator)->setCheckState(0,Qt::Unchecked);			
					g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strItemID,"0");
					CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的GOOSE转开入测试点%d个小于3个."),nCount);
				}
			}
			else if (strItemID == _T("SOEGin_Check"))
			{
				nCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex;
				if (nCount >= 3)
				{
		(*pIterator)->setCheckState(0,Qt::Checked); 
					(*pIterator)->parent()->setCheckState(0,Qt::Checked);
					g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strItemID,"1");
				}
				else
		{
					(*pIterator)->setCheckState(0,Qt::Unchecked);	
					g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strItemID,"0");
					CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("SOE测试的开出转GOOSE测试点%d个小于3个."),nCount);
				}
			}
			else
			{
				(*pIterator)->setCheckState(0,Qt::Checked);
				(*pIterator)->parent()->setCheckState(0,Qt::Checked);
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(strItemID,"1");
			}
		}
		
		pIterator++;
	}
}


void QTerminalTreeWidget::slot_Clear()
{
	QTreeWidgetItemIterator pIterator(m_pTreeWidget);
	while(*pIterator)
	{
		if((*pIterator)->checkState(0) == Qt::Checked)
		{
			(*pIterator)->setCheckState(0,Qt::Unchecked); 
		}
		pIterator++;
	}

	ResetDataItemValues();
}

void QTerminalTreeWidget::ResetDataItemValues()
{
	CDvmData* pDvmData = NULL;
	POS pos = g_TerminalAutoTest->m_pMUAutoTestDataGroup.GetHeadPosition();

	while(pos)
	{
		pDvmData = (CDvmData*)g_TerminalAutoTest->m_pMUAutoTestDataGroup.GetNext(pos);

		if ((pDvmData->m_strID == _T("SOEGout_Check")) ||(pDvmData->m_strID == _T("SOEGin_Check")) || IsGoutCheckID(pDvmData->m_strID) || IsGinCheckID(pDvmData->m_strID))
		{
			g_TerminalAutoTest->m_pMUAutoTestDataGroup.SetDataValue(pDvmData->m_strID,"0");
		}
	}
}

void QTerminalTreeWidget::slot_Setting()
{
	g_oSttTestResourceMngr.LoadDefaultIec61850Config();

	g_TerminalAutoTest->UpdateGinData();
	g_TerminalAutoTest->UpdateGoutData();

	m_pMuSettingTabWidget = new QTerminalSettingTabWidget;
	
	if (m_pMuSettingTabWidget->exec() == QDialog::Accepted) 
	{	
		g_TerminalAutoTest->updateData();
		//m_pMuSettingTabWidget->SaveXmlParas();
	}
}


void QTerminalTreeWidget::handleItemChanged(QTreeWidgetItem* item, int column)
{
	CheckChildItems(item, item->checkState(column));
}

void QTerminalTreeWidget::CheckChildItems(QTreeWidgetItem* item, Qt::CheckState checked)
{
	for (int i = 0; i < item->childCount(); ++i)
	{
		QTreeWidgetItem* child = item->child(i);
		child->setCheckState(0, checked); 
		CheckChildItems(child, checked); 
	}
}

BOOL QTerminalTreeWidget::IsGoutCheckID( const CString& strID )
{
	int nTestCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBoutIndex;
	for (int i = 0; i < nTestCount; i++)
	{
		CString checkID;
		checkID.Format("Gout_Check%d", i + 1);
		if (checkID == strID)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL QTerminalTreeWidget::IsGinCheckID( const CString& strID )
{
	int nTestCount = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_nBinIndex;
	for (int i = 0; i < nTestCount; i++)
	{
		CString checkID;
		checkID.Format("Gin_Check%d", i + 1);
		if (checkID == strID)
		{
			return TRUE;
		}
	}
	return FALSE;
}
