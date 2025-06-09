#ifndef QSTTSCLIEDTREEITEM_H
#define QSTTSCLIEDTREEITEM_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "../../../Module/BaseClass/ExBaseObject.h"

class QSttSclIedTreeItem : public QTreeWidgetItem
{
public:
	QSttSclIedTreeItem(QTreeWidgetItem *parent);
    QSttSclIedTreeItem(QTreeWidget *parent);
    ~QSttSclIedTreeItem();

public:
    void SetTreeItemObject(CExBaseObject *pObj);
    CExBaseObject* GetTreeItemObject(){    return m_pTreeItemNode; }

    virtual void ShowItemData();

private:
    CExBaseObject *m_pTreeItemNode;


};

#endif // QSTTSCLIEDTREEITEM_H
