#pragma once
#include "afxwin.h"
#include "XKeyDBUiGlobal.h"

#include "XBaseKeyDlg.h"
#include "XMultiKeyDlg.h"
#include "XAnalyzeDlg.h"

// CXKeyDbDlg 对话框
#include "..\..\Module\FilterText\FilterTextComboBox.h"


class CXKeyDbDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXKeyDbDlg)

public:
	CXKeyDbDlg(CXKeyDB *pXKeyDB, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXKeyDbDlg();

	void SetXKeyDB(CXKeyDB *pXKeyDb)
	{
		m_pKeyDb = pXKeyDb;
	}

	BOOL m_bKeyDbChanged;

protected:
	CXKeyDB *m_pKeyDb;
	CFilterTextMngr m_oFilterTextMngr;
	CExBaseObject m_oXKeyAnalyse;

	UINT m_nPopKeyDlgMode;
	CExBaseObject *m_pCurrSelKey;
	int m_nCurrSelIndex;

	CString m_strKeyDbPath;

	//操作
	//CString SearchKeyDbname(const CString &strXmlPath);
	void OpenXml(const CString &strXmlName);
	void SaveXml(const CString &strXmlName);
	void ShowList();
	void InsertXKeys(CExBaseList *pList, long &nIndex);
	void InsertXKey(CExBaseObject *pKey, long nIndex);
	void UpdateXKey(CExBaseObject *pKey, long nIndex);

	void PopDlg(CExBaseObject *pKey);
	void PopBaseKeyDlg(CExBaseObject *pKey);
	void PopMultiKeyDlg(CExBaseObject *pKey);

	void UpdateList(CExBaseObject *pKey,const int &nIndex);
	void AddNewKey(CExBaseObject *pKey);

	void KeySelectSimple(CExBaseObject *pKeyBase,const int &nBegin);
	void InsertListKeyDb();



	virtual BOOL OnInitDialog();
	void CreateControls();

public:
	virtual int DoModal();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	//CButton m_btnFileSave;
	CButton m_btnFilter;
	CButton m_btnBaseKeyNew;
	CButton m_btnMultiKeyNew;
	CButton m_btnGroupKeyNew;
	CButton m_btnDeleteKey;
	CButton m_btnSelectSameKey;
	CButton m_btnCinKeyDb;
	CButton m_btnAnalyze;

	CEdit m_editAnalyze;
	CString m_strAnalyze;

	CFilterTextComboBox m_combFilterKey;
	CListCtrl m_listKeyDB;

	//afx_msg void OnBnClickedBtnFilesave();

	afx_msg void OnBnClickedBtnBasekeynew();
	afx_msg void OnBnClickedBtnMultikeynew();
	afx_msg void OnBnClickedBtnKeydelete();

	afx_msg void OnBnClickedBtnFilter();
	afx_msg void OnDestroy();

	afx_msg void OnNMDblclkListKeydb(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListKeydb(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnValidateXkeyDb();
	afx_msg void OnBnClickedBtnInportkeydb();
	afx_msg void OnBnClickedBtnAnalyze();

};
