#pragma once
#include "WzdDlgBase.h"
#include "../StepCtrl/DvmMapGrid.h"
#include "../../../Module/GuideBook/GbDvmReplaceTool.h"
#include "../../../iSmartTestWzd/Resource.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"
#include "../../../../Module/DataMngr/DvmCmp/DvmMapTool.h"

class CWzdDlg_DvmMap : public CWzdDlgBase, public CGbDvmReplaceEventInterface
{
	DECLARE_DYNAMIC(CWzdDlg_DvmMap)
private:
	CDvmMapGrid m_gridMap;
	CStatic m_txtTitle;
	CStatic m_txtTip;

	CRect m_rcCtrls[6];
	BOOL m_bIsReplacing;
	CString m_strStandFile;
	CString m_strDestFile;
	CDvmMapTool m_oDvmCmpTool;
	long m_nStepCurrIndex;
	CGbDvmReplaceTool* m_pGbDvmReplaceTool;
	CString m_strInfo;
	CDvmDatasetMap* m_pCurDatasetMap;

public:  //2023-4-19  lijunqing
	virtual void ReplaceFinished();

public:
	CWzdDlg_DvmMap(CWnd* pParent = NULL);
	virtual ~CWzdDlg_DvmMap();

	enum { IDD = IDD_DVMMAP_DIALOG };

protected:
	virtual void XUI_InitAdjust();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCreateDatasetMap_Stand();
	afx_msg void OnCreateDatasetMap_Dest();
	afx_msg void OnDeleteDatasetMap_Stand();
	afx_msg void OnDeleteDatasetMap_Dest();
	HRESULT OnOpenDvmCmpDataset(WPARAM wParam, LPARAM lParam);
	LRESULT OnReplaceFinish(WPARAM wParam, LPARAM lParam);
	LRESULT OnMenuMessage(WPARAM wParam, LPARAM lParam);

public:
	virtual BOOL DoNext();
	void CmpDeviceFile(const CString& strFile);
	void UpdateDvmTitle(const CString& strText);
	void UpdateStandFile(const CString& strFile);
	virtual void OnInitialUpdate();
// 	virtual void SetMaxRange(long nMaxRange);
// 	virtual void ResetProcess();
// 	virtual void StepIt();
// 	virtual void ShowMsg(const CString &strMsg);
// 	virtual void Finish(DWORD dwParam=0);
// 	virtual void StartTimer(long nTimerLong);
	CDvmMapTool* GetDvmCmpTool() { return &m_oDvmCmpTool; }

	DECLARE_MESSAGE_MAP()
};

extern CWzdDlg_DvmMap* g_DvmMapDlg;