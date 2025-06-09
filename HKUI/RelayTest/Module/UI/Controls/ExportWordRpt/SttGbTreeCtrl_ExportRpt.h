#ifndef QSTTGTREECTRL_EXPORTRPT_H
#define QSTTGTREECTRL_EXPORTRPT_H

#include <QTreeWidget>
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../../SttCmd/GuideBook/SttItemBase.h"

#include "../../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"

class QSttGbTreeItem_ExportRpt : public QExBaseTreeWidgetItem
{
public:
	QSttGbTreeItem_ExportRpt(QTreeWidgetItem *parent, CExBaseObject *pData);
	QSttGbTreeItem_ExportRpt(QTreeWidget *parent, CExBaseObject *pData);
	virtual ~QSttGbTreeItem_ExportRpt();
};

class QSttGbTreeCtrl_ExportRpt : public CExBaseListTreeCtrl
{
    Q_OBJECT
    
public:
public:
    QSttGbTreeCtrl_ExportRpt(QFont font,QWidget *parent);
	virtual ~QSttGbTreeCtrl_ExportRpt();
    
	virtual QExBaseTreeWidgetItem* NewItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, BOOL bExpand=FALSE);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand=FALSE);

	void OnItemSelChanged(CExBaseObject *pSel);
	void SetQTreeWidgetScrollWidth(long nTreeVertWidth,long nTreeLevelWidth);
	virtual QExBaseTreeWidgetItem* InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QFont m_oFont;

public slots:

protected:

private:
    CExBaseList *m_pGuideBook;
};

#endif // QSTTGTREECTRL_EXPORTRPT_H
