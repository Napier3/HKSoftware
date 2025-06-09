#pragma once

#include "SclIecCfgDatas.h"

// CSclIecCfgTreeCtrl

class CSclIecCfgTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CSclIecCfgTreeCtrl)

private:
	CExBaseList *m_pCurrSelCtrls;
	CExBaseList *m_pSclIedList;
	CWnd *m_pMsgRcvWnd;
	BOOL m_bCanPostSelChangeMsg;
	CImageList m_imgSclData;

	CString m_strCurrIedID;
	CSclIed *m_pCurrSelIed;
	BOOL m_bShowDetail;

public:
	CSclIecCfgTreeCtrl();
	virtual ~CSclIecCfgTreeCtrl();
	
	void ShowIecfgSclIeds(CExBaseList *pList, BOOL bShowDetail=TRUE);
	void ShowSelectIED(const CString &strIedId);//周宏军 20200306 增加用于指定选择IED
	void AttachMsgRcvWnd(CWnd *pWnd)	{	m_pMsgRcvWnd = pWnd;	}
	void Filter(const CString &strText);
	void SetIDB_SclData(UINT nIDB);
	void SetCurrIedID(const CString &strIedID);
	CSclIed* GetCurrSelIed()	{	return m_pCurrSelIed;	}
	CSclIed* GetCurrSelIedEx();

protected:
	BOOL CanInsert(CExBaseObject *pObj);
	BOOL CanInsert(UINT nClassID);

	void ShowSclObj(CExBaseList *pList, HTREEITEM hParent);
	CString GetSclObjName(CExBaseObject *pSclObj, UINT &nClassID);;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


