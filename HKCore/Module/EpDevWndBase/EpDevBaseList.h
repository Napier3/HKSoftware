#pragma once

#include "EpDevBase.h"
#include "..\BaseClass\ExBaseList.h"

class CEpDevBaseList : public CEpDevBase,public CTLinkList<CEpDevBase>
{
public:
	CEpDevBaseList();
	virtual ~CEpDevBaseList();

public:
	//基本方法
	virtual UINT GetClassID()								{	return EPDCLASSID_DEVBASELIST;	}

	//插入方法
	virtual long InsertBefore(long nIndex, CEpDevBase *pObj);
	virtual long InsertAfter(long nIndex, CEpDevBase *pObj);

	//查找方法
	//virtual long FindIndex(CEpDevBase* pObj);

	//改变位置
	virtual long DragDropObject(long nIndex1, long nIndex2)	{	return 0;	}
	virtual long MoveUp(CEpDevBase* pObj)					{	return 0;	}
	virtual long MoveDown(CEpDevBase* pObj);

	//创建子对象
	virtual CEpDevBase *CreateNewChildObject(long nClassID);

	//调整区域
	virtual long AdjustChildrenPos(long nLeft,long nTop);

	//计算区域
	virtual long CalChildrenSize(CSize &sz);

	//创建、销毁方法
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();

	//显示、隐藏方法	
	virtual void ShowChildren(UINT nShow);

	//绘制连接线方法
	virtual void DrawLinkLines(CDC *pDC)					{	}
	virtual void EraseLinkLines(CDC *pDC)					{	}
};