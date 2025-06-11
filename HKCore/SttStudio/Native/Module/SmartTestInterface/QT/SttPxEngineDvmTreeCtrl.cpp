#include "SttPxEngineDvmTreeCtrl.h"
#include "../../../../AutoTest/Module/AutoTestGlobalDefine.h"

#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"

//////////////////////////////////////////////////////////////////////////
//QSttPxEngineDvmTreeItem
QSttPxEngineDvmTreeItem::QSttPxEngineDvmTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttPxEngineDvmTreeItem::QSttPxEngineDvmTreeItem(QTreeWidget *parent, CExBaseObject *pData)
: QExBaseTreeWidgetItem(parent, pData)
{
	
}

QSttPxEngineDvmTreeItem::~QSttPxEngineDvmTreeItem()
{

}

void QSttPxEngineDvmTreeItem::UpdateItemColor()
{

}


//////////////////////////////////////////////////////////////////////////
//QSttPxEngineDvmTreeCtrl
QSttPxEngineDvmTreeCtrl::QSttPxEngineDvmTreeCtrl(QFont *font,QWidget *parent)
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

	AddClassID(DVMCLASSID_CDVMDEVICE);
	AddClassID(DVMCLASSID_CDVMLOGICDEVICE);
	AddClassID(DVMCLASSID_CDVMDATASET);
}

QSttPxEngineDvmTreeCtrl::~QSttPxEngineDvmTreeCtrl()
{

}

QExBaseTreeWidgetItem* QSttPxEngineDvmTreeCtrl::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
	return new QSttPxEngineDvmTreeItem(parent, pData);
}


void QSttPxEngineDvmTreeCtrl::UpdateItemColour()
{

}

void QSttPxEngineDvmTreeCtrl::OnItemSelChanged(CExBaseObject *pSel)
{
	QExBaseTreeWidgetItem* pItem = (QExBaseTreeWidgetItem*)pSel->m_dwItemData;
	emit itemClicked(pItem, 0);
}

void QSttPxEngineDvmTreeCtrl::ShowBaseList(CExBaseList *pList, BOOL bAddRoot)
{
	CExBaseListTreeCtrl::ShowBaseList(pList, bAddRoot);

	CDvmDevice *pDevice = (CDvmDevice*)pList;
	CDvmDataset *pReport = pDevice->GetDataset(g_strPxDataSetID[PX_DSID_dsReport], g_strPxDataSetID[PX_DSID_dsReport]);

	if (pReport == NULL)
	{
		return;
	}

	pReport->m_strName = g_sLangTxt_SoeReportD;
	InsertItem(NULL, pReport);
}

BOOL QSttPxEngineDvmTreeCtrl::CanAdd(CExBaseObject *pObj)
{
	if (pObj->m_strID == g_strPxDataSetID[PX_DSID_dsReport])
	{
		return FALSE;
	}

	return CExBaseListTreeCtrl::CanAdd(pObj);
}

void QSttPxEngineDvmTreeCtrl::focusOutEvent(QFocusEvent *e)
{
	emit sig_focusOutEventGbTree(e);
}

void QSttPxEngineDvmTreeCtrl::mousePressEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	mousePressEvent_ScrollBase(ev);
#endif
	QTreeWidget::mousePressEvent( ev );
}


void QSttPxEngineDvmTreeCtrl::mouseMoveEvent(QMouseEvent *ev)
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

void QSttPxEngineDvmTreeCtrl::mouseReleaseEvent(QMouseEvent *ev)
{
#ifdef _PSX_QT_LINUX_
	if (!mouseReleaseEvent_ScrollBase(ev))
	{
		return;
	}
#endif

	QTreeWidget::mouseReleaseEvent( ev );
}

