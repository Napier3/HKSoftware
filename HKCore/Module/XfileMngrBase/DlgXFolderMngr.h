#pragma once

#include "DlgXFileMngr.h"

class CDlgXFolderMngr : public CDynDialogEx
{
	DECLARE_DYNAMIC(CDlgXFolderMngr)

public:
	CDlgXFolderMngr(UINT nIDTemplate,const CString& strFilePostFix,const CString& strPostFixDes,CXFileMngr* pFileMngrBase,UINT nMode = OPEN_FILE_MODE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgXFolderMngr();

	// 对话框数据
	enum { IDD };

protected:
	static char g_pszFileName[MAX_PATH];
	CToolTipCtrl m_ToolTip;
	CXFileMngr* m_pFileMngrBase;
	CBmpImageList m_oImageList;
	void CreateControls();

public:
	CString GetFileName();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CXFolderTreeCtrl m_folderTree;
	CButton m_btnOK;
	CButton m_btnCancel;
	CString m_strSelPath;

	virtual int DoModal(); 
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT OnChangeStaticPath(WPARAM wParam,LPARAM lParam);
	virtual void OnCancel();
};
