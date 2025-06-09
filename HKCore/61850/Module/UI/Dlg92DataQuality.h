#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\..\..\module\mfcctrlex\hexedit.h"
#include "..\..\..\Module\DataMngr\DataTypeComboBox.h"

#include "..\CfgDataMngr\IecCfg92ChQuality.h"

#include "afxwin.h"
// CDlg92DataQuality 对话框

#define IECFG_IDC_EDIT_QUALITY             8700
#define IECFG_IDC_CMB_VALIDITY             8701
#define IECFG_IDC_CMB_OVERFLOW             8702
#define IECFG_IDC_CMB_OUTOFRANGE           8703
#define IECFG_IDC_CMB_BADREFRENCE          8704
#define IECFG_IDC_CMB_OCILLATORY           8705
#define IECFG_IDC_CMB_FAILURE              8706
#define IECFG_IDC_CMB_OLDDATA              8708
#define IECFG_IDC_CMB_INCONSISTENT         8709
#define IECFG_IDC_CMB_INACCURATE           8710
#define IECFG_IDC_CMB_SOURCE               8711
#define IECFG_IDC_CMB_TEST                 8712
#define IECFG_IDC_CMB_OPB                  8713
#define IECFG_IDC_BUTTON_SET               8714
#define IECFG_IDC_BUTTON_CHK_ALL           8715

#define IECFG_IDC_EDIT_QUALITY_TITLE             8800
#define IECFG_IDC_CMB_VALIDITY_TITLE             8801
#define IECFG_IDC_CMB_OVERFLOW_TITLE             8802
#define IECFG_IDC_CMB_OUTOFRANGE_TITLE           8803
#define IECFG_IDC_CMB_BADREFRENCE_TITLE          8804
#define IECFG_IDC_CMB_OCILLATORY_TITLE           8805
#define IECFG_IDC_CMB_FAILURE_TITLE              8806
#define IECFG_IDC_CMB_OLDDATA_TITLE              8808
#define IECFG_IDC_CMB_INCONSISTENT_TITLE         8809
#define IECFG_IDC_CMB_INACCURATE_TITLE           8810
#define IECFG_IDC_CMB_SOURCE_TITLE               8811
#define IECFG_IDC_CMB_TEST_TITLE                 8812
#define IECFG_IDC_CMB_OPB_TITLE                  8813
#define IECFG_IDC_BUTTON_SET_TITLE               8814



class CDlg92DataQuality : public CDynDialogEx
{
public:
	CDlg92DataQuality(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg92DataQuality();

	DWORD m_dwQuality;

	void CreateControls();
	
	void ShowQuality();
	void SaveQuality();
	void ShowHexQuality();

	CWinThread *m_pInitThread;
	static UINT InitDialogThread(LPVOID lpPara);
	void InitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CDataTypeComboBox m_cmbValidity;
	CDataTypeComboBox m_cmbOverflow;
	CDataTypeComboBox m_cmbOutOfRange;
	CDataTypeComboBox m_cmbBadReference;
	CDataTypeComboBox m_cmbOscillatory;
	CDataTypeComboBox m_cmbFailure;
	CDataTypeComboBox m_cmbOldData;
	CDataTypeComboBox m_cmbInconsistent;
	CDataTypeComboBox m_cmbInaccurate;
	CDataTypeComboBox m_cmbSource;
	CDataTypeComboBox m_cmbTest;
	CDataTypeComboBox m_cmbOpb;

	CStatic m_stcValidity;
	CStatic m_stcOverflow;
	CStatic m_stcOutOfRange;
	CStatic m_stcBadReference;
	CStatic m_stcOscillatory;
	CStatic m_stcFailure;
	CStatic m_stcOldData;
	CStatic m_stcInconsistent;
	CStatic m_stcInaccurate;
	CStatic m_stcSource;
	CStatic m_stcTest;
	CStatic m_stcOpb;

	CButton m_btnOK;
	CButton m_btnCancel;
	CButton m_btnCheckAll;
	CButton m_btnSet;
	CHexEdit m_hexQuality;
	
	BOOL m_bEditAll;
	static BOOL m_bHasShowDlg;//zhouhj 20211123 判断该对话框是否已显示
protected:
	virtual void OnOK();
	virtual void OnCancel();

public:
	afx_msg void OnEnChangeEditquality();
	afx_msg void OnCbnSelchangeCmbValidity();
	afx_msg void OnCbnSelchangeCmbOverflow();
	afx_msg void OnCbnSelchangeCmbOutofrange();
	afx_msg void OnCbnSelchangeCmbBadrefrence();
	afx_msg void OnCbnSelchangeCmbOcillatory();
	afx_msg void OnCbnSelchangeCmbFailure();
	afx_msg void OnCbnSelchangeCmbOlddata();
	afx_msg void OnCbnSelchangeCmbInconsistent();
	afx_msg void OnCbnSelchangeCmbInaccurate();
	afx_msg void OnCbnSelchangeCmbSource();
	afx_msg void OnCbnSelchangeCmbTest();
	afx_msg void OnCbnSelchangeCmbOpb();
	afx_msg void OnBnClickedButtonSet();
};
