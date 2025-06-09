#pragma once

#include "DvmDevice.h"

/////////////////////////////////////////////////////////////////////////////
// CViewTree ����
#define DVMOBJ_SEL_CHANGED  (WM_USER+1855)

class CDvmDeviceTree : public CTreeCtrl
{
// ����
public:
	CDvmDeviceTree();
	void ShowDvmDevice(CDvmDevice *pDevice, CWnd *pMsgWnd, BOOL bSetItemData=TRUE);
	virtual CExBaseObject* GetSelectObject();	

	void InsertDvmObj(CExBaseObject *pDvmObj);
	void UpdateDvmObj(CExBaseObject *pDvmObj);
private:
	CWnd *m_pMsgRcvWnd;
	CDvmDevice *m_pDvmDevice;
	BOOL m_bSetItemData;

	void InsertLdevice(CDvmLogicDevice *pLdevice, HTREEITEM hParent);
	void InsertDataset(CDvmDataset *pDataset, HTREEITEM hParent);
// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// ʵ��
public:
	virtual ~CDvmDeviceTree();
	
	CExBaseObject* SelChanged(HTREEITEM hItem);
	CExBaseObject* SelectItem(const CString& strID);
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};
