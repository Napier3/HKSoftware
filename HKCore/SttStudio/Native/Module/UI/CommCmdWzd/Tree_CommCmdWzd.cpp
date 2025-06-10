#include "Tree_CommCmdWzd.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

CTree_CommCmdWzd::CTree_CommCmdWzd(QWidget *parent)
: CExBaseListTreeCtrl(parent)
{
	nHC = 1;
	m_bIsInInitState = TRUE;
}

CTree_CommCmdWzd::~CTree_CommCmdWzd()
{
}

void CTree_CommCmdWzd::ShowBaseList(CExBaseList *pList, BOOL bAddRoot)
{
	m_bIsInInitState = TRUE;
	QExBaseTreeWidgetItem* hItem = NULL;
	m_pList = pList;

	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nDataCount = 0;
	long nSelCount = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		hItem = AddObj(p,(QExBaseTreeWidgetItem* ) NULL, true);
		nDataCount = ((CExBaseList*)p)->GetCount();
		CDataGroup *pGrp = (CDataGroup *)p;
		nSelCount = GbGenWzd_GetSelCount(pGrp);

		if (nSelCount > 0)
		{
			pGrp->m_strValue = _T("1");
		}
		else
		{
			pGrp->m_strValue = _T("0");
		}
	
		if (hItem == NULL)
		{
			continue;
		}

		hItem->setExpanded(true);

		if (nSelCount == 0)
		{
			hItem->setCheckState(0, Qt::Unchecked);
		}
		else if (nSelCount == nDataCount)
		{
			hItem->setCheckState(0, Qt::Checked);
		}
		else
		{
			hItem->setCheckState(0, Qt::PartiallyChecked);
		}
	}

	m_bIsInInitState = FALSE;
}

QExBaseTreeWidgetItem* CTree_CommCmdWzd::AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand)
{
 	if(pObj->m_strID == "ReadSetting" 
		|| pObj->m_strID == "ReadEna"
		|| pObj->m_strID == STT_CMD_PARA_CMDAFT
		|| ((CExBaseList*)pObj->GetParent())->m_strID == STT_CMD_PARA_CMDAFT)
 	{
 		return NULL;
 	}

	UINT nClassID = pObj->GetClassID();
	QExBaseTreeWidgetItem* hItem = NULL;

	if (!CanAdd(nClassID))
	{
		return NULL;
	}

	hItem = InsertItem(hParent, pObj);
	hItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

	if (pObj->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		if (dvm_GetDvmX_Value_long(pObj) == 1)
		{
			hItem->setCheckState(0, Qt::Checked);
		}
		else
		{
			hItem->setCheckState(0, Qt::Unchecked);
		}
	}
	
	//pObj->m_dwReserved = 1;  //��ʾ��ѡ
	//dvm_SetDvmX_Value(pObj, 1); //2022-9-12  lijuniqng  ʹ��m_dwReserved���ܱ��浽�ļ�������ʹ��Value����

	if (!CBaseObject::IsBaseList(nClassID))
	{
		return hItem;
	}

	CExBaseList *pList = (CExBaseList*)pObj;
	AddObjChildren(pList, hItem, bExpand);

	if (bExpand)
	{
		hItem->setExpanded(true);
	}

	return hItem;
}

void CTree_CommCmdWzd::on_slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol)
{
	if (m_bIsInInitState)
	{
		return;
	}

	QTreeWidgetItemIterator it(this);
	CExBaseObject *pSel = ((QExBaseTreeWidgetItem*)pTreeItem)->m_pItemData;
	UINT nClassID = pSel->GetClassID();

	//��δѡ���Ϊѡ��״̬��ĳ�����ڵ�
	//if (pTreeItem->type() == Type_CombatMission)
	if(nClassID == DTMCLASSID_CDATAGROUP)
	{
		if (nHC)   //HC�𵽻����������ã�Ϊ˽�б�����Ա����ʼֵ��Ϊ1
		{
			if (pTreeItem->checkState(0) == Qt::Checked || pTreeItem->checkState(0) == Qt::PartiallyChecked)
			{
				//�����������
				nHC = 0;
				while (*it)
				{
					if (*it == pTreeItem || pTreeItem == (*it)->parent())
					{
						++it;
						continue;
					}
// 					else if ((*it)->type() == Type_CombatMission)
// 					{
// 						(*it)->setCheckState(0, Qt::Unchecked);
// 					}

					++it;
				}
			}
		}
	}

	if (pTreeItem->checkState(0) == Qt::Checked)
	{
		QTreeWidgetItem *parent = pTreeItem->parent();
		int cnt = pTreeItem->childCount();
		if (cnt > 0)
		{
			for (int i = 0; i < cnt; i++)
			{
				pTreeItem->child(i)->setCheckState(0, Qt::Checked);
			}
		}
		else
		{
			updateParentItem(pTreeItem);
		}
	}
	else if (pTreeItem->checkState(0) == Qt::Unchecked)
	{
		int cnt = pTreeItem->childCount();
		if (cnt > 0)
		{
			for (int i = 0; i < cnt; i++)
			{
				pTreeItem->child(i)->setCheckState(0, Qt::Unchecked);
			}
		}
		else
		{
			updateParentItem(pTreeItem);
		}
	}
	//�������ָ�
	nHC = 1;

	if(pTreeItem->checkState(0) == Qt::Unchecked)
	{
		//pSel->m_dwReserved = 0;
		dvm_SetDvmX_Value(pSel, 0); //2022-9-12  lijuniqng  ʹ��m_dwReserved���ܱ��浽�ļ�������ʹ��Value����
	}
	else
	{
		//pSel->m_dwReserved = 1;
		dvm_SetDvmX_Value(pSel, 1); //2022-9-12  lijuniqng  ʹ��m_dwReserved���ܱ��浽�ļ�������ʹ��Value����
	}

	//��������ڵ㱻ȡ����ѡ
	if(pSel->m_strID == STT_CMD_PARA_CMDBFT)
	{
		dvm_SetDvmX_Value(pSel, 1);
	}

	emit this->sig_CmdTreeItemChanged((QExBaseTreeWidgetItem*)pTreeItem);
}

//�����ڲ��Ժ�ָ����������ǰ�仯
void CTree_CommCmdWzd::on_slot_TreeItemChanged_Aft(QTreeWidgetItem *pTreeItem)
{
	CDvmData *pData = (CDvmData *)((QExBaseTreeWidgetItem*)pTreeItem)->m_pItemData;
	
	if (pData->m_strValue == _T("1"))
	{
		pTreeItem->setCheckState(0, Qt::Checked);
	}
	else
	{
		pTreeItem->setCheckState(0, Qt::Unchecked);
	}

	updateParentItem(pTreeItem);
	emit this->sig_CmdTreeItemChanged((QExBaseTreeWidgetItem*)pTreeItem);
}

void CTree_CommCmdWzd::updateParentItem(QTreeWidgetItem *item)
{
	if (m_bIsInInitState)
	{
		return;
	}

	QTreeWidgetItem *parent = item->parent();
	if (parent == NULL)
	{
		return;
	}
	//ѡ�е��ӽڵ����
	int selectedCount = 0;
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++)
	{
		QTreeWidgetItem *childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if (selectedCount <= 0)
	{
		//δѡ��״̬
		parent->setCheckState(0, Qt::Unchecked);
	}
	else if (selectedCount > 0 && selectedCount < childCount)
	{
		//����ѡ��״̬
		parent->setCheckState(0, Qt::PartiallyChecked);
	}
	else if (selectedCount == childCount)
	{
		//ѡ��״̬
		parent->setCheckState(0, Qt::Checked);
	}
}