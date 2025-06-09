#pragma once

#include "..\DataGroup.h"
#include "..\..\BaseClass\ExBaseListListCtrl.h"



class CDataGroupListView : public CExBaseListListCtrl
{
	DECLARE_DYNAMIC(CDataGroupListView)

public:
	CDataGroupListView();
	virtual ~CDataGroupListView();

	void OnDataSelChanged(CShortData *pData);
	void OnDataValueChanged(CShortData *pData);
	virtual void InitCollumns();

	CExBaseObject *m_pRoot;
	CString m_strFlag;

	static CString GetDataPath(CShortData *pData, CExBaseObject *pRoot, const CString &strFlag);

protected:
	CExBaseList m_listDatas;
	BOOL m_bFirstShow;
	long m_nCurrSelIndex;

	virtual void UpdateListCtrl(CExBaseObject* pObj, long nItem);

public:
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};