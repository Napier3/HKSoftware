#pragma once

#include "EpFrameRecord.h"
#include "EpCapThreadBase.h"
// CEpCapListCtrlEx

#define ID_EPCAP_LISTCTRL   31357
#define CAP_SPY_MAX_COUNT   5000

class CEpCapListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CEpCapListCtrlEx)

public:
	CEpCapListCtrlEx();
	virtual ~CEpCapListCtrlEx();
	void CreateWatch(CRect rc, CWnd *pParent);
	void SetCapConfig(CExBaseList *pCapConfig)	{	m_pCapConfig = pCapConfig;	}
	void ExitCap();

private:
	long m_nAddNew;
	long m_nCurrIndex;
	long m_nCurrCount;
	DWORD m_dwFrameRecord[CAP_SPY_MAX_COUNT];
	CExBaseList *m_pCapConfig;

protected:
	BOOL GetItemText(CEpFrameRecord *pRecord, long nSubItem, CString &strText);
	void GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest=FALSE);
	void GetContentText(CEpFrameRecord *pRecord, CString &strText);
	BOOL GetItemTextBuffer(CEpFrameRecord *pRecord,CString &strText);
	void GetDir(EP_ETHER_CAP_IP cap_ip, CString &strText);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShowWatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowWatchs(WPARAM wParam, LPARAM lParam);
};


