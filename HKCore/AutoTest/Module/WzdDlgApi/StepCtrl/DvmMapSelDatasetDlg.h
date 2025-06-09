#pragma once

#include "..\..\..\..\Module\DataMngr\DvmDeviceTree.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "WzdDlgButton.h"
#include "..\..\..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\..\..\Module\XLanguage\XLanguageButton.h"
#include "..\..\..\..\Module\DataMngr\DvmCmp\DvmDatasetMap.h"
#include "..\..\..\iSmartTestWzd\Resource.h"

// CDvmMap_SelDatasetDlg 对话框

class CDvmMap_SelDatasetDlg : public CDialog
{
	DECLARE_DYNAMIC(CDvmMap_SelDatasetDlg)

public:
	CDvmMap_SelDatasetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDvmMap_SelDatasetDlg();

	CDvmDevice  *m_pDvmDevice;
	CDvmDataset *m_pDvmDataset;
	CDvmDatasetMap *m_pDatasetMap;

	//void xlang_InitAndAdjust();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELDATASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDvmDeviceTree m_treeDvmDevice;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDvmTreeSelObjChanged(WPARAM wParam, LPARAM lParam);
	CWzdDlgNormalBtn m_btnOK;
	CWzdDlgNormalBtn m_btnSeldataSelCancel;
	afx_msg void OnBnClickedCancel();
	BOOL HasSameMap();
};
