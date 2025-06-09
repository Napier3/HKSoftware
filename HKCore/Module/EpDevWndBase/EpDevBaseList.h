#pragma once

#include "EpDevBase.h"
#include "..\BaseClass\ExBaseList.h"

class CEpDevBaseList : public CEpDevBase,public CTLinkList<CEpDevBase>
{
public:
	CEpDevBaseList();
	virtual ~CEpDevBaseList();

public:
	//��������
	virtual UINT GetClassID()								{	return EPDCLASSID_DEVBASELIST;	}

	//���뷽��
	virtual long InsertBefore(long nIndex, CEpDevBase *pObj);
	virtual long InsertAfter(long nIndex, CEpDevBase *pObj);

	//���ҷ���
	//virtual long FindIndex(CEpDevBase* pObj);

	//�ı�λ��
	virtual long DragDropObject(long nIndex1, long nIndex2)	{	return 0;	}
	virtual long MoveUp(CEpDevBase* pObj)					{	return 0;	}
	virtual long MoveDown(CEpDevBase* pObj);

	//�����Ӷ���
	virtual CEpDevBase *CreateNewChildObject(long nClassID);

	//��������
	virtual long AdjustChildrenPos(long nLeft,long nTop);

	//��������
	virtual long CalChildrenSize(CSize &sz);

	//���������ٷ���
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();

	//��ʾ�����ط���	
	virtual void ShowChildren(UINT nShow);

	//���������߷���
	virtual void DrawLinkLines(CDC *pDC)					{	}
	virtual void EraseLinkLines(CDC *pDC)					{	}
};