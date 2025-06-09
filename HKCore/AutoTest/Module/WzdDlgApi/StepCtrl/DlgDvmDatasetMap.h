#pragma once

#include "WzdDlgButton.h"
#include "..\..\..\iSmartTestWzd\Resource.h"
#include "..\..\..\..\Module\DataMngr\DvmCmp\DvmCmpDatasetMapPropGridCtrl.h"

#define ID_DVMCMP_GRID_STAND   0X4844
#define ID_DVMCMP_GRID_DEST    0X4845
// CDlgDvmDatasetMap 对话框

class CDlgDvmDatasetMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgDvmDatasetMap)

public:
	CDlgDvmDatasetMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDvmDatasetMap();

	CDvmCmpDsStandPropGridCtrl m_gridStand;
	CDvmCmpDsMapPropGridCtrl  m_gridDest;
	CExBaseList m_listDvmDsMapStand;
	CDvmDatasetMap *m_pDvmCmpObj;
	WPARAM m_wParam;
	LPARAM m_lParam;
	CString m_strTitle;

	CWzdDlgNormalBtn m_btnOK;

	void AdjustGrids(long cx, long cy);
	void DeleteMap(CDvmMapObject *pMap);
	void DeleteMap(CExBaseObject *pStand, CExBaseObject *pDest);

// 对话框数据
	enum { IDD = IDD_DIALOG_DATASET_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetDataMap(CExBaseList *pStandParent,CExBaseList *pDestParent,long nCount,long nStandGap,long nDestGap,long nStandIndex,long nDestIndex);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCreateDataMap_Stand();
	afx_msg void OnCreateDataMap_Dest();
	afx_msg void OnDeleteDataMap_Stand();
	afx_msg void OnDeleteDataMap_Dest();

	afx_msg void OnModifyDataMap_Stand();
	//afx_msg void OnModifyDataMap_Dest();
	afx_msg void OnConfirmDataMap_Stand();
	//afx_msg void OnConfirmDataMap_Dest();

	LRESULT OnDvmCmpGridStandPopDest(WPARAM wParam, LPARAM lParam);
	LRESULT OnDvmCmpGridDestPopStand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();

	void UpdateDvmCmpPropGridProperty();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
