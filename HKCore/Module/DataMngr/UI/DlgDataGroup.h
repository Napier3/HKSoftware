#pragma once
#include "afxcmn.h"

#include "DataGroupTreeCtrl.h"
#include "DataGroupListView.h"
#include "DataGroupGrid.h"
#include "afxwin.h"

#include "..\..\DialogBase\DynDialogEx.h"

// CDlgDataGroup 对话框

#define XDMF_IDC_TREE_DATAGROUP	         40001
#define XDMF_IDC_GRID_DATA               40002
#define XDMF_IDC_LIST_DATA               40003

class CDlgDataGroup : public CDynDialogEx, public CExBaseListGridOptrInterface
{
	DECLARE_DYNAMIC(CDlgDataGroup)

public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar);
	virtual void OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

public:
	CDlgDataGroup(const CString &strFile, const CString &strDatas,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDataGroup();

	CString m_strDatas;

	// 对话框数据
	enum { IDD };

protected:
	CDataGroup* m_pFolderSelect;
	CDataGroup  m_oFolderRoot;
	CDataTypes  m_oDataTypes;
	CExBaseList      m_listShortDatas;

	void CreateControls();

	void InitDestDatas();
	void InitByDestDatas();
	CShortData* FindData(const CString &strPath);
	CShortData* FindData(CDataGroup *pGroup, const CString &strPath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CDataGroupTreeCtrl m_folderTree;
	CDataGroupGrid m_gridDatas;
	CDataGroupListView m_listSelDatas;

	CButton m_btnOK;
	CButton m_btnCancel;

	virtual int DoModal(); 
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListData(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

};
