#pragma once

class CSclFileTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CSclFileTreeCtrl)
public:
	CWnd *m_pFrameWnd;
	void SetFrameWnd(CWnd *pFrameWnd)									{		m_pFrameWnd = pFrameWnd;	}

private:
	BOOL m_bCanPostSelChangeMsg;
	CImageList m_imgSclData;
	long m_nIEDNumber;
	HTREEITEM m_hIedItem;
	CWnd *m_pTreeMsgRcvWnd;

	CString m_strNodeName;

public:
	CSclFileTreeCtrl();
	virtual ~CSclFileTreeCtrl();
	void ShowModelTree();
	void Filter(const CString &strText);
	void SetIDB_SclData(UINT nIDB);
	void AttachTreeMsgRcvWnd(CWnd *pWnd)	{	m_pTreeMsgRcvWnd = pWnd;	}
	void ShowMainTreeCtrl();
	void MyExpandTree(CTreeCtrl *pTreeCtrl ,HTREEITEM hTreeItem);
	void PopulateMainTreeCtrl(pugi::xml_node oPugiNode, HTREEITEM hParent);
	void GetAttrNameAndDescValue(pugi::xml_node oPugiNode,CString *strAttrVal);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


