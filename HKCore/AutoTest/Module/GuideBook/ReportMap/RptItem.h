#pragma once
#include "../GuideBook.h"

class CRptItem :	public CExBaseList
{
public:
	CRptItem(void);
	virtual ~CRptItem(void);

//属性
public:
	CGbItemBase *m_pGbItemRef;
	BOOL m_bHasBkmk;
	BOOL m_bExpand;

//公共接口
public:
	void InitGbItems(CGuideBook *pGuideBook);
	void InitGbItem(CExBaseList *pList);
	BOOL InitItemStateByBkmk();
	void ClearDWData();
	void InitExpandState(BOOL bExpand=TRUE);
	BOOL IsAllAncestorExpand();

//重写父类方法
public:
	UINT GetClassID()		{		return RPTCLASSID_RPTITEM;	}
	//树形控件相关的操作
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

};
