#pragma once
#include "../GuideBook.h"

class CRptItem :	public CExBaseList
{
public:
	CRptItem(void);
	virtual ~CRptItem(void);

//����
public:
	CGbItemBase *m_pGbItemRef;
	BOOL m_bHasBkmk;
	BOOL m_bExpand;

//�����ӿ�
public:
	void InitGbItems(CGuideBook *pGuideBook);
	void InitGbItem(CExBaseList *pList);
	BOOL InitItemStateByBkmk();
	void ClearDWData();
	void InitExpandState(BOOL bExpand=TRUE);
	BOOL IsAllAncestorExpand();

//��д���෽��
public:
	UINT GetClassID()		{		return RPTCLASSID_RPTITEM;	}
	//���οؼ���صĲ���
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

};
