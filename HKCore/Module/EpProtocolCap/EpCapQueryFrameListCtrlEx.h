#pragma once

#include "CapCycleMemBuffer.h"
#include "CapSmFileDB\SmFileDBQueryDef.h"
#include "CapSmFileDB\CapSmDb.h"

// CEpCapQueryFrameListCtrlEx

#define ID_EPCAP_FRAME_LISTCTRL   31357


class CEpCapQueryFrameListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CEpCapQueryFrameListCtrlEx)

public:
	CEpCapQueryFrameListCtrlEx();
	virtual ~CEpCapQueryFrameListCtrlEx();
	void CreateWatch(CRect rc, CWnd *pParent);
	void SetCapConfig(CExBaseList *pCapConfig)	{	m_pCapConfig = pCapConfig;	}
	void SetQueryResults(CEpQueryEpCapDbBufferIndex *pQueryResults)	{	m_pQueryResults = pQueryResults;	}
	void SetCapSmDb(CCapSmDb *pSmbDb)	{	m_pCapSmDb = pSmbDb;	}
	void ShowResults();

private:
	long m_nAddNew;
	long m_nCurrIndex;
	long m_nCurrCount;
	CEpQueryEpCapDbBufferIndex *m_pQueryResults;
	CExBaseList *m_pCapConfig;
	CCapSmDb *m_pCapSmDb;

protected:
	BOOL GetItemText(CEpCapDbBufferIndex *pDbIndex, long nSubItem, CString &strText);
	void GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest=FALSE);
	void GetContentText(PEPCAPDBBUFFERINDEX pIndex, CString &strText);
	BOOL GetItemTextBuffer(CEpCapDbBufferIndex *pDbIndex,CString &strText);
	void GetDir(EP_ETHER_CAP_IP cap_ip, CString &strText);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShowWatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowWatchs(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChanged(NMHDR *pNMHDR, LRESULT *pResult);
};


