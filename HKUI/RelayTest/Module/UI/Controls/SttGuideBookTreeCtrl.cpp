#include "SttGuideBookTreeCtrl.h"
#include "../../SttCmd/GuideBook/SttItems.h"
#include "../../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../../../Module/API/GlobalConfigApi.h"

//////////////////////////////////////////////////////////////////////////
//QExBaseTreeWidgetItem
extern long g_nTreeVertScrollWidth;
extern long g_nTreeHorizontalScrollHeight;
QSttGuideBookTreeItem::QSttGuideBookTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttGuideBookTreeItem::QSttGuideBookTreeItem(QTreeWidget *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttGuideBookTreeItem::~QSttGuideBookTreeItem()
{

}

void QSttGuideBookTreeItem::UpdateItemColor()
{
	CSttItemBase* pNode = (CSttItemBase*)m_pItemData;

	if (pNode != NULL)
	{
		switch (pNode->m_nState)
		{	
		case TEST_STATE_TESTING:
			{
				setTextColor(0,Qt::blue);
				break;
			}
		case TEST_STATE_ELIGIBLE:
			{
				//南瑞要求合格的设置为绿色
				setTextColor(0,0x8FBC8F);    //darkseagreen
				break;
			}
		case TEST_STATE_STOPED:
			{
				setTextColor(0,Qt::gray);
				break;
			}
		case TEST_STATE_INLEGIBLE:
			{
				setTextColor(0,Qt::red);
				break;
			}
		default:
			{
				setTextColor(0,Qt::black);
				break;
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//QSttGuideBookTreeCtrl
QSttGuideBookTreeCtrl::QSttGuideBookTreeCtrl(QFont font,QWidget *parent)
    : CExBaseListTreeCtrl(parent)
{
	//m_bInsertIteming = FALSE;
	SetQTreeWidgetScrollWidth(g_nTreeVertScrollWidth,g_nTreeHorizontalScrollHeight);
	//SetQTreeWidgetLevelScrollWidth(g_nTreeHorizontalScrollHeight);
	//m_font = font;
	setColumnWidth(0,500);
	m_oFont = font;
	setFont(m_oFont);
	//this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {height: 50px;}");
	//this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width: 50px;}");
		
#ifdef _PSX_QT_LINUX_
	InitScrollCtrl(verticalScrollBar());
#endif
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	installEventFilter(this);
}

QSttGuideBookTreeCtrl::~QSttGuideBookTreeCtrl()
{

}

QExBaseTreeWidgetItem* QSttGuideBookTreeCtrl::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	return new QSttGuideBookTreeItem(parent, pData);
}


void QSttGuideBookTreeCtrl::UpdateItemColour()
{
	CExBaseObject *pObj = NULL;
	QColor color;
	QTreeWidgetItemIterator iterator(this);

	while (*iterator)
	{
		QSttGuideBookTreeItem *pItem = (QSttGuideBookTreeItem *)(*iterator);
		if (pItem != NULL)
		{
			pItem->UpdateItemColor();
		}
		iterator++;
	}
}

void QSttGuideBookTreeCtrl::OnItemSelChanged(CExBaseObject *pSel)
{
	QExBaseTreeWidgetItem* pItem = (QExBaseTreeWidgetItem*)pSel->m_dwItemData;
	emit itemClicked(pItem, 0);
}

void QSttGuideBookTreeCtrl::focusOutEvent(QFocusEvent *e)
{
	emit sig_focusOutEventGbTree(e);
}

void QSttGuideBookTreeCtrl::mousePressEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	mousePressEvent_ScrollBase(ev);
#endif
	QTreeWidget::mousePressEvent( ev );
}

// void QSttGuideBookTreeCtrl::slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol)
// {
// 	if (m_bInsertIteming)
// 	{
// 		//正在插入项目时，屏蔽槽响应
// 		return;
// 	}
// 
// 	CExBaseListTreeCtrl::slot_TreeItemChanged(pTreeItem, nCol);
// }

void QSttGuideBookTreeCtrl::mouseMoveEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseMoveEvent_ScrollBase(ev))
	{
		emit sig_MouseMoveGbTree(ev);
		return;
	}
#endif

	QTreeWidget::mouseMoveEvent( ev );
}

void QSttGuideBookTreeCtrl::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseReleaseEvent_ScrollBase(ev))
	{
		return;
	}
