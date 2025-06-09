#pragma  once

#include "../GuideBook/GuideBook.h"

class CGuideBookItemsSel : public CExBaseList
{
public:
	CGuideBookItemsSel();
	virtual ~CGuideBookItemsSel();

public:
	CItems *m_pItemsRef;
	long   m_nItemsRef;

	void BuildItems(CGuideBook *pGuideBook);

private:
	void BuildItemsSel(CItems *pItems);
	long BuildItemsSel();
	void BuildItemsSel_Del();
};

class CGuideBookItemsSelTreeCtrl : public CTreeCtrl
{
public:
	CGuideBookItemsSelTreeCtrl();
	virtual ~CGuideBookItemsSelTreeCtrl();

	//����
private:
	CGbItemBase* m_pCurrSelTestItem;		//��ǰѡ�еĲ�����Ŀ
	HTREEITEM m_hCurrSelTestItem;
	UINT m_nCurrSelTestItemIndex;
	BOOL m_bInTestItemInitState;

	long m_nTimerIDEvent;
	CPoint m_ptSelTestIItem;
	BOOL m_bShowOnlySelTestItems;
	BOOL m_bInUpdateItemsState;

	COLORREF m_crWindow;	// = RGB(0,0,255);
	long m_xSelCheckBox;			//ѡ����λ��
	long m_xItemTypeIcon;		//������Ŀ����ͼ��λ��
	long m_xItemTitle;					//������Ŀ�����λ��

	CGuideBook	*m_pGuideBook;
	CImageList  *m_pImageList;
	CGuideBookItemsSel m_oGuideBookItemsSel;
	
	//�����ӿ�
public:
	void InitGuideBook(CGuideBook* pGuideBook);
	void CloseTestProject();
	CGbItemBase* GetCurrSelTestItem()			{		return m_pCurrSelTestItem;		}
	void SelectTopItem(CGbItemBase* pItem);

protected:
	virtual void InsertGbItemToTreeCtrl(CGuideBookItemsSel *pItemsSel,HTREEITEM htiParent);
	virtual void InsertGbItemChildrenToTreeCtrl(CGuideBookItemsSel *pItemsSel,HTREEITEM htiParent);
	CGbItemBase* GetTestItemByTreeItem(long hTreeItem);
	void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);
	void UpdateItemSelectedState(CGbItemBase* pItem);

	//�������
	BOOL IsBadRect(CRect &r)
	{
		return ( r.IsRectEmpty() || (r.Height() <= 0) || (r.Width() <= 0) );
	}
	
	void GetCheckBoxRect(CRect &rcText,CRect &rcCheck);
	virtual long _DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult);
	virtual long _OnLButtonDown(long xPoint,long yPoint);
	virtual long _OnRButtonDown(long xPoint,long yPoint);
	virtual long _OnLButtonDblClk(long xPoint,long yPoint);
	virtual void _SetShowOnlySelTestItems(long nShow);
	virtual long OnItemExpandStateChanged(OLE_HANDLE hItem,long nAction);
	virtual COLORREF GetItemStateColor(CGbItemBase *pItem)	{	return  RGB(0, 0, 0);	}

	long GetVisibleItemCount(long &nVisibleCount, long &nCurrItemIndex, CGbItemBase *pCurrItem, CGbItemBase *pParent);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExpandAllChildren();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};