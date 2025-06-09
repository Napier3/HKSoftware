#include "QDeviceModelTreeCtrl_Eng.h"

QDeviceModelTreeItem_Eng::QDeviceModelTreeItem_Eng(QTreeWidgetItem *parent, CExBaseObject *pData): QExBaseTreeWidgetItem(parent, pData)
{

}

QDeviceModelTreeItem_Eng::QDeviceModelTreeItem_Eng(QTreeWidget *parent, CExBaseObject *pData): QExBaseTreeWidgetItem(parent, pData)
{

}

QDeviceModelTreeItem_Eng::~QDeviceModelTreeItem_Eng()
{

}

void QDeviceModelTreeItem_Eng::UpdateItemColor()
{

}




QDeviceModelTreeCtrl_Eng::QDeviceModelTreeCtrl_Eng(QWidget *parent,QFont *font): CExBaseListTreeCtrl(parent)
{
    m_nTreeShowType = _FIXED_VALUE_CORRELATION_TYPE_;
    setColumnWidth(0,500);
    if (font != NULL)
    {
        setFont(*font);
    }
    AddClassID(DVMCLASSID_CDVMDEVICE);
    AddClassID(DVMCLASSID_CDVMLOGICDEVICE);
    AddClassID(DVMCLASSID_CDVMDATASET);
    AddClassID(DVMCLASSID_CDVMDATA);
    AddClassID(DVMCLASSID_CDVMVALUE);


}

QDeviceModelTreeCtrl_Eng::~QDeviceModelTreeCtrl_Eng()
{

}

QExBaseTreeWidgetItem *QDeviceModelTreeCtrl_Eng::NewItem(QTreeWidgetItem *parent, CExBaseObject *pData)
{
    return new QDeviceModelTreeItem_Eng(parent, pData);
}

void QDeviceModelTreeCtrl_Eng::UpdateItemColour()
{

}

void QDeviceModelTreeCtrl_Eng::OnItemSelChanged(CExBaseObject *pSel)
{
    QExBaseTreeWidgetItem* pItem = (QExBaseTreeWidgetItem*)pSel->m_dwItemData;
    emit itemClicked(pItem, 0);
}

void QDeviceModelTreeCtrl_Eng::AddObjChildren(CExBaseList *pList, QExBaseTreeWidgetItem *hItem, BOOL bExpand)
{
    POS pos = pList->GetHeadPosition();
    CExBaseObject *p = NULL;
    while (pos != NULL)
    {
        p = pList->GetNext(pos);

        if(p->GetClassID() == DVMCLASSID_CDVMVALUE || p->GetClassID() == DVMCLASSID_CDVMDATA)
        {
            CExBaseList *pChildList = (CExBaseList*)p;
            POS SubPos = pChildList->GetHeadPosition();
            CExBaseObject *pSubObj = NULL;
            while(SubPos)
            {
                pSubObj = pChildList->GetNext(SubPos);
                CExBaseList *pGrandchildrenList = (CExBaseList*)pSubObj;
                if(pGrandchildrenList->GetCount() > 0)
                {
                    AddObj(p, hItem, bExpand);
                    break;
                }
            }
        }
        else
        {
            AddObj(p, hItem, bExpand);
        }
    }
}

void QDeviceModelTreeCtrl_Eng::ShowBaseListEx(CExBaseList *pList,BOOL bExpand)
{
    clear();
//    QExBaseTreeWidgetItem* hItem = NULL,*hFirstItem = NULL;
    m_pList = pList;

    POS pos = pList->GetHeadPosition();
    CExBaseObject *p = NULL,*pCurrSelObj = NULL;

    while (pos != NULL)
    {
        p = pList->GetNext(pos);
        if ((p->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE && p->m_strID == XRIO_DEVICE_MODEL_ID_RIO) &&
                (m_nTreeShowType == _FIXED_VALUE_CORRELATION_TYPE_))
        {
            continue;
        }

        AddObj(p, (QExBaseTreeWidgetItem*)NULL, bExpand);

        if (pCurrSelObj != NULL)
        {
            continue;
        }

        if (p->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE)
        {
            CExBaseList *pLogDevice = (CExBaseList*)p;
//            pCurrSelObj = pLogDevice->GetHead();
            pCurrSelObj = FindFirstValidNode(pLogDevice);//Xrio文件测试没问题，普通的设备数据模型未测试，如果有问题可以先注掉
        }
        else
        {
            pCurrSelObj = p;
        }
    }

    SetCurrSelObj(pCurrSelObj);

    if (pCurrSelObj != NULL)
    {
        QExBaseTreeWidgetItem *hItem = (QExBaseTreeWidgetItem*)pCurrSelObj->m_dwItemData;
        slot_TreeItemClicked(hItem, 0);
    }

    //resizeColumnToContents(0);
}