#endif

	QTreeWidget::mouseReleaseEvent( ev );
}



// void QSttGuideBookTreeCtrl::ShowBaseList(CExBaseList *pGuideBook, bool bAddRoot)
// {
// 	this->clear();
//     m_pGuideBook = pGuideBook;
//     
//     if (bAddRoot)
//     {
//         QSttGuideBookTreeItem *pTreeItem = new QSttGuideBookTreeItem(m_font,this);
//         pTreeItem->SetTreeItemObject(pGuideBook);
//         pTreeItem->ShowItemData();
//         this->addTopLevelItem(pTreeItem);
//         AddObj(m_pGuideBook, pTreeItem,false);
//     }
//     else
//     {
//         POS pos = pGuideBook->GetHeadPosition();
//         CExBaseObject *p = NULL;
//         
//         while (pos != NULL)
//         {
//             p = pGuideBook->GetNext(pos);
// 
// 			if (!CanAdd(p->GetClassID()))
// 			{
// 				continue;
// 			}
// 
//             QSttGuideBookTreeItem *pTreeItem = new QSttGuideBookTreeItem(m_font,this);
//             pTreeItem->SetTreeItemObject(p);
//             pTreeItem->ShowItemData();
//             this->addTopLevelItem(pTreeItem);
//             AddObj(p, pTreeItem,false);
//         }
//     }
// }
// 
// void QSttGuideBookTreeCtrl::AddObj(CExBaseObject *pObj, QSttGuideBookTreeItem *pTreeItem,bool bShowSelf /*= true*/ )
// {
//     UINT nClassID = pObj->GetClassID();
// 
//     if (!CanAdd(nClassID))
//     {
//         return;
//     }
// 
// 	QSttGuideBookTreeItem *pItem = NULL;
// 	if (bShowSelf)
// 	{
// 		pItem = new QSttGuideBookTreeItem(m_font,pTreeItem);
// 		pItem->SetTreeItemObject(pObj);
// 		pItem->ShowItemData();
// 	}
// 	else
// 	{
// 		pItem = pTreeItem;
// 	}
// 	
// 	if (!CBaseObject::IsBaseList(nClassID))
// 	{
// 		return;
// 	}
// 
//     CExBaseList *pList = (CExBaseList*)pObj;
//     POS pos = pList->GetHeadPosition();
//     CExBaseObject *p = NULL;
// 
//     while (pos != NULL)
//     {
//         p = pList->GetNext(pos);
// 		if (p != NULL)
// 		{
// 			AddObj(p, pItem);
// 		}
//     }
// }
// 
// 
// bool QSttGuideBookTreeCtrl::CanAdd(CExBaseObject *pObj)
// {
//     return CanAdd(pObj->GetClassID());
// }
// 
// bool QSttGuideBookTreeCtrl::CanAdd(unsigned int nClassID)
// {
//     if (m_arrDwClassID.size() == 0)
//     {
//         return TRUE;
//     }
// 
//     return GetIndexOfClassID(nClassID) >= 0;
// }
// 
// 
// void QSttGuideBookTreeCtrl::ClearArrClassID()
// {
//     m_arrDwClassID.clear();
// }
// 
// void QSttGuideBookTreeCtrl::AddClassID(unsigned int nClassID)
// {
//     m_arrDwClassID.append(nClassID);
// }
// 
// void QSttGuideBookTreeCtrl::RemoveClassID(unsigned int nClassID)
// {
//     long nIndex = GetIndexOfClassID(nClassID);
//     
//     if (nIndex >= 0)
//     {
//         m_arrDwClassID.removeAt(nIndex);
//     }
// }
// 
// long QSttGuideBookTreeCtrl::GetIndexOfClassID(unsigned int nClassID)
// {
//     long nIndex = 0;
//     long nIndexFind = -1;
//     long nCount = m_arrDwClassID.size();
//     
//     for (nIndex=0; nIndex<nCount; nIndex++)
//     {
//         if (nClassID == m_arrDwClassID.at(nIndex))
//         {
//             nIndexFind = nIndex;
//             break;
//         }
//     }
//     
//     return nIndexFind;
// }

