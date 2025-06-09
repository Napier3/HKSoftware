#include "SttCustomSetTree.h"
#include "../../XLangResource_Native.h"

//QSttOtherSetTree
QSttCustomSetTree::QSttCustomSetTree(QWidget *parent):CExBaseListTreeCtrl(parent)
{
}

QSttCustomSetTree::~QSttCustomSetTree()
{

}

void QSttCustomSetTree:: ShowMenuBaseList(CExBaseList *pList, bool bAddRoot)
{
	QExBaseTreeWidgetItem* hItem = NULL;
	m_pList = pList;

	if (bAddRoot)
	{
		CString strTmp;
		strTmp = /*("²Ëµ¥À¸")*/g_sLangTxt_menu;
		hItem = AddObj(pList, NULL,false);
		hItem->setText(0,strTmp);
		if (hItem)
		{
			hItem->setExpanded(true);
		}
	}
	else
	{
		POS pos = pList->GetHeadPosition(); 
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
            AddObj(p,(QExBaseTreeWidgetItem* ) NULL);
// 			if ( p->m_strID != _T("menuFile") )
// 			{
// 				AddObj(p,(QExBaseTreeWidgetItem* ) NULL);
// 
// 			}
		}
	}

}

BOOL QSttCustomSetTree::CanAdd(UINT nClassID)
{
// 	return(nClassID == MNGRCLASSID_CSTTFRAME_MENUS) 
// 		||(nClassID == MNGRCLASSID_CSTTFRAME_MENU) 
// 		||(nClassID == MNGRCLASSID_CSTTFRAME_ITEM)
// 		||(nClassID == MNGRCLASSID_CSTTFRAME_TOOLBAR)
// 		||(nClassID == MNGRCLASSID_CSTTFRAME_PANAL) 
// 		||(nClassID == MNGRCLASSID_CSTTFRAME_BUTTON);

	return true;
}

void QSttCustomSetTree:: ShowFloatBarTree(CExBaseList *pList,BOOL bClear)
{
	if (bClear)
	{
		this->clear();
		m_pSet = pList;
	}

	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strID == _T("float-buttons"))
		{
			AddObj(p,(QExBaseTreeWidgetItem* ) NULL);
		} 
	}
}

void QSttCustomSetTree::ShowCustomSetBarTree_ToolBar(CExBaseList *pList)
{
	
	m_pSet = pList;
	pList->m_strName = /*_T("¹¤¾ßÀ¸")*/g_sLangTxt_Native_Toolbar;
	AddObj(pList, NULL,false);
	

}

void QSttCustomSetTree::SetCustomSetScrollWidth(long nCustomVertWidth,long nCustomLevelWidth)
{

	CString strSheetStyle;

#ifdef _PSX_QT_LINUX_
	strSheetStyle.Format(_T("QTreeWidget::item{height:25px} QScrollBar:vertical{width: %ldpx;}"
		"QScrollBar:horizontal {height: %ldpx;}"),nCustomVertWidth,nCustomLevelWidth);
#else
	strSheetStyle.Format(_T("QTreeWidget::item{height:25px} QScrollBar:vertical{width: %ldpx;}"
		"QScrollBar:horizontal {height: %ldpx;}"),nCustomVertWidth,nCustomLevelWidth);
#endif
	setStyleSheet(strSheetStyle);

}
