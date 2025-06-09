#pragma once

#include "CapCycleMemBuffer.h"
#include "CapSmFileDB\SmFileDBQueryDef.h"
#include "CapSmFileDB\CapSmDb.h"

// CEpCapQueryDatasListCtrlEx

#define ID_EPCAP_DATAS_LISTCTRL   31399



class CEpCapQueryDatasListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CEpCapQueryDatasListCtrlEx)

public:
	CEpCapQueryDatasListCtrlEx();
	virtual ~CEpCapQueryDatasListCtrlEx();
	void CreateWatch(CRect rc, CWnd *pParent);

	void ShowResults(CEpDeviceDatas *pDeviceDatas, DWORD dwProtocol);
	void AddResults(CEpDeviceDatas *pDeviceDatas, DWORD dwProtocol);

private:
	long m_nAddNew;
	long m_nCurrIndex;
	long m_nCurrCount;
	CEpQueryEpCapDbBufferIndex *m_pQueryResults;
	CExBaseList *m_pCapConfig;
	CCapSmDb *m_pCapSmDb;
	DWORD m_dwDeviceDataType;
	DWORD m_dwProtocol;

	CEpDeviceDatas *m_pDeviceDatas;

protected:
	BOOL GetItemText(CEpY4Data *pData, long nSubItem, CString &strText);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShowWatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowWatchs(WPARAM wParam, LPARAM lParam);
};