QExBaseTreeWidgetItem* QSttGuideBookTreeCtrl::InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	QExBaseTreeWidgetItem *pNew = NewItem(parent, pData);
	CSttItemBase *pItemBase = (CSttItemBase *)pData;
	//m_bInsertIteming = TRUE;

	if (pItemBase->m_nSelect)
	{
		pNew->setCheckState(0, Qt::Checked);
	}
	else
	{
		pNew->setCheckState(0, Qt::Unchecked);
	}

	pNew->setText(0, pData->m_strName);

	if (parent == NULL)
	{
		addTopLevelItem(pNew);
	}

 	pNew->setFont(0,m_oFont);
	//m_bInsertIteming = FALSE;
	return pNew;
}

void QSttGuideBookTreeCtrl::SetQTreeWidgetScrollWidth(long nTreeVertWidth,long nTreeLevelWidth)
{
#ifdef _PSX_QT_LINUX_
	CString strSheetStyle;
	strSheetStyle.Format(_T("QScrollBar:vertical{width: %ldpx;}"
							"QScrollBar:horizontal {height: %ldpx;}"),nTreeVertWidth,nTreeLevelWidth);
	setStyleSheet(strSheetStyle);
#endif
}

/*void QSttGuideBookTreeCtrl::SetQTreeWidgetLevelScrollWidth(long nQTreeWidgetLevelScrollWidth)
{
	CString strSheetStyle;

#ifdef _PSX_QT_LINUX_
	strSheetStyle.Format(_T("QScrollBar:horizontal {height: %ldpx;}"),nQTreeWidgetLevelScrollWidth);
#else
	strSheetStyle.Format(_T("QScrollBar:horizontal {height: %ldpx;}"),nQTreeWidgetLevelScrollWidth);
#endif
	setStyleSheet(strSheetStyle);

}*/
QExBaseTreeWidgetItem* QSttGuideBookTreeCtrl::AddObj(CExBaseObject *pObj, BOOL bExpand)
{
	return CExBaseListTreeCtrl::AddObj(pObj, bExpand);
}

QExBaseTreeWidgetItem* QSttGuideBookTreeCtrl::AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand)
{
	QExBaseTreeWidgetItem* pItem = CExBaseListTreeCtrl::AddObj(pObj, hParent, bExpand);

	if(pItem)
	{
		if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			pItem->setIcon(0, m_icon_Normal[0]);
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems* pItems = (CSttItems*)pObj;
			long nTestTimes = pItems->m_nTestTimes;
			long nTitleLevel = pItems->m_nTitleLevel;

			if (nTestTimes >= 11)
			{
				nTestTimes = 11; //取数组的最后一个，测试次数用N代替
			}

			if (nTitleLevel >= 6)
			{
				nTitleLevel = 6;  //取数组最后一个，标题等级用M代替
			}
 
			if (pItems->m_nRptTitle <= 0)
			{
				//不作为标题使用
				pItem->setIcon(0, m_icon_Items[0][nTestTimes-1]);  //数组中，测试次数是从2开始画的，此处-1
				return pItem;
			}

			pItem->setIcon(0, m_icon_Items[nTitleLevel][nTestTimes-1]);  //数组中，测试次数是从2开始画的，此处-1
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pItem->setIcon(0, m_icon_Normal[2]);
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD)
		{
			pItem->setIcon(0, m_icon_Normal[3]);
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			pItem->setIcon(0, m_icon_Normal[4]);
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTSAFETY)
		{
			pItem->setIcon(0, m_icon_Normal[5]);
		}
	}

	return pItem;
}