void QDeviceModelTreeCtrl_Eng::ShowBaseListAfterUpdate(CExBaseList *pList, CExBaseObject *pSelObj, BOOL bExpand)
{
    clear();
    m_pList = pList;

    POS pos = pList->GetHeadPosition();
    CExBaseObject *p = NULL;

    while (pos != NULL)
    {
        p = pList->GetNext(pos);
        if ((p->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE && p->m_strID == XRIO_DEVICE_MODEL_ID_RIO) &&
                (m_nTreeShowType == _FIXED_VALUE_CORRELATION_TYPE_))
        {
            continue;
        }

        AddObj(p, (QExBaseTreeWidgetItem*)NULL, bExpand);
    }

    ASSERT(pSelObj);

    SetCurrSelObj(pSelObj);

    if (pSelObj != NULL)
    {
        QExBaseTreeWidgetItem *hItem = (QExBaseTreeWidgetItem*)pSelObj->m_dwItemData;
        slot_TreeItemClicked(hItem, 0);
    }
}

CExBaseObject* QDeviceModelTreeCtrl_Eng::FindFirstValidNode(CExBaseList *pSelObj)
{
    if(!pSelObj)
    {
        return NULL;
    }
    CExBaseObject* pObj = NULL;

    CExBaseObject* pDatasetObj = NULL;
    POS DatasetPos = pSelObj->GetHeadPosition();

    while(DatasetPos)
    {
        pDatasetObj = pSelObj->GetNext(DatasetPos);

        if(IsValidNode((CExBaseList*)pDatasetObj))
        {
            return pDatasetObj;
        }
        else
        {
            POS SubPos = ((CExBaseList*)pDatasetObj)->GetHeadPosition();
            while(SubPos)
            {
                pObj = ((CExBaseList*)pDatasetObj)->GetNext(SubPos);
                pObj = FindFirstValidChildNode((CExBaseList*)pObj);
                if(pObj != NULL)
                {
                    return pObj;
                }
            }
        }
    }
    //    return NULL;
    return pSelObj;
}

CExBaseObject *QDeviceModelTreeCtrl_Eng::FindFirstValidChildNode(CExBaseList *pSelObj)
{
    if(!pSelObj)
    {
        return NULL;
    }
    CExBaseObject* pObj = NULL;

    if(IsValidNode(pSelObj))
    {
        return pSelObj;
    }
    else
    {
        POS SubPos = pSelObj->GetHeadPosition();
        while(SubPos)
        {
            pObj = pSelObj->GetNext(SubPos);
            pObj = FindFirstValidChildNode((CExBaseList*)pObj);
            if(pObj != NULL)
            {
                return pObj;
            }
        }
    }
    return NULL;
}

BOOL QDeviceModelTreeCtrl_Eng::IsValidNode(CExBaseList *pSelObj)
{
    if(!pSelObj)
    {
        return FALSE;
    }
    CExBaseObject* pSubObj = NULL;
    POS pos = pSelObj->GetHeadPosition();
    POS SubPos = NULL;
    while(pos)
    {
        pSubObj = pSelObj->GetNext(pos);
        if(pSubObj != NULL)
        {
            SubPos = ((CExBaseList*)pSubObj)->GetHeadPosition();
        }
        while(SubPos)
        {
            CExBaseList* pGrandchildrenList = (CExBaseList*)((CExBaseList*)pSubObj)->GetNext(SubPos);
            if(pGrandchildrenList->GetCount() <= 0)
            {
                if(((CDvmValue*)pGrandchildrenList)->m_strValue == XRIO_DEVICE_MODEL_ID_ForeignId)
                {
                    return FALSE;//针对Xrio文件中补充的空的子节点，对于这样的空节点不作为第一个有效节点。
                }
                if(pGrandchildrenList->GetClassID() == DVMCLASSID_CDVMDATA)//针对普通的设备数据模型存在Data节点没有Value节点的情况，如果有也不添加。
                {
                    return FALSE;//这个IF分支在Xrio文件中应该不存在，但是对于普通的设备数据模型未测试，如果有问题可以注掉该分支。
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}

BOOL QDeviceModelTreeCtrl_Eng::CanAdd(CExBaseObject *pObj)
{
    return CExBaseListTreeCtrl::CanAdd(pObj);
}
