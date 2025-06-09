#pragma once

#include "PNTplRoot.h"
#include "..\..\XrioRead\XrioCustom.h"

class CPNTplTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CPNTplTreeCtrl)

public:
	CPNTplTreeCtrl();
	virtual ~CPNTplTreeCtrl();

protected:
	CPNTplRoot* m_pPNTpl;	
	CWnd *m_pFrameWnd;
	DWORD m_dwRcvMsg;
	BOOL m_bChangeChild;							//标识是否需要改变子对象显示，在SelChanged中使用
	CExBaseObject* m_pTreeSelNode;
	CExBaseObject* m_pTreeSelNodePrev;

public:
	void SetTreeSelNode(CExBaseObject* pObj)								{		m_pTreeSelNode = pObj;		}
	CExBaseObject* GetTreeSelNode()													{		return m_pTreeSelNode;		}
	void SetChangeChild(BOOL bFlag)													{		m_bChangeChild = bFlag;					}
	void InitShowPNTpl(CPNTplRoot* pPNTpl);
	void SetFrameWnd(CWnd *pFrameWnd, DWORD dwRcvMsg=0)									
	{		m_pFrameWnd = pFrameWnd;	m_dwRcvMsg = dwRcvMsg;	}
	//CExBaseObject *GetCurrDvmNode()													{		return m_pCurrDvmNode;					}
	CExBaseObject* SelChanged(HTREEITEM hItem);
	void InsertToTreeCtrl(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter = TVI_LAST, BOOL bSelect=FALSE);
	void UpdateToTreeCtrl(CExBaseObject *pItem);

	BOOL ChangeTreePosition(CExBaseObject* p1,CExBaseObject* p2);
	void DeleteTplNode(CExBaseObject *pTplNode);

private:
	void OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pDvmNode);
	UINT GetImgIndex(CExBaseObject* pDvmNode);
	BOOL IsObjVisible(UINT nClassID);

protected:	
	virtual void InsertChildrenToTreeCtrl(CExBaseList* pItem,HTREEITEM htiParent);
	CExBaseObject* GetDvmObjByTreeItem(long hTreeItem);

public:
	DECLARE_MESSAGE_MAP()

};