void QSttGuideBookTreeCtrl::UpdateTestTimesIcon(QExBaseTreeWidgetItem* pItem, CExBaseObject *pObj)
{
	CSttItems* pItems = (CSttItems*)pObj;
	long nTestTimes = pItems->m_nTestTimes;
	long nTitleLevel = pItems->m_nTitleLevel;

	if (nTestTimes >= 11)
	{
		nTestTimes = 11; //取数组的最后一个，测试次数用N代替
	}

	if (nTitleLevel >= 6)
	{
		nTitleLevel = 6;  //取数组最后一个，标题等级用M代替
	}

	if (pItems->m_nRptTitle <= 0)
	{
		//不作为标题使用
		pItem->setIcon(0, m_icon_Items[0][nTestTimes-1]);  //数组中，测试次数是从2开始画的，此处-1
		return;
	}

	pItem->setIcon(0, m_icon_Items[nTitleLevel][nTestTimes-1]);  //数组中，测试次数是从2开始画的，此处-1
}

void QSttGuideBookTreeCtrl::PaintIcon_Items(const CString &strIconBack_Path, long nLevel, long nTimes, QIcon &iconDest)
{
	QPixmap iconSrc = QPixmap(strIconBack_Path);

	long nOffset = 4;
	long nFontSize = 25;
	long nWidth = iconSrc.width() + 2 * nOffset;
	long nHeight = iconSrc.height() + 2 * nOffset;

	QFont font;
	font.setPixelSize(nFontSize);
	font.setBold(true);

	QPixmap tempPix(nWidth, nHeight);
	tempPix.fill(Qt::transparent);
	QPainter painter(&tempPix);
	painter.drawPixmap(nOffset, nOffset, iconSrc);

	QString strText;
	long nTextLen = 1;

	if (nLevel >= 1)
	{
		painter.setFont(font);

		painter.setPen(QColor(0, 0, 255));

		if (nLevel <= 5)
		{
			strText = QString("%1").arg(nLevel);
		}
		else
		{
			strText = "M";
		}

		nTextLen = strText.length() - 1;
		QRect rcLeft(nOffset - nTextLen * nFontSize / 2, nHeight / 2 - 8, nWidth, nHeight / 2);	
		painter.drawText(rcLeft, strText);
	}

	if (nTimes >= 2)
	{
		nFontSize = 20;
		font.setPixelSize(nFontSize);
		font.setBold(true);
		painter.setFont(font);

		painter.setPen(QColor(255, 0, 0));

		if (nTimes <= 10)
		{
			strText = QString("%1").arg(nTimes);
		}
		else
		{
			strText = "N";
		}
		
		nTextLen = strText.length();
		QRect rcRight(nWidth - nOffset - nTextLen * nFontSize / 2, nHeight / 2 - 3/*+ 5*/, nWidth, nHeight / 2);	
		painter.drawText(rcRight, strText);
	}

	iconDest.addPixmap(tempPix);
}

void QSttGuideBookTreeCtrl::InitAllIcons()
{
#ifdef _PSX_QT_WINDOWS_
	CString strIconPath = _P_GetResourcePath();
	strIconPath += "windows/";
#else
    CString strIconPath =  ":/ctrls/images/";
#endif
	CString strBmp = "Gbt_SttItems.bmp";
	CString strFullPath = strIconPath + strBmp;

	for (int i=0; i<7; i++)
	{
		for (int j=1; j<12; j++)
		{
			PaintIcon_Items(strFullPath, i, j, m_icon_Items[i][j-1]);
		}
	}

	strBmp = "Gbt_SttDevice.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[0]);  //0, 0表示不添加额外的字体

	strBmp = "Gbt_SttItems.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[1]);  //0, 0表示不添加额外的字体

	strBmp = "Gbt_SttMacroTest.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[2]);  //0, 0表示不添加额外的字体

	strBmp = "Gbt_SttCommCmd.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[3]);  //0, 0表示不添加额外的字体

	strBmp = "Gbt_SttMacroCharItems.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[4]);  //0, 0表示不添加额外的字体

	strBmp = "Gbt_SttSafety.bmp";
	strFullPath = strIconPath + strBmp;
	PaintIcon_Items(strFullPath, 0, 0, m_icon_Normal[5]);  //0, 0表示不添加额外的字体
}