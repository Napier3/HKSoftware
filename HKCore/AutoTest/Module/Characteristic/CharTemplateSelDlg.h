#pragma once

#include "CharLibTreeCtrl.h"

#include "..\..\..\Module\DialogBase\DynDialogEx.h"

#define IDC_CHARTEMPLATESEL_TREE	         40001

// CCharTemplateSelDlg �Ի���

class CCharTemplateSelDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CCharTemplateSelDlg)

public:
	CCharTemplateSelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCharTemplateSelDlg();

	CCharacteristicLib *m_pCharLib;
	CCharacteristic *m_pCharTemp;
	void InitImageList(UINT nBmpID);

protected:
	CImageList m_CharLibViewImages;
	void EnableOKButton();
	void CreateControls();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	virtual BOOL OnInitDialog();
	CButton m_btnOK;
	CButton m_btnCancel;
	CCharLibTreeCtrl m_treeCharTemplate;

protected:
	
public:
	afx_msg void OnTvnSelchangedTreeFolder(NMHDR *pNMHDR, LRESULT *pResult);
};
