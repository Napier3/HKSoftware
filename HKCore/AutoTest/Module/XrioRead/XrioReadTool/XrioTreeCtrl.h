#pragma once
#include "../XrioCustom.h"

#define _XRIO_IMAGE_INDEX_CUSTOM_        1
#define _XRIO_IMAGE_INDEX_BLOCK_         0
#define _XRIO_IMAGE_INDEX_PARAMETER_     2


// CXrioTreeCtrl

class CXrioTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CXrioTreeCtrl)

public:
	CXrioTreeCtrl();
	virtual ~CXrioTreeCtrl();

	BOOL OnShowXrioTree(CXrioCustom *pXrioCustom);
	HTREEITEM Insert(CExBaseObject *pItem,HTREEITEM htiParent,HTREEITEM hAfter);
	UINT GetImgIndex(CExBaseObject*pItem);
	BOOL CanInsert(CExBaseObject* pObj);
	void SetFrameWnd(CWnd *pFrameWnd)									{		m_pFrameWnd = pFrameWnd;	}

protected:
	DECLARE_MESSAGE_MAP()
	void OnTvnSelchanged(HTREEITEM hItem);

	CExBaseList m_oParametersListRef;

private:
	CXrioCustom *m_pXrioCustom;
	CWnd *m_pFrameWnd;
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

inline void xrio_PostParaObjSelChangeMsg(CWnd *pWnd, UINT nMsg, CExBaseObject *pXObj)
{
	if (pWnd == NULL)
	{
		return;
	}

	pWnd->PostMessage(nMsg, (WPARAM)pXObj, (LPARAM)pXObj);
}


