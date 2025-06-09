#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "WzdDlgButton.h"
#include "..\..\..\..\module\filtertext\filtertextcombobox.h"
#include "..\..\..\..\Module\MfcCtrlEx\NumberComboBox.h"
#include "..\..\..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\..\..\Module\XLanguage\XLanguageButton.h"
#include "..\..\..\..\Module\DataMngr\DvmData.h"
#include "..\..\..\..\Module\DataMngr\DvmValue.h"
#include "..\..\..\..\Module\DataMngr\DvmDataset.h"
#include "..\..\..\..\Module\DataMngr\DvmCmp\DvmMapObject.h"
#include "..\..\..\iSmartTestWzd\Resource.h"

class CDvmDatasetTreeCtrl : public CTreeCtrl
{
public:
	CDvmDatasetTreeCtrl();
	virtual ~CDvmDatasetTreeCtrl();

	CExBaseObject *m_pSelDvmObject;
	HTREEITEM m_hSelDvmItem;
	void ShowDataset(CExBaseList *pListDs);

protected:
	void ShowDataset(CDvmDataset *pDataset, HTREEITEM hParent);
	void ShowData(CDvmData *pData, HTREEITEM hParent);
	void ShowValues(CDvmValue *pValue, HTREEITEM hParent);
};

// CDvmMap_SelDataDlg 对话框

class CDvmMap_SelDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CDvmMap_SelDataDlg)

public:
	CDvmMap_SelDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDvmMap_SelDataDlg();

	CExBaseList m_listDataset;
	void AddDataset(CDvmDataset *pDataset);
	void AppendDataset(CExBaseList *pList);

	CDvmMapObject *m_pSelMapObject;
	CExBaseObject *m_pSelDvmObject;
	CExBaseObject *m_pDvmMapSrcObject;
	long m_nMatchCount;
	long m_nGapStand;
	long m_nGapDest;

	void EnableOkButton();

	CFilterTextMngr m_oFilterTextMngr;

	void xlang_InitAndAdjust();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDvmDatasetTreeCtrl m_treeDataset;
	CWzdDlgNormalBtn m_btnOK;
	afx_msg void OnTvnSelchangedTreeDatasets(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMatchMore();
	CNumberComboBox m_cmbNumber;
	CFilterTextComboBox m_cmbKeySel;
	CWzdDlgNormalBtn m_btnMatchMore;
	CNumberComboBox m_cmbGapStand;
	CNumberComboBox m_cmbGapDest;
	afx_msg void OnBnClickedBtnFind();
	CXLanguageTextWnd m_xFrameSearchData;
	CWzdDlgNormalBtn m_btnSeldataFind;
	CXLanguageTextWnd m_xFrameSelDataMatch;
	CXLanguageTextWnd m_wndSelDataStanBlank;
	CXLanguageTextWnd m_wndSelDataGeBlank;
	CXLanguageTextWnd m_wndSelDataGe;
	CXLanguageTextWnd m_wndSelDataGe2;
	CWzdDlgNormalBtn m_btnSelDataCancel;
	afx_msg void OnBnClickedCancel();
};
