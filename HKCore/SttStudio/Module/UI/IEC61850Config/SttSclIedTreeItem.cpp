#include "SttSclIedTreeItem.h"

QSttSclIedTreeItem::QSttSclIedTreeItem(QTreeWidgetItem *parent)
    : QTreeWidgetItem(parent)
{
    m_pTreeItemNode = NULL;
}

QSttSclIedTreeItem::QSttSclIedTreeItem(QTreeWidget *parent)
    : QTreeWidgetItem(parent)
{
    m_pTreeItemNode = NULL;
}

QSttSclIedTreeItem::~QSttSclIedTreeItem()
{

}

void QSttSclIedTreeItem::ShowItemData()
{
    if(m_pTreeItemNode != NULL)
    {
		QString strText;
		strText = QString("[%1]%2").arg(m_pTreeItemNode->m_strID).arg(m_pTreeItemNode->m_strName);
//		strText.Format(_T("[%s]%s"),.GetString(),m_pTreeItemNode->m_strName.GetString());
        setText(0,strText);
    }
    else
    {
        setText(0,"");
    }
}

void QSttSclIedTreeItem::SetTreeItemObject( CExBaseObject *pObj )
{
    m_pTreeItemNode = pObj;

	pObj->m_dwItemData = (DWORD)this;
}


