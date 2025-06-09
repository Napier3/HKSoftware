#include "SttCommCfgPointTblFileImportTreeCtrl.h"
#include "../../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"
extern CFont *g_pSttGlobalFont;
//////////////////////////////////////////////////////////////////////////

//QSttCommCfgPointTblFileImportTreeItem
QSttCommCfgPointTblFileImportTreeItem::QSttCommCfgPointTblFileImportTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttCommCfgPointTblFileImportTreeItem::QSttCommCfgPointTblFileImportTreeItem(QTreeWidget *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttCommCfgPointTblFileImportTreeItem::~QSttCommCfgPointTblFileImportTreeItem()
{

}

void QSttCommCfgPointTblFileImportTreeItem::UpdateItemColor()
{

}


//////////////////////////////////////////////////////////////////////////
//QSttCommCfgPointTblFileImportTreeCtrl
QSttCommCfgPointTblFileImportTreeCtrl::QSttCommCfgPointTblFileImportTreeCtrl(QFont *font,QWidget *parent)
    : CExBaseListTreeCtrl(parent)
{
	setColumnWidth(0,500);

    if (font != NULL)
    {
        setFont(*font);
    }

	InitScrollCtrl(verticalScrollBar());
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	installEventFilter(this);

	AddClassID(DTMCLASSID_CDATAGROUP);
	AddClassID(DVMCLASSID_CDVMDATA);
	setFont(*g_pSttGlobalFont);
}

QSttCommCfgPointTblFileImportTreeCtrl::~QSttCommCfgPointTblFileImportTreeCtrl()
{

}

QExBaseTreeWidgetItem* QSttCommCfgPointTblFileImportTreeCtrl::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	return new QSttCommCfgPointTblFileImportTreeItem(parent, pData);
}


void QSttCommCfgPointTblFileImportTreeCtrl::UpdateItemColour()
{

}

void QSttCommCfgPointTblFileImportTreeCtrl::OnItemSelChanged(CExBaseObject *pSel)
{
	QExBaseTreeWidgetItem* pItem = (QExBaseTreeWidgetItem*)pSel->m_dwItemData;
	emit itemClicked(pItem, 0);
}

void QSttCommCfgPointTblFileImportTreeCtrl::ShowBaseList(CExBaseList *pList, BOOL bAddRoot)
{
	CExBaseListTreeCtrl::ShowBaseList(pList, bAddRoot);

}

BOOL QSttCommCfgPointTblFileImportTreeCtrl::CanAdd(CExBaseObject *pObj)
{

	return CExBaseListTreeCtrl::CanAdd(pObj);
}

void QSttCommCfgPointTblFileImportTreeCtrl::focusOutEvent(QFocusEvent *e)
{
	emit sig_focusOutEventGbTree(e);
}

void QSttCommCfgPointTblFileImportTreeCtrl::mousePressEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	mousePressEvent_ScrollBase(ev);
#endif
	QTreeWidget::mousePressEvent( ev );
}


void QSttCommCfgPointTblFileImportTreeCtrl::mouseMoveEvent(QMouseEvent *ev)
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

void QSttCommCfgPointTblFileImportTreeCtrl::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseReleaseEvent_ScrollBase(ev))
	{
		return;
	}
#endif

	QTreeWidget::mouseReleaseEvent( ev );
}

