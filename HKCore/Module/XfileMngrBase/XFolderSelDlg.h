#pragma once

#include "XFileDlgDefine.h"
#include "XFileMngr.h"
#include "XFolderTreeCtrl.h"

// CXFolderSelDlg 对话框

class CXFolderSelDlg : public CDynDialogEx
{
	//DECLARE_DYNAMIC(CXFolderSelDlg)

public:
	CXFolderSelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXFolderSelDlg();
	
	CXFileMngr *m_pXFileMngr;
	CXFolder *m_pSrcFolder;
	void EnableOkButton();

// 对话框数据

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CButton m_btnOK;
	CButton m_btnCancel;
	CXFolderTreeCtrl m_treeFolder;
	CImageList *m_pImgFolder;//周宏军 20200228 用于增加树形控件的文件夹图标

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	afx_msg LRESULT OnXFileMngrSelChanged(WPARAM wParam, LPARAM lParam);

};
