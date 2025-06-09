//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndFileMngr.h  CUIWndFileMngr

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"
#include "UIBaseFileTypes.h"

#include "..\XfileMngrBase\XFolderTreeCtrl.h"
#include "..\XfileMngrBase\XFileListView.h"
#include "..\XfileMngrBase\XFileMngr.h"

#define UI_IDC_TREE_FOLDER   1959
#define UI_IDC_LIST_FILE     1960

class CUIWndFileMngr : public CStatic, public CUIWindowBase
{
public:
	CUIWndFileMngr();
	virtual ~CUIWndFileMngr();


	long  m_nTreeViewWidthRate;
	long  m_nTreeViewWidthMax;

protected:
	static CString g_strWndAttrID_FolderSel;
	static CString g_strWndAttrID_FileSel;


//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDFILEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndFileMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();
	virtual long ExecWndCmd(const CString &strCmd, const CString &strPara);
	virtual long GetWndAttr(const CString &strAttrID, CString &strAttrValue);
	virtual long SetWndAttr(const CString &strAttrID, const CString &strAttrValue);

//私有成员变量
private:
	CUIBaseFileTypes *m_pFileTypes;
	//CDib		   m_oDib;

	CXFolderTreeCtrl m_folderTree;
	CXFileListView m_fileListCtrl;
// 	CXFile* m_pFileSelect;	//当前选择的文件
	CString m_strFileName;
	CXFileMngr m_oXFileMngr;

	void AdjustWndSize(int cx, int cy);
	void ExecXFile(CXFile *pFile);

//私有成员变量访问方法
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIWndFileMngr)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	void LoadUIBitmap();
	//{{AFX_MSG(CUIWndFileMngr)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnXFileSelChanged(WPARAM wParam, LPARAM lParam);

	afx_msg void OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult);
// 	afx_msg void OnNMClickListFile(NMHDR *pNMHDR, LRESULT *pResult);
// 	afx_msg void OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateFolderAdd(CCmdUI* pCmdUI);
	afx_msg void OnFolderAdd();
	afx_msg void OnUpdateFolderDelete(CCmdUI* pCmdUI);
	afx_msg void OnFolderDelete();
	afx_msg void OnUpdateFolderEdit(CCmdUI* pCmdUI);
	afx_msg void OnFolderEdit();
	afx_msg void OnUpdateFolderExport(CCmdUI* pCmdUI);
	afx_msg void OnFolderExport();
	afx_msg void OnUpdateFolderImport(CCmdUI* pCmdUI);
	afx_msg void OnFolderImport();
	afx_msg void OnUpdateFileCopy(CCmdUI* pCmdUI);
	afx_msg void OnFileCopy();
	afx_msg void OnUpdateFilePaste(CCmdUI* pCmdUI);
	afx_msg void OnFilePaste();
	afx_msg void OnUpdateFileDelete(CCmdUI* pCmdUI);
	afx_msg void OnFileDelete();
	afx_msg void OnUpdateFileEdit(CCmdUI* pCmdUI);
	afx_msg void OnFileEdit();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileImport(CCmdUI* pCmdUI);
	afx_msg void OnFileImport();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

