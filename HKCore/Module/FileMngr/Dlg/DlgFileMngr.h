#pragma once
#include "afxcmn.h"

#include "FolderViewTreeCtrl.h"
#include "FileViewListCtrl.h"
#include "afxwin.h"

#include "..\..\DialogBase\DynDialogEx.h"
#include "..\..\FilterText\FilterTextMngr.h"
#include "..\..\Module\FilterText\FilterTextComboBox.h"

#include "DlgFileNameGen.h"

// CDlgFileMngr 对话框

#define OPEN_FILE_MODE 0		//打开模式
#define SAVE_FILE_MODE 1		//保存模式

UINT UI_GetImgeListID();

//下面的消息用于本对话框与App类(如CPpDev)和父窗口进行通信
//可根据需要添加
#define WM_THREAD_DLG_FILE_MNGR		WM_USER + 5101
#define WM_PARENT_SAVE_XML_FILE			WM_USER + 5102
#define WM_PARENT_OPEN_XML_FILE		WM_USER + 5103

#define XIDC_TREE_FOLDER	         40001
#define XIDC_LIST_FILE               40002
#define XIDC_COMBO_FILE_TYPE         40003
#define XIDC_EDIT_FILE_NAME          40004
#define XIDC_STATIC_PATH             40005
#define XIDC_STATIC_PATH_TITLE       40006
#define XIDC_EDIT_FILE_NAME_TITLE    40007
#define XIDC_FILE_TYPE_TITLE         40008
#define XIDC_EDIT_HISTORY_TITLE      40009
#define XIDC_COMBO_HISTORY           40010
#define XIDC_BTN_GO                  40011
#define XIDC_EDIT_FILE_NAME_GEN      40012

//获取框架类指针
CFrameWndEx* UI_GetFrameWndEx(CWnd* pWnd);

class CDlgFileMngr : public CDynDialogEx
{
	DECLARE_DYNAMIC(CDlgFileMngr)

public:
	CDlgFileMngr(UINT nIDTemplate,const CString& strFilePostFix,const CString& strPostFixDes,CFileMngrBase* pFileMngrBase,UINT nMode = OPEN_FILE_MODE,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFileMngr();

	// 对话框数据
	enum { IDD };

protected:
	CToolTipCtrl m_ToolTip;
	CImageList m_ImgetList;	
	CString m_strFilePostfix;											//文件后缀
	CString m_strPostFixDes;
	long m_nMode;
	BOOL m_bIsSaveAs;	//是否是另存为模式

	CFileBase* m_pFileSelect;	//当前选择的文件
	CFileMngrBase* m_pFileMngrBase;

	void InitTypeComboBox();
	BOOL SaveXmlFile();
	BOOL OpenXmlFile();

	static char g_pszFileName[MAX_PATH];
	void CreateControls();

	CString m_strHistoryMngrFile;
	CFilterTextMngr m_oFilterTextMngr;
	void SelectFile(CFilterText *pFilter);
	void ShowSelectFile(CFileBase *pFile);
	void InitHistoryCmboBox();
	CString m_strTrim;

	CString m_strFileNameGenConfigPath;

public:
	CString GetFileName();
	void SetSaveAs(BOOL bSaveAs)	{	m_bIsSaveAs = bSaveAs;	}
	BOOL GetSaveAs()	{	return m_bIsSaveAs;	}
	void InitHistory(const CString &strFileName, const CString &strTrim=_T(""));
	void SetFileNameGenConfigPath(const CString &strPath)	{	m_strFileNameGenConfigPath = strPath;	}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CFolderViewTreeCtrl m_folderTree;
	CFileViewListCtrl m_fileListCtrl;
	CComboBox m_comboBoxType;
	CEdit m_editPath;
	CStatic m_stcStaticPathTitle;
	CString m_strStaticPath;
	CString m_strFileName;
	CStatic m_stcFileNameTitle;
	CStatic m_stcFileTypeTitle;
	CStatic m_stcHistoryTitle;
	CEdit m_editFileName;
	CComboBox m_cmbHistory;

	CButton m_btnGO;
	CButton m_btnOK;
	CButton m_btnCancel;
	CButton m_btnFileNameGen;

	virtual int DoModal(); 
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFileNameGen();
	afx_msg void OnBnClickedGO();
	afx_msg void OnBnClickedOpenOtherFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditFileName();
	LRESULT OnChangeStaticPath(WPARAM wParam,LPARAM lParam);
	virtual void OnCancel();
	afx_msg void OnCbnSelchangeHistory();
};

CString DlgFile_GetOpenFile(const CString &strFileType, const CString &strFileDes, CWnd *pParent, CFileMngrBase *pFileMngr);
