#pragma once

#include "..\..\..\61850\Module\SCL\SclIecCfgDatas.h"


// CSclCCTreeCtrl

#define SCLFILE_TREECTRL_MNGRVIEW_NATURAL       0X0191000
#define SCLFILE_TREECTRL_MNGRVIEW_VOLLEVEL      0X0191001
#define SCLFILE_TREECTRL_MNGRVIEW_DVMTYPE       0X0191002
#define SCLFILE_TREECTRL_MNGRVIEW_VOLANDDVM     0X0191003



class CSclCCTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CSclCCTreeCtrl)
public:
	CWnd *m_pViewWnd;
	void SetViewWnd(CWnd *pViewWnd)									{		m_pViewWnd = pViewWnd;	}
	void SetTreeViewIndex(long nIndex){ m_nTreeViewIndex = nIndex ;}


private:
	CExBaseList *m_pSclIedList;
	CWnd *m_pSvInMsgRcvWnd;
	CWnd *m_pSvOutMsgRcvWnd;
	CWnd *m_pGsInMsgRcvWnd;
	CWnd *m_pGsOutMsgRcvWnd;
	CWnd *m_pRptCtrlMsgRcvWnd;
	CWnd *m_pLogCtrlMsgRcvWnd;
	CWnd *m_pDataSetMsgRcvWnd;
	BOOL m_bCanPostSelChangeMsg;
	CImageList m_imgSclData;

	CString m_strCurrIedID;
	CSclIed *m_pCurrSelIed;

	long m_nTreeViewIndex;

public:
	CSclCCTreeCtrl();
	virtual ~CSclCCTreeCtrl();
	
	void ShowIecfgSclIeds(CExBaseList *pList);
	void AttachSvInMsgRcvWnd(CWnd *pWnd)	{	m_pSvInMsgRcvWnd = pWnd;	}
	void AttachSvOutMsgRcvWnd(CWnd *pWnd)	{	m_pSvOutMsgRcvWnd = pWnd;	}
	void AttachGsInMsgRcvWnd(CWnd *pWnd)	{	m_pGsInMsgRcvWnd = pWnd;	}
	void AttachGsOutMsgRcvWnd(CWnd *pWnd)	{	m_pGsOutMsgRcvWnd = pWnd;	}
	void AttachRptCtrlMsgRcvWnd(CWnd *pWnd)	{	m_pRptCtrlMsgRcvWnd = pWnd;	}
	void AttachLogCtrlMsgRcvWnd(CWnd *pWnd)	{	m_pLogCtrlMsgRcvWnd = pWnd;	}
	void AttachDataSetMsgRcvWnd(CWnd *pWnd)	{	m_pDataSetMsgRcvWnd = pWnd;	}
	void Filter(const CString &strText);
	void SetIDB_SclData(UINT nIDB);
	void SetCurrIedID(const CString &strIedID);
	CSclIed* GetCurrSelIed()	{	return m_pCurrSelIed;	}

	void UpdateTabForm(CExBaseList *pSel );

protected:
	BOOL CanInsert(CExBaseObject *pObj);
	BOOL CanInsert(UINT nClassID);

	void ShowSclObj(CExBaseList *pList, HTREEITEM hParent);
	void ShowSclObjByVolLevel(CExBaseList *pList, HTREEITEM hParent);
	void ShowSclObjByDvmType(CExBaseList *pList, HTREEITEM hParent);
	void ShowSclObjByVolAndDvm(CExBaseList *pList, HTREEITEM hParent);
	void InsertItemByDevice( HTREEITEM hItemNO , HTREEITEM *hItemDvm ,CExBaseList *pList );
	void InsertItemByVoltage( CExBaseObject *p ,HTREEITEM *hItemDvm ,long *nIndex);
	CString GetSclObjName(CExBaseObject *pSclObj, UINT &nClassID);

	virtual void OnContextMenuTree(CWnd* pWnd,CPoint point,CExBaseObject* pObj);
	virtual void InitContextMenuTree(CMenu &menu,CExBaseObject* pObj);
	CExBaseObject* GetSelObject();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnUpdateNaturalGroupShow(CCmdUI* pCmdUI);
	afx_msg void OnNaturalGroupShow();
	afx_msg void OnUpdateVolLevelShow(CCmdUI* pCmdUI);
	afx_msg void OnVolLevelShow();
	afx_msg void OnUpdateDvmTypeShow(CCmdUI* pCmdUI);
	afx_msg void OnDvmTypeShow();
	afx_msg void OnUpdateVolAndDvmShow(CCmdUI* pCmdUI);
	afx_msg void OnVolAndDvmShow();
};


