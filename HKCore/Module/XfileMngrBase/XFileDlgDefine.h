#pragma once

#include "../DialogBase/DynDialogEx.h"

#define XFID_XFILEMNGR_FOLDER_ADD        0X0001000
#define XFID_XFILEMNGR_FOLDER_DELETE     0X0001001
#define XFID_XFILEMNGR_FOLDER_EDIT       0X0001002
#define XFID_XFILEMNGR_FOLDER_EXPORT     0X0001003
#define XFID_XFILEMNGR_FOLDER_IMPORT     0X0001004
#define XFID_XFILEMNGRFILE_COPY          0X0001005
#define XFID_XFILEMNGRFILE_PASTE         0X0001006
#define XFID_XFILEMNGRFILE_DELETE        0X0001007
#define XFID_XFILEMNGRFILE_EDIT          0X0001008
#define XFID_XFILEMNGRFILE_EXPORT        0X0001009
#define XFID_XFILEMNGRFILE_IMPORT        0X000100A
#define XFID_XFILEMNGRFILE_DOWNLOAD        0X000100B
#define XFID_XFILEMNGRFILE_UPLOAD        0X000100C

#define XFIDC_EDIT_SRC_NAME      0X00002001
#define XFIDC_EDIT_DEST_NAME     0X00002002
#define XFIDC_EDIT_INFOR         0X00002003
#define XFID_OVERWRITE           0X00002004
#define XFIDC_TITLE_SRC_NAME     0X00002005
#define XFIDC_TITLE_DEST_NAME    0X00002006

#define XFID_STCFGFILE_VIEW_TREE		    0X00002007
#define XFID_STCFGFILE_VIEW_CMB_FILTER	0X00002008
#define XFID_STCFGFILE_VIEW_BTN_FILTER	0X00002009
#define XFIDC_TREE_FOLDER	                0X0000200A
#define XFIDC_EDIT_FILENAME	            0X0000200B
#define XFIDC_LIST_FILE	                0X0000200C

#define XFID_XFILEMNGR_PUBLISH_ADD		0X0000200D

#define WM_THREAD_XFILE_MNGR      (WM_USER + 1027)
#define WM_INIT_XFILEMNGR_MENU    (WM_USER + 1028)
#define WM_XFILEMNGR_OPEN_XFILE   (WM_USER + 1029)


#define WM_XFILEMNGR_DELETE_XFILE (WM_USER + 1030)
#define WM_XFILEMNGR_EXPORT_XFILE (WM_USER + 1031)
#define XFILEMNGR_OPTR_FAILED  0X00FFFFFF
#define XFILEMNGR_OPTR_SUCC    0X00777777

class CXFile;
class CXFolder;
class CXFileMngr;
class CXFileOptrMsgRcvWnd;
class CXFolderTreeCtrl;
class CXFileListView;
// 
// class CXFileMngrOptrInterface
// {
// public:
// 	CXFileMngrOptrInterface();
// 	virtual ~CXFileMngrOptrInterface();
// 
// protected:
// 	CXFileMngr          *m_pXFileMngrRef;
// 	CXFileOptrMsgRcvWnd *m_pXFileMsgRcvWndRef;
// 	CXFolderTreeCtrl    *m_pXFolderTreeRef;
// 	CXFileListView      *m_pXFileListRef;
// 	BOOL                m_bDeleteAllFolder;
// 	CWnd                *m_pXFileMngrWnd;
// 
// 	CString             m_strXFilePostFix;
// 	CString             m_strXFileFilter;
// 
// public:
// 	void xfile_OnSaveAsFile(CXFolder *pCurrFolder, const CString &strFile);
// 	afx_msg LRESULT xfile_OnInitXFileMngrMenu(WPARAM wParam, LPARAM lParam);
// 
// 	afx_msg void xfile_OnUpdateFolderAdd(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFolderAdd();
// 	afx_msg void xfile_OnUpdateFolderDelete(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFolderDelete();
// 	afx_msg void xfile_OnUpdateFolderEdit(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFolderEdit();
// 	afx_msg void xfile_OnUpdateFolderExport(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFolderExport();
// 	afx_msg void xfile_OnUpdateFolderImport(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFolderImport();
// 	afx_msg void xfile_OnUpdateFileCopy(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFileCopy();
// 	afx_msg void xfile_OnUpdateFilePaste(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFilePaste();
// 	afx_msg void xfile_OnUpdateFileDelete(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFileDelete();
// 	afx_msg void xfile_OnUpdateFileEdit(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFileEdit();
// 	afx_msg void xfile_OnUpdateFileExport(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFileExport();
// 	afx_msg void xfile_OnUpdateFileImport(CCmdUI* pCmdUI);
// 	afx_msg void xfile_OnFileImport();
// 	afx_msg void xfile_OnTvnSelchangedXFile(NMHDR *pNMHDR, LRESULT *pResult);
// 	afx_msg void xfile_OnFileFilter();
// 	afx_msg void xfile_OnUpdateFileFilter(CCmdUI* pCmdUI);
// };
// 
