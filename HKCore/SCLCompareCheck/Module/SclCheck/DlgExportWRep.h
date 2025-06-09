#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"

#include "afxwin.h"


#define EXPORTREP_IDC_BUTTON_SCHEMA                 12022
#define EXPORTREP_IDC_BUTTON_DATATYPETMP            12023
#define EXPORTREP_IDC_BUTTON_APPMODEL               12024
#define EXPORTREP_IDC_BUTTON_VIRCIRCUIT             12025


class CDlgExportWRep : public CDynDialogEx
{
public:
	CDlgExportWRep(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgExportWRep();

	void CreateControls();
	void InitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CButton m_btnOk;
	CButton m_btnCancel;
	CButton m_btnSchema;
	CButton m_btnDataTypeTmp;
	CButton m_btnAppModel;
	CButton m_btnVirCircuit;
	BOOL m_bCheckSchema;
	BOOL m_bCheckDataTypeTmp;
	BOOL m_bCheckAppModel;
	BOOL m_bCheckVirCircuit;

protected:
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedCheckSchema();
	afx_msg void OnBnClickedCheckDataTypeTmp();
	afx_msg void OnBnClickedCheckAppModel();
	afx_msg void OnBnClickedCheckVirCircuit();

public:

};
