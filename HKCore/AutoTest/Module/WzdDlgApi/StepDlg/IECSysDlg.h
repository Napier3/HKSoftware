#pragma once
#include "WzdDlgBase.h"
#include "..\..\..\..\61850\Module\IecCfgTool\IecCfgFile.h"
#include "..\..\..\..\Module\MfcCtrlEx\NumberEdit.h"
#include "..\..\..\iSmartTestWzd\Resource.h"

#define IECCFG_SYSPARAS_VIEW_VOLT_TYPE            0
#define IECCFG_SYSPARAS_VIEW_CURR_TYPE            1

#define IECCFG_SYSPARAS_VIEW_PRIM_TYPE            0
#define IECCFG_SYSPARAS_VIEW_SECOND_TYPE          1

class CIECSysDlg : public CWzdDlgBase
{
	DECLARE_DYNCREATE(CIECSysDlg)

public:
	CIECSysDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CIECSysDlg();

public:
	enum { IDD = IDD_IECCFG_SYS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbPkgSendType;
	int m_nLC_Fiber[IECCFG_MAX_LC_FIBER_NUM];
	int m_nST_Fiber[IECCFG_MAX_ST_FIBER_NUM];
	CNumberEdit m_edtPrimPT[IECCFG_MAX_PT_CT_NUM];
	CNumberEdit m_edtSecPT[IECCFG_MAX_PT_CT_NUM];
	CNumberEdit m_edtPrimCT[IECCFG_MAX_PT_CT_NUM];
	CNumberEdit m_edtSecCT[IECCFG_MAX_PT_CT_NUM];
	virtual void OnInitialUpdate();

private:
	void SetFiberValue(const CString &strID,const long &nValue);
	void SetPrimRateValue(int nGroupIndex,int nVoltCurType,int nPrimSecondType,float fValue);
	CIecCfgSysParas *m_pSysParas;
	CIecCfgFiberParas *m_pFiberParas;
	CIecCfgPrimRates *m_pPrimRates;
	CComboBox m_cmbParasSetSel;

protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

public:
	CIecCfgFile *m_pIecCfgFile;

	void InitUI();
	void UpdateDatas(CIecCfgFile* pIecCfgFile);
	afx_msg void OnCbnSelchangeComboPkgSendType();
	afx_msg void OnBnClickedRadio100mFiber1();
	afx_msg void OnBnClickedRadio1000mFiber1();
	afx_msg void OnBnClickedRadio100mFiber2();
	afx_msg void OnBnClickedRadio1000mFiber2();
	afx_msg void OnBnClickedRadio100mFiber3();
	afx_msg void OnBnClickedRadio1000mFiber3();
	afx_msg void OnBnClickedRadio100mFiber4();
	afx_msg void OnBnClickedRadio1000mFiber4();
	afx_msg void OnBnClickedRadioBcodeFiber1();
	afx_msg void OnBnClickedRadioFt3Fiber1();
	afx_msg void OnBnClickedRadioBcodeFiber2();
	afx_msg void OnBnClickedRadioFt3Fiber2();
	afx_msg void OnBnClickedRadioBcodeFiber3();
	afx_msg void OnBnClickedRadioFt3Fiber3();
	afx_msg void OnBnClickedRadioBcodeFiber4();
	afx_msg void OnBnClickedRadioFt3Fiber4();
	afx_msg void OnBnClickedRadioBcodeFiber5();
	afx_msg void OnBnClickedRadioFt3Fiber5();
	afx_msg void OnBnClickedRadioBcodeFiber6();
	afx_msg void OnBnClickedRadioFt3Fiber6();
	afx_msg void OnEnUpdateEditPrimPtRate1();
	afx_msg void OnEnUpdateEditSecondPtRate1();
	afx_msg void OnEnUpdateEditPrimCtRate1();
	afx_msg void OnEnUpdateEditSecondCtRate1();
	afx_msg void OnEnUpdateEditPrimPtRate2();
	afx_msg void OnEnUpdateEditSecondPtRate2();
	afx_msg void OnEnUpdateEditPrimCtRate2();
	afx_msg void OnEnUpdateEditSecondCtRate2();

	afx_msg void OnEnUpdateEditPrimPtRate3();
	afx_msg void OnEnUpdateEditSecondPtRate3();
	afx_msg void OnEnUpdateEditPrimCtRate3();
	afx_msg void OnEnUpdateEditSecondCtRate3();

	afx_msg void OnEnUpdateEditPrimPtRate4();
	afx_msg void OnEnUpdateEditSecondPtRate4();
	afx_msg void OnEnUpdateEditPrimCtRate4();
	afx_msg void OnEnUpdateEditSecondCtRate4();

	afx_msg void OnEnUpdateEditPrimPtRate5();
	afx_msg void OnEnUpdateEditSecondPtRate5();
	afx_msg void OnEnUpdateEditPrimCtRate5();
	afx_msg void OnEnUpdateEditSecondCtRate5();

	afx_msg void OnEnUpdateEditPrimPtRate6();
	afx_msg void OnEnUpdateEditSecondPtRate6();
	afx_msg void OnEnUpdateEditPrimCtRate6();
	afx_msg void OnEnUpdateEditSecondCtRate6();

	afx_msg void OnCbnSelchangeComboParasSetSel();
};


