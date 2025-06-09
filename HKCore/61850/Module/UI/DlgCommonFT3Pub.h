#pragma once

#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "..\..\..\module\mfcctrlex\hexedit.h"
#include "..\..\..\Module\DataMngr\DataTypeComboBox.h"

#include "..\CfgDataMngr\IecCfg92ChQuality.h"

#include "afxwin.h"
// CDlg92DataQuality 对话框

#define IECCFG_COMMON_FT3_BIT_NUM                16

#define IECFG_IDC_CMB_BIT0                       8201
#define IECFG_IDC_CMB_BIT1                       8202
#define IECFG_IDC_CMB_BIT2                       8203
#define IECFG_IDC_CMB_BIT3                       8204
#define IECFG_IDC_CMB_BIT4                       8205
#define IECFG_IDC_CMB_BIT5                       8206
#define IECFG_IDC_CMB_BIT6                       8207
#define IECFG_IDC_CMB_BIT7                       8208
#define IECFG_IDC_CMB_BIT8                       8209
#define IECFG_IDC_CMB_BIT9                       8210
#define IECFG_IDC_CMB_BIT10                      8211
#define IECFG_IDC_CMB_BIT11                      8212
#define IECFG_IDC_CMB_BIT12                      8213
#define IECFG_IDC_CMB_BIT13                      8214
#define IECFG_IDC_CMB_BIT14                      8215
#define IECFG_IDC_CMB_BIT15                      8216


#define IECFG_IDC_CMB_BIT0_TITLE                 8301
#define IECFG_IDC_CMB_BIT1_TITLE                 8302
#define IECFG_IDC_CMB_BIT2_TITLE                 8303
#define IECFG_IDC_CMB_BIT3_TITLE                 8304
#define IECFG_IDC_CMB_BIT4_TITLE                 8305
#define IECFG_IDC_CMB_BIT5_TITLE                 8306
#define IECFG_IDC_CMB_BIT6_TITLE                 8307
#define IECFG_IDC_CMB_BIT7_TITLE                 8308
#define IECFG_IDC_CMB_BIT8_TITLE                 8309
#define IECFG_IDC_CMB_BIT9_TITLE                 8310
#define IECFG_IDC_CMB_BIT10_TITLE                8311
#define IECFG_IDC_CMB_BIT11_TITLE                8312
#define IECFG_IDC_CMB_BIT12_TITLE                8313
#define IECFG_IDC_CMB_BIT13_TITLE                8314
#define IECFG_IDC_CMB_BIT14_TITLE                8315
#define IECFG_IDC_CMB_BIT15_TITLE                8316



class CDlgCommonFT3Pub : public CDynDialogEx
{
public:
	CDlgCommonFT3Pub(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCommonFT3Pub();

	DWORD m_dwValue;

	void CreateControls();
	
	void ShowQuality();
	void SaveQuality();
	void ShowHexQuality();
	virtual void InitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CDataTypeComboBox m_cmbBitValue[IECCFG_COMMON_FT3_BIT_NUM];
	CStatic m_stcBitValue[IECCFG_COMMON_FT3_BIT_NUM];

	CButton m_btnOK;
	CButton m_btnCancel;
	static BOOL m_bHasShowDlg;
	
protected:
	virtual void OnOK();
	virtual void OnCancel();

public:

};
