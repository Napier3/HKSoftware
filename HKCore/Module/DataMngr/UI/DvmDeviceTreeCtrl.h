#pragma once

#include "..\DvmDevice.h"

#define WM_DVMNODE_SELCHANGED   (WM_USER + 2303)

class CExBaseListTreeCtrlOptrInterface
{
public:
	virtual void OnNMDblclk(CTreeCtrl *pTreeCtrl, NMHDR *pNMHDR, LRESULT *pResult)	{	return;	}
};

class CDvmDeviceTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CDvmDeviceTreeCtrl)

public:
	CDvmDeviceTreeCtrl();
	virtual ~CDvmDeviceTreeCtrl();

protected:
	CDvmDevice* m_pDvmDevice;	
	CWnd *m_pFrameWnd;
	DWORD m_dwRcvMsg;
	BOOL m_bChangeChild;							//标识是否需要改变子对象显示，在SelChanged中使用
	CExBaseObject* m_pTreeSelNode;
	CExBaseObject* m_pTreeSelNodePrev;

public:
	CExBaseListTreeCtrlOptrInterface *m_pDataViewOptrInterface;

public:
	virtual void AttachDataViewOptrInterface(CExBaseListTreeCtrlOptrInterface *pInterface)	{	m_pDataViewOptrInterface = pInterface;	}
	void SetTreeSelNode(CExBaseObject* pObj)								{		m_pTreeSelNode = pObj;		}
	CExBaseObject* GetTreeSelNode()													{		return m_pTreeSelNode;		}
	void SetChangeChild(BOOL bFlag)													{		m_bChangeChild = bFlag;					}
	void InitShowDvmDevice(CDvmDevice* pDvmDevice);
	void SetFrameWnd(CWnd *pFrameWnd, DWORD dwRcvMsg=0)									
	{		m_pFrameWnd = pFrameWnd;	m_dwRcvMsg = dwRcvMsg;	}
	//CExBaseObject *GetCurrDvmNode()													{		return m_pCurrDvmNode;					}
	CExBaseObject* SelChanged(HTREEITEM hItem);
	void InsertToTreeCtrl(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter = TVI_LAST, BOOL bSelect=FALSE);
	void UpdateToTreeCtrl(CExBaseObject *pItem);

	BOOL ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2);
	void DeleteDvmNode(CExBaseObject *pDvmNode);
	CDvmDataset* GetCurrSelDataset();

private:
	void OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pDvmNode);
	UINT GetImgIndex(CExBaseObject* pDvmNode);
	BOOL IsObjVisible(UINT nClassID);

protected:	
	virtual void InsertChildrenToTreeCtrl(CExBaseList* pItem,HTREEITEM htiParent);
	CExBaseObject* GetDvmObjByTreeItem(long hTreeItem);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

};

