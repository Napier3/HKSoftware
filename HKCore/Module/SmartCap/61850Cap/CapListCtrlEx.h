#pragma once

#include "ProtocolBase/Pcap/FrameMemBufferMngr.h"

// CCapListCtrlEx

#define ID_CAP_LISTCTRL   31357
#define WM_CAPLIST_ITEM_SEL   (WM_USER + 1418)

class CCapListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CCapListCtrlEx)

public:
	CCapListCtrlEx();
	virtual ~CCapListCtrlEx();
	void CreateWatch(CRect rc, CWnd *pParent);
	void ExitCap();
	void SetFrameMemBufferMngr(CXSmMemBufferMngr *pFrameMemBufferMngr);


private:
	long m_nAddNew;
	long m_nViewCurrIndex;
	long m_nViewCurrCount;
	CXSmMemBufferMngr *m_pFrameMemBufferMngr;
	long CAP_SPY_MAX_COUNT;
	__int64 m_n64BeginTime;
	double m_dBeginTime;
	BOOL m_bFirstTime;

#ifndef FrameMemBuffer_use_FrameID
	__int64 m_n64FrameID;
#endif

protected:
	BOOL GetItemText(CFrameMemBuffer *pCapBuffer, long nSubItem, CString &strText);
//	void GetAddrText(_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest=FALSE);
//	void GetContentText(CFrameRecord *pCapBuffer, CString &strText);
//	BOOL GetItemTextBuffer(CFrameRecord *pCapBuffer,CString &strText);
//	void GetDir(_ETHER_CAP_IP cap_ip, CString &strText);

	void PostItemSelChangeMsg(BOOL bCreateAndShow=FALSE);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShowWatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowWatchs(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult);
};


