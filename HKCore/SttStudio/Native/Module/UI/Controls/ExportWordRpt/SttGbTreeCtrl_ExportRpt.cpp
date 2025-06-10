#include "SttGbTreeCtrl_ExportRpt.h"
#include "../../../SttCmd/GuideBook/SttItems.h"

//////////////////////////////////////////////////////////////////////////
//QExBaseTreeWidgetItem
QSttGbTreeItem_ExportRpt::QSttGbTreeItem_ExportRpt(QTreeWidgetItem *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttGbTreeItem_ExportRpt::QSttGbTreeItem_ExportRpt(QTreeWidget *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttGbTreeItem_ExportRpt::~QSttGbTreeItem_ExportRpt()
{

}

//////////////////////////////////////////////////////////////////////////
//QSttGbTreeCtrl_ExportRpt
QSttGbTreeCtrl_ExportRpt::QSttGbTreeCtrl_ExportRpt(QFont font,QWidget *parent)
    : CExBaseListTreeCtrl(parent)
{
	m_oFont = font;
	setFont(m_oFont);
}

QSttGbTreeCtrl_ExportRpt::~QSttGbTreeCtrl_ExportRpt()
{
	//clear();
}

QExBaseTreeWidgetItem* QSttGbTreeCtrl_ExportRpt::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	return new QSttGbTreeItem_ExportRpt(parent, pData);
}

void QSttGbTreeCtrl_ExportRpt::OnItemSelChanged(CExBaseObject *pSel)
{
	QExBaseTreeWidgetItem* pItem = (QExBaseTreeWidgetItem*)pSel->m_dwItemData;
	emit itemClicked(pItem, 0);
}

QExBaseTreeWidgetItem* QSttGbTreeCtrl_ExportRpt::InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems *)pData;

		if (pItems->IsTypeNone())
		{
			return NULL;
		}

		if (pItems->m_strID == _T("_DevReset_")
			|| pItems->m_strID == _T("_AfterTest_")
			|| pItems->m_strID == _T("_BeforeTest_"))
		{
			return NULL;
		}
	}

	QExBaseTreeWidgetItem *pNew = NewItem(parent, pData);

	//CString strText = pData->m_strName;
	pNew->setText(0, pData->m_strName);

	if (parent == NULL)
	{
		addTopLevelItem(pNew);
	}

 	pNew->setFont(0,m_oFont);
	return pNew;
}

QExBaseTreeWidgetItem* QSttGbTreeCtrl_ExportRpt::AddObj(CExBaseObject *pObj, BOOL bExpand)
{
	return CExBaseListTreeCtrl::AddObj(pObj, bExpand);
}

QExBaseTreeWidgetItem* QSttGbTreeCtrl_ExportRpt::AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand)
{
	QExBaseTreeWidgetItem* pItem = CExBaseListTreeCtrl::AddObj(pObj, hParent, bExpand);
	CString strIconPath = _P_GetResourcePath();
	strIconPath += "windows/";

	if(pItem)
	{
		if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			strIconPath += "Gbt_SttDevice.bmp";
		}
		else if(pObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			strIconPath += "Gbt_SttItems.bmp";
		}

		QIcon icon(strIconPath);
		pItem->setIcon(0, icon);
	}

	return pItem;
}