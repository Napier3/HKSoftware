#ifndef QDeviceModelTreeCtrl_Eng_H
#define QDeviceModelTreeCtrl_Eng_H

#include "../../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "QDeviceModelDlg_Eng.h"

class QDeviceModelTreeItem_Eng:public QExBaseTreeWidgetItem
{
public:
    QDeviceModelTreeItem_Eng(QTreeWidgetItem *parent, CExBaseObject *pData);
    QDeviceModelTreeItem_Eng(QTreeWidget *parent, CExBaseObject *pData);
    virtual ~QDeviceModelTreeItem_Eng();
    void UpdateItemColor();
};

class QDeviceModelTreeCtrl_Eng:public CExBaseListTreeCtrl
{
    Q_OBJECT

public:
	void SetCurrentShowType(long nTreeShowType){ m_nTreeShowType = nTreeShowType; }
    QDeviceModelTreeCtrl_Eng(QWidget *parent = 0,QFont *font = 0);
    virtual ~QDeviceModelTreeCtrl_Eng();
    virtual QExBaseTreeWidgetItem* NewItem(QTreeWidgetItem *parent, CExBaseObject *pData);
    void UpdateItemColour();
    void OnItemSelChanged(CExBaseObject *pSel);
    virtual void AddObjChildren(CExBaseList *pList, QExBaseTreeWidgetItem* hItem, BOOL bExpand=FALSE);
    virtual void ShowBaseListEx(CExBaseList *pList,BOOL bExpand = FALSE);//增加展开树形控件节点  zhouhj  20221022
    virtual void ShowBaseListAfterUpdate(CExBaseList *pList, CExBaseObject *pSelObj, BOOL bExpand = FALSE);
private:
    long m_nTreeShowType;
    CExBaseObject* FindFirstValidNode(CExBaseList *pSelObj);
    CExBaseObject* FindFirstValidChildNode(CExBaseList *pSelObj);
    BOOL IsValidNode(CExBaseList *pSelObj);
    virtual BOOL CanAdd(CExBaseObject *pObj);
};
#endif // QDeviceModelTreeCtrl_Eng_H
