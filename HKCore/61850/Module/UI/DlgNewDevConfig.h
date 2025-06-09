#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"

#include "afxwin.h"
// CDlgSmvRate 对话框
#define IECFG_IDC_BUTTON_AUTO_CONFIG             12020
#define IECFG_IDC_BUTTON_NEW_DEVICE             12021
#define IECFG_IDC_BUTTON_CHOOSEPATH             12017
#define XIDC_STATIC_TITLE           12018
#define XIDC_EDIT_PATH           12019

#define IECFG_IDC_BUTTON_MODPATH             12025
#define IECFG_IDC_BUTTON_AUTOSAVE             12022
#define XIDC_STATIC_NEW           12023
#define XIDC_EDIT_PATHNEW           12024

class CDlgNewDevConfig : public CDynDialogEx
{
public:
	CDlgNewDevConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewDevConfig();

	void CreateControls();

	void InitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_btnAutoConfig;
	CButton m_btnNewDevice;
	CButton m_btnBrowse;

	CEdit m_editPath;
	CStatic m_stcTitle;
	CString m_strStaticPath;

	CStatic m_stcNew;
	CEdit m_editPathNew;
	CString m_strStaticPathNew;
	CButton m_btnModPath;
	CButton m_btnAutoSave;
	BOOL m_bAutoSave;



protected:
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedBrowse();

	afx_msg void OnBnClickedModPath();
	afx_msg void OnBnClickedAutoSave();

public:

};
