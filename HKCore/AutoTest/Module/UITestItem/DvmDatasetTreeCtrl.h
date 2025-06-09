#pragma once


// CDvmDatasetTreeCtrl
//#include "..\GuideBook\Device.h"
#include "..\GuideBook\GuideBook.h"

class CDvmDatasetTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CDvmDatasetTreeCtrl)

public:
	CDvmDatasetTreeCtrl();
	virtual ~CDvmDatasetTreeCtrl();
	void ShowDevice(CDevice *pDevice, CDvmDataset *pDsGlobalDatas);
	CListCtrl *m_pDatasetListCtrl;

	BOOL m_bShowTestPara;

	//2021-10-14  lijunqing
	void ShowDataset(CDataSet *pDataset, HTREEITEM hParent);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


